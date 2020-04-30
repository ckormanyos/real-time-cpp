///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2020.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <app/led/app_led.h>
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
  // Set the benchmark port pin to output
  port_type::set_direction_output();
}

void app::benchmark::task_func()
{
  port_type::set_pin_high();

  const bool result_is_ok = app::led::get_state_is_ok();

  port_type::set_pin_low();

  if(result_is_ok == false)
  {
    for(;;)
    {
      mcal::cpu::nop();
    }
  }
}
