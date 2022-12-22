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

  auto constexpr to_microseconds(std::uint64_t tick_val) -> std::uint64_t;

  auto constexpr to_microseconds(std::uint64_t tick_val) -> std::uint64_t
  {
    return
      static_cast<std::uint64_t>
      (
          static_cast<std::uint64_t>
          (
            static_cast<std::uint64_t>
            (
                static_cast<std::uint64_t>
                (
                  tick_val * static_cast<std::uint8_t>(UINT8_C(61))
                )
              + static_cast<std::uint64_t>(UINT8_C(1))
            )
            / static_cast<std::uint64_t>(UINT8_C(2))
          )
        +
          static_cast<std::uint64_t>
          (
            static_cast<std::uint64_t>
            (
                static_cast<std::uint64_t>
                (
                  tick_val * static_cast<std::uint8_t>(UINT8_C(36))
                )
              + static_cast<std::uint64_t>(UINT8_C(1024))
            )
            / static_cast<std::uint64_t>(UINT8_C(2048))
          )
      );
  }
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

  auto consistent_unscaled_tick = std::uint64_t { };

  for(;;)
  {
    const auto mt_lo = read_lo();
    const auto mt_hi = read_hi();

    if(read_lo() > mt_lo)
    {
      consistent_unscaled_tick = util::make_long(mt_lo, mt_hi);

      break;
    }
  }

  return
    static_cast<mcal::gpt::value_type>
    (
      to_microseconds(consistent_unscaled_tick)
    );
}
