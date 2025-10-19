///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2019- 2025.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

// chapter05_01-001_template_add.cpp

// See also https://godbolt.org/z/dqMa7WMc7

#include <iostream>
#include <string>

template<typename T>
constexpr auto add(const T& a, const T& b) -> T
{
  return a + b;
}

// 3
const auto n { add(1, 2) };

// "abcxyz".
const auto str { add(std::string("abc"), std::string("xyz")) };

auto main() -> int;

auto main() -> int
{
  // 3
  std::cout << n << std::endl;

  // abcxyz
  std::cout << str << std::endl;
}
