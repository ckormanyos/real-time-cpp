///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2020.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <cmath>
#include <cstdint>

#include "xcmath_impl.h"

#if defined(__GNUC__) && defined(__AVR__)
extern "C" float tgammaf(float x);
#endif

// Here, we compute the tgamma function for float.
// This provides an example of a portable special function
// calculation using floating-point type definitions having
// specified widths from the proposed <cstdfloat>.

namespace xcmath_impl
{
  float tgamma_inverse_taylor_series   (float);
  float tgamma_polynomial_approximation(float);

  float tgamma_inverse_taylor_series(float x)
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

  float tgamma_polynomial_approximation(float x)
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

extern "C"
float tgammaf(float x)
{
  // Use a positive argument for the Gamma calculation.
  const bool b_neg = (x < 0);

  x = ((!b_neg) ? x : -x);

  // Check if the argument is pure zero or indistinguishably close to zero.
  if(x < (std::numeric_limits<float>::min)())
  {
    return std::numeric_limits<float>::quiet_NaN();
  }

  // Check if the argument is smaller than epsilon().
  if(x < std::numeric_limits<float>::epsilon())
  {
    using xcmath_impl::euler;

    return ((!b_neg) ? (+1.0F / x) - euler<float>()
                     : (-1.0F / x) - euler<float>());
  }

  // Check for overflow.
  if(x > 35.04F)
  {
    return std::numeric_limits<float>::infinity();
  }

  // Check if the argument is very close to +1 or +2?
  if(b_neg == false)
  {
    using xcmath_impl::near_integer;

    const bool is_near_one = near_integer(x, static_cast<std::uint_least8_t>(1U));
    const bool is_near_two = near_integer(x, static_cast<std::uint_least8_t>(2U));

    if(is_near_one || is_near_two)
    {
      return 1.0F;
    }
  }

  // Evaluate the number of recursions needed in order to reach
  // the range 0 < x < 1, and scale the argument accordingly.
  const std::uint_least8_t n_recur = static_cast<std::uint_least8_t>(::floorf(x));

  x -= n_recur;

  // Obtain an approximation of tgamma(x), where x has
  // perhaps been negated and/or scaled to a lower value.
  float gamma_value = ((x < 0.1F) ? xcmath_impl::tgamma_inverse_taylor_series(x)
                                  : xcmath_impl::tgamma_polynomial_approximation(x));

  // Scale up the result via recursion if necessary.
  for(std::uint_least8_t k = static_cast<std::uint_least8_t>(0U); k < n_recur; ++k)
  {
    gamma_value *= x;

    ++x;
  }

  // Return (and possibly reflect) the result.
  if(false == b_neg)
  {
    return gamma_value;
  }
  else
  {
    using xcmath_impl::pi;

    using std::sin;

    const float sin_pi_x = sin(pi<float>() * x);

    return -pi<float>() / ((x * gamma_value) * sin_pi_x);
  }
}
