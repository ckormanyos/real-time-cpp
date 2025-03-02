///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2022.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

extern void mcal_gpt_increment_tick();

void IntQ0OV() __attribute__((interrupt_handler, used, noinline));

void IntQ0OV()
{
  mcal_gpt_increment_tick();
}
