///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2018 - 2023.
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
  // Set main clock prescaler (uses protect protected I/O registers).

  // CCP = static_cast<std::uint8_t>(UINT8_C(0xD8));
  mcal::reg::reg_access_static<std::uint8_t,
                               std::uint8_t,
                               mcal::reg::sys_ccp,
                               static_cast<std::uint8_t>(UINT8_C(0xD8))>::reg_set();

  // MCLKLOCK &= static_cast<std::uint8_t>(~1U);
  mcal::reg::reg_access_static<std::uint8_t,
                               std::uint8_t,
                               mcal::reg::clk_mclklock,
                               static_cast<std::uint8_t>(~1U)>::reg_and();

  // CCP = static_cast<std::uint8_t>(UINT8_C(0xD8));
  mcal::reg::reg_access_static<std::uint8_t,
                               std::uint8_t,
                               mcal::reg::sys_ccp,
                               static_cast<std::uint8_t>(UINT8_C(0xD8))>::reg_set();

  // MCLKCTRLA = static_cast<std::uint8_t>(UINT8_C(0x00));
  mcal::reg::reg_access_static<std::uint8_t,
                               std::uint8_t,
                               mcal::reg::clk_mclkctrla,
                               static_cast<std::uint8_t>(UINT8_C(0x00))>::reg_set();

  // CCP = static_cast<std::uint8_t>(UINT8_C(0xD8));
  mcal::reg::reg_access_static<std::uint8_t,
                               std::uint8_t,
                               mcal::reg::sys_ccp,
                               static_cast<std::uint8_t>(UINT8_C(0xD8))>::reg_set();

  // MCLKCTRLB = static_cast<std::uint8_t>(UINT8_C(0x00));
  mcal::reg::reg_access_static<std::uint8_t,
                               std::uint8_t,
                               mcal::reg::clk_mclkctrlb,
                               static_cast<std::uint8_t>(UINT8_C(0x00))>::reg_set();

  mcal::wdg::init(nullptr);
  mcal::port::init(nullptr);
  mcal::osc::init(nullptr);
}
