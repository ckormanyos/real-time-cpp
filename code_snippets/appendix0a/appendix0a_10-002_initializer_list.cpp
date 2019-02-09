///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2019.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

// appendix0a_10-002_initializer_list.cpp

#include <initializer_list>
#include <iostream>
#include <numeric>

constexpr std::initializer_list<int> lst {1, 2, 3};

// The result is 6.
const int sum = std::accumulate(std::begin(lst),
                                std::end(lst),
                                0);

int main()
{
  std::cout << "sum: " << sum << std::endl;
}
