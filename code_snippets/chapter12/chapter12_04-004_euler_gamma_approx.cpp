///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2017 - 2025.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

// chapter12_04-002_euler_gamma_approx.cpp

#include <algorithm>
#include <array>
#include <cmath>
#include <cstdint>
#include <iomanip>
#include <iostream>
#include <limits>
#include <numeric>

float euler_gamma_approx()
{
  std::array<float, 14U> arg_list;

  float f = 1.0F;

  // Generate a list of floats from 2.0 to 15.0.
  std::generate_n(arg_list.begin(),
                  arg_list.size(),
                  [&f]() -> float
                  {
                    return f += 1.0F;
                  });

  // Calculate the Euler-gamma approximation.
  const float sum =
    std::accumulate(
      arg_list.cbegin(),
      arg_list.cend(),
      0.0F,
      [](const float prev, const float& n) -> float
      {
        return     prev
               + ((std::riemann_zeta(n) - 1.0F) / n);
      });

  // Result: 0.577218, compare with 0.5772156649....
  const float euler_gamma = 1.0F - sum;

  return euler_gamma;
}

int main()
{
  std::cout << std::setprecision(std::numeric_limits<float>::digits10)
            << euler_gamma_approx()
            << std::endl;
}
