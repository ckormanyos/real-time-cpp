///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2020.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <esp32-hal-gpio.h>

#include <mcal/mcal.h>
#include <util/utility/util_time.h>

namespace
{
  constexpr int LED_BUILTIN = 2;
}

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

  timer_type app_led_timer(timer_type::seconds(1U));

  bool is_high;
}

void app::led::task_init()
{
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);

  digitalWrite(LED_BUILTIN, HIGH);

  is_high = true;
  //mcal::led::led0().toggle();
}

void app::led::task_func()
{
  if(app_led_timer.timeout())
  {
    app_led_timer.start_interval(timer_type::seconds(1U));

    if(is_high)
    {
      is_high = false;

      digitalWrite(LED_BUILTIN, LOW);
    }
    else
    {
      is_high = true;

      digitalWrite(LED_BUILTIN, HIGH);
    }
  }
}
