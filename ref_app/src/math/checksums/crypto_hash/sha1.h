
///////////////////////////////////////////////////////////////////////////////
//  Copyright Arwed Steuer 2013.
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
// This work has been created by Arwed Steuer.
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

#ifndef SHA1_H_INCLUDED
#define SHA1_H_INCLUDED

#include <array>
#include <functional>
#include "crypto_hash_base.h"

template <typename sha1_count_type>
class sha1 : public crypto_hash_base
{
public:
  typedef sha1_count_type                count_type;
  typedef std::array<std::uint8_t,  20U> result_type_as_bytes;
  typedef std::array<char,          40U> result_type_as_chars;
  typedef std::array<std::uint32_t,  5U> result_type_as_dwords;

  static_assert(   ( std::numeric_limits<count_type>::is_specialized == true)
                && ( std::numeric_limits<count_type>::is_integer     == true)
                && ( std::numeric_limits<count_type>::is_signed      == false)
                && ( std::numeric_limits<count_type>::radix          == 2)
                && ((std::numeric_limits<count_type>::digits % 8)    == 0),
                "the count type must be an unsigned integer type with radix 2, having a multiple of 8 bits");

  sha1();
  sha1(const std::uint8_t* data_stream, const count_type& length_message);
  sha1(const char*       string_stream, const count_type& length_message);
  //template<typename unsigned_integer_type> sha1(unsigned_integer_type u);
  sha1(const sha1& other);
  sha1& operator=(const sha1& other);

  result_type_as_bytes get_result_as_bytes_and_finalize_the_state ();
  result_type_as_bytes get_result_as_bytes_and_nochange_the_state () const;

  result_type_as_dwords get_result_as_dwords_and_finalize_the_state();
  result_type_as_dwords get_result_as_dwords_and_nochange_the_state() const;

  result_type_as_chars get_result_as_chars_and_finalize_the_state();
  result_type_as_chars get_result_as_chars_and_nochange_the_state() const;

  void process_data(const std::uint8_t* data_stream, const count_type& length_message);

  void process_data(const char* string_stream, const count_type& length_message)
  {
    process_data(static_cast<const std::uint8_t*>(static_cast<const void*>(string_stream)), length_message);
  }

  //template<typename unsigned_integer_type> void process_data(unsigned_integer_type u);

private:
  std::uint_fast8_t             index_block_message;
  count_type                    padding_length;
  std::array<std::uint32_t, 5U> hash_message;
  std::array<std::uint8_t, 64U> block_message;

  void perform_algorithm();
  void finalize();
  void reset();

  template<const std::uint_fast8_t digits_shift>
  static std::uint32_t circular_shift(const std::uint32_t& shift_32word)
  {
    return (shift_32word << digits_shift) | (shift_32word >> (static_cast<std::uint_fast8_t>(32U) - digits_shift));
  }
};

////IMPLEMENTATION////

template <typename sha1_count_type>
sha1<sha1_count_type>::sha1()
{
  reset();
}

template <typename sha1_count_type>
sha1<sha1_count_type>::sha1(const std::uint8_t* data_stream,
                            const sha1_count_type& length_message)
{
  reset();

  process_data(data_stream, length_message);
}

template <typename sha1_count_type>
sha1<sha1_count_type>::sha1(const char* string_stream,
                            const sha1_count_type& length_message)
{
  reset();

  process_data(string_stream, length_message);
}

template <typename sha1_count_type>
sha1<sha1_count_type>::sha1(const sha1& other) : crypto_hash_base   (other),
                                                 index_block_message(other.index_block_message),
                                                 padding_length     (other.padding_length),
                                                 hash_message       (other.hash_message),
                                                 block_message      (other.block_message)
{
}

template <typename sha1_count_type>
sha1<sha1_count_type>& sha1<sha1_count_type>::operator=(const sha1& other)
{
  if(this != &other)
  {
    static_cast<void>(crypto_hash_base::operator=(other));

    index_block_message = other.index_block_message;
    padding_length      = other.padding_length;
    hash_message        = other.hash_message;
    block_message       = other.block_message;
  }

  return *this;
}

template <typename sha1_count_type>
void sha1<sha1_count_type>::process_data(const std::uint8_t* message_hash, const sha1_count_type& length_message)
{
  if(the_result_is_finalized) { reset(); }

  count_type the_message_length = length_message;

  while(the_message_length != static_cast<count_type>(0U))
  {
    block_message[index_block_message] = *message_hash;

    ++index_block_message;

    ++padding_length;

    if(index_block_message == static_cast<std::uint_fast8_t>(64U))
    {
      perform_algorithm();
    }

    ++message_hash;
    --the_message_length;
  }
}

/*
template <typename sha1_count_type>
void sha1<sha1_count_type>::perform_algorithm()
{
  std::uint_fast8_t loop_counter;
  std::uint32_t temporary_32word;

  std::array<std::uint32_t, 80U> sequence_32word;
  std::array<std::uint32_t,  5U> buffer_32word;

  for(loop_counter = static_cast<std::uint_fast8_t>(0U); loop_counter < static_cast<std::uint_fast8_t>(16U); loop_counter++)
  {
    sequence_32word[loop_counter]  = (  (static_cast<std::uint32_t>(block_message[(loop_counter * 4U)                                     ]) << 24U)
                                      | (static_cast<std::uint32_t>(block_message[(loop_counter * 4U) + static_cast<std::uint_fast8_t>(1U)]) << 16U)
                                      | (static_cast<std::uint32_t>(block_message[(loop_counter * 4U) + static_cast<std::uint_fast8_t>(2U)]) <<  8U)
                                      | (static_cast<std::uint32_t>(block_message[(loop_counter * 4U) + static_cast<std::uint_fast8_t>(3U)]) <<  0U));
  }

  for(loop_counter = static_cast<std::uint_fast8_t>(16U); loop_counter < static_cast<std::uint_fast8_t>(80U); loop_counter++)
  {
    const std::uint32_t word_shift = (sequence_32word[loop_counter - static_cast<std::uint_fast8_t>( 3U)] ^
                                      sequence_32word[loop_counter - static_cast<std::uint_fast8_t>( 8U)] ^
                                      sequence_32word[loop_counter - static_cast<std::uint_fast8_t>(14U)] ^
                                      sequence_32word[loop_counter - static_cast<std::uint_fast8_t>(16U)]);

    sequence_32word[loop_counter] = circular_shift<1U>(word_shift);
  }

  buffer_32word = hash_message;

  for(loop_counter = static_cast<std::uint_fast8_t>(0U); loop_counter < static_cast<std::uint_fast8_t>(80U); loop_counter++)
  {
    temporary_32word =    circular_shift<5U>(buffer_32word[0U])
                        + functions(loop_counter, buffer_32word[1U], buffer_32word[2U], buffer_32word[3U])
                        + buffer_32word[4U]
                        + sequence_32word[loop_counter]
                        + constants(loop_counter);

    buffer_32word[4U] = buffer_32word[3U];
    buffer_32word[3U] = buffer_32word[2U];
    buffer_32word[2U] = circular_shift<30>(buffer_32word[1U]);
    buffer_32word[1U] = buffer_32word[0U];
    buffer_32word[0U] = temporary_32word;
  }

  std::transform(hash_message.cbegin(),
                 hash_message.cend(),
                 buffer_32word.cbegin(),
                 hash_message.begin(),
                 std::plus<std::uint32_t>());

  index_block_message = static_cast<std::uint_fast8_t>(0U);
}
*/

template <typename sha1_count_type>
void sha1<sha1_count_type>::perform_algorithm()
{
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
    [](const std::uint32_t* my_buffer_32word) -> std::uint32_t
    {
      return (std::uint32_t(my_buffer_32word[1U] & my_buffer_32word[2U]) | std::uint32_t(std::uint32_t(~my_buffer_32word[1U]) & my_buffer_32word[3U]));
    },
    [](const std::uint32_t* my_buffer_32word) -> std::uint32_t
    {
      return std::uint32_t(std::uint32_t(my_buffer_32word[1U] ^ my_buffer_32word[2U]) ^ my_buffer_32word[3U]);
    },
    [](const std::uint32_t* my_buffer_32word) -> std::uint32_t
    {
      return (std::uint32_t(my_buffer_32word[1U] & my_buffer_32word[2U]) | std::uint32_t(my_buffer_32word[1U] & my_buffer_32word[3U]) | std::uint32_t(my_buffer_32word[2U] & my_buffer_32word[3U]));
    },
    [](const std::uint32_t* my_buffer_32word) -> std::uint32_t
    {
      return (std::uint32_t(my_buffer_32word[1U] ^ my_buffer_32word[2U]) ^ my_buffer_32word[3U]);
    }
  }};

  std::array<std::uint32_t, 16U> sequence_32word;

  for(std::uint_fast8_t loop_counter = static_cast<std::uint_fast8_t>(0U); loop_counter < static_cast<std::uint_fast8_t>(16U); loop_counter++)
  {
    sequence_32word[loop_counter]  = (  (static_cast<std::uint32_t>(block_message[(loop_counter * 4U)                                     ]) << 24U)
                                      | (static_cast<std::uint32_t>(block_message[(loop_counter * 4U) + static_cast<std::uint_fast8_t>(1U)]) << 16U)
                                      | (static_cast<std::uint32_t>(block_message[(loop_counter * 4U) + static_cast<std::uint_fast8_t>(2U)]) <<  8U)
                                      | (static_cast<std::uint32_t>(block_message[(loop_counter * 4U) + static_cast<std::uint_fast8_t>(3U)]) <<  0U));
  }

  std::array<std::uint32_t, 5U> buffer_32word = hash_message;

  for(std::uint_fast8_t loop_counter = static_cast<std::uint_fast8_t>(0U); loop_counter < static_cast<std::uint_fast8_t>(80U); ++loop_counter)
  {
    const std::uint_fast8_t counter_loop = loop_counter & static_cast<std::uint_fast8_t>(0x0FU);

    if(loop_counter >= static_cast<std::uint_fast8_t>(16U))
    {
      sequence_32word[counter_loop] = circular_shift<1U>(sequence_32word[(counter_loop + static_cast<std::uint_fast8_t>(13U)) & static_cast<std::uint_fast8_t>(0x0FU)] ^
                                                         sequence_32word[(counter_loop + static_cast<std::uint_fast8_t>( 8U)) & static_cast<std::uint_fast8_t>(0x0FU)] ^
                                                         sequence_32word[(counter_loop + static_cast<std::uint_fast8_t>( 2U)) & static_cast<std::uint_fast8_t>(0x0FU)] ^
                                                         sequence_32word[(counter_loop                                      )                                        ]);
    }

    const std::uint_fast8_t loop_index = static_cast<std::uint_fast8_t>(loop_counter / static_cast<std::uint_fast8_t>(20U));

    const std::uint32_t temporary_32word =   circular_shift<5U>(buffer_32word[0U])
                                           + functions[loop_index](buffer_32word.data())
                                           + buffer_32word[4U]
                                           + sequence_32word[counter_loop]
                                           + constants[loop_index];

    buffer_32word[4U] = buffer_32word[3U];
    buffer_32word[3U] = buffer_32word[2U];
    buffer_32word[2U] = circular_shift<30U>(buffer_32word[1U]);
    buffer_32word[1U] = buffer_32word[0U];
    buffer_32word[0U] = temporary_32word;
  }

  std::transform(hash_message.cbegin     (),
                 hash_message.cend       (),
                 buffer_32word.cbegin    (),
                 hash_message.begin      (),
                 std::plus<std::uint32_t>());

  index_block_message = static_cast<std::uint_fast8_t>(0U);
}

template <typename sha1_count_type>
void sha1<sha1_count_type>::finalize()
{
  if (index_block_message > static_cast<std::uint_fast8_t>(55U))
  {
    block_message[index_block_message] = static_cast<std::uint8_t>(0x80U);

    ++index_block_message;

    std::fill(block_message.begin() + index_block_message,
              block_message.end(),
              static_cast<std::uint8_t>(0U));

    perform_algorithm();

    std::fill(block_message.begin(),
              block_message.end(),
              static_cast<std::uint8_t>(0U));
  }
  else
  {
    std::fill(block_message.begin() + index_block_message,
              block_message.end(),
              static_cast<std::uint8_t>(0U));

    block_message[index_block_message] = static_cast<std::uint8_t>(0x80U);

    ++index_block_message;
  }

  // Encode the number of bits. Simultaneously convert the number of bytes
  // to the number of bits by performing a left-shift of 3 on the byte-array.
  // The sha1 stores the 8 bytes of the bit counter in reverse order,
  // with the lowest byte being stored at the end of the buffer
  std::uint_least8_t carry = static_cast<std::uint_least8_t>(0U);
  std::int_least8_t   index = static_cast<std::int_least8_t>(0);

  count_type padding_length_tmp = padding_length;

  for( ; index < static_cast<std::int_least8_t>(std::numeric_limits<count_type>::digits / 8); ++index)
  {
    const std::uint_least16_t the_word = static_cast<std::uint_least16_t>(padding_length_tmp) << 3;

    padding_length_tmp >>= (static_cast<std::int_least8_t>(index + 1) * 8);

    *(block_message.rbegin() + index) = static_cast<std::uint8_t>(the_word | carry);

    carry = static_cast<std::uint_least8_t>(the_word >> 8);
  }

  if(index < static_cast<std::int_least8_t>(8))
  {
    *(block_message.rbegin() + index) = static_cast<std::uint8_t>(carry);
  }

  perform_algorithm();

  the_result_is_finalized = true;
}

template <typename sha1_count_type>
typename sha1<sha1_count_type>::result_type_as_bytes
sha1<sha1_count_type>::get_result_as_bytes_and_finalize_the_state()
{
  if(!the_result_is_finalized) { finalize(); }

  std::array<std::uint8_t, 20U> result;

  convert_uint32_input_to_uint8_output(hash_message.data(),
                                       hash_message.data() + hash_message.size(),
                                       result.data());

  return result;
}

template <typename sha1_count_type>
typename sha1<sha1_count_type>::result_type_as_bytes
sha1<sha1_count_type>::get_result_as_bytes_and_nochange_the_state() const
{
  sha1 other(*this);

  return other.get_result_as_bytes_and_finalize_the_state();
}

template <typename sha1_count_type>
typename sha1<sha1_count_type>::result_type_as_dwords
sha1<sha1_count_type>::get_result_as_dwords_and_finalize_the_state()
{
  if(!the_result_is_finalized) { finalize(); }

  return hash_message;
}

template <typename sha1_count_type>
typename sha1<sha1_count_type>::result_type_as_dwords
sha1<sha1_count_type>::get_result_as_dwords_and_nochange_the_state() const
{
  sha1 other(*this);

  return other.get_result_as_dwords_and_finalize_the_state();
}

template<typename sha1_count_type>
typename sha1<sha1_count_type>::result_type_as_chars
sha1<sha1_count_type>::get_result_as_chars_and_finalize_the_state()
{
  // Get the result of the sha1 as a byte array.
  const result_type_as_bytes the_result_as_bytes = get_result_as_bytes_and_finalize_the_state();

  result_type_as_chars the_result_as_chars;

  // Conver the result as a byte array to a character array.
  convert_uint8_input_to_char8_output(the_result_as_bytes.data(),
                                      the_result_as_bytes.data() + the_result_as_bytes.size(),
                                      the_result_as_chars.data());

  return the_result_as_chars;
}

template<typename sha1_count_type>
typename sha1<sha1_count_type>::result_type_as_chars
sha1<sha1_count_type>::get_result_as_chars_and_nochange_the_state() const
{
  // Make a local copy of the message digest.
  sha1 temp_sha1(*this);

  // Finalize the local copy of the message digest,
  // and return the final result from the copied object.
  return temp_sha1.get_result_as_chars_and_finalize_the_state();
}

template <typename sha1_count_type>
void sha1<sha1_count_type>::reset()
{
  block_message.fill(static_cast<std::uint8_t>(0U));

  hash_message[0U] = UINT32_C(0x67452301);
  hash_message[1U] = UINT32_C(0xEFCDAB89);
  hash_message[2U] = UINT32_C(0x98BADCFE);
  hash_message[3U] = UINT32_C(0x10325476);
  hash_message[4U] = UINT32_C(0xC3D2E1F0);

  padding_length          =     static_cast<std::uint64_t>(0U);
  index_block_message     = static_cast<std::uint_fast8_t>(0U);
  the_result_is_finalized =                              false;
}

#endif // SHA1_H_INCLUDED
