///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2018.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <cstdint>

#include <mcal/mcal_led_monochrome.h>
#include <mcal/mcal_led_rgb.h>
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
  using app_led_monochrome_timer_type = util::timer<std::uint32_t>;
  using app_led_rgb_timer_type        = util::timer<std::uint16_t>;

  app_led_monochrome_timer_type app_led_monochrome_timer(app_led_monochrome_timer_type::seconds(1U));
  app_led_rgb_timer_type        app_led_rgb_timer       (app_led_rgb_timer_type::milliseconds(20U));

  std::uint_fast8_t app_led_hue_r = UINT8_C(255);
  std::uint_fast8_t app_led_hue_g;
  std::uint_fast8_t app_led_hue_b;
}

void app::led::task_init()
{
  mcal::led::led_monochrome0().on();

  mcal::led::led_rgb0().set_color(app_led_hue_r,
                                  app_led_hue_g,
                                  app_led_hue_b);
}

void app::led::task_func()
{
  if(app_led_monochrome_timer.timeout())
  {
    // Toggle the monochrome user LED at 1/2 Hz.
    mcal::led::led_monochrome0().toggle();

    // Start the next timer interval for the monochrome user LED.
    app_led_monochrome_timer.start_interval(app_led_monochrome_timer_type::seconds(1U));
  }

  if(app_led_rgb_timer.timeout())
  {
    // Animate the RGB LED with the colors of the spectrum at 50 Hz.

    // Define the color transition states.
    typedef enum color_transition_enum
    {
      red_to_yellow,
      yellow_to_green,
      green_to_cyan,
      cyan_to_blue,
      blue_to_magenta,
      magenta_to_red
    }
    color_transition_type;

    // Initialize the color transition state.
    static color_transition_type color_transition_state = red_to_yellow;

    // Make a smooth color transition and
    // increment the color transition state
    // if necessary.
    switch(color_transition_state)
    {
      case red_to_yellow:   { if(++app_led_hue_g == UINT8_C(255)) { color_transition_state = yellow_to_green; } } break;
      case yellow_to_green: { if(--app_led_hue_r == UINT8_C(  0)) { color_transition_state = green_to_cyan;   } } break;
      case green_to_cyan:   { if(++app_led_hue_b == UINT8_C(255)) { color_transition_state = cyan_to_blue;    } } break;
      case cyan_to_blue:    { if(--app_led_hue_g == UINT8_C(  0)) { color_transition_state = blue_to_magenta; } } break;
      case blue_to_magenta: { if(++app_led_hue_r == UINT8_C(255)) { color_transition_state = magenta_to_red;  } } break;
      default:
      case magenta_to_red:  { if(--app_led_hue_b == UINT8_C(  0)) { color_transition_state = red_to_yellow;   } } break;
    }

    // Write the next color to the RGB LED.
    mcal::led::led_rgb0().set_color(app_led_hue_r,
                                    app_led_hue_g,
                                    app_led_hue_b);

    // Start the next timer interval for the RGB LED.
    app_led_rgb_timer.start_interval(app_led_rgb_timer_type::milliseconds(20U));
  }
}
