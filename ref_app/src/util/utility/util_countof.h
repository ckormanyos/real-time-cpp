#ifndef _UTIL_COUNTOF_2014_09_29_H_
  #define _UTIL_COUNTOF_2014_09_29_H_

  #include <cstddef>

  namespace util
  {
    #if defined(__GNUC__)

      template <class T, const std::size_t N>
      inline constexpr std::size_t countof(T(&c_array)[N])
      {
        static_assert(N > std::size_t(0U), "Sorry, util::countof requires a non-zero array size.");

        return sizeof(c_array) / sizeof(c_array[0U]);
      }

    #else

      template <class T, const std::size_t N>
      inline std::size_t countof(T(&c_array)[N])
      {
        static_assert(N > std::size_t(0U), "Sorry, util::countof requires a non-zero array size.");

        return sizeof(c_array) / sizeof(c_array[0U]);
      }

    #endif
  }

#endif // _UTIL_COUNTOF_2014_09_29_H_
