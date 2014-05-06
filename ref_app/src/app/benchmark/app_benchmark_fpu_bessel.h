
///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2014.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef _APP_BENCHMARK_FPU_BESSEL_2014_04_30_H_
  #define _APP_BENCHMARK_FPU_BESSEL_2014_04_30_H_

  #include <cmath>
  #if defined(__GNUC__) || (defined(_WIN32) && (_MSC_VER <= 1700))
    #include <cstdfloat>
    namespace std { std::float32_t tgamma(std::float32_t); }
  #endif
  #include <app/benchmark/app_benchmark_fpu_hypergeometric.h>

  namespace app
  {
    namespace benchmark
    {
      template<typename T>
      T cyl_bessel_j(T v, T x)
      {
        // Compute the Taylor series representation of cyl_bessel_j.
        // There are no checks on input range or parameter boundaries.

        const T x_half     = x / 2;
        const T v_plus_one = v + 1;

        const T hypergeometric_0f1_term = app::benchmark::hypergeometric_0f1(v_plus_one, -(x_half * x_half));

        using std::pow;
        using std::tgamma;

        return (pow(x_half, v) * hypergeometric_0f1_term) / tgamma(v_plus_one);
      }
    }
  } // namespace app::benchmark

#endif // _APP_BENCHMARK_FPU_BESSEL_2014_04_30_H_
