///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2023.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <mcal_cpu.h>
#include <mcal_osc.h>
#include <mcal_reg.h>

void mcal::osc::init(const config_type*)
{
  // Increase the power.
  //DCDC_REG3 = (DCDC_REG3 & (~(0x1FUL))) | 0x1FUL;
  mcal::reg::reg_access_static<std::uint32_t, std::uint32_t, mcal::reg::dcdc_reg3, static_cast<std::uint32_t>(UINT32_C(0x1F))>::reg_msk<static_cast<std::uint32_t>(UINT32_C(0x1F))>();

  //while((DCDC_REG0 & 0x80000000UL) == 0UL);
  while(!mcal::reg::reg_access_static<std::uint32_t, std::uint32_t, mcal::reg::dcdc_reg0, static_cast<std::uint32_t>(UINT32_C(31))>::bit_get())
  {
    mcal::cpu::nop();
  }

  // Switch the temporary CPU Subsystem clock to PLL2 (528 MHz).
  //CCM_CBCMR = (CCM_CBCMR & (~(3UL << 18U)));
  mcal::reg::reg_access_static<std::uint32_t, std::uint32_t, mcal::reg::ccm_cbcmr, static_cast<std::uint32_t>(~(3UL << 18U))>::reg_and();

  // Enable the PLL1 bypass.
  //CCM_ANALOG_PLL_ARM = (CCM_ANALOG_PLL_ARM & (~(3UL << 14U))) | (1UL << 16U);
  mcal::reg::reg_access_static<std::uint32_t, std::uint32_t, mcal::reg::ccm_analog_pll_arm, static_cast<std::uint32_t>(1UL << 16U)>::reg_msk<static_cast<std::uint32_t>(3UL << 14U)>();

  // Set PLL1 to 600 MHz.
  //CCM_ANALOG_PLL_ARM = (CCM_ANALOG_PLL_ARM & (~((0x7FUL << 0U) | (1UL << 12U)))) | (1UL << 13U) | 0x64U;
  mcal::reg::reg_access_static<std::uint32_t, std::uint32_t, mcal::reg::ccm_analog_pll_arm, static_cast<std::uint32_t>(static_cast<std::uint32_t>(1UL << 13U) | static_cast<std::uint32_t>(UINT32_C(0x64)))>::reg_msk<static_cast<std::uint32_t>(static_cast<std::uint32_t>(UINT32_C(0x7F)) | static_cast<std::uint32_t>(1UL << 12U))>();

  // Wait for PLL1 to lock.
  //while((CCM_ANALOG_PLL_ARM & 0x80000000UL) == 0UL);
  while(!mcal::reg::reg_access_static<std::uint32_t, std::uint32_t, mcal::reg::ccm_analog_pll_arm, static_cast<std::uint32_t>(UINT32_C(31))>::bit_get())
  {
    mcal::cpu::nop();
  }

  // Disable the PLL1 bypass.
  //CCM_ANALOG_PLL_ARM &= ~(1UL << 16U);
  mcal::reg::reg_access_static<std::uint32_t, std::uint32_t, mcal::reg::ccm_analog_pll_arm, static_cast<std::uint32_t>(~(1UL << 16U))>::reg_and();

  // Switch the CPU Subsystem clock to the new PLL1 value (of 600 MHz).
  //CCM_CBCMR = (CCM_CBCMR & (~(3UL << 18U))) | (3UL << 18U);
  mcal::reg::reg_access_static<std::uint32_t, std::uint32_t, mcal::reg::ccm_cbcmr, static_cast<std::uint32_t>(3UL << 18U)>::reg_msk<static_cast<std::uint32_t>(3UL << 18U)>();
}
