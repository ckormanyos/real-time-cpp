///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2014.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include "util_ring_allocator.h"

volatile std::uint8_t  util::ring_allocator_base::buffer[buffer_size];
volatile std::uint8_t* util::ring_allocator_base::get_ptr = buffer;

void* util::ring_allocator_base::do_allocate(const size_type size)
{
  // Get the newly allocated pointer.
  volatile std::uint8_t* p = get_ptr;

  // Increment the pointer for the next allocation.
  get_ptr += size;

  // Does this allocation overflow the top of the buffer?
  const bool is_wrap = (get_ptr >= (buffer + buffer_size));

  if(is_wrap)
  {
    // Here, the allocation overflows the top of the buffer.
    // Reset the allocated pointer to the bottom of the buffer
    // and increment the next get-pointer accordingly.
    p       = buffer;
    get_ptr = buffer + size;
  }

  return static_cast<void*>(const_cast<std::uint8_t*>(p));
}
