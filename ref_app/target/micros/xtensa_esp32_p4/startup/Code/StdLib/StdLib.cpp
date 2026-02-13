///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2025 - 2026.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

// Originally from (but strongly modified from):
/******************************************************************************************
  Filename    : StdLib.c
    
  Author      : Chalandi Amine
 
  Owner       : Chalandi Amine
  
  Date        : 22.02.2025
  
  Description : Handwritten StdLib functions
  
******************************************************************************************/

#include <cstddef>
#include <cstdint>
#include <cstring>

extern "C" {

#if defined(__GNUC__)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wcast-align"
#endif

auto memset(void* str, int c, size_t n) -> void*
{
  std::uint8_t* ptr { reinterpret_cast<std::uint8_t*>(str) };

  const std::uint8_t uc { static_cast<std::uint8_t>(c) };

  std::uint32_t value = static_cast<std::uint32_t>(uc);

  // Set value to repeat the byte across a 32-bit word.
  value |= value << unsigned { UINT8_C( 8) };
  value |= value << unsigned { UINT8_C(16) };

  // Align to the next 32-bit boundary.
  while (   (static_cast<unsigned>(reinterpret_cast<std::uintptr_t>(ptr) & unsigned { UINT8_C(3) }) != 0U)
         && (n > std::size_t { UINT8_C(0) }))
  {
    *ptr++ = uc;

    --n;
  }

  // Set memory in 32-bit chunks.
  std::uint32_t* ptr32 { reinterpret_cast<std::uint32_t*>(ptr) };

  while (n >= std::size_t { UINT8_C(4) })
  {
    *ptr32++ = value;

    n -= std::size_t { UINT8_C(4) };
  }

  // Handle any remaining bytes.
  ptr = reinterpret_cast<std::uint8_t*>(ptr32);

  while (n > std::size_t { UINT8_C(0) })
  {
    *ptr++ = uc;

    --n;
  }

  return str;
}

auto memcpy (void* dest, const void* src, size_t n) -> void*
{
        std::uint8_t* d { reinterpret_cast<std::uint8_t*>(dest) };
  const std::uint8_t* s { reinterpret_cast<const uint8_t*>(src) };

  // Align destination to the next 32-bit boundary.
  while (   (static_cast<unsigned>(reinterpret_cast<std::uintptr_t>(d) & unsigned { UINT8_C(3) }) != 0U)
         && (n > std::size_t { UINT8_C(0) }))
  {
    *d++ = *s++;

    --n;
  }

  // Copy memory in 32-bit chunks.

        std::uint32_t* d32 { reinterpret_cast<std::uint32_t*>(d) };
  const std::uint32_t* s32 { reinterpret_cast<const uint32_t*>(s) };

  while (n >= std::size_t { UINT8_C(4) })
  {
    *d32++ = *s32++;

    n -= std::size_t { UINT8_C(4) };
  }

  // Handle any remaining bytes.

  d = reinterpret_cast<std::uint8_t*>(d32);
  s = reinterpret_cast<const uint8_t*>(s32);

  while (n > std::size_t { UINT8_C(0) })
  {
    *d++ = *s++;

    --n;
  }

  return dest;
}

#if defined(__GNUC__)
#pragma GCC diagnostic pop
#endif

} // extern "C"
