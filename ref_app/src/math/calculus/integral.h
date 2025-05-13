///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2025.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef INTEGRAL_2012_01_09_H
 #define INTEGRAL_2012_01_09_H

 #include <cmath>

 namespace math
 {
   // Compute the numerical integral of a real function from a to b
   // using a recursive trapezoid rule.

   template<typename real_value_type,
            typename real_function_type>
   real_value_type integral(const real_value_type& a,
                            const real_value_type& b,
                            const real_value_type& tol,
                            real_function_type real_function)
   {
     std::uint_fast32_t n2 { UINT8_C(1) };

     real_value_type step { (b - a) / 2U };

     real_value_type result { (real_function(a) + real_function(b)) * step };

     constexpr std::uint_fast8_t k_max { UINT8_C(32) };

     for(std::uint_fast8_t k = UINT8_C(0); k < k_max; ++k)
     {
       real_value_type sum { 0 };

       for(std::uint_fast32_t j { std::uint_fast32_t { UINT8_C(0) } }; j < n2; ++j)
       {
         const std::uint_fast32_t two_j_plus_one { (j * UINT32_C(2)) + UINT32_C(1) };

         sum += real_function(a + real_value_type(step * two_j_plus_one));
       }

       const real_value_type tmp { result };

       result = (result / 2U) + (step * sum);

       const real_value_type ratio { tmp / result };

       using std::fabs;

       const real_value_type delta = fabs(ratio - 1U);

       if((k > std::uint_fast8_t { UINT8_C(1) }) && (delta < tol))
       {
         break;
       }

       n2 *= 2U;

       step /= 2U;
     }

     return result;
   }
 }

#endif // INTEGRAL_2012_01_09_H
