///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2026.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#if defined(__GNUC__) && !defined(__clang__)
#pragma GCC optimize ("O0")
#endif

#if !defined(__AVR__)
#define USE_COMPLEX_TGAMMA_CHECK
#endif

#include <cmath>
#include <complex>
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

static_assert(result_float_type_is_ok,  "Error: Wrong width of float type");

// Exercise a compile-time sanity check detecting 64-bit built-in double.
constexpr bool
  result_double_type_is_ok
  {
       (std::numeric_limits<double>::radix == 2)
    && (std::numeric_limits<double>::digits >= 53)
    && (std::numeric_limits<double>::min_exponent <= -1021)
    && (std::numeric_limits<double>::max_exponent >= 1024)
  };

static_assert(result_double_type_is_ok, "Error: Wrong width of float type");

namespace local
{
  namespace detail
  {
    static constexpr double poly[]
    {
          0.99999999999980993,
        676.5203681218851,
      -1259.1392167224028,
        771.32342877765313,
        -176.61502916214059,
          12.507343278686905,
          -0.13857109526572012,
           9.9843695780195716e-6,
           1.5056327351493116e-7
    };

    auto complex_gamma(std::complex<double> z) -> std::complex<double>;

    auto complex_gamma(std::complex<double> z) -> std::complex<double>
    {
      // 9-term Lanczos approximation (g = 7) valid for Re(z) > 0.5

      z -= 1.0;

      std::complex<double> x { poly[0] };

      for (int i { 1 }; i < 9; ++i)
      {
        x += poly[i] / (z + static_cast<double>(i));
      }

      const std::complex<double> t { z + 7.5 };

      return std::sqrt(2.0 * std::numbers::pi) * std::pow(t, z + 0.5) * std::exp(-t) * x;
    }
  } // namespace detail

  auto test_stl_numbers_answer() -> bool;
  auto test_stl_numbers_egamma() -> bool;
} // namespace local

auto test_stl_sanity_numbers() -> bool;

auto test_stl_sanity_numbers() -> bool
{
  return
    (
         local::test_stl_numbers_answer()
      && local::test_stl_numbers_egamma()
    );
}

auto local::test_stl_numbers_answer() -> bool
{
  using namespace std::numbers;

  // Evaluates to 1 + (1 + 2 + 1 + 1) = 6.00000000F
  const auto x =   std::sqrt(inv_pi_v<float>) / inv_sqrtpi_v<float>
                 + (
                       std::log(std::exp2(log2e_v<float>))
                     + 2.0F
                     + sqrt3_v<float> * inv_sqrt3_v<float>
                     + std::exp(0.0F)
                   );

  // Evaluates to 1 + 2 + 1 + 2 - (-1) = 7.00000000F
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

  bool result_egamma_is_ok { false };

  {
    // Select an optimal binary step (2^-6) for applying a 4-point
    // central difference rule for differentiation, here using
    // 32-bit float.
    constexpr float h { 0.015625F };

    // Use a 4-point central difference rule:
    // f'(x) approx (-f(x + 2h) + 8f(x + h) - 8f(x - h) + f(x - 2h)) / (12h)
    const float g_p2 { std::tgamma(1.0F + (2.0F * h)) };
    const float g_p1 { std::tgamma(1.0F + h) };
    const float g_m1 { std::tgamma(1.0F - h) };
    const float g_m2 { std::tgamma(1.0F - (2.0F * h)) };

    // Compare with:
    // N[-D[Gamma[x], x] /. x -> 1, 40]
    //   0.5772156649015328606065120900824024310422...
    const float approx_egamma { -(-g_p2 + (8.0F * g_p1) - (8.0F * g_m1) + g_m2) / (12.0F * h) };

    // Compute the relative error. This works whether approx_egamma
    // is slightly above or below egamma_v<float>
    const float rel_error { std::fabs(1.0F - (approx_egamma / egamma_v<float>)) };

    // The tolerance of 1e-5F (approx 84 ULPs in 32-bit float).
    // This easily accommodates the approximate 2.5e-6F actual error.
    constexpr float tolerance { 1.0e-5F };

    result_egamma_is_ok = (rel_error < tolerance);
  }

  #if defined(USE_COMPLEX_TGAMMA_CHECK)
  {
    using namespace std::complex_literals;

    // Step size well below sqrt(epsilon), avoiding O(h^2) truncation error
    constexpr double h_d { 1.0e-16 };

    // Zero subtraction cancellation: directly extracts Im(Gamma(1 + i*h)) / h
    const double approx_egamma_d { -detail::complex_gamma(std::complex<double>(1.0, h_d)).imag() / h_d };

    const double delta { std::fabs(1.0 - (approx_egamma_d / std::numbers::egamma)) };

    // Bit-exact match for float (0 ULP) and within 0-1 ULP for double
    const bool result_approx_egamma_is_ok { (delta < std::numeric_limits<double>::epsilon() * 10.0) };

    result_egamma_is_ok = (result_approx_egamma_is_ok && result_egamma_is_ok);
  }
  #endif

  return result_egamma_is_ok;
}
