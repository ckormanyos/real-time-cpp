///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2018.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <chrono>
#include <cstdfloat>
#include <thread>

#include <windows.h>

#include <mcal_gpt.h>

namespace
{
  LARGE_INTEGER frequency;
  LARGE_INTEGER start_time;
}

void mcal::gpt::init(const mcal::gpt::config_type*)
{
  const bool query_performance_frequency_is_ok =
    (QueryPerformanceFrequency(&frequency)  == TRUE);

  const bool query_performance_counter_is_ok =
    (QueryPerformanceCounter  (&start_time) == TRUE);

  static_cast<void>(query_performance_frequency_is_ok);
  static_cast<void>(query_performance_counter_is_ok);
}

mcal::gpt::value_type mcal::gpt::secure::get_time_elapsed()
{
  // Sleep in order to reduce the load on a Windows simulated target.
  static std::uint_fast16_t prescale;

  ++prescale;

  if((prescale % 4096U) == 0U)
  {
    std::this_thread::sleep_for(std::chrono::milliseconds(3U));
  }
  else
  {
    std::this_thread::yield();
  }

  // Query the performance counter for the local tick value.
  LARGE_INTEGER local_tick_value;

  const bool local_query_performance_counter_is_ok =
    (QueryPerformanceCounter(&local_tick_value) == TRUE);

  static_cast<void>(local_query_performance_counter_is_ok);

  const std::uint64_t elapsed =
    static_cast<std::uint64_t>(local_tick_value.QuadPart - start_time.QuadPart);

  // Return the system tick with resolution of 1us.
  return mcal::gpt::value_type((std::float64_t(elapsed) / std::float64_t(frequency.QuadPart)) * FLOAT64_C(1000000.0));
}
