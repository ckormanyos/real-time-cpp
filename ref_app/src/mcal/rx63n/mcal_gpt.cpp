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

extern "C" void __tmr0_ovi_irq() __attribute__((interrupt, used, externally_visible));

void __tmr0_ovi_irq()
{
  // Increment the software system tick.
  mcal_gpt_system_tick += UINT16_C(0x100);
}

void mcal::gpt::init(const config_type*)
{
  if(gpt_is_initialized() == false)
  {
    // Protection off
    // SYSTEM.PRCR.WORD = 0xA503u;
    mcal::reg::reg_access_static<std::uint32_t,
                                 std::uint16_t,
                                 mcal::reg::prcr,
                                 UINT16_C(0xA503)>::reg_set();

    // Activate timer0/timer1 by clearing bit-5 in the module-stop register.
    mcal::reg::reg_access_static<std::uint32_t,
                                 std::uint32_t,
                                 mcal::reg::mstpcra,
                                 UINT8_C(5)>::bit_clr();

    // Protection on
    // SYSTEM.PRCR.WORD = 0xA500u;
    mcal::reg::reg_access_static<std::uint32_t,
                                 std::uint16_t,
                                 mcal::reg::prcr,
                                 UINT16_C(0xA500)>::reg_set();

    // Set timer0 to have an interrupt on overflow.
    mcal::reg::reg_access_static<std::uint32_t,
                                 std::uint8_t,
                                 mcal::reg::tmr0_tcr,
                                 UINT8_C(0x20)>::reg_set();

    // Enable the timer0 overflow interrupt at ier15.4.
    mcal::reg::reg_access_static<std::uint32_t,
                                 std::uint8_t,
                                 mcal::reg::icu_ier15,
                                 UINT8_C(0x04)>::bit_set();

    // Set the timer0 overflow interrupt priority to 7.
    mcal::reg::reg_access_static<std::uint32_t,
                                 std::uint8_t,
                                 mcal::reg::icu_ipr170,
                                 UINT8_C(0x07)>::reg_set();

    // Select the internal clock (not external) with the value 8.
    // Also select a prescaler of 32 with the value 3.
    mcal::reg::reg_access_static<std::uint32_t,
                                 std::uint8_t,
                                 mcal::reg::tmr0_tccr,
                                 static_cast<std::uint8_t>(UINT8_C(0x08) | UINT8_C(0x03))>::reg_set();

    // Start timer0 counting up.
    mcal::reg::reg_access_static<std::uint32_t,
                                 std::uint16_t,
                                 mcal::reg::cmt_cmstr0,
                                 UINT16_C(0x01)>::reg_set();

    gpt_is_initialized() = true;
  }
}

mcal::gpt::value_type mcal::gpt::secure::get_time_elapsed()
{
  if(gpt_is_initialized())
  {
    // Return the system tick using a multiple read to ensure data consistency.

    typedef std::uint32_t timer_address_type;
    typedef std::uint8_t  timer_register_type;

    // Do the first read of the timer0 counter and the system tick.
    const timer_register_type timer_cnt_1  = mcal::reg::reg_access_static<timer_address_type, timer_register_type, mcal::reg::tmr0_tcnt>::reg_get();
    const mcal::gpt::value_type sys_tick_1 = mcal_gpt_system_tick;

    // Do the second read of the timer0 counter.
    const timer_register_type timer_cnt_2  = mcal::reg::reg_access_static<timer_address_type, timer_register_type, mcal::reg::tmr0_tcnt>::reg_get();

    // Perform the consistency check.
    mcal::gpt::value_type consistent_microsecond_tick =
      ((timer_cnt_2 >= timer_cnt_1) ? static_cast<mcal::gpt::value_type>(sys_tick_1           | timer_cnt_1)
                                    : static_cast<mcal::gpt::value_type>(mcal_gpt_system_tick | timer_cnt_2));

    // Convert the consistent tick to microseconds.
    consistent_microsecond_tick = static_cast<mcal::gpt::value_type>(static_cast<mcal::gpt::value_type>(consistent_microsecond_tick * 4U)  + 3U) / 6U;

    return consistent_microsecond_tick;
  }
  else
  {
    return mcal::gpt::value_type(0U);
  }
}

