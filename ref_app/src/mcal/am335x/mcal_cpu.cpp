///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2013.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <mcal_cpu.h>
#include <mcal_osc.h>
#include <mcal_port.h>
#include <mcal_reg_access.h>
#include <mcal_wdg.h>

void init_interrupts_nmi();

void mcal::cpu::init()
{
  // Copy the system interrupt vector table from ROM to RAM.
  init_interrupts_nmi();

  // Disable OPP50 operation and enable OPP100 operation.
  // Use the ratio for 24MHz to 32KHz division.
  // See Chapter 9.3.8 in the am335x manual.
  mcal::reg::access<std::uint32_t,
                    std::uint32_t,
                    mcal::reg::control::clk32kdivratio_ctrl,
                    UINT32_C(0x00000000)>::reg_set();

  mcal::wdg::init(nullptr);
  mcal::port::init(nullptr);
  mcal::osc::init(nullptr);
}
