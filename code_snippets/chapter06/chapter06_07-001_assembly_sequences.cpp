///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2018 - 2025.
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
    inline auto enable_all () -> void { /* Use target-specific assembly here. */ }
    inline auto disable_all() -> void { /* Use target-specific assembly here. */ }
  }
}

namespace mcal
{
  namespace cpu
  {
    // The no-operation.
    inline auto nop() -> void { /* Use target-specific assembly here. */ }
  }
}

auto main() -> int;

auto main() -> int
{
  // Initialize the mcal.
  // ...

  // Enable all global interrupts.
  // When on a target, the enable_all() function probable uses assembly!
  mcal::irq::enable_all();

  // Call one nop.
  // When on a target, the nop() function probable uses assembly!
  mcal::cpu::nop();

  // Start multitasking.
  // ...
}
