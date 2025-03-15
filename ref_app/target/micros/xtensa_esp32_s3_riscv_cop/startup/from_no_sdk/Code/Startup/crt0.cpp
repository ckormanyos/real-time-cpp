///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2025.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

// Generic code.

#include <mcal_cpu.h>

namespace crt
{
  void init_ram();
  void init_ctors();
}

extern "C"
{
  extern auto main() -> int;

  void __my_startup() __attribute__((used, noinline));
}

void __my_startup()
{
  // Initialize statics from ROM to RAM.
  // Zero-clear default-initialized static RAM.
  crt::init_ram();

  // Call all ctor initializations.
  crt::init_ctors();

  // Jump to main (and never return).
  static_cast<void>(main());

  // Catch an unexpected return from main.
  for(;;)
  {
    // Replace with a loud error if desired.
    mcal::cpu::nop();
  }
}
