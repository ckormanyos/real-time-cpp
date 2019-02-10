///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2019.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

// appendix0a_15-001_type_traits.cpp

#include <iomanip>
#include <iostream>
#include <type_traits>

using integral_type = int;

// Query the characteristics of integral_type.

constexpr bool type_is_arithmetic =
  std::is_arithmetic<integral_type>::value;

constexpr bool type_is_integral =
  std::is_integral<integral_type>::value;

constexpr bool type_is_signed =
  std::is_signed<integral_type>::value;

int main()
{
  std::cout << std::boolalpha << "type_is_arithmetic: " << type_is_arithmetic << std::endl;
  std::cout << std::boolalpha << "type_is_integral  : " << type_is_integral   << std::endl;
  std::cout << std::boolalpha << "type_is_signed    : " << type_is_signed     << std::endl;
}
