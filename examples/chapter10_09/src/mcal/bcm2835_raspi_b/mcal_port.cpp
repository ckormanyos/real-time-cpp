///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2020.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <mcal_port.h>
#include <mcal_port_expander_microchip_mcp23s17.h>

namespace
{
  mcal::port::port_pin_expander_microchip_mcp23s17<2U>& mcal_port_pin_expander_device()
  {
    using port_pin_expander_type = mcal::port::port_pin_expander_microchip_mcp23s17<2U>;

    static port_pin_expander_type device(mcal::spi::spi1());

    return device;
  }
}

void mcal::port::init(const config_type*)
{
}

void mcal_port_pin_expander_set_direction_output(const uint8_t bpos)
{
  mcal_port_pin_expander_device().set_direction_output(bpos);
}

void mcal_port_pin_expander_set_direction_input(const uint8_t bpos)
{
  mcal_port_pin_expander_device().set_direction_input(bpos);
}

void mcal_port_pin_expander_set_pin_high(const uint8_t bpos)
{
  mcal_port_pin_expander_device().set_pin_high(bpos);
}

void mcal_port_pin_expander_set_pin_low(const uint8_t bpos)
{
  mcal_port_pin_expander_device().set_pin_low(bpos);
}

bool mcal_port_pin_expander_read_input_value(const uint8_t bpos)
{
  (void) bpos;

  return false;
}

void mcal_port_pin_expander_toggle_pin(const uint8_t bpos)
{
  mcal_port_pin_expander_device().toggle_pin(bpos);
}
