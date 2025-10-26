///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2019 - 2025.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

// chapter06_17-002_use_the_stl.cpp

#include <array>
#include <cstdint>
#include <iomanip>
#include <iostream>
#include <numeric>

constexpr auto checksum(const std::uint8_t* p, const std::uint_fast8_t len) -> std::uint8_t;

constexpr auto checksum(const std::uint8_t* p, const std::uint_fast8_t len) -> std::uint8_t
{
  // Compare with a manually written accumulate.
  std::uint_fast8_t   sum { };

  const std::uint8_t* end = p + len;

  while(p != end)
  {
    sum += *p;

    ++p;
  };

  return static_cast<std::uint8_t>(~sum + UINT8_C(1));
}

auto main() -> int;

auto main() -> int
{
  const std::array<std::uint8_t, 3U> data
  {
    { UINT8_C(1), UINT8_C(2), UINT8_C(3) }
  };

  const std::uint8_t sum { checksum(data.data(), static_cast<std::uint_fast8_t>(data.size())) };

  // 250
  std::cout << "sum: " << static_cast<std::uint32_t>(sum) << std::endl;
}
