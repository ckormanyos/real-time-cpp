///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2019.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

// appendix0a_15-002_type_traits.cpp

#include <iomanip>
#include <iostream>
#include <type_traits>

// The variable pv is volatile.
volatile int* pv = nullptr;

// Remove the volatile qualifier.
auto pu = std::remove_volatile<int*>::type(pv);

// Verify that the type of pu is not volatile.
// In other words, volatile has been removed.

constexpr bool volatile_has_been_removed =
  (std::is_volatile<decltype(pu)>::value == false);

int main()
{
  std::cout << "volatile_has_been_removed: "
            << std::boolalpha
            <<  volatile_has_been_removed
            << std::endl;
}
