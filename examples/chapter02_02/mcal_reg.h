///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2025.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef MCAL_REG_2011_11_04_H
  #define MCAL_REG_2011_11_04_H

  #include <cstdint>

  namespace mcal::reg {

  constexpr std::uint8_t portb { UINT8_C(0x25U) };

  constexpr std::uint8_t bval0 { UINT8_C(0x01) };
  constexpr std::uint8_t bval1 { UINT8_C(0x01) << 1U };
  constexpr std::uint8_t bval2 { UINT8_C(0x01) << 2U };
  constexpr std::uint8_t bval3 { UINT8_C(0x01) << 3U };
  constexpr std::uint8_t bval4 { UINT8_C(0x01) << 4U };
  constexpr std::uint8_t bval5 { UINT8_C(0x01) << 5U };
  constexpr std::uint8_t bval6 { UINT8_C(0x01) << 6U };
  constexpr std::uint8_t bval7 { UINT8_C(0x01) << 7U };

  } // namespace mcal::reg

#endif // MCAL_REG_2011_11_04_H
