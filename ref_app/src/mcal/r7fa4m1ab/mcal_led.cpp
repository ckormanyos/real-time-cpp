///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2026.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <mcal_led.h>
#include <mcal_led/mcal_led_port.h>
#include <mcal_reg.h>

class led_minima_blinky : public mcal::led::led_boolean_state_base
{
public:
  led_minima_blinky()
  {
    // Configure pin P111 as output.
    // Disable register write protection for PFS.
    // PMISC->PWPR.bit.B0WI  = 0;
    // PMISC->PWPR.bit.PFSWE = 1;

    mcal::reg::reg_access_static<std::uint32_t, std::uint8_t, mcal::reg::pmisc_pwpr, UINT8_C(7)>::bit_clr();
    mcal::reg::reg_access_static<std::uint32_t, std::uint8_t, mcal::reg::pmisc_pwpr, UINT8_C(6)>::bit_set();

    // Configure the pin as output low.
    //PFS->P111PFS.bit.PODR = 0;
    //PFS->P111PFS.bit.PDR  = 1;
    mcal::reg::reg_access_static<std::uint32_t, std::uint32_t, mcal::reg::pfs_p111pfs_base, UINT32_C(0)>::bit_clr();
    mcal::reg::reg_access_static<std::uint32_t, std::uint32_t, mcal::reg::pfs_p111pfs_base, UINT32_C(2)>::bit_set();
  }

  ~led_minima_blinky() override = default;

  auto toggle() noexcept -> void override
  {
    using base_class_type = led_boolean_state_base;

    // Toggle the LED.
    // PFS->P111PFS.bit.PODR ^= 1;
    mcal::reg::reg_access_static<std::uint32_t, std::uint32_t, mcal::reg::pfs_p111pfs_base, UINT32_C(0)>::bit_not();

    base_class_type::toggle();
  }
};

mcal::led::led_base& mcal::led::led0()
{
  using led0_led_type = led_minima_blinky;

  static led0_led_type l0;

  return l0;
}
