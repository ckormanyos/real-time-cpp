///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2017 - 2018.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

// chapter12_07-001_area_of_a_circle.cpp

#include <cmath>
#include <iomanip>
#include <iostream>
#include <limits>

template<typename T>
constexpr T pi =
  T(3.1415926535'8979323846'2643383279L);

template<typename T>
constexpr T area_of_a_circle(T r)
{
  return (pi<T> * r) * r;
}

constexpr float f = area_of_a_circle(1.23F);
// 4.75292

constexpr double d = area_of_a_circle(1.23);
// 4.752915525616

int main()
{
  // 4.75292
  std::cout << std::setprecision(std::numeric_limits<float>::digits10)
            << f
            << std::endl;

  // 4.752915525616
  std::cout << std::setprecision(std::numeric_limits<double>::digits10)
            << d
            << std::endl;
}
