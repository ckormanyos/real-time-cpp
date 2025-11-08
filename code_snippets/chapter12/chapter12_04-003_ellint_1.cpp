///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2017 - 2025.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

// chapter12_04-003_ellint_1.cpp

#include <cmath>
#include <limits>
#include <iomanip>
#include <iostream>
#include <numbers>
#include <sstream>

auto main() -> int;

auto main() -> int
{
  // Note: Uses a different argument convention than C++.
  // N[EllipticF[Pi/2, (1/2)^2], 20]
  // 1.6857503548125960429

  constexpr float pi_half
  {  std::numbers::pi_v<float> / 2.0F };

  // 1.685750
  const float e1 { std::ellint_1(0.5F, pi_half) };

  std::stringstream strm { };

  strm << "e1: " << std::fixed << std::setprecision(std::numeric_limits<float>::digits10)  << e1 << '\n';

  std::cout << strm.str() << std::endl;
}
