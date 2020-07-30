///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2014 - 2020.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef MCAL_IRQ_2014_09_20_H_
  #define MCAL_IRQ_2014_09_20_H_

  extern "C" void __my_startup                     () __attribute__((used, noinline));                                             // Position 00 : This is implemented in crt0.cpp.
  extern "C" void __int_vect_undef_instr_handler   () __attribute__((section(".text.isr1"),  interrupt("UNDEF"), used, noinline)); // Position 01
  extern "C" void __int_vect_sw_interrupt_handler  () __attribute__((section(".text.isr2"),  interrupt("SWI"),   used, noinline)); // Position 02
  extern "C" void __int_vect_prefetch_abort_handler() __attribute__((section(".text.isr3"),  interrupt("ABORT"), used, noinline)); // Position 03
  extern "C" void __int_vect_data_abort_handler    () __attribute__((section(".text.isr4"),  interrupt("ABORT"), used, noinline)); // Position 04
  extern "C" void __int_vect_unused_05_handler     () __attribute__((section(".text.isr5"),  interrupt("IRQ"),   used, noinline)); // Position 05
  extern "C" void __int_vect_irq_handler           () __attribute__((section(".text.isr6"),  interrupt("IRQ"),   used, noinline)); // Position 06
  extern "C" void __int_vect_fiq_handler           () __attribute__((section(".text.isr7"),  interrupt("FIQ"),   used, noinline)); // Position 07

  namespace mcal
  {
    namespace irq
    {
      typedef void config_type;
      void init(const config_type*);

      inline void enable_all()
      {
        // Enable all maskable interrupts.
        asm volatile("cpsie i");
      }

      inline void disable_all()
      {
        // Disable all maskable interrupts.
        asm volatile("cpsid i");
      }
    }
  }

#endif // MCAL_IRQ_2014_09_20_H_
