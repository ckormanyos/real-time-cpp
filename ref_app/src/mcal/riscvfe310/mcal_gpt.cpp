///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2022.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <cstddef>
#include <cstdint>

#include <mcal_gpt.h>
#include <mcal_led.h>
#include <mcal_reg.h>

#include <util/utility/util_two_part_data_manipulation.h>

namespace
{
  auto gpt_is_initialized() -> bool& __attribute__((used, noinline));

  auto gpt_is_initialized() -> bool&
  {
    static bool is_init { };

    return is_init;
  }
}

namespace local
{
  auto get_consistent_microsecond_tick() -> mcal::gpt::value_type;
}

void mcal::gpt::init(const config_type*)
{
  if(!gpt_is_initialized())
  {
    // Set the 64-bit mtimer compare register
    // to its maximum value (essentially infinite).
    mcal::reg::reg_access_static<std::uint32_t, std::uint64_t, mcal::reg::clint_mtimecmp, static_cast<std::uint64_t>(UINT64_C(0xFFFFFFFFFFFFFFFF))>::reg_set();

    gpt_is_initialized() = true;
  }
}

mcal::gpt::value_type mcal::gpt::secure::get_time_elapsed()
{
  return (gpt_is_initialized() ? local::get_consistent_microsecond_tick()
                               : static_cast<mcal::gpt::value_type>(UINT8_C(0)));
}

auto local::get_consistent_microsecond_tick() -> mcal::gpt::value_type
{
  auto read_lo = [](void) -> std::uint32_t { return mcal::reg::reg_access_static<std::uint32_t, std::uint32_t, mcal::reg::clint_mtime >::reg_get(); };
  auto read_hi = [](void) -> std::uint32_t { return mcal::reg::reg_access_static<std::uint32_t, std::uint32_t, mcal::reg::clint_mtimeh>::reg_get(); };

  auto to_microseconds =
    [](const std::uint32_t tick_val) -> std::uint32_t
    {
      const auto result_non_trimmed =
        static_cast<std::uint64_t>
        (
            static_cast<std::uint64_t>(static_cast<std::uint64_t>(tick_val) * static_cast<std::uint8_t>(UINT8_C(61)))
          / static_cast<std::uint8_t>(UINT8_C(2))
        );

      const auto trimming_amount =
        static_cast<std::uint64_t>
        (
            static_cast<std::uint64_t>(static_cast<std::uint64_t>(tick_val) * static_cast<std::uint8_t>(UINT8_C(19)))
          / static_cast<std::uint32_t>(UINT32_C(32768))
        );

      return
        static_cast<std::uint32_t>
        (
          static_cast<std::uint64_t>(result_non_trimmed + trimming_amount)
        );
    };

  const auto mt_lo_1 = to_microseconds(read_lo());
  const auto mt_hi_1 = to_microseconds(read_hi());

  const auto mt_lo_2 = to_microseconds(read_lo());

  const auto consistent_microsecond_tick =
    static_cast<std::uint64_t>
    (
      (mt_lo_2 > mt_lo_1) ? util::make_long(mt_lo_1, mt_hi_1)
                          : util::make_long(mt_lo_2, to_microseconds(read_hi()))
    );

  return static_cast<mcal::gpt::value_type>(consistent_microsecond_tick);
}
