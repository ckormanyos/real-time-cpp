/******************************************************************************************
  Filename    : gpio.h
  
  Core        : RISC-V
  
  MCU         : ESP32-P4
    
  Author      : Chalandi Amine
 
  Owner       : Chalandi Amine
  
  Date        : 25.01.2026
  
  Description : GPIO driver header file
  
******************************************************************************************/
#ifndef __GPIO_H__
#define __GPIO_H__
//-----------------------------------------------------------------------------------------
// Includes
//-----------------------------------------------------------------------------------------

#include <esp32p4.h>

#include <stdio.h>
#include <stdint.h>

#if defined(__cplusplus)
extern "C"
{
#endif

void gpio_cfg_output(uint8_t pin);
void gpio_set_output_level(uint8_t pin, uint8_t level);
void gpio_toggle_output_level(uint8_t pin);

#if defined(__cplusplus)
}
#endif

#endif /*__GPIO_H__*/
