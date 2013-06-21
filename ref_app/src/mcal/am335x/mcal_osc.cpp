///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2013.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <cstdint>
#include <am335x_hw_regs.h>
#include <bfx.h>
#include <mcal_osc.h>
#include <mcal_reg_access.h>

// *****************************************************************************
// constants
// *****************************************************************************
#define VECT_TAB_OFFSET  0x0 /*!< Vector Table base offset field.
                                  This value must be a multiple of 0x200. */

constexpr std::uint32_t DPLL_MN_BYP_MODE = 0x04UL;
constexpr std::uint32_t DPLL_LP_BYP_MODE = 0x05UL;
constexpr std::uint32_t DPLL_FR_BYP_MODE = 0x06UL;
constexpr std::uint32_t DPLL_LOCK_MODE   = 0x07UL;

constexpr std::uint32_t ST_MN_BYPASS = 0x100u;
constexpr std::uint32_t ST_DPLL_CLK  = 0x1u;

constexpr std::uint32_t MODULEMODE_ENABLE   = 0x02u;
constexpr std::uint32_t MODULEMODE_DISABLE  = 0x00u;
constexpr std::uint32_t MODULEMODE_MASK     = 0x03u;

constexpr std::uint32_t IDLEST_FUNC    (0x00000000u);
constexpr std::uint32_t IDLEST_TRANS   (0x00010000u);
constexpr std::uint32_t IDLEST_IDLE    (0x00020000u);
constexpr std::uint32_t IDLEST_DISABLE (0x00030000u);
constexpr std::uint32_t IDLEST_MASK    (0x00030000u);

constexpr std::uint32_t CLKTRCTRL_NO_SLEEP = 0x0u;
constexpr std::uint32_t CLKTRCTRL_SW_SLEEP = 0x1u;
constexpr std::uint32_t CLKTRCTRL_SW_WKUP  = 0x2u;
constexpr std::uint32_t CLKTRCTRL_HW_AUTO  = 0x3u;
constexpr std::uint32_t CLKTRCTRL_MASK     = 0x3u;

constexpr std::uint32_t CLKACTIVITY_EMIF_GCLK      (0x00000004u);
constexpr std::uint32_t CLKACTIVITY_GPIO_1_GDBCLK  (0x00080000u);
constexpr std::uint32_t CLKACTIVITY_GPIO_2_GDBCLK  (0x00100000u);
constexpr std::uint32_t CLKACTIVITY_GPIO_3_GDBCLK  (0x00200000u);
constexpr std::uint32_t CLKACTIVITY_TIMER1_GCLK    (0x00002000u);
constexpr std::uint32_t CLKACTIVITY_TIMER7_GCLK    (0x00002000u);
constexpr std::uint32_t OPTFCLKEN_GPIO_1_GDBCLK    (0x00040000u);

constexpr std::uint32_t CLKSEL_CLK_M_OSC  = 1u;
constexpr std::uint32_t CLKSEL_CLK_32KHZ  = 2u;

typedef void Mcu_ConfigType;

typedef enum
{
  MCU_PLL_LOCKED = 0, //!< PLL locked
  MCU_PLL_UNLOCKED, //!< PLL unlocked
  MCU_PLL_STATUS_UNDEFINED //!< status of PLL undefined
} Mcu_PllStatusType;

typedef std::uint_least8_t Mcu_ClockType;

typedef std::uint32_t       Mcu_RawResetType;
typedef std::uint_least8_t  Mcu_ModeType;
typedef std::uint_least8_t  Mcu_RamSectionType;

typedef enum enum_Mcu_InitState
{
  MCU_UNINIT,
  MCU_INIT
}
Mcu_InitState;

// *****************************************************************************
// constants
// *****************************************************************************
constexpr Mcu_ClockType MCU_CLK_SETTING_HSI_PLL = (Mcu_ClockType) 0x00;  /*!< Internal oscillator with PLL */
constexpr Mcu_ClockType MCU_CLK_SETTING_HSE_PLL = (Mcu_ClockType) 0x01;  /*!< External oscillator with PLL */
constexpr Mcu_ClockType MCU_CLK_SETTING_HSI     = (Mcu_ClockType) 0x02;  /*!< Internal oscillator without PLL */
constexpr Mcu_ClockType MCU_CLK_SETTING_HSE     = (Mcu_ClockType) 0x03;  /*!< External oscillator without PLL */
constexpr Mcu_ModeType  MCU_MODE_RUN            = (Mcu_ModeType)  0x00;  /*!< Normal run at full speed */
constexpr Mcu_ModeType  MCU_MODE_SLOW           = (Mcu_ModeType)  0x01;  /*!< Reduced speed mode running on internal 8MHz oscillator */
constexpr Mcu_ModeType  MCU_MODE_SLEEP          = (Mcu_ModeType)  0x02;  /*!< No cpu clock, peripherals running */
constexpr Mcu_ModeType  MCU_MODE_STOP           = (Mcu_ModeType)  0x03;  /*!< All clocks off, SRAM powered */
constexpr Mcu_ModeType  MCU_MODE_HALT           = (Mcu_ModeType)  0x04;  /*!< Only backup domain powered (RTC, LSE osc, BKP registers) */

// CLKINP = 24MHz
constexpr std::uint32_t MCU_CLKINP = 24;
// Setting MPU clock to 600MHz
// CLKOUT = [M / (N+1)] * CLKINP * [1/M2] = 600
constexpr std::uint32_t MCU_MPU_PLL_M  =  600;
constexpr std::uint32_t MCU_MPU_PLL_N  =  23;
constexpr std::uint32_t MCU_MPU_PLL_M2 =   1;

// CLKINP = 24MHz
// CLKDCOLDO = 2 * [M / (N+1)] * CLKINP = 2000
// CLKOUTM4 =  CLKDCOLDO / M4 = 200
// CLKOUTM5 =  CLKDCOLDO / M5 = 250
// CLKOUTM6 =  CLKDCOLDO / M6 = 500
constexpr std::uint32_t MCU_CORE_PLL_M  =  1000;
constexpr std::uint32_t MCU_CORE_PLL_N  =  23;
constexpr std::uint32_t MCU_CORE_PLL_M4 = 10;
constexpr std::uint32_t MCU_CORE_PLL_M5 = 8;
constexpr std::uint32_t MCU_CORE_PLL_M6 = 4;

// Setting Peripheral clock to 960MHz
// CLKINP = 24MHz
// CLKOUT    = (M / (N+1))*CLKINP*(1/M2) = 192
// CLKDCOLDO = (M / (N+1))*CLKINP = 960
constexpr std::uint32_t MCU_PER_PLL_M  =  960;
constexpr std::uint32_t MCU_PER_PLL_N  =  23;
constexpr std::uint32_t MCU_PER_PLL_M2 =   5;
constexpr std::uint32_t MCU_PER_PLL_SD =   (((MCU_PER_PLL_M/(MCU_PER_PLL_N + 1) * MCU_CLKINP) + 249) / 250);

// Setting DDR clock to 266
constexpr std::uint32_t MCU_DDR_PLL_M  =  266;
constexpr std::uint32_t MCU_DDR_PLL_N  =  23;
constexpr std::uint32_t MCU_DDR_PLL_M2 =   1;

// *****************************************************************************
// macros
// *****************************************************************************


// *****************************************************************************
// global and static variables
// *****************************************************************************

std::uint8_t McalMcu_ucResetReason;

Mcu_ClockType Mcu_ClockSetting;
static Mcu_InitState Mcu_eInit = MCU_UNINIT;

// *****************************************************************************
// functions
// *****************************************************************************

void Mcu_MPUPLLInit(void)
{
  /* Put the PLL in bypass mode */
  Bfx_PutBitsMask((std::uint32_t*) &CM_WKUP->CLKMODE_DPLL_MPU, DPLL_MN_BYP_MODE, (std::uint32_t) 0x07u);

  /* Wait for DPLL to go in to bypass mode */
  while(!(CM_WKUP->IDLEST_DPLL_MPU & ST_MN_BYPASS));

  /* Set the multiplier and divider values for the PLL */
  Bfx_PutBitsMask((std::uint32_t*) &CM_WKUP->CLKSEL_DPLL_MPU,
                  std::uint32_t((MCU_MPU_PLL_M << 8) | (MCU_MPU_PLL_N)),
                  std::uint32_t(0x0007FF7FUL));

  /* Set the M2 divider values for the PLL */
  Bfx_PutBitsMask((std::uint32_t*) &CM_WKUP->DIV_M2_DPLL_MPU,
                  std::uint32_t(MCU_MPU_PLL_M2),
                  std::uint32_t(0x0000003FUL));

  /* Enable the PLL in lock mode */
  Bfx_PutBitsMask((std::uint32_t*) &CM_WKUP->CLKMODE_DPLL_MPU,
                  std::uint32_t(DPLL_LOCK_MODE),
                  std::uint32_t(0x07UL));

  /* Wait for lock */
  while(!(CM_WKUP->IDLEST_DPLL_MPU & ST_DPLL_CLK))
  {
    ;
  }
}

/* Enable the Core PLL */
void Mcu_CorePLLInit(void)
{
  /* Put the PLL in bypass mode */
  Bfx_PutBitsMask((std::uint32_t*) &CM_WKUP->CLKMODE_DPLL_CORE,
                  std::uint32_t(DPLL_MN_BYP_MODE),
                  std::uint32_t(0x07UL));

  /* Wait for DPLL to go in to bypass mode */
  while(!(CM_WKUP->IDLEST_DPLL_CORE & ST_MN_BYPASS))
  {
    ;
  }

  /* Set the multiplier and divider values for the PLL */
  Bfx_PutBitsMask((std::uint32_t*) &CM_WKUP->CLKSEL_DPLL_CORE,
                  std::uint32_t((MCU_CORE_PLL_M << 8) | (MCU_CORE_PLL_N)),
                  std::uint32_t(0x0007FF7FUL));

  /* Configure the High speed dividers */
  Bfx_PutBitsMask((std::uint32_t*) &CM_WKUP->DIV_M4_DPLL_CORE,
                  std::uint32_t(MCU_CORE_PLL_M4),
                  std::uint32_t(0x0000001FUL));
  Bfx_PutBitsMask((std::uint32_t*) &CM_WKUP->DIV_M5_DPLL_CORE,
                  std::uint32_t(MCU_CORE_PLL_M5),
                  std::uint32_t(0x0000001FUL));
  Bfx_PutBitsMask((std::uint32_t*) &CM_WKUP->DIV_M6_DPLL_CORE,
                  std::uint32_t(MCU_CORE_PLL_M6),
                  std::uint32_t(0x0000001FUL));

  /* Enable the PLL in lock mode */
  Bfx_PutBitsMask((std::uint32_t*) &CM_WKUP->CLKMODE_DPLL_CORE,
                  std::uint32_t(DPLL_LOCK_MODE),
                  std::uint32_t(0x07UL));

  /* Wait for lock */
  while(!(CM_WKUP->IDLEST_DPLL_CORE & ST_DPLL_CLK))
  {
    ;
  }
}

void Mcu_PerPLLInit(void)
{
  /* Put the PLL in bypass mode */
  Bfx_PutBitsMask((std::uint32_t*) &CM_WKUP->CLKMODE_DPLL_PER,
                  std::uint32_t(DPLL_MN_BYP_MODE),
                  std::uint32_t(0x07UL));

  /* Wait for DPLL to go in to bypass mode */
  while(!(CM_WKUP->IDLEST_DPLL_PER & ST_MN_BYPASS))
  {
    ;
  }

  /* Set the multiplier and divider values for the PLL */
  Bfx_PutBitsMask((std::uint32_t*) &CM_WKUP->CLKSEL_DPLL_PERIPH,
                  std::uint32_t((MCU_PER_PLL_SD << 24) | (MCU_PER_PLL_M << 8) | MCU_PER_PLL_N),
                  std::uint32_t(0xFF0FFFFFUL));

  /* Set the M2 divider values for the PLL */
  Bfx_PutBitsMask((std::uint32_t*) &CM_WKUP->DIV_M2_DPLL_PER,
                  std::uint32_t(MCU_PER_PLL_M2),
                  std::uint32_t(0x0000003FUL));

  /* Enable the PLL in lock mode */
  Bfx_PutBitsMask((std::uint32_t*) &CM_WKUP->CLKMODE_DPLL_PER,
                  std::uint32_t(DPLL_LOCK_MODE),
                  std::uint32_t(0x07UL));

  /* Wait for lock */
  while(!(CM_WKUP->IDLEST_DPLL_PER & ST_DPLL_CLK))
  {
    ;
  }
}

/* \brief This function initializes the DDR PLL
 *
 * \param none
 *
 * \return none
 *
 */
void Mcu_DDRPLLInit(void)
{
  /* Put the PLL in bypass mode */
  Bfx_PutBitsMask((std::uint32_t*) &CM_WKUP->CLKMODE_DPLL_DDR,
                  std::uint32_t(DPLL_MN_BYP_MODE),
                  std::uint32_t(0x07UL));

  /* Wait for DPLL to go in to bypass mode */
  while(!(CM_WKUP->IDLEST_DPLL_DDR & ST_MN_BYPASS))
  {
    ;
  }

  /* Set the multiplier and divider values for the PLL */
  Bfx_PutBitsMask((std::uint32_t*) &CM_WKUP->CLKSEL_DPLL_DDR,
                  std::uint32_t((MCU_DDR_PLL_M << 8) | MCU_DDR_PLL_N),
                  std::uint32_t(0x0007FF7FUL));

  /* Set the M2 divider values for the PLL */
  Bfx_PutBitsMask((std::uint32_t*) &CM_WKUP->DIV_M2_DPLL_DDR,
                  std::uint32_t(MCU_DDR_PLL_M2),
                  std::uint32_t(0x0000003FUL));

  /* Enable the PLL in lock mode */
  Bfx_PutBitsMask((std::uint32_t*) &CM_WKUP->CLKMODE_DPLL_DDR,
                  std::uint32_t(DPLL_LOCK_MODE),
                  std::uint32_t(0x07UL));

  /* Wait for lock */
  while(!(CM_WKUP->IDLEST_DPLL_DDR & ST_DPLL_CLK))
  {
    ;
  }
}

void Mcu_InterfaceClkInit(void)
{
  Bfx_PutBitsMask((std::uint32_t*) &CM_PER->L3_CLKCTRL, MODULEMODE_ENABLE, MODULEMODE_MASK);
  while((CM_PER->L3_CLKCTRL & MODULEMODE_MASK) != MODULEMODE_ENABLE) { ; }

  Bfx_PutBitsMask((std::uint32_t*) &CM_PER->L4LS_CLKCTRL, MODULEMODE_ENABLE, MODULEMODE_MASK);
  while((CM_PER->L4LS_CLKCTRL & MODULEMODE_MASK) != MODULEMODE_ENABLE) { ; }

  Bfx_PutBitsMask((std::uint32_t*) &CM_PER->L4FW_CLKCTRL, MODULEMODE_ENABLE, MODULEMODE_MASK);
  while((CM_PER->L4FW_CLKCTRL & MODULEMODE_MASK) != MODULEMODE_ENABLE) { ; }

  // TODO: delete this, read-only register
  Bfx_PutBitsMask((std::uint32_t*) &CM_WKUP->L4WKUP_CLKCTRL, MODULEMODE_ENABLE, MODULEMODE_MASK);
  while((CM_WKUP->L4WKUP_CLKCTRL & MODULEMODE_MASK) != MODULEMODE_ENABLE) { ; }

  Bfx_PutBitsMask((std::uint32_t*) &CM_PER->L3_INSTR_CLKCTRL, MODULEMODE_ENABLE, MODULEMODE_MASK);
  while((CM_PER->L3_INSTR_CLKCTRL & MODULEMODE_MASK) != MODULEMODE_ENABLE) { ; }

  Bfx_PutBitsMask((std::uint32_t*) &CM_PER->L4HS_CLKCTRL, MODULEMODE_ENABLE, MODULEMODE_MASK);
  while((CM_PER->L4HS_CLKCTRL & MODULEMODE_MASK) != MODULEMODE_ENABLE) { ; }
}

void Mcu_PowerDomainTransitionInit(void)
{
  Bfx_PutBitsMask((std::uint32_t*) &CM_PER->L3_CLKSTCTRL, CLKTRCTRL_SW_WKUP, CLKTRCTRL_MASK);
  while((CM_PER->L3_CLKSTCTRL & CLKTRCTRL_MASK) != CLKTRCTRL_SW_WKUP);
  Bfx_PutBitsMask((std::uint32_t*) &CM_PER->L4LS_CLKSTCTRL, CLKTRCTRL_SW_WKUP, CLKTRCTRL_MASK);
  while((CM_PER->L4LS_CLKSTCTRL & CLKTRCTRL_MASK) != CLKTRCTRL_SW_WKUP);
  Bfx_PutBitsMask((std::uint32_t*) &CM_WKUP->CLKSTCTRL, CLKTRCTRL_SW_WKUP, CLKTRCTRL_MASK);
  while((CM_WKUP->CLKSTCTRL & CLKTRCTRL_MASK) != CLKTRCTRL_SW_WKUP);

  // TODO: register doesn't exist in TRM
  // Bfx_PutBitsMask((std::uint32_t*) &CM_PER->L4FW_CLKSTCTRL, CLKTRCTRL_SW_WKUP, CLKTRCTRL_MASK);

  Bfx_PutBitsMask((std::uint32_t*) &CM_PER->L3S_CLKSTCTRL, CLKTRCTRL_SW_WKUP, CLKTRCTRL_MASK);
  while((CM_PER->L3S_CLKSTCTRL & CLKTRCTRL_MASK) != CLKTRCTRL_SW_WKUP);
}

void Mcu_EMIFInit(void)
{
  /* Enable the clocks for EMIF */
  // TODO: register doesn't exist in TRM
  // Bfx_PutBitsMask((std::uint32_t*) &CM_PER->EMIF_FW_CLKCTRL, MODULEMODE_ENABLE, MODULEMODE_MASK);
  Bfx_PutBitsMask((std::uint32_t*) &CM_PER->EMIF_CLKCTRL, MODULEMODE_ENABLE, MODULEMODE_MASK);
  while((CM_PER->L3_CLKSTCTRL & CLKACTIVITY_EMIF_GCLK) != CLKACTIVITY_EMIF_GCLK);
}

void Mcu_GPIO1ClkConfig(void)
{
  /* Writing to MODULEMODE field of CM_PER_GPIO1_CLKCTRL register. */
  Bfx_PutBitsMask((std::uint32_t*) &CM_PER->GPIO1_CLKCTRL, MODULEMODE_ENABLE, MODULEMODE_MASK);
  while((CM_PER->GPIO1_CLKCTRL & MODULEMODE_MASK) != MODULEMODE_ENABLE);

  /* Enable optional function clock */
  Bfx_PutBitsMask((std::uint32_t*) &CM_PER->GPIO1_CLKCTRL, OPTFCLKEN_GPIO_1_GDBCLK, OPTFCLKEN_GPIO_1_GDBCLK);
  // TODO: ist OPTFCLKEN_GPIO_1_GDBCLK ein Statusregister?
  while(OPTFCLKEN_GPIO_1_GDBCLK != (CM_PER->GPIO1_CLKCTRL & OPTFCLKEN_GPIO_1_GDBCLK));
  while(IDLEST_FUNC != (CM_PER->GPIO1_CLKCTRL & IDLEST_MASK));
  while(CLKACTIVITY_GPIO_1_GDBCLK !=   (CM_PER->L4LS_CLKSTCTRL & CLKACTIVITY_GPIO_1_GDBCLK));
}

void Mcu_DMTimer1ClkConfig(void)
{
    /* Select the clock source CLK_32KHZ for the Timer1 instance. */
  Bfx_PutBitsMask((std::uint32_t*) &CM_DPLL->CLKSEL_TIMER1MS_CLK,
                  std::uint32_t(1UL),
                  std::uint32_t(0x7UL));

  Bfx_PutBitsMask((std::uint32_t*) &CM_WKUP->TIMER1_CLKCTRL, MODULEMODE_ENABLE, MODULEMODE_MASK);
  while((CM_WKUP->TIMER1_CLKCTRL & MODULEMODE_MASK) != MODULEMODE_ENABLE) { ; }

  while(IDLEST_FUNC != (CM_WKUP->TIMER1_CLKCTRL & IDLEST_MASK)) { ; }
  while(CLKACTIVITY_TIMER1_GCLK != (CM_WKUP->CLKSTCTRL & CLKACTIVITY_TIMER1_GCLK)) { ; }
}

void Mcu_DMTimer7ClkConfig(void)
{
    /* Select the clock source CLKSEL_CLK_M_OSC for the Timer7 instance. */
  Bfx_PutBitsMask((std::uint32_t*) &CM_DPLL->CLKSEL_TIMER7_CLK,
                  std::uint32_t(CLKSEL_CLK_M_OSC),
                  std::uint32_t(0x3UL));
  while((CM_DPLL->CLKSEL_TIMER7_CLK & 0x3u) != CLKSEL_CLK_M_OSC);

  Bfx_PutBitsMask((std::uint32_t*) &CM_PER->TIMER7_CLKCTRL,
                  std::uint32_t(MODULEMODE_ENABLE),
                  std::uint32_t(MODULEMODE_MASK));
  while((CM_PER->TIMER7_CLKCTRL & MODULEMODE_MASK) != MODULEMODE_ENABLE);

  while(IDLEST_FUNC != (CM_PER->TIMER7_CLKCTRL & IDLEST_MASK));
  while(CLKACTIVITY_TIMER7_GCLK != (CM_PER->L4LS_CLKSTCTRL & CLKACTIVITY_TIMER7_GCLK));
}


/*! \brief Initialize Microcontroller abstraction for MCU unit
 *
 * \param ConfigPtr pointer to configuration data
 *
 * Set up clock, PLL and RAM.
 */
void Mcu_Init()
{
  Mcu_MPUPLLInit();
  Mcu_CorePLLInit();
  Mcu_PerPLLInit();
  Mcu_DDRPLLInit();
  Mcu_InterfaceClkInit();
  Mcu_PowerDomainTransitionInit();
  //    Mcu_DisplayPLLInit();

  Bfx_PutBitsMask((std::uint32_t*) &CM_WKUP->CONTROL_CLKCTRL,
                  std::uint32_t(MODULEMODE_ENABLE),
                  std::uint32_t(MODULEMODE_MASK));

  Mcu_EMIFInit();

  Mcu_GPIO1ClkConfig();
  Mcu_DMTimer7ClkConfig();

  Mcu_eInit = MCU_INIT;
}


void mcal::osc::init(const config_type*)
{
  Mcu_Init();
}
