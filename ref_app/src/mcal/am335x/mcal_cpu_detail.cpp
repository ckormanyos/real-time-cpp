///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2014 - 2020.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

// This file implements helper functions for initializing
// the ARM(R) A8 for bare-metal Beagle Bone applications.

#include <cstdint>
#include <mcal_cpu_detail.h>
#include <mcal_cpu_detail_secure.h>

void mcal::cpu::detail::init()
{
  secure::invalidate_caches            ();
  secure::clear_branch_prediction_array();
  secure::invalidate_tlb               ();
  secure::setup_domain_access_control  ();
  secure::fill_tlb_entries             ();
  secure::enable_mmu                   ();
  secure::enable_branch_prediction     ();
  secure::enable_caches                ();
}

void mcal::cpu::detail::user_mode()
{
  asm volatile("mrs r1, cpsr");
  asm volatile("bic r1, #0x0F");
  asm volatile("orr r1, #0x10");
  asm volatile("msr cpsr, r1");
}
