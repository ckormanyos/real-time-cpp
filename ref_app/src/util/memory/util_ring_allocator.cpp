///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2013.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <cstdint>
#include "util_ring_allocator.h"

void* util::ring_allocator_base::do_allocate(const size_type size)
{
  static std::uint8_t  buffer[ring_allocator_base::buffer_size];
  static std::uint8_t* get_ptr = buffer;

  // Get the newly allocated pointer.
  std::uint8_t* p = get_ptr;

  // Increment the pointer for next time.
  get_ptr += size;

  // Does the allocation wraparound the buffer?
  const bool is_wrap = (get_ptr >= (buffer + buffer_size));

  if(is_wrap)
  {
    get_ptr = buffer;
  }

  return static_cast<void*>(p);
}
