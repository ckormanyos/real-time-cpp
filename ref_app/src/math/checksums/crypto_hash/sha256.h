
///////////////////////////////////////////////////////////////////////////////
// \license BCP 78
// sha256 can not be redistributed or modified.
//

///////////////////////////////////////////////////////////////////////////////
//
// This work has been created by Arwed Steuer and Christopher Kormanyos.
// This work is an implementation of sha256 that has been specifically
// designed for C++. The implementation places particular
// emphasis on portability to microcontroller platforms.
//
// This work has been derived from:
// "RFC 4868 HMAC-SHA256, SHA384, and SHA512 in IPsec May 2007".
// The original license notices from "The IETF Trust"
// follow below.
//
// Copyright (C) The IETF Trust (2007).
//
// This document is subject to the rights, licenses and restrictions
// contained in BCP 78, and except as set forth therein, the authors
// retain all their rights.
//
// This document and the information contained herein are provided on an
// "AS IS" basis and THE CONTRIBUTOR, THE ORGANIZATION HE/SHE REPRESENTS
// OR IS SPONSORED BY (IF ANY), THE INTERNET SOCIETY, THE IETF TRUST AND
// THE INTERNET ENGINEERING TASK FORCE DISCLAIM ALL WARRANTIES, EXPRESS
// OR IMPLIED, INCLUDING BUT NOT LIMITED TO ANY WARRANTY THAT THE USE OF
// THE INFORMATION HEREIN WILL NOT INFRINGE ANY RIGHTS OR ANY IMPLIED
// WARRANTIES OF MERCHANTABILITY OR FITNESS FOR A PARTICULAR PURPOSE.
//
// Intellectual Property
//
// The IETF takes no position regarding the validity or scope of any
// Intellectual Property Rights or other rights that might be claimed to
// pertain to the implementation or use of the technology described in
// this document or the extent to which any license under such rights
// might or might not be available; nor does it represent that it has
// made any independent effort to identify any such rights. Information
// on the procedures with respect to rights in RFC documents can be
// found in BCP 78 and BCP 79.
//
// Copies of IPR disclosures made to the IETF Secretariat and any
// assurances of licenses to be made available, or the result of an
// attempt made to obtain a general license or permission for the use of
// such proprietary rights by implementers or users of this
// specification can be obtained from the IETF on-line IPR repository at
// http://www.ietf.org/ipr.
//
// The IETF invites any interested party to bring to its attention any
// copyrights, patents or patent applications, or other proprietary
// rights that may cover technology that may be required to implement
// this standard. Please address the information to the IETF at
// ietf-ipr@ietf.org.
///////////////////////////////////////////////////////////////////////////////

#ifndef _SHA256_2013_10_21_H_
  #define _SHA256_2013_10_21_H_

  #include <array>
  #include <cstddef>
  #include <functional>
  #include "crypto_hash_base.h"

  template <typename my_count_type>
  class sha256 : public crypto_hash_base
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

    sha256();
    sha256(const std::uint8_t* data_stream,   count_type message_length);
    sha256(const char*         string_stream, count_type message_length);
    template<typename unsigned_integer_type> sha256(unsigned_integer_type u);
    sha256(const sha256& other);
    sha256& operator=(const sha256& other);

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
    static const std::uint_least8_t sha256_blocksize = 64U;

    static_assert(sha256_blocksize == static_cast<std::uint_least8_t>(64U),
                  "the block size must exactly equal 64");

    typedef std::array<std::uint8_t, sha256_blocksize> message_block_type;

    count_type            message_length_total;
    result_type_as_dwords message_hash;
    message_block_type    message_block;

    void perform_algorithm();
    void finalize();
    void reset();
  };

  template <typename my_count_type>
  sha256<my_count_type>::sha256()
  {
  }

  template <typename my_count_type>
  sha256<my_count_type>::sha256(const std::uint8_t* data_stream, count_type message_length)
  {
    process_data(data_stream, message_length);
  }

  template <typename my_count_type>
  sha256<my_count_type>::sha256(const char* string_stream, count_type message_length)
  {
    process_data(static_cast<const std::uint8_t*>(static_cast<const void*>(string_stream)), message_length);
  }

  template<typename my_count_type>
  template<typename unsigned_integer_type>
  sha256<my_count_type>::sha256(unsigned_integer_type u)
  {
    process_data(u);
  }

  template <typename my_count_type>
  sha256<my_count_type>::sha256(const sha256& other) : crypto_hash_base    (other),
                                                 message_length_total(other.message_length_total),
                                                 message_hash        (other.message_hash),
                                                 message_block       (other.message_block)
  {
  }

  template <typename my_count_type>
  sha256<my_count_type>& sha256<my_count_type>::operator=(const sha256& other)
  {
    if(this != &other)
    {
      static_cast<void>(crypto_hash_base::operator=(other));

      message_length_total = other.message_length_total;
      message_hash         = other.message_hash;
      message_block        = other.message_block;
    }

    return *this;
  }

  template <typename my_count_type>
  void sha256<my_count_type>::process_data(const std::uint8_t* data_stream, count_type message_length)
  {
    if(the_result_is_finalized) { reset(); }

    while(message_length != static_cast<count_type>(0U))
    {
      message_block[message_block_index] = *data_stream;

      ++message_block_index;

      ++message_length_total;

      if(message_block_index == sha256_blocksize)
      {
        perform_algorithm();
      }

      ++data_stream;
      --message_length;
    }
  }

  template<typename my_count_type>
  template<typename unsigned_integer_type>
  void sha256<my_count_type>::process_data(unsigned_integer_type u)
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
  void sha256<my_count_type>::perform_algorithm()
  {
    // Apply the hash algorithm to a full data block.

    const std::array<std::uint32_t, 64> constants =
    {{
      UINT32_C(0x428A2F98), UINT32_C(0x71374491), UINT32_C(0xB5C0FBCF), UINT32_C(0xE9B5DBA5), 
      UINT32_C(0x3956C25B), UINT32_C(0x59F111F1), UINT32_C(0x923F82A4), UINT32_C(0xAB1C5ED5), 
      UINT32_C(0xD807AA98), UINT32_C(0x12835B01), UINT32_C(0x243185BE), UINT32_C(0x550C7DC3), 
      UINT32_C(0x72BE5D74), UINT32_C(0x80DEB1FE), UINT32_C(0x9BDC06A7), UINT32_C(0xC19BF174), 
      UINT32_C(0xE49B69C1), UINT32_C(0xEFBE4786), UINT32_C(0x0FC19DC6), UINT32_C(0x240CA1CC), 
      UINT32_C(0x2DE92C6F), UINT32_C(0x4A7484AA), UINT32_C(0x5CB0A9DC), UINT32_C(0x76F988DA), 
      UINT32_C(0x983E5152), UINT32_C(0xA831C66D), UINT32_C(0xB00327C8), UINT32_C(0xBF597FC7), 
      UINT32_C(0xC6E00BF3), UINT32_C(0xD5A79147), UINT32_C(0x06CA6351), UINT32_C(0x14292967), 
      UINT32_C(0x27B70A85), UINT32_C(0x2E1B2138), UINT32_C(0x4D2C6DFC), UINT32_C(0x53380D13), 
      UINT32_C(0x650A7354), UINT32_C(0x766A0ABB), UINT32_C(0x81C2C92E), UINT32_C(0x92722C85), 
      UINT32_C(0xA2BFE8A1), UINT32_C(0xA81A664B), UINT32_C(0xC24B8B70), UINT32_C(0xC76C51A3), 
      UINT32_C(0xD192E819), UINT32_C(0xD6990624), UINT32_C(0xF40E3585), UINT32_C(0x106AA070), 
      UINT32_C(0x19A4C116), UINT32_C(0x1E376C08), UINT32_C(0x2748774C), UINT32_C(0x34B0BCB5), 
      UINT32_C(0x391C0CB3), UINT32_C(0x4ED8AA4A), UINT32_C(0x5B9CCA4F), UINT32_C(0x682E6FF3), 
      UINT32_C(0x748F82EE), UINT32_C(0x78A5636F), UINT32_C(0x84C87814), UINT32_C(0x8CC70208), 
      UINT32_C(0x90BEFFFA), UINT32_C(0xA4506CEB), UINT32_C(0xBEF9A3F7), UINT32_C(0xC67178F2)
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

    for(std::uint_fast8_t loop_counter = static_cast<std::uint_fast8_t>(0U); loop_counter < static_cast<std::uint_fast8_t>(64U); loop_counter++)
    {
      const std::uint32_t tmp1 =   hash_tmp[7]
                                 + functions[1](hash_tmp[4])
                                 + std::uint32_t(std::uint32_t(hash_tmp[4] & hash_tmp[5]) ^ std::uint32_t(std::uint32_t(~hash_tmp[4]) & hash_tmp[6]))
                                 + constants[loop_counter]
                                 + sequence_32word[loop_counter];

      const std::uint32_t tmp2 =   functions[0](hash_tmp[0])
                                 + std::uint32_t(std::uint32_t(hash_tmp[0] & hash_tmp[1]) ^ std::uint32_t(hash_tmp[0] & hash_tmp[2]) ^ std::uint32_t(hash_tmp[1] & hash_tmp[2]));

      hash_tmp[7] = hash_tmp[6];
      hash_tmp[6] = hash_tmp[5];
      hash_tmp[5] = hash_tmp[4];
      hash_tmp[4] = hash_tmp[3] + tmp1;
      hash_tmp[3] = hash_tmp[2];
      hash_tmp[2] = hash_tmp[1];
      hash_tmp[1] = hash_tmp[0];
      hash_tmp[0] = tmp1 + tmp2;
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
  void sha256<my_count_type>::finalize()
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
    if(message_block_index > static_cast<std::uint_least8_t>(sha256_blocksize - 8U))
    {
      perform_algorithm();

      message_block.fill(static_cast<std::uint8_t>(0U));
    }

    // Encode the number of bits. Simultaneously convert the number of bytes
    // to the number of bits by performing a left-shift of 3 on the byte-array.
    // The sha256 stores the 8 bytes of the bit counter in reverse order,
    // with the lowest byte being stored at the highest position of the buffer
    std::uint_least8_t carry = static_cast<std::uint_least8_t>(0U);

    std::for_each(message_block.rbegin(),
                  message_block.rbegin() + 8U,
                  [&carry, this](std::uint8_t& the_byte)
                  {
                    const std::uint_least16_t the_word = static_cast<std::uint_least16_t>(this->message_length_total) << 3;

                    the_byte = static_cast<std::uint8_t>(the_word | carry);

                    this->message_length_total >>= 8;

                    carry = static_cast<std::uint_least8_t>(the_word >> 8) & static_cast<std::uint_least8_t>(0x07U);
                  });

    perform_algorithm();

    the_result_is_finalized = true;
  }

  template<typename my_count_type>
  void sha256<my_count_type>::reset()
  {
    message_hash[0U] = UINT32_C(0x6A09E667);
    message_hash[1U] = UINT32_C(0xBB67AE85);
    message_hash[2U] = UINT32_C(0x3C6EF372);
    message_hash[3U] = UINT32_C(0xA54FF53A);
    message_hash[4U] = UINT32_C(0x510E527F);
    message_hash[5U] = UINT32_C(0x9B05688C);
    message_hash[6U] = UINT32_C(0x1F83D9AB);
    message_hash[7U] = UINT32_C(0x5BE0CD19);

    the_result_is_finalized = false;
    message_length_total    = static_cast<count_type>(0U);
    message_block_index     = static_cast<std::uint_least8_t>(0U);
  }

  template<typename my_count_type>
  typename sha256<my_count_type>::result_type_as_bytes sha256<my_count_type>::get_result_as_bytes_and_finalize_the_state()
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
  typename sha256<my_count_type>::result_type_as_bytes sha256<my_count_type>::get_result_as_bytes_and_nochange_the_state() const
  {
    // Make a local copy of the hash object.
    sha256 other(*this);

    // Finalize the local copy of the hash object,
    // and return the final result from the copied object.
    return other.get_result_as_bytes_and_finalize_the_state();
  }

  template<typename my_count_type>
  typename sha256<my_count_type>::result_type_as_dwords sha256<my_count_type>::get_result_as_dwords_and_finalize_the_state()
  {
    if(!the_result_is_finalized) { finalize(); }

    return message_hash;
  }

  template<typename my_count_type>
  typename sha256<my_count_type>::result_type_as_dwords sha256<my_count_type>::get_result_as_dwords_and_nochange_the_state() const
  {
    // Make a local copy of the hash object.
    sha256 other(*this);

    // Finalize the local copy of the hash object,
    // and return the final result from the copied object.
    other.finalize();

    return other.message_hash;
  }

  template<typename my_count_type>
  typename sha256<my_count_type>::result_type_as_chars sha256<my_count_type>::get_result_as_chars_and_finalize_the_state()
  {
    // Get the result of the hash object as a byte array.
    const result_type_as_bytes the_result_as_bytes = get_result_as_bytes_and_finalize_the_state();

    result_type_as_chars the_result_as_chars;

    // Convert the result as a byte array to a character array.
    convert_uint8_input_to_char8_output(the_result_as_bytes.data(),
                                        the_result_as_bytes.data() + the_result_as_bytes.size(),
                                        the_result_as_chars.data());

    // Obtain the correct byte order for displaying the sha256 string in the usual fashion.
    for(std::uint_least8_t i = static_cast<std::uint_least8_t>(0U); i < static_cast<std::uint_least8_t>(the_result_as_chars.size()); i += 8U)
    {
      std::swap_ranges(the_result_as_chars.begin() + (i + 0U),
                       the_result_as_chars.begin() + (i + 2U),
                       the_result_as_chars.begin() + (i + 6U));

      std::swap_ranges(the_result_as_chars.begin() + (i + 2U),
                       the_result_as_chars.begin() + (i + 4U),
                       the_result_as_chars.begin() + (i + 4U));
    }

    return the_result_as_chars;
  }

  template<typename my_count_type>
  typename sha256<my_count_type>::result_type_as_chars sha256<my_count_type>::get_result_as_chars_and_nochange_the_state() const
  {
    // Make a local copy of the hash object.
    sha256 temp_sha256(*this);

    // Finalize the local copy of the hash object,
    // and return the final result from the copied object.
    return temp_sha256.get_result_as_chars_and_finalize_the_state();
  }

#endif // _SHA256_2013_10_21_H_
