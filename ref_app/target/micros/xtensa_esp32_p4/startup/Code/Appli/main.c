/******************************************************************************************
  Filename    : main.c
  
  Core        : RISC-V
  
  MCU         : ESP32-P4
    
  Author      : Chalandi Amine
 
  Owner       : Chalandi Amine
  
  Date        : 25.01.2026
  
  Description : Application main function
  
******************************************************************************************/

#include <gpio.h>

#include <stdbool.h>

extern uint32_t osGetActiveCore(void);

extern void main_core0(void);
extern void main_core1(void);

void main_x(void) __attribute__((used,noinline));

void main_x(void)
{
  const bool core_id_is_zero = ((uint32_t) UINT8_C(0) == osGetActiveCore());

  if(core_id_is_zero)
  {
    gpio_cfg_output(7);
    gpio_cfg_output(8);
    gpio_cfg_output(24);
    gpio_cfg_output(25);
    gpio_cfg_output(46);
    gpio_cfg_output(47);
    gpio_cfg_output(48);
    gpio_cfg_output(54);
    gpio_cfg_output(20);
    gpio_cfg_output(19);
    gpio_cfg_output(18);
    gpio_cfg_output(17);
    gpio_cfg_output(16);
    gpio_cfg_output(15);
    gpio_cfg_output(14);
    gpio_cfg_output(33);
    gpio_cfg_output(32);
    gpio_cfg_output(27);
    gpio_cfg_output(26);
    gpio_cfg_output(23);
    gpio_cfg_output(32);
    gpio_cfg_output(21);
  }

  // Go to the core-specific main subroutines.
  if(core_id_is_zero)
  {
    main_core0();
  }
  else
  {
    main_core1();
  }
}
