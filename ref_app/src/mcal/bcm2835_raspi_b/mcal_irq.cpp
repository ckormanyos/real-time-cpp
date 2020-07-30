///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2014 - 2020.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <mcal_cpu.h>
#include <mcal_gpt.h>
#include <mcal_irq.h>
#include <mcal_reg.h>

void mcal::irq::init(const config_type*)
{
  // Maskable interrupts are not used in this derivative.
  // Do not enable all global (maskable) interrupts.
}

extern "C" void __int_vect_undef_instr_handler   () { for(;;) { mcal::cpu::nop(); } }
extern "C" void __int_vect_sw_interrupt_handler  () { for(;;) { mcal::cpu::nop(); } }
extern "C" void __int_vect_prefetch_abort_handler() { for(;;) { mcal::cpu::nop(); } }
extern "C" void __int_vect_data_abort_handler    () { for(;;) { mcal::cpu::nop(); } }
extern "C" void __int_vect_unused_05_handler     () { for(;;) { mcal::cpu::nop(); } }
extern "C" void __int_vect_irq_handler           () { for(;;) { mcal::cpu::nop(); } } // For future use: Query, clear and handle the active interrupt bit(s).
extern "C" void __int_vect_fiq_handler           () { for(;;) { mcal::cpu::nop(); } }
