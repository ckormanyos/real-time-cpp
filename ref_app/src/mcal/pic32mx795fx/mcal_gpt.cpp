
///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2014.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <mcal_gpt.h>
#include <mcal_reg_access.h>

namespace
{
  // The one (and only one) system tick.
  volatile mcal::gpt::value_type system_tick;

  bool& gpt_is_initialized()
  {
    static bool is_init;

    return is_init;
  }

  // Here are some parameters that define the timer1 period.

  constexpr std::uint_least16_t timer1_period_in_ticks        = UINT16_C(40000);
  constexpr std::uint_least16_t timer1_period_in_microseconds = UINT16_C(1000);
  constexpr std::uint_least16_t timer1_ticks_per_microseconds = static_cast<std::uint_least16_t>(timer1_period_in_ticks / timer1_period_in_microseconds);

  static_assert(static_cast<std::uint_least16_t>(timer1_period_in_ticks % timer1_period_in_microseconds) == UINT16_C(0),
                "The timer1 microsecond period must evenly divide the timer1 tick period.");
}

extern "C" void __attribute__((nomips16, interrupt, used, noinline)) __vector_timer1();

void __attribute__((nomips16, interrupt, used, noinline)) __vector_timer1()
{
  // Increment the system tick.
  system_tick += timer1_period_in_microseconds;

  // Clear the timer1 interrupt request flag.
  mcal::reg::access<std::uint32_t,
                    std::uint32_t,
                    mcal::reg::ifs0,
                    UINT32_C(4)>::bit_clr();
}

void mcal::gpt::init(const config_type*)
{
  if(gpt_is_initialized() == false)
  {
    // Setup timer1 for basic operation with a prescaler of 1.
    mcal::reg::access<std::uint32_t,
                      std::uint32_t,
                      mcal::reg::t1con,
                      UINT32_C(0)>::reg_set();

    // Set the timer1 period.
    mcal::reg::access<std::uint32_t,
                      std::uint32_t,
                      mcal::reg::pr1,
                      static_cast<std::uint32_t>(timer1_period_in_ticks)>::reg_set();

    // Set the timer1 interrupt priority to 6.
    mcal::reg::access<std::uint32_t,
                      std::uint32_t,
                      mcal::reg::ipc1,
                      static_cast<std::uint32_t>(UINT32_C(6) << 2)>::reg_or();

    // Set the timer1 interrupt subpriority to 0.
    mcal::reg::access<std::uint32_t,
                      std::uint32_t,
                      mcal::reg::ipc1,
                      static_cast<std::uint32_t>(~UINT32_C(3))>::reg_and();

    // Clear the timer1 interrupt request flag.
    mcal::reg::access<std::uint32_t,
                      std::uint32_t,
                      mcal::reg::ifs0,
                      UINT32_C(4)>::bit_clr();

    // Enable the timer1 interrupt.
    mcal::reg::access<std::uint32_t,
                      std::uint32_t,
                      mcal::reg::iec0,
                      UINT32_C(4)>::bit_set();

    // Start timer1 counting.
    mcal::reg::access<std::uint32_t,
                      std::uint32_t,
                      mcal::reg::t1con,
                      UINT32_C(15)>::bit_set();

    gpt_is_initialized() = true;
  }
}

mcal::gpt::value_type mcal::gpt::secure::get_time_elapsed()
{
  if(gpt_is_initialized())
  {
    // Return the system tick using a multiple read to ensure data consistency.

    typedef std::uint32_t timer_address_type;
    typedef std::uint16_t timer_register_type;

    // Do the first read of the timer1 counter and the system tick.
    const timer_register_type   tmr1_cnt_1 = mcal::reg::access<timer_address_type, timer_register_type, mcal::reg::tmr1>::reg_get();
    const mcal::gpt::value_type sys_tick_1 = system_tick;

    // Do the second read of the timer1 counter.
    const timer_register_type   tmr1_cnt_2 = mcal::reg::access<timer_address_type, timer_register_type, mcal::reg::tmr1>::reg_get();

    // Perform the consistency check.
    const mcal::gpt::value_type consistent_microsecond_tick
      = ((tmr1_cnt_2 >= tmr1_cnt_1) ? mcal::gpt::value_type(sys_tick_1  | ((tmr1_cnt_1 + (timer1_ticks_per_microseconds / 2U)) / timer1_ticks_per_microseconds))
                                    : mcal::gpt::value_type(system_tick | ((tmr1_cnt_2 + (timer1_ticks_per_microseconds / 2U)) / timer1_ticks_per_microseconds)));

    return consistent_microsecond_tick;
  }
  else
  {
    return mcal::gpt::value_type(0U);
  }
}
