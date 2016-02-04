///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2014.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#if defined(__GNUC__) || (defined(_WIN32) && (_MSC_VER <= 1700))

  #include <cmath>
  #include <cstdfloat>
  #include <cstdint>
  #include "xcmath_impl.h"

  // Here, we compute the tgamma function for std::float32_t.
  // This provides an example of a portable special function
  // calculation using floating-point type definitions having
  // specified widths from the proposed <cstdfloat>.

  namespace detail
  {
    std::float32_t tgamma_inverse_taylor_series   (std::float32_t);
    std::float32_t tgamma_polynomial_approximation(std::float32_t);

    std::float32_t tgamma_inverse_taylor_series(std::float32_t x)
    {
      // Implement a small-argument Taylor series for 1 / tgamma(x).
      const std::float32_t inverse_series_value
        = (((((((     + FLOAT32_C(0.0072189432)
                  * x - FLOAT32_C(0.0096219715))
                  * x - FLOAT32_C(0.0421977346))
                  * x + FLOAT32_C(0.1665386114))
                  * x - FLOAT32_C(0.0420026350))
                  * x - FLOAT32_C(0.6558780715))
                  * x + FLOAT32_C(0.5772156649))
                  * x + FLOAT32_C(1.0))
                  * x;

        return FLOAT32_C(1.0) / inverse_series_value;
    }

    std::float32_t tgamma_polynomial_approximation(std::float32_t x)
    {
      // Implement an order-9 polynomial fit for gamma(1 + x).
      const std::float32_t polynomial_approximation_value
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

      // Return the polynomial fit for gamma(x).
      // One downward recursion is used here.
      return (polynomial_approximation_value / x);
    }
  }

  namespace std
  {
    std::float32_t tgamma(std::float32_t);
  }

  std::float32_t std::tgamma(std::float32_t x)
  {
    // Use a positive argument for the Gamma calculation.
    const bool b_neg = (x < 0);

    x = ((!b_neg) ? x : -x);

    // Check if the argument is pure zero or indistinguishably close to zero.
    if(x < (std::numeric_limits<std::float32_t>::min)())
    {
      return std::numeric_limits<std::float32_t>::quiet_NaN();
    }

    // Check if the argument is smaller than epsilon().
    if(x < std::numeric_limits<std::float32_t>::epsilon())
    {
      using xcmath::euler;

      return ((!b_neg) ? (FLOAT32_C(+1.0) / x) - euler<std::float32_t>()
                       : (FLOAT32_C(-1.0) / x) - euler<std::float32_t>());
    }

    // Check for overflow.
    if(x > FLOAT32_C(35.04))
    {
      return std::numeric_limits<std::float32_t>::infinity();
    }

    // Check if the argument is very close to +1 or +2?
    if(b_neg == false)
    {
      using xcmath::near_integer;

      const bool is_near_one = near_integer(x, static_cast<std::uint_least8_t>(1U));
      const bool is_near_two = near_integer(x, static_cast<std::uint_least8_t>(2U));

      if(is_near_one || is_near_two)
      {
        return FLOAT32_C(1.0);
      }
    }

    // Evaluate the number of recursions needed in order to reach
    // the range 0 < x < 1, and scale the argument accordingly.
    const std::uint_least8_t n_recur = static_cast<std::uint_least8_t>(std::floor(x));

    x -= n_recur;

    // Obtain an approximation of tgamma(x), where x has
    // perhaps been negated and/or scaled to a lower value.
    std::float32_t gamma_value = ((x < FLOAT32_C(0.1)) ? detail::tgamma_inverse_taylor_series(x)
                                                       : detail::tgamma_polynomial_approximation(x));

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
      using xcmath::pi;

      const std::float32_t sin_pi_x = std::sin(pi<std::float32_t>() * x);

      return -pi<std::float32_t>() / ((x * gamma_value) * sin_pi_x);
    }
  }

#endif
