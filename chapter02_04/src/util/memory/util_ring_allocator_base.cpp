#include "util_ring_allocator_base.h"

util::ring_allocator_base::size_type util::ring_allocator_base::buffer_size = default_buffer_size;
std::uint8_t  util::ring_allocator_base::default_buffer[default_buffer_size];
std::uint8_t* util::ring_allocator_base::buffer  = default_buffer;
std::uint8_t* util::ring_allocator_base::get_ptr = default_buffer;

void* util::ring_allocator_base::do_allocate(const size_type size)
{
  // Does the allocation wraparound the buffer?
  const bool is_wraparound =
    ((get_ptr + size) >= (buffer + buffer_size));

  // Get the newly allocated pointer.
  std::uint8_t* p = (is_wraparound ? buffer : get_ptr);

  // Increment the pointer for next time.
  get_ptr = p + size;

  return static_cast<void*>(p);
}

/*
#include <vector>
#include <numeric>
#include "util_relocatable_ring_allocator.h"

typedef util::relocatable_ring_allocator<std::uint8_t> alloc_type;
typedef std::vector<std::uint8_t, alloc_type> response_type;

void login_response(response_type& rsp)
{
  rsp.resize(5U);

  rsp[0U] = 0x55U; // Login OK key.
  rsp[1U] = 0x31U; // Response data '0'.
  rsp[2U] = 0x32U; // Response data '1'.
  rsp[3U] = 0x33U; // Response data '2'.

  // Checksum over four bytes.
  rsp[4U] = std::accumulate(rsp.begin(),
                            rsp.begin() + 4U,
                            static_cast<std::uint8_t>(0U));
}
*/
