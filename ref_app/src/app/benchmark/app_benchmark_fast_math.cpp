///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2018 - 2019.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//


#include <app/benchmark/app_benchmark.h>

#if(APP_BENCHMARK_TYPE == APP_BENCHMARK_TYPE_FAST_MATH)

#define FAST_MATH_IMPLEMENT_SPECIALIZED_SQRT

#include <app/benchmark/app_benchmark_detail.h>
#include <math/fast_math/fast_math.h>

using float_type = fast_math::float32_t;

extern float_type xx;
extern float_type yy;

bool app::benchmark::run_fast_math()
{
  static bool toggle_test_case;

  bool result_is_ok;

  if(toggle_test_case != true)
  {
    toggle_test_case = true;

    yy = fast_math::exp(xx);

    result_is_ok = detail::is_close_fraction(yy, 10.381236562731844796F, 1.0E-03F);
  }
  else
  {
    toggle_test_case = false;

    yy = fast_math::sqrt(xx);

    result_is_ok = detail::is_close_fraction(yy, 1.5297058540778354490F, 2.0E-03F);
  }

  return result_is_ok;
}

#if defined(APP_BENCHMARK_STANDALONE_MAIN)
int main()
{
  // g++ -Wall -O3 -march=native -I./ref_app/src/mcal/host -I./ref_app/src -DAPP_BENCHMARK_TYPE=APP_BENCHMARK_TYPE_FAST_MATH -DAPP_BENCHMARK_STANDALONE_MAIN ./ref_app/src/app/benchmark/app_benchmark_fast_math.cpp -o ./ref_app/bin/app_benchmark_fast_math.exe

  bool result_is_ok = true;

  for(unsigned i = 0U; i < 64U; ++i)
  {
    result_is_ok &= app::benchmark::run_fast_math();
  }

  return result_is_ok ? 0 : -1;
}
#endif

float_type xx = 2.34F;
float_type yy;

#endif // APP_BENCHMARK_TYPE_FAST_MATH
