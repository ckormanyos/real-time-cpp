///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2026.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <algorithm>
#include <array>
#include <cmath>
#include <cstdint>
#include <limits>
#include <numbers>

extern "C" float  tgammaf(float x);
extern "C" double tgamma (double z);

namespace xcmath_impl
{
  constexpr auto tgamma_inverse_taylor_series   (float) -> float;
  constexpr auto tgamma_polynomial_approximation(float) -> float;

  template<typename float_type>
  constexpr auto near_integer(const float_type& x, const std::uint_least8_t n) -> bool
  {
    const float_type
      n_eps
      {
        static_cast<float_type>
        (
            static_cast<float_type>((std::max)(std::uint_least8_t(2U), std::uint_least8_t(n + 1U)))
          * std::numeric_limits<float_type>::epsilon()
        )
      };

    const float_type n_minus_n_eps { static_cast<float_type>(n) - n_eps };
    const float_type n_plus_n_eps  { static_cast<float_type>(n) + n_eps };

    return ((x > n_minus_n_eps) && (x < n_plus_n_eps));
  }

  constexpr auto tgamma_inverse_taylor_series(float x) -> float
  {
    // Implement a small-argument Taylor series for 1 / tgamma(x).
    const float inverse_series_value
      = (((((((     + 0.0072189432F
                * x - 0.0096219715F)
                * x - 0.0421977346F)
                * x + 0.1665386114F)
                * x - 0.0420026350F)
                * x - 0.6558780715F)
                * x + 0.5772156649F)
                * x + 1.0F)
                * x;

      return float(1.0F / inverse_series_value);
  }

  constexpr auto tgamma_polynomial_approximation(float x) -> float
  {
    // Implement an order-9 polynomial fit for gamma(1 + x).
    const float polynomial_approximation_value
      = ((((((((    - 0.0235850272F
                * x + 0.1405004023F)
                * x - 0.3860871683F)
                * x + 0.6721315341F)
                * x - 0.8649108124F)
                * x + 0.9539074630F)
                * x - 0.9035083713F)
                * x + 0.9887589417F)
                * x - 0.5772069549F)
                * x + 0.9999999703F;

    // Return the polynomial fit for gamma(x).
    // One downward recursion is used here.
    return float(polynomial_approximation_value / x);
  }
}

// Here, we compute the tgamma function for built-in float.
// This provides an example of a portable specfun calculation.

extern "C"
auto tgammaf(float x) -> float
{
  // Use a positive argument for the Gamma calculation.
  const bool b_neg { (x < 0) };

  x = ((!b_neg) ? x : -x);

  // Check if the argument is pure zero or indistinguishably close to zero.
  if(x < (std::numeric_limits<float>::min)())
  {
    return std::numeric_limits<float>::quiet_NaN();
  }

  // Check if the argument is smaller than epsilon().
  if(x < std::numeric_limits<float>::epsilon())
  {
    return ((!b_neg) ? (+1.0F / x) - std::numbers::egamma_v<float>
                     : (-1.0F / x) - std::numbers::egamma_v<float>);
  }

  // Check for overflow.
  if(x > 35.04F)
  {
    return std::numeric_limits<float>::infinity();
  }

  // Check if the argument is very close to +1 or +2?
  if(!b_neg)
  {
    using xcmath_impl::near_integer;

    const bool is_near_one { near_integer(x, static_cast<std::uint_least8_t>(1U)) };
    const bool is_near_two { near_integer(x, static_cast<std::uint_least8_t>(2U)) };

    if(is_near_one || is_near_two)
    {
      return 1.0F;
    }
  }

  const float floor_x { std::floor(x) };

  const bool is_integer { ((floor_x <= x) && (x <= floor_x)) };

  // Evaluate the number of recursions needed in order to reach
  // the range 0 < x < 1, and scale the argument accordingly.
  std::uint_least8_t n_recur { static_cast<std::uint_least8_t>(floor_x) };

  float gamma_value;

  if((!b_neg) && is_integer)
  {
    --n_recur;
    x = 1.0F;
    gamma_value = 1.0F;
  }
  else
  {
    x -= n_recur;

    // Obtain an approximation of tgamma(x), where x has
    // perhaps been negated and/or scaled to a lower value.
    gamma_value = ((x < 0.1F) ? xcmath_impl::tgamma_inverse_taylor_series(x)
                              : xcmath_impl::tgamma_polynomial_approximation(x));
  }

  // Scale up the result via recursion if necessary.
  for(std::uint_least8_t k = static_cast<std::uint_least8_t>(0U); k < n_recur; ++k)
  {
    gamma_value *= x;

    ++x;
  }

  // Return (and possibly reflect) the result.
  if(!b_neg)
  {
    return gamma_value;
  }
  else
  {
    using std::sin;

    const float sin_pi_x { sin(std::numbers::pi_v<float> * x) };

    return -std::numbers::pi_v<float> / ((x * gamma_value) * sin_pi_x);
  }
}

namespace detail
{
  // 9-term Lanczos coefficients for g = 7 (IEEE 754 binary64 precision)
  inline constexpr std::array<double, 9> lanczos_p =
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

  // sqrt(2 * pi) derived from std::numbers::pi_v<double>
  // Note: std::sqrt is constexpr in C++26, or evaluated at compile-time by GCC
  inline constexpr double sqrt_2pi = 2.50662827463100050242;
} // namespace detail

extern "C"
double tgamma(double z)
{
  using std::numbers::pi_v;
  constexpr double inf = std::numeric_limits<double>::infinity();
  constexpr double nan = std::numeric_limits<double>::quiet_NaN();

  const int fpc_result { std::fpclassify(z) };

  const bool is_neg { z < 0.0 };

  // Handle special values and poles.
  if(std::isnan(z) || ((fpc_result == FP_INFINITE) && is_neg)) { return nan; }
  if(fpc_result == FP_INFINITE) { return inf; }
  if(fpc_result == FP_ZERO)     { return is_neg ? -inf : inf; }

  // Reflection formula: Gamma(z) = pi / (sin(pi * z) * Gamma(1 - z)).
  if(is_neg)
  {
    const double floor_z { std::floor(z) };

    const bool is_integer { ((floor_z <= z) && (z <= floor_z)) };

    if (is_integer) { return nan; } // Pole at negative integers

    return pi_v<double> / (std::sin(pi_v<double> * z) * tgamma(1.0 - z));
  }

  // Overflow threshold for IEEE 754 binary64 (~171.624)
  if(z > 171.6243769563027) { return inf; }

  z -= 1.0;
  double x = detail::lanczos_p[0];

  for(std::uint8_t i = 1; i < detail::lanczos_p.size(); ++i)
  {
    x += detail::lanczos_p[i] / (z + static_cast<double>(i));
  }

  const double t = z + 7.5; // z + g + 0.5

  // Prevent premature overflow in std::pow(t, z + 0.5) when 140 < z <= 171.624
  if(z > 140.0)
  {
    const double half_pow = std::pow(t, 0.5 * z + 0.25);

    return detail::sqrt_2pi * half_pow * std::exp(-t) * half_pow * x;
  }

  return detail::sqrt_2pi * std::pow(t, z + 0.5) * std::exp(-t) * x;
}
