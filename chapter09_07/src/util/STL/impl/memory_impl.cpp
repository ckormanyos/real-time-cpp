///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2013.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include "memory_impl.h"

void* std::allocator_base::do_allocate(const size_type size)
{
  static std::uint8_t  buffer[buffer_size];
  static std::uint8_t* get_ptr = buffer;

  // Get the newly allocated pointer.
  std::uint8_t* p = get_ptr;

  // Increment the pointer for next time.
  get_ptr += size;

  // Does the allocation wrap around the buffer?
  const bool is_wrap = (get_ptr >= (buffer + buffer_size));

  if(is_wrap)
  {
    // The allocation wraps around the buffer.
    // Reset the newly allocated pointer to the start of the buffer
    // and increment the next get-pointer accordingly.

    p       = buffer;
    get_ptr = buffer + size;
  }

  return static_cast<void*>(p);
}
