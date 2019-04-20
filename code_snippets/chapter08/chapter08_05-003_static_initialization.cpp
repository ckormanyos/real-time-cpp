///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2019.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

// chapter08_05-003_static_initialization.cpp

#include <cstdint>
#include <iomanip>
#include <iostream>

namespace
{
  char         c    = 'A';        // Explicit init.
  std::uint8_t key  = UINT8_C(3); // Explicit init.
  float        f    = 4.56F;      // Explicit init.
  bool         flag = true;       // Explicit init.
}

struct protocol_frame
{
  static std::uint8_t count;
  protocol_frame() { }
};

// Explicit init.
std::uint8_t protocol_frame::count = UINT8_C(42);

int main()
{
  std::cout.setf(std::ios::boolalpha);
  std::cout.setf(std::ios::fixed);

  std::cout << "c                    : " << c                                                 << std::endl;
  std::cout << "key                  : " << static_cast<std::uint32_t>(key)                   << std::endl;
  std::cout << "f                    : " << f                                                 << std::endl;
  std::cout << "flag                 : " << flag                                              << std::endl;
  std::cout << "protocol_frame::count: " << static_cast<std::uint32_t>(protocol_frame::count) << std::endl;
}
