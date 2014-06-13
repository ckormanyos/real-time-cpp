///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2013.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <algorithm>
#include <cstdint>
#include <mcal_cpu.h>
#include <mcal_cpu_detail.h>
#include <mcal_osc.h>
#include <mcal_port.h>
#include <mcal_reg_access.h>
#include <mcal_wdg.h>

void mcal::cpu::init()
{
  detail::initialize_the_neon_coprocessor_and_the_vfp();

  detail::invalidate_the_caches();

  detail::clear_the_branch_prediction_array();

  detail::invalidate_the_tlb();

  detail::setup_the_domain_access_control();

  detail::fill_the_tlb();

  detail::set_the_tlb_base_address();

  detail::enable_the_mmu();

  detail::enable_branch_prediction();

  detail::enable_the_caches();

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

void mcal::cpu::init2()
{
  detail::switch_to_user_mode();
}
