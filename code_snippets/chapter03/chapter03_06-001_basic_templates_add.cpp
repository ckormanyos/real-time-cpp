///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2017 - 2023.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

// chapter03_06-001_basic_templates_add.cpp

#include <cstdint>
#include <iostream>
#include <string>

template<typename T>
T add(const T& a, const T& b)
{
  return a + b;
}

const int   n = add(1, 2);
// n is 3.

const float f = add(1.2F, 3.4F);
// f is 4.6.

const std::string str = add(std::string("abc"),
                            std::string("xyz"));
// str is "abcxyz".

int main()
{
  std::cout << "int    addition result is " << n   << std::endl;
  std::cout << "float  addition result is " << f   << std::endl;
  std::cout << "string addition result is " << str << std::endl;
}
