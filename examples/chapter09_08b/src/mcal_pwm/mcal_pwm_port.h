///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2025.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef MCAL_PWM_PORT_2023_08_23_H
  #define MCAL_PWM_PORT_2023_08_23_H

  #include <mcal_pwm/mcal_pwm_base.h>

  #include <algorithm>

  namespace mcal { namespace pwm {

  // A software PWM template for a port-pin having the standard
  // port interface for ref_app. The default resolution is 100 ticks.

  template<typename PortPinType>
  class pwm_port : public pwm_base
  {
  private:
    using base_class_type = pwm_base;
    using port_pin_type = PortPinType;

  public:
    using base_class_type::duty_type;

    explicit pwm_port(const duty_type initial_duty = static_cast<duty_type>(UINT8_C(0)))
      : base_class_type(initial_duty),
        my_duty_shadow(initial_duty)
    {
      port_pin_type::set_pin_low();
      port_pin_type::set_direction_output();
    }

    ~pwm_port() override = default;

    auto init() -> bool override
    {
      return true;
    }

    static constexpr auto get_resolution() -> duty_type { return duty_type { UINT16_C(1000) }; }

    auto set_duty(const duty_type duty_cycle) -> void override
    {
      my_duty_shadow = (std::min)(duty_cycle, get_resolution());
    }

    auto service() -> void
    {
      // Increment the cycle counter.
      ++my_cycle_counter;

      ((my_cycle_counter <= base_class_type::get_duty()) ? port_pin_type::set_pin_high() : port_pin_type::set_pin_low());

      if(my_cycle_counter == get_resolution())
      {
        // Latch the duty cycle from the shadow register.
        // This is done at the end of the running cycle.
        base_class_type::set_duty(my_duty_shadow);

        // Reset the cycle counter for a new PWM period.
        my_cycle_counter = static_cast<duty_type>(UINT8_C(0));
      }
    }

  private:
    duty_type my_cycle_counter { };
    duty_type my_duty_shadow { };
  };

  } // namespace pwm
  } // namespace mcal

#endif // MCAL_PWM_PORT_2023_08_23_H
