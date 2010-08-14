/*=============================================================================
    Copyright (c) 2001-2010 Hartmut Kaiser
    Copyright (c) 2001-2010 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_SPIRIT_ATTRIBUTES_FWD_OCT_01_2009_0715AM)
#define BOOST_SPIRIT_ATTRIBUTES_FWD_OCT_01_2009_0715AM

#if defined(_MSC_VER)
#pragma once
#endif

namespace boost { namespace spirit { namespace traits
{
    ///////////////////////////////////////////////////////////////////////////
    // Determine if T is a proxy
    ///////////////////////////////////////////////////////////////////////////
    template <typename T, typename Enable = void>
    struct is_proxy;

    ///////////////////////////////////////////////////////////////////////////
    // Retrieve the attribute type to use from the given type
    //
    // This is needed to extract the correct attribute type from proxy classes
    // as utilized in FUSION_ADAPT_CLASS
    ///////////////////////////////////////////////////////////////////////////
    template <typename Attribute, typename Enable = void>
    struct attribute_type;

    ///////////////////////////////////////////////////////////////////////////
    // Determines how we pass attributes to semantic actions. This
    // may be specialized. By default, all attributes are wrapped in
    // a fusion sequence, because the attribute has to be treated as being
    // a single value in any case (even if it actually already is a fusion
    // sequence in its own).
    ///////////////////////////////////////////////////////////////////////////
    template <typename Component, typename Attribute, typename Enable = void>
    struct pass_attribute;

    ///////////////////////////////////////////////////////////////////////////
    template <typename T, typename Enable = void>
    struct optional_attribute;

    ///////////////////////////////////////////////////////////////////////////
    // Sometimes the user needs to transform the attribute types for certain
    // attributes. This template can be used as a customization point, where
    // the user is able specify specific transformation rules for any attribute
    // type.
    ///////////////////////////////////////////////////////////////////////////
    template <typename Exposed, typename Transformed, typename Enable = void>
    struct transform_attribute;

    ///////////////////////////////////////////////////////////////////////////
    template <typename Attribute, typename Iterator, typename Enable = void>
    struct assign_to_attribute_from_iterators;

    template <typename Attribute, typename T, typename Enable = void>
    struct assign_to_attribute_from_value;

    ///////////////////////////////////////////////////////////////////////////
    template <typename Attribute, typename Enable = void>
    struct extract_from_attribute;

    ///////////////////////////////////////////////////////////////////////////
    // Clear data efficiently
    ///////////////////////////////////////////////////////////////////////////
    template <typename T, typename Enable = void>
    struct clear_value;

    ///////////////////////////////////////////////////////////////////////
    // Determine the value type of the given container type
    ///////////////////////////////////////////////////////////////////////
    template <typename Container, typename Enable = void>
    struct container_value;

    template <typename Container, typename Enable = void>
    struct container_iterator;

    template <typename T, typename Enable = void>
    struct is_container;

    ///////////////////////////////////////////////////////////////////////////
    template <typename Container, typename T, typename Enable = void>
    struct push_back_container;

    template <typename Container, typename Enable = void>
    struct is_empty_container;

    ///////////////////////////////////////////////////////////////////////
    // Determine the iterator type of the given container type
    ///////////////////////////////////////////////////////////////////////
    template <typename Container, typename Enable = void>
    struct begin_container;

    template <typename Container, typename Enable = void>
    struct end_container;

    template <typename Iterator, typename Enable = void>
    struct deref_iterator;

    template <typename Iterator, typename Enable = void>
    struct next_iterator;

    template <typename Iterator, typename Enable = void>
    struct compare_iterators;
}}}

///////////////////////////////////////////////////////////////////////////////
namespace boost { namespace spirit { namespace result_of
{
    // forward declaration only
    template <typename Attribute>
    struct extract_from;

    template <typename Exposed, typename Transformed>
    struct pre_transform;

    template <typename T>
    struct optional_value;

    template <typename Container>
    struct begin;

    template <typename Container>
    struct end;

    template <typename Iterator>
    struct deref;
}}}

#endif

