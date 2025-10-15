///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2017 - 2025.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

// chapter03_11-001_array.cpp

#include <array>
#include <cstdint>
#include <cstddef>
#include <format>
#include <iostream>
#include <string>

using login_key_array_type = std::array<std::uint8_t, std::size_t { UINT8_C(3) }>;

// A login key stored in an std::array.

constexpr login_key_array_type
  login_key
  {
    UINT8_C(0x01),
    UINT8_C(0x02),
    UINT8_C(0x03)
  };

auto main() -> int
{
  std::string str_login_key { "login_key is: " };

  for(const auto& value : login_key)
  {
    str_login_key += std::format("{:#x},", value);
  }

  std::cout << str_login_key << std::endl;
}
