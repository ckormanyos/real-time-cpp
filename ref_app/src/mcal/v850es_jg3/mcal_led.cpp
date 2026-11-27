///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2026.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <mcal_led.h>
#include <mcal_led/mcal_led_boolean_state_base.h>

#include <cstdint>

#define PM3L (*(volatile uint8_t*)(0xFFFFF426ul))
#define P3L  (*(volatile uint8_t*)(0xFFFFF406ul))

class led_v850es_jg3_starter : public mcal::led::led_boolean_state_base
{
private:
  using base_class_type = mcal::led::led_boolean_state_base;

public:
  led_v850es_jg3_starter() noexcept
  {
    // Initialize the LED port pin
    // to output high (LED off).
    P3L  |= (uint8_t)(1u << 6);
    PM3L &= (uint8_t)~(1u << 6);
  }

  auto toggle() noexcept -> void override
  {
    // Toggle the LED port pin.
    P3L  ^= (uint8_t)(1u << 6);

    base_class_type::toggle();
  }
};

mcal::led::led_base& mcal::led::led0()
{
  using led0_led_type = led_v850es_jg3_starter;

  static led0_led_type l0 { };

  return l0;
}
