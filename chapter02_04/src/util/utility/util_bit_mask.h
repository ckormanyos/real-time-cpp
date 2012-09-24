#ifndef _UTIL_BIT_MASK_2010_06_13_H_
  #define _UTIL_BIT_MASK_2010_06_13_H_

  #include <limits>

  namespace util
  {
    template<typename data_type,
             const int bit_pos,
             const int bit_cnt>
    class bit_mask
    {
    public:
      // Ensure that the data_type is unsigned.
      static_assert(std::numeric_limits<data_type>::is_signed == false, "error: The data_type must be unsigned.");

      static constexpr data_type value = static_cast<data_type>(static_cast<data_type>(data_type(-1) >> (std::numeric_limits<data_type>::digits - bit_cnt)) << bit_pos);
    };

    template<typename data_type,
             const int bit_pos>
    class bit_value
    {
    public:
      // Ensure that the data_type is unsigned.
      static_assert(std::numeric_limits<data_type>::is_signed == false, "error: The data_type must be unsigned.");

      static constexpr data_type value = static_cast<data_type>(static_cast<data_type>(1ULL) << bit_pos);
    };
  }

#endif // _UTIL_BIT_MASK_2010_06_13_H_
