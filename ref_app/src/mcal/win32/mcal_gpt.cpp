#include <windows.h>
#include <mcal_gpt.h>

namespace
{
  void sleep_with_prescaler()
  {
    static std::uint_fast32_t prescale;
    ++prescale;

    const std::uint_fast32_t prescale_mod = static_cast<std::uint_fast32_t>(prescale % static_cast<std::uint_fast32_t>(4096U));
    const DWORD delay = ((prescale_mod == static_cast<std::uint_fast32_t>(0u)) ? static_cast<DWORD>(3u) : static_cast<DWORD>(0u));

    ::Sleep(delay);
  }

  std::uint64_t consistent_microsecond_tick()
  {
    static bool is_init = false;

    static std::uint64_t frequency;
    static std::uint64_t initial_tick;

    if(!is_init)
    {
      is_init = true;

      LARGE_INTEGER f;
      ::QueryPerformanceFrequency(&f);
      frequency = static_cast<std::uint64_t>(f.QuadPart);

      LARGE_INTEGER c;
      ::QueryPerformanceCounter(&c);
      initial_tick = c.QuadPart;
    }

    LARGE_INTEGER cnt;
    ::QueryPerformanceCounter(&cnt);

    const std::uint64_t delta = cnt.QuadPart - initial_tick;

    const double delta_seconds = static_cast<double>(delta) / static_cast<double>(frequency);

    return static_cast<std::uint64_t>(delta_seconds * 1000000.0);
  }
}

void mcal::gpt::init(const config_type*)
{
  static_cast<void>(::consistent_microsecond_tick());
}

mcal::gpt::value_type mcal::gpt::get_time_elapsed()
{
  sleep_with_prescaler();

  const std::uint64_t microsecond_tick_quad = consistent_microsecond_tick();

  const mcal::gpt::value_type microsecond_tick = static_cast<mcal::gpt::value_type>(microsecond_tick_quad);

  return microsecond_tick;
}
