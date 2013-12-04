///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2013.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <mcal_safety_dram.h>
#include <mcal_safety_rom_checksum.h>
#include <mcal_wdg.h>

namespace sys
{
  namespace idle
  {
    void task_init();
    void task_func(const bool do_trigger);
  }
}

namespace
{
  typedef mcal::safety::dram_memory_refresh_type my_dram_memory_refresh_type;
  typedef mcal::safety::rom_memory_checksum_type my_rom_memory_checksum_type;

  my_dram_memory_refresh_type sys_idle_dram_memory_refresh(mcal::safety::dram_memory_block_list);
  my_rom_memory_checksum_type sys_idle_rom_memory_checksum(mcal::safety::rom_memory_block_list,
                                                           mcal::safety::rom_memory_result_address);

  std::uint_least8_t safety_prescaler;
}

void sys::idle::task_init()
{
}

void sys::idle::task_func(const bool do_trigger)
{
  if(safety_prescaler == static_cast<std::uint_least8_t>(0U))
  {
    // Service the DRAM memory refresh mechanism.
    sys_idle_dram_memory_refresh.service();
  }
  else if(safety_prescaler == static_cast<std::uint_least8_t>(1U))
  {
    // Service the ROM memory checksum mechanism.
    sys_idle_rom_memory_checksum.service();
  }

  ++safety_prescaler;

  if(safety_prescaler >= static_cast<std::uint_least8_t>(2U))
  {
    safety_prescaler = static_cast<std::uint_least8_t>(0U);
  }

  const bool result_of_dram_refresh_is_ok = (sys_idle_dram_memory_refresh.get_result_of_process() != my_dram_memory_refresh_type::result_is_finished_and_wrong);
  const bool result_of_rom_checksum_is_ok = (sys_idle_rom_memory_checksum.get_result_of_process() != my_rom_memory_checksum_type::result_is_finished_and_wrong);

  // Service (trigger) the watchdog if necessary.
  if(do_trigger && result_of_dram_refresh_is_ok && result_of_rom_checksum_is_ok)
  {
    mcal::wdg::trigger();
  }
}
