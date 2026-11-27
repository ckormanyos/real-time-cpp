///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2026.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <mcal_wdg.h>

#include <cstdint>

#define WDTM2 (*(volatile uint8_t*)(0xFFFFF6D0ul))
#define WDTE  (*(volatile uint8_t*)(0xFFFFF6D1ul))
#define RCM   (*(volatile uint8_t*)(0xFFFFF80Cul))

auto mcal::wdg::init(const config_type*) -> void
{
  WDTE  = 0xAC;
  RCM   = 1;
  WDTM2 = 0;
}

auto mcal::wdg::secure::trigger() -> void
{
}

extern "C"
auto wdg_init(void) -> void;

extern "C"
auto wdg_init(void) -> void
{
  mcal::wdg::init(nullptr);
}
