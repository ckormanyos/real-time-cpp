///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2011 - 2013.
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

extern "C"
void* memset(void* s1, int c, size_t n)
{
  uint8_t* su1 = reinterpret_cast<uint8_t*>(s1);

  for( ; n > static_cast<size_t>(0U); --n)
  {
    *su1 = static_cast<uint8_t>(c);
    ++su1;
  }

  return s1;
}

extern "C"
void* memcpy(void* s1, const void* s2, size_t n)
{
        uint8_t* su1 = reinterpret_cast<      uint8_t*>(s1);
  const uint8_t* su2 = reinterpret_cast<const uint8_t*>(s2);

  for( ; n > static_cast<size_t>(0U); --n)
  {
    *su1 = *su2;
    ++su1;
    ++su2;
  }

  return s1;
}

extern "C"
void* memmove(void* s1, const void* s2, size_t n)
{
  // The function memmove *does* work properly even when its operands overlap.

        uint8_t* sc1 = reinterpret_cast<      uint8_t*>(s1);
  const uint8_t* sc2 = reinterpret_cast<const uint8_t*>(s2);

  // Check for a range overlap.
  if((sc2 < sc1) && (sc1 < (sc2 + n)))
  {
    sc1 += n;
    sc2 += n;

    for( ; n > static_cast<size_t>(0U); --n)
    {
      // Perform a backwards copy.
      --sc1;
      --sc2;
      *sc1 = *sc2;
    }
  }
  else
  {
    for( ; n > static_cast<size_t>(0U); --n)
    {
      // Perform a forwards copy.
      *sc1 = *sc2;
      ++sc1;
      ++sc2;
    }
  }

  return s1;
}
