///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2014.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <cstddef>
#include <cstdint>
#include <mcal_led.h>
#include <mcal_reg_access.h>

mcal::led::led_type::led_type() : led_is_on(false)
{
  // Write 1 to the gpio16 init nibble in the function select 1 gpio
  // peripheral register to enable gpio16 as an output.
  mcal::reg::access<std::uint32_t, std::uint32_t, mcal::reg::gpio_gpfsel1, UINT32_C(18)>::bit_set();

  // Set the gpio16 output high (which turns the ok led off).
  mcal::reg::access<std::uint32_t, std::uint32_t, mcal::reg::gpio_gpset0, UINT32_C(16)>::bit_set();
}

void mcal::led::led_type::toggle() const
{
  // Toggle the led state.
  // Note here, however, that the logic of the ok led is inverted.

  (led_is_on ? mcal::reg::access<std::uint32_t, std::uint32_t, mcal::reg::gpio_gpset0, UINT32_C(16)>::bit_set()
             : mcal::reg::access<std::uint32_t, std::uint32_t, mcal::reg::gpio_gpclr0, UINT32_C(16)>::bit_set());

  led_is_on = (!led_is_on);
}

namespace mcal
{
  namespace led
  {
    const led_type led0;
  }
}
