///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2019.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

// chapter07_02-001_register_access.cpp

#include <iostream>
#include <cstdint>

template<typename addr_type,
         typename reg_type>
struct reg_access_dynamic
{
  static void reg_set(const addr_type addr,
                      const reg_type val)
  {
    *reinterpret_cast<volatile reg_type*>(addr) = val;
  }
};

// The simulated portb.
std::uint8_t simulated_register_portb;

const std::uintptr_t address = reinterpret_cast<std::uintptr_t>(&simulated_register_portb);

void do_something()
{
  // Set portb to 0.
  reg_access_dynamic<std::uintptr_t, std::uint8_t>::reg_set(address, 0x0U);
}

int main()
{
  do_something();

  std::cout << "simulated_register_portb: "
            << unsigned(simulated_register_portb)
            << std::endl;
}
