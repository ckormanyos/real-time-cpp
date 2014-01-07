///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2013.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <mcal_safety_dram.h>
#include <mcal_safety_rom_checksum.h>
#include <mcal_wdg.h>
#include <util/safety/time/util_safety_max_time_since_service.h>

namespace sys
{
  namespace idle
  {
    void task_init();
    void task_func(const bool do_watchdog_trigger);
  }
}

namespace
{
  // Define the DRAM memory refresh mechanism.
  typedef mcal::safety::dram_memory_refresh_type my_dram_memory_refresh_type;

  my_dram_memory_refresh_type sys_idle_dram_memory_refresh(mcal::safety::dram_memory_block_list);

  // Define the ROM memory checksum mechanism.
  typedef mcal::safety::rom_memory_checksum_type my_rom_memory_checksum_type;

  my_rom_memory_checksum_type sys_idle_rom_memory_checksum(mcal::safety::rom_memory_block_list,
                                                           mcal::safety::rom_memory_result_address);

  // Define the mechanism that evaluates the maximum time
  // (in microseconds) since the last wathdog trigger.
  typedef std::uint16_t watchdog_statistics_value_type;

  const std::array<watchdog_statistics_value_type, 5U> sys_idle_watchdog_statistics_ranges =
  {{
    watchdog_statistics_value_type( 2000U),
    watchdog_statistics_value_type( 4000U),
    watchdog_statistics_value_type(10000U),
    watchdog_statistics_value_type(20000U),
    watchdog_statistics_value_type(32000U)
  }};

  typedef util::safety::max_time_since_service<watchdog_statistics_value_type, 5U, std::uint_least16_t> my_watchdog_statistics_type;

  my_watchdog_statistics_type sys_idle_time_since_watchdog_trigger(sys_idle_watchdog_statistics_ranges);
}

void sys::idle::task_init() { }

void sys::idle::task_func(const bool do_watchdog_trigger)
{
  static bool result_of_dram_refresh_is_ok = true;
  static bool result_of_rom_checksum_is_ok = true;

  if(do_watchdog_trigger)
  {
    // Service the mechanism that evaluates the maximum time
    // (in microseconds) since the last wathdog trigger.
    sys_idle_time_since_watchdog_trigger.service();

    if(result_of_dram_refresh_is_ok && result_of_rom_checksum_is_ok)
    {
      // Service the watchdog.
      mcal::wdg::secure::trigger();
    }
  }
  else
  {
    static std::uint_least8_t safety_prescaler;

    if((safety_prescaler == static_cast<std::uint_least8_t>(0U)) && result_of_dram_refresh_is_ok)
    {
      // Service the DRAM memory refresh mechanism.
      sys_idle_dram_memory_refresh.service();

      // Obtain (and store) the result of the DRAM memory refresh mechanism.
      result_of_dram_refresh_is_ok = (sys_idle_dram_memory_refresh.get_result_of_process() != my_dram_memory_refresh_type::result_is_finished_and_wrong);
    }
    else if((safety_prescaler == static_cast<std::uint_least8_t>(1U)) && result_of_rom_checksum_is_ok)
    {
      // Service the ROM memory checksum mechanism.
      sys_idle_rom_memory_checksum.service();

      // Obtain (and store) the result of the ROM memory checksum mechanism.
      result_of_rom_checksum_is_ok = (sys_idle_rom_memory_checksum.get_result_of_process() != my_rom_memory_checksum_type::result_is_finished_and_wrong);
    }

    ++safety_prescaler;

    if(safety_prescaler >= static_cast<std::uint_least8_t>(2U))
    {
      safety_prescaler = static_cast<std::uint_least8_t>(0U);
    }
  }
}
