///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2026.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <mcal_osc.h>

#include <cstdint>

#define PLLCTL   (*(volatile uint8_t*)0xFFFFF82Cul)
#define PLLLOCKR (*(volatile uint8_t*)0xFFFFF824ul)
#define PCC      (*(volatile uint8_t*)0xFFFFF828ul)
#define PRCMD    (*(volatile uint8_t*)0xFFFFF1FCul)

auto mcal::osc::init(const config_type*) -> void
{
  /* enable the PLL (20MHz) */
  PRCMD  = 0;
  PCC    = 0;
  PLLCTL = 3;
  while(PLLLOCKR);
}

extern "C"
auto pll_init(void) -> void;

extern "C"
auto pll_init(void) -> void
{
  mcal::osc::init(nullptr);
}
