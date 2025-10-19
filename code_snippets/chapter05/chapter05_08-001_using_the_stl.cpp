///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2018 - 2025.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

// chapter05_08-001_using_the_stl.cpp

#include <algorithm>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <vector>

auto do_something_with_the_stl() -> void;

auto do_something_with_the_stl() -> void
{
  // Create v with the decimal values (1, 2, 3).
  // Initialize with a convenient initializer_list.

  std::vector<char> v( { 1, 2, 3 } );

  {
    std::stringstream strm { };

    for(const auto& elem : v)
    {
      // Print as hex to prove values 1,2,3.
      strm << std::hex << std::showbase << unsigned(elem) << ',';
    }

    std::cout << strm.str() << std::endl;
  }

  // Use an algorithm with a lambda function.
  // Convert from decimal int to ASCII char.

  std::for_each(v.begin(),
                v.end(),
                [](char& c)
                {
                  c = char { static_cast<char>(c + '0') };
                });

  {
    std::stringstream strm { };

    for(const auto& elem : v)
    {
      // Print as ASCII characters.
      strm << elem << ',';
    }

    std::cout << strm.str() << std::endl;
  }
}

auto main() -> int;

auto main() -> int
{
  do_something_with_the_stl();
}
