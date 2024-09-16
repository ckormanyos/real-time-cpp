///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2024.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <mcal_cpu.h>
#include <mcal_osc.h>
#include <mcal_port.h>
#include <mcal_reg.h>
#include <mcal_wdg.h>

namespace local {

auto init_core() -> void;

auto init_core() -> void
{
  // We came here from the RP2350 BootRom and SBL.
  // Reset core1 to start from a known state.

  // HW_PER_PSM->FRCE_OFF.bit.PROC1 = 1U;
  mcal::reg::reg_access_static<std::uint32_t,
                               std::uint32_t,
                               mcal::reg::psm_frce_off,
                               UINT32_C(24)>::bit_set();

  // while((HW_PER_PSM->DONE.bit.PROC1 == 1U));
  while(mcal::reg::reg_access_static<std::uint32_t,
                                     std::uint32_t,
                                     mcal::reg::psm_done,
                                     UINT32_C(24)>::bit_get()) { mcal::cpu::nop(); }

  // HW_PER_PSM->FRCE_OFF.bit.PROC1 = 0U;
  mcal::reg::reg_access_static<std::uint32_t,
                               std::uint32_t,
                               mcal::reg::psm_frce_off,
                               UINT32_C(24)>::bit_clr();

  // while((HW_PER_PSM->DONE.bit.PROC1 != 1U));
  while(!mcal::reg::reg_access_static<std::uint32_t,
                                      std::uint32_t,
                                      mcal::reg::psm_done,
                                      UINT32_C(24)>::bit_get()) { mcal::cpu::nop(); }

  // Reset peripheral to start from a known state.

  // HW_PER_RESETS->RESET.bit.IO_BANK0   = 1U;
  mcal::reg::reg_access_static<std::uint32_t,
                               std::uint32_t,
                               mcal::reg::hw_per_resets_reset,
                               UINT32_C(6)>::bit_set();

  // HW_PER_RESETS->RESET.bit.PADS_BANK0 = 1U;
  mcal::reg::reg_access_static<std::uint32_t,
                               std::uint32_t,
                               mcal::reg::hw_per_resets_reset,
                               UINT32_C(9)>::bit_set();

  // while((HW_PER_RESETS->RESET_DONE.bit.IO_BANK0 == 1U) || (HW_PER_RESETS->RESET_DONE.bit.PADS_BANK0 == 1U));
  while
  (
       mcal::reg::reg_access_static<std::uint32_t, std::uint32_t,  mcal::reg::hw_per_resets_reset_done, UINT32_C(6)>::bit_get()
    || mcal::reg::reg_access_static<std::uint32_t, std::uint32_t,  mcal::reg::hw_per_resets_reset_done, UINT32_C(9)>::bit_get()
  )
  {
    mcal::cpu::nop();
  }

  // HW_PER_RESETS->RESET.bit.IO_BANK0   = 0U;
  mcal::reg::reg_access_static<std::uint32_t,
                               std::uint32_t,
                               mcal::reg::hw_per_resets_reset,
                               UINT32_C(6)>::bit_clr();

  // HW_PER_RESETS->RESET.bit.PADS_BANK0 = 0U;
  mcal::reg::reg_access_static<std::uint32_t,
                               std::uint32_t,
                               mcal::reg::hw_per_resets_reset,
                               UINT32_C(9)>::bit_clr();

  // while((HW_PER_RESETS->RESET_DONE.bit.IO_BANK0 == 0U) || (HW_PER_RESETS->RESET_DONE.bit.PADS_BANK0 == 0U));
  while
  (
       (!mcal::reg::reg_access_static<std::uint32_t, std::uint32_t,  mcal::reg::hw_per_resets_reset_done, UINT32_C(6)>::bit_get())
    || (!mcal::reg::reg_access_static<std::uint32_t, std::uint32_t,  mcal::reg::hw_per_resets_reset_done, UINT32_C(9)>::bit_get())
  )
  {
    mcal::cpu::nop();
  }

  // Setting EXTEXCLALL allows external exclusive operations to be used
  // in a configuration with no MPU. This is because the default memory map
  // does not include any shareable Normal memory.

  // SCnSCB->ACTLR |= (1ul<<29);
  mcal::reg::reg_access_static<std::uint32_t,
                               std::uint32_t,
                               mcal::reg::scnscb_actlr,
                               UINT32_C(29)>::bit_set();
}

} // namespace local


void mcal::cpu::init()
{
  local::init_core();

  mcal::wdg::init(nullptr);
  mcal::port::init(nullptr);
  mcal::osc::init(nullptr);
}
