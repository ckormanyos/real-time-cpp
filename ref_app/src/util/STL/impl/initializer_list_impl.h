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

  #include "cstddef_impl.h"

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

      constexpr initializer_list() : data  (nullptr),
                                     length(0U) { }

      constexpr size_type size() { return length; }

      constexpr const_iterator begin() { return data; }
      constexpr const_iterator end  () { return begin() + size(); }

    private:
      iterator data;
      const size_type length;

      constexpr initializer_list(const_iterator it, size_type len) : data  (it),
                                                                     length(len) { }
    };

    // Class-external begin and end of initializer_list<T>.
    template<typename T>
    constexpr typename initializer_list<T>::const_iterator begin(initializer_list<T> lst)
    {
      return lst.begin();
    }

    template<typename T>
    constexpr typename initializer_list<T>::const_iterator end(initializer_list<T> lst)
    {
      return lst.end();
    }
  }

#endif // _INITIALIZER_LIST_IMPL_2012_02_14_H_
