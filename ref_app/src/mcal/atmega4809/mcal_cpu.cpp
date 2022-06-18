///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2018 - 2022.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <mcal_cpu.h>
#include <mcal_osc.h>
#include <mcal_port.h>
#include <mcal_reg.h>
#include <mcal_wdg.h>

void mcal::cpu::init()
{
  // Set main clock prescaler (uses protect protected I/O registers).
  auto p_mclkctrla = reinterpret_cast<volatile std::uint8_t*>(mcal::reg::reg_mclkctrla);
  auto p_mclkctrlb = reinterpret_cast<volatile std::uint8_t*>(mcal::reg::reg_mclkctrlb);
  auto p_mclklock  = reinterpret_cast<volatile std::uint8_t*>(mcal::reg::reg_mclklock);
  auto p_ccp       = reinterpret_cast<volatile std::uint8_t*>(mcal::reg::reg_ccp);

  *p_ccp       = UINT8_C(0xD8);
  *p_mclklock  = static_cast<std::uint8_t>(*p_mclklock & static_cast<std::uint8_t>(~1U));

  *p_ccp       = UINT8_C(0xD8);
  *p_mclkctrla = UINT8_C(0x00);

  *p_ccp       = UINT8_C(0xD8);
  *p_mclkctrlb = UINT8_C(0x00);

  mcal::wdg::init(nullptr);
  mcal::port::init(nullptr);
  mcal::osc::init(nullptr);
}
