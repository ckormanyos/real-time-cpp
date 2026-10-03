///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2026.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef ALLOCATOR_IMPL_2010_02_23_H
  #define ALLOCATOR_IMPL_2010_02_23_H

  #include <cstddef>
  #include <iterator>
  #include <memory>

  // Implement helper functions for some of std::allocator.

  namespace std
  {
    template<typename iterator_type, typename allocator_type>
    inline void destroy_range(iterator_type first, iterator_type last, allocator_type& a)
    {
      while(first != last)
      {
        std::allocator_traits<allocator_type>::destroy(a, first);

        ++first;
      }
    }

    template<typename iterator_type, typename allocator_type>
    inline void deallocate_range(iterator_type first, iterator_type last, allocator_type& a)
    {
      if(first != last)
      {
        const std::size_t count = static_cast<std::size_t>(std::distance(first, last));

        a.deallocate(first, count);
      }
    }
  }

#endif // ALLOCATOR_IMPL_2010_02_23_H
