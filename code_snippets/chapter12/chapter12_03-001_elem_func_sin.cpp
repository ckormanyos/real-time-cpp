///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2025.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

// chapter12_03-001_elem_func_sin.cpp

#include <cmath>
#include <limits>
#include <iomanip>
#include <iostream>
#include <sstream>

auto main() -> int;

auto main() -> int
{
  std::stringstream strm { };

  const float s { std::sin(1.23F) };

  strm << "s: " << std::fixed << std::setprecision(std::numeric_limits<float>::digits10) << s << '\n';

  std::cout << strm.str() << std::endl;
}
