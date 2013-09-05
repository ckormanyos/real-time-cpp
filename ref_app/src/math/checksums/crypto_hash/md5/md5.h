///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2012 - 2013.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

///////////////////////////////////////////////////////////////////////////////
//
// January 2012:
// This work has been created by Christopher Kormanyos.
// It has been specifically designed for C++11 with particular
// emphasis on portability to microcontroller platforms.
//
// The origin of this work is identified as the
// "RSA Data Security, Inc. MD5 Message-Digest Algorithm"
//
// This work is: "derived from the RSA Data Security, Inc.
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

  #include <array>
  #include <cstddef>
  #include <functional>
  #include <limits>
  #include "../crypto_hash_base.h"

  class md5 : public crypto_hash_base
  {
  public:
    typedef std::array<std::uint8_t,  16U> result_type_bytes;
    typedef std::array<std::uint32_t,  4U> result_type_dwords;

    md5() : digest_state (),
            digest_result(),
            digest_buffer() { }

    md5(const md5& other) : crypto_hash_base(other),
                            digest_state    (other.digest_state),
                            digest_result   (other.digest_result),
                            digest_buffer   (other.digest_buffer) { }

    template<typename count_type>
    md5(const std::uint8_t* data_stream, const count_type& count);

    template<typename count_type>
    md5(const char* string_stream, const count_type& count);

    template<typename unsigned_integer_type>
    md5(unsigned_integer_type u);

    virtual ~md5() { }

    md5& operator=(const md5& other)
    {
      if(this != &other)
      {
        static_cast<void>(crypto_hash_base::operator=(other));

        digest_state  = other.digest_state;
        digest_result = other.digest_result;
        digest_buffer = other.digest_buffer;
      }

      return *this;
    }

    template<typename count_type>            void process_data(const std::uint8_t* data_stream,   const count_type& count);
    template<typename count_type>            void process_data(const char*         string_stream, const count_type& count);
    template<typename unsigned_integer_type> void process_data(unsigned_integer_type u);

    result_type_bytes get_result_bytes_and_finalize_the_state();
    result_type_bytes get_result_bytes_and_nochange_the_state() const;

    result_type_dwords get_result_dwords_and_finalize_the_state();
    result_type_dwords get_result_dwords_and_nochange_the_state() const;

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

    result_type_dwords                       digest_state;   // The message digest state so far.
    result_type_bytes                        digest_result;  // The result of the message digest.
    std::array<std::uint8_t,  md5_blocksize> digest_buffer;  // The message digest buffer.

    void initialize();
    void finalize();

    void process_single_data_section(const std::uint8_t* data_stream, const std::size_t& count)
    {
      if(the_result_is_finalized)
      {
        initialize();

        the_result_is_finalized = false;
      }

      // TBD: Obtain a clear understanding of the algorithm and re-program it.
      // Continue (or start) the message digest operation.

      // Compute the number of bytes mod 64.
      std::size_t index = static_cast<std::size_t>(static_cast<std::uint_least64_t>(count_of_bits / 8U) % md5_blocksize);

      // Update the number of bits.
      count_of_bits += static_cast<std::uint_least64_t>(count) * 8U;

      // Compute the number of bytes we need to inject into the buffer.
      const std::size_t firstpart = static_cast<std::size_t>(md5_blocksize - index);

      std::size_t i = static_cast<std::size_t>(0U);

      // Transform as many times as possible.
      if(count >= firstpart)
      {
        // Fill the buffer first, then transform.
        std::copy(data_stream, data_stream + firstpart, digest_buffer.begin() + index);

        transform(digest_buffer.data());

        // Transform chunks of md5_blocksize (64 bytes).
        for(i = firstpart; (i + md5_blocksize) <= count; i += md5_blocksize)
        {
          transform(&data_stream[i]);
        }

        index = static_cast<std::size_t>(0U);
      }

      // Buffer the remaining input.
      std::copy(data_stream + i, data_stream + count, digest_buffer.begin() + index);
    }

    template<typename count_type>
    void process_extended_data_stream(const std::uint8_t* data_stream, const count_type& count)
    {
      const std::size_t section_size  = static_cast<std::size_t>(std::size_t(1U) << (std::numeric_limits<std::size_t>::digits - 1));
      const count_type  section_count = static_cast<count_type> (count / section_size);

      count_type i;

      for(i = static_cast<count_type>(0U); i < section_count; ++i)
      {
        process_single_data_section(data_stream, section_size);
      }

      process_single_data_section(data_stream, static_cast<std::size_t>(count % section_size));
    }

    void transform(const std::uint8_t* block);

    // The following are the low-level bit twiddle operations of the message digest.

    // F, G, H and I are basic MD5 functions.
    static std::uint32_t f_permutation(const std::uint32_t& x, const std::uint32_t& y, const std::uint32_t& z);
    static std::uint32_t g_permutation(const std::uint32_t& x, const std::uint32_t& y, const std::uint32_t& z);
    static std::uint32_t h_permutation(const std::uint32_t& x, const std::uint32_t& y, const std::uint32_t& z);
    static std::uint32_t i_permutation(const std::uint32_t& x, const std::uint32_t& y, const std::uint32_t& z);

    // The rotate_left function rotates x to the left by n bits.
    template<const std::uint_fast8_t n>
    static std::uint32_t rotate_left(const std::uint32_t& x)
    {
      return static_cast<std::uint32_t>(static_cast<std::uint32_t>(x << n) | static_cast<std::uint32_t>(x >> (32U - n)));
    }

    // The following are the FF, GG, HH, and II transformations for
    // rounds 1, 2, 3, and 4 of the message digest.
    template<const std::uint_fast8_t s, const std::uint32_t ac>
    static void ff_transformation(std::uint32_t& a, const std::uint32_t& b, const std::uint32_t& c, const std::uint32_t& d, const std::uint32_t& x);

    template<const std::uint_fast8_t s, const std::uint32_t ac>
    static void gg_transformation(std::uint32_t& a, const std::uint32_t& b, const std::uint32_t& c, const std::uint32_t& d, const std::uint32_t& x);

    template<const std::uint_fast8_t s, const std::uint32_t ac>
    static void hh_transformation(std::uint32_t& a, const std::uint32_t& b, const std::uint32_t& c, const std::uint32_t& d, const std::uint32_t& x);

    template<const std::uint_fast8_t s, const std::uint32_t ac>
    static void ii_transformation(std::uint32_t& a, const std::uint32_t& b, const std::uint32_t& c, const std::uint32_t& d, const std::uint32_t& x);
  };

  template<typename count_type>
  md5::md5(const std::uint8_t* data_stream, const count_type& count) : digest_state (),
                                                                       digest_result(),
                                                                       digest_buffer()
  {
    process_data(data_stream, count);
  }

  template<typename count_type>
  md5::md5(const char* string_stream, const count_type& count) : digest_state (),
                                                                 digest_result(),
                                                                 digest_buffer()
  {
    process_data(string_stream, count);
  }

  template<typename unsigned_integer_type>
  md5::md5(unsigned_integer_type u) : digest_state (),
                                      digest_result(),
                                      digest_buffer()
  {
    process_data(u);
  }

  template<typename count_type>
  void md5::process_data(const std::uint8_t* data_stream, const count_type& count)
  {
    process_extended_data_stream(data_stream, count);
  }

  template<typename count_type>
  void md5::process_data(const char* string_stream, const count_type& count)
  {
    const std::uint8_t* data_stream = static_cast<const std::uint8_t*>(static_cast<const void*>(string_stream));

    process_extended_data_stream(data_stream, count);
  }

  template<typename unsigned_integer_type>
  void md5::process_data(unsigned_integer_type u)
  {
    // Ensure that the template parameter is an unsigned integer type with radix 2, having a multiple of 8 bits.
    static_assert(   ( std::numeric_limits<unsigned_integer_type>::is_specialized  == true)
                  && ( std::numeric_limits<unsigned_integer_type>::is_integer      == true)
                  && ( std::numeric_limits<unsigned_integer_type>::is_signed       == false)
                  && ( std::numeric_limits<unsigned_integer_type>::radix           == 2)
                  && ((std::numeric_limits<unsigned_integer_type>::digits % 8)     == 0),
                  "the template type must be an unsigned integer type with radix 2, having a multiple of 8 bits");

    std::array<std::uint8_t, std::numeric_limits<unsigned_integer_type>::digits / 8> the_data;

    std::for_each(the_data.begin(),
                  the_data.end(),
                  [&u](std::uint8_t& data_value)
                  {
                    data_value = std::uint8_t(u);

                    u >>= 8;
                  });

    process_single_data_section(the_data.data(), the_data.size());
  }

  md5::result_type_bytes md5::get_result_bytes_and_finalize_the_state()
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

  md5::result_type_bytes md5::get_result_bytes_and_nochange_the_state() const
  {
    // Make a local copy of the message digest.
    md5 temp_md5(*this);

    // Finalize the local copy of the message digest,
    // and return the final result from the copied object.
    return temp_md5.get_result_bytes_and_finalize_the_state();
  }

  md5::result_type_dwords md5::get_result_dwords_and_finalize_the_state()
  {
    if((!the_result_is_finalized))
    {
      // Finalize the result.
      finalize();

      // Extract the message digest result from the message digest state.
      // Even though we are only getting the dword representation in this
      // subroutine, we will prepare the byte representation as well.
      encode_uint32_input_to_uint8_output(digest_state.data(),
                                          digest_state.data() + digest_state.size(),
                                          digest_result.data());

      the_result_is_finalized = true;
    }

    return digest_state;
  }

  md5::result_type_dwords md5::get_result_dwords_and_nochange_the_state() const
  {
    // Make a local copy of the message digest.
    md5 temp_md5(*this);

    // Finalize the local copy of the message digest,
    // and return the final result from the copied object.
    temp_md5.finalize();

    return temp_md5.digest_state;
  }

  void md5::initialize()
  {
    // Clear the bit counters.
    count_of_bits = 0U;

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
    // This ends a message digest operation.

    // Create and initialize the padding.
    std::array<std::uint8_t, md5_blocksize - 8U> padding;
    padding[0U] = static_cast<std::uint8_t>(md5_blocksize * 2U);
    std::fill(padding.begin() + 1U, padding.end(), static_cast<std::uint8_t>(0U));

    // Encode the number of bits.
    const std::array<std::uint32_t, 2U> count_of_bits_non_encoded =
    {{
      std::uint32_t(count_of_bits),
      std::uint32_t(count_of_bits >> 32)
    }};

    std::array<std::uint8_t, 8U> count_of_bits_encoded;
    encode_uint32_input_to_uint8_output(count_of_bits_non_encoded.data(),
                                        count_of_bits_non_encoded.data() + count_of_bits_non_encoded.size(),
                                        count_of_bits_encoded.data());

    // Pad out to 56 mod 64.
    const std::size_t index = static_cast<std::size_t>(static_cast<std::uint32_t>(count_of_bits_non_encoded[0U] / 8U) % md5_blocksize);

    const std::size_t pad_len = ((index < static_cast<std::size_t>(md5_blocksize - 8U))
                                   ? (static_cast<std::size_t>( md5_blocksize       - 8U) - index)
                                   : (static_cast<std::size_t>((md5_blocksize * 2U) - 8U) - index));

    // Update the digest state with the padding.
    process_data(padding.data(), pad_len);

    // Update the digest state with the encoded number of bits.
    process_data(count_of_bits_encoded.data(), 8U);
  }

  void md5::transform(const std::uint8_t* block)
  {
    // Apply the MD5 algorithm to a block.

    std::array<std::uint32_t, md5_blocksize / 4U> transform_block;

    std::array<std::uint32_t, 4U> digest_state_tmp = digest_state;

    decode_uint8_input_to_uint32_output(block, block + md5_blocksize, transform_block.data());

    // Round 1
    ff_transformation<S11, UINT32_C(0xD76AA478)>(digest_state_tmp[0U], digest_state_tmp[1U], digest_state_tmp[2U], digest_state_tmp[3U], transform_block[ 0U]); //  1
    ff_transformation<S12, UINT32_C(0xE8C7B756)>(digest_state_tmp[3U], digest_state_tmp[0U], digest_state_tmp[1U], digest_state_tmp[2U], transform_block[ 1U]); //  2
    ff_transformation<S13, UINT32_C(0x242070DB)>(digest_state_tmp[2U], digest_state_tmp[3U], digest_state_tmp[0U], digest_state_tmp[1U], transform_block[ 2U]); //  3
    ff_transformation<S14, UINT32_C(0xC1BDCEEE)>(digest_state_tmp[1U], digest_state_tmp[2U], digest_state_tmp[3U], digest_state_tmp[0U], transform_block[ 3U]); //  4
    ff_transformation<S11, UINT32_C(0xF57C0FAF)>(digest_state_tmp[0U], digest_state_tmp[1U], digest_state_tmp[2U], digest_state_tmp[3U], transform_block[ 4U]); //  5
    ff_transformation<S12, UINT32_C(0x4787C62A)>(digest_state_tmp[3U], digest_state_tmp[0U], digest_state_tmp[1U], digest_state_tmp[2U], transform_block[ 5U]); //  6
    ff_transformation<S13, UINT32_C(0xA8304613)>(digest_state_tmp[2U], digest_state_tmp[3U], digest_state_tmp[0U], digest_state_tmp[1U], transform_block[ 6U]); //  7
    ff_transformation<S14, UINT32_C(0xFD469501)>(digest_state_tmp[1U], digest_state_tmp[2U], digest_state_tmp[3U], digest_state_tmp[0U], transform_block[ 7U]); //  8
    ff_transformation<S11, UINT32_C(0x698098D8)>(digest_state_tmp[0U], digest_state_tmp[1U], digest_state_tmp[2U], digest_state_tmp[3U], transform_block[ 8U]); //  9
    ff_transformation<S12, UINT32_C(0x8B44F7AF)>(digest_state_tmp[3U], digest_state_tmp[0U], digest_state_tmp[1U], digest_state_tmp[2U], transform_block[ 9U]); // 10
    ff_transformation<S13, UINT32_C(0xFFFF5BB1)>(digest_state_tmp[2U], digest_state_tmp[3U], digest_state_tmp[0U], digest_state_tmp[1U], transform_block[10U]); // 11
    ff_transformation<S14, UINT32_C(0x895CD7BE)>(digest_state_tmp[1U], digest_state_tmp[2U], digest_state_tmp[3U], digest_state_tmp[0U], transform_block[11U]); // 12
    ff_transformation<S11, UINT32_C(0x6B901122)>(digest_state_tmp[0U], digest_state_tmp[1U], digest_state_tmp[2U], digest_state_tmp[3U], transform_block[12U]); // 13
    ff_transformation<S12, UINT32_C(0xFD987193)>(digest_state_tmp[3U], digest_state_tmp[0U], digest_state_tmp[1U], digest_state_tmp[2U], transform_block[13U]); // 14
    ff_transformation<S13, UINT32_C(0xA679438E)>(digest_state_tmp[2U], digest_state_tmp[3U], digest_state_tmp[0U], digest_state_tmp[1U], transform_block[14U]); // 15
    ff_transformation<S14, UINT32_C(0x49B40821)>(digest_state_tmp[1U], digest_state_tmp[2U], digest_state_tmp[3U], digest_state_tmp[0U], transform_block[15U]); // 16

    // Round 2
    gg_transformation<S21, UINT32_C(0xF61E2562)>(digest_state_tmp[0U], digest_state_tmp[1U], digest_state_tmp[2U], digest_state_tmp[3U], transform_block[ 1U]); // 17
    gg_transformation<S22, UINT32_C(0xC040B340)>(digest_state_tmp[3U], digest_state_tmp[0U], digest_state_tmp[1U], digest_state_tmp[2U], transform_block[ 6U]); // 18
    gg_transformation<S23, UINT32_C(0x265E5A51)>(digest_state_tmp[2U], digest_state_tmp[3U], digest_state_tmp[0U], digest_state_tmp[1U], transform_block[11U]); // 19
    gg_transformation<S24, UINT32_C(0xE9B6C7AA)>(digest_state_tmp[1U], digest_state_tmp[2U], digest_state_tmp[3U], digest_state_tmp[0U], transform_block[ 0U]); // 20
    gg_transformation<S21, UINT32_C(0xD62F105D)>(digest_state_tmp[0U], digest_state_tmp[1U], digest_state_tmp[2U], digest_state_tmp[3U], transform_block[ 5U]); // 21
    gg_transformation<S22, UINT32_C(0x02441453)>(digest_state_tmp[3U], digest_state_tmp[0U], digest_state_tmp[1U], digest_state_tmp[2U], transform_block[10U]); // 22
    gg_transformation<S23, UINT32_C(0xD8A1E681)>(digest_state_tmp[2U], digest_state_tmp[3U], digest_state_tmp[0U], digest_state_tmp[1U], transform_block[15U]); // 23
    gg_transformation<S24, UINT32_C(0xE7D3FBC8)>(digest_state_tmp[1U], digest_state_tmp[2U], digest_state_tmp[3U], digest_state_tmp[0U], transform_block[ 4U]); // 24
    gg_transformation<S21, UINT32_C(0x21E1CDE6)>(digest_state_tmp[0U], digest_state_tmp[1U], digest_state_tmp[2U], digest_state_tmp[3U], transform_block[ 9U]); // 25
    gg_transformation<S22, UINT32_C(0xC33707D6)>(digest_state_tmp[3U], digest_state_tmp[0U], digest_state_tmp[1U], digest_state_tmp[2U], transform_block[14U]); // 26
    gg_transformation<S23, UINT32_C(0xF4D50D87)>(digest_state_tmp[2U], digest_state_tmp[3U], digest_state_tmp[0U], digest_state_tmp[1U], transform_block[ 3U]); // 27
    gg_transformation<S24, UINT32_C(0x455A14ED)>(digest_state_tmp[1U], digest_state_tmp[2U], digest_state_tmp[3U], digest_state_tmp[0U], transform_block[ 8U]); // 28
    gg_transformation<S21, UINT32_C(0xA9E3E905)>(digest_state_tmp[0U], digest_state_tmp[1U], digest_state_tmp[2U], digest_state_tmp[3U], transform_block[13U]); // 29
    gg_transformation<S22, UINT32_C(0xFCEFA3F8)>(digest_state_tmp[3U], digest_state_tmp[0U], digest_state_tmp[1U], digest_state_tmp[2U], transform_block[ 2U]); // 30
    gg_transformation<S23, UINT32_C(0x676F02D9)>(digest_state_tmp[2U], digest_state_tmp[3U], digest_state_tmp[0U], digest_state_tmp[1U], transform_block[ 7U]); // 31
    gg_transformation<S24, UINT32_C(0x8D2A4C8A)>(digest_state_tmp[1U], digest_state_tmp[2U], digest_state_tmp[3U], digest_state_tmp[0U], transform_block[12U]); // 32

    // Round 3
    hh_transformation<S31, UINT32_C(0xFFFA3942)>(digest_state_tmp[0U], digest_state_tmp[1U], digest_state_tmp[2U], digest_state_tmp[3U], transform_block[ 5U]); // 33
    hh_transformation<S32, UINT32_C(0x8771F681)>(digest_state_tmp[3U], digest_state_tmp[0U], digest_state_tmp[1U], digest_state_tmp[2U], transform_block[ 8U]); // 34
    hh_transformation<S33, UINT32_C(0x6D9D6122)>(digest_state_tmp[2U], digest_state_tmp[3U], digest_state_tmp[0U], digest_state_tmp[1U], transform_block[11U]); // 35
    hh_transformation<S34, UINT32_C(0xFDE5380C)>(digest_state_tmp[1U], digest_state_tmp[2U], digest_state_tmp[3U], digest_state_tmp[0U], transform_block[14U]); // 36
    hh_transformation<S31, UINT32_C(0xA4BEEA44)>(digest_state_tmp[0U], digest_state_tmp[1U], digest_state_tmp[2U], digest_state_tmp[3U], transform_block[ 1U]); // 37
    hh_transformation<S32, UINT32_C(0x4BDECFA9)>(digest_state_tmp[3U], digest_state_tmp[0U], digest_state_tmp[1U], digest_state_tmp[2U], transform_block[ 4U]); // 38
    hh_transformation<S33, UINT32_C(0xF6BB4B60)>(digest_state_tmp[2U], digest_state_tmp[3U], digest_state_tmp[0U], digest_state_tmp[1U], transform_block[ 7U]); // 39
    hh_transformation<S34, UINT32_C(0xBEBFBC70)>(digest_state_tmp[1U], digest_state_tmp[2U], digest_state_tmp[3U], digest_state_tmp[0U], transform_block[10U]); // 40
    hh_transformation<S31, UINT32_C(0x289B7EC6)>(digest_state_tmp[0U], digest_state_tmp[1U], digest_state_tmp[2U], digest_state_tmp[3U], transform_block[13U]); // 41
    hh_transformation<S32, UINT32_C(0xEAA127FA)>(digest_state_tmp[3U], digest_state_tmp[0U], digest_state_tmp[1U], digest_state_tmp[2U], transform_block[ 0U]); // 42
    hh_transformation<S33, UINT32_C(0xD4EF3085)>(digest_state_tmp[2U], digest_state_tmp[3U], digest_state_tmp[0U], digest_state_tmp[1U], transform_block[ 3U]); // 43
    hh_transformation<S34, UINT32_C(0x04881D05)>(digest_state_tmp[1U], digest_state_tmp[2U], digest_state_tmp[3U], digest_state_tmp[0U], transform_block[ 6U]); // 44
    hh_transformation<S31, UINT32_C(0xD9D4D039)>(digest_state_tmp[0U], digest_state_tmp[1U], digest_state_tmp[2U], digest_state_tmp[3U], transform_block[ 9U]); // 45
    hh_transformation<S32, UINT32_C(0xE6DB99E5)>(digest_state_tmp[3U], digest_state_tmp[0U], digest_state_tmp[1U], digest_state_tmp[2U], transform_block[12U]); // 46
    hh_transformation<S33, UINT32_C(0x1FA27CF8)>(digest_state_tmp[2U], digest_state_tmp[3U], digest_state_tmp[0U], digest_state_tmp[1U], transform_block[15U]); // 47
    hh_transformation<S34, UINT32_C(0xC4AC5665)>(digest_state_tmp[1U], digest_state_tmp[2U], digest_state_tmp[3U], digest_state_tmp[0U], transform_block[ 2U]); // 48

    // Round 4
    ii_transformation<S41, UINT32_C(0xF4292244)>(digest_state_tmp[0U], digest_state_tmp[1U], digest_state_tmp[2U], digest_state_tmp[3U], transform_block[ 0U]); // 49
    ii_transformation<S42, UINT32_C(0x432AFF97)>(digest_state_tmp[3U], digest_state_tmp[0U], digest_state_tmp[1U], digest_state_tmp[2U], transform_block[ 7U]); // 50
    ii_transformation<S43, UINT32_C(0xAB9423A7)>(digest_state_tmp[2U], digest_state_tmp[3U], digest_state_tmp[0U], digest_state_tmp[1U], transform_block[14U]); // 51
    ii_transformation<S44, UINT32_C(0xFC93A039)>(digest_state_tmp[1U], digest_state_tmp[2U], digest_state_tmp[3U], digest_state_tmp[0U], transform_block[ 5U]); // 52
    ii_transformation<S41, UINT32_C(0x655B59C3)>(digest_state_tmp[0U], digest_state_tmp[1U], digest_state_tmp[2U], digest_state_tmp[3U], transform_block[12U]); // 53
    ii_transformation<S42, UINT32_C(0x8F0CCC92)>(digest_state_tmp[3U], digest_state_tmp[0U], digest_state_tmp[1U], digest_state_tmp[2U], transform_block[ 3U]); // 54
    ii_transformation<S43, UINT32_C(0xFFEFF47D)>(digest_state_tmp[2U], digest_state_tmp[3U], digest_state_tmp[0U], digest_state_tmp[1U], transform_block[10U]); // 55
    ii_transformation<S44, UINT32_C(0x85845DD1)>(digest_state_tmp[1U], digest_state_tmp[2U], digest_state_tmp[3U], digest_state_tmp[0U], transform_block[ 1U]); // 56
    ii_transformation<S41, UINT32_C(0x6FA87E4F)>(digest_state_tmp[0U], digest_state_tmp[1U], digest_state_tmp[2U], digest_state_tmp[3U], transform_block[ 8U]); // 57
    ii_transformation<S42, UINT32_C(0xFE2CE6E0)>(digest_state_tmp[3U], digest_state_tmp[0U], digest_state_tmp[1U], digest_state_tmp[2U], transform_block[15U]); // 58
    ii_transformation<S43, UINT32_C(0xA3014314)>(digest_state_tmp[2U], digest_state_tmp[3U], digest_state_tmp[0U], digest_state_tmp[1U], transform_block[ 6U]); // 59
    ii_transformation<S44, UINT32_C(0x4E0811A1)>(digest_state_tmp[1U], digest_state_tmp[2U], digest_state_tmp[3U], digest_state_tmp[0U], transform_block[13U]); // 60
    ii_transformation<S41, UINT32_C(0xF7537E82)>(digest_state_tmp[0U], digest_state_tmp[1U], digest_state_tmp[2U], digest_state_tmp[3U], transform_block[ 4U]); // 61
    ii_transformation<S42, UINT32_C(0xBD3AF235)>(digest_state_tmp[3U], digest_state_tmp[0U], digest_state_tmp[1U], digest_state_tmp[2U], transform_block[11U]); // 62
    ii_transformation<S43, UINT32_C(0x2AD7D2BB)>(digest_state_tmp[2U], digest_state_tmp[3U], digest_state_tmp[0U], digest_state_tmp[1U], transform_block[ 2U]); // 63
    ii_transformation<S44, UINT32_C(0xEB86D391)>(digest_state_tmp[1U], digest_state_tmp[2U], digest_state_tmp[3U], digest_state_tmp[0U], transform_block[ 9U]); // 64

    // Update the state information with the transformation results.
    std::transform(digest_state.begin(),
                   digest_state.end(),
                   digest_state_tmp.begin(),
                   digest_state.begin(),
                   std::plus<std::uint32_t>());
  }

  std::uint32_t md5::f_permutation(const std::uint32_t& x, const std::uint32_t& y, const std::uint32_t& z)
  {
    return static_cast<std::uint32_t>(static_cast<std::uint32_t>(x & y) | static_cast<std::uint32_t>(static_cast<std::uint32_t>(~x) & z));
  }

  std::uint32_t md5::g_permutation(const std::uint32_t& x, const std::uint32_t& y, const std::uint32_t& z)
  {
    return static_cast<std::uint32_t>(static_cast<std::uint32_t>(x & z) | static_cast<std::uint32_t>(y & static_cast<std::uint32_t>(~z)));
  }

  std::uint32_t md5::h_permutation(const std::uint32_t& x, const std::uint32_t& y, const std::uint32_t& z)
  {
    return static_cast<std::uint32_t>(static_cast<std::uint32_t>(x ^ y) ^ z);
  }

  std::uint32_t md5::i_permutation(const std::uint32_t& x, const std::uint32_t& y, const std::uint32_t& z)
  {
    return static_cast<std::uint32_t>(y ^ static_cast<std::uint32_t>(x | static_cast<std::uint32_t>(~z)));
  }

  template<const std::uint_fast8_t my_s, const std::uint32_t my_ac>
  void md5::ff_transformation(std::uint32_t& a, const std::uint32_t& b, const std::uint32_t& c, const std::uint32_t& d, const std::uint32_t& x)
  {
    a = static_cast<std::uint32_t>(rotate_left<my_s>(static_cast<std::uint32_t>(a + f_permutation(b, c, d)) + static_cast<std::uint32_t>(x + my_ac)) + b);
  }

  template<const std::uint_fast8_t my_s, const std::uint32_t my_ac>
  void md5::gg_transformation(std::uint32_t& a, const std::uint32_t& b, const std::uint32_t& c, const std::uint32_t& d, const std::uint32_t& x)
  {
    a = static_cast<std::uint32_t>(rotate_left<my_s>(static_cast<std::uint32_t>(a + g_permutation(b, c, d)) + static_cast<std::uint32_t>(x + my_ac)) + b);
  }

  template<const std::uint_fast8_t my_s, const std::uint32_t my_ac>
  void md5::hh_transformation(std::uint32_t& a, const std::uint32_t& b, const std::uint32_t& c, const std::uint32_t& d, const std::uint32_t& x)
  {
    a = static_cast<std::uint32_t>(rotate_left<my_s>(static_cast<std::uint32_t>(a + h_permutation(b, c, d)) + static_cast<std::uint32_t>(x + my_ac)) + b);
  }

  template<const std::uint_fast8_t my_s, const std::uint32_t my_ac>
  void md5::ii_transformation(std::uint32_t& a, const std::uint32_t& b, const std::uint32_t& c, const std::uint32_t& d, const std::uint32_t& x)
  {
    a = static_cast<std::uint32_t>(rotate_left<my_s>(static_cast<std::uint32_t>(a + i_permutation(b, c, d)) + static_cast<std::uint32_t>(x + my_ac)) + b);
  }

  // Test code in main()...
  /*
  #include <math/checksums/crypto_hash/md5/md5.h>

  namespace
  {
    md5 the_md5("creativity", static_cast<std::uint_least8_t>(sizeof("creativity") - 1U));
  }

  extern "C" int main()
  {
    // Initialize the Microcontroller Abstraction Layer.
    mcal::init();

    const md5::result_type_dwords the_md5_result = the_md5.get_result_dwords_and_finalize_the_state();

    // Start the multitasking scheduler (and never return).
    if(the_md5_result.back() == UINT32_C(0x9F78BFB7))
    {
      os::start_os();
    }
  }
  */

#endif // _MD5_2012_01_13_H_
