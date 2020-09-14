///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2019- 2020.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

// chapter05_12-002_constants.cpp

#include <cmath>
#include <iomanip>
#include <iostream>
#include <limits>

template<typename T>
constexpr T pi =
  T(3.1415926535'8979323846'2643383279'5028841972L);

template<typename T>
constexpr T e =
  T(2.7182818284'5904523536'0287471352'6624977572L);

int main()
{
  constexpr std::streamsize prec =
    std::numeric_limits<float>::max_digits10;

  std::cout << std::setprecision(prec)
            << pi<float>
            << std::endl;

  std::cout << std::setprecision(prec)
            << e<float>
            << std::endl;
}
