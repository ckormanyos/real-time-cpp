///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2019- 2020.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

// chapter05_12-001_prime_number.cpp

#include <cstdint>
#include <iostream>

template<typename T>
constexpr T prime_number = T(541);

constexpr std::uint16_t p =
  prime_number<std::uint16_t>;

int main()
{
  std::cout << p << std::endl;
}
