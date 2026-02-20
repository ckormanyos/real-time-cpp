///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2014 - 2026.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef MATH_FUNCTIONS_BESSEL_2014_04_30_H
  #define MATH_FUNCTIONS_BESSEL_2014_04_30_H

  #include <cmath>

  #include <math/functions/math_functions_hypergeometric.h>

  namespace math
  {
    namespace functions
    {
      template<typename T>
      T cyl_bessel_j(T v, T x)
      {
        // Compute the Taylor series representation of cyl_bessel_j.
        // There are no checks on input range or parameter boundaries.

        // The following low-precision analysis has been carried out
        // for another perspective on small arguments.

        //   Series[BesselJ[n, x], {x, 0, 7}]
        //   Normal[%]
        //   FullSimplify[%]
        // Then explicitly take the polynomial part and run it through HornerForm[...].
        // The result is the following.
        // (1/(3 Gamma[4 + n])) 2^(-7 - n) x^n (384 (1 + n) (2 + n) (3 + n) - x^2 (576 + n (480 + 96 n) + x^2 (36 + 12 n - x^2)))
        // This should provide good precision for 32-bit float for arguments having (x/n) <= 3/10.

        const T x_half     = x / 2;
        const T v_plus_one = v + 1;

        const T hypergeometric_0f1_term
        {
          math::functions::hypergeometric_0f1(v_plus_one, -(x_half * x_half))
        };

        using std::pow;
        using std::tgamma;

        return (pow(x_half, v) * hypergeometric_0f1_term) / tgamma(v_plus_one);
      }
    }
  } // namespace math::functions

#endif // MATH_FUNCTIONS_BESSEL_2014_04_30_H
