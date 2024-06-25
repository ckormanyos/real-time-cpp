///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2022.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <cstddef>
#include <cstdint>
#include <limits>
#include <type_traits>

#include <mcal_gpt.h>
#include <mcal_reg.h>

#include <util/utility/util_two_part_data_manipulation.h>

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
  auto get_consistent_microsecond_tick() noexcept -> mcal::gpt::value_type __attribute__((warn_unused_result));

  auto constexpr to_microseconds(std::uint64_t tick_val) noexcept -> std::uint64_t;

  auto constexpr to_microseconds(std::uint64_t tick_val) noexcept -> std::uint64_t
  {
    // The frequency of the underlying 64-bit tick is 32.768kHz

    // Consider the following tick scaling from 32.768kHz to 1MHz:
    //   (((t * 61) + 1)/2) + (((t * 9) + 256)/512)

    // Test case: t = 32768 -->   999,424
    //                          +     576
    //                          ---------
    //                          1,000,000

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
              + static_cast<std::uint8_t>(UINT8_C(1))
            )
            / static_cast<std::uint8_t>(UINT8_C(2))
          )
        +
          static_cast<std::uint64_t>
          (
            static_cast<std::uint64_t>
            (
                static_cast<std::uint64_t>
                (
                  tick_val * static_cast<std::uint8_t>(UINT8_C(9))
                )
              + static_cast<std::uint16_t>(UINT16_C(256))
            )
            / static_cast<std::uint16_t>(UINT16_C(512))
          )
      );
  }

  auto read_lo = [](void) -> std::uint32_t { return mcal::reg::reg_access_static<std::uint32_t, std::uint32_t, mcal::reg::clint_mtime >::reg_get(); };
  auto read_hi = [](void) -> std::uint32_t { return mcal::reg::reg_access_static<std::uint32_t, std::uint32_t, mcal::reg::clint_mtimeh>::reg_get(); };
}

void mcal::gpt::init(const config_type*)
{
  if(!gpt_is_initialized())
  {
    using clint_mtimecmp_reg_address_type = std::uint32_t;
    using clint_mtimecmp_reg_value_type   = std::uint64_t;

    using clint_mtimecmp_reg_access_type =
      mcal::reg::reg_access_static<clint_mtimecmp_reg_address_type,
                                   clint_mtimecmp_reg_value_type,
                                   mcal::reg::clint_mtimecmp,
                                   (std::numeric_limits<clint_mtimecmp_reg_value_type>::max)()>;

    static_assert(std::is_same<typename clint_mtimecmp_reg_access_type::register_value_type, clint_mtimecmp_reg_value_type>::value,
                  "Error: Unexpected clint_mtimecmp register value type");

    // Set the 64-bit mtimer compare register to its maximum value.
    // This results in an essentially infinite timeout.
    clint_mtimecmp_reg_access_type::reg_set();

    gpt_is_initialized() = true;
  }
}

mcal::gpt::value_type mcal::gpt::secure::get_time_elapsed()
{
  return (gpt_is_initialized() ? local::get_consistent_microsecond_tick()
                               : static_cast<mcal::gpt::value_type>(UINT8_C(0)));
}

auto local::get_consistent_microsecond_tick() noexcept -> mcal::gpt::value_type
{
  auto consistent_unscaled_tick = std::uint64_t { };

  for(;;)
  {
    const auto mt_lo1 __attribute__((no_reorder)) = read_lo();
    const auto mt_hi  __attribute__((no_reorder)) = read_hi();
    const auto mt_lo2 __attribute__((no_reorder)) = read_lo();

    if(mt_lo2 > mt_lo1)
    {
      consistent_unscaled_tick = util::make_long(mt_lo1, mt_hi);

      break;
    }
  }

  return
    static_cast<mcal::gpt::value_type>
    (
      to_microseconds(consistent_unscaled_tick)
    );
}
