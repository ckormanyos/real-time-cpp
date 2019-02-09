///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2019.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

// appendix0a_01-001_static_cast.cpp

#include <iostream>

float f = 3.1415926535'8979323846'264338328F;

// The value of n is 3.
int n = static_cast<int>(f);

int main()
{
  std::cout << "f: " << f << std::endl;
  std::cout << "n: " << n << std::endl;
}
