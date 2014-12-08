///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2012 - 2014.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef _INITIALIZER_LIST_IMPL_2012_02_14_H_
  #define _INITIALIZER_LIST_IMPL_2012_02_14_H_

  #if defined(__GNUC__)
  #pragma GCC system_header
  #endif

  #include "_stl_local_constexpr.h"
  #include "cstddef_impl.h"
  #include "iterator_impl.h"

  // Implement some of std::initializer_list for compilers that do not yet support it.
  // See ISO/IEC 14882:2011 Chapter 18.9.

  namespace std
  {
    template<class T>
    class initializer_list
    {
    public:
      typedef T           value_type;
      typedef const T&    reference;
      typedef const T&    const_reference;
      typedef std::size_t size_type;
      typedef const T*    iterator;
      typedef const T*    const_iterator;

      STL_LOCAL_CONSTEXPR initializer_list() : data  (nullptr),
                                               length(0U) { }

      STL_LOCAL_CONSTEXPR size_type size() { return length; }

      STL_LOCAL_CONSTEXPR const_iterator begin() const { return data; }
      STL_LOCAL_CONSTEXPR const_iterator end  () const { return begin() + size(); }

    private:
      iterator data;
      const size_type length;

      STL_LOCAL_CONSTEXPR initializer_list(const_iterator it, size_type len) : data  (it),
                                                                               length(len) { }
    };

    // Class-external begin and end of initializer_list<T>.
    template<typename T>
    STL_LOCAL_CONSTEXPR typename initializer_list<T>::const_iterator begin(initializer_list<T> lst)
    {
      return lst.begin();
    }

    template<typename T>
    STL_LOCAL_CONSTEXPR typename initializer_list<T>::const_iterator end(initializer_list<T> lst)
    {
      return lst.end();
    }

    // Class-external reverse-begin and reverse-end of initializer_list<T>.
    // These are specified in C++14.
    template<typename T>
    STL_LOCAL_CONSTEXPR typename initializer_list<T>::const_iterator rbegin(initializer_list<T> lst)
    {
      typedef std::reverse_iterator<iterator> reverse_iterator_type;

      return reverse_iterator_type(lst.end());
    }

    template<typename T>
    STL_LOCAL_CONSTEXPR typename initializer_list<T>::const_iterator rend(initializer_list<T> lst)
    {
      typedef std::reverse_iterator<iterator> reverse_iterator_type;

      return reverse_iterator_type(lst.begin());
    }
  }

#endif // _INITIALIZER_LIST_IMPL_2012_02_14_H_
