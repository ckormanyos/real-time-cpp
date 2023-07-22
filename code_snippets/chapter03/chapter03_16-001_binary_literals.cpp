///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2017 - 2023.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

// chapter03_16-001_binary_literals.cpp

#include <cstdint>
#include <iostream>

constexpr auto one   = static_cast<std::uint8_t>(UINT8_C(0b1));

constexpr auto seven = static_cast<std::uint8_t>(UINT8_C(0b0000'0111));

int main()
{
  std::cout << "one   is " << one   << std::endl;
  std::cout << "seven is " << seven << std::endl;
}
