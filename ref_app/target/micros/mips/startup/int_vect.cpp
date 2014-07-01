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
const volatile std::array<std::uint8_t, 16U> option_bytes __attribute__ ((section(".opt")));

extern "C"
const volatile std::array<std::uint8_t, 16U> option_bytes =
{
  0xFF, 0xFF, 0xFF, 0xFF,
  0xFF, 0xFF, 0xFF, 0xFF,
  0xFF, 0xFF, 0xFF, 0xFF,
  0xFF, 0xFF, 0xFF, 0xFF
};

extern "C" void __my_startup();

extern "C" void __vector_unused_irq               (); // __attribute__((interrupt, used, externally_visible));


extern "C" void __vector_unused_irq               () { for(;;) { mcal::cpu::nop(); } }

struct isr
{
  typedef void(*function_type)();
};

extern "C"
const volatile std::array<isr::function_type, 4U> isr_vector_user __attribute__ ((section(".vectors_user")));

extern "C"
const volatile std::array<isr::function_type, 4U> isr_vector_user =
{{
  __vector_unused_irq, // - Reserved                             0 0000h
  __vector_unused_irq, // - Reserved                             1 0004h
  __vector_unused_irq, // - Reserved                             2 0008h
  __vector_unused_irq, // - Reserved                             3 000Ch
}};
