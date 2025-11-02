///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2025.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <mcal_port.h>
#include <mcal_pwm.h>
#include <mcal_pwm_board.h>
#include <mcal_reg.h>

#include <cstdint>

auto mcal::pwm::mcal_pwm0() -> mcal::pwm::pwm_base&
{
  using port0_type = mcal::port::port_pin<std::uint8_t,
                                          std::uint8_t,
                                          mcal::reg::portc,
                                          UINT8_C(3)>;

  using pwm0_type = mcal::pwm::pwm_board<port0_type>;

  using local_duty_type = typename pwm0_type::duty_type;

  static pwm0_type the_pwm0(local_duty_type { UINT8_C(100) });

  return the_pwm0;
}

auto mcal::pwm::mcal_pwm1() -> mcal::pwm::pwm_base&
{
  using port1_type = mcal::port::port_pin<std::uint8_t,
                                          std::uint8_t,
                                          mcal::reg::portc,
                                          UINT8_C(4)>;

  using pwm1_type = mcal::pwm::pwm_board<port1_type>;

  using local_duty_type = typename pwm1_type::duty_type;

  static pwm1_type the_pwm1(local_duty_type { UINT8_C(100) });

  return the_pwm1;
}

auto mcal::pwm::mcal_pwm2() -> mcal::pwm::pwm_base&
{
  using port2_type = mcal::port::port_pin<std::uint8_t,
                                          std::uint8_t,
                                          mcal::reg::portc,
                                          UINT8_C(5)>;

  using pwm2_type = mcal::pwm::pwm_board<port2_type>;

  using local_duty_type = typename pwm2_type::duty_type;

  static pwm2_type the_pwm2(local_duty_type { UINT8_C(100) });

  return the_pwm2;
}
