///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2013.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef _MCAL_IRQ_2010_04_10_H_
  #define _MCAL_IRQ_2010_04_10_H_

  namespace mcal
  {
    namespace irq
    {
      typedef void config_type;

      inline void init(const config_type*) { }

      inline void enable_all () { }
      inline void disable_all() { }
    }
  }

#endif // _MCAL_IRQ_2010_04_10_H_
