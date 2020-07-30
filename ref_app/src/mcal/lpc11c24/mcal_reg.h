///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2020.
//  Copyright Joel Winarske 2019.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef MCAL_REG_2019_06_21_H_
  #define MCAL_REG_2019_06_21_H_

  #include <cstdint>

  namespace mcal
  {
    namespace reg
    {
      // C_CAN registers.
      constexpr std::uint32_t rom_api_can             = UINT32_C(0x1FFF334C);

      // Watchdog registers.
      constexpr std::uint32_t wdt_mod                 = UINT32_C(0x40004000);
      constexpr std::uint32_t wdt_tc                  = UINT32_C(0x40004004);
      constexpr std::uint32_t wdt_feed                = UINT32_C(0x40004008);
      constexpr std::uint32_t wdt_tv                  = UINT32_C(0x4000400C);

      // Timer registers.
      constexpr std::uint32_t tim16_0                 = UINT32_C(0x4000C000);
      constexpr std::uint32_t tim16_1                 = UINT32_C(0x40010000);
      constexpr std::uint32_t tim32_0                 = UINT32_C(0x40014000);
      constexpr std::uint32_t tim32_1                 = UINT32_C(0x40018000);

      // Flash registers.
      constexpr std::uint32_t flash_flashcfg          = UINT32_C(0x4003C010);

      // Iocon registers.
      constexpr std::uint32_t iocon                   = UINT32_C(0x40044000);

      // Syscon registers.
      constexpr std::uint32_t syscon_sysmemremap      = UINT32_C(0x40048000);
      constexpr std::uint32_t syscon_presetctrl       = UINT32_C(0x40048004);
      constexpr std::uint32_t syscon_syspllctrl       = UINT32_C(0x40048008);
      constexpr std::uint32_t syscon_syspllstat       = UINT32_C(0x4004800C);
      constexpr std::uint32_t syscon_syspllclksel     = UINT32_C(0x40048040);
      constexpr std::uint32_t syscon_wdtoscctrl       = UINT32_C(0x40048024);
      constexpr std::uint32_t syscon_syspllclkuen     = UINT32_C(0x40048044);
      constexpr std::uint32_t syscon_mainclksel       = UINT32_C(0x40048070);
      constexpr std::uint32_t syscon_mainclkuen       = UINT32_C(0x40048074);
      constexpr std::uint32_t syscon_sysahbclkdiv     = UINT32_C(0x40048078);
      constexpr std::uint32_t syscon_sysahbclkctrl    = UINT32_C(0x40048080);
      constexpr std::uint32_t syscon_wdtclksel        = UINT32_C(0x400480D0);
      constexpr std::uint32_t syscon_wdtclkuen        = UINT32_C(0x400480D4);
      constexpr std::uint32_t syscon_wdtclkdiv        = UINT32_C(0x400480D8);
      constexpr std::uint32_t syscon_pdruncfg         = UINT32_C(0x40048238);
      constexpr std::uint32_t syscon_device_id        = UINT32_C(0x400483F4);

      // System AHB Clock Control bits
      constexpr std::uint32_t syscon_clock_sys        = UINT32_C(1 <<  0);
      constexpr std::uint32_t syscon_clock_rom        = UINT32_C(1 <<  1);
      constexpr std::uint32_t syscon_clock_ram        = UINT32_C(1 <<  2);
      constexpr std::uint32_t syscon_clock_flashreg   = UINT32_C(1 <<  3);
      constexpr std::uint32_t syscon_clock_flasharray = UINT32_C(1 <<  4);
      constexpr std::uint32_t syscon_clock_i2c        = UINT32_C(1 <<  5);
      constexpr std::uint32_t syscon_clock_gpio       = UINT32_C(1 <<  6);
      constexpr std::uint32_t syscon_clock_ct16b0     = UINT32_C(1 <<  7);
      constexpr std::uint32_t syscon_clock_ct16b1     = UINT32_C(1 <<  8);
      constexpr std::uint32_t syscon_clock_ct32b0     = UINT32_C(1 <<  9);
      constexpr std::uint32_t syscon_clock_ct32b1     = UINT32_C(1 << 10);
      constexpr std::uint32_t syscon_clock_ssp0       = UINT32_C(1 << 11);
      constexpr std::uint32_t syscon_clock_uart0      = UINT32_C(1 << 12);
      constexpr std::uint32_t syscon_clock_adc        = UINT32_C(1 << 13);
      constexpr std::uint32_t syscon_clock_wdg        = UINT32_C(1 << 15);
      constexpr std::uint32_t syscon_clock_iocon      = UINT32_C(1 << 16);
      constexpr std::uint32_t syscon_clock_can        = UINT32_C(1 << 17);

      // System Power Down bits
      constexpr std::uint32_t syscon_pdruncfg_sysosc_pd_bpos = UINT32_C(5);
      constexpr std::uint32_t syscon_pdruncfg_wdtosc_pd_bpos = UINT32_C(6);
      constexpr std::uint32_t syscon_pdruncfg_syspll_pd_bpos = UINT32_C(7);

      // Gpio registers.
      constexpr std::uint32_t gpio0                   = UINT32_C(0x50000000);
      constexpr std::uint32_t gpio1                   = UINT32_C(0x50010000);
      constexpr std::uint32_t gpio2                   = UINT32_C(0x50020000);
      constexpr std::uint32_t gpio3                   = UINT32_C(0x50030000);


      // System registers.
      constexpr std::uint32_t scb_vtor                = UINT32_C(0xE000ED08);
      constexpr std::uint32_t aircr                   = UINT32_C(0xE000ED0C);  // SCB application interrupt / reset control.

      // System Tick registers.
      constexpr std::uint32_t systick_ctrl            = UINT32_C(0xE000E010);  // SysTick control and status
      constexpr std::uint32_t systick_load            = UINT32_C(0xE000E014);  // SysTick reload
      constexpr std::uint32_t systick_val             = UINT32_C(0xE000E018);  // SysTick current value

      // Interrupt control registers.
      constexpr std::uint32_t nvic_iser               = UINT32_C(0xE000E100);  // Interrupt set enable registers.
      constexpr std::uint32_t nvic_icer               = UINT32_C(0xE000E180);  // Interrupt clear enable registers.
      constexpr std::uint32_t nvic_ispr               = UINT32_C(0xE000E200);  // Interrupt set pending registers.
      constexpr std::uint32_t nvic_icpr               = UINT32_C(0xE000E280);  // Interrupt clear pending registers.
      constexpr std::uint32_t nvic_ip                 = UINT32_C(0xE000E400);  // Interrupt priority registers (each one 8 bits wide).

      // System Control Block registers.
      constexpr std::uint32_t scb_shp                 = UINT32_C(0xE000ED1C);  // System control block base address
    }
  }

  #include <mcal/mcal_reg_access_dynamic.h>
  #include <mcal/mcal_reg_access_static.h>

#endif // MCAL_REG_2019_06_21_H_
