///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2021.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef MCAL_REG_2010_04_10_H_
  #define MCAL_REG_2010_04_10_H_

  #include <cstdint>

  static_assert(__AVR_ARCH__ == 103, "Error: Check the architecture for special function registers");

  namespace mcal
  {
    namespace reg
    {
      constexpr std::uint8_t   sfr_offset        = 0x00;

      // System registers.
      constexpr std::uint8_t   sys_ccp           = sfr_offset + 0x34U;

      // Clock registers.
      constexpr std::uint8_t   clk_mclkctrla     = 0x0060 + 0x00;
      constexpr std::uint8_t   clk_mclkctrlb     = 0x0060 + 0x01;
      constexpr std::uint8_t   clk_mclklock      = 0x0060 + 0x02;

      // Port registers.
      constexpr std::uint16_t  porta             = 0x0400U;
      constexpr std::uint16_t  portb             = 0x0420U;
      constexpr std::uint16_t  portc             = 0x0440U;
      constexpr std::uint16_t  portd             = 0x0460U;
      constexpr std::uint16_t  porte             = 0x0480U;
      constexpr std::uint16_t  portf             = 0x04A0U;

      // Real-Time Counter registers
      constexpr std::uint16_t  rtc_ctrla         = 0x0140U + 0x00U; // Control A
      constexpr std::uint16_t  rtc_status        = 0x0140U + 0x01U; // Status
      constexpr std::uint16_t  rtc_intctrl       = 0x0140U + 0x02U; // Interrupt Control
      constexpr std::uint16_t  rtc_intflags      = 0x0140U + 0x03U; // Interrupt Flags
      constexpr std::uint16_t  rtc_temp          = 0x0140U + 0x04U; // Temporary
      constexpr std::uint16_t  rtc_dbgctrl       = 0x0140U + 0x05U; // Debug control
      constexpr std::uint16_t  rtc_calib         = 0x0140U + 0x06U; // Calibration
      constexpr std::uint16_t  rtc_clksel        = 0x0140U + 0x07U; // Clock Select
      constexpr std::uint16_t  rtc_cnt           = 0x0140U + 0x08U; // Counter
      constexpr std::uint16_t  rtc_per           = 0x0140U + 0x0AU; // Period
      constexpr std::uint16_t  rtc_cmp           = 0x0140U + 0x0CU; // Compare
      constexpr std::uint16_t  rtc_reserved_0x0E = 0x0140U + 0x0EU;
      constexpr std::uint16_t  rtc_reserved_0x0F = 0x0140U + 0x0FU;
      constexpr std::uint16_t  rtc_pitctrla      = 0x0140U + 0x10U; // PIT Control A
      constexpr std::uint16_t  rtc_pitstatus     = 0x0140U + 0x11U; // PIT Status
      constexpr std::uint16_t  rtc_pitintctrl    = 0x0140U + 0x12U; // PIT Interrupt Control
      constexpr std::uint16_t  rtc_pitintflags   = 0x0140U + 0x13U; // PIT Interrupt Flags
      constexpr std::uint16_t  rtc_reserved      = 0x0140U + 0x14U;
      constexpr std::uint16_t  rtc_pitdbgctrl    = 0x0140U + 0x15U; // PIT Debug control
      constexpr std::uint16_t  rtc_reserved_0x16 = 0x0140U + 0x16U;
      constexpr std::uint16_t  rtc_reserved_0x17 = 0x0140U + 0x17U;
      constexpr std::uint16_t  rtc_reserved_0x18 = 0x0140U + 0x18U;
      constexpr std::uint16_t  rtc_reserved_0x19 = 0x0140U + 0x19U;
      constexpr std::uint16_t  rtc_reserved_0x1A = 0x0140U + 0x1AU;
      constexpr std::uint16_t  rtc_reserved_0x1B = 0x0140U + 0x1BU;
      constexpr std::uint16_t  rtc_reserved_0x1C = 0x0140U + 0x1CU;
      constexpr std::uint16_t  rtc_reserved_0x1D = 0x0140U + 0x1DU;
      constexpr std::uint16_t  rtc_reserved_0x1E = 0x0140U + 0x1EU;
      constexpr std::uint16_t  rtc_reserved_0x1F = 0x0140U + 0x1FU;

      // Watchdog registers
      constexpr std::uint16_t  wdt_ctrla         = 0x0100U + 0x00U;
      constexpr std::uint16_t  wdt_status        = 0x0100U + 0x01U;

      // Eeprom registers
    }
  }

  #include <mcal/mcal_reg_access_dynamic.h>
  #include <mcal/mcal_reg_access_static.h>

#endif // MCAL_REG_2010_04_10_H_
