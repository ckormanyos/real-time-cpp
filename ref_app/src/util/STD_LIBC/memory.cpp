///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2011 - 2015.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <cstddef>
#include <cstdint>
#include <cstring>

// Implement some efficient memory functions from the standard C library.
// If this file is included in the project, the linker will take these
// functions instead of its own corresponding functions from the C-library.
// The functions in this file *might* potentially save some code and/or
// runtime in the executable.

extern "C"
void* memset(void* dest, int c, size_t count)
{
  // Convert the value c to unsigned char and copy it into each
  // of the first count characters of the object pointed to by dest.
  // If the object is a potentially-overlapping subobject or is not
  // TriviallyCopyable (e.g., scalar, C-compatible struct,
  // or an array of trivially copyable type), the behavior is undefined.
  // If count is greater than the size of the object pointed to by dest,
  // the behavior is undefined.

  unsigned char* puchar_dest = reinterpret_cast<unsigned char*>(dest);
  const unsigned char uchar_c = static_cast<unsigned char>(c);

  size_t i = 0U;

  for( ; i < count; ++i)
  {
    *(volatile unsigned char*) (puchar_dest + i) = uchar_c;
  }

  return reinterpret_cast<void*>(puchar_dest + i);
}

extern "C"
void* memcpy(void* dest, const void* src, size_t count)
{
        unsigned char* puchar_dest = reinterpret_cast<      std::uint8_t*>(dest);
  const unsigned char* puchar_src  = reinterpret_cast<const std::uint8_t*>(src);

  for(size_t i = 0U; i < count; ++i)
  {
    puchar_dest[i] = puchar_src[i];
  }

  return reinterpret_cast<void*>(puchar_dest + count);
}

extern "C"
void* memmove(void* dst, const void* src, size_t n)
{
  // The function memmove *does* work properly even when its operands overlap.

        std::uint8_t* the_dst = static_cast<      std::uint8_t*>(dst);
  const std::uint8_t* the_src = static_cast<const std::uint8_t*>(src);

  // Check for a range overlap.
  if((the_src < the_dst) && (the_dst < (the_src + n)))
  {
    the_dst += n;
    the_src += n;

    for( ; n > static_cast<std::size_t>(0U); --n)
    {
      // Perform a backwards copy.
      --the_dst;
      --the_src;
      *the_dst = *the_src;
    }
  }
  else
  {
    for( ; n > static_cast<size_t>(0U); --n)
    {
      // Perform a forwards copy.
      *the_dst = *the_src;
      ++the_dst;
      ++the_src;
    }
  }

  return dst;
}
