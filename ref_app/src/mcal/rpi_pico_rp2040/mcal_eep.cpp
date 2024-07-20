///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2022.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <mcal_eep.h>

void mcal::eep::write(const address_type addr, const std::uint8_t data)
{
  static_cast<void>(addr);
  static_cast<void>(data);
}

std::uint8_t mcal::eep::read(const address_type addr)
{
  static_cast<void>(addr);

  return std::uint8_t(0U);
}
