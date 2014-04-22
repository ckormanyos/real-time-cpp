/////////////////////////////////////////////////////// 
//  Copyright 2013 Stephan Hage.
//  Copyright 2013 Christopher Kormanyos.
//  Distributed under the Boost 
//  Software License, Version 1.0. 
//  (See accompanying file LICENSE_1_0.txt 
//  or copy at http://www.boost.org/LICENSE_1_0.txt ) 
//


#include <cstdint>
#include <Bsw/EcuM/EcuM.h>
#include <Bsw/Mcal/Reg/Reg.h>



// RL78 startup code
// Switched to C++ and modified for RL78Fx by Chris.



#include <Bsw/Mcal/Wdg/Wdg.h>

extern "C" int main();

asm volatile(".extern __initial_stack_pointer");

namespace crt
{
  void init_ram();
  void init_ctors();
}

extern "C" void __my_startup()
{
  // Set the stack pointer.
  asm volatile("movw sp, #__initial_stack_pointer");

  // Initialize statics from ROM to RAM.
  // Zero-clear non-initialized static RAM.
  crt::init_ram();

  // Call all ctor initializations.
  crt::init_ctors();

  // Call main (and never return).
  asm volatile("call !!_main");

  // Catch an unexpected return from main.
  for(;;)
  {
    // Replace with a loud error if desired.
    Wdg_Trigger();
  }
}
