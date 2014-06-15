///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2014.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

// This file implements helper functions for initializing
// the ARM(R) A8 for bare-metal Beagle Bone applications.

#include <cstdint>
#include <mcal_cpu_detail.h>

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
      constexpr std::uint32_t tlb_base_address = UINT32_C(0x4030C000);
    }
  }
}

void mcal::cpu::detail::initialize_the_neon_coprocessor_and_the_vfp()
{
  asm volatile("mrc p15, #0, r1, c1, c0, #2");
  asm volatile("orr r1, r1, #0x00F00000");
  asm volatile("mcr p15, #0, r1, c1, c0, #2");
  asm volatile("isb");
  asm volatile("mov r1, #0x40000000");
  asm volatile("vmsr fpexc, r1");
}

void mcal::cpu::detail::invalidate_the_caches()
{
  // There are no contents here because the ARMv7 core
  // does not need to flush and invalidate the caches
  // prior to using them.
}

void mcal::cpu::detail::clear_the_branch_prediction_array()
{
  asm volatile("mov r1, #0x0");
  asm volatile("mcr p15, #0, r1, c7, c5, #6");
}

void mcal::cpu::detail::invalidate_the_tlb()
{
  asm volatile("mov r1, #0x0");
  asm volatile("mcr p15, #0, r1, c3, c0, #0");
}

void mcal::cpu::detail::setup_the_domain_access_control()
{
  asm volatile("mov r1, #0x3");
  asm volatile("mcr p15, #0, r1, c3, c0, #0");
}

void mcal::cpu::detail::fill_the_tlb()
{
  volatile std::uint32_t* pointer_to_tlb_base = reinterpret_cast<volatile std::uint32_t*>(tlb_base_address);

  // Set every memory block to be of type "strongly ordered memory",
  // which means there is no data caching.
  
  // The single memory block used by the bare-metal BeagleBone
  // application will be set for data caching below.

  for(std::uint32_t tlb_index = UINT32_C(0); tlb_index < UINT32_C(4096); ++tlb_index)
  {
    const std::uint32_t this_tlb_value = static_cast<std::uint32_t>(UINT32_C(0x00000C02) | static_cast<std::uint32_t>(tlb_index << 20));

    pointer_to_tlb_base[tlb_index] = this_tlb_value;
  }

  // (Re)-Set the index of the single memory block used by
  // the bare-metal BeagleBone application to be of type
  // "cacheable memory".

  // This memory block contains all of the code, the data,
  // and the stack in the bare-metal BeagleBone application.
  // This is the 1MB memory block that resides at 0x40200000.

  pointer_to_tlb_base[0x402U] = static_cast<std::uint32_t>(UINT32_C(0x00004C06) | static_cast<std::uint32_t>(UINT32_C(0x402) << 20));

  // Insert an instruction barrier.
  asm volatile("dsb");
}

void mcal::cpu::detail::set_the_tlb_base_address()
{
  const volatile std::uint32_t the_address = tlb_base_address;

  asm volatile("mcr p15, #0, %[value], c2, c0, #0" : : [value] "r" (the_address));

  static_cast<void>(the_address);
}

void mcal::cpu::detail::enable_the_mmu()
{
  asm volatile("mrc p15, #0, r1, c1, c0, #0");
  asm volatile("orr r1, r1, #0x1");
  asm volatile("mcr p15, #0, r1, c1, c0, #0");
}

void mcal::cpu::detail::enable_branch_prediction()
{
  asm volatile("mrc p15, #0, r1, c1, c0, #0");
  asm volatile("orr r1, r1, #0x0800");
  asm volatile("mcr p15, #0,r1, c1, c0, #0");
}

void mcal::cpu::detail::enable_the_caches()
{
  asm volatile("mrc p15, #0, r1, c1, c0, #0");
  asm volatile("orr r1,  r1, #0x0004");        // Bit  2: data cache.
  asm volatile("orr r1,  r1, #0x1000");        // Bit 12: instruction cache.
  asm volatile("mcr p15, #0, r1, c1, c0, #0");
}

void mcal::cpu::detail::load_the_address_of_the_nmi_interrupt_table()
{
  const volatile std::uint32_t the_address = int_vect::get_the_address_of_the_nmi_interrupt_table();

  asm volatile("mcr p15, #0, %[value], c12, c0, #0" : : [value] "r" (the_address));
}

void mcal::cpu::detail::switch_to_user_mode()
{
  asm volatile("mrs r1, cpsr");
  asm volatile("bic r1, #0x0F");
  asm volatile("orr r1, #0x10");
  asm volatile("msr cpsr, r1");
}
