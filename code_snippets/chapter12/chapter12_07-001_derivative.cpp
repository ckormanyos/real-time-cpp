///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2017 - 2026.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

// chapter12_07-001_derivative.cpp

// See also https://godbolt.org/z/baWzcrd1T

#include <cmath>
#include <iomanip>
#include <iostream>
#include <limits>
#include <numbers>
#include <sstream>

template<typename ValueType,
         typename FunctionType>
constexpr auto derivative(ValueType x,
                          ValueType dx,
                          FunctionType function)
  -> ValueType
{
  using value_type = ValueType;

  // Compute the derivative using a three point
  // central difference rule of O(dx^6).

  const auto dx1 = dx;
  const auto dx2 = static_cast<value_type>(dx1 * 2);
  const auto dx3 = static_cast<value_type>(dx1 * 3);

  const auto m1 = static_cast<value_type>((function(x + dx1) - function(x - dx1)) / 2);

  const auto m2 = static_cast<value_type>((function(x + dx2) - function(x - dx2)) / 4);

  const auto m3 = static_cast<value_type>((function(x + dx3) - function(x - dx3)) / 6);

  const auto fifteen_m1 = static_cast<value_type>(15 * m1);
  const auto six_m2     = static_cast<value_type>( 6 * m2);
  const auto ten_dx1    = static_cast<value_type>(10 * dx1);

  return ((fifteen_m1 - six_m2) + m3) / ten_dx1;
}

constexpr float xval { static_cast<float>(std::numbers::pi_v<float> / static_cast<float>(3.0L)) };

// Should be very near 0.5.
const auto y =
  derivative(xval,
             0.01F,
             [](float x) -> float
             {
               return std::sin(x);
             });

auto main() -> int;

auto main() -> int
{
  std::stringstream strm { };

  // 0.500003
  strm << std::setprecision(std::numeric_limits<float>::digits10) << std::fixed << y << '\n';

  using std::fabs;

  const auto delta = fabs(static_cast<float>(1.0L) - static_cast<float>(y / static_cast<float>(0.5L)));

  const auto result_close_fraction_is_ok = (delta < static_cast<float>(std::numeric_limits<float>::epsilon() * 128));

  strm << "result_close_fraction_is_ok: " << std::boolalpha << result_close_fraction_is_ok << '\n';

  std::cout << strm.str() << std::endl;

  return (result_close_fraction_is_ok ? 0 : -1);
}
