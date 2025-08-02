///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2021 - 2025.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <app/benchmark/app_benchmark.h>
#include <app/benchmark/app_benchmark_detail.h>

#if (defined(APP_BENCHMARK_TYPE) && (APP_BENCHMARK_TYPE == APP_BENCHMARK_TYPE_BOOST_MULTIPRECISION_CBRT))

//#define APP_BENCHMARK_TYPE_BOOST_MP_CBRT_USE_BIN_FLOAT

#if !defined(BOOST_MP_STANDALONE)
#define BOOST_MP_STANDALONE
#endif

#if !defined(BOOST_MATH_STANDALONE)
#define BOOST_MATH_STANDALONE
#endif

#if !defined(BOOST_MATH_NO_RTTI)
#define BOOST_MATH_NO_RTTI
#endif

#if !defined(BOOST_MATH_DISABLE_THREADS)
#define BOOST_MATH_DISABLE_THREADS
#endif

#if !defined(BOOST_MATH_NO_EXCEPTIONS)
#define BOOST_MATH_NO_EXCEPTIONS
#endif

#if !defined(BOOST_MP_NO_EXCEPTIONS)
#define BOOST_MP_NO_EXCEPTIONS
#endif

#if !defined(BOOST_NO_EXCEPTIONS)
#define BOOST_NO_EXCEPTIONS
#endif

#include <boost/math/special_functions/cbrt.hpp>
#if defined(APP_BENCHMARK_TYPE_BOOST_MP_CBRT_USE_BIN_FLOAT)
#include <boost/multiprecision/cpp_bin_float.hpp>
#else
#include <boost/multiprecision/cpp_dec_float.hpp>
#endif

namespace local
{
  constexpr unsigned app_benchmark_backend_digits10 { 201U };

  using app_benchmark_big_float_backend_type =
  #if defined(APP_BENCHMARK_TYPE_BOOST_MP_CBRT_USE_BIN_FLOAT)
    boost::multiprecision::cpp_bin_float<app_benchmark_backend_digits10, boost::multiprecision::backends::digit_base_10, void, std::int32_t>;
  #else
    boost::multiprecision::cpp_dec_float<app_benchmark_backend_digits10, std::int32_t, void>;
  #endif

  using app_benchmark_big_float_type =
    boost::multiprecision::number<app_benchmark_big_float_backend_type, boost::multiprecision::et_off>;

  // N[(123456/100)^(1/3), 211]
  // 10.7276369432283170454869317373527647801772956394047834686224956433128028534945259441672192774907629718402457465
  const app_benchmark_big_float_type
    app_benchmark_big_float_ctrl
    {
      "10.72763694322831704548693173735276478017729563940478346862249564331280285349452594416721927749076297184024574654480528769322221647332343140726593804683287639579165427122149453895093234587007864784138965614715829"
    };

  const app_benchmark_big_float_type
    app_benchmark_big_float_arg
    {
      app_benchmark_big_float_type(UINT32_C(123456)) / 100U
    };
} // namespace local

auto app::benchmark::run_boost_multiprecision_cbrt() -> bool
{
  using std::cbrt;
  using boost::math::cbrt;

  // Compute the cube root value.
  const local::app_benchmark_big_float_type local_big_float_result { cbrt(local::app_benchmark_big_float_arg) };

  // Compare the calculated result with the known control value.
  const bool
    app_benchmark_result_is_ok
    {
      detail::is_close_fraction(local_big_float_result, local::app_benchmark_big_float_ctrl)
    };

  return app_benchmark_result_is_ok;
}

#if defined(APP_BENCHMARK_STANDALONE_MAIN)
ATTRIBUTE(used) auto main() -> int;

auto main() -> int
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
