///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2022.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <cstddef>
#include <cstdint>

#include <mcal_gpt.h>
#include <mcal_reg.h>

namespace
{
  // The one (and only one) system tick.
  volatile mcal::gpt::value_type mcal_gpt_system_tick;

  bool& gpt_is_initialized() __attribute__((used, noinline));

  bool& gpt_is_initialized()
  {
    static bool is_init { };

    return is_init;
  }
}

void mcal::gpt::init(const config_type*)
{
  if(!gpt_is_initialized())
  {
    gpt_is_initialized() = true;
  }
}

mcal::gpt::value_type mcal::gpt::secure::get_time_elapsed()
{
  return (gpt_is_initialized() ? static_cast<mcal::gpt::value_type>(UINT8_C(0))
                               : static_cast<mcal::gpt::value_type>(UINT8_C(0)));
}
