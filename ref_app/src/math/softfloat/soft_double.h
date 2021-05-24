///////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2012 - 2021.                 //
//  Distributed under the Boost Software License,                //
//  Version 1.0. (See accompanying file LICENSE_1_0.txt          //
//  or copy at http://www.boost.org/LICENSE_1_0.txt)             //
///////////////////////////////////////////////////////////////////

// This work uses (significantly) modified parts of
// SoftFloat IEEE Floating-Point Arithmetic Package,
// Release 3e, by John R. Hauser.

// Full original copyright information is included
// at the bottom of this header file.

#ifndef SOFT_DOUBLE_2020_10_27_H_
  #define SOFT_DOUBLE_2020_10_27_H_

  //#define SOFT_DOUBLE_DISABLE_IOSTREAM

  #include <array>
  #include <cstdint>
  #include <cstddef>
  #if !defined(SOFT_DOUBLE_DISABLE_IOSTREAM)
  #include <iomanip>
  #include <sstream>
  #endif
  #include <limits>
  #include <type_traits>

  namespace math { namespace softfloat {

  // Forward declaration the math::softfloat::soft_double class.
  class soft_double;

  } }

  namespace std {

  // Forward declaration of the specialization of numeric_limits for soft_double.
  template<>
  class numeric_limits<math::softfloat::soft_double>;

  }

  namespace math { namespace softfloat {

  namespace detail {

  struct uint128_as_struct  { uint64_t v0, v64; };
  struct uint64_extra       { uint64_t extra, v; };

  template<typename UnsignedIntegralType>
  constexpr typename std::enable_if<   (std::is_integral<UnsignedIntegralType>::value == true)
                                    && (std::is_unsigned<UnsignedIntegralType>::value == true), UnsignedIntegralType>::type
  negate(UnsignedIntegralType u)
  {
    return (UnsignedIntegralType) (((UnsignedIntegralType) ~u) + 1U);
  }

  template<typename SignedIntegralType>
  constexpr typename std::enable_if<   (std::is_integral<SignedIntegralType>::value == true)
                                    && (std::is_signed  <SignedIntegralType>::value == true), SignedIntegralType>::type
  negate(SignedIntegralType n)
  {
    return (SignedIntegralType) -n;
  }

  inline constexpr bool          signF32UI(uint32_t a) { return ((bool) ((uint32_t) (a)>>31)); }
  inline constexpr std::int16_t  expF32UI (uint32_t a) { return ((int16_t) ((a)>>23) & 0xFF); }
  inline constexpr std::uint32_t fracF32UI(uint32_t a) { return ((a) & UINT32_C(0x007FFFFF)); }

  inline constexpr bool          signF64UI(std::uint64_t a) { return ((unsigned) ((std::uint64_t) a >> 63U) != 0U); }
  inline constexpr std::int16_t  expF64UI (std::uint64_t a) { return (std::int16_t) (a >> 52U) & INT16_C(0x7FF); }
  inline constexpr std::uint64_t fracF64UI(std::uint64_t a) { return (std::uint64_t) (a & UINT64_C(0x000FFFFFFFFFFFFF)); }

  template<typename IntegralTypeExp,
           typename IntegralTypeSig>
  constexpr uint64_t packToF64UI(bool sign, IntegralTypeExp expA, IntegralTypeSig sig)
  {
    return ((uint64_t) ((uint64_t) (((uint64_t) (sign ? 1U : 0U))<<63) + (uint64_t) (((uint64_t) expA)<<52) + (uint64_t) sig));
  }

  template<typename IntegralTypeExp,
           typename IntegralTypeSig>
  constexpr uint32_t packToF32UI(bool sign, IntegralTypeExp expA, IntegralTypeSig sig)
  {
    return ((uint32_t) ((uint32_t) (((uint32_t) (sign ? 1U : 0U))<<31) + (uint32_t) (((uint32_t) expA)<<23) + (uint32_t) sig));
  }

  /*----------------------------------------------------------------------------
  | Shifts 'a' right by the number of bits given in 'dist', which must be in
  | the range 1 to 63.  If any nonzero bits are shifted off, they are "jammed"
  | into the least-significant bit of the shifted value by setting the least-
  | significant bit to 1.  This shifted-and-jammed value is returned.
  *----------------------------------------------------------------------------*/
  constexpr uint64_t softfloat_shortShiftRightJam64(uint64_t a, uint_fast8_t dist)
  {
    return a >> dist | ((a & ((UINT64_C(1) << dist) - 1)) != 0 ? 1U : 0U);
  }

  /*----------------------------------------------------------------------------
  | Shifts 'a' right by the number of bits given in 'dist', which must not
  | be zero.  If any nonzero bits are shifted off, they are "jammed" into the
  | least-significant bit of the shifted value by setting the least-significant
  | bit to 1.  This shifted-and-jammed value is returned.
  *----------------------------------------------------------------------------*/
  constexpr uint32_t softfloat_shiftRightJam32(uint32_t a, uint16_t dist)
  {
    return (dist < 31) ? a >> dist | ((uint32_t)(a << (negate(dist) & 31)) != 0U ? 1U : 0U) : (a != 0U ? 1U : 0U);
  }

  /*----------------------------------------------------------------------------
  | Shifts 'a' right by the number of bits given in 'dist', which must not
  | be zero.
  *----------------------------------------------------------------------------*/
  constexpr uint64_t softfloat_shiftRightJam64(uint64_t a, uint32_t dist)
  {
    return (dist < 63) ? a >> dist | ((uint64_t)(a << (negate(dist) & 63)) != 0 ? 1U : 0U) : (a != 0 ? 1U : 0U);
  }

  /*----------------------------------------------------------------------------
  | A constant table that translates an 8-bit unsigned integer (the array index)
  | into the number of leading 0 bits before the most-significant 1 of that
  | integer.  For integer zero (index 0), the corresponding table element is 8.
  *----------------------------------------------------------------------------*/
  constexpr uint_fast8_t softfloat_countLeadingZeros8_z_table(const uint_fast8_t index)
  {
    return ((index < 0x1U) ? 4U :
           ((index < 0x2U) ? 3U :
           ((index < 0x4U) ? 2U :
           ((index < 0x8U) ? 1U : 0U))));
  }

  constexpr uint_fast8_t softfloat_countLeadingZeros8(const uint_fast8_t index)
  {
    return (index < 0x10U) ? 4U + softfloat_countLeadingZeros8_z_table(index &  0xFU)
                           :      softfloat_countLeadingZeros8_z_table(index >>   4U);
  }

  constexpr uint_fast8_t softfloat_countLeadingZeros16(uint16_t a)
  {
    return (a < UINT16_C(0x100)) ? 8U + softfloat_countLeadingZeros8((uint_fast8_t) a)
                                 :      softfloat_countLeadingZeros8((uint_fast8_t) (a >> 8U));
  }

  constexpr uint_fast8_t softfloat_countLeadingZeros32(uint32_t a)
  {
    // TBD: Finding MSB to count leading zeros can probably be done more efficiently.
    return (a < UINT32_C(0x10000)) ? 16U + softfloat_countLeadingZeros16((uint16_t) a)
                                   :       softfloat_countLeadingZeros16((uint16_t) (a >> 16U));
  }

  /*----------------------------------------------------------------------------
  | Returns the number of leading 0 bits before the most-significant 1 bit of
  | 'a'.  If 'a' is zero, 64 is returned.
  *----------------------------------------------------------------------------*/
  constexpr uint_fast8_t softfloat_countLeadingZeros64(uint64_t a)
  {
    // TBD: Finding MSB to count leading zeros can probably be done more efficiently.
    return (a < UINT64_C(0x100000000)) ? 32U + softfloat_countLeadingZeros32((uint32_t) a)
                                       :       softfloat_countLeadingZeros32((uint32_t) (a >> 32U));
  }

  /*----------------------------------------------------------------------------
  | Returns an approximation to the reciprocal of the number represented by 'a',
  | where 'a' is interpreted as an unsigned fixed-point number with one integer
  | bit and 31 fraction bits.
  *----------------------------------------------------------------------------*/
  constexpr uint32_t softfloat_approxRecip32_1(uint32_t a)
  {
    return (uint32_t) (UINT64_C(0x7FFFFFFFFFFFFFFF) / a);
  }

  /*----------------------------------------------------------------------------
  | Shifts the 128 bits formed by concatenating 'a' and 'extra' right by 64
  | _plus_ the number of bits given in 'dist', which must not be zero.  This
  | shifted value is at most 64 nonzero bits and is returned in the 'v' field
  | of the 'struct uint64_extra' result.
  *----------------------------------------------------------------------------*/
  constexpr struct uint64_extra softfloat_shiftRightJam64Extra(uint64_t a, uint64_t extra, uint32_t dist)
  {
    return
    {
      (dist < 64U) ? (a << (negate(dist) & 63U)) | (extra != 0U ? 1U : 0U) : ((dist == 64U) ? a : (a != 0U ? 1U : 0U))  | (extra != 0U ? 1U : 0U),
      (dist < 64U) ? (a >> dist)                                           : 0U
    };
  }

  template<const int BitCount,
           typename EnableType = void>
  struct uint_type_helper
  {
    static_assert(((BitCount >= 8) && (BitCount <= 64)),
                  "Error: uint_type_helper is not intended to be used for this BitCount");

    using exact_unsigned_type = std::uintmax_t;
  };

  template<const int BitCount> struct uint_type_helper<BitCount, typename std::enable_if<                    (BitCount <=  8)>::type> { using exact_unsigned_type = std::uint8_t;  };
  template<const int BitCount> struct uint_type_helper<BitCount, typename std::enable_if<(BitCount >=  9) && (BitCount <= 16)>::type> { using exact_unsigned_type = std::uint16_t; };
  template<const int BitCount> struct uint_type_helper<BitCount, typename std::enable_if<(BitCount >= 17) && (BitCount <= 32)>::type> { using exact_unsigned_type = std::uint32_t; };
  template<const int BitCount> struct uint_type_helper<BitCount, typename std::enable_if<(BitCount >= 33) && (BitCount <= 64)>::type> { using exact_unsigned_type = std::uint64_t; };

  template<typename BuiltInFloatType,
           typename ExactUnsignedIntegralType = typename uint_type_helper<std::numeric_limits<BuiltInFloatType>::digits>::exact_unsigned_type>
  union uz_type
  {
    static_assert((   std::is_same<BuiltInFloatType, float>::value
                   || std::is_same<BuiltInFloatType, double>::value),
                  "Error: This template is intended for either built-in float or double, but not for any other type(s)");

    using float_type    = BuiltInFloatType;
    using unsigned_type = ExactUnsignedIntegralType;

    const float_type    my_f;
    const unsigned_type my_u;

    constexpr uz_type(float_type    f) : my_f(f) { }
    constexpr uz_type(unsigned_type u) : my_u(u) { }
  };

  struct nothing { };

  }

  class soft_double;

  inline soft_double operator+(const soft_double& a, const soft_double& b);
  inline soft_double operator-(const soft_double& a, const soft_double& b);
  inline soft_double operator*(const soft_double& a, const soft_double& b);
  inline soft_double operator/(const soft_double& a, const soft_double& b);

  template<typename UnsignedIntegralType> typename std::enable_if<(std::is_integral<UnsignedIntegralType>::value == true) && (std::is_unsigned<UnsignedIntegralType>::value == true), soft_double>::type operator+(const soft_double& u, UnsignedIntegralType n);
  template<typename UnsignedIntegralType> typename std::enable_if<(std::is_integral<UnsignedIntegralType>::value == true) && (std::is_unsigned<UnsignedIntegralType>::value == true), soft_double>::type operator-(const soft_double& u, UnsignedIntegralType n);
  template<typename UnsignedIntegralType> typename std::enable_if<(std::is_integral<UnsignedIntegralType>::value == true) && (std::is_unsigned<UnsignedIntegralType>::value == true), soft_double>::type operator*(const soft_double& u, UnsignedIntegralType n);
  template<typename UnsignedIntegralType> typename std::enable_if<(std::is_integral<UnsignedIntegralType>::value == true) && (std::is_unsigned<UnsignedIntegralType>::value == true), soft_double>::type operator/(const soft_double& u, UnsignedIntegralType n);

  template<typename UnsignedIntegralType> typename std::enable_if<(std::is_integral<UnsignedIntegralType>::value == true) && (std::is_unsigned<UnsignedIntegralType>::value == true), soft_double>::type operator+(UnsignedIntegralType n, const soft_double& u);
  template<typename UnsignedIntegralType> typename std::enable_if<(std::is_integral<UnsignedIntegralType>::value == true) && (std::is_unsigned<UnsignedIntegralType>::value == true), soft_double>::type operator-(UnsignedIntegralType n, const soft_double& u);
  template<typename UnsignedIntegralType> typename std::enable_if<(std::is_integral<UnsignedIntegralType>::value == true) && (std::is_unsigned<UnsignedIntegralType>::value == true), soft_double>::type operator*(UnsignedIntegralType n, const soft_double& u);
  template<typename UnsignedIntegralType> typename std::enable_if<(std::is_integral<UnsignedIntegralType>::value == true) && (std::is_unsigned<UnsignedIntegralType>::value == true), soft_double>::type operator/(UnsignedIntegralType n, const soft_double& u);

  template<typename SignedIntegralType> typename std::enable_if<(std::is_integral<SignedIntegralType>::value == true) && (std::is_signed<SignedIntegralType>::value == true), soft_double>::type operator+(const soft_double& u, SignedIntegralType n);
  template<typename SignedIntegralType> typename std::enable_if<(std::is_integral<SignedIntegralType>::value == true) && (std::is_signed<SignedIntegralType>::value == true), soft_double>::type operator-(const soft_double& u, SignedIntegralType n);
  template<typename SignedIntegralType> typename std::enable_if<(std::is_integral<SignedIntegralType>::value == true) && (std::is_signed<SignedIntegralType>::value == true), soft_double>::type operator*(const soft_double& u, SignedIntegralType n);
  template<typename SignedIntegralType> typename std::enable_if<(std::is_integral<SignedIntegralType>::value == true) && (std::is_signed<SignedIntegralType>::value == true), soft_double>::type operator/(const soft_double& u, SignedIntegralType n);

  template<typename SignedIntegralType> typename std::enable_if<(std::is_integral<SignedIntegralType>::value == true) && (std::is_signed<SignedIntegralType>::value == true), soft_double>::type operator+(SignedIntegralType n, const soft_double& u);
  template<typename SignedIntegralType> typename std::enable_if<(std::is_integral<SignedIntegralType>::value == true) && (std::is_signed<SignedIntegralType>::value == true), soft_double>::type operator-(SignedIntegralType n, const soft_double& u);
  template<typename SignedIntegralType> typename std::enable_if<(std::is_integral<SignedIntegralType>::value == true) && (std::is_signed<SignedIntegralType>::value == true), soft_double>::type operator*(SignedIntegralType n, const soft_double& u);
  template<typename SignedIntegralType> typename std::enable_if<(std::is_integral<SignedIntegralType>::value == true) && (std::is_signed<SignedIntegralType>::value == true), soft_double>::type operator/(SignedIntegralType n, const soft_double& u);

  inline soft_double operator+(const soft_double& u, float f);
  inline soft_double operator-(const soft_double& u, float f);
  inline soft_double operator*(const soft_double& u, float f);
  inline soft_double operator/(const soft_double& u, float f);

  inline soft_double operator+(float f, const soft_double& u);
  inline soft_double operator-(float f, const soft_double& u);
  inline soft_double operator*(float f, const soft_double& u);
  inline soft_double operator/(float f, const soft_double& u);

  inline soft_double operator+(const soft_double& u, double f);
  inline soft_double operator-(const soft_double& u, double f);
  inline soft_double operator*(const soft_double& u, double f);
  inline soft_double operator/(const soft_double& u, double f);

  inline soft_double operator+(double f, const soft_double& u);
  inline soft_double operator-(double f, const soft_double& u);
  inline soft_double operator*(double f, const soft_double& u);
  inline soft_double operator/(double f, const soft_double& u);

  inline soft_double operator+(const soft_double& u, long double f);
  inline soft_double operator-(const soft_double& u, long double f);
  inline soft_double operator*(const soft_double& u, long double f);
  inline soft_double operator/(const soft_double& u, long double f);

  inline soft_double operator+(long double f, const soft_double& u);
  inline soft_double operator-(long double f, const soft_double& u);
  inline soft_double operator*(long double f, const soft_double& u);
  inline soft_double operator/(long double f, const soft_double& u);

  inline constexpr bool operator< (const soft_double& a, const soft_double& b);
  inline constexpr bool operator<=(const soft_double& a, const soft_double& b);
  inline constexpr bool operator==(const soft_double& a, const soft_double& b);
  inline constexpr bool operator!=(const soft_double& a, const soft_double& b);
  inline constexpr bool operator>=(const soft_double& a, const soft_double& b);
  inline constexpr bool operator> (const soft_double& a, const soft_double& b);

  template<typename UnsignedIntegralType> typename std::enable_if<(std::is_integral<UnsignedIntegralType>::value == true) && (std::is_unsigned<UnsignedIntegralType>::value == true), bool>::type operator< (const soft_double& a, const UnsignedIntegralType u);
  template<typename UnsignedIntegralType> typename std::enable_if<(std::is_integral<UnsignedIntegralType>::value == true) && (std::is_unsigned<UnsignedIntegralType>::value == true), bool>::type operator<=(const soft_double& a, const UnsignedIntegralType u);
  template<typename UnsignedIntegralType> typename std::enable_if<(std::is_integral<UnsignedIntegralType>::value == true) && (std::is_unsigned<UnsignedIntegralType>::value == true), bool>::type operator==(const soft_double& a, const UnsignedIntegralType u);
  template<typename UnsignedIntegralType> typename std::enable_if<(std::is_integral<UnsignedIntegralType>::value == true) && (std::is_unsigned<UnsignedIntegralType>::value == true), bool>::type operator!=(const soft_double& a, const UnsignedIntegralType u);
  template<typename UnsignedIntegralType> typename std::enable_if<(std::is_integral<UnsignedIntegralType>::value == true) && (std::is_unsigned<UnsignedIntegralType>::value == true), bool>::type operator>=(const soft_double& a, const UnsignedIntegralType u);
  template<typename UnsignedIntegralType> typename std::enable_if<(std::is_integral<UnsignedIntegralType>::value == true) && (std::is_unsigned<UnsignedIntegralType>::value == true), bool>::type operator> (const soft_double& a, const UnsignedIntegralType u);

  template<typename UnsignedIntegralType> typename std::enable_if<(std::is_integral<UnsignedIntegralType>::value == true) && (std::is_unsigned<UnsignedIntegralType>::value == true), bool>::type operator< (const UnsignedIntegralType u, const soft_double& a);
  template<typename UnsignedIntegralType> typename std::enable_if<(std::is_integral<UnsignedIntegralType>::value == true) && (std::is_unsigned<UnsignedIntegralType>::value == true), bool>::type operator<=(const UnsignedIntegralType u, const soft_double& a);
  template<typename UnsignedIntegralType> typename std::enable_if<(std::is_integral<UnsignedIntegralType>::value == true) && (std::is_unsigned<UnsignedIntegralType>::value == true), bool>::type operator==(const UnsignedIntegralType u, const soft_double& a);
  template<typename UnsignedIntegralType> typename std::enable_if<(std::is_integral<UnsignedIntegralType>::value == true) && (std::is_unsigned<UnsignedIntegralType>::value == true), bool>::type operator!=(const UnsignedIntegralType u, const soft_double& a);
  template<typename UnsignedIntegralType> typename std::enable_if<(std::is_integral<UnsignedIntegralType>::value == true) && (std::is_unsigned<UnsignedIntegralType>::value == true), bool>::type operator>=(const UnsignedIntegralType u, const soft_double& a);
  template<typename UnsignedIntegralType> typename std::enable_if<(std::is_integral<UnsignedIntegralType>::value == true) && (std::is_unsigned<UnsignedIntegralType>::value == true), bool>::type operator> (const UnsignedIntegralType u, const soft_double& a);

  template<typename SignedIntegralType> typename std::enable_if<(std::is_integral<SignedIntegralType>::value == true) && (std::is_signed<SignedIntegralType>::value == true), bool>::type operator< (const soft_double& a, const SignedIntegralType n);
  template<typename SignedIntegralType> typename std::enable_if<(std::is_integral<SignedIntegralType>::value == true) && (std::is_signed<SignedIntegralType>::value == true), bool>::type operator<=(const soft_double& a, const SignedIntegralType n);
  template<typename SignedIntegralType> typename std::enable_if<(std::is_integral<SignedIntegralType>::value == true) && (std::is_signed<SignedIntegralType>::value == true), bool>::type operator==(const soft_double& a, const SignedIntegralType n);
  template<typename SignedIntegralType> typename std::enable_if<(std::is_integral<SignedIntegralType>::value == true) && (std::is_signed<SignedIntegralType>::value == true), bool>::type operator!=(const soft_double& a, const SignedIntegralType n);
  template<typename SignedIntegralType> typename std::enable_if<(std::is_integral<SignedIntegralType>::value == true) && (std::is_signed<SignedIntegralType>::value == true), bool>::type operator>=(const soft_double& a, const SignedIntegralType n);
  template<typename SignedIntegralType> typename std::enable_if<(std::is_integral<SignedIntegralType>::value == true) && (std::is_signed<SignedIntegralType>::value == true), bool>::type operator> (const soft_double& a, const SignedIntegralType n);

  template<typename SignedIntegralType> typename std::enable_if<(std::is_integral<SignedIntegralType>::value == true) && (std::is_signed<SignedIntegralType>::value == true), bool>::type operator< (const SignedIntegralType n, const soft_double& a);
  template<typename SignedIntegralType> typename std::enable_if<(std::is_integral<SignedIntegralType>::value == true) && (std::is_signed<SignedIntegralType>::value == true), bool>::type operator<=(const SignedIntegralType n, const soft_double& a);
  template<typename SignedIntegralType> typename std::enable_if<(std::is_integral<SignedIntegralType>::value == true) && (std::is_signed<SignedIntegralType>::value == true), bool>::type operator==(const SignedIntegralType n, const soft_double& a);
  template<typename SignedIntegralType> typename std::enable_if<(std::is_integral<SignedIntegralType>::value == true) && (std::is_signed<SignedIntegralType>::value == true), bool>::type operator!=(const SignedIntegralType n, const soft_double& a);
  template<typename SignedIntegralType> typename std::enable_if<(std::is_integral<SignedIntegralType>::value == true) && (std::is_signed<SignedIntegralType>::value == true), bool>::type operator>=(const SignedIntegralType n, const soft_double& a);
  template<typename SignedIntegralType> typename std::enable_if<(std::is_integral<SignedIntegralType>::value == true) && (std::is_signed<SignedIntegralType>::value == true), bool>::type operator> (const SignedIntegralType n, const soft_double& a);

  inline bool operator< (const soft_double& a, const float f);
  inline bool operator<=(const soft_double& a, const float f);
  inline bool operator==(const soft_double& a, const float f);
  inline bool operator!=(const soft_double& a, const float f);
  inline bool operator>=(const soft_double& a, const float f);
  inline bool operator> (const soft_double& a, const float f);

  inline bool operator< (const float f, const soft_double& a);
  inline bool operator<=(const float f, const soft_double& a);
  inline bool operator==(const float f, const soft_double& a);
  inline bool operator!=(const float f, const soft_double& a);
  inline bool operator>=(const float f, const soft_double& a);
  inline bool operator> (const float f, const soft_double& a);

  inline bool operator< (const soft_double& a, const double f);
  inline bool operator<=(const soft_double& a, const double f);
  inline bool operator==(const soft_double& a, const double f);
  inline bool operator!=(const soft_double& a, const double f);
  inline bool operator>=(const soft_double& a, const double f);
  inline bool operator> (const soft_double& a, const double f);

  inline bool operator< (const double f, const soft_double& a);
  inline bool operator<=(const double f, const soft_double& a);
  inline bool operator==(const double f, const soft_double& a);
  inline bool operator!=(const double f, const soft_double& a);
  inline bool operator>=(const double f, const soft_double& a);
  inline bool operator> (const double f, const soft_double& a);

  inline bool operator< (const soft_double& a, const long double f);
  inline bool operator<=(const soft_double& a, const long double f);
  inline bool operator==(const soft_double& a, const long double f);
  inline bool operator!=(const soft_double& a, const long double f);
  inline bool operator>=(const soft_double& a, const long double f);
  inline bool operator> (const soft_double& a, const long double f);

  inline bool operator< (const long double f, const soft_double& a);
  inline bool operator<=(const long double f, const soft_double& a);
  inline bool operator==(const long double f, const soft_double& a);
  inline bool operator!=(const long double f, const soft_double& a);
  inline bool operator>=(const long double f, const soft_double& a);
  inline bool operator> (const long double f, const soft_double& a);

  #if !defined(SOFT_DOUBLE_DISABLE_IOSTREAM)
  template<typename char_type, typename traits_type> std::basic_ostream<char_type, traits_type>& operator<<(std::basic_ostream<char_type, traits_type>& os, const soft_double& f);
  template<typename char_type, typename traits_type> std::basic_istream<char_type, traits_type>& operator>>(std::basic_istream<char_type, traits_type>& is,       soft_double& f);
  #endif // !WIDE_DECIMAL_DISABLE_IOSTREAM

  inline bool        isnan   (const soft_double x);
  inline bool        isinf   (const soft_double x);
  inline bool        isfinite(const soft_double x);
  inline soft_double fabs    (const soft_double x);
  inline soft_double frexp   (const soft_double x, int* expptr);
  inline soft_double ldexp   (const soft_double x, int expval);
  inline soft_double floor   (const soft_double x);
  inline soft_double ceil    (const soft_double x);
  inline soft_double sqrt    (const soft_double x);
  inline soft_double exp     (const soft_double x);
  inline soft_double log     (const soft_double x);
  inline soft_double pow     (const soft_double x, const soft_double a);
  inline soft_double sin     (const soft_double x);
  inline soft_double cos     (const soft_double x);
  inline soft_double tan     (const soft_double x);
  inline soft_double sinh    (const soft_double x);
  inline soft_double cosh    (const soft_double x);
  inline soft_double tanh    (const soft_double x);

  template<typename UnsignedIntegralType,
           typename std::enable_if<(   (std::is_integral<UnsignedIntegralType>::value == true)
                                    && (std::is_unsigned<UnsignedIntegralType>::value == true))>::type const* = nullptr>
  soft_double pow(const soft_double x, const UnsignedIntegralType u);

  template<typename SignedIntegralType,
           typename std::enable_if<(   (std::is_integral<SignedIntegralType>::value == true)
                                    && (std::is_signed  <SignedIntegralType>::value == true))>::type const* = nullptr>
  soft_double pow(const soft_double x, const SignedIntegralType n);

  class soft_double final
  {
    static_assert(sizeof(float) == 4U,
                  "Error: This template is designed for 4 byte built-in float");
  public:
    using representation_type = uint64_t;

    soft_double() { }

    template<typename UnsignedIntegralType,
             typename std::enable_if<(   (std::is_integral<UnsignedIntegralType>::value == true)
                                      && (std::is_unsigned<UnsignedIntegralType>::value == true)
                                      && (sizeof(UnsignedIntegralType) <= sizeof(uint32_t)))>::type const* = nullptr>
    constexpr soft_double(UnsignedIntegralType u) : my_value(my_ui32_to_f64((std::uint32_t) u)) { }

    template<typename UnsignedIntegralType,
             typename std::enable_if<(   (std::is_integral<UnsignedIntegralType>::value == true)
                                      && (std::is_unsigned<UnsignedIntegralType>::value == true)
                                      && !(sizeof(UnsignedIntegralType) <= sizeof(uint32_t)))>::type const* = nullptr>
    constexpr soft_double(UnsignedIntegralType u) : my_value(my_ui64_to_f64((std::uint64_t) u)) { }

    template<typename SignedIntegralType,
             typename std::enable_if<(   (std::is_integral<SignedIntegralType>::value == true)
                                      && (std::is_signed  <SignedIntegralType>::value == true)
                                      && (sizeof(SignedIntegralType) <= sizeof(int32_t)))>::type const* = nullptr>
    constexpr soft_double(SignedIntegralType n) : my_value(my__i32_to_f64((std::int32_t) n)) { }

    template<typename SignedIntegralType,
             typename std::enable_if<(   (std::is_integral<SignedIntegralType>::value == true)
                                      && (std::is_signed  <SignedIntegralType>::value == true)
                                      && !(sizeof(SignedIntegralType) <= sizeof(int32_t)))>::type const* = nullptr>
    constexpr soft_double(SignedIntegralType n) : my_value(my__i64_to_f64((std::int64_t) n)) { }

    constexpr soft_double(float f)
      : my_value
        (
          ((detail::expF32UI (detail::uz_type<float>(f).my_u) == 0) && (detail::fracF32UI(detail::uz_type<float>(f).my_u) == 0U))
            ? detail::packToF64UI(detail::signF32UI(detail::uz_type<float>(f).my_u), 0, 0)
            : detail::packToF64UI(detail::signF32UI(detail::uz_type<float>(f).my_u), detail::expF32UI(detail::uz_type<float>(f).my_u) + 0x380, (uint64_t) detail::fracF32UI(detail::uz_type<float>(f).my_u) << 29)
        ) { }

    constexpr soft_double(double d)
      : my_value(detail::uz_type<double>(d).my_u) { }

    constexpr soft_double(const long double ld)
      : my_value(detail::uz_type<double>((double) ld).my_u) { }

    constexpr soft_double(const soft_double& other) noexcept
      : my_value(other.my_value) { }

    constexpr soft_double(const soft_double&& other) noexcept
      : my_value(other.my_value) { }

    constexpr soft_double(std::uint64_t n, const detail::nothing&) noexcept
      : my_value((std::uint64_t) n) { }

    ~soft_double() = default;

    soft_double& operator=(const soft_double& other)
    {
      if(this != &other)
      {
        my_value = other.my_value;
      }

      return *this;
    }

    soft_double& operator=(soft_double&& other)
    {
      my_value = other.my_value;

      return *this;
    }

          representation_type&  representation()       { return my_value; }
    const representation_type&  representation() const { return my_value; }
    const representation_type& crepresentation() const { return my_value; }

    static constexpr representation_type get_rep(soft_double a) { return a.my_value; }

    operator   signed char     () const { return   (signed char)      f64_to__i32(my_value); }
    operator   signed short    () const { return   (signed short)     f64_to__i32(my_value); }
    operator   signed int      () const { return   (signed int)       f64_to__i32(my_value); }
    operator   signed long     () const { return   (signed long)      f64_to__i64(my_value); }
    operator   signed long long() const { return   (signed long long) f64_to__i64(my_value); }

    operator unsigned char     () const { return (unsigned char)      f64_to_ui32(my_value); }
    operator unsigned short    () const { return (unsigned short)     f64_to_ui32(my_value); }
    operator unsigned int      () const { return (unsigned int)       f64_to_ui32(my_value); }
    operator unsigned long     () const { return (unsigned long)      f64_to_ui64(my_value); }
    operator unsigned long long() const { return (unsigned long long) f64_to_ui64(my_value); }

    operator float() const
    {
      static_assert(sizeof(float) == 4U,
                    "Error: This cast requires 4 byte built-in float");

      return f64_to_f32(my_value);
    }

    operator double() const
    {
      #if defined(__AVR__)
      // TBD: Is this the best way to deal with double/float ambiguity for GCC-ARV?
      return (double) ((float) *this);
      #else
      return detail::uz_type<double>(my_value).my_f;
      #endif
    }

    operator long double() const
    {
      return (long double) ((double) *this);
    }

    soft_double& operator+=(const soft_double& other) { my_value = f64_add(my_value, other.my_value); return *this; }
    soft_double& operator-=(const soft_double& other) { my_value = f64_sub(my_value, other.my_value); return *this; }
    soft_double& operator*=(const soft_double& other) { my_value = f64_mul(my_value, other.my_value); return *this; }
    soft_double& operator/=(const soft_double& other) { my_value = f64_div(my_value, other.my_value); return *this; }

    // Operators pre-increment and pre-decrement.
    soft_double& operator++() { return *this += my_value_one(); }
    soft_double& operator--() { return *this -= my_value_one(); }

    // Operators post-increment and post-decrement.
    soft_double operator++(int) { const soft_double w(*this); static_cast<void>(++(*this)); return w; }
    soft_double operator--(int) { const soft_double w(*this); static_cast<void>(--(*this)); return w; }

    const soft_double& operator+() const { return *this; }
          soft_double  operator-() const { return soft_double(my_value ^ (uint64_t) (1ULL << 63U), detail::nothing()); }

    static constexpr soft_double my_value_zero   () { return soft_double(UINT64_C(0),                   detail::nothing()); }
    static constexpr soft_double my_value_one    () { return soft_double(UINT64_C(0x3FF0000000000000),  detail::nothing()); }
    static constexpr soft_double my_value_two    () { return soft_double(UINT64_C(0x4000000000000000),  detail::nothing()); }
    static constexpr soft_double my_value_half   () { return soft_double(UINT64_C(0x3FE0000000000000),  detail::nothing()); }
    static constexpr soft_double my_value_pi     () { return soft_double(UINT64_C(4614256656552045848), detail::nothing()); }
    static constexpr soft_double my_value_pi_half() { return soft_double(UINT64_C(0x3FF921FB54442D18),  detail::nothing()); }

    static constexpr soft_double my_value_ln2 () { return soft_double(UINT64_C(4604418534313441775), detail::nothing()); }

    static constexpr soft_double my_value_min()           { return soft_double(UINT64_C(4503599627370496),    detail::nothing()); }
    static constexpr soft_double my_value_max()           { return soft_double(UINT64_C(9218868437227405311), detail::nothing()); }
    static constexpr soft_double my_value_lowest()        { return soft_double(UINT64_C(18442240474082181119),detail::nothing()); }
    static constexpr soft_double my_value_epsilon()       { return soft_double(UINT64_C(4372995238176751616), detail::nothing()); }
    static constexpr soft_double my_value_round_error()   { return soft_double(UINT64_C(0x3FE0000000000000),  detail::nothing()); }
    static constexpr soft_double my_value_denorm_min()    { return soft_double(UINT64_C(1),                   detail::nothing()); }
    static constexpr soft_double my_value_infinity()      { return soft_double(UINT64_C(0x7FF0000000000000),  detail::nothing()); }
    static constexpr soft_double my_value_quiet_NaN()     { return soft_double(UINT64_C(0xFFF8000000000000),  detail::nothing()); }
    static constexpr soft_double my_value_signaling_NaN() { return soft_double(UINT64_C(0x7FF8000000000000),  detail::nothing()); }

  private:
    representation_type my_value;

    static constexpr bool my_le(const soft_double& a, const soft_double& b)
    {
      return (detail::signF64UI(a.my_value) != detail::signF64UI(b.my_value))
               ? (detail::signF64UI(a.my_value) || !((a.my_value | b.my_value) & UINT64_C(0x7FFFFFFFFFFFFFFF)))
               : (a.my_value == b.my_value) || (detail::signF64UI(a.my_value) ^ (a.my_value < b.my_value));
    }

    static constexpr bool my_lt(const soft_double& a, const soft_double& b)
    {
      return (detail::signF64UI(a.my_value) != detail::signF64UI(b.my_value))
               ? detail::signF64UI(a.my_value) && ((a.my_value | b.my_value) & UINT64_C(0x7FFFFFFFFFFFFFFF))
               : (a.my_value != b.my_value) && (detail::signF64UI(a.my_value) ^ (a.my_value < b.my_value));
    }

    static uint64_t f64_add(const uint64_t a, const uint64_t b)
    {
      const bool signA = detail::signF64UI(a);
      const bool signB = detail::signF64UI(b);

      if(signA == signB)
      {
        return softfloat_addMagsF64(a, b, signA);
      }
      else
      {
        return softfloat_subMagsF64(a, b, signA);
      }
    }

    static uint64_t f64_sub(const uint64_t a, const uint64_t b)
    {
      const bool signA = detail::signF64UI(a);
      const bool signB = detail::signF64UI(b);

      if(signA == signB)
      {
        return softfloat_subMagsF64(a, b, signA);
      }
      else
      {
        return softfloat_addMagsF64(a, b, signA);
      }
    }

    static uint64_t f64_mul(const uint64_t a, const uint64_t b)
    {
      const bool     signA = detail::signF64UI(a);
      const int16_t  expA  = detail::expF64UI (a);
            uint64_t sigA  = detail::fracF64UI(a);

      const bool     signB = detail::signF64UI(b);
      const int16_t  expB  = detail::expF64UI (b);
            uint64_t sigB  = detail::fracF64UI(b);

      const bool signZ = signA ^ signB;

      if(((!expA) && (!sigA)) || ((!expB) && (!sigB)))
      {
        return detail::packToF64UI(signZ, 0, 0);
      }
      else
      {
        int16_t expZ = (int16_t) (expA + expB) - 0x3FF;

        sigA = (sigA | UINT64_C(0x0010000000000000)) << 10U;
        sigB = (sigB | UINT64_C(0x0010000000000000)) << 11U;


        // Compute the 128-bit product of sigA and sigB.

        const uint32_t a32 = (uint32_t) (sigA >> 32U);
        const uint32_t a0  = (uint32_t)  sigA;
        const uint32_t b32 = (uint32_t) (sigB >> 32U);
        const uint32_t b0  = (uint32_t)  sigB;

        struct detail::uint128_as_struct sig128Z;

        sig128Z.v0 = ((uint64_t) a0) * b0;

        uint64_t mid1 =                    ((uint64_t) a32) * b0;
        uint64_t mid  = mid1 + (uint64_t) (((uint64_t) b32) * a0);

        sig128Z.v64  = ((uint64_t) a32) * b32;
        sig128Z.v64 += ((uint64_t) (mid < mid1) << 32U) | (uint32_t) (mid >> 32U);

        mid <<= 32U;

        sig128Z.v0  += mid;
        sig128Z.v64 += (sig128Z.v0 < mid);

        if(sig128Z.v0 != 0U)
        {
          sig128Z.v64 |= 1U;
        }

        if(sig128Z.v64 < UINT64_C(0x4000000000000000))
        {
          --expZ;

          sig128Z.v64 <<= 1U;
        }

        return softfloat_roundPackToF64(signZ, expZ, sig128Z.v64);
      }
    }

    static uint64_t f64_div(const uint64_t a, const uint64_t b)
    {
      const bool     signA = detail::signF64UI(a);
            int16_t  expA  = detail::expF64UI (a);
            uint64_t sigA  = detail::fracF64UI(a);

      const bool     signB = detail::signF64UI(b);
            int16_t  expB  = detail::expF64UI (b);
            uint64_t sigB  = detail::fracF64UI(b);

      const bool signZ = signA ^ signB;

      if((!expA) && (!sigA))
      {
        return detail::packToF64UI(signZ, 0, 0);
      }
      else
      {
        int16_t expZ = (expA - expB) + 0x3FE;

        sigA |= UINT64_C(0x0010000000000000);
        sigB |= UINT64_C(0x0010000000000000);

        if(sigA < sigB)
        {
          --expZ;

          sigA <<= 11U;
        }
        else
        {
          sigA <<= 10U;
        }

        sigB <<= 11U;

        const uint32_t recip32 = detail::softfloat_approxRecip32_1(sigB >> 32U) - 2U;
        const uint32_t sig32Z  = ((uint32_t) (sigA >> 32U) * (uint64_t) recip32) >> 32U;

        uint32_t doubleTerm = sig32Z << 1U;

        uint64_t rem =   ((sigA - (uint64_t) doubleTerm *  (uint32_t) (sigB >> 32U)) << 28U)
                                - (uint64_t) doubleTerm * ((uint32_t)  sigB >> 4U);

        uint32_t q = (((uint32_t) (rem >> 32U) * (uint64_t) recip32) >> 32U) + 4U;

        uint64_t sigZ = ((uint64_t) sig32Z << 32U) + ((uint64_t) q << 4U);

        if((sigZ & 0x1FF) < (4UL << 4U))
        {
          q    &=  (uint32_t) ~7U;
          sigZ &= ~(uint64_t) 0x7F;

          doubleTerm = q << 1U;

          rem =   ((rem - (uint64_t) doubleTerm *  (uint32_t) (sigB >> 32U)) << 28U)
                -         (uint64_t) doubleTerm * ((uint32_t)  sigB >> 4U);

          if(rem & UINT64_C(0x8000000000000000))
          {
            sigZ -= (1UL << 7U);
          }
          else
          {
            if(rem)
            {
              sigZ |= 1U;
            }
          }
        }

        return softfloat_roundPackToF64(signZ, expZ, sigZ);
      }
    }

    static uint64_t f64_sqrt(const uint64_t a)
    {
      bool     signA = detail::signF64UI(a);
      int16_t  expA  = detail::expF64UI (a);
      uint64_t sigA  = detail::fracF64UI(a);

      if(((!expA) && (!sigA)) || signA)
      {
        return a;
      }
      else
      {
        /*------------------------------------------------------------------------
        | (`sig32Z' is guaranteed to be a lower bound on the square root of
        | `sig32A', which makes `sig32Z' also a lower bound on the square root of
        | `sigA'.)
        *------------------------------------------------------------------------*/
        int16_t expZ = ((expA - 0x3FF) >> 1) + 0x3FE;

        expA &= 1;
        sigA |= UINT64_C(0x0010000000000000);

        uint32_t sig32A      = (uint32_t) (sigA >> 21U);
        uint32_t recipSqrt32 = softfloat_approxRecipSqrt32_1((uint32_t) expA, sig32A);
        uint32_t sig32Z      = ((uint64_t) sig32A * recipSqrt32) >> 32U;

        if(expA)
        {
          sigA   <<= 8U;
          sig32Z >>= 1U;
        }
        else
        {
          sigA <<= 9U;
        }

              uint64_t rem = sigA - (uint64_t) sig32Z * sig32Z;
        const uint32_t q   = ((uint32_t) (rem >> 2U) * (uint64_t) recipSqrt32) >> 32U;

        uint64_t sigZ = ((uint64_t) sig32Z << 32U | (1UL << 5U)) + ((uint64_t) q << 3U);

        if((sigZ & 0x1FFU) < 0x22U)
        {
          sigZ &= ~(uint64_t) 0x3FU;

          const uint64_t shiftedSigZ = sigZ >> 6U;

          rem = (sigA << 52U) - shiftedSigZ * shiftedSigZ;

          if(rem & UINT64_C(0x8000000000000000))
          {
            --sigZ;
          }
          else
          {
            if(rem)
            {
              sigZ |= 1U;
            }
          }
        }

        return softfloat_roundPackToF64(0, expZ, sigZ);
      }
    }

    static uint32_t f64_to_ui32(const uint64_t a)
    {
      const bool     sign = detail::signF64UI(a);
      const int16_t  expA = detail::expF64UI (a);
            uint64_t sig  = detail::fracF64UI(a);

      if(expA)
      {
        sig |= UINT64_C(0x0010000000000000);
      }

      const int16_t shiftDist = 0x427 - expA;

      if(0 < shiftDist)
      {
        sig = detail::softfloat_shiftRightJam64(sig, (uint32_t) shiftDist);
      }

      return softfloat_roundToUI32(sign, sig);
    }

    static int32_t f64_to__i32(const uint64_t a)
    {
      const bool     sign = detail::signF64UI(a);
      const int16_t  expA = detail::expF64UI (a);
            uint64_t sig  = detail::fracF64UI(a);

      if(expA)
      {
        sig |= UINT64_C(0x0010000000000000);
      }

      int16_t shiftDist = 0x427 - expA;

      if(0 < shiftDist)
      {
        sig = detail::softfloat_shiftRightJam64(sig, (uint32_t) shiftDist);
      }

      return softfloat_roundToI32(sign, sig);
    }

    static uint64_t f64_to_ui64(const uint64_t a)
    {
      const bool     sign = detail::signF64UI(a);
      const int16_t  expA = detail::expF64UI (a);
            uint64_t sig  = detail::fracF64UI(a);

      if(expA)
      {
        sig |= UINT64_C(0x0010000000000000);
      }

      int16_t shiftDist = 0x433 - expA;

      struct detail::uint64_extra sigExtra;

      if(shiftDist <= 0)
      {
        if(shiftDist < -11)
        {
          shiftDist = -11;
        }

        sigExtra.v = sig << -shiftDist;
        sigExtra.extra = 0;
      }
      else
      {
        sigExtra = detail::softfloat_shiftRightJam64Extra(sig, 0U, (uint32_t) shiftDist);
      }

      return softfloat_roundToUI64(sign, sigExtra.v);
    }

    static int64_t f64_to__i64(const uint64_t a)
    {
      const bool     sign = detail::signF64UI(a);
      const int16_t  expA = detail::expF64UI (a);
            uint64_t sig  = detail::fracF64UI(a);

      if(expA)
      {
        sig |= UINT64_C(0x0010000000000000);
      }

      int16_t shiftDist = (int16_t) (INT16_C(0x433) - expA);

      struct detail::uint64_extra sigExtra;

      if(shiftDist <= 0)
      {
        if(shiftDist < -11)
        {
          shiftDist = -11;
        }

        sigExtra.v = sig << -shiftDist;
        sigExtra.extra = 0;
      }
      else
      {
        sigExtra = detail::softfloat_shiftRightJam64Extra(sig, 0U, (uint32_t) shiftDist);
      }

      return softfloat_roundToI64(sign, sigExtra.v);
    }

    static float f64_to_f32(const uint64_t a)
    {
      const bool     sign = detail::signF64UI(a);
      const int16_t  expA = detail::expF64UI (a);
      const uint64_t frac = detail::fracF64UI(a);

      const uint32_t frac32 = (uint32_t) detail::softfloat_shortShiftRightJam64(frac, 22);

      const float f = softfloat_roundPackToF32(sign, (int16_t) (expA - INT16_C(0x381)), frac32 | UINT32_C(0x40000000));

      return f;
    }

    static float softfloat_roundPackToF32(bool sign, int16_t expA, uint32_t sig)
    {
      constexpr uint_fast8_t roundIncrement = UINT8_C(0x40);

      const uint_fast8_t roundBits = sig & 0x7F;

      sig = (sig + roundIncrement)>>7;

      sig &= ~(uint_fast32_t) (((roundBits ^ 0x40) == 0U ? 1U : 0U) & 1U);

      if(!sig)
      {
        expA = 0;
      }

      return detail::uz_type<float>(detail::packToF32UI(sign, expA, sig)).my_f;
    }

    static constexpr uint64_t my__i32_to_f64(const int32_t a)
    {
      return
        (!a) ? 0U
             : detail::packToF64UI((a < 0), 0x432 - int_fast8_t((int_fast8_t) (detail::softfloat_countLeadingZeros32(uint32_t((a < 0) ? detail::negate((uint32_t) a) : (uint32_t) a)) + 21U)), (uint64_t) uint32_t((a < 0) ? detail::negate((uint32_t) a) : (uint32_t) a) << int_fast8_t((int_fast8_t) (detail::softfloat_countLeadingZeros32(uint32_t((a < 0) ? detail::negate((uint32_t) a) : (uint32_t) a)) + 21U)));
    }

    static constexpr uint64_t my__i64_to_f64(const int64_t a)
    {
      return
        (!((uint64_t) a & UINT64_C(0x7FFFFFFFFFFFFFFF)))
          ? ((a < 0) ? detail::packToF64UI(1, 0x43E, 0) : 0U)
          : softfloat_normRoundPackToF64((a < 0), 0x43C, uint64_t((a < 0) ? detail::negate((uint64_t) a) : (uint64_t) a));
    }

    static constexpr uint64_t my_ui32_to_f64(const uint32_t a)
    {
      return
        ((a == 0U)
          ? 0U
          : detail::packToF64UI(0, 0x432 - int_fast8_t((int_fast8_t) (detail::softfloat_countLeadingZeros32(a) + 21U)), ((uint64_t) a) << int_fast8_t((int_fast8_t) (detail::softfloat_countLeadingZeros32(a) + 21U))));
    }

    static constexpr uint64_t my_ui64_to_f64(const uint64_t a)
    {
      return (!a) ? (uint64_t) 0U
                  : (a & UINT64_C(0x8000000000000000)) ? softfloat_roundPackToF64(0, 0x43D, detail::softfloat_shortShiftRightJam64(a, 1))
                                                       : softfloat_normRoundPackToF64(0, 0x43C, a);
    }

    static constexpr int32_t softfloat_roundToI32(bool sign, uint64_t sig)
    {
      return (int32_t) ((uint32_t) (sign ? detail::negate((uint32_t) (sig >> 12U)) : (uint32_t) (sig >> 12U)));
    }

    static constexpr int64_t softfloat_roundToI64(bool sign, uint64_t sig)
    {
      return (int64_t) ((uint64_t) (sign ? detail::negate(sig) : sig));
    }

    static constexpr uint32_t softfloat_roundToUI32(bool sign, uint64_t sig)
    {
      return ((sign) && (sig == 0U)) ? 0U : (uint32_t) (sig >> 12);
    }

    static constexpr uint64_t softfloat_roundToUI64(bool sign, uint64_t sig)
    {
      return ((sign) && (sig == 0U)) ? 0U : sig;
    }

    static uint64_t softfloat_addMagsF64(uint64_t uiA, uint64_t uiB, bool signZ)
    {
      const int16_t  expA = detail::expF64UI (uiA);
            uint64_t sigA = detail::fracF64UI(uiA);
      const int16_t  expB = detail::expF64UI (uiB);
            uint64_t sigB = detail::fracF64UI(uiB);

      const int16_t expDiff = expA - expB;

      int16_t  expZ;
      uint64_t sigZ;

      if(expDiff == 0)
      {
        expZ = expA;
        sigZ = (uint64_t) (UINT64_C(0x0020000000000000) + sigA) + sigB;
        sigZ <<= 9U;
      }
      else
      {
        sigA <<= 9U;
        sigB <<= 9U;

        if(expDiff < 0)
        {
          expZ = expB;

          if(expA)
          {
            sigA += UINT64_C(0x2000000000000000);
          }
          else
          {
            sigA <<= 1;
          }

          sigA = detail::softfloat_shiftRightJam64(sigA, (uint32_t) (-expDiff));
        }
        else
        {
          expZ = expA;

          if(expB)
          {
            sigB += UINT64_C(0x2000000000000000);
          }
          else
          {
            sigB <<= 1U;
          }

          sigB = detail::softfloat_shiftRightJam64(sigB, (uint32_t) expDiff);
        }

        sigZ = (uint64_t) (UINT64_C(0x2000000000000000) + sigA) + sigB;

        if(sigZ < UINT64_C(0x4000000000000000))
        {
          --expZ;

          sigZ <<= 1U;
        }
      }

      return softfloat_roundPackToF64(signZ, expZ, sigZ);
    }

    /*----------------------------------------------------------------------------
    | Returns an approximation to the reciprocal of the square root of the number
    | represented by 'a', where 'a' is interpreted as an unsigned fixed-point
    | number either with one integer bit and 31 fraction bits or with two integer
    | bits and 30 fraction bits.
    *----------------------------------------------------------------------------*/
    static uint32_t softfloat_approxRecipSqrt32_1(uint32_t oddExpA, uint32_t a)
    {
      constexpr std::array<uint16_t, 16U> softfloat_approxRecipSqrt_1k0s =
      {{
        UINT16_C(0xB4C9), UINT16_C(0xFFAB), UINT16_C(0xAA7D), UINT16_C(0xF11C),
        UINT16_C(0xA1C5), UINT16_C(0xE4C7), UINT16_C(0x9A43), UINT16_C(0xDA29),
        UINT16_C(0x93B5), UINT16_C(0xD0E5), UINT16_C(0x8DED), UINT16_C(0xC8B7),
        UINT16_C(0x88C6), UINT16_C(0xC16D), UINT16_C(0x8424), UINT16_C(0xBAE1)
      }};

      constexpr std::array<uint16_t, 16U> softfloat_approxRecipSqrt_1k1s =
      {{
        UINT16_C(0xA5A5), UINT16_C(0xEA42), UINT16_C(0x8C21), UINT16_C(0xC62D),
        UINT16_C(0x788F), UINT16_C(0xAA7F), UINT16_C(0x6928), UINT16_C(0x94B6),
        UINT16_C(0x5CC7), UINT16_C(0x8335), UINT16_C(0x52A6), UINT16_C(0x74E2),
        UINT16_C(0x4A3E), UINT16_C(0x68FE), UINT16_C(0x432B), UINT16_C(0x5EFD)
      }};

      int16_t index       = (int16_t) (((uint32_t) (a >> 27U) & 0xEU) + oddExpA);
      uint16_t     eps    = (uint16_t) (a >> 12);
      uint16_t     r0     =                           softfloat_approxRecipSqrt_1k0s[(unsigned) index]
                            - (uint16_t) ((uint32_t) (softfloat_approxRecipSqrt_1k1s[(unsigned) index] * (uint32_t) eps) >> 20U);
      uint32_t     ESqrR0 = (uint32_t) r0 * r0;

      if(!oddExpA)
      {
        ESqrR0 <<= 1U;
      }

      const uint32_t sigma0 = ~(uint32_t) (((uint32_t) ESqrR0 * (uint64_t) a) >> 23U);

      uint32_t r = (((uint32_t) r0) << 16U) + (uint32_t) ((r0 * (uint64_t) sigma0) >> 25U);

      const uint32_t sqrSigma0 = (uint32_t) ((uint64_t) ((uint64_t) sigma0 * sigma0) >> 32U);

      r += (uint32_t) ((uint64_t) ((uint32_t) ((uint32_t) ((r >> 1U) + (r >> 3U)) - ((uint32_t) r0 << 14U)) * (uint64_t) sqrSigma0) >> 48U);

      if(!(r & UINT32_C(0x80000000)))
      {
        r = UINT32_C(0x80000000);
      }

      return r;
    }

    static uint64_t softfloat_normRoundPackToF64(bool sign, int16_t expA, uint64_t sig)
    {
      const int_fast8_t shiftDist = (int_fast8_t) (detail::softfloat_countLeadingZeros64(sig) - 1U);

      expA -= shiftDist;

      if((10 <= shiftDist) && ((uint32_t) expA < 0x7FDU))
      {
        const uint64_t uZ = detail::packToF64UI(sign, sig ? expA : 0, sig << (shiftDist - 10));

        return uZ;
      }
      else
      {
        return softfloat_roundPackToF64(sign, expA, sig << shiftDist);
      }
    }

    static uint64_t softfloat_roundPackToF64(bool sign, int16_t expA, uint64_t sig)
    {
      if(0x7FDU <= (uint16_t) expA)
      {
        if(expA < 0)
        {
          sig  = detail::softfloat_shiftRightJam64(sig, (uint32_t) -expA);
          expA = 0;
        }
      }

      const uint16_t roundBits = sig & 0x3FFU;

      sig = (sig + 0x200U) >> 10U;

      sig &= (uint64_t) (~(uint64_t) (((roundBits ^ 0x200U) == 0U ? 1U : 0U) & 1U));

      if(!sig)
      {
        expA = 0;
      }

      const uint64_t uiZ = detail::packToF64UI(sign, expA, sig);

      return uiZ;
    }

    static uint64_t softfloat_subMagsF64(uint64_t uiA, uint64_t uiB, bool signZ)
    {
      uint64_t uiZ;
      int16_t  expZ;

      int16_t  expA = detail::expF64UI(uiA);
      uint64_t sigA = detail::fracF64UI(uiA);
      int16_t  expB = detail::expF64UI(uiB);
      uint64_t sigB = detail::fracF64UI(uiB);

      const int16_t expDiff = expA - expB;

      if(!expDiff)
      {
        int64_t sigDiff = (int64_t) (sigA - sigB);

        if(!sigDiff)
        {
          uiZ = detail::packToF64UI(false, 0, 0);
        }
        else
        {
          if(expA)
          {
            --expA;
          }

          if(sigDiff < 0)
          {
            signZ   = (!signZ);
            sigDiff = -sigDiff;
          }

          int_fast8_t shiftDist = (int_fast8_t) (detail::softfloat_countLeadingZeros64((uint64_t) sigDiff) - 11U);

          expZ = expA - shiftDist;

          if(expZ < 0)
          {
            shiftDist = (int_fast8_t) expA;

            expZ = 0;
          }

          uiZ = detail::packToF64UI(signZ, expZ, sigDiff << shiftDist);
        }
      }
      else
      {
        sigA <<= 10U;
        sigB <<= 10U;

        uint64_t sigZ;

        if(expDiff < 0)
        {
          signZ = (!signZ);

          sigA += ((expA != 0) ? UINT64_C(0x4000000000000000) : sigA);
          sigA  = detail::softfloat_shiftRightJam64(sigA, (uint32_t) -expDiff);

          sigB |= UINT64_C(0x4000000000000000);

          expZ = expB;
          sigZ = sigB - sigA;
        }
        else
        {
          sigB += ((expB != 0) ? UINT64_C(0x4000000000000000) : sigB);
          sigB  = detail::softfloat_shiftRightJam64(sigB, (uint32_t) expDiff);

          sigA |= UINT64_C(0x4000000000000000);

          expZ = expA;
          sigZ = sigA - sigB;
        }

        return softfloat_normRoundPackToF64(signZ, (int16_t) (expZ - 1), sigZ);
      }

      return uiZ;
    }

    #if !defined(SOFT_DOUBLE_DISABLE_IOSTREAM)
    template<typename char_type, typename traits_type>
    friend std::basic_ostream<char_type, traits_type>& operator<<(std::basic_ostream<char_type, traits_type>& os, const soft_double& f)
    {
      std::basic_ostringstream<char_type, traits_type> ostr;

      // Copy all ostream settings from out to local ostr.
      ostr.flags(os.flags());
      ostr.imbue(os.getloc());
      ostr.precision(os.precision());

      static_cast<void>(ostr << (double) f);

      return (os << ostr.str());
    }

    template<typename char_type, typename traits_type>
    friend std::basic_istream<char_type, traits_type>& operator>>(std::basic_istream<char_type, traits_type>& is, soft_double& f)
    {
      double v;

      // Receive a floating-point number from the input stream.
      static_cast<void>(is >> v);

      // Subsequently make a fixed-point object from it.
      f = v;

      return is;
    }
    #endif // !SOFT_DOUBLE_DISABLE_IOSTREAM

    friend bool isfinite(const soft_double x) { return ((isnan(x) == false) && (isinf(x) == false)); }
    friend bool isnan   (const soft_double x) { return  (x.my_value == my_value_quiet_NaN().my_value); }
    friend bool isinf   (const soft_double x) { return ((x.my_value & my_value_infinity().my_value) == my_value_infinity().my_value); }

    friend inline soft_double fabs (const soft_double x) { return soft_double((uint64_t) (x.my_value & UINT64_C(0x7FFFFFFFFFFFFFFF)), detail::nothing()); }
    friend inline soft_double sqrt (const soft_double x) { return soft_double(f64_sqrt(x.my_value), detail::nothing()); }

    friend inline soft_double frexp(const soft_double x, int* expptr)
    {
      const bool     sign = detail::signF64UI(x.my_value);
      const int16_t  expA = detail::expF64UI (x.my_value) - INT16_C(0x3FE);
      const uint64_t frac = detail::fracF64UI(x.my_value);

      if(expptr != nullptr)
      {
        *expptr = (int) expA;
      }

      return soft_double(detail::packToF64UI(sign, INT16_C(0x3FE), frac), detail::nothing());
    }

    friend inline soft_double ldexp(const soft_double x, int expval)
    {
      const int expA = (int) (detail::expF64UI(x.my_value) + expval);

      return soft_double((uint64_t) ((uint64_t) (x.my_value & (uint64_t) ~(UINT64_C(0x7FF) << 52U)) | (uint64_t) expA << 52U), detail::nothing());
    }

    friend inline soft_double floor(const soft_double x)
    {
      soft_double result;

      if(x < 0)
      {
        const int64_t     xn = (int64_t) x;
        const soft_double fn = soft_double(xn);

        const bool is_pure_integer = (fn.my_value == x.my_value);

        result =
          (is_pure_integer ? fn : soft_double((int64_t) (x - soft_double::my_value_one())));
      }
      else
      {
        result = soft_double((int64_t)  x);
      }

      return result;
    }

    friend inline soft_double ceil(const soft_double x)
    {
      soft_double result;

      if(x < 0)
      {
        result = soft_double((int64_t)  x);
      }
      else
      {
        const int64_t     xn = (int64_t) x;
        const soft_double fn = soft_double(xn);

        const bool is_pure_integer = (fn.my_value == x.my_value);

        result =
          (is_pure_integer ? fn : soft_double((int64_t) (x + soft_double::my_value_one())));
      }

      return result;
    }

    friend inline soft_double exp(const soft_double x)
    {
      // PadeApproximant[Exp[x] - 1, {x, 0, {6, 6}}]
      // FullSimplify[%]
      //   (84 x (7920 + 240 x^2 + x^4))
      // / (665280 + x (-332640 + x (75600 + x (-10080 + x (840 + (-42 + x) x)))))

      const int n = (int) (x / soft_double::my_value_ln2());

      // Scale the argument such that Exp[x] = Exp[a + n * ln2].
      soft_double a = x - (n * soft_double::my_value_ln2());

      // Scale the argument yet again with division by 4.
      const int expA = (int) (detail::expF64UI(a.my_value) - 2);

      a.my_value &= (uint64_t) ~(UINT64_C(0x7FF) << 52U);
      a.my_value |= (uint64_t) expA << 52U;

      const soft_double a2 = a * a;

      // Use the small-argument Pade approximation having coefficients shown above.
      const soft_double top = (84 * a * (7920 + (240 + a2) * a2));
      const soft_double bot = (665280 + a * (-332640 + a * (75600 + a * (-10080 + a * (840 + (-42 + a) * a)))));

      soft_double result  = soft_double::my_value_one() + (top / bot);

      result *= result;
      result *= result;

      if(n != 0)
      {
        const soft_double p2 = ldexp(soft_double::my_value_one(), n);

        result *= p2;
      }

      return result;
    }

    friend inline soft_double log(const soft_double x)
    {
      soft_double result;

      if(x < soft_double::my_value_one())
      {
        result = -log(soft_double::my_value_one() / x);
      }
      else if(x > soft_double::my_value_one())
      {
        // See J.F. Hart et al., "Computer Approximations" (Krieger Publishing 1978),
        // page 111 (with correction) log_e = zP(z^2) / Q(z^2), where the leading 'z'
        // in the book is incorrect and coefficients are listed in LOGE 2688 on page 194.

        // P00 = -0.9812796124599728774775146E3;
        // P01 = +0.2098680741193909440902139E4;
        // P02 = -0.149596980292286125003062E4;
        // P03 = +0.39599373637329080057224E3;
        // P04 = -0.2857383397938418121918E2;
        // Q00 = -0.4906398062299865742258528E3;
        // Q01 = +0.1212886972673648778600404E4;
        // Q02 = -0.1054152597775536603834536E4;
        // Q03 = +0.37689507387121749065832E3;
        // Q04 = -0.4784212345106557147125E2;
        // Q05 = +0.1E1;

        // Scale the argument such that 1 <= a < 2.
        const int16_t n = detail::expF64UI(x.my_value) - INT16_C(0x3FF);

        const soft_double a((uint64_t) ((uint64_t) (x.my_value & (uint64_t) ~(UINT64_C(0x7FF) << 52U)) | UINT64_C(0x3FF) << 52U), detail::nothing());

        const soft_double z  = (a - 1) / (a + 1);
        const soft_double z2 = z * z;

        const soft_double pz2 =  (((((     + soft_double(UINT64_C(0xC03C92E6C89EC9E1), detail::nothing()))
                                      * z2 + soft_double(UINT64_C(0x4078BFE6581C8213), detail::nothing()))
                                      * z2 + soft_double(UINT64_C(0xC0975FE114047504), detail::nothing()))
                                      * z2 + soft_double(UINT64_C(0x40A0655C8A1C19C3), detail::nothing()))
                                      * z2 + soft_double(UINT64_C(0xC08EAA3CA575191A), detail::nothing()));

        const soft_double qz2 = ((((((     + soft_double(UINT64_C(0x3FF0000000000000), detail::nothing()))
                                      * z2 + soft_double(UINT64_C(0xC047EBCAB384C2B9), detail::nothing()))
                                      * z2 + soft_double(UINT64_C(0x40778E5238FAC622), detail::nothing()))
                                      * z2 + soft_double(UINT64_C(0xC090789C42975D7D), detail::nothing()))
                                      * z2 + soft_double(UINT64_C(0x4092F38C42908712), detail::nothing()))
                                      * z2 + soft_double(UINT64_C(0xC07EAA3CA575191C), detail::nothing()));

        result  = ((z * pz2) / qz2);

        result += (n * soft_double::my_value_ln2());
      }
      else
      {
        result = soft_double::my_value_zero();
      }

      return result;
    }

    friend inline soft_double pow(const soft_double x, const soft_double a)
    {
      return exp(a * log(x));
    }

    template<typename UnsignedIntegralType,
             typename std::enable_if<(   (std::is_integral<UnsignedIntegralType>::value == true)
                                      && (std::is_unsigned<UnsignedIntegralType>::value == true))>::type const*>
    friend soft_double pow(const soft_double x, const UnsignedIntegralType u)
    {
      soft_double result;

      if     (u == 0U) { result = soft_double::my_value_one(); }
      else if(u == 1U) { result = x; }
      else if(u == 2U) { result = x * x; }
      else
      {
        using floating_point_type = soft_double;

        result = soft_double::my_value_one();

        floating_point_type y(x);

        for(std::uint32_t p_local = (std::uint32_t) u; p_local != 0U; p_local >>= 1U)
        {
          if((p_local & 1U) != 0U)
          {
            result *= y;
          }

          y *= y;
        }
      }

      return result;
    }

    template<typename SignedIntegralType,
             typename std::enable_if<(   (std::is_integral<SignedIntegralType>::value == true)
                                      && (std::is_signed  <SignedIntegralType>::value == true))>::type const*>
    friend soft_double pow(const soft_double x, const SignedIntegralType n)
    {
      soft_double result;

      if     (n <  0) { result = soft_double::my_value_one() / pow(x, (SignedIntegralType) -n); }
      else if(n == 0) { result = soft_double::my_value_one(); }
      else if(n == 1) { result = x; }
      else if(n == 2) { result = x * x; }
      else
      {
        using floating_point_type = soft_double;

        result = soft_double::my_value_one();

        floating_point_type y(x);

        for(std::uint32_t p_local = (std::uint32_t) n; p_local != 0U; p_local >>= 1U)
        {
          if((p_local & 1U) != 0U)
          {
            result *= y;
          }

          y *= y;
        }
      }

      return result;
    }

    friend inline soft_double sin(const soft_double x);
    friend inline soft_double cos(const soft_double x);
    friend inline soft_double tan(const soft_double x);

    friend inline soft_double operator+(const soft_double& a, const soft_double& b) { return soft_double(f64_add(a.my_value, b.my_value), detail::nothing()); }
    friend inline soft_double operator-(const soft_double& a, const soft_double& b) { return soft_double(f64_sub(a.my_value, b.my_value), detail::nothing()); }
    friend inline soft_double operator*(const soft_double& a, const soft_double& b) { return soft_double(f64_mul(a.my_value, b.my_value), detail::nothing()); }
    friend inline soft_double operator/(const soft_double& a, const soft_double& b) { return soft_double(f64_div(a.my_value, b.my_value), detail::nothing()); }

    template<typename UnsignedIntegralType> friend typename std::enable_if<(std::is_integral<UnsignedIntegralType>::value == true) && (std::is_unsigned<UnsignedIntegralType>::value == true), soft_double>::type operator+(const soft_double& u, UnsignedIntegralType n) { return soft_double(u) += soft_double(n); }
    template<typename UnsignedIntegralType> friend typename std::enable_if<(std::is_integral<UnsignedIntegralType>::value == true) && (std::is_unsigned<UnsignedIntegralType>::value == true), soft_double>::type operator-(const soft_double& u, UnsignedIntegralType n) { return soft_double(u) -= soft_double(n); }
    template<typename UnsignedIntegralType> friend typename std::enable_if<(std::is_integral<UnsignedIntegralType>::value == true) && (std::is_unsigned<UnsignedIntegralType>::value == true), soft_double>::type operator*(const soft_double& u, UnsignedIntegralType n) { return soft_double(u) *= soft_double(n); }
    template<typename UnsignedIntegralType> friend typename std::enable_if<(std::is_integral<UnsignedIntegralType>::value == true) && (std::is_unsigned<UnsignedIntegralType>::value == true), soft_double>::type operator/(const soft_double& u, UnsignedIntegralType n) { return soft_double(u) /= soft_double(n); }

    template<typename UnsignedIntegralType> friend typename std::enable_if<(std::is_integral<UnsignedIntegralType>::value == true) && (std::is_unsigned<UnsignedIntegralType>::value == true), soft_double>::type operator+(UnsignedIntegralType n, const soft_double& u) { return soft_double(n) += u; }
    template<typename UnsignedIntegralType> friend typename std::enable_if<(std::is_integral<UnsignedIntegralType>::value == true) && (std::is_unsigned<UnsignedIntegralType>::value == true), soft_double>::type operator-(UnsignedIntegralType n, const soft_double& u) { return soft_double(n) -= u; }
    template<typename UnsignedIntegralType> friend typename std::enable_if<(std::is_integral<UnsignedIntegralType>::value == true) && (std::is_unsigned<UnsignedIntegralType>::value == true), soft_double>::type operator*(UnsignedIntegralType n, const soft_double& u) { return soft_double(n) *= u; }
    template<typename UnsignedIntegralType> friend typename std::enable_if<(std::is_integral<UnsignedIntegralType>::value == true) && (std::is_unsigned<UnsignedIntegralType>::value == true), soft_double>::type operator/(UnsignedIntegralType n, const soft_double& u) { return soft_double(n) /= u; }

    template<typename SignedIntegralType> friend typename std::enable_if<(std::is_integral<SignedIntegralType>::value == true) && (std::is_signed<SignedIntegralType>::value == true), soft_double>::type operator+(const soft_double& u, SignedIntegralType n) { return soft_double(u) += soft_double(n); }
    template<typename SignedIntegralType> friend typename std::enable_if<(std::is_integral<SignedIntegralType>::value == true) && (std::is_signed<SignedIntegralType>::value == true), soft_double>::type operator-(const soft_double& u, SignedIntegralType n) { return soft_double(u) -= soft_double(n); }
    template<typename SignedIntegralType> friend typename std::enable_if<(std::is_integral<SignedIntegralType>::value == true) && (std::is_signed<SignedIntegralType>::value == true), soft_double>::type operator*(const soft_double& u, SignedIntegralType n) { return soft_double(u) *= soft_double(n); }
    template<typename SignedIntegralType> friend typename std::enable_if<(std::is_integral<SignedIntegralType>::value == true) && (std::is_signed<SignedIntegralType>::value == true), soft_double>::type operator/(const soft_double& u, SignedIntegralType n) { return soft_double(u) /= soft_double(n); }

    template<typename SignedIntegralType> friend typename std::enable_if<(std::is_integral<SignedIntegralType>::value == true) && (std::is_signed<SignedIntegralType>::value == true), soft_double>::type operator+(SignedIntegralType n, const soft_double& u) { return soft_double(n) += u; }
    template<typename SignedIntegralType> friend typename std::enable_if<(std::is_integral<SignedIntegralType>::value == true) && (std::is_signed<SignedIntegralType>::value == true), soft_double>::type operator-(SignedIntegralType n, const soft_double& u) { return soft_double(n) -= u; }
    template<typename SignedIntegralType> friend typename std::enable_if<(std::is_integral<SignedIntegralType>::value == true) && (std::is_signed<SignedIntegralType>::value == true), soft_double>::type operator*(SignedIntegralType n, const soft_double& u) { return soft_double(n) *= u; }
    template<typename SignedIntegralType> friend typename std::enable_if<(std::is_integral<SignedIntegralType>::value == true) && (std::is_signed<SignedIntegralType>::value == true), soft_double>::type operator/(SignedIntegralType n, const soft_double& u) { return soft_double(n) /= u; }

    friend inline soft_double operator+(const soft_double& u, float f) { return soft_double(u) += soft_double(f); }
    friend inline soft_double operator-(const soft_double& u, float f) { return soft_double(u) -= soft_double(f); }
    friend inline soft_double operator*(const soft_double& u, float f) { return soft_double(u) *= soft_double(f); }
    friend inline soft_double operator/(const soft_double& u, float f) { return soft_double(u) /= soft_double(f); }

    friend inline soft_double operator+(float f, const soft_double& u) { return soft_double(f) += u; }
    friend inline soft_double operator-(float f, const soft_double& u) { return soft_double(f) -= u; }
    friend inline soft_double operator*(float f, const soft_double& u) { return soft_double(f) *= u; }
    friend inline soft_double operator/(float f, const soft_double& u) { return soft_double(f) /= u; }

    friend inline soft_double operator+(const soft_double& u, double f) { return soft_double(u) += soft_double(f); }
    friend inline soft_double operator-(const soft_double& u, double f) { return soft_double(u) -= soft_double(f); }
    friend inline soft_double operator*(const soft_double& u, double f) { return soft_double(u) *= soft_double(f); }
    friend inline soft_double operator/(const soft_double& u, double f) { return soft_double(u) /= soft_double(f); }

    friend inline soft_double operator+(double f, const soft_double& u) { return soft_double(f) += u; }
    friend inline soft_double operator-(double f, const soft_double& u) { return soft_double(f) -= u; }
    friend inline soft_double operator*(double f, const soft_double& u) { return soft_double(f) *= u; }
    friend inline soft_double operator/(double f, const soft_double& u) { return soft_double(f) /= u; }

    friend inline soft_double operator+(const soft_double& u, long double f)  { return soft_double(u) += soft_double((double) f); }
    friend inline soft_double operator-(const soft_double& u, long double f)  { return soft_double(u) -= soft_double((double) f); }
    friend inline soft_double operator*(const soft_double& u, long double f)  { return soft_double(u) *= soft_double((double) f); }
    friend inline soft_double operator/(const soft_double& u, long double f)  { return soft_double(u) /= soft_double((double) f); }

    friend inline soft_double operator+(long double f, const soft_double& u) { return soft_double((double) f) += u; }
    friend inline soft_double operator-(long double f, const soft_double& u) { return soft_double((double) f) -= u; }
    friend inline soft_double operator*(long double f, const soft_double& u) { return soft_double((double) f) *= u; }
    friend inline soft_double operator/(long double f, const soft_double& u) { return soft_double((double) f) /= u; }

    friend inline constexpr bool operator< (const soft_double& a, const soft_double& b) { return my_lt(a, b); }
    friend inline constexpr bool operator<=(const soft_double& a, const soft_double& b) { return my_le(a, b); }
    friend inline constexpr bool operator==(const soft_double& a, const soft_double& b) { return  (a.my_value == b.my_value); }
    friend inline constexpr bool operator!=(const soft_double& a, const soft_double& b) { return ((a == b) == false); }
    friend inline constexpr bool operator>=(const soft_double& a, const soft_double& b) { return ((a <  b) == false); }
    friend inline constexpr bool operator> (const soft_double& a, const soft_double& b) { return ((a <= b) == false); }

    template<typename UnsignedIntegralType> friend typename std::enable_if<(std::is_integral<UnsignedIntegralType>::value == true) && (std::is_unsigned<UnsignedIntegralType>::value == true), bool>::type operator< (const soft_double& a, const UnsignedIntegralType u) { return soft_double::my_lt(a, soft_double(u)); }
    template<typename UnsignedIntegralType> friend typename std::enable_if<(std::is_integral<UnsignedIntegralType>::value == true) && (std::is_unsigned<UnsignedIntegralType>::value == true), bool>::type operator<=(const soft_double& a, const UnsignedIntegralType u) { return soft_double::my_le(a, soft_double(u)); }
    template<typename UnsignedIntegralType> friend typename std::enable_if<(std::is_integral<UnsignedIntegralType>::value == true) && (std::is_unsigned<UnsignedIntegralType>::value == true), bool>::type operator==(const soft_double& a, const UnsignedIntegralType u) { return  (a.my_value == soft_double(u).my_value); }
    template<typename UnsignedIntegralType> friend typename std::enable_if<(std::is_integral<UnsignedIntegralType>::value == true) && (std::is_unsigned<UnsignedIntegralType>::value == true), bool>::type operator!=(const soft_double& a, const UnsignedIntegralType u) { return ((a == soft_double(u)) == false); }
    template<typename UnsignedIntegralType> friend typename std::enable_if<(std::is_integral<UnsignedIntegralType>::value == true) && (std::is_unsigned<UnsignedIntegralType>::value == true), bool>::type operator>=(const soft_double& a, const UnsignedIntegralType u) { return ((a <  soft_double(u)) == false); }
    template<typename UnsignedIntegralType> friend typename std::enable_if<(std::is_integral<UnsignedIntegralType>::value == true) && (std::is_unsigned<UnsignedIntegralType>::value == true), bool>::type operator> (const soft_double& a, const UnsignedIntegralType u) { return ((a <= soft_double(u)) == false); }

    template<typename UnsignedIntegralType> friend typename std::enable_if<(std::is_integral<UnsignedIntegralType>::value == true) && (std::is_unsigned<UnsignedIntegralType>::value == true), bool>::type operator< (const UnsignedIntegralType u, const soft_double& a) { return soft_double::my_lt(soft_double(u), a); }
    template<typename UnsignedIntegralType> friend typename std::enable_if<(std::is_integral<UnsignedIntegralType>::value == true) && (std::is_unsigned<UnsignedIntegralType>::value == true), bool>::type operator<=(const UnsignedIntegralType u, const soft_double& a) { return soft_double::my_le(soft_double(u), a); }
    template<typename UnsignedIntegralType> friend typename std::enable_if<(std::is_integral<UnsignedIntegralType>::value == true) && (std::is_unsigned<UnsignedIntegralType>::value == true), bool>::type operator==(const UnsignedIntegralType u, const soft_double& a) { return  (soft_double(u).my_value == a.my_value); }
    template<typename UnsignedIntegralType> friend typename std::enable_if<(std::is_integral<UnsignedIntegralType>::value == true) && (std::is_unsigned<UnsignedIntegralType>::value == true), bool>::type operator!=(const UnsignedIntegralType u, const soft_double& a) { return ((soft_double(u) == a) == false); }
    template<typename UnsignedIntegralType> friend typename std::enable_if<(std::is_integral<UnsignedIntegralType>::value == true) && (std::is_unsigned<UnsignedIntegralType>::value == true), bool>::type operator>=(const UnsignedIntegralType u, const soft_double& a) { return ((soft_double(u) <  a) == false); }
    template<typename UnsignedIntegralType> friend typename std::enable_if<(std::is_integral<UnsignedIntegralType>::value == true) && (std::is_unsigned<UnsignedIntegralType>::value == true), bool>::type operator> (const UnsignedIntegralType u, const soft_double& a) { return ((soft_double(u) <= a) == false); }

    template<typename SignedIntegralType> friend typename std::enable_if<(std::is_integral<SignedIntegralType>::value == true) && (std::is_signed<SignedIntegralType>::value == true), bool>::type operator< (const soft_double& a, const SignedIntegralType n) { return soft_double::my_lt(a, soft_double(n)); }
    template<typename SignedIntegralType> friend typename std::enable_if<(std::is_integral<SignedIntegralType>::value == true) && (std::is_signed<SignedIntegralType>::value == true), bool>::type operator<=(const soft_double& a, const SignedIntegralType n) { return soft_double::my_le(a, soft_double(n)); }
    template<typename SignedIntegralType> friend typename std::enable_if<(std::is_integral<SignedIntegralType>::value == true) && (std::is_signed<SignedIntegralType>::value == true), bool>::type operator==(const soft_double& a, const SignedIntegralType n) { return  (a.my_value == soft_double(n).my_value); }
    template<typename SignedIntegralType> friend typename std::enable_if<(std::is_integral<SignedIntegralType>::value == true) && (std::is_signed<SignedIntegralType>::value == true), bool>::type operator!=(const soft_double& a, const SignedIntegralType n) { return ((a == soft_double(n)) == false); }
    template<typename SignedIntegralType> friend typename std::enable_if<(std::is_integral<SignedIntegralType>::value == true) && (std::is_signed<SignedIntegralType>::value == true), bool>::type operator>=(const soft_double& a, const SignedIntegralType n) { return ((a <  soft_double(n)) == false); }
    template<typename SignedIntegralType> friend typename std::enable_if<(std::is_integral<SignedIntegralType>::value == true) && (std::is_signed<SignedIntegralType>::value == true), bool>::type operator> (const soft_double& a, const SignedIntegralType n) { return ((a <= soft_double(n)) == false); }

    template<typename SignedIntegralType> friend typename std::enable_if<(std::is_integral<SignedIntegralType>::value == true) && (std::is_signed<SignedIntegralType>::value == true), bool>::type operator< (const SignedIntegralType n, const soft_double& a) { return soft_double::my_lt(soft_double(n), a); }
    template<typename SignedIntegralType> friend typename std::enable_if<(std::is_integral<SignedIntegralType>::value == true) && (std::is_signed<SignedIntegralType>::value == true), bool>::type operator<=(const SignedIntegralType n, const soft_double& a) { return soft_double::my_le(soft_double(n), a); }
    template<typename SignedIntegralType> friend typename std::enable_if<(std::is_integral<SignedIntegralType>::value == true) && (std::is_signed<SignedIntegralType>::value == true), bool>::type operator==(const SignedIntegralType n, const soft_double& a) { return  (soft_double(n).my_value == a.my_value); }
    template<typename SignedIntegralType> friend typename std::enable_if<(std::is_integral<SignedIntegralType>::value == true) && (std::is_signed<SignedIntegralType>::value == true), bool>::type operator!=(const SignedIntegralType n, const soft_double& a) { return ((soft_double(n) == a) == false); }
    template<typename SignedIntegralType> friend typename std::enable_if<(std::is_integral<SignedIntegralType>::value == true) && (std::is_signed<SignedIntegralType>::value == true), bool>::type operator>=(const SignedIntegralType n, const soft_double& a) { return ((soft_double(n) <  a) == false); }
    template<typename SignedIntegralType> friend typename std::enable_if<(std::is_integral<SignedIntegralType>::value == true) && (std::is_signed<SignedIntegralType>::value == true), bool>::type operator> (const SignedIntegralType n, const soft_double& a) { return ((soft_double(n) <= a) == false); }

    friend inline bool operator< (const soft_double& a, const float f) { return soft_double::my_lt(a, soft_double(f)); }
    friend inline bool operator<=(const soft_double& a, const float f) { return soft_double::my_le(a, soft_double(f)); }
    friend inline bool operator==(const soft_double& a, const float f) { return  (a.my_value == soft_double(f).my_value); }
    friend inline bool operator!=(const soft_double& a, const float f) { return ((a == soft_double(f)) == false); }
    friend inline bool operator>=(const soft_double& a, const float f) { return ((a <  soft_double(f)) == false); }
    friend inline bool operator> (const soft_double& a, const float f) { return ((a <= soft_double(f)) == false); }

    friend inline bool operator< (const float f, const soft_double& a) { return soft_double::my_lt(soft_double(f), a); }
    friend inline bool operator<=(const float f, const soft_double& a) { return soft_double::my_le(soft_double(f), a); }
    friend inline bool operator==(const float f, const soft_double& a) { return  (soft_double(f).my_value == a.my_value); }
    friend inline bool operator!=(const float f, const soft_double& a) { return ((soft_double(f) == a) == false); }
    friend inline bool operator>=(const float f, const soft_double& a) { return ((soft_double(f) <  a) == false); }
    friend inline bool operator> (const float f, const soft_double& a) { return ((soft_double(f) <= a) == false); }

    friend inline bool operator< (const soft_double& a, const double f) { return soft_double::my_lt(a, soft_double(f)); }
    friend inline bool operator<=(const soft_double& a, const double f) { return soft_double::my_le(a, soft_double(f)); }
    friend inline bool operator==(const soft_double& a, const double f) { return  (a.my_value == soft_double(f).my_value); }
    friend inline bool operator!=(const soft_double& a, const double f) { return ((a == soft_double(f)) == false); }
    friend inline bool operator>=(const soft_double& a, const double f) { return ((a <  soft_double(f)) == false); }
    friend inline bool operator> (const soft_double& a, const double f) { return ((a <= soft_double(f)) == false); }

    friend inline bool operator< (const double f, const soft_double& a) { return soft_double::my_lt(soft_double(f), a); }
    friend inline bool operator<=(const double f, const soft_double& a) { return soft_double::my_le(soft_double(f), a); }
    friend inline bool operator==(const double f, const soft_double& a) { return  (soft_double(f).my_value == a.my_value); }
    friend inline bool operator!=(const double f, const soft_double& a) { return ((soft_double(f) == a) == false); }
    friend inline bool operator>=(const double f, const soft_double& a) { return ((soft_double(f) <  a) == false); }
    friend inline bool operator> (const double f, const soft_double& a) { return ((soft_double(f) <= a) == false); }

    friend inline bool operator< (const soft_double& a, const long double f) { return soft_double::my_lt(a, soft_double((double) f)); }
    friend inline bool operator<=(const soft_double& a, const long double f) { return soft_double::my_le(a, soft_double((double) f)); }
    friend inline bool operator==(const soft_double& a, const long double f) { return  (a.my_value == soft_double((double) f).my_value); }
    friend inline bool operator!=(const soft_double& a, const long double f) { return ((a == soft_double((double) f)) == false); }
    friend inline bool operator>=(const soft_double& a, const long double f) { return ((a <  soft_double((double) f)) == false); }
    friend inline bool operator> (const soft_double& a, const long double f) { return ((a <= soft_double((double) f)) == false); }

    friend inline bool operator< (const long double f, const soft_double& a) { return soft_double::my_lt(soft_double((double) f), a); }
    friend inline bool operator<=(const long double f, const soft_double& a) { return soft_double::my_le(soft_double((double) f), a); }
    friend inline bool operator==(const long double f, const soft_double& a) { return  (soft_double((double) f).my_value == a.my_value); }
    friend inline bool operator!=(const long double f, const soft_double& a) { return ((soft_double((double) f) == a) == false); }
    friend inline bool operator>=(const long double f, const soft_double& a) { return ((soft_double((double) f) <  a) == false); }
    friend inline bool operator> (const long double f, const soft_double& a) { return ((soft_double((double) f) <= a) == false); }
  };

  namespace detail {

  inline soft_double sin_pade(soft_double x)
  {
    // PadeApproximant[Sin[x], {x, 0, {7,7}}]
    // FullSimplify[%]

    //    x (11511339840 - 1640635920 x^2 + 52785432 x^4 - 479249 x^6)
    // / (7 ( 1644477120  +  39702960 x^2 +   453960 x^4 +   2623 x^6))

    static const soft_double coef_sin_top_0(INT64_C(+11511339840));
    static const soft_double coef_sin_top_1(INT32_C(-1640635920));
    static const soft_double coef_sin_top_2(INT32_C(+52785432));
    static const soft_double coef_sin_top_3(INT32_C(-479249));

    static const soft_double coef_sin_bot_0(UINT32_C(+1644477120));
    static const soft_double coef_sin_bot_1(UINT32_C(+39702960));
    static const soft_double coef_sin_bot_2(UINT32_C(+453960));
    static const soft_double coef_sin_bot_3(UINT32_C(+2623));


    const soft_double x2(x * x);

    const soft_double top = ((((     + coef_sin_top_3)
                                * x2 + coef_sin_top_2)
                                * x2 + coef_sin_top_1)
                                * x2 + coef_sin_top_0);

    const soft_double bot = ((((     + coef_sin_bot_3)
                                * x2 + coef_sin_bot_2)
                                * x2 + coef_sin_bot_1)
                                * x2 + coef_sin_bot_0);

    return (x * top) / (bot * 7);
  }

  inline soft_double cos_pade(soft_double x)
  {
    // PadeApproximant[Cos[x] - 1, {x, 0, {8,6}}]
    // FullSimplify[%]

    //   (x^2 (-5491886400 + 346666320 x^2 - 7038360 x^4 + 45469 x^6))
    // / (24  (  457657200 +   9249240 x^2 +   86030 x^4 +   389 x^6))

    static const soft_double coef_cos_top_0(INT64_C(-5491886400));
    static const soft_double coef_cos_top_1(INT32_C(+346666320));
    static const soft_double coef_cos_top_2(INT32_C(-7038360));
    static const soft_double coef_cos_top_3(INT32_C(+45469));

    static const soft_double coef_cos_bot_0(UINT32_C(457657200));
    static const soft_double coef_cos_bot_1(UINT32_C(9249240));
    static const soft_double coef_cos_bot_2(UINT32_C(86030));
    static const soft_double coef_cos_bot_3(UINT32_C(389));

    const soft_double x2(x * x);

    const soft_double top = ((((     + coef_cos_top_3)
                                * x2 + coef_cos_top_2)
                                * x2 + coef_cos_top_1)
                                * x2 + coef_cos_top_0);

    const soft_double bot = ((((     + coef_cos_bot_3)
                                * x2 + coef_cos_bot_2)
                                * x2 + coef_cos_bot_1)
                                * x2 + coef_cos_bot_0);

    return 1U + ((x2 * top) / (bot * 24));
  }

  }

  inline soft_double sin(soft_double x)
  {
    soft_double s;

    if(x < 0)
    {
      s = -sin(-x);
    }
    else if(x > 0)
    {
      // Remove even multiples of pi.

      bool b_negate_sin = false;

      const std::uint32_t n_pi = (std::uint32_t) (x / soft_double::my_value_pi());

      if(n_pi != 0U)
      {
        x -= (soft_double::my_value_pi() * n_pi);

        if((n_pi % 2U) != 0)
        {
          b_negate_sin = (!b_negate_sin);
        }
      }

      // Check if the reduced argument is very close to pi/2.
      const soft_double delta_pi_half  = soft_double::my_value_pi_half() - x;
      const bool        b_near_pi_half = (fabs(delta_pi_half) < soft_double(UINT64_C(0x3FE0C152382D7366), detail::nothing()));

      if(b_near_pi_half)
      {
        // PadeApproximant[Hypergeometric0F1[1/2, -(dx^2)/4], {dx, 0, {6, 6}}]
        // FullSimplify[%]
        //   (39251520 - 18471600 dx^2 + 1075032 dx^4 - 14615 dx^6)
        // / (39251520 +  1154160 dx^2 +   16632 dx^4 +   127 dx^6)

        static const soft_double coef_top_0(INT32_C(+39251520));
        static const soft_double coef_top_1(INT32_C(-18471600));
        static const soft_double coef_top_2(INT32_C(+1075032));
        static const soft_double coef_top_3(INT32_C(-14615));

        static const soft_double coef_bot_0(UINT32_C(39251520));
        static const soft_double coef_bot_1(UINT32_C(1154160));
        static const soft_double coef_bot_2(UINT32_C(16632));
        static const soft_double coef_bot_3(UINT32_C(127));

        const soft_double x2(delta_pi_half * delta_pi_half);

        const soft_double top = ((((     + coef_top_3)
                                    * x2 + coef_top_2)
                                    * x2 + coef_top_1)
                                    * x2 + coef_top_0);

        const soft_double bot = ((((     + coef_bot_3)
                                    * x2 + coef_bot_2)
                                    * x2 + coef_bot_1)
                                    * x2 + coef_bot_0);

        s = top / bot;
      }
      else
      {
        // Reduce the argument to 0 <= x <= pi/2.
        if(x > soft_double::my_value_pi_half())
        {
          x = soft_double::my_value_pi() - x;
        }

        if(x > soft_double(UINT64_C(0x3FE0C152382D7366), detail::nothing()))
        {
          // x is larger than pi/6, scale by 9.
          x /= 9U;

          s = detail::sin_pade(x);

          s = (s * 3U) - (((s * s) * s) * 4U);
          s = (s * 3U) - (((s * s) * s) * 4U);
        }
        else if(x > soft_double(UINT64_C(0x3FC657184AE74487), detail::nothing()))
        {
          // x is larger than pi/18, scale by 3.
          x /= 3U;

          s = detail::sin_pade(x);

          s = (s * 3U) - (((s * s) * s) * 4U);
        }
        else
        {
          s = detail::sin_pade(x);
        }
      }

      if(b_negate_sin)
      {
        s = -s;
      }
    }
    else
    {
      s = 0;
    }

    return s;
  }

  inline soft_double cos(soft_double x)
  {
    soft_double c;

    if(x < 0)
    {
      c = cos(-x);
    }
    else if(x > 0)
    {
      // Remove even multiples of pi.

      bool b_negate_cos = false;

      const std::uint32_t n_pi = (std::uint32_t) (x / soft_double::my_value_pi());

      if(n_pi != 0U)
      {
        x -= (soft_double::my_value_pi() * n_pi);

        if((n_pi % 2U) != 0)
        {
          b_negate_cos = (!b_negate_cos);
        }
      }

      // Check if the reduced argument is very close to pi/2.
      const soft_double delta_pi_half  = soft_double::my_value_pi_half() - x;
      const bool        b_near_pi_half = (fabs(delta_pi_half) < soft_double(UINT64_C(0x3FE0C152382D7366), detail::nothing()));

      if(b_near_pi_half)
      {
        // PadeApproximant[Hypergeometric0F1[3/2, -(dx^2)/4], {dx, 0, {6, 6}}]
        // FullSimplify[%]
        //      (11511339840 - 1640635920 dx^2 + 52785432 dx^4 - 479249 dx^6)
        // / (7 ( 1644477120 +   39702960 dx^2 +   453960 dx^4 +   2623 dx^6))

        // This is the same approximation as the one found in detail::sin_pade().

        c = detail::sin_pade(delta_pi_half);
      }
      else
      {
        // Reduce the argument to 0 <= x <= pi/2.
        if(x > soft_double::my_value_pi_half())
        {
          x = soft_double::my_value_pi() - x;

          b_negate_cos = (!b_negate_cos);
        }

        if(x > soft_double(UINT64_C(0x3FE0C152382D7366), detail::nothing()))
        {
          // x is larger than pi/6, scale by 9.
          x /= 9U;

          c = detail::cos_pade(x);

          c = (((c * c) * c) * 4U) - (c * 3U);
          c = (((c * c) * c) * 4U) - (c * 3U);
        }
        else if(x > soft_double(UINT64_C(0x3FC657184AE74487), detail::nothing()))
        {
          // x is larger than pi/18, scale by 3.
          x /= 3U;

          c = detail::cos_pade(x);

          c = (((c * c) * c) * 4U) - (c * 3U);
        }
        else
        {
          c = detail::cos_pade(x);
        }
      }

      if(b_negate_cos)
      {
        c = -c;
      }
    }
    else
    {
      c = soft_double::my_value_one();
    }

    return c;
  }

  inline soft_double tan(const soft_double x)
  {
    return sin(x) / cos(x);
  }

  inline soft_double sinh(soft_double x)
  {
    const soft_double ep = exp(x);

    return (ep - (1 / ep)) / 2;
  }

  inline soft_double cosh(soft_double x)
  {
    const soft_double ep = exp(x);

    return (ep + (1 / ep)) / 2;
  }

  inline soft_double tanh(soft_double x)
  {
    const soft_double ep = exp(x);
    const soft_double em = 1 / ep;

    return (ep - em) / (ep + em);
  }

  using float64_t = soft_double;

  } } // namespace math::softfloat

  namespace std {

  // Specialization of numeric_limits for soft_double.
  template<>
  class numeric_limits<math::softfloat::soft_double>
  {
  public:
    static constexpr bool               is_specialized    = true;
    static constexpr float_denorm_style has_denorm        = denorm_present;
    static constexpr bool               has_denorm_loss   = false;
    static constexpr bool               has_infinity      = true;
    static constexpr bool               has_quiet_NaN     = true;
    static constexpr bool               has_signaling_NaN = false;
    static constexpr bool               is_bounded        = true;
    static constexpr bool               is_iec559         = false;
    static constexpr bool               is_integer        = false;
    static constexpr bool               is_exact          = false;
    static constexpr bool               is_signed         = true;
    static constexpr bool               is_modulo         = false;
    static constexpr bool               traps             = false;
    static constexpr bool               tinyness_before   = false;
    static constexpr float_round_style  round_style       = round_to_nearest;
    static constexpr int                radix             = 2;

    static constexpr int                digits            = 53;
    static constexpr int                digits10          = 15;
    static constexpr int                max_digits10      = 17;
    static constexpr int                max_exponent      = 1024;
    static constexpr int                max_exponent10    = 308;
    static constexpr int                min_exponent      = -1021;
    static constexpr int                min_exponent10    = -307;

    static constexpr math::softfloat::soft_double (min)        () noexcept { return math::softfloat::soft_double::my_value_min(); }
    static constexpr math::softfloat::soft_double (max)        () noexcept { return math::softfloat::soft_double::my_value_max(); }
    static constexpr math::softfloat::soft_double lowest       () noexcept { return math::softfloat::soft_double::my_value_lowest(); }
    static constexpr math::softfloat::soft_double epsilon      () noexcept { return math::softfloat::soft_double::my_value_epsilon(); }
    static constexpr math::softfloat::soft_double round_error  () noexcept { return math::softfloat::soft_double::my_value_round_error(); }
    static constexpr math::softfloat::soft_double denorm_min   () noexcept { return math::softfloat::soft_double::my_value_denorm_min(); }
    static constexpr math::softfloat::soft_double infinity     () noexcept { return math::softfloat::soft_double::my_value_infinity(); }
    static constexpr math::softfloat::soft_double quiet_NaN    () noexcept { return math::softfloat::soft_double::my_value_quiet_NaN(); }
    static constexpr math::softfloat::soft_double signaling_NaN() noexcept { return math::softfloat::soft_double::my_value_signaling_NaN(); }
  };

  }

#endif // SOFT_DOUBLE_2020_10_27_H_

/*----------------------------------------------------------------------------

This C header file is part of the SoftFloat IEEE Floating-Point Arithmetic
Package, Release 3e, by John R. Hauser.

Copyright 2011, 2012, 2013, 2014, 2015, 2016, 2017 The Regents of the
University of California.  All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

 1. Redistributions of source code must retain the above copyright notice,
    this list of conditions, and the following disclaimer.

 2. Redistributions in binary form must reproduce the above copyright notice,
    this list of conditions, and the following disclaimer in the documentation
    and/or other materials provided with the distribution.

 3. Neither the name of the University nor the names of its contributors may
    be used to endorse or promote products derived from this software without
    specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS "AS IS", AND ANY
EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE, ARE
DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE FOR ANY
DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

-----------------------------------------------------------------------------*/
