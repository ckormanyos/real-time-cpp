///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2012 - 2020.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <mcal_spi.h>

#include <mcal_port_pin_dummy.h>
#include <mcal_spi.h>

#include <mcal_spi/mcal_spi_software_port_driver.h>

void mcal::spi::init(const mcal::spi::config_type*)
{
}

util::communication_base& mcal::spi::spi1()
{
  using local_port_pin_sck__type = mcal::port::port_pin<mcal::port::gpio_pin18_h12>;
  using local_port_pin_mosi_type = mcal::port::port_pin<mcal::port::gpio_pin19_h35>;
  using local_port_pin_csn__type = mcal::port::port_pin<mcal::port::gpio_pin16_h36>;

  using mcal_spi_channel1_type =
    mcal::spi::spi_software_port_driver<local_port_pin_sck__type,
                                        local_port_pin_mosi_type,
                                        local_port_pin_csn__type,
                                        mcal::port::port_pin_dummy,
                                        32U,
                                        false>;

  static mcal_spi_channel1_type com1;

  return com1;
}
