///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2015.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <array>
#include <cstddef>
#include <cstdint>

#include <mcal_cpu.h>
#include <mcal_gpt.h>
#include <mcal_reg.h>

namespace
{
  // The one (and only one) system tick.
  volatile std::uint64_t system_tick;

  bool& gpt_is_initialized() __attribute__((used, noinline));

  bool& gpt_is_initialized()
  {
    static bool is_init = false;

    return is_init;
  }
}

extern "C" void __sys_tick_handler(void) __attribute__((used, noinline));

extern "C" void __sys_tick_handler(void)
{
  // Increment the 64-bit system tick with 0x01000000, representing (2^24) [microseconds/32].

  system_tick = system_tick + UINT32_C(0x01000000);
}

void mcal::gpt::init(const config_type*)
{
  if(gpt_is_initialized() == false)
  {
    // Set up an interrupt on ARM(R) sys tick.

    mcal::reg::reg_access_static<std::uint32_t, std::uint32_t, mcal::reg::sys_tick_ctrl, UINT32_C(0)>::reg_set();

    // Set sys tick reload register.
    mcal::reg::reg_access_static<std::uint32_t, std::uint32_t, mcal::reg::sys_tick_load, UINT32_C(0x00FFFFFF)>::reg_set();

    // Initialize sys tick counter value.
    mcal::reg::reg_access_static<std::uint32_t, std::uint32_t, mcal::reg::sys_tick_val,  UINT32_C(0)>::reg_set();

    // Set sys tick clock source to ahb.
    mcal::reg::reg_access_static<std::uint32_t, std::uint32_t, mcal::reg::sys_tick_ctrl, UINT32_C(4)>::reg_or();

    // Enable sys tick interrupt.
    mcal::reg::reg_access_static<std::uint32_t, std::uint32_t, mcal::reg::sys_tick_ctrl, UINT32_C(2)>::reg_or();

    // Enable sys tick timer.
    mcal::reg::reg_access_static<std::uint32_t, std::uint32_t, mcal::reg::sys_tick_ctrl, UINT32_C(1)>::reg_or();

    gpt_is_initialized() = true;
  }
}

mcal::gpt::value_type mcal::gpt::secure::get_time_elapsed()
{
  if(gpt_is_initialized())
  {
    // Return the system tick using a multiple read to ensure data consistency.

    typedef std::uint32_t timer_address_type;
    typedef std::uint32_t timer_register_type;

    // Do the first read of the sys tick counter and the system tick.
    // Handle reverse counting for sys tick counting down.
    const timer_register_type   sys_tick_val_1 =
      timer_register_type(  UINT32_C(0x00FFFFFF)
                          - mcal::reg::reg_access_static<timer_address_type,
                                                         timer_register_type,
                                                         mcal::reg::sys_tick_val>::reg_get());

    const std::uint64_t system_tick_gpt = system_tick;

    // Do the second read of the sys tick counter.
    // Handle reverse counting for sys tick counting down.
    const timer_register_type   sys_tick_val_2 =
      timer_register_type(  UINT32_C(0x00FFFFFF)
                          - mcal::reg::reg_access_static<timer_address_type,
                                                         timer_register_type,
                                                         mcal::reg::sys_tick_val>::reg_get());

    // Perform the consistency check.
    const std::uint64_t consistent_tick =
      ((sys_tick_val_2 >= sys_tick_val_1) ? std::uint64_t(system_tick_gpt | sys_tick_val_1)
                                          : std::uint64_t(system_tick     | sys_tick_val_2));

    // Perform scaling and include a rounding correction.
    const mcal::gpt::value_type consistent_microsecond_tick =
      mcal::gpt::value_type(std::uint64_t(consistent_tick + 84U) / 168U);

    return consistent_microsecond_tick;
  }
  else
  {
    return mcal::gpt::value_type(0U);
  }
}
