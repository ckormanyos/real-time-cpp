///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2011 - 2013.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <stddef.h>

void* memset(void* s1, int c, size_t n)
{
  char* su1 = (char*) s1;

  for( ; (size_t) 0U < n; --n)
  {
    *su1 = (char) c;
    ++su1;
  }

  return s1;
}

void* memcpy(void* s1, const void* s2, size_t n)
{
  // For additional implementation details, see
  // P.J. Plauger, "The Standard C Library", Figure 14.4, page 400.

  char* su1 = (char*) s1;
  const char* su2 = (const char*) s2;

  for( ; (size_t) 0U < n; --n)
  {
    *su1 = *su2;
    ++su1;
    ++su2;
  }

  return s1;
}

void* memmove(void* s1, const void* s2, size_t n)
{
  // For additional implementation details, see
  // P.J. Plauger, "The Standard C Library", Figure 14.5, page 400.

  // The function memmove does work properly even when its operands overlap.

  char* sc1 = (char*) s1;
  const char* sc2 = (const char*) s2;

  // Check for overlap.
  if((sc2 < sc1) && (sc1 < (sc2 + n)))
  {
    sc1 += n;
    sc2 += n;

    for( ; (size_t) 0u < n; --n)
    {
      *--sc1 = *--sc2; // Copy backwards.
    }
  }
  else
  {
    for( ; (size_t) 0u < n; --n)
    {
      *sc1++ = *sc2++; // Copy forwards.
    }
  }

  return (void*) s1;
}
