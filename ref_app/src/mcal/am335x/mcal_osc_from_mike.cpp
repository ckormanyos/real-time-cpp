///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2013.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <cstdint>
#include <mcal_cpu.h>
#include <mcal_osc.h>
#include <mcal_reg_access.h>
#include <am335x_hw_regs.h>
#include <bfx.h>

constexpr std::uint32_t DPLL_MN_BYP_MODE          =      0x04UL;
constexpr std::uint32_t DPLL_LP_BYP_MODE          =      0x05UL;
constexpr std::uint32_t DPLL_FR_BYP_MODE          =      0x06UL;
constexpr std::uint32_t DPLL_LOCK_MODE            =      0x07UL;

constexpr std::uint32_t ST_MN_BYPASS              =     0x100UL;
constexpr std::uint32_t ST_DPLL_CLK               =       0x1UL;

constexpr std::uint32_t MODULEMODE_ENABLE         =      0x02UL;
constexpr std::uint32_t MODULEMODE_DISABLE        =      0x00UL;
constexpr std::uint32_t MODULEMODE_MASK           =      0x03UL;

constexpr std::uint32_t IDLEST_FUNC               = 0x00000000UL;
constexpr std::uint32_t IDLEST_TRANS              = 0x00010000UL;
constexpr std::uint32_t IDLEST_IDLE               = 0x00020000UL;
constexpr std::uint32_t IDLEST_DISABLE            = 0x00030000UL;
constexpr std::uint32_t IDLEST_MASK               = 0x00030000UL;

constexpr std::uint32_t CLKTRCTRL_NO_SLEEP        =        0x0UL;
constexpr std::uint32_t CLKTRCTRL_SW_SLEEP        =        0x1UL;
constexpr std::uint32_t CLKTRCTRL_SW_WKUP         =        0x2UL;
constexpr std::uint32_t CLKTRCTRL_HW_AUTO         =        0x3UL;
constexpr std::uint32_t CLKTRCTRL_MASK            =        0x3UL;

constexpr std::uint32_t CLKACTIVITY_EMIF_GCLK     = 0x00000004UL;
constexpr std::uint32_t CLKACTIVITY_GPIO_1_GDBCLK = 0x00080000UL;
constexpr std::uint32_t CLKACTIVITY_GPIO_2_GDBCLK = 0x00100000UL;
constexpr std::uint32_t CLKACTIVITY_GPIO_3_GDBCLK = 0x00200000UL;
constexpr std::uint32_t CLKACTIVITY_TIMER1_GCLK   = 0x00002000UL;
constexpr std::uint32_t CLKACTIVITY_TIMER7_GCLK   = 0x00002000UL;
constexpr std::uint32_t OPTFCLKEN_GPIO_1_GDBCLK   = 0x00040000UL;

constexpr std::uint32_t CLKSEL_CLK_M_OSC          =           1UL;
constexpr std::uint32_t CLKSEL_CLK_32KHZ          =           2UL;

constexpr std::uint32_t MCU_CLK_SETTING_HSI_PLL = 0x00UL;  // Internal oscillator with PLL
constexpr std::uint32_t MCU_CLK_SETTING_HSE_PLL = 0x01UL;  // External oscillator with PLL
constexpr std::uint32_t MCU_CLK_SETTING_HSI     = 0x02UL;  // Internal oscillator without PLL
constexpr std::uint32_t MCU_CLK_SETTING_HSE     = 0x03UL;  // External oscillator without PLL
constexpr std::uint32_t MCU_MODE_RUN            = 0x00UL;  // Normal run at full speed
constexpr std::uint32_t MCU_MODE_SLOW           = 0x01UL;  // Reduced speed mode running on internal 8MHz oscillator
constexpr std::uint32_t MCU_MODE_SLEEP          = 0x02UL;  // No cpu clock, peripherals running
constexpr std::uint32_t MCU_MODE_STOP           = 0x03UL;  // All clocks off, SRAM powered
constexpr std::uint32_t MCU_MODE_HALT           = 0x04UL;  // Only backup domain powered (RTC, LSE osc, BKP registers)

// CLKINP = 24MHz
// Setting MPU clock to 600MHz
// CLKOUT = [M / (N+1)] * CLKINP * [1/M2] = 600
constexpr std::uint32_t MCU_CLKINP      =    24UL;
constexpr std::uint32_t MCU_MPU_PLL_M   =   600UL;
constexpr std::uint32_t MCU_MPU_PLL_N   =    23UL;
constexpr std::uint32_t MCU_MPU_PLL_M2  =     1UL;

// CLKINP = 24MHz
// CLKDCOLDO = 2 * [M / (N+1)] * CLKINP = 2000
// CLKOUTM4 =  CLKDCOLDO / M4 = 200
// CLKOUTM5 =  CLKDCOLDO / M5 = 250
// CLKOUTM6 =  CLKDCOLDO / M6 = 500
constexpr std::uint32_t MCU_CORE_PLL_M  =  1000UL;
constexpr std::uint32_t MCU_CORE_PLL_N  =    23UL;
constexpr std::uint32_t MCU_CORE_PLL_M4 =    10UL;
constexpr std::uint32_t MCU_CORE_PLL_M5 =     8UL;
constexpr std::uint32_t MCU_CORE_PLL_M6 =     4UL;

// Setting Peripheral clock to 960MHz
// CLKINP = 24MHz
// CLKOUT    = (M / (N+1))*CLKINP*(1/M2) = 192
// CLKDCOLDO = (M / (N+1))*CLKINP = 960
constexpr std::uint32_t MCU_PER_PLL_M  =   960UL;
constexpr std::uint32_t MCU_PER_PLL_N  =    23UL;
constexpr std::uint32_t MCU_PER_PLL_M2 =     5UL;
constexpr std::uint32_t MCU_PER_PLL_SD =   (((MCU_PER_PLL_M/(MCU_PER_PLL_N + 1UL) * MCU_CLKINP) + 249UL) / 250UL);

// Setting DDR clock to 266
constexpr std::uint32_t MCU_DDR_PLL_M  =   266UL;
constexpr std::uint32_t MCU_DDR_PLL_N  =    23UL;
constexpr std::uint32_t MCU_DDR_PLL_M2 =     1UL;

void mpu_pll_init()
{
  // Put the PLL in bypass mode.
  bfx_clear_and_set_bit_mask((std::uint32_t*) &CM_WKUP->CLKMODE_DPLL_MPU,
                             DPLL_MN_BYP_MODE,
                             (std::uint32_t) 0x07UL);

  // Wait for DPLL to go in to bypass mode.
  while(!(CM_WKUP->IDLEST_DPLL_MPU & ST_MN_BYPASS)) { mcal::cpu::nop(); }

  // Set the multiplier and divider values for the PLL.
  bfx_clear_and_set_bit_mask((std::uint32_t*) &CM_WKUP->CLKSEL_DPLL_MPU,
                             std::uint32_t((MCU_MPU_PLL_M << 8) | (MCU_MPU_PLL_N)),
                             std::uint32_t(0x0007FF7FUL));

  // Set the M2 divider values for the PLL.
  bfx_clear_and_set_bit_mask((std::uint32_t*) &CM_WKUP->DIV_M2_DPLL_MPU,
                             MCU_MPU_PLL_M2,
                             0x0000003FUL);

  // Enable the PLL in lock mode.
  bfx_clear_and_set_bit_mask((std::uint32_t*) &CM_WKUP->CLKMODE_DPLL_MPU,
                             DPLL_LOCK_MODE,
                             0x07UL);

  // Wait for lock.
  while(!(CM_WKUP->IDLEST_DPLL_MPU & ST_DPLL_CLK)) { mcal::cpu::nop(); }
}

// Enable the Core PLL.
void core_pll_init(void)
{
  // Put the PLL in bypass mode.
  bfx_clear_and_set_bit_mask((std::uint32_t*) &CM_WKUP->CLKMODE_DPLL_CORE,
                             DPLL_MN_BYP_MODE,
                             0x07UL);

  // Wait for DPLL to go in to bypass mode.
  while(!(CM_WKUP->IDLEST_DPLL_CORE & ST_MN_BYPASS)) { mcal::cpu::nop(); }

  // Set the multiplier and divider values for the PLL.
  bfx_clear_and_set_bit_mask((std::uint32_t*) &CM_WKUP->CLKSEL_DPLL_CORE,
                             std::uint32_t((MCU_CORE_PLL_M << 8) | (MCU_CORE_PLL_N)),
                             std::uint32_t(0x0007FF7FUL));

  // Configure the High speed dividers.
  bfx_clear_and_set_bit_mask((std::uint32_t*) &CM_WKUP->DIV_M4_DPLL_CORE,
                             std::uint32_t(MCU_CORE_PLL_M4),
                             0x0000001FUL);
  bfx_clear_and_set_bit_mask((std::uint32_t*) &CM_WKUP->DIV_M5_DPLL_CORE,
                             std::uint32_t(MCU_CORE_PLL_M5),
                             0x0000001FUL);
  bfx_clear_and_set_bit_mask((std::uint32_t*) &CM_WKUP->DIV_M6_DPLL_CORE,
                             std::uint32_t(MCU_CORE_PLL_M6),
                             0x0000001FUL);

  // Enable the PLL in lock mode.
  bfx_clear_and_set_bit_mask((std::uint32_t*) &CM_WKUP->CLKMODE_DPLL_CORE,
                  std::uint32_t(DPLL_LOCK_MODE),
                  0x07UL);

  // Wait for lock.
  while(!(CM_WKUP->IDLEST_DPLL_CORE & ST_DPLL_CLK)) { mcal::cpu::nop(); }
}

void peripheral_pll_init(void)
{
  // Put the PLL in bypass mode.
  bfx_clear_and_set_bit_mask((std::uint32_t*) &CM_WKUP->CLKMODE_DPLL_PER,
                             std::uint32_t(DPLL_MN_BYP_MODE),
                             0x07UL);

  // Wait for DPLL to go in to bypass mode.
  while(!(CM_WKUP->IDLEST_DPLL_PER & ST_MN_BYPASS)) { mcal::cpu::nop(); }

  // Set the multiplier and divider values for the PLL.
  bfx_clear_and_set_bit_mask((std::uint32_t*) &CM_WKUP->CLKSEL_DPLL_PERIPH,
                             std::uint32_t((MCU_PER_PLL_SD << 24) | (MCU_PER_PLL_M << 8) | MCU_PER_PLL_N),
                             0xFF0FFFFFUL);

  // Set the M2 divider values for the PLL.
  bfx_clear_and_set_bit_mask((std::uint32_t*) &CM_WKUP->DIV_M2_DPLL_PER,
                             std::uint32_t(MCU_PER_PLL_M2),
                             0x0000003FUL);

  // Enable the PLL in lock mode.
  bfx_clear_and_set_bit_mask((std::uint32_t*) &CM_WKUP->CLKMODE_DPLL_PER,
                             std::uint32_t(DPLL_LOCK_MODE),
                             0x07UL);

  // Wait for lock.
  while(!(CM_WKUP->IDLEST_DPLL_PER & ST_DPLL_CLK)) { mcal::cpu::nop(); }
}

void ddr_pll_init(void)
{
  // Put the PLL in bypass mode.
  bfx_clear_and_set_bit_mask((std::uint32_t*) &CM_WKUP->CLKMODE_DPLL_DDR,
                             std::uint32_t(DPLL_MN_BYP_MODE),
                             0x07UL);

  // Wait for DPLL to go in to bypass mode.
  while(!(CM_WKUP->IDLEST_DPLL_DDR & ST_MN_BYPASS)) { mcal::cpu::nop(); }

  // Set the multiplier and divider values for the PLL.
  bfx_clear_and_set_bit_mask((std::uint32_t*) &CM_WKUP->CLKSEL_DPLL_DDR,
                             std::uint32_t((MCU_DDR_PLL_M << 8) | MCU_DDR_PLL_N),
                             0x0007FF7FUL);

  // Set the M2 divider values for the PLL.
  bfx_clear_and_set_bit_mask((std::uint32_t*) &CM_WKUP->DIV_M2_DPLL_DDR,
                             std::uint32_t(MCU_DDR_PLL_M2),
                             0x0000003FUL);

  // Enable the PLL in lock mode.
  bfx_clear_and_set_bit_mask((std::uint32_t*) &CM_WKUP->CLKMODE_DPLL_DDR,
                             std::uint32_t(DPLL_LOCK_MODE),
                             0x07UL);

  // Wait for lock.
  while(!(CM_WKUP->IDLEST_DPLL_DDR & ST_DPLL_CLK)) { mcal::cpu::nop(); }
}

void interface_clock_init(void)
{
  bfx_clear_and_set_bit_mask((std::uint32_t*) &CM_PER->L3_CLKCTRL,
                             MODULEMODE_ENABLE,
                             MODULEMODE_MASK);
  while((CM_PER->L3_CLKCTRL & MODULEMODE_MASK) != MODULEMODE_ENABLE) { mcal::cpu::nop(); }

  bfx_clear_and_set_bit_mask((std::uint32_t*) &CM_PER->L4LS_CLKCTRL,
                             MODULEMODE_ENABLE,
                             MODULEMODE_MASK);
  while((CM_PER->L4LS_CLKCTRL & MODULEMODE_MASK) != MODULEMODE_ENABLE) { mcal::cpu::nop(); }

  bfx_clear_and_set_bit_mask((std::uint32_t*) &CM_PER->L4FW_CLKCTRL,
                             MODULEMODE_ENABLE,
                             MODULEMODE_MASK);
  while((CM_PER->L4FW_CLKCTRL & MODULEMODE_MASK) != MODULEMODE_ENABLE) { mcal::cpu::nop(); }

  // TODO: delete this, read-only register
  bfx_clear_and_set_bit_mask((std::uint32_t*) &CM_WKUP->L4WKUP_CLKCTRL,
                             MODULEMODE_ENABLE,
                             MODULEMODE_MASK);
  while((CM_WKUP->L4WKUP_CLKCTRL & MODULEMODE_MASK) != MODULEMODE_ENABLE) { mcal::cpu::nop(); }

  bfx_clear_and_set_bit_mask((std::uint32_t*) &CM_PER->L3_INSTR_CLKCTRL,
                             MODULEMODE_ENABLE,
                             MODULEMODE_MASK);
  while((CM_PER->L3_INSTR_CLKCTRL & MODULEMODE_MASK) != MODULEMODE_ENABLE) { mcal::cpu::nop(); }

  bfx_clear_and_set_bit_mask((std::uint32_t*) &CM_PER->L4HS_CLKCTRL,
                             MODULEMODE_ENABLE,
                             MODULEMODE_MASK);
  while((CM_PER->L4HS_CLKCTRL & MODULEMODE_MASK) != MODULEMODE_ENABLE) { mcal::cpu::nop(); }
}

void power_domain_transition_init(void)
{
  bfx_clear_and_set_bit_mask((std::uint32_t*) &CM_PER->L3_CLKSTCTRL,
                             CLKTRCTRL_SW_WKUP,
                             CLKTRCTRL_MASK);
  while((CM_PER->L3_CLKSTCTRL & CLKTRCTRL_MASK) != CLKTRCTRL_SW_WKUP) { mcal::cpu::nop(); }

  bfx_clear_and_set_bit_mask((std::uint32_t*) &CM_PER->L4LS_CLKSTCTRL,
                             CLKTRCTRL_SW_WKUP,
                             CLKTRCTRL_MASK);
  while((CM_PER->L4LS_CLKSTCTRL & CLKTRCTRL_MASK) != CLKTRCTRL_SW_WKUP) { mcal::cpu::nop(); }

  bfx_clear_and_set_bit_mask((std::uint32_t*) &CM_WKUP->CLKSTCTRL,
                             CLKTRCTRL_SW_WKUP,
                             CLKTRCTRL_MASK);
  while((CM_WKUP->CLKSTCTRL & CLKTRCTRL_MASK) != CLKTRCTRL_SW_WKUP) { mcal::cpu::nop(); }

  // TODO: register doesn't exist in TRM
  // bfx_clear_and_set_bit_mask((std::uint32_t*) &CM_PER->L4FW_CLKSTCTRL, CLKTRCTRL_SW_WKUP, CLKTRCTRL_MASK);

  bfx_clear_and_set_bit_mask((std::uint32_t*) &CM_PER->L3S_CLKSTCTRL,
                             CLKTRCTRL_SW_WKUP,
                             CLKTRCTRL_MASK);
  while((CM_PER->L3S_CLKSTCTRL & CLKTRCTRL_MASK) != CLKTRCTRL_SW_WKUP) { mcal::cpu::nop(); }
}

void emif_init(void)
{
  // Enable the clocks for EMIF.
  // TODO: register doesn't exist in TRM
  // bfx_clear_and_set_bit_mask((std::uint32_t*) &CM_PER->EMIF_FW_CLKCTRL, MODULEMODE_ENABLE, MODULEMODE_MASK);
  bfx_clear_and_set_bit_mask((std::uint32_t*) &CM_PER->EMIF_CLKCTRL,
                             MODULEMODE_ENABLE,
                             MODULEMODE_MASK);
  while((CM_PER->L3_CLKSTCTRL & CLKACTIVITY_EMIF_GCLK) != CLKACTIVITY_EMIF_GCLK) { mcal::cpu::nop(); }
}

void gpio1_clock_config(void)
{
  // Writing to MODULEMODE field of CM_PER_GPIO1_CLKCTRL register.
  bfx_clear_and_set_bit_mask((std::uint32_t*) &CM_PER->GPIO1_CLKCTRL,
                             MODULEMODE_ENABLE,
                             MODULEMODE_MASK);
  while((CM_PER->GPIO1_CLKCTRL & MODULEMODE_MASK) != MODULEMODE_ENABLE) { mcal::cpu::nop(); }

  // Enable optional function clock.
  bfx_clear_and_set_bit_mask((std::uint32_t*) &CM_PER->GPIO1_CLKCTRL,
                             OPTFCLKEN_GPIO_1_GDBCLK,
                             OPTFCLKEN_GPIO_1_GDBCLK);
  // TODO: ist OPTFCLKEN_GPIO_1_GDBCLK ein Statusregister?

  while(OPTFCLKEN_GPIO_1_GDBCLK != (CM_PER->GPIO1_CLKCTRL & OPTFCLKEN_GPIO_1_GDBCLK)) { mcal::cpu::nop(); }
  while(IDLEST_FUNC != (CM_PER->GPIO1_CLKCTRL & IDLEST_MASK)) { mcal::cpu::nop(); }
  while(CLKACTIVITY_GPIO_1_GDBCLK !=   (CM_PER->L4LS_CLKSTCTRL & CLKACTIVITY_GPIO_1_GDBCLK)) { mcal::cpu::nop(); }
}

void Mcu_DMTimer1ClkConfig(void)
{
  // Select the clock source CLK_32KHZ for the Timer1 instance.
  bfx_clear_and_set_bit_mask((std::uint32_t*) &CM_DPLL->CLKSEL_TIMER1MS_CLK,
                             std::uint32_t(1UL),
                             0x07UL);

  bfx_clear_and_set_bit_mask((std::uint32_t*) &CM_WKUP->TIMER1_CLKCTRL,
                             MODULEMODE_ENABLE,
                             MODULEMODE_MASK);
  while((CM_WKUP->TIMER1_CLKCTRL & MODULEMODE_MASK) != MODULEMODE_ENABLE) { mcal::cpu::nop(); }

  while(IDLEST_FUNC != (CM_WKUP->TIMER1_CLKCTRL & IDLEST_MASK)) { mcal::cpu::nop(); }
  while(CLKACTIVITY_TIMER1_GCLK != (CM_WKUP->CLKSTCTRL & CLKACTIVITY_TIMER1_GCLK)) { mcal::cpu::nop(); }
}

void dm_timer7_clock_config(void)
{
  // Select the clock source CLKSEL_CLK_M_OSC for the Timer7 instance.
  bfx_clear_and_set_bit_mask((std::uint32_t*) &CM_DPLL->CLKSEL_TIMER7_CLK,
                             std::uint32_t(CLKSEL_CLK_M_OSC),
                             std::uint32_t(0x3UL));
  while((CM_DPLL->CLKSEL_TIMER7_CLK & 0x3u) != CLKSEL_CLK_M_OSC) { mcal::cpu::nop(); }

  bfx_clear_and_set_bit_mask((std::uint32_t*) &CM_PER->TIMER7_CLKCTRL,
                             std::uint32_t(MODULEMODE_ENABLE),
                             std::uint32_t(MODULEMODE_MASK));
  while((CM_PER->TIMER7_CLKCTRL & MODULEMODE_MASK) != MODULEMODE_ENABLE) { mcal::cpu::nop(); }

  while(IDLEST_FUNC != (CM_PER->TIMER7_CLKCTRL & IDLEST_MASK)) { mcal::cpu::nop(); }
  while(CLKACTIVITY_TIMER7_GCLK != (CM_PER->L4LS_CLKSTCTRL & CLKACTIVITY_TIMER7_GCLK)) { mcal::cpu::nop(); }
}

void mcal::osc::init(const config_type*)
{
  // Setup the clocks, PLL and RAM.
  mpu_pll_init();
  core_pll_init();
  peripheral_pll_init();
  ddr_pll_init();
  interface_clock_init();
  power_domain_transition_init();

  bfx_clear_and_set_bit_mask((std::uint32_t*) &CM_WKUP->CONTROL_CLKCTRL,
                             MODULEMODE_ENABLE,
                             MODULEMODE_MASK);

  emif_init();

  gpio1_clock_config();
  dm_timer7_clock_config();
}
