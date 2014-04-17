///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2013.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef _INTEGRAL_2012_01_09_H_
  #define _INTEGRAL_2012_01_09_H_

  #include <cstdint>
  #include <complex>

  template<typename value_type,
           typename function_type>
  value_type integral(const value_type a,
                      const value_type b,
                      const value_type tol,
                      function_type function)
  {
    std::uint_fast8_t n = 1U;

    value_type h = (b - a);
    value_type I = (function(a) + function(b)) * (h / 2);

    for(std::uint_fast8_t k = 0U; k < 8U; ++k)
    {
      h /= 2;

      value_type sum(0);
      for(std::uint_fast8_t j = 1U; j <= n; ++j)
      {
        sum += function(value_type(a + (value_type((j * 2) - 1) * h)));
      }

      const value_type I0 = I;
      I = (I / value_type(2)) + (h * sum);

      const value_type ratio = I0 / I;
      const value_type delta = std::abs(ratio - value_type(1));

      if((k > 1U) && (delta < tol))
      {
        break;
      }

      n *= 2U;
    }

    return I;
  }

  template<typename value_type,
           typename function_type>
  std::complex<value_type> integral_complex(const value_type a,
                                            const value_type b,
                                            const value_type tol,
                                            function_type function)
  {
    std::uint_fast8_t n = 1U;

    value_type h = (b - a);
    std::complex<value_type> I = (function(a) + function(b)) * (h / 2);

    for(std::uint_fast8_t k = 0U; k < 8U; ++k)
    {
      h /= 2;

      std::complex<value_type> sum(0);
      for(std::uint_fast8_t j = 1U; j <= n; ++j)
      {
        sum += function(std::complex<value_type>(a + (value_type((j * 2) - 1) * h)));
      }

      const std::complex<value_type> I0 = I;
      I = (I / value_type(2)) + (h * sum);

      const std::complex<value_type> ratio = I0 / I;
      const value_type  delta = std::abs(ratio - value_type(1));

      if((k > 1U) && (delta < tol))
      {
        break;
      }

      n *= 2U;
    }

    return I;
  }

#endif // _INTEGRAL_2012_01_09_H_

/*
#include <cmath>
#include <complex>
#include <math/constants/constants.h>
#include <math/calculus/integral.h>

// Compute y = J1(1.23 + 3.45 I) = -1.12043943555101131903 + 3.65329424719653313092 I.
// N[BesselJ[2, 123/100 + ((345 / 100) I)], 21]

using std::cos;
using std::sin;

const std::complex<float> x(1.23F, 3.45F);
const std::uint_fast8_t n = 2U;

std::complex<float> zj = integral_complex(0.0F,
                                          const_pi<float>(),
                                          static_cast<float>(1.0F / 1024),
                                          [&x, &n](const std::complex<float>& t) -> std::complex<float>
                                          {
                                            return cos(x * sin(t) - (float(n) * t));
                                          }) / const_pi<float>();
*/
