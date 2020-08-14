///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2019.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <app/benchmark/app_benchmark.h>
#include <mcal_benchmark.h>
#include <mcal_cpu.h>

namespace
{
  using port_type = mcal::benchmark::benchmark_port_type;
}

namespace app
{
  namespace benchmark
  {
    void task_init();
    void task_func();
  }
}

void app::benchmark::task_init()
{
  #if(APP_BENCHMARK_TYPE == APP_BENCHMARK_TYPE_NONE)
  #else
  // Set the benchmark port pin direction to output.
  port_type::set_direction_output();
  #endif
}

void app::benchmark::task_func()
{
  // Set the benchmark port pin level to high.
  port_type::set_pin_high();

  // Run the benchmark (if enabled via compiler switch).

  #if(APP_BENCHMARK_TYPE == APP_BENCHMARK_TYPE_NONE)

  const bool result_is_ok = true;

  #elif(APP_BENCHMARK_TYPE == APP_BENCHMARK_TYPE_COMPLEX)

  const bool result_is_ok = app::benchmark::run_complex();

  #elif(APP_BENCHMARK_TYPE == APP_BENCHMARK_TYPE_CRC)

  const bool result_is_ok = app::benchmark::run_crc();

  #elif (APP_BENCHMARK_TYPE == APP_BENCHMARK_TYPE_FAST_MATH)

  const bool result_is_ok = app::benchmark::run_fast_math();

  #elif (APP_BENCHMARK_TYPE == APP_BENCHMARK_TYPE_FILTER)

  const bool result_is_ok = app::benchmark::run_filter();

  #elif(APP_BENCHMARK_TYPE == APP_BENCHMARK_TYPE_FIXED_POINT)

  const bool result_is_ok = app::benchmark::run_fixed_point();

  #elif (APP_BENCHMARK_TYPE == APP_BENCHMARK_TYPE_FLOAT)

  const bool result_is_ok = app::benchmark::run_float();

  #elif(APP_BENCHMARK_TYPE == APP_BENCHMARK_TYPE_WIDE_INTEGER)

  const bool result_is_ok = app::benchmark::run_wide_integer();

  #elif(APP_BENCHMARK_TYPE == APP_BENCHMARK_TYPE_PI_SPIGOT)

  const bool result_is_ok = app::benchmark::run_pi_spigot();

  #elif(APP_BENCHMARK_TYPE == APP_BENCHMARK_TYPE_PI_SPIGOT_SINGLE)

  const bool result_is_ok = app::benchmark::run_pi_spigot_single();

  #elif(APP_BENCHMARK_TYPE == APP_BENCHMARK_TYPE_HASH)

  const bool result_is_ok = app::benchmark::run_hash();

  #endif

  // Set the benchmark port pin level to low.
  port_type::set_pin_low();

  if(result_is_ok == false)
  {
    // Purposefully crash the system (watchdog) if the benchmark fails.
    for(;;)
    {
      mcal::cpu::nop();
    }
  }
}
