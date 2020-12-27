///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2020.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#if defined(__GNUC__) && defined(__XTENSA__)

extern "C"
{
  void app_main(void);

  int atexit (void (*)(void)) noexcept;

  int atexit (void (*)(void))
  {
    return 0;
  }
}

#else
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
#endif
