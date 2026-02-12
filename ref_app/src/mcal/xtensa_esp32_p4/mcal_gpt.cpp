///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2022 - 2026.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <mcal_gpt.h>
#include <mcal_reg.h>

#include <util/utility/util_two_part_data_manipulation.h>

#include <interrupt.h>

#include <cstddef>
#include <cstdint>
#include <limits>
#include <type_traits>

extern "C"
{
  uint32_t osGetActiveCore(void);
}

namespace
{
  constexpr unsigned TIMEOUT_1S { 320000000u };
}

void mcal::gpt::init(const config_type*)
{
  // Set the MTIME timeout.
  CLINT_MTIMECMP = (uint64_t) UINT64_C(0xFFFFFFFFFFFFFFFF);
}

mcal::gpt::value_type mcal::gpt::secure::get_time_elapsed()
{
  const std::uint64_t tick_unscaled_01 = (uint64_t) CLINT_MTIME;
  const std::uint64_t tick_unscaled_02 = (uint64_t) CLINT_MTIME;

  const std::uint64_t tick_unscaled =
    (uint64_t) (((uint32_t) tick_unscaled_02 > (uint32_t) tick_unscaled_01) ? tick_unscaled_01 : (uint64_t) CLINT_MTIME);

  return (std::uint64_t) ((std::uint64_t) (tick_unscaled + 160U) / 320U);
}

mcal::gpt::value_type mcal::gpt::secure::get_time_elapsed_core1()
{
  const std::uint64_t tick_unscaled_01 = (uint64_t) CLINT_MTIME;
  const std::uint64_t tick_unscaled_02 = (uint64_t) CLINT_MTIME;

  const std::uint64_t tick_unscaled =
    (uint64_t) (((uint32_t) tick_unscaled_02 > (uint32_t) tick_unscaled_01) ? tick_unscaled_01 : (uint64_t) CLINT_MTIME);

  return (std::uint64_t) ((std::uint64_t) (tick_unscaled + 160U) / 320U);
}
