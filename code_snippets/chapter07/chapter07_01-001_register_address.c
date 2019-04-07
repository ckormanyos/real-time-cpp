///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2019.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

// chapter07_01-001_register_address.c

#include <stdio.h>
#include <stdint.h>

static uint8_t simulated_address_of_portb_at_0x25;

// The simulated address of portb.
#define REG_PORTB ((uintptr_t) &simulated_address_of_portb_at_0x25)

void do_something()
{
  // Set portb to 0.
  *((volatile uint8_t*) REG_PORTB) = UINT8_C(0);
}

int main()
{
  do_something();

  printf("simulated_address_of_portb_at_0x25: %d\n",
         (unsigned) simulated_address_of_portb_at_0x25);
}
