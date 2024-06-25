///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2022 - 2024.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <SysTick.h>

#include <mcal_gpt.h>

#include <cstdint>

namespace
{
  auto gpt_is_initialized() noexcept -> bool& __attribute__((used, noinline));

  auto gpt_is_initialized() noexcept -> bool&
  {
    static bool is_init { };

    return is_init;
  }
}

namespace local
{
  auto get_consistent_microsecond_tick() noexcept -> mcal::gpt::value_type;

  auto get_consistent_microsecond_tick() noexcept -> mcal::gpt::value_type
  {
    return static_cast<mcal::gpt::value_type>(static_cast<uint64>(::SysTick_Get() + 72U) / 144U);
  }
}

void mcal::gpt::init(const config_type*)
{
  if(!gpt_is_initialized())
  {
    ::SysTick_Init();

    gpt_is_initialized() = true;
  }
}

mcal::gpt::value_type mcal::gpt::secure::get_time_elapsed()
{
  return (gpt_is_initialized() ? local::get_consistent_microsecond_tick()
                               : static_cast<mcal::gpt::value_type>(UINT8_C(0)));
}
