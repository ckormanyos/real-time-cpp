///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2025.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

// chapter12_02-001_numbers_pi.cpp

#include <limits>
#include <iomanip>
#include <iostream>
#include <numbers>
#include <sstream>

auto main() -> int;

auto main() -> int
{
  std::stringstream strm { };

  constexpr float  pi_f = std::numbers::pi_v<float>;
  constexpr double pi_d = std::numbers::pi_v<double>;

  strm << "pi_f: " << std::fixed << std::setprecision(std::numeric_limits<float>::digits10) << pi_f << '\n';
  strm << "pi_d: " << std::fixed << std::setprecision(std::numeric_limits<double>::digits10) << pi_d << '\n';

  std::cout << strm.str() << std::endl;
}
