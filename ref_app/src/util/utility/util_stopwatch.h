///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2014.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef UTIL_STOPWATCH_2014_01_07_H_
  #define UTIL_STOPWATCH_2014_01_07_H_

  namespace util
  {
    template<typename clock_type>
    class stopwatch final
    {
    public:
      typedef typename clock_type::duration duration_type;

      stopwatch() : my_start(clock_type::now()) { }

      stopwatch(typename clock_type::time_point start) : my_start(start) { }

      stopwatch(const stopwatch& other) : my_start(other.my_start) { }

      ~stopwatch() { }

      stopwatch& operator=(const stopwatch& other)
      {
        if(this != &other)
        {
          my_start = other.my_start;
        }

        return *this;
      }

      duration_type elapsed() const
      {
        return clock_type::now() - my_start;
      }

      void reset()
      {
        my_start = clock_type::now();
      }

    private:
        typename clock_type::time_point my_start;
    };
  }

  //  util::stopwatch<std::chrono::high_resolution_clock> my_stopwatch;
  //  const auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(my_stopwatch.elapsed()).count();
  //  const auto elapsed = std::chrono::duration_cast<std::chrono::duration<float>>(my_stopwatch.elapsed()).count();

#endif // UTIL_STOPWATCH_2014_01_07_H_
