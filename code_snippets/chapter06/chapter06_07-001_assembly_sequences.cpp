///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2018 - 2019.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

// chapter06_07-001_assembly_sequences.cpp

namespace mcal
{
  namespace irq
  {
    // Interrupt enable/disable.
    inline void enable_all () { /* Use target-specific assembly here. */ }
    inline void disable_all() { /* Use target-specific assembly here. */ }
  }
}

namespace mcal
{
  namespace cpu
  {
    // The no-operation.
    inline void nop() { /* Use target-specific assembly here. */ }
  }
}

int main()
{
  // Initialize the mcal.
  // ...

  // Enable all global interrupts.
  // The enable_all() function uses assembly!
  mcal::irq::enable_all();

  // Start multitasking.
  // ...
}
