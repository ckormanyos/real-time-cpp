///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2015.
//  Copyright Joel Winarske 2019.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <array>
#include <cstddef>
#include <cstdint>
#include <mcal_config.h>
#include <mcal_gpt.h>
#include <mcal_reg.h>
#include <mcal_irq.h>
#include <mcal_osc.h>

namespace
{
  // The one (and only one) system tick.
  volatile mcal::gpt::value_type mcal_gpt_system_tick;

  bool& gpt_is_initialized() __attribute__((used, noinline));

  bool& gpt_is_initialized()
  {
    static bool is_init = bool();

    return is_init;
  }
}

extern "C" void __sys_tick_handler() __attribute__((interrupt));

extern "C" void __sys_tick_handler()
{
  // Update 64-bit counter with microsecond count.
  mcal_gpt_system_tick += mcal::config::systick_inc;
}

void mcal::gpt::init(const config_type*)
{
  if(!gpt_is_initialized())
  {
    const std::uint32_t systick_load_val =
      std::uint32_t(mcal::osc::get_sys_clk_rate() / mcal::config::systick_hz) & UINT32_C(0x00FFFFFF);

    // set reload register
    mcal::reg::reg_access_dynamic<std::uint32_t,
                                  std::uint32_t>::reg_set(mcal::reg::systick_load, systick_load_val - 1);

    // set nvic priority
    mcal::irq::set_handler_priority(mcal::irq::systick_irqn,
                                    std::uint32_t(std::uint32_t(UINT32_C(1) << mcal::irq::nvic_priority_bits) - UINT32_C(1)));

    // load counter value
    mcal::reg::reg_access_static<std::uint32_t,
                                 std::uint32_t,
                                 mcal::reg::systick_val,
                                 UINT32_C(0)>::reg_set();

    // enable IRQ and timer
    mcal::reg::reg_access_static<std::uint32_t,
                                 std::uint32_t,
                                 mcal::reg::systick_ctrl,
                                 std::uint32_t(  systick_ctrl_clksource
                                               | systick_ctrl_tickint
                                               | systick_ctrl_enable)>::reg_set();

    gpt_is_initialized() = true;
  }
}

mcal::gpt::value_type mcal::gpt::secure::get_time_elapsed()
{
  if(gpt_is_initialized())
  {
    // Return the system tick using a multiple read to ensure data consistency.

    typedef std::uint32_t timer_address_type;
    typedef std::uint16_t timer_register_type;

    // Do the first read of the systick counter and the system tick variable.
    const timer_register_type   sys_tick_cnt_1 = mcal::reg::reg_access_static<timer_address_type,
                                                                              timer_register_type,
                                                                              mcal::reg::systick_val>::reg_get();
    const mcal::gpt::value_type sys_tick_1     = mcal_gpt_system_tick;

    // Do the second read of the systick counter.
    const timer_register_type   sys_tick_cnt_2 = mcal::reg::reg_access_static<timer_address_type,
                                                                              timer_register_type,
                                                                              mcal::reg::systick_val>::reg_get();

    // Perform the consistency check.
    const mcal::gpt::value_type consistent_microsecond_tick
      = ((sys_tick_cnt_2 >= sys_tick_cnt_1) ? mcal::gpt::value_type(sys_tick_1           | sys_tick_cnt_1)
                                            : mcal::gpt::value_type(mcal_gpt_system_tick | sys_tick_cnt_2));

    return consistent_microsecond_tick;
  }
  else
  {
    return mcal::gpt::value_type(0U);
  }
}
