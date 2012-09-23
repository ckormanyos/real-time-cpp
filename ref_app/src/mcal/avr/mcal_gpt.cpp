#include <atomic>
#include <chrono>
#include <mcal_gpt.h>

#include <mcal_reg_access.h>

namespace
{
  // The one (and only one) system tick.
  volatile mcal::gpt::value_type system_tick;

  mcal::gpt::value_type consistent_microsecond_tick()
  {
    // Return the system tick using a multiple read to ensure
    // data consistency of the high-byte of the system tick.

    // Do the first read of the timer0 counter register.
    const std::uint8_t tim0_cnt_0 = mcal::reg_access<std::uint8_t, std::uint8_t, mcal::reg::tcnt0>::reg_get();

    // Read the system tick.
    const mcal::gpt::value_type sys_tick_0 = system_tick;

    // Do the second read of the timer0 counter register.
    const std::uint8_t tim0_cnt_1 = mcal::reg_access<std::uint8_t, std::uint8_t, mcal::reg::tcnt0>::reg_get();

    // Perform the consistency check and return the consistent microsecond tick.
    return ((tim0_cnt_1 >= tim0_cnt_0) ? static_cast<mcal::gpt::value_type>(sys_tick_0  | (static_cast<std::uint16_t>(tim0_cnt_0 + 1U) >> 1))
                                       : static_cast<mcal::gpt::value_type>(system_tick | (static_cast<std::uint16_t>(tim0_cnt_1 + 1U) >> 1)));
  }
}

mcal::gpt::value_type mcal::gpt::get_time_elapsed()
{
  // Get the time-point of now.
  const auto time_point_now = std::chrono::high_resolution_clock::now();

  // Get the initial time-point of (time = zero).
  decltype(time_point_now) time_point_zero;

  // Compute the elapsed time from now and the initial zero time.
  const auto elapsed = std::chrono::duration_cast<std::chrono::microseconds>(time_point_now - time_point_zero);

  // Return the elapsed time.
  return static_cast<mcal::gpt::value_type>(elapsed.count());
}

extern "C" void __vector_timer0_cmp_a_irq() __attribute__((signal, used, externally_visible));

void __vector_timer0_cmp_a_irq()
{
  // This interrupt occurs every 128us.
  // Increment the 32-bit system tick by 128.
  system_tick += 0x80U;
}

void mcal::gpt::init(const config_type*)
{
  // Clear Timer0 Overflow Flag.
  mcal::reg_access<std::uint8_t, std::uint8_t, mcal::reg::tifr0, 0x02U>::reg_set();

  // Enable Compare Match A Interrupt.
  mcal::reg_access<std::uint8_t, std::uint8_t, mcal::reg::timsk0, 0x02U>::reg_set();

  // Set ctc mode 2 for counter timer0 compare.
  mcal::reg_access<std::uint8_t, std::uint8_t, mcal::reg::tccr0a, 0x02U>::reg_set();

  // Set the compare match a value to 255.
  mcal::reg_access<std::uint8_t, std::uint8_t, mcal::reg::ocr0a, 0xFFU>::reg_set();

  // Set the timer0 clock source to f_osc/8 = 2MHz and begin counting.
  mcal::reg_access<std::uint8_t, std::uint8_t, mcal::reg::tccr0b, 0x02U>::reg_set();
}

// Implement std::chrono::high_resolution_clock::now()
// for the standard library high-resolution clock.
namespace std
{
  namespace chrono
  {
    high_resolution_clock::time_point high_resolution_clock::now()
    {
      // The source of the high-resolution clock is from microseconds.
      typedef std::chrono::time_point<high_resolution_clock, microseconds> from_type;

      // Get the consistent tick in units of microseconds.
      const auto microsecond_tick = consistent_microsecond_tick();

      // Now obtain a time-point in microseconds.
      auto from_micro = from_type(microseconds(microsecond_tick));

      // And return the corresponding duration in microseconds.
      return time_point_cast<duration>(from_micro);
    }
  }
}
