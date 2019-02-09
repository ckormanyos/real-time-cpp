///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2019.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

// appendix0a_08-004_stl_algorithms.cpp

#include <algorithm>
#include <iostream>
#include <vector>

void do_something()
{
  // Set v to (1,2,3).
  std::vector<int> v(3U);

  v[0U] = 1;
  v[1U] = 2;
  v[2U] = 3;

  std::cout << "v: ";
  for(int element : v) { std::cout << element << ","; }
  std::cout << std::endl;

  // Add 5 to each element in v, giving (6,7,8).
  std::for_each(v.begin(),
                v.end(),
                [](int& elem)
                {
                  elem += 5;
                });

  std::cout << "v: ";
  for(int element : v) { std::cout << element << ","; }
  std::cout << std::endl;
}

int main()
{
  do_something();
}
