/* MD5
 January 2012:
 Modified by Christopher Kormanyos
 for C++2011 and port to microcontrollers

 converted to C++ class by Frank Thilo (thilo@unix-ag.org)
 for bzflag (http://www.bzflag.org)

 based on:

 md5.h and md5.c
 reference implementation of RFC 1321

 Copyright (C) 1991-2, RSA Data Security, Inc. Created 1991. All
 rights reserved.

 License to copy and use this software is granted provided that it
 is identified as the "RSA Data Security, Inc. MD5 Message-Digest
 Algorithm" in all material mentioning or referencing this software
 or this function.

 License is also granted to make and use derivative works provided
 that such works are identified as "derived from the RSA Data
 Security, Inc. MD5 Message-Digest Algorithm" in all material
 mentioning or referencing the derived work.

 RSA Data Security, Inc. makes no representations concerning either
 the merchantability of this software or the suitability of this
 software for any particular purpose. It is provided "as is"
 without express or implied warranty of any kind.

 These notices must be retained in any copies of any part of this
 documentation and/or software.
*/

#include <cstddef>
#include <algorithm>
#include "md5.h"

namespace
{
  class MD5
  {
  public:
    static constexpr std::size_t blocksize = 64;

    static void init();
    static void update(const std::uint8_t* buf, const std::size_t len);
    static void finalize();

  private:
    // Constants for MD5Transform routine.
    static constexpr std::uint_fast8_t S11 =  7UL;
    static constexpr std::uint_fast8_t S12 = 12UL;
    static constexpr std::uint_fast8_t S13 = 17UL;
    static constexpr std::uint_fast8_t S14 = 22UL;
    static constexpr std::uint_fast8_t S21 =  5UL;
    static constexpr std::uint_fast8_t S22 =  9UL;
    static constexpr std::uint_fast8_t S23 = 14UL;
    static constexpr std::uint_fast8_t S24 = 20UL;
    static constexpr std::uint_fast8_t S31 =  4UL;
    static constexpr std::uint_fast8_t S32 = 11UL;
    static constexpr std::uint_fast8_t S33 = 16UL;
    static constexpr std::uint_fast8_t S34 = 23UL;
    static constexpr std::uint_fast8_t S41 =  6UL;
    static constexpr std::uint_fast8_t S42 = 10UL;
    static constexpr std::uint_fast8_t S43 = 15UL;
    static constexpr std::uint_fast8_t S44 = 21UL;

    static void transform(const std::uint8_t* block);
    static void decode(std::uint32_t* output, const std::uint8_t* input, const std::size_t len);
    static void encode(std::uint8_t*  output, const std::uint32_t* input, const std::size_t len);
  };

  std::array<std::uint8_t, 16U> digest; // the result
  std::array<std::uint32_t, 2U> count;  // counter for number of bits
  std::array<std::uint32_t, 4U> state;  // digest so far

  std::array<std::uint32_t, 16U> x_transform;

  std::array<std::uint8_t, MD5::blocksize> buffer; // bytes that didn't fit in last 64 byte chunk

  std::array<std::uint8_t, 64U> padding;
  std::array<std::uint8_t, 8U>  bits;

  // low level logic operations

  // F, G, H and I are basic MD5 functions.
  inline std::uint32_t F(const std::uint32_t& x, const std::uint32_t& y, const std::uint32_t& z)
  {
    return static_cast<std::uint32_t>(static_cast<std::uint32_t>(x & y) | static_cast<std::uint32_t>(static_cast<std::uint32_t>(~x) & z));
  }

  inline std::uint32_t G(const std::uint32_t& x, const std::uint32_t& y, const std::uint32_t& z)
  {
    return static_cast<std::uint32_t>(static_cast<std::uint32_t>(x & z) | static_cast<std::uint32_t>(y & static_cast<std::uint32_t>(~z)));
  }

  inline std::uint32_t H(const std::uint32_t& x, const std::uint32_t& y, const std::uint32_t& z)
  {
    return static_cast<std::uint32_t>(static_cast<std::uint32_t>(x ^ y) ^ z);
  }

  inline std::uint32_t I(const std::uint32_t& x, const std::uint32_t& y, const std::uint32_t& z)
  {
    return static_cast<std::uint32_t>(y ^ static_cast<std::uint32_t>(x | static_cast<std::uint32_t>(~z)));
  }

  // rotate_left rotates x left n bits.
  template<const std::uint_fast8_t n>
  inline std::uint32_t rotate_left(const std::uint32_t& x)
  {
    return static_cast<std::uint32_t>((x << n) | (x >> (32U - n)));
  }

  // FF, GG, HH, and II transformations for rounds 1, 2, 3, and 4.
  // Rotation is separate from addition to prevent re-computation.
  template<const std::uint_fast8_t s,
           const std::uint32_t ac>
  inline void FF(std::uint32_t& a, const std::uint32_t& b, const std::uint32_t& c, const std::uint32_t& d, const std::uint32_t& x)
  {
    a = static_cast<std::uint32_t>(rotate_left<s>((a + F(b, c, d)) + (x + ac)) + b);
  }

  template<const std::uint_fast8_t s,
           const std::uint32_t ac>
  inline void GG(std::uint32_t& a, const std::uint32_t& b, const std::uint32_t& c, const std::uint32_t& d, const std::uint32_t& x)
  {
    a = static_cast<std::uint32_t>(rotate_left<s>((a + G(b,c,d)) + (x + ac)) + b);
  }

  template<const std::uint_fast8_t s,
           const std::uint32_t ac>
  inline void HH(std::uint32_t& a, const std::uint32_t& b, const std::uint32_t& c, const std::uint32_t& d, const std::uint32_t& x)
  {
    a = static_cast<std::uint32_t>(rotate_left<s>((a + H(b,c,d)) + (x + ac)) + b);
  }

  template<const std::uint_fast8_t s,
           const std::uint32_t ac>
  inline void II(std::uint32_t& a, const std::uint32_t& b, const std::uint32_t& c, const std::uint32_t& d, const std::uint32_t& x)
  {
    a = static_cast<std::uint32_t>(rotate_left<s>((a + I(b,c,d)) + (x + ac)) + b);
  }
}

void MD5::init()
{
  std::fill(count.begin(), count.end(), static_cast<std::uint32_t>(0U));

  // Load magic initialization constants.
  state[0U] = static_cast<std::uint32_t>(0x67452301UL);
  state[1U] = static_cast<std::uint32_t>(0xEfCDAB89UL);
  state[2U] = static_cast<std::uint32_t>(0x98BADCFEUL);
  state[3U] = static_cast<std::uint32_t>(0x10325476UL);
}

// Decodes the input (std::uint8_t) into the output (std::uint32_t).
// This assumes the len is a multiple of 4.
void MD5::decode(std::uint32_t* output, const std::uint8_t* input, const std::size_t len)
{
  std::size_t i = static_cast<std::size_t>(0U);

  for(std::size_t j = static_cast<std::size_t>(0U); j < len; j += 4U)
  {
    output[i] =    static_cast<std::uint32_t>(static_cast<std::uint32_t>(input[j + 0U]) <<  0U)
                 | static_cast<std::uint32_t>(static_cast<std::uint32_t>(input[j + 1U]) <<  8U)
                 | static_cast<std::uint32_t>(static_cast<std::uint32_t>(input[j + 2U]) << 16U)
                 | static_cast<std::uint32_t>(static_cast<std::uint32_t>(input[j + 3U]) << 24U);

    ++i;
  }
}

// Encodes the input (std::uint32_t) into the output (std::uint8_t).
// This assumes the length is a multiple of 4.
void MD5::encode(std::uint8_t* output, const std::uint32_t* input, const std::size_t len)
{
  std::size_t i = static_cast<std::size_t>(0U);

  for(std::size_t j = static_cast<std::size_t>(0U); j < len; j += 4U)
  {
    output[j + 0U] = static_cast<std::uint8_t>(input[i] >>  0U);
    output[j + 1U] = static_cast<std::uint8_t>(input[i] >>  8U);
    output[j + 2U] = static_cast<std::uint8_t>(input[i] >> 16U);
    output[j + 3U] = static_cast<std::uint8_t>(input[i] >> 24U);

    ++i;
  }
}

// Apply the MD5 algorithm on a block.
void MD5::transform(const std::uint8_t* block)
{
  std::uint32_t a_transform = state[0U];
  std::uint32_t b_transform = state[1U];
  std::uint32_t c_transform = state[2U];
  std::uint32_t d_transform = state[3U];

  decode(x_transform.data(), block, blocksize);

  // Round 1
  FF<S11, 0xD76AA478UL>(a_transform, b_transform, c_transform, d_transform, x_transform[ 0U]); //  1
  FF<S12, 0xE8C7B756UL>(d_transform, a_transform, b_transform, c_transform, x_transform[ 1U]); //  2
  FF<S13, 0x242070DBUL>(c_transform, d_transform, a_transform, b_transform, x_transform[ 2U]); //  3
  FF<S14, 0xC1BDCEEEUL>(b_transform, c_transform, d_transform, a_transform, x_transform[ 3U]); //  4
  FF<S11, 0xF57C0FAFUL>(a_transform, b_transform, c_transform, d_transform, x_transform[ 4U]); //  5
  FF<S12, 0x4787C62AUL>(d_transform, a_transform, b_transform, c_transform, x_transform[ 5U]); //  6
  FF<S13, 0xA8304613UL>(c_transform, d_transform, a_transform, b_transform, x_transform[ 6U]); //  7
  FF<S14, 0xFD469501UL>(b_transform, c_transform, d_transform, a_transform, x_transform[ 7U]); //  8
  FF<S11, 0x698098D8UL>(a_transform, b_transform, c_transform, d_transform, x_transform[ 8U]); //  9
  FF<S12, 0x8B44F7AFUL>(d_transform, a_transform, b_transform, c_transform, x_transform[ 9U]); // 10
  FF<S13, 0xFFFF5BB1UL>(c_transform, d_transform, a_transform, b_transform, x_transform[10U]); // 11
  FF<S14, 0x895CD7BEUL>(b_transform, c_transform, d_transform, a_transform, x_transform[11U]); // 12
  FF<S11, 0x6B901122UL>(a_transform, b_transform, c_transform, d_transform, x_transform[12U]); // 13
  FF<S12, 0xFD987193UL>(d_transform, a_transform, b_transform, c_transform, x_transform[13U]); // 14
  FF<S13, 0xA679438EUL>(c_transform, d_transform, a_transform, b_transform, x_transform[14U]); // 15
  FF<S14, 0x49B40821UL>(b_transform, c_transform, d_transform, a_transform, x_transform[15U]); // 16

  // Round 2
  GG<S21, 0xF61E2562UL>(a_transform, b_transform, c_transform, d_transform, x_transform[ 1U]); // 17
  GG<S22, 0xC040B340UL>(d_transform, a_transform, b_transform, c_transform, x_transform[ 6U]); // 18
  GG<S23, 0x265E5A51UL>(c_transform, d_transform, a_transform, b_transform, x_transform[11U]); // 19
  GG<S24, 0xE9B6C7AAUL>(b_transform, c_transform, d_transform, a_transform, x_transform[ 0U]); // 20
  GG<S21, 0xD62F105DUL>(a_transform, b_transform, c_transform, d_transform, x_transform[ 5U]); // 21
  GG<S22, 0x02441453UL>(d_transform, a_transform, b_transform, c_transform, x_transform[10U]); // 22
  GG<S23, 0xD8A1E681UL>(c_transform, d_transform, a_transform, b_transform, x_transform[15U]); // 23
  GG<S24, 0xE7D3FBC8UL>(b_transform, c_transform, d_transform, a_transform, x_transform[ 4U]); // 24
  GG<S21, 0x21E1CDE6UL>(a_transform, b_transform, c_transform, d_transform, x_transform[ 9U]); // 25
  GG<S22, 0xC33707D6UL>(d_transform, a_transform, b_transform, c_transform, x_transform[14U]); // 26
  GG<S23, 0xF4D50D87UL>(c_transform, d_transform, a_transform, b_transform, x_transform[ 3U]); // 27
  GG<S24, 0x455A14EDUL>(b_transform, c_transform, d_transform, a_transform, x_transform[ 8U]); // 28
  GG<S21, 0xA9E3E905UL>(a_transform, b_transform, c_transform, d_transform, x_transform[13U]); // 29
  GG<S22, 0xFCEFA3F8UL>(d_transform, a_transform, b_transform, c_transform, x_transform[ 2U]); // 30
  GG<S23, 0x676F02D9UL>(c_transform, d_transform, a_transform, b_transform, x_transform[ 7U]); // 31
  GG<S24, 0x8D2A4C8AUL>(b_transform, c_transform, d_transform, a_transform, x_transform[12U]); // 32

  // Round 3
  HH<S31, 0xFFFA3942UL>(a_transform, b_transform, c_transform, d_transform, x_transform[ 5U]); // 33
  HH<S32, 0x8771F681UL>(d_transform, a_transform, b_transform, c_transform, x_transform[ 8U]); // 34
  HH<S33, 0x6D9D6122UL>(c_transform, d_transform, a_transform, b_transform, x_transform[11U]); // 35
  HH<S34, 0xFDE5380CUL>(b_transform, c_transform, d_transform, a_transform, x_transform[14U]); // 36
  HH<S31, 0xA4BEEA44UL>(a_transform, b_transform, c_transform, d_transform, x_transform[ 1U]); // 37
  HH<S32, 0x4BDECFA9UL>(d_transform, a_transform, b_transform, c_transform, x_transform[ 4U]); // 38
  HH<S33, 0xF6BB4B60UL>(c_transform, d_transform, a_transform, b_transform, x_transform[ 7U]); // 39
  HH<S34, 0xBEBFBC70UL>(b_transform, c_transform, d_transform, a_transform, x_transform[10U]); // 40
  HH<S31, 0x289B7EC6UL>(a_transform, b_transform, c_transform, d_transform, x_transform[13U]); // 41
  HH<S32, 0xEAA127FAUL>(d_transform, a_transform, b_transform, c_transform, x_transform[ 0U]); // 42
  HH<S33, 0xD4EF3085UL>(c_transform, d_transform, a_transform, b_transform, x_transform[ 3U]); // 43
  HH<S34,  0x4881D05UL>(b_transform, c_transform, d_transform, a_transform, x_transform[ 6U]); // 44
  HH<S31, 0xD9D4D039UL>(a_transform, b_transform, c_transform, d_transform, x_transform[ 9U]); // 45
  HH<S32, 0xE6DB99E5UL>(d_transform, a_transform, b_transform, c_transform, x_transform[12U]); // 46
  HH<S33, 0x1FA27CF8UL>(c_transform, d_transform, a_transform, b_transform, x_transform[15U]); // 47
  HH<S34, 0xC4AC5665UL>(b_transform, c_transform, d_transform, a_transform, x_transform[ 2U]); // 48

  // Round 4
  II<S41, 0xF4292244UL>(a_transform, b_transform, c_transform, d_transform, x_transform[ 0U]); // 49
  II<S42, 0x432AFF97UL>(d_transform, a_transform, b_transform, c_transform, x_transform[ 7U]); // 50
  II<S43, 0xAB9423A7UL>(c_transform, d_transform, a_transform, b_transform, x_transform[14U]); // 51
  II<S44, 0xFC93A039UL>(b_transform, c_transform, d_transform, a_transform, x_transform[ 5U]); // 52
  II<S41, 0x655B59C3UL>(a_transform, b_transform, c_transform, d_transform, x_transform[12U]); // 53
  II<S42, 0x8F0CCC92UL>(d_transform, a_transform, b_transform, c_transform, x_transform[ 3U]); // 54
  II<S43, 0xFFEFF47DUL>(c_transform, d_transform, a_transform, b_transform, x_transform[10U]); // 55
  II<S44, 0x85845DD1UL>(b_transform, c_transform, d_transform, a_transform, x_transform[ 1U]); // 56
  II<S41, 0x6FA87E4FUL>(a_transform, b_transform, c_transform, d_transform, x_transform[ 8U]); // 57
  II<S42, 0xFE2CE6E0UL>(d_transform, a_transform, b_transform, c_transform, x_transform[15U]); // 58
  II<S43, 0xA3014314UL>(c_transform, d_transform, a_transform, b_transform, x_transform[ 6U]); // 59
  II<S44, 0x4E0811A1UL>(b_transform, c_transform, d_transform, a_transform, x_transform[13U]); // 60
  II<S41, 0xF7537E82UL>(a_transform, b_transform, c_transform, d_transform, x_transform[ 4U]); // 61
  II<S42, 0xBD3AF235UL>(d_transform, a_transform, b_transform, c_transform, x_transform[11U]); // 62
  II<S43, 0x2AD7D2BBUL>(c_transform, d_transform, a_transform, b_transform, x_transform[ 2U]); // 63
  II<S44, 0xEB86D391UL>(b_transform, c_transform, d_transform, a_transform, x_transform[ 9U]); // 64

  state[0U] += a_transform;
  state[1U] += b_transform;
  state[2U] += c_transform;
  state[3U] += d_transform;
}

// MD5 block update operation. Continues an MD5 message-digest
// operation, processing another message block
void MD5::update(const std::uint8_t* input, const std::size_t len)
{
  // Compute number of bytes mod 64.
  std::size_t index = static_cast<std::size_t>(static_cast<std::size_t>(count[0U] / 8U) % blocksize);

  // Update the number of bits.
  const std::uint32_t len_shift = static_cast<std::uint32_t>(static_cast<std::uint32_t>(len) << 3U);

  count[0U] += len_shift;

  if(count[0U] < len_shift)
  {
    ++count[1U];
  }

  count[1U] += static_cast<std::uint32_t>(static_cast<std::uint32_t>(len) >> 29U);

  // Compute the number of bytes we need to fill in the buffer.
  const std::size_t firstpart = static_cast<std::size_t>(blocksize - index);

  std::size_t i = static_cast<std::size_t>(0U);

  // Transform as many times as possible.
  if(len >= firstpart)
  {
    // Fill the buffer first, then transform.
    std::copy(input, input + firstpart, buffer.begin() + index);

    transform(buffer.data());


    // Transform chunks of blocksize (64 bytes).
    for(i = firstpart; (i + blocksize) <= len; i += blocksize)
    {
      transform(&input[i]);
    }

    index = static_cast<std::size_t>(0U);
  }

  // Buffer the remaining input.
  std::copy(input + i, input + len, buffer.begin() + index);
}

// MD5 finalization. Ends an MD5 message-digest operation, writing
// the message digest and zero-clearing the context.
void MD5::finalize()
{
  // (Re-)Initialize the padding.
  padding[0U] = static_cast<std::uint8_t>(0x80U);
  std::fill(padding.begin() + 1U, padding.end(), static_cast<std::uint8_t>(0U));

  // Save the number of bits.
  encode(bits.data(), count.data(), 8U);

  // Pad out to 56 mod 64.
  const std::size_t index = static_cast<std::size_t>(static_cast<std::uint32_t>(count[0U] / 8U) % 64U);
  const std::size_t padLen = ((index < static_cast<std::size_t>(56U))
                               ? (static_cast<std::size_t>(56U) - index)
                               : (static_cast<std::size_t>(120U) - index));

  update(padding.data(), padLen);

  // Append length (before padding).
  update(bits.data(), 8U);

  // Store state in digest.
  encode(digest.data(), state.data(), digest.size());

  // Zero-clear sensitive information.
  std::fill(buffer.begin(), buffer.end(), static_cast<std::uint8_t>(0U));
  std::fill(count.begin(), count.end(), static_cast<std::uint32_t>(0U));
}

std::array<std::uint8_t, 16U> md5(const std::uint8_t* buffer, const std::size_t byte_count)
{
  MD5::init();
  MD5::update(buffer, byte_count);
  MD5::finalize();

  return digest;
}
