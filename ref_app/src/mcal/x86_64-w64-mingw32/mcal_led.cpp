///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2020.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <mcal_led.h>
#include <mcal_led/mcal_led_console.h>

auto mcal::led::led0() -> mcal::led::led_base&
{
  static mcal::led::led_console local_led0(static_cast<std::uint_fast8_t>(UINT8_C(0)));

  return local_led0;
}
