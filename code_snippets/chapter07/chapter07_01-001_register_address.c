///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2019 - 2024.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

// chapter07_01-001_register_address.c

#include <stdio.h>
#include <stdint.h>

static uint8_t simulated_register_portb;

// The simulated address of portb.
#define REG_PORTB ((uintptr_t) &simulated_register_portb)

void do_something(void);

void do_something(void)
{
  // Set portb to 0.
  *((volatile uint8_t*) REG_PORTB) = UINT8_C(0);
}

int main(void);

int main(void)
{
  do_something();

  printf("simulated_register_portb: %d\n", (unsigned) simulated_register_portb);
}
