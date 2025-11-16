///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2025.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef UTIL_NOTHING_2010_06_13_H
  #define UTIL_NOTHING_2010_06_13_H

  namespace util
  {
    // This is a structure that is used to represent *nothing*.
    struct nothing final
    {
      constexpr nothing() = default;

      constexpr nothing(const nothing&) { }
      constexpr nothing(nothing&&) { }

      ~nothing() = default;

      constexpr auto operator=(const nothing&) -> nothing& { return *this; }
      constexpr auto operator=(nothing&&) -> nothing& { return *this; }
    };

    inline constexpr auto operator==(const nothing&, const nothing&) -> bool { return true; }
    inline constexpr auto operator!=(const nothing&, const nothing&) -> bool { return false; }
    inline constexpr auto operator< (const nothing&, const nothing&) -> bool { return false; }
    inline constexpr auto operator<=(const nothing&, const nothing&) -> bool { return false; }
    inline constexpr auto operator> (const nothing&, const nothing&) -> bool { return false; }
    inline constexpr auto operator>=(const nothing&, const nothing&) -> bool { return false; }
  }

#endif // UTIL_NOTHING_2010_06_13_H
