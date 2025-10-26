///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2019 - 2025.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

// chapter06_09-002_alias_led_template.cpp

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

template<typename port_type,
         typename bval_type>
class led_template
{
private:
  using port_pin_type = reg_access_dynamic<std::uintptr_t, std::uint8_t>;

public:
  led_template(const port_type port,
               const bval_type bval) : my_port(port),
                                       my_bval(bval)
  {
    // Set the port pin value to low.
    port_pin_type::bit_clr(my_port, my_bval);
  }

  auto toggle() -> void
  {
    // Toggle the LED.
    port_pin_type::bit_not(my_port, my_bval);

    is_on = (!is_on);
  }

  auto get_is_on() const -> bool { return is_on; }

private:
  const port_type my_port;
  const bval_type my_bval;
  bool is_on { };
};

// The simulated portb.
std::uint8_t simulated_register_portb { };

const auto address { reinterpret_cast<std::uintptr_t>(&simulated_register_portb) };

auto main() -> int;

auto main() -> int
{
  // Use a convenient alias to save tedious typing work.
  using led_b5_type = led_template<std::uintptr_t, std::uint8_t>;

  led_b5_type led_b5 { address, static_cast<std::uint8_t>(UINT8_C(5)) };

  for(auto i = static_cast<unsigned>(UINT8_C(0)); i < static_cast<unsigned>(UINT8_C(4)); ++i)
  {
    led_b5.toggle();

    std::cout << "LED is: " << (led_b5.get_is_on() ? "on" : "off") << std::endl;
  }
}
