///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2021.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <array>
#include <cstdint>

#include <app/benchmark/app_benchmark.h>
#include <app/benchmark/app_benchmark_detail.h>

#if(APP_BENCHMARK_TYPE == APP_BENCHMARK_TYPE_BOOST_MATH_CBRT_TGAMMA)

//#define APP_BENCHMARK_TYPE_BOOST_MATH_CBRT_TGAMMA_EXCLUDES_TGAMMA

//TGT_INCLUDES  = -I$(PATH_APP)/util/STL                                            \
//                -I$(PATH_APP)/util/boost_metal_bindings                           \
//                -IC:/boost/boost_1_77_0


#if !defined(BOOST_MATH_STANDALONE)
#define BOOST_MATH_STANDALONE
#endif

#if !defined(BOOST_NO_RTTI)
#define BOOST_NO_RTTI
#endif

#if !defined(BOOST_DISABLE_THREADS)
#define BOOST_DISABLE_THREADS
#endif

#if !defined(BOOST_NO_EXCEPTIONS)
#define BOOST_NO_EXCEPTIONS
#endif

#if !defined(BOOST_MATH_MAX_SERIES_ITERATION_POLICY)
#define BOOST_MATH_MAX_SERIES_ITERATION_POLICY 10000U
#endif

#if !defined(BOOST_MATH_DISABLE_ERROR_HANDLING)
#define BOOST_MATH_DISABLE_ERROR_HANDLING
#endif

#define BOOST_MATH_PROMOTE_FLOAT_POLICY false

#include <boost/math/constants/constants.hpp>
#include <boost/math/special_functions/cbrt.hpp>
#if defined(APP_BENCHMARK_TYPE_BOOST_MATH_CBRT_TGAMMA_EXCLUDES_TGAMMA)
#else
#include <boost/math/special_functions/gamma.hpp>
#endif

extern float cb;
extern float x;

bool app::benchmark::run_boost_math_cbrt()
{
  #if defined(APP_BENCHMARK_TYPE_BOOST_MATH_CBRT_TGAMMA_EXCLUDES_TGAMMA)
  // Table[N[((456 n)/(100 Pi))^(1/3), 21], {n, 1, 101, 10}]

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
  #else
  // Table[N[Gamma[((456 n)/(100 Pi))^(1/3)], 21], {n, 1, 101, 10}]

  constexpr std::array<float, 11U> app_benchmark_control =
  {{
     0.939131814550229181011F,
     1.34645417009670049451F,
     2.24865197861464813285F,
     3.54010862139328036869F,
     5.32678290474027222700F,
     7.74480814145513084405F,
    10.9608033153333194319F,
    15.1764307769968425577F,
    20.6341757772658373763F,
    27.6240717359003789929F,
    36.4914014381246411895F
  }};
  #endif

  static unsigned app_benchmark_n_index      = 0U;
  static unsigned app_benchmark_n_value      = 1U;
  static bool     app_benchmark_result_is_ok = true;

  #if defined(APP_BENCHMARK_TYPE_BOOST_MATH_CBRT_TGAMMA_EXCLUDES_TGAMMA)
  cb = boost::math::cbrt(x * float(app_benchmark_n_value));
  #else
  cb = boost::math::tgamma(boost::math::cbrt(x * float(app_benchmark_n_value)));
  #endif

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
  // g++ -Wall -O3 -march=native -I./ref_app/src/mcal/host -I./ref_app/src -DAPP_BENCHMARK_TYPE=APP_BENCHMARK_TYPE_BOOST_MATH_CBRT_TGAMMA -DAPP_BENCHMARK_STANDALONE_MAIN ./ref_app/src/app/benchmark/app_benchmark_boost_math_cbrt_tgamma.cpp -o ./ref_app/bin/app_benchmark_boost_math_cbrt_tgamma.exe

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

#endif // APP_BENCHMARK_TYPE_BOOST_MATH_CBRT_TGAMMA
