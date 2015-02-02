///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2015.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <cstdfloat>
#include <windows.h>
#include <mcal_gpt.h>

mcal::gpt::value_type mcal::gpt::secure::get_time_elapsed()
{
  // Sleep in order to reduce the load on a Win32 simulated target.
  static std::uint_least16_t prescale;
  ++prescale;

  ::Sleep((std::uint_least16_t(prescale % 4096U) == std::uint_least16_t(0U)) ? 3U : 0U);

  static bool is_init = bool();

  static LARGE_INTEGER start_time;
  static LARGE_INTEGER frequency;

  if(is_init == false)
  {
    is_init = true;

    ::QueryPerformanceFrequency(&frequency);
    ::QueryPerformanceCounter  (&start_time);
  }

  LARGE_INTEGER tick;
  ::QueryPerformanceCounter(&tick);

  const std::uint64_t elapsed = static_cast<std::uint64_t>(tick.QuadPart - start_time.QuadPart);

  return mcal::gpt::value_type((std::float64_t(elapsed) / std::float64_t(frequency.QuadPart)) * FLOAT64_C(1000000.0));
}
