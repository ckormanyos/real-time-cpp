///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2019.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

// chapter08_01-001_my_startup.cpp

#include <iostream>

namespace mcal
{
  namespace cpu
  {
    void init() { /* simulated initialization of the CPU */ }
  } // namespace mcal::cpu

  namespace wdg
  {
    struct secure
    {
      static void trigger() { /* simulated watchdog trigger */ }
    };
  } // namespace mcal::wdg
}

namespace crt {

void init_ram  () { /* simulated initialization of RAM */ }
void init_ctors() { /* simulated initialization of static constructors */}

} // namespace crt

extern "C"
void simulated_main(void)
{
  // This is a sinulated main() subroutine.
  for(;;)
  {
    std::cout << "in simulated main()" << std::endl;

    mcal::wdg::secure::trigger();
  }
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
