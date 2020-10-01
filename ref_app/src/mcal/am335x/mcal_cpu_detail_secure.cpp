///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2014.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

// This file implements helper functions for initializing
// the ARM(R) A8 for bare-metal Beagle Bone applications.

#include <algorithm>
#include <cstdint>
#include <mcal_cpu_detail_secure.h>

void mcal::cpu::detail::secure::initialize_vfp_unit()
{
  asm volatile("mrc p15, #0, r1, c1, c0, #2");
  asm volatile("orr r1, r1, #0x00F00000");
  asm volatile("mcr p15, #0, r1, c1, c0, #2");
  asm volatile("isb");
  asm volatile("mov r1, #0x40000000");
  asm volatile("vmsr fpexc, r1");
}

void mcal::cpu::detail::secure::invalidate_caches()
{
  // There are no contents here because the ARMv7 core
  // does not need to flush and invalidate the caches
  // prior to using them.
}

void mcal::cpu::detail::secure::clear_branch_prediction_array()
{
  asm volatile("mov r1, #0x0");
  asm volatile("mcr p15, #0, r1, c7, c5, #6");
}

void mcal::cpu::detail::secure::invalidate_tlb()
{
  asm volatile("mov r1, #0x0");
  asm volatile("mcr p15, #0, r1, c3, c0, #0");
}

void mcal::cpu::detail::secure::setup_domain_access_control()
{
  asm volatile("mov r1, #0x3");
  asm volatile("mcr p15, #0, r1, c3, c0, #0");
}

void mcal::cpu::detail::secure::fill_tlb_entries()
{
  volatile std::uint32_t* pointer_to_tlb_base = reinterpret_cast<volatile std::uint32_t*>(tlb_base_address);

  // Initialize every memory block to be of type "strongly ordered memory",
  // which means there is no data caching. Set the actual data caching below.

  {
    std::uint_fast16_t tlb_index = UINT16_C(0);

    std::for_each(pointer_to_tlb_base,
                  pointer_to_tlb_base + static_cast<std::size_t>(4096U),
                  [&tlb_index](volatile std::uint32_t& tlb_entry)
                  {
                    tlb_entry = static_cast<std::uint32_t>(UINT32_C(0x00000C02) | static_cast<std::uint32_t>(tlb_index << 20));

                    ++tlb_index;
                  });
  }

  // (Re)-Set the tlb entry of the single memory block used by
  // the bare-metal BeagleBone application to be of type
  // "cacheable memory".

  // This memory block contains all of the code, the data,
  // and the stack in the bare-metal BeagleBone application.
  // This is the 1MB memory block that resides at 0x40200000.

  *(pointer_to_tlb_base + static_cast<std::size_t>(0x402U)) = static_cast<std::uint32_t>(UINT32_C(0x00004C06) | static_cast<std::uint32_t>(UINT32_C(0x402) << 20));

  // Insert an instruction barrier.
  asm volatile("dsb");
}

void mcal::cpu::detail::secure::set_tlb_base_address()
{
  const volatile std::uint32_t the_address = tlb_base_address;

  asm volatile("mcr p15, #0, %[value], c2, c0, #0" : : [value] "r" (the_address));

  static_cast<void>(the_address);
}

void mcal::cpu::detail::secure::enable_mmu()
{
  asm volatile("mrc p15, #0, r1, c1, c0, #0");
  asm volatile("orr r1, r1, #0x1");
  asm volatile("mcr p15, #0, r1, c1, c0, #0");
}

void mcal::cpu::detail::secure::enable_branch_prediction()
{
  asm volatile("mrc p15, #0, r1, c1, c0, #0");
  asm volatile("orr r1, r1, #0x0800");
  asm volatile("mcr p15, #0,r1, c1, c0, #0");
}

void mcal::cpu::detail::secure::enable_caches()
{
  // Here we have:
  // * bit  2 = data cache
  // * bit 12 = instruction cache

  asm volatile("mrc p15, #0, r1, c1, c0, #0");
  asm volatile("orr r1, r1, #0x0004");
  asm volatile("orr r1, r1, #0x1000");
  asm volatile("mcr p15, #0, r1, c1, c0, #0");
}
