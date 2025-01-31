///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2025.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <app/led/app_led.h>
#include <mcal_cpu.h>
#include <mcal_led.h>
#include <mcal_wdg.h>
#include <os/os_task.h>
#include <util/utility/util_time.h>

namespace
{
  using app_led_timer_type = util::timer<std::uint32_t>;
  using app_led_tick_type  = typename app_led_timer_type::tick_type;

  app_led_timer_type app_led_timer_background;
  app_led_timer_type app_led_timer_toggle_led0;
}

extern "C"
void app_led_task_background(void*)
{
  // This background task runs perpetually without pause, break or yield
  // (unless running on _MSC_VER, where there is a yield for task break).

  // This task has lowest priority and will be interrupted by any other
  // task having higher priority, such as the LED 1/2 Hz toggle task
  // (i.e., app_led_timer_toggle_led0).

  for(;;)
  {
    while((!app_led_timer_background.timeout()))
    {
      #if defined(_MSC_VER)
      {
        #if defined(__AVR__)
        #error This code sequence is not intended fof __AVR__;
        #endif

        static unsigned prescaler { };

        if(unsigned { ++prescaler % unsigned { UINT8_C(8) } } == unsigned { UINT8_C(0) })
        {
          OS_TASK_WAIT_YIELD(OS_TASK_MSEC(TickType_t { UINT8_C(3) }));
        }
      }
      #endif

      mcal::cpu::nop();
    }

    app_led_timer_background.start_interval(app_led_timer_type::milliseconds(app_led_tick_type { UINT8_C(50) }));

    mcal::led::led1().toggle();
  }
}

extern "C"
void app_led_task_toggle_led0(void*)
{
  // This application task is intended to yield every 125ms. It has higher
  // priority than the background task. This task will, in fact, preemptively
  // interrupt the lower-priority background task.

  for(;;)
  {
    mcal::wdg::secure::trigger();

    if(app_led_timer_toggle_led0.timeout())
    {
      app_led_timer_toggle_led0.start_interval(app_led_timer_type::seconds(app_led_tick_type { UINT8_C(1) }));

      mcal::led::led0().toggle();
    }

    OS_TASK_WAIT_YIELD(OS_TASK_MSEC(125U));
  }
}
