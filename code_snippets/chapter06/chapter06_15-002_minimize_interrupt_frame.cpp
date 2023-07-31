///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2019 - 2023.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

// chapter06_15-002_minimize_interrupt_frame.cpp

#include <chrono>
#include <cstdint>
#include <iostream>
#include <thread>

namespace
{
  volatile auto system_tick = std::uint32_t { };
}

auto increment_system_tick() -> void;

extern "C"
{
  auto __vector_simulated_timer(void) -> void;

  auto __vector_simulated_timer(void) -> void
  {
    increment_system_tick();
  }
}

auto simulated_timer_thread() -> void;

auto simulated_timer_thread() -> void
{
  for(auto i = static_cast<unsigned>(UINT8_C(0)); i < static_cast<unsigned>(UINT8_C(8)); ++i)
  {
    std::this_thread::sleep_for(std::chrono::milliseconds(static_cast<unsigned>(UINT8_C(100))));

    __vector_simulated_timer();
  }
}

auto main() -> int;

auto main() -> int
{
  std::thread t1 { simulated_timer_thread };

  t1.join();
}

auto increment_system_tick() -> void
{
  system_tick =
    static_cast<std::uint32_t>
    (
      system_tick + static_cast<std::uint32_t>(UINT8_C(1))
    );

  std::cout << "system:tick: " << system_tick << std::endl;
}
