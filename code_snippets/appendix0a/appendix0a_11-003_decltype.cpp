///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2019.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

// appendix0a_11-003_decltype.cpp

#include <iomanip>
#include <iostream>
#include <type_traits>

// The type of a is int.
int a = 1;

// The type of b is int.
decltype(a) b = 2;

int main()
{
  constexpr bool type_of_b_is_int = std::is_same<decltype(a), int>::value;

  std::cout << std::boolalpha << "type_of_b_is_int: " << type_of_b_is_int << std::endl;
}
