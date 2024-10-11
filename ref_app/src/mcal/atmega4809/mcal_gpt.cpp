///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2021.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <mcal_gpt.h>
#include <mcal_reg.h>

namespace
{
  // The one (and only one) system tick.
  volatile std::uint64_t mcal_gpt_system_tick;

  bool& gpt_is_initialized() __attribute__((used, noinline));

  bool& gpt_is_initialized()
  {
    static bool is_init = bool();

    return is_init;
  }
}

extern "C"
void __vector_3() __attribute__((signal, used, externally_visible));

void __vector_3()
{
  // The real-time counter's count register has overflowed
  // the software-set period of 0x01FF (512 ticks).

  // Clear the interrupt flag (on overflow).
  mcal::reg::reg_access_static<std::uint16_t,
                               std::uint8_t,
                               mcal::reg::rtc_intflags,
                               UINT8_C(0)>::bit_set();

  // Increment the 64-bit system tick with 15625 [us].
  // This number of microseconds represents the time
  // span needed for 512 ticks at 32.768 kHz.
  const mcal::gpt::value_type new_tick = mcal_gpt_system_tick + static_cast<std::uint32_t>(15625U);

  mcal_gpt_system_tick = new_tick;
}

void mcal::gpt::init(const config_type*)
{
  if(!gpt_is_initialized())
  {
    // The system tick for the multitasking scheduler is derived
    // from the real-time counter. The numerics of setting up
    // the real-time counter are outlined as follows.

    // We take the real-time counter clocked at 32.768 kHz and
    // use a prescalar of 1. The resulting frequency is 32.768 kHz.
    // We will use a both period and compare value of 0x01FF below
    // (with interrupt on overflow).

    // This results in a tick count of 512 ticks (at) 32.768 kHz.
    // Under these conditions, 512 ticks requires:
    // T = (1,000,000 [us] / 32,768) * 512 = 15,625 [us].
    // So there will be an interrupt every 15,625 [us]
    // and the system tick, having resolution of microseconds,
    // is incremented with 15,625 in the interrupt handler.

    // Scaling from ticks to [us] requires multiplication
    // by a factor of (15,625 / 512), which is done via
    // rounded integer mathematics in the subroutine
    // mcal::gpt::get_time_elapsed() below.

    // Enable interrupt on overflow.
    mcal::reg::reg_access_static<std::uint16_t,
                                 std::uint8_t,
                                 mcal::reg::rtc_intctrl,
                                 UINT8_C(0)>::bit_set();

    // 32.768 kHz from osculp32k.
    mcal::reg::reg_access_static<std::uint16_t,
                                 std::uint8_t,
                                 mcal::reg::rtc_clksel,
                                 UINT8_C(0x00)>::reg_set();

    // Set the real-time counter's period to 0x01FF.
    mcal::reg::reg_access_static<std::uint16_t,
                                 std::uint8_t,
                                 mcal::reg::rtc_per,
                                 UINT8_C(0xFF)>::reg_set();

    mcal::reg::reg_access_static<std::uint16_t,
                                 std::uint8_t,
                                 mcal::reg::rtc_per + 1U,
                                 UINT8_C(0x01)>::reg_set();

    // Set the real-time counter's compare value to 0x01FF
    // (even though it is not directly used).
    mcal::reg::reg_access_static<std::uint16_t,
                                 std::uint8_t,
                                 mcal::reg::rtc_cmp,
                                 UINT8_C(0xFF)>::reg_set();

    mcal::reg::reg_access_static<std::uint16_t,
                                 std::uint8_t,
                                 mcal::reg::rtc_cmp + 1U,
                                 UINT8_C(0x01)>::reg_set();

    // Set the real-time counter's count value to 0x0000.
    mcal::reg::reg_access_static<std::uint16_t,
                                 std::uint8_t,
                                 mcal::reg::rtc_cnt,
                                 UINT8_C(0x00)>::reg_set();

    mcal::reg::reg_access_static<std::uint16_t,
                                 std::uint8_t,
                                 mcal::reg::rtc_cnt + 1U,
                                 UINT8_C(0x00)>::reg_set();

    // Enable the real-time counter. Keep the real-time counter
    // also enabled in sleep mode. Set the prescaler to 1.
    mcal::reg::reg_access_static<std::uint16_t,
                                 std::uint8_t,
                                 mcal::reg::rtc_ctrla,
                                 UINT8_C(0x81)>::reg_set();

    // Set the is-initialized indication flag.
    gpt_is_initialized() = true;
  }
}

mcal::gpt::value_type mcal::gpt::secure::get_time_elapsed()
{
  if(gpt_is_initialized())
  {
    // Return the system tick using a multiple read to ensure data consistency.

    // Do the first read of the real-time counter's cnt register and the system tick.
    const std::uint8_t  rtc_cnt_1  = mcal::reg::reg_access_static<std::uint16_t, std::uint8_t, mcal::reg::rtc_cnt + 0U>::reg_get();
    const std::uint64_t sys_tick_1 = mcal_gpt_system_tick;

    // Do the second read of the real-time counter's cnt register.
    const std::uint8_t  rtc_cnt_2  = mcal::reg::reg_access_static<std::uint16_t, std::uint8_t, mcal::reg::rtc_cnt + 0U>::reg_get();

    // Perform the consistency check.
    std::uint64_t consistent_microsecond_tick;

    if(rtc_cnt_2 >= rtc_cnt_1)
    {
      const std::uint32_t low_part = (std::uint32_t) ((std::uint32_t) (rtc_cnt_1 * (std::uint32_t) 15625U) + 256U) / 512U;

      consistent_microsecond_tick = sys_tick_1 | low_part;
    }
    else
    {
      const std::uint32_t low_part = (std::uint32_t) ((std::uint32_t) (rtc_cnt_2 * (std::uint32_t) 15625U) + 256U) / 512U;

      consistent_microsecond_tick = mcal_gpt_system_tick | low_part;
    }

    return (mcal::gpt::value_type) consistent_microsecond_tick;
  }
  else
  {
    return mcal::gpt::value_type(0U);
  }
}
