///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2019.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

// chapter06_09-002_typedef_led_template.cpp

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

template<typename port_type,
         typename bval_type>
class led_template
{
public:
  led_template(const port_type port,
               const bval_type bval) : my_port(port),
                                       my_bval(bval)
  {
    // Set the port pin value to low.
    port_pin_type::bit_clr(my_port, my_bval);
  }

  void toggle()
  {
    // Toggle the LED.
    port_pin_type::bit_not(my_port, my_bval);
  }

private:
  const port_type my_port;
  const bval_type my_bval;

  // Type definition of the port data register.
  typedef reg_access_dynamic<std::uintptr_t,
                             std::uint8_t> port_pin_type;
};

// The simulated portb.
std::uint8_t simulated_register_portb;

const std::uintptr_t address =
  reinterpret_cast<std::uintptr_t>(&simulated_register_portb);

int main()
{
  typedef led_template<std::uintptr_t, std::uint8_t> led_b5_type;

  led_b5_type led_b5(address, 5U);

  for(;;)
  {
    led_b5.toggle();

    std::cout << "simulated_register_portb: "
              << std::hex
              << "0x"
              << std::setw(2)
              << std::setfill(char('0'))
              << unsigned(simulated_register_portb)
              << std::endl;
  }
}
