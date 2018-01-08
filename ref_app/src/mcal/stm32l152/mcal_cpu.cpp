///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2018.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <mcal_cpu.h>
#include <mcal_osc.h>
#include <mcal_port.h>
#include <mcal_reg_access.h>
#include <mcal_wdg.h>

void mcal::cpu::init()
{
  // Set the msion bit in the control register.
  mcal::reg::access<std::uint32_t, std::uint32_t, mcal::reg::rcc_cr, 0x00000100UL>::reg_or();

  // Prepare the configuration register.
  mcal::reg::access<std::uint32_t, std::uint32_t, mcal::reg::rcc_cfgr, 0x88FFC00CUL>::reg_and();

  // Prepare some clock bits.
  mcal::reg::access<std::uint32_t, std::uint32_t, mcal::reg::rcc_cr, 0xEEFEFFFEUL>::reg_and();

  // Prepare some more clock bits.
  mcal::reg::access<std::uint32_t, std::uint32_t, mcal::reg::rcc_cr, 0xFFFBFFFFUL>::reg_and();

  // Prepare some clock/pll bits.
  mcal::reg::access<std::uint32_t, std::uint32_t, mcal::reg::rcc_cfgr, 0xFF02FFFFUL>::reg_and();

  // Disable all interrupts and clear pending bits.
  mcal::reg::access<std::uint32_t, std::uint32_t, mcal::reg::rcc_cir, 0x00000000UL>::reg_set();

  // Relocate the vector table to internal flash.
  mcal::reg::access<std::uint32_t, std::uint32_t, mcal::reg::scb_vtor, 0x08000000UL>::reg_set();

  mcal::wdg::init(nullptr);
  mcal::port::init(nullptr);
  mcal::osc::init(nullptr);
}
