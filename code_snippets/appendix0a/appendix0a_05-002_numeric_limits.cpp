///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2019.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

// appendix0a_05-002_numeric_limits.cpp

#include <cstdint>
#include <limits>
#include <iomanip>
#include <iostream>

template<typename unsigned_type>
struct hi_bit
{
  // The bit-position of the high bit.
  static constexpr int bpos
    = std::numeric_limits<unsigned_type>::digits - 1;

  // The value of the type with the high-bit set.
  static constexpr unsigned_type value
    = static_cast<unsigned_type>(1) << bpos;
};

constexpr std::uint8_t hi08 =
  hi_bit<std::uint8_t>::value;  // (1 <<  7)

constexpr std::uint16_t hi16 =
  hi_bit<std::uint16_t>::value; // (1 << 15)

constexpr std::uint32_t hi32 =
  hi_bit<std::uint32_t>::value; // (1 << 31)

constexpr std::uint64_t hi64 =
  hi_bit<std::uint64_t>::value; // (1 << 63)

int main()
{
  std::cout << "hi08: 0x" << std::hex << std::uppercase << std::setw( 2) << std::setfill(char('0')) << std::uintmax_t(hi08) << std::endl;
  std::cout << "hi16: 0x" << std::hex << std::uppercase << std::setw( 4) << std::setfill(char('0')) << std::uintmax_t(hi16) << std::endl;
  std::cout << "hi32: 0x" << std::hex << std::uppercase << std::setw( 8) << std::setfill(char('0')) << std::uintmax_t(hi32) << std::endl;
  std::cout << "hi64: 0x" << std::hex << std::uppercase << std::setw(16) << std::setfill(char('0')) << std::uintmax_t(hi64) << std::endl;
}
