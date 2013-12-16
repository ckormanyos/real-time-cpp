///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2013.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef _DERIVATIVE_2012_01_09_H_
  #define _DERIVATIVE_2012_01_09_H_

  template<typename value_type,
           typename function_type>
  value_type derivative(const value_type x,
                        const value_type dx,
                        function_type function)
  {
    // Compute the first derivative of the input function
    // using a three-point central difference rule of O(dx^6).

    const value_type dx2(dx * 2U);
    const value_type dx3(dx * 3U);

    const value_type m1((  function(x + dx)
                         - function(x - dx))  / 2U);
    const value_type m2((  function(x + dx2)
                         - function(x - dx2)) / 4U);
    const value_type m3((  function(x + dx3)
                         - function(x - dx3)) / 6U);

    const value_type fifteen_m1(m1 * 15U);
    const value_type six_m2    (m2 *  6U);
    const value_type ten_dx    (dx * 10U);

    return ((fifteen_m1 - six_m2) + m3) / ten_dx;
  }

  template<typename value_type,
           typename function_type>
  value_type derivative_two(const value_type x,
                            const value_type dx,
                            function_type function)
  {
    // Compute the second derivative of the input function
    // using a three-point central difference rule of O(dx^6).

    const value_type fn2(function(x) * 2U);
    const value_type dx2(dx * 2U);
    const value_type dx3(dx * 3U);

    const value_type c1(   function(x + dx)
                         - fn2
                         + function(x - dx));
    const value_type c2((  function(x + dx2)
                         - fn2
                         + function(x - dx2)) / 4U);
    const value_type c3((  function(x + dx3)
                         - fn2
                         + function(x - dx3)) / 9U);

    return ((((c1 * 54U) - (c2 * 9U)) - (c3 * 2U)) / (dx * dx)) / 43U;
  }

#endif // _DERIVATIVE_2012_01_09_H_
