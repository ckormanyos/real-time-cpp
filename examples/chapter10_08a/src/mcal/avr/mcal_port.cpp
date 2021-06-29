///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2020.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <mcal_port.h>
#include <mcal_port_expander_microchip_mcp23s17.h>
#include <mcal_port_word.h>
#include <mcal_spi.h>

namespace
{
  using port_word_expander_type = mcal::port::port_word_expander_microchip_mcp23s17<1U>;

  port_word_expander_type& mcal_port_word_expander_device()
  {
    static port_word_expander_type device(mcal::spi::spi0());

    return device;
  }

  //using port_pin_expander_type = mcal::port::port_pin_expander_microchip_mcp23s17<2U>;
  using port_pin_expander_type = mcal::port::port_pin_expander_microchip_mcp23s17_writeonly<2U>;

  port_pin_expander_type& mcal_port_pin_expander_device()
  {
    static port_pin_expander_type device(mcal::spi::spi0());

    return device;
  }
}

void mcal::port::init(const config_type*)
{
}

void mcal_port_word_expander_set_port(const uint16_t value_to_write)
{
  mcal_port_word_expander_device().set_port(value_to_write);
}

void mcal_port_word_expander_set_direction_output()
{
  mcal_port_word_expander_device().set_direction_output();
}

void mcal_port_word_expander_set_direction_input()
{
  mcal_port_word_expander_device().set_direction_input();
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
  return mcal_port_pin_expander_device().read_input_value(bpos);
}

void mcal_port_pin_expander_toggle_pin(const uint8_t bpos)
{
  mcal_port_pin_expander_device().toggle_pin(bpos);
}
