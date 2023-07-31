///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2019 - 2023.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

// chapter06_14-002_romable_array.cpp

#include <array>
#include <cstddef>
#include <cstdint>
#include <iomanip>
#include <iostream>

namespace
{
  // A version that is compile-time constant.
  constexpr auto version_string =
    std::array<char, static_cast<std::size_t>(UINT8_C(5))>
    {
      '1', '.', '2', '3', '\0'
    };
}

static_assert(version_string.front() == static_cast<char>('1'), "Error: Wrong value in front of array.");

auto main() -> int;

auto main() -> int
{
  const auto flg = std::cout.flags();

  std::cout << std::hex
            << "version_string[0U]: 0x"
            << std::setw(2)
            << std::setfill('0')
            << static_cast<unsigned>(version_string.at(static_cast<std::size_t>(UINT8_C(0))))
            << std::endl;

  std::cout << "version_string: "
            << version_string.data()
            << std::endl;

  std::cout.flags(flg);
}
