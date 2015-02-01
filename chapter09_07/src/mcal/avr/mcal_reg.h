///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2013.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef _MCAL_REG_2010_04_10_H_
  #define _MCAL_REG_2010_04_10_H_

  #include <cstdint>

  namespace mcal
  {
    namespace reg
    {
      // Bit-position values.
      const std::uint8_t bval0  = 1U;
      const std::uint8_t bval1  = 1U << 1U;
      const std::uint8_t bval2  = 1U << 2U;
      const std::uint8_t bval3  = 1U << 3U;
      const std::uint8_t bval4  = 1U << 4U;
      const std::uint8_t bval5  = 1U << 5U;
      const std::uint8_t bval6  = 1U << 6U;
      const std::uint8_t bval7  = 1U << 7U;

      // Port registers
      const std::uint8_t portb   = 0x00U;
    }
  }
#endif // _MCAL_REG_2010_04_10_H_
