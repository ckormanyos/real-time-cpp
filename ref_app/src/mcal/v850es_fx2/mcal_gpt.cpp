///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2021.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <cstdint>

#include <mcal_gpt.h>
#include <mcal_led.h>
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

namespace mcal { namespace gpt {

using UINT8  = std::uint8_t;
using UINT32 = std::uint32_t;
using UINT64 = std::uint64_t;

UINT64 GetTick64_at_xxMHz(void);

} } // namespace mcal::gpt

extern "C" void mcal_gpt_increment_tick(void);

extern "C" void mcal_gpt_increment_tick(void)
{
  mcal_gpt_system_tick += UINT32_C(0x10000);
}

void mcal::gpt::init(const config_type*)
{
  if(gpt_is_initialized() == false)
  {
    gpt_is_initialized() = true;

    // Select free-running mode for TQ0.
    mcal::reg::reg_access_static<std::uint32_t, std::uint8_t, mcal::reg::tq0ctl1, UINT8_C(5)>::reg_set();

    // Select a prescaler of 1 (bit pattern 0) for TQ0.
    mcal::reg::reg_access_static<std::uint32_t, std::uint8_t, mcal::reg::tq0ctl0, UINT8_C(0)>::reg_set();

    // Set the TQ0 overflow interrupt priority.
    // Enable the TQ0 overflow interrupt.
    mcal::reg::reg_access_static<std::uint32_t, std::uint8_t, mcal::reg::tq0ovic, UINT8_C(0x06)>::reg_set();

    // Start TQ0.
    mcal::reg::reg_access_static<std::uint32_t, std::uint8_t, mcal::reg::tq0ctl0, UINT8_C(7)>::bit_set();
  }
}

mcal::gpt::value_type mcal::gpt::secure::get_time_elapsed()
{
  return (gpt_is_initialized() ? mcal::gpt::value_type(GetTick64_at_xxMHz())
                               : mcal::gpt::value_type(0U));
}

mcal::gpt::UINT64 mcal::gpt::GetTick64_at_xxMHz(void)
{
  // Return the system tick using a multiple read to ensure data consistency.

  typedef std::uint16_t timer_register_type;

  // Do the first read of the timer4 counter and the system tick.
  const timer_register_type   tq0_cnt_1  = mcal::reg::reg_access_static<std::uint32_t, std::uint16_t, mcal::reg::tq0cnt>::reg_get();
  const mcal::gpt::value_type sys_tick_1 = mcal_gpt_system_tick;

  // Do the second read of the timer4 counter.
  const timer_register_type   tq0_cnt_2  = mcal::reg::reg_access_static<std::uint32_t, std::uint16_t, mcal::reg::tq0cnt>::reg_get();

  // Perform the consistency check.
  const mcal::gpt::value_type consistent_microsecond_tick
    = ((tq0_cnt_2 >= tq0_cnt_1) ? mcal::gpt::value_type(sys_tick_1           | tq0_cnt_1)
                                : mcal::gpt::value_type(mcal_gpt_system_tick | tq0_cnt_2));

  return mcal::gpt::value_type(mcal::gpt::value_type(consistent_microsecond_tick + 10U) / 20U);
}
