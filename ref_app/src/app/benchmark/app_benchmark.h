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

  #define APP_BENCHMARK_TYPE   APP_BENCHMARK_TYPE_NONE
  //#define APP_BENCHMARK_TYPE   APP_BENCHMARK_TYPE_COMPLEX
  //#define APP_BENCHMARK_TYPE   APP_BENCHMARK_TYPE_CRC
  //#define APP_BENCHMARK_TYPE   APP_BENCHMARK_TYPE_FAST_MATH
  //#define APP_BENCHMARK_TYPE   APP_BENCHMARK_TYPE_FILTER
  //#define APP_BENCHMARK_TYPE   APP_BENCHMARK_TYPE_FIXED_POINT
  //#define APP_BENCHMARK_TYPE   APP_BENCHMARK_TYPE_FLOAT
  //#define APP_BENCHMARK_TYPE   APP_BENCHMARK_TYPE_WIDE_INTEGER

  namespace app { namespace benchmark {

  bool run_complex     ();
  bool run_crc         ();
  bool run_fast_math   ();
  bool run_filter      ();
  bool run_fixed_point ();
  bool run_float       ();
  bool run_wide_integer();

  } } // namespace app:::benchmark

#endif // APP_BENCHMARK_2018_10_02_H_
