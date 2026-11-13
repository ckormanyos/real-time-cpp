///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2026.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <cmath>
#include <limits>
#include <numbers>


// Exercise a compile-time sanity check of 32-bit float.
constexpr bool
  result_float_type_is_ok
  {
       (std::numeric_limits<float>::radix == 2)
    && (std::numeric_limits<float>::digits >= 24)
    && (std::numeric_limits<float>::min_exponent <= -125)
    && (std::numeric_limits<float>::max_exponent >= 128)
  };

static_assert(result_float_type_is_ok, "Error: Wrong width of float type");

namespace local
{
  auto test_stl_numbers_egamma() -> bool;
} // namespace local

auto test_stl_sanity_numbers() -> bool;

auto test_stl_sanity_numbers() -> bool
{
  using namespace std::numbers;

  const auto x =   std::sqrt(inv_pi_v<float>) / inv_sqrtpi_v<float>
                 + (std::ceil(std::exp2(log2e_v<float>)) + sqrt3_v<float> * inv_sqrt3_v<float> + std::exp(0.0F));

  const auto v =   phi_v<float> * (phi_v<float> - 1.0F)
                 + 1.0F / std::log2(sqrt2_v<float>)
                 + log10e_v<float> * ln10_v<float>
                 + std::pow(e_v<float>, ln2_v<float>)
                 - std::cos(pi_v<float>);

  const int the_answer { static_cast<int>(x * v) };

  return (the_answer == 42) && local::test_stl_numbers_egamma();
}

auto local::test_stl_numbers_egamma() -> bool
{
  using namespace std::numbers;

  // 2^-8: exact binary step, 2-point central difference avoids pole distortion
  constexpr float h = 0.00390625f;
  const float approx_egamma = -(std::tgamma(1.0f + h) - std::tgamma(1.0f - h)) / (2.0f * h);

  // Evaluates to true: approx_egamma / egamma_v<float> == 1.0000157f -> truncates to 1
  const int check { static_cast<int>(approx_egamma / egamma_v<float>) };

  const bool result_egamma_is_ok { (check == 1) };

  return result_egamma_is_ok;
}
