
#include "BL602.h"

#include <mcal_gpt.h>

//-----------------------------------------------------------------------------------------
// Defines
//-----------------------------------------------------------------------------------------
namespace
{
  constexpr std::uint64_t TIMEOUT_1S { UINT64_C(10000000) };

  // The one (and only one) system tick.
  volatile auto mcal_gpt_system_tick = mcal::gpt::value_type { };

  auto gpt_is_initialized() -> bool& __attribute__((used, noinline));

  auto gpt_is_initialized() -> bool&
  {
    static auto is_init = bool { };

    return is_init;
  }
}

extern "C" void Isr_TIMER_Interrupt (void) __attribute__((interrupt,used,noinline));

extern "C"
void Isr_TIMER_Interrupt (void)
{
  // Set the next timer timeout timeout.

  CLIC_MTIMECMP = (uint64_t)(CLIC_MTIME + TIMEOUT_1S);
}

extern "C" auto mcal_gpt_init() -> void;

extern "C" auto mcal_gpt_init() -> void
{
  mcal::gpt::init(nullptr);
}

auto mcal::gpt::init(const config_type*) -> void
{
  if(!gpt_is_initialized())
  {
    // Set the next timer interrupt timeout.
    CLIC_MTIMECMP = (uint64_t)(CLIC_MTIME + TIMEOUT_1S);

    // Set the is-initialized indication flag.
    gpt_is_initialized() = true;
  }
}

auto mcal::gpt::secure::get_time_elapsed() -> mcal::gpt::value_type
{
  if(gpt_is_initialized())
  {
    // Return the system tick using a multiple read to ensure data consistency.

    const volatile uint64_t time_first  = CLIC_MTIME;
    const volatile uint64_t time_second = CLIC_MTIME;

    const volatile bool is_steady = (((uint32_t) time_second > (uint32_t) time_first) ? true : false);

    value_type consistent_microsecond_tick = (is_steady ? time_first : CLIC_MTIME);

    consistent_microsecond_tick /= 10U;

    return consistent_microsecond_tick;
  }
  else
  {
    return value_type { UINT8_C(0) };
  }
}
