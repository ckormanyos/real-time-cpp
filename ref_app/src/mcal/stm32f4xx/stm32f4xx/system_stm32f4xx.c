/**
  ******************************************************************************
  * @file    system_stm32f4xx.c
  * @author  MCD Application Team
  * @version V1.0.0
  * @date    11-September-2013
  * @brief   CMSIS Cortex-M4 Device Peripheral Access Layer System Source File.
  *          This file contains the system clock configuration for STM32F4xx devices.
  *
  *          The STM32F401x is configured to run at 84 MHz, following the three
  *          configuration below:
  *            - PLL_SOURCE_HSI                : HSI (~16MHz) used to clock the PLL, and
  *                                              the PLL is used as system clock source.  
  *            - PLL_SOURCE_HSE                : HSE (8MHz) used to clock the PLL, and 
  *                                              the PLL is used as system clock source.
  *            - PLL_SOURCE_HSE_BYPASS         : HSE bypassed with an external clock 
  *                                              (8MHz, coming from ST-Link) used to clock
  *                                              the PLL, and the PLL is used as system
  *                                              clock source.  
  *
  * 1.  This file provides two functions and one global variable to be called from
  *     user application:
  *      - SystemInit(): Setups the system clock (System clock source, PLL Multiplier
  *                      and Divider factors, AHB/APBx prescalers and Flash settings),
  *                      depending on the configuration made in the clock xls tool.
  *                      This function is called at startup just after reset and
  *                      before branch to main program. This call is made inside
  *                      the "startup_stm32f401xx.s" file.
  *
  *      - SystemCoreClock variable: Contains the core clock (HCLK), it can be used
  *                                  by the user application to setup the SysTick
  *                                  timer or configure other parameters.
  *                                     
  *      - SystemCoreClockUpdate(): Updates the variable SystemCoreClock and must
  *                                 be called whenever the core clock is changed
  *                                 during program execution.
  *
  * 2. After each device reset the HSI (16 MHz) is used as system clock source.
  *    Then SystemInit() function is called, in "startup_stm32f401xx.s" file, to
  *    configure the system clock before to branch to main program.
  *
  * 3. If the system clock source selected by user fails to startup, the SystemInit()
  *    function will do nothing and HSI still used as system clock source. User can
  *    add some code to deal with this issue inside the SetSysClock() function.
  *
  * 4. The default value of HSE crystal is set to 8 MHz, refer to "HSE_VALUE" define
  *    in "stm32f4xx.h" file. When HSE is used as system clock source, directly or
  *    through PLL, and you are using different crystal you have to adapt the HSE
  *    value to your own configuration.
  *
  ****************************************************************************** 
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2013 STMicroelectronics</center></h2>
  *
  * Licensed under MCD-ST Liberty SW License Agreement V2, (the "License");
  * You may not use this file except in compliance with the License.
  * You may obtain a copy of the License at:
  *
  *        http://www.st.com/software_license_agreement_liberty_v2
  *
  * Unless required by applicable law or agreed to in writing, software
  * distributed under the License is distributed on an "AS IS" BASIS,
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
  ******************************************************************************
  */

#include "stm32f4xx.h"

// PLL Parameters:
// PLL_VCO = (HSE_VALUE or HSI_VALUE / PLL_M) * PLL_N
#define PLL_M      8
#define PLL_N      256

// SYSCLK = PLL_VCO / PLL_P
#define PLL_P      2

// USB OTG FS, SDIO and RNG Clock =  PLL_VCO / PLLQ
#define PLL_Q      6

// Select the PLL clock source
// HSE (8MHz) is used to clock the PLL, and the PLL is used
// as the system clock source.
#define PLL_SOURCE_HSE

uint32_t SystemCoreClock = UINT32_C(128000000);

void SystemInitCore(void);
void SetSysClock   (void);

void SystemInitCore(void)
{
  // Initialize the FPU.
  // Set CP10 and CP11 to Full Access.
  SCB->CPACR |= ((3UL << 10 * 2) | (3UL << 11 * 2));

  // Reset the RCC clock configuration to the default reset state
  // Set the HSION bit.
  RCC->CR |= (uint32_t) 0x00000001;

  // Reset the CFGR register.
  RCC->CFGR = 0x00000000;

  // Reset the HSEON, CSSON and PLLON bits.
  RCC->CR &= (uint32_t) 0xFEF6FFFF;

  // Reset the PLLCFGR register.
  RCC->PLLCFGR = 0x24003010;

  // Reset the HSEBYP bit.
  RCC->CR &= (uint32_t) 0xFFFBFFFF;

  // Disable all interrupts.
  RCC->CIR = 0x00000000;
}

/**
  * @brief  Configures the System clock source, PLL Multiplier and Divider factors,
  *         AHB/APBx prescalers and Flash settings
  * @Note   This function should be called only once the RCC clock configuration
  *         is reset to the default reset state (done in SystemInit() function).
  * @param  None
  * @retval None
  */
void SetSysClock(void)
{
  // Configure the system clock for 84MHz using the PLL.

  // The PLL is used as the system clock source.
  __IO uint32_t StartUpCounter = 0;
  __IO uint32_t HSEStatus      = 0;

  // Enable the HSE.
  RCC->CR |= ((uint32_t)RCC_CR_HSEON);

  // Wait until the HSE is ready or exit if timeout occurs.
  do
  {
    HSEStatus = RCC->CR & RCC_CR_HSERDY;
    StartUpCounter++;
  }
  while((HSEStatus == 0) && (StartUpCounter != HSE_STARTUP_TIMEOUT));

  // Verify that the HSE is ready.
  if((RCC->CR & RCC_CR_HSERDY) != RESET)
  {
    HSEStatus = (uint32_t)0x01;
  }
  else
  {
    HSEStatus = (uint32_t)0x00;
  }

  if(HSEStatus == (uint32_t) 0x01)
  {
    // Configure the main PLL.
    RCC->PLLCFGR =    PLL_M
                   | (PLL_N << 6)
                   | (((PLL_P >> 1) - 1) << 16)
                   | (RCC_PLLCFGR_PLLSRC_HSE)
                   | (PLL_Q << 24);
  }
  else
  {
    // If HSE fails to start-up, the application will have wrong clock
    // configuration. User can add here some code to deal with this error.
  }

  // Select regulator voltage output Scale 2 mode, System frequency up to 84 MHz.
  RCC->APB1ENR |= RCC_APB1ENR_PWREN;
  PWR->CR &= (uint32_t) ~(PWR_CR_VOS);

  // HCLK = SYSCLK / 1.
  RCC->CFGR |= RCC_CFGR_HPRE_DIV1;

  // PCLK2 = HCLK / 2.
  RCC->CFGR |= RCC_CFGR_PPRE2_DIV2;

  // PCLK1 = HCLK / 4.
  RCC->CFGR |= RCC_CFGR_PPRE1_DIV4;

  // Enable the main PLL.
  RCC->CR |= RCC_CR_PLLON;

  // Wait till the main PLL is ready.
  while((RCC->CR & RCC_CR_PLLRDY) == 0)
  {
    ;
  }

  // Configure Flash prefetch, Instruction cache, Data cache and wait state.
  FLASH->ACR =   FLASH_ACR_PRFTEN
               | FLASH_ACR_ICEN
               | FLASH_ACR_DCEN
               | FLASH_ACR_LATENCY_4WS;

  // Select the main PLL as system clock source.
  RCC->CFGR &= (uint32_t)((uint32_t)~(RCC_CFGR_SW));
  RCC->CFGR |= RCC_CFGR_SW_PLL;

  // Verify that the PLL is the clock source.
  while ((RCC->CFGR & (uint32_t)RCC_CFGR_SWS ) != RCC_CFGR_SWS_PLL)
  {
    ;
  }
}
