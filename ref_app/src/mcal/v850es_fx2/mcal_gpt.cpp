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
  std::uint64_t system_tick;

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

UINT64 GetTick64_at_xxMHz();

} } // namespace mcal::gpt

extern "C" void IntQ0OV() __attribute__((interrupt));

extern "C" void IntQ0OV(void)
{
  //mcal::led::led0().toggle();
  ++system_tick;
}

void mcal::gpt::init(const config_type*)
{
  if(gpt_is_initialized() == false)
  {
    gpt_is_initialized() = true;

    #if 1
    // Select free-running mode for TAB1.
    TQ0CTL1 = static_cast<UINT8>(0x05u);

    // Select a prescaler of 1 (bit pattern 0) for TAB1.
    TQ0CTL0 = static_cast<UINT8>(0x00u);
  
    // Set the TAB1 overflow interrupt priority.
    // Enable the TAB1 overflow interrupt.
    TQ0OVIC = static_cast<UINT8>(0x06u);

    // Start TAB1.
    TQ0CTL0 |= static_cast<UINT8>(0x80u);
    #endif
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
  return static_cast<UINT64>(0U);
}
