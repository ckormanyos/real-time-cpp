///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2025.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <mcal_led.h>
#include <mcal_led/mcal_led_port.h>
#include <mcal_port.h>
#include <mcal_reg.h>

namespace local
{
  template<const unsigned LedId>
  struct led_x
  {
    static auto get_led_ref() -> mcal::led::led_base&;
  };

  template<const unsigned LedId>
  auto led_x<LedId>::get_led_ref() -> mcal::led::led_base&
  {
    using local_led_port_type = mcal::port::port_pin<mcal::reg::gpio0, LedId>;

    static mcal::led::led_port<local_led_port_type> led_instance;

    return led_instance;
  }
} // namespace local

auto mcal::led::led0() -> mcal::led::led_base& { return local::led_x<mcal::led::LED_ID_1>::get_led_ref(); }
auto mcal::led::led1() -> mcal::led::led_base& { return local::led_x<mcal::led::LED_ID_2>::get_led_ref(); }
auto mcal::led::led2() -> mcal::led::led_base& { return local::led_x<mcal::led::LED_ID_3>::get_led_ref(); }
auto mcal::led::led3() -> mcal::led::led_base& { return local::led_x<mcal::led::LED_ID_4>::get_led_ref(); }
