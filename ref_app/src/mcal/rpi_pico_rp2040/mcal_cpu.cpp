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
  // We came here from the RP2040 BootRom and SBL.
  // Reset core1 to start from a known state.

  // PSM->FRCE_OFF.bit.proc1 = 1U;
  mcal::reg::reg_access_static<std::uint32_t,
                               std::uint32_t,
                               mcal::reg::psm_frce_off,
                               UINT32_C(16)>::bit_set();

  // while((PSM->DONE.bit.proc1 == 1U));
  while(mcal::reg::reg_access_static<std::uint32_t,
                                     std::uint32_t,
                                     mcal::reg::psm_done,
                                     UINT32_C(16)>::bit_get()) { mcal::cpu::nop(); }

  // PSM->FRCE_OFF.bit.proc1 = 0U;
  mcal::reg::reg_access_static<std::uint32_t,
                               std::uint32_t,
                               mcal::reg::psm_frce_off,
                               UINT32_C(16)>::bit_clr();

  // while((PSM->DONE.bit.proc1 != 1U));
  while(!mcal::reg::reg_access_static<std::uint32_t,
                                      std::uint32_t,
                                      mcal::reg::psm_done,
                                      UINT32_C(16)>::bit_get()) { mcal::cpu::nop(); }

  // Reset peripheral to start from a known state.

  // RESETS->RESET.bit.io_bank0   = 1U;
  mcal::reg::reg_access_static<std::uint32_t,
                               std::uint32_t,
                               mcal::reg::resets_reset,
                               UINT32_C(5)>::bit_set();

  //RESETS->RESET.bit.pads_bank0 = 1U;
  mcal::reg::reg_access_static<std::uint32_t,
                               std::uint32_t,
                               mcal::reg::resets_reset,
                               UINT32_C(8)>::bit_set();

  // while((RESETS->RESET_DONE.bit.io_bank0 == 1U) || (RESETS->RESET_DONE.bit.pads_bank0 == 1U));
  while
  (
       mcal::reg::reg_access_static<std::uint32_t, std::uint32_t,  mcal::reg::resets_reset_done, UINT32_C(5)>::bit_get()
    || mcal::reg::reg_access_static<std::uint32_t, std::uint32_t,  mcal::reg::resets_reset_done, UINT32_C(8)>::bit_get()
  )
  {
    mcal::cpu::nop();
  }

  // RESETS->RESET.bit.io_bank0   = 0U;
  mcal::reg::reg_access_static<std::uint32_t,
                                std::uint32_t,
                                mcal::reg::resets_reset,
                                UINT32_C(5)>::bit_clr();

  // RESETS->RESET.bit.pads_bank0 = 0U;
  mcal::reg::reg_access_static<std::uint32_t,
                                std::uint32_t,
                                mcal::reg::resets_reset,
                                UINT32_C(8)>::bit_clr();

  // while((RESETS->RESET_DONE.bit.io_bank0 == 0U) || (RESETS->RESET_DONE.bit.pads_bank0 == 0U));
  while
  (
       (!mcal::reg::reg_access_static<std::uint32_t, std::uint32_t,  mcal::reg::resets_reset_done, UINT32_C(5)>::bit_get())
    || (!mcal::reg::reg_access_static<std::uint32_t, std::uint32_t,  mcal::reg::resets_reset_done, UINT32_C(8)>::bit_get())
  )
  {
    mcal::cpu::nop();
  }
}

} // namespace local


void mcal::cpu::init()
{
  local::init_core();

  mcal::wdg::init(nullptr);
  mcal::port::init(nullptr);
  mcal::osc::init(nullptr);
}
