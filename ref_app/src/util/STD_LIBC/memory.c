///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2011 - 2021.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <stddef.h>
#include <stdint.h>

// Implement some efficient memory functions from the standard C library.
// If this file is included in the project, the linker will take these
// functions instead of its own corresponding functions from the C-library.
// The functions in this file *might* potentially save some code and/or
// runtime in the executable.

void* memset (void* dest, int val, size_t count)         __attribute__((used, noinline));
void* memcpy (void* dest, const void* src, size_t count) __attribute__((used, noinline));
void* memmove(void* dst, const void* src, size_t n)      __attribute__((used, noinline));

void* memset(void* dest, int val, size_t count)
{
  unsigned char* ptr = (unsigned char*) dest;

  while(count-- > 0)
  {
    *ptr++ = (unsigned char) val;
  }

  return dest;
}

void* memcpy(void* dest, const void* src, size_t count)
{
        unsigned char* puchar_dest = (      uint8_t*) dest;
  const unsigned char* puchar_src  = (const uint8_t*) src;

  for(size_t i = 0U; i < count; ++i)
  {
    puchar_dest[i] = puchar_src[i];
  }

  return (void*) (puchar_dest + count);
}

void* memmove(void *dest, const void *src, size_t n)
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
    // copy forwards, to avoid overwriting from */
    for(size_t i = 0U; i < n; ++i)
    {
      to[i] = from[i];
    }

    return dest;
  }

  memcpy(dest, src, n);

  return dest;
}
