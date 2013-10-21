#ifndef _SHA2_2013_10_21_H_
  #define _SHA2_2013_10_21_H_

  #include <array>
  #include <cstddef>
  #include <functional>
  #include "crypto_hash_base.h"

  template <typename my_count_type>
  class sha2 : public crypto_hash_base
  {
  public:
    typedef my_count_type                  count_type;
    typedef std::array<std::uint8_t,  32U> result_type_as_bytes;
    typedef std::array<char,          64U> result_type_as_chars;
    typedef std::array<std::uint32_t,  8U> result_type_as_dwords;

    static_assert(   ( std::numeric_limits<count_type>::is_specialized == true)
                  && ( std::numeric_limits<count_type>::is_integer     == true)
                  && ( std::numeric_limits<count_type>::is_signed      == false)
                  && ( std::numeric_limits<count_type>::radix          == 2)
                  && ((std::numeric_limits<count_type>::digits % 8)    == 0),
                  "the count type must be an unsigned integer with radix 2, having a multiple of 8 bits");

    sha2();
    sha2(const std::uint8_t* data_stream,   count_type message_length);
    sha2(const char*         string_stream, count_type message_length);
    template<typename unsigned_integer_type> sha2(unsigned_integer_type u);
    sha2(const sha2& other);
    sha2& operator=(const sha2& other);

    void process_data(const std::uint8_t* data_stream, count_type message_length);

    void process_data(const char* string_stream, count_type message_length)
    {
      process_data(static_cast<const std::uint8_t*>(static_cast<const void*>(string_stream)), message_length);
    }

    template<typename unsigned_integer_type> void process_data(unsigned_integer_type u);

    result_type_as_bytes get_result_as_bytes_and_finalize_the_state();
    result_type_as_bytes get_result_as_bytes_and_nochange_the_state() const;

    result_type_as_dwords get_result_as_dwords_and_finalize_the_state();
    result_type_as_dwords get_result_as_dwords_and_nochange_the_state() const;

    result_type_as_chars get_result_as_chars_and_finalize_the_state();
    result_type_as_chars get_result_as_chars_and_nochange_the_state() const;

  private:
    static const std::uint_least8_t sha2_blocksize = 64U;

    static_assert(sha2_blocksize == static_cast<std::uint_least8_t>(64U),
                  "the block size must exactly equal 64");

    typedef std::array<std::uint8_t, sha2_blocksize> message_block_type;

    count_type            padding_length;
    result_type_as_dwords message_hash;
    message_block_type    message_block;

    void perform_algorithm();
    void finalize();
    void reset();

    template<const std::uint_fast8_t digits_shift>
    static std::uint32_t circular_shift(const std::uint32_t& shift_32word)
    {
      return   static_cast<std::uint32_t>(shift_32word << digits_shift)
             | static_cast<std::uint32_t>(shift_32word >> (static_cast<std::uint_fast8_t>(32U) - digits_shift));
    }
  };

  template <typename my_count_type>
  sha2<my_count_type>::sha2()
  {
  }

  template <typename my_count_type>
  sha2<my_count_type>::sha2(const std::uint8_t* data_stream, count_type message_length)
  {
    process_data(data_stream, message_length);
  }

  template <typename my_count_type>
  sha2<my_count_type>::sha2(const char* string_stream, count_type message_length)
  {
    process_data(static_cast<const std::uint8_t*>(static_cast<const void*>(string_stream)), message_length);
  }

  template<typename my_count_type>
  template<typename unsigned_integer_type>
  sha2<my_count_type>::sha2(unsigned_integer_type u)
  {
    process_data(u);
  }

  template <typename my_count_type>
  sha2<my_count_type>::sha2(const sha2& other) : crypto_hash_base(other),
                                                   padding_length  (other.padding_length),
                                                   message_hash    (other.message_hash),
                                                   message_block   (other.message_block)
  {
  }

  template <typename my_count_type>
  sha2<my_count_type>& sha2<my_count_type>::operator=(const sha2& other)
  {
    if(this != &other)
    {
      static_cast<void>(crypto_hash_base::operator=(other));

      padding_length = other.padding_length;
      message_hash   = other.message_hash;
      message_block  = other.message_block;
    }

    return *this;
  }

  template <typename my_count_type>
  void sha2<my_count_type>::process_data(const std::uint8_t* data_stream, count_type message_length)
  {
    if(the_result_is_finalized) { reset(); }

    while(message_length != static_cast<count_type>(0U))
    {
      message_block[message_block_index] = *data_stream;

      ++message_block_index;

      ++padding_length;

      if(message_block_index == sha2_blocksize)
      {
        perform_algorithm();
      }

      ++data_stream;
      --message_length;
    }
  }

  template<typename my_count_type>
  template<typename unsigned_integer_type>
  void sha2<my_count_type>::process_data(unsigned_integer_type u)
  {
    static_assert(   ( std::numeric_limits<unsigned_integer_type>::is_specialized == true)
                  && ( std::numeric_limits<unsigned_integer_type>::is_integer     == true)
                  && ( std::numeric_limits<unsigned_integer_type>::is_signed      == false)
                  && ( std::numeric_limits<unsigned_integer_type>::radix          == 2)
                  && ((std::numeric_limits<unsigned_integer_type>::digits % 8)    == 0),
                  "the template parameter type must be an unsigned integer type with radix 2, having a multiple of 8 bits");

    std::array<std::uint8_t, std::numeric_limits<unsigned_integer_type>::digits / 8> the_data;

    std::for_each(the_data.begin(),
                  the_data.end(),
                  [&u](std::uint8_t& data_value)
                  {
                    data_value = static_cast<std::uint8_t>(u);

                    u >>= 8;
                  });

    process_data(the_data.data(), the_data.size());
  }

  template <typename my_count_type>
  void sha2<my_count_type>::perform_algorithm()
  {
    // Apply the hash algorithm to a full data block.

    const std::array<std::uint32_t, 64> constants =
    {{
      UINT32_C(0x428a2f98),
      UINT32_C(0x71374491),
      UINT32_C(0xb5c0fbcf),
      UINT32_C(0xe9b5dba5),
      UINT32_C(0x3956c25b),
      UINT32_C(0x59f111f1),
      UINT32_C(0x923f82a4),
      UINT32_C(0xab1c5ed5),
      UINT32_C(0xd807aa98),
      UINT32_C(0x12835b01),
      UINT32_C(0x243185be),
      UINT32_C(0x550c7dc3),
      UINT32_C(0x72be5d74),
      UINT32_C(0x80deb1fe),
      UINT32_C(0x9bdc06a7),
      UINT32_C(0xc19bf174),
      UINT32_C(0xe49b69c1),
      UINT32_C(0xefbe4786),
      UINT32_C(0x0fc19dc6),
      UINT32_C(0x240ca1cc),
      UINT32_C(0x2de92c6f),
      UINT32_C(0x4a7484aa),
      UINT32_C(0x5cb0a9dc),
      UINT32_C(0x76f988da),
      UINT32_C(0x983e5152),
      UINT32_C(0xa831c66d),
      UINT32_C(0xb00327c8),
      UINT32_C(0xbf597fc7),
      UINT32_C(0xc6e00bf3),
      UINT32_C(0xd5a79147),
      UINT32_C(0x06ca6351),
      UINT32_C(0x14292967),
      UINT32_C(0x27b70a85),
      UINT32_C(0x2e1b2138),
      UINT32_C(0x4d2c6dfc),
      UINT32_C(0x53380d13),
      UINT32_C(0x650a7354),
      UINT32_C(0x766a0abb),
      UINT32_C(0x81c2c92e),
      UINT32_C(0x92722c85),
      UINT32_C(0xa2bfe8a1),
      UINT32_C(0xa81a664b),
      UINT32_C(0xc24b8b70),
      UINT32_C(0xc76c51a3),
      UINT32_C(0xd192e819),
      UINT32_C(0xd6990624),
      UINT32_C(0xf40e3585),
      UINT32_C(0x106aa070),
      UINT32_C(0x19a4c116),
      UINT32_C(0x1e376c08),
      UINT32_C(0x2748774c),
      UINT32_C(0x34b0bcb5),
      UINT32_C(0x391c0cb3),
      UINT32_C(0x4ed8aa4a),
      UINT32_C(0x5b9cca4f),
      UINT32_C(0x682e6ff3),
      UINT32_C(0x748f82ee),
      UINT32_C(0x78a5636f),
      UINT32_C(0x84c87814),
      UINT32_C(0x8cc70208),
      UINT32_C(0x90befffa),
      UINT32_C(0xa4506ceb),
      UINT32_C(0xbef9a3f7),
      UINT32_C(0xc67178f2)
    }};

    typedef std::uint32_t(*function_type)(const std::uint32_t);

    const std::array<function_type, 4U> functions =
    {{
      [](const std::uint32_t my_buffer_32word) -> std::uint32_t //BSIG0
      {
        return (((my_buffer_32word >>  2) | (my_buffer_32word << (32 -  2)))
               ^((my_buffer_32word >> 13) | (my_buffer_32word << (32 - 13)))
               ^((my_buffer_32word >> 22) | (my_buffer_32word << (32 - 22))));
      },
      [](const std::uint32_t my_buffer_32word) -> std::uint32_t //BSIG1
      {
        return (((my_buffer_32word >>  6) | (my_buffer_32word << (32 -  6)))
               ^((my_buffer_32word >> 11) | (my_buffer_32word << (32 - 11)))
               ^((my_buffer_32word >> 25) | (my_buffer_32word << (32 - 25))));
      },
      [](const std::uint32_t my_buffer_32word) -> std::uint32_t //SSIG0
      {
        return (((my_buffer_32word >>  7) | (my_buffer_32word << (32 -  7)))
               ^((my_buffer_32word >> 18) | (my_buffer_32word << (32 - 18)))
               ^( my_buffer_32word >>  3));
      },
      [](const std::uint32_t my_buffer_32word) -> std::uint32_t //SSIG1
      {
        return (((my_buffer_32word >> 17) | (my_buffer_32word << (32 - 17)))
               ^((my_buffer_32word >> 19) | (my_buffer_32word << (32 - 19)))
               ^( my_buffer_32word >> 10));
      }
    }};

    std::array<std::uint32_t, 64U> sequence_32word;

    for(std::uint_fast8_t loop_counter = static_cast<std::uint_fast8_t>(0U); loop_counter < static_cast<std::uint_fast8_t>(16U); loop_counter++)
    {
      sequence_32word[loop_counter]  = (  (static_cast<std::uint32_t>(message_block[(loop_counter * 4U)                                     ]) << 24U)
                                        | (static_cast<std::uint32_t>(message_block[(loop_counter * 4U) + static_cast<std::uint_fast8_t>(1U)]) << 16U)
                                        | (static_cast<std::uint32_t>(message_block[(loop_counter * 4U) + static_cast<std::uint_fast8_t>(2U)]) <<  8U)
                                        | (static_cast<std::uint32_t>(message_block[(loop_counter * 4U) + static_cast<std::uint_fast8_t>(3U)]) <<  0U));
    }

    for(std::uint_fast8_t loop_counter = static_cast<std::uint_fast8_t>(16U); loop_counter < static_cast<std::uint_fast8_t>(64U); loop_counter++)
    {
      sequence_32word[loop_counter] =   functions[3](sequence_32word[loop_counter - 2])
                                      + sequence_32word[loop_counter - 7]
                                      + functions[2](sequence_32word[loop_counter - 15])
                                      + sequence_32word[loop_counter - 16];
    }

    result_type_as_dwords hash_tmp = message_hash;

    std::uint32_t temporary1;
    std::uint32_t temporary2;

    for(std::uint_fast8_t loop_counter = static_cast<std::uint_fast8_t>(0U); loop_counter < static_cast<std::uint_fast8_t>(64U); loop_counter++)
    {
      temporary1 =   hash_tmp[7]
                   + functions[1](hash_tmp[4])
                   + (hash_tmp[4] & hash_tmp[5]) ^ ((!hash_tmp[4]) & hash_tmp[6])
                   + constants[loop_counter]
                   + sequence_32word[loop_counter];
      temporary2 =   functions[0](hash_tmp[0])
                   + (hash_tmp[0] & hash_tmp[1]) ^ (hash_tmp[0] & hash_tmp[2]) ^ (hash_tmp[1] & hash_tmp[2]);

      hash_tmp[7] = hash_tmp[6];
      hash_tmp[6] = hash_tmp[5];
      hash_tmp[5] = hash_tmp[4];
      hash_tmp[4] = hash_tmp[3] + temporary1;
      hash_tmp[3] = hash_tmp[2];
      hash_tmp[2] = hash_tmp[1];
      hash_tmp[1] = hash_tmp[0];
      hash_tmp[0] = temporary1 + temporary2;
    }

    // Update the hash state with the transformation results.
    std::transform(message_hash.cbegin     (),
                   message_hash.cend       (),
                   hash_tmp.cbegin         (),
                   message_hash.begin      (),
                   std::plus<std::uint32_t>());

    message_block_index = static_cast<std::uint_least8_t>(0U);
  }

  template <typename my_count_type>
  void sha2<my_count_type>::finalize()
  {
    // Create the padding. Begin by setting the leading padding byte to 0x80.
    message_block[message_block_index] = static_cast<std::uint8_t>(0x80U);

    ++message_block_index;

    // Fill the rest of the padding bytes with zero.
    std::fill(message_block.begin() + message_block_index,
              message_block.end(),
              static_cast<std::uint8_t>(0U));

    // Do we need an extra block? If so, then transform the
    // current block and pad an additional block.
    if(message_block_index > static_cast<std::uint_least8_t>(sha2_blocksize - 8U))
    {
      perform_algorithm();

      message_block.fill(static_cast<std::uint8_t>(0U));
    }

    // Encode the number of bits. Simultaneously convert the number of bytes
    // to the number of bits by performing a left-shift of 3 on the byte-array.
    // The sha2 stores the 8 bytes of the bit counter in reverse order,
    // with the lowest byte being stored at the highest position of the buffer
    std::uint_least8_t carry = static_cast<std::uint_least8_t>(0U);

    std::for_each(message_block.rbegin(),
                  message_block.rbegin() + 8U,
                  [&carry, this](std::uint8_t& the_byte)
                  {
                    const std::uint_least16_t the_word = static_cast<std::uint_least16_t>(this->padding_length) << 3;

                    the_byte = static_cast<std::uint8_t>(the_word | carry);

                    this->padding_length >>= 8;

                    carry = static_cast<std::uint_least8_t>(the_word >> 8) & static_cast<std::uint_least8_t>(0x07U);
                  });

    perform_algorithm();

    the_result_is_finalized = true;
  }

  template<typename my_count_type>
  void sha2<my_count_type>::reset()
  {
    message_hash[0U] = UINT32_C(0x6a09e667);
    message_hash[1U] = UINT32_C(0xbb67ae85);
    message_hash[2U] = UINT32_C(0x3c6ef372);
    message_hash[3U] = UINT32_C(0xa54ff53a);
    message_hash[4U] = UINT32_C(0x510e527f);
    message_hash[5U] = UINT32_C(0x9b05688c);
    message_hash[6U] = UINT32_C(0x1f83d9ab);
    message_hash[7U] = UINT32_C(0x5be0cd19);

    the_result_is_finalized = false;
    padding_length          = static_cast<count_type>(0U);
    message_block_index     = static_cast<std::uint_least8_t>(0U);
  }

  template<typename my_count_type>
  typename sha2<my_count_type>::result_type_as_bytes sha2<my_count_type>::get_result_as_bytes_and_finalize_the_state()
  {
    if(!the_result_is_finalized) { finalize(); }

    result_type_as_bytes result;

    // Extract the hash result from the message digest state.
    convert_uint32_input_to_uint8_output(message_hash.data(),
                                         message_hash.data() + message_hash.size(),
                                         result.data());

    return result;
  }

  template<typename my_count_type>
  typename sha2<my_count_type>::result_type_as_bytes sha2<my_count_type>::get_result_as_bytes_and_nochange_the_state() const
  {
    // Make a local copy of the hash object.
    sha2 other(*this);

    // Finalize the local copy of the hash object,
    // and return the final result from the copied object.
    return other.get_result_as_bytes_and_finalize_the_state();
  }

  template<typename my_count_type>
  typename sha2<my_count_type>::result_type_as_dwords sha2<my_count_type>::get_result_as_dwords_and_finalize_the_state()
  {
    if(!the_result_is_finalized) { finalize(); }

    return message_hash;
  }

  template<typename my_count_type>
  typename sha2<my_count_type>::result_type_as_dwords sha2<my_count_type>::get_result_as_dwords_and_nochange_the_state() const
  {
    // Make a local copy of the hash object.
    sha2 other(*this);

    // Finalize the local copy of the hash object,
    // and return the final result from the copied object.
    other.finalize();

    return other.message_hash;
  }

  template<typename my_count_type>
  typename sha2<my_count_type>::result_type_as_chars sha2<my_count_type>::get_result_as_chars_and_finalize_the_state()
  {
    // Get the result of the hash object as a byte array.
    const result_type_as_bytes the_result_as_bytes = get_result_as_bytes_and_finalize_the_state();

    result_type_as_chars the_result_as_chars;

    // Convert the result as a byte array to a character array.
    convert_uint8_input_to_char8_output(the_result_as_bytes.data(),
                                        the_result_as_bytes.data() + the_result_as_bytes.size(),
                                        the_result_as_chars.data());

    // Obtain the correct byte order for displaying the sha2 string in the usual fashion.
/*    for(std::uint_least8_t i = static_cast<std::uint_least8_t>(0U); i < static_cast<std::uint_least8_t>(the_result_as_chars.size()); i += 8U)
    {
      std::swap_ranges(the_result_as_chars.begin() + (i + 0U),
                       the_result_as_chars.begin() + (i + 2U),
                       the_result_as_chars.begin() + (i + 6U));

      std::swap_ranges(the_result_as_chars.begin() + (i + 2U),
                       the_result_as_chars.begin() + (i + 4U),
                       the_result_as_chars.begin() + (i + 4U));
    }*/

    return the_result_as_chars;
  }

  template<typename my_count_type>
  typename sha2<my_count_type>::result_type_as_chars sha2<my_count_type>::get_result_as_chars_and_nochange_the_state() const
  {
    // Make a local copy of the hash object.
    sha2 temp_sha2(*this);

    // Finalize the local copy of the hash object,
    // and return the final result from the copied object.
    return temp_sha2.get_result_as_chars_and_finalize_the_state();
  }

#endif // _SHA2_2013_10_21_H_
