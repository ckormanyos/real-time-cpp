///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2017 - 2018.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

// chapter03_16-002_binary_literals.cpp

#include <cstdint>
#include <iomanip>
#include <iostream>

// The simulated portb register.
static std::uint8_t simulated_portb;

void do_something()
{
  // Switch portb.5 from low to high.
  *reinterpret_cast<volatile std::uint8_t*>(&simulated_portb)
    |= UINT8_C(0b0010'0000);
}

int main()
{
  do_something();

  std::cout << "simulated portb is "
            << std::hex
            << std::showbase
            << unsigned(simulated_portb)
            << std::endl;
}
