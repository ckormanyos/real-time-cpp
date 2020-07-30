

/*******************************************************************************************************************
** Includes
*******************************************************************************************************************/
#include <gpio.h>
#include <mcu.h>

/*******************************************************************************************************************
** Defines
*******************************************************************************************************************/


/*******************************************************************************************************************
** Globals 
*******************************************************************************************************************/


/*******************************************************************************************************************
** Static functions
*******************************************************************************************************************/

/*******************************************************************************************************************
** Function:    
** Description: 
** Parameter:   
** Return:      
*******************************************************************************************************************/
void gpio_ClrPin(uint8 PortPin)
{

  const uint32 port    = (uint32)((PortPin & 0xF0u) >> 4u);
  const uint32 pin     = (uint32)(PortPin & 0x0Fu);
  const uint32 pos     = (uint32)((port * 10u) + pin);
  const uint32 addfsel = (uint32)(GPFSEL0_ADDR + (uint32)(4u*port));
  const uint32 valfsel = (uint32)GPIO_PIN_X_OUTPUT << (pin*3u);
  const uint32 addclr  = (uint32)((PortPin < 0x32u) ? GPCLR0_ADDR : GPCLR1_ADDR);
  const uint32 valclr  = (uint32)((uint32)GPIO_SET_GPIO_PIN_X << ((pos < 32u) ? (pos) : (pos - 32u)));

  /* Set GPIO mode */
  Mcu_WriteBcm2835Register(addfsel, (Mcu_ReadBcm2835Register(addfsel) | valfsel));

  /* set the gpio low */
  Mcu_WriteBcm2835Register(addclr, (Mcu_ReadBcm2835Register(addclr) | valclr));

}

/*******************************************************************************************************************
** Function:    
** Description: 
** Parameter:   
** Return:      
*******************************************************************************************************************/
void gpio_SetPin(uint8 PortPin)
{

  const uint32 port    = (uint32)((PortPin & 0xF0u) >> 4u);
  const uint32 pin     = (uint32)(PortPin & 0x0Fu);
  const uint32 pos     = (uint32)((port * 10u) + pin);
  const uint32 addfsel = (uint32)(GPFSEL0_ADDR + (uint32)(4u*port));
  const uint32 valfsel = (uint32)GPIO_PIN_X_OUTPUT << (pin*3u);
  const uint32 addset  = (uint32)((PortPin < 0x32u) ? GPSET0_ADDR : GPSET1_ADDR);
  const uint32 valset  = (uint32)((uint32)GPIO_SET_GPIO_PIN_X << ((pos < 32u) ? (pos) : (pos - 32u)));

  /* Set GPIO mode */
  Mcu_WriteBcm2835Register(addfsel, (Mcu_ReadBcm2835Register(addfsel) | valfsel));

  /* set the gpio high */
  Mcu_WriteBcm2835Register(addset, (Mcu_ReadBcm2835Register(addset) | valset));

}
