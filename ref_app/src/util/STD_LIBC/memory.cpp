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

extern "C" void* memset (void* dest, int c, size_t count)           __attribute__((used, noinline));
extern "C" void* memcpy (void* dest, const void* src, size_t count) __attribute__((used, noinline));
extern "C" void* memmove(void* dst, const void* src, size_t n)      __attribute__((used, noinline));

void* memset(void* dest, int c, size_t count)
{
  // Convert the value c to unsigned char and copy it into each
  // of the first count characters of the object pointed to by dest.
  // If the object is a potentially-overlapping subobject or is not
  // TriviallyCopyable (e.g., scalar, C-compatible struct,
  // or an array of trivially copyable type), the behavior is undefined.
  // If count is greater than the size of the object pointed to by dest,
  // the behavior is undefined.

  unsigned char* puchar_dest  = (unsigned char*) dest;
  const unsigned char uchar_c = (unsigned char)  c;

  size_t i = 0U;

  for( ; i < count; ++i)
  {
    *(volatile unsigned char*) (puchar_dest + i) = uchar_c;
  }

  return (void*) (puchar_dest + i);
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

void* memmove(void* dst, const void* src, size_t n)
{
  // The function memmove *does* work properly even when its operands overlap.

        uint8_t* the_dst = (      uint8_t*) dst;
  const uint8_t* the_src = (const uint8_t*) src;

  // Check for a range overlap.
  if((the_src < the_dst) && (the_dst < (the_src + n)))
  {
    the_dst += n;
    the_src += n;

    for( ; n > (size_t) (0U); --n)
    {
      // Perform a backwards copy.
      --the_dst;
      --the_src;
      *the_dst = *the_src;
    }
  }
  else
  {
    for( ; n > (size_t) 0U; --n)
    {
      // Perform a forwards copy.
      *the_dst = *the_src;
      ++the_dst;
      ++the_src;
    }
  }

  return dst;
}
