
///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2012 - 2013.
//
// \license LGPLv3
// md5 is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// chrono is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
// GNU Lesser Public License for more details.
// You should have received a copy of the GNU Lesser Public License
// along with chrono. If not, see <http://www.gnu.org/licenses/>.
//

///////////////////////////////////////////////////////////////////////////////
//
// This work has been created by Christopher Kormanyos.
// This work is an md5 implementation that has been specifically
// designed for C++. The implementation places particular
// emphasis on portability to microcontroller platforms.
//
// The origin of this work is identified as the
// "RSA Data Security, Inc. MD5 Message-Digest Algorithm"
// This work is: "derived from the RSA Data Security, Inc.
// MD5 Message-Digest Algorithm". The original license notices
// from RSA Data Security, Inc. follow below.
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
  #include <limits>
  #include "crypto_hash_base.h"

  template<typename md5_count_type>
  class md5 : public crypto_hash_base
  {
  public:
    typedef md5_count_type                 count_type;
    typedef std::array<std::uint8_t,  16U> result_type_as_bytes;
    typedef std::array<char,          32U> result_type_as_chars;
    typedef std::array<std::uint32_t,  4U> result_type_as_dwords;

    static_assert(   ( std::numeric_limits<count_type>::is_specialized == true)
                  && ( std::numeric_limits<count_type>::is_integer     == true)
                  && ( std::numeric_limits<count_type>::is_signed      == false)
                  && ( std::numeric_limits<count_type>::radix          == 2)
                  && ((std::numeric_limits<count_type>::digits % 8)    == 0),
                  "the count type must be an unsigned integer type with radix 2, having a multiple of 8 bits");

    md5() { }

    md5(const std::uint8_t* data_stream, const count_type& count);

    md5(const char* string_stream, const count_type& count);

    template<typename unsigned_integer_type> md5(unsigned_integer_type u);

    md5(const md5& other);

    result_type_as_bytes get_result_as_bytes_and_finalize_the_state();
    result_type_as_bytes get_result_as_bytes_and_nochange_the_state() const;

    result_type_as_dwords get_result_as_dwords_and_finalize_the_state();
    result_type_as_dwords get_result_as_dwords_and_nochange_the_state() const;

    result_type_as_chars get_result_as_chars_and_finalize_the_state();
    result_type_as_chars get_result_as_chars_and_nochange_the_state() const;

    md5& operator=(const md5& other);

    void process_data(const std::uint8_t* data_stream, const count_type& count);
    void process_data(const char* string_stream, const count_type& count);

    template<typename unsigned_integer_type> void process_data(unsigned_integer_type u);

  private:
    static const std::uint_least8_t md5_blocksize = 64U;

    static_assert(md5_blocksize == static_cast<std::uint_least8_t>(64U), "the md5 block size must exactly equal 64");

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

    count_type                               count_of_bytes; // The running byte count in the md5.
    result_type_as_dwords                    digest_state;   // The message digest state so far.
    result_type_as_bytes                     digest_result;  // The result of the message digest.
    std::array<std::uint8_t,  md5_blocksize> digest_buffer;  // The message digest buffer.

    void apply_the_md5_algorithm(const std::uint8_t* block);

    void finalize_the_md5_algorithm();
    void initialize_the_md5_algorithm();

    void process_data_stream(const std::uint8_t* data_stream, const count_type& count);

    // F, G, H, and I are the low-level permutation operations of the md5.

    static std::uint32_t permutation_f(const std::uint32_t& x, const std::uint32_t& y, const std::uint32_t& z)
    {
      return static_cast<std::uint32_t>(static_cast<std::uint32_t>(x & y) | static_cast<std::uint32_t>(static_cast<std::uint32_t>(~x) & z));
    }

    static std::uint32_t permutation_g(const std::uint32_t& x, const std::uint32_t& y, const std::uint32_t& z)
    {
      return static_cast<std::uint32_t>(static_cast<std::uint32_t>(x & z) | static_cast<std::uint32_t>(y & static_cast<std::uint32_t>(~z)));
    }

    static std::uint32_t permutation_h(const std::uint32_t& x, const std::uint32_t& y, const std::uint32_t& z)
    {
      return static_cast<std::uint32_t>(static_cast<std::uint32_t>(x ^ y) ^ z);
    }

    static std::uint32_t permutation_i(const std::uint32_t& x, const std::uint32_t& y, const std::uint32_t& z)
    {
      return static_cast<std::uint32_t>(y ^ static_cast<std::uint32_t>(x | static_cast<std::uint32_t>(~z)));
    }

    template<const std::uint_fast8_t n>
    static std::uint32_t rotate_left(const std::uint32_t& x)
    {
      // Rotates x to the left by n bits.
      return static_cast<std::uint32_t>(static_cast<std::uint32_t>(x << n) | static_cast<std::uint32_t>(x >> (32U - n)));
    }

    // FF, GG, HH, and II are the transformations for rounds 1, 2, 3, and 4 of the md5.

    template<const std::uint_fast8_t my_s, const std::uint32_t my_ac>
    static void transformation_ff(std::uint32_t& a, const std::uint32_t& b, const std::uint32_t& c, const std::uint32_t& d, const std::uint32_t& x)
    {
      a = static_cast<std::uint32_t>(rotate_left<my_s>(static_cast<std::uint32_t>(a + permutation_f(b, c, d)) + static_cast<std::uint32_t>(x + my_ac)) + b);
    }

    template<const std::uint_fast8_t my_s, const std::uint32_t my_ac>
    static void transformation_gg(std::uint32_t& a, const std::uint32_t& b, const std::uint32_t& c, const std::uint32_t& d, const std::uint32_t& x)
    {
      a = static_cast<std::uint32_t>(rotate_left<my_s>(static_cast<std::uint32_t>(a + permutation_g(b, c, d)) + static_cast<std::uint32_t>(x + my_ac)) + b);
    }

    template<const std::uint_fast8_t my_s, const std::uint32_t my_ac>
    static void transformation_hh(std::uint32_t& a, const std::uint32_t& b, const std::uint32_t& c, const std::uint32_t& d, const std::uint32_t& x)
    {
      a = static_cast<std::uint32_t>(rotate_left<my_s>(static_cast<std::uint32_t>(a + permutation_h(b, c, d)) + static_cast<std::uint32_t>(x + my_ac)) + b);
    }

    template<const std::uint_fast8_t my_s, const std::uint32_t my_ac>
    static void transformation_ii(std::uint32_t& a, const std::uint32_t& b, const std::uint32_t& c, const std::uint32_t& d, const std::uint32_t& x)
    {
      a = static_cast<std::uint32_t>(rotate_left<my_s>(static_cast<std::uint32_t>(a + permutation_i(b, c, d)) + static_cast<std::uint32_t>(x + my_ac)) + b);
    }
  };

  template<typename md5_count_type>
  md5<md5_count_type>::md5(const std::uint8_t* data_stream, const count_type& count)
  {
    process_data(data_stream, count);
  }

  template<typename md5_count_type>
  md5<md5_count_type>::md5(const char* string_stream, const count_type& count)
  {
    process_data(static_cast<const std::uint8_t*>(static_cast<const void*>(string_stream)), count);
  }

  template<typename md5_count_type>
  template<typename unsigned_integer_type>
  md5<md5_count_type>::md5(unsigned_integer_type u)
  {
    process_data(u);
  }

  template<typename md5_count_type>
  md5<md5_count_type>::md5(const md5& other) : crypto_hash_base(other),
                                               count_of_bytes  (other.count_of_bytes),
                                               digest_state    (other.digest_state),
                                               digest_result   (other.digest_result),
                                               digest_buffer   (other.digest_buffer) { }

  template<typename md5_count_type>
  typename md5<md5_count_type>::result_type_as_bytes md5<md5_count_type>::get_result_as_bytes_and_finalize_the_state()
  {
    if((!the_result_is_finalized))
    {
      // Finalize the result.
      finalize_the_md5_algorithm();

      // Extract the message digest result from the message digest state.
      convert_uint32_input_to_uint8_output(digest_state.data(),
                                           digest_state.data() + digest_state.size(),
                                           digest_result.data());

      the_result_is_finalized = true;
    }

    return digest_result;
  }

  template<typename md5_count_type>
  typename md5<md5_count_type>::result_type_as_bytes md5<md5_count_type>::get_result_as_bytes_and_nochange_the_state() const
  {
    // Make a local copy of the message digest.
    md5 temp_md5(*this);

    // Finalize the local copy of the message digest,
    // and return the final result from the copied object.
    return temp_md5.get_result_as_bytes_and_finalize_the_state();
  }

  template<typename md5_count_type>
  typename md5<md5_count_type>::result_type_as_dwords md5<md5_count_type>::get_result_as_dwords_and_finalize_the_state()
  {
    if((!the_result_is_finalized))
    {
      // Finalize the result.
      finalize_the_md5_algorithm();

      // Extract the message digest result from the message digest state.
      // Even though we are getting the dword representation in this
      // subroutine, we will also prepare the byte representation.
      convert_uint32_input_to_uint8_output(digest_state.data(),
                                           digest_state.data() + digest_state.size(),
                                           digest_result.data());

      the_result_is_finalized = true;
    }

    return digest_state;
  }

  template<typename md5_count_type>
  typename md5<md5_count_type>::result_type_as_dwords md5<md5_count_type>::get_result_as_dwords_and_nochange_the_state() const
  {
    // Make a local copy of the message digest.
    md5 temp_md5(*this);

    // Finalize the local copy of the message digest,
    // and return the final result from the copied object.
    temp_md5.finalize_the_md5_algorithm();

    return temp_md5.digest_state;
  }

  template<typename md5_count_type>
  typename md5<md5_count_type>::result_type_as_chars md5<md5_count_type>::get_result_as_chars_and_finalize_the_state()
  {
    // Get the result of the md5 as a byte array.
    const result_type_as_bytes the_result_as_bytes = get_result_as_bytes_and_finalize_the_state();

    result_type_as_chars the_result_as_chars;

    // Conver the result as a byte array to a character array.
    convert_uint8_input_to_char8_output(the_result_as_bytes.data(),
                                        the_result_as_bytes.data() + the_result_as_bytes.size(),
                                        the_result_as_chars.data());

    return the_result_as_chars;
  }

  template<typename md5_count_type>
  typename md5<md5_count_type>::result_type_as_chars md5<md5_count_type>::get_result_as_chars_and_nochange_the_state() const
  {
    // Make a local copy of the message digest.
    md5 temp_md5(*this);

    // Finalize the local copy of the message digest,
    // and return the final result from the copied object.
    return temp_md5.get_result_as_chars_and_finalize_the_state();
  }

  template<typename md5_count_type>
  md5<md5_count_type>& md5<md5_count_type>::operator=(const md5& other)
  {
    if(this != &other)
    {
      static_cast<void>(crypto_hash_base::operator=(other));

      count_of_bytes = other.count_of_bytes;
      digest_state   = other.digest_state;
      digest_result  = other.digest_result;
      digest_buffer  = other.digest_buffer;
    }

    return *this;
  }

  template<typename md5_count_type>
  void md5<md5_count_type>::process_data(const std::uint8_t* data_stream, const count_type& count)
  {
    process_data_stream(data_stream, count);
  }

  template<typename md5_count_type>
  void md5<md5_count_type>::process_data(const char* string_stream, const count_type& count)
  {
    const std::uint8_t* data_stream = static_cast<const std::uint8_t*>(static_cast<const void*>(string_stream));

    process_data_stream(data_stream, count);
  }

  template<typename md5_count_type>
  template<typename unsigned_integer_type>
  void md5<md5_count_type>::process_data(unsigned_integer_type u)
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
                    data_value = std::uint8_t(u);

                    u >>= 8;
                  });

    process_data_stream(the_data.data(), the_data.size());
  }

  template<typename md5_count_type>
  void md5<md5_count_type>::apply_the_md5_algorithm(const std::uint8_t* block)
  {
    // Apply the md5 algorithm to a 64-byte data block.

    std::array<std::uint32_t, 4U> digest_tmp = digest_state;

    std::array<std::uint32_t, md5_blocksize / 4U> transform_block;

    convert_uint8_input_to_uint32_output(block, block + md5_blocksize, transform_block.data());

    // Perform transformation round 1.
    transformation_ff<S11, UINT32_C(0xD76AA478)>(digest_tmp[0U], digest_tmp[1U], digest_tmp[2U], digest_tmp[3U], transform_block[ 0U]); //  1
    transformation_ff<S12, UINT32_C(0xE8C7B756)>(digest_tmp[3U], digest_tmp[0U], digest_tmp[1U], digest_tmp[2U], transform_block[ 1U]); //  2
    transformation_ff<S13, UINT32_C(0x242070DB)>(digest_tmp[2U], digest_tmp[3U], digest_tmp[0U], digest_tmp[1U], transform_block[ 2U]); //  3
    transformation_ff<S14, UINT32_C(0xC1BDCEEE)>(digest_tmp[1U], digest_tmp[2U], digest_tmp[3U], digest_tmp[0U], transform_block[ 3U]); //  4
    transformation_ff<S11, UINT32_C(0xF57C0FAF)>(digest_tmp[0U], digest_tmp[1U], digest_tmp[2U], digest_tmp[3U], transform_block[ 4U]); //  5
    transformation_ff<S12, UINT32_C(0x4787C62A)>(digest_tmp[3U], digest_tmp[0U], digest_tmp[1U], digest_tmp[2U], transform_block[ 5U]); //  6
    transformation_ff<S13, UINT32_C(0xA8304613)>(digest_tmp[2U], digest_tmp[3U], digest_tmp[0U], digest_tmp[1U], transform_block[ 6U]); //  7
    transformation_ff<S14, UINT32_C(0xFD469501)>(digest_tmp[1U], digest_tmp[2U], digest_tmp[3U], digest_tmp[0U], transform_block[ 7U]); //  8
    transformation_ff<S11, UINT32_C(0x698098D8)>(digest_tmp[0U], digest_tmp[1U], digest_tmp[2U], digest_tmp[3U], transform_block[ 8U]); //  9
    transformation_ff<S12, UINT32_C(0x8B44F7AF)>(digest_tmp[3U], digest_tmp[0U], digest_tmp[1U], digest_tmp[2U], transform_block[ 9U]); // 10
    transformation_ff<S13, UINT32_C(0xFFFF5BB1)>(digest_tmp[2U], digest_tmp[3U], digest_tmp[0U], digest_tmp[1U], transform_block[10U]); // 11
    transformation_ff<S14, UINT32_C(0x895CD7BE)>(digest_tmp[1U], digest_tmp[2U], digest_tmp[3U], digest_tmp[0U], transform_block[11U]); // 12
    transformation_ff<S11, UINT32_C(0x6B901122)>(digest_tmp[0U], digest_tmp[1U], digest_tmp[2U], digest_tmp[3U], transform_block[12U]); // 13
    transformation_ff<S12, UINT32_C(0xFD987193)>(digest_tmp[3U], digest_tmp[0U], digest_tmp[1U], digest_tmp[2U], transform_block[13U]); // 14
    transformation_ff<S13, UINT32_C(0xA679438E)>(digest_tmp[2U], digest_tmp[3U], digest_tmp[0U], digest_tmp[1U], transform_block[14U]); // 15
    transformation_ff<S14, UINT32_C(0x49B40821)>(digest_tmp[1U], digest_tmp[2U], digest_tmp[3U], digest_tmp[0U], transform_block[15U]); // 16

    // Perform transformation round 2.
    transformation_gg<S21, UINT32_C(0xF61E2562)>(digest_tmp[0U], digest_tmp[1U], digest_tmp[2U], digest_tmp[3U], transform_block[ 1U]); // 17
    transformation_gg<S22, UINT32_C(0xC040B340)>(digest_tmp[3U], digest_tmp[0U], digest_tmp[1U], digest_tmp[2U], transform_block[ 6U]); // 18
    transformation_gg<S23, UINT32_C(0x265E5A51)>(digest_tmp[2U], digest_tmp[3U], digest_tmp[0U], digest_tmp[1U], transform_block[11U]); // 19
    transformation_gg<S24, UINT32_C(0xE9B6C7AA)>(digest_tmp[1U], digest_tmp[2U], digest_tmp[3U], digest_tmp[0U], transform_block[ 0U]); // 20
    transformation_gg<S21, UINT32_C(0xD62F105D)>(digest_tmp[0U], digest_tmp[1U], digest_tmp[2U], digest_tmp[3U], transform_block[ 5U]); // 21
    transformation_gg<S22, UINT32_C(0x02441453)>(digest_tmp[3U], digest_tmp[0U], digest_tmp[1U], digest_tmp[2U], transform_block[10U]); // 22
    transformation_gg<S23, UINT32_C(0xD8A1E681)>(digest_tmp[2U], digest_tmp[3U], digest_tmp[0U], digest_tmp[1U], transform_block[15U]); // 23
    transformation_gg<S24, UINT32_C(0xE7D3FBC8)>(digest_tmp[1U], digest_tmp[2U], digest_tmp[3U], digest_tmp[0U], transform_block[ 4U]); // 24
    transformation_gg<S21, UINT32_C(0x21E1CDE6)>(digest_tmp[0U], digest_tmp[1U], digest_tmp[2U], digest_tmp[3U], transform_block[ 9U]); // 25
    transformation_gg<S22, UINT32_C(0xC33707D6)>(digest_tmp[3U], digest_tmp[0U], digest_tmp[1U], digest_tmp[2U], transform_block[14U]); // 26
    transformation_gg<S23, UINT32_C(0xF4D50D87)>(digest_tmp[2U], digest_tmp[3U], digest_tmp[0U], digest_tmp[1U], transform_block[ 3U]); // 27
    transformation_gg<S24, UINT32_C(0x455A14ED)>(digest_tmp[1U], digest_tmp[2U], digest_tmp[3U], digest_tmp[0U], transform_block[ 8U]); // 28
    transformation_gg<S21, UINT32_C(0xA9E3E905)>(digest_tmp[0U], digest_tmp[1U], digest_tmp[2U], digest_tmp[3U], transform_block[13U]); // 29
    transformation_gg<S22, UINT32_C(0xFCEFA3F8)>(digest_tmp[3U], digest_tmp[0U], digest_tmp[1U], digest_tmp[2U], transform_block[ 2U]); // 30
    transformation_gg<S23, UINT32_C(0x676F02D9)>(digest_tmp[2U], digest_tmp[3U], digest_tmp[0U], digest_tmp[1U], transform_block[ 7U]); // 31
    transformation_gg<S24, UINT32_C(0x8D2A4C8A)>(digest_tmp[1U], digest_tmp[2U], digest_tmp[3U], digest_tmp[0U], transform_block[12U]); // 32

    // Perform transformation round 3.
    transformation_hh<S31, UINT32_C(0xFFFA3942)>(digest_tmp[0U], digest_tmp[1U], digest_tmp[2U], digest_tmp[3U], transform_block[ 5U]); // 33
    transformation_hh<S32, UINT32_C(0x8771F681)>(digest_tmp[3U], digest_tmp[0U], digest_tmp[1U], digest_tmp[2U], transform_block[ 8U]); // 34
    transformation_hh<S33, UINT32_C(0x6D9D6122)>(digest_tmp[2U], digest_tmp[3U], digest_tmp[0U], digest_tmp[1U], transform_block[11U]); // 35
    transformation_hh<S34, UINT32_C(0xFDE5380C)>(digest_tmp[1U], digest_tmp[2U], digest_tmp[3U], digest_tmp[0U], transform_block[14U]); // 36
    transformation_hh<S31, UINT32_C(0xA4BEEA44)>(digest_tmp[0U], digest_tmp[1U], digest_tmp[2U], digest_tmp[3U], transform_block[ 1U]); // 37
    transformation_hh<S32, UINT32_C(0x4BDECFA9)>(digest_tmp[3U], digest_tmp[0U], digest_tmp[1U], digest_tmp[2U], transform_block[ 4U]); // 38
    transformation_hh<S33, UINT32_C(0xF6BB4B60)>(digest_tmp[2U], digest_tmp[3U], digest_tmp[0U], digest_tmp[1U], transform_block[ 7U]); // 39
    transformation_hh<S34, UINT32_C(0xBEBFBC70)>(digest_tmp[1U], digest_tmp[2U], digest_tmp[3U], digest_tmp[0U], transform_block[10U]); // 40
    transformation_hh<S31, UINT32_C(0x289B7EC6)>(digest_tmp[0U], digest_tmp[1U], digest_tmp[2U], digest_tmp[3U], transform_block[13U]); // 41
    transformation_hh<S32, UINT32_C(0xEAA127FA)>(digest_tmp[3U], digest_tmp[0U], digest_tmp[1U], digest_tmp[2U], transform_block[ 0U]); // 42
    transformation_hh<S33, UINT32_C(0xD4EF3085)>(digest_tmp[2U], digest_tmp[3U], digest_tmp[0U], digest_tmp[1U], transform_block[ 3U]); // 43
    transformation_hh<S34, UINT32_C(0x04881D05)>(digest_tmp[1U], digest_tmp[2U], digest_tmp[3U], digest_tmp[0U], transform_block[ 6U]); // 44
    transformation_hh<S31, UINT32_C(0xD9D4D039)>(digest_tmp[0U], digest_tmp[1U], digest_tmp[2U], digest_tmp[3U], transform_block[ 9U]); // 45
    transformation_hh<S32, UINT32_C(0xE6DB99E5)>(digest_tmp[3U], digest_tmp[0U], digest_tmp[1U], digest_tmp[2U], transform_block[12U]); // 46
    transformation_hh<S33, UINT32_C(0x1FA27CF8)>(digest_tmp[2U], digest_tmp[3U], digest_tmp[0U], digest_tmp[1U], transform_block[15U]); // 47
    transformation_hh<S34, UINT32_C(0xC4AC5665)>(digest_tmp[1U], digest_tmp[2U], digest_tmp[3U], digest_tmp[0U], transform_block[ 2U]); // 48

    // Perform transformation round 4.
    transformation_ii<S41, UINT32_C(0xF4292244)>(digest_tmp[0U], digest_tmp[1U], digest_tmp[2U], digest_tmp[3U], transform_block[ 0U]); // 49
    transformation_ii<S42, UINT32_C(0x432AFF97)>(digest_tmp[3U], digest_tmp[0U], digest_tmp[1U], digest_tmp[2U], transform_block[ 7U]); // 50
    transformation_ii<S43, UINT32_C(0xAB9423A7)>(digest_tmp[2U], digest_tmp[3U], digest_tmp[0U], digest_tmp[1U], transform_block[14U]); // 51
    transformation_ii<S44, UINT32_C(0xFC93A039)>(digest_tmp[1U], digest_tmp[2U], digest_tmp[3U], digest_tmp[0U], transform_block[ 5U]); // 52
    transformation_ii<S41, UINT32_C(0x655B59C3)>(digest_tmp[0U], digest_tmp[1U], digest_tmp[2U], digest_tmp[3U], transform_block[12U]); // 53
    transformation_ii<S42, UINT32_C(0x8F0CCC92)>(digest_tmp[3U], digest_tmp[0U], digest_tmp[1U], digest_tmp[2U], transform_block[ 3U]); // 54
    transformation_ii<S43, UINT32_C(0xFFEFF47D)>(digest_tmp[2U], digest_tmp[3U], digest_tmp[0U], digest_tmp[1U], transform_block[10U]); // 55
    transformation_ii<S44, UINT32_C(0x85845DD1)>(digest_tmp[1U], digest_tmp[2U], digest_tmp[3U], digest_tmp[0U], transform_block[ 1U]); // 56
    transformation_ii<S41, UINT32_C(0x6FA87E4F)>(digest_tmp[0U], digest_tmp[1U], digest_tmp[2U], digest_tmp[3U], transform_block[ 8U]); // 57
    transformation_ii<S42, UINT32_C(0xFE2CE6E0)>(digest_tmp[3U], digest_tmp[0U], digest_tmp[1U], digest_tmp[2U], transform_block[15U]); // 58
    transformation_ii<S43, UINT32_C(0xA3014314)>(digest_tmp[2U], digest_tmp[3U], digest_tmp[0U], digest_tmp[1U], transform_block[ 6U]); // 59
    transformation_ii<S44, UINT32_C(0x4E0811A1)>(digest_tmp[1U], digest_tmp[2U], digest_tmp[3U], digest_tmp[0U], transform_block[13U]); // 60
    transformation_ii<S41, UINT32_C(0xF7537E82)>(digest_tmp[0U], digest_tmp[1U], digest_tmp[2U], digest_tmp[3U], transform_block[ 4U]); // 61
    transformation_ii<S42, UINT32_C(0xBD3AF235)>(digest_tmp[3U], digest_tmp[0U], digest_tmp[1U], digest_tmp[2U], transform_block[11U]); // 62
    transformation_ii<S43, UINT32_C(0x2AD7D2BB)>(digest_tmp[2U], digest_tmp[3U], digest_tmp[0U], digest_tmp[1U], transform_block[ 2U]); // 63
    transformation_ii<S44, UINT32_C(0xEB86D391)>(digest_tmp[1U], digest_tmp[2U], digest_tmp[3U], digest_tmp[0U], transform_block[ 9U]); // 64

    // Update the state information with the transformation results.
    std::transform(digest_state.begin(),
                    digest_state.end(),
                    digest_tmp.begin(),
                    digest_state.begin(),
                    std::plus<std::uint32_t>());
  }

  template<typename md5_count_type>
  void md5<md5_count_type>::finalize_the_md5_algorithm()
  {
    // Perform the md5 finalization. This ends a message digest operation.

    // Create the padding. Begin by setting the leading padding byte to 128.
    digest_buffer[count_remaining_in_buffer] = static_cast<std::uint8_t>(md5_blocksize * 2U);

    // Fill the rest of the padding bytes with zero.
    if(count_remaining_in_buffer > std::uint_least8_t(md5_blocksize - 8U))
    {
      // We need an extra block. Fill the current block with zeros,
      // transform it, and pad an additional block.
      std::fill(digest_buffer.begin() + count_remaining_in_buffer + 1U,
                digest_buffer.end(),
                static_cast<std::uint8_t>(0U));

      apply_the_md5_algorithm(digest_buffer.data());

      std::fill(digest_buffer.begin(),
                digest_buffer.end() - 8U,
                static_cast<std::uint8_t>(0U));
    }
    else
    {
      std::fill(digest_buffer.begin() + (count_remaining_in_buffer + 1U),
                digest_buffer.end() - 8U,
                static_cast<std::uint8_t>(0U));
    }

    // Add the bits from the remaining bytes in the buffer to the count of bits.
    count_of_bytes += count_remaining_in_buffer;

    std::fill(digest_buffer.end() - 8U, digest_buffer.end(), static_cast<std::uint8_t>(0U));

    // Encode the number of bits. Simultaneously convert the number of bytes
    // to the number of bits by performing a left-shift of 3 on the byte-array.
    std::uint_least8_t carry = static_cast<std::uint_least8_t>(0U);
    std::uint_fast8_t  i     = static_cast<std::uint_fast8_t>(0U);

    for( ; i < std::uint_fast8_t(std::numeric_limits<count_type>::digits / 8U); ++i)
    {
      const std::uint_least16_t the_word = static_cast<std::uint_least16_t>(static_cast<std::uint_least16_t>(count_of_bytes) << 3) >> (i * 8);

      *(digest_buffer.end() - (8U - i)) = static_cast<std::uint8_t>(the_word | carry);

      carry = static_cast<std::uint_least8_t>(the_word >> 8);
    }

    if(static_cast<std::uint_fast8_t>((md5_blocksize - 8U) + 1) < static_cast<std::uint_fast8_t>(md5_blocksize))
    {
      *(digest_buffer.end() - (8U - i)) = static_cast<std::uint8_t>(carry);
    }

    apply_the_md5_algorithm(digest_buffer.data());
  }

  template<typename md5_count_type>
  void md5<md5_count_type>::initialize_the_md5_algorithm()
  {
    count_of_bytes          = count_type(0U);
    the_result_is_finalized = false;

    digest_state[0U] = UINT32_C(0x67452301);
    digest_state[1U] = UINT32_C(0xEfCDAB89);
    digest_state[2U] = UINT32_C(0x98BADCFE);
    digest_state[3U] = UINT32_C(0x10325476);
  }

  template<typename md5_count_type>
  void md5<md5_count_type>::process_data_stream(const std::uint8_t* data_stream, const count_type& count)
  {
    // Check if initialization is required.
    if(the_result_is_finalized)
    {
      initialize_the_md5_algorithm();

      the_result_is_finalized = false;
    }

    count_type number_processed_in_this_call = static_cast<count_type>(0U);

    // Transform any data that are not contained within a modulus-64 block.
    if(count > static_cast<count_type>(md5_blocksize - count_remaining_in_buffer))
    {
      number_processed_in_this_call = static_cast<count_type>(md5_blocksize - count_remaining_in_buffer);

      std::copy(data_stream,
                data_stream + number_processed_in_this_call,
                digest_buffer.begin() + count_remaining_in_buffer);

      apply_the_md5_algorithm(digest_buffer.data());
    }

    // Transform all data that are contained within subsequent modulus-64 blocks.
    const count_type number_of_blocks = static_cast<count_type>(count - number_processed_in_this_call) / md5_blocksize;

    for(count_type i = static_cast<count_type>(0U); i < number_of_blocks; ++i)
    {
      std::copy(data_stream +  number_processed_in_this_call,
                data_stream + (number_processed_in_this_call + (md5_blocksize + count_type(i * md5_blocksize))),
                digest_buffer.begin());

      apply_the_md5_algorithm(digest_buffer.data());
    }

    number_processed_in_this_call += static_cast<count_type>(number_of_blocks * md5_blocksize);

    // Buffer the remaining input that could not fit into a modulus-64 block.
    std::copy(data_stream + number_processed_in_this_call,
              data_stream + count,
              digest_buffer.begin() + count_remaining_in_buffer);

    count_remaining_in_buffer += std::uint_least8_t(count - number_processed_in_this_call);

    // Update the number of bits.
    count_of_bytes += number_processed_in_this_call;
  }

#endif // _MD5_2012_01_13_H_
