///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2017 - 2018.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <mcal/mcal_led_monochrome.h>
#include <mcal_port.h>
#include <mcal_reg.h>
#include <mcal_led_monochrome_board.h>

util::device::led_monochrome& mcal::led::led_monochrome0()
{
  static mcal::led::led_momochrome_board<mcal::reg::portb,
                                         UINT8_C(5)> the_led;

  return the_led;
}
