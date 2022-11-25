///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2022.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <Cache.h>
#include <mcal_cpu.h>
#include <mcal_osc.h>
#include <mcal_port.h>
#include <mcal_reg.h>
#include <mcal_wdg.h>
#include <STM32H7x3.h>

extern "C"
{
  extern unsigned long __INTVECT_BASE_ADDRESS;
}

void mcal::cpu::init()
{
  // Configure the flash wait states (280 MHz --> 6 WS).
  Flash->ACR.bit.LATENCY = 6u;

  // Setup the VTOR.
  SCB->VTOR.reg = (unsigned long)& __INTVECT_BASE_ADDRESS;

  // Initialize the FPU: Enable CP10 and CP11.
  CPACR |= 0x00F00000UL;

  // Enable ITCM and DTCM.
  ITCMCR |= 1UL;
  DTCMCR |= 1UL;

  __asm("DSB");
  __asm("ISB");

  mcal::wdg::init(nullptr);
  mcal::port::init(nullptr);
  mcal::osc::init(nullptr);
}

void mcal::cpu::post_init()
{
  // Enable the Cache-I and Cache-D.
  Cache_EnableICache();
  Cache_EnableDCache();
}
