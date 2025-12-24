///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2014 - 2024.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef UTIL_STOPWATCH_2014_01_07_H
  #define UTIL_STOPWATCH_2014_01_07_H

  #include <chrono>

  namespace util
  {
    template<typename clock_type>
    class stopwatch final
    {
    public:
      using duration_type = typename clock_type::duration;

      using time_point_type = typename clock_type::time_point;

      stopwatch() : my_start(clock_type::now()) { }

      explicit stopwatch(time_point_type start) : my_start(start) { }

      stopwatch(const stopwatch& other) : my_start(other.my_start) { }

      stopwatch(stopwatch&& other) noexcept : my_start(other.my_start) { }

      ~stopwatch() = default;

      auto operator=(const stopwatch& other) -> stopwatch&
      {
        if(this != &other)
        {
          my_start = other.my_start;
        }

        return *this;
      }

      auto operator=(stopwatch&& other) noexcept -> stopwatch&
      {
        my_start = other.my_start;

        return *this;
      }

      auto elapsed() const -> duration_type
      {
        return clock_type::now() - my_start;
      }

      auto reset() -> void
      {
        my_start = clock_type::now();
      }

    private:
      time_point_type my_start;
    };
  }

  //  util::stopwatch<std::chrono::high_resolution_clock> my_stopwatch;
  //  const auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(my_stopwatch.elapsed()).count();
  //  const auto elapsed = std::chrono::duration_cast<std::chrono::duration<float>>(my_stopwatch.elapsed()).count();

#endif // UTIL_STOPWATCH_2014_01_07_H
