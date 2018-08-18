///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2018.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

// chapter06_06-001_name_mangling.cpp

#include <iostream>

namespace this_space
{
  int the_int;
}

namespace another_space
{
  int the_int;
}

void do_something()
{
  this_space::the_int    = 123;
  another_space::the_int =  42;

  std::cout << this_space::the_int    << std::endl;
  std::cout << another_space::the_int << std::endl;
}

int main()
{
  do_something();
}
