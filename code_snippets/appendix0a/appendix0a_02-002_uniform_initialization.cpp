///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2019.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

// appendix0a_02-002_uniform_initialization.cpp

#include <iostream>

struct my_struct
{
  int   my_n;
  float my_f;

  my_struct(const int    n = 0,
            const float& f = 0.0F) : my_n(n),
                                     my_f(f) { }
};

my_struct instance
{
  123,                     // Initial value of n.
  3.1415926535'8979323846F // Initial value of f.
};

int main()
{
  std::cout << "instance.my_n: " << instance.my_n << std::endl;
  std::cout << "instance.my_f: " << instance.my_f << std::endl;
}
