///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2018 - 2019.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <array>
#include <cstddef>
#include <mcal_cpu.h>

extern "C" void __initial_stack_pointer();

extern "C" void __my_startup         () __attribute__((used, noinline));
extern "C" void __vector_unused_irq  () __attribute__((used, noinline));
extern "C" void __nmi_handler        () __attribute__((used, noinline));
extern "C" void __hard_fault_handler () __attribute__((used, noinline));
extern "C" void __mem_manage_handler () __attribute__((used, noinline));
extern "C" void __bus_fault_handler  () __attribute__((used, noinline));
extern "C" void __usage_fault_handler() __attribute__((used, noinline));
extern "C" void __svc_handler        () __attribute__((used, noinline));
extern "C" void __debug_mon_handler  () __attribute__((used, noinline));
extern "C" void __pend_sv_handler    () __attribute__((used, noinline));
extern "C" void __sys_tick_handler   () __attribute__((used, noinline));
extern "C" void __vector_timer4      ();

extern "C" void __vector_unused_irq  () { for(;;) { mcal::cpu::nop(); } }
extern "C" void __nmi_handler        () { for(;;) { mcal::cpu::nop(); } }
extern "C" void __hard_fault_handler () { for(;;) { mcal::cpu::nop(); } }
extern "C" void __mem_manage_handler () { for(;;) { mcal::cpu::nop(); } }
extern "C" void __bus_fault_handler  () { for(;;) { mcal::cpu::nop(); } }
extern "C" void __usage_fault_handler() { for(;;) { mcal::cpu::nop(); } }
extern "C" void __svc_handler        () { for(;;) { mcal::cpu::nop(); } }
extern "C" void __debug_mon_handler  () { for(;;) { mcal::cpu::nop(); } }
extern "C" void __pend_sv_handler    () { for(;;) { mcal::cpu::nop(); } }
extern "C" void __sys_tick_handler   () { for(;;) { mcal::cpu::nop(); } }

namespace
{
  typedef void(*isr_type)();

  constexpr std::size_t number_of_interrupts = 128U;
}

extern "C"
const volatile std::array<isr_type, number_of_interrupts> __isr_vector __attribute__((section(".isr_vector")));

extern "C"
const volatile std::array<isr_type, number_of_interrupts> __isr_vector =
{{
  __initial_stack_pointer,   // 0x0000, initial stack pointer
  __my_startup,              // 0x0004, reset
  __nmi_handler,             // 0x0008, nmi exception
  __hard_fault_handler,      // 0x000C, hard fault exception
  __mem_manage_handler,      // 0x0010, memory management exception
  __bus_fault_handler,       // 0x0014, bus fault exception
  __usage_fault_handler,     // 0x0018, usage fault exception
  __vector_unused_irq,       // 0x001C, reserved
  __vector_unused_irq,       // 0x0020, reserved
  __vector_unused_irq,       // 0x0024, reserved
  __vector_unused_irq,       // 0x0028, reserved
  __svc_handler,             // 0x002C, svc handler
  __debug_mon_handler,       // 0x0030, debug monitor
  __vector_unused_irq,       // 0x0034, reserved
  __pend_sv_handler,         // 0x0038, pending svc,
  __sys_tick_handler,        // 0x003C, system tick handler,
  __vector_unused_irq,       // 0x0040, wwdg irq handler,
  __vector_unused_irq,       // 0x0044, pvd irq handler,
  __vector_unused_irq,       // 0x0048, tamper irq handler,
  __vector_unused_irq,       // 0x004C, rtc irq handler,
  __vector_unused_irq,       // 0x0050, flash irq handler,
  __vector_unused_irq,       // 0x0054, rcc irq handler,
  __vector_unused_irq,       // 0x0058, exti0 irq handler,
  __vector_unused_irq,       // 0x005C, exti1 irq handler,
  __vector_unused_irq,       // 0x0060, exti2 irq handler,
  __vector_unused_irq,       // 0x0064, exti3 irq handler,
  __vector_unused_irq,       // 0x0068, exti4 irq handler,
  __vector_unused_irq,       // 0x006C, dma_channel1 irq handler,
  __vector_unused_irq,       // 0x0070, dma_channel2 irq handler,
  __vector_unused_irq,       // 0x0074, dma_channel3 irq handler,
  __vector_unused_irq,       // 0x0078, dma_channel4 irq handler,
  __vector_unused_irq,       // 0x007C, dma_channel5 irq handler,
  __vector_unused_irq,       // 0x0080, dma_channel6 irq handler,
  __vector_unused_irq,       // 0x0084, dma_channel7 irq handler,
  __vector_unused_irq,       // 0x0088, adc irq handler,
  __vector_unused_irq,       // 0x008C, usb_hp_can_tx irq handler,
  __vector_unused_irq,       // 0x0090, usb_lp_can_rx0 irq handler,
  __vector_unused_irq,       // 0x0094, can_rx1 irq handler,
  __vector_unused_irq,       // 0x0098, can_sce irq handler,
  __vector_unused_irq,       // 0x009C, exti9_5 irq handler,
  __vector_unused_irq,       // 0x00A0, tim1_brk irq handler,
  __vector_unused_irq,       // 0x00A4, tim1_up irq handler,
  __vector_unused_irq,       // 0x00A8, tim1_trg_com irq handler,
  __vector_unused_irq,       // 0x00AC, tim1_cc irq handler,
  __vector_unused_irq,       // 0x00B0, tim2 irq handler,
  __vector_unused_irq,       // 0x00B4, tim3 irq handler,
  __vector_timer4,           // 0x00B8, tim4 irq handler,
  __vector_unused_irq,       // 0x00BC, i2c1_ev irq handler,
  __vector_unused_irq,       // 0x00C0, i2c1_er irq handler,
  __vector_unused_irq,       // 0x00C4, i2c2_ev irq handler,
  __vector_unused_irq,       // 0x00C8, i2c2_er irq handler,
  __vector_unused_irq,       // 0x00CC, spi1 irq handler,
  __vector_unused_irq,       // 0x00D0, spi2 irq handler,
  __vector_unused_irq,       // 0x00D4, usart1 irq handler,
  __vector_unused_irq,       // 0x00D8, usart2 irq handler,
  __vector_unused_irq,       // 0x00DC, usart3 irq handler,
  __vector_unused_irq,       // 0x00E0, exti15_10 irq handler,
  __vector_unused_irq,       // 0x00E4, rtcalarm irq handler,
  __vector_unused_irq,       // 0x00E8, usbwakeup irq handler,
  __vector_unused_irq,       // 0x00EC, tim8 break and tim12
  __vector_unused_irq,       // 0x00F0, tim8 update and tim13
  __vector_unused_irq,       // 0x00F4, tim8 trigger and commutation and tim14
  __vector_unused_irq,       // 0x00F8, tim8 capture compare
  __vector_unused_irq,       // 0x00FC, dma1 stream7
  __vector_unused_irq,       // 0x0100, fmc
  __vector_unused_irq,       // 0x0104, sdio
  __vector_unused_irq,       // 0x0108, tim5
  __vector_unused_irq,       // 0x010C, spi3
  __vector_unused_irq,       // 0x0110, uart4
  __vector_unused_irq,       // 0x0114, uart5
  __vector_unused_irq,       // 0x0118, tim6 and dac1&2 underrun errors
  __vector_unused_irq,       // 0x011C, tim7
  __vector_unused_irq,       // 0x0120, dma2 stream 0
  __vector_unused_irq,       // 0x0124, dma2 stream 1
  __vector_unused_irq,       // 0x0128, dma2 stream 2
  __vector_unused_irq,       // 0x012C, dma2 stream 3
  __vector_unused_irq,       // 0x0130, dma2 stream 4
  __vector_unused_irq,       // 0x0134, ethernet
  __vector_unused_irq,       // 0x0138, ethernet wakeup through exti line
  __vector_unused_irq,       // 0x013C, can2 tx
  __vector_unused_irq,       // 0x0140, can2 rx0
  __vector_unused_irq,       // 0x0144, can2 rx1
  __vector_unused_irq,       // 0x0148, can2 sce
  __vector_unused_irq,       // 0x014C, usb otg fs
  __vector_unused_irq,       // 0x0150, dma2 stream 5
  __vector_unused_irq,       // 0x0154, dma2 stream 6
  __vector_unused_irq,       // 0x0158, dma2 stream 7
  __vector_unused_irq,       // 0x015C, usart6
  __vector_unused_irq,       // 0x0160, i2c3 event
  __vector_unused_irq,       // 0x0164, i2c3 error
  __vector_unused_irq,       // 0x0168, usb otg hs end point 1 out
  __vector_unused_irq,       // 0x016C, usb otg hs end point 1 in
  __vector_unused_irq,       // 0x0170, usb otg hs wakeup through exti
  __vector_unused_irq,       // 0x0174, usb otg hs
  __vector_unused_irq,       // 0x0178, dcmi
  __vector_unused_irq,       // 0x017C, cryp crypto
  __vector_unused_irq,       // 0x0180, hash and rng
  __vector_unused_irq,       // 0x0184, fpu
  __vector_unused_irq,       // 0x0188, uart7
  __vector_unused_irq,       // 0x018C, uart8
  __vector_unused_irq,       // 0x0190, spi4
  __vector_unused_irq,       // 0x0194, spi5
  __vector_unused_irq,       // 0x0198, spi6
  __vector_unused_irq,       // 0x019C, sai1
  __vector_unused_irq,       // 0x01A0, reserved
  __vector_unused_irq,       // 0x01A4, reserved
  __vector_unused_irq,       // 0x01A8, dma2d
  nullptr,                   // 0x01AC, dummy
  nullptr,                   // 0x01B0, dummy
  nullptr,                   // 0x01B4, dummy
  nullptr,                   // 0x01B8, dummy
  nullptr,                   // 0x01BC, dummy
  nullptr,                   // 0x01C0, dummy
  nullptr,                   // 0x01C4, dummy
  nullptr,                   // 0x01C8, dummy
  nullptr,                   // 0x01CC, dummy
  nullptr,                   // 0x01D0, dummy
  nullptr,                   // 0x01D4, dummy
  nullptr,                   // 0x01D8, dummy
  nullptr,                   // 0x01DC, dummy
  nullptr,                   // 0x01E0, dummy
  nullptr,                   // 0x01E4, dummy
  nullptr,                   // 0x01E8, dummy
  nullptr,                   // 0x01EC, dummy
  nullptr,                   // 0x01F0, dummy
  nullptr,                   // 0x01F4, dummy
  nullptr,                   // 0x01F8, dummy
  nullptr                    // 0x01FC, dummy
}};

/*
Reserved 0x0000 (See pages 238-242 in the manual)
-3 fixed Reset Reset 0x0004
-2 fixed NMI Non maskable interrupt, Clock Security System 0x0008
-1 fixed HardFault All class of fault 0x000C
0 settable MemManage Memory management 0x0010
1 settable BusFault Pre-fetch fault, memory access fault 0x0014
2 settable UsageFault Undefined instruction or illegal state 0x0018
Reserved 0x001C
Reserved 0x0020
Reserved 0x0024
Reserved 0x0028
3 settable SVCall System Service call via SWI instruction 0x002C
4 settable Debug Monitor Debug Monitor 0x0030
Reserved 0x0034
5 settable PendSV Pendable request for system service 0x0038
6 settable Systick System tick timer 0x003C
0 7 settable WWDG Window Watchdog interrupt 0x0040
1 8 settable PVD PVD through EXTI line detection interrupt 0x0044
2 9 settable TAMP_STAMP Tamper and TimeStamp interrupts through the EXTI line 0x0048
3 10 settable RTC_WKUP RTC Wakeup interrupt through the EXTI line 0x004C
4 11 settable FLASH Flash global interrupt 0x0050
5 12 settable RCC RCC global interrupt 0x0054
6 13 settable EXTI0 EXTI Line0 interrupt 0x0058
7 14 settable EXTI1 EXTI Line1 interrupt 0x005C
8 15 settable EXTI2 EXTI Line2 interrupt 0x0060
9 16 settable EXTI3 EXTI Line3 interrupt 0x0064
10 17 settable EXTI4 EXTI Line4 interrupt 0x0068
11 18 settable DMA1_Stream0 DMA1 Stream0 global interrupt 0x006C
12 19 settable DMA1_Stream1 DMA1 Stream1 global interrupt 0x0070
13 20 settable DMA1_Stream2 DMA1 Stream2 global interrupt 0x0074
14 21 settable DMA1_Stream3 DMA1 Stream3 global interrupt 0x0078
15 22 settable DMA1_Stream4 DMA1 Stream4 global interrupt 0x007C
16 23 settable DMA1_Stream5 DMA1 Stream5 global interrupt 0x0080
17 24 settable DMA1_Stream6 DMA1 Stream6 global interrupt 0x0084
18 25 settable ADC ADC1, ADC2 and ADC3 global interrupts 0x0088
19 26 settable CAN1_TX CAN1 TX interrupts 0x008C
20 27 settable CAN1_RX0 CAN1 RX0 interrupts 0x0090
21 28 settable CAN1_RX1 CAN1 RX1 interrupt 0x0094
22 29 settable CAN1_SCE CAN1 SCE interrupt 0x0098
23 30 settable EXTI9_5 EXTI Line[9:5] interrupts 0x009C
24 31 settable TIM1_BRK_TIM9 TIM1 Break interrupt and TIM9 global interrupt 0x00A0
25 32 settable TIM1_UP_TIM10 TIM1 Update interrupt and TIM10 global interrupt 0x00A4
26 33 settable TIM1_TRG_COM_TIM11 TIM1 Trigger and Commutation interrupts and TIM11 global interrupt 0x00A8
27 34 settable TIM1_CC TIM1 Capture Compare interrupt 0x00AC
28 35 settable TIM2 TIM2 global interrupt 0x00B0
29 36 settable TIM3 TIM3 global interrupt 0x00B4
30 37 settable TIM4 TIM4 global interrupt 0x00B8
31 38 settable I2C1_EV I2C1 event interrupt 0x00BC
32 39 settable I2C1_ER I2C1 error interrupt 0x00C0
33 40 settable I2C2_EV I2C2 event interrupt 0x00C4
34 41 settable I2C2_ER I2C2 error interrupt 0x00C8
35 42 settable SPI1 SPI1 global interrupt 0x00CC
36 43 settable SPI2 SPI2 global interrupt 0x00D0
37 44 settable USART1 USART1 global interrupt 0x00D4
38 45 settable USART2 USART2 global interrupt 0x00D8
39 46 settable USART3 USART3 global interrupt 0x00DC
40 47 settable EXTI15_10 EXTI Line[15:10] interrupts 0x00E0
41 48 settable RTC_Alarm RTC Alarms (A and B) through EXTI line interrupt 0x00E4
42 49 settable OTG_FS WKUP USB On-The-Go FS Wakeup through EXTI line interrupt 0x00E8
43 50 settable TIM8_BRK_TIM12 TIM8 Break interrupt and TIM12 global interrupt 0x00EC
44 51 settable TIM8_UP_TIM13 TIM8 Update interrupt and TIM13 global interrupt 0x00F0
45 52 settable TIM8_TRG_COM_TIM14 TIM8 Trigger and Commutation interrupts and TIM14 global interrupt 0x00F4
46 53 settable TIM8_CC TIM8 Capture Compare interrupt 0x00F8
47 54 settable DMA1_Stream7 DMA1 Stream7 global interrupt 0x00FC
48 55 settable FMC FMC global interrupt 0x0100
49 56 settable SDIO SDIO global interrupt 0x0104
50 57 settable TIM5 TIM5 global interrupt 0x0108
51 58 settable SPI3 SPI3 global interrupt 0x010C
52 59 settable UART4 UART4 global interrupt 0x0110
53 60 settable UART5 UART5 global interrupt 0x0114
54 61 settable TIM6_DAC TIM6 global interrupt, DAC1 and DAC2 underrun error interrupts 0x0118
55 62 settable TIM7 TIM7 global interrupt 0x011C
56 63 settable DMA2_Stream0 DMA2 Stream0 global interrupt 0x0120
57 64 settable DMA2_Stream1 DMA2 Stream1 global interrupt 0x0124
58 65 settable DMA2_Stream2 DMA2 Stream2 global interrupt 0x0128
59 66 settable DMA2_Stream3 DMA2 Stream3 global interrupt 0x012C
60 67 settable DMA2_Stream4 DMA2 Stream4 global interrupt 0x0130
61 68 Reserved 0x0134
62 69 Reserved 0x0138
63 70 settable CAN2_TX CAN2 TX interrupts 0x013C
64 71 settable CAN2_RX0 CAN2 RX0 interrupts 0x0140
65 72 settable CAN2_RX1 CAN2 RX1 interrupt 0x0144
66 73 settable CAN2_SCE CAN2 SCE interrupt 0x0148
67 74 settable OTG_FS USB On The Go FS global interrupt 0x014C
68 75 settable DMA2_Stream5 DMA2 Stream5 global interrupt 0x0150
69 76 settable DMA2_Stream6 DMA2 Stream6 global interrupt 0x0154
70 77 settable DMA2_Stream7 DMA2 Stream7 global interrupt 0x0158
71 78 settable USART6 USART6 global interrupt 0x015C
72 79 settable I2C3_EV I2C3 event interrupt 0x0160
73 80 settable I2C3_ER I2C3 error interrupt 0x0164
74 81 settable OTG_HS_EP1_OUT USB On The Go HS End Point 1 Out global interrupt 0x0168
75 82 settable OTG_HS_EP1_IN USB On The Go HS End Point 1 In global interrupt 0x016C
76 83 settable OTG_HS_WKUP USB On The Go HS Wakeup through EXTI interrupt 0x0170
77 84 settable OTG_HS USB On The Go HS global interrupt 0x0174
78 85 settable DCMI DCMI global interrupt 0x0178
79 86 Reserved 0x017C
80 87 Reserved 0x0180
81 88 settable FPU FPU global interrupt 0x0184
82 89 Reserved 0x0188
83 90 Reserved 0x018C
84 91 settable SPI4 SPI 4 global interrupt 0x0190
85 92 Reserved 0x0194
86 93 Reserved 0x0198
87 94 settable SAI1 SAI1 global interrupt 0x019C
88 95 Reserved 0x01A0
89 96 Reserved 0x01A4
90 97 Reserved 0x01A8
91 98 settable SAI2 SAI2 global interrupt 0x01AC
92 99 settable QuadSPI QuadSPI global interrupt 0x01B0
93 100 settable HDMI-CEC HDMI-CEC global interrupt 0x01B4
94 101 settable SPDIF-Rx SPDIF-Rx global interrupt 0x01B8
95 102 settable FMPI2C1 FMPI2C1 event interrupt 0x01BC
96 103 settable FMPI2C1 error FMPI2C1 error interrupt 0x01C0
*/
