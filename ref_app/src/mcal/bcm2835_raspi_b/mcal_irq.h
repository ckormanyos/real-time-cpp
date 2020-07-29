///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2014 - 2020.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef MCAL_IRQ_2014_09_20_H_
  #define MCAL_IRQ_2014_09_20_H_

  extern "C" void __int_vect_undef_instr_handler   () __attribute__((section(".text.isr1"),  interrupt("UNDEF"), used, noinline));
  extern "C" void __int_vect_sw_interrupt_handler  () __attribute__((section(".text.isr2"),  interrupt("SWI"),   used, noinline));
  extern "C" void __int_vect_prefetch_abort_handler() __attribute__((section(".text.isr3"),  interrupt("ABORT"), used, noinline));
  extern "C" void __int_vect_data_abort_handler    () __attribute__((section(".text.isr4"),  interrupt("ABORT"), used, noinline));
  extern "C" void __int_vect_unused_05_handler     () __attribute__((section(".text.isr5"),  interrupt("IRQ"),   used, noinline));
  extern "C" void __int_vect_irq_handler           () __attribute__((section(".text.isr6"),  interrupt("IRQ"),   used, noinline));
  extern "C" void __int_vect_fiq_handler           () __attribute__((section(".text.isr7"),  interrupt("FIQ"),   used, noinline));

  namespace mcal
  {
    namespace irq
    {
      typedef void config_type;
      void init(const config_type*);

      inline void enable_all()
      {
        // Enable all maskable interrupts.
        //asm volatile("cpsie i");
        asm volatile("mrs r1, cpsr");
        asm volatile("bic r1, r1, #0x80");
        asm volatile("msr cpsr_c, r1");
      }

      inline void disable_all()
      {
        // Disable all maskable interrupts.
        //asm volatile("cpsid i");
        asm volatile("mrs r1, cpsr");
        asm volatile("orr r1, r1, #0x80");
        asm volatile("msr cpsr_c, r1");
      }

      class secure final
      {
        static void int_vect_undef_instr_handler_callback   ();
        static void int_vect_sw_interrupt_handler_callback  ();
        static void int_vect_prefetch_abort_handler_callback();
        static void int_vect_data_abort_handler_callback    ();
        static void int_vect_unused_05_handler_callback     ();
        static void int_vect_irq_handler_callback           ();
        static void int_vect_fiq_handler_callback           ();

        friend void ::__int_vect_undef_instr_handler   ();
        friend void ::__int_vect_sw_interrupt_handler  ();
        friend void ::__int_vect_prefetch_abort_handler();
        friend void ::__int_vect_data_abort_handler    ();
        friend void ::__int_vect_unused_05_handler     ();
        friend void ::__int_vect_irq_handler           ();
        friend void ::__int_vect_fiq_handler           ();
      };
    }
  }

#endif // MCAL_IRQ_2014_09_20_H_
