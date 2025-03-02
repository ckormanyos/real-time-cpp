///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2011 - 2025.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <mcal_osc.h>
#include <mcal_reg.h>

void mcal::osc::init(const config_type*)
{
  // Set the core clock to 240 MHz and APB clock to 80 MHz.

  // SYSTEM->CPU_PERI_CLK_EN.reg = 7;
  mcal::reg::reg_access_static<std::uint32_t, std::uint32_t, mcal::reg::system::cpu_peri_clk_en, static_cast<std::uint32_t>(UINT32_C(7))>::reg_set();

  //SYSTEM->SYSCLK_CONF.reg = 0x401;
  mcal::reg::reg_access_static<std::uint32_t, std::uint32_t, mcal::reg::system::sysclk_conf, static_cast<std::uint32_t>(UINT32_C(0x00000401))>::reg_set();
}
