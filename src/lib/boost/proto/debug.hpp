///////////////////////////////////////////////////////////////////////////////
/// \file debug.hpp
/// Utilities for debugging Proto expression trees
//
//  Copyright 2008 Eric Niebler. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PROTO_DEBUG_HPP_EAN_12_31_2006
#define BOOST_PROTO_DEBUG_HPP_EAN_12_31_2006

#include <boost/preprocessor/iteration/local.hpp>
#include <boost/preprocessor/repetition/repeat.hpp>
#include <boost/preprocessor/stringize.hpp>
#include <iomanip>
#include <iostream>
#include <typeinfo>
#include <boost/mpl/assert.hpp>
#include <boost/proto/proto_fwd.hpp>
#include <boost/proto/expr.hpp>
#include <boost/proto/traits.hpp>
#include <boost/proto/matches.hpp>
#include <boost/proto/detail/dont_care.hpp>

namespace boost { namespace proto
{
    namespace tag
    {
    #define BOOST_PROTO_DEFINE_TAG_INSERTION(Tag)                               \
        /** \brief INTERNAL ONLY */                                             \
        inline std::ostream &operator <<(std::ostream &sout, Tag const &)       \
        {                                                                       \
            return sout << BOOST_PP_STRINGIZE(Tag);                             \
        }                                                                       \
        /**/

        BOOST_PROTO_DEFINE_TAG_INSERTION(terminal)
        BOOST_PROTO_DEFINE_TAG_INSERTION(unary_plus)
        BOOST_PROTO_DEFINE_TAG_INSERTION(negate)
        BOOST_PROTO_DEFINE_TAG_INSERTION(dereference)
        BOOST_PROTO_DEFINE_TAG_INSERTION(complement)
        BOOST_PROTO_DEFINE_TAG_INSERTION(address_of)
        BOOST_PROTO_DEFINE_TAG_INSERTION(logical_not)
        BOOST_PROTO_DEFINE_TAG_INSERTION(pre_inc)
        BOOST_PROTO_DEFINE_TAG_INSERTION(pre_dec)
        BOOST_PROTO_DEFINE_TAG_INSERTION(post_inc)
        BOOST_PROTO_DEFINE_TAG_INSERTION(post_dec)
        BOOST_PROTO_DEFINE_TAG_INSERTION(shift_left)
        BOOST_PROTO_DEFINE_TAG_INSERTION(shift_right)
        BOOST_PROTO_DEFINE_TAG_INSERTION(multiplies)
        BOOST_PROTO_DEFINE_TAG_INSERTION(divides)
        BOOST_PROTO_DEFINE_TAG_INSERTION(modulus)
        BOOST_PROTO_DEFINE_TAG_INSERTION(plus)
        BOOST_PROTO_DEFINE_TAG_INSERTION(minus)
        BOOST_PROTO_DEFINE_TAG_INSERTION(less)
        BOOST_PROTO_DEFINE_TAG_INSERTION(greater)
        BOOST_PROTO_DEFINE_TAG_INSERTION(less_equal)
        BOOST_PROTO_DEFINE_TAG_INSERTION(greater_equal)
        BOOST_PROTO_DEFINE_TAG_INSERTION(equal_to)
        BOOST_PROTO_DEFINE_TAG_INSERTION(not_equal_to)
        BOOST_PROTO_DEFINE_TAG_INSERTION(logical_or)
        BOOST_PROTO_DEFINE_TAG_INSERTION(logical_and)
        BOOST_PROTO_DEFINE_TAG_INSERTION(bitwise_and)
        BOOST_PROTO_DEFINE_TAG_INSERTION(bitwise_or)
        BOOST_PROTO_DEFINE_TAG_INSERTION(bitwise_xor)
        BOOST_PROTO_DEFINE_TAG_INSERTION(comma)
        BOOST_PROTO_DEFINE_TAG_INSERTION(mem_ptr)
        BOOST_PROTO_DEFINE_TAG_INSERTION(assign)
        BOOST_PROTO_DEFINE_TAG_INSERTION(shift_left_assign)
        BOOST_PROTO_DEFINE_TAG_INSERTION(shift_right_assign)
        BOOST_PROTO_DEFINE_TAG_INSERTION(multiplies_assign)
        BOOST_PROTO_DEFINE_TAG_INSERTION(divides_assign)
        BOOST_PROTO_DEFINE_TAG_INSERTION(modulus_assign)
        BOOST_PROTO_DEFINE_TAG_INSERTION(plus_assign)
        BOOST_PROTO_DEFINE_TAG_INSERTION(minus_assign)
        BOOST_PROTO_DEFINE_TAG_INSERTION(bitwise_and_assign)
        BOOST_PROTO_DEFINE_TAG_INSERTION(bitwise_or_assign)
        BOOST_PROTO_DEFINE_TAG_INSERTION(bitwise_xor_assign)
        BOOST_PROTO_DEFINE_TAG_INSERTION(subscript)
        BOOST_PROTO_DEFINE_TAG_INSERTION(member)
        BOOST_PROTO_DEFINE_TAG_INSERTION(if_else_)
        BOOST_PROTO_DEFINE_TAG_INSERTION(function)

    #undef BOOST_PROTO_DEFINE_TAG_INSERTION
    }

    namespace hidden_detail_
    {
        struct ostream_wrapper
        {
            ostream_wrapper(std::ostream &sout)
              : sout_(sout)
            {}

            std::ostream &sout_;
        };

        template<typename Tag>
        std::ostream &operator <<(ostream_wrapper sout_wrap, Tag const &)
        {
            return sout_wrap.sout_ << typeid(Tag).name();
        }
    }

    namespace functional
    {
        /// \brief Pretty-print a Proto expression tree.
        ///
        /// A PolymorphicFunctionObject which accepts a Proto expression
        /// tree and pretty-prints it to an \c ostream for debugging
        /// purposes.
        struct display_expr
        {
            typedef void result_type;

            /// \param sout  The \c ostream to which the expression tree
            ///              will be written.
            /// \param depth The starting indentation depth for this node.
            ///              Children nodes will be displayed at a starting
            ///              depth of <tt>depth+4</tt>.
            explicit display_expr(std::ostream &sout = std::cout, int depth = 0)
              : depth_(depth)
              , first_(true)
              , sout_(sout)
            {}

            /// \brief Pretty-print the current node in a Proto expression
            /// tree.
            template<typename Tag, typename Args>
            void operator()(proto::expr<Tag, Args, 0> const &expr) const
            {
                using namespace hidden_detail_;
                this->sout_ << std::setw(this->depth_) << (this->first_? "" : ", ")
                    << Tag() << "(" << proto::value(expr) << ")\n";
                this->first_ = false;
            }

        #define BOOST_PROTO_CHILD(Z, N, DATA)                                                       \
            display(proto::child_c<N>(expr));                                                       \
            /**/

        #define BOOST_PP_LOCAL_MACRO(N)                                                             \
            /** \overload */                                                                        \
            template<typename Tag, typename Args>                                                   \
            void operator()(proto::expr<Tag, Args, N> const &expr) const                            \
            {                                                                                       \
                using namespace hidden_detail_;                                                     \
                this->sout_ << std::setw(this->depth_) << (this->first_? "" : ", ")                 \
                    << Tag() << "(\n";                                                              \
                display_expr display(this->sout_, this->depth_ + 4);                                \
                BOOST_PP_REPEAT(N, BOOST_PROTO_CHILD, _)                                            \
                this->sout_ << std::setw(this->depth_) << "" << ")\n";                              \
                this->first_ = false;                                                               \
            }                                                                                       \
            /**/

        #define BOOST_PP_LOCAL_LIMITS (1, BOOST_PROTO_MAX_ARITY)
        #include BOOST_PP_LOCAL_ITERATE()
        #undef BOOST_PROTO_CHILD

            /// \overload
            ///
            template<typename T>
            void operator()(T const &t) const
            {
                (*this)(t.proto_base());
            }

        private:
            display_expr &operator =(display_expr const &);
            int depth_;
            mutable bool first_;
            std::ostream &sout_;
        };
    }

    /// \brief Pretty-print a Proto expression tree.
    ///
    /// \note Equivalent to <tt>functional::display_expr(0, sout)(expr)</tt>
    /// \param expr The Proto expression tree to pretty-print
    /// \param sout The \c ostream to which the output should be
    ///             written. If not specified, defaults to
    ///             <tt>std::cout</tt>.
    template<typename Expr>
    void display_expr(Expr const &expr, std::ostream &sout)
    {
        functional::display_expr(sout, 0)(expr);
    }

    /// \overload
    ///
    template<typename Expr>
    void display_expr(Expr const &expr)
    {
        functional::display_expr()(expr);
    }

    /// \brief Assert at compile time that a particular expression
    ///        matches the specified grammar.
    ///
    /// \note Equivalent to <tt>BOOST_MPL_ASSERT((proto::matches\<Expr, Grammar\>))</tt>
    /// \param expr The Proto expression to check againts <tt>Grammar</tt>
    template<typename Grammar, typename Expr>
    void assert_matches(Expr const & /*expr*/)
    {
        BOOST_MPL_ASSERT((proto::matches<Expr, Grammar>));
    }

    /// \brief Assert at compile time that a particular expression
    ///        does not match the specified grammar.
    ///
    /// \note Equivalent to <tt>BOOST_MPL_ASSERT_NOT((proto::matches\<Expr, Grammar\>))</tt>
    /// \param expr The Proto expression to check againts <tt>Grammar</tt>
    template<typename Grammar, typename Expr>
    void assert_matches_not(Expr const & /*expr*/)
    {
        BOOST_MPL_ASSERT_NOT((proto::matches<Expr, Grammar>));
    }

    /// \brief Assert at compile time that a particular expression
    ///        matches the specified grammar.
    ///
    /// \note Equivalent to <tt>proto::assert_matches\<Grammar\>(Expr)</tt>
    /// \param Expr The Proto expression to check againts <tt>Grammar</tt>
    /// \param Grammar The grammar used to validate Expr.
    #define BOOST_PROTO_ASSERT_MATCHES(Expr, Grammar)                                               \
        (true ? (void)0 : boost::proto::assert_matches<Grammar>(Expr))

    /// \brief Assert at compile time that a particular expression
    ///        does not match the specified grammar.
    ///
    /// \note Equivalent to <tt>proto::assert_matches_not\<Grammar\>(Expr)</tt>
    /// \param Expr The Proto expression to check againts <tt>Grammar</tt>
    /// \param Grammar The grammar used to validate Expr.
    #define BOOST_PROTO_ASSERT_MATCHES_NOT(Expr, Grammar)                                           \
        (true ? (void)0 : boost::proto::assert_matches_not<Grammar>(Expr))

}}

#endif
