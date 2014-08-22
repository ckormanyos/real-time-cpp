/////////////////////////////////////////////////////// 
//  Copyright 2014 Christopher Kormanyos.
//  Distributed under the Boost 
//  Software License, Version 1.0. 
//  (See accompanying file LICENSE_1_0.txt 
//  or copy at http://www.boost.org/LICENSE_1_0.txt ) 
//

#include <mcal_cpu.h>

extern "C" void __attribute__((nomips16, interrupt, used, noinline)) __vector_unused_irq();
extern "C" void __attribute__((nomips16, interrupt, used, noinline)) __vector_timer1    ();

#if defined(QUOTE)
#undef QUOTE
#endif

#define QUOTE(arg)   #arg
#define STRVAL(arg)  QUOTE(arg)

#define DECLARE_INTERRUPT(x, func)                          \
   asm(" .section .vector_" STRVAL(x) ",\"ax\",@progbits"); \
   asm(".set noreorder");                                   \
   asm(".ent _vector_" STRVAL(x) );                         \
   asm("_vector_" STRVAL(x) ":");                           \
   asm("j " STRVAL(func));                                  \
   asm("nop");                                              \
   asm(".end _vector_" STRVAL(x));                          \
   asm(".globl _vector_" STRVAL(x));                        \
   asm(".text")

DECLARE_INTERRUPT( 0, __vector_unused_irq); // coretimer                         0
DECLARE_INTERRUPT( 1, __vector_unused_irq); // coresw0                           1
DECLARE_INTERRUPT( 2, __vector_unused_irq); // coresw1                           2
DECLARE_INTERRUPT( 3, __vector_unused_irq); // int0                              3
DECLARE_INTERRUPT( 4, __vector_timer1);     // timer1                            4
DECLARE_INTERRUPT( 5, __vector_unused_irq); // ic1                               5
DECLARE_INTERRUPT( 6, __vector_unused_irq); // oc1                               6
DECLARE_INTERRUPT( 7, __vector_unused_irq); // int1                              7
DECLARE_INTERRUPT( 8, __vector_unused_irq); // timer2                            8
DECLARE_INTERRUPT( 9, __vector_unused_irq); // ic2                               9
DECLARE_INTERRUPT(10, __vector_unused_irq); // oc2                              10
DECLARE_INTERRUPT(11, __vector_unused_irq); // int2                             11
DECLARE_INTERRUPT(12, __vector_unused_irq); // timer3                           12
DECLARE_INTERRUPT(13, __vector_unused_irq); // ic3                              13
DECLARE_INTERRUPT(14, __vector_unused_irq); // oc3                              14
DECLARE_INTERRUPT(15, __vector_unused_irq); // int3                             15
DECLARE_INTERRUPT(16, __vector_unused_irq); // timer4                           16
DECLARE_INTERRUPT(17, __vector_unused_irq); // ic4                              17
DECLARE_INTERRUPT(18, __vector_unused_irq); // oc4                              18
DECLARE_INTERRUPT(19, __vector_unused_irq); // int4                             19
DECLARE_INTERRUPT(20, __vector_unused_irq); // timer5                           20
DECLARE_INTERRUPT(21, __vector_unused_irq); // ic5                              21
DECLARE_INTERRUPT(22, __vector_unused_irq); // oc5                              22
DECLARE_INTERRUPT(23, __vector_unused_irq); // spi1                             23
DECLARE_INTERRUPT(24, __vector_unused_irq); // i2c3, spi3, uart1                24
DECLARE_INTERRUPT(25, __vector_unused_irq); // i2c1                             25
DECLARE_INTERRUPT(26, __vector_unused_irq); // cn                               26
DECLARE_INTERRUPT(27, __vector_unused_irq); // adc                              27
DECLARE_INTERRUPT(28, __vector_unused_irq); // pmp                              28
DECLARE_INTERRUPT(29, __vector_unused_irq); // c1                               29
DECLARE_INTERRUPT(30, __vector_unused_irq); // c2                               30
DECLARE_INTERRUPT(31, __vector_unused_irq); // i2c4, spi2, uart3                31
DECLARE_INTERRUPT(32, __vector_unused_irq); // i2c5, spi4, uart2                32
DECLARE_INTERRUPT(33, __vector_unused_irq); // i2c2                             33
DECLARE_INTERRUPT(34, __vector_unused_irq); // fscm                             34
DECLARE_INTERRUPT(35, __vector_unused_irq); // rtcc                             35
DECLARE_INTERRUPT(36, __vector_unused_irq); // dma0                             36
DECLARE_INTERRUPT(37, __vector_unused_irq); // dma1                             37
DECLARE_INTERRUPT(38, __vector_unused_irq); // dma2                             38
DECLARE_INTERRUPT(39, __vector_unused_irq); // dma3                             39
DECLARE_INTERRUPT(40, __vector_unused_irq); // dma4                             40
DECLARE_INTERRUPT(41, __vector_unused_irq); // dma5                             41
DECLARE_INTERRUPT(42, __vector_unused_irq); // dma6                             42
DECLARE_INTERRUPT(43, __vector_unused_irq); // dma7                             43
DECLARE_INTERRUPT(44, __vector_unused_irq); // fce                              44
DECLARE_INTERRUPT(45, __vector_unused_irq); // usb1                             45
DECLARE_INTERRUPT(46, __vector_unused_irq); // can1                             46
DECLARE_INTERRUPT(47, __vector_unused_irq); // can2                             47
DECLARE_INTERRUPT(48, __vector_unused_irq); // eth                              48
DECLARE_INTERRUPT(49, __vector_unused_irq); // uart4                            49
DECLARE_INTERRUPT(50, __vector_unused_irq); // uart6                            50
DECLARE_INTERRUPT(51, __vector_unused_irq); // uart5                            51
DECLARE_INTERRUPT(52, __vector_unused_irq); // unused                           52
DECLARE_INTERRUPT(53, __vector_unused_irq); // unused                           53
DECLARE_INTERRUPT(54, __vector_unused_irq); // unused                           54
DECLARE_INTERRUPT(55, __vector_unused_irq); // unused                           55
DECLARE_INTERRUPT(56, __vector_unused_irq); // unused                           56
DECLARE_INTERRUPT(57, __vector_unused_irq); // unused                           57
DECLARE_INTERRUPT(58, __vector_unused_irq); // unused                           58
DECLARE_INTERRUPT(59, __vector_unused_irq); // unused                           59
DECLARE_INTERRUPT(60, __vector_unused_irq); // unused                           60
DECLARE_INTERRUPT(61, __vector_unused_irq); // unused                           61
DECLARE_INTERRUPT(62, __vector_unused_irq); // unused                           62
DECLARE_INTERRUPT(63, __vector_unused_irq); // unused                           63

void __attribute__((nomips16, interrupt, used, noinline)) __vector_unused_irq()
{
  for(;;)
  {
    mcal::cpu::nop();
  }
}
