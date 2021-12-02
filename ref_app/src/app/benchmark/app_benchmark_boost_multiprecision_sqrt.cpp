///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2021.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <app/benchmark/app_benchmark.h>
#include <app/benchmark/app_benchmark_detail.h>

#if(APP_BENCHMARK_TYPE == APP_BENCHMARK_TYPE_BOOST_MULTIPRECISION_SQRT)

//TGT_INCLUDES  = -IC:/boost/boost_multiprecision_standalone/include                \
//                -IC:/boost/modular_boost/boost/libs/math/include                  \
//                -IC:/boost/modular_boost/boost/libs/config/include

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

#define BOOST_MATH_PROMOTE_FLOAT_POLICY false

#include <boost/multiprecision/cpp_dec_float.hpp>

namespace local
{
  using big_float_type =
    boost::multiprecision::number<boost::multiprecision::cpp_dec_float<51, std::int32_t, void>,
                                  boost::multiprecision::et_off>;
}

bool app::benchmark::run_boost_multiprecision_sqrt()
{
  using local::big_float_type;

  // N[Sqrt[3001/3], 51]
  // 31.6280466253186956650730523324944190761410921737177

  const big_float_type big_float_arg    = big_float_type(3001) / 3;
  const big_float_type big_float_result = sqrt(big_float_arg);

  const bool app_benchmark_result_is_ok = (static_cast<int>(big_float_result) == 31);

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

  return result_is_ok ? 0 : -1;
}

#endif

#endif // APP_BENCHMARK_TYPE_BOOST_MATH_CBRT_TGAMMA
