#include <cstdint>
#include "util_static_allocator.h"

void* util::static_allocator_base::do_allocate(const size_type size)
{
  static std::uint8_t  buffer[buffer_size];
  static std::uint8_t* get_ptr = buffer;

  // Get the newly allocated pointer.
  std::uint8_t* p = get_ptr;

  // Increment the pointer for next time.
  get_ptr += size;

  return static_cast<void*>(p);
}
