#ifndef UTIL_SAFETY_MAX_TIME_BASE_2013_12_07_H_
  #define UTIL_SAFETY_MAX_TIME_BASE_2013_12_07_H_

  #include <cstdint>

  #include <util/utility/util_noncopyable.h>
  #include <util/utility/util_time.h>

  namespace util
  {
    namespace safety
    {
      template<typename statistics_range_type,
               const std::size_t statistics_list_count,
               typename timer_tick_type>
      class max_time_base : private util::noncopyable
      {
      public:
        typedef std::uint_least8_t statistics_type;
        typedef std::array<statistics_type, statistics_list_count> statistics_list_type;

        typedef std::array<statistics_range_type, statistics_list_count> statistics_range_list_type;

        typedef util::timer<timer_tick_type> timer_type;
        typedef typename timer_type::tick_type tick_type;

        virtual ~max_time_base() { }

      protected:
        const statistics_range_list_type& statistics_ranges;
        statistics_range_list_type statistics_list;

        max_time_base(const statistics_range_list_type& ranges)
          : statistics_ranges(ranges),
            statistics_list  () { }
      };
    }
  }

#endif // UTIL_SAFETY_MAX_TIME_BASE_2013_12_07_H_
