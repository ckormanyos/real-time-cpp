///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2026.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <cmath>
#include <limits>
#include <numbers>

// Check that GCC and Clang do not use (-ffast-math / -Ofast / -funsafe-math-optimizations)
#if defined(__GNUC__) || defined(__clang__)
  #if defined(__FAST_MATH__) || defined(__FINITE_MATH_ONLY__) && (__FINITE_MATH_ONLY__ > 0)
    #error "Strict IEEE-754 math is required: disable -ffast-math / -Ofast."
  #endif
#endif

// Check that MSVC does not use (/fp:fast)
#if defined(_MSC_VER)
  #if defined(_M_FP_FAST)
    #error "Strict IEEE-754 math is required: compile with /fp:precise or /fp:strict instead of /fp:fast."
  #endif
#endif

// Exercise a compile-time sanity check detecting 32-bit built-in float.
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
  auto test_stl_numbers_answer() -> bool;
  auto test_stl_numbers_egamma() -> bool;
} // namespace local

auto test_stl_sanity_numbers() -> bool;

auto test_stl_sanity_numbers() -> bool
{
  using namespace local;

  return (test_stl_numbers_answer() && test_stl_numbers_egamma());
}

auto local::test_stl_numbers_answer() -> bool
{
  using namespace std::numbers;

  // Evaluates to 1 + (1 + 2 + 1 + 1) = 6.0F
  const auto x =   std::sqrt(inv_pi_v<float>) / inv_sqrtpi_v<float>
                 + (
                       std::log(std::exp2(log2e_v<float>))
                     + 2.0F
                     + sqrt3_v<float> * inv_sqrt3_v<float>
                     + std::exp(0.0F)
                   );

  // Evaluates to 1 + 2 + 1 + 2 - (-1) = 7.0F
  const auto v =   phi_v<float> * (phi_v<float> - 1.0F)
                 + 1.0F / std::log2(sqrt2_v<float>)
                 + log10e_v<float> * ln10_v<float>
                 + std::pow(e_v<float>, ln2_v<float>)
                 - std::cos(pi_v<float>);

  const int the_answer { static_cast<int>(x * v) };

  const bool result_the_answer_is_ok { (the_answer == 42) };

  return result_the_answer_is_ok;
}

auto local::test_stl_numbers_egamma() -> bool
{
  using namespace std::numbers;

  // 2^-8: exact binary step, 2-point central difference avoids pole distortion
  constexpr float h { 0.00390625F };

  const float approx_egamma { -(std::tgamma(1.0F + h) - std::tgamma(1.0F - h)) / (2.0F * h) };

  const float egamma_ratio { (approx_egamma / egamma_v<float>) };

  // Evaluates to true:
  // approx_egamma / egamma_v<float> is very slightly more than 1 and truncates to 1.
  const bool result_egamma_is_ok { (static_cast<int>(egamma_ratio) == 1) };

  return result_egamma_is_ok;
}
