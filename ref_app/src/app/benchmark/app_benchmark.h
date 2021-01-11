///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2021.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef APP_BENCHMARK_2018_10_02_H_
  #define APP_BENCHMARK_2018_10_02_H_

  #define APP_BENCHMARK_TYPE_NONE                  0
  #define APP_BENCHMARK_TYPE_COMPLEX               1
  #define APP_BENCHMARK_TYPE_CRC                   2
  #define APP_BENCHMARK_TYPE_FAST_MATH             3
  #define APP_BENCHMARK_TYPE_FILTER                4
  #define APP_BENCHMARK_TYPE_FIXED_POINT           5
  #define APP_BENCHMARK_TYPE_FLOAT                 6
  #define APP_BENCHMARK_TYPE_WIDE_INTEGER          7
  #define APP_BENCHMARK_TYPE_PI_SPIGOT             8
  #define APP_BENCHMARK_TYPE_PI_SPIGOT_SINGLE      9
  #define APP_BENCHMARK_TYPE_HASH                 10
  #define APP_BENCHMARK_TYPE_WIDE_DECIMAL         11
  #define APP_BENCHMARK_TYPE_TRAPEZOID_INTEGRAL   12
  #define APP_BENCHMARK_TYPE_PI_AGM               13

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

  #if !defined(APP_BENCHMARK_TYPE)
  #define APP_BENCHMARK_TYPE   APP_BENCHMARK_TYPE_NONE
  #endif

  namespace app { namespace benchmark {

  #if  (APP_BENCHMARK_TYPE == APP_BENCHMARK_TYPE_NONE)
  // none
  bool run_none();
  #elif(APP_BENCHMARK_TYPE == APP_BENCHMARK_TYPE_COMPLEX)
  bool run_complex();
  #elif(APP_BENCHMARK_TYPE == APP_BENCHMARK_TYPE_CRC)
  bool run_crc();
  #elif(APP_BENCHMARK_TYPE == APP_BENCHMARK_TYPE_FAST_MATH)
  bool run_fast_math();
  #elif(APP_BENCHMARK_TYPE == APP_BENCHMARK_TYPE_FILTER)
  bool run_filter();
  #elif(APP_BENCHMARK_TYPE == APP_BENCHMARK_TYPE_FIXED_POINT)
  bool run_fixed_point();
  #elif(APP_BENCHMARK_TYPE == APP_BENCHMARK_TYPE_FLOAT)
  bool run_float();
  #elif(APP_BENCHMARK_TYPE == APP_BENCHMARK_TYPE_WIDE_INTEGER)
  bool run_wide_integer();
  #elif(APP_BENCHMARK_TYPE == APP_BENCHMARK_TYPE_PI_SPIGOT)
  bool run_pi_spigot();
  #elif(APP_BENCHMARK_TYPE == APP_BENCHMARK_TYPE_PI_SPIGOT_SINGLE)
  bool run_pi_spigot_single();
  #elif(APP_BENCHMARK_TYPE == APP_BENCHMARK_TYPE_HASH)
  bool run_hash();
  #elif(APP_BENCHMARK_TYPE == APP_BENCHMARK_TYPE_WIDE_DECIMAL)
  bool run_wide_decimal();
  #elif(APP_BENCHMARK_TYPE == APP_BENCHMARK_TYPE_TRAPEZOID_INTEGRAL)
  bool run_trapezoid_integral();
  #elif(APP_BENCHMARK_TYPE == APP_BENCHMARK_TYPE_PI_AGM)
  bool run_pi_agm();
  #endif

  } } // namespace app:::benchmark

#endif // APP_BENCHMARK_2018_10_02_H_
