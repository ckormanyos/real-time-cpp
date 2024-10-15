///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2013.
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
      constexpr std::uint8_t sfr_offset = 0x20U;

      // Bit-position values.
      constexpr std::uint8_t bval0  = 1U;
      constexpr std::uint8_t bval1  = 1U << 1U;
      constexpr std::uint8_t bval2  = 1U << 2U;
      constexpr std::uint8_t bval3  = 1U << 3U;
      constexpr std::uint8_t bval4  = 1U << 4U;
      constexpr std::uint8_t bval5  = 1U << 5U;
      constexpr std::uint8_t bval6  = 1U << 6U;
      constexpr std::uint8_t bval7  = 1U << 7U;

      // System registers.
      constexpr std::uint8_t mcusr  = 0x14U + sfr_offset;
      constexpr std::uint8_t prr    = 0x64U;

      // Port registers.
      constexpr std::uint8_t pinb   = 0x03U + sfr_offset;
      constexpr std::uint8_t ddrb   = 0x04U + sfr_offset;
      constexpr std::uint8_t portb  = 0x05U + sfr_offset;
      constexpr std::uint8_t pinc   = 0x06U + sfr_offset;
      constexpr std::uint8_t ddrc   = 0x07U + sfr_offset;
      constexpr std::uint8_t portc  = 0x08U + sfr_offset;
      constexpr std::uint8_t pind   = 0x09U + sfr_offset;
      constexpr std::uint8_t ddrd   = 0x0AU + sfr_offset;
      constexpr std::uint8_t portd  = 0x0BU + sfr_offset;
      constexpr std::uint8_t pine   = 0x0CU + sfr_offset;
      constexpr std::uint8_t ddre   = 0x0DU + sfr_offset;
      constexpr std::uint8_t porte  = 0x0EU + sfr_offset;

      // Timer registers
      constexpr std::uint8_t tifr0  = 0x15U + sfr_offset;
      constexpr std::uint8_t tccr0a = 0x24U + sfr_offset;
      constexpr std::uint8_t tccr0b = 0x25U + sfr_offset;
      constexpr std::uint8_t tcnt0  = 0x26U + sfr_offset;
      constexpr std::uint8_t ocr0a  = 0x27U + sfr_offset;
      constexpr std::uint8_t timsk0 = 0x6EU;

      constexpr std::uint8_t tifr1  = 0x16U + sfr_offset;
      constexpr std::uint8_t tccr1a = 0x80U;
      constexpr std::uint8_t tccr1b = 0x81U;
      constexpr std::uint8_t tcnt1l = 0x84U;
      constexpr std::uint8_t tcnt1h = 0x85U;
      constexpr std::uint8_t icr1   = 0x86U;  // 16-bit register
      constexpr std::uint8_t ocr1a  = 0x88U;  // 16-bit register
      constexpr std::uint8_t ocr1b  = 0x8AU;  // 16-bit register
      constexpr std::uint8_t timsk1 = 0x6FU;

      constexpr std::uint8_t tifr2  = 0x17U + sfr_offset;
      constexpr std::uint8_t tccr2a = 0xB0U;
      constexpr std::uint8_t tccr2b = 0xB1U;
      constexpr std::uint8_t tcnt2  = 0xB2U;
      constexpr std::uint8_t ocr2a  = 0xB3U;
      constexpr std::uint8_t timsk2 = 0x70U;

      // SPI(TM) registers.
      constexpr std::uint8_t spcr = 0x2CU + sfr_offset;
      constexpr std::uint8_t spsr = 0x2DU + sfr_offset;
      constexpr std::uint8_t spdr = 0x2EU + sfr_offset;

      // Watchdog registers
      constexpr std::uint8_t wdtcsr = 0x60U;

      // Eeprom registers
      constexpr std::uint8_t eecr   = 0x1FU + sfr_offset;
      constexpr std::uint8_t eedr   = 0x20U + sfr_offset;
      constexpr std::uint8_t eear   = 0x21U + sfr_offset;
      constexpr std::uint8_t eearl  = 0x21U + sfr_offset;
      constexpr std::uint8_t eearh  = 0x22U + sfr_offset;
    }
  }

  #include <mcal/mcal_reg_access_dynamic.h>
  #include <mcal/mcal_reg_access_static.h>

#endif // MCAL_REG_2010_04_10_H_
