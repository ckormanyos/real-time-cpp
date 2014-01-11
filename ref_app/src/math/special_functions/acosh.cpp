///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2013.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <cmath>
#include <cstdfloat>
#include <math/special_functions/acosh.h>
#include <math/tools/tools.h>

// The acosh function is implemented here using logarithmic functions.
// This provides an example of a transcendental function calculation.

std::float32_t math::acosh(std::float32_t x)
{
  if(x < FLOAT32_C(1.0))
  {
    return std::numeric_limits<std::float32_t>::quiet_NaN();
  }
  else if(math::tools::near_integer(x, std::uint_least8_t(1U)))
  {
    return FLOAT32_C(0.0);
  }
  else
  {
    const std::float32_t xp = (x + 1);
    const std::float32_t xm = (x - 1);

    return std::log(x + (xp * std::sqrt(xm / xp)));
  }
}
