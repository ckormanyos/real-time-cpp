///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2017 - 2018.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

// chapter03_11-001_array.cpp

#include <algorithm>
#include <array>
#include <cstdint>
#include <iostream>
#include <iomanip>
#include <iterator>

// A login key stored in an std::array.
constexpr std::array<std::uint8_t, 3U> login_key
{
  {
    UINT8_C(0x01),
    UINT8_C(0x02),
    UINT8_C(0x03)
  }
};

int main()
{
  std::cout.unsetf(std::ios::dec);
  std::cout.setf(std::ios::hex);
  std::cout.setf(std::ios::showbase);

  std::cout << "login_key is ";
  std::copy(login_key.cbegin(), login_key.cend(), std::ostream_iterator<unsigned int>(std::cout, ","));
  std::cout << std::endl;
}
