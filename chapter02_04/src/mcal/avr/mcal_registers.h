#ifndef _MCAL_REGISTERS_2010_04_10_H_
  #define _MCAL_REGISTERS_2010_04_10_H_

  #include <util/utility/util_type.h>

  namespace mcal
  {
    namespace registers
    {
      constexpr std::uint8_t SFR_OFFSET = static_cast<std::uint8_t>(0x20U);

      // Bit-position values.
      constexpr std::uint8_t BVAL0  = static_cast<std::uint8_t>(1U << 0U);
      constexpr std::uint8_t BVAL1  = static_cast<std::uint8_t>(1U << 1U);
      constexpr std::uint8_t BVAL2  = static_cast<std::uint8_t>(1U << 2U);
      constexpr std::uint8_t BVAL3  = static_cast<std::uint8_t>(1U << 3U);
      constexpr std::uint8_t BVAL4  = static_cast<std::uint8_t>(1U << 4U);
      constexpr std::uint8_t BVAL5  = static_cast<std::uint8_t>(1U << 5U);
      constexpr std::uint8_t BVAL6  = static_cast<std::uint8_t>(1U << 6U);
      constexpr std::uint8_t BVAL7  = static_cast<std::uint8_t>(1U << 7U);

      // Port registers
      constexpr std::uint8_t REG_DDRB   = static_cast<std::uint8_t>(0x04U + SFR_OFFSET);
      constexpr std::uint8_t REG_PORTB  = static_cast<std::uint8_t>(0x05U + SFR_OFFSET);
      constexpr std::uint8_t REG_DDRC   = static_cast<std::uint8_t>(0x07U + SFR_OFFSET);
      constexpr std::uint8_t REG_PORTC  = static_cast<std::uint8_t>(0x08U + SFR_OFFSET);
      constexpr std::uint8_t REG_DDRD   = static_cast<std::uint8_t>(0x0AU + SFR_OFFSET);
      constexpr std::uint8_t REG_PORTD  = static_cast<std::uint8_t>(0x0BU + SFR_OFFSET);
      constexpr std::uint8_t REG_DDRE   = static_cast<std::uint8_t>(0x0DU + SFR_OFFSET);
      constexpr std::uint8_t REG_PORTE  = static_cast<std::uint8_t>(0x0EU + SFR_OFFSET);

      // Timer0 registers
      constexpr std::uint8_t REG_TIFR0  = static_cast<std::uint8_t>(0x15U + SFR_OFFSET);
      constexpr std::uint8_t REG_TCCR0A = static_cast<std::uint8_t>(0x24U + SFR_OFFSET);
      constexpr std::uint8_t REG_TCCR0B = static_cast<std::uint8_t>(0x25U + SFR_OFFSET);
      constexpr std::uint8_t REG_OCR0A  = static_cast<std::uint8_t>(0x27U + SFR_OFFSET);
      constexpr std::uint8_t REG_TIMSK0 = static_cast<std::uint8_t>(0x6EU);
    }
  }
#endif // _MCAL_REGISTERS_2010_04_10_H_
