///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2024.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef MCAL_REG_2010_04_10_H
  #define MCAL_REG_2010_04_10_H

  #include <cstdint>

  namespace mcal
  {
    namespace reg
    {
      // Global base addresses.
      constexpr std::uint32_t scs_base      { UINT32_C(0xE000E000) };

      // Core peripherals.
      constexpr std::uint32_t stk_base      { scs_base + UINT32_C(0x0010) };
      constexpr std::uint32_t nvic_base     { scs_base + UINT32_C(0x0100) };
      constexpr std::uint32_t scb_base      { scs_base + UINT32_C(0x0D00) };

      // SCB registers.
      constexpr std::uint32_t scb_cpacr     { scb_base + UINT32_C(0x0088) };

      // Base addresses for peripheral registers.
      constexpr std::uint32_t rcc_base      { UINT32_C(0x40021000) };
      constexpr std::uint32_t pwr_base      { UINT32_C(0x40007000) };
      constexpr std::uint32_t flash_base    { UINT32_C(0x40022000) };
      constexpr std::uint32_t gpiob_base    { UINT32_C(0x48000400) };

      // FLASH registers.
      constexpr std::uint32_t flash_acr     { flash_base + UINT32_C(0x0000) };

      // PWR registers.
      constexpr std::uint32_t pwr_cr1       { pwr_base + UINT32_C(0x0000) };
      constexpr std::uint32_t pwr_sr2       { pwr_base + UINT32_C(0x0014) };

      // RCC Registers.
      constexpr std::uint32_t rcc_cr        { rcc_base + UINT32_C(0x0000) };
      constexpr std::uint32_t rcc_icscr     { rcc_base + UINT32_C(0x0004) };
      constexpr std::uint32_t rcc_cfgr      { rcc_base + UINT32_C(0x0008) };
      constexpr std::uint32_t rcc_pllcfgr   { rcc_base + UINT32_C(0x000C) };
      constexpr std::uint32_t rcc_cier      { rcc_base + UINT32_C(0x0018) };
      constexpr std::uint32_t rcc_ahb1enr   { rcc_base + UINT32_C(0x0048) };
      constexpr std::uint32_t rcc_ahb2enr   { rcc_base + UINT32_C(0x004C) };
      constexpr std::uint32_t rcc_apb1enr1  { rcc_base + UINT32_C(0x0058) };
      constexpr std::uint32_t rcc_apb1enr2  { rcc_base + UINT32_C(0x005C) };
      constexpr std::uint32_t rcc_apb2enr   { rcc_base + UINT32_C(0x0060) };

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

#endif // MCAL_REG_2010_04_10_H
