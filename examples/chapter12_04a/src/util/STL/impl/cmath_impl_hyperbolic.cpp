///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2014.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <cmath>
#include <cstdint>
#include "xcmath_impl.h"

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
  // Implement a naive hyperbolic arc-sine function.

  using std::log;
  using std::sqrt;

  return log(x + sqrt((x * x) + 1.0F));
}

extern "C"
float acoshf(float x)
{
  const float x_minus_one = x - 1.0F;

  if(x_minus_one < -std::numeric_limits<float>::epsilon())
  {
    return std::numeric_limits<float>::quiet_NaN();
  }
  else if(x_minus_one < std::numeric_limits<float>::epsilon())
  {
    return 1.0F;
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
