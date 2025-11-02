///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2023.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <mcal_led_sys_start_interface.h>
#include <mcal/mcal.h>
#include <os/os.h>

// Here we create a separate callable my_sys_start()
// function that is used to provide cross compilation
// support for the PC application (because the PC
// program uses WinMain() instead of main().

void mcal::led::sys_start_interface::my_sys_start()
{
  // Initialize the microcontroller abstraction layer.
  mcal::init();

  // Start the multitasking scheduler, and never return.
  os::start_os();
}

#if !defined(_MSC_VER)
auto main() -> int;

auto main() -> int
{
  mcal::led::sys_start_interface::my_sys_start();
}
#endif
