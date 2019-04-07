///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2019.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

// chapter07_01-002_register_address.cpp

#include <iostream>
#include <cstdint>

namespace mcal
{
  struct reg
  {
    static uint8_t simulated_address_of_portb_at_0x25;
  };
}

// The simulated portb.
uint8_t mcal::reg::simulated_address_of_portb_at_0x25;

void do_something()
{
  // Set portb to 0.
  *reinterpret_cast<volatile std::uint8_t*>(&mcal::reg::simulated_address_of_portb_at_0x25) = UINT8_C(0);
}

int main()
{
  do_something();

  std::cout << "mcal::reg::simulated_address_of_portb_at_0x25: "
            << unsigned(mcal::reg::simulated_address_of_portb_at_0x25)
            << std::endl;
}
