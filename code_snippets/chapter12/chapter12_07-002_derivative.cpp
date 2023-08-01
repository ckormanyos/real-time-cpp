///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2017 - 2023.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

// chapter12_07-002_derivative.cpp

// See also https://godbolt.org/z/cra4qo4ab

#include <cmath>
#include <iomanip>
#include <iostream>
#include <limits>

template<typename ValueType,
         typename FunctionType>
auto derivative(const ValueType x,
                const ValueType dx,
                FunctionType function) -> ValueType
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

template<typename T>
constexpr T pi = static_cast<T>(3.1415926535'8979323846'2643383279L);

const auto x = static_cast<float>(pi<float> / static_cast<float>(3.0L));

// Should be very near 0.5.
const auto y =
  derivative(x,
             static_cast<float>(0.01L),
             [](const float& x) -> float
             {
               return std::sin(x);
             });

auto main() -> int;

auto main() -> int
{
  const auto flg = std::cout.flags();

  // 0.500003
  std::cout << std::setprecision(std::numeric_limits<float>::digits10)
            << y
            << std::endl;

  using std::fabs;

  const auto delta = fabs(static_cast<float>(1.0L) - static_cast<float>(y / static_cast<float>(0.5L)));

  const auto result_close_fraction_is_ok = (delta < static_cast<float>(std::numeric_limits<float>::epsilon() * 128));

  std::cout << "result_close_fraction_is_ok: " << std::boolalpha << result_close_fraction_is_ok << std::endl;

  std::cout.flags(flg);

  return (result_close_fraction_is_ok ? 0 : -1);
}
