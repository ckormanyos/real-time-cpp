#ifndef UTIL_SAFETY_MAX_TIME_OF_PROCESS_2013_12_07_H_
  #define UTIL_SAFETY_MAX_TIME_OF_PROCESS_2013_12_07_H_

  #include <algorithm>
  #include <array>
  #include <cstdint>
  #include <iterator>
  #include <limits>
  #include <util/utility/util_noncopyable.h>
  #include <util/utility/util_time.h>

  namespace util
  {
    namespace safety
    {
      template<typename statistics_range_type,
               const std::size_t statistics_list_count,
               typename timer_tick_type = std::uint32_t>
      class max_time_of_process : public util::safety::max_time_base<statistics_range_type,
                                                                     statistics_list_count,
                                                                     timer_tick_type>
      {
      public:
        typedef std::array<statistics_range_type, statistics_list_count> statistics_range_list_type;

        typedef util::timer<timer_tick_type> timer_type;
        typedef typename timer_type::tick_type tick_type;

        max_time_of_process(const statistics_range_list_type& ranges)
          : statistics_ranges     (ranges),
            statistics_list       (),
            timer_start_of_process(),
            max_usec_of_process   (0U) { }

        virtual ~max_time_of_process() { }

        void start();
        void stop();

      private:
        const statistics_range_list_type& statistics_ranges;
        statistics_range_list_type statistics_list;

        timer_type            timer_start_of_process;
        statistics_range_type max_usec_of_process;
      };
    }
  }

  template<typename statistics_range_type,
           const std::size_t statistics_list_count,
           typename timer_tick_type>
  void util::safety::max_time_of_process<statistics_range_type,
                                         statistics_list_count,
                                         timer_tick_type>::start()
  {
  }

  template<typename statistics_range_type,
           const std::size_t statistics_list_count,
           typename timer_tick_type>
  void util::safety::max_time_of_process<statistics_range_type,
                                         statistics_list_count,
                                         timer_tick_type>::stop()
  {
  }

#endif // UTIL_SAFETY_MAX_TIME_OF_PROCESS_2013_12_07_H_
