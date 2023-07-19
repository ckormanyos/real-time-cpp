///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2020.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <mcal_led.h>
#include <mcal_led_monochrome_pc.h>

auto mcal::led::led0() -> led_base&
{
  static mcal::led::led_monochrome_pc local_led0;

  return local_led0;
}
