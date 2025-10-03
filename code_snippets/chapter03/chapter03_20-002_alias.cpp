///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2017 - 2025.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

// chapter03_20-002_alias.cpp

#include <algorithm>
#include <array>
#include <cstdint>
#include <iostream>

auto do_something() -> void
{
  // Alias for unsigned int.
  using uint_type     = unsigned int;

  // Alias for array of uint_type.
  using array_type    = std::array<uint_type, 3U>;

  // Alias for reverse iterator of array of uint_type.
  using reverse_iterator_type =
    array_type::const_reverse_iterator;

  constexpr array_type my_array( {{ 1U, 2U, 3U }} );

  // Find result is 2.
  const reverse_iterator_type ri =
    std::find(my_array.crbegin(),
              my_array.crend(),
              2U);

  std::cout << "find result is " << *ri << std::endl;
}

auto main() -> int
{
  do_something();
}
