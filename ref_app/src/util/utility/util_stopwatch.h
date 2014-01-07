///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2014.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef _UTIL_STOPWATCH_2014_01_07_H_
  #define _UTIL_STOPWATCH_2014_01_07_H_

  #include <util/utility/util_noncopyable.h>

  namespace util
  {
    template<typename clock_type>
    class stopwatch : private util::noncopyable
    {
    public:
      typedef typename clock_type::duration duration_type;

      stopwatch() : my_start(clock_type::now()) { }

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

#endif // _UTIL_STOPWATCH_2014_01_07_H_
