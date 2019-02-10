///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2019.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

// appendix0a_13-001_tuple_basics.cpp

#include <iostream>
#include <tuple>

using tuple_type = std::tuple<float, char, int>;

void do_something()
{
  // Make a tuple from float, char and int.
  tuple_type t(1.23F, char('a'), 456);

  // Get element 0 of the tuple (1.23F).
  const float f = std::get<0>(t);
  std::cout << "f from tuple t : " << f << std::endl;

  // Get element 1 of the tuple ('a').
  const char c = std::get<1>(t);
  std::cout << "c from tuple t : " << c << std::endl;

  // Get element 2 of the tuple (456).
  int n = std::get<2>(t);
  std::cout << "n from tuple t : " << n << std::endl;

  // Obtain a the type of a tuple element.
  using tuple_float_type =
    std::tuple_element<0, tuple_type>::type;

  static_assert(std::is_same<float,
                tuple_float_type>::value);

  // Get the size of the tuple.
  int size = std::tuple_size<tuple_type>::value;

  std::cout << "size of tuple t: " << size << std::endl;
}

int main()
{
  do_something();
}
