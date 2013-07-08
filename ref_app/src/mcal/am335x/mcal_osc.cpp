///////////////////////////////////////////////////////////////////////////////
//  Copyright Michael Schnerr 2011 - 2013.
//  Copyright Christopher Kormanyos 2013.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <cstdint>
#include <mcal_cpu.h>
#include <mcal_osc.h>
#include <mcal_reg_access.h>

namespace mcal
{
  namespace osc
  {
    namespace detail
    {
      void mpu_pll_init                ();
      void core_pll_init               ();
      void peripheral_pll_init         ();
      void ddr_pll_init                ();
      void interface_clock_init        ();
      void power_domain_transition_init();
      void emif_init                   ();
      void gpio1_clock_init            ();
      void dm_timer7_clock_init        ();

      constexpr std::uint32_t mcu_clkinp        =         24UL; // Clock input 24MHz.

      constexpr std::uint32_t dpll_mn_byp_mode  =       0x04UL;
      constexpr std::uint32_t dpll_lock_mode    =       0x07UL;

      constexpr unsigned st_dpll_clk_bpos       =           0U;
      constexpr unsigned st_mn_bypass_bpos      =           8U;

      constexpr std::uint32_t modulemode_enable =       0x02UL;
      constexpr std::uint32_t modulemode_mask   =       0x03UL;

      constexpr std::uint32_t idlest_func       = 0x00000000UL;
      constexpr std::uint32_t idlest_mask       = 0x00030000UL;
    }
  }
}

void mcal::osc::detail::mpu_pll_init()
{
  // Set the MPU clock to 600MHz.

  // CLKOUT = [M / (N + 1)] * CLKINP * [1 / M2] = 600
  constexpr std::uint32_t mcu_mpu_pll_m  = 600UL;
  constexpr std::uint32_t mcu_mpu_pll_n  =  23UL;
  constexpr std::uint32_t mcu_mpu_pll_m2 =   1UL;

  // Put the PLL in bypass mode.
  mcal::reg::access<std::uint32_t,
                    std::uint32_t,
                    mcal::reg::cm_wkup::clkmode_dpll_mpu,
                    dpll_mn_byp_mode>::reg_msk<0x07UL>();

  // Wait for DPLL to go into bypass mode.
  while(!mcal::reg::access<std::uint32_t, std::uint32_t, mcal::reg::cm_wkup::idlest_dpll_mpu, st_mn_bypass_bpos>::bit_get()) { mcal::cpu::nop(); }

  // Set the multiplier and divider values for the PLL.
  mcal::reg::access<std::uint32_t,
                    std::uint32_t,
                    mcal::reg::cm_wkup::clksel_dpll_mpu,
                    (mcu_mpu_pll_m << 8) | (mcu_mpu_pll_n)>::reg_msk<0x0007FF7FUL>();

  // Set the M2 divider values for the PLL.
  mcal::reg::access<std::uint32_t,
                    std::uint32_t,
                    mcal::reg::cm_wkup::div_m2_dpll_mpu,
                    mcu_mpu_pll_m2>::reg_msk<0x0000003FUL>();

  // Enable the PLL in lock mode.
  mcal::reg::access<std::uint32_t,
                    std::uint32_t,
                    mcal::reg::cm_wkup::clkmode_dpll_mpu,
                    dpll_lock_mode>::reg_msk<0x07UL>();

  // Wait for lock.
  while(!mcal::reg::access<std::uint32_t, std::uint32_t, mcal::reg::cm_wkup::idlest_dpll_mpu, st_dpll_clk_bpos>::bit_get()) { mcal::cpu::nop(); }
}

void mcal::osc::detail::core_pll_init()
{
  // Enable the Core PLL.

  // clkinp = 24MHz
  // clkdcoldo = 2 * [m / (n + 1)] * clkinp = 2000
  // clkoutm4  = clkdcoldo / m4 = 200
  // clkoutm5  = clkdcoldo / m5 = 250
  // clkoutm6  = clkdcoldo / m6 = 500
  constexpr std::uint32_t mcu_core_pll_m  =  1000UL;
  constexpr std::uint32_t mcu_core_pll_n  =    23UL;
  constexpr std::uint32_t mcu_core_pll_m4 =    10UL;
  constexpr std::uint32_t mcu_core_pll_m5 =     8UL;
  constexpr std::uint32_t mcu_core_pll_m6 =     4UL;

  // Put the PLL in bypass mode.
  mcal::reg::access<std::uint32_t,
                    std::uint32_t,
                    mcal::reg::cm_wkup::clkmode_dpll_core,
                    dpll_mn_byp_mode>::reg_msk<0x07UL>();

  // Wait for DPLL to go into bypass mode.
  while(!mcal::reg::access<std::uint32_t, std::uint32_t, mcal::reg::cm_wkup::idlest_dpll_core, st_mn_bypass_bpos>::bit_get()) { mcal::cpu::nop(); }

  // Set the multiplier and divider values for the PLL.
  mcal::reg::access<std::uint32_t,
                    std::uint32_t,
                    mcal::reg::cm_wkup::clksel_dpll_core,
                    (mcu_core_pll_m << 8) | (mcu_core_pll_n)>::reg_msk<0x0007ff7FUL>();

  // Configure the high speed dividers.
  mcal::reg::access<std::uint32_t,
                    std::uint32_t,
                    mcal::reg::cm_wkup::div_m4_dpll_core,
                    mcu_core_pll_m4>::reg_msk<0x0000001FUL>();

  mcal::reg::access<std::uint32_t,
                    std::uint32_t,
                    mcal::reg::cm_wkup::div_m5_dpll_core,
                    mcu_core_pll_m5>::reg_msk<0x0000001FUL>();

  mcal::reg::access<std::uint32_t,
                    std::uint32_t,
                    mcal::reg::cm_wkup::div_m6_dpll_core,
                    mcu_core_pll_m6>::reg_msk<0x0000001FUL>();

  // Enable the PLL in lock mode.
  mcal::reg::access<std::uint32_t,
                    std::uint32_t,
                    mcal::reg::cm_wkup::clkmode_dpll_core,
                    dpll_lock_mode>::reg_msk<0x07UL>();

  // Wait for lock.
  while(!mcal::reg::access<std::uint32_t, std::uint32_t, mcal::reg::cm_wkup::idlest_dpll_core, st_dpll_clk_bpos>::bit_get()) { mcal::cpu::nop(); }
}

void mcal::osc::detail::peripheral_pll_init()
{
  // Set the Peripheral clock to 960MHz
  // clkinp = 24MHz
  // clkout    = (m / (n + 1)) * clkinp * (1 / m2) = 192
  // clkdcoldo = (m / (n + 1)) * clkinp            = 960
  constexpr std::uint32_t mcu_per_pll_m  =   960UL;
  constexpr std::uint32_t mcu_per_pll_n  =    23UL;
  constexpr std::uint32_t mcu_per_pll_m2 =     5UL;
  constexpr std::uint32_t mcu_per_pll_sd =   (((mcu_per_pll_m / (mcu_per_pll_n + 1UL) * mcu_clkinp) + 249UL) / 250UL);

  // Put the PLL in bypass mode.
  mcal::reg::access<std::uint32_t,
                    std::uint32_t,
                    mcal::reg::cm_wkup::clkmode_dpll_per,
                    dpll_mn_byp_mode>::reg_msk<0x07UL>();

  // Wait for DPLL to go into bypass mode.
  while(!mcal::reg::access<std::uint32_t, std::uint32_t, mcal::reg::cm_wkup::idlest_dpll_per, st_mn_bypass_bpos>::bit_get()) { mcal::cpu::nop(); }

  // Set the multiplier and divider values for the PLL.
  mcal::reg::access<std::uint32_t,
                    std::uint32_t,
                    mcal::reg::cm_wkup::clksel_dpll_periph,
                    (mcu_per_pll_sd << 24U) | (mcu_per_pll_m << 8U) | mcu_per_pll_n>::reg_msk<0xFF0FFFFFUL>();

  // Set the M2 divider values for the PLL.
  mcal::reg::access<std::uint32_t,
                    std::uint32_t,
                    mcal::reg::cm_wkup::div_m2_dpll_per,
                    mcu_per_pll_m2>::reg_msk<0x0000003FUL>();

  // Enable the PLL in lock mode.
  mcal::reg::access<std::uint32_t,
                    std::uint32_t,
                    mcal::reg::cm_wkup::clkmode_dpll_per,
                    dpll_lock_mode>::reg_msk<0x07UL>();

  // Wait for lock.
  while(!mcal::reg::access<std::uint32_t, std::uint32_t, mcal::reg::cm_wkup::idlest_dpll_per, st_dpll_clk_bpos>::bit_get()) { mcal::cpu::nop(); }
}

void mcal::osc::detail::ddr_pll_init()
{
  // Setting DDR clock to 266
  constexpr std::uint32_t mcu_ddr_pll_m  = 266UL;
  constexpr std::uint32_t mcu_ddr_pll_n  =  23UL;
  constexpr std::uint32_t mcu_ddr_pll_m2 =   1UL;

  // Put the PLL in bypass mode.
  mcal::reg::access<std::uint32_t,
                    std::uint32_t,
                    mcal::reg::cm_wkup::clkmode_dpll_ddr,
                    dpll_mn_byp_mode>::reg_msk<0x07UL>();

  // Wait for DPLL to go into bypass mode.
  while(!mcal::reg::access<std::uint32_t, std::uint32_t, mcal::reg::cm_wkup::idlest_dpll_ddr, st_mn_bypass_bpos>::bit_get()) { mcal::cpu::nop(); }

  // Set the multiplier and divider values for the PLL.
  mcal::reg::access<std::uint32_t,
                    std::uint32_t,
                    mcal::reg::cm_wkup::clksel_dpll_ddr,
                    (mcu_ddr_pll_m << 8) | mcu_ddr_pll_n>::reg_msk<0x0007FF7FUL>();

  // Set the m2 divider values for the PLL.
  mcal::reg::access<std::uint32_t,
                    std::uint32_t,
                    mcal::reg::cm_wkup::div_m2_dpll_ddr,
                    mcu_ddr_pll_m2>::reg_msk<0x0000003FUL>();

  // Enable the PLL in lock mode.
  mcal::reg::access<std::uint32_t,
                    std::uint32_t,
                    mcal::reg::cm_wkup::clkmode_dpll_ddr,
                    dpll_lock_mode>::reg_msk<0x07UL>();

  // Wait for lock.
  while(!mcal::reg::access<std::uint32_t, std::uint32_t, mcal::reg::cm_wkup::idlest_dpll_ddr, st_dpll_clk_bpos>::bit_get()) { mcal::cpu::nop(); }
}

void mcal::osc::detail::interface_clock_init()
{
  mcal::reg::access<std::uint32_t,
                    std::uint32_t,
                    mcal::reg::cm_per::l3_clkctrl,
                    modulemode_enable>::reg_msk<modulemode_mask>();
  while((mcal::reg::access<std::uint32_t, std::uint32_t, mcal::reg::cm_per::l3_clkctrl>::reg_get() & modulemode_mask) != modulemode_enable) { mcal::cpu::nop(); }

  mcal::reg::access<std::uint32_t,
                    std::uint32_t,
                    mcal::reg::cm_per::l4ls_clkctrl,
                    modulemode_enable>::reg_msk<modulemode_mask>();
  while((mcal::reg::access<std::uint32_t, std::uint32_t, mcal::reg::cm_per::l4ls_clkctrl>::reg_get() & modulemode_mask) != modulemode_enable) { mcal::cpu::nop(); }

  mcal::reg::access<std::uint32_t,
                    std::uint32_t,
                    mcal::reg::cm_per::l4fw_clkctrl,
                    modulemode_enable>::reg_msk<modulemode_mask>();
  while((mcal::reg::access<std::uint32_t, std::uint32_t, mcal::reg::cm_per::l4fw_clkctrl>::reg_get() & modulemode_mask) != modulemode_enable) { mcal::cpu::nop(); }

  // TBD: delete this: It seems to be a read-only register?
  mcal::reg::access<std::uint32_t,
                    std::uint32_t,
                    mcal::reg::cm_wkup::l4wkup_clkctrl,
                    modulemode_enable>::reg_msk<modulemode_mask>();
  while((mcal::reg::access<std::uint32_t, std::uint32_t, mcal::reg::cm_wkup::l4wkup_clkctrl>::reg_get() & modulemode_mask) != modulemode_enable) { mcal::cpu::nop(); }

  mcal::reg::access<std::uint32_t,
                    std::uint32_t,
                    mcal::reg::cm_per::l3_instr_clkctrl,
                    modulemode_enable>::reg_msk<modulemode_mask>();
  while((mcal::reg::access<std::uint32_t, std::uint32_t, mcal::reg::cm_per::l3_instr_clkctrl>::reg_get() & modulemode_mask) != modulemode_enable) { mcal::cpu::nop(); }

  mcal::reg::access<std::uint32_t,
                    std::uint32_t,
                    mcal::reg::cm_per::l4hs_clkctrl,
                    modulemode_enable>::reg_msk<modulemode_mask>();
  while((mcal::reg::access<std::uint32_t, std::uint32_t, mcal::reg::cm_per::l4hs_clkctrl>::reg_get() & modulemode_mask) != modulemode_enable) { mcal::cpu::nop(); }
}

void mcal::osc::detail::power_domain_transition_init()
{
  constexpr std::uint32_t clktrctrl_sw_wkup = 0x2UL;
  constexpr std::uint32_t clktrctrl_mask    = 0x3UL;

  mcal::reg::access<std::uint32_t,
                    std::uint32_t,
                    mcal::reg::cm_per::l3_clkstctrl,
                    clktrctrl_sw_wkup>::reg_msk<clktrctrl_mask>();
  while((mcal::reg::access<std::uint32_t, std::uint32_t, mcal::reg::cm_per::l3_clkstctrl>::reg_get() & clktrctrl_mask) != clktrctrl_sw_wkup) { mcal::cpu::nop(); }

  mcal::reg::access<std::uint32_t,
                    std::uint32_t,
                    mcal::reg::cm_per::l4ls_clkstctrl,
                    clktrctrl_sw_wkup>::reg_msk<clktrctrl_mask>();
  while((mcal::reg::access<std::uint32_t, std::uint32_t, mcal::reg::cm_per::l4ls_clkstctrl>::reg_get() & clktrctrl_mask) != clktrctrl_sw_wkup) { mcal::cpu::nop(); }

  mcal::reg::access<std::uint32_t,
                    std::uint32_t,
                    mcal::reg::cm_wkup::clkstctrl,
                    clktrctrl_sw_wkup>::reg_msk<clktrctrl_mask>();
  while((mcal::reg::access<std::uint32_t, std::uint32_t, mcal::reg::cm_wkup::clkstctrl>::reg_get() & clktrctrl_mask) != clktrctrl_sw_wkup) { mcal::cpu::nop(); }

  mcal::reg::access<std::uint32_t,
                    std::uint32_t,
                    mcal::reg::cm_per::l3s_clkstctrl,
                    clktrctrl_sw_wkup>::reg_msk<clktrctrl_mask>();
  while((mcal::reg::access<std::uint32_t, std::uint32_t, mcal::reg::cm_per::l3s_clkstctrl>::reg_get() & clktrctrl_mask) != clktrctrl_sw_wkup) { mcal::cpu::nop(); }
}

void mcal::osc::detail::emif_init()
{
  constexpr std::uint32_t clkactivity_emif_gclk = 0x00000004UL;

  // Enable the clocks for the emif.

  mcal::reg::access<std::uint32_t,
                    std::uint32_t,
                    mcal::reg::cm_per::emif_clkctrl,
                    modulemode_enable>::reg_msk<modulemode_mask>();
  while((mcal::reg::access<std::uint32_t, std::uint32_t, mcal::reg::cm_per::l3_clkstctrl>::reg_get() & clkactivity_emif_gclk) != clkactivity_emif_gclk) { mcal::cpu::nop(); }
}

void mcal::osc::detail::gpio1_clock_init()
{
  constexpr std::uint32_t optfclken_gpio_1_gdbclk   = 0x00040000UL;
  constexpr std::uint32_t clkactivity_gpio_1_gdbclk = 0x00080000UL;

  // Set the module field of the cm_per::gpio1_clkctrl register.
  mcal::reg::access<std::uint32_t,
                    std::uint32_t,
                    mcal::reg::cm_per::gpio1_clkctrl,
                    modulemode_enable>::reg_msk<modulemode_mask>();
  while((mcal::reg::access<std::uint32_t, std::uint32_t, mcal::reg::cm_per::gpio1_clkctrl>::reg_get() & modulemode_mask) != modulemode_enable) { mcal::cpu::nop(); }

  // Enable the optional function clock.
  mcal::reg::access<std::uint32_t,
                    std::uint32_t,
                    mcal::reg::cm_per::gpio1_clkctrl,
                    optfclken_gpio_1_gdbclk>::reg_msk<optfclken_gpio_1_gdbclk>();

  while((mcal::reg::access<std::uint32_t, std::uint32_t, mcal::reg::cm_per::gpio1_clkctrl>::reg_get()  & optfclken_gpio_1_gdbclk  ) != optfclken_gpio_1_gdbclk  ) { mcal::cpu::nop(); }
  while((mcal::reg::access<std::uint32_t, std::uint32_t, mcal::reg::cm_per::gpio1_clkctrl>::reg_get()  & idlest_mask              ) != idlest_func              ) { mcal::cpu::nop(); }
  while((mcal::reg::access<std::uint32_t, std::uint32_t, mcal::reg::cm_per::l4ls_clkstctrl>::reg_get() & clkactivity_gpio_1_gdbclk) != clkactivity_gpio_1_gdbclk) { mcal::cpu::nop(); }
}

void mcal::osc::detail::dm_timer7_clock_init()
{
  constexpr std::uint32_t clksel_clk_m_osc        = 1UL;
  constexpr std::uint32_t clkactivity_timer7_gclk = 0x00002000UL;

  // Select the clock source clksel_clk_m_osc for timer7.
  mcal::reg::access<std::uint32_t,
                    std::uint32_t,
                    mcal::reg::cm_dpll::clksel_timer7_clk,
                    clksel_clk_m_osc>::reg_msk<0x3UL>();
  while((mcal::reg::access<std::uint32_t, std::uint32_t, mcal::reg::cm_dpll::clksel_timer7_clk>::reg_get() & 0x3UL) != clksel_clk_m_osc) { mcal::cpu::nop(); }

  mcal::reg::access<std::uint32_t,
                    std::uint32_t,
                    mcal::reg::cm_per::timer7_clkctrl,
                    modulemode_enable>::reg_msk<modulemode_mask>();

  while((mcal::reg::access<std::uint32_t, std::uint32_t, mcal::reg::cm_per::timer7_clkctrl>::reg_get() & modulemode_mask        ) != modulemode_enable      ) { mcal::cpu::nop(); }
  while((mcal::reg::access<std::uint32_t, std::uint32_t, mcal::reg::cm_per::timer7_clkctrl>::reg_get() & idlest_mask            ) != idlest_func            ) { mcal::cpu::nop(); }
  while((mcal::reg::access<std::uint32_t, std::uint32_t, mcal::reg::cm_per::l4ls_clkstctrl>::reg_get() & clkactivity_timer7_gclk) != clkactivity_timer7_gclk) { mcal::cpu::nop(); }
}

void mcal::osc::init(const config_type*)
{
  // Setup the clocksfor oscillator, PLL, RAM, I/O ports, and peripherals.

  detail::mpu_pll_init();
  detail::core_pll_init();
  detail::peripheral_pll_init();
  detail::ddr_pll_init();
  detail::interface_clock_init();
  detail::power_domain_transition_init();

  mcal::reg::access<std::uint32_t,
                    std::uint32_t,
                    mcal::reg::cm_wkup::control_clkctrl,
                    detail::modulemode_enable>::reg_msk<detail::modulemode_mask>();

  detail::emif_init();

  detail::gpio1_clock_init();
  detail::dm_timer7_clock_init();
}
