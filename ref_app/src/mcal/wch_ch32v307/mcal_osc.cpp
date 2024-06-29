///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2022 - 2024.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <mcal_osc.h>
#include <mcal_reg.h>

#include <cstdint>

void mcal::osc::init(const config_type*)
{
  // Enable the HSE clock.
  // RCC->CTLR.bit.HSEON = 1u;
  mcal::reg::reg_access_static<std::uint32_t, std::uint32_t, mcal::reg::rcc_ctlr, static_cast<std::uint32_t>(UINT8_C(16))>::bit_set();

  // Wait for the HSE to be ready.
  // while(!(RCC->CTLR.bit.HSERDY));
  while(!mcal::reg::reg_access_static<std::uint32_t, std::uint32_t, mcal::reg::rcc_ctlr, static_cast<std::uint32_t>(UINT8_C(17))>::bit_get());

  // Configure the PLL.

  // PREDIV1 clock source is HSE.
  // RCC->CFGR2.bit.PREDIV1SRC = 0u;
  mcal::reg::reg_access_static<std::uint32_t, std::uint32_t, mcal::reg::rcc_cfgr2, static_cast<std::uint32_t>(UINT8_C(16))>::bit_clr();

  // PREDIV1 output is 8 MHz / 1.
  // RCC->CFGR2.bit.PREDIV1 = 0u;
  mcal::reg::reg_access_static<std::uint32_t,
                               std::uint32_t,
                               mcal::reg::rcc_cfgr2,
                               UINT32_C(0)>::template reg_msk<UINT32_C(0xF)>();

  // PLL entry clock source is HSE.
  // RCC->CFGR0.bit.PLLSRC = 1u;
  mcal::reg::reg_access_static<std::uint32_t, std::uint32_t, mcal::reg::rcc_cfgr0, static_cast<std::uint32_t>(UINT8_C(16))>::bit_set();

  // PLLCLK = 8MHz * 18 = 144 MHz.
  // RCC->CFGR0.bit.PLLMUL = 0u;
  mcal::reg::reg_access_static<std::uint32_t,
                               std::uint32_t,
                               mcal::reg::rcc_cfgr0,
                               UINT32_C(0)>::template reg_msk<UINT32_C(0xF) << 18U>();

  // HSE clock not divided for PLL entry.
  // RCC->CFGR0.bit.PLLXTPRE   = 0u;
  mcal::reg::reg_access_static<std::uint32_t, std::uint32_t, mcal::reg::rcc_cfgr0, static_cast<std::uint32_t>(UINT8_C(17))>::bit_clr();

  // Configure the internal bus clocks.

  // AHB = PLLCLK = 144 MHz.
  // RCC->CFGR0.bit.HPRE  = 0u;
  mcal::reg::reg_access_static<std::uint32_t,
                               std::uint32_t,
                               mcal::reg::rcc_cfgr0,
                               UINT32_C(0)>::template reg_msk<UINT32_C(0xF) << 4U>();

  // APB1 = AHB / 2 = 72 MHz.
  // RCC->CFGR0.bit.PPRE1 = 4u;
  mcal::reg::reg_access_static<std::uint32_t,
                               std::uint32_t,
                               mcal::reg::rcc_cfgr0,
                               UINT32_C(4)>::template reg_msk<UINT32_C(0x7) << 8U>();

  // APB2 = AHB = 144 MHz.
  // RCC->CFGR0.bit.PPRE2 = 0u;
  mcal::reg::reg_access_static<std::uint32_t,
                               std::uint32_t,
                               mcal::reg::rcc_cfgr0,
                               UINT32_C(0)>::template reg_msk<UINT32_C(0x7) << 13U>();

  // Enable the PLL (144 MHz).
  // RCC->CTLR.bit.PLLON = 1u;
  // while(!(RCC->CTLR.bit.PLLRDY));
  mcal::reg::reg_access_static<std::uint32_t, std::uint32_t, mcal::reg::rcc_ctlr, static_cast<std::uint32_t>(UINT8_C(24))>::bit_set();
  while(!mcal::reg::reg_access_static<std::uint32_t, std::uint32_t, mcal::reg::rcc_ctlr, static_cast<std::uint32_t>(UINT8_C(25))>::bit_get());

  // Set the PLL as the system clock.
  // RCC->CFGR0.bit.SW = 2u;
  // while(RCC->CFGR0.bit.SWS != 2u);
  mcal::reg::reg_access_static<std::uint32_t,
                               std::uint32_t,
                               mcal::reg::rcc_cfgr0,
                               UINT32_C(2)>::template reg_msk<UINT32_C(0x3) << 0U>();

  while(((mcal::reg::reg_access_static<std::uint32_t, std::uint32_t, mcal::reg::rcc_cfgr0>::reg_get() >> 2U) & 0x3U) != 2U);
}
