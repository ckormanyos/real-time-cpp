///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2025.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <mcal_cpu.h>
#include <mcal_osc.h>
#include <mcal_port.h>
#include <mcal_reg.h>
#include <mcal_wdg.h>

auto mcal::cpu::init() -> void
{
  // Disable all interrupts and clear pending bits.
  mcal::reg::reg_access_static<std::uint32_t, std::uint32_t, mcal::reg::rcc_cir, 0x009F0000UL>::reg_set();

  // Reset the cfgr2 register.
  mcal::reg::reg_access_static<std::uint32_t, std::uint32_t, mcal::reg::rcc_cfgr2, 0x00000000UL>::reg_set();

  // Relocate the vector table to internal flash.
  mcal::reg::reg_access_static<std::uint32_t, std::uint32_t, mcal::reg::scb_vtor, 0x08000000UL>::reg_set();

  mcal::wdg::init(nullptr);
  mcal::port::init(nullptr);
  mcal::osc::init(nullptr);
}
