///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2014.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include "cmath_impl.h"

// Here, we implement computations of the inverse hyperbolic
// trigonometric functions asinh, acosh, and atanh for std::float32_t.
// The functions are implemented with logarithmic functions.

// This provides an example of calculating some common elementary
// transcendental functions using floating-point typedefs having
// specified widths.

std::float32_t std::asinh(std::float32_t x)
{
  return std::log(x + std::sqrt((x * x) + FLOAT32_C(1.0)));
}

std::float32_t std::acosh(std::float32_t x)
{
  if(x < FLOAT32_C(1.0))
  {
    return std::numeric_limits<std::float32_t>::quiet_NaN();
  }
  else if((x - FLOAT32_C(1.0)) < std::numeric_limits<std::float32_t>::epsilon())
  {
    return FLOAT32_C(0.0);
  }
  else
  {
    const std::float32_t xp = (x + FLOAT32_C(1.0));
    const std::float32_t xm = (x - FLOAT32_C(1.0));

    return std::log(x + std::sqrt(xm * xp));
  }
}

std::float32_t std::atanh(std::float32_t x)
{
  const bool is_neg = (x < FLOAT32_C(0.0));

  const std::float32_t xx = ((!is_neg) ? x : -x);

  if(xx > FLOAT32_C(1.0))
  {
    return std::numeric_limits<std::float32_t>::quiet_NaN();
  }

  std::float32_t result;

  if(xx < FLOAT32_C(1.0))
  {
    const std::float32_t xp = (xx + FLOAT32_C(1.0));
    const std::float32_t xm = (xx - FLOAT32_C(1.0));

    result = (std::log(xp) - std::log(-xm)) / FLOAT32_C(2.0);
  }
  else
  {
    result = std::numeric_limits<std::float32_t>::infinity();
  }

  return ((!is_neg) ? result : -result);
}
