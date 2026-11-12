///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2014 - 2026.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include "xcmath_impl.h"

#include <cmath>
#include <cstdint>
#include <limits>

#if defined(__GNUC__) && defined(__AVR__)
extern "C" float asinhf(float x);
extern "C" float acoshf(float x);
extern "C" float atanhf(float x);
#endif

// Here, we implement naive computations of the inverse hyperbolic
// trigonometric functions asinh, acosh, and atanh for float.
// The inverse hyperbolic trigonometric functions are represented
// in terms of logarithmic functions.

// These provide examples of portable calculations of some common
// elementary transcendental functions using floating-point typedefs
// having specified widths.

extern "C"
float asinhf(float x)
{
  const bool is_negative = (x < 0.0F);
  const float abs_x = ((!is_negative) ? x : -x);

  if(abs_x < std::sqrt(std::numeric_limits<float>::epsilon()))
  {
    return x;
  }

  using std::log;
  using std::sqrt;

  const float result =
    (abs_x > 1.0F)
      ? log(abs_x) + log(1.0F + sqrt(1.0F + ((1.0F / abs_x) * (1.0F / abs_x))))
      : log(abs_x + sqrt((abs_x * abs_x) + 1.0F));

  return ((!is_negative) ? result : -result);
}

extern "C"
float acoshf(float x)
{
  const float x_minus_one = x - 1.0F;

  if(x < 1.0F)
  {
    return std::numeric_limits<float>::quiet_NaN();
  }
  else if(x_minus_one < std::numeric_limits<float>::epsilon())
  {
    return 0.0F;
  }
  else
  {
    // Implement a naive hyperbolic arc-cosine function.

    using std::log;
    using std::sqrt;

    const float xp = (x + 1.0F);
    const float xm = (x - 1.0F);

    return log(x + sqrt(xm * xp));
  }
}

extern "C"
float atanhf(float x)
{
  const bool is_neg = (x < 0.0F);

  const float xx = ((!is_neg) ? x : -x);

  if(xx > 1.0F)
  {
    return std::numeric_limits<float>::quiet_NaN();
  }

  float result;

  if(xx < 1.0F)
  {
    // Implement a naive hyperbolic arc-tangent function.
    const float xp = (xx + 1.0F);
    const float xm = (1.0F - xx);

    using std::log;

    result = (float) (log(xp) - log(xm)) / 2.0F;
  }
  else
  {
    result = std::numeric_limits<float>::infinity();
  }

  return ((!is_neg) ? result : -result);
}
