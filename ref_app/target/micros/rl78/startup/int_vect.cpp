/////////////////////////////////////////////////////// 
//  Copyright 2013 Stephan Hage.
//  Copyright 2013 Christopher Kormanyos.
//  Distributed under the Boost 
//  Software License, Version 1.0. 
//  (See accompanying file LICENSE_1_0.txt 
//  or copy at http://www.boost.org/LICENSE_1_0.txt ) 
//

#include <cstdint>
#include <mcal_cpu.h>

extern "C" void __my_startup       ();
extern "C" void __inttm02_vect     () __attribute__((interrupt, used, externally_visible));
extern "C" void __vector_unused_irq() __attribute__((interrupt, used, externally_visible));

extern "C" void __vector_unused_irq() { for(;;) { mcal::cpu::nop(); } }

struct isr
{
  typedef void(*function_type)();
};

extern "C"
const volatile isr::function_type isr_vector[64U] __attribute__((section(".ivec")));

extern "C"
const volatile isr::function_type isr_vector[64U] __attribute__((section(".ivec"))) =
{
  __my_startup,                    // 0x0000 __my_startup
  __vector_unused_irq,             // 0x0002 intdbg_vect
  __vector_unused_irq,             // 0x0004 intwdti_vect
  __vector_unused_irq,             // 0x0006 intlvi_vect
  __vector_unused_irq,             // 0x0008 intp0_vect
  __vector_unused_irq,             // 0x000A intp1_vect
  __vector_unused_irq,             // 0x000C intp2_vect
  __vector_unused_irq,             // 0x000E intp3_vect
  __vector_unused_irq,             // 0x0010 intp4_vect
  __vector_unused_irq,             // 0x0012 intp5_vect
  __vector_unused_irq,             // 0x0014 intcsi20_vect / intiic20_vect / intst2_vect
  __vector_unused_irq,             // 0x0016 intcsi21_vect / intiic21_vect / intsr2_vect
  __vector_unused_irq,             // 0x0018 intsre2_vect
  __vector_unused_irq,             // 0x001A intdma0_vect
  __vector_unused_irq,             // 0x001C intdma1_vect
  __vector_unused_irq,             // 0x001E intcsi00_vect / intiic00_vect / intst0_vect
  __vector_unused_irq,             // 0x0020 intcsi01_vect / intiic01_vect / intsr0_vect
  __vector_unused_irq,             // 0x0022 intsre0_vect  / inttm01h_vect
  __vector_unused_irq,             // 0x0024 intst1_vect   / intcsi10_vect / intiic10_vect
  __vector_unused_irq,             // 0x0026 intcsi11_vect / intiic11_vect / intsr1_vect
  __vector_unused_irq,             // 0x0028 intsre1_vect  / inttm03h_vect
  __vector_unused_irq,             // 0x002A intiica0_vect
  __vector_unused_irq,             // 0x002C inttm00_vect
  __vector_unused_irq,             // 0x002E inttm01_vect
  __inttm02_vect,                  // 0x0030 inttm02_vec
  __vector_unused_irq,             // 0x0032 inttm03_vect
  __vector_unused_irq,             // 0x0034 intad_vect
  __vector_unused_irq,             // 0x0036 intrtc_vect
  __vector_unused_irq,             // 0x0038 intit_vect
  __vector_unused_irq,             // 0x003A intkr_vect
  __vector_unused_irq,             // 0x003C intcsis0_vect / intsts0_vect
  __vector_unused_irq,             // 0x003E intsrs0_vect / intcsis1_vect
  __vector_unused_irq,             // 0x0040 intwutm_vect
  __vector_unused_irq,             // 0x0042 inttm04_vect
  __vector_unused_irq,             // 0x0044 inttm05_vect
  __vector_unused_irq,             // 0x0046 inttm06_vect
  __vector_unused_irq,             // 0x0048 inttm07_vect
  __vector_unused_irq,             // 0x004A intp6_vect
  __vector_unused_irq,             // 0x004C intlt_vect / intp7_vect
  __vector_unused_irq,             // 0x004E intlr_vect / intp8_vect
  __vector_unused_irq,             // 0x0050 intls_vect / intp9_vect
  __vector_unused_irq,             // 0x0052 intsreS0_vect / intp10_vect
  __vector_unused_irq,             // 0x0054 intp11_vect
  nullptr,                         // 0x0056 nullptr
  nullptr,                         // 0x0058 nullptr
  nullptr,                         // 0x005A nullptr
  nullptr,                         // 0x005C nullptr
  __vector_unused_irq,             // 0x005E intmd_vect,
  nullptr,                         // 0x0060 nullptr,
  __vector_unused_irq,             // 0x0062 intfl_vect,
  nullptr,                         // 0x0064 nullptr,
  nullptr,                         // 0x0066 nullptr,
  nullptr,                         // 0x0068 nullptr,
  nullptr,                         // 0x006A nullptr,
  nullptr,                         // 0x006C nullptr,
  nullptr,                         // 0x006E nullptr,
  nullptr,                         // 0x0070 nullptr,
  nullptr,                         // 0x0072 nullptr,
  nullptr,                         // 0x0074 nullptr,
  nullptr,                         // 0x0076 nullptr,
  nullptr,                         // 0x0078 nullptr,
  nullptr,                         // 0x007A nullptr,
  nullptr,                         // 0x007C nullptr,
  __vector_unused_irq              // 0x007E brk_i_vect
};
