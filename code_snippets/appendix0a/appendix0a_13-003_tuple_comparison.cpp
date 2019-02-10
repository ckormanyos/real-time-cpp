///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2018 - 2019.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

// appendix0a_13-003_tuple_comparison.cpp

#include <tuple>
#include <iomanip>
#include <iostream>

void do_something()
{
  using tuple_type = std::tuple<int, std::string>;

  tuple_type t1(456, "identical");
  tuple_type t2 = t1;
  tuple_type t3(t1);

  bool result;

  result = (t1 == t2);  // true
  std::cout << std::boolalpha << "result (t1 == t2): " << result << std::endl;

  result = (t1 == t3);  // true
  std::cout << std::boolalpha << "result (t1 == t3): " << result << std::endl;

  std::get<0>(t2) += 1; // 456 -> 457

  result = (t2 > t1);   // true
  std::cout << std::boolalpha << "result (t2  > t1): " << result << std::endl;

  // Now transform the std::string element
  // from "identical" to "xdentical".
  std::get<1>(t3).at(0U) = 'x';

  result = (t3 > t1);   // true
  std::cout << std::boolalpha << "result (t3  > t1): " << result << std::endl;
}

int main()
{
  do_something();
}
