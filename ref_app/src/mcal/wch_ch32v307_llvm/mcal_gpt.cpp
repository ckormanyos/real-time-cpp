///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2022 - 2024.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <mcal_gpt.h>
#include <mcal_reg.h>

#include <util/utility/util_two_part_data_manipulation.h>

#include <cstdint>

namespace
{
  [[nodiscard]] auto gpt_is_initialized() noexcept -> bool&;

  [[nodiscard]] auto gpt_is_initialized() noexcept -> bool&
  {
    static bool is_init { };

    return is_init;
  }
}

namespace local
{
  auto get_consistent_microsecond_tick() noexcept -> mcal::gpt::value_type;

  auto read_lo = [](void) -> std::uint32_t { return mcal::reg::reg_access_static<std::uint32_t, std::uint32_t, mcal::reg::r32_stk_cntl>::reg_get(); };
  auto read_hi = [](void) -> std::uint32_t { return mcal::reg::reg_access_static<std::uint32_t, std::uint32_t, mcal::reg::r32_stk_cnth>::reg_get(); };

  auto get_consistent_microsecond_tick() noexcept -> mcal::gpt::value_type
  {
    std::uint64_t consistent_unscaled_tick { };

    for(;;)
    {
      const volatile std::uint32_t mt_lo1 = read_lo();
      const volatile std::uint32_t mt_hi  = read_hi();
      const volatile std::uint32_t mt_lo2 = read_lo();

      if(mt_lo2 >= mt_lo1)
      {
        consistent_unscaled_tick = util::make_long(mt_lo1, mt_hi);

        break;
      }
    }

    return static_cast<mcal::gpt::value_type>((std::uint64_t) (consistent_unscaled_tick + 72U) / 144U);
  }
}

void mcal::gpt::init(const config_type*)
{
  if(!gpt_is_initialized())
  {
    // Clear the counter entirely and thereby initialize the count value (bits_05-30) to 0.
    mcal::reg::reg_access_static<std::uint32_t, std::uint32_t, mcal::reg::r32_stk_ctlr, static_cast<std::uint32_t>(UINT8_C(0))>::reg_set();

    // Enable the counter interrupt (bit_01).
    // R32_STK_CTLR->bit.u1STIE = 1u;
    mcal::reg::reg_access_static<std::uint32_t, std::uint32_t, mcal::reg::r32_stk_ctlr, static_cast<std::uint32_t>(UINT8_C(1))>::bit_set();

    // Select HCLK as time base (bit_02).
    // R32_STK_CTLR->bit.u1STCLK = 1u;
    mcal::reg::reg_access_static<std::uint32_t, std::uint32_t, mcal::reg::r32_stk_ctlr, static_cast<std::uint32_t>(UINT8_C(2))>::bit_set();

    // Select upcounting mode (bit_04).
    // R32_STK_CTLR->bit.u1MODE = 0u;
    mcal::reg::reg_access_static<std::uint32_t, std::uint32_t, mcal::reg::r32_stk_ctlr, static_cast<std::uint32_t>(UINT8_C(4))>::bit_clr();

    // Start the counter (bit_00).
    // R32_STK_CTLR->bit.u1STE = 1u;
    mcal::reg::reg_access_static<std::uint32_t, std::uint32_t, mcal::reg::r32_stk_ctlr, static_cast<std::uint32_t>(UINT8_C(0))>::bit_set();

    gpt_is_initialized() = true;
  }
}

mcal::gpt::value_type mcal::gpt::secure::get_time_elapsed()
{
  return local::get_consistent_microsecond_tick();
}
