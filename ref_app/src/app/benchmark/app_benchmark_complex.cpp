///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2014 - 2024.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <app/benchmark/app_benchmark.h>

#if (defined(APP_BENCHMARK_TYPE) && (APP_BENCHMARK_TYPE == APP_BENCHMARK_TYPE_COMPLEX))

#define EXTENDED_COMPLEX_DISABLE_IOSTREAM

#include <app/benchmark/app_benchmark_detail.h>
#include <math/extended_complex/extended_complex.h>

namespace
{
  using local_floating_point_type = float;

  using complex_type = extended_complex::complex<local_floating_point_type>;
}

extern complex_type x_val;
extern complex_type y_val;

auto app::benchmark::run_complex() -> bool
{
  using std::sin;

  // 14.859343457123410999 + 5.259004469728472689 i
  y_val = sin(x_val);

  const bool result_is_ok = (   detail::is_close_fraction(y_val.real(), static_cast<local_floating_point_type>(14.859343457123410999L))
                             && detail::is_close_fraction(y_val.imag(), static_cast<local_floating_point_type>( 5.259004469728472689L)));

  return result_is_ok;
}

#if defined(APP_BENCHMARK_STANDALONE_MAIN)
ATTRIBUTE(used) auto main() -> int;

auto main() -> int
{
  // g++ -Wall -O3 -march=native -I./ref_app/src/mcal/host -I./ref_app/src -DAPP_BENCHMARK_TYPE=APP_BENCHMARK_TYPE_COMPLEX -DAPP_BENCHMARK_STANDALONE_MAIN ./ref_app/src/app/benchmark/app_benchmark_complex.cpp -o ./ref_app/bin/app_benchmark_complex.exe

  bool result_is_ok = true;

  for(unsigned i = 0U; i < 64U; ++i)
  {
    result_is_ok &= app::benchmark::run_complex();
  }

  return result_is_ok ? 0 : -1;
}

#endif

complex_type x_val { static_cast<local_floating_point_type>(1.23L), static_cast<local_floating_point_type>(3.45L) };
complex_type y_val { };

#endif // APP_BENCHMARK_TYPE_COMPLEX
