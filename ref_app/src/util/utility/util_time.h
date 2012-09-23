#ifndef _UTIL_TIME_2010_04_10_H_
#define _UTIL_TIME_2010_04_10_H_

  #include <limits>
  #include <mcal_gpt.h>

  namespace util
  {
    template<typename unsigned_tick>
    class timer
    {
    public:
      typedef unsigned_tick tick_type;

      template<typename other> static tick_type microseconds(const other& u) { return u; }
      template<typename other> static tick_type milliseconds(const other& u) { return static_cast<tick_type>(1000UL) * microseconds(u); }
      template<typename other> static tick_type seconds     (const other& u) { return static_cast<tick_type>(1000UL) * milliseconds(u); }
      template<typename other> static tick_type minutes     (const other& u) { return static_cast<tick_type>(60UL) * seconds(u); }
      template<typename other> static tick_type hours       (const other& u) { return static_cast<tick_type>(60UL) * minutes(u); }
      template<typename other> static tick_type days        (const other& u) { return static_cast<tick_type>(24UL) * hours(u); }

      timer() : my_tick(now()) { }
      explicit timer(const tick_type& t) : my_tick(now() + t) { }

      timer(const timer& t) : my_tick(t.my_tick) { }

      timer& operator=(const timer& t)
      {
        my_tick = t.my_tick;
        return *this;
      }

      void start_interval(const tick_type& t)
      {
        my_tick += t;
      }

      void start_relative(const tick_type& t)
      {
        my_tick = now() + t;
      }

      bool timeout() const
      {
        const tick_type timer_mask = (1ULL << (std::numeric_limits<tick_type>::digits - 1)) - 1ULL;
        const tick_type delta = now() - my_tick;
        return (delta <= timer_mask);
      }

      static tick_type now()
      {
        return mcal::gpt::get_time_elapsed();
      }

      static void blocking_delay(const tick_type& delay)
      {
        const timer t_delay(delay);
        while(!t_delay.timeout()) { ; }
      }

    private:
      tick_type my_tick;
    };
  }

#endif // _UTIL_TIME_2010_04_10_H_
