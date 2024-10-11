///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2024.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef UTIL_TIME_2010_04_10_H
  #define UTIL_TIME_2010_04_10_H

  #include <mcal_gpt.h>
  #include <mcal_wdg.h>

  #include <cstdint>
  #include <limits>

  namespace util
  {
    template<typename unsigned_tick_type>
    class timer
    {
    private:
      static constexpr auto timer_mask =
        static_cast<unsigned_tick_type>
        (
          (UINTMAX_C(1) << static_cast<unsigned>(std::numeric_limits<unsigned_tick_type>::digits - 1)) - UINTMAX_C(1)
        );

    public:
      using tick_type = unsigned_tick_type;

      template<typename other_tick_type> static constexpr auto microseconds(other_tick_type value_microseconds) noexcept -> tick_type { return static_cast<tick_type>(value_microseconds); }
      template<typename other_tick_type> static constexpr auto milliseconds(other_tick_type value_milliseconds) noexcept -> tick_type { return static_cast<tick_type>(UINT16_C(1000)) * microseconds(value_milliseconds); }
      template<typename other_tick_type> static constexpr auto seconds     (other_tick_type value_seconds)      noexcept -> tick_type { return static_cast<tick_type>(UINT16_C(1000)) * milliseconds(value_seconds     ); }
      template<typename other_tick_type> static constexpr auto minutes     (other_tick_type value_minutes)      noexcept -> tick_type { return static_cast<tick_type>(UINT16_C(  60)) * seconds     (value_minutes     ); }
      template<typename other_tick_type> static constexpr auto hours       (other_tick_type value_hours)        noexcept -> tick_type { return static_cast<tick_type>(UINT16_C(  60)) * minutes     (value_hours       ); }
      template<typename other_tick_type> static constexpr auto days        (other_tick_type value_days)         noexcept -> tick_type { return static_cast<tick_type>(UINT16_C(  24)) * hours       (value_days        ); }
      template<typename other_tick_type> static constexpr auto weeks       (other_tick_type value_weeks)        noexcept -> tick_type { return static_cast<tick_type>(UINT16_C(   7)) * days        (value_weeks       ); }

      constexpr timer() = default;

      explicit constexpr timer(tick_type tick_value) : my_tick(my_now() + tick_value) { }

      constexpr timer(const timer& other) = default;

      constexpr timer(timer&& other) noexcept  = default;

      ~timer() = default;

      auto operator=(const timer& other) -> timer& = default;

      auto operator=(timer&& other) noexcept -> timer& = default;

      auto start_interval(const tick_type& tick_value) -> void
      {
        my_tick += tick_value;
      }

      auto start_relative(const tick_type& tick_value) -> void
      {
        my_tick = my_now() + tick_value;
      }

      constexpr auto timeout() const -> bool
      {
        return (static_cast<tick_type>(my_now() - my_tick) <= timer_mask);
      }

      constexpr auto timeout_of_specific_timepoint(const tick_type timepoint) const -> bool
      {
        return (static_cast<tick_type>(timepoint - my_tick) <= timer_mask);
      }

      auto set_mark() -> void
      {
        return (my_tick = my_now());
      }

      static constexpr auto get_mark() -> tick_type
      {
        return my_now();
      }

      constexpr auto get_ticks_since_mark() const -> tick_type
      {
        return my_now() - my_tick;
      }

      static auto blocking_delay(const tick_type& delay) -> void
      {
        const timer t_delay(delay);

        while(!t_delay.timeout()) // NOLINT(altera-id-dependent-backward-branch)
        {
          mcal::wdg::secure::trigger();
        }
      }

    private:
      tick_type my_tick { my_now() };

      constexpr static auto my_now() -> tick_type
      {
        return static_cast<tick_type>(mcal::gpt::secure::get_time_elapsed());
      }

      static_assert((!std::numeric_limits<tick_type>::is_signed),
                    "the timer tick_type must be unsigned");

      static_assert(std::numeric_limits<tick_type>::digits <= std::numeric_limits<mcal::gpt::value_type>::digits,
                    "The width of the timer tick_type can not exceed the width of mcal::gpt::value_type");
    };
  } // namespace util

#endif // UTIL_TIME_2010_04_10_H
