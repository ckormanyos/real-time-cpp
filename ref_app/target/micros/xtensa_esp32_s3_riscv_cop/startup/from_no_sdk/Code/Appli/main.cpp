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

extern "C" auto main() -> int;

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

  auto delay(const std::uint32_t loop_count) -> void
  {
    for (std::uint32_t loop { UINT32_C(0) }; loop < loop_count; ++loop)
    {
      main_counter = std::uint32_t { main_counter + UINT8_C(1) };
    }
  }
}

extern "C" auto main() -> int
{
  mcal::init();

  unsigned prescaler { UINT8_C(0) };
  unsigned cycle     { UINT8_C(0) };

  for(;;)
  {
    switch(unsigned { cycle % unsigned { UINT8_C(16) } })
    {
      case unsigned { UINT8_C( 0) }: mcal::led::led0().toggle(); delay(std::uint32_t { UINT8_C(60) }); mcal::led::led0().toggle(); delay(std::uint32_t { UINT8_C( 4) }); break;
      case unsigned { UINT8_C( 1) }: mcal::led::led0().toggle(); delay(std::uint32_t { UINT8_C(32) }); mcal::led::led0().toggle(); delay(std::uint32_t { UINT8_C(32) }); break;
      case unsigned { UINT8_C( 2) }: mcal::led::led0().toggle(); delay(std::uint32_t { UINT8_C( 8) }); mcal::led::led0().toggle(); delay(std::uint32_t { UINT8_C(56) }); break;
      case unsigned { UINT8_C( 3) }: mcal::led::led0().toggle(); delay(std::uint32_t { UINT8_C( 6) }); mcal::led::led0().toggle(); delay(std::uint32_t { UINT8_C(58) }); break;
      case unsigned { UINT8_C( 4) }: mcal::led::led0().toggle(); delay(std::uint32_t { UINT8_C( 4) }); mcal::led::led0().toggle(); delay(std::uint32_t { UINT8_C(60) }); break;
      case unsigned { UINT8_C( 5) }: mcal::led::led0().toggle(); delay(std::uint32_t { UINT8_C( 3) }); mcal::led::led0().toggle(); delay(std::uint32_t { UINT8_C(61) }); break;
      case unsigned { UINT8_C( 6) }: mcal::led::led0().toggle(); delay(std::uint32_t { UINT8_C( 2) }); mcal::led::led0().toggle(); delay(std::uint32_t { UINT8_C(62) }); break;
      case unsigned { UINT8_C( 7) }: mcal::led::led0().toggle(); delay(std::uint32_t { UINT8_C( 1) }); mcal::led::led0().toggle(); delay(std::uint32_t { UINT8_C(63) }); break;
      case unsigned { UINT8_C( 8) }: mcal::led::led0().toggle(); delay(std::uint32_t { UINT8_C( 1) }); mcal::led::led0().toggle(); delay(std::uint32_t { UINT8_C(60) }); break;
      case unsigned { UINT8_C( 9) }: mcal::led::led0().toggle(); delay(std::uint32_t { UINT8_C( 2) }); mcal::led::led0().toggle(); delay(std::uint32_t { UINT8_C(32) }); break;
      case unsigned { UINT8_C(10) }: mcal::led::led0().toggle(); delay(std::uint32_t { UINT8_C( 3) }); mcal::led::led0().toggle(); delay(std::uint32_t { UINT8_C( 8) }); break;
      case unsigned { UINT8_C(11) }: mcal::led::led0().toggle(); delay(std::uint32_t { UINT8_C( 4) }); mcal::led::led0().toggle(); delay(std::uint32_t { UINT8_C( 6) }); break;
      case unsigned { UINT8_C(12) }: mcal::led::led0().toggle(); delay(std::uint32_t { UINT8_C( 6) }); mcal::led::led0().toggle(); delay(std::uint32_t { UINT8_C( 4) }); break;
      case unsigned { UINT8_C(13) }: mcal::led::led0().toggle(); delay(std::uint32_t { UINT8_C( 8) }); mcal::led::led0().toggle(); delay(std::uint32_t { UINT8_C( 3) }); break;
      case unsigned { UINT8_C(14) }: mcal::led::led0().toggle(); delay(std::uint32_t { UINT8_C(32) }); mcal::led::led0().toggle(); delay(std::uint32_t { UINT8_C( 2) }); break;
      case unsigned { UINT8_C(15) }: mcal::led::led0().toggle(); delay(std::uint32_t { UINT8_C(60) }); mcal::led::led0().toggle(); delay(std::uint32_t { UINT8_C( 1) }); break;
    }

    if(unsigned { ++prescaler % unsigned { UINT8_C(1024) } } == unsigned { UINT8_C(0) })
    {
      ++cycle;
    }
  }
}
