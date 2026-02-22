///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2026.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

// Originally from:

/******************************************************************************************
  Filename    : main.c
  
  Core        : RISC-V
  
  MCU         : ESP32-P4
    
  Author      : Chalandi Amine
 
  Owner       : Chalandi Amine
  
  Date        : 25.01.2026
  
  Description : Application main function
  
******************************************************************************************/

#include <stdbool.h>
#include <stdint.h>

extern uint32_t osGetActiveCore(void);

extern void main_core0(void);
extern void main_core1(void);

void main_x(void) __attribute__((used,noinline));

void main_x(void)
{
  const bool core_id_is_zero = ((uint32_t) UINT8_C(0) == osGetActiveCore());

  // Go to the core-specific main subroutines.
  if(core_id_is_zero)
  {
    main_core0();
  }
  else
  {
    main_core1();
  }
}

int main(void) __attribute__((used,noinline));

void main_caller();

void main_caller()
{
  (void) main();
}
