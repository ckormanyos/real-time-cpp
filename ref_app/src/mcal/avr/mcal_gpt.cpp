///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2013.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <chrono>
#include <mcal_gpt.h>
#include <mcal_reg_access.h>

namespace
{
  // The one (and only one) system tick.
  volatile mcal::gpt::value_type system_tick;

  mcal::gpt::value_type consistent_microsecond_tick()
  {
    // Return the system tick using a multiple read to ensure
    // data consistency of the high-byte of the system tick.

    typedef std::uint8_t timer_address_type;
    typedef std::uint8_t timer_register_type;

    // Do the first read of the timer0 counter and the system tick.
    const timer_register_type   tim0_cnt_1 = mcal::reg::access<timer_address_type, timer_register_type, mcal::reg::tcnt0>::reg_get();
    const mcal::gpt::value_type sys_tick_1 = system_tick;

    // Do the second read of the timer0 counter and the system tick.
    const timer_register_type   tim0_cnt_2 = mcal::reg::access<timer_address_type, timer_register_type, mcal::reg::tcnt0>::reg_get();
    const mcal::gpt::value_type sys_tick_2 = system_tick;

    // Perform the consistency check and return the consistent microsecond tick.
    return ((tim0_cnt_2 >= tim0_cnt_1) ? mcal::gpt::value_type(sys_tick_1 | std::uint8_t(std::uint16_t(std::uint16_t(tim0_cnt_1) + 1U) >> 1U))
                                       : mcal::gpt::value_type(sys_tick_2 | std::uint8_t(std::uint16_t(std::uint16_t(tim0_cnt_2) + 1U) >> 1U)));
  }
}

extern "C" void __vector_timer0_cmp_a_irq() __attribute__((signal, used, externally_visible));

void __vector_timer0_cmp_a_irq()
{
  // This interrupt occurs every 128us.
  // Increment the 32-bit system tick by 128.
  system_tick += std::uint8_t(0x80U);
}

void mcal::gpt::init(const config_type*)
{
  // Clear Timer0 Overflow Flag.
  mcal::reg::access<std::uint8_t, std::uint8_t, mcal::reg::tifr0, 0x02U>::reg_set();

  // Enable Compare Match A Interrupt.
  mcal::reg::access<std::uint8_t, std::uint8_t, mcal::reg::timsk0, 0x02U>::reg_set();

  // Set ctc mode 2 for counter timer0 compare.
  mcal::reg::access<std::uint8_t, std::uint8_t, mcal::reg::tccr0a, 0x02U>::reg_set();

  // Set the compare match a value to 255.
  mcal::reg::access<std::uint8_t, std::uint8_t, mcal::reg::ocr0a, 0xFFU>::reg_set();

  // Set the timer0 clock source to f_osc/8 = 2MHz and begin counting.
  mcal::reg::access<std::uint8_t, std::uint8_t, mcal::reg::tccr0b, 0x02U>::reg_set();
}

mcal::gpt::value_type mcal::gpt::get_time_elapsed()
{
  return consistent_microsecond_tick();
}

// Implement std::chrono::high_resolution_clock::now()
// for the standard library high-resolution clock.
namespace std
{
  namespace chrono
  {
    high_resolution_clock::time_point high_resolution_clock::now()
    {
      // The source of the high-resolution clock is microseconds.
      typedef std::chrono::time_point<high_resolution_clock, microseconds> microseconds_type;

      // Obtain a time-point from the consistent tick in units of microseconds.
      const microseconds_type my_now(std::chrono::microseconds(::consistent_microsecond_tick()));

      // Return the corresponding duration in microseconds.
      return std::chrono::high_resolution_clock::time_point(my_now);
    }
  }
}
