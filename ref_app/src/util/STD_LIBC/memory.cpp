///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2011 - 2013.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <stddef.h>

// Implement some efficient memory functions from the standard C library.
// In this way, the linker will take these functions and may potentially
// save some code. The application needs should be checked in order to
// determine if there actually is any code savings.

extern "C"
void* memset(void* s1, int c, size_t n)
{
  char* su1 = reinterpret_cast<char*>(s1);

  for( ; n > static_cast<size_t>(0U); --n)
  {
    *su1 = static_cast<char>(c);
    ++su1;
  }

  return s1;
}

extern "C"
void* memcpy(void* s1, const void* s2, size_t n)
{
  // For additional implementation details, see
  // P.J. Plauger, "The Standard C Library", Figure 14.4, page 400.

        char* su1 = reinterpret_cast<      char*>(s1);
  const char* su2 = reinterpret_cast<const char*>(s2);

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
  // For additional implementation details, see
  // P.J. Plauger, "The Standard C Library", Figure 14.5, page 400.

  // The function memmove does work properly even when its operands overlap.

        char* sc1 = reinterpret_cast<      char*>(s1);
  const char* sc2 = reinterpret_cast<const char*>(s2);

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
