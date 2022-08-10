///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2022.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include "stm32h7xx_hal.h"

#include <mcal_cpu.h>
#include <mcal_osc.h>
#include <mcal_reg.h>

namespace local
{
  HAL_StatusTypeDef hal_pwr_ex_config_supply(std::uint32_t SupplySource);

  HAL_StatusTypeDef hal_pwr_ex_config_supply(std::uint32_t SupplySource)
  {
    // Check if supply source was configured.
    volatile auto pwr_cr3_value = mcal::reg::reg_access_static<std::uint32_t,
                                                               std::uint32_t,
                                                               mcal::reg::pwr_cr3>::reg_get();

    if ((pwr_cr3_value & (PWR_CR3_SMPSEN | PWR_CR3_LDOEN | PWR_CR3_BYPASS)) != (PWR_CR3_SMPSEN | PWR_CR3_LDOEN))
    {
      // Check supply configuration.
      pwr_cr3_value = mcal::reg::reg_access_static<std::uint32_t,
                                                   std::uint32_t,
                                                   mcal::reg::pwr_cr3>::reg_get();

      if ((pwr_cr3_value & PWR_SUPPLY_CONFIG_MASK) != SupplySource)
      {
        // Supply configuration update locked, can't apply a new supply config.
        return HAL_ERROR;
      }
      else
      {
        // Supply configuration update locked, but new supply configuration
        // matches with old supply configuration : nothing to do.
        return HAL_OK;
      }
    }

    // Set the power supply configuration.
    // MODIFY_REG (PWR->CR3, PWR_SUPPLY_CONFIG_MASK, SupplySource);
    mcal::reg::reg_access_dynamic<std::uint32_t,
                                  std::uint32_t>::reg_msk(mcal::reg::pwr_cr3, SupplySource, PWR_SUPPLY_CONFIG_MASK);

    /* Wait till voltage level flag is set */
    volatile std::uint32_t delay { };
    
    for(delay = static_cast<std::uint32_t>(UINT32_C(0)); delay < static_cast<std::uint32_t>(UINT32_C(1000000)); ++delay)
    {
      const auto pwr_flag_actvosrdy_is_set =
        mcal::reg::reg_access_static<std::uint32_t,
                                     std::uint32_t,
                                     mcal::reg::pwr_csr1,
                                     static_cast<std::uint32_t>(UINT8_C(13))>::bit_get();

      if(pwr_flag_actvosrdy_is_set)
      {
        break;
      }
    }

    if(delay == static_cast<std::uint32_t>(UINT32_C(1000000)))
    {
      return HAL_ERROR;
    }

    /* When the SMPS supplies external circuits verify that SDEXTRDY flag is set */
    if ((SupplySource == PWR_SMPS_1V8_SUPPLIES_EXT_AND_LDO) ||
        (SupplySource == PWR_SMPS_2V5_SUPPLIES_EXT_AND_LDO) ||
        (SupplySource == PWR_SMPS_1V8_SUPPLIES_EXT)         ||
        (SupplySource == PWR_SMPS_2V5_SUPPLIES_EXT))
    {

      for(delay = static_cast<std::uint32_t>(UINT32_C(0)); delay < static_cast<std::uint32_t>(UINT32_C(1000000)); ++delay)
      {
        const auto pwr_flag_smpsextrdy_is_set =
          mcal::reg::reg_access_static<std::uint32_t,
                                       std::uint32_t,
                                       mcal::reg::pwr_cr3,
                                       static_cast<std::uint32_t>(UINT8_C(16))>::bit_get();

        if(pwr_flag_smpsextrdy_is_set)
        {
          break;
        }
      }

      if(delay == static_cast<std::uint32_t>(UINT32_C(1000000)))
      {
        return HAL_ERROR;
      }
    }

    return HAL_OK;
  }
} // namespace local

void mcal::osc::init(const config_type*)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = { 0UL, 0UL, 0UL, 0UL, 0UL, 0UL, 0UL, 0UL, 0UL, { 0UL, 0UL, 0UL, 0UL, 0UL, 0UL, 0UL, 0UL, 0UL, 0UL } };
  RCC_ClkInitTypeDef RCC_ClkInitStruct = { 0UL, 0UL, 0UL, 0UL, 0UL, 0UL, 0UL, 0UL };

  // AXI clock gating.
  // RCC->CKGAENR = 0xFFFFFFFF;
  mcal::reg::reg_access_static<std::uint32_t,
                               std::uint32_t,
                               mcal::reg::rcc_ckgaenr,
                               static_cast<std::uint32_t>(UINT32_C(0xFFFFFFFF))>::reg_set();

  // Supply configuration update enable
  static_cast<void>(local::hal_pwr_ex_config_supply(PWR_DIRECT_SMPS_SUPPLY));

  // Configure the main internal regulator output voltage
  // Configure the Voltage Scaling.
  // __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE0);
  mcal::reg::reg_access_static<std::uint32_t,
                               std::uint32_t,
                               mcal::reg::pwr_srdcr,
                               static_cast<std::uint32_t>(PWR_REGULATOR_VOLTAGE_SCALE0)>::reg_msk<static_cast<std::uint32_t>(PWR_SRDCR_VOS)>();

  // Delay after setting the voltage scaling
  const volatile auto tmpreg =
    mcal::reg::reg_access_static<std::uint32_t,
                                 std::uint32_t,
                                 mcal::reg::pwr_srdcr>::reg_get();

  static_cast<void>(tmpreg);

  while(!mcal::reg::reg_access_static<std::uint32_t,
                                      std::uint32_t,
                                      mcal::reg::pwr_srdcr,
                                      static_cast<std::uint32_t>(UINT8_C(13))>::bit_get()) { ; }

  // Initializes the RCC Oscillators according to the specified parameters
  // in the RCC_OscInitTypeDef structure.

  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI48|RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_BYPASS;
  RCC_OscInitStruct.HSI48State = RCC_HSI48_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 1;
  RCC_OscInitStruct.PLL.PLLN = 24;
  RCC_OscInitStruct.PLL.PLLP = 2;
  RCC_OscInitStruct.PLL.PLLQ = 4;
  RCC_OscInitStruct.PLL.PLLR = 2;
  RCC_OscInitStruct.PLL.PLLRGE = RCC_PLL1VCIRANGE_3;
  RCC_OscInitStruct.PLL.PLLVCOSEL = RCC_PLL1VCOWIDE;
  RCC_OscInitStruct.PLL.PLLFRACN = 0;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    for(;;) { ; }
  }

  // Initializes the CPU, AHB and APB buses clocks

  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2
                              |RCC_CLOCKTYPE_D3PCLK1|RCC_CLOCKTYPE_D1PCLK1;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.SYSCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB3CLKDivider = RCC_APB3_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_APB1_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_APB2_DIV1;
  RCC_ClkInitStruct.APB4CLKDivider = RCC_APB4_DIV1;

  constexpr auto flash_latency_2 = static_cast<std::uint32_t>(UINT8_C(2));

  static_cast<void>(HAL_RCC_ClockConfig(&RCC_ClkInitStruct, flash_latency_2));
}
