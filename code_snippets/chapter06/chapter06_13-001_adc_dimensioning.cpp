///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2019.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

// chapter06_13-001_adc_dimensioning.cpp

#include <cstdint>
#include <iostream>

std::uint16_t raw2mv(const std::uint16_t& raw)
{
  return raw * UINT16_C(32);
}

int main()
{
  std::cout << "raw2mv(2U): " << raw2mv(2U) << std::endl;
}
