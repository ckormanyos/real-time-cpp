///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2020.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <mcal/mcal.h>
#include <os/os.h>

#if defined(__GNUC__) && defined(__XTENSA__)
extern "C" [[noreturn]] void main_loop(void*);
#else
[[noreturn]] int main(void);
#endif

#if defined(__GNUC__) && defined(__XTENSA__)
void main_loop(void*)
#else
int main(void)
#endif
{
  // Initialize the microcontroller abstraction layer.
  mcal::init();

  // Start the multitasking scheduler, and never return.
  os::start_os();

  for(;;) { mcal::cpu::nop(); }
}
