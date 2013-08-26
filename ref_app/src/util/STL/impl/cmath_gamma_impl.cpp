///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2013.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <cstdint>
#include <cmath>
#include "cmath_constants_impl.h"
#include "xcmath_impl.h"

// The tgamma function is implemented here.
// This provides an example of a special function calculation.

namespace
{
  float gamma1(float x)
  {
    // Compute the float Gamma(x) for 0 < x < 1.

    if(x < 0.1F)
    {
      // Small-argument Taylor series for 1/gamma.
      const float gsum = (((((((    + 0.0072189432F
                                * x - 0.0096219715F)
                                * x - 0.0421977346F)
                                * x + 0.1665386114F)
                                * x - 0.0420026350F)
                                * x - 0.6558780715F)
                                * x + 0.5772156649F)
                                * x + 1)
                                * x;

      return 1 / gsum;
    }
    else
    {
      // Order-9 polynomial fit.
      const float g1 = ((((((((    - 0.0235850272F
                               * x + 0.1405004023F)
                               * x - 0.3860871683F)
                               * x + 0.6721315341F)
                               * x - 0.8649108124F)
                               * x + 0.9539074630F)
                               * x - 0.9035083713F)
                               * x + 0.9887589417F)
                               * x - 0.5772069549F)
                               * x + 0.9999999703F;

      // Note: We are using one downward recursion here.
      return g1 / x;
    }
  }
}

float tgamma(float x)
{
  // Check for pure zero argument.
  if(xcmath::near_integer(x, std::uint_least8_t(0U)))
  {
    return std::numeric_limits<float>::quiet_NaN();
  }

  // Check for overflow and underflow.
  if(    (x > 35)
     || ((x > -1.0E-4F) && (x < 1.0E-4F))
    )
  {
    return std::numeric_limits<float>::infinity();
  }

  // Is the argument 1 or 2?
  if(   xcmath::near_integer(x, std::uint_least8_t(1U))
     || xcmath::near_integer(x, std::uint_least8_t(2U))
    )
  {
    return 1.0F;
  }

  // Use a positive argument for the Gamma calculation.
  const bool b_neg = (x < 0);
  x = (b_neg ? -x : x);

  // Get any integer recursion and scale the argument.
  const std::uint16_t nx = std::uint16_t(::floor(x));
  x -= float(nx);

  float g = gamma1(x);

  // Do the recursion if necessary.
  for(std::uint16_t recur = 0U; recur < nx; ++recur)
  {
    g *= x;
    ++x;
  }

  // Return (and possibly reflect) the result.
  if(false == b_neg)
  {
    return g;
  }
  else
  {
    const float sin_pi_x = sin(const_pi<float>() * x);

    return -const_pi<float>() / ((x * g) * sin_pi_x);
  }
}
