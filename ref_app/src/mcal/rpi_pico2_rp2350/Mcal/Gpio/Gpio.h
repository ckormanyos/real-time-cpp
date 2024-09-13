/******************************************************************************************
  Filename    : Gpio.h
  
  Core        : ARM Cortex-M33 / RISC-V Hazard3
  
  MCU         : RP2350
    
  Author      : Chalandi Amine
 
  Owner       : Chalandi Amine
  
  Date        : 04.09.2024
  
  Description : GPIO driver header file for RP2350
  
******************************************************************************************/
#ifndef __RP2350_GPIO_H__
#define __RP2350_GPIO_H__

//=============================================================================
// Includes
//=============================================================================
#include "RP2350.h"
#include "Platform_Types.h"

//=============================================================================
// Macros
//=============================================================================
#define GPIO_SET_DIRECTION_OUTPUT(pin)  HW_PER_SIO->GPIO_OE_CLR.bit.GPIO_OE_CLR |= 1UL<<pin; HW_PER_SIO->GPIO_OUT_CLR.bit.GPIO_OUT_CLR |= 1UL<<pin; \
                                        HW_PER_IO_BANK0->GPIO##pin##_CTRL.bit.FUNCSEL = IO_BANK0_GPIO##pin##_CTRL_FUNCSEL_siob_proc_##pin; \
                                        HW_PER_SIO->GPIO_OE_SET.bit.GPIO_OE_SET |= 1UL<<pin; HW_PER_PADS_BANK0->GPIO##pin.bit.ISO = 0u

#define PIO_SET_DIRECTION_OUTPUT(id, pin) HW_PER_SIO->GPIO_OE_CLR.bit.GPIO_OE_CLR |= 1UL<<pin; HW_PER_SIO->GPIO_OUT_CLR.bit.GPIO_OUT_CLR |= 1UL<<pin;\
                                          HW_PER_IO_BANK0->GPIO##pin##_CTRL.bit.FUNCSEL = IO_BANK0_GPIO##pin##_CTRL_FUNCSEL_pio##id##_##pin; \
                                          HW_PER_SIO->GPIO_OE_SET.bit.GPIO_OE_SET |= 1UL<<pin

#define GPIO_SET_OUTPUT_HIGH(pin)       HW_PER_SIO->GPIO_OUT_SET.bit.GPIO_OUT_SET |= 1UL<<pin
#define GPIO_SET_OUTPUT_LOW(pin)        HW_PER_SIO->GPIO_OUT_CLR.bit.GPIO_OUT_CLR |= 1UL<<pin

#define GPIO_SET_OUTPUT_XOR(pin)        HW_PER_SIO->GPIO_OUT_XOR.bit.GPIO_OUT_XOR |= 1UL<<pin


//=============================================================================
// Defines
//=============================================================================

#define LED_GREEN_CFG()               GPIO_SET_DIRECTION_OUTPUT(25)
#define LED_GREEN_OFF()               GPIO_SET_OUTPUT_LOW(25)
#define LED_GREEN_ON()                GPIO_SET_OUTPUT_HIGH(25)
#define LED_GREEN_TOGGLE()            GPIO_SET_OUTPUT_XOR(25)

#define LED_RED_CFG()                 GPIO_SET_DIRECTION_OUTPUT(18)
#define LED_RED_OFF()                 GPIO_SET_OUTPUT_LOW(18)
#define LED_RED_ON()                  GPIO_SET_OUTPUT_HIGH(18)
#define LED_RED_TOGGLE()              GPIO_SET_OUTPUT_XOR(18)

#define LED_BLUE_CFG()                GPIO_SET_DIRECTION_OUTPUT(20)
#define LED_BLUE_OFF()                GPIO_SET_OUTPUT_LOW(20)
#define LED_BLUE_ON()                 GPIO_SET_OUTPUT_HIGH(20)
#define LED_BLUE_TOGGLE()             GPIO_SET_OUTPUT_XOR(20)

#endif /* __RP2350_GPIO_H__ */
