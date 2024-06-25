///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2022 - 2024.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <SysTick.h>

#include <mcal_gpt.h>

#include <cstdint>

extern "C"
{
  extern std::uint64_t SysTick_Get(void);
}

namespace local
{
  auto get_consistent_microsecond_tick() noexcept -> mcal::gpt::value_type;

  auto get_consistent_microsecond_tick() noexcept -> mcal::gpt::value_type
  {
    return static_cast<mcal::gpt::value_type>(::SysTick_Get());
  }
}

void mcal::gpt::init(const config_type*)
{
}

mcal::gpt::value_type mcal::gpt::secure::get_time_elapsed()
{
  return local::get_consistent_microsecond_tick();
}
