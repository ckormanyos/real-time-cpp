///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2019.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

// chapter08_07-002_main_and_scheduler.cpp

#include <iostream>

namespace mcal
{
  namespace cpu
  {
    // Simulated initialization of the CPU
    void init() { }
  }

  namespace wdg
  {
    struct secure
    {
      // Simulated watchdog trigger.
      static void trigger() { }
    };
  }

  void init()
  {
    // simulated initialization of the MCAL.
  }
}

namespace crt {

// Simulated initialization of RAM.
void init_ram  () { }

// Simulated initialization of static constructors.
void init_ctors() { }

} // namespace crt

void simulated_scheduler()
{
  // This is a simulated multitasking scheduler.
  for(;;)
  {
    std::cout << "In simulated_scheduler()." << std::endl;

    mcal::wdg::secure::trigger();
  }
}

extern "C"
void simulated_main(void)
{
  simulated_scheduler();
}

extern "C"
void __my_startup()
{
  // CPU Initialization, including watchdog,
  // port, oscillators (i.e. clocks).
  mcal::cpu::init();

  // Initialize statics from ROM to RAM.
  // Zero-clear default-initialized static RAM.
  crt::init_ram();
  mcal::wdg::secure::trigger();

  // Call all constructor initializations.
  crt::init_ctors();
  mcal::wdg::secure::trigger();

  // Call the simulated main (and never return).
  simulated_main();

  // Catch an unexpected return from main.
  for(;;)
  {
    // Replace with a loud error if desired.
    mcal::wdg::secure::trigger();
  }
}

int main()
{
  __my_startup();
}
