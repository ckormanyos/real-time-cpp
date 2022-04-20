///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2013 - 2022.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <chrono>
#include <iostream>
#include <mcal_wdg_watchdog.h>

const mcal::wdg::watchdog::timer_type::tick_type mcal::wdg::watchdog::my_period(timer_type::seconds(2U));

mcal::wdg::watchdog mcal::wdg::watchdog::the_watchdog(watchdog::the_watchdog_thread_function);

auto mcal::wdg::watchdog::get_watchdog_timeout() -> bool
{
  // TBD: Consider using C++11/C++20 atomics for this code area.
  // See Synopsis Coverity: https://scan9.scan.coverity.com/reports.htm#v48132/p14235/fileInstanceId=95338277&defectInstanceId=8753985&mergedDefectId=254442
  my_mutex.lock();
  const auto timeout_result = my_timer.timeout();
  my_mutex.unlock();

  return timeout_result;
}

auto mcal::wdg::watchdog::reset_watchdog_timer() -> void
{
  // TBD: Consider using C++11/C++20 atomics for this code area.
  // See Synopsis Coverity: https://scan9.scan.coverity.com/reports.htm#v48132/p14235/fileInstanceId=95338277&defectInstanceId=8753986&mergedDefectId=254441
  my_mutex.lock();
  my_timer.start_relative(mcal::wdg::watchdog::my_period);
  my_mutex.unlock();
}

MCAL_WDG_NORETURN
auto mcal::wdg::watchdog::the_watchdog_thread_function() -> void
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
      if(watchdog::the_watchdog.get_watchdog_timeout())
      {
        timeout_has_occurred = true;
      }

      std::this_thread::sleep_for(std::chrono::milliseconds(20U));
    }
  }
}
