///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2019 - 2025.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

// chapter06_13-001_adc_dimensioning.cpp

#include <cstdint>
#include <iostream>

constexpr auto raw2mv(const std::uint16_t& raw) -> std::uint16_t;

constexpr auto raw2mv(const std::uint16_t& raw) -> std::uint16_t
{
  return static_cast<std::uint16_t>(raw * 32U);
}

auto main() -> int;

auto main() -> int
{
  // 64
  std::cout << "raw2mv(2U): " << raw2mv(2U) << std::endl;
}
