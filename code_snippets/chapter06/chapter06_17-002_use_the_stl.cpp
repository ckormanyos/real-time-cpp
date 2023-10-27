///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2019.
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

std::uint8_t checksum(const std::uint8_t* p,
                      const std::uint_fast8_t len)
{
  // Compare with a manually written accumulate.
  std::uint_fast8_t   sum = UINT8_C(0);
  const std::uint8_t* end = p + len;

  while(p != end)
  {
    sum += *p;
    ++p;
  };

  return sum;
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
