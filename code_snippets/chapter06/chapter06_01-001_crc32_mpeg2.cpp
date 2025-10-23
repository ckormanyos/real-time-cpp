///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2018 - 2025.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

// chapter06_01-001_crc32_mpeg2.cpp

#include <array>
#include <cstdint>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <sstream>

template<typename input_iterator>
constexpr
auto crc32_mpeg2(input_iterator first,
                 input_iterator last) -> std::uint32_t
{
  // Name            : CRC-32/MPEG-2
  // Polynomial      : 0x04C11DB7
  // Initial value   : 0xFFFFFFFF
  // Test: '1'...'9' : 0x0376E6E7

  // ISO/IEC 13818-1:2000
  // Recommendation H.222.0 Annex A

  // CRC-32/MPEG-2 Table based on nibbles.
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

  // Set the initial value.
  std::uint32_t crc { UINT32_C(0xFFFFFFFF) };

  // Loop through the input data stream.
  while(first != last)
  {
    // Define a local value_type.
    using value_type =
      typename
      std::iterator_traits<input_iterator>::value_type;

    const value_type value
      { static_cast<value_type>
        ((*first) & UINT8_C(0xFF)) };

    const std::uint_fast8_t byte
      { uint_fast8_t(value) };

    std::uint_fast8_t index { };

    // Perform the CRC-32/MPEG-2 algorithm.
    index = (  (std::uint_fast8_t(crc  >> 28U))
             ^ (std::uint_fast8_t(byte >>  4U))
            ) & UINT8_C(0x0F);

    crc =   std::uint32_t(  std::uint32_t(crc << 4U)
                          & UINT32_C(0xFFFFFFF0))
          ^ table[index];

    index = (  (std::uint_fast8_t(crc >> 28U))
             ^ (std::uint_fast8_t(byte))
            ) & UINT8_C(0x0F);

    crc =   std::uint32_t(  std::uint32_t(crc << 4U)
                          & UINT32_C(0xFFFFFFF0))
          ^ table[index];

    ++first;
  }

  return crc;
}

auto do_something() -> void;

auto do_something() -> void
{
  constexpr std::array<std::uint8_t, 9U> data =
  {{
    0x31U, 0x32U, 0x33U, 0x34U, 0x35U, 0x36U, 0x37U, 0x38U, 0x39U
  }};

  const std::uint32_t crc32_mpeg2_value
    { crc32_mpeg2(data.cbegin(), data.cend()) };

  const bool crc32_mpeg2_value_is_ok { (crc32_mpeg2_value == UINT32_C(0x0376E6E7)) };

  std::stringstream strm { };

  strm << "crc32_mpeg2_value: 0x"
       << std::hex
       << std::uppercase
       << std::setw(8)
       << std::setfill(char('0'))
       << crc32_mpeg2_value
       << '\n';

  strm << "crc32_mpeg2_value_is_ok: "
       << std::boolalpha
       << crc32_mpeg2_value_is_ok;

  std::cout << strm.str() << std::endl;
}

auto main() -> int;

auto main() -> int
{
  do_something();
}
