///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2019.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

// chapter06_17-001_use_the_stl.cpp

#include <array>
#include <cstdint>
#include <iomanip>
#include <iostream>
#include <numeric>

std::uint8_t checksum(const std::uint8_t* p,
                      const std::uint_fast8_t len)
{
  // Use the STL's version of accumulate.
  return std::accumulate(p,
                         p + len,
                         std::uint_fast8_t(0U));
}

int main()
{
  const std::array<std::uint8_t, 3U> data
  {
    { 1U, 2U, 3U }
  };

  const std::uint8_t sum = checksum(data.data(), static_cast<std::uint_fast8_t>(data.size()));

  std::cout << "sum: " << static_cast<std::uint32_t>(sum) << std::endl;
}
