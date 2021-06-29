///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2020.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef MCAL_CPU_2009_02_14_H_
  #define MCAL_CPU_2009_02_14_H_

  #define MY_PROGMEM

  namespace mcal { namespace cpu {

  void init();

  void post_init();

  inline void nop() { asm volatile("nop"); }

  } } // namespace mcal::cpu

#endif // MCAL_CPU_2009_02_14_H_
