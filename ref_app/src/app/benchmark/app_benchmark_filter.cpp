///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2010 - 2019.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <cstdint>

#include <app/benchmark/app_benchmark.h>

#if(APP_BENCHMARK_TYPE == APP_BENCHMARK_TYPE_FILTER)

#include <math/filters/fir_order_n.h>

namespace
{
  using filter_type = fir_order_n<17U, 64U, std::int16_t, std::int32_t>;
  using sample_type = filter_type::sample_type;
}

extern       filter_type f;
extern const sample_type sample;

bool app::benchmark::run_filter()
{
  static std::uint_fast8_t sample_counter;

  bool result_is_ok;

  f.new_sample<-2, -2, -2, -1, 3, 9, 15, 20, 24,
               24, 20, 15, 9, 3, -1, -2, -2, -2>(sample);

  if(sample_counter < 10U)
  {
    ++sample_counter;

    result_is_ok = true;
  }
  else
  {
    sample_counter = 0U;

    const std::int16_t filter_result = f.get_result();

    result_is_ok = (filter_result == INT16_C(84));

    f = filter_type();
  }

  return result_is_ok;
}

      filter_type f;
const sample_type sample(100);

#endif // APP_BENCHMARK_TYPE_FILTER
