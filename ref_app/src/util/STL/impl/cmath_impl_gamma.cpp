///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2014.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#if defined(__GNUC__) || (defined(_WIN32) && (_MSC_VER <= 1700))

  #include <cmath>
  #include <cstdint>
  #include <cstdfloat>
  #include "xcmath_impl.h"

  // Here, we compute the tgamma function for std::float32_t.
  // This provides an example of a portable special function
  // calculation using floating-point type definitions having
  // specified widths (i.e., in the proposed <cstdfloat>).

  namespace detail
  {
    std::float32_t tgamma_taylor_series           (std::float32_t x);
    std::float32_t tgamma_polynomial_approximation(std::float32_t x);
  }

  std::float32_t detail::tgamma_taylor_series(std::float32_t x)
  {
    // Perform the small-argument Taylor series for 1 / tgamma(x).
    const std::float32_t gamma_inverse_series
      = (((((((     + FLOAT32_C(0.0072189432)
                * x - FLOAT32_C(0.0096219715))
                * x - FLOAT32_C(0.0421977346))
                * x + FLOAT32_C(0.1665386114))
                * x - FLOAT32_C(0.0420026350))
                * x - FLOAT32_C(0.6558780715))
                * x + FLOAT32_C(0.5772156649))
                * x + FLOAT32_C(1.0))
                * x;

      return FLOAT32_C(1.0) / gamma_inverse_series;
    }

  std::float32_t detail::tgamma_polynomial_approximation(std::float32_t x)
  {
    // Perform the order-9 polynomial fit for tgamma(1 + x).
    const std::float32_t gamma_polynomial_approximation
      = ((((((((    - FLOAT32_C(0.0235850272)
                * x + FLOAT32_C(0.1405004023))
                * x - FLOAT32_C(0.3860871683))
                * x + FLOAT32_C(0.6721315341))
                * x - FLOAT32_C(0.8649108124))
                * x + FLOAT32_C(0.9539074630))
                * x - FLOAT32_C(0.9035083713))
                * x + FLOAT32_C(0.9887589417))
                * x - FLOAT32_C(0.5772069549))
                * x + FLOAT32_C(0.9999999703);

    // Note that we are using one downward recursion here.
    return gamma_polynomial_approximation / x;
  }

  namespace std { std::float32_t tgamma(std::float32_t); }

  std::float32_t std::tgamma(std::float32_t x)
  {
    // Check for pure zero argument.
    if(xcmath::near_integer(x, static_cast<std::uint_least8_t>(0U)))
    {
      return std::numeric_limits<std::float32_t>::quiet_NaN();
    }

    // Check for overflow and underflow.
    const bool has_overflow_high_range = (x > FLOAT32_C(35.0));
    const bool has_overflow_low_range  = (std::abs(x) < FLOAT32_C(1.0E-4));

    if(has_overflow_high_range || has_overflow_low_range)
    {
      return std::numeric_limits<std::float32_t>::infinity();
    }

    // Is the argument 1 or 2?
    if(   xcmath::near_integer(x, static_cast<std::uint_least8_t>(1U))
       || xcmath::near_integer(x, static_cast<std::uint_least8_t>(2U))
      )
    {
      return FLOAT32_C(1.0);
    }

    // Use a positive argument for the Gamma calculation.
    const bool b_neg = (x < 0);
    x = ((!b_neg) ? x : -x);

    // Evaluate the number of recursions needed in order to reach
    // the range 0 < x < 1, and scale the argument accordingly.
    const std::uint_least8_t n_recur = static_cast<std::uint_least8_t>(std::floor(x));
    x -= n_recur;

    // Obtain an approximation of the tgamma(x), where x has
    // perhaps been negated and/or scaled to a lower value.
    std::float32_t gamma_value = ((x < FLOAT32_C(0.1)) ? detail::tgamma_taylor_series(x)
                                                       : detail::tgamma_polynomial_approximation(x));

    // Scale up the result via recursion, if necessary.
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
      const std::float32_t sin_pi_x = std::sin(xcmath::pi<std::float32_t>() * x);

      return -xcmath::pi<std::float32_t>() / ((x * gamma_value) * sin_pi_x);
    }
  }

#endif
