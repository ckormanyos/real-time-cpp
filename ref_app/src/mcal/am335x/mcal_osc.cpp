///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2014 - 2020.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <mcal_cpu.h>
#include <mcal_osc.h>
#include <mcal_osc_shared.h>
#include <mcal_reg.h>

namespace
{
  struct osc_detail
  {
    static void mpu_pll_init                ();
    static void core_pll_init               ();
    static void peripheral_pll_init         ();
    static void ddr_pll_init                ();
    static void interface_clock_init        ();
    static void power_domain_transition_init();
    static void emif_init                   ();
    static void dm_timer7_clock_init        ();

    static constexpr std::uint32_t modulemode_enable = mcal::osc::mcal_osc_shared::modulemode_enable;
    static constexpr std::uint32_t modulemode_mask   = mcal::osc::mcal_osc_shared::modulemode_mask;

    static constexpr std::uint32_t idlest_func       = mcal::osc::mcal_osc_shared::idlest_func;
    static constexpr std::uint32_t idlest_mask       = mcal::osc::mcal_osc_shared::idlest_mask;

    static constexpr std::uint32_t mcu_clkinp        = UINT32_C(24); // Clock input 24MHz.

    static constexpr std::uint32_t dpll_mn_byp_mode  = UINT32_C(0x04);
    static constexpr std::uint32_t dpll_lock_mode    = UINT32_C(0x07);

    static constexpr std::uint32_t st_dpll_clk_bpos  = UINT32_C(0);
    static constexpr std::uint32_t st_mn_bypass_bpos = UINT32_C(8);
  };
}

void osc_detail::mpu_pll_init()
{
  // Set the MPU clock.
  // Use up to 900MHz for the BeagleBone black edition.
  // The BeagleBone white edition is limited to 720MHz.

  // clkout = [m / (n + 1)] * clkinp * [1 / m2] = 900
  constexpr std::uint32_t mcu_mpu_pll_m  = UINT32_C(900);
  constexpr std::uint32_t mcu_mpu_pll_n  = UINT32_C(mcu_clkinp - 1);
  constexpr std::uint32_t mcu_mpu_pll_m2 = UINT32_C(1);

  // Put the PLL in bypass mode.
  mcal::reg::reg_access_static<std::uint32_t,
                               std::uint32_t,
                               mcal::reg::cm_wkup::clkmode_dpll_mpu,
                               dpll_mn_byp_mode>::reg_msk<UINT32_C(0x07)>();

  // Wait for DPLL to go into bypass mode.
  while(!mcal::reg::reg_access_static<std::uint32_t, std::uint32_t, mcal::reg::cm_wkup::idlest_dpll_mpu, st_mn_bypass_bpos>::bit_get()) { mcal::cpu::nop(); }

  // Set the multiplier and divider values for the PLL.
  // Here, we are using bits 0...6 and bits 8...18, resulting
  // in the bit mask 0x0007FF7F.
  mcal::reg::reg_access_static<std::uint32_t,
                               std::uint32_t,
                               mcal::reg::cm_wkup::clksel_dpll_mpu,
                               std::uint32_t((mcu_mpu_pll_m << 8) | (mcu_mpu_pll_n))>::reg_msk<UINT32_C(0x0007FF7F)>();

  // Set the M2 divider values for the PLL. Here, we are using
  // bits 0...4, resulting in the bit mask 0x0000001F.
  mcal::reg::reg_access_static<std::uint32_t,
                               std::uint32_t,
                               mcal::reg::cm_wkup::div_m2_dpll_mpu,
                               mcu_mpu_pll_m2>::reg_msk<UINT32_C(0x0000001F)>();

  // Enable the PLL in lock mode. Here, we are using
  // bits 0...2, resulting in the bit mask 0x00000007.
  mcal::reg::reg_access_static<std::uint32_t,
                               std::uint32_t,
                               mcal::reg::cm_wkup::clkmode_dpll_mpu,
                               dpll_lock_mode>::reg_msk<UINT32_C(0x07)>();

  // Wait for lock.
  while(!mcal::reg::reg_access_static<std::uint32_t, std::uint32_t, mcal::reg::cm_wkup::idlest_dpll_mpu, st_dpll_clk_bpos>::bit_get()) { mcal::cpu::nop(); }
}

void osc_detail::core_pll_init()
{
  // Enable the Core PLL.

  // clkinp = 24MHz
  // clkdcoldo = 2 * [m / (n + 1)] * clkinp = 2000
  // clkoutm4  = clkdcoldo / m4 = 2000 / 10 =  200
  // clkoutm5  = clkdcoldo / m5 = 2000 /  8 =  250
  // clkoutm6  = clkdcoldo / m6 = 2000 /  4 =  500

  // See also:
  // https://github.com/kientzle/u-boot-beaglebone-freebsd

  constexpr std::uint32_t mcu_core_pll_m  =  UINT32_C(1000);
  constexpr std::uint32_t mcu_core_pll_n  =  UINT32_C(mcu_clkinp - 1);
  constexpr std::uint32_t mcu_core_pll_m4 =  UINT32_C(10);
  constexpr std::uint32_t mcu_core_pll_m5 =  UINT32_C(8);
  constexpr std::uint32_t mcu_core_pll_m6 =  UINT32_C(4);

  // Switch the PLL to bypass mode. Here, we are using
  // bits 0...2, resulting in the bit mask 0x00000007.
  mcal::reg::reg_access_static<std::uint32_t,
                               std::uint32_t,
                               mcal::reg::cm_wkup::clkmode_dpll_core,
                               dpll_mn_byp_mode>::reg_msk<UINT32_C(0x07)>();

  // Wait for DPLL to go into bypass mode.
  while(!mcal::reg::reg_access_static<std::uint32_t, std::uint32_t, mcal::reg::cm_wkup::idlest_dpll_core, st_mn_bypass_bpos>::bit_get()) { mcal::cpu::nop(); }

  // Set the multiplier and divider values for the PLL.
  // Here, we are using bits 0...6 and bits 8...18, resulting
  // in the bit mask 0x0007FF7F.
  mcal::reg::reg_access_static<std::uint32_t,
                               std::uint32_t,
                               mcal::reg::cm_wkup::clksel_dpll_core,
                               std::uint32_t((mcu_core_pll_m << 8) | (mcu_core_pll_n))>::reg_msk<UINT32_C(0x0007FF7F)>();

  // Configure the high speed divider m4. Here, we are using
  // bits 0...4, resulting in the bit mask 0x0000001F.
  mcal::reg::reg_access_static<std::uint32_t,
                               std::uint32_t,
                               mcal::reg::cm_wkup::div_m4_dpll_core,
                               mcu_core_pll_m4>::reg_msk<UINT32_C(0x0000001F)>();

  // Configure the high speed divider m5. Here, we are using
  // bits 0...4, resulting in the bit mask 0x0000001F.
  mcal::reg::reg_access_static<std::uint32_t,
                               std::uint32_t,
                               mcal::reg::cm_wkup::div_m5_dpll_core,
                               mcu_core_pll_m5>::reg_msk<UINT32_C(0x0000001F)>();

  // Configure the high speed divider m6. Here, we are using
  // bits 0...4, resulting in the bit mask 0x0000001F.
  mcal::reg::reg_access_static<std::uint32_t,
                               std::uint32_t,
                               mcal::reg::cm_wkup::div_m6_dpll_core,
                               mcu_core_pll_m6>::reg_msk<UINT32_C(0x0000001F)>();

  // Enable the PLL in lock mode. Here, we are using
  // bits 0...2, resulting in the bit mask 0x00000007.
  mcal::reg::reg_access_static<std::uint32_t,
                               std::uint32_t,
                               mcal::reg::cm_wkup::clkmode_dpll_core,
                               dpll_lock_mode>::reg_msk<UINT32_C(0x07)>();

  // Wait for lock.
  while(!mcal::reg::reg_access_static<std::uint32_t, std::uint32_t, mcal::reg::cm_wkup::idlest_dpll_core, st_dpll_clk_bpos>::bit_get()) { mcal::cpu::nop(); }
}

void osc_detail::peripheral_pll_init()
{
  // Set the Peripheral clock to 960MHz
  // clkinp = 24MHz
  // clkout    = (m / (n + 1)) * clkinp * (1 / m2) = 192
  // clkdcoldo = (m / (n + 1)) * clkinp            = 960
  constexpr std::uint32_t mcu_per_pll_m  = UINT32_C(960);
  constexpr std::uint32_t mcu_per_pll_n  = UINT32_C(mcu_clkinp - 1);
  constexpr std::uint32_t mcu_per_pll_m2 = UINT32_C(5);
  constexpr std::uint32_t mcu_per_pll_sd = std::uint32_t(((mcu_per_pll_m / (mcu_per_pll_n + UINT32_C(1)) * mcu_clkinp) + UINT32_C(249)) / UINT32_C(250));

  // Put the PLL in bypass mode.
  mcal::reg::reg_access_static<std::uint32_t,
                    std::uint32_t,
                    mcal::reg::cm_wkup::clkmode_dpll_per,
                    dpll_mn_byp_mode>::reg_msk<UINT32_C(0x07)>();

  // Wait for DPLL to go into bypass mode.
  while(!mcal::reg::reg_access_static<std::uint32_t, std::uint32_t, mcal::reg::cm_wkup::idlest_dpll_per, st_mn_bypass_bpos>::bit_get()) { mcal::cpu::nop(); }

  // Set the multiplier and divider values for the PLL.
  constexpr std::uint32_t pll_val = std::uint32_t(  std::uint32_t(mcu_per_pll_sd << 24)
                                                  | std::uint32_t(mcu_per_pll_m << 8)
                                                  | mcu_per_pll_n);

  mcal::reg::reg_access_static<std::uint32_t,
                               std::uint32_t,
                               mcal::reg::cm_wkup::clksel_dpll_periph,
                               pll_val>::reg_msk<UINT32_C(0xFF0FFFFF)>();

  // Set the M2 divider values for the PLL.
  mcal::reg::reg_access_static<std::uint32_t,
                               std::uint32_t,
                               mcal::reg::cm_wkup::div_m2_dpll_per,
                               mcu_per_pll_m2>::reg_msk<UINT32_C(0x0000003F)>();

  // Enable the PLL in lock mode.
  mcal::reg::reg_access_static<std::uint32_t,
                               std::uint32_t,
                               mcal::reg::cm_wkup::clkmode_dpll_per,
                               dpll_lock_mode>::reg_msk<UINT32_C(0x07)>();

  // Wait for lock.
  while(!mcal::reg::reg_access_static<std::uint32_t, std::uint32_t, mcal::reg::cm_wkup::idlest_dpll_per, st_dpll_clk_bpos>::bit_get()) { mcal::cpu::nop(); }
}

void osc_detail::ddr_pll_init()
{
  // Setting DDR clock to 266
  constexpr std::uint32_t mcu_ddr_pll_m  = UINT32_C(266);
  constexpr std::uint32_t mcu_ddr_pll_n  = UINT32_C(mcu_clkinp - 1);
  constexpr std::uint32_t mcu_ddr_pll_m2 = UINT32_C(1);

  // Put the PLL in bypass mode.
  mcal::reg::reg_access_static<std::uint32_t,
                               std::uint32_t,
                               mcal::reg::cm_wkup::clkmode_dpll_ddr,
                               dpll_mn_byp_mode>::reg_msk<UINT32_C(0x07)>();

  // Wait for DPLL to go into bypass mode.
  while(!mcal::reg::reg_access_static<std::uint32_t, std::uint32_t, mcal::reg::cm_wkup::idlest_dpll_ddr, st_mn_bypass_bpos>::bit_get()) { mcal::cpu::nop(); }

  // Set the multiplier and divider values for the PLL.
  constexpr std::uint32_t pll_val = std::uint32_t(  std::uint32_t(mcu_ddr_pll_m << 8)
                                                  | mcu_ddr_pll_n);

  mcal::reg::reg_access_static<std::uint32_t,
                               std::uint32_t,
                               mcal::reg::cm_wkup::clksel_dpll_ddr,
                               pll_val>::reg_msk<UINT32_C(0x0007FF7F)>();

  // Set the m2 divider values for the PLL.
  mcal::reg::reg_access_static<std::uint32_t,
                               std::uint32_t,
                               mcal::reg::cm_wkup::div_m2_dpll_ddr,
                               mcu_ddr_pll_m2>::reg_msk<UINT32_C(0x0000003F)>();

  // Enable the PLL in lock mode.
  mcal::reg::reg_access_static<std::uint32_t,
                    std::uint32_t,
                    mcal::reg::cm_wkup::clkmode_dpll_ddr,
                    dpll_lock_mode>::reg_msk<UINT32_C(0x07)>();

  // Wait for lock.
  while(!mcal::reg::reg_access_static<std::uint32_t, std::uint32_t, mcal::reg::cm_wkup::idlest_dpll_ddr, st_dpll_clk_bpos>::bit_get()) { mcal::cpu::nop(); }
}

void osc_detail::interface_clock_init()
{
  mcal::reg::reg_access_static<std::uint32_t,
                               std::uint32_t,
                               mcal::reg::cm_per::l3_clkctrl,
                               modulemode_enable>::reg_msk<modulemode_mask>();
  while((mcal::reg::reg_access_static<std::uint32_t, std::uint32_t, mcal::reg::cm_per::l3_clkctrl>::reg_get() & modulemode_mask) != modulemode_enable) { mcal::cpu::nop(); }

  mcal::reg::reg_access_static<std::uint32_t,
                               std::uint32_t,
                               mcal::reg::cm_per::l4ls_clkctrl,
                               modulemode_enable>::reg_msk<modulemode_mask>();
  while((mcal::reg::reg_access_static<std::uint32_t, std::uint32_t, mcal::reg::cm_per::l4ls_clkctrl>::reg_get() & modulemode_mask) != modulemode_enable) { mcal::cpu::nop(); }

  mcal::reg::reg_access_static<std::uint32_t,
                               std::uint32_t,
                               mcal::reg::cm_per::l4fw_clkctrl,
                               modulemode_enable>::reg_msk<modulemode_mask>();
  while((mcal::reg::reg_access_static<std::uint32_t, std::uint32_t, mcal::reg::cm_per::l4fw_clkctrl>::reg_get() & modulemode_mask) != modulemode_enable) { mcal::cpu::nop(); }

  // Is this an error in the documentation. The entire register,
  // including the modulemask field, is listed as a read-only register.
  mcal::reg::reg_access_static<std::uint32_t,
                               std::uint32_t,
                               mcal::reg::cm_wkup::l4wkup_clkctrl,
                               modulemode_enable>::reg_msk<modulemode_mask>();
  while((mcal::reg::reg_access_static<std::uint32_t, std::uint32_t, mcal::reg::cm_wkup::l4wkup_clkctrl>::reg_get() & modulemode_mask) != modulemode_enable) { mcal::cpu::nop(); }

  mcal::reg::reg_access_static<std::uint32_t,
                               std::uint32_t,
                               mcal::reg::cm_per::l3_instr_clkctrl,
                               modulemode_enable>::reg_msk<modulemode_mask>();
  while((mcal::reg::reg_access_static<std::uint32_t, std::uint32_t, mcal::reg::cm_per::l3_instr_clkctrl>::reg_get() & modulemode_mask) != modulemode_enable) { mcal::cpu::nop(); }

  mcal::reg::reg_access_static<std::uint32_t,
                               std::uint32_t,
                               mcal::reg::cm_per::l4hs_clkctrl,
                               modulemode_enable>::reg_msk<modulemode_mask>();
  while((mcal::reg::reg_access_static<std::uint32_t, std::uint32_t, mcal::reg::cm_per::l4hs_clkctrl>::reg_get() & modulemode_mask) != modulemode_enable) { mcal::cpu::nop(); }
}

void osc_detail::power_domain_transition_init()
{
  constexpr std::uint32_t clktrctrl_sw_wkup = UINT32_C(0x2);
  constexpr std::uint32_t clktrctrl_mask    = UINT32_C(0x3);

  mcal::reg::reg_access_static<std::uint32_t,
                               std::uint32_t,
                               mcal::reg::cm_per::l3_clkstctrl,
                               clktrctrl_sw_wkup>::reg_msk<clktrctrl_mask>();
  while((mcal::reg::reg_access_static<std::uint32_t, std::uint32_t, mcal::reg::cm_per::l3_clkstctrl>::reg_get() & clktrctrl_mask) != clktrctrl_sw_wkup) { mcal::cpu::nop(); }

  mcal::reg::reg_access_static<std::uint32_t,
                               std::uint32_t,
                               mcal::reg::cm_per::l4ls_clkstctrl,
                               clktrctrl_sw_wkup>::reg_msk<clktrctrl_mask>();
  while((mcal::reg::reg_access_static<std::uint32_t, std::uint32_t, mcal::reg::cm_per::l4ls_clkstctrl>::reg_get() & clktrctrl_mask) != clktrctrl_sw_wkup) { mcal::cpu::nop(); }

  mcal::reg::reg_access_static<std::uint32_t,
                               std::uint32_t,
                               mcal::reg::cm_wkup::clkstctrl,
                               clktrctrl_sw_wkup>::reg_msk<clktrctrl_mask>();
  while((mcal::reg::reg_access_static<std::uint32_t, std::uint32_t, mcal::reg::cm_wkup::clkstctrl>::reg_get() & clktrctrl_mask) != clktrctrl_sw_wkup) { mcal::cpu::nop(); }

  mcal::reg::reg_access_static<std::uint32_t,
                               std::uint32_t,
                               mcal::reg::cm_per::l3s_clkstctrl,
                               clktrctrl_sw_wkup>::reg_msk<clktrctrl_mask>();
  while((mcal::reg::reg_access_static<std::uint32_t, std::uint32_t, mcal::reg::cm_per::l3s_clkstctrl>::reg_get() & clktrctrl_mask) != clktrctrl_sw_wkup) { mcal::cpu::nop(); }
}

void osc_detail::emif_init()
{
  constexpr std::uint32_t clkactivity_emif_gclk = UINT32_C(0x00000004);

  // Enable the clocks for the emif.

  mcal::reg::reg_access_static<std::uint32_t,
                               std::uint32_t,
                               mcal::reg::cm_per::emif_clkctrl,
                               modulemode_enable>::reg_msk<modulemode_mask>();
  while((mcal::reg::reg_access_static<std::uint32_t, std::uint32_t, mcal::reg::cm_per::l3_clkstctrl>::reg_get() & clkactivity_emif_gclk) != clkactivity_emif_gclk) { mcal::cpu::nop(); }
}

void osc_detail::dm_timer7_clock_init()
{
  constexpr std::uint32_t clksel_clk_m_osc        = UINT32_C(1);
  constexpr std::uint32_t clkactivity_timer7_gclk = UINT32_C(0x00002000);

  // Select the clock source clksel_clk_m_osc for timer7.
  mcal::reg::reg_access_static<std::uint32_t,
                               std::uint32_t,
                               mcal::reg::cm_dpll::clksel_timer7_clk,
                               clksel_clk_m_osc>::reg_msk<UINT32_C(0x3)>();
  while((mcal::reg::reg_access_static<std::uint32_t, std::uint32_t, mcal::reg::cm_dpll::clksel_timer7_clk>::reg_get() & UINT32_C(0x3)) != clksel_clk_m_osc) { mcal::cpu::nop(); }

  mcal::reg::reg_access_static<std::uint32_t,
                               std::uint32_t,
                               mcal::reg::cm_per::timer7_clkctrl,
                               modulemode_enable>::reg_msk<modulemode_mask>();

  while((mcal::reg::reg_access_static<std::uint32_t, std::uint32_t, mcal::reg::cm_per::timer7_clkctrl>::reg_get() & modulemode_mask        ) != modulemode_enable      ) { mcal::cpu::nop(); }
  while((mcal::reg::reg_access_static<std::uint32_t, std::uint32_t, mcal::reg::cm_per::timer7_clkctrl>::reg_get() & idlest_mask            ) != idlest_func            ) { mcal::cpu::nop(); }
  while((mcal::reg::reg_access_static<std::uint32_t, std::uint32_t, mcal::reg::cm_per::l4ls_clkstctrl>::reg_get() & clkactivity_timer7_gclk) != clkactivity_timer7_gclk) { mcal::cpu::nop(); }
}

void mcal::osc::init(const config_type*)
{
  // Setup the clocks for oscillator, PLL, RAM, I/O ports, and peripherals.

  osc_detail::mpu_pll_init();
  osc_detail::core_pll_init();
  osc_detail::peripheral_pll_init();
  osc_detail::ddr_pll_init();
  osc_detail::interface_clock_init();
  osc_detail::power_domain_transition_init();

  mcal::reg::reg_access_static<std::uint32_t,
                               std::uint32_t,
                               mcal::reg::cm_wkup::control_clkctrl,
                               osc_detail::modulemode_enable>::reg_msk<osc_detail::modulemode_mask>();

  osc_detail::emif_init();
  osc_detail::dm_timer7_clock_init();
}
