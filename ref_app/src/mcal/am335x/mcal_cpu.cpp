///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2013.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <cstdint>
#include <mcal_cpu.h>
#include <mcal_osc.h>
#include <mcal_port.h>
#include <mcal_reg_access.h>
#include <mcal_wdg.h>

void init_interrupts_nmi();

void mcal::cpu::init()
{
/*
  // Initialize the NEON coprocessor and the VFP.
  asm volatile("mrc p15, #0, r3, c1, c0, #2"); // Read the cpacr.
  asm volatile("orr r3, r3, #0x00F00000");     // Enable the FPU via setting cp10 and cp11.
  asm volatile("mcr p15, #0, r3, c1, c0, #2"); // Write the cpacr.

  // Enable the NEON coprocessor and the VFP.
  asm volatile("mov r0, #0x40000000");
  asm volatile("vmsr fpexc, r0");              // Enable the floating-point exception register.
  asm volatile("vmrs r1, fpsid");
*/

  // Initialize the neon coprocessor and the vfp.
  asm volatile("mrc p15, #0, r1, c1, c0, #2");
  asm volatile("orr r1, r1, #(0xF << 20)");
  asm volatile("mcr p15, #0, r1, c1, c0, #2");

  asm volatile("mov r1, #0");
  asm volatile("mcr p15, #0, r1, c7, c5, #4"); // Flush prefetch buffer because of fmxr below
                                               // and because cp10 and cp11 were only just enabled.
  asm volatile("mov r0,#0x40000000");          // Enable the vfp.
  asm volatile("fmxr fpexc, r0");

  // Enable the level 1 instruction cache.
  asm volatile("mrc p15, 0, r1, c1, c0, 0");
  asm volatile("orr r1, r1, #0x1000");         // Enable the ICache.
  asm volatile("mcr p15, 0, r1, c1, c0, 0");
  asm volatile("mov r1, #0");
  asm volatile("mcr p15, 0, r1, c7, c5, 0");   // Invalidate (flush) the entire instruction cache.
  asm volatile("nop" : : : "r1");              // Indicate that r1 has been clobbered.
  asm volatile("isb");                         // Flush the processor pipeline.

/*
  // Populate and enable the tlb.
  asm volatile("ldr r0, tlb_l1_base");
  asm volatile("mcr p15, 0, r0, c2, c0, 0");
  asm volatile("tlb_l1_base:");
  asm volatile(".word 0x402F0000");

  asm volatile("ldr r0, entry402F");
  asm volatile("ldr r1, val402F");
  asm volatile("str r1, [r0]");
  asm volatile("entry402F:");
  asm volatile(".word 0x402F1008");
  asm volatile("val402F:");
  asm volatile(".word 0x402F0C02");

  asm volatile("mov r0, #0x3");
  asm volatile("mcr p15, 0, r0, c3, c0, 0");

  asm volatile("mrc p15, 0, r0, c1, c0, 0");
  asm volatile("orr r0, r0, #0x1");
  asm volatile("mcr p15, 0, r0, c1, c0, 0");
*/

  // Enable the level 1 data cache.
/*
  asm volatile("mrc p15,0,r1,c1,c0,0;");
  asm volatile("orr r1,r1,#0x0002;");          // Enable the DCache.
  asm volatile("mcr p15, 0, r1 ,c1, c0, 0");
  asm volatile("mov r1,#0;");
  asm volatile("mcr p15, 0, r1, c7, c6, 0;");
  asm volatile("mcr p15, 0, r1, c8, c7, 0;");
  asm volatile("dsb");
  asm volatile("nop" : : : "r1", "memory");
*/

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
