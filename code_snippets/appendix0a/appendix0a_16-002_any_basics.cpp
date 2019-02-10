///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2017 - 2018.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

// appendix0a_16-001_any_basics.cpp

#include <any>
#include <iostream>
#include <string>

// Create from int.
std::any ai(42);

// Create from float.
std::any af(1.23F);

// Create from std::string.
std::any as(std::string("hello"));

// Retrieve int value.
const int i = std::any_cast<int>(ai);

// Retrieve float value.
const float f = std::any_cast<float>(af);

// Retrieve std::string value.
const std::string s = std::any_cast<std::string>(as);

int main()
{
  std::cout << "i: " << i << std::endl;
  std::cout << "f: " << f << std::endl;
  std::cout << "s: " << s << std::endl;
}
