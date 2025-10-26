///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2019 - 2025.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

// chapter06_10-001_checksum_uint8_t.cpp

#include <array>
#include <cstddef>
#include <cstdint>
#include <iomanip>
#include <iostream>

constexpr auto checksum(const std::uint8_t* p, const std::uint8_t len) -> std::uint8_t;

constexpr auto checksum(const std::uint8_t* p, const std::uint8_t len) -> std::uint8_t
{
  std::uint8_t sum { UINT8_C(0) };

  for(std::uint8_t i = UINT8_C(0); i < len; ++i)
  {
    sum += *p;

    ++p;
  };

  return static_cast<std::uint8_t>(~sum + UINT8_C(1));
}

auto main() -> int;

auto main() -> int
{
  const std::array<std::uint8_t, std::size_t { UINT8_C(3) }> data =
  {{
    UINT8_C(1),
    UINT8_C(2),
    UINT8_C(3)
  }};

  const std::uint8_t sum { checksum(data.data(), static_cast<std::uint8_t>(data.size())) };

  // 250
  std::cout << "sum: " << static_cast<unsigned>(sum) << std::endl;
}
