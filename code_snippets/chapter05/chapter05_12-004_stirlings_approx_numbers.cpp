///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2019 - 2025.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

// chapter05_12-004_stirlings_approx_numbers.cpp

#include <cmath>
#include <iomanip>
#include <iostream>
#include <limits>
#include <numbers>
#include <sstream>

template<typename T>
constexpr auto tgamma_order_2(T x) -> T
{
  using namespace std::numbers;

  using std::pow;
  using std::sqrt;

  const T sqx { sqrt2_v<T> * sqrt(pi_v<T> / x) };

  return pow(x / e_v<T>, x) * sqx * (1 + 1 / (12 * x));
}

auto main() -> int;

auto main() -> int
{
  std::stringstream strm { };

  constexpr std::streamsize prec { std::numeric_limits<float>::digits10 + 1 };

  // Test tgamma_order_2(20.0F).
  // Result:       1.216442 e+17.
  // Compare with: 1.216451 e+17.

  const float tg { tgamma_order_2(20.0F) };
  constexpr float ctrl { 1.2164510040883200000e17F };

  strm << std::setprecision(prec) << "tg:   " << tg << "\nctrl: " << ctrl;

  std::cout << strm.str() << std::endl;
}
