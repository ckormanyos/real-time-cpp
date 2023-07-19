///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2017 - 2018.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <windows.h>

#include <mcal_led_rgb_pc.h>

auto post_message_led_rgb(const std::uint32_t color) -> void;

auto mcal::led::led_rgb_pc::apply_color() -> void
{
  post_message_led_rgb(get_color());
}
