///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2021.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <array>
#include <cstdint>

#if !defined(BOOST_MATH_STANDALONE)
#define BOOST_MATH_STANDALONE
#endif

#define BOOST_MATH_PROMOTE_FLOAT_POLICY false

#include <boost/math/special_functions/cbrt.hpp>
#include <boost/math/constants/constants.hpp>

#include <app/benchmark/app_benchmark.h>
#include <app/benchmark/app_benchmark_detail.h>

#if(APP_BENCHMARK_TYPE == APP_BENCHMARK_TYPE_BOOST_MATH_CBRT)


extern float cb;
extern float x;

bool app::benchmark::run_boost_math_cbrt()
{
  // Table[N[Gamma[((456 n)/(100 Pi))^(1/3)], 21], {n, 1, 101, 10}]

  constexpr std::array<float, 11U> app_benchmark_control =
  {{
    1.13223955591538834215F,
    2.51807823011086695042F,
    3.12376308426998860514F,
    3.55679543482482372870F,
    3.90420795695072854283F,
    4.19883087509735642352F,
    4.45705782245778172910F,
    4.68839764973308916541F,
    4.89891603901205916941F,
    5.09274722453205566419F,
    5.27285037700955609422F
  }};

  static unsigned app_benchmark_n_index      = 0U;
  static unsigned app_benchmark_n_value      = 1U;
  static bool     app_benchmark_result_is_ok = true;

  cb = boost::math::cbrt(x * float(app_benchmark_n_value));

  app_benchmark_result_is_ok &= detail::is_close_fraction(cb, app_benchmark_control[app_benchmark_n_index]);

  app_benchmark_n_value += 10U;

  ++app_benchmark_n_index;

  if(app_benchmark_n_index == app_benchmark_control.size())
  {
    app_benchmark_n_index = 0U;
    app_benchmark_n_value = 1U;
  }

  return app_benchmark_result_is_ok;
}

#if defined(APP_BENCHMARK_STANDALONE_MAIN)
int main()
{
  // g++ -Wall -O3 -march=native -I./ref_app/src/mcal/host -I./ref_app/src -DAPP_BENCHMARK_TYPE=APP_BENCHMARK_TYPE_BOOST_MATH_CBRT -DAPP_BENCHMARK_STANDALONE_MAIN ./ref_app/src/app/benchmark/app_benchmark_boost_math_cbrt.cpp -o ./ref_app/bin/app_benchmark_boost_math_cbrt.exe

  bool result_is_ok = true;

  for(unsigned i = 0U; i < 64U; ++i)
  {
    result_is_ok &= app::benchmark::run_boost_math_cbrt();
  }

  return result_is_ok ? 0 : -1;
}

#endif

float cb;
float x = 4.56F / boost::math::constants::pi<float>();

#endif // APP_BENCHMARK_TYPE_BOOST_MATH_CBRT
