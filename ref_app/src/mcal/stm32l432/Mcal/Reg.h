#ifndef REG_2023_08_26_H
  #define REG_2023_08_26_H

  #include <stdint.h>

  /* ----------------------------------------------------------------------------------- */
  /*  Types definition                                                                   */
  /* ----------------------------------------------------------------------------------- */

  /* ----------------------------------------------------------------------------------- */
  /* Macros                                                                              */
  /* ----------------------------------------------------------------------------------- */

  /* System Control Space Base Address */
  #define SCS_BASE            (0xE000E000UL)

  /* Core peripherals */
  #define STK_BASE            ((SCS_BASE + 0x0010UL))
  #define NVIC_BASE           ((SCS_BASE + 0x0100UL))
  #define SCB_BASE            ((SCS_BASE + 0x0D00UL))

  /* SCB registers */
  #define SCB_CPACR           (*(volatile uint32_t*)(SCB_BASE + 0x88UL))

  /* SysTick registers */
  #define STK_CTRL            (*(volatile uint32_t*)(STK_BASE + 0x00UL))
  #define STK_LOAD            (*(volatile uint32_t*)(STK_BASE + 0x04UL))
  #define STK_VAL             (*(volatile uint32_t*)(STK_BASE + 0x08UL))

  /* Base addresses for peripheral registers */
  #define RCC_BASE            0x40021000UL
  #define PWR_BASE            0x40007000UL
  #define FLASH_BASE          0x40022000UL
  #define GPIOB_BASE          0x48000400UL

  /* FLASH registers */
  #define FLASH_ACR           (*(volatile uint32_t*)(FLASH_BASE + 0x000UL))

  /* PWR registers */
  #define PWR_CR1             (*(volatile uint32_t*)(PWR_BASE + 0x000UL))
  #define PWR_SR2             (*(volatile uint32_t*)(PWR_BASE + 0x014UL))



  /* RCC Registers */
  #define RCC_CR              (*(volatile uint32_t*)(RCC_BASE + 0x00UL))
  #define RCC_ICSCR           (*(volatile uint32_t*)(RCC_BASE + 0x04UL))
  #define RCC_CFGR            (*(volatile uint32_t*)(RCC_BASE + 0x08UL))
  #define RCC_PLLCFGR         (*(volatile uint32_t*)(RCC_BASE + 0x0CUL))
  #define RCC_CIER            (*(volatile uint32_t*)(RCC_BASE + 0x18UL))
  #define RCC_AHB1ENR         (*(volatile uint32_t*)(RCC_BASE + 0x48UL))
  #define RCC_AHB2ENR         (*(volatile uint32_t*)(RCC_BASE + 0x4CUL))
  #define RCC_APB1ENR1        (*(volatile uint32_t*)(RCC_BASE + 0x58UL))
  #define RCC_APB1ENR2        (*(volatile uint32_t*)(RCC_BASE + 0x5CUL))
  #define RCC_APB2ENR         (*(volatile uint32_t*)(RCC_BASE + 0x60UL))

  /* GPIOB registers */
  #define GPIOB_MODER         (*(volatile uint32_t*)(GPIOB_BASE + 0x00UL))
  #define GPIOB_OTYPER        (*(volatile uint32_t*)(GPIOB_BASE + 0x04UL))
  #define GPIOB_OSPEEDR       (*(volatile uint32_t*)(GPIOB_BASE + 0x08UL))
  #define GPIOB_PUPDR         (*(volatile uint32_t*)(GPIOB_BASE + 0x0CUL))
  #define GPIOB_ODR           (*(volatile uint32_t*)(GPIOB_BASE + 0x14UL))
  #define GPIOB_AFRL          (*(volatile uint32_t*)(GPIOB_BASE + 0x20UL))
  #define GPIOB_AFRH          (*(volatile uint32_t*)(GPIOB_BASE + 0x24UL))



#endif /* REG_2023_08_26_H */
