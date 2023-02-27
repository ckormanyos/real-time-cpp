///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2023.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef APP_BENCHMARK_2018_10_02_H_
  #define APP_BENCHMARK_2018_10_02_H_

  #define APP_BENCHMARK_TYPE_NONE                                0
  #define APP_BENCHMARK_TYPE_COMPLEX                             1
  #define APP_BENCHMARK_TYPE_CRC                                 2
  #define APP_BENCHMARK_TYPE_FAST_MATH                           3
  #define APP_BENCHMARK_TYPE_FILTER                              4
  #define APP_BENCHMARK_TYPE_FIXED_POINT                         5
  #define APP_BENCHMARK_TYPE_FLOAT                               6
  #define APP_BENCHMARK_TYPE_WIDE_INTEGER                        7
  #define APP_BENCHMARK_TYPE_PI_SPIGOT                           8
  #define APP_BENCHMARK_TYPE_PI_SPIGOT_SINGLE                    9
  #define APP_BENCHMARK_TYPE_HASH                               10
  #define APP_BENCHMARK_TYPE_WIDE_DECIMAL                       11
  #define APP_BENCHMARK_TYPE_TRAPEZOID_INTEGRAL                 12
  #define APP_BENCHMARK_TYPE_PI_AGM                             13
  #define APP_BENCHMARK_TYPE_BOOST_MATH_CBRT_TGAMMA             14
  #define APP_BENCHMARK_TYPE_CNL_SCALED_INTEGER                 15
  #define APP_BENCHMARK_TYPE_SOFT_DOUBLE_H2F1                   16
  #define APP_BENCHMARK_TYPE_BOOST_MULTIPRECISION_CBRT          17
  #define APP_BENCHMARK_TYPE_BOOST_MATH_CYL_BESSEL_J            18
  #define APP_BENCHMARK_TYPE_HASH_SHA256                        19

  //#define APP_BENCHMARK_TYPE   APP_BENCHMARK_TYPE_NONE
  //#define APP_BENCHMARK_TYPE   APP_BENCHMARK_TYPE_COMPLEX
  //#define APP_BENCHMARK_TYPE   APP_BENCHMARK_TYPE_CRC
  //#define APP_BENCHMARK_TYPE   APP_BENCHMARK_TYPE_FAST_MATH
  //#define APP_BENCHMARK_TYPE   APP_BENCHMARK_TYPE_FILTER
  //#define APP_BENCHMARK_TYPE   APP_BENCHMARK_TYPE_FIXED_POINT
  //#define APP_BENCHMARK_TYPE   APP_BENCHMARK_TYPE_FLOAT
  //#define APP_BENCHMARK_TYPE   APP_BENCHMARK_TYPE_WIDE_INTEGER
  //#define APP_BENCHMARK_TYPE   APP_BENCHMARK_TYPE_PI_SPIGOT
  //#define APP_BENCHMARK_TYPE   APP_BENCHMARK_TYPE_PI_SPIGOT_SINGLE
  //#define APP_BENCHMARK_TYPE   APP_BENCHMARK_TYPE_HASH
  //#define APP_BENCHMARK_TYPE   APP_BENCHMARK_TYPE_WIDE_DECIMAL
  //#define APP_BENCHMARK_TYPE   APP_BENCHMARK_TYPE_TRAPEZOID_INTEGRAL
  //#define APP_BENCHMARK_TYPE   APP_BENCHMARK_TYPE_PI_AGM
  //#define APP_BENCHMARK_TYPE   APP_BENCHMARK_TYPE_BOOST_MATH_CBRT_TGAMMA
  //#define APP_BENCHMARK_TYPE   APP_BENCHMARK_TYPE_CNL_SCALED_INTEGER
  //#define APP_BENCHMARK_TYPE   APP_BENCHMARK_TYPE_SOFT_DOUBLE_H2F1
  //#define APP_BENCHMARK_TYPE   APP_BENCHMARK_TYPE_BOOST_MULTIPRECISION_CBRT
  //#define APP_BENCHMARK_TYPE   APP_BENCHMARK_TYPE_BOOST_MATH_CYL_BESSEL_J
  //#define APP_BENCHMARK_TYPE   APP_BENCHMARK_TYPE_HASH_SHA256

  #if !defined(APP_BENCHMARK_TYPE)
  #define APP_BENCHMARK_TYPE   APP_BENCHMARK_TYPE_NONE
  #endif

  namespace app { namespace benchmark {

  #if  (APP_BENCHMARK_TYPE == APP_BENCHMARK_TYPE_NONE)
  auto run_none() -> bool;
  #elif(APP_BENCHMARK_TYPE == APP_BENCHMARK_TYPE_COMPLEX)
  auto run_complex() -> bool;
  #elif(APP_BENCHMARK_TYPE == APP_BENCHMARK_TYPE_CRC)
  auto run_crc() -> bool;
  #elif(APP_BENCHMARK_TYPE == APP_BENCHMARK_TYPE_FAST_MATH)
  auto run_fast_math() -> bool;
  #elif(APP_BENCHMARK_TYPE == APP_BENCHMARK_TYPE_FILTER)
  auto run_filter() -> bool;
  #elif(APP_BENCHMARK_TYPE == APP_BENCHMARK_TYPE_FIXED_POINT)
  auto run_fixed_point() -> bool;
  #elif(APP_BENCHMARK_TYPE == APP_BENCHMARK_TYPE_FLOAT)
  auto run_float() -> bool;
  #elif(APP_BENCHMARK_TYPE == APP_BENCHMARK_TYPE_WIDE_INTEGER)
  auto run_wide_integer() -> bool;
  #elif(APP_BENCHMARK_TYPE == APP_BENCHMARK_TYPE_PI_SPIGOT)
  auto run_pi_spigot() -> bool;
  #elif(APP_BENCHMARK_TYPE == APP_BENCHMARK_TYPE_PI_SPIGOT_SINGLE)
  auto run_pi_spigot_single() -> bool;
  #elif(APP_BENCHMARK_TYPE == APP_BENCHMARK_TYPE_HASH)
  auto run_hash() -> bool;
  #elif(APP_BENCHMARK_TYPE == APP_BENCHMARK_TYPE_WIDE_DECIMAL)
  auto run_wide_decimal() -> bool;
  #elif(APP_BENCHMARK_TYPE == APP_BENCHMARK_TYPE_TRAPEZOID_INTEGRAL)
  auto run_trapezoid_integral() -> bool;
  #elif(APP_BENCHMARK_TYPE == APP_BENCHMARK_TYPE_PI_AGM)
  auto run_pi_agm() -> bool;
  #elif(APP_BENCHMARK_TYPE == APP_BENCHMARK_TYPE_BOOST_MATH_CBRT_TGAMMA)
  auto run_boost_math_cbrt_tgamma() -> bool;
  #elif(APP_BENCHMARK_TYPE == APP_BENCHMARK_TYPE_CNL_SCALED_INTEGER)
  auto run_cnl_scaled_integer() -> bool;
  #elif(APP_BENCHMARK_TYPE == APP_BENCHMARK_TYPE_SOFT_DOUBLE_H2F1)
  auto run_soft_double_h2f1() -> bool;
  #elif(APP_BENCHMARK_TYPE == APP_BENCHMARK_TYPE_BOOST_MULTIPRECISION_CBRT)
  auto run_boost_multiprecision_cbrt() -> bool;
  #elif(APP_BENCHMARK_TYPE == APP_BENCHMARK_TYPE_BOOST_MATH_CYL_BESSEL_J)
  auto run_boost_math_cbrt_cyl_bessel_j() -> bool;
  #elif(APP_BENCHMARK_TYPE == APP_BENCHMARK_TYPE_HASH_SHA256)
  auto run_hash_sha256() -> bool;
  #else
  #error APP_BENCHMARK_TYPE is undefined.
  #endif

  } } // namespace app:::benchmark

#endif // APP_BENCHMARK_2018_10_02_H_
