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

namespace int_vect
{
  std::uint32_t get_the_address_of_the_nmi_interrupt_table();
}

namespace mcal
{
  namespace cpu
  {
    namespace detail
    {
      void initialize_the_neon_coprocessor_and_the_vfp();
      void enable_the_level_1_instruction_cache();
      void enable_the_level_1_data_cache();
      void load_the_address_of_the_nmi_interrupt_table();
    }
  }
} // namespace mcal::cpu::detail


void mcal::cpu::detail::initialize_the_neon_coprocessor_and_the_vfp()
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

void mcal::cpu::detail::enable_the_level_1_instruction_cache()
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

void mcal::cpu::detail::enable_the_level_1_data_cache()
{
  // TBD: Enable the level 1 data cache.
}

void mcal::cpu::detail::load_the_address_of_the_nmi_interrupt_table()
{
  // Load the address of the nmi interrupt table.
  const std::uint32_t the_address = int_vect::get_the_address_of_the_nmi_interrupt_table();

  asm volatile("mcr p15, #0, %[value], c12, c0, 0" :: [value] "r" (the_address));
}

void mcal::cpu::init()
{
  detail::initialize_the_neon_coprocessor_and_the_vfp();

  detail::enable_the_level_1_instruction_cache();

  // TBD: Enabling the level 1 data chache is not yet implemented.
  detail::enable_the_level_1_data_cache();

  detail::load_the_address_of_the_nmi_interrupt_table();

  // Disable OPP50 operation and enable OPP100 operation.
  // Use the ratio for 24MHz to 32KHz division.
  // See Chapter 9.3.8 in the am335x manual.
  mcal::reg::access<std::uint32_t,
                    std::uint32_t,
                    mcal::reg::control::clk32kdivratio_ctrl,
                    UINT32_C(0x00000000)>::reg_set();

  mcal::wdg::init (nullptr);
  mcal::port::init(nullptr);
  mcal::osc::init (nullptr);
}
