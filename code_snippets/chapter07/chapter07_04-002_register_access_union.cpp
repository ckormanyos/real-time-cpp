///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2019.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

// chapter07_04-002_register_access_union.cpp

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

typedef union reg_map_c
{
  std::uint8_t value;
  bit8_type    bits;
}
reg_map_c;

// The simulated portb.
std::uint8_t simulated_register_portb;

const std::uintptr_t address =
  reinterpret_cast<std::uintptr_t>(&simulated_register_portb);

void do_something()
{
  // Set portb to 0.
  reinterpret_cast<volatile reg_map_c*>(address)->value = UINT8_C(0);

  // Set portb.5 to 1.
  reinterpret_cast<volatile reg_map_c*>(address)->bits.b5 = 1U;
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
