///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2025.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

// chapter12_02-003_zeta_three.cpp

#include <concepts>
#include <limits>
#include <iomanip>
#include <iostream>
#include <numbers>
#include <sstream>

template<typename T>
requires std::floating_point<T>
constexpr T zeta_three_v =
  T(1.2020569031'5959428539'9738161511'4499907650L);

auto main() -> int;

auto main() -> int
{
  std::stringstream strm { };

  constexpr float  z3_f = zeta_three_v<float>;
  constexpr double z3_d = zeta_three_v<double>;

  strm << "z3_f: " << std::fixed << std::setprecision(std::numeric_limits<float>::digits10)  << z3_f << '\n';
  strm << "z3_d: " << std::fixed << std::setprecision(std::numeric_limits<double>::digits10) << z3_d << '\n';

  std::cout << strm.str() << std::endl;
}

