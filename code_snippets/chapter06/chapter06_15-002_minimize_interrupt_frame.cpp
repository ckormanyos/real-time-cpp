///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2019.
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
  volatile std::uint32_t system_tick;
}

void increment_system_tick();

extern "C"
void __vector_simulated_timer(void)
{
  increment_system_tick();
}

void simulated_timer_thread()
{
  for(;;)
  {
    std::this_thread::sleep_for(std::chrono::milliseconds(100U));

    __vector_simulated_timer();
  }
}

int main()
{
  std::thread t1 { simulated_timer_thread };

  t1.join();
}

void increment_system_tick()
{
  ++system_tick;

  std::cout << "system:tick: " << system_tick << std::endl;
}
