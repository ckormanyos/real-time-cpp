///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2017 - 2018.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

// chapter03_17-005_user_defined_literals.cpp

#include <cmath>
#include <complex>
#include <iostream>

using namespace std::complex_literals;

const std::complex<double> z = 1.2 + 3.4i;

// (13.9794,5.42282)
const std::complex<double> s = std::sin(z);

int main()
{
  std::cout << s << std::endl;
}
