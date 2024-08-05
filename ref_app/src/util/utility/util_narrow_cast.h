///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2020.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef UTIL_NARROW_CAST_2020_09_24_H
  #define UTIL_NARROW_CAST_2020_09_24_H

  #include <utility>

  namespace util
  {
    template <class T, class U>
    constexpr auto narrow_cast(U&& u) noexcept -> T
    {
      return static_cast<T>(std::forward<U>(u));
    }
  }

#endif // UTIL_NARROW_CAST_2020_09_24_H
