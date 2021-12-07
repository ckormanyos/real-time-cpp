///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2021.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <app/benchmark/app_benchmark.h>
#include <app/benchmark/app_benchmark_detail.h>

#if(APP_BENCHMARK_TYPE == APP_BENCHMARK_TYPE_BOOST_MULTIPRECISION_SQRT)

//#define APP_BENCHMARK_TYPE_BOOST_BOOST_MULTIPRECISION_SQRT_USE_BIN_FLOAT

//TGT_INCLUDES  = -IC:/boost/boost_multiprecision_standalone/include                \
//                -IC:/boost/modular_boost/boost/libs/math/include                  \
//                -IC:/boost/modular_boost/boost/libs/config/include

//C:/boost/boost_multiprecision_standalone/include;C:/boost/modular_boost/boost/libs/math/include;C:/boost/modular_boost/boost/libs/config/include;

#if !defined(BOOST_MP_STANDALONE)
#define BOOST_MP_STANDALONE
#endif

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

#if !defined(BOOST_MATH_DISABLE_ERROR_HANDLING)
#define BOOST_MATH_DISABLE_ERROR_HANDLING
#endif

#if !defined(BOOST_NO_CXX11_THREAD_LOCAL)
#define BOOST_NO_CXX11_THREAD_LOCAL
#endif

#include <boost/config.hpp>
#if defined(APP_BENCHMARK_TYPE_BOOST_BOOST_MULTIPRECISION_SQRT_USE_BIN_FLOAT)
#include <boost/multiprecision/cpp_bin_float.hpp>
#else
#include <boost/multiprecision/cpp_dec_float.hpp>
#endif

namespace local
{
  using big_float_type =
  #if defined(APP_BENCHMARK_TYPE_BOOST_BOOST_MULTIPRECISION_SQRT_USE_BIN_FLOAT)
    boost::multiprecision::number<boost::multiprecision::cpp_bin_float<101>,
                                  boost::multiprecision::et_off>;
  #else
    boost::multiprecision::number<boost::multiprecision::cpp_dec_float<101, std::int32_t, void>,
                                  boost::multiprecision::et_off>;
  #endif
}

bool app::benchmark::run_boost_multiprecision_sqrt()
{
  using local::big_float_type;

  // N[Sqrt[3001/3], 111]
  // 31.6280466253186956650730523324944190761410921737176918710172729131615977753452108050362516806270353838640956123
  static const big_float_type
    control
    (
      "31.6280466253186956650730523324944190761410921737176918710172729131615977753452108050362516806270353838640956123"
    );

  using std::sqrt;

  // Compute a square root.
  const big_float_type big_float_arg    = big_float_type(3001) / 3;
  const big_float_type big_float_result = sqrt(big_float_arg);

  // Compare the calculated result with the known control value.
  const bool app_benchmark_result_is_ok = detail::is_close_fraction(big_float_result, control);

  return app_benchmark_result_is_ok;
}

#if defined(APP_BENCHMARK_STANDALONE_MAIN)
int main()
{
  // g++ -Wall -O3 -march=native -I./ref_app/src/mcal/host -I./ref_app/src -DAPP_BENCHMARK_TYPE=APP_BENCHMARK_TYPE_BOOST_MULTIPRECISION_SQRT -DAPP_BENCHMARK_STANDALONE_MAIN ./ref_app/src/app/benchmark/app_benchmark_boost_math_cbrt_tgamma.cpp -o ./ref_app/bin/app_benchmark_boost_multiprecision_sqrt.exe

  bool result_is_ok = true;

  for(unsigned i = 0U; i < 64U; ++i)
  {
    result_is_ok &= app::benchmark::run_boost_multiprecision_sqrt();
  }

  return (result_is_ok ? 0 : -1);
}

#endif

#endif // APP_BENCHMARK_TYPE_BOOST_MULTIPRECISION_SQRT
