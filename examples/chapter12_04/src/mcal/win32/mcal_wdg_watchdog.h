///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2013 - 2023.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef MCAL_WDG_WATCHDOG_2013_12_11_H
  #define MCAL_WDG_WATCHDOG_2013_12_11_H

  #include <mcal_wdg.h>

  #include <util/utility/util_noncopyable.h>
  #include <util/utility/util_time.h>

  #include <atomic>
  #include <cstdint>
  #include <functional>
  #include <thread>

  #if defined(_MSC_VER)
  #define  MCAL_WDG_NORETURN
  #else
  #define  MCAL_WDG_NORETURN [[noreturn]]
  #endif

  namespace mcal
  {
    namespace wdg
    {
      auto print_timeout_message() -> void;

      class watchdog_base : private util::noncopyable
      {
      public:
        using base_timer_type = util::timer<std::uint32_t>;

        watchdog_base() noexcept = default;
        watchdog_base(const watchdog_base&) = delete;
        watchdog_base(watchdog_base&&) = delete;

        auto operator=(const watchdog_base&) -> watchdog_base& = delete;
        auto operator=(watchdog_base&&) -> watchdog_base& = delete;

        virtual ~watchdog_base() noexcept = default;
      };

      template<const typename watchdog_base::base_timer_type::tick_type MyPeriod>
      class watchdog : public watchdog_base
      {
      public:
        using timer_type = watchdog_base::base_timer_type;

        watchdog() noexcept = delete;
        watchdog(const watchdog&) = delete;
        watchdog(watchdog&&) = delete;

        auto operator=(const watchdog&) -> watchdog& = delete;
        auto operator=(watchdog&&) -> watchdog& = delete;

        ~watchdog() noexcept override = default;

      private:
        using function_type = std::function<void()>;

        explicit watchdog(const function_type& pf) : my_thread(pf) { }

        static constexpr timer_type::tick_type my_period = MyPeriod;

        timer_type  my_timer { my_period };
        const std::thread my_thread;

        static watchdog         my_watchdog; // NOLINT(cppcoreguidelines-avoid-non-const-global-variables)
        static std::atomic_flag my_lock;     // NOLINT(cppcoreguidelines-avoid-non-const-global-variables)

        auto get_watchdog_timeout() const -> bool
        {
          while(my_lock.test_and_set()) { ; }
          const auto timeout_result = my_timer.timeout();
          my_lock.clear();

          return timeout_result;
        }

        auto reset_watchdog_timer() -> void
        {
          while(my_lock.test_and_set()) { ; }
          my_timer.start_relative(my_period);
          my_lock.clear();
        }

        MCAL_WDG_NORETURN static auto thread_function() -> void
        {
          std::this_thread::sleep_for(std::chrono::milliseconds(static_cast<unsigned>(UINT8_C(10))));

          bool timeout_has_occurred = false;

          for(;;)
          {
            if(timeout_has_occurred)
            {
              print_timeout_message();

              std::this_thread::sleep_for(std::chrono::milliseconds(static_cast<unsigned>(UINT16_C(500))));
            }
            else
            {
              if(watchdog::my_watchdog.get_watchdog_timeout())
              {
                timeout_has_occurred = true;
              }

              std::this_thread::sleep_for(std::chrono::milliseconds(static_cast<unsigned>(UINT8_C(20))));
            }
          }
        }

        friend struct ::mcal::wdg::secure;
      };

      template<const typename watchdog_base::base_timer_type::tick_type MyPeriod>
      watchdog<MyPeriod> watchdog<MyPeriod>::my_watchdog(thread_function); // NOLINT(cppcoreguidelines-avoid-non-const-global-variables,cert-err58-cpp)

      template<const typename watchdog_base::base_timer_type::tick_type MyPeriod>
      std::atomic_flag watchdog<MyPeriod>::my_lock = ATOMIC_FLAG_INIT; // NOLINT(cppcoreguidelines-avoid-non-const-global-variables)
    } // namespace wdg
  } // namespace mcal

#endif // MCAL_WDG_WATCHDOG_2013_12_11_H
