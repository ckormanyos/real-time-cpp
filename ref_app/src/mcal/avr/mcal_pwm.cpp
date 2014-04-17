///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2013.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <mcal_pwm.h>

/*
namespace
{
  typedef mcal::pwm::pwm_type<std::uint8_t,
                              std::uint8_t,
                              mcal::reg::portb,
                              0U> pwm0_type;

  typedef mcal::pwm::pwm_type<std::uint8_t,
                              std::uint8_t,
                              mcal::reg::portb,
                              1U> pwm1_type;

  typedef mcal::pwm::pwm_type<std::uint8_t,
                              std::uint8_t,
                              mcal::reg::portb,
                              2U> pwm2_type;

  pwm0_type pwm0;
  pwm1_type pwm1;
  pwm2_type pwm2;
}
*/

extern "C" void __vector_13() __attribute__((signal, used, externally_visible));

void __vector_13()
{
/*
  // Service the PWMs.
  pwm0.service();
  pwm1.service();
  pwm2.service();

  // Preload Time Counter 1 Register.
  mcal::reg::access<std::uint8_t, std::uint8_t, mcal::reg::tcnt1h, 0xFF>::reg_set();
  mcal::reg::access<std::uint8_t, std::uint8_t, mcal::reg::tcnt1l, 0xCD>::reg_set();
*/
}

void mcal::pwm::init(const config_type*)
{
/*
  // Initialize a timer interrupt for 50 microseconds.

  // Clear the timer1 overflow flag.
  mcal::reg::access<std::uint8_t, std::uint8_t, mcal::reg::tifr1, 0x01U>::reg_set();

  // Preload Time Counter 1 High Register.
  mcal::reg::access<std::uint8_t, std::uint8_t, mcal::reg::tcnt1h, 0xFF>::reg_set();
  mcal::reg::access<std::uint8_t, std::uint8_t, mcal::reg::tcnt1l, 0xCD>::reg_set();

  // Enable the timer1 overflow interrupt.
  mcal::reg::access<std::uint8_t, std::uint8_t, mcal::reg::timsk1, 0x01U>::reg_set();

  // Set the timer1 clock source to f_osc/8 = 2MHz and begin counting.
  mcal::reg::access<std::uint8_t, std::uint8_t, mcal::reg::tccr1b, 0x02U>::reg_set();
*/
}

void mcal::pwm::set_duty_cycle(const std::uint8_t channel, const std::uint8_t duty_cycle)
{
  static_cast<void>(channel);
  static_cast<void>(duty_cycle);
/*
  const std::uint8_t max_duty_cycle = pwm0.get_period();

  if(channel == static_cast<std::uint8_t>(0U))
  {
    pwm0.set_duty(std::min(max_duty_cycle, duty_cycle));
  }
  else if(channel == static_cast<std::uint8_t>(1U))
  {
    pwm1.set_duty(std::min(max_duty_cycle, duty_cycle));
  }
  else if(channel == static_cast<std::uint8_t>(2U))
  {
    pwm2.set_duty(std::min(max_duty_cycle, duty_cycle));
  }
*/
}
