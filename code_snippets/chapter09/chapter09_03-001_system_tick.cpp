///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2019 - 2020.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

// chapter09_03-001_system_tick.cpp

#include <atomic>
#include <chrono>
#include <cstdint>
#include <iostream>
#include <thread>

namespace mcal { namespace gpt {

  using value_type  = std::uint64_t;
  using config_type = void;

  void init(const config_type*);

  struct secure
  {
    static value_type get_time_elapsed();
  };

} } // simulated namespace mcal::gpt

namespace
{
  // The one (and only one) system tick.
  volatile mcal::gpt::value_type system_tick;
  volatile std::uint8_t          system_tick_simulated_register;

  bool& gpt_is_initialized();

  bool& gpt_is_initialized()
  {
    static bool is_init = bool();

    return is_init;
  }
}

void mcal::gpt::init(const config_type*)
{
  if(gpt_is_initialized() == false)
  {
    // Set the is-initialized indication flag.
    gpt_is_initialized() = true;
  }
}

mcal::gpt::value_type mcal::gpt::secure::get_time_elapsed()
{
  if(gpt_is_initialized())
  {
    // Return the system tick using a multiple read to ensure data consistency.

    typedef std::uint8_t timer_register_type;

    // Do the first read of the timer0 counter and the system tick.
    const timer_register_type   tim0_cnt_1 = system_tick_simulated_register;
    const mcal::gpt::value_type sys_tick_1 = system_tick;

    // Do the second read of the timer0 counter.
    const timer_register_type tim0_cnt_2   = system_tick_simulated_register;

    // Perform the consistency check.
    const mcal::gpt::value_type consistent_microsecond_tick
      = ((tim0_cnt_2 >= tim0_cnt_1) ? mcal::gpt::value_type(sys_tick_1  | std::uint8_t(tim0_cnt_1 >> 1U))
                                    : mcal::gpt::value_type(system_tick | std::uint8_t(tim0_cnt_2 >> 1U)));

    return consistent_microsecond_tick;
  }
  else
  {
    return mcal::gpt::value_type(0U);
  }
}

void simulated_system_tick()
{
  for(;;)
  {
    ++system_tick_simulated_register;

    std::this_thread::sleep_for(std::chrono::microseconds(1U));

    if(system_tick_simulated_register == 0x80U)
    {
      system_tick_simulated_register = 0U;

      system_tick += 0x80U;

      std::this_thread::sleep_for(std::chrono::milliseconds(3U));
    }
  }
}

void simulated_system_start()
{
  static std::uint16_t prescaler;

  for(;;)
  {
    ++prescaler;

    if(prescaler == 0U)
    {
      std::this_thread::sleep_for(std::chrono::milliseconds(3U));
    }

    std::cout << "mcal::gpt::secure::get_time_elapsed(): "
              << mcal::gpt::secure::get_time_elapsed()
              << std::endl;
  }
}

int main()
{
  mcal::gpt::init(nullptr);

  std::thread simulated_thread_system_tick (simulated_system_tick);
  std::thread simulated_thread_system_start(simulated_system_start);

  simulated_thread_system_tick.join();
  simulated_thread_system_start.join();
}
