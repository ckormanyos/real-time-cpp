///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2015.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <array>
#include <cstddef>
#include <cstdint>
#include <mcal_gpt.h>
#include <mcal_reg_access.h>

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
}

// TBD: Do we really need interrupt attributes here?
extern "C" void __vector_timer4() __attribute__((interrupt));

extern "C" void __vector_timer4()
{
  // Clear the interrupt request bit.
  mcal::reg::access<std::uint32_t, std::uint16_t, mcal::reg::tim4_sr, UINT16_C(0x0000)>::reg_set();

  // Increment the 64-bit system tick with 0x10000, representing (2^16) microseconds.
  system_tick += UINT32_C(0x10000);
}

void mcal::gpt::init(const config_type*)
{
  if(gpt_is_initialized() == false)
  {
    // Set up an interrupt on timer4 for a system tick based
    // on the free-running 16-bit timer4 with a frequency of 1MHz.

    // Power management: Enable the power for timer4.
    mcal::reg::access<std::uint32_t, std::uint32_t, mcal::reg::rcc_apb1enr, UINT32_C(0x00000004)>::reg_or();

    // Compute the timer4 interrupt priority.
    const std::uint32_t aircr_value = mcal::reg::access<std::uint32_t, std::uint32_t, mcal::reg::aircr>::reg_get();

    // Calculate the timer4 interrupt priority.
    const std::uint32_t tmp_prio = (UINT32_C(0x700) - (aircr_value & UINT32_C(0x700))) >> 0x08;
    const std::uint32_t tmp_pre  = (UINT32_C( 0x04) - tmp_prio);
    const std::uint32_t tmp_sub  =  UINT32_C( 0x0F) >> tmp_prio;

    constexpr std::uint32_t timer4_nvic_irq_preemption_prio = UINT32_C(0x0F);
    constexpr std::uint32_t timer4_nvic_irq_sub_prio        = UINT32_C(0x0F);

    constexpr std::uint32_t timer4_irq_n = UINT32_C(30);

    const std::uint8_t timer4_interrupt_priority = std::uint8_t(  std::uint32_t(timer4_nvic_irq_preemption_prio << tmp_pre)
                                                                | std::uint32_t(timer4_nvic_irq_sub_prio & tmp_sub)
                                                               ) << 0x04;

    // Set the timer4 interrupt priority.
    mcal::reg::dynamic_access<std::uint32_t,
                              std::uint8_t>::reg_set(std::uint32_t(mcal::reg::nvic_ip + timer4_irq_n),
                                                     timer4_interrupt_priority);

    // Set the timer4 interrupt set enable register.
    mcal::reg::access<std::uint32_t,
                      std::uint32_t,
                      std::uint32_t(mcal::reg::nvic_iser + ((timer4_irq_n >> 5) * 4U)),
                      std::uint32_t(UINT32_C(1) << (timer4_irq_n & UINT32_C(0x1F)))>::reg_set();

    // Clear the timer4 interrupt request bit.
    mcal::reg::access<std::uint32_t, std::uint16_t, mcal::reg::tim4_sr, UINT16_C(0x0000)>::reg_set();

    // Enable the timer4 update interrupt.
    mcal::reg::access<std::uint32_t, std::uint16_t, mcal::reg::tim4_dier, UINT16_C(0x0001)>::reg_set();

    // Set the timer prescaler to 83 resulting in a 1MHz frequency.
    mcal::reg::access<std::uint32_t, std::uint16_t, mcal::reg::tim4_psc, UINT16_C(84 - 1)>::reg_set();

    // Set the auto-reload register for the entire 16-bit period of the timer.
    mcal::reg::access<std::uint32_t, std::uint16_t, mcal::reg::tim4_arr, UINT16_C(0xFFFF)>::reg_set();

    // Set the counter direction to counting-up and enable the counter.
    mcal::reg::access<std::uint32_t, std::uint16_t, mcal::reg::tim4_cr1, UINT16_C(0x0001)>::reg_set();

    // Re-initialize the counter and generate an update of the registers.
    mcal::reg::access<std::uint32_t, std::uint16_t, mcal::reg::tim4_egr, UINT16_C(0x0001)>::reg_set();

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

    // Do the first read of the timer4 counter and the system tick.
    const timer_register_type   tim4_cnt_1 = mcal::reg::access<timer_address_type, timer_register_type, mcal::reg::tim4_cnt>::reg_get();
    const mcal::gpt::value_type sys_tick_1 = system_tick;

    // Do the second read of the timer4 counter.
    const timer_register_type   tim4_cnt_2 = mcal::reg::access<timer_address_type, timer_register_type, mcal::reg::tim4_cnt>::reg_get();

    // Perform the consistency check.
    const mcal::gpt::value_type consistent_microsecond_tick
      = ((tim4_cnt_2 >= tim4_cnt_1) ? mcal::gpt::value_type(sys_tick_1  | tim4_cnt_1)
                                    : mcal::gpt::value_type(system_tick | tim4_cnt_2));

    return consistent_microsecond_tick;
  }
  else
  {
    return mcal::gpt::value_type(0U);
  }
}
