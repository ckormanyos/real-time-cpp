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

  template<const std::uint_fast8_t digits_shift>
  inline std::uint32_t crypto_hash_circular_shift(const std::uint32_t& the_dword)
  {
    return std::uint32_t(  std::uint32_t(the_dword << digits_shift)
                         | std::uint32_t(the_dword >> (std::uint_fast8_t(32U) - digits_shift)));
  }

  class crypto_hash_base
  {
  protected:
    bool               the_result_is_finalized;
    std::uint_least8_t message_block_index;

    crypto_hash_base();

    crypto_hash_base(const crypto_hash_base& other);

    crypto_hash_base& operator=(const crypto_hash_base& other);

    static void convert_uint8_input_to_uint32_output        (const std::uint8_t* src_begin, const std::uint8_t* src_end, std::uint32_t* dest_begin);
    static void convert_uint8_input_to_uint32_output_reverse(const std::uint8_t* src_begin, const std::uint8_t* src_end, std::uint32_t* dest_begin);

    static void convert_uint32_input_to_uint8_output(const std::uint32_t* src_begin, const std::uint32_t* src_end, std::uint8_t*  dest_begin);
    static void convert_uint8_input_to_char8_output (const std::uint8_t*  src_begin, const std::uint8_t*  src_end, char*          dest_begin);

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

  void crypto_hash_base::convert_uint8_input_to_uint32_output(const std::uint8_t* src_begin, const std::uint8_t* src_end, std::uint32_t* dest_begin)
  {
    // Decodes the input (std::uint8_t) into the output (std::uint32_t).
    // This assumes that the length of the input is a multiple of 4.

    std::uint_least8_t j = static_cast<std::uint_least8_t>(0U);

    std::for_each(dest_begin,
                  dest_begin + std::uint_least8_t(src_end - src_begin) / 4U,
                  [&j, &src_begin](std::uint32_t& dest_value)
                  {
                    dest_value =  std::uint32_t(  static_cast<std::uint32_t>(static_cast<std::uint32_t>(src_begin[j + 0U]) <<  0U)
                                                | static_cast<std::uint32_t>(static_cast<std::uint32_t>(src_begin[j + 1U]) <<  8U)
                                                | static_cast<std::uint32_t>(static_cast<std::uint32_t>(src_begin[j + 2U]) << 16U)
                                                | static_cast<std::uint32_t>(static_cast<std::uint32_t>(src_begin[j + 3U]) << 24U));

                    j += 4U;
                  });
  }

  void crypto_hash_base::convert_uint8_input_to_uint32_output_reverse(const std::uint8_t* src_begin, const std::uint8_t* src_end, std::uint32_t* dest_begin)
  {
    // Decodes the input (std::uint8_t) into the output (std::uint32_t).
    // This assumes that the length of the input is a multiple of 4.

    std::uint_least8_t j = static_cast<std::uint_least8_t>(0U);

    std::for_each(dest_begin,
                  dest_begin + std::uint_least8_t(src_end - src_begin) / 4U,
                  [&j, &src_begin](std::uint32_t& dest_value)
                  {
                    dest_value =  std::uint32_t(  static_cast<std::uint32_t>(static_cast<std::uint32_t>(src_begin[j + 3U]) <<  0U)
                                                | static_cast<std::uint32_t>(static_cast<std::uint32_t>(src_begin[j + 2U]) <<  8U)
                                                | static_cast<std::uint32_t>(static_cast<std::uint32_t>(src_begin[j + 1U]) << 16U)
                                                | static_cast<std::uint32_t>(static_cast<std::uint32_t>(src_begin[j + 0U]) << 24U));

                    j += 4U;
                  });
  }

  void crypto_hash_base::convert_uint32_input_to_uint8_output(const std::uint32_t* src_begin, const std::uint32_t* src_end, std::uint8_t* dest_begin)
  {
    // Encodes the input (std::uint32_t) into the output (std::uint8_t).
    // This assumes that the length of the output is a multiple of 4.

    std::uint_least8_t j = static_cast<std::uint_least8_t>(0U);

    std::for_each(src_begin,
                  src_end,
                  [&j, &dest_begin](const std::uint32_t& src_value)
                  {
                    dest_begin[j + 0U] = static_cast<std::uint8_t>(src_value >>  0U);
                    dest_begin[j + 1U] = static_cast<std::uint8_t>(src_value >>  8U);
                    dest_begin[j + 2U] = static_cast<std::uint8_t>(src_value >> 16U);
                    dest_begin[j + 3U] = static_cast<std::uint8_t>(src_value >> 24U);

                    j += 4U;
                  });
  }

  void crypto_hash_base::convert_uint8_input_to_char8_output(const std::uint8_t* src_begin, const std::uint8_t* src_end, char* dest_begin)
  {
    std::uint_least8_t j = static_cast<std::uint_least8_t>(0U);

    std::for_each(src_begin,
                  src_end,
                  [&j, &dest_begin](const std::uint8_t& the_byte)
                  {
                    const std::uint8_t lo_nibble =  the_byte & static_cast<std::uint8_t>(0x0FU);
                    const std::uint8_t hi_nibble = (the_byte >> 4);

                    dest_begin[j + 1U] = convert_nibble4_to_char(lo_nibble, true);
                    dest_begin[j + 0U] = convert_nibble4_to_char(hi_nibble, true);

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
