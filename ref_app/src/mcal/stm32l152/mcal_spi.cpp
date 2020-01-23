///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2012 - 2020.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <mcal_spi.h>

void mcal::spi::init(const mcal::spi::config_type*)
{
}

bool mcal::spi::spi_communication::send(const std::uint8_t byte_to_send)
{
  const bool send_is_ok = true;

  static_cast<void>(byte_to_send);

  return send_is_ok;
}

util::communication_base& mcal::spi::spi0()
{
  static mcal::spi::spi_communication com;

  return com;
}
