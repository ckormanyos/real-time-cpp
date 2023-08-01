///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2019 - 2023.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

// chapter07_03-003_register_access.cpp

#include <cstdint>
#include <iomanip>
#include <iostream>

template<typename RegisterAddressType,
         typename RegisterValueType>
struct reg_access_dynamic final
{
  using register_address_type = RegisterAddressType;
  using register_value_type   = RegisterValueType;

  static auto bit_not(const register_address_type address, const register_value_type value) -> void { volatile register_value_type* pa = reinterpret_cast<volatile register_value_type*>(address); *pa = static_cast<register_value_type>(*pa ^ static_cast<register_value_type>(1UL << value)); }
};

// The simulated portb.
std::uint8_t simulated_register_portb;

const std::uintptr_t address =
  reinterpret_cast<std::uintptr_t>(&simulated_register_portb);

void do_something()
{
  // Toggle the simulated portb.5.
  reg_access_dynamic<std::uintptr_t, std::uint8_t>::bit_not(address, 5u);
}

int main()
{
  do_something();

  std::cout << "simulated_register_portb: "
            << std::hex
            << "0x"
            << std::setw(2)
            << std::setfill(char('0'))
            << unsigned(simulated_register_portb)
            << std::endl;
}
