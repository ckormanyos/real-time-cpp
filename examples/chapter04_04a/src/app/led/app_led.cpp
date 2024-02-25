///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2024.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <array>
#include <functional>

#include <app/led/app_led.h>
#include <mcal/mcal.h>
#include <util/utility/util_time.h>

namespace app
{
  namespace led
  {
    void task_init();
    void task_func();
  }
}

namespace
{
  typedef util::timer<std::uint32_t> timer_type;

  constexpr auto app_led_one_sec = timer_type::seconds(1U);

  timer_type app_led_timer(app_led_one_sec);

  using app_led_ref_type = std::reference_wrapper<mcal::led::led_base>;

  std::array<app_led_ref_type, 5U> app_led_base_class_refs =
  {{
    mcal::led::led0(),
    mcal::led::led1(),
    mcal::led::led2(),
    mcal::led::led3(),
    mcal::led::led4()
  }};

  bool app_led_state_is_on = true;
}

bool app::led::get_state_is_ok() noexcept
{
  bool app_led_state_is_ok = true;

  if(app_led_state_is_on)
  {
    app_led_state_is_ok &= std::all_of(app_led_base_class_refs.cbegin(),
                                       app_led_base_class_refs.cend(),
                                       [](typename app_led_ref_type::type& led) -> bool
                                       {
                                         return (led.state_is_on() == true);
                                       });
  }
  else
  {
    app_led_state_is_ok &= std::all_of(app_led_base_class_refs.cbegin(),
                                       app_led_base_class_refs.cend(),
                                       [](typename app_led_ref_type::type& led) -> bool
                                       {
                                         return (led.state_is_on() == false);
                                       });
  }

  return app_led_state_is_ok;
}

void app::led::task_init()
{
  for(typename app_led_ref_type::type& led : app_led_base_class_refs)
  {
    led.toggle();
  }

  app_led_state_is_on = true;
}

void app::led::task_func()
{
  if(app_led_timer.timeout())
  {
    app_led_timer.start_interval(app_led_one_sec);

    for(typename app_led_ref_type::type& led : app_led_base_class_refs)
    {
      led.toggle();
    }

    app_led_state_is_on = (!app_led_state_is_on);
  }
}
