///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2019.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

// appendix0a_10-001_initializer_list.cpp

#include <algorithm>
#include <iostream>
#include <iterator>
#include <vector>

using container_type = std::vector<int>;

// Initialization with the assignment operator.
container_type c1 = { 1, 2, 3 };

// Initialization with the constructor.
container_type c2( { 1, 2, 3 } );

// Uniform initialization syntax.
container_type c3 { { 1, 2, 3 } };

int main()
{
  std::cout << "c1: ";
  std::copy(c1.cbegin(), c1.cend(), std::ostream_iterator<int>(std::cout, ","));
  std::cout << std::endl;

  std::cout << "c2: ";
  std::copy(c2.cbegin(), c2.cend(), std::ostream_iterator<int>(std::cout, ","));
  std::cout << std::endl;

  std::cout << "c3: ";
  std::copy(c3.cbegin(), c3.cend(), std::ostream_iterator<int>(std::cout, ","));
  std::cout << std::endl;
}
