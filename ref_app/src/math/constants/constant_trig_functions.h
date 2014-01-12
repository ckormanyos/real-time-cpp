///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2013 - 2014.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef _CONSTANT_TRIG_FUNCTIONS_2013_01_02_H_
  #define _CONSTANT_TRIG_FUNCTIONS_2013_01_02_H_

  #include <cstdint>
  #include <cstdfloat>
  #include "constants.h"

  namespace math
  {
    namespace constants
    {
      template<typename T>
      constexpr T sin(T x)
      {
        // Scale x to CONST_UNIQUE_CHI (+-pi/2 to +-1).
        #define CONST_UNIQUE_CHI_S T(x / pi_half<T>())

        // Take the absolute value of CONST_UNIQUE_CHI.
        #define CONST_UNIQUE_IS_NEG bool(CONST_UNIQUE_CHI_S < T(0))
        #define CONST_UNIQUE_CHI_A  T(CONST_UNIQUE_IS_NEG ? -CONST_UNIQUE_CHI_S : CONST_UNIQUE_CHI_S)

        // Do the argument reduction.
        #define CONST_UNIQUE_NPI2 std::uint32_t(CONST_UNIQUE_CHI_A / 2)
        #define CONST_UNIQUE_NPI  std::uint32_t(                             \
                      (CONST_UNIQUE_CHI_A - (CONST_UNIQUE_NPI2 * 2) > T(1))  \
                        ? CONST_UNIQUE_NPI2 + 1                              \
                        : CONST_UNIQUE_NPI2)

        #define CONST_UNIQUE_CHI  T(CONST_UNIQUE_CHI_A - T(CONST_UNIQUE_NPI * 2))
        #define CONST_UNIQUE_CHI2 T(CONST_UNIQUE_CHI * CONST_UNIQUE_CHI)

        // Perform the polynomial expansion. See the Mathematica(R) code
        // below for details on generating the polynomial coefficients.
        #define CONST_UNIQUE_SUM                                                                \
                       ((((((((( - static_cast<T>(FLOATMAX_C(4.2468171354841523379493663E-14))  \
             * CONST_UNIQUE_CHI2 + static_cast<T>(FLOATMAX_C(6.0640855645940930588123490E-12))) \
             * CONST_UNIQUE_CHI2 - static_cast<T>(FLOATMAX_C(6.6880001786329819459555395E-10))) \
             * CONST_UNIQUE_CHI2 + static_cast<T>(FLOATMAX_C(5.6921726597221657560994942E-08))) \
             * CONST_UNIQUE_CHI2 - static_cast<T>(FLOATMAX_C(3.5988432339708525153771884E-06))) \
             * CONST_UNIQUE_CHI2 + static_cast<T>(FLOATMAX_C(1.6044118478699232812460184E-04))) \
             * CONST_UNIQUE_CHI2 - static_cast<T>(FLOATMAX_C(4.6817541353186228516958362E-03))) \
             * CONST_UNIQUE_CHI2 + static_cast<T>(FLOATMAX_C(7.9692626246167038770053004E-02))) \
             * CONST_UNIQUE_CHI2 - static_cast<T>(FLOATMAX_C(6.4596409750624625337325359E-01))) \
             * CONST_UNIQUE_CHI2 + static_cast<T>(FLOATMAX_C(1.5707963267948966192276341E+00))) \
             * CONST_UNIQUE_CHI

        // Reflect the result if necessary.
        #define CONST_UNIQUE_NEEDS_REFLECT bool((CONST_UNIQUE_NPI % 2) != 0)

        return ((CONST_UNIQUE_NEEDS_REFLECT == CONST_UNIQUE_IS_NEG)
                 ?  (CONST_UNIQUE_SUM)
                 : -(CONST_UNIQUE_SUM));

        #undef CONST_UNIQUE_CHI_S
        #undef CONST_UNIQUE_IS_NEG
        #undef CONST_UNIQUE_NPI2
        #undef CONST_UNIQUE_NPI
        #undef CONST_UNIQUE_CHI
        #undef CONST_UNIQUE_CHI2
        #undef CONST_UNIQUE_SUM
        #undef CONST_UNIQUE_NEEDS_REFLECT
      }

      template<typename T>
      constexpr T cos(T x)
      {
        return -sin<T>(x - pi_half<T>());
      }

      template<typename T>
      constexpr T tan(T x)
      {
        return sin<T>(x) / cos<T>(x);
      }
    }
  }

/*
Table[{x, Sin[x Pi/2]}, {x, -1, 1, 1/120}]

N[%, 64]

Fit[%, {x, x^3, x^5, x^7, x^9, x^11, x^13, x^15, x^17, x^19, x^21, x^23, x^25, x^27, x^29, x^31, x^33, x^35}, x]

+ 1.570796326794896619231321691639751442098584699187310251698132565947755715874 x
- 0.6459640975062462536557565638979457333796933947507295603478558397604403709 x^3
+ 0.07969262624616704512050554949047802252090348618260694026669353093091830 x^5
- 0.0046817541353186881006854639339534378592278674444405145311428729474133 x^7
+ 0.000160441184787359821872660870163473324694584030095137832078043936305 x^9
- 3.59884323521208534045854001820832950160202164273290740585710688*10^-6 x^11
+ 5.69217292196792681177525530354327480905453975421415582837703*10^-8 x^13
- 6.68803510981146723247822630728280092198142530760947834435*10^-10 x^15
+ 6.066935731106195667101433450952857147312343457306385617*10^-12 x^17
- 4.377065467313742277180343695616457169350561338155389*10^-14 x^19
+ 2.5714228928604738651946371816806764338849498189806*10^-16 x^21
- 1.25389954053545748642485561647413471239575711505*10^-18 x^23
+ 5.15645517658002772440440204871671019235838611*10^-21 x^25
- 1.812399312821471012227718687983339251151045*10^-23 x^27
+ 5.507285764575258903815270075397852665189*10^-26 x^29
- 1.4611474454146482327655058465577124173*10^-28 x^31
+ 3.41355654163618725285729366189197196*10^-31 x^33
- 6.960126571061682906052555861870486*10^-34 x^35
*/

#endif // _CONSTANT_TRIG_FUNCTIONS_2013_01_02_H_
