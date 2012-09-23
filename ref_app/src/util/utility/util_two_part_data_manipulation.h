#ifndef _UTIL_TWO_PART_DATA_MANIPULATION_2010_06_13_H_
  #define _UTIL_TWO_PART_DATA_MANIPULATION_2010_06_13_H_

  #include <limits>

  namespace util
  {
    template<typename short_type,
             typename long_type>
    inline long_type make_long(const short_type& lo, const short_type& hi)
    {
      // Ensure that the long_type has exactly twice the digits as the short_type.
      static_assert((std::numeric_limits<short_type>::digits * 2) == std::numeric_limits<long_type>::digits, "error: The width of long_type must be twice that of short_type.");

      // Ensure that both the short_type as well as the long_type are unsigned.
      static_assert(std::numeric_limits<short_type>::is_signed == false, "error: The short_type must be unsigned.");
      static_assert(std::numeric_limits< long_type>::is_signed == false, "error: The long_type  must be unsigned.");

      const long_type val = static_cast<long_type>(static_cast<long_type>(hi) << std::numeric_limits<short_type>::digits);
      return static_cast<long_type>(val | lo);
    }

    template<typename short_type,
             typename long_type>
    inline short_type lo_part(const long_type& val)
    {
      // Ensure that the long_type has exactly twice the digits as the short_type.
      static_assert((std::numeric_limits<short_type>::digits * 2) == std::numeric_limits<long_type>::digits, "error: The width of long_type must be twice that of short_type.");

      // Ensure that both the short_type as well as the long_type are unsigned.
      static_assert(std::numeric_limits<short_type>::is_signed == false, "error: The short_type must be unsigned.");
      static_assert(std::numeric_limits< long_type>::is_signed == false, "error: The long_type  must be unsigned.");

      return static_cast<short_type>(val);
    }

    template<typename short_type,
             typename long_type>
    inline short_type hi_part(const long_type& val)
    {
      // Ensure that the long_type has exactly twice the digits as the short_type.
      static_assert((std::numeric_limits<short_type>::digits * 2) == std::numeric_limits<long_type>::digits, "error: The width of long_type must be twice that of short_type.");

      // Ensure that both the short_type as well as the long_type are unsigned.
      static_assert(std::numeric_limits<short_type>::is_signed == false, "error: The short_type must be unsigned.");
      static_assert(std::numeric_limits< long_type>::is_signed == false, "error: The long_type  must be unsigned.");

      return static_cast<short_type>(val >> std::numeric_limits<short_type>::digits);
    }
  }

#endif // _UTIL_TWO_PART_DATA_MANIPULATION_2010_06_13_H_
