///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2018 - 2021.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <from_sdk/esp32-hal-gpio.h>

#include <mcal_port.h>
#include <mcal_reg.h>

void mcal::port::init(const config_type*)
{
}

extern "C"
void mcal_port_pin_mode_out(const unsigned pin_index, bool set_direction_to_output)
{
  ::pinMode(pin_index, set_direction_to_output ? OUTPUT : INPUT);
}

extern "C"
void mcal_port_pin_set(const unsigned pin_index, bool set_value_to_high)
{
  ::digitalWrite(pin_index, set_value_to_high ? HIGH : LOW);
}

extern "C"
bool mcal_port_pin_read(const unsigned pin_index)
{
  const int n_port_value = ::digitalRead(pin_index);

  return (n_port_value != 0);
}
