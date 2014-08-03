/////////////////////////////////////////////////////// 
//  Copyright 2014 Christopher Kormanyos.
//  Distributed under the Boost 
//  Software License, Version 1.0. 
//  (See accompanying file LICENSE_1_0.txt 
//  or copy at http://www.boost.org/LICENSE_1_0.txt ) 
//

#include <mcal_cpu.h>

extern "C" void __vector_unused_irq() __attribute__ ((used, noinline));
extern "C" void __vector_timer2    ();

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

DECLARE_INTERRUPT( 0, __vector_unused_irq); // CORETIMER_VECTOR                         0
DECLARE_INTERRUPT( 1, __vector_unused_irq); // CORESW0_VECTOR                           1
DECLARE_INTERRUPT( 2, __vector_unused_irq); // CORESW1_VECTOR                           2
DECLARE_INTERRUPT( 3, __vector_unused_irq); // INT0_VECTOR                              3
DECLARE_INTERRUPT( 4, __vector_unused_irq); // TIMER1_VECTOR                            4
DECLARE_INTERRUPT( 5, __vector_unused_irq); // IC1_VECTOR                               5
DECLARE_INTERRUPT( 6, __vector_unused_irq); // OC1_VECTOR                               6
DECLARE_INTERRUPT( 7, __vector_unused_irq); // INT1_VECTOR                              7
DECLARE_INTERRUPT( 8, __vector_timer2);     // TIMER2_VECTOR                            8
DECLARE_INTERRUPT( 9, __vector_unused_irq); // IC2_VECTOR                               9
DECLARE_INTERRUPT(10, __vector_unused_irq); // OC2_VECTOR                              10
DECLARE_INTERRUPT(11, __vector_unused_irq); // INT2_VECTOR                             11
DECLARE_INTERRUPT(12, __vector_unused_irq); // TIMER3_VECTOR                           12
DECLARE_INTERRUPT(13, __vector_unused_irq); // IC3_VECTOR                              13
DECLARE_INTERRUPT(14, __vector_unused_irq); // OC3_VECTOR                              14
DECLARE_INTERRUPT(15, __vector_unused_irq); // INT3_VECTOR                             15
DECLARE_INTERRUPT(16, __vector_unused_irq); // TIMER4_VECTOR                           16
DECLARE_INTERRUPT(17, __vector_unused_irq); // IC4_VECTOR                              17
DECLARE_INTERRUPT(18, __vector_unused_irq); // OC4_VECTOR                              18
DECLARE_INTERRUPT(19, __vector_unused_irq); // INT4_VECTOR                             19
DECLARE_INTERRUPT(20, __vector_unused_irq); // TIMER5_VECTOR                           20
DECLARE_INTERRUPT(21, __vector_unused_irq); // IC5_VECTOR                              21
DECLARE_INTERRUPT(22, __vector_unused_irq); // OC5_VECTOR                              22
DECLARE_INTERRUPT(23, __vector_unused_irq); // SPI1_VECTOR                             23
DECLARE_INTERRUPT(24, __vector_unused_irq); // I2C3_VECTOR, SPI3_VECTOR, UART1_VECTOR  24
DECLARE_INTERRUPT(25, __vector_unused_irq); // I2C1_VECTOR                             25
DECLARE_INTERRUPT(26, __vector_unused_irq); // CN_VECTOR                               26
DECLARE_INTERRUPT(27, __vector_unused_irq); // ADC_VECTOR                              27
DECLARE_INTERRUPT(28, __vector_unused_irq); // PMP_VECTOR                              28
DECLARE_INTERRUPT(29, __vector_unused_irq); // C1_VECTOR                               29
DECLARE_INTERRUPT(30, __vector_unused_irq); // C2_VECTOR                               30
DECLARE_INTERRUPT(31, __vector_unused_irq); // I2C4_VECTOR, SPI2_VECTOR, UART3_VECTOR  31
DECLARE_INTERRUPT(32, __vector_unused_irq); // I2C5_VECTOR, SPI4_VECTOR, UART2_VECTOR  32
DECLARE_INTERRUPT(33, __vector_unused_irq); // I2C2_VECTOR                             33
DECLARE_INTERRUPT(34, __vector_unused_irq); // FSCM_VECTOR                             34
DECLARE_INTERRUPT(35, __vector_unused_irq); // RTCC_VECTOR                             35
DECLARE_INTERRUPT(36, __vector_unused_irq); // DMA0_VECTOR                             36
DECLARE_INTERRUPT(37, __vector_unused_irq); // DMA1_VECTOR                             37
DECLARE_INTERRUPT(38, __vector_unused_irq); // DMA2_VECTOR                             38
DECLARE_INTERRUPT(39, __vector_unused_irq); // DMA3_VECTOR                             39
DECLARE_INTERRUPT(40, __vector_unused_irq); // DMA4_VECTOR                             40
DECLARE_INTERRUPT(41, __vector_unused_irq); // DMA5_VECTOR                             41
DECLARE_INTERRUPT(42, __vector_unused_irq); // DMA6_VECTOR                             42
DECLARE_INTERRUPT(43, __vector_unused_irq); // DMA7_VECTOR                             43
DECLARE_INTERRUPT(44, __vector_unused_irq); // FCE_VECTOR                              44
DECLARE_INTERRUPT(45, __vector_unused_irq); // USB1_VECTOR                             45
DECLARE_INTERRUPT(46, __vector_unused_irq); // CAN1_VECTOR                             46
DECLARE_INTERRUPT(47, __vector_unused_irq); // CAN2_VECTOR                             47
DECLARE_INTERRUPT(48, __vector_unused_irq); // ETH_VECTOR                              48
DECLARE_INTERRUPT(49, __vector_unused_irq); // UART4_VECTOR                            49
DECLARE_INTERRUPT(50, __vector_unused_irq); // UART6_VECTOR                            50
DECLARE_INTERRUPT(51, __vector_unused_irq); // UART5_VECTOR                            51
DECLARE_INTERRUPT(52, __vector_unused_irq); // unused                                  52
DECLARE_INTERRUPT(53, __vector_unused_irq); // unused                                  53
DECLARE_INTERRUPT(54, __vector_unused_irq); // unused                                  54
DECLARE_INTERRUPT(55, __vector_unused_irq); // unused                                  55
DECLARE_INTERRUPT(56, __vector_unused_irq); // unused                                  56
DECLARE_INTERRUPT(57, __vector_unused_irq); // unused                                  57
DECLARE_INTERRUPT(58, __vector_unused_irq); // unused                                  58
DECLARE_INTERRUPT(59, __vector_unused_irq); // unused                                  59
DECLARE_INTERRUPT(60, __vector_unused_irq); // unused                                  60
DECLARE_INTERRUPT(61, __vector_unused_irq); // unused                                  61
DECLARE_INTERRUPT(62, __vector_unused_irq); // unused                                  62
DECLARE_INTERRUPT(63, __vector_unused_irq); // unused                                  63

void __vector_unused_irq()
{
  for(;;)
  {
    mcal::cpu::nop();
  }
}
