///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2021.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

// Allocator traits -*- C++ -*-

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

#ifndef ALLOC_TRAITS_2021_01_26_H_
  #define ALLOC_TRAITS_2021_01_26_H_

  #include <impl/ptr_traits.h>

  namespace std
  {
    template<typename T>
    class allocator;

    template<typename... >
    using __void_t = void;

    struct __allocator_traits_base
    {
      template<typename _Tp, typename _Up, typename = void>
      struct __rebind : __replace_first_arg<_Tp, _Up> { };

      template<typename _Tp, typename _Up>
      struct __rebind<_Tp, _Up, __void_t<typename _Tp::template rebind<_Up>::other>>
      {
        using type = typename _Tp::template rebind<_Up>::other;
      };

    protected:
      template<typename _Tp>
      using __pointer = typename _Tp::pointer;

      template<typename _Tp>
      using __c_pointer = typename _Tp::const_pointer;

      template<typename _Tp>
      using __v_pointer = typename _Tp::void_pointer;

      template<typename _Tp>
      using __cv_pointer = typename _Tp::const_void_pointer;

      template<typename _Tp>
      using __pocca = typename _Tp::propagate_on_container_copy_assignment;

      template<typename _Tp>
      using __pocma = typename _Tp::propagate_on_container_move_assignment;

      template<typename _Tp>
      using __pocs = typename _Tp::propagate_on_container_swap;

      template<typename _Tp>
      using __equal = typename _Tp::is_always_equal;
    };

    template<typename AllocatorType, typename _Up>
    using __alloc_rebind = typename __allocator_traits_base::template __rebind<AllocatorType, _Up>::type;

    template<typename AllocatorType>
    struct allocator_traits : __allocator_traits_base
    {
    public:
      typedef AllocatorType allocator_type;
      typedef typename AllocatorType::value_type value_type;

      using pointer = __detected_or_t<value_type*, __pointer, AllocatorType>;

    private:
      template<template<typename> class _Func, typename _Tp, typename = void>
      struct _Ptr
      {
        using type = typename pointer_traits<pointer>::template rebind<_Tp>;
      };

      template<template<typename> class _Func, typename _Tp>
      struct _Ptr<_Func, _Tp, __void_t<_Func<AllocatorType>>>
      {
        using type = _Func<AllocatorType>;
      };

      template<typename _A2, typename _PtrT, typename = void>
      struct _Diff
      {
        using type = typename pointer_traits<_PtrT>::difference_type;
      };

      template<typename _A2, typename _PtrT>
      struct _Diff<_A2, _PtrT, __void_t<typename _A2::difference_type>>
      {
        using type = typename _A2::difference_type;
      };

      template<typename _A2, typename _DiffT, typename = void>
      struct _Size
      {
        using type = size_t;
      };

      template<typename _A2, typename _DiffT>
      struct _Size<_A2, _DiffT, __void_t<typename _A2::size_type>>
      {
        using type = typename _A2::size_type;
      };

    public:
      using const_pointer      = typename _Ptr<__c_pointer, const value_type>::type;
      using void_pointer       = typename _Ptr<__v_pointer, void>::type;
      using const_void_pointer = typename _Ptr<__cv_pointer, const void>::type;
      using difference_type    = typename _Diff<AllocatorType, pointer>::type;
      using size_type          = typename _Size<AllocatorType, difference_type>::type;

      using propagate_on_container_swap = __detected_or_t<false_type, __pocs, AllocatorType>;

      template<typename _Tp>
      using rebind_alloc = __alloc_rebind<AllocatorType, _Tp>;

      template<typename _Tp>
      using rebind_traits = allocator_traits<rebind_alloc<_Tp>>;

    private:
      template<typename _Alloc2>
      static auto _S_allocate(_Alloc2& __a, size_type __n, const_void_pointer __hint, int) -> decltype(__a.allocate(__n, __hint))
      {
        return __a.allocate(__n, __hint);
      }

      template<typename _Alloc2>
      static pointer _S_allocate(_Alloc2& __a, size_type __n, const_void_pointer, ...)
      {
        return __a.allocate(__n);
      }

      template<typename _Tp, typename... _Args>
      struct __construct_helper
      {
        template<typename _Alloc2,
                 typename = decltype(std::declval<_Alloc2*>()->construct(
                 std::declval<_Tp*>(), std::declval<_Args>()...))>
        static true_type __test(int);

        template<typename>
        static false_type __test(...);

        using type = decltype(__test<AllocatorType>(0));
      };

      template<typename _Tp, typename... _Args>
      using __has_construct = typename __construct_helper<_Tp, _Args...>::type;

      template<typename _Tp, typename... _Args>
      static void _S_construct(AllocatorType& __a, _Tp* __p, _Args&&... __args)
      {
        __a.construct(__p, std::forward<_Args>(__args)...);
      }

      template<typename _Alloc2, typename _Tp>
      static void _S_destroy(_Alloc2& __a, _Tp* __p, int)
      {
        __a.destroy(__p);
      }

      template<typename _Alloc2, typename _Tp>
      static void _S_destroy(_Alloc2&, _Tp* __p, ...)
      {
        __p->~_Tp();
      }

      template<typename _Alloc2>
      static size_type _S_max_size(_Alloc2& __a, int)
      {
        return __a.max_size();
      }

      template<typename _Alloc2>
      static size_type _S_max_size(_Alloc2&, ...)
      {
        return (size_type) (0xFFFFFFFFFFFFFFFFULL / sizeof(value_type));
      }

      template<typename _Alloc2>
      static auto _S_select(_Alloc2& __a, int) -> decltype(__a.select_on_container_copy_construction())
      {
        return __a.select_on_container_copy_construction();
      }

      template<typename _Alloc2>
      static _Alloc2 _S_select(_Alloc2& __a, ...)
      {
        return __a;
      }

    public:
      static pointer allocate(AllocatorType& __a, size_type __n)
      {
        return __a.allocate(__n);
      }

      static pointer allocate(AllocatorType& __a, size_type __n, const_void_pointer __hint)
      {
        return _S_allocate(__a, __n, __hint, 0);
      }

      static void deallocate(AllocatorType& __a, pointer __p, size_type __n)
      {
        __a.deallocate(__p, __n);
      }

      template<typename _Tp, typename... _Args>
      static auto construct(AllocatorType& __a, _Tp* __p, _Args&&... __args) -> decltype(_S_construct(__a, __p, std::forward<_Args>(__args)...))
      {
        _S_construct(__a, __p, std::forward<_Args>(__args)...);
      }

      template<typename _Tp>
      static void destroy(AllocatorType& __a, _Tp* __p)
      {
        _S_destroy(__a, __p, 0);
      }

      static size_type max_size(const AllocatorType& __a) noexcept
      { return _S_max_size(__a, 0); }

      static AllocatorType
      select_on_container_copy_construction(const AllocatorType& __rhs)
      { return _S_select(__rhs, 0); }
    };

    template<typename _Tp>
    struct allocator_traits<allocator<_Tp>>
    {
      // Partial specialization for std::allocator.
      using allocator_type = allocator<_Tp>;
      using value_type = _Tp;
      using pointer = _Tp*;
      using const_pointer = const _Tp*;
      using void_pointer = void*;
      using const_void_pointer = const void*;
      using difference_type = std::ptrdiff_t;
      using size_type = std::size_t;
      using propagate_on_container_copy_assignment = false_type;
      using propagate_on_container_move_assignment = true_type;
      using propagate_on_container_swap = false_type;
      using is_always_equal = true_type;

      template<typename _Up>
      using rebind_alloc = allocator<_Up>;

      template<typename _Up>
      using rebind_traits = allocator_traits<allocator<_Up>>;

      static pointer allocate(allocator_type& __a, size_type __n)
      { return __a.allocate(__n); }

      static pointer allocate(allocator_type& __a, size_type __n, const_void_pointer __hint)
      { return __a.allocate(__n, __hint); }

      static void deallocate(allocator_type& __a, pointer __p, size_type __n)
      { __a.deallocate(__p, __n); }

      template<typename _Up, typename... _Args>
      static void construct(allocator_type& __a, _Up* __p, _Args&&... __args)
      { __a.construct(__p, std::forward<_Args>(__args)...); }

      template<typename _Up>
      static void destroy(allocator_type& __a, _Up* __p) noexcept(noexcept(__a.destroy(__p)))
      { __a.destroy(__p); }

      static size_type max_size(const allocator_type& __a) noexcept
      { return __a.max_size(); }

      static allocator_type select_on_container_copy_construction(const allocator_type& __rhs)
      { return __rhs; }
    };
  }

#endif // ALLOC_TRAITS_2021_01_26_H_
