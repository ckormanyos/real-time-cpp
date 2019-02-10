///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2019.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

// appendix0a_13-002_tuple_assign.cpp

#include <iostream>
#include <tuple>

void do_something()
{
  using tuple_type = std::tuple<float, char, int>;

  tuple_type t;

  // Assign the tuple t using std::make_tuple.
  t = std::make_tuple(1.23F, char('a'), 456);

  // Get element 0 of the tuple (1.23F).
  const float f = std::get<0>(t);

  // Get element 1 of the tuple ('a').
  const char c = std::get<1>(t);

  // Get element 2 of the tuple (456).
  int n = std::get<2>(t);

  std::cout << "f from tuple t : " << f << std::endl;
  std::cout << "c from tuple t : " << c << std::endl;
  std::cout << "n from tuple t : " << n << std::endl;
}

int main()
{
  do_something();
}
