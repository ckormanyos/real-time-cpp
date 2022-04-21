///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2013 - 2022.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef MCAL_WDG_WATCHDOG_2013_12_11_H
  #define MCAL_WDG_WATCHDOG_2013_12_11_H

  #include <cstdint>
  #include <functional>
  #include <thread>

  #include <mcal_wdg.h>
  #include <util/utility/util_noncopyable.h>
  #include <util/utility/util_time.h>

  #if defined(_MSC_VER)
  #define  MCAL_WDG_NORETURN
  #else
  #define  MCAL_WDG_NORETURN [[noreturn]]
  #endif

  namespace mcal
  {
    namespace wdg
    {
      class watchdog;

      class watchdog : private util::noncopyable
      {
      public:
        using timer_type = util::timer<std::uint32_t>;

        watchdog() noexcept = delete;
        watchdog(const watchdog&) = delete;
        watchdog(watchdog&&) = delete;

        auto operator=(const watchdog&) -> watchdog& = delete;
        auto operator=(watchdog&&) -> watchdog& = delete;

        ~watchdog() noexcept = default;

      private:
        using function_type = std::function<void()>;

        explicit watchdog(const function_type& pf) : my_thread(pf) { }

        static constexpr timer_type::tick_type my_period = timer_type::seconds(2U);

        timer_type  my_timer { my_period };
        std::thread my_thread;

        static watchdog& the_watchdog();

        auto get_watchdog_timeout() -> bool;
        auto reset_watchdog_timer() -> void;

        MCAL_WDG_NORETURN static auto the_watchdog_thread_function() -> void;

        friend class ::mcal::wdg::secure;
      };
    }
  }

#endif // MCAL_WDG_WATCHDOG_2013_12_11_H
