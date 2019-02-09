///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2019.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

// appendix0a_02-005_uniform_initialization.cpp

#include <array>
#include <iostream>
#include <vector>

std::array<int, 3U> a
{
  { 1, 2, 3 }
};

std::vector<char> v
{
  { 'a', 'b', 'c' }
};

int main()
{
  for(int element_a : a)
  {
    std::cout << element_a << std::endl;
  }

  for(char element_v : v)
  {
    std::cout << element_v << std::endl;
  }
}
