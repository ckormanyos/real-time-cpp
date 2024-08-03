///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2011 - 2024.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <mcal_osc.h>

#include <Mcal/Reg.h>

extern "C"
void SetSysClock(void);

extern "C"
void SetSysClock(void)
{
  /* Set HSION (HSI16 clock enable) enable bit */
  RCC_CR |= (uint32_t)(1UL << 8U);

  /* wait until HSI16 clock is ready */
  while (!(RCC_CR & (uint32_t)(1UL << 10UL)))
  {
    __asm volatile("nop");
  }

  /* PWREN: Power interface clock enable */
  RCC_APB1ENR1 |= (uint32_t)(1UL << 28);

  /* Enable main PLL */
  RCC_CR &= (uint32_t)(~(uint32_t)(1UL << 24));

  /* Wait until main PLL is enabled */
  while (RCC_CR & (uint32_t)(1UL << 25))
  {
    __asm volatile("nop");
  }

  /*  PLL configuration for 80MHz system clock from 16MHz HSI   */
  /*  f(VCO clock) = 16MHz * (40 / 4) = 160MHz                  */
  /*  f(System Clock) = f(VCO clock) / PLLR = 80MHz             */

  RCC_PLLCFGR = (uint32_t)((2UL << 0U)    /* Set PLL source to HSI */
                         | (3UL << 4U)    /* Set PLLM to 4         */
                         | (40UL << 8U)   /* Set PLLN to 40        */
                         | (0UL << 25U)); /* Set PLLR to 2         */

  /* Enable Main PLLCLK output for the system clock */
  RCC_PLLCFGR |= (uint32_t)(1UL << 24);

  /* Enable main PLL */
  RCC_CR |= (uint32_t)(1UL << 24);

  /* Wait until main PLL is enabled */
  while (!(RCC_CR & (uint32_t)(1UL << 25)))
  {
    __asm volatile("nop");
  }

  /* Select PLL as system clock source */
  RCC_CFGR &= (uint32_t)(~(3UL << 0));
  RCC_CFGR |= (uint32_t)(3UL << 0U);

  /* Wait till the main PLL is used as system clock source */
  while ((RCC_CFGR & (uint32_t)(0x0CU << 0)) != (0x0CU << 0))
  {
    __asm volatile("nop");
  }
}

void mcal::osc::init(const config_type*)
{
  :: SetSysClock();
}
