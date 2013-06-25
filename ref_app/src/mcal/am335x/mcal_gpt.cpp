///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2013.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <mcal_cpu.h>
#include <mcal_gpt.h>
#include <mcal_reg_access.h>
#include <am335x_hw_regs.h>
#include <bfx.h>

namespace
{
  // The one (and only one) system tick.
  volatile mcal::gpt::value_type system_tick;

  bool& gpt_is_initialized()
  {
    static bool is_init;

    return is_init;
  }
}

mcal::gpt::value_type consistent_microsecond_tick()
{
  // Return the system tick using a multiple read to ensure
  // data consistency of the high-byte of the system tick.

  // TBD: Do this, as described above.
  // TBD: Account for the underlying 24MHz timer frequency.
  // TBD: Account counting up and the roll-over at 0xFFFFFFFE.

  return mcal::gpt::value_type(0U);
}

extern "C" void __vector_timer7() __attribute__((interrupt));

void __vector_timer7()
{
  // Disable the DMTimer interrupts.
  DMTIMER7->IRQENABLE_CLR = std::uint32_t(7UL);

  // Clear the status of the interrupt flags.
  DMTIMER7->IRQSTATUS = std::uint32_t(7UL);

  // Increment the 64-bit system tick by 1000 (decimal).
  system_tick += 1000U;

  // Notify end of interrupt.
  DMTIMER7->IRQ_EOI &= std::uint32_t(~1UL);

  // Enable the DMTimer interrupts.
  DMTIMER7->IRQENABLE_SET = std::uint32_t(2UL);
}

void mcal::gpt::init(const config_type*)
{
  if(gpt_is_initialized() == false)
  {
    DMTIMER7->TSICR = std::uint32_t(6UL);
    while(std::uint32_t(DMTIMER7->TIOCP_CFG & std::uint32_t(1UL)) != std::uint32_t(0UL)) { mcal::cpu::nop(); }

    // TBD: Register other parts of the timer7 interrupt (such as routing, etc.).
    //  Int_Register(SYS_INT_TINT7, Gpt_Notification_Timer7, 0, INT_ROUTE_IRQ);

    // Enable the timer7 overflow interrupt.
    bfx_clear_and_set_bit_mask((std::uint32_t*) &DMTIMER7->IRQENABLE_SET,
                               std::uint32_t(2UL),
                               0x7UL);

    // Set the timer7 counter register.
    while(DMTIMER7->TWPS != std::uint32_t(0UL)) { mcal::cpu::nop(); }
    DMTIMER7->TCRR = std::uint32_t(0xFFFFFFFEUL - 24000UL);

    // Set the timer7 reload register.
    while (DMTIMER7->TWPS != std::uint32_t(0UL)) { mcal::cpu::nop(); }
    DMTIMER7->TLDR = std::uint32_t(0xFFFFFFFEUL - 24000UL);

    // Set auto reload mode and start timer (no prescaler).
    DMTIMER7->TCLR = std::uint32_t(3UL);
  }
}

mcal::gpt::value_type mcal::gpt::get_time_elapsed()
{
  return (gpt_is_initialized() ? consistent_microsecond_tick()
                               : mcal::gpt::value_type(0U));
}
