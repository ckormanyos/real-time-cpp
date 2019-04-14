///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2019.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

// chapter06_10-001_checksum_uint8_t.cpp

#include <cstdint>
#include <iomanip>
#include <iostream>

std::uint8_t checksum(const std::uint8_t* p,
                      const std::uint8_t len)
{
  std::uint8_t sum = UINT8_C(0);

  for(std::uint8_t i = UINT8_C(0); i < len; i++)
  {
    sum += *p;
    ++p;
  };

  return sum;
}

int main()
{
  const std::uint8_t data[3U] = { 1U, 2U, 3U };

  const std::uint8_t sum = checksum(data, 3U);

  // 6
  std::cout << "sum: " << static_cast<std::uint32_t>(sum) << std::endl;
}
