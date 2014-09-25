/////////////////////////////////////////////////////// 
//  Copyright 2013 Stephan Hage.
//  Copyright 2013 Christopher Kormanyos.
//  Distributed under the Boost 
//  Software License, Version 1.0. 
//  (See accompanying file LICENSE_1_0.txt 
//  or copy at http://www.boost.org/LICENSE_1_0.txt ) 
//

#include <array>
#include <cstdint>
#include <mcal_cpu.h>

extern "C"
const volatile std::array<std::uint8_t, 16U> option_bytes __attribute__((section(".opt")));

extern "C"
const volatile std::array<std::uint8_t, 16U> option_bytes =
{
  0xFF, 0xFF, 0xFF, 0xFF,
  0xFF, 0xFF, 0xFF, 0xFF,
  0xFF, 0xFF, 0xFF, 0xFF,
  0xFF, 0xFF, 0xFF, 0xFF
};

extern "C" void __my_startup();

extern "C" void __vector_unused_irq               () __attribute__((interrupt, used, externally_visible));
extern "C" void __rx_priviledged_exception_handler() __attribute__((interrupt, used, externally_visible));
extern "C" void __rx_access_exception_handler     () __attribute__((interrupt, used, externally_visible));
extern "C" void __rx_undefined_exception_handler  () __attribute__((interrupt, used, externally_visible));
extern "C" void __rx_floating_exception_handler   () __attribute__((interrupt, used, externally_visible));
extern "C" void __rx_nonmaskable_exception_handler() __attribute__((interrupt, used, externally_visible));
extern "C" void __tmr0_ovi_irq                    () __attribute__((interrupt, used, externally_visible));


extern "C" void __vector_unused_irq               () { for(;;) { mcal::cpu::nop(); } }
extern "C" void __rx_priviledged_exception_handler() { for(;;) { mcal::cpu::nop(); } }
extern "C" void __rx_access_exception_handler     () { for(;;) { mcal::cpu::nop(); } }
extern "C" void __rx_undefined_exception_handler  () { for(;;) { mcal::cpu::nop(); } }
extern "C" void __rx_floating_exception_handler   () { for(;;) { mcal::cpu::nop(); } }
extern "C" void __rx_nonmaskable_exception_handler() { for(;;) { mcal::cpu::nop(); } }

struct isr
{
  typedef void(*function_type)();
};

extern "C"
const volatile std::array<isr::function_type, 12U> isr_vector_fixed __attribute__((section(".vectors_fixed")));

extern "C"
const volatile std::array<isr::function_type, 12U> isr_vector_fixed =
{{
  __rx_priviledged_exception_handler,
  __rx_access_exception_handler,
  nullptr,
  __rx_undefined_exception_handler,
  nullptr,
  __rx_floating_exception_handler,
  nullptr,
  nullptr,
  nullptr,
  nullptr,
  __rx_nonmaskable_exception_handler,
  __my_startup
}};

extern "C"
const volatile std::array<isr::function_type, 256U> isr_vector_user __attribute__((section(".vectors_user")));

extern "C"
const volatile std::array<isr::function_type, 256U> isr_vector_user =
{{
  __vector_unused_irq, // - Reserved                             0 0000h -          X X X X X - - -
  __vector_unused_irq, // - Reserved                             1 0004h -          X X X X X - - -
  __vector_unused_irq, // - Reserved                             2 0008h -          X X X X X - - -
  __vector_unused_irq, // - Reserved                             3 000Ch -          X X X X X - - -
  __vector_unused_irq, // - Reserved                             4 0010h -          X X X X X - - -
  __vector_unused_irq, // - Reserved                             5 0014h -          X X X X X - - -
  __vector_unused_irq, // - Reserved                             6 0018h -          X X X X X - - -
  __vector_unused_irq, // - Reserved                             7 001Ch -          X X X X X - - -
  __vector_unused_irq, // - Reserved                             8 0020h -          X X X X X - - -
  __vector_unused_irq, // - Reserved                             9 0024h -          X X X X X - - -
  __vector_unused_irq, // - Reserved                            10 0028h -          X X X X X - - -
  __vector_unused_irq, // - Reserved                            11 002Ch -          X X X X X - - -
  __vector_unused_irq, // - Reserved                            12 0030h -          X X X X X - - -
  __vector_unused_irq, // - Reserved                            13 0034h -          X X X X X - - -
  __vector_unused_irq, // - Reserved                            14 0038h -          X X X X X - - -
  __vector_unused_irq, // - Reserved                            15 003Ch -          X X X X X - - -
  __vector_unused_irq, // BSC BUSERR                            16 0040h Level      0 X X X X IER02.IEN0 IPR000 -
  __vector_unused_irq, // - Reserved                            17 0044h -          X X X X X - - -
  __vector_unused_irq, // - Reserved                            18 0048h -          X X X X X - - -
  __vector_unused_irq, // - Reserved                            19 004Ch -          X X X X X - - -
  __vector_unused_irq, // - Reserved                            20 0050h -          X X X X X - - -
  __vector_unused_irq, // FCU FIFERR                            21 0054h Level      0 X X X X IER02.IEN5 IPR001 -
  __vector_unused_irq, // - Reserved                            22 0058h -          X X X X X - - -
  __vector_unused_irq, // FCU FRDYI                             23 005Ch Edge       X X X X X IER02.IEN7 IPR002 -
  __vector_unused_irq, // - Reserved                            24 0060h -          X X X X X - - -
  __vector_unused_irq, // - Reserved                            25 0064h -          X X X X X - - -
  __vector_unused_irq, // - Reserved                            26 0068h -          X X X X X - - -
  __vector_unused_irq, // ICU SWINT                             27 006Ch Edge       0 0 X X X IER03.IEN3 IPR003 DTCER027
  __vector_unused_irq, // CMT0 CMI0                             28 0070h Edge       0 0 0 X X IER03.IEN4 IPR004 DTCER028
  __vector_unused_irq, // CMT1 CMI1                             29 0074h Edge       0 0 0 X X IER03.IEN5 IPR005 DTCER029
  __vector_unused_irq, // CMT2 CMI2                             30 0078h Edge       0 0 0 X X IER03.IEN6 IPR006 DTCER030
  __vector_unused_irq, // CMT3 CMI3                             31 007Ch Edge       0 0 0 X X IER03.IEN7 IPR007 DTCER031
  __vector_unused_irq, // Ether EINT                            32 0080h Level      0 X X X X IER04.IEN0 IPR032 -
  __vector_unused_irq, // USB0 D0FIFO0                          33 0084h Edge       0 0 0 X X IER04.IEN1 IPR033 DTCER033
  __vector_unused_irq, // D1FIFO0                               34 0088h Edge       0 0 0 X X IER04.IEN2 IPR034 DTCER034
  __vector_unused_irq, // USBI0                                 35 008Ch Edge       0 X X X X IER04.IEN3 IPR035 -
  __vector_unused_irq, // USB1 D0FIFO1                          36 0090h Edge       0 0 0 X X IER04.IEN4 IPR036 DTCER036
  __vector_unused_irq, // D1FIFO1                               37 0094h Edge       0 0 0 X X IER04.IEN5 IPR037 DTCER037
  __vector_unused_irq, // USBI1                                 38 0098h Edge       0 X X X X IER04.IEN6 IPR038 -
  __vector_unused_irq, // RSPI0 SPRI0                           39 009Ch Edge       0 0 0 X X IER04.IEN7 IPR039 DTCER039
  __vector_unused_irq, // SPTI0                                 40 00A0h Edge       0 0 0 X X IER05.IEN0 DTCER040
  __vector_unused_irq, // SPII0                                 41 00A4h Level      0 X X X X IER05.IEN1 -
  __vector_unused_irq, // RSPI1 SPRI1                           42 00A8h Edge       0 0 0 X X IER05.IEN2 IPR042 DTCER042
  __vector_unused_irq, // SPTI1                                 43 00ACh Edge       0 0 0 X X IER05.IEN3 DTCER043
  __vector_unused_irq, // SPII1                                 44 00B0h Level      0 X X X X IER05.IEN4 -
  __vector_unused_irq, // RSPI2 SPRI2                           45 00B4h Edge       0 0 0 X X IER05.IEN5 IPR045 DTCER045
  __vector_unused_irq, // SPTI2                                 46 00B8h Edge       0 0 0 X X IER05.IEN6 DTCER046
  __vector_unused_irq, // SPII2                                 47 00BCh Level      0 X X X X IER05.IEN7 -
  __vector_unused_irq, // CAN0 RXF0                             48 00C0h Edge       0 X X X X IER06.IEN0 IPR048 -
  __vector_unused_irq, // TXF0                                  49 00C4h Edge       0 X X X X IER06.IEN1 -
  __vector_unused_irq, // RXM0                                  50 00C8h Edge       0 X X X X IER06.IEN2 -
  __vector_unused_irq, // TXM0                                  51 00CCh Edge       0 X X X X IER06.IEN3 -
  __vector_unused_irq, // CAN1 RXF1                             52 00D0h Edge       0 X X X X IER06.IEN4 IPR052 -
  __vector_unused_irq, // TXF1                                  53 00D4h Edge       0 X X X X IER06.IEN5 -
  __vector_unused_irq, // RXM1                                  54 00D8h Edge       0 X X X X IER06.IEN6 -
  __vector_unused_irq, // TXM1                                  55 00DCh Edge       0 X X X X IER06.IEN7 -
  __vector_unused_irq, // CAN2 RXF2                             56 00E0h Edge       0 X X X X IER07.IEN0 IPR056 -
  __vector_unused_irq, // TXF2                                  57 00E4h Edge       0 X X X X IER07.IEN1 -
  __vector_unused_irq, // RXM2                                  58 00E8h Edge       0 X X X X IER07.IEN2 -
  __vector_unused_irq, // TXM2                                  59 00ECh Edge       0 X X X X IER07.IEN3 -
  __vector_unused_irq, // - Reserved                            60 00F0h -          X X X X X - - -
  __vector_unused_irq, // - Reserved                            61 00F4h -          X X X X X - - -
  __vector_unused_irq, // RTC CUP                               62 00F8h Edge       0 X X X X IER07.IEN6 IPR062 -
  __vector_unused_irq, // - Reserved                            63 00FCh -          X X X X X - - -
  __vector_unused_irq, // ICU IRQ0                              64 0100h Edge/Level 0 0 0 0 0 IER08.IEN0 IPR064 DTCER064
  __vector_unused_irq, // IRQ1                                  65 0104h Edge/Level 0 0 0 0 0 IER08.IEN1 IPR065 DTCER065
  __vector_unused_irq, // IRQ2                                  66 0108h Edge/Level 0 0 0 0 0 IER08.IEN2 IPR066 DTCER066
  __vector_unused_irq, // IRQ3                                  67 010Ch Edge/Level 0 0 0 0 0 IER08.IEN3 IPR067 DTCER067
  __vector_unused_irq, // IRQ4                                  68 0110h Edge/Level 0 0 X 0 0 IER08.IEN4 IPR068 DTCER068
  __vector_unused_irq, // IRQ5                                  69 0114h Edge/Level 0 0 X 0 0 IER08.IEN5 IPR069 DTCER069
  __vector_unused_irq, // IRQ6                                  70 0118h Edge/Level 0 0 X 0 0 IER08.IEN6 IPR070 DTCER070
  __vector_unused_irq, // IRQ7                                  71 011Ch Edge/Level 0 0 X 0 0 IER08.IEN7 IPR071 DTCER071
  __vector_unused_irq, // IRQ8                                  72 0120h Edge/Level 0 0 X 0 0 IER09.IEN0 IPR072 DTCER072
  __vector_unused_irq, // IRQ9                                  73 0124h Edge/Level 0 0 X 0 0 IER09.IEN1 IPR073 DTCER073
  __vector_unused_irq, // IRQ10                                 74 0128h Edge/Level 0 0 X 0 0 IER09.IEN2 IPR074 DTCER074
  __vector_unused_irq, // IRQ11                                 75 012Ch Edge/Level 0 0 X 0 0 IER09.IEN3 IPR075 DTCER075
  __vector_unused_irq, // IRQ12                                 76 0130h Edge/Level 0 0 X 0 0 IER09.IEN4 IPR076 DTCER076
  __vector_unused_irq, // IRQ13                                 77 0134h Edge/Level 0 0 X 0 0 IER09.IEN5 IPR077 DTCER077
  __vector_unused_irq, // IRQ14                                 78 0138h Edge/Level 0 0 X 0 0 IER09.IEN6 IPR078 DTCER078
  __vector_unused_irq, // IRQ15                                 79 013Ch Edge/Level 0 0 X 0 0 IER09.IEN7 IPR079 DTCER079
  __vector_unused_irq, // - Reserved                            80 0140h -          X X X X X - - -
  __vector_unused_irq, // - Reserved                            81 0144h -          X X X X X - - -
  __vector_unused_irq, // - Reserved                            82 0148h -          X X X X X - - -
  __vector_unused_irq, // - Reserved                            83 014Ch -          X X X X X - - -
  __vector_unused_irq, // - Reserved                            84 0150h -          X X X X X - - -
  __vector_unused_irq, // - Reserved                            85 0154h -          X X X X X - - -
  __vector_unused_irq, // - Reserved                            86 0158h -          X X X X X - - -
  __vector_unused_irq, // - Reserved                            87 015Ch -          X X X X X - - -
  __vector_unused_irq, // - Reserved                            88 0160h -          X X X X X - - -
  __vector_unused_irq, // - Reserved                            89 0164h -          X X X X X - - -
  __vector_unused_irq, // USB USBR0                             90 0168h Level      0 X X 0 0 IER0B.IEN2 IPR090 -
  __vector_unused_irq, // USBR1                                 91 016Ch Level      0 X X 0 0 IER0B.IEN3 IPR091 -
  __vector_unused_irq, // RTC ALM                               92 0170h Edge       0 X X 0 0 IER0B.IEN4 IPR092 -
  __vector_unused_irq, // PRD                                   93 0174h Edge       0 X X 0 0 IER0B.IEN5 IPR093 -
  __vector_unused_irq, // - Reserved                            94 0178h -          X X X X X - - -
  __vector_unused_irq, // - Reserved                            95 017Ch -          X X X X X - - -
  __vector_unused_irq, // - Reserved                            96 0180h -          X X X X X - - -
  __vector_unused_irq, // - Reserved                            97 0184h -          X X X X X - - -
  __vector_unused_irq, // AD0 AD                                98 0188h Edge       0 0 0 X X IER0C.IEN2 IPR098 DTCER098
  __vector_unused_irq, // - Reserved                            99 018Ch -          X X X X X - - -
  __vector_unused_irq, // - Reserved                           100 0190h -          X X X X X - - -
  __vector_unused_irq, // - Reserved                           101 0194h -          X X X X X - - -
  __vector_unused_irq, // S12AD S12ADI0                        102 0198h Edge       0 0 0 X X IER0C.IEN6 IPR102 DTCER102
  __vector_unused_irq, // - Reserved                           103 019Ch -          X X X X X - - -
  __vector_unused_irq, // - Reserved                           104 01A0h -          X X X X X - - -
  __vector_unused_irq, // - Reserved                           105 01A4h -          X X X X X - - -
  __vector_unused_irq, // ICU*2 GROUP0                         106 01A8h Level      0 X X X X IER0D.IEN2 IPR106 -
  __vector_unused_irq, // GROUP1                               107 01ACh Level      0 X X X X IER0D.IEN3 IPR107 -
  __vector_unused_irq, // GROUP2                               108 01B0h Level      0 X X X X IER0D.IEN4 IPR108 -
  __vector_unused_irq, // GROUP3                               109 01B4h Level      0 X X X X IER0D.IEN5 IPR109 -
  __vector_unused_irq, // GROUP4                               110 01B8h Level      0 X X X X IER0D.IEN6 IPR110 -
  __vector_unused_irq, // GROUP5                               111 01BCh Level      0 X X X X IER0D.IEN7 IPR111 -
  __vector_unused_irq, // GROUP6                               112 01C0h Level      0 X X X X IER0E.IEN0 IPR112 -
  __vector_unused_irq, // - Reserved                           113 01C4h -          X X X X X - - -
  __vector_unused_irq, // ICU*2 GROUP12                        114 01C8h Level      0 X X X X IER0E.IEN2 IPR114 -
  __vector_unused_irq, // - Reserved                           115 01CCh -          X X X X X - - -
  __vector_unused_irq, // - Reserved                           116 01D0h -          X X X X X - - -
  __vector_unused_irq, // - Reserved                           117 01D4h -          X X X X X - - -
  __vector_unused_irq, // - Reserved                           118 01D8h -          X X X X X - - -
  __vector_unused_irq, // - Reserved                           119 01DCh -          X X X X X - - -
  __vector_unused_irq, // - Reserved                           120 01E0h -          X X X X X - - -
  __vector_unused_irq, // - Reserved                           121 01E4h -          X X X X X - - -
  __vector_unused_irq, // SCI12 SCIX0                          122 01E8h Level      0 X X X X IER0F.IEN2 IPR122 -
  __vector_unused_irq, // SCIX1                                123 01ECh Level      0 X X X X IER0F.IEN3 -
  __vector_unused_irq, // SCIX2                                124 01F0h Level      0 X X X X IER0F.IEN4 -
  __vector_unused_irq, // SCIX3                                125 01F4h Level      0 X X X X IER0F.IEN5 -
  __vector_unused_irq, // TPU0 TGI0A                           126 01F8h Edge       0 0 0 X X IER0F.IEN6 IPR126 DTCER126
  __vector_unused_irq, // TGI0B                                127 01FCh Edge       0 0 X X X IER0F.IEN7 DTCER127
  __vector_unused_irq, // TGI0C                                128 0200h Edge       0 0 X X X IER10.IEN0 DTCER128
  __vector_unused_irq, // TGI0D                                129 0204h Edge       0 0 X X X IER10.IEN1 DTCER129
  __vector_unused_irq, // TPU1 TGI1A                           130 0208h Edge       0 0 0 X X IER10.IEN2 IPR130 DTCER130
  __vector_unused_irq, // TGI1B                                131 020Ch Edge       0 0 X X X IER10.IEN3 DTCER131
  __vector_unused_irq, // TPU2 TGI2A                           132 0210h Edge       0 0 0 X X IER10.IEN4 IPR132 DTCER132
  __vector_unused_irq, // TGI2B                                133 0214h Edge       0 0 X X X IER10.IEN5 DTCER133
  __vector_unused_irq, // TPU3 TGI3A                           134 0218h Edge       0 0 0 X X IER10.IEN6 IPR134 DTCER134
  __vector_unused_irq, // TGI3B                                135 021Ch Edge       0 0 X X X IER10.IEN7 DTCER135
  __vector_unused_irq, // TGI3C                                136 0220h Edge       0 0 X X X IER11.IEN0 DTCER136
  __vector_unused_irq, // TGI3D                                137 0224h Edge       0 0 X X X IER11.IEN1 DTCER137
  __vector_unused_irq, // TPU4 TGI4A                           138 0228h Edge       0 0 0 X X IER11.IEN2 IPR138 DTCER138
  __vector_unused_irq, // TGI4B                                139 022Ch Edge       0 0 X X X IER11.IEN3 DTCER139
  __vector_unused_irq, // TPU5 TGI5A                           140 0230h Edge       0 0 0 X X IER11.IEN4 IPR140 DTCER140
  __vector_unused_irq, // TGI5B                                141 0234h Edge       0 0 X X X IER11.IEN5 DTCER141 
  __vector_unused_irq, // TPU6/MTU0 TGI6A(TPU6)/TGIA0(MTU0)    142 0238h Edge       0 0 0 X X IER11.IEN6 IPR142 DTCER142
  __vector_unused_irq, // TGI6B(TPU6)/TGIB0(MTU0)              143 023Ch Edge       0 0 X X X IER11.IEN7 DTCER143
  __vector_unused_irq, // TGI6C(TPU6)/TGIC0(MTU0)              144 0240h Edge       0 0 X X X IER12.IEN0 DTCER144
  __vector_unused_irq, // TGI6D(TPU6)/TGID0(MTU0)              145 0244h Edge       0 0 X X X IER12.IEN1 DTCER145
  __vector_unused_irq, // TGIE0(MTU0)                          146 0248h Edge       0 X X X X IER12.IEN2 IPR146 -
  __vector_unused_irq, // TGIF0(MTU0)                          147 024Ch Edge       0 X X X X IER12.IEN3 -
  __vector_unused_irq, // TPU7/MTU1 TGI7A(TPU7)/TGIA1(MTU1)    148 0250h Edge       0 0 0 X X IER12.IEN4 IPR148 DTCER148
  __vector_unused_irq, // TGI7B(TPU7)/TGIB1(MTU1)              149 0254h Edge       0 0 X X X IER12.IEN5 DTCER149
  __vector_unused_irq, // TPU8/MTU2 TGI8A(TPU8)/TGIA2(MTU2)    150 0258h Edge       0 0 0 X X IER12.IEN6 IPR150 DTCER150
  __vector_unused_irq, // TGI8B(TPU8)/TGIB2(MTU2)              151 025Ch Edge       0 0 X X X IER12.IEN7 DTCER151
  __vector_unused_irq, // TPU9/MTU3 TGI9A(TPU9)/TGIA3(MTU3)    152 0260h Edge       0 0 0 X X IER13.IEN0 IPR152 DTCER152
  __vector_unused_irq, // TGI9B(TPU9)/TGIB3(MTU3)              153 0264h Edge       0 0 X X X IER13.IEN1 DTCER153
  __vector_unused_irq, // TGI9C(TPU9)/TGIC3(MTU3)              154 0268h Edge       0 0 X X X IER13.IEN2 DTCER154
  __vector_unused_irq, // TGI9D(TPU9)/TGID3(MTU3)              155 026Ch Edge       0 0 X X X IER13.IEN3 DTCER155
  __vector_unused_irq, // TPU10/MTU4 TGI10A(TPU10)/TGIA4(MTU4) 156 0270h Edge       0 0 0 X X IER13.IEN4 IPR156 DTCER156
  __vector_unused_irq, // TGI10B(TPU10)/TGIB4(MTU4)            157 0274h Edge       0 0 X X X IER13.IEN5 DTCER157
  __vector_unused_irq, // TGIC4(MTU4)                          158 0278h Edge       0 0 X X X IER13.IEN6 DTCER158
  __vector_unused_irq, // TGID4(MTU4)                          159 027Ch Edge       0 0 X X X IER13.IEN7 DTCER159
  __vector_unused_irq, // TCIV4(MTU4)                          160 0280h Edge       0 0 X X X IER14.IEN0 IPR160 DTCER160
  __vector_unused_irq, // TPU11/MTU5 TGIU5(MTU5)               161 0284h Edge       0 0 X X X IER14.IEN1 IPR161 DTCER161
  __vector_unused_irq, // TGIV5(MTU5)                          162 0288h Edge       0 0 X X X IER14.IEN2 DTCER162
  __vector_unused_irq, // TGIW5(MTU5)                          163 028Ch Edge       0 0 X X X IER14.IEN3 DTCER163
  __vector_unused_irq, // TGI11A(TPU11)                        164 0290h Edge       0 0 0 X X IER14.IEN4 IPR164 DTCER164
  __vector_unused_irq, // TGI11B(TPU11)                        165 0294h Edge       0 0 X X X IER14.IEN5 DTCER165
  __vector_unused_irq, // POE OEI1                             166 0298h Level      0 X X X X IER14.IEN6 IPR166 -
  __vector_unused_irq, // OEI2                                 167 029Ch Level      0 X X X X IER14.IEN7 -
  __vector_unused_irq, // - Reserved                           168 02A0h -          X X X X X - - -
  __vector_unused_irq, // - Reserved                           169 02A4h -          X X X X X - - -
  __vector_unused_irq, // TMR0 CMIA0                           170 02A8h Edge       0 0 X X 0*3 IER15.IEN2 IPR170 DTCER170
  __vector_unused_irq, // CMIB0                                171 02ACh Edge       0 0 X X 0*3 IER15.IEN3 DTCER171
  __tmr0_ovi_irq,      // OVI0                                 172 02B0h Edge       0 X X X 0*3 IER15.IEN4 -
  __vector_unused_irq, // TMR1 CMIA1                           173 02B4h Edge       0 0 X X 0*3 IER15.IEN5 IPR173 DTCER173
  __vector_unused_irq, // CMIB1                                174 02B8h Edge       0 0 X X 0*3 IER15.IEN6 DTCER174
  __vector_unused_irq, // OVI1                                 175 02BCh Edge       0 X X X 0*3 IER15.IEN7 -
  __vector_unused_irq, // TMR2 CMIA2                           176 02C0h Edge       0 0 X X 0*3 IER16.IEN0 IPR176 DTCER176
  __vector_unused_irq, // CMIB2                                177 02C4h Edge       0 0 X X 0*3 IER16.IEN1 DTCER177
  __vector_unused_irq, // OVI2                                 178 02C8h Edge       0 X X X 0*3 IER16.IEN2 -
  __vector_unused_irq, // TMR3 CMIA3                           179 02CCh Edge       0 0 X X 0*3 IER16.IEN3 IPR179 DTCER179
  __vector_unused_irq, // CMIB3                                180 02D0h Edge       0 0 X X 0*3 IER16.IEN4 DTCER180
  __vector_unused_irq, // OVI3                                 181 02D4h Edge       0 X X X 0*3 IER16.IEN5 -
  __vector_unused_irq, // RIIC0 EEI0                           182 02D8h Level      0 X X X X IER16.IEN6 IPR182 -
  __vector_unused_irq, // RXI0                                 183 02DCh Edge       0 0 0 X X IER16.IEN7 IPR183 DTCER183
  __vector_unused_irq, // TXI0                                 184 02E0h Edge       0 0 0 X X IER17.IEN0 IPR184 DTCER184
  __vector_unused_irq, // TEI0                                 185 02E4h Level      0 X X X X IER17.IEN1 IPR185 -
  __vector_unused_irq, // RIIC1 EEI1                           186 02E8h Level      0 X X X X IER17.IEN2 IPR186 -
  __vector_unused_irq, // RXI1                                 187 02ECh Edge       0 0 0 X X IER17.IEN3 IPR187 DTCER187
  __vector_unused_irq, // TXI1                                 188 02F0h Edge       0 0 0 X X IER17.IEN4 IPR188 DTCER188
  __vector_unused_irq, // TEI1                                 189 02F4h Level      0 X X X X IER17.IEN5 IPR189 -
  __vector_unused_irq, // RIIC2 EEI2                           190 02F8h Level      0 X X X X IER17.IEN6 IPR190 -
  __vector_unused_irq, // RXI2                                 191 02FCh Edge       0 0 0 X X IER17.IEN7 IPR191 DTCER191
  __vector_unused_irq, // TXI2                                 192 0300h Edge       0 0 0 X X IER18.IEN0 IPR192 DTCER192
  __vector_unused_irq, // TEI2                                 193 0304h Level      0 X X X X IER18.IEN1 IPR193 -
  __vector_unused_irq, // RIIC3 EEI3                           194 0308h Level      0 X X X X IER18.IEN2 IPR194 -
  __vector_unused_irq, // RXI3                                 195 030Ch Edge       0 0 0 X X IER18.IEN3 IPR195 DTCER195
  __vector_unused_irq, // TXI3                                 196 0310h Edge       0 0 0 X X IER18.IEN4 IPR196 DTCER196
  __vector_unused_irq, // TEI3                                 197 0314h Level      0 X X X X IER18.IEN5 IPR197 -
  __vector_unused_irq, // DMAC DMAC0I                          198 0318h Edge       0 0 X X X IER18.IEN6 IPR198 DTCER198
  __vector_unused_irq, // DMAC1I                               199 031Ch Edge       0 0 X X X IER18.IEN7 IPR199 DTCER199
  __vector_unused_irq, // DMAC2I                               200 0320h Edge       0 0 X X X IER19.IEN0 IPR200 DTCER200
  __vector_unused_irq, // DMAC3I                               201 0324h Edge       0 0 X X X IER19.IEN1 IPR201 DTCER201
  __vector_unused_irq, // EXDMAC EXDMAC0I                      202 0328h Edge       0 0 X X X IER19.IEN2 IPR202 DTCER202
  __vector_unused_irq, // EXDMAC1I                             203 032Ch Edge       0 0 X X X IER19.IEN3 IPR203 DTCER203
  __vector_unused_irq, // - Reserved                           204 0330h -          X X X X X - - -
  __vector_unused_irq, // - Reserved                           205 0334h -          X X X X X - - -
  __vector_unused_irq, // DEU DEU0                             206 0338h Edge       0 0 0 X X IER19.IEN6 IPR206 DCTER206
  __vector_unused_irq, // DEU1                                 207 033Ch Edge       0 0 0 X X IER19.IEN7 IPR207 DCTER207
  __vector_unused_irq, // PDC PCDFI                            208 0340h Edge       0 0 0 X X IER1A.IEN0 IPR208 DCTER208
  __vector_unused_irq, // PCFEI                                209 0344h Level      0 X X X X IER1A.IEN1 IPR209 -
  __vector_unused_irq, // PCERI                                210 0348h Level      0 X X X X IER1A.IEN2 IPR210 -
  __vector_unused_irq, // - Reserved                           211 034Ch -          X X X X X - - -
  __vector_unused_irq, // - Reserved                           212 0350h -          X X X X X - - -
  __vector_unused_irq, // - Reserved                           213 0354h -          X X X X X - - -
  __vector_unused_irq, // SCI0 RXI0                            214 0358h Edge       0 0 0 X X IER1A.IEN6 IPR214 DTCER214
  __vector_unused_irq, // TXI0                                 215 035Ch Edge       0 0 0 X X IER1A.IEN7 DTCER215
  __vector_unused_irq, // TEI0                                 216 0360h Level      0 X X X X IER1B.IEN0 -
  __vector_unused_irq, // SCI1 RXI1                            217 0364h Edge       0 0 0 X X IER1B.IEN1 IPR217 DTCER217
  __vector_unused_irq, // TXI1                                 218 0368h Edge       0 0 0 X X IER1B.IEN2 DTCER218
  __vector_unused_irq, // TEI1                                 219 036Ch Level      0 X X X X IER1B.IEN3 -
  __vector_unused_irq, // SCI2 RXI2                            220 0370h Edge       0 0 0 X X IER1B.IEN4 IPR220 DTCER220
  __vector_unused_irq, // TXI2                                 221 0374h Edge       0 0 0 X X IER1B.IEN5 DTCER221
  __vector_unused_irq, // TEI2                                 222 0378h Level      0 X X X X IER1B.IEN6 -
  __vector_unused_irq, // SCI3 RXI3                            223 037Ch Edge       0 0 0 X X IER1B.IEN7 IPR223 DTCER223
  __vector_unused_irq, // TXI3                                 224 0380h Edge       0 0 0 X X IER1C.IEN0 DTCER224
  __vector_unused_irq, // TEI3                                 225 0384h Level      0 X X X X IER1C.IEN1 -
  __vector_unused_irq, // SCI4 RXI4                            226 0388h Edge       0 0 0 X X IER1C.IEN2 IPR226 DTCER226
  __vector_unused_irq, // TXI4                                 227 038Ch Edge       0 0 0 X X IER1C.IEN3 DTCER227
  __vector_unused_irq, // TEI4                                 228 0390h Level      0 X X X X IER1C.IEN4 -
  __vector_unused_irq, // SCI5 RXI5                            229 0394h Edge       0 0 0 X X IER1C.IEN5 IPR229 DTCER229
  __vector_unused_irq, // TXI5                                 230 0398h Edge       0 0 0 X X IER1C.IEN6 DTCER230
  __vector_unused_irq, // TEI5                                 231 039Ch Level      0 X X X X IER1C.IEN7 -
  __vector_unused_irq, // SCI6 RXI6                            232 03A0h Edge       0 0 0 X X IER1D.IEN0 IPR232 DTCER232
  __vector_unused_irq, // TXI6                                 233 03A4h Edge       0 0 0 X X IER1D.IEN1 DTCER233
  __vector_unused_irq, // TEI6                                 234 03A8h Level      0 X X X X IER1D.IEN2 -
  __vector_unused_irq, // SCI7 RXI7                            235 03ACh Edge       0 0 0 X X IER1D.IEN3 IPR235 DTCER235
  __vector_unused_irq, // TXI7                                 236 03B0h Edge       0 0 0 X X IER1D.IEN4 DTCER236
  __vector_unused_irq, // TEI7                                 237 03B4h Level      0 X X X X IER1D.IEN5 -
  __vector_unused_irq, // SCI8 RXI8                            238 03B8h Edge       0 0 0 X X IER1D.IEN6 IPR238 DTCER238
  __vector_unused_irq, // TXI8                                 239 03BCh Edge       0 0 0 X X IER1D.IEN7 DTCER239
  __vector_unused_irq, // TEI8                                 240 03C0h Level      0 X X X X IER1E.IEN0 -
  __vector_unused_irq, // SCI9 RXI9                            241 03C4h Edge       0 0 0 X X IER1E.IEN1 IPR241 DTCER241
  __vector_unused_irq, // TXI9                                 242 03C8h Edge       0 0 0 X X IER1E.IEN2 DTCER242
  __vector_unused_irq, // TEI9                                 243 03CCh Level      0 X X X X IER1E.IEN3 -
  __vector_unused_irq, // SCI10 RXI10                          244 03D0h Edge       0 0 0 X X IER1E.IEN4 IPR244 DTCER244
  __vector_unused_irq, // TXI10                                245 03D4h Edge       0 0 0 X X IER1E.IEN5 DTCER245
  __vector_unused_irq, // TEI10                                246 03D8h Level      0 X X X X IER1E.IEN6 -
  __vector_unused_irq, // SCI11 RXI11                          247 03DCh Edge       0 0 0 X X IER1E.IEN7 IPR247 DTCER247
  __vector_unused_irq, // TXI11                                248 03E0h Edge       0 0 0 X X IER1F.IEN0 DTCER248
  __vector_unused_irq, // TEI11                                249 03E4h Level      0 X X X X IER1F.IEN1 -
  __vector_unused_irq, // SCI12 RXI12                          250 03E8h Edge       0 0 0 X X IER1F.IEN2 IPR250 DTCER250
  __vector_unused_irq, // TXI12                                251 03ECh Edge       0 0 0 X X IER1F.IEN3 DTCER251
  __vector_unused_irq, // TEI12                                252 03F0h Level      0 X X X X IER1F.IEN4 -
  __vector_unused_irq, // IEB IEBINT                           253 03F4h Level      0 X X X X IER1F.IEN5 IPR253 -
  __vector_unused_irq, // - Reserved                           254 03F8h -          X X X X X - - -
  __vector_unused_irq  // - Reserved                           255 03FCh -          X X X X X - - -
}};
