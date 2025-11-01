///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2025.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <mcal_led.h>
#include <mcal_led/mcal_led_boolean_state_base.h>
#include <mcal_reg.h>
#include <util/utility/util_time.h>

#include "BL602.h"

#include <cstdint>

class led_port_tmp_bl606 : public mcal::led::led_boolean_state_base
{
public:
  led_port_tmp_bl606() noexcept
  {
    /* configure IO3 as output */
    glb->GPIO_CFGCTL1.bit.reg_gpio_3_func_sel = GPIO_FUN_SWGPIO;
    glb->GPIO_CFGCTL1.bit.reg_gpio_3_ie       = 0ul;
    glb->GPIO_CFGCTL1.bit.reg_gpio_3_drv      = 0ul;
    glb->GPIO_CFGCTL1.bit.reg_gpio_3_smt      = 0ul;
    glb->GPIO_CFGCTL34.bit.reg_gpio_3_oe      = 1ul;
  }

  ~led_port_tmp_bl606() override = default;

  auto toggle() noexcept -> void override
  {
    using base_class_type = led_boolean_state_base;

    // Toggle the IO3 pin.
    mcal::reg::reg_access_static<std::uintptr_t, std::uint32_t, mcal::reg::gpio_cfgctl32, UINT32_C(3)>::bit_not();
    //glb->GPIO_CFGCTL32.bit.reg_gpio_3_o ^= 1ul;

    base_class_type::toggle();
  }
};

auto mcal::led::led0() -> mcal::led::led_base&
{
  using led0_led_type = led_port_tmp_bl606;

  static led0_led_type l0;

  return l0;
}

