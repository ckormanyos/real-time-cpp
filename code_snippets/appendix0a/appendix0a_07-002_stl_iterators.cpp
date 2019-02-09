///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2019.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

// appendix0a_07-002_stl_iterators.cpp

#include <algorithm>
#include <array>
#include <iostream>
#include <vector>

void do_something()
{
  // Initialized src with (101, 101, 101).
  const std::vector<int> src(3U, 101);

  std::cout << "src: ";
  for(int element : src) { std::cout << element << ","; }
  std::cout << std::endl;

  // Default-initialized dst.
  std::array<int, 3U> dst = {{ }};

  std::cout << "dst: ";
  for(int element : dst) { std::cout << element << ","; }
  std::cout << std::endl;

  // Copy from vector src to array dst.
  // dst now also contains (101, 101, 101).
  std::copy(src.begin(), src.end(), dst.begin());

  std::cout << "dst: ";
  for(int element : dst) { std::cout << element << ","; }
  std::cout << std::endl;
}

int main()
{
  do_something();
}
