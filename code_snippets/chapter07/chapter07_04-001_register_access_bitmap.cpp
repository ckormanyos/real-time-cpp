///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2019.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

// chapter07_04-001_register_access_bitmap.cpp

#include <iomanip>
#include <iostream>
#include <cstdint>

typedef struct bit8_type
{
  std::uint8_t b0 : 1;
  std::uint8_t b1 : 1;
  std::uint8_t b2 : 1;
  std::uint8_t b3 : 1;
  std::uint8_t b4 : 1;
  std::uint8_t b5 : 1;
  std::uint8_t b6 : 1;
  std::uint8_t b7 : 1;
}
bit8_type;

// The simulated portb.
std::uint8_t simulated_register_portb;

const std::uintptr_t address =
  reinterpret_cast<std::uintptr_t>(&simulated_register_portb);

void do_something()
{
  // Set the simulated portb.5.
  reinterpret_cast<volatile bit8_type*>(address)->b5 = 1U;
}

int main()
{
  do_something();

  std::cout << "simulated_register_portb: "
            << std::hex
            << "0x"
            << std::setw(2)
            << unsigned(simulated_register_portb)
            << std::endl;
}
