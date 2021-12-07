///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2021.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <app/benchmark/app_benchmark.h>
#include <app/benchmark/app_benchmark_detail.h>

#if(APP_BENCHMARK_TYPE == APP_BENCHMARK_TYPE_BOOST_MULTIPRECISION_CBRT)

//#define APP_BENCHMARK_TYPE_BOOST_BOOST_MULTIPRECISION_CBRT_USE_BIN_FLOAT

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
#include <boost/math/special_functions/cbrt.hpp>
#if defined(APP_BENCHMARK_TYPE_BOOST_BOOST_MULTIPRECISION_CBRT_USE_BIN_FLOAT)
#include <boost/multiprecision/cpp_bin_float.hpp>
#else
#include <boost/multiprecision/cpp_dec_float.hpp>
#endif

namespace local
{
  using big_float_type =
  #if defined(APP_BENCHMARK_TYPE_BOOST_BOOST_MULTIPRECISION_CBRT_USE_BIN_FLOAT)
    boost::multiprecision::number<boost::multiprecision::cpp_bin_float<101>,
                                  boost::multiprecision::et_off>;
  #else
    boost::multiprecision::number<boost::multiprecision::cpp_dec_float<101, std::int32_t, void>,
                                  boost::multiprecision::et_off>;
  #endif

  // N[(3001/3)^(1/3), 111]
  // 10.0011109876771782769109438960277928258242274909220595675238056009519465183945889896557377478820599978423940127
  const big_float_type
    control
    (
      "10.0011109876771782769109438960277928258242274909220595675238056009519465183945889896557377478820599978423940127"
    );
}

bool app::benchmark::run_boost_multiprecision_cbrt()
{
  using local::big_float_type;

  using std::cbrt;
  using boost::math::cbrt;

  // Compute a square root.
  const big_float_type big_float_arg    = big_float_type(3001) / 3;
  const big_float_type big_float_result = cbrt(big_float_arg);

  using local::control;

  // Compare the calculated result with the known control value.
  const bool app_benchmark_result_is_ok = detail::is_close_fraction(big_float_result, control);

  return app_benchmark_result_is_ok;
}

#if defined(APP_BENCHMARK_STANDALONE_MAIN)
int main()
{
  // g++ -Wall -O3 -march=native -I./ref_app/src/mcal/host -I./ref_app/src -DAPP_BENCHMARK_TYPE=APP_BENCHMARK_TYPE_BOOST_MULTIPRECISION_CBRT -DAPP_BENCHMARK_STANDALONE_MAIN ./ref_app/src/app/benchmark/app_benchmark_boost_math_cbrt_tgamma.cpp -o ./ref_app/bin/app_benchmark_boost_multiprecision_cbrt.exe

  bool result_is_ok = true;

  for(unsigned i = 0U; i < 64U; ++i)
  {
    result_is_ok &= app::benchmark::run_boost_multiprecision_cbrt();
  }

  return (result_is_ok ? 0 : -1);
}

#endif

#endif // APP_BENCHMARK_TYPE_BOOST_MULTIPRECISION_CBRT
