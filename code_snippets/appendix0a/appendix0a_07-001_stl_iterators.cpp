///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2019.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

// appendix0a_07-001_stl_iterators.cpp

#include <iostream>
#include <vector>

void do_something()
{
  // Set v to (1,2,3).
  std::vector<int> v( { 1, 2, 3 } );

  std::cout << "v: ";
  for(int element : v) { std::cout << element << ","; }
  std::cout << std::endl;

  // Declare an iterator for std::vector<int>.
  std::vector<int>::iterator it;

  // Add 5 to each element in v.
  for(it = v.begin(); it != v.end(); ++it)
  {
    *it += 5;
  }

  // Now v is (6,7,8).

  std::cout << "v: ";
  for(int element : v) { std::cout << element << ","; }
  std::cout << std::endl;
}

int main()
{
  do_something();
}
