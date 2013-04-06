#ifndef _CONST_TRIG_2013_01_02_H_
  #define _CONST_TRIG_2013_01_02_H_

  #include <cstdint>
  #include "constants.h"

  template<typename T>
  constexpr T const_sin(T x)
  {
    // Scale x to CONST_UNIQUE_CHI (+-pi/2 to +-1).
    #define CONST_UNIQUE_CHI_S T(x / const_pi_half<T>())

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

    // Do the order-19 polynomial expansion.
    #define CONST_UNIQUE_SUM                                       \
                   ((((((((( - T(4.2468171354841523379493663E-14)  \
         * CONST_UNIQUE_CHI2 + T(6.0640855645940930588123490E-12)) \
         * CONST_UNIQUE_CHI2 - T(6.6880001786329819459555395E-10)) \
         * CONST_UNIQUE_CHI2 + T(5.6921726597221657560994942E-08)) \
         * CONST_UNIQUE_CHI2 - T(3.5988432339708525153771884E-06)) \
         * CONST_UNIQUE_CHI2 + T(1.6044118478699232812460184E-04)) \
         * CONST_UNIQUE_CHI2 - T(4.6817541353186228516958362E-03)) \
         * CONST_UNIQUE_CHI2 + T(7.9692626246167038770053004E-02)) \
         * CONST_UNIQUE_CHI2 - T(6.4596409750624625337325359E-01)) \
         * CONST_UNIQUE_CHI2 + T(1.5707963267948966192276341E+00)) \
         * CONST_UNIQUE_CHI

    // Reflect the result if necessary.
    #define CONST_UNIQUE_NEEDS_REFLECT bool((CONST_UNIQUE_NPI % 2) != 0)

    return ((CONST_UNIQUE_NEEDS_REFLECT == CONST_UNIQUE_IS_NEG)
             ?  CONST_UNIQUE_SUM
             : -CONST_UNIQUE_SUM);

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
  constexpr T const_cos(T x)
  {
    return -const_sin<T>(x - const_pi_half<T>());
  }

  template<typename T>
  constexpr T const_tan(T x)
  {
    return const_sin<T>(x) / const_cos<T>(x);
  }

#endif // _CONST_TRIG_2013_01_02_H_
