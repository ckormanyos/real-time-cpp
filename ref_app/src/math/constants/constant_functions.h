///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2013 - 2020.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef CONSTANT_FUNCTIONS_2013_01_02_H_
  #define CONSTANT_FUNCTIONS_2013_01_02_H_

  #include <cstdfloat>
  #include <cstdint>
  #include <limits>

  #include <math/constants/constants.h>

  namespace math
  {
    namespace const_functions
    {
      template<typename T>
      inline constexpr T pow_imp(T val, std::int32_t n);

      template<typename T>
      inline constexpr T pow_imp2(T val, std::int32_t n)
      {
        return ((std::int32_t(n & INT32_C(1)) != INT32_C(1))
          ? (pow_imp(val, n / 2) * pow_imp(val, n / 2)) * val
          :  pow_imp(val, n / 2));
      }

      template<typename T>
      inline constexpr T pow_imp(T val, std::int32_t n)
      {
        return ((n == INT32_C(1)) ? val
                         : ((n == INT32_C(2)) ? val * val
                                     : ((n == INT32_C(3)) ? (val * val) * val : pow_imp2(val, n))));
      }

      template<typename T>
      inline constexpr T pow(T val, std::int32_t n)
      {
        return ((n < INT32_C(0)) ? 1 / pow_imp(val, -n)
                                 : ((n == INT32_C(0)) ? T(1) : pow_imp(val, n)));
      }

      template<typename T>
      inline constexpr T log2_order(T x)
      {
        return ((x <= 1) ? T(0) : 1 + log2_order(x / 2));
      }

      template<typename F1, typename F2>
      struct newton
      {
        static constexpr F1 f1 = {};
        static constexpr F2 f2 = {};

        template<typename T>
        static constexpr T eval_once(T x, T target)
        {
          return x - (f1(x, target) / f2(x));
        }

        template<typename T>
        static constexpr T eval_n(T x, T target, int n)
        {
          return ((n == 0) ? x
                           : ((n == 1) ? eval_once(x, target)
                                       : eval_once(eval_n(x, target, n - 1), target)));
        }

        template<typename T>
        static constexpr T eval(T x, T target)
        {
          return eval_n(x, target, log2_order(std::numeric_limits<T>::digits));
        }
      };

      template<typename F1, typename F2>
      constexpr F1 newton<F1, F2>::f1;

      template<typename F1, typename F2>
      constexpr F2 newton<F1, F2>::f2;

      template<typename T>
      struct sqrt_f1
      {
        inline constexpr T operator()(T x, T target)
        {
          return (x * x) - target;
        }
      };

      template<typename T>
      struct sqrt_f2
      {
        inline constexpr T operator()(T x)
        {
          return 2 * x;
        }
      };

      template<typename T>
      inline constexpr T sqrt_estimate(T x)
      {
        return pow(T(2), log2_order(x) / 2);
      }

      template<typename T>
      inline constexpr T sqrt(T x)
      {
        return newton<sqrt_f1<T>, sqrt_f2<T> >::eval(sqrt_estimate(x), x);
      }

      template<typename T>
      constexpr T sin(T x)
      {
        // Scale x to CONST_UNIQUE_CHI (+-pi/2 to +-1).
        #define CONST_UNIQUE_CHI_S T(x / constants::half_pi<T>())

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
        // Mathematica(R) code:
        //   Table[{x, Sin[x Pi/2]}, {x, -1, 1, 1/120}]
        //   N[%, 80]
        //   Fit[%, {x, x^3, x^5, x^7, x^9, x^11, x^13, x^15, x^17, x^19, x^21, x^23, x^25, x^27, x^29, x^31, x^33, x^35}, x]
        // ... and then manually edit the coefficients, etc.
        #define CONST_UNIQUE_SUM                                                                                \
            ((((((((((((((((( - static_cast<T>(FLOATMAX_C(6.960126571061682906052555861870486E-34))             \
          * CONST_UNIQUE_CHI2 + static_cast<T>(FLOATMAX_C(3.41355654163618725285729366189197196E-31)))          \
          * CONST_UNIQUE_CHI2 - static_cast<T>(FLOATMAX_C(1.4611474454146482327655058465577124173E-28)))        \
          * CONST_UNIQUE_CHI2 + static_cast<T>(FLOATMAX_C(5.507285764575258903815270075397852665189E-26)))      \
          * CONST_UNIQUE_CHI2 - static_cast<T>(FLOATMAX_C(1.812399312821471012227718687983339251151045E-23)))   \
          * CONST_UNIQUE_CHI2 + static_cast<T>(FLOATMAX_C(5.15645517658002772440440204871671019235838611E-21))) \
          * CONST_UNIQUE_CHI2 - static_cast<T>(FLOATMAX_C(1.25389954053545748642485561647413471239575712E-18))) \
          * CONST_UNIQUE_CHI2 + static_cast<T>(FLOATMAX_C(2.57142289286047386519463718168067643388494982E-16))) \
          * CONST_UNIQUE_CHI2 - static_cast<T>(FLOATMAX_C(4.37706546731374227718034369561645716935056134E-14))) \
          * CONST_UNIQUE_CHI2 + static_cast<T>(FLOATMAX_C(6.06693573110619566710143345095285714731234346E-12))) \
          * CONST_UNIQUE_CHI2 - static_cast<T>(FLOATMAX_C(6.68803510981146723247822630728280092198142531E-10))) \
          * CONST_UNIQUE_CHI2 + static_cast<T>(FLOATMAX_C(5.69217292196792681177525530354327480905453975E-08))) \
          * CONST_UNIQUE_CHI2 - static_cast<T>(FLOATMAX_C(3.59884323521208534045854001820832950160202164E-06))) \
          * CONST_UNIQUE_CHI2 + static_cast<T>(FLOATMAX_C(1.60441184787359821872660870163473324694584030E-04))) \
          * CONST_UNIQUE_CHI2 - static_cast<T>(FLOATMAX_C(4.68175413531868810068546393395343785922786744E-03))) \
          * CONST_UNIQUE_CHI2 + static_cast<T>(FLOATMAX_C(7.96926262461670451205055494904780225209034862E-02))) \
          * CONST_UNIQUE_CHI2 - static_cast<T>(FLOATMAX_C(6.45964097506246253655756563897945733379693395E-01))) \
          * CONST_UNIQUE_CHI2 + static_cast<T>(FLOATMAX_C(1.57079632679489661923132169163975144209858470E+00))) \
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
        return -sin<T>(x - constants::half_pi<T>());
      }

      template<typename T>
      constexpr T tan(T x)
      {
        return sin<T>(x) / cos<T>(x);
      }
    }
  }

#endif // CONSTANT_FUNCTIONS_2013_01_02_H_
