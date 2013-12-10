///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2013.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <chrono>
#include <cstdint>
#include <iostream>
#include <mutex>
#include <thread>
#include <mcal_wdg.h>
#include <util/utility/util_noncopyable.h>
#include <util/utility/util_time.h>

namespace
{
  class watchdog_timeout : private util::noncopyable
  {
  private:
    typedef util::timer<std::uint32_t> timer_type;

    static const timer_type::tick_type watchdog_timeout_period;
    static timer_type                  watchdog_timeout_timer;
    static std::mutex                  watchdog_timeout_mutex;

    static void watchdog_timeout_function();

    friend class mcal::wdg::secure;
  };

  const watchdog_timeout::timer_type::tick_type watchdog_timeout::watchdog_timeout_period(timer_type::seconds(2U));
  watchdog_timeout::timer_type                  watchdog_timeout::watchdog_timeout_timer (watchdog_timeout_period);
  std::mutex                                    watchdog_timeout::watchdog_timeout_mutex;

  void watchdog_timeout::watchdog_timeout_function()
  {
    static bool timeout_has_occurred;

    for(;;)
    {
      watchdog_timeout::watchdog_timeout_mutex.lock();
      const bool timeout_result = watchdog_timeout::watchdog_timeout_timer.timeout();
      watchdog_timeout::watchdog_timeout_mutex.unlock();

      if(timeout_result)
      {
        timeout_has_occurred = true;
      }

      std::this_thread::sleep_for(std::chrono::milliseconds(50U));

      if(timeout_has_occurred)
      {
        std::cout << "error: at least one watchdog timeout has occurred" << std::endl;
      }
    }
  }
}

void mcal::wdg::secure::trigger()
{
  static std::thread watchdog_timeout_thread(watchdog_timeout::watchdog_timeout_function);

  watchdog_timeout::watchdog_timeout_mutex.lock();
  watchdog_timeout::watchdog_timeout_timer.start_relative(watchdog_timeout::watchdog_timeout_period);
  watchdog_timeout::watchdog_timeout_mutex.unlock();
}
