
///////////////////////////////////////////////////////////////////////////////
//  Copyright Arwed Steuer 2013.
//  Copyright Christopher Kormanyos 2013.
//
// \license LGPLv3
// sha1 is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// sha1 is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
// GNU Lesser Public License for more details.
// You should have received a copy of the GNU Lesser Public License
// along with sha1. If not, see <http://www.gnu.org/licenses/>.
//

///////////////////////////////////////////////////////////////////////////////
//
// This work has been created by Arwed Steuer and Christopher Kormanyos.
// This work is an implementation of sha1 that has been specifically
// designed for C++. The implementation places particular
// emphasis on portability to microcontroller platforms.
//
// This work has been derived from:
// "RFC 3174 US Secure Hash Algorithm 1 (SHA1) September 2001".
// The original license notices from "The Internet Society"
// follow below.
//
// Copyright (C) The Internet Society (2001).  All Rights Reserved.
//
// This document and translations of it may be copied and furnished to
// others, and derivative works that comment on or otherwise explain it
// or assist in its implementation may be prepared, copied, published
// and distributed, in whole or in part, without restriction of any
// kind, provided that the above copyright notice and this paragraph are
// included on all such copies and derivative works.  However, this
// document itself may not be modified in any way, such as by removing
// the copyright notice or references to the Internet Society or other
// Internet organizations, except as needed for the purpose of
// developing Internet standards in which case the procedures for
// copyrights defined in the Internet Standards process must be
// followed, or as required to translate it into languages other than
// English.
//
// The limited permissions granted above are perpetual and will not be
// revoked by the Internet Society or its successors or assigns.
//
// This document and the information contained herein is provided on an
// "AS IS" basis and THE INTERNET SOCIETY AND THE INTERNET ENGINEERING
// TASK FORCE DISCLAIMS ALL WARRANTIES, EXPRESS OR IMPLIED, INCLUDING
// BUT NOT LIMITED TO ANY WARRANTY THAT THE USE OF THE INFORMATION
// HEREIN WILL NOT INFRINGE ANY RIGHTS OR ANY IMPLIED WARRANTIES OF
// MERCHANTABILITY OR FITNESS FOR A PARTICULAR PURPOSE.
///////////////////////////////////////////////////////////////////////////////

#ifndef _SHA1_2013_09_03_H_
  #define _SHA1_2013_09_03_H_

  #include <array>
  #include <cstddef>
  #include <functional>
  #include "crypto_hash_base.h"

  template <typename my_count_type>
  class sha1 : public crypto_hash_base
  {
  public:
    typedef my_count_type                  count_type;
    typedef std::array<std::uint8_t,  20U> result_type_as_bytes;
    typedef std::array<char,          40U> result_type_as_chars;
    typedef std::array<std::uint32_t,  5U> result_type_as_dwords;

    static_assert(   ( std::numeric_limits<count_type>::is_specialized == true)
                  && ( std::numeric_limits<count_type>::is_integer     == true)
                  && ( std::numeric_limits<count_type>::is_signed      == false)
                  && ( std::numeric_limits<count_type>::radix          == 2)
                  && ((std::numeric_limits<count_type>::digits % 8)    == 0),
                  "the count type must be an unsigned integer with radix 2, having a multiple of 8 bits");

    sha1();
    sha1(const std::uint8_t* data_bytes, count_type message_length);
    sha1(const char*         data_chars, count_type message_length);
    template<typename unsigned_integer_type> sha1(unsigned_integer_type u);
    sha1(const sha1& other);
    sha1& operator=(const sha1& other);

    void process_data(const std::uint8_t* data_bytes, count_type message_length);

    void process_data(const char* data_chars, count_type message_length)
    {
      process_data(static_cast<const std::uint8_t*>(static_cast<const void*>(data_chars)), message_length);
    }

    template<typename unsigned_integer_type> void process_data(unsigned_integer_type u);

    result_type_as_bytes get_result_as_bytes_and_finalize_the_state();
    result_type_as_bytes get_result_as_bytes_and_nochange_the_state() const;

    result_type_as_dwords get_result_as_dwords_and_finalize_the_state();
    result_type_as_dwords get_result_as_dwords_and_nochange_the_state() const;

    result_type_as_chars get_result_as_chars_and_finalize_the_state();
    result_type_as_chars get_result_as_chars_and_nochange_the_state() const;

  private:
    static const std::uint_fast8_t sha1_blocksize = 64U;

    static_assert(sha1_blocksize == static_cast<std::uint_fast8_t>(64U),
                  "the block size must exactly equal 64");

    typedef std::array<std::uint8_t, sha1_blocksize>       message_block_type;
    typedef std::array<std::uint32_t, sha1_blocksize / 4U> transform_block_type;

    count_type            message_length_total;
    result_type_as_dwords message_hash;
    message_block_type    message_block;

    void perform_algorithm();
    void finalize();
    void reset();
  };

  template <typename my_count_type>
  sha1<my_count_type>::sha1()
  {
  }

  template <typename my_count_type>
  sha1<my_count_type>::sha1(const std::uint8_t* data_bytes, count_type message_length)
  {
    process_data(data_bytes, message_length);
  }

  template <typename my_count_type>
  sha1<my_count_type>::sha1(const char* data_chars, count_type message_length)
  {
    process_data(static_cast<const std::uint8_t*>(static_cast<const void*>(data_chars)), message_length);
  }

  template<typename my_count_type>
  template<typename unsigned_integer_type>
  sha1<my_count_type>::sha1(unsigned_integer_type u)
  {
    process_data(u);
  }

  template <typename my_count_type>
  sha1<my_count_type>::sha1(const sha1& other) : crypto_hash_base    (other),
                                                 message_length_total(other.message_length_total),
                                                 message_hash        (other.message_hash),
                                                 message_block       (other.message_block)
  {
  }

  template <typename my_count_type>
  sha1<my_count_type>& sha1<my_count_type>::operator=(const sha1& other)
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
  void sha1<my_count_type>::process_data(const std::uint8_t* data_bytes, count_type message_length)
  {
    if(the_result_is_finalized) { reset(); }

    while(message_length != static_cast<count_type>(0U))
    {
      message_block[message_block_index] = *data_bytes;

      ++message_block_index;

      ++message_length_total;

      if(message_block_index == sha1_blocksize)
      {
        perform_algorithm();

        message_block_index = static_cast<std::uint_fast8_t>(0U);
      }

      ++data_bytes;
      --message_length;
    }
  }

  template<typename my_count_type>
  template<typename unsigned_integer_type>
  void sha1<my_count_type>::process_data(unsigned_integer_type u)
  {
    static_assert(   ( std::numeric_limits<unsigned_integer_type>::is_specialized == true)
                  && ( std::numeric_limits<unsigned_integer_type>::is_integer     == true)
                  && ( std::numeric_limits<unsigned_integer_type>::is_signed      == false)
                  && ( std::numeric_limits<unsigned_integer_type>::radix          == 2)
                  && ((std::numeric_limits<unsigned_integer_type>::digits % 8)    == 0),
                  "the template count type must be an unsigned integer with radix 2, having a multiple of 8 bits");

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
  void sha1<my_count_type>::perform_algorithm()
  {
    // Apply the hash algorithm to a full data block.

    const std::array<std::uint32_t, 4> constants =
    {{
      UINT32_C(0x5A827999),
      UINT32_C(0x6ED9EBA1),
      UINT32_C(0x8F1BBCDC),
      UINT32_C(0xCA62C1D6)
    }};

    typedef std::uint32_t(*function_type)(const std::uint32_t*);

    const std::array<function_type, 4U> functions =
    {{
      [](const std::uint32_t* hash_ptr) -> std::uint32_t
      {
        return (std::uint32_t(hash_ptr[1U] & hash_ptr[2U]) | std::uint32_t(std::uint32_t(~hash_ptr[1U]) & hash_ptr[3U]));
      },
      [](const std::uint32_t* hash_ptr) -> std::uint32_t
      {
        return std::uint32_t(std::uint32_t(hash_ptr[1U] ^ hash_ptr[2U]) ^ hash_ptr[3U]);
      },
      [](const std::uint32_t* hash_ptr) -> std::uint32_t
      {
        return (std::uint32_t(hash_ptr[1U] & hash_ptr[2U]) | std::uint32_t(hash_ptr[1U] & hash_ptr[3U]) | std::uint32_t(hash_ptr[2U] & hash_ptr[3U]));
      },
      [](const std::uint32_t* hash_ptr) -> std::uint32_t
      {
        return (std::uint32_t(hash_ptr[1U] ^ hash_ptr[2U]) ^ hash_ptr[3U]);
      }
    }};

    transform_block_type transform_block;

    convert_uint8_input_to_uint32_output_reverse(message_block.data(),
                                                 message_block.data() + sha1_blocksize,
                                                 transform_block.data());

    result_type_as_dwords hash_tmp = message_hash;

    std::uint_fast8_t loop_index = static_cast<std::uint_fast8_t>(0U);

    for(std::uint_fast8_t loop_counter = static_cast<std::uint_fast8_t>(0U); loop_counter < static_cast<std::uint_fast8_t>(80U); ++loop_counter)
    {
      if(loop_counter >= static_cast<std::uint_fast8_t>(16U))
      {
        const std::uint32_t the_dword =   transform_block[static_cast<std::uint_fast8_t>(static_cast<std::uint_fast8_t>(loop_counter + 13U) & static_cast<std::uint_fast8_t>(0x0FU))]
                                        ^ transform_block[static_cast<std::uint_fast8_t>(static_cast<std::uint_fast8_t>(loop_counter +  8U) & static_cast<std::uint_fast8_t>(0x0FU))]
                                        ^ transform_block[static_cast<std::uint_fast8_t>(static_cast<std::uint_fast8_t>(loop_counter +  2U) & static_cast<std::uint_fast8_t>(0x0FU))]
                                        ^ transform_block[static_cast<std::uint_fast8_t>(                               loop_counter        & static_cast<std::uint_fast8_t>(0x0FU))];

        transform_block[static_cast<std::uint_fast8_t>(loop_counter & static_cast<std::uint_fast8_t>(0x0FU))] = circular_shift<1U>(the_dword);

        if     (loop_counter == static_cast<std::uint_fast8_t>(20U)) { loop_index = static_cast<std::uint_fast8_t>(1U); }
        else if(loop_counter == static_cast<std::uint_fast8_t>(40U)) { loop_index = static_cast<std::uint_fast8_t>(2U); }
        else if(loop_counter == static_cast<std::uint_fast8_t>(60U)) { loop_index = static_cast<std::uint_fast8_t>(3U); }
      }

      const std::uint32_t tmp32 =   circular_shift<5U>(hash_tmp[0U])
                                  + functions[loop_index](hash_tmp.data())
                                  + hash_tmp[4U]
                                  + transform_block[static_cast<std::uint_fast8_t>(loop_counter & static_cast<std::uint_fast8_t>(0x0FU))]
                                  + constants[loop_index];

      hash_tmp[4U] = hash_tmp[3U];
      hash_tmp[3U] = hash_tmp[2U];
      hash_tmp[2U] = circular_shift<30U>(hash_tmp[1U]);
      hash_tmp[1U] = hash_tmp[0U];
      hash_tmp[0U] = tmp32;
    }

    // Update the hash state with the transformation results.
    std::transform(message_hash.cbegin     (),
                   message_hash.cend       (),
                   hash_tmp.cbegin         (),
                   message_hash.begin      (),
                   std::plus<std::uint32_t>());
  }

  template <typename my_count_type>
  void sha1<my_count_type>::finalize()
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
    if(message_block_index > static_cast<std::uint_fast8_t>(sha1_blocksize - 8U))
    {
      perform_algorithm();

      message_block.fill(static_cast<std::uint8_t>(0U));
    }

    // Encode the number of bits. Simultaneously convert the number of bytes
    // to the number of bits by performing a left-shift of 3 on the byte-array.
    // The sha1 stores the 8 bytes of the bit counter in reverse order,
    // with the lowest byte being stored at the highest position of the buffer
    std::uint_fast8_t carry = static_cast<std::uint_fast8_t>(0U);

    std::for_each(message_block.rbegin(),
                  message_block.rbegin() + 8U,
                  [&carry, this](std::uint8_t& the_byte)
                  {
                    const std::uint_least16_t the_word = static_cast<std::uint_least16_t>(this->message_length_total) << 3;

                    the_byte = static_cast<std::uint8_t>(the_word | carry);

                    (this->message_length_total) >>= 8;

                    carry = static_cast<std::uint_fast8_t>(the_word >> 8) & static_cast<std::uint_fast8_t>(0x07U);
                  });

    perform_algorithm();

    the_result_is_finalized = true;
  }

  template<typename my_count_type>
  void sha1<my_count_type>::reset()
  {
    message_hash[0U] = UINT32_C(0x67452301);
    message_hash[1U] = UINT32_C(0xEFCDAB89);
    message_hash[2U] = UINT32_C(0x98BADCFE);
    message_hash[3U] = UINT32_C(0x10325476);
    message_hash[4U] = UINT32_C(0xC3D2E1F0);

    the_result_is_finalized = false;
    message_length_total    = static_cast<count_type>(0U);
    message_block_index     = static_cast<std::uint_fast8_t>(0U);
  }

  template<typename my_count_type>
  typename sha1<my_count_type>::result_type_as_bytes sha1<my_count_type>::get_result_as_bytes_and_finalize_the_state()
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
  typename sha1<my_count_type>::result_type_as_bytes sha1<my_count_type>::get_result_as_bytes_and_nochange_the_state() const
  {
    // Make a local copy of the hash object.
    sha1 other(*this);

    // Finalize the local copy of the hash object,
    // and return the final result from the copied object.
    return other.get_result_as_bytes_and_finalize_the_state();
  }

  template<typename my_count_type>
  typename sha1<my_count_type>::result_type_as_dwords sha1<my_count_type>::get_result_as_dwords_and_finalize_the_state()
  {
    if(!the_result_is_finalized) { finalize(); }

    return message_hash;
  }

  template<typename my_count_type>
  typename sha1<my_count_type>::result_type_as_dwords sha1<my_count_type>::get_result_as_dwords_and_nochange_the_state() const
  {
    // Make a local copy of the hash object.
    sha1 other(*this);

    // Finalize the local copy of the hash object,
    // and return the final result from the copied object.
    other.finalize();

    return other.message_hash;
  }

  template<typename my_count_type>
  typename sha1<my_count_type>::result_type_as_chars sha1<my_count_type>::get_result_as_chars_and_finalize_the_state()
  {
    // Get the result of the hash object as a byte array.
    const result_type_as_bytes the_result_as_bytes = get_result_as_bytes_and_finalize_the_state();

    result_type_as_chars the_result_as_chars;

    // Conver the result as a byte array to a character array.
    convert_uint8_input_to_char8_output(the_result_as_bytes.data(),
                                        the_result_as_bytes.data() + the_result_as_bytes.size(),
                                        the_result_as_chars.data());

    // Obtain the correct byte order for displaying the sha1 string in the usual fashion.
    for(std::uint_fast8_t i = static_cast<std::uint_fast8_t>(0U); i < static_cast<std::uint_fast8_t>(the_result_as_chars.size()); i += 8U)
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
  typename sha1<my_count_type>::result_type_as_chars sha1<my_count_type>::get_result_as_chars_and_nochange_the_state() const
  {
    // Make a local copy of the hash object.
    sha1 temp_sha1(*this);

    // Finalize the local copy of the hash object,
    // and return the final result from the copied object.
    return temp_sha1.get_result_as_chars_and_finalize_the_state();
  }

#endif // _SHA1_2013_09_03_H_
