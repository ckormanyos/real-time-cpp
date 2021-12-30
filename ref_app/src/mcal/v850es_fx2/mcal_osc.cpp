///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2004 - 2021.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <mcal_cpu.h>
#include <mcal_osc.h>
#include <mcal_reg.h>

void mcal::osc::init(const config_type*)
{
  // Set the minimum number of wait states for flash.
  mcal::reg::reg_access_static<std::uint32_t, std::uint8_t, mcal::reg::vswc, UINT8_C(0x01)>::reg_set();

  // Start the MainOSC
  do
  {
    // PCC is write protected, use special access sequence.
    mcal::reg::reg_access_static<std::uint32_t, std::uint8_t, mcal::reg::sys, UINT8_C(0)>::reg_set();

    // Access sequence: write PRCMD as prerequisite for PCC
    mcal::reg::reg_access_static<std::uint32_t, std::uint8_t, mcal::reg::prcmd, UINT8_C(0)>::reg_set();

    // Wait five clock cycles.
    mcal::cpu::nop(); mcal::cpu::nop(); mcal::cpu::nop(); mcal::cpu::nop(); mcal::cpu::nop();

    // Start operation of main clock, _MCK=0, fcpu=fXX.
    mcal::reg::reg_access_static<std::uint32_t, std::uint8_t, mcal::reg::pcc, UINT8_C(6)>::bit_set();
  }
  while(mcal::reg::reg_access_static<std::uint32_t, std::uint8_t, mcal::reg::sys, UINT8_C(0)>::bit_get() != false);

  // Wait eight clock cycles.
  mcal::cpu::nop(); mcal::cpu::nop(); mcal::cpu::nop(); mcal::cpu::nop();
  mcal::cpu::nop(); mcal::cpu::nop(); mcal::cpu::nop(); mcal::cpu::nop();

  // To operate the PLL from the stopped status, set the
  // PLLON bit to 1, and then set the SELPLL bit to 1 after
  // the LOCKR.LOCK bit = 0.

  // Setup the PLL lockup time 2^13 / fx.
  mcal::reg::reg_access_static<std::uint32_t, std::uint8_t, mcal::reg::plls, UINT8_C(3)>::reg_set();

  // Enable the PLL, while CPU is still on main osc.
  mcal::reg::reg_access_static<std::uint32_t, std::uint8_t, mcal::reg::pllctl, UINT8_C(1)>::reg_set();

  // Wait for a stable PLL.
  while(mcal::reg::reg_access_static<std::uint32_t, std::uint8_t, mcal::reg::lockr, UINT8_C(0)>::bit_get() != false)
  {
    mcal::cpu::nop();
  }

  // Switch to PLL.
  mcal::reg::reg_access_static<std::uint32_t, std::uint8_t, mcal::reg::pllctl, UINT8_C(3)>::reg_set();
}
