///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2019 - 2025.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

// chapter06_09-001_alias_reg_access.cpp

#include <cstdint>
#include <iomanip>
#include <iostream>
#include <sstream>

template<typename RegisterAddressType,
         typename RegisterValueType>
struct reg_access_dynamic final
{
  using register_address_type = RegisterAddressType;
  using register_value_type   = RegisterValueType;

  static auto reg_get(const register_address_type address) -> register_value_type                   { return *reinterpret_cast<volatile register_value_type*>(address); }
  static auto reg_set(const register_address_type address, const register_value_type value) -> void { volatile register_value_type* pa = reinterpret_cast<volatile register_value_type*>(address); *pa = value; }
  static auto reg_and(const register_address_type address, const register_value_type value) -> void { volatile register_value_type* pa = reinterpret_cast<volatile register_value_type*>(address); *pa = static_cast<register_value_type>(*pa & value); }
  static auto reg_or (const register_address_type address, const register_value_type value) -> void { volatile register_value_type* pa = reinterpret_cast<volatile register_value_type*>(address); *pa = static_cast<register_value_type>(*pa | value); }
  static auto reg_not(const register_address_type address, const register_value_type value) -> void { volatile register_value_type* pa = reinterpret_cast<volatile register_value_type*>(address); *pa = static_cast<register_value_type>(*pa & static_cast<register_value_type>(~value)); }

  static auto reg_msk(const register_address_type address,
                      const register_value_type   value,
                      const register_value_type   mask_value) -> void
  {
    volatile register_value_type* pa = reinterpret_cast<volatile register_value_type*>(address);

    *pa =
      static_cast<register_value_type>
      (
          static_cast<register_value_type>(reg_get(address) & static_cast<register_value_type>(~mask_value))
        | value
      );
  }

  static auto bit_set(const register_address_type address, const register_value_type value) -> void { volatile register_value_type* pa = reinterpret_cast<volatile register_value_type*>(address); *pa = static_cast<register_value_type>(*pa | static_cast<register_value_type>(1UL << value)); }
  static auto bit_clr(const register_address_type address, const register_value_type value) -> void { volatile register_value_type* pa = reinterpret_cast<volatile register_value_type*>(address); *pa = static_cast<register_value_type>(*pa & static_cast<register_value_type>(~static_cast<register_value_type>(1UL << value))); }
  static auto bit_not(const register_address_type address, const register_value_type value) -> void { volatile register_value_type* pa = reinterpret_cast<volatile register_value_type*>(address); *pa = static_cast<register_value_type>(*pa ^ static_cast<register_value_type>(1UL << value)); }
  static auto bit_get(const register_address_type address, const register_value_type value) -> bool { return (static_cast<register_value_type>(reg_get(address) & static_cast<register_value_type>(1UL << value)) != static_cast<register_value_type>(0U)); }
};

// The simulated portb.
auto simulated_register_portb = std::uint8_t { };

const auto address = reinterpret_cast<std::uintptr_t>(&simulated_register_portb);

auto do_something() -> void;

auto do_something() -> void
{
  // Use a convenient alias to save tedious typing work.
  using port_type = reg_access_dynamic<std::uintptr_t, std::uint8_t>;

  // Toggle the simulated portb.5.
  port_type::bit_not(address, static_cast<std::uint8_t>(UINT8_C(5)));
}

auto main() -> int;

auto main() -> int
{
  for(auto i = static_cast<unsigned>(UINT8_C(0)); i < static_cast<unsigned>(UINT8_C(4)); ++i)
  {
    do_something();

    std::stringstream strm { };

    strm << "simulated_register_portb: "
         << std::hex
         << "0x"
         << std::setw(static_cast<std::streamsize>(INT8_C(2)))
         << std::setfill('0')
         << static_cast<unsigned>(simulated_register_portb);

    std::cout << strm.str() << std::endl;
  }
}
