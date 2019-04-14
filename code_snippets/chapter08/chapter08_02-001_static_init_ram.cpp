///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2019.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

// chapter08_02-001_static_init_ram.cpp

#include <cstdint>
#include <iostream>

namespace
{
  // Needs zero-clear.
  std::uint16_t flag;

  // Needs ROM-to-RAM init.
  std::uint8_t  version = UINT8_C(3);
}


int main()
{
  std::cout << "flag   : " << unsigned(flag)    << std::endl;
  std::cout << "version: " << unsigned(version) << std::endl;
}
