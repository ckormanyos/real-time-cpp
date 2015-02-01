///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2014.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#if defined(__GNUC__) || (defined(_WIN32) && (_MSC_VER <= 1700))

  #include <cmath>
  #include <cstdfloat>
  #include <cstdint>
  #include "xcmath_impl.h"

  // Here, we implement naive computations of the inverse hyperbolic
  // trigonometric functions asinh, acosh, and atanh for std::float32_t.
  // The inverse hyperbolic trigonometric functions are represented
  // in terms of logarithmic functions.

  // These provide examples of portable calculations of some common
  // elementary transcendental functions using floating-point typedefs
  // having specified widths.

  namespace std
  {
    std::float32_t asinh(std::float32_t);
    std::float32_t acosh(std::float32_t);
    std::float32_t atanh(std::float32_t);
  }

  std::float32_t std::asinh(std::float32_t x)
  {
    // Implement a naive hyperbolic arc-sine function.
    return std::log(x + std::sqrt((x * x) + FLOAT32_C(1.0)));
  }

  std::float32_t std::acosh(std::float32_t x)
  {
    const std::float32_t x_minus_one = x - FLOAT32_C(1.0);

    if(x_minus_one < -std::numeric_limits<std::float32_t>::epsilon())
    {
      return std::numeric_limits<std::float32_t>::quiet_NaN();
    }
    else if(x_minus_one < std::numeric_limits<std::float32_t>::epsilon())
    {
      return FLOAT32_C(1.0);
    }
    else
    {
      // Implement a naive hyperbolic arc-cosine function.
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
      // Implement a naive hyperbolic arc-tangent function.
      const std::float32_t xp = (xx + FLOAT32_C(1.0));
      const std::float32_t xm = (FLOAT32_C(1.0) - xx);

      result = (std::log(xp) - std::log(xm)) / FLOAT32_C(2.0);
    }
    else
    {
      result = std::numeric_limits<std::float32_t>::infinity();
    }

    return ((!is_neg) ? result : -result);
  }

#endif
