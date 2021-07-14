///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2021.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <app/led/app_led.h>
#include <mcal_led.h>
#include <mcal_wdg.h>
#include <os/os_task.h>
#include <util/utility/util_time.h>

namespace
{
  using app_led_timer_type = util::timer<std::uint32_t>;

  app_led_timer_type app_led_timer_background;
  app_led_timer_type app_led_timer_toggle_led0;
}

extern "C"
void app_led_task_background(void*)
{
  // This background task runs perpetually without pause, break or yield.
  // This task has lowest priority and will be interrupted by the task
  // having higher priority.

  for(;;)
  {
    while((!app_led_timer_background.timeout()))
    {
      ;
    }

    app_led_timer_background.start_interval(app_led_timer_type::milliseconds(50U));

    mcal::led::led1().toggle();
  }
}

extern "C"
void app_led_task_toggle_led0(void*)
{
  // This application task is intended to yield every 70ms. It has higher
  // priority than the background task. This task will, in fact, preemptively
  // interrupt the lower-priority background task.

  for(;;)
  {
    mcal::wdg::secure::trigger();

    if(app_led_timer_toggle_led0.timeout())
    {
      app_led_timer_toggle_led0.start_interval(app_led_timer_type::seconds(1U));

      mcal::led::led0().toggle();
    }

    OS_TASK_WAIT_YIELD(OS_TASK_MSEC(70U));
  }
}
