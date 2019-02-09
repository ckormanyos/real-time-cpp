///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2019.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

// appendix0a_04-002_static_assert.cpp

#include <iostream>

constexpr unsigned int version = 3U;

// Print error message if version is less than 2.
static_assert(version >= 2U, "Version is too low!");

int main()
{
  std::cout << "version >= 2U: ok" << std::endl;
}
