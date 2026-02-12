///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2022 - 2026.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <mcal_gpt.h>
#include <mcal_reg.h>

#include <limits>

extern "C"
{
  extern auto osGetActiveCore(void) -> std::uint32_t;
}

namespace
{
  auto gpt_is_initialized_core0() -> bool& __attribute__((used, noinline));
  auto gpt_is_initialized_core1() -> bool& __attribute__((used, noinline));

  auto gpt_is_initialized_core0() -> bool& { static bool is_init { }; return is_init; }
  auto gpt_is_initialized_core1() -> bool& { static bool is_init { }; return is_init; }
}

auto mcal::gpt::init(const config_type*) -> void
{
  const std::uint32_t core_id { ::osGetActiveCore() };

  if(core_id == std::uint32_t { UINT8_C(0) })
  {
    gpt_is_initialized_core0() = true;
  }
  else
  {
    gpt_is_initialized_core1() = true;
  }

  // Set the MTIME timeout to essentially infinite.
  mcal::reg::reg_access_static<std::uint32_t, std::uint64_t, mcal::reg::clint_mtimecmp, (std::numeric_limits<std::uint64_t>::max)()>::reg_set();
}

auto mcal::gpt::secure::get_time_elapsed() -> mcal::gpt::value_type
{
  std::uint64_t tick_unscaled { };

  if(gpt_is_initialized_core0())
  {
    const std::uint64_t tick_unscaled_01 { mcal::reg::reg_access_static<std::uint32_t, std::uint64_t, mcal::reg::clint_mtime>::reg_get() };
    const std::uint64_t tick_unscaled_02 { mcal::reg::reg_access_static<std::uint32_t, std::uint64_t, mcal::reg::clint_mtime>::reg_get() };

    tick_unscaled =
      static_cast<std::uint64_t>
      (
        (static_cast<std::uint32_t>(tick_unscaled_02) > static_cast<std::uint32_t>(tick_unscaled_01))
          ? tick_unscaled_01
          : mcal::reg::reg_access_static<std::uint32_t, std::uint64_t, mcal::reg::clint_mtime>::reg_get()
      );

    tick_unscaled = static_cast<std::uint64_t>(static_cast<std::uint64_t>(tick_unscaled + 160U) / 320U);
  }

  return static_cast<mcal::gpt::value_type>(tick_unscaled);
}

auto mcal::gpt::secure::get_time_elapsed_core1() -> mcal::gpt::value_type
{
  std::uint64_t tick_unscaled { };

  if(gpt_is_initialized_core1())
  {
    const std::uint64_t tick_unscaled_01 { mcal::reg::reg_access_static<std::uint32_t, std::uint64_t, mcal::reg::clint_mtime>::reg_get() };
    const std::uint64_t tick_unscaled_02 { mcal::reg::reg_access_static<std::uint32_t, std::uint64_t, mcal::reg::clint_mtime>::reg_get() };

    tick_unscaled =
      static_cast<std::uint64_t>
      (
        (static_cast<std::uint32_t>(tick_unscaled_02) > static_cast<std::uint32_t>(tick_unscaled_01))
          ? tick_unscaled_01
          : mcal::reg::reg_access_static<std::uint32_t, std::uint64_t, mcal::reg::clint_mtime>::reg_get()
      );

    tick_unscaled = static_cast<std::uint64_t>(static_cast<std::uint64_t>(tick_unscaled + 160U) / 320U);
  }

  return static_cast<mcal::gpt::value_type>(tick_unscaled);
}
