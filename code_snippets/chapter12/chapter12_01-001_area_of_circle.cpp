///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2025.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

// chapter12_01-001_area_of_circle.cpp

#include <cmath>
#include <format>
#include <limits>
#include <iomanip>
#include <iostream>
#include <numbers>
#include <sstream>

constexpr auto area_of_a_circle(float r) -> float
{
  return (std::numbers::pi_v<float> * r) * r;
}

auto main() -> int;

auto main() -> int
{
  std::stringstream strm { };

  strm << "area_of_a_circle(0.5F): " << std::fixed << std::setprecision(std::numeric_limits<float>::digits10) << area_of_a_circle(0.5F) << '\n';
  strm << "area_of_a_circle(1.5F): " << std::fixed << std::setprecision(std::numeric_limits<float>::digits10) << area_of_a_circle(1.5F) << '\n';

  std::cout << strm.str() << std::endl;
}
