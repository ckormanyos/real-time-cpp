///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2025.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <mcal_port.h>
#include <mcal_reg.h>

extern "C"
{
  void mcal_port_init();

  void mcal_port_init()
  {
    // Set all gpio to output low.

    // GPIO->ENABLE_W1TS.reg = 0xFFFFFFFF;
    // GPIO->ENABLE1_W1TS.reg = 0xFFFFFFFF;
    // GPIO->OUT.reg   = 0;
    // GPIO->OUT1.reg  = 0;
    mcal::reg::reg_access_static<std::uint32_t, std::uint32_t, mcal::reg::gpio::enable_w1ts,  static_cast<std::uint32_t>(UINT32_C(0xFFFFFFFF))>::reg_set();
    mcal::reg::reg_access_static<std::uint32_t, std::uint32_t, mcal::reg::gpio::enable1_w1ts, static_cast<std::uint32_t>(UINT32_C(0xFFFFFFFF))>::reg_set();
    mcal::reg::reg_access_static<std::uint32_t, std::uint32_t, mcal::reg::gpio::out,          static_cast<std::uint32_t>(UINT32_C(0x00000000))>::reg_set();
    mcal::reg::reg_access_static<std::uint32_t, std::uint32_t, mcal::reg::gpio::out1,         static_cast<std::uint32_t>(UINT32_C(0x00000000))>::reg_set();
  }
}

void mcal::port::init(const config_type*)
{
}
