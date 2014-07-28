///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2013.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef _UTIL_TWO_PART_DATA_MANIPULATION_2010_06_13_H_
  #define _UTIL_TWO_PART_DATA_MANIPULATION_2010_06_13_H_

  #include <limits>

  namespace util
  {
    template<typename long_type,
             typename short_type>
    inline long_type make_long(short_type lo, short_type hi)
    {
      // Ensure that the long_type has exactly twice the digits as the short_type.
      static_assert((std::numeric_limits<short_type>::digits * 2) == std::numeric_limits<long_type>::digits,
                    "the long type of the make_long template must be twice as wide as the short_type");

      // Ensure that both the short_type as well as the long_type are unsigned.
      static_assert(std::numeric_limits<short_type>::is_signed == false,
                    "the short type of the make_long template must be unsigned");

      static_assert(std::numeric_limits< long_type>::is_signed == false,
                    "the long type of the make_long template must be unsigned.");

      return static_cast<long_type>(static_cast<long_type>(static_cast<long_type>(hi) << std::numeric_limits<short_type>::digits) | lo);
    }

    template<typename short_type,
             typename long_type>
    inline short_type lo_part(long_type val)
    {
      // Ensure that the long_type has exactly twice the digits as the short_type.
      static_assert((std::numeric_limits<short_type>::digits * 2) == std::numeric_limits<long_type>::digits,
                    "the long type of the lo_part template must be twice as wide as the short_type");

      // Ensure that both the short_type as well as the long_type are unsigned.
      static_assert(std::numeric_limits<short_type>::is_signed == false,
                    "the short type of the lo_part template must be unsigned");

      static_assert(std::numeric_limits<long_type>::is_signed == false,
                    "the long type of the lo_part template must be unsigned");

      return static_cast<short_type>(val);
    }

    template<typename short_type,
             typename long_type>
    inline short_type hi_part(long_type val)
    {
      // Ensure that the long_type has exactly twice the digits as the short_type.
      static_assert((std::numeric_limits<short_type>::digits * 2) == std::numeric_limits<long_type>::digits,
                    "the long type of the hi_part template must be twice as wide as the short_type");

      // Ensure that both the short_type as well as the long_type are unsigned.
      static_assert(std::numeric_limits<short_type>::is_signed == false,
                    "the short type of the hi_part template must be unsigned");

      static_assert(std::numeric_limits<long_type>::is_signed == false,
                    "the long type of the hi_part template must be unsigned");

      return static_cast<short_type>(val >> std::numeric_limits<short_type>::digits);
    }
  }

#endif // _UTIL_TWO_PART_DATA_MANIPULATION_2010_06_13_H_
