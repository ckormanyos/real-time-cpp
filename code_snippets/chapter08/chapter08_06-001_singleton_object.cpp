///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2019.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

// chapter08_05-002_static_initialization.cpp

#include <cstdint>
#include <iomanip>
#include <iostream>

namespace
{
  char         c    = '\0';       // Not necessary.
  std::uint8_t key  = UINT8_C(0); // Not necessary.
  float        f    = 0.0F;       // Not necessary.
  bool         flag = false;      // Not necessary.
}

struct protocol_frame
{
  static std::uint8_t count;
  protocol_frame() { }
};

// Not necessary.
std::uint8_t protocol_frame::count = UINT8_C(0);

int main()
{
  std::cout.setf(std::ios::boolalpha);
  std::cout.setf(std::ios::fixed);

  std::cout << "c                    : " << static_cast<std::uint32_t>(c)                     << std::endl;
  std::cout << "key                  : " << static_cast<std::uint32_t>(key)                   << std::endl;
  std::cout << "f                    : " << f                                                 << std::endl;
  std::cout << "flag                 : " << flag                                              << std::endl;
  std::cout << "protocol_frame::count: " << static_cast<std::uint32_t>(protocol_frame::count) << std::endl;
}
