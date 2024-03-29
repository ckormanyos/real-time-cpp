///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2023.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef MCAL_CPU_2009_02_14_H
  #define MCAL_CPU_2009_02_14_H

  #define MY_PROGMEM

  namespace mcal { namespace cpu {

  void init();

  void post_init();

  inline void nop();

  } } // namespace mcal::cpu


  inline void mcal::cpu::nop() { asm volatile("nop"); }

#endif // MCAL_CPU_2009_02_14_H
