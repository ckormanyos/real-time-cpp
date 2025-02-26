///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2021.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

extern "C" void unhandled_exception() __attribute__((interrupt_handler, used, noinline));

extern "C"
void unhandled_exception()
{
  for(;;)
  {
    asm volatile("nop");
  }
}
