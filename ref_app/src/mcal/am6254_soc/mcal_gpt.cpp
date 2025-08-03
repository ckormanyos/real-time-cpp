#include <mcal_gpt.h>

#include <core_macros.h>

mcal::gpt::value_type mcal::gpt::secure::get_time_elapsed()
{
  // Get the system tick from the system counter register.
  const value_type consistent_microsecond_tick = (value_type) ARM64_READ_SYSREG(CNTPCT_EL0);

  // Convert the consistent tick to microseconds.
  return static_cast<value_type>(static_cast<value_type>(consistent_microsecond_tick + UINT64_C(100)) / UINT64_C(200));
}
