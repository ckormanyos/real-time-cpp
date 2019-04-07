
///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2015.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <mcal_gpt.h>
#include <mcal_reg.h>

namespace
{
  // The one (and only one) system tick.
  volatile mcal::gpt::value_type system_tick;

  bool& gpt_is_initialized() __attribute__((used, noinline));

  bool& gpt_is_initialized()
  {
    static bool is_init = bool();

    return is_init;
  }

  constexpr std::uint16_t system_timer_reload = UINT16_C(0xFFFF);

  // Timer rpi_arm timer counter width 16-bit / 32-bit : Select 1 = 32-bit counters.
  constexpr std::uint32_t  rpi_armtimer_ctrl_32bit        = (UINT32_C(1) << 1);

  constexpr std::uint32_t  rpi_armtimer_ctrl_prescale_1   = (UINT32_C(0) << 2);
  constexpr std::uint32_t  rpi_armtimer_ctrl_prescale_16  = (UINT32_C(1) << 2);
  constexpr std::uint32_t  rpi_armtimer_ctrl_prescale_256 = (UINT32_C(2) << 2);

  // Timer rpi_arm timer interrupt disabled : Select 1 = interrupt enabled.
  constexpr std::uint32_t  rpi_armtimer_ctrl_int_enable   = (UINT32_C(1) << 5);
  constexpr std::uint32_t  rpi_armtimer_ctrl_int_disable  = (UINT32_C(0) << 5);

  // Timer rpi_arm timer function disabled : Select 1 = timer function enabled.
  constexpr std::uint32_t  rpi_armtimer_ctrl_enable       = (UINT32_C(1) << 7);
  constexpr std::uint32_t  rpi_armtimer_ctrl_disable      = (UINT32_C(0) << 7);

  // Timer rpi_arm timer modes.
  constexpr std::uint32_t rpi_basic_arm_timer_irq         = (UINT32_C(1) << 0);
  constexpr std::uint32_t rpi_basic_arm_mailbox_irq       = (UINT32_C(1) << 1);
  constexpr std::uint32_t rpi_basic_arm_doorbell_0_irq    = (UINT32_C(1) << 2);
  constexpr std::uint32_t rpi_basic_arm_doorbell_1_irq    = (UINT32_C(1) << 3);
  constexpr std::uint32_t rpi_basic_gpu_0_halted_irq      = (UINT32_C(1) << 4);
  constexpr std::uint32_t rpi_basic_gpu_1_halted_irq      = (UINT32_C(1) << 5);
  constexpr std::uint32_t rpi_basic_access_error_1_irq    = (UINT32_C(1) << 6);
  constexpr std::uint32_t rpi_basic_access_error_0_irq    = (UINT32_C(1) << 7);
}

void mcal::gpt::detail::rpi_armtimer_interrupt_callback()
{
  // ARM Timer IRQ pending: Clear the rpi_arm timer interrupt request bit.
  mcal::reg::reg_access_static<std::uint32_t,
                               std::uint32_t,
                               mcal::reg::rpi_armtimer_irq_clear,
                               UINT32_C(1)>::reg_set();

  // Increment the system tick.
  system_tick += static_cast<std::uint32_t>(static_cast<std::uint32_t>(system_timer_reload) + UINT32_C(1));
}

void mcal::gpt::init(const config_type*)
{
  if(gpt_is_initialized() == false)
  {
    gpt_is_initialized() = true;

    // Setup the rpi_arm timer period.
    // Timer frequency = (Clock / 1) * 0x10000.
    mcal::reg::reg_access_static<std::uint32_t,
                                 std::uint32_t,
                                 mcal::reg::rpi_armtimer_load,
                                 system_timer_reload>::reg_set();

    // Setup the rpi_arm timer control register.
    mcal::reg::reg_access_static<std::uint32_t,
                      std::uint32_t,
                      mcal::reg::rpi_armtimer_control,
                      (  rpi_armtimer_ctrl_enable
                       | rpi_armtimer_ctrl_int_enable
                       | rpi_armtimer_ctrl_prescale_1)>::reg_set();

    // Enable the rpi_arm timer interrupt.
    mcal::reg::reg_access_static<std::uint32_t,
                                 std::uint32_t,
                                 mcal::reg::rpi_interrupt_enable_basic_irqs,
                                 rpi_basic_arm_timer_irq>::reg_set();
  }
}

mcal::gpt::value_type mcal::gpt::secure::get_time_elapsed()
{
  if(gpt_is_initialized())
  {
    // Return the system tick using a multiple read to ensure data consistency.

    typedef std::uint32_t timer_address_type;
    typedef std::uint16_t timer_register_type;

    // Do the first read of the rpi_arm timer value and the system tick.
    const timer_register_type   tmr_tick_1 = system_timer_reload - mcal::reg::reg_access_static<timer_address_type, timer_register_type, mcal::reg::rpi_armtimer_value>::reg_get();
    const mcal::gpt::value_type sys_tick_1 = system_tick;

    // Do the second read of the rpi_arm timer value.
    const timer_register_type   tmr_tick_2 = system_timer_reload - mcal::reg::reg_access_static<timer_address_type, timer_register_type, mcal::reg::rpi_armtimer_value>::reg_get();

    // Perform the consistency check.
    const mcal::gpt::value_type consistent_microsecond_tick
      = ((tmr_tick_2 >= tmr_tick_1) ? mcal::gpt::value_type(sys_tick_1  | tmr_tick_1)
                                    : mcal::gpt::value_type(system_tick | tmr_tick_2));

    return consistent_microsecond_tick;
  }
  else
  {
    return mcal::gpt::value_type(0U);
  }
}
