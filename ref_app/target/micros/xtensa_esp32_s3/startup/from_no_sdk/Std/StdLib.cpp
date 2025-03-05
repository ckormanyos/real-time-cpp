///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2025.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

// Originally from:

/******************************************************************************************
  Filename    : StdLib.c

  Core        : Xtensa LX7

  MCU         : ESP32-S3

  Author      : Chalandi Amine

  Owner       : Chalandi Amine

  Date        : 22.02.2025

  Description : Handwritten StdLib functions

******************************************************************************************/

#include <cstdint>
#include <cstring>

extern "C" {

typedef   signed long long DItype  __attribute__((mode (DI)));
typedef unsigned long long UDItype __attribute__((mode (DI)));
typedef unsigned int       USItype __attribute__((mode (SI)));

extern int __builtin_clzll(long long unsigned int);

#define DWtype  DItype
#define UDWtype UDItype
#define UWtype  USItype

UDWtype __udivmoddi4 (UDWtype n, UDWtype d, UDWtype *rp);

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
    lz1 = __builtin_clzll (d);
    lz2 = __builtin_clzll (n);

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

void* memset(void* str, int c, size_t n)
{
  uint8_t *ptr = (uint8_t*) str;
  uint32_t value = (uint8_t) c;

  // Set value to repeat the byte across a 32-bit word.
  value |= value << 8;
  value |= value << 16;

  // Align to the next 32-bit boundary.
  while (((uintptr_t)ptr & 3) && n > 0)
  {
    *ptr++ = (uint8_t) c;

    --n;
  }

  // Set memory in 32-bit chunks.
  uint32_t* ptr32 = (uint32_t*) ptr;

  while (n >= 4)
  {
    *ptr32++ = value;

    n -= 4;
  }

  // Handle any remaining bytes.
  ptr = (uint8_t*) ptr32;

  while (n > 0)
  {
    *ptr++ = (uint8_t) c;

    --n;
  }

  return str;
}

void* memcpy (void* dest, const void* src, size_t n)
{
  uint8_t *d = (uint8_t*) dest;
  const uint8_t* s = (const uint8_t*) src;

  // Align destination to the next 32-bit boundary.
  while (((uintptr_t) d & 3) && n > 0)
  {
    *d++ = *s++;

    --n;
  }

  // Copy memory in 32-bit chunks.

  uint32_t *d32 = (uint32_t*) d;
  const uint32_t* s32 = (const uint32_t*) s;

  while (n >= 4)
  {
    *d32++ = *s32++;

    n -= 4;
  }

  // Handle any remaining bytes.

  d = (uint8_t*) d32;
  s = (const uint8_t*) s32;

  while (n > 0)
  {
    *d++ = *s++;

    --n;
  }

  return dest;
}

void* memmove (void* dest, const void* src, size_t n)
{
  uint8_t* from = (uint8_t*) src;
  uint8_t* to   = (uint8_t*) dest;

  if(from == to || n == 0)
  {
    return dest;
  }

  if(to > from && (ptrdiff_t) (to - from) < (ptrdiff_t) n)
  {
    // to overlaps with from
    //  <from......>
    //         <to........>
    // copy in reverse, to avoid overwriting from

    for(ptrdiff_t i = (ptrdiff_t) (n - 1); i >= 0; --i)
    {
      to[i] = from[i];
    }

    return dest;
  }

  if(from > to && (ptrdiff_t) (from - to) < (ptrdiff_t) n)
  {
    // to overlaps with from
    //        <from......>
    //  <to........>
    // copy forwards, to avoid overwriting from

    for(size_t i = 0U; i < n; ++i)
    {
      to[i] = from[i];
    }

    return dest;
  }

  memcpy(dest, src, n);

  return dest;
}

} // extern "C"
