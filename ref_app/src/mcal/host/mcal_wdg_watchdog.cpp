///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2013 - 2022.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <atomic>
#include <chrono>
#include <iostream>

#include <mcal_wdg_watchdog.h>

namespace local
{
  auto timer_lock() noexcept -> std::atomic_flag&
  {
    static std::atomic_flag  my_lock = ATOMIC_FLAG_INIT;

    return my_lock;
  }
}

mcal::wdg::watchdog& mcal::wdg::watchdog::the_watchdog()
{
  static mcal::wdg::watchdog wd(the_watchdog_thread_function);

  return wd;
}

auto mcal::wdg::watchdog::get_watchdog_timeout() -> bool
{
  while(local::timer_lock().test_and_set()) { ; }
  const auto timeout_result = my_timer.timeout();
  local::timer_lock().clear();

  return timeout_result;
}

auto mcal::wdg::watchdog::reset_watchdog_timer() -> void
{
  while(local::timer_lock().test_and_set()) { ; }
  my_timer.start_relative(mcal::wdg::watchdog::my_period);
  local::timer_lock().clear();
}

MCAL_WDG_NORETURN auto mcal::wdg::watchdog::the_watchdog_thread_function() -> void
{
  std::this_thread::sleep_for(std::chrono::milliseconds(10U));

  bool timeout_has_occurred = false;

  for(;;)
  {
    if(timeout_has_occurred)
    {
      std::cout << "error: at least one watchdog timeout has occurred" << std::endl;

      std::this_thread::sleep_for(std::chrono::milliseconds(500U));
    }
    else
    {
      if(watchdog::the_watchdog().get_watchdog_timeout())
      {
        timeout_has_occurred = true;
      }

      std::this_thread::sleep_for(std::chrono::milliseconds(20U));
    }
  }
}
