///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2014.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef _MCAL_IRQ_2014_09_20_H_
  #define _MCAL_IRQ_2014_09_20_H_

  extern "C" void __int_vect_undef_instr_handler   () __attribute__((section(".text.isr1"),  interrupt("UNDEF"), used, noinline));
  extern "C" void __int_vect_sw_interrupt_handler  () __attribute__((section(".text.isr2"),  interrupt("SWI"),   used, noinline));
  extern "C" void __int_vect_prefetch_abort_handler() __attribute__((section(".text.isr3"),  interrupt("ABORT"), used, noinline));
  extern "C" void __int_vect_data_abort_handler    () __attribute__((section(".text.isr4"),  interrupt("ABORT"), used, noinline));
  extern "C" void __int_vect_unused_05_handler     () __attribute__((section(".text.isr5"),  interrupt("IRQ"),   used, noinline));
  extern "C" void __int_vect_irq_handler           () __attribute__((section(".text.isr6"),  interrupt("IRQ"),   used, noinline));
  extern "C" void __int_vect_fiq_handler           () __attribute__((section(".text.isr7"),  interrupt("FIQ"),   used, noinline));
  extern "C" void __int_vect_future_08_handler     () __attribute__((section(".text.isr8"),  interrupt("IRQ"),   used, noinline));
  extern "C" void __int_vect_future_09_handler     () __attribute__((section(".text.isr9"),  interrupt("IRQ"),   used, noinline));
  extern "C" void __int_vect_future_10_handler     () __attribute__((section(".text.isr10"), interrupt("IRQ"),   used, noinline));
  extern "C" void __int_vect_future_11_handler     () __attribute__((section(".text.isr11"), interrupt("IRQ"),   used, noinline));
  extern "C" void __int_vect_future_12_handler     () __attribute__((section(".text.isr12"), interrupt("IRQ"),   used, noinline));
  extern "C" void __int_vect_future_13_handler     () __attribute__((section(".text.isr13"), interrupt("IRQ"),   used, noinline));
  extern "C" void __int_vect_future_14_handler     () __attribute__((section(".text.isr14"), interrupt("IRQ"),   used, noinline));
  extern "C" void __int_vect_future_15_handler     () __attribute__((section(".text.isr15"), interrupt("IRQ"),   used, noinline));

  namespace mcal
  {
    namespace irq
    {
      typedef void config_type;
      void init(const config_type*);

      void enable_all ();
      void disable_all();

      struct secure
      {
      private:
        static void int_vect_undef_instr_handler_callback   ();
        static void int_vect_sw_interrupt_handler_callback  ();
        static void int_vect_prefetch_abort_handler_callback();
        static void int_vect_data_abort_handler_callback    ();
        static void int_vect_unused_05_handler_callback     ();
        static void int_vect_irq_handler_callback           ();
        static void int_vect_fiq_handler_callback           ();
        static void int_vect_future_08_handler_callback     ();
        static void int_vect_future_09_handler_callback     ();
        static void int_vect_future_10_handler_callback     ();
        static void int_vect_future_11_handler_callback     ();
        static void int_vect_future_12_handler_callback     ();
        static void int_vect_future_13_handler_callback     ();
        static void int_vect_future_14_handler_callback     ();
        static void int_vect_future_15_handler_callback     ();

        friend void ::__int_vect_undef_instr_handler   ();
        friend void ::__int_vect_sw_interrupt_handler  ();
        friend void ::__int_vect_prefetch_abort_handler();
        friend void ::__int_vect_data_abort_handler    ();
        friend void ::__int_vect_unused_05_handler     ();
        friend void ::__int_vect_irq_handler           ();
        friend void ::__int_vect_fiq_handler           ();
        friend void ::__int_vect_future_08_handler     ();
        friend void ::__int_vect_future_09_handler     ();
        friend void ::__int_vect_future_10_handler     ();
        friend void ::__int_vect_future_11_handler     ();
        friend void ::__int_vect_future_12_handler     ();
        friend void ::__int_vect_future_13_handler     ();
        friend void ::__int_vect_future_14_handler     ();
        friend void ::__int_vect_future_15_handler     ();
      };
    }
  }

#endif // _MCAL_IRQ_2014_09_20_H_
