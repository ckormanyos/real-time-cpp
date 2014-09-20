///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2014.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <mcal_cpu.h>
#include <mcal_irq.h>

extern "C" void _reset_                               () __attribute__((section(".startup"), used, noinline));
extern "C" void undefined_instruction_vector          () __attribute__((interrupt("UNDEF"), used, noinline));
extern "C" void software_interrupt_vector             () __attribute__((interrupt("SWI"),   used, noinline));
extern "C" void prefetch_abort_vector                 () __attribute__((interrupt("ABORT"), used, noinline));
extern "C" void data_abort_vector                     () __attribute__((interrupt("ABORT"), used, noinline));
extern "C" void the_one_and_only_interrupt_vector     () __attribute__((interrupt("IRQ"),   used, noinline));
extern "C" void the_one_and_only_fast_interrupt_vector() __attribute__((interrupt("FIQ"),   used, noinline));

void undefined_instruction_vector() { for(;;) { mcal::cpu::nop(); } }
void software_interrupt_vector   () { for(;;) { mcal::cpu::nop(); } }
void prefetch_abort_vector       () { for(;;) { mcal::cpu::nop(); } }
void data_abort_vector           () { for(;;) { mcal::cpu::nop(); } }

void the_one_and_only_interrupt_vector()
{
  mcal::irq::secure::interrupt_vector();
}

void the_one_and_only_fast_interrupt_vector()
{
  mcal::irq::secure::fast_interrupt_vector();
}
