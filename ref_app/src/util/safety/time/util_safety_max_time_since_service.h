#ifndef UTIL_SAFETY_MAX_TIME_SINCE_SERVICE_2013_12_06_H_
  #define UTIL_SAFETY_MAX_TIME_SINCE_SERVICE_2013_12_06_H_

  #include <algorithm>
  #include <array>
  #include <iterator>
  #include <limits>
  #include <util/safety/time/util_safety_max_time_base.h>

  namespace util
  {
    namespace safety
    {
      template<typename statistics_range_type,
               const std::size_t statistics_list_count,
               typename timer_tick_type>
      class max_time_since_service : public util::safety::max_time_base<statistics_range_type,
                                                                        statistics_list_count,
                                                                        timer_tick_type>
      {
      public:
        typedef std::array<statistics_range_type, statistics_list_count> statistics_range_list_type;

        typedef util::timer<timer_tick_type> timer_type;
        typedef typename timer_type::tick_type tick_type;

        max_time_since_service(const statistics_range_list_type& ranges);

        virtual ~max_time_since_service() { }

        void service();

        statistics_range_type get_max_usec_since_service() const { return max_usec_since_service; }

      private:
        typedef util::safety::max_time_base<statistics_range_type,
                                            statistics_list_count,
                                            timer_tick_type> max_time_base_type;

        timer_type            timer_last_service;
        statistics_range_type max_usec_since_service;
      };
    }
  }

  template<typename statistics_range_type,
           const std::size_t statistics_list_count,
           typename timer_tick_type>
  util::safety::max_time_since_service<statistics_range_type,
                                       statistics_list_count,
                                       timer_tick_type>::max_time_since_service(const statistics_range_list_type& ranges)
   : max_time_base_type(ranges),
     timer_last_service    (),
     max_usec_since_service(0U)
  {
  }

  template<typename statistics_range_type,
           const std::size_t statistics_list_count,
           typename timer_tick_type>
  void util::safety::max_time_since_service<statistics_range_type,
                                            statistics_list_count,
                                            timer_tick_type>::service()
  {
    // Obtain the number of ticks (in microseconds) since the last service.
    const tick_type this_ticks_since_service = timer_last_service.get_ticks_since_mark();

    // Set a new timer mark for the next service.
    timer_last_service.set_mark();

    // Calculate the time (in microseconds) since the last service.
    const statistics_range_type this_usec_since_service = static_cast<statistics_range_type>(this_ticks_since_service / timer_type::microseconds(tick_type(1U)));

    // Set the maximum time (in microseconds) since the last service.
    max_usec_since_service = (std::max)(this_usec_since_service, max_usec_since_service);

    // Handle the statistics.
    // Find the statistics slot that should be incremented.
    const typename statistics_range_list_type::const_reverse_iterator statistics_slot =
      std::find_if(max_time_base_type::statistics_ranges.rbegin(),
                   max_time_base_type::statistics_ranges.rend(),
                   [&this_usec_since_service](const statistics_range_type& range)
                   {
                     return (this_usec_since_service >= range);
                   });

    // Obtain the index of the appropriate statistics slot.
    // Thereby, ensure that the index remains within bounds.
    const std::uint_least8_t index_distance = static_cast<std::uint_least8_t>(std::distance(statistics_slot, max_time_base_type::statistics_ranges.rend()));

    const std::uint_least8_t index = (std::min)(static_cast<std::uint_least8_t>(max_time_base_type::statistics_list.size() - 1U),
                                                index_distance);

    // Increment the corresponding statistics slot.
    if(max_time_base_type::statistics_list[index] < (std::numeric_limits<typename max_time_base_type::statistics_type>::max)())
    {
      ++max_time_base_type::statistics_list[index];
    }
  }

#endif // UTIL_SAFETY_MAX_TIME_SINCE_SERVICE_2013_12_06_H_
