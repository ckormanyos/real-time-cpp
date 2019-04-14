///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2019.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

// chapter06_12-001_mul_shift_and_add.cpp

#include <cstdint>
#include <iostream>

std::uint32_t scale(const std::uint32_t x)
{
  // Let the compiler decide for
  // shift-and-add or multiply.
  return std::uint32_t(x * 23U);
}

int main()
{
  std::cout << "scale(2U): " << scale(2U) << std::endl;
}
