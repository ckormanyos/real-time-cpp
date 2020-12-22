///////////////////////////////////////////////////////////////////////////////
//  Copyright Michael Schnerr 2011 - 2013.
//  Copyright Christopher Kormanyos 2013 - 2020.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <array>
#include <cstddef>
#include <cstdint>
#include <mcal_cpu.h>
#include <mcal_irq.h>

extern "C" void __my_startup         () __attribute__((section(".startup"), used, noinline));
extern "C" void __undef_instr_handler() __attribute__((used, noinline));
extern "C" void __pend_sv_handler    () __attribute__((used, noinline));
extern "C" void __abort_handler      () __attribute__((used, noinline));
extern "C" void __irq_handler        () __attribute__((used, noinline, naked));
extern "C" void __fiq_handler        () __attribute__((used, noinline, naked));
extern "C" void __vector_unused_irq  () __attribute__((used, noinline));
extern "C" void __vector_timer7      ();

namespace
{
  typedef void(*function_type)();

  constexpr std::size_t number_of_interrupts_nmi = std::size_t(16U);
  constexpr std::size_t number_of_interrupts     = std::size_t(mcal::irq::interrupt_descriptor::number_of_interrupts);
}

extern "C" const volatile std::array<function_type, number_of_interrupts_nmi> __isr_vector_nmi __attribute__((section(".isr_vector_nmi")));
extern "C" const volatile std::array<function_type, number_of_interrupts>     __isr_vector     __attribute__((section(".isr_vector")));

void __undef_instr_handler() { for(;;) { mcal::cpu::nop(); } }
void __pend_sv_handler    () { for(;;) { mcal::cpu::nop(); } }
void __abort_handler      () { for(;;) { mcal::cpu::nop(); } }
void __vector_unused_irq  () { for(;;) { mcal::cpu::nop(); } }

extern "C"
const volatile std::array<function_type, number_of_interrupts_nmi> __isr_vector_nmi =
{{
  reinterpret_cast<function_type>(UINT32_C(0xE59FF018)),
  reinterpret_cast<function_type>(UINT32_C(0xE59FF018)),
  reinterpret_cast<function_type>(UINT32_C(0xE59FF018)),
  reinterpret_cast<function_type>(UINT32_C(0xE59FF018)),
  reinterpret_cast<function_type>(UINT32_C(0xE59FF014)),
  reinterpret_cast<function_type>(UINT32_C(0xE24FF008)),
  reinterpret_cast<function_type>(UINT32_C(0xE59FF010)),
  reinterpret_cast<function_type>(UINT32_C(0xE59FF010)),
  __my_startup,
  __undef_instr_handler,
  __pend_sv_handler,
  __abort_handler,
  __irq_handler,
  __fiq_handler,
  nullptr,
  nullptr
}};

extern "C"
const volatile std::array<function_type, number_of_interrupts> __isr_vector =
{{
  __vector_unused_irq,        // emuint            :   0
  __vector_unused_irq,        // commtx            :   1
  __vector_unused_irq,        // commrx            :   2
  __vector_unused_irq,        // bench             :   3
  __vector_unused_irq,        // elm_irq           :   4
  __vector_unused_irq,        // ssm_wfi_irq       :   5
  __vector_unused_irq,        // ssm_irq           :   6
  __vector_unused_irq,        // nmi               :   7
  __vector_unused_irq,        // sec_evnt          :   8
  __vector_unused_irq,        // l3debug           :   9
  __vector_unused_irq,        // l3appint          :  10
  __vector_unused_irq,        // prcmint           :  11
  __vector_unused_irq,        // edmacompint       :  12
  __vector_unused_irq,        // edmamperr         :  13
  __vector_unused_irq,        // edmaerrint        :  14
  __vector_unused_irq,        // wdt0int           :  15
  __vector_unused_irq,        // adc_tsc_genint    :  16
  __vector_unused_irq,        // usbssint          :  17
  __vector_unused_irq,        // usb0              :  18
  __vector_unused_irq,        // usb1              :  19
  __vector_unused_irq,        // pruss1_evtout0    :  20
  __vector_unused_irq,        // pruss1_evtout1    :  21
  __vector_unused_irq,        // pruss1_evtout2    :  22
  __vector_unused_irq,        // pruss1_evtout3    :  23
  __vector_unused_irq,        // pruss1_evtout4    :  24
  __vector_unused_irq,        // pruss1_evtout5    :  25
  __vector_unused_irq,        // pruss1_evtout6    :  26
  __vector_unused_irq,        // pruss1_evtout7    :  27
  __vector_unused_irq,        // mmcsd1int         :  28
  __vector_unused_irq,        // mmcsd2int         :  29
  __vector_unused_irq,        // i2c2int           :  30
  __vector_unused_irq,        // ecap0int          :  31
  __vector_unused_irq,        // gpioint2a         :  32
  __vector_unused_irq,        // gpioint2b         :  33
  __vector_unused_irq,        // usbwakeup         :  34
  __vector_unused_irq,        // unused35          :  35
  __vector_unused_irq,        // lcdcint           :  36
  __vector_unused_irq,        // gfxint            :  37
  __vector_unused_irq,        // 2dhwaint          :  38
  __vector_unused_irq,        // epwm2int          :  39
  __vector_unused_irq,        // 3pgswrxthr0       :  40
  __vector_unused_irq,        // 3pgswrxint0       :  41
  __vector_unused_irq,        // 3pgswtxint0       :  42
  __vector_unused_irq,        // 3pgswmisc0        :  43
  __vector_unused_irq,        // uart3int          :  44
  __vector_unused_irq,        // uart4int          :  45
  __vector_unused_irq,        // uart5int          :  46
  __vector_unused_irq,        // ecap1int          :  47
  __vector_unused_irq,        // unused48          :  48
  __vector_unused_irq,        // unused49          :  49
  __vector_unused_irq,        // unused50          :  50
  __vector_unused_irq,        // unused51          :  51
  __vector_unused_irq,        // dcan0_int0        :  52
  __vector_unused_irq,        // dcan0_int1        :  53
  __vector_unused_irq,        // dcan0_parity      :  54
  __vector_unused_irq,        // dcan1_int0        :  55
  __vector_unused_irq,        // dcan1_int1        :  56
  __vector_unused_irq,        // dcan1_parity      :  57
  __vector_unused_irq,        // epwm0_tzint       :  58
  __vector_unused_irq,        // epwm1_tzint       :  59
  __vector_unused_irq,        // epwm2_tzint       :  60
  __vector_unused_irq,        // ecap2int          :  61
  __vector_unused_irq,        // gpioint3a         :  62
  __vector_unused_irq,        // gpioint3b         :  63
  __vector_unused_irq,        // mmcsd0int         :  64
  __vector_unused_irq,        // spi0int           :  65
  __vector_unused_irq,        // tint0             :  66
  __vector_unused_irq,        // tint1_1ms         :  67
  __vector_unused_irq,        // tint2             :  68
  __vector_unused_irq,        // tint3             :  69
  __vector_unused_irq,        // i2c0int           :  70
  __vector_unused_irq,        // i2c1int           :  71
  __vector_unused_irq,        // uart0int          :  72
  __vector_unused_irq,        // uart1int          :  73
  __vector_unused_irq,        // uart2int          :  74
  __vector_unused_irq,        // rtcint            :  75
  __vector_unused_irq,        // rtcalarmint       :  76
  __vector_unused_irq,        // mbint0            :  77
  __vector_unused_irq,        // m3_txev           :  78
  __vector_unused_irq,        // eqep0int          :  79
  __vector_unused_irq,        // mcatxint0         :  80
  __vector_unused_irq,        // mcarxint0         :  81
  __vector_unused_irq,        // mcatxint1         :  82
  __vector_unused_irq,        // mcarxint1         :  83
  __vector_unused_irq,        // dummy84           :  84
  __vector_unused_irq,        // dummy84           :  85
  __vector_unused_irq,        // epwm0int          :  86
  __vector_unused_irq,        // epwm1int          :  87
  __vector_unused_irq,        // eqep1int          :  88
  __vector_unused_irq,        // eqep2int          :  89
  __vector_unused_irq,        // dma_intr_pin2     :  90
  __vector_unused_irq,        // wdt1int           :  91
  __vector_unused_irq,        // tint4             :  92
  __vector_unused_irq,        // tint5             :  93
  __vector_unused_irq,        // tint6             :  94
  __vector_timer7,            // tint7             :  95
  __vector_unused_irq,        // gpioint0a         :  96
  __vector_unused_irq,        // gpioint0b         :  97
  __vector_unused_irq,        // gpioint1a         :  98
  __vector_unused_irq,        // gpioint1b         :  99
  __vector_unused_irq,        // gpmcint           : 100
  __vector_unused_irq,        // ddrerr0           : 101
  __vector_unused_irq,        // aes0_irq_s        : 102
  __vector_unused_irq,        // aes0_irq_p        : 103
  __vector_unused_irq,        // unused104         : 104
  __vector_unused_irq,        // unused105         : 105
  __vector_unused_irq,        // unused106         : 106
  __vector_unused_irq,        // unused107         : 107
  __vector_unused_irq,        // sha_irq_s         : 108
  __vector_unused_irq,        // sha_irq_p         : 109
  __vector_unused_irq,        // fpka_sintrequest_s: 110
  __vector_unused_irq,        // rng_irq           : 111
  __vector_unused_irq,        // tcerrint0         : 112
  __vector_unused_irq,        // tcerrint1         : 113
  __vector_unused_irq,        // tcerrint2         : 114
  __vector_unused_irq,        // unused115         : 115
  __vector_unused_irq,        // unused116         : 116
  __vector_unused_irq,        // unused117         : 117
  __vector_unused_irq,        // unused118         : 118
  __vector_unused_irq,        // unused119         : 119
  __vector_unused_irq,        // smrflx_sabertooth : 120
  __vector_unused_irq,        // smrflx_core       : 121
  __vector_unused_irq,        // unused122         : 122
  __vector_unused_irq,        // dma_intr_pin0     : 123
  __vector_unused_irq,        // dma_intr_pin1     : 124
  __vector_unused_irq,        // spi1int           : 125
  __vector_unused_irq,        // unused126         : 126
  __vector_unused_irq         // unused127         : 127
}};

void __irq_handler()
{
  // Route the ISR of highest priority in the IRQ to its handler.
  // This does not support nested interrupts.

  // For an alternate implementation in the assembly language
  // of the target processor and additional information, see parts
  // of Sitara Ware's "exception.s".

  asm volatile("stmfd r13!, {r0-r3, r12, r14}");
  asm volatile("ldr r0, =0x48200040");
  asm volatile("ldr r1, [r0]");
  asm volatile("and r1, r1, #0x0000007F");
  asm volatile("ldr r0, =__isr_vector");
  asm volatile("add r14, pc, #0");
  asm volatile("ldr pc, [r0, r1, lsl #2]");
  asm volatile("mov r0, #0x00000001");
  asm volatile("ldr r1, =0x48200048");
  asm volatile("str r0, [r1]");
  asm volatile("dmb");
  asm volatile("ldmfd r13!, {r0-r3, r12, r14}");
  asm volatile("subs pc, r14, #0x4");
}

void __fiq_handler()
{
  // Route the ISR of highest priority in the FIQ to its handler.
  // This does not support nested interrupts.

  // For an alternate implementation in the assembly language
  // of the target processor and additional information, see parts
  // of Sitara Ware's "exception.s".

  asm volatile("stmfd r13!, {r0-r3, r12, r14}");
  asm volatile("ldr r0, =0x48200044");
  asm volatile("ldr r1, [r0]");
  asm volatile("and r1, r1, #0x0000007F");
  asm volatile("ldr r0, =__isr_vector");
  asm volatile("add r14, pc, #0");
  asm volatile("ldr pc, [r0, r1, lsl #2]");
  asm volatile("mov r0, #0x00000002");
  asm volatile("ldr r1, =0x48200048");
  asm volatile("str r0, [r1]");
  asm volatile("dmb");
  asm volatile("ldmfd r13!, {r0-r3, r12, r14}");
  asm volatile("subs pc, r14, #0x4");
}
