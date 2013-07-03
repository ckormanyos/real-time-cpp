///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2013.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef _MCAL_CPU_2009_02_14_H_
  #define _MCAL_CPU_2009_02_14_H_

  #include <cstdint>

  namespace mcal
  {
    namespace cpu
    {
      void init();

      inline void nop() { asm volatile("nop"); }
    }
  }

#endif // _MCAL_CPU_2009_02_14_H_
