///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2022.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef UTIL_TIME_2010_04_10_H
  #define UTIL_TIME_2010_04_10_H

  #include <cstdint>
  #include <limits>

  #include <mcal_gpt.h>
  #include <mcal_wdg.h>

  namespace util
  {
    template<typename unsigned_tick_type>
    class timer
    {
    private:
      static constexpr auto timer_mask =
        static_cast<unsigned_tick_type>
        (
          (UINTMAX_C(1) << (std::numeric_limits<unsigned_tick_type>::digits - 1)) - UINTMAX_C(1)
        );

    public:
      using tick_type = unsigned_tick_type;

      template<typename other_tick_type> static constexpr auto microseconds(other_tick_type value_microseconds) noexcept -> tick_type { return value_microseconds; }
      template<typename other_tick_type> static constexpr auto milliseconds(other_tick_type value_milliseconds) noexcept -> tick_type { return static_cast<tick_type>(1000UL) * microseconds(value_milliseconds); }
      template<typename other_tick_type> static constexpr auto seconds     (other_tick_type value_seconds)      noexcept -> tick_type { return static_cast<tick_type>(1000UL) * milliseconds(value_seconds     ); }
      template<typename other_tick_type> static constexpr auto minutes     (other_tick_type value_minutes)      noexcept -> tick_type { return static_cast<tick_type>(  60UL) * seconds     (value_minutes     ); }
      template<typename other_tick_type> static constexpr auto hours       (other_tick_type value_hours)        noexcept -> tick_type { return static_cast<tick_type>(  60UL) * minutes     (value_hours       ); }
      template<typename other_tick_type> static constexpr auto days        (other_tick_type value_days)         noexcept -> tick_type { return static_cast<tick_type>(  24UL) * hours       (value_days        ); }
      template<typename other_tick_type> static constexpr auto weeks       (other_tick_type value_weeks)        noexcept -> tick_type { return static_cast<tick_type>(   7UL) * days        (value_weeks       ); }

      constexpr timer() noexcept = default;

      constexpr timer(tick_type tick_value) noexcept : my_tick(my_now() + tick_value) { }

      constexpr timer(const timer& other) noexcept : my_tick(other.my_tick) { }

      constexpr timer(timer&& other) noexcept : my_tick(other.my_tick) { }

      ~timer() noexcept = default;

      auto operator=(const timer& other) noexcept -> timer&
      {
        if(this != &other)
        {
          my_tick = other.my_tick;
        }

        return *this;
      }

      auto operator=(timer&& other) noexcept -> timer&
      {
        my_tick = other.my_tick;

        return *this;
      }

      auto start_interval(const tick_type& tick_value) noexcept -> void
      {
        my_tick += tick_value;
      }

      auto start_relative(const tick_type& tick_value) noexcept -> void
      {
        my_tick = my_now() + tick_value;
      }

      constexpr auto timeout() const noexcept -> bool
      {
        return (static_cast<tick_type>(my_now() - my_tick) <= timer_mask);
      }

      constexpr auto timeout_of_specific_timepoint(const tick_type timepoint) const noexcept -> bool
      {
        return (static_cast<tick_type>(timepoint - my_tick) <= timer_mask);
      }

      auto set_mark() noexcept -> void
      {
        return (my_tick = my_now());
      }

      static constexpr auto get_mark() noexcept -> tick_type
      {
        return my_now();
      }

      constexpr auto get_ticks_since_mark() const noexcept -> tick_type
      {
        return my_now() - my_tick;
      }

      static auto blocking_delay(const tick_type& delay) noexcept -> void
      {
        const timer t_delay(delay);

        while(false == t_delay.timeout())
        {
          mcal::wdg::secure::trigger();
        }
      }

    private:
      tick_type my_tick { };

      constexpr static auto my_now() noexcept -> tick_type
      {
        return static_cast<tick_type>(mcal::gpt::secure::get_time_elapsed());
      }

      static_assert(std::numeric_limits<tick_type>::is_signed == false,
                    "the timer tick_type must be unsigned");

      static_assert(std::numeric_limits<tick_type>::digits <= std::numeric_limits<mcal::gpt::value_type>::digits,
                    "The width of the timer tick_type can not exceed the width of mcal::gpt::value_type");
    };
  }

#endif // UTIL_TIME_2010_04_10_H
