/**
  ******************************************************************************
  * @file    stm32h7a3xxq.h
  * @author  MCD Application Team
  * @brief   CMSIS STM32H7A3xxQ Device Peripheral Access Layer Header File.
  *
  *          This file contains:
  *           - Data structures and the address mapping for all peripherals
  *           - Peripheral's registers declarations and bits definition
  *           - Macros to access peripheral's registers hardware
  *
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2019 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */

/** @addtogroup CMSIS_Device
  * @{
  */

/** @addtogroup stm32h7a3xxq
  * @{
  */

#ifndef STM32H7A3xxQ_H
#define STM32H7A3xxQ_H

typedef enum
{
  // Cortex-M Processor Exceptions Numbers
  NonMaskableInt_IRQn         = -14, // 2 Non Maskable Interrupt
  HardFault_IRQn              = -13, // 3 Cortex-M Hard Fault Interrupt
  MemoryManagement_IRQn       = -12, // 4 Cortex-M Memory Management Interrupt
  BusFault_IRQn               = -11, // 5 Cortex-M Bus Fault Interrupt
  UsageFault_IRQn             = -10, // 6 Cortex-M Usage Fault Interrupt
  SVCall_IRQn                 = -5,  // 11 Cortex-M SV Call Interrupt
  DebugMonitor_IRQn           = -4,  // 12 Cortex-M Debug Monitor Interrupt
  PendSV_IRQn                 = -2,  // 14 Cortex-M Pend SV Interrupt
  SysTick_IRQn                = -1,  // 15 Cortex-M System Tick Interrupt
  UnusedHandler_00            =  0,  // Dummy specific Interrupt Numbers
  UnusedHandler_01            =  1,
  UnusedHandler_02            =  2,
  UnusedHandler_03            =  3,
  UnusedHandler_04            =  4,
  UnusedHandler_05            =  5,
  UnusedHandler_06            =  6,
  UnusedHandler_07            =  7,
  UnusedHandler_08            =  8,
  UnusedHandler_09            =  9,
  UnusedHandler_10            = 10,
  UnusedHandler_11            = 11,
  UnusedHandler_12            = 12,
  UnusedHandler_13            = 13,
  UnusedHandler_14            = 14,
  UnusedHandler_15            = 15,
  UnusedHandler_16            = 16,
  UnusedHandler_17            = 17,
  UnusedHandler_18            = 18,
  UnusedHandler_19            = 19,
  UnusedHandler_20            = 20,
  UnusedHandler_21            = 21,
  UnusedHandler_22            = 22,
  UnusedHandler_23            = 23,
  UnusedHandler_24            = 24,
  UnusedHandler_25            = 25,
  UnusedHandler_26            = 26,
  UnusedHandler_27            = 27,
  UnusedHandler_28            = 28,
  UnusedHandler_29            = 29,
  UnusedHandler_30            = 30,
  UnusedHandler_31            = 31
}
IRQn_Type;

#define SMPS       /*!< Switched mode power supply feature */

// Configuration of the Cortex-M7 Processor and Core Peripherals
#define __CM7_REV               0x0100U   /*!< Cortex-M7 revision r1p0                       */
#define __MPU_PRESENT             1U       /*!< CM7 provides an MPU                           */
#define __NVIC_PRIO_BITS          4U       /*!< CM7 uses 4 Bits for the Priority Levels       */
#define __Vendor_SysTickConfig    0U       /*!< Set to 1 if different SysTick Config is used  */
#define __FPU_PRESENT             1U       /*!< FPU present                                   */
#define __ICACHE_PRESENT          1U       /*!< CM7 instruction cache present                 */
#define __DCACHE_PRESENT          1U       /*!< CM7 data cache present                        */
#include "core_cm7.h"                     /*!< Cortex-M7 processor and core peripherals      */

#include <cstdint>

// FLASH Registers
typedef struct
{
  __IO std::uint32_t ACR;             // FLASH access control register,                            Address offset: 0x000
  __IO std::uint32_t KEYR1;           // Flash Key Register for bank1,                             Address offset: 0x004
  __IO std::uint32_t OPTKEYR;         // Flash Option Key Register,                                Address offset: 0x008
  __IO std::uint32_t CR1;             // Flash Control Register for bank1,                         Address offset: 0x00C
  __IO std::uint32_t SR1;             // Flash Status Register for bank1,                          Address offset: 0x010
  __IO std::uint32_t CCR1;            // Flash Control Register for bank1,                         Address offset: 0x014
  __IO std::uint32_t OPTCR;           // Flash Option Control Register,                            Address offset: 0x018
  __IO std::uint32_t OPTSR_CUR;       // Flash Option Status Current Register,                     Address offset: 0x01C
  __IO std::uint32_t OPTSR_PRG;       // Flash Option Status to Program Register,                  Address offset: 0x020
  __IO std::uint32_t OPTCCR;          // Flash Option Clear Control Register,                      Address offset: 0x024
  __IO std::uint32_t PRAR_CUR1;       // Flash Current Protection Address Register for bank1,      Address offset: 0x028
  __IO std::uint32_t PRAR_PRG1;       // Flash Protection Address to Program Register for bank1,   Address offset: 0x02C
  __IO std::uint32_t SCAR_CUR1;       // Flash Current Secure Address Register for bank1,          Address offset: 0x030
  __IO std::uint32_t SCAR_PRG1;       // Flash Secure Address to Program Register for bank1,       Address offset: 0x034
  __IO std::uint32_t WPSN_CUR1;       // Flash Current Write Protection Register on bank1,         Address offset: 0x038
  __IO std::uint32_t WPSN_PRG1;       // Flash Write Protection to Program Register on bank1,      Address offset: 0x03C
  __IO std::uint32_t BOOT_CUR;        // Flash Current Boot Address for Pelican Core Register,     Address offset: 0x040
  __IO std::uint32_t BOOT_PRG;        // Flash Boot Address to Program for Pelican Core Register,  Address offset: 0x044
       std::uint32_t RESERVED0[2U];   // Reserved, 0x48 to 0x4C
  __IO std::uint32_t CRCCR1;          // Flash CRC Control register For Bank1 Register ,           Address offset: 0x050
  __IO std::uint32_t CRCSADD1;        // Flash CRC Start Address Register for Bank1 ,              Address offset: 0x054
  __IO std::uint32_t CRCEADD1;        // Flash CRC End Address Register for Bank1 ,                Address offset: 0x058
  __IO std::uint32_t CRCDATA;         // Flash CRC Data Register for Bank1 ,                       Address offset: 0x05C
  __IO std::uint32_t ECC_FA1;         // Flash ECC Fail Address For Bank1 Register ,               Address offset: 0x060
       std::uint32_t RESERVED;        // Reserved, 0x64
  __IO std::uint32_t OTPBL_CUR;       // Flash Current OTP Block Lock Register,                    Address offset: 0x068
  __IO std::uint32_t OTPBL_PRG;       // Flash OTP Block Lock to Program Register,                 Address offset: 0x06C
       std::uint32_t RESERVED1[37U];  // Reserved, 0x70 to 0x100
  __IO std::uint32_t KEYR2;           // Flash Key Register for bank2,                             Address offset: 0x104
       std::uint32_t RESERVED2;       // Reserved, 0x108
  __IO std::uint32_t CR2;             // Flash Control Register for bank2,                         Address offset: 0x10C
  __IO std::uint32_t SR2;             // Flash Status Register for bank2,                          Address offset: 0x110
  __IO std::uint32_t CCR2;            // Flash Status Register for bank2,                          Address offset: 0x114
       std::uint32_t RESERVED3[4U];   // Reserved, 0x118 to 0x124
  __IO std::uint32_t PRAR_CUR2;       // Flash Current Protection Address Register for bank2,      Address offset: 0x128
  __IO std::uint32_t PRAR_PRG2;       // Flash Protection Address to Program Register for bank2,   Address offset: 0x12C
  __IO std::uint32_t SCAR_CUR2;       // Flash Current Secure Address Register for bank2,          Address offset: 0x130
  __IO std::uint32_t SCAR_PRG2;       // Flash Secure Address Register for bank2,                  Address offset: 0x134
  __IO std::uint32_t WPSN_CUR2;       // Flash Current Write Protection Register on bank2,         Address offset: 0x138
  __IO std::uint32_t WPSN_PRG2;       // Flash Write Protection to Program Register on bank2,      Address offset: 0x13C
       std::uint32_t RESERVED4[4U];   // Reserved, 0x140 to 0x14C
  __IO std::uint32_t CRCCR2;          // Flash CRC Control register For Bank2 Register ,           Address offset: 0x150
  __IO std::uint32_t CRCSADD2;        // Flash CRC Start Address Register for Bank2 ,              Address offset: 0x154
  __IO std::uint32_t CRCEADD2;        // Flash CRC End Address Register for Bank2 ,                Address offset: 0x158
  __IO std::uint32_t CRCDATA2;        // Flash CRC Data Register for Bank2 ,                       Address offset: 0x15C
  __IO std::uint32_t ECC_FA2;         // Flash ECC Fail Address For Bank2 Register ,               Address offset: 0x160
}
FLASH_TypeDef;

/**
  * @brief Flexible Memory Controller
  */

typedef struct
{
  __IO uint32_t BTCR[8];    /*!< NOR/PSRAM chip-select control register(BCR) and chip-select timing register(BTR), Address offset: 0x00-1C */
} FMC_Bank1_TypeDef;

// Power Control
typedef struct
{
  __IO uint32_t CR1;       /*!< PWR power control register 1,            Address offset: 0x00 */
  __IO uint32_t CSR1;      /*!< PWR power control status register 1,     Address offset: 0x04 */
  __IO uint32_t CR2;       /*!< PWR power control register 2,            Address offset: 0x08 */
  __IO uint32_t CR3;       /*!< PWR power control register 3,            Address offset: 0x0C */
  __IO uint32_t CPUCR;     /*!< PWR CPU control register,                Address offset: 0x10 */
       uint32_t RESERVED0; /*!< Reserved,                                Address offset: 0x14 */
  __IO uint32_t SRDCR;     /*!< PWR SRD domain control register,         Address offset: 0x18 */
       uint32_t RESERVED1; /*!< Reserved,                                Address offset: 0x1C */
  __IO uint32_t WKUPCR;    /*!< PWR wakeup clear register,               Address offset: 0x20 */
  __IO uint32_t WKUPFR;    /*!< PWR wakeup flag register,                Address offset: 0x24 */
  __IO uint32_t WKUPEPR;   /*!< PWR wakeup enable and polarity register, Address offset: 0x28 */
} PWR_TypeDef;

/**
  * @brief Reset and Clock Control
  */

typedef struct
{
 __IO uint32_t CR;             /*!< RCC clock control register,                                              Address offset: 0x00  */
 __IO uint32_t HSICFGR;        /*!< HSI Clock Calibration Register,                                          Address offset: 0x04  */
 __IO uint32_t CRRCR;          /*!< Clock Recovery RC  Register,                                             Address offset: 0x08  */
 __IO uint32_t CSICFGR;        /*!< CSI Clock Calibration Register,                                          Address offset: 0x0C  */
 __IO uint32_t CFGR;           /*!< RCC clock configuration register,                                        Address offset: 0x10  */
 uint32_t     RESERVED1;       /*!< Reserved,                                                                Address offset: 0x14  */
 __IO uint32_t CDCFGR1;         /*!< RCC Domain 1 configuration register,                                    Address offset: 0x18  */
 __IO uint32_t CDCFGR2;         /*!< RCC Domain 2 configuration register,                                    Address offset: 0x1C  */
 __IO uint32_t SRDCFGR;         /*!< RCC Domain 3 configuration register,                                    Address offset: 0x20  */
 uint32_t     RESERVED2;       /*!< Reserved,                                                                Address offset: 0x24  */
 __IO uint32_t PLLCKSELR;      /*!< RCC PLLs Clock Source Selection Register,                                Address offset: 0x28  */
 __IO uint32_t PLLCFGR;        /*!< RCC PLLs  Configuration Register,                                        Address offset: 0x2C  */
 __IO uint32_t PLL1DIVR;       /*!< RCC PLL1 Dividers Configuration Register,                                Address offset: 0x30  */
 __IO uint32_t PLL1FRACR;      /*!< RCC PLL1 Fractional Divider Configuration Register,                      Address offset: 0x34  */
 __IO uint32_t PLL2DIVR;       /*!< RCC PLL2 Dividers Configuration Register,                                Address offset: 0x38  */
 __IO uint32_t PLL2FRACR;      /*!< RCC PLL2 Fractional Divider Configuration Register,                      Address offset: 0x3C  */
 __IO uint32_t PLL3DIVR;       /*!< RCC PLL3 Dividers Configuration Register,                                Address offset: 0x40  */
 __IO uint32_t PLL3FRACR;      /*!< RCC PLL3 Fractional Divider Configuration Register,                      Address offset: 0x44  */
 uint32_t      RESERVED3;      /*!< Reserved,                                                                Address offset: 0x48  */
 __IO uint32_t  CDCCIPR;       /*!< RCC Domain 1 Kernel Clock Configuration Register                         Address offset: 0x4C  */
 __IO uint32_t  CDCCIP1R;      /*!< RCC Domain 2 Kernel Clock Configuration Register                         Address offset: 0x50  */
 __IO uint32_t  CDCCIP2R;      /*!< RCC Domain 2 Kernel Clock Configuration Register                         Address offset: 0x54  */
 __IO uint32_t  SRDCCIPR;       /*!< RCC Domain 3 Kernel Clock Configuration Register                         Address offset: 0x58  */
 uint32_t      RESERVED4;      /*!< Reserved,                                                                Address offset: 0x5C  */
 __IO uint32_t  CIER;          /*!< RCC Clock Source Interrupt Enable Register                               Address offset: 0x60  */
 __IO uint32_t  CIFR;          /*!< RCC Clock Source Interrupt Flag Register                                 Address offset: 0x64  */
 __IO uint32_t  CICR;          /*!< RCC Clock Source Interrupt Clear Register                                Address offset: 0x68  */
 uint32_t     RESERVED5;       /*!< Reserved,                                                                Address offset: 0x6C  */
 __IO uint32_t  BDCR;          /*!< RCC Vswitch Backup Domain Control Register,                              Address offset: 0x70  */
 __IO uint32_t  CSR;           /*!< RCC clock control & status register,                                     Address offset: 0x74  */
 uint32_t     RESERVED6;       /*!< Reserved,                                                                Address offset: 0x78  */
 __IO uint32_t AHB3RSTR;       /*!< RCC AHB3 peripheral reset register,                                      Address offset: 0x7C  */
 __IO uint32_t AHB1RSTR;       /*!< RCC AHB1 peripheral reset register,                                      Address offset: 0x80  */
 __IO uint32_t AHB2RSTR;       /*!< RCC AHB2 peripheral reset register,                                      Address offset: 0x84  */
 __IO uint32_t AHB4RSTR;       /*!< RCC AHB4 peripheral reset register,                                      Address offset: 0x88  */
 __IO uint32_t APB3RSTR;       /*!< RCC APB3 peripheral reset register,                                      Address offset: 0x8C  */
 __IO uint32_t APB1LRSTR;      /*!< RCC APB1 peripheral reset Low Word register,                             Address offset: 0x90  */
 __IO uint32_t APB1HRSTR;      /*!< RCC APB1 peripheral reset High Word register,                            Address offset: 0x94  */
 __IO uint32_t APB2RSTR;       /*!< RCC APB2 peripheral reset register,                                      Address offset: 0x98  */
 __IO uint32_t APB4RSTR;       /*!< RCC APB4 peripheral reset register,                                      Address offset: 0x9C  */
 uint32_t     RESERVED7;       /*!< Reserved,                                                                Address offset: 0xA0  */
 uint32_t     RESERVED8;       /*!< Reserved,                                                                Address offset: 0xA4  */
 __IO uint32_t SRDAMR;         /*!< RCC Domain 3 Autonomous Mode Register,                                   Address offset: 0xA8  */
  uint32_t     RESERVED9;      /*!< Reserved, 0xAC-0xAF                                                      Address offset: 0xAC  */
 __IO uint32_t CKGAENR;        /*!< AXI Clocks Gating Enable Register,                                       Address offset: 0xB0  */
  uint32_t     RESERVED10[31];   /*!< Reserved, 0xAC-0xAF                                                    Address offset: 0xAC  */
 __IO uint32_t RSR;            /*!< RCC Reset status register,                                               Address offset: 0xD0  */
 __IO uint32_t AHB3ENR;        /*!< RCC AHB3 peripheral clock  register,                                     Address offset: 0xD4  */
 __IO uint32_t AHB1ENR;        /*!< RCC AHB1 peripheral clock  register,                                     Address offset: 0xD8  */
 __IO uint32_t AHB2ENR;        /*!< RCC AHB2 peripheral clock  register,                                     Address offset: 0xDC  */
 __IO uint32_t AHB4ENR;        /*!< RCC AHB4 peripheral clock  register,                                     Address offset: 0xE0  */
 __IO uint32_t APB3ENR;        /*!< RCC APB3 peripheral clock  register,                                     Address offset: 0xE4  */
 __IO uint32_t APB1LENR;       /*!< RCC APB1 peripheral clock  Low Word register,                            Address offset: 0xE8  */
 __IO uint32_t APB1HENR;       /*!< RCC APB1 peripheral clock  High Word register,                           Address offset: 0xEC  */
 __IO uint32_t APB2ENR;        /*!< RCC APB2 peripheral clock  register,                                     Address offset: 0xF0  */
 __IO uint32_t APB4ENR;        /*!< RCC APB4 peripheral clock  register,                                     Address offset: 0xF4  */
 uint32_t      RESERVED12;      /*!< Reserved,                                                                Address offset: 0xF8  */
 __IO uint32_t AHB3LPENR;      /*!< RCC AHB3 peripheral sleep clock  register,                               Address offset: 0xFC  */
 __IO uint32_t AHB1LPENR;      /*!< RCC AHB1 peripheral sleep clock  register,                               Address offset: 0x100 */
 __IO uint32_t AHB2LPENR;      /*!< RCC AHB2 peripheral sleep clock  register,                               Address offset: 0x104 */
 __IO uint32_t AHB4LPENR;      /*!< RCC AHB4 peripheral sleep clock  register,                               Address offset: 0x108 */
 __IO uint32_t APB3LPENR;      /*!< RCC APB3 peripheral sleep clock  register,                               Address offset: 0x10C */
 __IO uint32_t APB1LLPENR;     /*!< RCC APB1 peripheral sleep clock  Low Word register,                      Address offset: 0x110 */
 __IO uint32_t APB1HLPENR;     /*!< RCC APB1 peripheral sleep clock  High Word register,                     Address offset: 0x114 */
 __IO uint32_t APB2LPENR;      /*!< RCC APB2 peripheral sleep clock  register,                               Address offset: 0x118 */
 __IO uint32_t APB4LPENR;      /*!< RCC APB4 peripheral sleep clock  register,                               Address offset: 0x11C */
 uint32_t     RESERVED13[4];   /*!< Reserved, 0x120-0x12C                                                    Address offset: 0x120 */

} RCC_TypeDef;

#define PERIPH_BASE               (0x40000000UL) /*!< Base address of : AHB/ABP Peripherals                                                    */
#define SRD_AHB4PERIPH_BASE      (PERIPH_BASE + 0x18020000UL)   /*!<  D3_AHB1PERIPH_BASE       (PERIPH_BASE + 0x18020000UL)                    */
#define CD_AHB3PERIPH_BASE       (PERIPH_BASE + 0x12000000UL)   /*!<  D1_AHB1PERIPH_BASE       (PERIPH_BASE + 0x12000000UL)                    */

#define RCC_BASE              (SRD_AHB4PERIPH_BASE + 0x4400UL)
#define PWR_BASE              (SRD_AHB4PERIPH_BASE + 0x4800UL)
#define FLASH_R_BASE          (CD_AHB3PERIPH_BASE + 0x2000UL)

#define RCC                 ((RCC_TypeDef *) RCC_BASE)
#define FLASH               ((FLASH_TypeDef *) FLASH_R_BASE)
#define PWR                 ((PWR_TypeDef *) PWR_BASE)

#define PWR_CR1_DBP_Pos                (8U)
#define PWR_CR1_DBP_Msk                (0x1UL << PWR_CR1_DBP_Pos)              /*!< 0x00000100 */
#define PWR_CR1_DBP                    PWR_CR1_DBP_Msk                         /*!< Disable Back-up domain Protection */

/********************  Bit definition for PWR_CR3 register  *******************/
#define PWR_CR3_USB33RDY_Pos           (26U)
#define PWR_CR3_USB33RDY_Msk           (0x1UL << PWR_CR3_USB33RDY_Pos)         /*!< 0x04000000 */
#define PWR_CR3_USB33RDY               PWR_CR3_USB33RDY_Msk                    /*!< USB supply ready */
#define PWR_CR3_USBREGEN_Pos           (25U)
#define PWR_CR3_USBREGEN_Msk           (0x1UL << PWR_CR3_USBREGEN_Pos)         /*!< 0x02000000 */
#define PWR_CR3_USBREGEN               PWR_CR3_USBREGEN_Msk                    /*!< USB regulator enable */
#define PWR_CR3_USB33DEN_Pos           (24U)
#define PWR_CR3_USB33DEN_Msk           (0x1UL << PWR_CR3_USB33DEN_Pos)         /*!< 0x01000000 */
#define PWR_CR3_USB33DEN               PWR_CR3_USB33DEN_Msk                    /*!< VDD33_USB voltage level detector enable */
#define PWR_CR3_SMPSEXTRDY_Pos         (16U)
#define PWR_CR3_SMPSEXTRDY_Msk         (0x1UL << PWR_CR3_SMPSEXTRDY_Pos)       /*!< 0x00010000 */
#define PWR_CR3_SMPSEXTRDY             PWR_CR3_SMPSEXTRDY_Msk                  /*!< SMPS External supply ready */
#define PWR_CR3_VBRS_Pos               (9U)
#define PWR_CR3_VBRS_Msk               (0x1UL << PWR_CR3_VBRS_Pos)             /*!< 0x00000200 */
#define PWR_CR3_VBRS                   PWR_CR3_VBRS_Msk                        /*!< VBAT charging resistor selection */
#define PWR_CR3_VBE_Pos                (8U)
#define PWR_CR3_VBE_Msk                (0x1UL << PWR_CR3_VBE_Pos)              /*!< 0x00000100 */
#define PWR_CR3_VBE                    PWR_CR3_VBE_Msk                         /*!< VBAT charging enable */
#define PWR_CR3_SMPSLEVEL_Pos          (4U)
#define PWR_CR3_SMPSLEVEL_Msk          (0x3UL << PWR_CR3_SMPSLEVEL_Pos)        /*!< 0x00000030 */
#define PWR_CR3_SMPSLEVEL              PWR_CR3_SMPSLEVEL_Msk                   /*!< SMPS output Voltage */
#define PWR_CR3_SMPSLEVEL_0            (0x1UL << PWR_CR3_SMPSLEVEL_Pos)        /*!< 0x00000010 */
#define PWR_CR3_SMPSLEVEL_1            (0x2UL << PWR_CR3_SMPSLEVEL_Pos)        /*!< 0x00000020 */
#define PWR_CR3_SMPSEXTHP_Pos          (3U)
#define PWR_CR3_SMPSEXTHP_Msk          (0x1UL << PWR_CR3_SMPSEXTHP_Pos)        /*!< 0x00000008 */
#define PWR_CR3_SMPSEXTHP              PWR_CR3_SMPSEXTHP_Msk                   /*!< SMPS forced ON and in High Power MR mode */
#define PWR_CR3_SMPSEN_Pos             (2U)
#define PWR_CR3_SMPSEN_Msk             (0x1UL << PWR_CR3_SMPSEN_Pos)           /*!< 0x00000004 */
#define PWR_CR3_SMPSEN                 PWR_CR3_SMPSEN_Msk                      /*!< SMPS Enable */
#define PWR_CR3_LDOEN_Pos              (1U)
#define PWR_CR3_LDOEN_Msk              (0x1UL << PWR_CR3_LDOEN_Pos)            /*!< 0x00000002 */
#define PWR_CR3_LDOEN                  PWR_CR3_LDOEN_Msk                       /*!< Low Drop Output regulator enable */
#define PWR_CR3_BYPASS_Pos             (0U)
#define PWR_CR3_BYPASS_Msk             (0x1UL << PWR_CR3_BYPASS_Pos)           /*!< 0x00000001 */
#define PWR_CR3_BYPASS                 PWR_CR3_BYPASS_Msk                      /*!< Power Management Unit bypass */

/********************  Bit definition for PWR_CPUCR register  *****************/
#define PWR_CPUCR_RUN_SRD_Pos          (11U)
#define PWR_CPUCR_RUN_SRD_Msk          (0x1UL << PWR_CPUCR_RUN_SRD_Pos)        /*!< 0x00000800 */
#define PWR_CPUCR_RUN_SRD              PWR_CPUCR_RUN_SRD_Msk                   /*!< Keep system SRD domain in RUN mode regardless of the CPU sub-systems modes */
#define PWR_CPUCR_CSSF_Pos             (9U)
#define PWR_CPUCR_CSSF_Msk             (0x1UL << PWR_CPUCR_CSSF_Pos)           /*!< 0x00000200 */
#define PWR_CPUCR_CSSF                 PWR_CPUCR_CSSF_Msk                      /*!< Clear D1 domain CPU1 STANDBY, STOP and HOLD flags */
#define PWR_CPUCR_SBF_Pos              (6U)
#define PWR_CPUCR_SBF_Msk              (0x1UL << PWR_CPUCR_SBF_Pos)            /*!< 0x00000040 */
#define PWR_CPUCR_SBF                  PWR_CPUCR_SBF_Msk                       /*!< System STANDBY Flag */
#define PWR_CPUCR_STOPF_Pos            (5U)
#define PWR_CPUCR_STOPF_Msk            (0x1UL << PWR_CPUCR_STOPF_Pos)          /*!< 0x00000020 */
#define PWR_CPUCR_STOPF                PWR_CPUCR_STOPF_Msk                     /*!< STOP Flag */
#define PWR_CPUCR_PDDS_SRD_Pos         (2U)
#define PWR_CPUCR_PDDS_SRD_Msk         (0x1UL << PWR_CPUCR_PDDS_SRD_Pos)       /*!< 0x00000004 */
#define PWR_CPUCR_PDDS_SRD             PWR_CPUCR_PDDS_SRD_Msk                  /*!< System SRD domain Power Down Deepsleep */
#define PWR_CPUCR_RETDS_CD_Pos         (0U)
#define PWR_CPUCR_RETDS_CD_Msk         (0x1UL << PWR_CPUCR_RETDS_CD_Pos)       /*!< 0x00000001 */
#define PWR_CPUCR_RETDS_CD             PWR_CPUCR_RETDS_CD_Msk                  /*!< CD domain Power Down Deepsleep selection */
/********************  Bit definition for PWR_SRDCR register  *****************/
#define PWR_SRDCR_VOS_Pos              (14U)
#define PWR_SRDCR_VOS_Msk              (0x3UL << PWR_SRDCR_VOS_Pos)             /*!< 0x0000C000 */
#define PWR_SRDCR_VOS                  PWR_SRDCR_VOS_Msk                        /*!< Voltage Scaling selection according performance */
#define PWR_SRDCR_VOS_0                (0x1UL << PWR_SRDCR_VOS_Pos)             /*!< 0x00004000 */
#define PWR_SRDCR_VOS_1                (0x2UL << PWR_SRDCR_VOS_Pos)             /*!< 0x00008000 */
#define PWR_SRDCR_VOSRDY_Pos           (13U)
#define PWR_SRDCR_VOSRDY_Msk           (0x1UL << PWR_SRDCR_VOSRDY_Pos)          /*!< 0x00002000 */
#define PWR_SRDCR_VOSRDY               PWR_SRDCR_VOSRDY_Msk                     /*!< VOS Ready bit for VDD11 Voltage Scaling output selection */

/*******************  Bits definition for FLASH_ACR register  **********************/
#define FLASH_ACR_LATENCY_Pos                (0U)
#define FLASH_ACR_LATENCY_Msk                (0xFUL << FLASH_ACR_LATENCY_Pos)  /*!< 0x0000000F: bit4 is kept only for legacy purpose */
#define FLASH_ACR_LATENCY                    FLASH_ACR_LATENCY_Msk             /*!< Read Latency */
#define FLASH_ACR_LATENCY_0WS                (0x00000000UL)
#define FLASH_ACR_LATENCY_1WS                (0x00000001UL)
#define FLASH_ACR_LATENCY_2WS                (0x00000002UL)
#define FLASH_ACR_LATENCY_3WS                (0x00000003UL)
#define FLASH_ACR_LATENCY_4WS                (0x00000004UL)
#define FLASH_ACR_LATENCY_5WS                (0x00000005UL)
#define FLASH_ACR_LATENCY_6WS                (0x00000006UL)
#define FLASH_ACR_LATENCY_7WS                (0x00000007UL)

#define FLASH_LATENCY_DEFAULT                FLASH_ACR_LATENCY_3WS /* FLASH Three Latency cycles */

/******************************************************************************/
/*                                                                            */
/*                         Reset and Clock Control                            */
/*                                                                            */
/******************************************************************************/
/*******************************  RCC VERSION  ********************************/
#define RCC_VER_2_0

/********************  Bit definition for RCC_CR register  ********************/
#define RCC_CR_HSION_Pos                       (0U)
#define RCC_CR_HSION_Msk                       (0x1UL << RCC_CR_HSION_Pos)     /*!< 0x00000001 */
#define RCC_CR_HSION                           RCC_CR_HSION_Msk                /*!< Internal High Speed clock enable */
#define RCC_CR_HSIKERON_Pos                    (1U)
#define RCC_CR_HSIKERON_Msk                    (0x1UL << RCC_CR_HSIKERON_Pos)  /*!< 0x00000002 */
#define RCC_CR_HSIKERON                        RCC_CR_HSIKERON_Msk             /*!< Internal High Speed clock enable for some IPs Kernel */
#define RCC_CR_HSIRDY_Pos                      (2U)
#define RCC_CR_HSIRDY_Msk                      (0x1UL << RCC_CR_HSIRDY_Pos)    /*!< 0x00000004 */
#define RCC_CR_HSIRDY                          RCC_CR_HSIRDY_Msk               /*!< Internal High Speed clock ready flag */
#define RCC_CR_HSIDIV_Pos                      (3U)
#define RCC_CR_HSIDIV_Msk                      (0x3UL << RCC_CR_HSIDIV_Pos)    /*!< 0x00000018 */
#define RCC_CR_HSIDIV                          RCC_CR_HSIDIV_Msk               /*!< Internal High Speed clock divider selection */
#define RCC_CR_HSIDIV_1                        (0x0UL << RCC_CR_HSIDIV_Pos)     /*!< 0x00000000 */
#define RCC_CR_HSIDIV_2                        (0x1UL << RCC_CR_HSIDIV_Pos)     /*!< 0x00000008 */
#define RCC_CR_HSIDIV_4                        (0x2UL << RCC_CR_HSIDIV_Pos)     /*!< 0x00000010 */
#define RCC_CR_HSIDIV_8                        (0x3UL << RCC_CR_HSIDIV_Pos)     /*!< 0x00000018 */

#define RCC_CR_HSIDIVF_Pos                     (5U)
#define RCC_CR_HSIDIVF_Msk                     (0x1UL << RCC_CR_HSIDIVF_Pos)   /*!< 0x00000020 */
#define RCC_CR_HSIDIVF                         RCC_CR_HSIDIVF_Msk              /*!< HSI Divider flag */
#define RCC_CR_CSION_Pos                       (7U)
#define RCC_CR_CSION_Msk                       (0x1UL << RCC_CR_CSION_Pos)     /*!< 0x00000080 */
#define RCC_CR_CSION                           RCC_CR_CSION_Msk                /*!< The Internal RC 4MHz oscillator clock enable */
#define RCC_CR_CSIRDY_Pos                      (8U)
#define RCC_CR_CSIRDY_Msk                      (0x1UL << RCC_CR_CSIRDY_Pos)    /*!< 0x00000100 */
#define RCC_CR_CSIRDY                          RCC_CR_CSIRDY_Msk               /*!< The Internal RC 4MHz oscillator clock ready */
#define RCC_CR_CSIKERON_Pos                    (9U)
#define RCC_CR_CSIKERON_Msk                    (0x1UL << RCC_CR_CSIKERON_Pos)  /*!< 0x00000200 */
#define RCC_CR_CSIKERON                        RCC_CR_CSIKERON_Msk             /*!< Internal RC 4MHz oscillator clock enable for some IPs Kernel */
#define RCC_CR_HSI48ON_Pos                     (12U)
#define RCC_CR_HSI48ON_Msk                     (0x1UL << RCC_CR_HSI48ON_Pos)   /*!< 0x00001000 */
#define RCC_CR_HSI48ON                         RCC_CR_HSI48ON_Msk              /*!< HSI48 clock enable clock enable  */
#define RCC_CR_HSI48RDY_Pos                    (13U)
#define RCC_CR_HSI48RDY_Msk                    (0x1UL << RCC_CR_HSI48RDY_Pos)  /*!< 0x00002000 */
#define RCC_CR_HSI48RDY                        RCC_CR_HSI48RDY_Msk             /*!< HSI48 clock ready */

#define RCC_CR_CPUCKRDY_Pos                     (14U)
#define RCC_CR_CPUCKRDY_Msk                     (0x1UL << RCC_CR_CPUCKRDY_Pos)   /*!< 0x00004000 */
#define RCC_CR_CPUCKRDY                         RCC_CR_CPUCKRDY_Msk              /*!< CPU domain clocks ready flag  */
#define RCC_CR_CDCKRDY_Pos                     (15U)
#define RCC_CR_CDCKRDY_Msk                     (0x1UL << RCC_CR_CDCKRDY_Pos)   /*!< 0x00008000 */
#define RCC_CR_CDCKRDY                         RCC_CR_CDCKRDY_Msk              /*!< CD domain clocks ready flag */

#define RCC_CR_HSEON_Pos                       (16U)
#define RCC_CR_HSEON_Msk                       (0x1UL << RCC_CR_HSEON_Pos)     /*!< 0x00010000 */
#define RCC_CR_HSEON                           RCC_CR_HSEON_Msk                /*!< External High Speed clock enable */
#define RCC_CR_HSERDY_Pos                      (17U)
#define RCC_CR_HSERDY_Msk                      (0x1UL << RCC_CR_HSERDY_Pos)    /*!< 0x00020000 */
#define RCC_CR_HSERDY                          RCC_CR_HSERDY_Msk               /*!< External High Speed clock ready */
#define RCC_CR_HSEBYP_Pos                      (18U)
#define RCC_CR_HSEBYP_Msk                      (0x1UL << RCC_CR_HSEBYP_Pos)    /*!< 0x00040000 */
#define RCC_CR_HSEBYP                          RCC_CR_HSEBYP_Msk               /*!< External High Speed clock Bypass */
#define RCC_CR_CSSHSEON_Pos                    (19U)
#define RCC_CR_CSSHSEON_Msk                    (0x1UL << RCC_CR_CSSHSEON_Pos)  /*!< 0x00080000 */
#define RCC_CR_CSSHSEON                        RCC_CR_CSSHSEON_Msk             /*!< HSE Clock security System enable */

#define RCC_CR_HSEEXT_Pos                    (20U)
#define RCC_CR_HSEEXT_Msk                    (0x1UL << RCC_CR_HSEEXT_Pos)  /*!< 0x00080000 */
#define RCC_CR_HSEEXT                        RCC_CR_HSEEXT_Msk             /*!< HSE Clock security System enable */

#define RCC_CR_PLL1ON_Pos                      (24U)
#define RCC_CR_PLL1ON_Msk                      (0x1UL << RCC_CR_PLL1ON_Pos)    /*!< 0x01000000 */
#define RCC_CR_PLL1ON                          RCC_CR_PLL1ON_Msk               /*!< System PLL1 clock enable */
#define RCC_CR_PLL1RDY_Pos                     (25U)
#define RCC_CR_PLL1RDY_Msk                     (0x1UL << RCC_CR_PLL1RDY_Pos)   /*!< 0x02000000 */
#define RCC_CR_PLL1RDY                         RCC_CR_PLL1RDY_Msk              /*!< System PLL1 clock ready */
#define RCC_CR_PLL2ON_Pos                      (26U)
#define RCC_CR_PLL2ON_Msk                      (0x1UL << RCC_CR_PLL2ON_Pos)    /*!< 0x04000000 */
#define RCC_CR_PLL2ON                          RCC_CR_PLL2ON_Msk               /*!< System PLL2 clock enable */
#define RCC_CR_PLL2RDY_Pos                     (27U)
#define RCC_CR_PLL2RDY_Msk                     (0x1UL << RCC_CR_PLL2RDY_Pos)   /*!< 0x08000000 */
#define RCC_CR_PLL2RDY                         RCC_CR_PLL2RDY_Msk              /*!< System PLL2 clock ready */
#define RCC_CR_PLL3ON_Pos                      (28U)
#define RCC_CR_PLL3ON_Msk                      (0x1UL << RCC_CR_PLL3ON_Pos)    /*!< 0x10000000 */
#define RCC_CR_PLL3ON                          RCC_CR_PLL3ON_Msk               /*!< System PLL3 clock enable */
#define RCC_CR_PLL3RDY_Pos                     (29U)
#define RCC_CR_PLL3RDY_Msk                     (0x1UL << RCC_CR_PLL3RDY_Pos)   /*!< 0x20000000 */
#define RCC_CR_PLL3RDY                         RCC_CR_PLL3RDY_Msk              /*!< System PLL3 clock ready */

/*Legacy */
#define RCC_CR_PLLON_Pos                       (24U)
#define RCC_CR_PLLON_Msk                       (0x1UL << RCC_CR_PLLON_Pos)     /*!< 0x01000000 */
#define RCC_CR_PLLON                           RCC_CR_PLLON_Msk                /*!< System PLL clock enable */
#define RCC_CR_PLLRDY_Pos                      (25U)
#define RCC_CR_PLLRDY_Msk                      (0x1UL << RCC_CR_PLLRDY_Pos)    /*!< 0x02000000 */
#define RCC_CR_PLLRDY                          RCC_CR_PLLRDY_Msk               /*!< System PLL clock ready */

/********************  Bit definition for RCC_HSICFGR register  ***************/
/*!< HSICAL configuration */
#define RCC_HSICFGR_HSICAL_Pos                 (0U)
#define RCC_HSICFGR_HSICAL_Msk                 (0xFFFUL << RCC_HSICFGR_HSICAL_Pos) /*!< 0x00000FFF */
#define RCC_HSICFGR_HSICAL                     RCC_HSICFGR_HSICAL_Msk          /*!< HSICAL[11:0] bits */
#define RCC_HSICFGR_HSICAL_0                   (0x001UL << RCC_HSICFGR_HSICAL_Pos) /*!< 0x00000001 */
#define RCC_HSICFGR_HSICAL_1                   (0x002UL << RCC_HSICFGR_HSICAL_Pos) /*!< 0x00000002 */
#define RCC_HSICFGR_HSICAL_2                   (0x004UL << RCC_HSICFGR_HSICAL_Pos) /*!< 0x00000004 */
#define RCC_HSICFGR_HSICAL_3                   (0x008UL << RCC_HSICFGR_HSICAL_Pos) /*!< 0x00000008 */
#define RCC_HSICFGR_HSICAL_4                   (0x010UL << RCC_HSICFGR_HSICAL_Pos) /*!< 0x00000010 */
#define RCC_HSICFGR_HSICAL_5                   (0x020UL << RCC_HSICFGR_HSICAL_Pos) /*!< 0x00000020 */
#define RCC_HSICFGR_HSICAL_6                   (0x040UL << RCC_HSICFGR_HSICAL_Pos) /*!< 0x00000040 */
#define RCC_HSICFGR_HSICAL_7                   (0x080UL << RCC_HSICFGR_HSICAL_Pos) /*!< 0x00000080 */
#define RCC_HSICFGR_HSICAL_8                   (0x100UL << RCC_HSICFGR_HSICAL_Pos) /*!< 0x00000100 */
#define RCC_HSICFGR_HSICAL_9                   (0x200UL << RCC_HSICFGR_HSICAL_Pos) /*!< 0x00000200 */
#define RCC_HSICFGR_HSICAL_10                  (0x400UL << RCC_HSICFGR_HSICAL_Pos) /*!< 0x00000400 */
#define RCC_HSICFGR_HSICAL_11                  (0x800UL << RCC_HSICFGR_HSICAL_Pos) /*!< 0x00000800 */

/*!< HSITRIM configuration */
#define RCC_HSICFGR_HSITRIM_Pos                (24U)
#define RCC_HSICFGR_HSITRIM_Msk                (0x7FUL << RCC_HSICFGR_HSITRIM_Pos) /*!< 0x7F000000 */
#define RCC_HSICFGR_HSITRIM                    RCC_HSICFGR_HSITRIM_Msk         /*!< HSITRIM[6:0] bits */
#define RCC_HSICFGR_HSITRIM_0                  (0x01UL << RCC_HSICFGR_HSITRIM_Pos) /*!< 0x01000000 */
#define RCC_HSICFGR_HSITRIM_1                  (0x02UL << RCC_HSICFGR_HSITRIM_Pos) /*!< 0x02000000 */
#define RCC_HSICFGR_HSITRIM_2                  (0x04UL << RCC_HSICFGR_HSITRIM_Pos) /*!< 0x04000000 */
#define RCC_HSICFGR_HSITRIM_3                  (0x08UL << RCC_HSICFGR_HSITRIM_Pos) /*!< 0x08000000 */
#define RCC_HSICFGR_HSITRIM_4                  (0x10UL << RCC_HSICFGR_HSITRIM_Pos) /*!< 0x10000000 */
#define RCC_HSICFGR_HSITRIM_5                  (0x20UL << RCC_HSICFGR_HSITRIM_Pos) /*!< 0x20000000 */
#define RCC_HSICFGR_HSITRIM_6                  (0x40UL << RCC_HSICFGR_HSITRIM_Pos) /*!< 0x40000000 */


/********************  Bit definition for RCC_CRRCR register  *****************/

/*!< HSI48CAL configuration */
#define RCC_CRRCR_HSI48CAL_Pos                 (0U)
#define RCC_CRRCR_HSI48CAL_Msk                 (0x3FFUL << RCC_CRRCR_HSI48CAL_Pos) /*!< 0x000003FF */
#define RCC_CRRCR_HSI48CAL                     RCC_CRRCR_HSI48CAL_Msk          /*!< HSI48CAL[9:0] bits */
#define RCC_CRRCR_HSI48CAL_0                   (0x001UL << RCC_CRRCR_HSI48CAL_Pos) /*!< 0x00000001 */
#define RCC_CRRCR_HSI48CAL_1                   (0x002UL << RCC_CRRCR_HSI48CAL_Pos) /*!< 0x00000002 */
#define RCC_CRRCR_HSI48CAL_2                   (0x004UL << RCC_CRRCR_HSI48CAL_Pos) /*!< 0x00000004 */
#define RCC_CRRCR_HSI48CAL_3                   (0x008UL << RCC_CRRCR_HSI48CAL_Pos) /*!< 0x00000008 */
#define RCC_CRRCR_HSI48CAL_4                   (0x010UL << RCC_CRRCR_HSI48CAL_Pos) /*!< 0x00000010 */
#define RCC_CRRCR_HSI48CAL_5                   (0x020UL << RCC_CRRCR_HSI48CAL_Pos) /*!< 0x00000020 */
#define RCC_CRRCR_HSI48CAL_6                   (0x040UL << RCC_CRRCR_HSI48CAL_Pos) /*!< 0x00000040 */
#define RCC_CRRCR_HSI48CAL_7                   (0x080UL << RCC_CRRCR_HSI48CAL_Pos) /*!< 0x00000080 */
#define RCC_CRRCR_HSI48CAL_8                   (0x100UL << RCC_CRRCR_HSI48CAL_Pos) /*!< 0x00000100 */
#define RCC_CRRCR_HSI48CAL_9                   (0x200UL << RCC_CRRCR_HSI48CAL_Pos) /*!< 0x00000200 */


/********************  Bit definition for RCC_CSICFGR register  *****************/
/*!< CSICAL configuration */
#define RCC_CSICFGR_CSICAL_Pos                 (0U)
#define RCC_CSICFGR_CSICAL_Msk                 (0xFFUL << RCC_CSICFGR_CSICAL_Pos) /*!< 0x000000FF */
#define RCC_CSICFGR_CSICAL                     RCC_CSICFGR_CSICAL_Msk          /*!< CSICAL[7:0] bits */
#define RCC_CSICFGR_CSICAL_0                   (0x01UL << RCC_CSICFGR_CSICAL_Pos) /*!< 0x00000001 */
#define RCC_CSICFGR_CSICAL_1                   (0x02UL << RCC_CSICFGR_CSICAL_Pos) /*!< 0x00000002 */
#define RCC_CSICFGR_CSICAL_2                   (0x04UL << RCC_CSICFGR_CSICAL_Pos) /*!< 0x00000004 */
#define RCC_CSICFGR_CSICAL_3                   (0x08UL << RCC_CSICFGR_CSICAL_Pos) /*!< 0x00000008 */
#define RCC_CSICFGR_CSICAL_4                   (0x10UL << RCC_CSICFGR_CSICAL_Pos) /*!< 0x00000010 */
#define RCC_CSICFGR_CSICAL_5                   (0x20UL << RCC_CSICFGR_CSICAL_Pos) /*!< 0x00000020 */
#define RCC_CSICFGR_CSICAL_6                   (0x40UL << RCC_CSICFGR_CSICAL_Pos) /*!< 0x00000040 */
#define RCC_CSICFGR_CSICAL_7                   (0x80UL << RCC_CSICFGR_CSICAL_Pos) /*!< 0x00000080 */

/*!< CSITRIM configuration */
#define RCC_CSICFGR_CSITRIM_Pos                (24U)
#define RCC_CSICFGR_CSITRIM_Msk                (0x3FUL << RCC_CSICFGR_CSITRIM_Pos) /*!< 0x3F000000 */
#define RCC_CSICFGR_CSITRIM                    RCC_CSICFGR_CSITRIM_Msk         /*!< CSITRIM[5:0] bits */
#define RCC_CSICFGR_CSITRIM_0                  (0x01UL << RCC_CSICFGR_CSITRIM_Pos) /*!< 0x01000000 */
#define RCC_CSICFGR_CSITRIM_1                  (0x02UL << RCC_CSICFGR_CSITRIM_Pos) /*!< 0x02000000 */
#define RCC_CSICFGR_CSITRIM_2                  (0x04UL << RCC_CSICFGR_CSITRIM_Pos) /*!< 0x04000000 */
#define RCC_CSICFGR_CSITRIM_3                  (0x08UL << RCC_CSICFGR_CSITRIM_Pos) /*!< 0x08000000 */
#define RCC_CSICFGR_CSITRIM_4                  (0x10UL << RCC_CSICFGR_CSITRIM_Pos) /*!< 0x10000000 */
#define RCC_CSICFGR_CSITRIM_5                  (0x20UL << RCC_CSICFGR_CSITRIM_Pos) /*!< 0x20000000 */

/********************  Bit definition for RCC_CFGR register  ******************/
/*!< SW configuration */
#define RCC_CFGR_SW_Pos                        (0U)
#define RCC_CFGR_SW_Msk                        (0x7UL << RCC_CFGR_SW_Pos)           /*!< 0x00000007 */
#define RCC_CFGR_SW                            RCC_CFGR_SW_Msk                     /*!< SW[2:0] bits (System clock Switch) */
#define RCC_CFGR_SW_0                          (0x1UL << RCC_CFGR_SW_Pos)           /*!< 0x00000001 */
#define RCC_CFGR_SW_1                          (0x2UL << RCC_CFGR_SW_Pos)           /*!< 0x00000002 */
#define RCC_CFGR_SW_2                          (0x4UL << RCC_CFGR_SW_Pos)           /*!< 0x00000004 */

#define RCC_CFGR_SW_HSI                        (0x00000000UL)                       /*!< HSI selection as system clock */
#define RCC_CFGR_SW_CSI                        (0x00000001UL)                       /*!< CSI selection as system clock */
#define RCC_CFGR_SW_HSE                        (0x00000002UL)                       /*!< HSE selection as system clock */
#define RCC_CFGR_SW_PLL1                       (0x00000003UL)                       /*!< PLL1 selection as system clock */

/*!< SWS configuration */
#define RCC_CFGR_SWS_Pos                       (3U)
#define RCC_CFGR_SWS_Msk                       (0x7UL << RCC_CFGR_SWS_Pos)          /*!< 0x00000038 */
#define RCC_CFGR_SWS                           RCC_CFGR_SWS_Msk                    /*!< SWS[2:0] bits (System Clock Switch Status) */
#define RCC_CFGR_SWS_0                         (0x1UL << RCC_CFGR_SWS_Pos)          /*!< 0x00000008 */
#define RCC_CFGR_SWS_1                         (0x2UL << RCC_CFGR_SWS_Pos)          /*!< 0x00000010 */
#define RCC_CFGR_SWS_2                         (0x4UL << RCC_CFGR_SWS_Pos)          /*!< 0x00000020 */

#define RCC_CFGR_SWS_HSI                       (0x00000000UL)                       /*!< HSI used as system clock */
#define RCC_CFGR_SWS_CSI                       (0x00000008UL)                       /*!< CSI used as system clock */
#define RCC_CFGR_SWS_HSE                       (0x00000010UL)                       /*!< HSE used as system clock */
#define RCC_CFGR_SWS_PLL1                      (0x00000018UL)                       /*!< PLL1 used as system clock */

#define RCC_CFGR_STOPWUCK_Pos                  (6U)
#define RCC_CFGR_STOPWUCK_Msk                  (0x1UL << RCC_CFGR_STOPWUCK_Pos)     /*!< 0x00000040 */
#define RCC_CFGR_STOPWUCK                      RCC_CFGR_STOPWUCK_Msk                /*!< Wake Up from stop and CSS backup clock selection */

#define RCC_CFGR_STOPKERWUCK_Pos               (7U)
#define RCC_CFGR_STOPKERWUCK_Msk               (0x1UL << RCC_CFGR_STOPKERWUCK_Pos)  /*!< 0x00000080 */
#define RCC_CFGR_STOPKERWUCK                   RCC_CFGR_STOPKERWUCK_Msk             /*!< Kernel Clock Selection after a Wake Up from STOP */

/*!< RTCPRE configuration */
#define RCC_CFGR_RTCPRE_Pos                    (8U)
#define RCC_CFGR_RTCPRE_Msk                    (0x3FUL << RCC_CFGR_RTCPRE_Pos)
#define RCC_CFGR_RTCPRE                        RCC_CFGR_RTCPRE_Msk                  /*!< 0x00003F00 */
#define RCC_CFGR_RTCPRE_0                      (0x1UL << RCC_CFGR_RTCPRE_Pos)        /*!< 0x00000100 */
#define RCC_CFGR_RTCPRE_1                      (0x2UL << RCC_CFGR_RTCPRE_Pos)        /*!< 0x00000200 */
#define RCC_CFGR_RTCPRE_2                      (0x4UL << RCC_CFGR_RTCPRE_Pos)        /*!< 0x00000400 */
#define RCC_CFGR_RTCPRE_3                      (0x8UL << RCC_CFGR_RTCPRE_Pos)        /*!< 0x00000800 */
#define RCC_CFGR_RTCPRE_4                      (0x10UL << RCC_CFGR_RTCPRE_Pos)       /*!< 0x00001000 */
#define RCC_CFGR_RTCPRE_5                      (0x20UL << RCC_CFGR_RTCPRE_Pos)       /*!< 0x00002000 */


/*!< TIMPRE configuration */
#define RCC_CFGR_TIMPRE_Pos                    (15U)
#define RCC_CFGR_TIMPRE_Msk                    (0x1UL << RCC_CFGR_TIMPRE_Pos)
#define RCC_CFGR_TIMPRE                        RCC_CFGR_TIMPRE_Msk                  /*!< 0x00008000 */

/*!< MCO1 configuration */
#define RCC_CFGR_MCO1_Pos                      (22U)
#define RCC_CFGR_MCO1_Msk                      (0x7UL << RCC_CFGR_MCO1_Pos)
#define RCC_CFGR_MCO1                          RCC_CFGR_MCO1_Msk                       /*!< 0x01C00000 */
#define RCC_CFGR_MCO1_0                        (0x1UL <<  RCC_CFGR_MCO1_Pos)            /*!< 0x00400000 */
#define RCC_CFGR_MCO1_1                        (0x2UL <<  RCC_CFGR_MCO1_Pos)            /*!< 0x00800000 */
#define RCC_CFGR_MCO1_2                        (0x4UL <<  RCC_CFGR_MCO1_Pos)            /*!< 0x01000000 */

#define RCC_CFGR_MCO1PRE_Pos                   (18U)
#define RCC_CFGR_MCO1PRE_Msk                   (0xFUL << RCC_CFGR_MCO1PRE_Pos)
#define RCC_CFGR_MCO1PRE                       RCC_CFGR_MCO1PRE_Msk                    /*!< 0x003C0000 */
#define RCC_CFGR_MCO1PRE_0                     (0x1UL << RCC_CFGR_MCO1PRE_Pos)          /*!< 0x00040000 */
#define RCC_CFGR_MCO1PRE_1                     (0x2UL << RCC_CFGR_MCO1PRE_Pos)          /*!< 0x00080000 */
#define RCC_CFGR_MCO1PRE_2                     (0x4UL << RCC_CFGR_MCO1PRE_Pos)          /*!< 0x00100000 */
#define RCC_CFGR_MCO1PRE_3                     (0x8UL << RCC_CFGR_MCO1PRE_Pos)          /*!< 0x00200000 */

#define RCC_CFGR_MCO2PRE_Pos                   (25U)
#define RCC_CFGR_MCO2PRE_Msk                   (0xFUL << RCC_CFGR_MCO2PRE_Pos)
#define RCC_CFGR_MCO2PRE                       RCC_CFGR_MCO2PRE_Msk                    /*!< 0x1E000000 */
#define RCC_CFGR_MCO2PRE_0                     (0x1UL << RCC_CFGR_MCO2PRE_Pos)          /*!< 0x02000000 */
#define RCC_CFGR_MCO2PRE_1                     (0x2UL << RCC_CFGR_MCO2PRE_Pos)          /*!< 0x04000000 */
#define RCC_CFGR_MCO2PRE_2                     (0x4UL << RCC_CFGR_MCO2PRE_Pos)          /*!< 0x08000000 */
#define RCC_CFGR_MCO2PRE_3                     (0x8UL << RCC_CFGR_MCO2PRE_Pos)          /*!< 0x10000000 */

#define RCC_CFGR_MCO2_Pos                      (29U)
#define RCC_CFGR_MCO2_Msk                      (0x7UL << RCC_CFGR_MCO2_Pos)
#define RCC_CFGR_MCO2                          RCC_CFGR_MCO2_Msk                       /*!< 0xE0000000 */
#define RCC_CFGR_MCO2_0                        (0x1UL << RCC_CFGR_MCO2_Pos)             /*!< 0x20000000 */
#define RCC_CFGR_MCO2_1                        (0x2UL << RCC_CFGR_MCO2_Pos)             /*!< 0x40000000 */
#define RCC_CFGR_MCO2_2                        (0x4UL << RCC_CFGR_MCO2_Pos)             /*!< 0x80000000 */

/********************  Bit definition for RCC_D1CFGR register  ******************/
/*!< D1HPRE configuration */
#define RCC_CDCFGR1_HPRE_Pos                    (0U)
#define RCC_CDCFGR1_HPRE_Msk                    (0xFUL << RCC_CDCFGR1_HPRE_Pos)  /*!< 0x0000000F */
#define RCC_CDCFGR1_HPRE                        RCC_CDCFGR1_HPRE_Msk             /*!< HPRE[3:0] bits (AHB3 prescaler) */
#define RCC_CDCFGR1_HPRE_0                      (0x1UL << RCC_CDCFGR1_HPRE_Pos)   /*!< 0x00000001 */
#define RCC_CDCFGR1_HPRE_1                      (0x2UL << RCC_CDCFGR1_HPRE_Pos)   /*!< 0x00000002 */
#define RCC_CDCFGR1_HPRE_2                      (0x4UL << RCC_CDCFGR1_HPRE_Pos)   /*!< 0x00000004 */
#define RCC_CDCFGR1_HPRE_3                      (0x8UL << RCC_CDCFGR1_HPRE_Pos)   /*!< 0x00000008 */

#define RCC_CDCFGR1_HPRE_DIV1                   ((uint32_t)0x00000000)                 /*!< AHB3 Clock not divided */
#define RCC_CDCFGR1_HPRE_DIV2_Pos               (3U)
#define RCC_CDCFGR1_HPRE_DIV2_Msk               (0x1UL << RCC_CDCFGR1_HPRE_DIV2_Pos)   /*!< 0x00000008 */
#define RCC_CDCFGR1_HPRE_DIV2                   RCC_CDCFGR1_HPRE_DIV2_Msk              /*!< AHB3 Clock divided by 2 */
#define RCC_CDCFGR1_HPRE_DIV4_Pos               (0U)
#define RCC_CDCFGR1_HPRE_DIV4_Msk               (0x9UL << RCC_CDCFGR1_HPRE_DIV4_Pos)   /*!< 0x00000009 */
#define RCC_CDCFGR1_HPRE_DIV4                   RCC_CDCFGR1_HPRE_DIV4_Msk              /*!< AHB3 Clock divided by 4 */
#define RCC_CDCFGR1_HPRE_DIV8_Pos               (1U)
#define RCC_CDCFGR1_HPRE_DIV8_Msk               (0x5UL << RCC_CDCFGR1_HPRE_DIV8_Pos)   /*!< 0x0000000A */
#define RCC_CDCFGR1_HPRE_DIV8                   RCC_CDCFGR1_HPRE_DIV8_Msk              /*!< AHB3 Clock divided by 8 */
#define RCC_CDCFGR1_HPRE_DIV16_Pos              (0U)
#define RCC_CDCFGR1_HPRE_DIV16_Msk              (0xBUL << RCC_CDCFGR1_HPRE_DIV16_Pos)  /*!< 0x0000000B */
#define RCC_CDCFGR1_HPRE_DIV16                  RCC_CDCFGR1_HPRE_DIV16_Msk             /*!< AHB3 Clock divided by 16 */
#define RCC_CDCFGR1_HPRE_DIV64_Pos              (2U)
#define RCC_CDCFGR1_HPRE_DIV64_Msk              (0x3UL << RCC_CDCFGR1_HPRE_DIV64_Pos)  /*!< 0x0000000C */
#define RCC_CDCFGR1_HPRE_DIV64                  RCC_CDCFGR1_HPRE_DIV64_Msk             /*!< AHB3 Clock divided by 64 */
#define RCC_CDCFGR1_HPRE_DIV128_Pos             (0U)
#define RCC_CDCFGR1_HPRE_DIV128_Msk             (0xDUL << RCC_CDCFGR1_HPRE_DIV128_Pos) /*!< 0x0000000D */
#define RCC_CDCFGR1_HPRE_DIV128                 RCC_CDCFGR1_HPRE_DIV128_Msk            /*!< AHB3 Clock divided by 128 */
#define RCC_CDCFGR1_HPRE_DIV256_Pos             (1U)
#define RCC_CDCFGR1_HPRE_DIV256_Msk             (0x7UL << RCC_CDCFGR1_HPRE_DIV256_Pos) /*!< 0x0000000E */
#define RCC_CDCFGR1_HPRE_DIV256                 RCC_CDCFGR1_HPRE_DIV256_Msk            /*!< AHB3 Clock divided by 256 */
#define RCC_CDCFGR1_HPRE_DIV512_Pos             (0U)
#define RCC_CDCFGR1_HPRE_DIV512_Msk             (0xFUL << RCC_CDCFGR1_HPRE_DIV512_Pos) /*!< 0x0000000F */
#define RCC_CDCFGR1_HPRE_DIV512                 RCC_CDCFGR1_HPRE_DIV512_Msk            /*!< AHB3 Clock divided by 512 */

/*!< D1PPRE configuration */
#define RCC_CDCFGR1_CDPPRE_Pos                  (4U)
#define RCC_CDCFGR1_CDPPRE_Msk                  (0x7UL << RCC_CDCFGR1_CDPPRE_Pos)      /*!< 0x00000070 */
#define RCC_CDCFGR1_CDPPRE                      RCC_CDCFGR1_CDPPRE_Msk                 /*!< CDPRE[2:0] bits (APB3 prescaler) */
#define RCC_CDCFGR1_CDPPRE_0                    (0x1UL << RCC_CDCFGR1_CDPPRE_Pos)      /*!< 0x00000010 */
#define RCC_CDCFGR1_CDPPRE_1                    (0x2UL << RCC_CDCFGR1_CDPPRE_Pos)      /*!< 0x00000020 */
#define RCC_CDCFGR1_CDPPRE_2                    (0x4UL << RCC_CDCFGR1_CDPPRE_Pos)      /*!< 0x00000040 */

#define RCC_CDCFGR1_CDPPRE_DIV1                 ((uint32_t)0x00000000)                 /*!< APB3 clock not divided */
#define RCC_CDCFGR1_CDPPRE_DIV2_Pos             (6U)
#define RCC_CDCFGR1_CDPPRE_DIV2_Msk             (0x1UL << RCC_CDCFGR1_CDPPRE_DIV2_Pos) /*!< 0x00000040 */
#define RCC_CDCFGR1_CDPPRE_DIV2                 RCC_CDCFGR1_CDPPRE_DIV2_Msk            /*!< APB3 clock divided by 2 */
#define RCC_CDCFGR1_CDPPRE_DIV4_Pos             (4U)
#define RCC_CDCFGR1_CDPPRE_DIV4_Msk             (0x5UL << RCC_CDCFGR1_CDPPRE_DIV4_Pos) /*!< 0x00000050 */
#define RCC_CDCFGR1_CDPPRE_DIV4                 RCC_CDCFGR1_CDPPRE_DIV4_Msk            /*!< APB3 clock divided by 4 */
#define RCC_CDCFGR1_CDPPRE_DIV8_Pos             (5U)
#define RCC_CDCFGR1_CDPPRE_DIV8_Msk             (0x3UL << RCC_CDCFGR1_CDPPRE_DIV8_Pos) /*!< 0x00000060 */
#define RCC_CDCFGR1_CDPPRE_DIV8                 RCC_CDCFGR1_CDPPRE_DIV8_Msk            /*!< APB3 clock divided by 8 */
#define RCC_CDCFGR1_CDPPRE_DIV16_Pos            (4U)
#define RCC_CDCFGR1_CDPPRE_DIV16_Msk            (0x7UL << RCC_CDCFGR1_CDPPRE_DIV16_Pos) /*!< 0x00000070 */
#define RCC_CDCFGR1_CDPPRE_DIV16                RCC_CDCFGR1_CDPPRE_DIV16_Msk            /*!< APB3 clock divided by 16 */

#define RCC_CDCFGR1_CDCPRE_Pos                  (8U)
#define RCC_CDCFGR1_CDCPRE_Msk                  (0xFUL << RCC_CDCFGR1_CDCPRE_Pos)       /*!< 0x00000F00 */
#define RCC_CDCFGR1_CDCPRE                      RCC_CDCFGR1_CDCPRE_Msk                  /*!< CDCPRE[2:0] bits (Domain 1 Core prescaler) */
#define RCC_CDCFGR1_CDCPRE_0                    (0x1UL << RCC_CDCFGR1_CDCPRE_Pos)       /*!< 0x00000100 */
#define RCC_CDCFGR1_CDCPRE_1                    (0x2UL << RCC_CDCFGR1_CDCPRE_Pos)       /*!< 0x00000200 */
#define RCC_CDCFGR1_CDCPRE_2                    (0x4UL << RCC_CDCFGR1_CDCPRE_Pos)       /*!< 0x00000400 */
#define RCC_CDCFGR1_CDCPRE_3                    (0x8UL << RCC_CDCFGR1_CDCPRE_Pos)       /*!< 0x00000800 */

#define RCC_CDCFGR1_CDCPRE_DIV1                 ((uint32_t)0x00000000)                  /*!< Domain 1 Core clock not divided */
#define RCC_CDCFGR1_CDCPRE_DIV2_Pos             (11U)
#define RCC_CDCFGR1_CDCPRE_DIV2_Msk             (0x1UL << RCC_CDCFGR1_CDCPRE_DIV2_Pos)  /*!< 0x00000800 */
#define RCC_CDCFGR1_CDCPRE_DIV2                 RCC_CDCFGR1_CDCPRE_DIV2_Msk             /*!< Domain 1 Core clock divided by 2 */
#define RCC_CDCFGR1_CDCPRE_DIV4_Pos             (8U)
#define RCC_CDCFGR1_CDCPRE_DIV4_Msk             (0x9UL << RCC_CDCFGR1_CDCPRE_DIV4_Pos)  /*!< 0x00000900 */
#define RCC_CDCFGR1_CDCPRE_DIV4                 RCC_CDCFGR1_CDCPRE_DIV4_Msk             /*!< Domain 1 Core clock divided by 4 */
#define RCC_CDCFGR1_CDCPRE_DIV8_Pos             (9U)
#define RCC_CDCFGR1_CDCPRE_DIV8_Msk             (0x5UL << RCC_CDCFGR1_CDCPRE_DIV8_Pos)  /*!< 0x00000A00 */
#define RCC_CDCFGR1_CDCPRE_DIV8                 RCC_CDCFGR1_CDCPRE_DIV8_Msk             /*!< Domain 1 Core clock divided by 8 */
#define RCC_CDCFGR1_CDCPRE_DIV16_Pos            (8U)
#define RCC_CDCFGR1_CDCPRE_DIV16_Msk            (0xBUL << RCC_CDCFGR1_CDCPRE_DIV16_Pos) /*!< 0x00000B00 */
#define RCC_CDCFGR1_CDCPRE_DIV16                RCC_CDCFGR1_CDCPRE_DIV16_Msk            /*!< Domain 1 Core clock divided by 16 */
#define RCC_CDCFGR1_CDCPRE_DIV64_Pos            (10U)
#define RCC_CDCFGR1_CDCPRE_DIV64_Msk            (0x3UL << RCC_CDCFGR1_CDCPRE_DIV64_Pos) /*!< 0x00000C00 */
#define RCC_CDCFGR1_CDCPRE_DIV64                RCC_CDCFGR1_CDCPRE_DIV64_Msk            /*!< Domain 1 Core clock divided by 64 */
#define RCC_CDCFGR1_CDCPRE_DIV128_Pos           (8U)
#define RCC_CDCFGR1_CDCPRE_DIV128_Msk           (0xDUL << RCC_CDCFGR1_CDCPRE_DIV128_Pos)/*!< 0x00000D00 */
#define RCC_CDCFGR1_CDCPRE_DIV128               RCC_CDCFGR1_CDCPRE_DIV128_Msk           /*!< Domain 1 Core clock divided by 128 */
#define RCC_CDCFGR1_CDCPRE_DIV256_Pos           (9U)
#define RCC_CDCFGR1_CDCPRE_DIV256_Msk           (0x7UL << RCC_CDCFGR1_CDCPRE_DIV256_Pos)/*!< 0x00000E00 */
#define RCC_CDCFGR1_CDCPRE_DIV256               RCC_CDCFGR1_CDCPRE_DIV256_Msk           /*!< Domain 1 Core clock divided by 256 */
#define RCC_CDCFGR1_CDCPRE_DIV512_Pos           (8U)
#define RCC_CDCFGR1_CDCPRE_DIV512_Msk           (0xFUL << RCC_CDCFGR1_CDCPRE_DIV512_Pos)/*!< 0x00000F00 */
#define RCC_CDCFGR1_CDCPRE_DIV512               RCC_CDCFGR1_CDCPRE_DIV512_Msk           /*!< Domain 1 Core clock divided by 512 */

/********************  Bit definition for RCC_CDCFGR2 register  ******************/
/*!< CDPPRE1 configuration */
#define RCC_CDCFGR2_CDPPRE1_Pos                 (4U)
#define RCC_CDCFGR2_CDPPRE1_Msk                 (0x7UL << RCC_CDCFGR2_CDPPRE1_Pos) /*!< 0x00000070 */
#define RCC_CDCFGR2_CDPPRE1                     RCC_CDCFGR2_CDPPRE1_Msk          /*!< D1PPRE1[2:0] bits (APB1 prescaler) */
#define RCC_CDCFGR2_CDPPRE1_0                   (0x1UL << RCC_CDCFGR2_CDPPRE1_Pos) /*!< 0x00000010 */
#define RCC_CDCFGR2_CDPPRE1_1                   (0x2UL << RCC_CDCFGR2_CDPPRE1_Pos) /*!< 0x00000020 */
#define RCC_CDCFGR2_CDPPRE1_2                   (0x4UL << RCC_CDCFGR2_CDPPRE1_Pos) /*!< 0x00000040 */

#define RCC_CDCFGR2_CDPPRE1_DIV1                ((uint32_t)0x00000000)          /*!< APB1 clock not divided */
#define RCC_CDCFGR2_CDPPRE1_DIV2_Pos            (6U)
#define RCC_CDCFGR2_CDPPRE1_DIV2_Msk            (0x1UL << RCC_CDCFGR2_CDPPRE1_DIV2_Pos) /*!< 0x00000040 */
#define RCC_CDCFGR2_CDPPRE1_DIV2                RCC_CDCFGR2_CDPPRE1_DIV2_Msk     /*!< APB1 clock divided by 2 */
#define RCC_CDCFGR2_CDPPRE1_DIV4_Pos            (4U)
#define RCC_CDCFGR2_CDPPRE1_DIV4_Msk            (0x5UL << RCC_CDCFGR2_CDPPRE1_DIV4_Pos) /*!< 0x00000050 */
#define RCC_CDCFGR2_CDPPRE1_DIV4                RCC_CDCFGR2_CDPPRE1_DIV4_Msk     /*!< APB1 clock divided by 4 */
#define RCC_CDCFGR2_CDPPRE1_DIV8_Pos            (5U)
#define RCC_CDCFGR2_CDPPRE1_DIV8_Msk            (0x3UL << RCC_CDCFGR2_CDPPRE1_DIV8_Pos) /*!< 0x00000060 */
#define RCC_CDCFGR2_CDPPRE1_DIV8                RCC_CDCFGR2_CDPPRE1_DIV8_Msk     /*!< APB1 clock divided by 8 */
#define RCC_CDCFGR2_CDPPRE1_DIV16_Pos           (4U)
#define RCC_CDCFGR2_CDPPRE1_DIV16_Msk           (0x7UL << RCC_CDCFGR2_CDPPRE1_DIV16_Pos) /*!< 0x00000070 */
#define RCC_CDCFGR2_CDPPRE1_DIV16               RCC_CDCFGR2_CDPPRE1_DIV16_Msk    /*!< APB1 clock divided by 16 */

/*!< CDPPRE2 configuration */
#define RCC_CDCFGR2_CDPPRE2_Pos                 (8U)
#define RCC_CDCFGR2_CDPPRE2_Msk                 (0x7UL << RCC_CDCFGR2_CDPPRE2_Pos) /*!< 0x00000700 */
#define RCC_CDCFGR2_CDPPRE2                     RCC_CDCFGR2_CDPPRE2_Msk          /*!< CDPPRE2[2:0] bits (APB2 prescaler) */
#define RCC_CDCFGR2_CDPPRE2_0                   (0x1UL << RCC_CDCFGR2_CDPPRE2_Pos) /*!< 0x00000100 */
#define RCC_CDCFGR2_CDPPRE2_1                   (0x2UL << RCC_CDCFGR2_CDPPRE2_Pos) /*!< 0x00000200 */
#define RCC_CDCFGR2_CDPPRE2_2                   (0x4UL << RCC_CDCFGR2_CDPPRE2_Pos) /*!< 0x00000400 */

#define RCC_CDCFGR2_CDPPRE2_DIV1                ((uint32_t)0x00000000)          /*!< APB2 clock not divided */
#define RCC_CDCFGR2_CDPPRE2_DIV2_Pos            (10U)
#define RCC_CDCFGR2_CDPPRE2_DIV2_Msk            (0x1UL << RCC_CDCFGR2_CDPPRE2_DIV2_Pos) /*!< 0x00000400 */
#define RCC_CDCFGR2_CDPPRE2_DIV2                RCC_CDCFGR2_CDPPRE2_DIV2_Msk     /*!< APB2 clock divided by 2 */
#define RCC_CDCFGR2_CDPPRE2_DIV4_Pos            (8U)
#define RCC_CDCFGR2_CDPPRE2_DIV4_Msk            (0x5UL << RCC_CDCFGR2_CDPPRE2_DIV4_Pos) /*!< 0x00000500 */
#define RCC_CDCFGR2_CDPPRE2_DIV4                RCC_CDCFGR2_CDPPRE2_DIV4_Msk     /*!< APB2 clock divided by 4 */
#define RCC_CDCFGR2_CDPPRE2_DIV8_Pos            (9U)
#define RCC_CDCFGR2_CDPPRE2_DIV8_Msk            (0x3UL << RCC_CDCFGR2_CDPPRE2_DIV8_Pos) /*!< 0x00000600 */
#define RCC_CDCFGR2_CDPPRE2_DIV8                RCC_CDCFGR2_CDPPRE2_DIV8_Msk     /*!< APB2 clock divided by 8 */
#define RCC_CDCFGR2_CDPPRE2_DIV16_Pos           (8U)
#define RCC_CDCFGR2_CDPPRE2_DIV16_Msk           (0x7UL << RCC_CDCFGR2_CDPPRE2_DIV16_Pos) /*!< 0x00000700 */
#define RCC_CDCFGR2_CDPPRE2_DIV16               RCC_CDCFGR2_CDPPRE2_DIV16_Msk    /*!< APB2 clock divided by 16 */

/********************  Bit definition for RCC_SRDCFGR register  ******************/
/*!< SRDPPRE configuration */
#define RCC_SRDCFGR_SRDPPRE_Pos                  (4U)
#define RCC_SRDCFGR_SRDPPRE_Msk                  (0x7UL << RCC_SRDCFGR_SRDPPRE_Pos) /*!< 0x00000070 */
#define RCC_SRDCFGR_SRDPPRE                      RCC_SRDCFGR_SRDPPRE_Msk           /*!< SRDPPRE1[2:0] bits (APB4 prescaler) */
#define RCC_SRDCFGR_SRDPPRE_0                    (0x1UL << RCC_SRDCFGR_SRDPPRE_Pos) /*!< 0x00000010 */
#define RCC_SRDCFGR_SRDPPRE_1                    (0x2UL << RCC_SRDCFGR_SRDPPRE_Pos) /*!< 0x00000020 */
#define RCC_SRDCFGR_SRDPPRE_2                    (0x4UL << RCC_SRDCFGR_SRDPPRE_Pos) /*!< 0x00000040 */

#define RCC_SRDCFGR_SRDPPRE_DIV1                 ((uint32_t)0x00000000)          /*!< APB4 clock not divided */
#define RCC_SRDCFGR_SRDPPRE_DIV2_Pos             (6U)
#define RCC_SRDCFGR_SRDPPRE_DIV2_Msk             (0x1UL << RCC_SRDCFGR_SRDPPRE_DIV2_Pos) /*!< 0x00000040 */
#define RCC_SRDCFGR_SRDPPRE_DIV2                 RCC_SRDCFGR_SRDPPRE_DIV2_Msk      /*!< APB4 clock divided by 2 */
#define RCC_SRDCFGR_SRDPPRE_DIV4_Pos             (4U)
#define RCC_SRDCFGR_SRDPPRE_DIV4_Msk             (0x5UL << RCC_SRDCFGR_SRDPPRE_DIV4_Pos) /*!< 0x00000050 */
#define RCC_SRDCFGR_SRDPPRE_DIV4                 RCC_SRDCFGR_SRDPPRE_DIV4_Msk      /*!< APB4 clock divided by 4 */
#define RCC_SRDCFGR_SRDPPRE_DIV8_Pos             (5U)
#define RCC_SRDCFGR_SRDPPRE_DIV8_Msk             (0x3UL << RCC_SRDCFGR_SRDPPRE_DIV8_Pos) /*!< 0x00000060 */
#define RCC_SRDCFGR_SRDPPRE_DIV8                 RCC_SRDCFGR_SRDPPRE_DIV8_Msk      /*!< APB4 clock divided by 8 */
#define RCC_SRDCFGR_SRDPPRE_DIV16_Pos            (4U)
#define RCC_SRDCFGR_SRDPPRE_DIV16_Msk            (0x7UL << RCC_SRDCFGR_SRDPPRE_DIV16_Pos) /*!< 0x00000070 */
#define RCC_SRDCFGR_SRDPPRE_DIV16                RCC_SRDCFGR_SRDPPRE_DIV16_Msk     /*!< APB4 clock divided by 16 */

/********************  Bit definition for RCC_PLLCKSELR register  *************/

#define RCC_PLLCKSELR_PLLSRC_Pos               (0U)
#define RCC_PLLCKSELR_PLLSRC_Msk               (0x3UL << RCC_PLLCKSELR_PLLSRC_Pos) /*!< 0x00000003 */
#define RCC_PLLCKSELR_PLLSRC                   RCC_PLLCKSELR_PLLSRC_Msk

#define RCC_PLLCKSELR_PLLSRC_HSI               ((uint32_t)0x00000000)          /*!< HSI source clock selected */
#define RCC_PLLCKSELR_PLLSRC_CSI_Pos           (0U)
#define RCC_PLLCKSELR_PLLSRC_CSI_Msk           (0x1UL << RCC_PLLCKSELR_PLLSRC_CSI_Pos) /*!< 0x00000001 */
#define RCC_PLLCKSELR_PLLSRC_CSI               RCC_PLLCKSELR_PLLSRC_CSI_Msk    /*!< CSI source clock selected */
#define RCC_PLLCKSELR_PLLSRC_HSE_Pos           (1U)
#define RCC_PLLCKSELR_PLLSRC_HSE_Msk           (0x1UL << RCC_PLLCKSELR_PLLSRC_HSE_Pos) /*!< 0x00000002 */
#define RCC_PLLCKSELR_PLLSRC_HSE               RCC_PLLCKSELR_PLLSRC_HSE_Msk    /*!< HSE source clock selected */
#define RCC_PLLCKSELR_PLLSRC_NONE_Pos          (0U)
#define RCC_PLLCKSELR_PLLSRC_NONE_Msk          (0x3UL << RCC_PLLCKSELR_PLLSRC_NONE_Pos) /*!< 0x00000003 */
#define RCC_PLLCKSELR_PLLSRC_NONE              RCC_PLLCKSELR_PLLSRC_NONE_Msk   /*!< No source clock selected  */

#define RCC_PLLCKSELR_DIVM1_Pos                (4U)
#define RCC_PLLCKSELR_DIVM1_Msk                (0x3FUL << RCC_PLLCKSELR_DIVM1_Pos) /*!< 0x000003F0 */
#define RCC_PLLCKSELR_DIVM1                    RCC_PLLCKSELR_DIVM1_Msk
#define RCC_PLLCKSELR_DIVM1_0                  (0x01UL << RCC_PLLCKSELR_DIVM1_Pos) /*!< 0x00000010 */
#define RCC_PLLCKSELR_DIVM1_1                  (0x02UL << RCC_PLLCKSELR_DIVM1_Pos) /*!< 0x00000020 */
#define RCC_PLLCKSELR_DIVM1_2                  (0x04UL << RCC_PLLCKSELR_DIVM1_Pos) /*!< 0x00000040 */
#define RCC_PLLCKSELR_DIVM1_3                  (0x08UL << RCC_PLLCKSELR_DIVM1_Pos) /*!< 0x00000080 */
#define RCC_PLLCKSELR_DIVM1_4                  (0x10UL << RCC_PLLCKSELR_DIVM1_Pos) /*!< 0x00000100 */
#define RCC_PLLCKSELR_DIVM1_5                  (0x20UL << RCC_PLLCKSELR_DIVM1_Pos) /*!< 0x00000200 */

#define RCC_PLLCKSELR_DIVM2_Pos                (12U)
#define RCC_PLLCKSELR_DIVM2_Msk                (0x3FUL << RCC_PLLCKSELR_DIVM2_Pos) /*!< 0x0003F000 */
#define RCC_PLLCKSELR_DIVM2                    RCC_PLLCKSELR_DIVM2_Msk
#define RCC_PLLCKSELR_DIVM2_0                  (0x01UL << RCC_PLLCKSELR_DIVM2_Pos) /*!< 0x00001000 */
#define RCC_PLLCKSELR_DIVM2_1                  (0x02UL << RCC_PLLCKSELR_DIVM2_Pos) /*!< 0x00002000 */
#define RCC_PLLCKSELR_DIVM2_2                  (0x04UL << RCC_PLLCKSELR_DIVM2_Pos) /*!< 0x00004000 */
#define RCC_PLLCKSELR_DIVM2_3                  (0x08UL << RCC_PLLCKSELR_DIVM2_Pos) /*!< 0x00008000 */
#define RCC_PLLCKSELR_DIVM2_4                  (0x10UL << RCC_PLLCKSELR_DIVM2_Pos) /*!< 0x00010000 */
#define RCC_PLLCKSELR_DIVM2_5                  (0x20UL << RCC_PLLCKSELR_DIVM2_Pos) /*!< 0x00020000 */

#define RCC_PLLCKSELR_DIVM3_Pos                (20U)
#define RCC_PLLCKSELR_DIVM3_Msk                (0x3FUL << RCC_PLLCKSELR_DIVM3_Pos) /*!< 0x03F00000 */
#define RCC_PLLCKSELR_DIVM3                    RCC_PLLCKSELR_DIVM3_Msk
#define RCC_PLLCKSELR_DIVM3_0                  (0x01UL << RCC_PLLCKSELR_DIVM3_Pos) /*!< 0x00100000 */
#define RCC_PLLCKSELR_DIVM3_1                  (0x02UL << RCC_PLLCKSELR_DIVM3_Pos) /*!< 0x00200000 */
#define RCC_PLLCKSELR_DIVM3_2                  (0x04UL << RCC_PLLCKSELR_DIVM3_Pos) /*!< 0x00400000 */
#define RCC_PLLCKSELR_DIVM3_3                  (0x08UL << RCC_PLLCKSELR_DIVM3_Pos) /*!< 0x00800000 */
#define RCC_PLLCKSELR_DIVM3_4                  (0x10UL << RCC_PLLCKSELR_DIVM3_Pos) /*!< 0x01000000 */
#define RCC_PLLCKSELR_DIVM3_5                  (0x20UL << RCC_PLLCKSELR_DIVM3_Pos) /*!< 0x02000000 */

/********************  Bit definition for RCC_PLLCFGR register  ***************/

#define RCC_PLLCFGR_PLL1FRACEN_Pos             (0U)
#define RCC_PLLCFGR_PLL1FRACEN_Msk             (0x1UL << RCC_PLLCFGR_PLL1FRACEN_Pos) /*!< 0x00000001 */
#define RCC_PLLCFGR_PLL1FRACEN                 RCC_PLLCFGR_PLL1FRACEN_Msk
#define RCC_PLLCFGR_PLL1VCOSEL_Pos             (1U)
#define RCC_PLLCFGR_PLL1VCOSEL_Msk             (0x1UL << RCC_PLLCFGR_PLL1VCOSEL_Pos) /*!< 0x00000002 */
#define RCC_PLLCFGR_PLL1VCOSEL                 RCC_PLLCFGR_PLL1VCOSEL_Msk
#define RCC_PLLCFGR_PLL1RGE_Pos                (2U)
#define RCC_PLLCFGR_PLL1RGE_Msk                (0x3UL << RCC_PLLCFGR_PLL1RGE_Pos) /*!< 0x0000000C */
#define RCC_PLLCFGR_PLL1RGE                    RCC_PLLCFGR_PLL1RGE_Msk
#define RCC_PLLCFGR_PLL1RGE_0                  (0x0UL << RCC_PLLCFGR_PLL1RGE_Pos) /*!< 0x00000000 */
#define RCC_PLLCFGR_PLL1RGE_1                  (0x1UL << RCC_PLLCFGR_PLL1RGE_Pos) /*!< 0x00000004 */
#define RCC_PLLCFGR_PLL1RGE_2                  (0x2UL << RCC_PLLCFGR_PLL1RGE_Pos) /*!< 0x00000008 */
#define RCC_PLLCFGR_PLL1RGE_3                  (0x3UL << RCC_PLLCFGR_PLL1RGE_Pos) /*!< 0x0000000C */

#define RCC_PLLCFGR_PLL2FRACEN_Pos             (4U)
#define RCC_PLLCFGR_PLL2FRACEN_Msk             (0x1UL << RCC_PLLCFGR_PLL2FRACEN_Pos) /*!< 0x00000010 */
#define RCC_PLLCFGR_PLL2FRACEN                 RCC_PLLCFGR_PLL2FRACEN_Msk
#define RCC_PLLCFGR_PLL2VCOSEL_Pos             (5U)
#define RCC_PLLCFGR_PLL2VCOSEL_Msk             (0x1UL << RCC_PLLCFGR_PLL2VCOSEL_Pos) /*!< 0x00000020 */
#define RCC_PLLCFGR_PLL2VCOSEL                 RCC_PLLCFGR_PLL2VCOSEL_Msk
#define RCC_PLLCFGR_PLL2RGE_Pos                (6U)
#define RCC_PLLCFGR_PLL2RGE_Msk                (0x3UL << RCC_PLLCFGR_PLL2RGE_Pos) /*!< 0x000000C0 */
#define RCC_PLLCFGR_PLL2RGE                    RCC_PLLCFGR_PLL2RGE_Msk
#define RCC_PLLCFGR_PLL2RGE_0                  (0x0UL << RCC_PLLCFGR_PLL2RGE_Pos) /*!< 0x00000000 */
#define RCC_PLLCFGR_PLL2RGE_1                  (0x1UL << RCC_PLLCFGR_PLL2RGE_Pos) /*!< 0x00000040 */
#define RCC_PLLCFGR_PLL2RGE_2                  (0x2UL << RCC_PLLCFGR_PLL2RGE_Pos) /*!< 0x00000080 */
#define RCC_PLLCFGR_PLL2RGE_3                  (0x3UL << RCC_PLLCFGR_PLL2RGE_Pos) /*!< 0x000000C0 */

#define RCC_PLLCFGR_PLL3FRACEN_Pos             (8U)
#define RCC_PLLCFGR_PLL3FRACEN_Msk             (0x1UL << RCC_PLLCFGR_PLL3FRACEN_Pos) /*!< 0x00000100 */
#define RCC_PLLCFGR_PLL3FRACEN                 RCC_PLLCFGR_PLL3FRACEN_Msk
#define RCC_PLLCFGR_PLL3VCOSEL_Pos             (9U)
#define RCC_PLLCFGR_PLL3VCOSEL_Msk             (0x1UL << RCC_PLLCFGR_PLL3VCOSEL_Pos) /*!< 0x00000200 */
#define RCC_PLLCFGR_PLL3VCOSEL                 RCC_PLLCFGR_PLL3VCOSEL_Msk
#define RCC_PLLCFGR_PLL3RGE_Pos                (10U)
#define RCC_PLLCFGR_PLL3RGE_Msk                (0x3UL << RCC_PLLCFGR_PLL3RGE_Pos) /*!< 0x00000C00 */
#define RCC_PLLCFGR_PLL3RGE                    RCC_PLLCFGR_PLL3RGE_Msk
#define RCC_PLLCFGR_PLL3RGE_0                  (0x0UL << RCC_PLLCFGR_PLL3RGE_Pos) /*!< 0x00000000 */
#define RCC_PLLCFGR_PLL3RGE_1                  (0x1UL << RCC_PLLCFGR_PLL3RGE_Pos) /*!< 0x00000400 */
#define RCC_PLLCFGR_PLL3RGE_2                  (0x2UL << RCC_PLLCFGR_PLL3RGE_Pos) /*!< 0x00000800 */
#define RCC_PLLCFGR_PLL3RGE_3                  (0x3UL << RCC_PLLCFGR_PLL3RGE_Pos) /*!< 0x00000C00 */

#define RCC_PLLCFGR_DIVP1EN_Pos                (16U)
#define RCC_PLLCFGR_DIVP1EN_Msk                (0x1UL << RCC_PLLCFGR_DIVP1EN_Pos) /*!< 0x00010000 */
#define RCC_PLLCFGR_DIVP1EN                    RCC_PLLCFGR_DIVP1EN_Msk
#define RCC_PLLCFGR_DIVQ1EN_Pos                (17U)
#define RCC_PLLCFGR_DIVQ1EN_Msk                (0x1UL << RCC_PLLCFGR_DIVQ1EN_Pos) /*!< 0x00020000 */
#define RCC_PLLCFGR_DIVQ1EN                    RCC_PLLCFGR_DIVQ1EN_Msk
#define RCC_PLLCFGR_DIVR1EN_Pos                (18U)
#define RCC_PLLCFGR_DIVR1EN_Msk                (0x1UL << RCC_PLLCFGR_DIVR1EN_Pos) /*!< 0x00040000 */
#define RCC_PLLCFGR_DIVR1EN                    RCC_PLLCFGR_DIVR1EN_Msk

#define RCC_PLLCFGR_DIVP2EN_Pos                (19U)
#define RCC_PLLCFGR_DIVP2EN_Msk                (0x1UL << RCC_PLLCFGR_DIVP2EN_Pos) /*!< 0x00080000 */
#define RCC_PLLCFGR_DIVP2EN                    RCC_PLLCFGR_DIVP2EN_Msk
#define RCC_PLLCFGR_DIVQ2EN_Pos                (20U)
#define RCC_PLLCFGR_DIVQ2EN_Msk                (0x1UL << RCC_PLLCFGR_DIVQ2EN_Pos) /*!< 0x00100000 */
#define RCC_PLLCFGR_DIVQ2EN                    RCC_PLLCFGR_DIVQ2EN_Msk
#define RCC_PLLCFGR_DIVR2EN_Pos                (21U)
#define RCC_PLLCFGR_DIVR2EN_Msk                (0x1UL << RCC_PLLCFGR_DIVR2EN_Pos) /*!< 0x00200000 */
#define RCC_PLLCFGR_DIVR2EN                    RCC_PLLCFGR_DIVR2EN_Msk

#define RCC_PLLCFGR_DIVP3EN_Pos                (22U)
#define RCC_PLLCFGR_DIVP3EN_Msk                (0x1UL << RCC_PLLCFGR_DIVP3EN_Pos) /*!< 0x00400000 */
#define RCC_PLLCFGR_DIVP3EN                    RCC_PLLCFGR_DIVP3EN_Msk
#define RCC_PLLCFGR_DIVQ3EN_Pos                (23U)
#define RCC_PLLCFGR_DIVQ3EN_Msk                (0x1UL << RCC_PLLCFGR_DIVQ3EN_Pos) /*!< 0x00800000 */
#define RCC_PLLCFGR_DIVQ3EN                    RCC_PLLCFGR_DIVQ3EN_Msk
#define RCC_PLLCFGR_DIVR3EN_Pos                (24U)
#define RCC_PLLCFGR_DIVR3EN_Msk                (0x1UL << RCC_PLLCFGR_DIVR3EN_Pos) /*!< 0x01000000 */
#define RCC_PLLCFGR_DIVR3EN                    RCC_PLLCFGR_DIVR3EN_Msk


/********************  Bit definition for RCC_PLL1DIVR register  ***************/
#define RCC_PLL1DIVR_N1_Pos                    (0U)
#define RCC_PLL1DIVR_N1_Msk                    (0x1FFUL << RCC_PLL1DIVR_N1_Pos) /*!< 0x000001FF */
#define RCC_PLL1DIVR_N1                        RCC_PLL1DIVR_N1_Msk
#define RCC_PLL1DIVR_P1_Pos                    (9U)
#define RCC_PLL1DIVR_P1_Msk                    (0x7FUL << RCC_PLL1DIVR_P1_Pos) /*!< 0x0000FE00 */
#define RCC_PLL1DIVR_P1                        RCC_PLL1DIVR_P1_Msk
#define RCC_PLL1DIVR_Q1_Pos                    (16U)
#define RCC_PLL1DIVR_Q1_Msk                    (0x7FUL << RCC_PLL1DIVR_Q1_Pos) /*!< 0x007F0000 */
#define RCC_PLL1DIVR_Q1                        RCC_PLL1DIVR_Q1_Msk
#define RCC_PLL1DIVR_R1_Pos                    (24U)
#define RCC_PLL1DIVR_R1_Msk                    (0x7FUL << RCC_PLL1DIVR_R1_Pos) /*!< 0x7F000000 */
#define RCC_PLL1DIVR_R1                        RCC_PLL1DIVR_R1_Msk

/********************  Bit definition for RCC_PLL1FRACR register  ***************/
#define RCC_PLL1FRACR_FRACN1_Pos               (3U)
#define RCC_PLL1FRACR_FRACN1_Msk               (0x1FFFUL << RCC_PLL1FRACR_FRACN1_Pos) /*!< 0x0000FFF8 */
#define RCC_PLL1FRACR_FRACN1                   RCC_PLL1FRACR_FRACN1_Msk

/********************  Bit definition for RCC_PLL2DIVR register  ***************/
#define RCC_PLL2DIVR_N2_Pos                    (0U)
#define RCC_PLL2DIVR_N2_Msk                    (0x1FFUL << RCC_PLL2DIVR_N2_Pos) /*!< 0x000001FF */
#define RCC_PLL2DIVR_N2                        RCC_PLL2DIVR_N2_Msk
#define RCC_PLL2DIVR_P2_Pos                    (9U)
#define RCC_PLL2DIVR_P2_Msk                    (0x7FUL << RCC_PLL2DIVR_P2_Pos) /*!< 0x0000FE00 */
#define RCC_PLL2DIVR_P2                        RCC_PLL2DIVR_P2_Msk
#define RCC_PLL2DIVR_Q2_Pos                    (16U)
#define RCC_PLL2DIVR_Q2_Msk                    (0x7FUL << RCC_PLL2DIVR_Q2_Pos) /*!< 0x007F0000 */
#define RCC_PLL2DIVR_Q2                        RCC_PLL2DIVR_Q2_Msk
#define RCC_PLL2DIVR_R2_Pos                    (24U)
#define RCC_PLL2DIVR_R2_Msk                    (0x7FUL << RCC_PLL2DIVR_R2_Pos) /*!< 0x7F000000 */
#define RCC_PLL2DIVR_R2                        RCC_PLL2DIVR_R2_Msk

/********************  Bit definition for RCC_PLL2FRACR register  ***************/
#define RCC_PLL2FRACR_FRACN2_Pos               (3U)
#define RCC_PLL2FRACR_FRACN2_Msk               (0x1FFFUL << RCC_PLL2FRACR_FRACN2_Pos) /*!< 0x0000FFF8 */
#define RCC_PLL2FRACR_FRACN2                   RCC_PLL2FRACR_FRACN2_Msk

/********************  Bit definition for RCC_PLL3DIVR register  ***************/
#define RCC_PLL3DIVR_N3_Pos                    (0U)
#define RCC_PLL3DIVR_N3_Msk                    (0x1FFUL << RCC_PLL3DIVR_N3_Pos) /*!< 0x000001FF */
#define RCC_PLL3DIVR_N3                        RCC_PLL3DIVR_N3_Msk
#define RCC_PLL3DIVR_P3_Pos                    (9U)
#define RCC_PLL3DIVR_P3_Msk                    (0x7FUL << RCC_PLL3DIVR_P3_Pos) /*!< 0x0000FE00 */
#define RCC_PLL3DIVR_P3                        RCC_PLL3DIVR_P3_Msk
#define RCC_PLL3DIVR_Q3_Pos                    (16U)
#define RCC_PLL3DIVR_Q3_Msk                    (0x7FUL << RCC_PLL3DIVR_Q3_Pos) /*!< 0x007F0000 */
#define RCC_PLL3DIVR_Q3                        RCC_PLL3DIVR_Q3_Msk
#define RCC_PLL3DIVR_R3_Pos                    (24U)
#define RCC_PLL3DIVR_R3_Msk                    (0x7FUL << RCC_PLL3DIVR_R3_Pos) /*!< 0x7F000000 */
#define RCC_PLL3DIVR_R3                        RCC_PLL3DIVR_R3_Msk

/********************  Bit definition for RCC_PLL3FRACR register  ***************/
#define RCC_PLL3FRACR_FRACN3_Pos               (3U)
#define RCC_PLL3FRACR_FRACN3_Msk               (0x1FFFUL << RCC_PLL3FRACR_FRACN3_Pos) /*!< 0x0000FFF8 */
#define RCC_PLL3FRACR_FRACN3                   RCC_PLL3FRACR_FRACN3_Msk

/********************  Bit definition for RCC_CSR register  *******************/
#define RCC_CSR_LSION_Pos                      (0U)
#define RCC_CSR_LSION_Msk                      (0x1UL << RCC_CSR_LSION_Pos)    /*!< 0x00000001 */
#define RCC_CSR_LSION                          RCC_CSR_LSION_Msk
#define RCC_CSR_LSIRDY_Pos                     (1U)
#define RCC_CSR_LSIRDY_Msk                     (0x1UL << RCC_CSR_LSIRDY_Pos)   /*!< 0x00000002 */
#define RCC_CSR_LSIRDY                         RCC_CSR_LSIRDY_Msk

/********************  Bit definition for RCC_BDCR register  ******************/
#define RCC_BDCR_LSEON_Pos                     (0U)
#define RCC_BDCR_LSEON_Msk                     (0x1UL << RCC_BDCR_LSEON_Pos)   /*!< 0x00000001 */
#define RCC_BDCR_LSEON                         RCC_BDCR_LSEON_Msk
#define RCC_BDCR_LSERDY_Pos                    (1U)
#define RCC_BDCR_LSERDY_Msk                    (0x1UL << RCC_BDCR_LSERDY_Pos)  /*!< 0x00000002 */
#define RCC_BDCR_LSERDY                        RCC_BDCR_LSERDY_Msk
#define RCC_BDCR_LSEBYP_Pos                    (2U)
#define RCC_BDCR_LSEBYP_Msk                    (0x1UL << RCC_BDCR_LSEBYP_Pos)  /*!< 0x00000004 */
#define RCC_BDCR_LSEBYP                        RCC_BDCR_LSEBYP_Msk

#endif /* STM32H7A3xxQ_H */
