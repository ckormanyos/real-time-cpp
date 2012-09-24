#ifndef _UTIL_TIME_2010_04_10_H_
#define _UTIL_TIME_2010_04_10_H_

  #include <limits>

  #include <mcal_gpt.h>
  #include <util/utility/util_bit_mask.h>

  namespace util
  {
    template<typename T>
    class timer
    {
    public:
      typedef T tick_type;

      template<typename UT> static tick_type millisecond(const UT& ut) { return mcal::gpt::my_msec(ut); }
      template<typename UT> static tick_type second     (const UT& ut) { return static_cast<tick_type>(static_cast<tick_type>(1000UL) * millisecond(ut)); }
      template<typename UT> static tick_type minute     (const UT& ut) { return static_cast<tick_type>(static_cast<tick_type>(  60UL) * second(ut)); }
      template<typename UT> static tick_type hour       (const UT& ut) { return static_cast<tick_type>(static_cast<tick_type>(  60UL) * minute(ut)); }
      template<typename UT> static tick_type day        (const UT& ut) { return static_cast<tick_type>(static_cast<tick_type>(  24UL) * hour(ut)); }

      timer() : my_tick(get_tick()) { }
      explicit timer(const tick_type& t) : my_tick(get_tick() + t) { }

      timer(const timer& t) : my_tick(t.my_tick) { }

      timer& operator=(const timer& t)
      {
        my_tick = t.my_tick;
        return *this;
      }

      void start_interval(const tick_type& t) { my_tick += t; }
      void start_relative(const tick_type& t) { my_tick = get_tick() + t; }

      bool timeout(void) const
      {
        constexpr tick_type timer_mask = (1UL << (std::numeric_limits<tick_type>::digits - 1)) - 1UL;
        const tick_type delta = get_tick() - my_tick;
        return (delta <= timer_mask);
      }

      static void blocking_delay(const tick_type& delay)
      {
        const timer t_delay(delay);
        while(!t_delay.timeout()) { ; }
      }

    private:
      tick_type my_tick;

      static tick_type get_tick(void)
      {
        return static_cast<tick_type>(mcal::gpt::get_time_elapsed());
      }
    };
  }

#endif // _UTIL_TIME_2010_04_10_H_
