///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2022 - 2026.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <mcal_gpt.h>
#include <mcal_reg.h>

#include <interrupt.h>

#include <cstdint>
#include <limits>

extern "C"
{
  uint32_t osGetActiveCore(void);
}

namespace
{
  constexpr std::uint32_t TIMEOUT_1S { UINT32_C(320000000) };
}

void mcal::gpt::init(const config_type*)
{
  // Set the MTIME timeout.
  CLINT_MTIMECMP = (std::numeric_limits<std::uint64_t>::max)();
}

mcal::gpt::value_type mcal::gpt::secure::get_time_elapsed()
{
  const std::uint64_t tick_unscaled_01 = (std::uint64_t) CLINT_MTIME;
  const std::uint64_t tick_unscaled_02 = (std::uint64_t) CLINT_MTIME;

  const std::uint64_t tick_unscaled =
    (std::uint64_t) (((std::uint32_t) tick_unscaled_02 > (std::uint32_t) tick_unscaled_01) ? tick_unscaled_01 : (std::uint64_t) CLINT_MTIME);

  return (std::uint64_t) ((std::uint64_t) (tick_unscaled + 160U) / 320U);
}

mcal::gpt::value_type mcal::gpt::secure::get_time_elapsed_core1()
{
  const std::uint64_t tick_unscaled_01 = (std::uint64_t) CLINT_MTIME;
  const std::uint64_t tick_unscaled_02 = (std::uint64_t) CLINT_MTIME;

  const std::uint64_t tick_unscaled =
    (std::uint64_t) (((std::uint32_t) tick_unscaled_02 > (std::uint32_t) tick_unscaled_01) ? tick_unscaled_01 : (std::uint64_t) CLINT_MTIME);

  return (std::uint64_t) ((std::uint64_t) (tick_unscaled + 160U) / 320U);
}
