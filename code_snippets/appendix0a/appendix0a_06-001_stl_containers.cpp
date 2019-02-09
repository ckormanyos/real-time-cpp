///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2019.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

// appendix0a_06-001_stl_containers.cpp

#include <cstdint>
#include <limits>
#include <iomanip>
#include <iostream>
#include <vector>

void do_something()
{
  // Create v with three elements having value 0.
  std::vector<int> v(3U, 0);

  std::cout << "v: ";
  for(int element : v) { std::cout << element << ","; }
  std::cout << std::endl;

  // Set the values in v to (1,2,3).
  v[0U] = 1;
  v[1U] = 2;
  v[2U] = 3;

  std::cout << "v: ";
  for(int element : v) { std::cout << element << ","; }
  std::cout << std::endl;

  // The initial size is 3.
  std::vector<int>::size_type s = v.size();

  std::cout << "v.size(): " << s << std::endl;

  v.push_back(4);

  // The size is now 4.
  s = v.size();

  std::cout << "v.size(): " << s << std::endl;

  int x0 = v.at(0U); // Value of x0 is 1.
  int x3 = v.back(); // Value of x3 is 4.

  std::cout << "v.at(0U): " << x0 << std::endl;
  std::cout << "v.back(): " << x3 << std::endl;

  // Copy constructor from another vector.
  std::vector<int> v2(v);

  std::cout << "v2: ";
  for(int element : v2) { std::cout << element << ","; }
  std::cout << std::endl;

  // Constructor from other input iterators.
  std::vector<int> v3(v.begin(), v.end());

  std::cout << "v3: ";
  for(int element : v3) { std::cout << element << ","; }
  std::cout << std::endl;

  // Support for operator=().
  std::vector<int> v4 = v;

  std::cout << "v4: ";
  for(int element : v4) { std::cout << element << ","; }
  std::cout << std::endl;
}

int main()
{
  do_something();
}
