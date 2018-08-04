///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2018.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

// chapter05_08-001_using_the_stl.cpp

#include <algorithm>
#include <iomanip>
#include <iostream>
#include <vector>

void do_something_with_the_stl()
{
  // Create v with the decimal values (1, 2, 3).
  // Initialize with a convenient initializer_list.

  std::vector<char> v { 1, 2, 3 };

  for(std::vector<char>::size_type i = 0U; i < v.size(); ++i)
  {
    std::cout << std::hex << std::showbase << unsigned(v[i]) << std::endl;
  }

  // Use an algorithm with a lambda function.
  // Convert from decimal int to ASCII char.

  std::for_each(v.begin(),
                v.end(),
                [](char& c)
                {
                  c += 0x30;
                });

  for(std::vector<char>::size_type i = 0U; i < v.size(); ++i)
  {
    std::cout << std::hex << std::showbase << unsigned(v[i]) << std::endl;
  }
}

int main()
{
  do_something_with_the_stl();
}
