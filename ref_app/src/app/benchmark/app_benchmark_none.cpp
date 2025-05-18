///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2021.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <app/benchmark/app_benchmark.h>

#if (defined(APP_BENCHMARK_TYPE) && (APP_BENCHMARK_TYPE == APP_BENCHMARK_TYPE_NONE))

auto app::benchmark::run_none() -> bool
{
  constexpr auto result_is_ok = true;

  return result_is_ok;
}

#if defined(APP_BENCHMARK_STANDALONE_MAIN)
auto main() -> int;

auto main() -> int
{
  // g++ -Wall -O3 -march=native -I./ref_app/src/mcal/host -I./ref_app/src -DAPP_BENCHMARK_TYPE=APP_BENCHMARK_TYPE_NONE -DAPP_BENCHMARK_STANDALONE_MAIN ./ref_app/src/app/benchmark/app_benchmark_none.cpp -o ./ref_app/bin/app_benchmark_none.exe

  bool result_is_ok = true;

  for(unsigned i = 0U; i < 64U; ++i)
  {
    result_is_ok &= app::benchmark::run_none();
  }

  return result_is_ok ? 0 : -1;
}
#endif

#endif // APP_BENCHMARK_TYPE_NONE
