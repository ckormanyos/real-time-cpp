///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2013.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

/*
#include "../cmath_impl.h"
#include "../limits_impl.h"

// The acosh function is implemented here for the AVR(R).
// This provides an example of a transcendental function calculation.
// Note that double is the same as float for this compier.

float acosh(float x)
{
  if(!isfinite(x))
  {
    return x;
  }

  if(x < 1.0)
  {
    return std::numeric_limits<float>::quiet_NaN();
  }
  else if(1 == x)
  {
    return 0.0;
  }
  else
  {
    const float xp(x + 1);
    const float xm(x - 1);
    return log(x + (xp * sqrt(xm / xp)));
  }
}

double acosh(double x)
{
  return static_cast<double>(acosh(static_cast<float>(x)));
}
*/
