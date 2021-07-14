///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2020.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef MCAL_PWM_BASE_2020_04_12_H_
  #define MCAL_PWM_BASE_2020_04_12_H_

  #include <cstdint>

  #include <util/utility/util_noncopyable.h>

  namespace mcal { namespace pwm {

  class pwm_base : private util::noncopyable
  {
  public:
    virtual ~pwm_base() = default;

    virtual bool init() noexcept = 0;

    virtual void set_duty(const std::uint16_t duty_cycle) noexcept = 0;

    std::uint16_t get_duty() const noexcept { return my_duty_cycle; }

  protected:
    pwm_base() : my_duty_cycle(0U) { }

  protected:
    std::uint16_t my_duty_cycle;
  };

  } }

#endif // MCAL_PWM_BASE_2020_04_12_H_
