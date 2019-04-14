///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2019.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

// chapter06_14-002_romable_array.cpp

#include <array>
#include <iostream>

namespace
{
  // A version that is compile-time constant.
  constexpr std::array<char, 5U> version_string
  {
    { '1', '.', '2', '3', '\0' }
  };
}

int main()
{
  std::cout << "version_string: " << version_string.data() << std::endl;
}
