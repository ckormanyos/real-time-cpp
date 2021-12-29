///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2015.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <cstdint>

#include <io_macros.h>
#include <DF3375.h>

#include <mcal_gpt.h>
#include <mcal_led.h>
#include <mcal_reg.h>

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

namespace mcal { namespace gpt {

using UINT8  = std::uint8_t;
using UINT32 = std::uint32_t;
using UINT64 = std::uint64_t;

UINT64 GetTick64_at_xxMHz(void);

} } // namespace mcal::gpt

extern "C" void IntQ0OV() __attribute__((interrupt_handler));

extern "C" void IntQ0OV(void)
{
  system_tick = static_cast<mcal::gpt::value_type>(system_tick + UINT32_C(0x10000));
}

void mcal::gpt::init(const config_type*)
{
  if(gpt_is_initialized() == false)
  {
    gpt_is_initialized() = true;

    // Select free-running mode for TAB1.
    TQ0CTL1 = static_cast<UINT8>(0x05u);

    // Select a prescaler of 1 (bit pattern 0) for TAB1.
    TQ0CTL0 = static_cast<UINT8>(0x00u);

    // Set the TAB1 overflow interrupt priority.
    // Enable the TAB1 overflow interrupt.
    TQ0OVIC = static_cast<UINT8>(0x06u);

    // Start TAB1.
    TQ0CTL0 |= static_cast<UINT8>(0x80u);
  }
}

mcal::gpt::value_type mcal::gpt::secure::get_time_elapsed()
{
  if(gpt_is_initialized())
  {
    return mcal::gpt::value_type(GetTick64_at_xxMHz());
  }
  else
  {
    return mcal::gpt::value_type(0U);
  }
}

mcal::gpt::UINT64 mcal::gpt::GetTick64_at_xxMHz(void)
{
  // Return the system tick using a multiple read to ensure data consistency.

  typedef std::uint16_t timer_register_type;

  // Do the first read of the timer4 counter and the system tick.
  const timer_register_type   tq0_cnt_1  = static_cast<timer_register_type>(TQ0CNT);
  const mcal::gpt::value_type sys_tick_1 = system_tick;

  // Do the second read of the timer4 counter.
  const timer_register_type   tq0_cnt_2  = static_cast<timer_register_type>(TQ0CNT);

  // Perform the consistency check.
  const mcal::gpt::value_type consistent_microsecond_tick
    = ((tq0_cnt_2 >= tq0_cnt_1) ? mcal::gpt::value_type(sys_tick_1  | tq0_cnt_1)
                                : mcal::gpt::value_type(system_tick | tq0_cnt_2));

  return mcal::gpt::value_type(mcal::gpt::value_type(consistent_microsecond_tick + 10U) / 20U);
}
