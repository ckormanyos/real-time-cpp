///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2015.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef _CRC32_2015_01_26_H_
  #define _CRC32_2015_01_26_H_

  #include <array>
  #include <cstdint>

  namespace math
  {
    namespace checksums
    {
      inline std::uint32_t crc32_mpeg2(const std::uint8_t* first,
                                       const std::uint8_t* last)
      {
        // Name   : "CRC-32/MPEG-2"
        // Poly   : 0x04C1'1DB7
        // Init   : 0xFFFF'FFFF
        // Check  : 0x0376'E6E7

        // ISO/IEC 13818-1:2000-ITU-T
        // Recommendation H.222.0 Annex A

        constexpr std::array<std::uint32_t, 16U> table =
        {{
          UINT32_C(0x00000000), UINT32_C(0x04C11DB7),
          UINT32_C(0x09823B6E), UINT32_C(0x0D4326D9),
          UINT32_C(0x130476DC), UINT32_C(0x17C56B6B),
          UINT32_C(0x1A864DB2), UINT32_C(0x1E475005),
          UINT32_C(0x2608EDB8), UINT32_C(0x22C9F00F),
          UINT32_C(0x2F8AD6D6), UINT32_C(0x2B4BCB61),
          UINT32_C(0x350C9B64), UINT32_C(0x31CD86D3),
          UINT32_C(0x3C8EA00A), UINT32_C(0x384fBDBD)
        }};

        std::uint32_t crc = UINT32_C(0xFFFFFFFF);

        while(first != last)
        {
          const std::uint_fast8_t data =
            uint_fast8_t(*first) & UINT8_C(0xFF);

          std::uint_fast8_t index;

          index = (  std::uint_fast8_t(crc  >> 28)
                   ^ std::uint_fast8_t(data >>  4)
                  ) & UINT8_C(0xFF);

          crc   = std::uint32_t(crc << 4) ^ table[index];

          index = (  std::uint_fast8_t(crc  >> 28)
                   ^ std::uint_fast8_t(data & UINT8_C(0x0F))
                  )  & UINT8_C(0xFF);

          crc   = std::uint32_t(crc << 4) ^ table[index];

          ++first;
        }

        return crc;
      }
    }
  }

#endif // _CRC32_2015_01_26_H_
