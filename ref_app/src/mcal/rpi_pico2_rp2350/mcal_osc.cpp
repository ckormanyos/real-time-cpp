///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2024.
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

  // HW_PER_XOSC->STARTUP.bit.X4 = 0U;
  mcal::reg::reg_access_static<std::uint32_t,
                               std::uint32_t,
                               mcal::reg::xosc_startup,
                               std::uint32_t { UINT32_C(20) }>::bit_clr();

  // HW_PER_XOSC->STARTUP.bit.DELAY = 47U;
  mcal::reg::reg_access_static<std::uint32_t,
                               std::uint32_t,
                               mcal::reg::xosc_startup,
                               std::uint32_t { UINT32_C(47) << 0U }>::template reg_msk<std::uint32_t { UINT32_C(0x1FFF) << 0U }>();

  // HW_PER_XOSC->CTRL.bit.FREQ_RANGE = HW_PER_XOSC->STATUS.bit.FREQ_RANGE;

  const std::uint32_t
    status_freq_range
    {
        mcal::reg::reg_access_static<std::uint32_t, std::uint32_t, mcal::reg::xosc_status>::reg_get()
      & std::uint32_t { UINT32_C(3) }
    };

  mcal::reg::reg_access_dynamic<std::uint32_t, std::uint32_t>::reg_msk
  (
    mcal::reg::xosc_ctrl,
    std::uint32_t { status_freq_range << 0U },
    std::uint32_t { UINT32_C(0x0FFF) << 0U }
  );

  // HW_PER_XOSC->CTRL.bit.ENABLE = XOSC_CTRL_ENABLE_ENABLE;
  mcal::reg::reg_access_static<std::uint32_t,
                               std::uint32_t,
                               mcal::reg::xosc_ctrl,
                               std::uint32_t { UINT32_C(4011) << 12U }>::template reg_msk<std::uint32_t { UINT32_C(0x0FFF) << 12U }>();

  // while(HW_PER_XOSC->STATUS.bit.STABLE != 1U);
  while(!mcal::reg::reg_access_static<std::uint32_t,
                                      std::uint32_t,
                                      mcal::reg::xosc_status,
                                      std::uint32_t { UINT32_C(31) }>::bit_get()) { mcal::cpu::nop(); }

  // Switch the ref clock to use the xosc clock as its source.
  // HW_PER_CLOCKS->CLK_REF_CTRL.bit.SRC = CLOCKS_CLK_REF_CTRL_SRC_xosc_clksrc;
  mcal::reg::reg_access_static<std::uint32_t,
                               std::uint32_t,
                               mcal::reg::clocks_clk_ref_ctrl,
                               std::uint32_t { UINT32_C(2) << 0U }>::template reg_msk<std::uint32_t { UINT32_C(0x3) << 0U }>();

  // while(HW_PER_CLOCKS->CLK_REF_SELECTED.reg != (1ul << CLOCKS_CLK_REF_CTRL_SRC_xosc_clksrc));
  while
  (
    mcal::reg::reg_access_static<std::uint32_t,
                                 std::uint32_t,
                                 mcal::reg::clocks_clk_ref_selected>::reg_get() != std::uint32_t { UINT32_C(1) << 2U }
  )
  {
    mcal::cpu::nop();
  }

  // while(HW_PER_CLOCKS->CLK_REF_DIV.bit.INT != 1);

  {
    std::uint8_t ref_div_int { UINT8_C(1) };

    while(ref_div_int != UINT8_C(1))
    {
      ref_div_int =
        static_cast<std::uint8_t>
        (
          mcal::reg::reg_access_static<std::uint32_t,
                                       std::uint32_t,
                                       mcal::reg::clocks_clk_ref_div>::reg_get() >> 16U
        );
    }
  }

  // Release the reset of PLL_SYS.
  // HW_PER_RESETS->RESET.bit.PLL_SYS = 0U;
  mcal::reg::reg_access_static<std::uint32_t,
                               std::uint32_t,
                               mcal::reg::resets_reset,
                               std::uint32_t { UINT32_C(14) }>::bit_clr();

  // while(HW_PER_RESETS->RESET_DONE.bit.PLL_SYS != 1);
  while(!mcal::reg::reg_access_static<std::uint32_t,
                                      std::uint32_t,
                                      mcal::reg::resets_reset_done,
                                      std::uint32_t { UINT32_C(14) }>::bit_get()) { mcal::cpu::nop(); }

  // Configure the PLL_SYS.
  // HW_PER_PLL_SYS->CS.bit.REFDIV = 1U;
  mcal::reg::reg_access_static<std::uint32_t,
                               std::uint32_t,
                               mcal::reg::pll_sys_cs,
                               std::uint32_t { UINT32_C(1) }>::template reg_msk<std::uint32_t { UINT32_C(0x3F) << 0U }>();

  // HW_PER_PLL_SYS->FBDIV_INT.bit.FBDIV_INT = 125U;
  mcal::reg::reg_access_static<std::uint32_t,
                               std::uint32_t,
                               mcal::reg::pll_sys_fbdiv_int,
                               std::uint32_t { UINT32_C(125) }>::template reg_msk<std::uint32_t { UINT32_C(0xFFF) << 0U }>();

  // HW_PER_PLL_SYS->PRIM.bit.POSTDIV1 = 5U;
  mcal::reg::reg_access_static<std::uint32_t,
                               std::uint32_t,
                               mcal::reg::pll_sys_prim,
                               std::uint32_t { UINT32_C(5) << 16U }>::template reg_msk<std::uint32_t { UINT32_C(0x7) << 16U }>();

  // HW_PER_PLL_SYS->PRIM.bit.POSTDIV2 = 2U;
  mcal::reg::reg_access_static<std::uint32_t,
                               std::uint32_t,
                               mcal::reg::pll_sys_prim,
                               std::uint32_t { UINT32_C(2) << 12U }>::template reg_msk<std::uint32_t { UINT32_C(0x7) << 12U }>();

  // HW_PER_PLL_SYS->PWR.bit.PD = 0U;
  mcal::reg::reg_access_static<std::uint32_t,
                               std::uint32_t,
                               mcal::reg::pll_sys_pwr,
                               std::uint32_t { UINT32_C(0) }>::bit_clr();

  // HW_PER_PLL_SYS->PWR.bit.VCOPD = 0U;
  mcal::reg::reg_access_static<std::uint32_t,
                               std::uint32_t,
                               mcal::reg::pll_sys_pwr,
                               std::uint32_t { UINT32_C(5) }>::bit_clr();

  // HW_PER_PLL_SYS->PWR.bit.POSTDIVPD = 0U;
  mcal::reg::reg_access_static<std::uint32_t,
                               std::uint32_t,
                               mcal::reg::pll_sys_pwr,
                               std::uint32_t { UINT32_C(3) }>::bit_clr();

  // while(HW_PER_PLL_SYS->CS.bit.LOCK != 1U);
  while(!mcal::reg::reg_access_static<std::uint32_t,
                                      std::uint32_t,
                                      mcal::reg::pll_sys_cs,
                                      std::uint32_t { UINT32_C(31) }>::bit_get()) { mcal::cpu::nop(); }

  // Switch the system clock to use the PLL.

  // HW_PER_CLOCKS->CLK_SYS_DIV.reg = 0x10000ul;
  mcal::reg::reg_access_static<std::uint32_t,
                               std::uint32_t,
                               mcal::reg::clocks_clk_sys_div,
                               std::uint32_t { UINT32_C(0x10000) }>::reg_set();

  // HW_PER_CLOCKS->CLK_SYS_CTRL.bit.AUXSRC = CLOCKS_CLK_SYS_CTRL_AUXSRC_clksrc_pll_sys;
  mcal::reg::reg_access_static<std::uint32_t,
                               std::uint32_t,
                               mcal::reg::clocks_clk_sys_ctrl,
                               std::uint32_t { UINT32_C(0) << 5U }>::template reg_msk<std::uint32_t { UINT32_C(0x7) << 5U }>();

  // HW_PER_CLOCKS->CLK_SYS_CTRL.bit.SRC = CLOCKS_CLK_SYS_CTRL_SRC_clksrc_clk_sys_aux;
  mcal::reg::reg_access_static<std::uint32_t,
                               std::uint32_t,
                               mcal::reg::clocks_clk_sys_ctrl,
                               std::uint32_t { UINT32_C(0) }>::bit_set();

  // while(HW_PER_CLOCKS->CLK_SYS_SELECTED.bit.CLK_SYS_SELECTED != (1ul << CLOCKS_CLK_SYS_CTRL_SRC_clksrc_clk_sys_aux));
  {
    std::uint8_t clk_sys_sel { UINT8_C(2) };

    while(clk_sys_sel != UINT8_C(2))
    {
      clk_sys_sel =
        static_cast<std::uint8_t>
        (
          mcal::reg::reg_access_static<std::uint32_t,
                                       std::uint32_t,
                                       mcal::reg::clocks_clk_sys_selected>::reg_get() & std::uint32_t { UINT32_C(3) }
        );
    }
  }

  // Enable the clock for peripherals.
  // HW_PER_CLOCKS->CLK_PERI_CTRL.bit.ENABLE = 1U;
  mcal::reg::reg_access_static<std::uint32_t,
                               std::uint32_t,
                               mcal::reg::clocks_clk_peri_ctrl,
                               std::uint32_t { UINT32_C(11) }>::bit_set();

  // Release the reset on IO_BANK0.
  // HW_PER_RESETS->RESET.bit.IO_BANK0 = 0U;
  mcal::reg::reg_access_static<std::uint32_t,
                               std::uint32_t,
                               mcal::reg::resets_reset,
                               std::uint32_t { UINT32_C(6) }>::bit_clr();

  // Wait for reset to be done.
  // Release reset is done on IO_BANK0.
  // while(HW_PER_RESETS->RESET_DONE.bit.IO_BANK0 != 1);
  while(!mcal::reg::reg_access_static<std::uint32_t,
                                      std::uint32_t,
                                      mcal::reg::resets_reset_done,
                                      std::uint32_t { UINT32_C(6) }>::bit_get()) { mcal::cpu::nop(); }
}
