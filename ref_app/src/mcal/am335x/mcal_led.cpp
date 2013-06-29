///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2013.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <dio.h>
#include <mcal_led.h>
#include <am335x_hw_regs.h>

#define  GetGroupNr(x) (((x) >> 5) & 0x07U)
#define  GetPortNr(x)  ((x)  &  0x1FU)

void Dio_WriteChannel(Dio_ChannelType ChannelId, Dio_LevelType Level)
{
  const std::uint32_t bit_val = std::uint32_t(1UL << GetPortNr(ChannelId));

  GPIO_TypeDef* gpio;

  switch(GetGroupNr(ChannelId))
  {
  default:
  case 0U:
    gpio  =  GPIO0;
    break;
  case 1U:
    gpio  =  GPIO1;
    break;
  case 2U:
    gpio  =  GPIO2;
    break;
  case 3U:
    gpio  =  GPIO3;
    break;
  }

  if(Level != Dio_LevelType(STD_LOW))
  {
    gpio->SETDATAOUT  =  bit_val;
  }
  else
  {
    gpio->CLEARDATAOUT  =  bit_val;
  }
}

namespace mcal
{
  namespace led
  {
    const led_type led0;
  }
}

void mcal::led::led::toggle() const
{
  // Toggle the LED state.
  is_on = (!is_on);

  (is_on ? Dio_WriteChannel(Do_LED3, STD_HIGH)
         : Dio_WriteChannel(Do_LED3, STD_LOW));
}
