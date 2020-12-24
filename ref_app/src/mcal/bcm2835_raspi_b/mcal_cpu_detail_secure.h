///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2013 - 2020.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef MCAL_CPU_DETAIL_SECURE_2020_08_26_H_
  #define MCAL_CPU_DETAIL_SECURE_2020_08_26_H_

  #include <cstdint>

  #include <mcal_reg.h>

  extern "C" void mcal_cpu_detail_secure_start_mmu(uint32_t tlb_base, uint32_t mmu_flags);

  namespace mcal { namespace cpu { namespace detail {

  void init();

  constexpr std::uint32_t tlb_base_address = UINT32_C(0x00004000);

  class secure final
  {
    static void initialize_vfp_unit()
    {
      asm volatile("mrc p15, 0, r1, c1, c1, 2");
      asm volatile("ldr r0, =0x00000C00");
      asm volatile("orr r1, r0");
      asm volatile("mcr p15, 0, r1, c1, c1, 2");

      asm volatile("mrc p15, 0, r1, c1, c0, 2");
      asm volatile("ldr r0, =0x00F00000");
      asm volatile("orr r1, r0");
      asm volatile("mcr p15, 0, r1, c1, c0, 2");

      asm volatile("mov r0, #0");
      asm volatile("mcr p15, 0, r0, c7, c10, 5");

      asm volatile("ldr r0, =#0x40000000");
      asm volatile("vmsr fpexc,r0");
    }

    static void invalidate_caches()
    {
    }

    static void clear_branch_prediction_array()
    {
      asm volatile("mov r1, #0x0");
      asm volatile("mcr p15, #0, r1, c7, c5, #6");
    }

    static void invalidate_tlb()
    {
      asm volatile("mov r2,#0");
      asm volatile("mcr p15,0,r2,c8,c7,0");   // Invalidate tlb.
      asm volatile("mcr p15,0,r2,c7,c10,5");  // Barrier instruction.
    }

    static void setup_domain_access_control()
    {
    }

    static void fill_tlb_entries()
    {
      // Clear the TLB (in case any have been set in,
      // for instance,.the boot loader.
      for(std::uint32_t ra = UINT32_C(0); ra < UINT32_C(0x02000000); ra += UINT32_C(0x00100000))
      {
        (void) set_mmu_section(ra, ra, UINT32_C(0x0000));
      }

      // See Table 6.2. TEX field, and C and B bit encodings used in page table formats
      // https://developer.arm.com/documentation/ddi0301/h/memory-management-unit/memory-region-attributes/c-and-b-bit--and-type-extension-field-encodings

      // Cache both instructions as well as data
      // in the first 2 MB of SDRAM.
      (void) set_mmu_section(UINT32_C(0x00000000), UINT32_C(0x00000000), std::uint32_t(0x0000UL | 8UL | 4UL));
      (void) set_mmu_section(UINT32_C(0x00100000), UINT32_C(0x00100000), std::uint32_t(0x0000UL | 8UL | 4UL));

      // Do not cache any peripherals.
      (void) set_mmu_section(mcal::reg::io_base,   mcal::reg::io_base,   UINT32_C(0x0000));
      (void) set_mmu_section(mcal::reg::gpio_base, mcal::reg::gpio_base, UINT32_C(0x0000));
    }

    static void enable_mmu()
    {
      mcal_cpu_detail_secure_start_mmu(tlb_base_address, std::uint32_t(0x00000001UL | 0x1000UL |0x0004UL));
    }

    static void enable_branch_prediction()
    {
      asm volatile("mrc p15, 0, r1, c1, c0, 0");
      asm volatile("ldr r0, =#0x00000800");
      asm volatile("orr r1, r0");
      asm volatile("mcr p15, 0, r1, c1, c0, 0");
    }

    static void enable_caches()
    {
      // Enable the caches, where
      //   (Bit  2 = data cache) and
      //   (Bit 12 = instruction cache).
      asm volatile("mrc p15, 0, r1, c1, c0, 0");
      asm volatile("ldr r0, =#0x00001004");
      asm volatile("orr r1, r0");
      asm volatile("mcr p15, 0, r1, c1, c0, 0");
    }

    static bool set_mmu_section(const std::uint32_t virtual_address,
                                const std::uint32_t physical_address,
                                const std::uint32_t mmu_flags)
    {
      const bool set_is_ok = (std::uint32_t(physical_address % UINT32_C(0x00100000)) == 0U);

      if(set_is_ok)
      {
        const std::uint32_t ra = std::uint32_t(virtual_address >> 20U);

        const std::uint32_t rb = std::uint32_t(tlb_base_address | (ra << 2U));

        const std::uint32_t rc =
          std::uint32_t(  physical_address
                        | std::uint32_t(UINT32_C(0xC00) | std::uint32_t(mmu_flags | UINT32_C(2))));

        mcal::reg::reg_access_dynamic<std::uint32_t, std::uint32_t>::reg_set(rb, rc);
      }

      return set_is_ok;
    }

    friend void init();
  };

  } } } // namespace mcal::cpu::detail

#endif // MCAL_CPU_DETAIL_SECURE_2020_08_26_H_
