///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2013.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef _XALLOCATOR_IMPL_2010_02_23_H_
  #define _XALLOCATOR_IMPL_2010_02_23_H_

  #if defined(__GNUC__)
  #pragma GCC system_header
  #endif

  #include "cstddef_impl.h"

  // Implement helper functions for std::allocator.

  namespace xallocator
  {
    template<typename iterator_type, typename allocator_type>
    inline void xdestroy_range(iterator_type first, iterator_type last, allocator_type a)
    {
      while(first != last)
      {
        a.destroy(first);
        ++first;
      }
    }

    template<typename iterator_type, typename allocator_type>
    inline void xdeallocate_range(iterator_type first, iterator_type last, allocator_type a)
    {
      a.deallocate(first, (std::size_t) (last - first));
    }
  }

#endif // _XALLOCATOR_IMPL_2010_02_23_H_
