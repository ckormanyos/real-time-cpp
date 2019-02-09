///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2019.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

// appendix0a_02-004_uniform_initialization.cpp

#include <iostream>

struct point
{
  point(const int x = 0,
        const int y = 0) : my_x{x},
                            my_y{y} { }

  int my_x;
  int my_y;
};

point pt
{
  123,
  456
};

int main()
{
  std::cout << "pt.my_x: " << pt.my_x << std::endl;
  std::cout << "pt.my_y: " << pt.my_y << std::endl;
}
