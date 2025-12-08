///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2025.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <app/led/app_led.h>
#include <mcal/mcal.h>
#include <os/os_task.h>

#include <mcal_memory/mcal_memory_sram_array.h>

#include <util/utility/util_attribute.h>

ATTRIBUTE(used,noinline) auto main() -> int;

auto manip_container() -> bool;

constexpr auto sram_start_address = static_cast<mcal_sram_uintptr_t>(UINT8_C(0));

using sram_container_type =
  mcal::memory::sram::array<std::uint32_t,
                            std::uint32_t { UINT32_C(1024) * UINT32_C(1024) },
                            sram_start_address>;

sram_container_type container { };

auto main() -> int
{
  // Initialize the microcontroller abstraction layer.
  mcal::init();

  mcal::spi::sram::mcal_spi_sram_type::init();

  // Configure and create the OS tasks. These macros
  // also setup the task static resources including the
  // task control block structures and task stacks.

  OS_TASK_CREATE(app_led_task_background,  nullptr, 1U, 64U);
  OS_TASK_CREATE(app_led_task_toggle_led0, nullptr, 3U, 64U);

  // Start the OS scheduler (and never return).
  OS_TASK_START_SCHEDULER();
}

auto manip_container() -> bool
{
  static sram_container_type::pointer my_sram_ptr { container.data() };
  static std::uint32_t my_sram_value { };

  *my_sram_ptr = my_sram_value;

  const bool result_sram_is_ok { (*my_sram_ptr == my_sram_value) };

  ++my_sram_ptr;
  ++my_sram_value;

  if(my_sram_ptr == container.data() + container.size())
  {
    my_sram_ptr = container.data();
  }

  return result_sram_is_ok;
}