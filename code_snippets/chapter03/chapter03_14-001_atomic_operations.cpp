///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2017 - 2025.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

// chapter03_14-001_atomic_operations.cpp

#include <atomic>
#include <chrono>
#include <cstdint>
#include <iostream>
#include <thread>

static void simulated_tick_interrupt_handler();

namespace
{
  // The one (and only one) 32-bit system-tick.
  volatile std::atomic<std::uint32_t> system_tick { };
}

static void simulated_tick_interrupt_handler()
{
  for(;;)
  {
    ++system_tick;

    std::this_thread::sleep_for(std::chrono::milliseconds(10U));
  }
}

auto get_time_elapsed() -> std::uint32_t
{
  // Ensure 32-bit consistency on an 8-bit CPU.
  return std::atomic_load(&system_tick);
}

auto main() -> int
{
  std::thread simulated_system_tick_thread(simulated_tick_interrupt_handler);

  for(;;)
  {
    std::cout << "get_time_elapsed() is " << get_time_elapsed() << std::endl;
  }
}
