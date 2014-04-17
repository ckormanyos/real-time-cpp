///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2013.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef _UTIL_BIT_MASK_2010_06_13_H_
  #define _UTIL_BIT_MASK_2010_06_13_H_

  #include <limits>

  namespace util
  {
    template<typename data_type,
             const unsigned bit_pos,
             const unsigned bit_cnt>
    struct bit_mask_multi_bit_value
    {
      // Ensure that the data_type is unsigned.
      static_assert(std::numeric_limits<data_type>::is_signed == false,
                    "the data type of the bit mask template must be unsigned");

      // Ensure that the requested bit mask is in range.
      static_assert((bit_pos + bit_cnt) <= unsigned(std::numeric_limits<data_type>::digits),
                    "the requested bit mask exceeds the bits available in the data type");

      static const data_type value = (data_type(~data_type(0ULL)) >> (std::numeric_limits<data_type>::digits - (bit_cnt + 1U))) << bit_pos;
    };

    template<typename data_type,
             const unsigned bit_pos>
    struct bit_mask_multi_bit_value<data_type, bit_pos, 1U>
    {
      // Ensure that the data_type is unsigned.
      static_assert(std::numeric_limits<data_type>::is_signed == false,
                    "the data type of the bit mask template must be unsigned");

      // Ensure that the requested bit mask is in range.
      static_assert(bit_pos < unsigned(std::numeric_limits<data_type>::digits),
                    "the requested bit mask exceeds the bits available in the data type");

      static const data_type value = static_cast<data_type>(static_cast<data_type>(1U) << bit_pos);
    };

    template<typename data_type,
             const unsigned bit_pos>
    struct bit_mask_single_bit_value
    {
      // Ensure that the data_type is unsigned.
      static_assert(std::numeric_limits<data_type>::is_signed == false,
                    "the data type of the bit value template must be unsigned");

      // Ensure that the requested bit position is in range.
      static_assert(bit_pos < unsigned(std::numeric_limits<data_type>::digits),
                    "the requested bit position exceeds the bits available in the data type");

      static const data_type value = static_cast<data_type>(static_cast<data_type>(1U) << bit_pos);
    };
  }

#endif // _UTIL_BIT_MASK_2010_06_13_H_
