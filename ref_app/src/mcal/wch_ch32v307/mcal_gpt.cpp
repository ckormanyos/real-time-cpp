///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2022 - 2024.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <mcal_gpt.h>

#include <util/utility/util_two_part_data_manipulation.h>

#include <CH32V30xxx.h>
#include <SysTick.h>

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
    std::uint64_t consistent_unscaled_tick { };

    for(;;)
    {
      const volatile std::uint32_t mt_lo1 __attribute__((no_reorder)) = R32_STK_CNTL->u32Reg;
      const volatile std::uint32_t mt_hi  __attribute__((no_reorder)) = R32_STK_CNTH->u32Reg;
      const volatile std::uint32_t mt_lo2 __attribute__((no_reorder)) = R32_STK_CNTL->u32Reg;

      if(mt_lo2 >= mt_lo1)
      {
        consistent_unscaled_tick = (std::uint64_t) ((std::uint64_t) (((std::uint64_t) mt_hi) << 32U) | mt_lo1);

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
    /* enable counter interrupt */
    R32_STK_CTLR->bit.u1STIE = 1u;

    /* select HCLK as time base */
    R32_STK_CTLR->bit.u1STCLK = 1u;

    /* select upcounting mode */
    R32_STK_CTLR->bit.u1MODE = 0u;

    /* init the count value */
    R32_STK_CTLR->bit.u1INIT = 0u;

    /* start the counter */
    R32_STK_CTLR->bit.u1STE = 1u;

    gpt_is_initialized() = true;
  }
}

mcal::gpt::value_type mcal::gpt::secure::get_time_elapsed()
{
  return local::get_consistent_microsecond_tick();
}
