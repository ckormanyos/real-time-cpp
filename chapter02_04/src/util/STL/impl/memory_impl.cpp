#include "memory_impl.h"

std::uint8_t  std::allocator_base::buffer[buffer_size];
std::uint8_t* std::allocator_base::get_ptr = buffer;

void* std::allocator_base::do_allocate(const size_type size)
{
  // Does the allocation wraparound the buffer?
  const bool is_wraparound = ((get_ptr + size) >= (buffer + buffer_size));

  // Get the newly allocated pointer.
  std::uint8_t* p = (is_wraparound ? buffer : get_ptr);

  // Increment the pointer for next time.
  get_ptr = p + size;

  return static_cast<void*>(p);
}
