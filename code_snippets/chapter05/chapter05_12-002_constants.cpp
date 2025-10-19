///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2019- 2025.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

// chapter05_12-002_constants.cpp

#include <cmath>
#include <iomanip>
#include <iostream>
#include <limits>
#include <sstream>

template<typename T>
constexpr T sqrt2 =
  T(1.4142135623'7309504880'1688724209'6980785697L);

template<typename T>
constexpr T pi =
  T(3.1415926535'8979323846'2643383279'5028841972L);

template<typename T>
constexpr T e =
  T(2.7182818284'5904523536'0287471352'6624977572L);

auto main() -> int;

auto main() -> int
{
  constexpr std::streamsize prec { std::numeric_limits<float>::digits10 + 1 };

  std::stringstream strm { };

  strm << std::setprecision(prec) << '\n' << sqrt2<float>;
  strm << std::setprecision(prec) << '\n' << pi<float>;
  strm << std::setprecision(prec) << '\n' << e<float>;

  std::cout << strm.str() << std::endl;
}
