///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2023.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <mcal_gpt.h>

extern "C"
auto __sys_tick_handler(void) noexcept -> void
{
  using local_arm_sys_tick_type = ::mcal::gpt::arm_sys_tick_type;
  using local_value_type        = typename local_arm_sys_tick_type::value_type;

  // Increment the system tick (having 64-bits) with 0x01000000.

  local_arm_sys_tick_type::my_sys_tick_value =
    static_cast<local_value_type>
    (
        local_arm_sys_tick_type::my_sys_tick_value
      + static_cast<std::uint32_t>(UINT32_C(0x01000000))
    );
}
