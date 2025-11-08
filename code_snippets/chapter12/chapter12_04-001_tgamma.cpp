///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2019 - 2025.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

// chapter12_04-001_tgamma.cpp

#include <cmath>
#include <concepts>
#include <cstdint>
#include <limits>
#include <iomanip>
#include <iostream>
#include <numbers>
#include <sstream>

auto gamma1(const float& x) -> float
{
  // Compute Gamma(x) for 0 < x < 1 (float).
  if(x < 0.1F)
  {
    // Small-argument Taylor series for 1/gamma.
    const float sum = (((((((    + 0.0072189432F
                             * x - 0.0096219715F)
                             * x - 0.0421977346F)
                             * x + 0.1665386114F)
                             * x - 0.0420026350F)
                             * x - 0.6558780715F)
                             * x + 0.5772156649F)
                             * x + 1)
                             * x;

    return 1.0F / sum;
  }
  else
  {
    // Do the order-9 polynomial fit.
    const float g = ((((((((    - 0.0235850272F
                            * x + 0.1405004023F)
                            * x - 0.3860871683F)
                            * x + 0.6721315341F)
                            * x - 0.8649108124F)
                            * x + 0.9539074630F)
                            * x - 0.9035083713F)
                            * x + 0.9887589417F)
                            * x - 0.5772069549F)
                            * x + 0.9999999703F;

    // Note: We use one downward recursion here.
    return g / x;
  }
}

namespace math
{
  auto tgamma(float x) -> float;
}

auto math::tgamma(float x) -> float
{
  // Is the argument a subnormal?
  if(!std::isfinite(x))
  {
    return x;
  }

  // Check for pure zero argument.
  if(x == 0.0F)
  {
    return std::numeric_limits<float>::quiet_NaN();
  }

  // Check for overflow and underflow.
  if(    (x > 35.0F)
     || ((x > -1.0E-4F) && (x < 1.0E-4F))
    )
  {
    return std::numeric_limits<float>::infinity();
  }

  // Is the argument 1 or 2?
  if((x == 1.0F) || (x == 2.0F))
  {
    return 1.0F;
  }

  // Use a positive argument for the Gamma calculation.
  const bool b_neg { (x < 0.0F) };

  x = std::fabs(x);

  // Get any integer recursion and scale the argument.
  const std::uint_fast8_t nx
    { static_cast<std::uint_fast8_t>(std::floor(x)) };

  x -= static_cast<float>(nx);

  // Calculate gamma of the scaled argument.
  float g { gamma1(x) };

  // Do the recursion if necessary.
  for(std::uint_fast8_t i = UINT8_C(0); i < nx; ++i)
  {
    g *= x;

    ++x;
  }

  // Return (and possibly reflect) the result.
  if(b_neg == false)
  {
    return g;
  }
  else
  {
    const float sin_pi_x
      { std::sin(std::numbers::pi_v<float> * x) };

    return   -std::numbers::pi_v<float>
           / ((x * g) * sin_pi_x);
  }
}

auto main() -> int;

auto main() -> int
{
  std::stringstream strm { };

  strm << "math::tgamma(+0.5F) : " << std::fixed << std::setprecision(std::numeric_limits<float>::digits10)  << math::tgamma(+0.50F) << '\n';
  strm << "math::tgamma(+8.76F): " << std::fixed << std::setprecision(std::numeric_limits<float>::digits10)  << math::tgamma(+8.76F) << '\n';
  strm << "math::tgamma(+0.02F): " << std::fixed << std::setprecision(std::numeric_limits<float>::digits10)  << math::tgamma(+0.02F) << '\n';
  strm << "math::tgamma(-3.45F): " << std::fixed << std::setprecision(std::numeric_limits<float>::digits10)  << math::tgamma(-3.45F) << '\n';

  std::cout << strm.str() << std::endl;
}
