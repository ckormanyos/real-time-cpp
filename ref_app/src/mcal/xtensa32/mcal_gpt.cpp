///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2020.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <mcal_gpt.h>

extern "C"
{
  extern int64_t esp_timer_get_time(void);
}

void mcal::gpt::init(const config_type*)
{
}

mcal::gpt::value_type mcal::gpt::secure::get_time_elapsed()
{
  return (mcal::gpt::value_type) ::esp_timer_get_time();
}
