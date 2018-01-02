///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2017 - 2018.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

// chapter12_04-001_ellint_1.cpp

#include <cmath>
#include <iomanip>
#include <iostream>
#include <limits>

int main()
{
  constexpr float pi_half = std::acos(-1.0F) / 2.0F;

  const float e1 = std::ellint_1(0.5F, pi_half);

  std::cout << std::setprecision(std::numeric_limits<float>::digits10)
            << e1
            << std::endl;

  // 1.68575
}
