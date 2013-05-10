///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2013.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

asm volatile (".extern __tablejump__");

asm volatile (".extern _ctors_begin");
asm volatile (".extern _ctors_end");

extern "C" void __do_global_ctors() __attribute__ ((section(".init6")));

extern "C" void __do_global_ctors()
{
  asm volatile ("ldi r17, hi8(_ctors_begin)");
  asm volatile ("ldi r28, lo8(_ctors_end)");
  asm volatile ("ldi r29, hi8(_ctors_end)");

  asm volatile ("rjmp .L__do_global_ctors_start");

  asm volatile (".L__do_global_ctors_loop:");

  asm volatile ("sbiw  r28, 0x02");
  asm volatile ("movw  r30, r28");
  asm volatile ("call __tablejump__");

  asm volatile (".L__do_global_ctors_start:");

  asm volatile ("cpi r28, lo8(_ctors_begin)");
  asm volatile ("cpc r29, r17");
  asm volatile ("brne .L__do_global_ctors_loop");
}

extern "C" void __tablejump__() __attribute__ ((section(".text")));

extern "C" void __tablejump__()
{
  asm volatile ("lpm  r0, Z+");
  asm volatile ("lpm  r31, Z");
  asm volatile ("mov  r30, r0");
  asm volatile ("ijmp");
}
