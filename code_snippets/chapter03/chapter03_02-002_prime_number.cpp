///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2017 - 2025.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

// chapter03_02-002_prime_number.cpp

#include <cstdint>
#include <iostream>

// Initialize the 664,999th prime number.

// See also PrimeQ[10006721] at Wolfram Alpha(R) https://www.wolframalpha.com/input?i=PrimeQ%5B10006721%5D
// See also Prime[664999] at Wolfram Alpha(R) https://www.wolframalpha.com/input?i=Prime%5B664999%5D

// Types like uint32_t and macros such as UINT32_C() are portable.
// See also https://godbolt.org/z/3c38v3EY5

constexpr std::uint32_t prime_664999 { UINT32_C(10'006'721) };

auto main() -> int
{
  std::cout << prime_664999 << std::endl;
}
