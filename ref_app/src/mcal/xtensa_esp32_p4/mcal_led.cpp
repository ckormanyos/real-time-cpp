///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2026.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <gpio.h>

#include <mcal_led.h>
#include <mcal_led/mcal_led_port.h>
#include <mcal_port.h>
#include <mcal_reg.h>

namespace local
{
  class led_port54 : public mcal::led::led_boolean_state_base
  {
  public:
    led_port54() noexcept
    {
      gpio_cfg_output(54);
    }

    ~led_port54() override = default;

    auto toggle() noexcept -> void override
    {
      using base_class_type = led_boolean_state_base;

      gpio_toggle_output_level(54);

      base_class_type::toggle();
    }
  };

  class led_port19 : public mcal::led::led_boolean_state_base
  {
  public:
    led_port19() noexcept
    {
      gpio_cfg_output(19);
    }

    ~led_port19() override = default;

    auto toggle() noexcept -> void override
    {
      using base_class_type = led_boolean_state_base;

      gpio_toggle_output_level(19);

      base_class_type::toggle();
    }
  };
} // namespace local

auto mcal::led::led0() -> mcal::led::led_base& { static local::led_port54 my_led { }; return my_led; }
auto mcal::led::led1() -> mcal::led::led_base& { static local::led_port19 my_led { }; return my_led; }
