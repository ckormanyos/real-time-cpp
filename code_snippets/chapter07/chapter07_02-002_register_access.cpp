///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2019.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

// chapter07_02-002_register_access.cpp

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

// The simulated timer0 mode register.
std::uint8_t simulated_register_tm0ctl0;

// The simulated timer0 compare0 register.
std::uint16_t simulated_register_tm0cmp0;

void do_something()
{
  const std::uintptr_t address_tm0ctl0 =
    reinterpret_cast<std::uintptr_t>(&simulated_register_tm0ctl0);

  // Set the simulated timer0 mode register to 0.
  reg_access_dynamic<std::uintptr_t, std::uint8_t>::reg_set(address_tm0ctl0, 0x0U);

  const std::uintptr_t address_tm0cmp0 =
    reinterpret_cast<std::uintptr_t>(&simulated_register_tm0cmp0);

  // Set the simulated timer0 compare0 register to 32,000 - 1.
  reg_access_dynamic<std::uintptr_t, std::uint16_t>::reg_set(address_tm0cmp0, 32000UL - 1UL);
}

int main()
{
  do_something();

  std::cout << "simulated_register_tm0ctl0: "
            << unsigned(simulated_register_tm0ctl0)
            << std::endl;

  std::cout << "simulated_register_tm0cmp0: "
            << unsigned(simulated_register_tm0cmp0)
            << std::endl;
}
