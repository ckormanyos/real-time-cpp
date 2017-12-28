///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2017 - 2018.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef MCAL_PROGMEM_2017_12_16_H_
  #define MCAL_PROGMEM_2017_12_16_H_

  #if defined(__AVR__)
    #define MY_PROGMEM __attribute__((progmem))
  #else
    #define MY_PROGMEM
  #endif

#endif // MCAL_PROGMEM_2017_12_16_H_
