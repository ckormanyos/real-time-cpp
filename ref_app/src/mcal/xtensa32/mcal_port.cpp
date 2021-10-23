///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2018 - 2021.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <from_sdk/esp32-hal-gpio.h>

#include <mcal_port.h>

void mcal_port_pin_mode_out(const unsigned pin_index, const bool set_direction_to_output)
{
  const uint8_t idx = (uint8_t) pin_index;
  const uint8_t dir = (uint8_t) set_direction_to_output ? OUTPUT : INPUT;

  ::pinMode(idx, dir);
}

void mcal_port_pin_set(const unsigned pin_index, const bool set_value_to_high)
{
  const uint8_t idx = (uint8_t) pin_index;
  const uint8_t val = (uint8_t) set_value_to_high ? HIGH : LOW;

  ::digitalWrite(idx, val);
}

bool mcal_port_pin_read(const unsigned pin_index)
{
  const uint8_t idx = (uint8_t) pin_index;

  const int val = ::digitalRead((uint8_t) idx);

  return (val != 0);
}
