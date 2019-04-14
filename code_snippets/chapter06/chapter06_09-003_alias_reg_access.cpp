///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2019.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

// chapter06_09-003_alias_reg_access.cpp

#include <iomanip>
#include <iostream>
#include <cstdint>

template<typename register_address_type,
         typename register_value_type>
struct reg_access_dynamic final
{
  static register_value_type
              reg_get(const register_address_type address) { return *reinterpret_cast<volatile register_value_type*>(address); }

  static void reg_set(const register_address_type address, const register_value_type value) { *reinterpret_cast<volatile register_value_type*>(address)  = value; }
  static void reg_and(const register_address_type address, const register_value_type value) { *reinterpret_cast<volatile register_value_type*>(address) &= value; }
  static void reg_or (const register_address_type address, const register_value_type value) { *reinterpret_cast<volatile register_value_type*>(address) |= value; }
  static void reg_not(const register_address_type address, const register_value_type value) { *reinterpret_cast<volatile register_value_type*>(address) &= register_value_type(~value); }
  static void reg_msk(const register_address_type address, const register_value_type value,
                      const register_value_type mask_value)                                 { *reinterpret_cast<volatile register_value_type*>(address) = register_value_type(register_value_type(reg_get(address) & register_value_type(~mask_value)) | register_value_type(value & mask_value)); }

  static void bit_set(const register_address_type address, const register_value_type value) { *reinterpret_cast<volatile register_value_type*>(address) |= static_cast<register_value_type>(1UL << value); }
  static void bit_clr(const register_address_type address, const register_value_type value) { *reinterpret_cast<volatile register_value_type*>(address) &= static_cast<register_value_type>(~static_cast<register_value_type>(1UL << value)); }
  static void bit_not(const register_address_type address, const register_value_type value) { *reinterpret_cast<volatile register_value_type*>(address) ^= static_cast<register_value_type>(1UL << value); }
  static bool bit_get(const register_address_type address, const register_value_type value) { return (static_cast<volatile register_value_type>(reg_get(address) & static_cast<register_value_type>(1UL << value)) != static_cast<register_value_type>(0U)); }
};

// The simulated portb.
std::uint8_t simulated_register_portb;

const std::uintptr_t address =
  reinterpret_cast<std::uintptr_t>(&simulated_register_portb);

void do_something()
{
  // Use an alias to save tedious typing work.
  using port_type = reg_access_dynamic<std::uintptr_t, std::uint8_t>;

  // Toggle the simulated portb.5.
  port_type::bit_not(address, 5u);
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
