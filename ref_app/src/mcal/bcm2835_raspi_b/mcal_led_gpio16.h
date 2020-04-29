///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2020.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef MCAL_LED_GPIO16_2020_04_29_H_
  #define MCAL_LED_GPIO16_2020_04_29_H_

  #include <cstdint>

  #include <mcal_reg.h>
  #include <mcal_led/mcal_led_base.h>

  namespace mcal { namespace led {

  class led_gpio16 final : public mcal::led::led_base
  {
  public:
    led_gpio16() : is_on(false)
    {
      // Write 1 to the GPIO16 init nibble in the Function Select 1 GPIO
      // peripheral register to enable GPIO16 as an output.
      mcal::reg::reg_access_static<std::uint32_t, std::uint32_t, mcal::reg::gpio_gpfsel1, UINT32_C(18)>::bit_set();

      // Set the GPIO16 output high (turn the OK LED off).
      mcal::reg::reg_access_static<std::uint32_t, std::uint32_t, mcal::reg::gpio_gpset0, UINT32_C(16)>::bit_set();
    }

    virtual ~led_gpio16() = default;

    void toggle()
    {
      // Toggle the LED state.
      // Note here that the logic of the led is inverted.

      (is_on ? mcal::reg::reg_access_static<std::uint32_t, std::uint32_t, mcal::reg::gpio_gpset0, UINT32_C(16)>::bit_set()
             : mcal::reg::reg_access_static<std::uint32_t, std::uint32_t, mcal::reg::gpio_gpclr0, UINT32_C(16)>::bit_set());

      is_on = (!is_on);
    }

    virtual bool state_is_on() const { return is_on; }

  private:
    bool is_on;
  };

  } } // namespace mcal::led

#endif // MCAL_LED_GPIO16_2020_04_29_H_
