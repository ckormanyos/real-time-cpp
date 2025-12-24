///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2025.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <mcal/mcal_led_monochrome.h>
#include <mcal/mcal_led_rgb.h>
#include <util/utility/util_time.h>

#include <cstdint>
#include <cstdlib>

namespace app
{
  namespace led
  {
    auto task_init() -> void;
    auto task_func() -> void;
  }
}

auto app::led::task_init() -> void
{
  mcal::led::led_monochrome0().on();

  mcal::led::led_rgb0().set_color(UINT8_C(255), UINT8_C(0), UINT8_C(0));
}

auto app::led::task_func() -> void
{
  using app_led_monochrome_timer_type = util::timer<std::uint32_t>;

  static app_led_monochrome_timer_type app_led_monochrome_timer { app_led_monochrome_timer_type::seconds(UINT8_C(1)) };

  if(app_led_monochrome_timer.timeout())
  {
    // Toggle the monochrome user LED at 1/2 Hz.
    mcal::led::led_monochrome0().toggle();

    // Start the next 1s timer interval for the monochrome user LED.
    app_led_monochrome_timer.start_interval(app_led_monochrome_timer_type::seconds(1U));
  }

  // Define the color transition states.
  enum class color_transition_type
  {
    red_to_yellow,
    yellow_to_green,
    green_to_cyan,
    cyan_to_blue,
    blue_to_magenta,
    magenta_to_red
  };

  using app_led_rgb_timer_type = util::timer<std::uint32_t>;

  static app_led_rgb_timer_type app_led_rgb_timer { app_led_rgb_timer_type::milliseconds(UINT8_C(30)) };

  if(app_led_rgb_timer.timeout())
  {
    // Initialize the color hues.
    static std::uint_fast8_t app_led_hue_r { UINT8_C(255) };
    static std::uint_fast8_t app_led_hue_g { UINT8_C(0) };
    static std::uint_fast8_t app_led_hue_b { UINT8_C(0) };

    // Initialize the color transition state.
    static color_transition_type color_transition_state { color_transition_type::red_to_yellow };

    // Animate the RGB LED with the colors of the spectrum.

    const auto rgb_hue_sum =
      static_cast<std::uint_fast16_t>
      (
          static_cast<std::uint_fast16_t>(app_led_hue_r)
        + static_cast<std::uint_fast16_t>(app_led_hue_g)
        + static_cast<std::uint_fast16_t>(app_led_hue_b)
      );

    const bool rgb_hue_sum_is_in_bump_range
    {
         (rgb_hue_sum >= std::uint_fast16_t { UINT16_C(250) })
      && (rgb_hue_sum <= std::uint_fast16_t { UINT16_C(260) })
    };

    const bool rgb_hue_is_near_bump_point
    {
         ((app_led_hue_r > std::uint_fast8_t { UINT8_C(250) }) && rgb_hue_sum_is_in_bump_range)
      || ((app_led_hue_g > std::uint_fast8_t { UINT8_C(250) }) && rgb_hue_sum_is_in_bump_range)
      || ((app_led_hue_b > std::uint_fast8_t { UINT8_C(250) }) && rgb_hue_sum_is_in_bump_range)
    };

    unsigned color_persist_time { UINT8_C(30) };

    if(rgb_hue_is_near_bump_point)
    {
      const auto delta_bump_point = std::abs(static_cast<int>(rgb_hue_sum) - static_cast<int>(INT16_C(255)));

      if     (delta_bump_point == int { INT8_C(0) }) { color_persist_time = unsigned { UINT16_C(600) }; }
      else if(delta_bump_point == int { INT8_C(1) }) { color_persist_time = unsigned { UINT16_C(500) }; }
      else if(delta_bump_point == int { INT8_C(2) }) { color_persist_time = unsigned { UINT16_C(400) }; }
      else if(delta_bump_point == int { INT8_C(3) }) { color_persist_time = unsigned { UINT16_C(300) }; }
      else if(delta_bump_point == int { INT8_C(4) }) { color_persist_time = unsigned { UINT16_C(200) }; }
      else                                           { color_persist_time = unsigned { UINT16_C(100) }; }
    }

    // Make a smooth color transition and increment the color
    // transition state if necessary.

    switch(color_transition_state)
    {
      case color_transition_type::red_to_yellow:   { if(++app_led_hue_g == std::uint_fast8_t { UINT8_C(255) }) { color_transition_state = color_transition_type::yellow_to_green; } } break;
      case color_transition_type::yellow_to_green: { if(--app_led_hue_r == std::uint_fast8_t { UINT8_C(  0) }) { color_transition_state = color_transition_type::green_to_cyan;   } } break;
      case color_transition_type::green_to_cyan:   { if(++app_led_hue_b == std::uint_fast8_t { UINT8_C(255) }) { color_transition_state = color_transition_type::cyan_to_blue;    } } break;
      case color_transition_type::cyan_to_blue:    { if(--app_led_hue_g == std::uint_fast8_t { UINT8_C(  0) }) { color_transition_state = color_transition_type::blue_to_magenta; } } break;
      case color_transition_type::blue_to_magenta: { if(++app_led_hue_r == std::uint_fast8_t { UINT8_C(255) }) { color_transition_state = color_transition_type::magenta_to_red;  } } break;
      default:
      case color_transition_type::magenta_to_red:  { if(--app_led_hue_b == static_cast<std::uint_fast8_t>(UINT8_C(  0))) { color_transition_state = color_transition_type::red_to_yellow;   } } break;
    }

    // Write the next color to the RGB LED.
    mcal::led::led_rgb0().set_color(app_led_hue_r, app_led_hue_g, app_led_hue_b);

    // Start the next timer interval for the RGB LED.
    app_led_rgb_timer.start_interval(app_led_rgb_timer_type::milliseconds(color_persist_time));
  }
}
