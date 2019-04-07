///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2011 - 2018.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <cstdint>

#include <mcal_cpu.h>
#include <mcal_osc.h>
#include <mcal_reg.h>

void mcal::osc::init(const config_type*)
{
  // Configure the system clock for 32MHz using
  // the (HSI) high-speed internal oscillator.

  // Disable the PLL.
  mcal::reg::reg_access_static<std::uint32_t,
                               std::uint32_t,
                               mcal::reg::rcc_cr,
                               24U>::bit_clr();

  // Wait until the PLL is disabled.
  while(mcal::reg::reg_access_static<std::uint32_t,
                                     std::uint32_t,
                                     mcal::reg::rcc_cr,
                                     UINT32_C(25)>::bit_get() == true)
  {
    mcal::cpu::nop();
  }

  // Set PLLDIV to divide by 3.
  mcal::reg::reg_access_static<std::uint32_t,
                               std::uint32_t,
                               mcal::reg::rcc_cfgr,
                               23U>::bit_set();

  // Set PLLMUL to multiply by 6.
  mcal::reg::reg_access_static<std::uint32_t,
                               std::uint32_t,
                               mcal::reg::rcc_cfgr,
                               19U>::bit_set();

  // Enable the HSI (high-speed internal clock).
  mcal::reg::reg_access_static<std::uint32_t,
                               std::uint32_t,
                               mcal::reg::rcc_cr,
                               0U>::bit_set();

  // Wait until the HSI is ready.
  // Read the HSIRDY bit.
  while(mcal::reg::reg_access_static<std::uint32_t,
                                     std::uint32_t,
                                     mcal::reg::rcc_cr,
                                     UINT32_C(1)>::bit_get() == false)
  {
    mcal::cpu::nop();
  }

  // Use internal RC clock as input for the PLL.
  mcal::reg::reg_access_static<std::uint32_t,
                               std::uint32_t,
                               mcal::reg::rcc_cfgr,
                               16U>::bit_clr();

  // Use the PLL as the system clock.
  mcal::reg::reg_access_static<std::uint32_t,
                               std::uint32_t,
                               mcal::reg::rcc_cfgr,
                               UINT32_C(3)>::reg_or();

  // Enable the PLL.
  mcal::reg::reg_access_static<std::uint32_t,
                               std::uint32_t,
                               mcal::reg::rcc_cr,
                               24U>::bit_set();
}
