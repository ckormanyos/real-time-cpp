///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2018.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <windows.h>

#include <mcal_led_monochrome_pc.h>

void post_message_led_monochrome(const bool is_on);

void mcal::led::led_monochrome_pc::my_on()
{
  post_message_led_monochrome(true);
}

void mcal::led::led_monochrome_pc::my_off()
{
  post_message_led_monochrome(false);
}
