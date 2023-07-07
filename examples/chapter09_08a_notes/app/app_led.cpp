///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2023.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <mcal/mcal.h>
#include <util/utility/util_time.h>

namespace app { namespace led {

void task_init();
void task_func();

} // namespace led
} // namespace app

namespace local
{
  using app_led_timer_type = util::timer<std::uint32_t>;

  using app_led_tick_type = typename app_led_timer_type::tick_type;

  auto app_led_timer() noexcept -> app_led_timer_type&;

  using color_type = mcal::led::led_rgb_base::color_rgb;

  using app_led_rgb_timer_type = util::timer<std::uint16_t>;

  app_led_rgb_timer_type app_led_rgb_timer(app_led_rgb_timer_type::milliseconds(20U));

  auto app_led_hue_r = static_cast<std::uint8_t>(UINT8_C(255));
  auto app_led_hue_g = static_cast<std::uint8_t>(UINT8_C(0));
  auto app_led_hue_b = static_cast<std::uint8_t>(UINT8_C(0));

  auto my_color = color_type { app_led_hue_r, app_led_hue_g, app_led_hue_b };
} // namespace local

auto local::app_led_timer() noexcept -> app_led_timer_type&
{
  static auto local_app_led_timer =
    static_cast<app_led_timer_type>
    (
      app_led_timer_type::seconds(static_cast<app_led_tick_type>(UINT8_C(1)))
    );

  return local_app_led_timer;
}

auto app::led::task_init() -> void
{
  mcal::led::led0().toggle();

  mcal::led::led_rgb0().set(local::my_color);
}

auto app::led::task_func() -> void
{
  if(local::app_led_timer().timeout())
  {
    local::app_led_timer().start_interval
    (
      local::app_led_timer_type::seconds(static_cast<local::app_led_tick_type>(UINT8_C(1)))
    );

    mcal::led::led0().toggle();
  }

  if(local::app_led_rgb_timer.timeout())
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
      case red_to_yellow:   { if(++local::app_led_hue_g == UINT8_C(255)) { color_transition_state = yellow_to_green; } } break;
      case yellow_to_green: { if(--local::app_led_hue_r == UINT8_C(  0)) { color_transition_state = green_to_cyan;   } } break;
      case green_to_cyan:   { if(++local::app_led_hue_b == UINT8_C(255)) { color_transition_state = cyan_to_blue;    } } break;
      case cyan_to_blue:    { if(--local::app_led_hue_g == UINT8_C(  0)) { color_transition_state = blue_to_magenta; } } break;
      case blue_to_magenta: { if(++local::app_led_hue_r == UINT8_C(255)) { color_transition_state = magenta_to_red;  } } break;
      default:
      case magenta_to_red:  { if(--local::app_led_hue_b == UINT8_C(  0)) { color_transition_state = red_to_yellow;   } } break;
    }

    local::my_color =
      local::color_type
      {
        local::app_led_hue_r,
        local::app_led_hue_g,
        local::app_led_hue_b
      };


    // Write the next color to the RGB LED.
    mcal::led::led_rgb0().set(local::my_color);

    // Start the next timer interval for the RGB LED.
    local::app_led_rgb_timer.start_interval(local::app_led_rgb_timer_type::milliseconds(20U));
  }
}
