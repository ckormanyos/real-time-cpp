///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2018.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef UTIL_BIT_MASK_2010_06_13_H_
  #define UTIL_BIT_MASK_2010_06_13_H_

  #include <limits>

  namespace util
  {
    template<typename data_type,
             const unsigned bit_pos,
             const unsigned bit_cnt>
    struct bit_mask_multi_value
    {
      // This bit mask contains bit_cnt continuous bits starting at bit_pos.

      // Ensure that the data_type is an integer type.
      static_assert(std::numeric_limits<data_type>::is_integer == true,
                    "the data_type of the bit_mask template must be an integer type");

      // Ensure that the data_type is unsigned.
      static_assert(std::numeric_limits<data_type>::is_signed == false,
                    "the data_type of the bit_mask template must be unsigned");

      // Ensure that the requested bit mask is in range.
      static_assert((bit_pos + bit_cnt) <= unsigned(std::numeric_limits<data_type>::digits),
                    "the requested bit_mask value exceeds the maximum value of the data_type");

      static const data_type value = static_cast<data_type>(static_cast<data_type>(static_cast<data_type>(~static_cast<data_type>(0U)) >> (std::numeric_limits<data_type>::digits - (bit_cnt + 1U))) << bit_pos);
    };

    template<typename data_type,
             const unsigned bit_pos>
    struct bit_mask_multi_value<data_type, bit_pos, 1U>
    {
      // This bit mask contains one bit at bit_pos.

      // Ensure that the data_type is an integer type.
      static_assert(std::numeric_limits<data_type>::is_integer == true,
                    "the data_type of the bit_mask template must be an integer type");

      // Ensure that the data_type is unsigned.
      static_assert(std::numeric_limits<data_type>::is_signed == false,
                    "the data_type of the bit_mask template must be unsigned");

      // Ensure that the requested bit mask is in range.
      static_assert((bit_pos + 1) <= unsigned(std::numeric_limits<data_type>::digits),
                    "the requested bit_mask value exceeds the maximum value of the data_type");

      static const data_type value = static_cast<data_type>(static_cast<data_type>(1U) << bit_pos);
    };

    template<typename data_type,
             const unsigned bit_pos>
    struct bit_mask_single_value
    {
      // This bit mask contains one bit at bit_pos.

      // Ensure that the data_type is an integer type.
      static_assert(std::numeric_limits<data_type>::is_integer == true,
                    "the data_type of the bit_mask template must be an integer type");

      // Ensure that the data_type is unsigned.
      static_assert(std::numeric_limits<data_type>::is_signed == false,
                    "the data_type of the bit_mask template must be unsigned");

      // Ensure that the requested bit mask is in range.
      static_assert((bit_pos + 1) <= unsigned(std::numeric_limits<data_type>::digits),
                    "the requested bit_mask value exceeds the maximum value of the data_type");

      static const data_type value = static_cast<data_type>(static_cast<data_type>(1U) << bit_pos);
    };
  }

#endif // UTIL_BIT_MASK_2010_06_13_H_
