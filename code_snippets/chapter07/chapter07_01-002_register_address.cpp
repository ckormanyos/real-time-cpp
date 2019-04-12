///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2019.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

// chapter07_01-002_register_address.cpp

#include <cstdint>
#include <iostream>

static std::uint8_t simulated_register_portb;

void do_something()
{
  // Set portb to 0.
  *reinterpret_cast<volatile std::uint8_t*>(&simulated_register_portb) = UINT8_C(0);
}

int main()
{
  do_something();

  std::cout << "simulated_register_portb: "
            << unsigned(simulated_register_portb)
            << std::endl;
}
