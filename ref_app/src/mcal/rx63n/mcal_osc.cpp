///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2014.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <cstdint>
#include <mcal_cpu.h>
#include <mcal_osc.h>
#include <mcal_reg.h>

void mcal::osc::init(const config_type*)
{
  // Protection off
  // SYSTEM.PRCR.WORD = 0xA503u;
  mcal::reg::reg_access_static<std::uint32_t,
                               std::uint16_t,
                               mcal::reg::prcr,
                               UINT16_C(0xA503)>::reg_set();

  // Stop sub-clock
  // SYSTEM.SOSCCR.BYTE = 0x01u;
  mcal::reg::reg_access_static<std::uint32_t,
                               std::uint8_t,
                               mcal::reg::sosccr,
                               UINT8_C(0x01)>::reg_set();

  // Set main oscillator settling time to 10ms (131072 cycles at 12MHz)
  // SYSTEM.MOSCWTCR.BYTE = 0x0Du;
  mcal::reg::reg_access_static<std::uint32_t,
                               std::uint8_t,
                               mcal::reg::moscwtcr,
                               UINT8_C(0x0D)>::reg_set();

  // Set the PLL circuit settling time to 10ms (2097152 cycles at 192MHz)
  // SYSTEM.PLLWTCR.BYTE = 0x0Eu;
  mcal::reg::reg_access_static<std::uint32_t,
                               std::uint8_t,
                               mcal::reg::pllwtcr,
                               UINT8_C(0x0E)>::reg_set();

  // Set the PLL circuit to x16
  // SYSTEM.PLLCR.WORD = 0x0F00u;
  mcal::reg::reg_access_static<std::uint32_t,
                               std::uint16_t,
                               mcal::reg::pllcr,
                               UINT16_C(0x0F00)>::reg_set();

  // Start the external 12Mhz oscillator
  // SYSTEM.MOSCCR.BYTE = 0x00u;
  mcal::reg::reg_access_static<std::uint32_t,
                               std::uint8_t,
                               mcal::reg::mosccr,
                               UINT8_C(0x00)>::reg_set();

  // Switch on the PLL.
  // SYSTEM.PLLCR2.BYTE = 0x00u;
  mcal::reg::reg_access_static<std::uint32_t,
                               std::uint8_t,
                               mcal::reg::pllcr2,
                               UINT8_C(0x00)>::reg_set();

  // Wait for at least 12ms (~2075op/s at 125KHz).
  // Execute a delay loop 210 times. The delay loop has 10 operations:
  // one subtraction, one branching-comparison, and eight no-operations.
  for(std::uint_fast16_t i = UINT16_C(0); i < UINT16_C(210); ++i)
  {
    mcal::cpu::nop(); mcal::cpu::nop(); mcal::cpu::nop(); mcal::cpu::nop();
    mcal::cpu::nop(); mcal::cpu::nop(); mcal::cpu::nop(); mcal::cpu::nop();
  }

  // Configure the clocks as follows -
  // Clock Description              Frequency
  // ----------------------------------------
  // PLL Clock frequency...............192MHz
  // System Clock Frequency.............96MHz
  // Peripheral Module Clock B..........48MHz
  // FlashIF Clock......................48MHz
  // External Bus Clock.................48MHz
  // SYSTEM.SCKCR.LONG = 0x21821211u;
  mcal::reg::reg_access_static<std::uint32_t,
                               std::uint32_t,
                               mcal::reg::sckcr,
                               UINT32_C(0x21821211)>::reg_set();

  // Configure the clocks as follows -
  // Clock Description              Frequency
  // ----------------------------------------
  // USB Clock..........................48MHz
  // IEBus Clock........................24MHz
  // SYSTEM.SCKCR2.WORD = 0x0033u;
  mcal::reg::reg_access_static<std::uint32_t,
                               std::uint16_t,
                               mcal::reg::sckcr2,
                               UINT16_C(0x0033)>::reg_set();

  // Set the clock source to PLL
  // SYSTEM.SCKCR3.WORD = 0x0400u;
  mcal::reg::reg_access_static<std::uint32_t,
                               std::uint16_t,
                               mcal::reg::sckcr3,
                               UINT16_C(0x0400)>::reg_set();

  // Protection on
  // SYSTEM.PRCR.WORD = 0xA500u;
  mcal::reg::reg_access_static<std::uint32_t,
                               std::uint16_t,
                               mcal::reg::prcr,
                               UINT16_C(0xA500)>::reg_set();
}
