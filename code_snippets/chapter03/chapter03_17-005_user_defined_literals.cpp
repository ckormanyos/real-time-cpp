///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2017 - 2025.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

// chapter03_17-005_user_defined_literals.cpp

#include <cmath>
#include <complex>
#include <iomanip>
#include <iostream>
#include <limits>

using namespace std::complex_literals;

const std::complex<double> z { 1.2 + 3.4i };

// (13.979408806018, 5.4228154724634)
const std::complex<double> s { std::sin(z) };

auto main() -> int
{
  std::cout << std::setprecision(std::numeric_limits<double>::digits10)
            << s
            << std::endl;
}
