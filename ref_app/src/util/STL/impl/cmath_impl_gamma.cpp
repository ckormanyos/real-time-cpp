///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2026.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <algorithm>
#include <cmath>
#include <cstdint>
#include <limits>
#include <numbers>

#if defined(__GNUC__) && defined(__AVR__)
extern "C" float tgammaf(float x);
#endif

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

  using std::floor;

  // Evaluate the number of recursions needed in order to reach
  // the range 0 < x < 1, and scale the argument accordingly.
  const float floor_x { floor(x) };

  std::uint_least8_t n_recur { static_cast<std::uint_least8_t>(floor_x) };

  const bool is_integer { ((floor_x <= x) && (x <= floor_x)) };

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
