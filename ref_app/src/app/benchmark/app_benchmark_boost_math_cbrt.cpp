///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2019.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <cstdint>

#include <boost/math/special_functions/cbrt.hpp>

#include <app/benchmark/app_benchmark.h>

#if(APP_BENCHMARK_TYPE == APP_BENCHMARK_TYPE_BOOST_MATH_CBRT)

namespace local
{
  template<typename FloatingPointType>
  bool is_close_fraction(const FloatingPointType a,
                         const FloatingPointType b,
                         const FloatingPointType tol = std::numeric_limits<FloatingPointType>::epsilon() * 10.0F)
  {
    using std::fabs;

    const FloatingPointType ratio = fabs(a / b);

    const FloatingPointType delta = fabs(1 - ratio);

    const bool result_is_ok = (delta < tol);

    return result_is_ok;
  }
}

extern float cb;
extern float x;

bool app::benchmark::run_boost_math_cbrt()
{
  cb = boost::math::cbrt(x);

  const bool result_is_ok = local::is_close_fraction(cb, 1.0714412696907731080F);

  return result_is_ok;
}

float cb;
float x = 1.23F;


#if defined(APP_BENCHMARK_STANDALONE_MAIN)
int main()
{
  // g++ -Wall -O3 -march=native -I./ref_app/src/mcal/host -I./ref_app/src -DAPP_BENCHMARK_TYPE=APP_BENCHMARK_TYPE_CRC -DAPP_BENCHMARK_STANDALONE_MAIN ./ref_app/src/app/benchmark/app_benchmark_crc.cpp -o ./ref_app/bin/app_benchmark_crc.exe

  bool result_is_ok = true;

  for(unsigned i = 0U; i < 64U; ++i)
  {
    result_is_ok &= app::benchmark::run_boost_math_cbrt();
  }

  return result_is_ok ? 0 : -1;
}

#endif

#endif // APP_BENCHMARK_TYPE_BOOST_MATH_CBRT
