///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2019.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

// appendix0a_04-003_static_assert.cpp

#include <iostream>

constexpr unsigned int version = 3U;

// Print default error message if version is not 3.
static_assert(version == 3U);

int main()
{
  std::cout << "version == 3U: ok" << std::endl;
}
