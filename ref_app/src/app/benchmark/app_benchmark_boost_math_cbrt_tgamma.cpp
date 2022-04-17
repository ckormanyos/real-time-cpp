///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2021 - 2022.
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
#define BOOST_MATH_MAX_SERIES_ITERATION_POLICY 1000U
#endif

#if !defined(BOOST_MATH_DISABLE_ERROR_HANDLING)
#define BOOST_MATH_DISABLE_ERROR_HANDLING
#endif

#define BOOST_MATH_PROMOTE_FLOAT_POLICY false

#include <boost/cstdfloat.hpp>
#include <boost/math/constants/constants.hpp>
#include <boost/math/special_functions/cbrt.hpp>
#if defined(APP_BENCHMARK_TYPE_BOOST_MATH_CBRT_TGAMMA_EXCLUDES_TGAMMA)
#else
#include <boost/math/special_functions/gamma.hpp>
#endif

using my_float_type = boost::float64_t;

extern my_float_type cb;
extern my_float_type x;

auto app::benchmark::run_boost_math_cbrt_tgamma() -> bool
{
  static_assert(std::numeric_limits<my_float_type>::digits >= 53,
                "Error: Incorrect float64_t type definition");

  #if defined(APP_BENCHMARK_TYPE_BOOST_MATH_CBRT_TGAMMA_EXCLUDES_TGAMMA)
  // Table[N[((456 n)/(100 Pi))^(1/3), 36], {n, 1, 101, 10}]

  constexpr std::array<my_float_type, 11U> app_benchmark_control =
  {{
    my_float_type(BOOST_FLOATMAX_C(1.13223955591538834215180569196551578)),
    my_float_type(BOOST_FLOATMAX_C(2.51807823011086695042373251863402592)),
    my_float_type(BOOST_FLOATMAX_C(3.12376308426998860513729941565095654)),
    my_float_type(BOOST_FLOATMAX_C(3.55679543482482372869766829470888416)),
    my_float_type(BOOST_FLOATMAX_C(3.90420795695072854282866828867270250)),
    my_float_type(BOOST_FLOATMAX_C(4.19883087509735642352123538073247751)),
    my_float_type(BOOST_FLOATMAX_C(4.45705782245778172910333795189080075)),
    my_float_type(BOOST_FLOATMAX_C(4.68839764973308916541237692184508925)),
    my_float_type(BOOST_FLOATMAX_C(4.89891603901205916940792293385924057)),
    my_float_type(BOOST_FLOATMAX_C(5.09274722453205566419335519685355370)),
    my_float_type(BOOST_FLOATMAX_C(5.27285037700955609422383709083151200))
  }};
  #else
  // Table[N[Gamma[((456 n)/(100 Pi))^(1/3)], 21], {n, 1, 101, 10}]

  constexpr std::array<my_float_type, 11U> app_benchmark_control =
  {{
    my_float_type(BOOST_FLOATMAX_C(0.939131814550229181011151980662907952)),
    my_float_type(BOOST_FLOATMAX_C(1.34645417009670049450881257836426513)),
    my_float_type(BOOST_FLOATMAX_C(2.24865197861464813284549389915695163)),
    my_float_type(BOOST_FLOATMAX_C(3.54010862139328036868593771662409929)),
    my_float_type(BOOST_FLOATMAX_C(5.32678290474027222700118887035805285)),
    my_float_type(BOOST_FLOATMAX_C(7.74480814145513084404751762515242577)),
    my_float_type(BOOST_FLOATMAX_C(10.9608033153333194319415514453787809)),
    my_float_type(BOOST_FLOATMAX_C(15.1764307769968425576636827673821899)),
    my_float_type(BOOST_FLOATMAX_C(20.6341757772658373762859051310361056)),
    my_float_type(BOOST_FLOATMAX_C(27.6240717359003789929215625751284983)),
    my_float_type(BOOST_FLOATMAX_C(36.4914014381246411895171472115548616))
  }};
  #endif

  static unsigned app_benchmark_n_index      = 0U;
  static unsigned app_benchmark_n_value      = 1U;
  static bool     app_benchmark_result_is_ok = true;

  #if defined(APP_BENCHMARK_TYPE_BOOST_MATH_CBRT_TGAMMA_EXCLUDES_TGAMMA)
  cb = boost::math::cbrt(x * my_float_type(app_benchmark_n_value));
  #else
  cb = boost::math::tgamma(boost::math::cbrt(x * my_float_type(app_benchmark_n_value)));
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
    result_is_ok &= app::benchmark::run_boost_math_cbrt_tgamma();
  }

  return result_is_ok ? 0 : -1;
}

#endif

my_float_type cb;
my_float_type x = my_float_type(BOOST_FLOATMAX_C(4.56)) / boost::math::constants::pi<my_float_type>();

#endif // APP_BENCHMARK_TYPE_BOOST_MATH_CBRT_TGAMMA
