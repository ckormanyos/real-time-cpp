///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2025.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <app/led/app_led.h>
#include <mcal/mcal.h>
#include <util/utility/util_time.h>

#include <array>
#include <cstddef>
#include <cstdint>
#include <functional>

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
  using timer_type = util::timer<std::uint32_t>;

  using app_led_type = mcal::led::led_base;

  using app_led_array_type = std::array<std::reference_wrapper<app_led_type>, static_cast<std::size_t>(UINT8_C(5))>;

  constexpr auto app_led_one_sec = timer_type::seconds(1U);

  timer_type app_led_timer { app_led_one_sec };

  app_led_array_type& app_led_base_class_array();

  app_led_array_type& app_led_base_class_array()
  {
    using namespace mcal::led;

    static app_led_array_type local_base_class_array
    {
      led0(), led1(), led2(), led3(), led4()
    };

    return local_base_class_array;
  }

  bool app_led_state_is_on { true };
}

bool app::led::get_state_is_ok()
{
  const auto& local_base_class_array = app_led_base_class_array();

  const auto app_led_state_result_is_ok =
    std::all_of
    (
      local_base_class_array.cbegin(),
      local_base_class_array.cend(),
      [](app_led_type& led) -> bool
      {
        return (app_led_state_is_on == led.state_is_on());
      });

  return app_led_state_result_is_ok;
}

void app::led::task_init()
{
  auto& local_base_class_array = app_led_base_class_array();

  for(app_led_type& led : local_base_class_array)
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

    auto& local_base_class_array = app_led_base_class_array();

    for(app_led_type& led : local_base_class_array)
    {
      led.toggle();
    }

    app_led_state_is_on = (!app_led_state_is_on);
  }
}
