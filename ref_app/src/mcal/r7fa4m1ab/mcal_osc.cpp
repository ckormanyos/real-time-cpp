///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2026.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <mcal_osc.h>

#include <R7FA4M1AB.h>

auto mcal::osc::init(const config_type*) -> void
{
  constexpr uint32_t HOCOCR2 { UINT32_C(0x4001E037) };

  /* disable register write protection for clock module */
  SYSTEM->PRCR.reg = (uint16_t)((0xA5 << 8) | 1);

  /*set system clock division to 1*/
  SYSTEM->SCKDIVCR.reg = 0;

  /* set the HOCO clock frequency to 48 MHz */
  *((volatile uint8_t*)HOCOCR2) = (4 << 3);

  /* switch sysclk to HOCO clock (48 MHz) */
  SYSTEM->OPCCR.bit.OPCM = 0;
  while(SYSTEM->OPCCR.bit.OPCMTSF);

  /* switch power operation mode to high-speed mode */
  SYSTEM->HOCOCR.bit.HCSTP = 0;
  while(!SYSTEM->OSCSF.bit.HOCOSF);

  /* enable memory wait cycle */
  SYSTEM->MEMWAIT.bit.MEMWAIT = 1;

  /* switch sysclk to HOCO clock (48 MHz) */
  SYSTEM->SCKSCR.reg = 0;
}
