///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2004 - 2021.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <mcal_cpu.h>
#include <mcal_osc.h>
#include <mcal_reg.h>

#include <io_macros.h>
#include <DF3375.h>

void mcal::osc::init(const config_type*)
{
  using UINT8 = std::uint8_t;

  // Set the minimum number of wait states for flash.
  VSWC = static_cast<UINT8>(0x01u);

  // Start the MainOSC
  do
  {
    // PCC is write protected, use special access sequence.
    SYS   = static_cast<UINT8>(0u);

    // Access sequence: write PRCMD as prerequisite for PCC
    PRCMD = static_cast<UINT8>(0u);

    // Wait five clock cycles.
    mcal::cpu::nop(); mcal::cpu::nop(); mcal::cpu::nop(); mcal::cpu::nop(); mcal::cpu::nop();

    // start operation of main clock, _MCK=0, fcpu=fXX
    _MCK  = 0U;
  }
  while(static_cast<UINT8>(SYS & static_cast<UINT8>(1u)) != static_cast<UINT8>(0u));

  // Wait eight clock cycles.
  mcal::cpu::nop(); mcal::cpu::nop(); mcal::cpu::nop(); mcal::cpu::nop();
  mcal::cpu::nop(); mcal::cpu::nop(); mcal::cpu::nop(); mcal::cpu::nop();

  // To operate the PLL from the stopped status, set the
  // PLLON bit to 1, and then set the SELPLL bit to 1 after
  // the LOCKR.LOCK bit = 0.

  // Setup the PLL lockup time 2^13 / fx.
  PLLS = static_cast<UINT8>(3u);

  // Enable the PLL, CPU still on main
  PLLCTL = static_cast<UINT8>(1u);

  // Wait for a stable PLL.
  while(static_cast<UINT8>(LOCKR & static_cast<UINT8>(1u)) != static_cast<UINT8>(0u))
  {
    mcal::cpu::nop();
  }

  // Switch to PLL.
  PLLCTL = static_cast<UINT8>(3u);
}
