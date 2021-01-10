///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2015.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <mcal_gpt.h>
#include <mcal_reg.h>

#include <util/utility/util_two_part_data_manipulation.h>

namespace
{
  // The one (and only one) system tick.
  volatile mcal::gpt::value_type system_tick;

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
  // Increment the 64-bit system tick with 15625 [us].
  const mcal::gpt::value_type new_tick = system_tick + static_cast<std::uint32_t>(15625U);

  system_tick = new_tick;

  // Clear the interrupt flag (on overflow).
  mcal::reg::reg_access_static<std::uint16_t,
                               std::uint8_t,
                               mcal::reg::rtc_intflags,
                               UINT8_C(0)>::bit_set();
}

void mcal::gpt::init(const config_type*)
{
  if(gpt_is_initialized() == false)
  {
    // Enable interrupt on overflow.
    mcal::reg::reg_access_static<std::uint16_t,
                                 std::uint8_t,
                                 mcal::reg::rtc_intctrl,
                                 UINT8_C(0)>::bit_set();

    // 32.768 kHz from OSCULP32K.
    mcal::reg::reg_access_static<std::uint16_t,
                                 std::uint8_t,
                                 mcal::reg::rtc_clksel,
                                 UINT8_C(0x00)>::reg_set();

    // Set the rtc period to 0xFF.
    mcal::reg::reg_access_static<std::uint16_t,
                                 std::uint8_t,
                                 mcal::reg::rtc_per,
                                 UINT8_C(0xFF)>::reg_set();

    mcal::reg::reg_access_static<std::uint16_t,
                                 std::uint8_t,
                                 mcal::reg::rtc_per + 1U,
                                 UINT8_C(0x00)>::reg_set();

    // Set the rtc compare value to 0xFF (even though this is not used).
    mcal::reg::reg_access_static<std::uint16_t,
                                 std::uint8_t,
                                 mcal::reg::rtc_cmp,
                                 UINT8_C(0xFF)>::reg_set();

    mcal::reg::reg_access_static<std::uint16_t,
                                 std::uint8_t,
                                 mcal::reg::rtc_cmp + 1U,
                                 UINT8_C(0x00)>::reg_set();

    // Set the rtc ount value to 0.
    mcal::reg::reg_access_static<std::uint16_t,
                                 std::uint8_t,
                                 mcal::reg::rtc_cnt,
                                 UINT8_C(0x00)>::reg_set();

    mcal::reg::reg_access_static<std::uint16_t,
                                 std::uint8_t,
                                 mcal::reg::rtc_cnt + 1U,
                                 UINT8_C(0x00)>::reg_set();

    // Enable the real-time counter.
    // Enabled in sleep mode, prescaler of 2.
    mcal::reg::reg_access_static<std::uint16_t,
                                 std::uint8_t,
                                 mcal::reg::rtc_ctrla,
                                 (std::uint8_t) (0x81U | (1U << 3U))>::reg_set();

    // Set the is-initialized indication flag.
    gpt_is_initialized() = true;
  }
}

mcal::gpt::value_type mcal::gpt::secure::get_time_elapsed()
{
  if(gpt_is_initialized())
  {
    // Return the system tick using a multiple read to ensure data consistency.

    // Do the first read of the rtc counter and the system tick.
    const std::uint8_t          rtc_cnt_1  = mcal::reg::reg_access_static<std::uint16_t, std::uint8_t, mcal::reg::rtc_cnt + 0U>::reg_get();
    const mcal::gpt::value_type sys_tick_1 = system_tick;

    // Do the second read of the rtc counter counter.
    const std::uint8_t          rtc_cnt_2  = mcal::reg::reg_access_static<std::uint16_t, std::uint8_t, mcal::reg::rtc_cnt + 0U>::reg_get();

    // Perform the consistency check.
    std::uint32_t         low_part;
    mcal::gpt::value_type consistent_microsecond_tick;

    if(rtc_cnt_2 >= rtc_cnt_1)
    {
      low_part = (std::uint32_t) ((std::uint32_t) (rtc_cnt_1 * (std::uint32_t) 15625U) + 128U) / 256U;

      consistent_microsecond_tick = sys_tick_1 | low_part;
    }
    else
    {
      low_part = (std::uint32_t) ((std::uint32_t) (rtc_cnt_2 * (std::uint32_t) 15625U) + 128U) / 256U;

      consistent_microsecond_tick = system_tick | low_part;
    }

    return consistent_microsecond_tick;
  }
  else
  {
    return mcal::gpt::value_type(0U);
  }
}
