///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2025.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

// Originally from:
/******************************************************************************************
  Filename    : main.c
  
  Core        : RISC-V
  
  MCU         : ESP32-S3
    
  Author      : Chalandi Amine
 
  Owner       : Chalandi Amine
  
  Date        : 22.02.2025
  
  Description : Application main function for ULP-RISC-V Co-processor
  
******************************************************************************************/

#include <mcal_port.h>

#include <cstdint>

extern "C"
void main();

extern "C"
void main()
{
  // Set all GPIO out registers to low.
  mcal::reg::reg_access_static<std::uint32_t, std::uint32_t, mcal::reg::gpio::rtc_gpio_out_reg, UINT32_C(0)>::reg_set();

  // Configure GPIO17 as output low.
  using port_pin_type = mcal::port::port_pin<UINT32_C(17)>;

  port_pin_type::set_direction_output();

  for(;;)
  {
     port_pin_type::toggle_pin();

     for(uint32_t i=0; i< 0xC0000; i++)
     {
       asm volatile("nop");
     }
  }
}
