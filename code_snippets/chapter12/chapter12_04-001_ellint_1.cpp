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
  using std::acos;
  using std::ellint_1;

  const auto pi_half =
    static_cast<float>
    (
      acos(static_cast<float>(-1.0L)) / static_cast<float>(2.0L)
    );

  const float e1 = ellint_1(static_cast<float>(0.5L), pi_half);

  const auto flg = std::cout.flags();

  std::cout << std::setprecision(std::numeric_limits<float>::digits10)
            << e1
            << std::endl;

  // 1.68575

  std::cout.flags(flg);
}
