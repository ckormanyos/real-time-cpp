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

#include <mcal_gpt.h>
#include <mcal_led.h>
#include <mcal_port.h>

extern "C" void main();

namespace mcal
{
  auto init() -> void;

  auto init() -> void
  {
    mcal::port::init(nullptr);
    mcal::gpt::init(nullptr);
  }
}

namespace
{
  volatile std::uint32_t main_counter { };

  auto delay() -> void
  {
    constexpr std::uint32_t loop_count{ UINT32_C(0x00060000) };

    for (std::uint32_t loop{ UINT32_C(0) }; loop < loop_count; ++loop)
    {
      main_counter = std::uint32_t { main_counter + UINT8_C(1) };
    }
  }
}

extern "C" void main()
{
  mcal::init();

  for(;;)
  {
     mcal::led::led0().toggle();

     delay();
  }
}
