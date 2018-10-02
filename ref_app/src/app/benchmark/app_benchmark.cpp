///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2018.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <array>
#include <cstdint>
#include <limits>

#include <app/benchmark/app_benchmark.h>
#include <mcal_benchmark.h>
#include <mcal_cpu.h>
#include <mcal_irq.h>

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
  port_type::set_direction_output();
  #endif
}

void app::benchmark::task_func()
{
  bool result_is_ok;

  #if(APP_BENCHMARK_TYPE == APP_BENCHMARK_TYPE_NONE)

  result_is_ok = true;

  #else

    mcal::irq::disable_all();
    port_type::set_pin_high();

    #if(APP_BENCHMARK_TYPE == APP_BENCHMARK_TYPE_COMPLEX)

    result_is_ok = app::benchmark::run_complex();

    #elif(APP_BENCHMARK_TYPE == APP_BENCHMARK_TYPE_CRC)

    result_is_ok = app::benchmark::run_crc();

    #elif (APP_BENCHMARK_TYPE == APP_BENCHMARK_TYPE_FILTER)

    result_is_ok = app::benchmark::run_filter();

    #elif(APP_BENCHMARK_TYPE == APP_BENCHMARK_TYPE_FIXED_POINT)

    result_is_ok = app::benchmark::run_fixed_point();

    #elif (APP_BENCHMARK_TYPE == APP_BENCHMARK_TYPE_FLOAT)

    result_is_ok = app::benchmark::run_float();

    #elif(APP_BENCHMARK_TYPE == APP_BENCHMARK_TYPE_WIDE_INTEGER)

    result_is_ok = app::benchmark::run_wide_integer();

    #endif

    port_type::set_pin_low();
    mcal::irq::enable_all();

  #endif

  if(result_is_ok == false)
  {
    for(;;)
    {
      mcal::cpu::nop();
    }
  }
}
