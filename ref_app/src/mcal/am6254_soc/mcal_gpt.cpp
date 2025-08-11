///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2025.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <mcal_gpt.h>

#include <core_macros.h>

auto mcal::gpt::secure::get_time_elapsed() -> mcal::gpt::value_type
{
  // Get the system tick from the system counter register.
  const value_type consistent_microsecond_tick = static_cast<value_type>(ARM64_READ_SYSREG(CNTPCT_EL0));

  // Convert the consistent tick to microseconds.
  return static_cast<value_type>(static_cast<value_type>(consistent_microsecond_tick + UINT64_C(100)) / UINT64_C(200));
}

auto mcal::gpt::secure::get_time_elapsed_core1() -> mcal::gpt::value_type_core1
{
  // Get the system tick from the system counter register.
  const value_type_core1 consistent_microsecond_tick = static_cast<value_type_core1>(ARM64_READ_SYSREG(CNTPCT_EL0));

  // Convert the consistent tick to microseconds.
  return static_cast<value_type_core1>(static_cast<value_type_core1>(consistent_microsecond_tick + UINT64_C(100)) / UINT64_C(200));
}

auto mcal::gpt::secure::get_time_elapsed_core2() -> mcal::gpt::value_type_core2
{
  // Get the system tick from the system counter register.
  const value_type_core2 consistent_microsecond_tick = static_cast<value_type_core2>(ARM64_READ_SYSREG(CNTPCT_EL0));

  // Convert the consistent tick to microseconds.
  return static_cast<value_type_core2>(static_cast<value_type_core2>(consistent_microsecond_tick + UINT64_C(100)) / UINT64_C(200));
}

auto mcal::gpt::secure::get_time_elapsed_core3() -> mcal::gpt::value_type_core3
{
  // Get the system tick from the system counter register.
  const value_type_core3 consistent_microsecond_tick = static_cast<value_type_core3>(ARM64_READ_SYSREG(CNTPCT_EL0));

  // Convert the consistent tick to microseconds.
  return static_cast<value_type_core3>(static_cast<value_type_core3>(consistent_microsecond_tick + UINT64_C(100)) / UINT64_C(200));
}
