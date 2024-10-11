///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2012 - 2020.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <mcal_cpu.h>
#include <mcal_gpt.h>
#include <mcal_irq.h>
#include <mcal_reg.h>

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

  constexpr std::uint16_t timer7_frequency_khz = UINT16_C(24);
  constexpr std::uint32_t timer7_reload_value  = static_cast<std::uint32_t>(UINT32_C(0x10000) * static_cast<std::uint32_t>(timer7_frequency_khz));
}

extern "C" void __vector_timer7();

void __vector_timer7()
{
  // Disable the dmtimer7 interrupts.
  mcal::reg::reg_access_static<std::uint32_t,
                               std::uint32_t,
                               mcal::reg::dmtimer7::irqenable_clr,
                               UINT32_C(7)>::reg_set();

  // Clear the status of the dmtimer7 interrupt flags.
  mcal::reg::reg_access_static<std::uint32_t,
                               std::uint32_t,
                               mcal::reg::dmtimer7::irqstatus,
                               UINT32_C(7)>::reg_set();

  // Increment the 64-bit system tick with 0x100000000, representing (2^32) [microseconds/24].

  mcal_gpt_system_tick += UINT64_C(0x100000000);

  // Signal the end of the dmtimer7 interrupt.
  mcal::reg::reg_access_static<std::uint32_t,
                               std::uint32_t,
                               mcal::reg::dmtimer7::irq_eoi,
                               UINT32_C(0)>::bit_clr();

  // Enable the dmtimer7 interrupts.
  mcal::reg::reg_access_static<std::uint32_t,
                               std::uint32_t,
                               mcal::reg::dmtimer7::irqenable_set,
                               UINT32_C(1)>::bit_set();
}

void mcal::gpt::init(const config_type*)
{
  if(!gpt_is_initialized())
  {
    mcal::reg::reg_access_static<std::uint32_t,
                                 std::uint32_t,
                                 mcal::reg::dmtimer7::tsicr,
                                 UINT32_C(6)>::reg_set();

    while(mcal::reg::reg_access_static<std::uint32_t,
                                       std::uint32_t,
                                       mcal::reg::dmtimer7::tiocp_cfg,
                                       UINT32_C(0)>::bit_get())
    {
      mcal::cpu::nop();
    }

    // Register the dmtimer7 interrupt, including priority, routing, etc.
    mcal::irq::interrupt_descriptor::register_interrupt<mcal::irq::interrupt_descriptor::isr_id_tint7,
                                                        mcal::irq::interrupt_descriptor::priority_type(0U),
                                                        mcal::irq::interrupt_descriptor::route_to_irq>();

    // Enable the dmtimer7 overflow interrupt.
    mcal::reg::reg_access_static<std::uint32_t,
                                 std::uint32_t,
                                 mcal::reg::dmtimer7::irqenable_set,
                                 UINT32_C(2)>::template reg_msk<UINT32_C(7)>();

    // Set the dmtimer7 Timer CounteR Register (TCRR).
    mcal::reg::reg_access_static<std::uint32_t,
                                 std::uint32_t,
                                 mcal::reg::dmtimer7::tcrr,
                                 UINT32_C(0)>::reg_set();

    // Poll the dmtimer7 Timer Write Posting bitS register (TWPS).
    // In posted mode the software must read the pending write
    // status bits (Timer Write Posted Status register bits [4:0])
    // to insure that following write access will not be discarded
    // due to on going write synchronization process.
    // These bits are automatically cleared by internal logic
    // when the write to the corresponding register is acknowledged.

    while(mcal::reg::reg_access_static<std::uint32_t, std::uint32_t, mcal::reg::dmtimer7::twps, UINT32_C(1)>::bit_get()) { mcal::cpu::nop(); }

    // Set the dmtimer7 Timer LoaD Register (TLDR).
    mcal::reg::reg_access_static<std::uint32_t,
                                 std::uint32_t,
                                 mcal::reg::dmtimer7::tldr,
                                 UINT32_C(0)>::reg_set();

    while(mcal::reg::reg_access_static<std::uint32_t, std::uint32_t, mcal::reg::dmtimer7::twps, UINT32_C(2)>::bit_get()) { mcal::cpu::nop(); }

    // Setup auto reload mode and start dmtimer7, with no prescaler.
    mcal::reg::reg_access_static<std::uint32_t,
                                 std::uint32_t,
                                 mcal::reg::dmtimer7::tclr,
                                 UINT32_C(3)>::reg_set();

    while(mcal::reg::reg_access_static<std::uint32_t, std::uint32_t, mcal::reg::dmtimer7::twps, UINT32_C(0)>::bit_get()) { mcal::cpu::nop(); }

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

    // Do the first read of the dmtimer7 counter and the system tick.
    const timer_register_type tim7_cnt_1   = timer7_reload_value + mcal::reg::reg_access_static<timer_address_type, timer_register_type, mcal::reg::dmtimer7::tcrr>::reg_get();
    while(mcal::reg::reg_access_static<std::uint32_t, std::uint32_t, mcal::reg::dmtimer7::twps, UINT32_C(1)>::bit_get()) { mcal::cpu::nop(); }
    const mcal::gpt::value_type sys_tick_1 = mcal_gpt_system_tick;

    // Do the second read of the dmtimer7 counter.
    const timer_register_type tim7_cnt_2   = timer7_reload_value + mcal::reg::reg_access_static<timer_address_type, timer_register_type, mcal::reg::dmtimer7::tcrr>::reg_get();
    while(mcal::reg::reg_access_static<std::uint32_t, std::uint32_t, mcal::reg::dmtimer7::twps, UINT32_C(1)>::bit_get()) { mcal::cpu::nop(); }

    // Perform the consistency check.
    const std::uint64_t consistent_tick =
      ((tim7_cnt_2 >= tim7_cnt_1) ? std::uint64_t(sys_tick_1           | tim7_cnt_1)
                                  : std::uint64_t(mcal_gpt_system_tick | tim7_cnt_2));

    // Perform scaling and include a rounding correction.
    const mcal::gpt::value_type consistent_microsecond_tick =
      mcal::gpt::value_type(std::uint64_t(consistent_tick + 12U) / 24U);

    return consistent_microsecond_tick;
  }
  else
  {
    return mcal::gpt::value_type(0U);
  }
}
