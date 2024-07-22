/******************************************************************************************
  Filename    : Gpio.h
  
  Core        : ARM Cortex-M0+
  
  MCU         : RP2040
    
  Author      : Chalandi Amine
 
  Owner       : Chalandi Amine
  
  Date        : 07.02.2023
  
  Description : GPIO driver header file for RP2040
  
******************************************************************************************/
#ifndef __RP2040_GPIO_H__
#define __RP2040_GPIO_H__

//=============================================================================
// Includes
//=============================================================================
#include "RP2040.h"
#include "Platform_Types.h"

#ifdef __cplusplus
extern "C" {
#endif

//=============================================================================
// Macros
//=============================================================================
#define GPIO_SET_DIRECTION_OUTPUT(pin)  SIO->GPIO_OE_CLR.bit.GPIO_OE_CLR |= 1UL<<pin; SIO->GPIO_OUT_CLR.bit.GPIO_OUT_CLR |= 1UL<<pin; \
                                        IO_BANK0->GPIO##pin##_CTRL.bit.FUNCSEL = IO_BANK0_GPIO##pin##_CTRL_FUNCSEL_sio_##pin; \
                                        SIO->GPIO_OE_SET.bit.GPIO_OE_SET |= 1UL<<pin


#define GPIO_SET_OUTPUT_HIGH(pin)       SIO->GPIO_OUT_SET.bit.GPIO_OUT_SET |= 1UL<<pin
#define GPIO_SET_OUTPUT_LOW(pin)        SIO->GPIO_OUT_CLR.bit.GPIO_OUT_CLR |= 1UL<<pin

#define GPIO_SET_OUTPUT_XOR(pin)        SIO->GPIO_OUT_XOR.bit.GPIO_OUT_XOR |= 1UL<<pin


//=============================================================================
// Defines
//=============================================================================
#define CPU_LOAD_CFG()                 GPIO_SET_DIRECTION_OUTPUT(22); PADS_BANK0->GPIO22.bit.SLEWFAST = 1u
#define CPU_LOAD_START_MEASUREMENT()   GPIO_SET_OUTPUT_HIGH(22)
#define CPU_LOAD_STOP_MEASUREMENT()    GPIO_SET_OUTPUT_LOW(22)

#define DMA_LOAD_CFG()                 GPIO_SET_DIRECTION_OUTPUT(27); PADS_BANK0->GPIO27.bit.SLEWFAST = 1u
#define DMA_LOAD_START_MEASUREMENT()   GPIO_SET_OUTPUT_HIGH(27)
#define DMA_LOAD_STOP_MEASUREMENT()    GPIO_SET_OUTPUT_LOW(27)

#define SEND_LOAD_CFG()                 GPIO_SET_DIRECTION_OUTPUT(26); PADS_BANK0->GPIO26.bit.SLEWFAST = 1u
#define SEND_LOAD_START_MEASUREMENT()   GPIO_SET_OUTPUT_HIGH(26)
#define SEND_LOAD_STOP_MEASUREMENT()    GPIO_SET_OUTPUT_LOW(26)

#define LED_GREEN                       25
#define LED_GREEN_CFG()                 GPIO_SET_DIRECTION_OUTPUT(25)
#define LED_GREEN_OFF()                 GPIO_SET_OUTPUT_LOW(25)
#define LED_GREEN_ON()                  GPIO_SET_OUTPUT_HIGH(25)
#define LED_GREEN_TOGGLE()              GPIO_SET_OUTPUT_XOR(25)

#ifdef __cplusplus
}
#endif

#endif /* __RP2040_GPIO_H__ */
