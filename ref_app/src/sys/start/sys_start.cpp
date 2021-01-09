///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2021.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <mcal/mcal.h>
#include <os/os.h>

#if defined(__GNUC__)
#if defined(__XTENSA__)
extern "C" void main_loop(void*);
#else
int main(void) __attribute__((used));
#endif
#endif

#if defined(__GNUC__) && defined(__XTENSA__)
void main_loop(void*)
#else
int main(void)
#endif
{
  // Initialize the microcontroller abstraction layer.
  mcal::init();

  // Start the multitasking scheduler. (This does not return.)
  // Handle an unexpected return from main() in the startup code.
  os::start_os();

  #if defined(__GNUC__) && defined(__XTENSA__)
  #else
  return 0;
  #endif
}
