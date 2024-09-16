///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2024.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <mcal_cpu.h>
#include <mcal_osc.h>
#include <mcal_port.h>
#include <mcal_wdg.h>

#include <RP2350.h>

namespace local {

auto init_core() -> void;

auto init_core() -> void
{
  /* we came here from the RP2350 BootRom and SBL */
  /* Reset core1 to start from a known state */

  HW_PER_PSM->FRCE_OFF.bit.PROC1 = 1U;

  while((HW_PER_PSM->DONE.bit.PROC1 == 1U));

  HW_PER_PSM->FRCE_OFF.bit.PROC1 = 0U;

  while((HW_PER_PSM->DONE.bit.PROC1 != 1U));

  /* Reset peripheral to start from a known state */
  HW_PER_RESETS->RESET.bit.IO_BANK0   = 1U;
  HW_PER_RESETS->RESET.bit.PADS_BANK0 = 1U;

  while((HW_PER_RESETS->RESET_DONE.bit.IO_BANK0 == 1U) || (HW_PER_RESETS->RESET_DONE.bit.PADS_BANK0 == 1U));

  HW_PER_RESETS->RESET.bit.IO_BANK0   = 0U;
  HW_PER_RESETS->RESET.bit.PADS_BANK0 = 0U;

  while((HW_PER_RESETS->RESET_DONE.bit.IO_BANK0 == 0U) || (HW_PER_RESETS->RESET_DONE.bit.PADS_BANK0 == 0U));

  /*Setting EXTEXCLALL allows external exclusive operations to be used in a configuration with no MPU.
  This is because the default memory map does not include any shareable Normal memory.*/
  SCnSCB->ACTLR |= (1ul<<29);
}

} // namespace local


void mcal::cpu::init()
{
  local::init_core();

  mcal::wdg::init(nullptr);
  mcal::port::init(nullptr);
  mcal::osc::init(nullptr);
}
