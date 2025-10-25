///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2019 - 2025.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

// chapter09_01-001_port_pin_template.cpp

#include <cstdint>
#include <iostream>

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

template<typename addr_type,
         typename reg_type,
         const reg_type bpos>
class port_pin
{
public:
  static auto set_direction_output(const addr_type address) -> void
  {
    std::cout << "Set the port pin direction to output." << std::endl;

    // Set the port pin direction to output.
    pin_is_output = true;

    const addr_type pdir = address - 1U;

    port_register_type::bit_set(pdir, bpos);
  }

  static auto set_direction_input(const addr_type address) -> void
  {
    std::cout << "Set the port pin direction to input." << std::endl;

    // Set the port pin direction to input.
    pin_is_output = true;

    const addr_type pdir = address - 1U;

    port_register_type::bit_clr(pdir, bpos);
  }

  static auto set_pin_high(const addr_type address) -> void
  {
    std::cout << "Set the port pin output value to high." << std::endl;

    // Set the port output value to high.
    pin_is_high = true;

    port_register_type::bit_set(address, bpos);
  }

  static auto set_pin_low(const addr_type address) -> void
  {
    std::cout << "Set the port pin output value to low." << std::endl;

    // Set the port output value to low.
    pin_is_high = false;

    port_register_type::bit_clr(address, bpos);
  }

  static auto read_input_value(const addr_type address) -> bool
  {
    static_cast<void>(address);

    std::cout << "Read the port pin input value." << std::endl;

    // Read the port input value.
    const bool pin_input_value_is_high =
      ((pin_is_output == false) && (pin_is_high == true));

    return pin_input_value_is_high;
  }

  static auto toggle(const addr_type address) -> void
  {
    std::cout << "Toggle the port pin output value." << std::endl;

    // Toggle the port output value.
    port_register_type::bit_not(address, bpos);
  }

private:
  static bool pin_is_output;
  static bool pin_is_high;

  using port_register_type = reg_access_dynamic<addr_type, reg_type>;
};

template<typename addr_type,
         typename reg_type,
         const reg_type bpos>
bool port_pin<addr_type, reg_type, bpos>::pin_is_output { };

template<typename addr_type,
         typename reg_type,
         const reg_type bpos>
bool port_pin<addr_type, reg_type, bpos>::pin_is_high { };

// The simulated portd.
std::uint8_t simulated_register_portd;

const std::uintptr_t address
  { reinterpret_cast<std::uintptr_t>(&simulated_register_portd) };

auto do_something() -> void;

auto do_something() -> void
{
  // Toggle the simulated portd.0.
  using simulated_port_d0_type =
    port_pin<std::uintptr_t, std::uint8_t, 0U>;

  simulated_port_d0_type::set_pin_high(address);
  simulated_port_d0_type::set_direction_output(address);

  const bool pin_input_value_is_high
    { simulated_port_d0_type::read_input_value(address) };

  static_cast<void>(pin_input_value_is_high);

  simulated_port_d0_type::toggle(address);
}

auto main() -> int;

auto main() -> int
{
  do_something();
}
