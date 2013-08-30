///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2012 - 2013.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

///////////////////////////////////////////////////////////////////////////////
//
// January 2012:
// This work has been created by Christopher Kormanyos and
// specifically designed for C++2011 and for portability
// to microcontroller platforms.
//
// This work was originally converted to a C++ class by
// Frank Thilo (thilo@unix-ag.org) for bzflag (http://www.bzflag.org).
//
// The origin of this work is identified as the
// "RSA Data Security, Inc. MD5 Message-Digest Algorithm"
//
// This work is "derived from the RSA Data Security, Inc.
// MD5 Message-Digest Algorithm".
//
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

  #include <algorithm>
  #include <array>
  #include <cstdint>
  #include <cstddef>
  #include <functional>
  #include <limits>

  class md5
  {
  public:
    typedef std::array<std::uint8_t, 16U> result_type;

    md5() : the_result_is_finalized(true),
            count_of_bits          (),
            digest_state           (),
            digest_buffer          (),
            digest_result          () { }

    md5(const std::uint8_t* data_buffer, const std::size_t count) : the_result_is_finalized(true),
                                                                    count_of_bits          (),
                                                                    digest_state           (),
                                                                    digest_buffer          (),
                                                                    digest_result          ()
    {
      process_data(data_buffer, count);
    }

    md5(const char* data_string, const std::size_t count) : the_result_is_finalized(true),
                                                            count_of_bits          (),
                                                            digest_state           (),
                                                            digest_buffer          (),
                                                            digest_result          ()
    {
      process_data(static_cast<const std::uint8_t*>(static_cast<const void*>(data_string)), count);
    }

    template<typename unsigned_integer_type>
    md5(const unsigned_integer_type& u) : the_result_is_finalized(true),
                                          count_of_bits          (),
                                          digest_state           (),
                                          digest_buffer          (),
                                          digest_result          ()
    {
      // Ensure that the template parameter is an unsigned integer type with radix 2, having a multiple of 8 bits.
      static_assert(   ( std::numeric_limits<unsigned_integer_type>::is_specialized  == true)
                    && ( std::numeric_limits<unsigned_integer_type>::is_integer      == true)
                    && ( std::numeric_limits<unsigned_integer_type>::is_signed       == false)
                    && ( std::numeric_limits<unsigned_integer_type>::radix           == 2)
                    && ((std::numeric_limits<unsigned_integer_type>::digits % 8)     == 0),
                    "the template type must be an unsigned integer type with radix 2, having a multiple of 8 bits");

      std::array<std::uint8_t, std::numeric_limits<unsigned_integer_type>::digits / 8> the_data;

      std::uint_fast8_t i = 0U;

      std::for_each(the_data.begin(),
                    the_data.end(),
                    [&u, &i](std::uint8_t& data_value)
                    {
                      data_value = std::uint8_t(u >> i);

                      i += 8U;
                    });

      process_data(the_data.data(), the_data.size());
    }

    void process_data(const std::uint8_t* data_buffer, const std::size_t count);

    void process_data(const char* data_string, const std::size_t count)
    {
      process_data(static_cast<const std::uint8_t*>(static_cast<const void*>(data_string)), count);
    }

    template<typename unsigned_integer_type>
    void process_data(const unsigned_integer_type& u)
    {
      // Ensure that the template parameter is an unsigned integer type with radix 2, having a multiple of 8 bits.
      static_assert(   ( std::numeric_limits<unsigned_integer_type>::is_specialized  == true)
                    && ( std::numeric_limits<unsigned_integer_type>::is_integer      == true)
                    && ( std::numeric_limits<unsigned_integer_type>::is_signed       == false)
                    && ( std::numeric_limits<unsigned_integer_type>::radix           == 2)
                    && ((std::numeric_limits<unsigned_integer_type>::digits % 8)     == 0),
                    "the template type must be an unsigned integer type with radix 2, having a multiple of 8 bits");

      std::array<std::uint8_t, std::numeric_limits<unsigned_integer_type>::digits / 8> the_data;

      std::uint_fast8_t i = 0U;

      std::for_each(the_data.begin(),
                    the_data.end(),
                    [&u, &i](std::uint8_t& data_value)
                    {
                      data_value = std::uint8_t(u >> i);

                      i += 8U;
                    });

      process_data(the_data.data(), the_data.size());
    }

    const result_type& get_result_and_re_initialize();

  private:
    static const std::size_t md5_blocksize = 64U;

    static_assert(md5_blocksize == static_cast<std::size_t>(64U), "the md5 block size must exactly equal 64");

    // Constants for the MD5 transform routine.
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

    bool                                     the_result_is_finalized; // A flag signalizing whether or not the result is finalized.
    std::array<std::uint32_t, 2U>            count_of_bits;           // A counter for number of bits.
    std::array<std::uint32_t, 4U>            digest_state;            // The message digest state so far.
    std::array<std::uint8_t,  md5_blocksize> digest_buffer;           // The message digest buffer.
    result_type                              digest_result;           // The result of the message digest.

    void initialize();
    void finalize();

    static void decode_uint8_input_to_uint32_output(const std::uint8_t*  input_begin, const std::uint8_t*  input_end, std::uint32_t* output_begin);
    static void encode_uint32_input_to_uint8_output(const std::uint32_t* input_begin, const std::uint32_t* input_end, std::uint8_t*  output_begin);

    void transform(const std::uint8_t* block);

    // The following are the low-level bit twiddle operations of the message digest.

    // F, G, H and I are basic MD5 functions.
    static std::uint32_t f_bit_twiddle(const std::uint32_t& x, const std::uint32_t& y, const std::uint32_t& z);
    static std::uint32_t g_bit_twiddle(const std::uint32_t& x, const std::uint32_t& y, const std::uint32_t& z);
    static std::uint32_t h_bit_twiddle(const std::uint32_t& x, const std::uint32_t& y, const std::uint32_t& z);
    static std::uint32_t i_bit_twiddle(const std::uint32_t& x, const std::uint32_t& y, const std::uint32_t& z);

    // The rotate_left function rotates x to the left by n bits.
    template<const std::uint_fast8_t n>
    static std::uint32_t rotate_left(const std::uint32_t& x)
    {
      return static_cast<std::uint32_t>(static_cast<std::uint32_t>(x << n) | static_cast<std::uint32_t>(x >> (32U - n)));
    }

    // The following are the FF, GG, HH, and II transformations for
    // rounds 1, 2, 3, and 4 of the message digest.
    template<const std::uint_fast8_t s, const std::uint32_t ac>
    static void ff_transform(std::uint32_t& a, const std::uint32_t& b, const std::uint32_t& c, const std::uint32_t& d, const std::uint32_t& x);

    template<const std::uint_fast8_t s, const std::uint32_t ac>
    static void gg_transform(std::uint32_t& a, const std::uint32_t& b, const std::uint32_t& c, const std::uint32_t& d, const std::uint32_t& x);

    template<const std::uint_fast8_t s, const std::uint32_t ac>
    static void hh_transform(std::uint32_t& a, const std::uint32_t& b, const std::uint32_t& c, const std::uint32_t& d, const std::uint32_t& x);

    template<const std::uint_fast8_t s, const std::uint32_t ac>
    static void ii_transform(std::uint32_t& a, const std::uint32_t& b, const std::uint32_t& c, const std::uint32_t& d, const std::uint32_t& x);
  };

  void md5::process_data(const std::uint8_t* data_buffer, const std::size_t count)
  {
    if(the_result_is_finalized)
    {
      initialize();

      the_result_is_finalized = false;
    }

    // Continue (or start) the message digest operation.

    // Compute the number of bytes mod 64.
    std::size_t index = static_cast<std::size_t>(static_cast<std::size_t>(count_of_bits[0U] / 8U) % md5_blocksize);

    // Update the number of bits.
    const std::uint32_t len_shift = static_cast<std::uint32_t>(static_cast<std::uint32_t>(count) << 3U);

    count_of_bits[0U] += len_shift;

    if(count_of_bits[0U] < len_shift)
    {
      ++count_of_bits[1U];
    }

    count_of_bits[1U] += static_cast<std::uint32_t>(static_cast<std::uint32_t>(count) >> 29U);

    // Compute the number of bytes we need to inject into the buffer.
    const std::size_t firstpart = static_cast<std::size_t>(md5_blocksize - index);

    std::size_t i = static_cast<std::size_t>(0U);

    // Transform as many times as possible.
    if(count >= firstpart)
    {
      // Fill the buffer first, then transform.
      std::copy(data_buffer, data_buffer + firstpart, digest_buffer.begin() + index);

      transform(digest_buffer.data());

      // Transform chunks of md5_blocksize (64 bytes).
      for(i = firstpart; (i + md5_blocksize) <= count; i += md5_blocksize)
      {
        transform(&data_buffer[i]);
      }

      index = static_cast<std::size_t>(0U);
    }

    // Buffer the remaining input.
    std::copy(data_buffer + i, data_buffer + count, digest_buffer.begin() + index);
  }

  const md5::result_type& md5::get_result_and_re_initialize()
  {
    if((!the_result_is_finalized))
    {
      // Finalize the result.
      finalize();

      // Extract the message digest result from the message digest state.
      encode_uint32_input_to_uint8_output(digest_state.data(),
                                          digest_state.data() + digest_state.size(),
                                          digest_result.data());

      the_result_is_finalized = true;
    }

    return digest_result;
  }

  void md5::initialize()
  {
    // Clear the bit counters.
    std::fill(count_of_bits.begin(), count_of_bits.end(), static_cast<std::uint32_t>(0U));

    // Load the *magic* initialization constants.
    digest_state[0U] = UINT32_C(0x67452301);
    digest_state[1U] = UINT32_C(0xEfCDAB89);
    digest_state[2U] = UINT32_C(0x98BADCFE);
    digest_state[3U] = UINT32_C(0x10325476);

    the_result_is_finalized = false;
  }

  void md5::finalize()
  {
    // Perform the MD5 finalization.
    // This ends an MD5 message-digest operation.

    // Create and initialize the padding.
    std::array<std::uint8_t, md5_blocksize - 8U> padding;
    padding[0U] = static_cast<std::uint8_t>(md5_blocksize * 2U);
    std::fill(padding.begin() + 1U, padding.end(), static_cast<std::uint8_t>(0U));

    // Encode the number of bits.
    std::array<std::uint8_t, 8U> count_of_bits_encoded;
    encode_uint32_input_to_uint8_output(count_of_bits.data(),
                                        count_of_bits.data() + count_of_bits.size(),
                                        count_of_bits_encoded.data());

    // Pad out to 56 mod 64.
    const std::size_t index = static_cast<std::size_t>(static_cast<std::uint32_t>(count_of_bits[0U] / 8U) % md5_blocksize);

    const std::size_t pad_len = ((index < static_cast<std::size_t>(md5_blocksize - 8U))
                                   ? (static_cast<std::size_t>( md5_blocksize       - 8U) - index)
                                   : (static_cast<std::size_t>((md5_blocksize * 2U) - 8U) - index));

    // Update the digest state with the padding.
    process_data(padding.data(), pad_len);

    // Update the digest state with the encoded number of bits.
    process_data(count_of_bits_encoded.data(), 8U);
  }

  void md5::decode_uint8_input_to_uint32_output(const std::uint8_t* input_begin, const std::uint8_t* input_end, std::uint32_t* output_begin)
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

  void md5::encode_uint32_input_to_uint8_output(const std::uint32_t* input_begin, const std::uint32_t* input_end, std::uint8_t* output_begin)
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

  void md5::transform(const std::uint8_t* block)
  {
    // Apply the MD5 algorithm to a block.

    std::array<std::uint32_t, md5_blocksize / 4U> x_transform;

    std::array<std::uint32_t, 4U> abcd_transform = digest_state;

    decode_uint8_input_to_uint32_output(block, block + md5_blocksize, x_transform.data());

    // Round 1
    ff_transform<S11, UINT32_C(0xD76AA478)>(abcd_transform[0U], abcd_transform[1U], abcd_transform[2U], abcd_transform[3U], x_transform[ 0U]); //  1
    ff_transform<S12, UINT32_C(0xE8C7B756)>(abcd_transform[3U], abcd_transform[0U], abcd_transform[1U], abcd_transform[2U], x_transform[ 1U]); //  2
    ff_transform<S13, UINT32_C(0x242070DB)>(abcd_transform[2U], abcd_transform[3U], abcd_transform[0U], abcd_transform[1U], x_transform[ 2U]); //  3
    ff_transform<S14, UINT32_C(0xC1BDCEEE)>(abcd_transform[1U], abcd_transform[2U], abcd_transform[3U], abcd_transform[0U], x_transform[ 3U]); //  4
    ff_transform<S11, UINT32_C(0xF57C0FAF)>(abcd_transform[0U], abcd_transform[1U], abcd_transform[2U], abcd_transform[3U], x_transform[ 4U]); //  5
    ff_transform<S12, UINT32_C(0x4787C62A)>(abcd_transform[3U], abcd_transform[0U], abcd_transform[1U], abcd_transform[2U], x_transform[ 5U]); //  6
    ff_transform<S13, UINT32_C(0xA8304613)>(abcd_transform[2U], abcd_transform[3U], abcd_transform[0U], abcd_transform[1U], x_transform[ 6U]); //  7
    ff_transform<S14, UINT32_C(0xFD469501)>(abcd_transform[1U], abcd_transform[2U], abcd_transform[3U], abcd_transform[0U], x_transform[ 7U]); //  8
    ff_transform<S11, UINT32_C(0x698098D8)>(abcd_transform[0U], abcd_transform[1U], abcd_transform[2U], abcd_transform[3U], x_transform[ 8U]); //  9
    ff_transform<S12, UINT32_C(0x8B44F7AF)>(abcd_transform[3U], abcd_transform[0U], abcd_transform[1U], abcd_transform[2U], x_transform[ 9U]); // 10
    ff_transform<S13, UINT32_C(0xFFFF5BB1)>(abcd_transform[2U], abcd_transform[3U], abcd_transform[0U], abcd_transform[1U], x_transform[10U]); // 11
    ff_transform<S14, UINT32_C(0x895CD7BE)>(abcd_transform[1U], abcd_transform[2U], abcd_transform[3U], abcd_transform[0U], x_transform[11U]); // 12
    ff_transform<S11, UINT32_C(0x6B901122)>(abcd_transform[0U], abcd_transform[1U], abcd_transform[2U], abcd_transform[3U], x_transform[12U]); // 13
    ff_transform<S12, UINT32_C(0xFD987193)>(abcd_transform[3U], abcd_transform[0U], abcd_transform[1U], abcd_transform[2U], x_transform[13U]); // 14
    ff_transform<S13, UINT32_C(0xA679438E)>(abcd_transform[2U], abcd_transform[3U], abcd_transform[0U], abcd_transform[1U], x_transform[14U]); // 15
    ff_transform<S14, UINT32_C(0x49B40821)>(abcd_transform[1U], abcd_transform[2U], abcd_transform[3U], abcd_transform[0U], x_transform[15U]); // 16

    // Round 2
    gg_transform<S21, UINT32_C(0xF61E2562)>(abcd_transform[0U], abcd_transform[1U], abcd_transform[2U], abcd_transform[3U], x_transform[ 1U]); // 17
    gg_transform<S22, UINT32_C(0xC040B340)>(abcd_transform[3U], abcd_transform[0U], abcd_transform[1U], abcd_transform[2U], x_transform[ 6U]); // 18
    gg_transform<S23, UINT32_C(0x265E5A51)>(abcd_transform[2U], abcd_transform[3U], abcd_transform[0U], abcd_transform[1U], x_transform[11U]); // 19
    gg_transform<S24, UINT32_C(0xE9B6C7AA)>(abcd_transform[1U], abcd_transform[2U], abcd_transform[3U], abcd_transform[0U], x_transform[ 0U]); // 20
    gg_transform<S21, UINT32_C(0xD62F105D)>(abcd_transform[0U], abcd_transform[1U], abcd_transform[2U], abcd_transform[3U], x_transform[ 5U]); // 21
    gg_transform<S22, UINT32_C(0x02441453)>(abcd_transform[3U], abcd_transform[0U], abcd_transform[1U], abcd_transform[2U], x_transform[10U]); // 22
    gg_transform<S23, UINT32_C(0xD8A1E681)>(abcd_transform[2U], abcd_transform[3U], abcd_transform[0U], abcd_transform[1U], x_transform[15U]); // 23
    gg_transform<S24, UINT32_C(0xE7D3FBC8)>(abcd_transform[1U], abcd_transform[2U], abcd_transform[3U], abcd_transform[0U], x_transform[ 4U]); // 24
    gg_transform<S21, UINT32_C(0x21E1CDE6)>(abcd_transform[0U], abcd_transform[1U], abcd_transform[2U], abcd_transform[3U], x_transform[ 9U]); // 25
    gg_transform<S22, UINT32_C(0xC33707D6)>(abcd_transform[3U], abcd_transform[0U], abcd_transform[1U], abcd_transform[2U], x_transform[14U]); // 26
    gg_transform<S23, UINT32_C(0xF4D50D87)>(abcd_transform[2U], abcd_transform[3U], abcd_transform[0U], abcd_transform[1U], x_transform[ 3U]); // 27
    gg_transform<S24, UINT32_C(0x455A14ED)>(abcd_transform[1U], abcd_transform[2U], abcd_transform[3U], abcd_transform[0U], x_transform[ 8U]); // 28
    gg_transform<S21, UINT32_C(0xA9E3E905)>(abcd_transform[0U], abcd_transform[1U], abcd_transform[2U], abcd_transform[3U], x_transform[13U]); // 29
    gg_transform<S22, UINT32_C(0xFCEFA3F8)>(abcd_transform[3U], abcd_transform[0U], abcd_transform[1U], abcd_transform[2U], x_transform[ 2U]); // 30
    gg_transform<S23, UINT32_C(0x676F02D9)>(abcd_transform[2U], abcd_transform[3U], abcd_transform[0U], abcd_transform[1U], x_transform[ 7U]); // 31
    gg_transform<S24, UINT32_C(0x8D2A4C8A)>(abcd_transform[1U], abcd_transform[2U], abcd_transform[3U], abcd_transform[0U], x_transform[12U]); // 32

    // Round 3
    hh_transform<S31, UINT32_C(0xFFFA3942)>(abcd_transform[0U], abcd_transform[1U], abcd_transform[2U], abcd_transform[3U], x_transform[ 5U]); // 33
    hh_transform<S32, UINT32_C(0x8771F681)>(abcd_transform[3U], abcd_transform[0U], abcd_transform[1U], abcd_transform[2U], x_transform[ 8U]); // 34
    hh_transform<S33, UINT32_C(0x6D9D6122)>(abcd_transform[2U], abcd_transform[3U], abcd_transform[0U], abcd_transform[1U], x_transform[11U]); // 35
    hh_transform<S34, UINT32_C(0xFDE5380C)>(abcd_transform[1U], abcd_transform[2U], abcd_transform[3U], abcd_transform[0U], x_transform[14U]); // 36
    hh_transform<S31, UINT32_C(0xA4BEEA44)>(abcd_transform[0U], abcd_transform[1U], abcd_transform[2U], abcd_transform[3U], x_transform[ 1U]); // 37
    hh_transform<S32, UINT32_C(0x4BDECFA9)>(abcd_transform[3U], abcd_transform[0U], abcd_transform[1U], abcd_transform[2U], x_transform[ 4U]); // 38
    hh_transform<S33, UINT32_C(0xF6BB4B60)>(abcd_transform[2U], abcd_transform[3U], abcd_transform[0U], abcd_transform[1U], x_transform[ 7U]); // 39
    hh_transform<S34, UINT32_C(0xBEBFBC70)>(abcd_transform[1U], abcd_transform[2U], abcd_transform[3U], abcd_transform[0U], x_transform[10U]); // 40
    hh_transform<S31, UINT32_C(0x289B7EC6)>(abcd_transform[0U], abcd_transform[1U], abcd_transform[2U], abcd_transform[3U], x_transform[13U]); // 41
    hh_transform<S32, UINT32_C(0xEAA127FA)>(abcd_transform[3U], abcd_transform[0U], abcd_transform[1U], abcd_transform[2U], x_transform[ 0U]); // 42
    hh_transform<S33, UINT32_C(0xD4EF3085)>(abcd_transform[2U], abcd_transform[3U], abcd_transform[0U], abcd_transform[1U], x_transform[ 3U]); // 43
    hh_transform<S34, UINT32_C(0x04881D05)>(abcd_transform[1U], abcd_transform[2U], abcd_transform[3U], abcd_transform[0U], x_transform[ 6U]); // 44
    hh_transform<S31, UINT32_C(0xD9D4D039)>(abcd_transform[0U], abcd_transform[1U], abcd_transform[2U], abcd_transform[3U], x_transform[ 9U]); // 45
    hh_transform<S32, UINT32_C(0xE6DB99E5)>(abcd_transform[3U], abcd_transform[0U], abcd_transform[1U], abcd_transform[2U], x_transform[12U]); // 46
    hh_transform<S33, UINT32_C(0x1FA27CF8)>(abcd_transform[2U], abcd_transform[3U], abcd_transform[0U], abcd_transform[1U], x_transform[15U]); // 47
    hh_transform<S34, UINT32_C(0xC4AC5665)>(abcd_transform[1U], abcd_transform[2U], abcd_transform[3U], abcd_transform[0U], x_transform[ 2U]); // 48

    // Round 4
    ii_transform<S41, UINT32_C(0xF4292244)>(abcd_transform[0U], abcd_transform[1U], abcd_transform[2U], abcd_transform[3U], x_transform[ 0U]); // 49
    ii_transform<S42, UINT32_C(0x432AFF97)>(abcd_transform[3U], abcd_transform[0U], abcd_transform[1U], abcd_transform[2U], x_transform[ 7U]); // 50
    ii_transform<S43, UINT32_C(0xAB9423A7)>(abcd_transform[2U], abcd_transform[3U], abcd_transform[0U], abcd_transform[1U], x_transform[14U]); // 51
    ii_transform<S44, UINT32_C(0xFC93A039)>(abcd_transform[1U], abcd_transform[2U], abcd_transform[3U], abcd_transform[0U], x_transform[ 5U]); // 52
    ii_transform<S41, UINT32_C(0x655B59C3)>(abcd_transform[0U], abcd_transform[1U], abcd_transform[2U], abcd_transform[3U], x_transform[12U]); // 53
    ii_transform<S42, UINT32_C(0x8F0CCC92)>(abcd_transform[3U], abcd_transform[0U], abcd_transform[1U], abcd_transform[2U], x_transform[ 3U]); // 54
    ii_transform<S43, UINT32_C(0xFFEFF47D)>(abcd_transform[2U], abcd_transform[3U], abcd_transform[0U], abcd_transform[1U], x_transform[10U]); // 55
    ii_transform<S44, UINT32_C(0x85845DD1)>(abcd_transform[1U], abcd_transform[2U], abcd_transform[3U], abcd_transform[0U], x_transform[ 1U]); // 56
    ii_transform<S41, UINT32_C(0x6FA87E4F)>(abcd_transform[0U], abcd_transform[1U], abcd_transform[2U], abcd_transform[3U], x_transform[ 8U]); // 57
    ii_transform<S42, UINT32_C(0xFE2CE6E0)>(abcd_transform[3U], abcd_transform[0U], abcd_transform[1U], abcd_transform[2U], x_transform[15U]); // 58
    ii_transform<S43, UINT32_C(0xA3014314)>(abcd_transform[2U], abcd_transform[3U], abcd_transform[0U], abcd_transform[1U], x_transform[ 6U]); // 59
    ii_transform<S44, UINT32_C(0x4E0811A1)>(abcd_transform[1U], abcd_transform[2U], abcd_transform[3U], abcd_transform[0U], x_transform[13U]); // 60
    ii_transform<S41, UINT32_C(0xF7537E82)>(abcd_transform[0U], abcd_transform[1U], abcd_transform[2U], abcd_transform[3U], x_transform[ 4U]); // 61
    ii_transform<S42, UINT32_C(0xBD3AF235)>(abcd_transform[3U], abcd_transform[0U], abcd_transform[1U], abcd_transform[2U], x_transform[11U]); // 62
    ii_transform<S43, UINT32_C(0x2AD7D2BB)>(abcd_transform[2U], abcd_transform[3U], abcd_transform[0U], abcd_transform[1U], x_transform[ 2U]); // 63
    ii_transform<S44, UINT32_C(0xEB86D391)>(abcd_transform[1U], abcd_transform[2U], abcd_transform[3U], abcd_transform[0U], x_transform[ 9U]); // 64

    // Update the state information with the transformation results.
    std::transform(digest_state.begin(),
                   digest_state.end(),
                   abcd_transform.begin(),
                   digest_state.begin(),
                   std::plus<std::uint32_t>());
  }

  std::uint32_t md5::f_bit_twiddle(const std::uint32_t& x, const std::uint32_t& y, const std::uint32_t& z)
  {
    return static_cast<std::uint32_t>(static_cast<std::uint32_t>(x & y) | static_cast<std::uint32_t>(static_cast<std::uint32_t>(~x) & z));
  }

  std::uint32_t md5::g_bit_twiddle(const std::uint32_t& x, const std::uint32_t& y, const std::uint32_t& z)
  {
    return static_cast<std::uint32_t>(static_cast<std::uint32_t>(x & z) | static_cast<std::uint32_t>(y & static_cast<std::uint32_t>(~z)));
  }

  std::uint32_t md5::h_bit_twiddle(const std::uint32_t& x, const std::uint32_t& y, const std::uint32_t& z)
  {
    return static_cast<std::uint32_t>(static_cast<std::uint32_t>(x ^ y) ^ z);
  }

  std::uint32_t md5::i_bit_twiddle(const std::uint32_t& x, const std::uint32_t& y, const std::uint32_t& z)
  {
    return static_cast<std::uint32_t>(y ^ static_cast<std::uint32_t>(x | static_cast<std::uint32_t>(~z)));
  }

  template<const std::uint_fast8_t my_s, const std::uint32_t my_ac>
  void md5::ff_transform(std::uint32_t& a, const std::uint32_t& b, const std::uint32_t& c, const std::uint32_t& d, const std::uint32_t& x)
  {
    a = static_cast<std::uint32_t>(rotate_left<my_s>(static_cast<std::uint32_t>(a + f_bit_twiddle(b, c, d)) + static_cast<std::uint32_t>(x + my_ac)) + b);
  }

  template<const std::uint_fast8_t my_s, const std::uint32_t my_ac>
  void md5::gg_transform(std::uint32_t& a, const std::uint32_t& b, const std::uint32_t& c, const std::uint32_t& d, const std::uint32_t& x)
  {
    a = static_cast<std::uint32_t>(rotate_left<my_s>(static_cast<std::uint32_t>(a + g_bit_twiddle(b, c, d)) + static_cast<std::uint32_t>(x + my_ac)) + b);
  }

  template<const std::uint_fast8_t my_s, const std::uint32_t my_ac>
  void md5::hh_transform(std::uint32_t& a, const std::uint32_t& b, const std::uint32_t& c, const std::uint32_t& d, const std::uint32_t& x)
  {
    a = static_cast<std::uint32_t>(rotate_left<my_s>(static_cast<std::uint32_t>(a + h_bit_twiddle(b, c, d)) + static_cast<std::uint32_t>(x + my_ac)) + b);
  }

  template<const std::uint_fast8_t my_s, const std::uint32_t my_ac>
  void md5::ii_transform(std::uint32_t& a, const std::uint32_t& b, const std::uint32_t& c, const std::uint32_t& d, const std::uint32_t& x)
  {
    a = static_cast<std::uint32_t>(rotate_left<my_s>(static_cast<std::uint32_t>(a + i_bit_twiddle(b, c, d)) + static_cast<std::uint32_t>(x + my_ac)) + b);
  }

  // Test code in main()...
  /*
  #include <math/checksums/md5/md5.h>

  namespace
  {
    md5 the_md5("creativity", sizeof("creativity") - 1U);
  }

  extern "C" int main()
  {
    // Initialize the Microcontroller Abstraction Layer.
    mcal::init();

    const md5::result_type the_md5_result = the_md5.get_result_and_re_initialize();

    // Start the multitasking scheduler (and never return).
    if(the_md5_result.back() == static_cast<std::uint8_t>(0x9FU))
    {
      os::start_os();
    }
  }
  */

#endif // _MD5_2012_01_13_H_
