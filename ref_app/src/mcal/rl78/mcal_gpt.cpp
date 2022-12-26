///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2015.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <mcal_gpt.h>
#include <mcal_reg.h>

namespace
{
  // The one (and only one) system tick.
  volatile mcal::gpt::value_type mcal_gpt_system_tick;

  bool& gpt_is_initialized() __attribute__((used, noinline));

  bool& gpt_is_initialized()
  {
    static bool is_init = bool();

    return is_init;
  }
}

extern "C" void __inttm02_vect() __attribute__((interrupt, used, externally_visible));

void __inttm02_vect()
{
  // Increment the software system tick.
  mcal_gpt_system_tick += UINT32_C(0x10000);
}

void mcal::gpt::init(const config_type*)
{
  if(gpt_is_initialized() == false)
  {
    // set TAU0EN to enable input clock supply.
    mcal::reg::reg_access_static<std::uint32_t,
                                 std::uint8_t,
                                 mcal::reg::per0,
                                 0x01U>::reg_set();

    // fclk 32 MHz --> 1 MHz frequency (prescaler fclk/2^5).
    mcal::reg::reg_access_static<std::uint32_t,
                                 std::uint16_t,
                                 mcal::reg::tps0,
                                 0x005U>::reg_set();

    // Data register of timer channel 2, compare value of 0xFFFFU.
    mcal::reg::reg_access_static<std::uint32_t,
                                 std::uint16_t,
                                 mcal::reg::tdr02,
                                 0xFFFFU>::reg_set();

    // Configure Timer mode (interval timer mode, downcounting) falling edge
    mcal::reg::reg_access_static<std::uint32_t,
                                 std::uint16_t,
                                 mcal::reg::tmr02,
                                 0x000U>::reg_set();

    //start timing (set bit ts0.2).
    mcal::reg::reg_access_static<std::uint32_t,
                                 std::uint16_t,
                                 mcal::reg::ts0,
                                 0x004U>::reg_set();

    //enable INTTM02 interrupt.
    mcal::reg::reg_access_static<std::uint32_t,
                                 std::uint8_t,
                                 mcal::reg::mk1l,
                                 6U>::bit_clr();

    // set priority.
    mcal::reg::reg_access_static<std::uint32_t,
                                 std::uint8_t,
                                 mcal::reg::pr01l,
                                 6U>::bit_clr();

    // also set priority.
    mcal::reg::reg_access_static<std::uint32_t,
                                 std::uint8_t,
                                 mcal::reg::pr11l,
                                 6U>::bit_clr();

    // Set the is-initialized indication flag.
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

    // Attention: Down-counting timer --> use (0xFFFFU - timer counter).

    // Do the first read of the timer channel 2 counter and the system tick.
    const timer_register_type timer_cnt_1 = UINT16_C(0xFFFF) - mcal::reg::reg_access_static<timer_address_type, timer_register_type, mcal::reg::tcr02>::reg_get();

    const mcal::gpt::value_type sys_tick_1 = mcal_gpt_system_tick;

    // Do the second read of the timer channel 2 counter.
    const timer_register_type timer_cnt_2 = UINT16_C(0xFFFF) - mcal::reg::reg_access_static<timer_address_type, timer_register_type, mcal::reg::tcr02>::reg_get();

    // Perform the consistency check.
    const mcal::gpt::value_type consistent_microsecond_tick
      = ((timer_cnt_2 >= timer_cnt_1) ? static_cast<mcal::gpt::value_type>(sys_tick_1           | timer_cnt_1)
                                      : static_cast<mcal::gpt::value_type>(mcal_gpt_system_tick | timer_cnt_2));

    return consistent_microsecond_tick;
  }
  else
  {
    return mcal::gpt::value_type(0U);
  }
}
