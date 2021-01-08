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
  // Increment the 32-bit system tick with 0x80, representing 128 microseconds.
  const mcal::gpt::value_type new_tick = system_tick + static_cast<std::uint8_t>(0x80U);

  system_tick = new_tick;
}

void mcal::gpt::init(const config_type*)
{
  if(gpt_is_initialized() == false)
  {
    // Set the is-initialized indication flag.
    gpt_is_initialized() = true;
  }
}

mcal::gpt::value_type mcal::gpt::secure::get_time_elapsed()
{
  if(gpt_is_initialized())
  {
    return mcal::gpt::value_type(0U);
  }
  else
  {
    return mcal::gpt::value_type(0U);
  }
}
