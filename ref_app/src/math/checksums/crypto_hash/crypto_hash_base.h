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

  class crypto_hash_base
  {
  protected:
    crypto_hash_base() : the_result_is_finalized  (true),
                         count_remaining_in_buffer(0U) { }

    crypto_hash_base(const crypto_hash_base& other) : the_result_is_finalized  (other.the_result_is_finalized),
                                                      count_remaining_in_buffer(other.count_remaining_in_buffer) { }

    crypto_hash_base& operator=(const crypto_hash_base& other)
    {
      the_result_is_finalized   = other.the_result_is_finalized;
      count_remaining_in_buffer = other.count_remaining_in_buffer;

      return *this;
    }

    bool               the_result_is_finalized;
    std::uint_least8_t count_remaining_in_buffer;

    static void convert_uint8_input_to_uint32_output(const std::uint8_t* input_begin, const std::uint8_t* input_end, std::uint32_t* output_begin)
    {
      // Decodes the input (std::uint8_t) into the output (std::uint32_t).
      // This assumes that the length of the input is a multiple of 4.

      std::size_t j = static_cast<std::size_t>(0U);

      std::for_each(output_begin,
                    output_begin + std::size_t(std::size_t(input_end - input_begin) / 4U),
                    [&j, &input_begin](std::uint32_t& output_value)
                    {
                      output_value =  std::uint32_t(  static_cast<std::uint32_t>(static_cast<std::uint32_t>(input_begin[j + 0U]) <<  0U)
                                                    | static_cast<std::uint32_t>(static_cast<std::uint32_t>(input_begin[j + 1U]) <<  8U)
                                                    | static_cast<std::uint32_t>(static_cast<std::uint32_t>(input_begin[j + 2U]) << 16U)
                                                    | static_cast<std::uint32_t>(static_cast<std::uint32_t>(input_begin[j + 3U]) << 24U));

                      j += 4U;
                    });
    }

    static void convert_uint32_input_to_uint8_output(const std::uint32_t* input_begin, const std::uint32_t* input_end, std::uint8_t* output_begin)
    {
      // Encodes the input (std::uint32_t) into the output (std::uint8_t).
      // This assumes that the length of the output is a multiple of 4.

      std::size_t j = static_cast<std::size_t>(0U);

      std::for_each(input_begin,
                    input_end,
                    [&j, &output_begin](const std::uint32_t& input_value)
                    {
                      output_begin[j + 0U] = static_cast<std::uint8_t>(input_value >>  0U);
                      output_begin[j + 1U] = static_cast<std::uint8_t>(input_value >>  8U);
                      output_begin[j + 2U] = static_cast<std::uint8_t>(input_value >> 16U);
                      output_begin[j + 3U] = static_cast<std::uint8_t>(input_value >> 24U);

                      j += 4U;
                    });
    }
  };

#endif // _CRYPTO_HASH_BASE_2013_09_05_H_
