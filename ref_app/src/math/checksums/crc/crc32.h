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
  #include <iterator>
  #include <numeric>

  namespace math
  {
    namespace checksums
    {
      template<typename input_iterator>
      std::uint32_t crc32_mpeg2(input_iterator first,
                                input_iterator last)
      {
        // Name            : CRC-32/MPEG-2
        // Polynomial      : 0x04C1'1DB7
        // Initial value   : 0xFFFF'FFFF
        // Test: '1'...'9' : 0x0376'E6E7

        // ISO/IEC 13818-1:2000
        // Recommendation H.222.0 Annex A

        // CRC-32/MPEG2 Table based on nibbles.

        // Define a local value_type.
        typedef typename std::iterator_traits<input_iterator>::value_type value_type;

        // Loop through the input data stream to generate the CRC-32/MPEG2 result.
        return std::accumulate(first,
                               last,
                               std::uint32_t(UINT32_C(0xFFFFFFFF)),
                               [](std::uint32_t& crc, const value_type& value) -> std::uint32_t
                               {
                                 constexpr std::array<std::uint32_t, 16U> table =
                                 {{
                                   UINT32_C(0x00000000), UINT32_C(0x04C11DB7),
                                   UINT32_C(0x09823B6E), UINT32_C(0x0D4326D9),
                                   UINT32_C(0x130476DC), UINT32_C(0x17C56B6B),
                                   UINT32_C(0x1A864DB2), UINT32_C(0x1E475005),
                                   UINT32_C(0x2608EDB8), UINT32_C(0x22C9F00F),
                                   UINT32_C(0x2F8AD6D6), UINT32_C(0x2B4BCB61),
                                   UINT32_C(0x350C9B64), UINT32_C(0x31CD86D3),
                                   UINT32_C(0x3C8EA00A), UINT32_C(0x384FBDBD)
                                 }};

                                 const std::uint_fast8_t byte = uint_fast8_t(value) & UINT8_C(0xFF);

                                 std::uint_fast8_t index;

                                 // Perform the CRC-32/MPEG2 algorithm.
                                 index = ((std::uint_fast8_t(crc >> 28)) ^ (std::uint_fast8_t(byte >> 4))) & std::uint_fast8_t(UINT8_C(0x0F));

                                 crc   = std::uint32_t(std::uint32_t(crc << 4) & UINT32_C(0xFFFFFFF0)) ^ table[index];

                                 index = ((std::uint_fast8_t(crc >> 28)) ^ (std::uint_fast8_t(byte))) & std::uint_fast8_t(UINT8_C(0x0F));

                                 crc   = std::uint32_t(std::uint32_t(crc << 4) & UINT32_C(0xFFFFFFF0)) ^ table[index];

                                 return crc;
                               });
      }
    }
  }

#endif // _CRC32_2015_01_26_H_
