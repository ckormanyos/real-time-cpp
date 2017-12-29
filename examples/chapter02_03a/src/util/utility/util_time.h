///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2014.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef UTIL_TIME_2010_04_10_H_
  #define UTIL_TIME_2010_04_10_H_

  #include <cstdint>
  #include <limits>

  #include <mcal_cpu.h>
  #include <mcal_gpt.h>

  namespace util
  {
    template<typename unsigned_tick_type>
    class timer
    {
    public:
      typedef unsigned_tick_type tick_type;

      static_assert(std::numeric_limits<tick_type>::is_signed == false,
                    "the timer tick_type must be unsigned");

      static_assert(std::numeric_limits<tick_type>::digits <= std::numeric_limits<mcal::gpt::value_type>::digits,
                    "The width of the timer tick_type can not exceed the width of mcal::gpt::value_type");

    private:
      static const tick_type timer_mask = static_cast<tick_type>((UINTMAX_C(1) << (std::numeric_limits<tick_type>::digits - 1)) - UINTMAX_C(1));

    public:
      template<typename other_tick_type> static tick_type microseconds(const other_tick_type& value_microseconds) { return static_cast<tick_type>(value_microseconds); }
      template<typename other_tick_type> static tick_type milliseconds(const other_tick_type& value_milliseconds) { return static_cast<tick_type>(1000UL) * microseconds(value_milliseconds); }
      template<typename other_tick_type> static tick_type seconds     (const other_tick_type& value_seconds     ) { return static_cast<tick_type>(1000UL) * milliseconds(value_seconds     ); }
      template<typename other_tick_type> static tick_type minutes     (const other_tick_type& value_minutes     ) { return static_cast<tick_type>(  60UL) * seconds     (value_minutes     ); }
      template<typename other_tick_type> static tick_type hours       (const other_tick_type& value_hours       ) { return static_cast<tick_type>(  60UL) * minutes     (value_hours       ); }
      template<typename other_tick_type> static tick_type days        (const other_tick_type& value_days        ) { return static_cast<tick_type>(  24UL) * hours       (value_days        ); }
      template<typename other_tick_type> static tick_type weeks       (const other_tick_type& value_weeks       ) { return static_cast<tick_type>(   7UL) * days        (value_weeks       ); }

      timer() : my_tick(0U) { }

      timer(const tick_type& tick_value) : my_tick(my_now() + tick_value) { }

      timer(const timer& other) : my_tick(other.my_tick) { }

      timer& operator=(const timer& other)
      {
        if(this != &other)
        {
          my_tick = other.my_tick;
        }

        return *this;
      }

      void start_interval(const tick_type& tick_value)
      {
        my_tick += tick_value;
      }

      void start_relative(const tick_type& tick_value)
      {
        my_tick = my_now() + tick_value;
      }

      bool timeout() const
      {
        const tick_type delta = my_now() - my_tick;

        return (delta <= timer_mask);
      }

      bool timeout_of_specific_timepoint(const tick_type timepoint) const
      {
        const tick_type delta = timepoint - my_tick;

        return (delta <= timer_mask);
      }

      void set_mark()
      {
        my_tick = my_now();

        return my_tick;
      }

      static tick_type get_mark()
      {
        return my_now();
      }

      tick_type get_ticks_since_mark() const
      {
        return my_now() - my_tick;
      }

      static void blocking_delay(const tick_type& delay)
      {
        const timer t_delay(delay);

        while(false == t_delay.timeout())
        {
          mcal::cpu::nop();
        }
      }

    private:
      tick_type my_tick;

      static tick_type my_now() { return static_cast<tick_type>(mcal::gpt::secure::get_time_elapsed()); }
    };
  }

#endif // UTIL_TIME_2010_04_10_H_
