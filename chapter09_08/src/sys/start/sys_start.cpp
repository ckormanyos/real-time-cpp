///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2013.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <mcal_led_sys_start_interface.h>
#include <mcal/mcal.h>
#include <os/os.h>

void mcal::led::sys_start_interface::my_sys_start()
{
  // Initialize the microcontroller abstraction layer.
  mcal::init();

  // Start the multitasking scheduler, and never return.
  os::start_os();
}

#if defined(__GNUC__)
extern "C" int main() __attribute__((used, noinline));
#endif

extern "C" int main()
{
  mcal::led::sys_start_interface::my_sys_start();
}
