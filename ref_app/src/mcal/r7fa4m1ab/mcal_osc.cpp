///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2026.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <mcal_cpu.h>
#include <mcal_osc.h>
#include <mcal_reg.h>

#include <cstddef>

auto mcal::osc::init(const config_type*) -> void
{
  // Disable register write protection for clock module.
  // SYSTEM->PRCR.reg = (uint16_t)((0xA5 << 8) | 1);
  mcal::reg::reg_access_static<std::uint32_t, std::uint16_t, mcal::reg::system_prcr, std::uint16_t { ((0xA5UL << 8U) | 1UL) }>::reg_set();

  // Set system clock division to 1.
  // SYSTEM->SCKDIVCR.reg = 0;
  mcal::reg::reg_access_static<std::uint32_t, std::uint32_t, mcal::reg::system_sckdivcr, UINT32_C(0)>::reg_set();

  // set the HOCO clock frequency to 48 MHz.
  // constexpr uint32_t HOCOCR2 { UINT32_C(0x4001E037) };
  // *((volatile uint8_t*)HOCOCR2) = (4 << 3);
  mcal::reg::reg_access_static<std::uint32_t, std::uint8_t, mcal::reg::unknown_hococr2, static_cast<std::uint8_t>(4UL << 3U)>::reg_set();

  // Switch sysclk to HOCO clock (48 MHz).
  // SYSTEM->OPCCR.bit.OPCM = 0;
  // while(SYSTEM->OPCCR.bit.OPCMTSF);

  mcal::reg::reg_access_static<std::uint32_t, std::uint8_t, mcal::reg::system_opccr, UINT8_C(0)>::template reg_msk<UINT8_C(3)>();

  while(mcal::reg::reg_access_static<std::uint32_t, std::uint8_t, mcal::reg::system_opccr, UINT8_C(4)>::bit_get())
  {
    mcal::cpu::nop();
  }

  // Switch power operation mode to high-speed mode.
  // SYSTEM->HOCOCR.bit.HCSTP = 0;
  // while(!SYSTEM->OSCSF.bit.HOCOSF);

  mcal::reg::reg_access_static<std::uint32_t, std::uint8_t, mcal::reg::system_hococr, UINT8_C(0)>::bit_clr();

  while(!mcal::reg::reg_access_static<std::uint32_t, std::uint8_t, mcal::reg::system_oscsf, UINT8_C(0)>::bit_get())
  {
    mcal::cpu::nop();
  }

  // Enable memory wait cycle.
  // SYSTEM->MEMWAIT.bit.MEMWAIT = 1;
  mcal::reg::reg_access_static<std::uint32_t, std::uint8_t, mcal::reg::system_memwait, UINT8_C(0)>::bit_set();

  // Switch sysclk to HOCO clock (48 MHz).
  // SYSTEM->SCKSCR.reg = 0;
  mcal::reg::reg_access_static<std::uint32_t, std::uint8_t, mcal::reg::system_sckscr, UINT8_C(0)>::reg_set();
}
