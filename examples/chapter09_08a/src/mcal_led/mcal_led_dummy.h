///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2025.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef MCAL_LED_DUMMY_2025_02_22_H
  #define MCAL_LED_DUMMY_2025_02_22_H

  #include <mcal_led/mcal_led_boolean_state_base.h>
  #include <mcal_port.h>

  namespace mcal { namespace led {

  class led_dummy : public mcal::led::led_boolean_state_base
  {
  public:
    led_dummy() noexcept
    {
    }

    ~led_dummy() override = default;

    auto toggle() noexcept -> void override
    {
      using base_class_type = mcal::led::led_boolean_state_base;

      base_class_type::toggle();
    }
  };

  } // namespace led
  } // namespace mcal

#endif // MCAL_LED_DUMMY_2025_02_22_H
