///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2017 - 2018.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <mcal_led_sys_start_interface.h>

bool& mcal::led::sys_start_interface::my_exit_pc_api_flag()
{
  static bool my_flag;

  return my_flag;
}
