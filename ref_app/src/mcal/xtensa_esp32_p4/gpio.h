///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2026.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

// Originally from:

/******************************************************************************************
  Filename    : gpio.h
  
  Core        : RISC-V
  
  MCU         : ESP32-P4
    
  Author      : Chalandi Amine
 
  Owner       : Chalandi Amine
  
  Date        : 25.01.2026
  
  Description : GPIO driver header file
  
******************************************************************************************/
#ifndef GPIO_2026_02_13_H
  #define GPIO_2026_02_13_H

  #if defined(__cplusplus)
  #include <cstdint>
  #else
  #include <stdint.h>
  #endif

  #if defined(__cplusplus)
  extern "C"
  {
  #endif

  void gpio_cfg_output(const uint8_t pin);
  void gpio_set_output_level(const uint8_t pin, const uint8_t level);
  void gpio_toggle_output_level(const uint8_t pin);

  #if defined(__cplusplus)
  }
  #endif

#endif // GPIO_2026_02_13_H
