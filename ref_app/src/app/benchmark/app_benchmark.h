///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2019.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef APP_BENCHMARK_2018_10_02_H_
  #define APP_BENCHMARK_2018_10_02_H_

  #define APP_BENCHMARK_TYPE_NONE                0
  #define APP_BENCHMARK_TYPE_COMPLEX             1
  #define APP_BENCHMARK_TYPE_CRC                 2
  #define APP_BENCHMARK_TYPE_FAST_MATH           3
  #define APP_BENCHMARK_TYPE_FILTER              4
  #define APP_BENCHMARK_TYPE_FIXED_POINT         5
  #define APP_BENCHMARK_TYPE_FLOAT               6
  #define APP_BENCHMARK_TYPE_WIDE_INTEGER        7
  #define APP_BENCHMARK_TYPE_PI_SPIGOT           8

  #define APP_BENCHMARK_TYPE   APP_BENCHMARK_TYPE_NONE
  //#define APP_BENCHMARK_TYPE   APP_BENCHMARK_TYPE_COMPLEX
  //#define APP_BENCHMARK_TYPE   APP_BENCHMARK_TYPE_CRC
  //#define APP_BENCHMARK_TYPE   APP_BENCHMARK_TYPE_FAST_MATH
  //#define APP_BENCHMARK_TYPE   APP_BENCHMARK_TYPE_FILTER
  //#define APP_BENCHMARK_TYPE   APP_BENCHMARK_TYPE_FIXED_POINT
  //#define APP_BENCHMARK_TYPE   APP_BENCHMARK_TYPE_FLOAT
  //#define APP_BENCHMARK_TYPE   APP_BENCHMARK_TYPE_WIDE_INTEGER
  //#define APP_BENCHMARK_TYPE   APP_BENCHMARK_TYPE_PI_SPIGOT

  namespace app { namespace benchmark {

  #if  (APP_BENCHMARK_TYPE == APP_BENCHMARK_TYPE_NONE)
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
  #endif

  } } // namespace app:::benchmark

#endif // APP_BENCHMARK_2018_10_02_H_
