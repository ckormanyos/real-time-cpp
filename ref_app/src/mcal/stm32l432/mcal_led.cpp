///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2024.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <mcal_led.h>
#include <mcal_led/mcal_led_boolean_state_base.h>

#include <Mcal/Reg.h>

namespace mcal { namespace led {

class led_port_b3 : public mcal::led::led_boolean_state_base
{
public:
  led_port_b3()
  {
    /* Configure GPIOB Pin 3 as output */
    GPIOB_MODER |= (uint32_t)(1U << 6U);
    GPIOB_MODER &= (uint32_t)(~(uint32_t)(1U << 7U));

    /* Switch off the LED.*/
    GPIOB_ODR &= (uint32_t)(~(uint32_t)(1UL << 3U));
  }

  auto toggle() -> void override
  {
    using base_class_type = led_boolean_state_base;

    GPIOB_ODR ^= (uint32_t)(1U << 3U);

    base_class_type::toggle();
  }
};

} } // namespace mcal::led


mcal::led::led_base& mcal::led::led0()
{
  // The user LED on the stm32l432 Nucleo-64 board:
  // - portb.3: green

  using led0_led_type = mcal::led::led_port_b3;

  static led0_led_type l0;

  return l0;
}
