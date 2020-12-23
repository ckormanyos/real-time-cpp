///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2020.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <mcal/mcal.h>
#include <os/os.h>

[[noreturn]] int main(void);

int main(void)
{
  // Initialize the microcontroller abstraction layer.
  mcal::init();

  // Start the multitasking scheduler, and never return.
  os::start_os();

  for(;;) { mcal::cpu::nop(); }
}
