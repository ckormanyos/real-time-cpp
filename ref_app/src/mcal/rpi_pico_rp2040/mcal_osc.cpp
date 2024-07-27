///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2011 - 2024.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <mcal_cpu.h>
#include <mcal_osc.h>
#include <mcal_reg.h>

void mcal::osc::init(const config_type*)
{
  // Initialize the clock XOSC.

  // XOSC->STARTUP.bit.X4 = 1U;
  mcal::reg::reg_access_static<std::uint32_t,
                               std::uint32_t,
                               mcal::reg::xosc_startup,
                               UINT32_C(20)>::bit_set();

  // XOSC->STARTUP.bit.DELAY = 47U;
  mcal::reg::reg_access_static<std::uint32_t,
                               std::uint32_t,
                               mcal::reg::xosc_startup,
                               UINT32_C(47)>::template reg_msk<UINT32_C(0x1FFF) << 0U>();

  // XOSC->CTRL.bit.FREQ_RANGE = XOSC_CTRL_FREQ_RANGE_1_15MHZ;
  mcal::reg::reg_access_static<std::uint32_t,
                               std::uint32_t,
                               mcal::reg::xosc_ctrl,
                               UINT32_C(2720)>::template reg_msk<UINT32_C(0x0FFF) << 0U>();

  // XOSC->CTRL.bit.ENABLE     = XOSC_CTRL_ENABLE_ENABLE;
  mcal::reg::reg_access_static<std::uint32_t,
                               std::uint32_t,
                               mcal::reg::xosc_ctrl,
                               UINT32_C(4011) << 12U>::template reg_msk<UINT32_C(0x0FFF) << 12U>();

  // while(XOSC->STATUS.bit.STABLE != 1U);
  while(!mcal::reg::reg_access_static<std::uint32_t,
                                      std::uint32_t,
                                      mcal::reg::xosc_status,
                                      UINT32_C(31)>::bit_get()) { mcal::cpu::nop(); }

  // Release the reset of PLL_SYS
  // RESETS->RESET.bit.pll_sys = 0U;
  mcal::reg::reg_access_static<std::uint32_t,
                               std::uint32_t,
                               mcal::reg::resets_reset,
                               UINT32_C(12)>::bit_clr();

  // while(RESETS->RESET_DONE.bit.pll_sys != 1);
  while(!mcal::reg::reg_access_static<std::uint32_t,
                                      std::uint32_t,
                                      mcal::reg::resets_reset_done,
                                      UINT32_C(12)>::bit_get()) { mcal::cpu::nop(); }

  // Configure the PLL_SYS.
  // PLL_SYS->CS.bit.REFDIV = 1U;
  mcal::reg::reg_access_static<std::uint32_t,
                               std::uint32_t,
                               mcal::reg::pll_sys_cs,
                               UINT32_C(1)>::template reg_msk<UINT32_C(0x3F) << 0U>();

  // PLL_SYS->FBDIV_INT.bit.FBDIV_INT = 133U;
  mcal::reg::reg_access_static<std::uint32_t,
                               std::uint32_t,
                               mcal::reg::pll_sys_fbdiv_int,
                               UINT32_C(133)>::template reg_msk<UINT32_C(0xFFF) << 0U>();

  // PLL_SYS->PRIM.bit.POSTDIV1 = 6U;
  mcal::reg::reg_access_static<std::uint32_t,
                               std::uint32_t,
                               mcal::reg::pll_sys_prim,
                               UINT32_C(6) << 16U>::template reg_msk<UINT32_C(0x7) << 16U>();

  // PLL_SYS->PRIM.bit.POSTDIV2 = 2U;
  mcal::reg::reg_access_static<std::uint32_t,
                               std::uint32_t,
                               mcal::reg::pll_sys_prim,
                               UINT32_C(2) << 12U>::template reg_msk<UINT32_C(0x7) << 12U>();

  // PLL_SYS->PWR.bit.PD        = 0U;
  mcal::reg::reg_access_static<std::uint32_t,
                               std::uint32_t,
                               mcal::reg::pll_sys_pwr,
                               UINT32_C(0)>::bit_clr();

  // PLL_SYS->PWR.bit.VCOPD     = 0U;
  mcal::reg::reg_access_static<std::uint32_t,
                               std::uint32_t,
                               mcal::reg::pll_sys_pwr,
                               UINT32_C(5)>::bit_clr();

  // while(PLL_SYS->CS.bit.LOCK != 1U);
  while(!mcal::reg::reg_access_static<std::uint32_t,
                                      std::uint32_t,
                                      mcal::reg::pll_sys_cs,
                                      UINT32_C(31)>::bit_get()) { mcal::cpu::nop(); }

  // PLL_SYS->PWR.bit.POSTDIVPD = 0U;
  mcal::reg::reg_access_static<std::uint32_t,
                               std::uint32_t,
                               mcal::reg::pll_sys_pwr,
                               UINT32_C(3)>::bit_clr();

  // Switch the system clock to use the PLL.
  // CLOCKS->CLK_SYS_CTRL.bit.AUXSRC = CLOCKS_CLK_SYS_CTRL_AUXSRC_clksrc_pll_sys;
  mcal::reg::reg_access_static<std::uint32_t,
                               std::uint32_t,
                               mcal::reg::clocks_clk_sys_ctrl,
                               UINT32_C(0) << 5U>::template reg_msk<UINT32_C(0x7) << 5U>();


  // CLOCKS->CLK_SYS_CTRL.bit.SRC    = CLOCKS_CLK_SYS_CTRL_SRC_clksrc_clk_sys_aux;
  mcal::reg::reg_access_static<std::uint32_t,
                               std::uint32_t,
                               mcal::reg::clocks_clk_sys_ctrl,
                               UINT32_C(0)>::bit_set();

  // CLOCKS->CLK_SYS_DIV.bit.INT = 1U;
  mcal::reg::reg_access_static<std::uint32_t,
                               std::uint32_t,
                               mcal::reg::clocks_clk_sys_div,
                               UINT32_C(1) << 8U>::template reg_msk<UINT32_C(0x00FFFFFF) << 8U>();

  // CLOCKS->CLK_SYS_DIV.bit.FRAC = 0U;
  mcal::reg::reg_access_static<std::uint32_t,
                               std::uint32_t,
                               mcal::reg::clocks_clk_sys_div,
                               UINT32_C(0) << 0U>::template reg_msk<UINT32_C(0x000000FF) << 0U>();

  // while(CLOCKS->CLK_SYS_SELECTED == 0UL);
  while(mcal::reg::reg_access_static<std::uint32_t,
                                     std::uint32_t,
                                     mcal::reg::clocks_clk_sys_selected>::reg_get() == std::uint32_t { UINT8_C(0) })
  {
    mcal::cpu::nop();
  }

  // Enable the clock for peripherals.
  // CLOCKS->CLK_PERI_CTRL.bit.ENABLE = 1U;
  mcal::reg::reg_access_static<std::uint32_t,
                               std::uint32_t,
                               mcal::reg::clocks_clk_peri_ctrl,
                               UINT32_C(11)>::bit_set();

  // Release reset on IO_BANK0.
  // RESETS->RESET.bit.io_bank0 = 0U;
  mcal::reg::reg_access_static<std::uint32_t,
                               std::uint32_t,
                               mcal::reg::resets_reset,
                               UINT32_C(5)>::bit_clr();

  // Wait for reset to be done.
  // Release reset is done on IO_BANK0.
  // while(RESETS->RESET_DONE.bit.io_bank0 != 1);

  while(!mcal::reg::reg_access_static<std::uint32_t,
                                      std::uint32_t,
                                      mcal::reg::resets_reset_done,
                                      UINT32_C(5)>::bit_get()) {  mcal::cpu::nop(); }
}
