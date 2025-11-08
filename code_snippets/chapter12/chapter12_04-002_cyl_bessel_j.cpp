///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2017 - 2025.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

// chapter12_04-002_cyl_bessel_j.cpp

#include <cmath>
#include <limits>
#include <iomanip>
#include <iostream>
#include <sstream>

auto main() -> int;

auto main() -> int
{
  // N[BesselJ[12/10, 34/10], 20]
  // 0.27579406927737016191

  // 0.275794
  const float jv { std::cyl_bessel_j(1.2F, 3.4F) };

  std::stringstream strm { };

  strm << "jv: " << std::fixed << std::setprecision(std::numeric_limits<float>::digits10)  << jv << '\n';

  std::cout << strm.str() << std::endl;
}
