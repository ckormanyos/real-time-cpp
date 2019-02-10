///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2019.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

// appendix0a_12-001_range_based_for.cpp

#include <cstdint>
#include <iostream>
#include <vector>

void do_something()
{
  // Set v to (1,2,3).
  std::vector<char> v =
  {
    char(1),
    char(2),
    char(3)
  };

  // Add 0x30 to each element in v,
  // giving (0x31,0x32,0x33).
  // Use range-based-for(:).
  for(char& c : v)
  {
    c += char(0x30);
  }

  // Print v as characters.
  std::cout << "v: ";
  for(char c : v) { std::cout << c << ","; }
  std::cout << std::endl;

  // Print v as integers.
  std::cout << "v: ";
  for(char c : v) { std::cout << "0x" << std::hex << std::uint32_t(c) << ","; }
  std::cout << std::endl;
}

int main()
{
  do_something();
}
