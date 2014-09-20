///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2014.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef _MCAL_IRQ_2014_09_20_H_
  #define _MCAL_IRQ_2014_09_20_H_

  extern "C" void the_one_and_only_interrupt_vector     () __attribute__((interrupt("IRQ"), used, noinline));
  extern "C" void the_one_and_only_fast_interrupt_vector() __attribute__((interrupt("FIQ"), used, noinline));

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
        static void interrupt_vector();
        static void fast_interrupt_vector();

        friend void ::the_one_and_only_interrupt_vector();
        friend void ::the_one_and_only_fast_interrupt_vector();
      };
    }
  }

#endif // _MCAL_IRQ_2014_09_20_H_
