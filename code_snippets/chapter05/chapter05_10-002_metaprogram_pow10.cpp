///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2018 - 2019.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

// chapter05_10-002_metaprogram_pow10.cpp

#include <cstdint>
#include <iostream>

template<const std::uint32_t n>
constexpr std::uint32_t pow10()
{
  static_assert(n <= 9U, "Error: n is limited to 9 or less.");

  return pow10<n - 1U>() * UINT32_C(10);
};

template<>
constexpr std::uint32_t pow10<UINT32_C(0)>()
{
  return UINT32_C(1);
};

int main()
{
  // 1,000,000
  constexpr std::uint32_t million = pow10<6U>();

  std::cout << million << std::endl;
}
