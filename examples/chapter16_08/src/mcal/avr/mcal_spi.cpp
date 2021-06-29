///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2012 - 2020.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <mcal_port.h>
#include <mcal_port_pin_dummy.h>
#include <mcal_spi.h>
#include <mcal_spi/mcal_spi_software_port_driver.h>

void mcal::spi::init(const config_type*)
{
}

util::communication_base& mcal::spi::spi1()
{
  using led_port_pin_expander_spi_port_pin_sck__type = mcal::port::port_pin<std::uint8_t, std::uint8_t, mcal::reg::portc, 3U>;
  using led_port_pin_expander_spi_port_pin_mosi_type = mcal::port::port_pin<std::uint8_t, std::uint8_t, mcal::reg::portc, 1U>;
  using led_port_pin_expander_spi_port_pin_csn__type = mcal::port::port_pin<std::uint8_t, std::uint8_t, mcal::reg::portc, 0U>;
  using led_port_pin_expander_spi_port_pin_miso_type = mcal::port::port_pin<std::uint8_t, std::uint8_t, mcal::reg::portc, 2U>;

  using led_port_pin_expander_spi_communication_type =
    mcal::spi::spi_software_port_driver<led_port_pin_expander_spi_port_pin_sck__type,
                                        led_port_pin_expander_spi_port_pin_mosi_type,
                                        led_port_pin_expander_spi_port_pin_csn__type,
                                        led_port_pin_expander_spi_port_pin_miso_type,
                                        0U,
                                        true>;

  static led_port_pin_expander_spi_communication_type com1;

  return com1;
}
