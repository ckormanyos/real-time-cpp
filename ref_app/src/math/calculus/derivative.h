///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2025.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef DERIVATIVE_2012_01_09_H
  #define DERIVATIVE_2012_01_09_H

  namespace math
  {
    template<typename real_value_type,
             typename real_function_type>
    auto derivative(const real_value_type& x,
                    const real_value_type& dx,
                    real_function_type real_function) -> real_value_type
    {
      // Compute the first derivative of the input function
      // using a three-point central difference rule of O(dx^6).

      const real_value_type dx2(dx  + dx);
      const real_value_type dx3(dx2 + dx);

      const real_value_type m1((  real_function(x + dx)
                                - real_function(x - dx))  / 2);
      const real_value_type m2((  real_function(x + dx2)
                                - real_function(x - dx2)) / 4);
      const real_value_type m3((  real_function(x + dx3)
                                - real_function(x - dx3)) / 6);

      const real_value_type fifteen_m1(m1 * 15);
      const real_value_type six_m2    (m2 *  6);
      const real_value_type ten_dx    (dx * 10);

      return ((fifteen_m1 - six_m2) + m3) / ten_dx;
    }

    template<typename real_value_type,
             typename real_function_type>
    auto derivative_two(const real_value_type& x,
                        const real_value_type& dx,
                        real_function_type real_function) -> real_value_type
    {
      // Compute the second derivative of real_function using
      // a three-point central difference rule of O(dx^6).

      const real_value_type fn2(real_function(x) * 2);
      const real_value_type dx2(dx  + dx);
      const real_value_type dx3(dx2 + dx);

      const real_value_type c1(   real_function(x + dx)
                                - fn2
                                + real_function(x - dx));
      const real_value_type c2((  real_function(x + dx2)
                                - fn2
                                + real_function(x - dx2)) / 4);
      const real_value_type c3((  real_function(x + dx3)
                                - fn2
                                + real_function(x - dx3)) / 9);

      return ((((c1 * 54) - (c2 * 9)) - (c3 * 2)) / (dx * 43)) / dx;
    }
  } // namespace math

#endif // DERIVATIVE_2012_01_09_H
