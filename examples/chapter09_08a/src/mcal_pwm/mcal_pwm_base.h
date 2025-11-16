///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2020 - 2025.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef MCAL_PWM_BASE_2020_04_12_H
  #define MCAL_PWM_BASE_2020_04_12_H

  #include <util/utility/util_noncopyable.h>

  #include <cstdint>

  namespace mcal { namespace pwm {

  class pwm_base : private util::noncopyable // NOLINT(cppcoreguidelines-special-member-functions,hicpp-special-member-functions)
  {
  public:
    using duty_type = std::uint16_t;

    virtual ~pwm_base() = default;

    virtual auto init() -> bool = 0;

    virtual auto set_duty(const duty_type duty_cycle) -> void { my_duty_cycle = duty_cycle; }

    auto get_duty() const -> duty_type { return my_duty_cycle; }

  protected:
    explicit pwm_base(const duty_type initial_duty = static_cast<duty_type>(UINT8_C(0)))
      : my_duty_cycle(initial_duty) { }

  private:
    duty_type my_duty_cycle { }; // NOLINT(readability-identifier-naming)
  };

  } // namespace pwm
  } // namespace mcal

#endif // MCAL_PWM_BASE_2020_04_12_H
