///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2020.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

// chapter05_12-004_stirlings_approx_cpp_numbers.cpp

#include <cmath>
#include <iomanip>
#include <iostream>
#include <limits>
#include <numbers>

template<typename T>
T tgamma_order_2(T x)
{
  using std::pow;
  using std::sqrt;

  const T      one_over_x = T(1.0L) / x;
  const T sqrt_one_over_x = sqrt(one_over_x);

  const T term0 =    sqrt(T(2.0L) * std::numbers::pi_v<T>)
                   * sqrt_one_over_x;
  const T term1 = (  sqrt(std::numbers::pi_v<T> / T(2.0L))
                   * (  sqrt_one_over_x
                      * one_over_x))
                  / T(6.0L);

  return pow(x / std::numbers::e_v<T>, x) * (term0 + term1);
}

int main()
{
  constexpr std::streamsize prec =
    std::numeric_limits<float>::max_digits10;

  std::cout << std::setprecision(prec)
            << tgamma_order_2(20.0F)
            << std::endl;
}

// Test tgamma_order_2(20.0F).
// Result:       1.21644237     e+17.
// Compare with: 1.2164510041...e+17.
