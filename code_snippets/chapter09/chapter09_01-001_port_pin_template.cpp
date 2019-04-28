///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2019.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

// chapter09_01-001_port_pin_template.cpp

#include <iostream>

template<typename addr_type,
         typename reg_type>
struct reg_access_dynamic final
{
  static reg_type
              reg_get(const addr_type address) { return *reinterpret_cast<volatile reg_type*>(address); }

  static void reg_set(const addr_type address, const reg_type value) { *reinterpret_cast<volatile reg_type*>(address)  = value; }
  static void reg_and(const addr_type address, const reg_type value) { *reinterpret_cast<volatile reg_type*>(address) &= value; }
  static void reg_or (const addr_type address, const reg_type value) { *reinterpret_cast<volatile reg_type*>(address) |= value; }
  static void reg_not(const addr_type address, const reg_type value) { *reinterpret_cast<volatile reg_type*>(address) &= reg_type(~value); }
  static void reg_msk(const addr_type address, const reg_type value,
                      const reg_type mask_value)                     { *reinterpret_cast<volatile reg_type*>(address) = reg_type(reg_type(reg_get(address) & reg_type(~mask_value)) | reg_type(value & mask_value)); }

  static void bit_set(const addr_type address, const reg_type value) { *reinterpret_cast<volatile reg_type*>(address) |= static_cast<reg_type>(1UL << value); }
  static void bit_clr(const addr_type address, const reg_type value) { *reinterpret_cast<volatile reg_type*>(address) &= static_cast<reg_type>(~static_cast<reg_type>(1UL << value)); }
  static void bit_not(const addr_type address, const reg_type value) { *reinterpret_cast<volatile reg_type*>(address) ^= static_cast<reg_type>(1UL << value); }
  static bool bit_get(const addr_type address, const reg_type value) { return (static_cast<volatile reg_type>(reg_get(address) & static_cast<reg_type>(1UL << value)) != static_cast<reg_type>(0U)); }
};

template<typename addr_type,
         typename reg_type,
         const reg_type bpos>
class port_pin
{
public:
  static void set_direction_output(const addr_type address)
  {
    std::cout << "Set the port pin direction to output." << std::endl;

    // Set the port pin direction to output.
    pin_is_output = true;

    const addr_type pdir = address - 1U;

    port_register_type::bit_set(pdir, bpos);
  }

  static void set_direction_input(const addr_type address)
  {
    std::cout << "Set the port pin direction to input." << std::endl;

    // Set the port pin direction to input.
    pin_is_output = true;

    const addr_type pdir = address - 1U;

    port_register_type::bit_clr(pdir, bpos);
  }

  static void set_pin_high(const addr_type address)
  {
    std::cout << "Set the port pin output value to high." << std::endl;

    // Set the port output value to high.
    pin_is_high = true;

    port_register_type::bit_set(address, bpos);
  }

  static void set_pin_low(const addr_type address)
  {
    std::cout << "Set the port pin output value to low." << std::endl;

    // Set the port output value to low.
    pin_is_high = false;

    port_register_type::bit_clr(address, bpos);
  }

  static bool read_input_value(const addr_type address)
  {
    std::cout << "Read the port pin input value." << std::endl;

    // Read the port input value.
    const bool pin_input_value_is_high =
      ((pin_is_output == false) && (pin_is_high == true));

    return pin_input_value_is_high;
  }

  static void toggle(const addr_type address)
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
bool port_pin<addr_type, reg_type, bpos>::pin_is_output;

template<typename addr_type,
         typename reg_type,
         const reg_type bpos>
bool port_pin<addr_type, reg_type, bpos>::pin_is_high;

// The simulated portd.
std::uint8_t simulated_register_portd;

const std::uintptr_t address =
  reinterpret_cast<std::uintptr_t>(&simulated_register_portd);

void do_something()
{
  // Toggle the simulated portd.0.
  using simulated_port_d0_type =
    port_pin<std::uintptr_t, std::uint8_t, 0U>;

  simulated_port_d0_type::set_pin_high(address);
  simulated_port_d0_type::set_direction_output(address);

  const bool pin_input_value_is_high =
    simulated_port_d0_type::read_input_value(address);

  static_cast<void>(pin_input_value_is_high);

  simulated_port_d0_type::toggle(address);
}

int main() noexcept
{
  do_something();
}
