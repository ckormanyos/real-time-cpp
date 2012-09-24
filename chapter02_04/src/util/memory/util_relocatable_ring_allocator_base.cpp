#include "util_relocatable_ring_allocator_base.h"

void util::relocatable_ring_allocator_base::relocate(std::uint8_t* pbuf, const size_type size)
{
  buffer = get_ptr = pbuf;
  buffer_size = size;
}
