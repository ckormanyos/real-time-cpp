#ifndef _DERIVATIVE_2012_01_09_H_
  #define _DERIVATIVE_2012_01_09_H_

  template<typename value_type,
           typename function_type>
  value_type derivative(const value_type x,
                        const value_type dx,
                        function_type function)
  {
    // Compute the function derivative using a three point
    // central difference rule of O(dx^6).

    const value_type dx1 = dx;
    const value_type dx2 = dx1 * 2;
    const value_type dx3 = dx1 * 3;

    const value_type m1 = (  function(x + dx1)
                           - function(x - dx1)) / 2;
    const value_type m2 = (  function(x + dx2)
                           - function(x - dx2)) / 4;
    const value_type m3 = (  function(x + dx3)
                           - function(x - dx3)) / 6;

    const value_type fifteen_m1 = 15 * m1;
    const value_type six_m2     =  6 * m2;
    const value_type ten_dx1    = 10 * dx1;

    return ((fifteen_m1 - six_m2) + m3) / ten_dx1;
  }

#endif // _DERIVATIVE_2012_01_09_H_

/*
#include <cmath>
#include <math/constants/constants.h>
#include <math/calculus/derivative.h>

const float x = const_pi<float>() / 3.0F;

// Should be very near 0.5.
const float y = derivative(x,
                           0.01F,
                           [](const float& x) -> float
                           {
                             return sin(x);
                           });
*/
