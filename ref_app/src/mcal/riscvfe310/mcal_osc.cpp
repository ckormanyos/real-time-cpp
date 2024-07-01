///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2022.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <cstdint>

#include <mcal_cpu.h>
#include <mcal_osc.h>
#include <mcal_reg.h>

void mcal::osc::init(const config_type*)
{
  // Wait for HFXOSC to be become ready.
  //while(!PRCI->hfxosccfg.bit.ready);
  while(!mcal::reg::reg_access_static<std::uint32_t, std::uint32_t, mcal::reg::prci_hfxosccfg, static_cast<std::uint32_t>(UINT8_C(31))>::bit_get())
  {
    mcal::cpu::nop();
  }

  // Select pllref clock (HFXOSC).
  //PRCI->pllcfg.bit.refsel = 1;
  mcal::reg::reg_access_static<std::uint32_t, std::uint32_t, mcal::reg::prci_pllcfg, static_cast<std::uint32_t>(UINT8_C(17))>::bit_set();

  // Divide pllref (HFXOSC) by 2 ==> refr = 8 MHz.
  //PRCI->pllcfg.bit.pllr = 1;
  mcal::reg::reg_access_static<std::uint32_t, std::uint32_t, mcal::reg::prci_pllcfg, static_cast<std::uint32_t>(UINT8_C(1))>::template reg_msk<static_cast<std::uint32_t>(UINT8_C(7))>();

  // multiply refr by 96 ==> vco = 768 MHz.
  //PRCI->pllcfg.bit.pllf = 47;
  mcal::reg::reg_access_static<std::uint32_t, std::uint32_t, mcal::reg::prci_pllcfg, static_cast<std::uint32_t>(47ULL << 4U)>::template reg_msk<static_cast<std::uint32_t>(63ULL << 4U)>();

  // Divide vco by 4 ==> pllout = 192 MHz.
  //PRCI->pllcfg.bit.pllq = 2;
  mcal::reg::reg_access_static<std::uint32_t, std::uint32_t, mcal::reg::prci_pllcfg, static_cast<std::uint32_t>(2ULL << 10U)>::template reg_msk<static_cast<std::uint32_t>(3ULL << 10U)>();

  // Bypass final pllout divider.
  //PRCI->plloutdiv.bit.divby1 = 1;
  mcal::reg::reg_access_static<std::uint32_t, std::uint32_t, mcal::reg::prci_plloutdiv, static_cast<std::uint32_t>(UINT8_C(8))>::bit_set();

  // Drive the final hfclk with the PLL output.
  //PRCI->pllcfg.bit.sel = 1;
  mcal::reg::reg_access_static<std::uint32_t, std::uint32_t, mcal::reg::prci_pllcfg, static_cast<std::uint32_t>(UINT8_C(16))>::bit_set();

  // Disable pll bypass.
  //PRCI->pllcfg.bit.bypass = 0;
  mcal::reg::reg_access_static<std::uint32_t, std::uint32_t, mcal::reg::prci_pllcfg, static_cast<std::uint32_t>(UINT8_C(18))>::bit_clr();

  // Wait for the pll to lock.
  //while(!PRCI->pllcfg.bit.lock);
  while(!mcal::reg::reg_access_static<std::uint32_t, std::uint32_t, mcal::reg::prci_pllcfg, static_cast<std::uint32_t>(UINT8_C(31))>::bit_get())
  {
    mcal::cpu::nop();
  }
}
