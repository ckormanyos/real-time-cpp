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
  // Initialize the NEON coprocessor and the VFP.
  asm volatile("mrc p15, #0, r3, c1, c0, #2"); // Read the cpacr.
  asm volatile("orr r3, r3, #0x00F00000");     // Enable the FPU via setting cp10 and cp11.
  asm volatile("mcr p15, #0, r3, c1, c0, #2"); // Write the cpacr.
  asm volatile("isb");                         // Perform an instruction memory barrier (IMB/ISB) sequence .

  // Enable the NEON coprocessor and the VFP.
  asm volatile("mov r0, #0x40000000");
  asm volatile("vmsr fpexc, r0");              // Enable the floating-point exception register.
  asm volatile("vmrs r1, fpsid");
  asm volatile("isb");                         // Perform an instruction memory barrier (IMB/ISB) sequence .

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
