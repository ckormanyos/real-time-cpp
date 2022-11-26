///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2022.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <mcal_cpu.h>
#include <mcal_osc.h>
#include <mcal_port.h>
#include <mcal_reg.h>
#include <mcal_wdg.h>
#include <Cache.h>

void mcal::cpu::init()
{
  // Configure the flash wait states (280 MHz --> 6 WS).
  //Flash->ACR.bit.LATENCY = 6u;
  mcal::reg::reg_access_static<std::uint32_t, std::uint32_t, mcal::reg::flash_acr, UINT32_C(6)>::reg_msk<UINT32_C(7)>();

  // Relocate the vector table to internal flash.
  mcal::reg::reg_access_static<std::uint32_t, std::uint32_t, mcal::reg::scb_vtor, UINT32_C(0x08000000)>::reg_set();

  // Initialize the FPU: Enable CP10 and CP11.
  //CPACR |= 0x00F00000UL;
  mcal::reg::reg_access_static<std::uint32_t, std::uint32_t, mcal::reg::scb_cpacr, UINT32_C(0x00F00000)>::reg_or();

  // Enable ITCM and DTCM.
  //ITCMCR |= 1UL;
  //DTCMCR |= 1UL;
  mcal::reg::reg_access_static<std::uint32_t, std::uint32_t, mcal::reg::scb_itcmcr, UINT32_C(1)>::reg_or();
  mcal::reg::reg_access_static<std::uint32_t, std::uint32_t, mcal::reg::scb_dtcmcr, UINT32_C(1)>::reg_or();

  __asm("DSB");
  __asm("ISB");

  mcal::wdg::init(nullptr);
  mcal::port::init(nullptr);
  mcal::osc::init(nullptr);

  // Enable the Cache-I and Cache-D.
  ::Cache_EnableICache();
  ::Cache_EnableDCache();
}
