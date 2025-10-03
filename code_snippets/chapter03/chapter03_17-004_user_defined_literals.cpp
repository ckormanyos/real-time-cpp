///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2017 - 2025.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

// chapter03_17-004_user_defined_literals.cpp

#include <complex>
#include <iostream>

using namespace std::complex_literals;

std::complex<float> z { 1.2f + 3.4if };

auto main() -> int
{
  // (1.2,3.4)
  std::cout << z << std::endl;
}
