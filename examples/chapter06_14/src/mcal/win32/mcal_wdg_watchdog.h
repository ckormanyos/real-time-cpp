///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2013.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef MCAL_WDG_WATCHDOG_2013_12_11_H_
  #define MCAL_WDG_WATCHDOG_2013_12_11_H_

  #include <mutex>
  #include <thread>
  #include <mcal_wdg.h>
  #include <util/utility/util_noncopyable.h>
  #include <util/utility/util_time.h>

  namespace mcal
  {
    namespace wdg
    {
      class watchdog;

      class watchdog : private util::noncopyable
      {
      public:
        typedef util::timer<std::uint32_t> timer_type;

        ~watchdog() { }

      private:
        typedef void(*function_type)();

        watchdog(function_type function) : my_timer (my_period),
                                           my_mutex (),
                                           my_thread(function) { }

        static const timer_type::tick_type my_period;

        timer_type  my_timer;
        std::mutex  my_mutex;
        std::thread my_thread;

        static watchdog the_watchdog;

        bool get_watchdog_timeout();
        void reset_watchdog_timer();

        static void the_watchdog_thread_function();

        friend class ::mcal::wdg::secure;
      };
    }
  }

#endif // MCAL_WDG_WATCHDOG_2013_12_11_H_
