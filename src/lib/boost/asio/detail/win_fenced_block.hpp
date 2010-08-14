//
// win_fenced_block.hpp
// ~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2010 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_WIN_FENCED_BLOCK_HPP
#define BOOST_ASIO_DETAIL_WIN_FENCED_BLOCK_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/push_options.hpp>

#include <boost/asio/detail/push_options.hpp>
#include <boost/config.hpp>
#include <boost/asio/detail/pop_options.hpp>

#if defined(BOOST_WINDOWS) && !defined(UNDER_CE)

#include <boost/asio/detail/socket_types.hpp>

namespace boost {
namespace asio {
namespace detail {

class win_fenced_block
  : private noncopyable
{
public:
  // Constructor.
  win_fenced_block()
  {
#if defined(BOOST_MSVC) && (BOOST_MSVC < 1400)
# if defined(_M_IX86)
#  pragma warning(push)
#  pragma warning(disable:4793)
    LONG barrier;
    __asm { xchg barrier, eax }
#  pragma warning(pop)
# endif // defined(_M_IX86)
#else // defined(BOOST_MSVC) && (BOOST_MSVC < 1400)
    MemoryBarrier();
#endif // defined(BOOST_MSVC) && (BOOST_MSVC < 1400)
  }

  // Destructor.
  ~win_fenced_block()
  {
#if defined(BOOST_MSVC) && (BOOST_MSVC < 1400)
# if defined(_M_IX86)
#  pragma warning(push)
#  pragma warning(disable:4793)
    LONG barrier;
    __asm { xchg barrier, eax }
#  pragma warning(pop)
# endif // defined(_M_IX86)
#else // defined(BOOST_MSVC) && (BOOST_MSVC < 1400)
    MemoryBarrier();
#endif // defined(BOOST_MSVC) && (BOOST_MSVC < 1400)
  }
};

} // namespace detail
} // namespace asio
} // namespace boost

#endif // defined(BOOST_WINDOWS) && !defined(UNDER_CE)

#include <boost/asio/detail/pop_options.hpp>

#endif // BOOST_ASIO_DETAIL_WIN_FENCED_BLOCK_HPP
