///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2026.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef MCAL_IRQ_2026_11_26_H
  #define MCAL_IRQ_2026_11_26_H

  namespace mcal
  {
    namespace irq
    {
      typedef void config_type;

      inline void enable_all () { asm volatile("ei"); }
      inline void disable_all() { asm volatile("di"); }

      void init(const config_type*);
    }
  }

#endif // MCAL_IRQ_2026_11_26_H
