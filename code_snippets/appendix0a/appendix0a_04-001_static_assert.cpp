///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2019.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

// appendix0a_04-001_static_assert.cpp

#include <iostream>

static_assert(true, "ok");

// This static_assert should result in a compile-time error.
//static_assert(false, "not ok");

int main()
{
  std::cout << "static_assert: ok" << std::endl;
}
