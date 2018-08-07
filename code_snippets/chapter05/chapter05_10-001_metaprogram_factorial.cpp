///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2018.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

// chapter05_10-001_metaprogram_factorial.cpp

#include <cstdint>
#include <iostream>

template<const std::uint32_t N>
struct factorial
{
  // Multiply N * (N - 1U) with template recursion.
  static constexpr std::uint32_t value
    = N * factorial<N - 1U>::value;
};

template<>
struct factorial<0U>
{
  // Zero'th specialization terminates the recursion.
  static constexpr std::uint32_t value = 1U;
};

int main()
{
  // 120
  constexpr std::uint32_t fact5 = factorial<5U>::value;

  std::cout << fact5 << std::endl;
}
