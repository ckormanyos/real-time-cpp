///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2025.
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
      constexpr std::uint32_t scs_base        = UINT32_C(0xE000E000);

      // Individual unit base addresses.
      constexpr std::uint32_t sys_tick_base   = scs_base + UINT32_C(0x00000010);

      // System registers.
      constexpr std::uint32_t scb_vtor  = static_cast<std::uint32_t>(0xE000ED08UL);   // 32-bit register.
      constexpr std::uint32_t aircr     = static_cast<std::uint32_t>(0xE000ED0CUL);   // 32-bit register. SCB application interrupt / reset control.

      // Interrupt registers.
      constexpr std::uint32_t rcc_cr    = static_cast<std::uint32_t>(0x40021000UL);   // 32-bit register.
      constexpr std::uint32_t rcc_cfgr  = static_cast<std::uint32_t>(0x40021004UL);   // 32-bit register.
      constexpr std::uint32_t rcc_cir   = static_cast<std::uint32_t>(0x40021008UL);   // 32-bit register.
      constexpr std::uint32_t rcc_cfgr2 = static_cast<std::uint32_t>(0x4002102CUL);   // 32-bit register.

      // System tick addresses.
      constexpr std::uint32_t sys_tick_ctrl   = sys_tick_base + UINT32_C(0x00000000);
      constexpr std::uint32_t sys_tick_load   = sys_tick_base + UINT32_C(0x00000004);
      constexpr std::uint32_t sys_tick_val    = sys_tick_base + UINT32_C(0x00000008);
      constexpr std::uint32_t sys_tick_cal    = sys_tick_base + UINT32_C(0x0000000C);

      // Port registers.
      constexpr std::uint32_t gpioa_crl = static_cast<std::uint32_t>(0x40010800UL);   // 32-bit register.
      constexpr std::uint32_t gpioa_crh = static_cast<std::uint32_t>(0x40010804UL);   // 32-bit register.
      constexpr std::uint32_t gpioa_idr = static_cast<std::uint32_t>(0x40010808UL);   // 32-bit register.
      constexpr std::uint32_t gpioa_odr = static_cast<std::uint32_t>(0x4001080CUL);   // 32-bit register.

      constexpr std::uint32_t gpiob_crl = static_cast<std::uint32_t>(0x40010C00UL);   // 32-bit register.
      constexpr std::uint32_t gpiob_crh = static_cast<std::uint32_t>(0x40010C04UL);   // 32-bit register.
      constexpr std::uint32_t gpiob_idr = static_cast<std::uint32_t>(0x40010C08UL);   // 32-bit register.
      constexpr std::uint32_t gpiob_odr = static_cast<std::uint32_t>(0x40010C0CUL);   // 32-bit register.

      constexpr std::uint32_t gpioc_crl = static_cast<std::uint32_t>(0x40011000UL);   // 32-bit register.
      constexpr std::uint32_t gpioc_crh = static_cast<std::uint32_t>(0x40011004UL);   // 32-bit register.
      constexpr std::uint32_t gpioc_idr = static_cast<std::uint32_t>(0x40011008UL);   // 32-bit register.
      constexpr std::uint32_t gpioc_odr = static_cast<std::uint32_t>(0x4001100CUL);   // 32-bit register.

      // Timer registers.
      constexpr std::uint32_t tim4_cr1   = static_cast<std::uint32_t>(0x40000800UL);  // 16-bit register.
      constexpr std::uint32_t tim4_cr2   = static_cast<std::uint32_t>(0x40000804UL);  // 16-bit register.
      constexpr std::uint32_t tim4_smcr  = static_cast<std::uint32_t>(0x40000808UL);  // 16-bit register.
      constexpr std::uint32_t tim4_dier  = static_cast<std::uint32_t>(0x4000080CUL);  // 16-bit register.
      constexpr std::uint32_t tim4_sr    = static_cast<std::uint32_t>(0x40000810UL);  // 16-bit register.
      constexpr std::uint32_t tim4_egr   = static_cast<std::uint32_t>(0x40000814UL);  // 16-bit register.
      constexpr std::uint32_t tim4_ccmr1 = static_cast<std::uint32_t>(0x40000818UL);  // 16-bit register.
      constexpr std::uint32_t tim4_ccmr2 = static_cast<std::uint32_t>(0x4000081CUL);  // 16-bit register.
      constexpr std::uint32_t tim4_ccer  = static_cast<std::uint32_t>(0x40000820UL);  // 16-bit register.
      constexpr std::uint32_t tim4_cnt   = static_cast<std::uint32_t>(0x40000824UL);  // 16-bit register.
      constexpr std::uint32_t tim4_psc   = static_cast<std::uint32_t>(0x40000828UL);  // 16-bit register.
      constexpr std::uint32_t tim4_arr   = static_cast<std::uint32_t>(0x4000082CUL);  // 16-bit register.
      constexpr std::uint32_t tim4_rcr   = static_cast<std::uint32_t>(0x40000830UL);  // 16-bit register.

      // Power management registers.
      constexpr std::uint32_t rcc_apbenr  = static_cast<std::uint32_t>(0x40021014UL); // 32-bit register.
      constexpr std::uint32_t rcc_apb2enr = static_cast<std::uint32_t>(0x40021018UL); // 32-bit register.
      constexpr std::uint32_t rcc_apb1enr = static_cast<std::uint32_t>(0x4002101CUL); // 32-bit register.

      // Watchdog registers.
      constexpr std::uint32_t iwdg_kr     = static_cast<std::uint32_t>(0x40003000UL); // 32-bit register.
      constexpr std::uint32_t iwdg_pr     = static_cast<std::uint32_t>(0x40003004UL); // 32-bit register.
      constexpr std::uint32_t iwdg_rlr    = static_cast<std::uint32_t>(0x40003008UL); // 32-bit register.
      constexpr std::uint32_t iwdg_sr     = static_cast<std::uint32_t>(0x4000300CUL); // 32-bit register.

      // Interrupt control registers.
      constexpr std::uint32_t nvic_iser   = static_cast<std::uint32_t>(0xE000E100 + 0x0000); // 32-bit registers : Interrupt set enable registers.
      constexpr std::uint32_t nvic_icer   = static_cast<std::uint32_t>(0xE000E100 + 0x0080); // 32-bit registers : Interrupt clear enable registers.
      constexpr std::uint32_t nvic_ispr   = static_cast<std::uint32_t>(0xE000E100 + 0x0100); // 32-bit registers : Interrupt set pending registers.
      constexpr std::uint32_t nvic_icpr   = static_cast<std::uint32_t>(0xE000E100 + 0x0180); // 32-bit registers : Interrupt clear pending registers.
      constexpr std::uint32_t nvic_iabr   = static_cast<std::uint32_t>(0xE000E100 + 0x0200); // 32-bit registers : Interrupt active bit registers.
      constexpr std::uint32_t nvic_ip     = static_cast<std::uint32_t>(0xE000E100 + 0x0300); //  8-bit registers : Interrupt priority registers (each one 8 bits wide).
    }
  }

  #include <mcal/mcal_reg_access_dynamic.h>
  #include <mcal/mcal_reg_access_static.h>

#endif // MCAL_REG_2010_04_10_H
