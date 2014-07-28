///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2013.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef _XITERATOR_IMPL_2010_02_23_H_
  #define _XITERATOR_IMPL_2010_02_23_H_

  #if defined(__GNUC__)
  #pragma GCC system_header
  #endif

  #include "cstddef_impl.h"

  // Implement helper functions for some of <iterator>.

  namespace xiterator
  {
    class xinput_iterator_tag {};
    class xoutput_iterator_tag {};
    class xforward_iterator_tag : public xinput_iterator_tag {};
    class xbidirectional_iterator_tag : public xforward_iterator_tag {};
    class xrandom_access_iterator_tag : public xbidirectional_iterator_tag {};

    template<typename iterator_type>
    class xiterator_traits
    {
    public:
      typedef typename iterator_type::difference_type   difference_type;
      typedef typename iterator_type::value_type        value_type;
      typedef typename iterator_type::pointer           pointer;
      typedef typename iterator_type::reference         reference;
      typedef typename iterator_type::iterator_category iterator_category;
    };

    template<typename T>
    class xiterator_traits<T*>
    {
    public:
      typedef std::ptrdiff_t              difference_type;
      typedef T                           value_type;
      typedef value_type*                 pointer;
      typedef value_type&                 reference;
      typedef xrandom_access_iterator_tag iterator_category;
    };

    template<typename T>
    class xiterator_traits<const T*>
    {
    public:
      typedef std::ptrdiff_t              difference_type;
      typedef T                           value_type;
      typedef const value_type*           pointer;
      typedef const value_type&           reference;
      typedef xrandom_access_iterator_tag iterator_category;
    };
  }

#endif // _XITERATOR_IMPL_2010_02_23_H_
