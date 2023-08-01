///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2019.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

// appendix0a_01-002_reinterpret_cast.cpp

#include <cstdint>
#include <iomanip>
#include <iostream>

// Here, portb is of type std::uint8_t having
// a statically determined address, where the
// address is determined by the compiler/linker.
std::uint8_t portb;

int main()
{
  // Cast std::uint8_t to std::uint8_t*.
  // For PC simulation, use the address of portb.
  volatile std::uint8_t* pb = reinterpret_cast<volatile std::uint8_t*>(&portb);

  // Set portb.5.
  *pb = static_cast<std::uint8_t>(*pb | static_cast<std::uint8_t>(UINT8_C(0x20)));

  std::cout << "portb: 0x"
            << std::hex
            << std::uppercase
            << std::setw(2)
            << std::setfill(char('0'))
            << std::uint32_t(portb)
            << std::endl;
}
