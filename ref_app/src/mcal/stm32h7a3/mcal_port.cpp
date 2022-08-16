///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2022.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <mcal_port.h>
#include <mcal_reg.h>

namespace local
{
  using led_port_type = mcal::port::port_pin<std::uint32_t,
                                             std::uint32_t,
                                             mcal::reg::gpiob_base,
                                             static_cast<std::uint32_t>(UINT8_C(0))>;
} // namespace local

void mcal::port::init(const config_type*)
{
  mcal::reg::reg_access_static<std::uint32_t,
                               std::uint32_t,
                               mcal::reg::rcc_ahb4enr,
                               static_cast<std::uint32_t>(UINT8_C(0x0A))>::reg_or();

  const volatile auto ahb4enr_portb_is_on = mcal::reg::reg_access_static<std::uint32_t,
                                                                         std::uint32_t,
                                                                         mcal::reg::rcc_ahb4enr>::reg_get();

  static_cast<void>(ahb4enr_portb_is_on);
}
