///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2024.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef MCAL_REG_2010_04_10_H_
  #define MCAL_REG_2010_04_10_H_

  #include <cstdint>

  namespace mcal
  {
    namespace reg
    {
      // Global base addresses.
      #define SCS_BASE        0xE000E000UL

      constexpr std::uint32_t scs_base           { UINT32_C(0xE000E000) };

      // Core peripherals.
      #define STK_BASE        ((SCS_BASE + 0x0010UL))
      #define NVIC_BASE       ((SCS_BASE + 0x0100UL))
      #define SCB_BASE        ((SCS_BASE + 0x0D00UL))

      constexpr std::uint32_t stk_base   { scs_base + UINT32_C(0x0010) };
      constexpr std::uint32_t nvic_base  { scs_base + UINT32_C(0x0100) };
      constexpr std::uint32_t scb_base   { scs_base + UINT32_C(0x0D00) };

      // SCB registers.
      #define SCB_CPACR       (*(volatile uint32_t*)(SCB_BASE + 0x88UL))

      constexpr std::uint32_t scb_cpacr  { scb_base + UINT32_C(0x0088) };

      // Base addresses for peripheral registers.
      #define RCC_BASE            0x40021000UL
      #define PWR_BASE            0x40007000UL
      #define FLASH_BASE          0x40022000UL
      #define GPIOB_BASE          0x48000400UL

      constexpr std::uint32_t rcc_base   { UINT32_C(0x40021000) };
      constexpr std::uint32_t pwr_base   { UINT32_C(0x40007000) };
      constexpr std::uint32_t flash_base { UINT32_C(0x40022000) };
      constexpr std::uint32_t gpiob_base { UINT32_C(0x48000400) };

      // FLASH registers.
      #define FLASH_ACR           (*(volatile uint32_t*)(FLASH_BASE + 0x000UL))

      constexpr std::uint32_t flash_acr { flash_base + UINT32_C(0x0000) };

      // PWR registers.
      #define PWR_CR1             (*(volatile uint32_t*)(PWR_BASE + 0x000UL))
      #define PWR_SR2             (*(volatile uint32_t*)(PWR_BASE + 0x014UL))

      constexpr std::uint32_t pwr_cr1 { pwr_base + UINT32_C(0x0000) };
      constexpr std::uint32_t pwr_sr2 { pwr_base + UINT32_C(0x0014) };

      // RCC Registers.
      #define RCC_CR              (*(volatile uint32_t*)(RCC_BASE + 0x00UL))
      #define RCC_ICSCR           (*(volatile uint32_t*)(RCC_BASE + 0x04UL))
      #define RCC_CFGR            (*(volatile uint32_t*)(RCC_BASE + 0x08UL))
      #define RCC_PLLCFGR         (*(volatile uint32_t*)(RCC_BASE + 0x0CUL))
      #define RCC_CIER            (*(volatile uint32_t*)(RCC_BASE + 0x18UL))
      #define RCC_AHB1ENR         (*(volatile uint32_t*)(RCC_BASE + 0x48UL))
      #define RCC_AHB2ENR         (*(volatile uint32_t*)(RCC_BASE + 0x4CUL))
      #define RCC_APB1ENR1        (*(volatile uint32_t*)(RCC_BASE + 0x58UL))
      #define RCC_APB1ENR2        (*(volatile uint32_t*)(RCC_BASE + 0x5CUL))
      #define RCC_APB2ENR         (*(volatile uint32_t*)(RCC_BASE + 0x60UL))

      constexpr std::uint32_t rcc_cr       { rcc_base + UINT32_C(0x0000) };
      constexpr std::uint32_t rcc_icscr    { rcc_base + UINT32_C(0x0004) };
      constexpr std::uint32_t rcc_cfgr     { rcc_base + UINT32_C(0x0008) };
      constexpr std::uint32_t rcc_pllcfgr  { rcc_base + UINT32_C(0x000C) };
      constexpr std::uint32_t rcc_cier     { rcc_base + UINT32_C(0x0018) };
      constexpr std::uint32_t rcc_ahb1enr  { rcc_base + UINT32_C(0x0048) };
      constexpr std::uint32_t rcc_ahb2enr  { rcc_base + UINT32_C(0x004C) };
      constexpr std::uint32_t rcc_apb1enr1 { rcc_base + UINT32_C(0x0058) };
      constexpr std::uint32_t rcc_apb1enr2 { rcc_base + UINT32_C(0x005C) };
      constexpr std::uint32_t rcc_apb2enr  { rcc_base + UINT32_C(0x0060) };

      // GPIOB registers.
      constexpr std::uint32_t gpiob_moder   { gpiob_base + UINT32_C(0x0000) };
      constexpr std::uint32_t gpiob_otyper  { gpiob_base + UINT32_C(0x0004) };
      constexpr std::uint32_t gpiob_ospeedr { gpiob_base + UINT32_C(0x0008) };
      constexpr std::uint32_t gpiob_pupdr   { gpiob_base + UINT32_C(0x000C) };
      constexpr std::uint32_t gpioc_idr     { gpiob_base + UINT32_C(0x0010) };
      constexpr std::uint32_t gpiob_odr     { gpiob_base + UINT32_C(0x0014) };
    }
  }

  #include <mcal/mcal_reg_access_dynamic.h>
  #include <mcal/mcal_reg_access_static.h>

#endif // MCAL_REG_2010_04_10_H_
