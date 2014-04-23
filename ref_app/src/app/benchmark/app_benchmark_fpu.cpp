
///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2014.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

//#define CFG_USE_BENCHMARK_FPU

#if defined(CFG_USE_BENCHMARK_FPU)

  #include <cmath>
  #include <cstdint>
  #include <cstdfloat>
  #include <mcal_benchmark.h>

  std::float32_t value_x;
  std::float32_t value_y;

#endif

namespace app
{
  namespace benchmark
  {
    namespace fpu
    {
      void task_init();
      void task_func();
    }
  }
}

void app::benchmark::fpu::task_init()
{
  #if defined(CFG_USE_BENCHMARK_FPU)

  mcal::benchmark::benchmark_port_type::set_direction_output();

  value_x = 0.5F;

  #endif
}

void app::benchmark::fpu::task_func()
{
  #if defined(CFG_USE_BENCHMARK_FPU)

  mcal::benchmark::benchmark_port_type::set_pin_high();

  value_y = std::tgamma(value_x);

  // The expected value is: tgamma(0.5) = sqrt(pi) = (approx.) 1.77245385.
  const bool the_result_is_ok = ((value_y > 1.772F) && (value_y < 1.773F));

  if(the_result_is_ok)
  {
    mcal::benchmark::benchmark_port_type::set_pin_low();
  }

  #endif
}
