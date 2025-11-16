///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2025.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef MCAL_IRQ_2010_04_10_H
  #define MCAL_IRQ_2010_04_10_H

  namespace mcal
  {
    namespace irq
    {
      using config_type = void;

      auto init(const config_type*) -> void;

      inline auto enable_all () -> void { asm volatile("sei"); }
      inline auto disable_all() -> void { asm volatile("cli"); }
    }
  }

#endif // MCAL_IRQ_2010_04_10_H
