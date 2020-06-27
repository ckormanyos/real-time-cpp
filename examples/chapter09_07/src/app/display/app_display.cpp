
///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2015 - 2020.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <cstdint>

#include <mcal/mcal.h>
#include <mcal/mcal_display_seven_segment.h>
#include <util/utility/util_time.h>

namespace app
{
  namespace display
  {
    void task_init();
    void task_func();
  }
}

namespace
{
  typedef util::timer<std::uint32_t> timer_type;

  timer_type app_display_timer(timer_type::seconds(1U));

  uint8_t app_display_index;
  bool    app_display_dp_on = true;
}

void app::display::task_init()
{
  mcal::led::led0.toggle();

  mcal::display::display0().write_dp(app_display_dp_on);

  mcal::display::display0().write(app_display_index);
}

void app::display::task_func()
{
  if(app_display_timer.timeout())
  {
    app_display_timer.start_interval(timer_type::seconds(1U));

    // Toggle the user LED at 1/2Hz.
    mcal::led::led0.toggle();

    // The index runs from 0...F and is used to express
    // the character that is to be written on the display.
    ++app_display_index;

    if(app_display_index >= UINT8_C(0x10))
    {
      app_display_index = UINT8_C(0);

      // Toggle the decimal point for each successive
      // group of 16 hexadecimal digits.
      app_display_dp_on = (!app_display_dp_on);
    }

    // Write the decimal point.
    mcal::display::display0().write_dp(app_display_dp_on);

    // Write the character 0...F.
    mcal::display::display0().write(app_display_index);
  }
}
