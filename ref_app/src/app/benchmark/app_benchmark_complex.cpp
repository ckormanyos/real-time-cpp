///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2014 - 2019.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <app/benchmark/app_benchmark.h>

#if(APP_BENCHMARK_TYPE == APP_BENCHMARK_TYPE_COMPLEX)

#define EXTENDED_COMPLEX_DISABLE_IOSTREAM

#include <app/benchmark/app_benchmark_detail.h>
#include <math/extended_complex/extended_complex.h>

namespace
{
  using complex_type = extended_complex::complex<float>;
}

extern complex_type x;
extern complex_type y;

bool app::benchmark::run_complex()
{
  using std::sin;

  // 14.859343457123410999 + 5.259004469728472689 i
  y = sin(x);

  const bool result_is_ok = (   detail::is_close_fraction(y.real(), 14.859343457123410999F)
                             && detail::is_close_fraction(y.imag(),  5.259004469728472689F));

  return result_is_ok;
}

complex_type x(1.23F, 3.45F);
complex_type y;

#endif // APP_BENCHMARK_TYPE_COMPLEX
