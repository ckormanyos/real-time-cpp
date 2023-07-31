///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2019- 2020.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

// chapter05_01-002_template_add2.cpp

#include <iostream>

template<typename T1,
         typename T2>
auto add(const T1& a, const T2& b) -> T1
{
  return a + T1(b);
}

const auto d = add(1.1, 2); // OK, 3.1, double

auto main() -> int;

auto main() -> int
{
  std::cout << d << std::endl;
}
