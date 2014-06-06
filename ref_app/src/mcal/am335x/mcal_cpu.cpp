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

namespace mcal
{
  namespace cpu
  {
    namespace detail
    {
      struct secure
      {
      private:
        friend void mcal::cpu::init();

        static void initialize_the_neon_coprocessor_and_the_vfp();

        static void enable_the_level_1_instruction_cache();

        static void enable_the_level_1_data_cache();
      };
    }
  }
} // namespace mcal::cpu::detail


void mcal::cpu::detail::secure::initialize_the_neon_coprocessor_and_the_vfp()
{
  // Initialize the neon coprocessor and the vfp.
  asm volatile("push {r1}");
  asm volatile("mrc p15, #0, r1, c1, c0, #2");
  asm volatile("orr r1, r1, #0x00F00000");
  asm volatile("mcr p15, #0, r1, c1, c0, #2");

  asm volatile("mov r1, #0");
  asm volatile("mcr p15, #0, r1, c7, c5, #4"); // Flush the prefetch buffer because of fmxr below
                                                // and because cp10 and cp11 were only just enabled.
  asm volatile("mov r1, #0x40000000");         // Enable the vfp.
  asm volatile("fmxr fpexc, r1");
  asm volatile("pop {r1}");

  /*
  // Initialize the neon coprocessor and the vfp.
  asm volatile("push {r1}");
  asm volatile("mrc p15, #0, r3, c1, c0, #2"); // Read the cpacr.
  asm volatile("orr r3, r3, #0x00F00000");     // Enable the vfp via setting cp10 and cp11.
  asm volatile("mcr p15, #0, r3, c1, c0, #2"); // Write the cpacr.

  // Enable the neon coprocessor and the vfp.
  asm volatile("mov r0, #0x40000000");
  asm volatile("vmsr fpexc, r1");              // Enable the floating-point exception register.
  asm volatile("vmrs r1, fpsid");
  asm volatile("pop {r1}");
  */
}

void mcal::cpu::detail::secure::enable_the_level_1_instruction_cache()
{
  // Enable the level 1 instruction cache.
  asm volatile("push {r1}");
  asm volatile("mrc p15, #0, r1, c1, c0, #0");
  asm volatile("orr r1, r1, #0x1000");         // Enable the ICache.
  asm volatile("mcr p15, #0, r1, c1, c0, #0");
  asm volatile("mov r1, #0");
  asm volatile("mcr p15, #0, r1, c7, c5, #0"); // Invalidate (flush) the entire instruction cache.
  asm volatile("isb");                         // Flush the processor pipeline.
  asm volatile("pop {r1}");
}

void mcal::cpu::detail::secure::enable_the_level_1_data_cache()
{
  // TBD: Enable the level 1 data cache.
}

void mcal::cpu::init()
{
  detail::secure::initialize_the_neon_coprocessor_and_the_vfp();

  detail::secure::enable_the_level_1_instruction_cache();

  // TBD: Enabling the level 1 data chache is not yet implemented.
  detail::secure::enable_the_level_1_data_cache();

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
