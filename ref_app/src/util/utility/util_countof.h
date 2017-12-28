///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2014.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef UTIL_COUNTOF_2014_09_29_H_
  #define UTIL_COUNTOF_2014_09_29_H_

  #include <cstddef>

  namespace util
  {
    #if defined(__GNUC__)

      template<typename T, const std::size_t N>
      inline constexpr std::size_t countof(T(&c_array)[N])
      {
        static_assert(N > std::size_t(0U),
                      "Sorry, util::countof requires an array size larger than zero.");

        static_assert(sizeof(c_array[0U]) > std::size_t(0U),
                      "Sorry, util::countof requires an element size larger than zero.");

        return sizeof(c_array) / sizeof(c_array[0U]);
      }

    #else

      template<typename T, const std::size_t N>
      inline std::size_t countof(T(&c_array)[N])
      {
        static_assert(N > std::size_t(0U),
                      "Sorry, util::countof requires an array size larger than zero.");

        static_assert(sizeof(c_array[0U]) > std::size_t(0U),
                      "Sorry, util::countof requires an element size larger than zero.");

        return sizeof(c_array) / sizeof(c_array[0U]);
      }

    #endif
  }

#endif // UTIL_COUNTOF_2014_09_29_H_
