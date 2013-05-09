///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2013.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <mcal_spi.h>
#include <mcal_reg_access.h>

void mcal::spi::init(const config_type*)
{
  // Disable the SPI(TM) end-of-transmission interrupt
  // by clearing the spie bit in the spcr register.
  mcal::reg::access<std::uint8_t, std::uint8_t, mcal::reg::spcr, 7U>::bit_clr();
}

mcal::spi::spi_communication::~spi_communication()
{
}
