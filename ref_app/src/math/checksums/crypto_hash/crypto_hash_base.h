///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2013.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef _CRYPTO_HASH_BASE_2013_09_05_H_
  #define _CRYPTO_HASH_BASE_2013_09_05_H_

  #include <algorithm>
  #include <cstdint>
  #include <limits>

  class crypto_hash_base
  {
  public:
    virtual ~crypto_hash_base() { }

  protected:
    bool                the_result_is_finalized;
    std::uint_least8_t  message_block_index;

    crypto_hash_base();

    crypto_hash_base(const crypto_hash_base& other);

    crypto_hash_base& operator=(const crypto_hash_base& other);

    template<const std::uint_fast8_t digits_shift,
             typename arithmetic_type>
    static arithmetic_type circular_right_shift(const arithmetic_type& the_value)
    {
      const std::uint_fast8_t left_shift_amount = static_cast<std::uint_fast8_t>(std::numeric_limits<arithmetic_type>::digits - digits_shift);

      const arithmetic_type part1 = arithmetic_type(arithmetic_type(the_value) >> (digits_shift));
      const arithmetic_type part2 = arithmetic_type(arithmetic_type(the_value) << left_shift_amount);

      return arithmetic_type(part1 | part2);
    }

    template<const std::uint_fast8_t digits_shift,
             typename arithmetic_type>
    static arithmetic_type circular_left_shift(const arithmetic_type& the_value)
    {
      const std::uint_fast8_t right_shift_amount = static_cast<std::uint_fast8_t>(std::numeric_limits<arithmetic_type>::digits - digits_shift);

      const arithmetic_type part1 = arithmetic_type(arithmetic_type(the_value) << (digits_shift));
      const arithmetic_type part2 = arithmetic_type(arithmetic_type(the_value) >> right_shift_amount);

      return arithmetic_type(part1 | part2);
    }

    static void convert_uint8_input_to_uint32_output        (const std::uint8_t*  in_begin, const std::uint8_t*  in_end, std::uint32_t* out_begin);
    static void convert_uint8_input_to_uint32_output_reverse(const std::uint8_t*  in_begin, const std::uint8_t*  in_end, std::uint32_t* out_begin);
    static void convert_uint32_input_to_uint8_output        (const std::uint32_t* in_begin, const std::uint32_t* in_end, std::uint8_t*  out_begin);
    static void convert_uint32_input_to_uint8_output_reverse(const std::uint32_t* in_begin, const std::uint32_t* in_end, std::uint8_t*  out_begin);

    static void convert_uint8_input_to_uint64_output        (const std::uint8_t*  in_begin, const std::uint8_t*  in_end, std::uint64_t* out_begin);
    static void convert_uint8_input_to_uint64_output_reverse(const std::uint8_t*  in_begin, const std::uint8_t*  in_end, std::uint64_t* out_begin);
    static void convert_uint64_input_to_uint8_output        (const std::uint64_t* in_begin, const std::uint64_t* in_end, std::uint8_t*  out_begin);
    static void convert_uint64_input_to_uint8_output_reverse(const std::uint64_t* in_begin, const std::uint64_t* in_end, std::uint8_t*  out_begin);

    static void convert_uint8_input_to_char8_output (const std::uint8_t*  in_begin, const std::uint8_t*  in_end, char*          out_begin);

  private:
    static char convert_nibble4_to_char(const std::uint8_t& the_nibble, const bool use_uppercase);
  };

  crypto_hash_base::crypto_hash_base() : the_result_is_finalized(true),
                                         message_block_index    (0U) { }

  crypto_hash_base::crypto_hash_base(const crypto_hash_base& other) : the_result_is_finalized(other.the_result_is_finalized),
                                                                      message_block_index    (other.message_block_index) { }

  crypto_hash_base& crypto_hash_base::operator=(const crypto_hash_base& other)
  {
    the_result_is_finalized = other.the_result_is_finalized;
    message_block_index     = other.message_block_index;

    return *this;
  }

  void crypto_hash_base::convert_uint8_input_to_uint32_output(const std::uint8_t* in_begin, const std::uint8_t* in_end, std::uint32_t* out_begin)
  {
    // Decodes the input (std::uint8_t) into the output (std::uint32_t).
    // This assumes that the length of the input is a multiple of 4.

    std::uint_least8_t j = static_cast<std::uint_least8_t>(0U);

    std::for_each(out_begin,
                  out_begin + std::uint_least8_t(in_end - in_begin) / 4U,
                  [&j, &in_begin](std::uint32_t& out_value)
                  {
                    out_value =  std::uint32_t(  static_cast<std::uint32_t>(static_cast<std::uint32_t>(in_begin[j + 0U]) <<  0U)
                                               | static_cast<std::uint32_t>(static_cast<std::uint32_t>(in_begin[j + 1U]) <<  8U)
                                               | static_cast<std::uint32_t>(static_cast<std::uint32_t>(in_begin[j + 2U]) << 16U)
                                               | static_cast<std::uint32_t>(static_cast<std::uint32_t>(in_begin[j + 3U]) << 24U));

                    j += 4U;
                  });
  }

  void crypto_hash_base::convert_uint8_input_to_uint32_output_reverse(const std::uint8_t* in_begin, const std::uint8_t* in_end, std::uint32_t* out_begin)
  {
    // Decodes the input (std::uint8_t) into the output (std::uint32_t).
    // This assumes that the length of the input is a multiple of 4.

    std::uint_least8_t j = static_cast<std::uint_least8_t>(0U);

    std::for_each(out_begin,
                  out_begin + std::uint_least8_t(in_end - in_begin) / 4U,
                  [&j, &in_begin](std::uint32_t& out_value)
                  {
                    out_value =  std::uint32_t(  static_cast<std::uint32_t>(static_cast<std::uint32_t>(in_begin[j + 3U]) <<  0U)
                                               | static_cast<std::uint32_t>(static_cast<std::uint32_t>(in_begin[j + 2U]) <<  8U)
                                               | static_cast<std::uint32_t>(static_cast<std::uint32_t>(in_begin[j + 1U]) << 16U)
                                               | static_cast<std::uint32_t>(static_cast<std::uint32_t>(in_begin[j + 0U]) << 24U));

                    j += 4U;
                  });
  }

  void crypto_hash_base::convert_uint32_input_to_uint8_output(const std::uint32_t* in_begin, const std::uint32_t* in_end, std::uint8_t* out_begin)
  {
    // Encodes the input (std::uint32_t) into the output (std::uint8_t).
    // This assumes that the length of the output is a multiple of 4.

    std::uint_least8_t j = static_cast<std::uint_least8_t>(0U);

    std::for_each(in_begin,
                  in_end,
                  [&j, &out_begin](const std::uint32_t& in_value)
                  {
                    out_begin[j + 0U] = static_cast<std::uint8_t>(in_value >>  0U);
                    out_begin[j + 1U] = static_cast<std::uint8_t>(in_value >>  8U);
                    out_begin[j + 2U] = static_cast<std::uint8_t>(in_value >> 16U);
                    out_begin[j + 3U] = static_cast<std::uint8_t>(in_value >> 24U);

                    j += 4U;
                  });
  }

    void crypto_hash_base::convert_uint32_input_to_uint8_output_reverse(const std::uint32_t* in_begin, const std::uint32_t* in_end, std::uint8_t* out_begin)
  {
    // Encodes the input (std::uint32_t) into the output (std::uint8_t).
    // This assumes that the length of the output is a multiple of 4.

    std::uint_least8_t j = static_cast<std::uint_least8_t>(0U);

    std::for_each(in_begin,
                  in_end,
                  [&j, &out_begin](const std::uint32_t& in_value)
                  {
                    out_begin[j + 3U] = static_cast<std::uint8_t>(in_value >>  0U);
                    out_begin[j + 2U] = static_cast<std::uint8_t>(in_value >>  8U);
                    out_begin[j + 1U] = static_cast<std::uint8_t>(in_value >> 16U);
                    out_begin[j + 0U] = static_cast<std::uint8_t>(in_value >> 24U);

                    j += 4U;
                  });
  }


  void crypto_hash_base::convert_uint8_input_to_uint64_output(const std::uint8_t* in_begin, const std::uint8_t* in_end, std::uint64_t* out_begin)
  {
    // Decodes the input (std::uint8_t) into the output (std::uint64_t).
    // This assumes that the length of the input is a multiple of 8.

    std::uint_least8_t j = static_cast<std::uint_least8_t>(0U);

    std::for_each(out_begin,
                  out_begin + std::uint_least8_t(in_end - in_begin) / 8U,
                  [&j, &in_begin](std::uint64_t& out_value)
                  {
                    out_value =  std::uint64_t(  static_cast<std::uint64_t>(static_cast<std::uint64_t>(in_begin[j + 0U]) <<  0U)
                                               | static_cast<std::uint64_t>(static_cast<std::uint64_t>(in_begin[j + 1U]) <<  8U)
                                               | static_cast<std::uint64_t>(static_cast<std::uint64_t>(in_begin[j + 2U]) << 16U)
                                               | static_cast<std::uint64_t>(static_cast<std::uint64_t>(in_begin[j + 3U]) << 24U)
                                               | static_cast<std::uint64_t>(static_cast<std::uint64_t>(in_begin[j + 4U]) << 32U)
                                               | static_cast<std::uint64_t>(static_cast<std::uint64_t>(in_begin[j + 5U]) << 40U)
                                               | static_cast<std::uint64_t>(static_cast<std::uint64_t>(in_begin[j + 6U]) << 48U)
                                               | static_cast<std::uint64_t>(static_cast<std::uint64_t>(in_begin[j + 7U]) << 56U));

                    j += 8U;
                  });
  }

  void crypto_hash_base::convert_uint8_input_to_uint64_output_reverse(const std::uint8_t* in_begin, const std::uint8_t* in_end, std::uint64_t* out_begin)
  {
    // Decodes the input (std::uint8_t) into the output (std::uint64_t).
    // This assumes that the length of the input is a multiple of 8.

    std::uint_least8_t j = static_cast<std::uint_least8_t>(0U);

    std::for_each(out_begin,
                  out_begin + std::uint_least8_t(in_end - in_begin) / 8U,
                  [&j, &in_begin](std::uint64_t& out_value)
                  {
                    out_value =  std::uint64_t(  static_cast<std::uint64_t>(static_cast<std::uint64_t>(in_begin[j + 7U]) <<  0U)
                                               | static_cast<std::uint64_t>(static_cast<std::uint64_t>(in_begin[j + 6U]) <<  8U)
                                               | static_cast<std::uint64_t>(static_cast<std::uint64_t>(in_begin[j + 5U]) << 16U)
                                               | static_cast<std::uint64_t>(static_cast<std::uint64_t>(in_begin[j + 4U]) << 24U)
                                               | static_cast<std::uint64_t>(static_cast<std::uint64_t>(in_begin[j + 3U]) << 32U)
                                               | static_cast<std::uint64_t>(static_cast<std::uint64_t>(in_begin[j + 2U]) << 40U)
                                               | static_cast<std::uint64_t>(static_cast<std::uint64_t>(in_begin[j + 1U]) << 48U)
                                               | static_cast<std::uint64_t>(static_cast<std::uint64_t>(in_begin[j + 0U]) << 56U));

                    j += 8U;
                  });
  }

  void crypto_hash_base::convert_uint64_input_to_uint8_output(const std::uint64_t* in_begin, const std::uint64_t* in_end, std::uint8_t* out_begin)
  {
    // Encodes the input (std::uint64_t) into the output (std::uint8_t).
    // This assumes that the length of the output is a multiple of 8.

    std::uint_least8_t j = static_cast<std::uint_least8_t>(0U);

    std::for_each(in_begin,
                  in_end,
                  [&j, &out_begin](const std::uint64_t& in_value)
                  {
                    out_begin[j + 0U] = static_cast<std::uint8_t>(in_value >>  0U);
                    out_begin[j + 1U] = static_cast<std::uint8_t>(in_value >>  8U);
                    out_begin[j + 2U] = static_cast<std::uint8_t>(in_value >> 16U);
                    out_begin[j + 3U] = static_cast<std::uint8_t>(in_value >> 24U);
                    out_begin[j + 4U] = static_cast<std::uint8_t>(in_value >> 32U);
                    out_begin[j + 5U] = static_cast<std::uint8_t>(in_value >> 40U);
                    out_begin[j + 6U] = static_cast<std::uint8_t>(in_value >> 48U);
                    out_begin[j + 7U] = static_cast<std::uint8_t>(in_value >> 56U);

                    j += 8U;
                  });
  }

    void crypto_hash_base::convert_uint64_input_to_uint8_output_reverse(const std::uint64_t* in_begin, const std::uint64_t* in_end, std::uint8_t* out_begin)
  {
    // Encodes the input (std::uint64_t) into the output (std::uint8_t).
    // This assumes that the length of the output is a multiple of 8.

    std::uint_least8_t j = static_cast<std::uint_least8_t>(0U);

    std::for_each(in_begin,
                  in_end,
                  [&j, &out_begin](const std::uint64_t& in_value)
                  {
                    out_begin[j + 7U] = static_cast<std::uint8_t>(in_value >>  0U);
                    out_begin[j + 6U] = static_cast<std::uint8_t>(in_value >>  8U);
                    out_begin[j + 5U] = static_cast<std::uint8_t>(in_value >> 16U);
                    out_begin[j + 4U] = static_cast<std::uint8_t>(in_value >> 24U);
                    out_begin[j + 3U] = static_cast<std::uint8_t>(in_value >> 32U);
                    out_begin[j + 2U] = static_cast<std::uint8_t>(in_value >> 40U);
                    out_begin[j + 1U] = static_cast<std::uint8_t>(in_value >> 48U);
                    out_begin[j + 0U] = static_cast<std::uint8_t>(in_value >> 56U);

                    j += 8U;
                  });
  }


  void crypto_hash_base::convert_uint8_input_to_char8_output(const std::uint8_t* in_begin, const std::uint8_t* in_end, char* out_begin)
  {
    std::uint_least8_t j = static_cast<std::uint_least8_t>(0U);

    std::for_each(in_begin,
                  in_end,
                  [&j, &out_begin](const std::uint8_t& the_byte)
                  {
                    const std::uint8_t lo_nibble =  the_byte & static_cast<std::uint8_t>(0x0FU);
                    const std::uint8_t hi_nibble = (the_byte >> 4);

                    out_begin[j + 1U] = convert_nibble4_to_char(lo_nibble, true);
                    out_begin[j + 0U] = convert_nibble4_to_char(hi_nibble, true);

                    j += 2U;
                  });
  }

  char crypto_hash_base::convert_nibble4_to_char(const std::uint8_t& the_nibble, const bool use_uppercase)
  {
    char c;

    if(the_nibble <= static_cast<std::uint8_t>(9U))
    {
      c = static_cast<char>(the_nibble + static_cast<std::uint8_t>(0x30U));
    }
    else if(   (the_nibble >= static_cast<std::uint8_t>(0x0AU))
            && (the_nibble <= static_cast<std::uint8_t>(0x0FU)))
    {
      c = (use_uppercase ? static_cast<char>(the_nibble + static_cast<std::uint8_t>(55U))
                         : static_cast<char>(the_nibble + static_cast<std::uint8_t>(87U)));
    }
    else
    {
      c = static_cast<char>(0x30U);
    }

    return c;
  }

#endif // _CRYPTO_HASH_BASE_2013_09_05_H_
