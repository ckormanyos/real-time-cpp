///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2017 - 2025.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

// chapter03_17-006_user_defined_literals.cpp

#include <complex>
#include <iostream>

using namespace std::complex_literals;

std::complex<double> z { 1.0 + 0b0000'0001i };

auto main() -> int
{
  // (1,1)
  std::cout << z << std::endl;
}
