#include <mcal_gpt.h>
#include <mcal_reg_access.h>
#include <util/utility/util_two_part_data_manipulation.h>

namespace
{
  // The one (and only one) system tick.
  volatile mcal::gpt::value_type system_tick;
}

mcal::gpt::value_type mcal::gpt::get_time_elapsed(void)
{
  // Return the system tick using a multiple read to ensure data consistency
  // of the high-byte of the system tick.
  // Avoid disabling the interrupts here (i.e., with std::atomic_load)
  // because this subroutine is called very often in the inner-loop of
  // the multitasking scheduler.

  const value_type tick0 = system_tick;
  const value_type tick1 = system_tick;

  const bool tick0_is_consistent = (util::hi_part<std::uint8_t>(tick0) == util::hi_part<std::uint8_t>(tick1));

  return (tick0_is_consistent ? tick0 : system_tick);
}

extern "C" void __vector_14(void) __attribute__((signal, used, externally_visible));
void __vector_14(void)
{
  // Increment the system tick in the timer interrupt.
  ++::system_tick;
}

void mcal::gpt::init(const mcal::gpt::config_type*)
{
  // Clear Timer0 Overflow Flag.
  mcal::reg_access<std::uint8_t, std::uint8_t, mcal::registers::REG_TIFR0, 0x02U>::fixed_reg_set();

  // Enable Compare Match A Interrupt.
  mcal::reg_access<std::uint8_t, std::uint8_t, mcal::registers::REG_TIMSK0, 0x02U>::fixed_reg_set();

  // Set CTC mode 2.
  mcal::reg_access<std::uint8_t, std::uint8_t, mcal::registers::REG_TCCR0A, 0x02U>::fixed_reg_set();

  // Set clock to 16MHz/64 = 250kHz.
  mcal::reg_access<std::uint8_t, std::uint8_t, mcal::registers::REG_TCCR0B, 0x03U>::fixed_reg_set();

  // Set Compare Match A value for 0.5ms (= 125 ticks).
  mcal::reg_access<std::uint8_t, std::uint8_t, mcal::registers::REG_OCR0A, 125U - 1U>::fixed_reg_set();
}
