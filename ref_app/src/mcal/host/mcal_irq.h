///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2020.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef MCAL_IRQ_2010_04_10_H_
  #define MCAL_IRQ_2010_04_10_H_

  namespace mcal
  {
    namespace irq
    {
      typedef void config_type;

      auto init(const config_type*) -> void;

      inline auto enable_all () -> void { }
      inline auto disable_all() -> void { }
    }
  }

#endif // MCAL_IRQ_2010_04_10_H_
