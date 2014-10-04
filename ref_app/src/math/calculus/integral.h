///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2014.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef _INTEGRAL_2012_01_09_H_
  #define _INTEGRAL_2012_01_09_H_

  #include <cstdint>
  #include <complex>

  template<typename real_value_type,
           typename real_function_type>
  real_value_type integral(const real_value_type& a,
                           const real_value_type& b,
                           const real_value_type& tol,
                           real_function_type real_function)
  {
    std::uint_fast8_t n = UINT8_C(1);

    real_value_type h = (b - a) / 2;
    real_value_type I = (real_function(a) + real_function(b)) * h;

    for(std::uint_fast8_t k = UINT8_C(0); k < UINT8_C(8); ++k)
    {
      real_value_type sum(0);

      for(std::uint_fast8_t j = UINT8_C(1); j <= n; ++j)
      {
        sum += function(real_value_type(a + (real_value_type((j * 2) - 1) * h)));
      }

      const real_value_type I0 = I;
      I = (I / real_value_type(2)) + (h * sum);

      const real_value_type ratio = std::abs(I0 / I);
      const real_value_type delta = std::abs(ratio - real_value_type(1));

      if((k > UINT8_C(1)) && (delta < tol))
      {
        break;
      }

      n *= 2;

      h /= 2;
    }

    return I;
  }

  template<typename real_value_type,
           typename complex_function_type>
  std::complex<real_value_type> integral_complex(const real_value_type& a,
                                                 const real_value_type& b,
                                                 const real_value_type& tol,
                                                 complex_function_type complex_function)
  {
    typedef std::complex<real_value_type> complex_value_type;

    std::uint_fast8_t n = UINT8_C(1);

    real_value_type    h = (b - a) / 2;
    complex_value_type I = (complex_function(a) + complex_function(b)) * h;

    for(std::uint_fast8_t k = UINT8_C(0); k < UINT8_C(8); ++k)
    {
      std::complex<real_value_type> sum(0);

      for(std::uint_fast8_t j = UINT8_C(1); j <= n; ++j)
      {
        sum += complex_function(complex_value_type(a + (real_value_type((j * 2) - 1) * h)));
      }

      const complex_value_type I0 = I;
      I = (I / real_value_type(2)) + (h * sum);

      const real_value_type ratio = std::abs(I0 / I);
      const real_value_type delta = std::abs(ratio - real_value_type(1));

      if((k > UINT8_C(1)) && (delta < tol))
      {
        break;
      }

      n *= 2;

      h /= 2;
    }

    return I;
  }

#endif // _INTEGRAL_2012_01_09_H_

/*
#include <cmath>
#include <complex>
#include <math/constants/constants.h>
#include <math/calculus/integral.h>

void do_something();

void do_something()
{
  // Compute y = J1(1.23 + 3.45 I) = -1.12043943555101131903 + 3.65329424719653313092 I.
  // N[BesselJ[2, 123/100 + ((345 / 100) I)], 21]

  using std::cos;
  using std::sin;

  const std::complex<float> x(1.23F, 3.45F);
  const std::uint_fast8_t n = 2U;

  std::complex<float> zj = integral_complex(0.0F,
                                            math::constants::pi<float>(),
                                            static_cast<float>(1.0F / 1024),
                                            [&x, &n](const std::complex<float>& t) -> std::complex<float>
                                            {
                                              return cos(x * sin(t) - (float(n) * t));
                                            }) / math::constants::pi<float>();

  static_cast<void>(zj);
}
*/
