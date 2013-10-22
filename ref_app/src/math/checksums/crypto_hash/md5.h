
///////////////////////////////////////////////////////////////////////////////
//  Copyright Arwed Steuer 2013.
//  Copyright Christopher Kormanyos 2012 - 2013.
//
// \license LGPLv3
// md5 is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// md5 is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
// GNU Lesser Public License for more details.
// You should have received a copy of the GNU Lesser Public License
// along with md5. If not, see <http://www.gnu.org/licenses/>.
//

///////////////////////////////////////////////////////////////////////////////
//
// This work has been created by Arwed Steuer and Christopher Kormanyos.
// This work is an implementation of md5 that has been specifically
// designed for C++. The implementation places particular
// emphasis on portability to microcontroller platforms.
//
// This work has been derived from:
// "RSA Data Security, Inc. MD5 Message-Digest Algorithm".
// The original license notices from RSA Data Security, Inc.
// follow below.
//
// Copyright (C) 1991-2, RSA Data Security, Inc. Created 1991. All
// rights reserved.
//
// License to copy and use this software is granted provided that it
// is identified as the "RSA Data Security, Inc. MD5 Message-Digest
// Algorithm" in all material mentioning or referencing this software
// or this function.
//
// License is also granted to make and use derivative works provided
// that such works are identified as "derived from the RSA Data
// Security, Inc. MD5 Message-Digest Algorithm" in all material
// mentioning or referencing the derived work.
//
// RSA Data Security, Inc. makes no representations concerning either
// the merchantability of this software or the suitability of this
// software for any particular purpose. It is provided "as is"
// without express or implied warranty of any kind.
//
// These notices must be retained in any copies of any part of this
// documentation and/or software.
///////////////////////////////////////////////////////////////////////////////

#ifndef _MD5_2012_01_13_H_
  #define _MD5_2012_01_13_H_

  #include <array>
  #include <cstddef>
  #include <functional>
  #include "crypto_hash_base.h"

  template<typename my_count_type>
  class md5 : public crypto_hash_base
  {
  public:
    typedef my_count_type                  count_type;
    typedef std::array<std::uint8_t,  16U> result_type_as_bytes;
    typedef std::array<char,          32U> result_type_as_chars;
    typedef std::array<std::uint32_t,  4U> result_type_as_dwords;

    static_assert(   ( std::numeric_limits<count_type>::is_specialized == true)
                  && ( std::numeric_limits<count_type>::is_integer     == true)
                  && ( std::numeric_limits<count_type>::is_signed      == false)
                  && ( std::numeric_limits<count_type>::radix          == 2)
                  && ((std::numeric_limits<count_type>::digits % 8)    == 0),
                  "the template count type must be an unsigned integer with radix 2, having a multiple of 8 bits");

    md5();
    md5(const std::uint8_t* data_bytes, count_type message_length);
    md5(const char*         data_chars, count_type message_length);
    template<typename unsigned_integer_type> md5(unsigned_integer_type u);
    md5(const md5& other);
    md5& operator=(const md5& other);

    void process_data(const std::uint8_t* byte_data, count_type message_length);

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
    static const std::uint_fast8_t md5_blocksize = 64U;

    static_assert(md5_blocksize == static_cast<std::uint_fast8_t>(64U),
                  "the block size must exactly equal 64");

    typedef std::array<std::uint8_t,  md5_blocksize>      message_block_type;
    typedef std::array<std::uint32_t, md5_blocksize / 4U> transform_block_type;

    count_type            message_length_total;
    result_type_as_dwords message_hash;
    message_block_type    message_block;

    void perform_algorithm();
    void finalize();
    void reset();

    // Constants for the md5 transform routine.
    static const std::uint_fast8_t S11 = UINT8_C( 7);
    static const std::uint_fast8_t S12 = UINT8_C(12);
    static const std::uint_fast8_t S13 = UINT8_C(17);
    static const std::uint_fast8_t S14 = UINT8_C(22);
    static const std::uint_fast8_t S21 = UINT8_C( 5);
    static const std::uint_fast8_t S22 = UINT8_C( 9);
    static const std::uint_fast8_t S23 = UINT8_C(14);
    static const std::uint_fast8_t S24 = UINT8_C(20);
    static const std::uint_fast8_t S31 = UINT8_C( 4);
    static const std::uint_fast8_t S32 = UINT8_C(11);
    static const std::uint_fast8_t S33 = UINT8_C(16);
    static const std::uint_fast8_t S34 = UINT8_C(23);
    static const std::uint_fast8_t S41 = UINT8_C( 6);
    static const std::uint_fast8_t S42 = UINT8_C(10);
    static const std::uint_fast8_t S43 = UINT8_C(15);
    static const std::uint_fast8_t S44 = UINT8_C(21);

    // FF, GG, HH, and II are the transformations for rounds 1, 2, 3, and 4 of the md5.

    template<const std::uint_fast8_t my_s, const std::uint32_t my_ac>
    static void transformation_ff(std::uint32_t& a, const std::uint32_t& b, const std::uint32_t& c, const std::uint32_t& d, const std::uint32_t& x)
    {
      const std::uint32_t permutation_f = static_cast<std::uint32_t>(b & c) | static_cast<std::uint32_t>(static_cast<std::uint32_t>(~b) & d);

      a = static_cast<std::uint32_t>(circular_shift<my_s>(static_cast<std::uint32_t>(a + permutation_f) + static_cast<std::uint32_t>(x + my_ac)) + b);
    }

    template<const std::uint_fast8_t my_s, const std::uint32_t my_ac>
    static void transformation_gg(std::uint32_t& a, const std::uint32_t& b, const std::uint32_t& c, const std::uint32_t& d, const std::uint32_t& x)
    {
      const std::uint32_t permutation_g = static_cast<std::uint32_t>(b & d) | static_cast<std::uint32_t>(c & static_cast<std::uint32_t>(~d));

      a = static_cast<std::uint32_t>(circular_shift<my_s>(static_cast<std::uint32_t>(a + permutation_g) + static_cast<std::uint32_t>(x + my_ac)) + b);
    }

    template<const std::uint_fast8_t my_s, const std::uint32_t my_ac>
    static void transformation_hh(std::uint32_t& a, const std::uint32_t& b, const std::uint32_t& c, const std::uint32_t& d, const std::uint32_t& x)
    {
      const std::uint32_t permutation_h = static_cast<std::uint32_t>(b ^ c) ^ d;

      a = static_cast<std::uint32_t>(circular_shift<my_s>(static_cast<std::uint32_t>(a + permutation_h) + static_cast<std::uint32_t>(x + my_ac)) + b);
    }

    template<const std::uint_fast8_t my_s, const std::uint32_t my_ac>
    static void transformation_ii(std::uint32_t& a, const std::uint32_t& b, const std::uint32_t& c, const std::uint32_t& d, const std::uint32_t& x)
    {
      const std::uint32_t permutation_i = c ^ static_cast<std::uint32_t>(b | static_cast<std::uint32_t>(~d));

      a = static_cast<std::uint32_t>(circular_shift<my_s>(static_cast<std::uint32_t>(a + permutation_i) + static_cast<std::uint32_t>(x + my_ac)) + b);
    }
  };

  template<typename my_count_type>
  md5<my_count_type>::md5()
  {
  }

  template<typename my_count_type>
  md5<my_count_type>::md5(const std::uint8_t* data_bytes, count_type message_length)
  {
    process_data(data_bytes, message_length);
  }

  template<typename my_count_type>
  md5<my_count_type>::md5(const char* data_chars, count_type message_length)
  {
    process_data(static_cast<const std::uint8_t*>(static_cast<const void*>(data_chars)), message_length);
  }

  template<typename my_count_type>
  template<typename unsigned_integer_type>
  md5<my_count_type>::md5(unsigned_integer_type u)
  {
    process_data(u);
  }

  template<typename my_count_type>
  md5<my_count_type>::md5(const md5& other) : crypto_hash_base    (other),
                                              message_length_total(other.message_length_total),
                                              message_hash        (other.message_hash),
                                              message_block       (other.message_block)
  {
  }

  template<typename my_count_type>
  md5<my_count_type>& md5<my_count_type>::operator=(const md5& other)
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

  template<typename my_count_type>
  void md5<my_count_type>::process_data(const std::uint8_t* data_bytes, count_type message_length)
  {
    if(the_result_is_finalized) { reset(); }

    while(message_length != static_cast<count_type>(0U))
    {
      message_block[message_block_index] = *data_bytes;

      ++message_block_index;

      ++message_length_total;

      if(message_block_index == md5_blocksize)
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
  void md5<my_count_type>::process_data(unsigned_integer_type u)
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

  template<typename my_count_type>
  void md5<my_count_type>::perform_algorithm()
  {
    // Apply the hash algorithm to a full data block.

    transform_block_type transform_block;

    convert_uint8_input_to_uint32_output(message_block.data(),
                                         message_block.data() + md5_blocksize,
                                         transform_block.data());

    result_type_as_dwords hash_tmp = message_hash;

    // Perform transformation round 1.
    transformation_ff<S11, UINT32_C(0xD76AA478)>(hash_tmp[0U], hash_tmp[1U], hash_tmp[2U], hash_tmp[3U], transform_block[ 0U]); //  1
    transformation_ff<S12, UINT32_C(0xE8C7B756)>(hash_tmp[3U], hash_tmp[0U], hash_tmp[1U], hash_tmp[2U], transform_block[ 1U]); //  2
    transformation_ff<S13, UINT32_C(0x242070DB)>(hash_tmp[2U], hash_tmp[3U], hash_tmp[0U], hash_tmp[1U], transform_block[ 2U]); //  3
    transformation_ff<S14, UINT32_C(0xC1BDCEEE)>(hash_tmp[1U], hash_tmp[2U], hash_tmp[3U], hash_tmp[0U], transform_block[ 3U]); //  4
    transformation_ff<S11, UINT32_C(0xF57C0FAF)>(hash_tmp[0U], hash_tmp[1U], hash_tmp[2U], hash_tmp[3U], transform_block[ 4U]); //  5
    transformation_ff<S12, UINT32_C(0x4787C62A)>(hash_tmp[3U], hash_tmp[0U], hash_tmp[1U], hash_tmp[2U], transform_block[ 5U]); //  6
    transformation_ff<S13, UINT32_C(0xA8304613)>(hash_tmp[2U], hash_tmp[3U], hash_tmp[0U], hash_tmp[1U], transform_block[ 6U]); //  7
    transformation_ff<S14, UINT32_C(0xFD469501)>(hash_tmp[1U], hash_tmp[2U], hash_tmp[3U], hash_tmp[0U], transform_block[ 7U]); //  8
    transformation_ff<S11, UINT32_C(0x698098D8)>(hash_tmp[0U], hash_tmp[1U], hash_tmp[2U], hash_tmp[3U], transform_block[ 8U]); //  9
    transformation_ff<S12, UINT32_C(0x8B44F7AF)>(hash_tmp[3U], hash_tmp[0U], hash_tmp[1U], hash_tmp[2U], transform_block[ 9U]); // 10
    transformation_ff<S13, UINT32_C(0xFFFF5BB1)>(hash_tmp[2U], hash_tmp[3U], hash_tmp[0U], hash_tmp[1U], transform_block[10U]); // 11
    transformation_ff<S14, UINT32_C(0x895CD7BE)>(hash_tmp[1U], hash_tmp[2U], hash_tmp[3U], hash_tmp[0U], transform_block[11U]); // 12
    transformation_ff<S11, UINT32_C(0x6B901122)>(hash_tmp[0U], hash_tmp[1U], hash_tmp[2U], hash_tmp[3U], transform_block[12U]); // 13
    transformation_ff<S12, UINT32_C(0xFD987193)>(hash_tmp[3U], hash_tmp[0U], hash_tmp[1U], hash_tmp[2U], transform_block[13U]); // 14
    transformation_ff<S13, UINT32_C(0xA679438E)>(hash_tmp[2U], hash_tmp[3U], hash_tmp[0U], hash_tmp[1U], transform_block[14U]); // 15
    transformation_ff<S14, UINT32_C(0x49B40821)>(hash_tmp[1U], hash_tmp[2U], hash_tmp[3U], hash_tmp[0U], transform_block[15U]); // 16

    // Perform transformation round 2.
    transformation_gg<S21, UINT32_C(0xF61E2562)>(hash_tmp[0U], hash_tmp[1U], hash_tmp[2U], hash_tmp[3U], transform_block[ 1U]); // 17
    transformation_gg<S22, UINT32_C(0xC040B340)>(hash_tmp[3U], hash_tmp[0U], hash_tmp[1U], hash_tmp[2U], transform_block[ 6U]); // 18
    transformation_gg<S23, UINT32_C(0x265E5A51)>(hash_tmp[2U], hash_tmp[3U], hash_tmp[0U], hash_tmp[1U], transform_block[11U]); // 19
    transformation_gg<S24, UINT32_C(0xE9B6C7AA)>(hash_tmp[1U], hash_tmp[2U], hash_tmp[3U], hash_tmp[0U], transform_block[ 0U]); // 20
    transformation_gg<S21, UINT32_C(0xD62F105D)>(hash_tmp[0U], hash_tmp[1U], hash_tmp[2U], hash_tmp[3U], transform_block[ 5U]); // 21
    transformation_gg<S22, UINT32_C(0x02441453)>(hash_tmp[3U], hash_tmp[0U], hash_tmp[1U], hash_tmp[2U], transform_block[10U]); // 22
    transformation_gg<S23, UINT32_C(0xD8A1E681)>(hash_tmp[2U], hash_tmp[3U], hash_tmp[0U], hash_tmp[1U], transform_block[15U]); // 23
    transformation_gg<S24, UINT32_C(0xE7D3FBC8)>(hash_tmp[1U], hash_tmp[2U], hash_tmp[3U], hash_tmp[0U], transform_block[ 4U]); // 24
    transformation_gg<S21, UINT32_C(0x21E1CDE6)>(hash_tmp[0U], hash_tmp[1U], hash_tmp[2U], hash_tmp[3U], transform_block[ 9U]); // 25
    transformation_gg<S22, UINT32_C(0xC33707D6)>(hash_tmp[3U], hash_tmp[0U], hash_tmp[1U], hash_tmp[2U], transform_block[14U]); // 26
    transformation_gg<S23, UINT32_C(0xF4D50D87)>(hash_tmp[2U], hash_tmp[3U], hash_tmp[0U], hash_tmp[1U], transform_block[ 3U]); // 27
    transformation_gg<S24, UINT32_C(0x455A14ED)>(hash_tmp[1U], hash_tmp[2U], hash_tmp[3U], hash_tmp[0U], transform_block[ 8U]); // 28
    transformation_gg<S21, UINT32_C(0xA9E3E905)>(hash_tmp[0U], hash_tmp[1U], hash_tmp[2U], hash_tmp[3U], transform_block[13U]); // 29
    transformation_gg<S22, UINT32_C(0xFCEFA3F8)>(hash_tmp[3U], hash_tmp[0U], hash_tmp[1U], hash_tmp[2U], transform_block[ 2U]); // 30
    transformation_gg<S23, UINT32_C(0x676F02D9)>(hash_tmp[2U], hash_tmp[3U], hash_tmp[0U], hash_tmp[1U], transform_block[ 7U]); // 31
    transformation_gg<S24, UINT32_C(0x8D2A4C8A)>(hash_tmp[1U], hash_tmp[2U], hash_tmp[3U], hash_tmp[0U], transform_block[12U]); // 32

    // Perform transformation round 3.
    transformation_hh<S31, UINT32_C(0xFFFA3942)>(hash_tmp[0U], hash_tmp[1U], hash_tmp[2U], hash_tmp[3U], transform_block[ 5U]); // 33
    transformation_hh<S32, UINT32_C(0x8771F681)>(hash_tmp[3U], hash_tmp[0U], hash_tmp[1U], hash_tmp[2U], transform_block[ 8U]); // 34
    transformation_hh<S33, UINT32_C(0x6D9D6122)>(hash_tmp[2U], hash_tmp[3U], hash_tmp[0U], hash_tmp[1U], transform_block[11U]); // 35
    transformation_hh<S34, UINT32_C(0xFDE5380C)>(hash_tmp[1U], hash_tmp[2U], hash_tmp[3U], hash_tmp[0U], transform_block[14U]); // 36
    transformation_hh<S31, UINT32_C(0xA4BEEA44)>(hash_tmp[0U], hash_tmp[1U], hash_tmp[2U], hash_tmp[3U], transform_block[ 1U]); // 37
    transformation_hh<S32, UINT32_C(0x4BDECFA9)>(hash_tmp[3U], hash_tmp[0U], hash_tmp[1U], hash_tmp[2U], transform_block[ 4U]); // 38
    transformation_hh<S33, UINT32_C(0xF6BB4B60)>(hash_tmp[2U], hash_tmp[3U], hash_tmp[0U], hash_tmp[1U], transform_block[ 7U]); // 39
    transformation_hh<S34, UINT32_C(0xBEBFBC70)>(hash_tmp[1U], hash_tmp[2U], hash_tmp[3U], hash_tmp[0U], transform_block[10U]); // 40
    transformation_hh<S31, UINT32_C(0x289B7EC6)>(hash_tmp[0U], hash_tmp[1U], hash_tmp[2U], hash_tmp[3U], transform_block[13U]); // 41
    transformation_hh<S32, UINT32_C(0xEAA127FA)>(hash_tmp[3U], hash_tmp[0U], hash_tmp[1U], hash_tmp[2U], transform_block[ 0U]); // 42
    transformation_hh<S33, UINT32_C(0xD4EF3085)>(hash_tmp[2U], hash_tmp[3U], hash_tmp[0U], hash_tmp[1U], transform_block[ 3U]); // 43
    transformation_hh<S34, UINT32_C(0x04881D05)>(hash_tmp[1U], hash_tmp[2U], hash_tmp[3U], hash_tmp[0U], transform_block[ 6U]); // 44
    transformation_hh<S31, UINT32_C(0xD9D4D039)>(hash_tmp[0U], hash_tmp[1U], hash_tmp[2U], hash_tmp[3U], transform_block[ 9U]); // 45
    transformation_hh<S32, UINT32_C(0xE6DB99E5)>(hash_tmp[3U], hash_tmp[0U], hash_tmp[1U], hash_tmp[2U], transform_block[12U]); // 46
    transformation_hh<S33, UINT32_C(0x1FA27CF8)>(hash_tmp[2U], hash_tmp[3U], hash_tmp[0U], hash_tmp[1U], transform_block[15U]); // 47
    transformation_hh<S34, UINT32_C(0xC4AC5665)>(hash_tmp[1U], hash_tmp[2U], hash_tmp[3U], hash_tmp[0U], transform_block[ 2U]); // 48

    // Perform transformation round 4.
    transformation_ii<S41, UINT32_C(0xF4292244)>(hash_tmp[0U], hash_tmp[1U], hash_tmp[2U], hash_tmp[3U], transform_block[ 0U]); // 49
    transformation_ii<S42, UINT32_C(0x432AFF97)>(hash_tmp[3U], hash_tmp[0U], hash_tmp[1U], hash_tmp[2U], transform_block[ 7U]); // 50
    transformation_ii<S43, UINT32_C(0xAB9423A7)>(hash_tmp[2U], hash_tmp[3U], hash_tmp[0U], hash_tmp[1U], transform_block[14U]); // 51
    transformation_ii<S44, UINT32_C(0xFC93A039)>(hash_tmp[1U], hash_tmp[2U], hash_tmp[3U], hash_tmp[0U], transform_block[ 5U]); // 52
    transformation_ii<S41, UINT32_C(0x655B59C3)>(hash_tmp[0U], hash_tmp[1U], hash_tmp[2U], hash_tmp[3U], transform_block[12U]); // 53
    transformation_ii<S42, UINT32_C(0x8F0CCC92)>(hash_tmp[3U], hash_tmp[0U], hash_tmp[1U], hash_tmp[2U], transform_block[ 3U]); // 54
    transformation_ii<S43, UINT32_C(0xFFEFF47D)>(hash_tmp[2U], hash_tmp[3U], hash_tmp[0U], hash_tmp[1U], transform_block[10U]); // 55
    transformation_ii<S44, UINT32_C(0x85845DD1)>(hash_tmp[1U], hash_tmp[2U], hash_tmp[3U], hash_tmp[0U], transform_block[ 1U]); // 56
    transformation_ii<S41, UINT32_C(0x6FA87E4F)>(hash_tmp[0U], hash_tmp[1U], hash_tmp[2U], hash_tmp[3U], transform_block[ 8U]); // 57
    transformation_ii<S42, UINT32_C(0xFE2CE6E0)>(hash_tmp[3U], hash_tmp[0U], hash_tmp[1U], hash_tmp[2U], transform_block[15U]); // 58
    transformation_ii<S43, UINT32_C(0xA3014314)>(hash_tmp[2U], hash_tmp[3U], hash_tmp[0U], hash_tmp[1U], transform_block[ 6U]); // 59
    transformation_ii<S44, UINT32_C(0x4E0811A1)>(hash_tmp[1U], hash_tmp[2U], hash_tmp[3U], hash_tmp[0U], transform_block[13U]); // 60
    transformation_ii<S41, UINT32_C(0xF7537E82)>(hash_tmp[0U], hash_tmp[1U], hash_tmp[2U], hash_tmp[3U], transform_block[ 4U]); // 61
    transformation_ii<S42, UINT32_C(0xBD3AF235)>(hash_tmp[3U], hash_tmp[0U], hash_tmp[1U], hash_tmp[2U], transform_block[11U]); // 62
    transformation_ii<S43, UINT32_C(0x2AD7D2BB)>(hash_tmp[2U], hash_tmp[3U], hash_tmp[0U], hash_tmp[1U], transform_block[ 2U]); // 63
    transformation_ii<S44, UINT32_C(0xEB86D391)>(hash_tmp[1U], hash_tmp[2U], hash_tmp[3U], hash_tmp[0U], transform_block[ 9U]); // 64

    // Update the hash state with the transformation results.
    std::transform(message_hash.cbegin     (),
                   message_hash.cend       (),
                   hash_tmp.cbegin         (),
                   message_hash.begin      (),
                   std::plus<std::uint32_t>());
  }

  template<typename my_count_type>
  void md5<my_count_type>::finalize()
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
    if(message_block_index > static_cast<std::uint_fast8_t>(md5_blocksize - 8U))
    {
      perform_algorithm();

      message_block.fill(static_cast<std::uint8_t>(0U));
    }

    // Encode the number of bits. Simultaneously convert the number of bytes
    // to the number of bits by performing a left-shift of 3 on the byte-array.
    // The md5 stores the 8 bytes of the bit counter in forward order,
    // with the lowest byte being stored at index 56 in the buffer
    std::uint_fast8_t carry = static_cast<std::uint_fast8_t>(0U);

    std::for_each(message_block.end() - 8U,
                  message_block.end(),
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
  void md5<my_count_type>::reset()
  {
    message_hash[0U] = UINT32_C(0x67452301);
    message_hash[1U] = UINT32_C(0xEFCDAB89);
    message_hash[2U] = UINT32_C(0x98BADCFE);
    message_hash[3U] = UINT32_C(0x10325476);

    the_result_is_finalized = false;
    message_length_total    = static_cast<count_type>(0U);
    message_block_index     = static_cast<std::uint_fast8_t>(0U);
  }

  template<typename my_count_type>
  typename md5<my_count_type>::result_type_as_bytes md5<my_count_type>::get_result_as_bytes_and_finalize_the_state()
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
  typename md5<my_count_type>::result_type_as_bytes md5<my_count_type>::get_result_as_bytes_and_nochange_the_state() const
  {
    // Make a local copy of the hash object.
    md5 other(*this);

    // Finalize the local copy of the hash object,
    // and return the final result from the copied object.
    return other.get_result_as_bytes_and_finalize_the_state();
  }

  template<typename my_count_type>
  typename md5<my_count_type>::result_type_as_dwords md5<my_count_type>::get_result_as_dwords_and_finalize_the_state()
  {
    if(!the_result_is_finalized) { finalize(); }

    return message_hash;
  }

  template<typename my_count_type>
  typename md5<my_count_type>::result_type_as_dwords md5<my_count_type>::get_result_as_dwords_and_nochange_the_state() const
  {
    // Make a local copy of the hash object.
    md5 other(*this);

    // Finalize the local copy of the hash object,
    // and return the final result from the copied object.
    other.finalize();

    return other.message_hash;
  }

  template<typename my_count_type>
  typename md5<my_count_type>::result_type_as_chars md5<my_count_type>::get_result_as_chars_and_finalize_the_state()
  {
    // Get the result of the hash object as a byte array.
    const result_type_as_bytes the_result_as_bytes = get_result_as_bytes_and_finalize_the_state();

    result_type_as_chars the_result_as_chars;

    // Conver the result as a byte array to a character array.
    convert_uint8_input_to_char8_output(the_result_as_bytes.data(),
                                        the_result_as_bytes.data() + the_result_as_bytes.size(),
                                        the_result_as_chars.data());

    return the_result_as_chars;
  }

  template<typename my_count_type>
  typename md5<my_count_type>::result_type_as_chars md5<my_count_type>::get_result_as_chars_and_nochange_the_state() const
  {
    // Make a local copy of the hash object.
    md5 temp_md5(*this);

    // Finalize the local copy of the hash object,
    // and return the final result from the copied object.
    return temp_md5.get_result_as_chars_and_finalize_the_state();
  }

#endif // _MD5_2012_01_13_H_
