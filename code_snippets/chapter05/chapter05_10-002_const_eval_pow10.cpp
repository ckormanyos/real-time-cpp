///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2018 - 2025.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

// chapter05_10-002_const_eval_pow10.cpp

#include <cstdint>
#include <cmath>
#include <iostream>
#include <type_traits>

extern std::uint32_t p_nonconst;

template<typename T>
constexpr auto pow10(T p)
  -> std::enable_if_t<std::is_unsigned_v<T>, T>;

template<typename T>
constexpr auto pow10(T p)
  -> std::enable_if_t<std::is_unsigned_v<T>, T>
{
  if(std::is_constant_evaluated())
  {
    constexpr T ten { 10 };

    return   p == 0 ? T { 1 }
           : p == 1 ? ten
           : ten * pow10(T { p - 1U });
  }
  else
  {
    using std::pow;

    return static_cast<T>(pow(10, p));
  }
}

auto main() -> int
{
  constexpr std::uint32_t p { UINT64_C(6) };

  // This is constexpr.
  constexpr std::uint32_t million { pow10(p) };

  static_assert(million == UINT32_C(1'000'000),
                "Error: wrong result for pow10 function.");

  // This is not constexpr.
  const std::uint32_t million_nonconst { pow10(p_nonconst) };

  std::cout << "million:          " << million          << std::endl;
  std::cout << "million_nonconst: " << million_nonconst << std::endl;
}

std::uint32_t p_nonconst { UINT64_C(6) };
