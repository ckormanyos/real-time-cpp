///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2019.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

// chapter08_05-001_static_initialization.cpp

#include <cstdint>
#include <iomanip>
#include <iostream>

namespace
{
  char         c;    // Default initialized.
  std::uint8_t key;  // Default initialized.
  float        f;    // Default initialized.
  bool         flag; // Default initialized.
}

struct protocol_frame
{
  static std::uint8_t count;
  protocol_frame() { }
};

// Default initialized.
std::uint8_t protocol_frame::count;

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
