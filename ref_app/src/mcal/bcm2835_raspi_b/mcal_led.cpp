///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2014 - 2020.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <mcal_led.h>
#include <mcal_led/mcal_led_base.h>

#include <gpio.h>

namespace mcal { namespace led {

class led_gpio_status_led final : public mcal::led::led_base
{
public:
  led_gpio_status_led() : is_on(false)
  {
    switch_led_off();
  }

  virtual ~led_gpio_status_led() = default;

  void toggle()
  {
    // Toggle the LED state.
    // Note here that the logic of the led is inverted.

    (is_on ? switch_led_off() : switch_led_on());
  }

  virtual bool state_is_on() const { return is_on; }

private:
  bool is_on;

  void switch_led_on()
  {
    ::gpio_ClrPin(GPIO_STATUS_LED);

    is_on = true;
  }

  void switch_led_off()
  {
    ::gpio_SetPin(GPIO_STATUS_LED);

    is_on = false;
  }
};

} } // namespace mcal::led

mcal::led::led_base& mcal::led::led0()
{
  static mcal::led::led_gpio_status_led l0;

  return l0;
}
