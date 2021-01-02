
///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2014 - 2018.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef MATH_FUNCTIONS_BESSEL_2014_04_30_H_
  #define MATH_FUNCTIONS_BESSEL_2014_04_30_H_

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

        const T x_half     = x / 2;
        const T v_plus_one = v + 1;

        const T hypergeometric_0f1_term =
          math::functions::hypergeometric_0f1(v_plus_one, -(x_half * x_half));

        using std::pow;
        using std::tgamma;

        return (pow(x_half, v) * hypergeometric_0f1_term) / tgamma(v_plus_one);
      }
    }
  } // namespace math::functions

#endif // MATH_FUNCTIONS_BESSEL_2014_04_30_H_
