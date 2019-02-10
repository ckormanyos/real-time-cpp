///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2017 - 2018.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

// appendix0a_16-003_any_and_stl_container.cpp

#include <any>
#include <algorithm>
#include <array>
#include <iomanip>
#include <iostream>
#include <string>

void do_something()
{
  // Fill an array with three instances of any.
  const std::array<std::any, 3U> many
  {{
    std::any(42),                  // int
    std::any(1.23F),               // float
    std::any(std::string("hello")) // std::string
  }};

  // Use random access on the container elements.
  int n = std::any_cast<int>(many[0U]);
  std::cout << "n   : " << n << std::endl;

  float f = std::any_cast<float>(many[1U]);
  std::cout << "f   : " << f << std::endl;

  std::string str =
    std::any_cast<std::string>(many[2U]);
  std::cout << "str : " << str << std::endl;

  // Query the container size.
  const std::size_t size = many.size();
  std::cout << "size: " << size << std::endl;

  // Iterate in an algorithm
  // and use a member function.
  // 42
  // 1.23
  // hello
  // 3

  const bool has_many_values =
    std::all_of(many.cbegin(),
                many.cend(),
                [](const std::any& a) -> bool
                {
                  return a.has_value();
                });

  std::cout << "has_many_values: " << std::boolalpha << has_many_values << std::endl;
}

int main()
{
  do_something();
}
