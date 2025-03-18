///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2025.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

// Originally from (but strongly modified from):
/******************************************************************************************
  Filename    : StdLib.c

  Core        : Xtensa LX7

  MCU         : ESP32-S3

  Author      : Chalandi Amine

  Owner       : Chalandi Amine

  Date        : 22.02.2025

  Description : Hand-written StdLib functions

******************************************************************************************/

#include <cstddef>
#include <cstdint>
#include <cstring>

extern "C" {

typedef   signed long long DItype  __attribute__((mode (DI)));
typedef unsigned long long UDItype __attribute__((mode (DI)));
typedef unsigned int       USItype __attribute__((mode (SI)));

extern int __builtin_clzll(unsigned long long);

#define DWtype  DItype
#define UDWtype UDItype
#define UWtype  USItype

UDWtype __udivdi3    (UDWtype n, UDWtype d);
UDWtype __udivmoddi4 (UDWtype n, UDWtype d, UDWtype *rp);
UDWtype __umoddi3    (UDWtype u, UDWtype v);

UDWtype __udivdi3 (UDWtype n, UDWtype d)
{
  return __udivmoddi4 (n, d, (UDWtype *) 0);
}

UDWtype __umoddi3 (UDWtype u, UDWtype v)
{
  UDWtype w;

  (void) __udivmoddi4 (u, v, &w);

  return w;
}

UDWtype __udivmoddi4 (UDWtype n, UDWtype d, UDWtype *rp)
{
  UDWtype q = 0, r = n, y = d;
  UWtype lz1, lz2, i, k;

  // Implements align divisor shift dividend method. This algorithm
  // aligns the divisor under the dividend and then perform number of
  // test-subtract iterations which shift the dividend left. Number of
  // iterations is k + 1 where k is the number of bit positions the
  // divisor must be shifted left to align it under the dividend.
  // quotient bits can be saved in the rightmost positions of the dividend
  // as it shifts left on each test-subtract iteration.

  if (y <= r)
  {
    lz1 = static_cast<USItype>(__builtin_clzll(static_cast<unsigned long long>(d)));
    lz2 = static_cast<USItype>(__builtin_clzll(static_cast<unsigned long long>(n)));

    k = lz1 - lz2;
    y = (y << k);

    // Dividend can exceed 2 ^ (width - 1) - 1 but still be less than the
    // aligned divisor. Normal iteration can drops the high order bit
    // of the dividend. Therefore, first test-subtract iteration is a
    // special case, saving its quotient bit in a separate location and
    // not shifting the dividend.

    if (r >= y)
    {
      r = r - y;
      q =  (1ULL << k);
    }
    
    if (k > 0)
    {
      y = y >> 1;

      // k additional iterations where k regular test subtract shift
      // dividend iterations are done.

      i = k;

      do
      {
        if (r >= y)
        {
          r = ((r - y) << 1) + 1;
        }
        else
        {
          r =  (r << 1);
        }

        i = i - 1;
      }
      while (i != 0);

      // First quotient bit is combined with the quotient bits resulting
      // from the k regular iterations.

      q = q + r;
      r = r >> k;
      q = q - (r << k);
    }
  }

  if (rp)
  {
    *rp = r;
  }

  return q;
}

#if defined(__GNUC__)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wcast-align"
#endif

void* memset(void* str, int c, size_t n)
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

void* memcpy (void* dest, const void* src, size_t n)
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
