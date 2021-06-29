///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2021.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

// Pointer Traits -*- C++ -*-

// Copyright (C) 2011-2019 Free Software Foundation, Inc.
//
// This file is part of the GNU ISO C++ Library.  This library is free
// software; you can redistribute it and/or modify it under the
// terms of the GNU General Public License as published by the
// Free Software Foundation; either version 3, or (at your option)
// any later version.

// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// Under Section 7 of GPL version 3, you are granted additional
// permissions described in the GCC Runtime Library Exception, version
// 3.1, as published by the Free Software Foundation.

// You should have received a copy of the GNU General Public License and
// a copy of the GCC Runtime Library Exception along with this program;
// see the files COPYING3 and COPYING.RUNTIME respectively.  If not, see
// <http://www.gnu.org/licenses/>.

/** @file bits/ptr_traits.h
 *  This is an internal header file, included by other library headers.
 *  Do not attempt to use it directly. @headername{memory}
 */

#ifndef PTR_TRAITS_2021_01_26_H_
  #define PTR_TRAITS_2021_01_26_H_

  namespace std
  {
    template<typename...>
    using __void_t = void;

    // Implementation of the detection idiom (negative case).
    template<typename _Default, typename _AlwaysVoid,
    template<typename...> class _Op, typename... _Args>
    struct __detector
    {
      using value_t = false_type;
      using type = _Default;
    };

    // Implementation of the detection idiom (positive case).
    template<typename _Default,
             template<typename...> class _Op,
             typename... _Args>
    struct __detector<_Default, __void_t<_Op<_Args...>>, _Op, _Args...>
    {
      using value_t = true_type;
      using type = _Op<_Args...>;
    };

    // Detect whether _Op<_Args...> is a valid type, use _Default if not.
    template<typename _Default, template<typename...> class _Op, typename... _Args>
    using __detected_or = __detector<_Default, void, _Op, _Args...>;

    // _Op<_Args...> if that is a valid type, otherwise _Default.
    template<typename _Default, template<typename...> class _Op, typename... _Args>
    using __detected_or_t = typename __detected_or<_Default, _Op, _Args...>::type;

    class __undefined;

    // Given Template<T, ...> return T, otherwise invalid.
    template<typename _Tp>
    struct __get_first_arg
    { using type = __undefined; };

    template<template<typename, typename...> class _Template,
             typename _Tp,
             typename... _Types>
    struct __get_first_arg<_Template<_Tp, _Types...>>
    { using type = _Tp; };

    template<typename _Tp>
    using __get_first_arg_t = typename __get_first_arg<_Tp>::type;

    // Given Template<T, ...> and U return Template<U, ...>, otherwise invalid.
    template<typename _Tp, typename _Up>
    struct __replace_first_arg { };

    template<template<typename, typename...> class _Template,
             typename _Up,
             typename _Tp, typename... _Types>
    struct __replace_first_arg<_Template<_Tp, _Types...>, _Up>
    { using type = _Template<_Up, _Types...>; };

    template<typename _Tp, typename _Up>
    using __replace_first_arg_t = typename __replace_first_arg<_Tp, _Up>::type;

    template<typename _Tp>
    using __make_not_void = typename conditional<is_void<_Tp>::value, __undefined, _Tp>::type;

    template<typename _Ptr>
    struct pointer_traits
    {
    private:
      template<typename _Tp>
      using __element_type = typename _Tp::element_type;

      template<typename _Tp>
      using __difference_type = typename _Tp::difference_type;

      template<typename _Tp, typename _Up, typename = void>
      struct __rebind : __replace_first_arg<_Tp, _Up> { };

      template<typename _Tp, typename _Up>
      struct __rebind<_Tp, _Up, __void_t<typename _Tp::template rebind<_Up>>>
      { using type = typename _Tp::template rebind<_Up>; };

    public:
      using pointer = _Ptr;
      using element_type = __detected_or_t<__get_first_arg_t<_Ptr>, __element_type, _Ptr>;
      using difference_type = __detected_or_t<ptrdiff_t, __difference_type, _Ptr>;

      template<typename _Up>
      using rebind = typename __rebind<_Ptr, _Up>::type;

      static _Ptr pointer_to(__make_not_void<element_type>& __e)
      { return _Ptr::pointer_to(__e); }

      static_assert(!is_same<element_type, __undefined>::value,
                    "pointer type defines element_type or is like SomePointer<T, Args>");
    };

    template<typename _Tp>
    struct pointer_traits<_Tp*>
    {
      typedef _Tp* pointer;
      typedef _Tp  element_type;
      typedef ptrdiff_t difference_type;

      template<typename _Up>
      using rebind = _Up*;

      static constexpr pointer pointer_to(__make_not_void<element_type>& __r)
      { return std::addressof(__r); }
    };

    // Convenience alias for rebinding pointers.
    template<typename _Ptr, typename _Tp>
    using __ptr_rebind = typename pointer_traits<_Ptr>::template rebind<_Tp>;

    template<typename _Tp>
    constexpr _Tp* __to_address(_Tp* __ptr)
    {
      return __ptr;
    }

    #if __cplusplus <= 201703L
    template<typename _Ptr>
    constexpr typename std::pointer_traits<_Ptr>::element_type* __to_address(const _Ptr& __ptr)
    { return std::__to_address(__ptr.operator->()); }
    #else
    template<typename _Ptr>
    constexpr auto __to_address(const _Ptr& __ptr) -> decltype(std::pointer_traits<_Ptr>::to_address(__ptr))
    { return std::pointer_traits<_Ptr>::to_address(__ptr); }

    template<typename _Ptr, typename... _None>
    constexpr auto __to_address(const _Ptr& __ptr, _None...)
    {
      return std::__to_address(__ptr.operator->());
    }

    template<typename _Tp>
    constexpr _Tp*
    to_address(_Tp* __ptr)
    { return std::__to_address(__ptr); }

    template<typename _Ptr>
    constexpr auto
    to_address(const _Ptr& __ptr)
    { return std::__to_address(__ptr); }

    #endif // C++2a
  }

#endif // PTR_TRAITS_2021_01_26_H_
