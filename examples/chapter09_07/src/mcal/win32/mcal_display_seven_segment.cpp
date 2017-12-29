///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2015 - 2018.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <mcal/mcal_display_seven_segment.h>
#include <mcal_display_console.h>

util::device::display_seven_segment& mcal::display::display0()
{
  typedef display_console display_type;

  static display_type the_display;

  return the_display;
}
