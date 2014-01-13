///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2014.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <cmath>
#include <cstdfloat>
#include <math/special_functions/acosh.h>

// Here, we implement a simplified computation of the
// hyperbolic arc-cosine function (acosh) for std::float32_t.
// The acosh function is implemented with logarithmic functions.

// This provides an example of the calculation of a common
// elementary transcendental function using floating-point
// typedefs having specified widths.

std::float32_t math::acosh(std::float32_t x)
{
  if(x < FLOAT32_C(1.0))
  {
    return std::numeric_limits<std::float32_t>::quiet_NaN();
  }
  else if(std::abs(x) < std::numeric_limits<std::float32_t>::epsilon())
  {
    return FLOAT32_C(0.0);
  }
  else
  {
    const std::float32_t xp = (x + 1);
    const std::float32_t xm = (x - 1);

    return std::log(x + std::sqrt(xm * xp));
  }
}
