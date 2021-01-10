///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2018.
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
  volatile std::uint8_t* p_mclkctrla = (volatile std::uint8_t*) mcal::reg::reg_mclkctrla;
  volatile std::uint8_t* p_mclkctrlb = (volatile std::uint8_t*) mcal::reg::reg_mclkctrlb;
  volatile std::uint8_t* p_mclklock  = (volatile std::uint8_t*) mcal::reg::reg_mclklock;
  volatile std::uint8_t* p_ccp       = (volatile std::uint8_t*) mcal::reg::reg_ccp;

  *p_ccp        = 0xD8U;
  *p_mclklock  &= (std::uint8_t) ~1U;

  *p_ccp        = 0xD8U;
  *p_mclkctrla  = 0x00U;

  *p_ccp        = 0xD8U;
  *p_mclkctrlb  = 0x00U;

  mcal::wdg::init(nullptr);
  mcal::port::init(nullptr);
  mcal::osc::init(nullptr);
}
