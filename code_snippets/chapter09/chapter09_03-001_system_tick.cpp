///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2019 - 2023.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

// chapter09_03-001_system_tick.cpp

// See also https://godbolt.org/z/MTT31WGd4

#include <atomic>
#include <chrono>
#include <cstdint>
#include <iostream>
#include <thread>

namespace mcal { namespace gpt {

  using value_type  = std::uint64_t;
  using config_type = void;

  void init(const config_type*);

  std::atomic<bool> simulation_is_ended = false;

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
    const auto tim0_cnt_1 = static_cast<timer_register_type>(system_tick_simulated_register);
    const auto sys_tick_1 = system_tick;

    // Do the second read of the timer0 counter.
    const auto tim0_cnt_2 = static_cast<timer_register_type>(system_tick_simulated_register);

    // Perform the consistency check.
    const auto consistent_microsecond_tick
      =
      static_cast<mcal::gpt::value_type>
      (
        (tim0_cnt_2 >= tim0_cnt_1) ? static_cast<mcal::gpt::value_type>(sys_tick_1  | static_cast<std::uint8_t>(tim0_cnt_1 >> static_cast<unsigned>(UINT8_C(1))))
                                   : static_cast<mcal::gpt::value_type>(system_tick | static_cast<std::uint8_t>(tim0_cnt_2 >> static_cast<unsigned>(UINT8_C(1))))
      );

    return consistent_microsecond_tick;
  }
  else
  {
    return static_cast<mcal::gpt::value_type>(UINT8_C(0));
  }
}

auto simulated_system_tick() -> void
{
  while(!std::atomic_load(&mcal::gpt::simulation_is_ended))
  {
    system_tick_simulated_register =
      static_cast<std::uint8_t>
      (
        system_tick_simulated_register + static_cast<std::uint8_t>(UINT8_C(1))
      );

    std::this_thread::sleep_for(std::chrono::microseconds(1U));

    if(system_tick_simulated_register == 0x80U)
    {
      system_tick_simulated_register = 0U;

      system_tick =
        static_cast<mcal::gpt::value_type>
        (
          system_tick + static_cast<mcal::gpt::value_type>(UINT8_C(0x80))
        );

      std::this_thread::sleep_for(std::chrono::milliseconds(3U));
    }
  }
}

auto simulated_system_start() -> void
{
  for(auto prescaler = static_cast<std::uint16_t>(UINT8_C(0)); prescaler < static_cast<std::uint16_t>(UINT8_C(32)); ++prescaler)
  {
    std::this_thread::sleep_for(std::chrono::milliseconds(static_cast<unsigned>(UINT8_C(7))));

    std::cout << "mcal::gpt::secure::get_time_elapsed(): "
              << mcal::gpt::secure::get_time_elapsed()
              << std::endl;
  }

  std::atomic_store(&mcal::gpt::simulation_is_ended, true);
}

auto main() -> int;

auto main() -> int
{
  mcal::gpt::init(nullptr);

  std::thread simulated_thread_system_tick (simulated_system_tick);
  std::thread simulated_thread_system_start(simulated_system_start);

  simulated_thread_system_tick.join();
  simulated_thread_system_start.join();
}
