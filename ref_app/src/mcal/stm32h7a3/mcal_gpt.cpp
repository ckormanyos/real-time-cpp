///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2022.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <mcal/mcal_gpt_arm_sys_tick.h>

#include <mcal_gpt.h>

namespace local
{
  using arm_sys_tick_type =
    mcal::gpt::arm_sys_tick<static_cast<std::uint32_t>(UINT32_C(280)), mcal::gpt::value_type>;
}

extern "C"
auto __sys_tick_handler(void) noexcept -> void
{
  using local::arm_sys_tick_type;

  // Increment the system tick (having 64-bits) with 0x01000000.

  arm_sys_tick_type::my_system_tick =
    static_cast<typename arm_sys_tick_type::value_type>
    (
      arm_sys_tick_type::my_system_tick + static_cast<std::uint32_t>(UINT32_C(0x01000000))
    );
}

auto mcal::gpt::init(const config_type*) -> void
{
  using local::arm_sys_tick_type;

  arm_sys_tick_type::init();
}

auto mcal::gpt::secure::get_time_elapsed() -> mcal::gpt::value_type
{
  using local::arm_sys_tick_type;

  return static_cast<mcal::gpt::value_type>(arm_sys_tick_type::get_time_elapsed());
}
