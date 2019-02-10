///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2019.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

// appendix0a_11-002_type_inference.cpp

#include <array>
#include <iostream>

void do_something()
{
  const std::array<int, 3U> a = {{ 1, 2, 3 }};

  // Use long type information of const_iterator.
  for(std::array<int, 3U>::const_iterator i = a.cbegin();
      i != a.cend();
      ++i)
  {
    std::cout << *i << ",";
  }
  std::cout << std::endl;

  // Use type inference of const_iterator.
  for(auto i = a.cbegin(); i != a.cend(); ++i)
  {
    std::cout << *i << ",";
  }
  std::cout << std::endl;

  // Use type inference of const_iterator,
  // and use generic std::cbegin() and std::cend().
  for(auto i = std::cbegin(a); i != std::cend(a); ++i)
  {
    std::cout << *i << ",";
  }
  std::cout << std::endl;
}

int main()
{
  do_something();
}
