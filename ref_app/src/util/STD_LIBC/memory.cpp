///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2011 - 2015.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <cstddef>
#include <cstdint>

// Implement some efficient memory functions from the standard C library.
// If this file is included in the project, the linker will take these
// functions instead of its own corresponding functions from the C-library.
// The functions in this file *might* potentially save some code and/or
// runtime in the executable.

extern "C"
void* memset(void* dst, int c, size_t n)
{
  std::uint8_t* the_dst = reinterpret_cast<std::uint8_t*>(dst);

  for( ; n > static_cast<size_t>(0U); --n)
  {
    *the_dst = static_cast<uint8_t>(c);
    ++the_dst;
  }

  return dst;
}

extern "C"
void* memcpy(void* dst, const void* src, size_t n)
{
        std::uint8_t* the_dst = reinterpret_cast<      std::uint8_t*>(dst);
  const std::uint8_t* the_src = reinterpret_cast<const std::uint8_t*>(src);

  for( ; n > static_cast<std::size_t>(0U); --n)
  {
    *the_dst = *the_src;
    ++the_dst;
    ++the_src;
  }

  return dst;
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
