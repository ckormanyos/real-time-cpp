///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2017 - 2018.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

// chapter03_02-002_fixed_size_integer.cpp

#include <cstdint>
#include <iostream>

// Initialize the 79,000th prime number.
// Macros like UINT32_C() are portable.

constexpr std::uint32_t prime_79000 = UINT32_C(10'006'721);

int main()
{
  std::cout << prime_79000 << std::endl;
}
