///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2019- 2020.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

// chapter05_01-001_template_add.cpp

#include <cstdint>
#include <iostream>
#include <string>

template<typename T>
T add(const T& a, const T& b)
{
  return a + b;
}

const int n = add(1, 2); // 3

const std::string s =
  add(std::string("abc"),
      std::string("xyz")); // "abcxyz".

int main()
{
  std::cout << n << std::endl;
  std::cout << s << std::endl;
}
