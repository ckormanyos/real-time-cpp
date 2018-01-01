///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2017 - 2018.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

// chapter12_05-001_complex.cpp

#include <complex>
#include <iomanip>
#include <iostream>
#include <limits>

int main()
{
  std::complex<float> x(1.23F, 3.45F); // (1.23 + 3.45 I)
  std::complex<float> y(0.77F, 0.22F); // (0.77 + 0.22 I)

  float nx = std::norm(x); // 13.4154
  float ay = std::abs(y);  // 0.800812

  std::cout << std::setprecision(std::numeric_limits<float>::digits10)
            << nx
            << std::endl;

  std::cout << std::setprecision(std::numeric_limits<float>::digits10)
            << ay
            << std::endl;
}
