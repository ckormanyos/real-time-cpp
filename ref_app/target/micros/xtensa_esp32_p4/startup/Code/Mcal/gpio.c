/******************************************************************************************
  Filename    : gpio.c
  
  Core        : RISC-V
  
  MCU         : ESP32-P4
    
  Author      : Chalandi Amine
 
  Owner       : Chalandi Amine
  
  Date        : 25.01.2026
  
  Description : GPIO driver implementation
  
******************************************************************************************/

//-----------------------------------------------------------------------------------------
// Includes
//-----------------------------------------------------------------------------------------
#include "gpio.h"


//-----------------------------------------------------------------------------------------
// Types
//-----------------------------------------------------------------------------------------

typedef union {
  volatile uint32_t reg;
 
  struct {
    volatile uint32_t MCU_OE     : 1;
    volatile uint32_t SLP_SEL    : 1;
    volatile uint32_t MCU_WPD    : 1;
    volatile uint32_t MCU_WPU    : 1;
    volatile uint32_t MCU_IE     : 1;
    volatile uint32_t MCU_DRV    : 2;
    volatile uint32_t FUN_WPD    : 1;
    volatile uint32_t FUN_WPU    : 1;
    volatile uint32_t FUN_IE     : 1;
    volatile uint32_t FUN_DRV    : 2;
    volatile uint32_t MCU_SEL    : 3;
    volatile uint32_t FILTER_EN  : 1;
             uint32_t            : 16;
  } bit;
} IO_MUX_GPIO;

typedef union {
  __IOM uint32_t reg;
    
  struct {
    __IOM uint32_t OUT_SEL     : 9;
    __IOM uint32_t INV_SEL     : 1;
    __IOM uint32_t OEN_SEL     : 1;
    __IOM uint32_t OEN_INV_SEL : 1;
          uint32_t             : 20;
  } bit;
} GPIO_FUNC_OUT_SEL_CFG;

typedef union {
  __IOM uint32_t reg;
  
  struct {
    __IOM uint32_t REG_PAD_DRV       : 2;
    __IOM uint32_t REG_PAD_RDE       : 1;
    __IOM uint32_t REG_PAD_RUE       : 1;
    __IOM uint32_t REG_PAD_MUX_SEL   : 1;
    __IOM uint32_t REG_PAD_FUN_SEL   : 2;
    __IOM uint32_t REG_PAD_SLP_SEL   : 1;
    __IOM uint32_t REG_PAD_SLP_IE    : 1;
    __IOM uint32_t REG_PAD_SLP_OE    : 1;
    __IOM uint32_t REG_PAD_FUN_IE    : 1;
    __IOM uint32_t REG_PAD_FILTER_EN : 1;
          uint32_t                   : 20;
  } bit;
} LP_IO_MUX_GPIO;

//-----------------------------------------------------------------------------------------
/// \brief  
///
/// \param  
///
/// \return 
//-----------------------------------------------------------------------------------------
void gpio_cfg_output(uint8_t pin)
{
  if(pin > 54)
     return;
  
  volatile IO_MUX_GPIO* pIO_MUX_GPIO = (volatile IO_MUX_GPIO*)(IO_MUX_BASE + 4ul + 4ul*pin);
  volatile GPIO_FUNC_OUT_SEL_CFG* pGPIO_FUNC_OUT_SEL_CFG = (volatile GPIO_FUNC_OUT_SEL_CFG*)(GPIO_BASE + 0x558ul + 4ul*pin);
  volatile LP_IO_MUX_GPIO* pLP_IO_MUX_GPIO = (volatile LP_IO_MUX_GPIO*)(LP_IO_MUX_BASE + 8ul + 4ul*pin);
  volatile uint32_t* pGPIO_OUTx_W1TC     = (volatile uint32_t*)(GPIO_BASE + ((pin < 32u) ? (0x0Cul) : (0x18ul)));
  volatile uint32_t* pGPIO_ENABLE1x_W1TS = (volatile uint32_t*)(GPIO_BASE + ((pin < 32u) ? (0x24ul) : (0x30ul)));

  /* configure the pinmux */
  pIO_MUX_GPIO->bit.FUN_DRV = 2;
  pIO_MUX_GPIO->bit.FUN_IE  = 0;
  pIO_MUX_GPIO->bit.MCU_SEL = 1;

  /* set the output configuration */
  pGPIO_FUNC_OUT_SEL_CFG->bit.OUT_SEL = 256;
  pGPIO_FUNC_OUT_SEL_CFG->bit.OEN_SEL = 1;

  if(pin < 16)
  {
    /* make LP_GPIO use HP_IO_MUX */
    pLP_IO_MUX_GPIO->bit.REG_PAD_MUX_SEL = 0;
  }
  
  /* drive the IO output low */
  *pGPIO_OUTx_W1TC     = (uint32_t)(1ul << ((pin < 32ul) ? (pin) : (pin - 32ul)));
  *pGPIO_ENABLE1x_W1TS = (uint32_t)(1ul << ((pin < 32ul) ? (pin) : (pin - 32ul)));
}

//-----------------------------------------------------------------------------------------
/// \brief  
///
/// \param  
///
/// \return 
//-----------------------------------------------------------------------------------------
void gpio_set_output_level(uint8_t pin, uint8_t level)
{
  volatile uint32_t* pGPIO_OUT_W1Tx = (volatile uint32_t*)(GPIO_BASE + ((pin < 32u) ? (8ul) : (0x14ul)) + ((level == 1u) ? (0ul) : (4ul)));

  if((pin > 54) && (level > 1))
    return;

  *pGPIO_OUT_W1Tx = (uint32_t)(1ul << ((pin < 32ul) ? (pin) : (pin - 32ul)));
}

//-----------------------------------------------------------------------------------------
/// \brief  
///
/// \param  
///
/// \return 
//-----------------------------------------------------------------------------------------
void gpio_toggle_output_level(uint8_t pin)
{
  volatile uint32_t* pGPIO_OUT = (volatile uint32_t*)(GPIO_BASE + 4ul + ((pin < 32u) ? 0ul : 0xcul));

  if(pin > 54)
    return;

  *pGPIO_OUT ^= (uint32_t)(1ul << ((pin < 32u) ? (pin) : (pin - 32u)));
}