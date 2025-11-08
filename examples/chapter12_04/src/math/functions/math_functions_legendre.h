///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2014 - 2025.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef MATH_FUNCTIONS_LEGENDRE_2014_04_30_H
  #define MATH_FUNCTIONS_LEGENDRE_2014_04_30_H

  #include <cmath>

  #include <math/functions/math_functions_hypergeometric.h>

  namespace math
  {
    namespace functions
    {
      template<typename T>
      T legendre_p(T v, T u, T x)
      {
        // Compute the Taylor series representation of legendre_p.
        // There are no checks on input range or parameter boundaries.

        const T my_one(1);

        const T one_plus_x  = my_one + x;
        const T one_minus_x = my_one - x;

        using std::pow;
        using std::tgamma;

        const T one_plus_x_over_one_minus_x_pow_u_half = pow(one_plus_x / one_minus_x, u / 2);

        const T gamma_of_one_minus_u = tgamma(my_one - u);

        const T hypergeometric_2f1_term =
          math::functions::hypergeometric_2f1(-v,
                                               v + my_one,
                                               my_one - u,
                                              (my_one - x) / 2);

        return (one_plus_x_over_one_minus_x_pow_u_half * hypergeometric_2f1_term) / gamma_of_one_minus_u;
      }
    }
  } // namespace math::functions

#endif // MATH_FUNCTIONS_LEGENDRE_2014_04_30_H
