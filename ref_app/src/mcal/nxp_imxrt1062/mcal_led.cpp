///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2022.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <mcal_led/mcal_led_boolean_state_base.h>
#include <mcal_led.h>
#include <mcal_reg.h>

class led_teensy : public mcal::led::led_boolean_state_base
{
private:
  using base_class_type = mcal::led::led_boolean_state_base;

public:
  ~led_teensy() override = default;

  led_teensy()
  {
    led_init();
    led_off();
  }

  auto toggle() -> void override
  {
    // Toggle the LED state.
    led_toggle();

    base_class_type::toggle();
  }

private:
  static auto led_init  () -> void { mcal::reg::reg_access_static<std::uint32_t, std::uint32_t, static_cast<std::uint32_t>(UINT32_C(0x401BC004)), static_cast<std::uint32_t>(1UL << 3UL)>::reg_or(); }
  static auto led_off   () -> void { mcal::reg::reg_access_static<std::uint32_t, std::uint32_t, static_cast<std::uint32_t>(UINT32_C(0x401BC088)), static_cast<std::uint32_t>(1UL << 3UL)>::reg_or(); }
  static auto led_toggle() -> void { mcal::reg::reg_access_static<std::uint32_t, std::uint32_t, static_cast<std::uint32_t>(UINT32_C(0x401BC08C)), static_cast<std::uint32_t>(1UL << 3UL)>::reg_or(); }
};

mcal::led::led_base& mcal::led::led0()
{
  using led0_led_type = led_teensy;

  static led0_led_type l0;

  return l0;
}
