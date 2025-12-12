///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2025.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <app/led/app_led.h>
#include <mcal_benchmark.h>
#include <mcal/mcal.h>
#include <os/os_task.h>

#include <mcal_memory/mcal_memory_sram_array.h>

#include <util/utility/util_attribute.h>

ATTRIBUTE(used,noinline) auto main() -> int;

auto main() -> int
{
  // Initialize the microcontroller abstraction layer.
  mcal::init();

  using benchmark_port_type = ::mcal::benchmark::benchmark_port_type;

  benchmark_port_type::set_direction_output();

  mcal::spi::sram::mcal_spi_sram_type::init();
  mcal::spi::lcd::mcal_spi_lcd_type::init();

  // Configure and create the OS tasks. These macros
  // also setup the task static resources including the
  // task control block structures and task stacks.

  OS_TASK_CREATE(app_led_task_background,  nullptr, 1U, 512U);
  OS_TASK_CREATE(app_led_task_toggle_led0, nullptr, 3U,  32U);

  // Start the OS scheduler (and never return).
  OS_TASK_START_SCHEDULER();
}
