
///////////////////////////////////////////////////////////////////////////////
// \license BCP 78
// sha512 can not be redistributed or modified with a license less
// restrictive than BCP 78.
//

///////////////////////////////////////////////////////////////////////////////
//
// This work has been created by Christopher Kormanyos.
// This work is an implementation of sha512 that has been specifically
// designed for C++. The implementation places particular
// emphasis on portability to microcontroller platforms.
//
// This work has been derived from:
// "RFC 4868 HMAC-SHA512, SHA512, and SHA512 in IPsec May 2007".
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

// Note: SHA224, 256, 384, 512 are from RFC 4634, not from RFC 4868

#ifndef _SHA512_2013_10_21_H_
  #define _SHA512_2013_10_21_H_

  #include <array>
  #include <cstddef>
  #include <functional>
  #include "crypto_hash_base.h"

  template <typename my_count_type>
  class sha512 : public crypto_hash_base
  {
  public:
    typedef my_count_type                   count_type;
    typedef std::array<std::uint8_t,   64U> result_type_as_bytes;
    typedef std::array<char,          128U> result_type_as_chars;
    typedef std::array<std::uint64_t,   8U> result_type_as_integral_values;

    static_assert(   ( std::numeric_limits<count_type>::is_specialized == true)
                  && ( std::numeric_limits<count_type>::is_integer     == true)
                  && ( std::numeric_limits<count_type>::is_signed      == false)
                  && ( std::numeric_limits<count_type>::radix          == 2)
                  && ((std::numeric_limits<count_type>::digits % 8)    == 0),
                  "the count type must be an unsigned integer with radix 2, having a multiple of 8 bits");

    sha512();
    sha512(const std::uint8_t* data_bytes, count_type message_length);
    sha512(const char*         data_chars, count_type message_length);
    template<typename unsigned_integer_type> sha512(unsigned_integer_type u);
    sha512(const sha512& other);
    sha512& operator=(const sha512& other);

    void process_data(const std::uint8_t* data_bytes, count_type message_length);

    void process_data(const char* data_chars, count_type message_length)
    {
      process_data(static_cast<const std::uint8_t*>(static_cast<const void*>(data_chars)), message_length);
    }

    template<typename unsigned_integer_type> void process_data(unsigned_integer_type u);

    result_type_as_bytes get_result_as_bytes_and_finalize_the_state();
    result_type_as_bytes get_result_as_bytes_and_nochange_the_state() const;

    result_type_as_integral_values get_result_as_integral_values_and_finalize_the_state();
    result_type_as_integral_values get_result_as_integral_values_and_nochange_the_state() const;

    result_type_as_chars get_result_as_chars_and_finalize_the_state();
    result_type_as_chars get_result_as_chars_and_nochange_the_state() const;

  private:
    static const std::uint_least8_t sha512_blocksize = 128U;

    static_assert(sha512_blocksize == static_cast<std::uint_least8_t>(128U),
                  "the block size must exactly equal 128");

    typedef std::array<std::uint8_t,  sha512_blocksize> message_block_type;
    typedef std::array<std::uint64_t,              80U> transform_block_type;

    result_type_as_integral_values          message_hash;
    count_type                              message_index;
    count_type                              message_length_total;
    const std::uint8_t*                     the_message;

    void perform_algorithm();
    void finalize();
    void reset();

      // BSIG0
      static std::uint64_t transform_function1(const std::uint64_t& the_qword)
      {
        return std::uint64_t(  circular_right_shift<28U>(the_qword)
                             ^ circular_right_shift<34U>(the_qword)
                             ^ circular_right_shift<39U>(the_qword));
      }

      // BSIG1
      static std::uint64_t transform_function2(const std::uint64_t& the_qword)
      {
        return std::uint64_t(  circular_right_shift<14U>(the_qword)
                             ^ circular_right_shift<18U>(the_qword)
                             ^ circular_right_shift<41U>(the_qword));
      }

      // SSIG0
      static std::uint64_t transform_function3(const std::uint64_t& the_qword)
      {
        return std::uint64_t(  circular_right_shift< 1U>(the_qword)
                             ^ circular_right_shift< 8U>(the_qword)
                             ^ std::uint64_t(the_qword >>  7U));
      }

      // SSIG1
      static std::uint64_t transform_function4(const std::uint64_t& the_qword)
      {
        return std::uint64_t(  circular_right_shift<19U>(the_qword)
                             ^ circular_right_shift<61U>(the_qword)
                             ^ std::uint64_t(the_qword >>  6U));
      }
  };

  template <typename my_count_type>
  sha512<my_count_type>::sha512()
  {
  }

  template <typename my_count_type>
  sha512<my_count_type>::sha512(const std::uint8_t* data_bytes, count_type message_length)
  {
    process_data(data_bytes, message_length);
  }

  template <typename my_count_type>
  sha512<my_count_type>::sha512(const char* data_chars, count_type message_length)
  {
    process_data(static_cast<const std::uint8_t*>(static_cast<const void*>(data_chars)), message_length);
  }

  template<typename my_count_type>
  template<typename unsigned_integer_type>
  sha512<my_count_type>::sha512(unsigned_integer_type u)
  {
    process_data(u);
  }

  template <typename my_count_type>
  sha512<my_count_type>::sha512(const sha512& other) : crypto_hash_base    (other),
                                                       message_length_total(other.message_length_total),
                                                       message_hash        (other.message_hash)
  {
  }

  template <typename my_count_type>
  sha512<my_count_type>& sha512<my_count_type>::operator=(const sha512& other)
  {
    if(this != &other)
    {
      static_cast<void>(crypto_hash_base::operator=(other));

      message_length_total = other.message_length_total;
      message_hash         = other.message_hash;
    }

    return *this;
  }

  template <typename my_count_type>
  void sha512<my_count_type>::process_data(const std::uint8_t* data_bytes, count_type message_length)
  {
    if(the_result_is_finalized) { reset(); }

    the_message = data_bytes;

    while(message_length != static_cast<count_type>(0U))
    {
      ++message_block_index;
      ++message_length_total;

      if(message_block_index == sha512_blocksize)
      {
        perform_algorithm();

        message_block_index = static_cast<std::uint_least8_t>(0U);
        ++message_index;
      }

      --message_length;
    }
  }

  template<typename my_count_type>
  template<typename unsigned_integer_type>
  void sha512<my_count_type>::process_data(unsigned_integer_type u)
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

    process_data(the_data.data(), static_cast<count_type>(the_data.size()));
  }

  template <typename my_count_type>
  void sha512<my_count_type>::perform_algorithm()
  {
    // Apply the hash algorithm to a full data block.

    static const std::array<std::uint64_t, 80U> constants =
    {{
      UINT64_C(0x428A2F98D728AE22), UINT64_C(0x7137449123EF65CD), UINT64_C(0xB5C0FBCFEC4D3B2F), UINT64_C(0xE9B5DBA58189DBBC),
      UINT64_C(0x3956C25BF348B538), UINT64_C(0x59F111F1B605D019), UINT64_C(0x923F82A4AF194F9B), UINT64_C(0xAB1C5ED5DA6D8118),
      UINT64_C(0xD807AA98A3030242), UINT64_C(0x12835B0145706FBE), UINT64_C(0x243185BE4EE4B28C), UINT64_C(0x550C7DC3D5FFB4E2),
      UINT64_C(0x72BE5D74F27B896F), UINT64_C(0x80DEB1FE3B1696B1), UINT64_C(0x9BDC06A725C71235), UINT64_C(0xC19BF174CF692694),
      UINT64_C(0xE49B69C19EF14AD2), UINT64_C(0xEFBE4786384F25E3), UINT64_C(0x0FC19DC68B8CD5B5), UINT64_C(0x240CA1CC77AC9C65),
      UINT64_C(0x2DE92C6F592B0275), UINT64_C(0x4A7484AA6EA6E483), UINT64_C(0x5CB0A9DCBD41FBD4), UINT64_C(0x76F988DA831153B5),
      UINT64_C(0x983E5152EE66DFAB), UINT64_C(0xA831C66D2DB43210), UINT64_C(0xB00327C898FB213F), UINT64_C(0xBF597FC7BEEF0EE4),
      UINT64_C(0xC6E00BF33DA88FC2), UINT64_C(0xD5A79147930AA725), UINT64_C(0x06CA6351E003826F), UINT64_C(0x142929670A0E6E70),
      UINT64_C(0x27B70A8546D22FFC), UINT64_C(0x2E1B21385C26C926), UINT64_C(0x4D2C6DFC5AC42AED), UINT64_C(0x53380D139D95B3DF),
      UINT64_C(0x650A73548BAF63DE), UINT64_C(0x766A0ABB3C77B2A8), UINT64_C(0x81C2C92E47EDAEE6), UINT64_C(0x92722C851482353B),
      UINT64_C(0xA2BFE8A14CF10364), UINT64_C(0xA81A664BBC423001), UINT64_C(0xC24B8B70D0F89791), UINT64_C(0xC76C51A30654BE30),
      UINT64_C(0xD192E819D6EF5218), UINT64_C(0xD69906245565A910), UINT64_C(0xF40E35855771202A), UINT64_C(0x106AA07032BBD1B8),
      UINT64_C(0x19A4C116B8D2D0C8), UINT64_C(0x1E376C085141AB53), UINT64_C(0x2748774CDF8EEB99), UINT64_C(0x34B0BCB5E19B48A8),
      UINT64_C(0x391C0CB3C5C95A63), UINT64_C(0x4ED8AA4AE3418ACB), UINT64_C(0x5B9CCA4F7763E373), UINT64_C(0x682E6FF3D6B2B8A3),
      UINT64_C(0x748F82EE5DEFB2FC), UINT64_C(0x78A5636F43172F60), UINT64_C(0x84C87814A1F0AB72), UINT64_C(0x8CC702081A6439EC),
      UINT64_C(0x90BEFFFA23631E28), UINT64_C(0xA4506CEBDE82BDE9), UINT64_C(0xBEF9A3F7B2C67915), UINT64_C(0xC67178F2E372532B),
      UINT64_C(0xCA273ECEEA26619C), UINT64_C(0xD186B8C721C0C207), UINT64_C(0xEADA7DD6CDE0EB1E), UINT64_C(0xF57D4F7FEE6ED178),
      UINT64_C(0x06F067AA72176FBA), UINT64_C(0x0A637DC5A2C898A6), UINT64_C(0x113F9804BEF90DAE), UINT64_C(0x1B710B35131C471B),
      UINT64_C(0x28DB77F523047D84), UINT64_C(0x32CAAB7B40C72493), UINT64_C(0x3C9EBE0A15C9BEBC), UINT64_C(0x431D67C49C100D4C),
      UINT64_C(0x4CC5D4BECB3E42B6), UINT64_C(0x597F299CFC657E2A), UINT64_C(0x5FCB6FAB3AD6FAEC), UINT64_C(0x6C44198C4A475817)
    }};

    typedef std::uint64_t(*function_type)(const std::uint64_t&);

    static const std::array<function_type, 4U> functions =
    {{
      transform_function1,
      transform_function2,
      transform_function3,
      transform_function4
    }};

    transform_block_type transform_block;

    convert_uint8_input_to_uint64_output_reverse(the_message + sha512_blocksize *  message_index,
                                                 the_message + sha512_blocksize * (message_index + 1U),
                                                 transform_block.data());

    for(std::uint_fast8_t loop_counter = static_cast<std::uint_fast8_t>(16U); loop_counter < static_cast<std::uint_fast8_t>(80U); ++loop_counter)
    {
      transform_block[loop_counter] =   functions[3U](transform_block[loop_counter - 2U])
                                      + transform_block[loop_counter - 7U]
                                      + functions[2U](transform_block[loop_counter - 15U])
                                      + transform_block[loop_counter - 16U];
    }

    result_type_as_integral_values hash_tmp = message_hash;

    for(std::uint_fast8_t loop_counter = static_cast<std::uint_fast8_t>(0U); loop_counter < static_cast<std::uint_fast8_t>(80U); ++loop_counter)
    {
      const std::uint64_t tmp1 =   hash_tmp[7U]
                                 + functions[1U](hash_tmp[4U])
                                 + std::uint64_t(std::uint64_t(hash_tmp[4U] & hash_tmp[5U]) ^ std::uint64_t(std::uint64_t(~hash_tmp[4U]) & hash_tmp[6U]))
                                 + constants[loop_counter]
                                 + transform_block[loop_counter];

      const std::uint64_t tmp2 =   functions[0U](hash_tmp[0U])
                                 + std::uint64_t(std::uint64_t(hash_tmp[0U] & hash_tmp[1U]) ^ std::uint64_t(hash_tmp[0U] & hash_tmp[2U]) ^ std::uint64_t(hash_tmp[1U] & hash_tmp[2U]));

      hash_tmp[7U] = hash_tmp[6U];
      hash_tmp[6U] = hash_tmp[5U];
      hash_tmp[5U] = hash_tmp[4U];
      hash_tmp[4U] = hash_tmp[3U] + tmp1;
      hash_tmp[3U] = hash_tmp[2U];
      hash_tmp[2U] = hash_tmp[1U];
      hash_tmp[1U] = hash_tmp[0U];
      hash_tmp[0U] = tmp1 + tmp2;
    }

    // Update the hash state with the transformation results.
    std::transform(message_hash.cbegin     (),
                   message_hash.cend       (),
                   hash_tmp.cbegin         (),
                   message_hash.begin      (),
                   std::plus<std::uint64_t>());
  }

  template <typename my_count_type>
  void sha512<my_count_type>::finalize()
  {
    message_block_type the_last_message_block;
    std::copy((the_message + sha512_blocksize*message_index),
              (the_message + sha512_blocksize*message_index + message_block_index),
              (the_last_message_block.begin()));

    // Create the padding. Begin by setting the leading padding byte to 0x80.
    the_last_message_block[message_block_index] = static_cast<std::uint8_t>(0x80U);

    ++message_block_index;

    // Fill the rest of the padding bytes with zero.
    std::fill(the_last_message_block.begin() + message_block_index,
              the_last_message_block.end(),
              static_cast<std::uint8_t>(0U));

    // Do we need an extra block? If so, then transform the
    // current block and pad an additional block.
    if(message_block_index > static_cast<std::uint_least8_t>(sha512_blocksize - 16U))
    {
      message_index = static_cast<count_type>(0U);
      the_message = the_last_message_block.data();

      perform_algorithm();

      the_last_message_block.fill(static_cast<std::uint8_t>(0U));
    }

    // Encode the number of bits. Simultaneously convert the number of bytes
    // to the number of bits by performing a left-shift of 3 on the byte-array.
    // The sha512 stores the 16 bytes of the bit counter in reverse order,
    // with the lowest byte being stored at the highest position of the buffer
    std::uint_least8_t carry = static_cast<std::uint_least8_t>(0U);

    std::for_each(the_last_message_block.rbegin(),
                  the_last_message_block.rbegin() + 16U,
                  [&carry, this](std::uint8_t& the_byte)
                  {
                    const std::uint_least16_t the_word = static_cast<std::uint_least16_t>(this->message_length_total) << 3;

                    the_byte = static_cast<std::uint8_t>(the_word | carry);

                    (this->message_length_total) >>= 8;

                    carry = static_cast<std::uint_least8_t>(the_word >> 8) & static_cast<std::uint_least8_t>(0x07U);
                  });

    message_index = static_cast<count_type>(0U);
    the_message = the_last_message_block.data();

    perform_algorithm();

    the_result_is_finalized = true;
  }

  template<typename my_count_type>
  void sha512<my_count_type>::reset()
  {
    message_hash[0U] = UINT64_C(0x6A09E667F3BCC908);
    message_hash[1U] = UINT64_C(0xBB67AE8584CAA73B);
    message_hash[2U] = UINT64_C(0x3C6EF372FE94F82B);
    message_hash[3U] = UINT64_C(0xA54FF53A5F1D36F1);
    message_hash[4U] = UINT64_C(0x510E527FADE682D1);
    message_hash[5U] = UINT64_C(0x9B05688C2B3E6C1F);
    message_hash[6U] = UINT64_C(0x1F83D9ABFB41BD6B);
    message_hash[7U] = UINT64_C(0x5BE0CD19137E2179);

    the_result_is_finalized = false;
    message_length_total    = static_cast<count_type>(0U);
    message_block_index     = static_cast<std::uint_least8_t>(0U);
    message_index           = static_cast<count_type>(0U);
  }

  template<typename my_count_type>
  typename sha512<my_count_type>::result_type_as_bytes sha512<my_count_type>::get_result_as_bytes_and_finalize_the_state()
  {
    if(!the_result_is_finalized) { finalize(); }

    result_type_as_bytes result;

    // Extract the hash result from the message digest state.
    convert_uint64_input_to_uint8_output_reverse(message_hash.data(),
                                                 message_hash.data() + message_hash.size(),
                                                 result.data());

    return result;
  }

  template<typename my_count_type>
  typename sha512<my_count_type>::result_type_as_bytes sha512<my_count_type>::get_result_as_bytes_and_nochange_the_state() const
  {
    // Make a local copy of the hash object.
    sha512 other(*this);

    // Finalize the local copy of the hash object,
    // and return the final result from the copied object.
    return other.get_result_as_bytes_and_finalize_the_state();
  }

  template<typename my_count_type>
  typename sha512<my_count_type>::result_type_as_integral_values sha512<my_count_type>::get_result_as_integral_values_and_finalize_the_state()
  {
    if(!the_result_is_finalized) { finalize(); }

    return message_hash;
  }

  template<typename my_count_type>
  typename sha512<my_count_type>::result_type_as_integral_values sha512<my_count_type>::get_result_as_integral_values_and_nochange_the_state() const
  {
    // Make a local copy of the hash object.
    sha512 other(*this);

    // Finalize the local copy of the hash object,
    // and return the final result from the copied object.
    other.finalize();

    return other.message_hash;
  }

  template<typename my_count_type>
  typename sha512<my_count_type>::result_type_as_chars sha512<my_count_type>::get_result_as_chars_and_finalize_the_state()
  {
    // Get the result of the hash object as a byte array.
    const result_type_as_bytes the_result_as_bytes = get_result_as_bytes_and_finalize_the_state();

    result_type_as_chars the_result_as_chars;

    // Convert the result as a byte array to a character array.
    convert_uint8_input_to_char8_output(the_result_as_bytes.data(),
                                        the_result_as_bytes.data() + the_result_as_bytes.size(),
                                        the_result_as_chars.data());

    return the_result_as_chars;
  }

  template<typename my_count_type>
  typename sha512<my_count_type>::result_type_as_chars sha512<my_count_type>::get_result_as_chars_and_nochange_the_state() const
  {
    // Make a local copy of the hash object.
    sha512 temp_sha512(*this);

    // Finalize the local copy of the hash object,
    // and return the final result from the copied object.
    return temp_sha512.get_result_as_chars_and_finalize_the_state();
  }

#endif // _SHA512_2013_10_21_H_
