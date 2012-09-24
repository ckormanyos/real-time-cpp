#ifndef _MCAL_REGISTERS_2010_04_10_H_
  #define _MCAL_REGISTERS_2010_04_10_H_

  #include <util/utility/util_type.h>

  namespace mcal
  {
    namespace registers
    {
      constexpr std::uint8_t sfr_offset = static_cast<std::uint8_t>(0x20U);

      // Bit-position values.
      constexpr std::uint8_t bval0  = static_cast<std::uint8_t>(1U << 0U);
      constexpr std::uint8_t bval1  = static_cast<std::uint8_t>(1U << 1U);
      constexpr std::uint8_t bval2  = static_cast<std::uint8_t>(1U << 2U);
      constexpr std::uint8_t bval3  = static_cast<std::uint8_t>(1U << 3U);
      constexpr std::uint8_t bval4  = static_cast<std::uint8_t>(1U << 4U);
      constexpr std::uint8_t bval5  = static_cast<std::uint8_t>(1U << 5U);
      constexpr std::uint8_t bval6  = static_cast<std::uint8_t>(1U << 6U);
      constexpr std::uint8_t bval7  = static_cast<std::uint8_t>(1U << 7U);

      // Port registers
      constexpr std::uint8_t ddrb   = static_cast<std::uint8_t>(0x04U + sfr_offset);
      constexpr std::uint8_t portb  = static_cast<std::uint8_t>(0x05U + sfr_offset);
      constexpr std::uint8_t ddrc   = static_cast<std::uint8_t>(0x07U + sfr_offset);
      constexpr std::uint8_t portc  = static_cast<std::uint8_t>(0x08U + sfr_offset);
      constexpr std::uint8_t ddrd   = static_cast<std::uint8_t>(0x0AU + sfr_offset);
      constexpr std::uint8_t portd  = static_cast<std::uint8_t>(0x0BU + sfr_offset);
      constexpr std::uint8_t ddre   = static_cast<std::uint8_t>(0x0DU + sfr_offset);
      constexpr std::uint8_t porte  = static_cast<std::uint8_t>(0x0EU + sfr_offset);

      // Timer registers
      constexpr std::uint8_t tifr0  = static_cast<std::uint8_t>(0x15U + sfr_offset);
      constexpr std::uint8_t tccr0a = static_cast<std::uint8_t>(0x24U + sfr_offset);
      constexpr std::uint8_t tccr0b = static_cast<std::uint8_t>(0x25U + sfr_offset);
      constexpr std::uint8_t tcnt0  = static_cast<std::uint8_t>(0x26U + sfr_offset);
      constexpr std::uint8_t ocr0a  = static_cast<std::uint8_t>(0x27U + sfr_offset);
      constexpr std::uint8_t timsk0 = static_cast<std::uint8_t>(0x6EU);

      // SPI(TM) registers.
      constexpr std::uint8_t spcr = static_cast<std::uint8_t>(0x2CU + sfr_offset);
      constexpr std::uint8_t spsr = static_cast<std::uint8_t>(0x2DU + sfr_offset);
      constexpr std::uint8_t spdr = static_cast<std::uint8_t>(0x2EU + sfr_offset);
    }
  }
#endif // _MCAL_REGISTERS_2010_04_10_H_
