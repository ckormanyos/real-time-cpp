///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2022.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef FROM_PERIPH_DRIVER_2022_08_08_H_
  #define FROM_PERIPH_DRIVER_2022_08_08_H_

  #if defined(__cplusplus)
  #include <cstdint>
  #else
  #include <stdint.h>
  #endif

  // FLASH_Latency FLASH Latency
  #define FLASH_LATENCY_0          FLASH_ACR_LATENCY_0WS   /* FLASH Zero Latency cycle      */
  #define FLASH_LATENCY_1          FLASH_ACR_LATENCY_1WS   /* FLASH One Latency cycle       */
  #define FLASH_LATENCY_2          FLASH_ACR_LATENCY_2WS   /* FLASH Two Latency cycles      */
  #define FLASH_LATENCY_3          FLASH_ACR_LATENCY_3WS   /* FLASH Three Latency cycles    */
  #define FLASH_LATENCY_4          FLASH_ACR_LATENCY_4WS   /* FLASH Four Latency cycles     */
  #define FLASH_LATENCY_5          FLASH_ACR_LATENCY_5WS   /* FLASH Five Latency cycles     */
  #define FLASH_LATENCY_6          FLASH_ACR_LATENCY_6WS   /* FLASH Six Latency cycles      */
  #define FLASH_LATENCY_7          FLASH_ACR_LATENCY_7WS   /* FLASH Seven Latency cycles    */

  // Bit definitions for FLASH_ACR register.
  #define FLASH_ACR_LATENCY_Pos                (0U)
  #define FLASH_ACR_LATENCY_Msk                (0xFUL << FLASH_ACR_LATENCY_Pos)             /* 0x0000000F: bit4 is kept only for legacy purpose */
  #define FLASH_ACR_LATENCY                    FLASH_ACR_LATENCY_Msk                        /* Read Latency */
  #define FLASH_ACR_LATENCY_0WS                (0x00000000UL)
  #define FLASH_ACR_LATENCY_1WS                (0x00000001UL)
  #define FLASH_ACR_LATENCY_2WS                (0x00000002UL)
  #define FLASH_ACR_LATENCY_3WS                (0x00000003UL)
  #define FLASH_ACR_LATENCY_4WS                (0x00000004UL)
  #define FLASH_ACR_LATENCY_5WS                (0x00000005UL)
  #define FLASH_ACR_LATENCY_6WS                (0x00000006UL)
  #define FLASH_ACR_LATENCY_7WS                (0x00000007UL)

  #define FLASH_LATENCY_DEFAULT                FLASH_ACR_LATENCY_3WS

  //  Bit definitions for RCC_CR register
  #define RCC_CR_HSION_Pos                     (0U)
  #define RCC_CR_HSION_Msk                     (0x1UL << RCC_CR_HSION_Pos)                  /* 0x00000001 */
  #define RCC_CR_HSION                         RCC_CR_HSION_Msk                             /* Internal High Speed clock enable */

  // Cache Size ID Register Macros.
  #define SCB_CCSIDR_NUMSETS_Pos               13U                                          /* SCB CCSIDR: NumSets Position */
  #define SCB_CCSIDR_NUMSETS_Msk               (0x7FFFUL << SCB_CCSIDR_NUMSETS_Pos)         /* SCB CCSIDR: NumSets Mask */

  #define SCB_CCSIDR_ASSOCIATIVITY_Pos         3U                                           /* SCB CCSIDR: Associativity Position */
  #define SCB_CCSIDR_ASSOCIATIVITY_Msk         (0x3FFUL << SCB_CCSIDR_ASSOCIATIVITY_Pos)    /* SCB CCSIDR: Associativity Mask */

  // SCB D-Cache Invalidate by Set-way Register Definitions.
  #define SCB_DCISW_WAY_Pos                    30U                                          /* SCB DCISW: Way Position */
  #define SCB_DCISW_WAY_Msk                    (3UL << SCB_DCISW_WAY_Pos)                   /* SCB DCISW: Way Mask */

  #define SCB_DCISW_SET_Pos                    5U                                           /* SCB DCISW: Set Position */
  #define SCB_DCISW_SET_Msk                    (0x1FFUL << SCB_DCISW_SET_Pos)               /* SCB DCISW: Set Mask */

  #define CCSIDR_WAYS(x)         (((x) & SCB_CCSIDR_ASSOCIATIVITY_Msk) >> SCB_CCSIDR_ASSOCIATIVITY_Pos)
  #define CCSIDR_SETS(x)         (((x) & SCB_CCSIDR_NUMSETS_Msk      ) >> SCB_CCSIDR_NUMSETS_Pos      )

  // BIT definitions for PWR CR3 register
  #define PWR_CR3_USB33RDY_Pos                 (26U)
  #define PWR_CR3_USB33RDY_Msk                 (0x1UL << PWR_CR3_USB33RDY_Pos)               /* 0x04000000 */
  #define PWR_CR3_USB33RDY                     PWR_CR3_USB33RDY_Msk                          /* USB supply ready */
  #define PWR_CR3_USBREGEN_Pos                 (25U)
  #define PWR_CR3_USBREGEN_Msk                 (0x1UL << PWR_CR3_USBREGEN_Pos)               /* 0x02000000 */
  #define PWR_CR3_USBREGEN                     PWR_CR3_USBREGEN_Msk                          /* USB regulator enable */
  #define PWR_CR3_USB33DEN_Pos                 (24U)
  #define PWR_CR3_USB33DEN_Msk                 (0x1UL << PWR_CR3_USB33DEN_Pos)               /* 0x01000000 */
  #define PWR_CR3_USB33DEN                     PWR_CR3_USB33DEN_Msk                          /* VDD33_USB voltage level detector enable */
  #define PWR_CR3_SMPSEXTRDY_Pos               (16U)
  #define PWR_CR3_SMPSEXTRDY_Msk               (0x1UL << PWR_CR3_SMPSEXTRDY_Pos)             /* 0x00010000 */
  #define PWR_CR3_SMPSEXTRDY                   PWR_CR3_SMPSEXTRDY_Msk                        /* SMPS External supply ready */
  #define PWR_CR3_VBRS_Pos                     (9U)
  #define PWR_CR3_VBRS_Msk                     (0x1UL << PWR_CR3_VBRS_Pos)                   /* 0x00000200 */
  #define PWR_CR3_VBRS                         PWR_CR3_VBRS_Msk                              /* VBAT charging resistor selection */
  #define PWR_CR3_VBE_Pos                      (8U)
  #define PWR_CR3_VBE_Msk                      (0x1UL << PWR_CR3_VBE_Pos)                   /* 0x00000100 */
  #define PWR_CR3_VBE                          PWR_CR3_VBE_Msk                              /* VBAT charging enable */
  #define PWR_CR3_SMPSLEVEL_Pos                (4U)
  #define PWR_CR3_SMPSLEVEL_Msk                (0x3UL << PWR_CR3_SMPSLEVEL_Pos)             /* 0x00000030 */
  #define PWR_CR3_SMPSLEVEL                    PWR_CR3_SMPSLEVEL_Msk                        /* SMPS output Voltage */
  #define PWR_CR3_SMPSLEVEL_0                  (0x1UL << PWR_CR3_SMPSLEVEL_Pos)             /* 0x00000010 */
  #define PWR_CR3_SMPSLEVEL_1                  (0x2UL << PWR_CR3_SMPSLEVEL_Pos)             /* 0x00000020 */
  #define PWR_CR3_SMPSEXTHP_Pos                (3U)
  #define PWR_CR3_SMPSEXTHP_Msk                (0x1UL << PWR_CR3_SMPSEXTHP_Pos)             /* 0x00000008 */
  #define PWR_CR3_SMPSEXTHP                    PWR_CR3_SMPSEXTHP_Msk                        /* SMPS forced ON and in High Power MR mode */
  #define PWR_CR3_SMPSEN_Pos                   (2U)
  #define PWR_CR3_SMPSEN_Msk                   (0x1UL << PWR_CR3_SMPSEN_Pos)                /* 0x00000004 */
  #define PWR_CR3_SMPSEN                       PWR_CR3_SMPSEN_Msk                           /* SMPS Enable */
  #define PWR_CR3_LDOEN_Pos                    (1U)
  #define PWR_CR3_LDOEN_Msk                    (0x1UL << PWR_CR3_LDOEN_Pos)                            /* 0x00000002 */
  #define PWR_CR3_LDOEN                        PWR_CR3_LDOEN_Msk                            /* Low Drop Output regulator enable */
  #define PWR_CR3_BYPASS_Pos                   (0U)
  #define PWR_CR3_BYPASS_Msk                   (0x1UL << PWR_CR3_BYPASS_Pos)                /* 0x00000001 */
  #define PWR_CR3_BYPASS                       PWR_CR3_BYPASS_Msk                           /* Power Management Unit bypass */

  // Bit definition for PWR_SRDCR register
  #define PWR_SRDCR_VOS_Pos                    (14U)
  #define PWR_SRDCR_VOS_Msk                    (0x3UL << PWR_SRDCR_VOS_Pos)                 /* 0x0000C000 */
  #define PWR_SRDCR_VOS                        PWR_SRDCR_VOS_Msk                            /* Voltage Scaling selection according performance */
  #define PWR_SRDCR_VOS_0                      (0x1UL << PWR_SRDCR_VOS_Pos)                 /* 0x00004000 */
  #define PWR_SRDCR_VOS_1                      (0x2UL << PWR_SRDCR_VOS_Pos)                 /* 0x00008000 */
  #define PWR_SRDCR_VOSRDY_Pos                 (13U)
  #define PWR_SRDCR_VOSRDY_Msk                 (0x1UL << PWR_SRDCR_VOSRDY_Pos)              /* 0x00002000 */
  #define PWR_SRDCR_VOSRDY                     PWR_SRDCR_VOSRDY_Msk                         /* VOS Ready bit for VDD11 Voltage Scaling output selection */

  // PWREx_Supply_configuration PWREx Supply configuration
  #define PWR_LDO_SUPPLY                      PWR_CR3_LDOEN                                                               /* Core domains are supplied from the LDO */
  #define PWR_DIRECT_SMPS_SUPPLY              PWR_CR3_SMPSEN                                                              /* Core domains are supplied from the SMPS only */
  #define PWR_SMPS_1V8_SUPPLIES_LDO           (PWR_CR3_SMPSLEVEL_0 | PWR_CR3_SMPSEN    | PWR_CR3_LDOEN)                   /* The SMPS 1.8V output supplies the LDO which supplies the Core domains */
  #define PWR_SMPS_2V5_SUPPLIES_LDO           (PWR_CR3_SMPSLEVEL_1 | PWR_CR3_SMPSEN    | PWR_CR3_LDOEN)                   /* The SMPS 2.5V output supplies the LDO which supplies the Core domains */
  #define PWR_SMPS_1V8_SUPPLIES_EXT_AND_LDO   (PWR_CR3_SMPSLEVEL_0 | PWR_CR3_SMPSEXTHP | PWR_CR3_SMPSEN | PWR_CR3_LDOEN)  /* The SMPS 1.8V output supplies an external circuits and the LDO. The Core domains are supplied from the LDO */
  #define PWR_SMPS_2V5_SUPPLIES_EXT_AND_LDO   (PWR_CR3_SMPSLEVEL_1 | PWR_CR3_SMPSEXTHP | PWR_CR3_SMPSEN | PWR_CR3_LDOEN)  /* The SMPS 2.5V output supplies an external circuits and the LDO. The Core domains are supplied from the LDO */
  #define PWR_SMPS_1V8_SUPPLIES_EXT           (PWR_CR3_SMPSLEVEL_0 | PWR_CR3_SMPSEXTHP | PWR_CR3_SMPSEN | PWR_CR3_BYPASS) /* The SMPS 1.8V output supplies an external source which supplies the Core domains */
  #define PWR_SMPS_2V5_SUPPLIES_EXT           (PWR_CR3_SMPSLEVEL_1 | PWR_CR3_SMPSEXTHP | PWR_CR3_SMPSEN | PWR_CR3_BYPASS) /* The SMPS 2.5V output supplies an external source which supplies the Core domains */
  #define PWR_EXTERNAL_SOURCE_SUPPLY          PWR_CR3_BYPASS                                                              /* The SMPS disabled and the LDO Bypass. The Core domains are supplied from an external source */
  #define PWR_DIRECT_SMPS_SUPPLY              PWR_CR3_SMPSEN                                                              /* Core domains are supplied from the SMPS only */

  #define PWR_SUPPLY_CONFIG_MASK (PWR_CR3_SMPSLEVEL | PWR_CR3_SMPSEXTHP | \
                                  PWR_CR3_SMPSEN | PWR_CR3_LDOEN | PWR_CR3_BYPASS)

  #define PWR_REGULATOR_VOLTAGE_SCALE0  (PWR_SRDCR_VOS_1 | PWR_SRDCR_VOS_0)
  #define PWR_REGULATOR_VOLTAGE_SCALE1  (PWR_SRDCR_VOS_1)
  #define PWR_REGULATOR_VOLTAGE_SCALE2  (PWR_SRDCR_VOS_0)
  #define PWR_REGULATOR_VOLTAGE_SCALE3  (0U)

  #define RCC_CR_HSEON_Pos                       (16U)
  #define RCC_CR_HSEON_Msk                       (0x1UL << RCC_CR_HSEON_Pos)     /* 0x00010000 */
  #define RCC_CR_HSEON                           RCC_CR_HSEON_Msk                /* External High Speed clock enable */
  #define RCC_CR_HSERDY_Pos                      (17U)
  #define RCC_CR_HSERDY_Msk                      (0x1UL << RCC_CR_HSERDY_Pos)    /* 0x00020000 */
  #define RCC_CR_HSERDY                          RCC_CR_HSERDY_Msk               /* External High Speed clock ready */
  #define RCC_CR_HSEBYP_Pos                      (18U)
  #define RCC_CR_HSEBYP_Msk                      (0x1UL << RCC_CR_HSEBYP_Pos)    /* 0x00040000 */
  #define RCC_CR_HSEBYP                          RCC_CR_HSEBYP_Msk               /* External High Speed clock Bypass */
  #define RCC_CR_CSSHSEON_Pos                    (19U)
  #define RCC_CR_CSSHSEON_Msk                    (0x1UL << RCC_CR_CSSHSEON_Pos)  /* 0x00080000 */
  #define RCC_CR_CSSHSEON                        RCC_CR_CSSHSEON_Msk             /* HSE Clock security System enable */

  // RCC_Oscillator_Type  RCC Oscillator Type
  #define RCC_OSCILLATORTYPE_NONE        (0x00000000U)
  #define RCC_OSCILLATORTYPE_HSE         (0x00000001U)
  #define RCC_OSCILLATORTYPE_HSI         (0x00000002U)
  #define RCC_OSCILLATORTYPE_LSE         (0x00000004U)
  #define RCC_OSCILLATORTYPE_LSI         (0x00000008U)
  #define RCC_OSCILLATORTYPE_CSI         (0x00000010U)
  #define RCC_OSCILLATORTYPE_HSI48       (0x00000020U)

  // RCC_HSE_Config  RCC HSE Config
  #define RCC_HSE_OFF                    (0x00000000U)
  #define RCC_HSE_ON                     RCC_CR_HSEON
  #define RCC_HSE_BYPASS                 ((uint32_t)(RCC_CR_HSEBYP | RCC_CR_HSEON))

  // RCC_PLL_Config  RCC PLL Config
  #define RCC_PLL_NONE                   (0x00000000U)
  #define RCC_PLL_OFF                    (0x00000001U)
  #define RCC_PLL_ON                     (0x00000002U)

  // RCC_PLL_Clock_Source  RCC PLL Clock Source
  #define RCC_PLLSOURCE_HSI              (0x00000000U)
  #define RCC_PLLSOURCE_CSI              (0x00000001U)
  #define RCC_PLLSOURCE_HSE              (0x00000002U)
  #define RCC_PLLSOURCE_NONE             (0x00000003U)

  // RCC_HSI48_Config  RCC HSI48 Config
  #define RCC_HSI48_OFF                      ((uint8_t)0x00)
  #define RCC_HSI48_ON                       ((uint8_t)0x01)

  // Bit definition for RCC_PLLCFGR register

  #define RCC_PLLCFGR_PLL1FRACEN_Pos             (0U)
  #define RCC_PLLCFGR_PLL1FRACEN_Msk             (0x1UL << RCC_PLLCFGR_PLL1FRACEN_Pos) /* 0x00000001 */
  #define RCC_PLLCFGR_PLL1FRACEN                 RCC_PLLCFGR_PLL1FRACEN_Msk
  #define RCC_PLLCFGR_PLL1VCOSEL_Pos             (1U)
  #define RCC_PLLCFGR_PLL1VCOSEL_Msk             (0x1UL << RCC_PLLCFGR_PLL1VCOSEL_Pos) /* 0x00000002 */
  #define RCC_PLLCFGR_PLL1VCOSEL                 RCC_PLLCFGR_PLL1VCOSEL_Msk
  #define RCC_PLLCFGR_PLL1RGE_Pos                (2U)
  #define RCC_PLLCFGR_PLL1RGE_Msk                (0x3UL << RCC_PLLCFGR_PLL1RGE_Pos) /* 0x0000000C */
  #define RCC_PLLCFGR_PLL1RGE                    RCC_PLLCFGR_PLL1RGE_Msk
  #define RCC_PLLCFGR_PLL1RGE_0                  (0x0UL << RCC_PLLCFGR_PLL1RGE_Pos) /* 0x00000000 */
  #define RCC_PLLCFGR_PLL1RGE_1                  (0x1UL << RCC_PLLCFGR_PLL1RGE_Pos) /* 0x00000004 */
  #define RCC_PLLCFGR_PLL1RGE_2                  (0x2UL << RCC_PLLCFGR_PLL1RGE_Pos) /* 0x00000008 */
  #define RCC_PLLCFGR_PLL1RGE_3                  (0x3UL << RCC_PLLCFGR_PLL1RGE_Pos) /* 0x0000000C */

  // RCC_PLL1_VCI_Range  RCC PLL1 VCI Range
  #define RCC_PLL1VCIRANGE_0                RCC_PLLCFGR_PLL1RGE_0       /* Clock range frequency between 1 and 2 MHz  */
  #define RCC_PLL1VCIRANGE_1                RCC_PLLCFGR_PLL1RGE_1       /* Clock range frequency between 2 and 4 MHz  */
  #define RCC_PLL1VCIRANGE_2                RCC_PLLCFGR_PLL1RGE_2       /* Clock range frequency between 4 and 8 MHz  */
  #define RCC_PLL1VCIRANGE_3                RCC_PLLCFGR_PLL1RGE_3       /* Clock range frequency between 8 and 16 MHz */

  // RCC_PLL1_VCO_Range  RCC PLL1 VCO Range
  #define RCC_PLL1VCOWIDE                 (0x00000000U)
  #define RCC_PLL1VCOMEDIUM               RCC_PLLCFGR_PLL1VCOSEL

  // RCC_System_Clock_Type  RCC System Clock Type
  #define RCC_CLOCKTYPE_SYSCLK           (0x00000001U)
  #define RCC_CLOCKTYPE_HCLK             (0x00000002U)
  #define RCC_CLOCKTYPE_D1PCLK1          (0x00000004U)
  #define RCC_CLOCKTYPE_PCLK1            (0x00000008U)
  #define RCC_CLOCKTYPE_PCLK2            (0x00000010U)
  #define RCC_CLOCKTYPE_D3PCLK1          (0x00000020U)

  #define RCC_CFGR_SW_PLL1               (0x00000003UL)                 /* PLL1 selection as system clock */
  #define RCC_SYSCLKSOURCE_PLLCLK        RCC_CFGR_SW_PLL1

  #define RCC_CDCFGR1_CDCPRE_DIV1        ((uint32_t)0x00000000)         /* Domain 1 Core clock not divided */
  #define RCC_SYSCLK_DIV1                RCC_CDCFGR1_CDCPRE_DIV1

  #define RCC_CDCFGR1_HPRE_DIV1          ((uint32_t)0x00000000)         /* AHB3 Clock not divided */
  #define RCC_HCLK_DIV1                  RCC_CDCFGR1_HPRE_DIV1

  #define RCC_CDCFGR1_CDPPRE_DIV1        ((uint32_t)0x00000000)         /* APB3 clock not divided */
  #define RCC_APB3_DIV1                  RCC_CDCFGR1_CDPPRE_DIV1

  #define RCC_CDCFGR2_CDPPRE1_DIV1       ((uint32_t)0x00000000)         /* APB1 clock not divided */
  #define RCC_APB1_DIV1                  RCC_CDCFGR2_CDPPRE1_DIV1

  #define RCC_CDCFGR2_CDPPRE2_DIV1       ((uint32_t)0x00000000)         /* APB2 clock not divided */
  #define RCC_APB2_DIV1                  RCC_CDCFGR2_CDPPRE2_DIV1

  #define RCC_SRDCFGR_SRDPPRE_DIV1       ((uint32_t)0x00000000)         /* APB4 clock not divided */
  #define RCC_APB4_DIV1                  RCC_SRDCFGR_SRDPPRE_DIV1

  #if defined(__cplusplus)
  extern "C"
  {
  #endif

  typedef struct
  {
    volatile std::uint32_t BTCR[8U];
  }
  FMC_Bank1_TypeDef;

  typedef struct
  {
    uint32_t PLLState;   // The new state of the PLL.
    uint32_t PLLSource;  // RCC_PLLSource: PLL entry clock source.
    uint32_t PLLM;       // PLLM: Division factor for PLL VCO input clock.
    uint32_t PLLN;       // PLLN: Multiplication factor for PLL VCO output clock.
    uint32_t PLLP;       // PLLP: Division factor for system clock.
    uint32_t PLLQ;       // PLLQ: Division factor for peripheral clocks.
    uint32_t PLLR;       // PLLR: Division factor for peripheral clocks.
    uint32_t PLLRGE;     // PLLRGE: PLL1 clock Input range
    uint32_t PLLVCOSEL;  // PLLVCOSEL: PLL1 clock Output range
    uint32_t PLLFRACN;   // PLLFRACN: Specifies Fractional Part Of The Multiplication Factor for
  }
  RCC_PLLInitTypeDef;

  typedef struct
  {
    uint32_t OscillatorType;       // The oscillators to be configured.
    uint32_t HSEState;             // The new state of the HSE.
    uint32_t LSEState;             // The new state of the LSE.
    uint32_t HSIState;             // The new state of the HSI.
    uint32_t HSICalibrationValue;  // The calibration trimming value.
    uint32_t LSIState;             // The new state of the LSI.
    uint32_t HSI48State;           // The new state of the HSI48.
    uint32_t CSIState;             // The new state of the CSI.
    uint32_t CSICalibrationValue;  // The calibration trimming value.
    RCC_PLLInitTypeDef PLL;        // PLL structure parameters
  }
  RCC_OscInitTypeDef;

  typedef struct
  {
    uint32_t ClockType;             // The clock to be configured.
    uint32_t SYSCLKSource;          // The clock source (SYSCLKS) used as system clock.
    uint32_t SYSCLKDivider;         // The system clock  divider. This parameter can be
    uint32_t AHBCLKDivider;         // The AHB clock (HCLK) divider. This clock is derived from the system clock (SYSCLK).
    uint32_t APB3CLKDivider;        // The APB3 clock (D1PCLK1) divider. This clock is derived from the AHB clock (HCLK).
    uint32_t APB1CLKDivider;        // The APB1 clock (PCLK1) divider. This clock is derived from the AHB clock (HCLK).
    uint32_t APB2CLKDivider;        // The APB2 clock (PCLK2) divider. This clock is derived from the AHB clock (HCLK).
    uint32_t APB4CLKDivider;        // The APB4 clock (D3PCLK1) divider. This clock is derived from the AHB clock (HCLK).
  }
  RCC_ClkInitTypeDef;

  // HAL Status structures definition
  typedef enum
  {
    HAL_OK       = 0x00,
    HAL_ERROR    = 0x01,
    HAL_BUSY     = 0x02,
    HAL_TIMEOUT  = 0x03
  }
  HAL_StatusTypeDef;

  HAL_StatusTypeDef HAL_RCC_OscConfig(RCC_OscInitTypeDef *RCC_OscInitStruct);
  HAL_StatusTypeDef HAL_RCC_ClockConfig(RCC_ClkInitTypeDef *RCC_ClkInitStruct, uint32_t FLatency);

  #if defined(__cplusplus)
  }
  #endif

#endif // FROM_PERIPH_DRIVER_2022_08_08_H_
