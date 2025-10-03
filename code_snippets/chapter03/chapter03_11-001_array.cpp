///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2017 - 2025.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

// chapter03_11-001_array.cpp

#include <algorithm>
#include <array>
#include <cstddef>
#include <cstdint>
#include <iostream>
#include <iomanip>
#include <iterator>

using login_key_array_type = std::array<std::uint8_t, static_cast<std::size_t>(UINT8_C(3))>;

// A login key stored in an std::array.

constexpr auto login_key =
  login_key_array_type
  {
    static_cast<std::uint8_t>(UINT8_C(0x01)),
    static_cast<std::uint8_t>(UINT8_C(0x02)),
    static_cast<std::uint8_t>(UINT8_C(0x03))
  };

auto main() -> int
{
  const auto flg = std::cout.flags();

  std::cout.unsetf(std::ios::dec);
  std::cout.setf(std::ios::hex);
  std::cout.setf(std::ios::showbase);

  std::cout << "login_key is ";
  std::copy(login_key.cbegin(), login_key.cend(), std::ostream_iterator<unsigned int>(std::cout, ","));
  std::cout << std::endl;

  std::cout.flags(flg);
}
