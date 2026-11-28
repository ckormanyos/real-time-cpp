///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2026.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <mcal_cpu.h>
#include <mcal_osc.h>

#include <cstdint>

auto mcal::osc::init(const config_type*) -> void
{
  constexpr std::uintptr_t PLLCTL   { 0xFFFFF82CUL };
  constexpr std::uintptr_t PLLLOCKR { 0xFFFFF824UL };
  constexpr std::uintptr_t PCC      { 0xFFFFF828UL };
  constexpr std::uintptr_t PRCMD    { 0xFFFFF1FCUL };

  /* enable the PLL (20MHz) */
  *(volatile uint8_t*) PRCMD  = 0;
  *(volatile uint8_t*) PCC    = 0;
  *(volatile uint8_t*) PLLCTL = 3;

  while(*(volatile uint8_t*) PLLLOCKR != std::uint8_t { UINT8_C(0) })
  {
    mcal::cpu::nop();
  }
}

extern "C"
auto pll_init(void) -> void;

extern "C"
auto pll_init(void) -> void
{
  mcal::osc::init(nullptr);
}
