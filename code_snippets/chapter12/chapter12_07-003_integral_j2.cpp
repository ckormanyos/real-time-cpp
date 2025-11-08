///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2017 - 2025.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

// chapter12_07-003_integral_j2.cpp

#include <cmath>
#include <cstdint>
#include <iomanip>
#include <iostream>
#include <limits>
#include <numbers>
#include <sstream>

template<typename real_value_type,
         typename real_function_type>
auto integral(
  const real_value_type& a,
  const real_value_type& b,
  const real_value_type& tol,
  real_function_type real_function) -> real_value_type
{
  std::uint_fast32_t n2(1);

  real_value_type step = ((b - a) / 2U);

  real_value_type result =
    (real_function(a) + real_function(b)) * step;

  const std::uint_fast8_t k_max = UINT8_C(32);

  for(std::uint_fast8_t k(0U); k < k_max; ++k)
  {
    real_value_type sum(0);

    for(std::uint_fast32_t j(0U); j < n2; ++j)
    {
      const std::uint_fast32_t two_j_plus_one =
        (j * UINT32_C(2)) + UINT32_C(1);

      sum +=
        real_function(a + (step * two_j_plus_one));
    }

    const real_value_type tmp = result;

    result = (result / 2U) + (step * sum);

    const real_value_type ratio =
      std::abs(tmp / result);

    const real_value_type delta = std::abs(ratio - 1U);

    if((k > UINT8_C(1)) && (delta < tol))
    {
      break;
    }

    n2 *= 2U;

    step /= 2U;
  }

  return result;
}

template<typename float_type>
auto cyl_bessel_j(const std::uint_fast8_t n,
                  const float_type& x) -> float_type
{
  constexpr float_type eps
    { std::numeric_limits<float_type>::epsilon() };

  const float_type tol { std::sqrt(eps) };

  const float_type jn =
    integral
    (
      float_type(0),
      std::numbers::pi_v<float_type>,
      tol,
      [&x,&n](const float_type& t) -> float_type
      {
        return std::cos(x * std::sin(t) - (n * t));
      }
    )
    / std::numbers::pi_v<float_type>;

  return jn;
}

auto main() -> int;

auto main() -> int
{
  const float j2 { cyl_bessel_j(UINT8_C(2), 1.23F) };

  // Computed result: 0.166369
  // Known value:     0.1663693837...

  std::stringstream strm { };

  strm << "j2: " << std::setprecision(std::numeric_limits<float>::digits10) << j2 << '\n';

  std::cout << strm.str() << std::endl;
}
