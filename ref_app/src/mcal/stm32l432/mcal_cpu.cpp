///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2024.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <mcal_cpu.h>
#include <mcal_osc.h>
#include <mcal_port.h>
#include <mcal_reg.h>
#include <mcal_wdg.h>

#include <Mcal/Reg.h>

extern "C"
void SystemInit(void);

extern "C"
void SystemInit(void)
{
  /* Set coprocessor access control register CP10 and CP11 Full Access (Enable floating point unit) */
  SCB_CPACR |= (uint32_t)((uint32_t)(3UL << 20U) | (uint32_t)(3UL << 22U));

  /* Reset HSEON, CSSON, HSEBYP and PLLON bits */
  RCC_CR &= (uint32_t)((~(1UL << 16)) | (~(1UL << 18))) | (~(1UL << 19)) | (~(1UL << 24));

  /* Reset CFGR register */
  RCC_CFGR = (uint32_t)0x40000000UL;

  /* Reset PLLCFGR register */
  RCC_PLLCFGR = (uint32_t)0x00001000UL;

  /* Disable all interrupts */
  RCC_CIER = (uint32_t)0x00000000UL;

  /* Configure Flash prefetch, Instruction cache, Data cache and wait state (3 wait states) */
  FLASH_ACR = (uint32_t)((1UL << 9) | (1UL << 10) | (3UL << 0));
}

auto mcal::cpu::init() -> void
{
  ::SystemInit();

  mcal::wdg::init(nullptr);
  mcal::port::init(nullptr);
  mcal::osc::init(nullptr);
}
