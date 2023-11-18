///////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2012 - 2023.                 //
//  Distributed under the Boost Software License,                //
//  Version 1.0. (See accompanying file LICENSE_1_0.txt          //
//  or copy at http://www.boost.org/LICENSE_1_0.txt)             //
///////////////////////////////////////////////////////////////////

// This work uses (significantly) modified parts of
// SoftFloat IEEE Floating-Point Arithmetic Package,
// Release 3e, by John R. Hauser.

// Full original SoftFloat 3e copyright information follows.
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

#ifndef SOFT_DOUBLE_2020_10_27_H
  #define SOFT_DOUBLE_2020_10_27_H

  //#define SOFT_DOUBLE_DISABLE_IOSTREAM

  #include <array>
  #include <cstddef>
  #include <cstdint>
  #if !defined(SOFT_DOUBLE_DISABLE_IOSTREAM)
  #include <iomanip>
  #endif
  #include <limits>
  #if !defined(SOFT_DOUBLE_DISABLE_IOSTREAM)
  #include <sstream>
  #endif
  #include <type_traits>

  #if (defined(__clang__) && (__clang_major__ <= 9))
  #define SOFT_DOUBLE_NUM_LIMITS_CLASS_TYPE struct // NOLINT(cppcoreguidelines-macro-usage)
  #else
  #define SOFT_DOUBLE_NUM_LIMITS_CLASS_TYPE class  // NOLINT(cppcoreguidelines-macro-usage)
  #endif

  #if defined(__clang__)
    #if(__cplusplus >= 201703L)
    #define SOFT_DOUBLE_NODISCARD [[nodiscard]] // NOLINT(cppcoreguidelines-macro-usage)
    #else
    #define SOFT_DOUBLE_NODISCARD // NOLINT(cppcoreguidelines-macro-usage)
    #endif
  #else
    #if (defined(_MSC_VER) && (_MSC_VER < 1920))
    #define SOFT_DOUBLE_NODISCARD
    #else
    #if (defined(__has_cpp_attribute) && __has_cpp_attribute(nodiscard))
    #define SOFT_DOUBLE_NODISCARD [[nodiscard]]
    #else
    #define SOFT_DOUBLE_NODISCARD
    #endif
    #endif
  #endif

  #if(__cplusplus >= 201703L)
  namespace math::softfloat {
  #else
  namespace math { namespace softfloat { // NOLINT(modernize-concat-nested-namespaces)
  #endif

  // Forward declaration the math::softfloat::soft_double class.
  class soft_double;

  #if(__cplusplus >= 201703L)
  } // namespace math::softfloat
  #else
  } // namespace softfloat
  } // namespace math
  #endif

  namespace std {

  // Forward declaration of the specialization of numeric_limits for soft_double.
  template<>
  SOFT_DOUBLE_NUM_LIMITS_CLASS_TYPE numeric_limits<::math::softfloat::soft_double>;

  } // namespace std

  #if(__cplusplus >= 201703L)
  namespace math::softfloat {
  #else
  namespace math { namespace softfloat { // NOLINT(modernize-concat-nested-namespaces)
  #endif

  namespace detail {

  template<typename T>
  constexpr auto my_max(T a, T b) noexcept -> T { return ((a > b) ? a : b); }

  template<const int BitCount,
           typename EnableType = void>
  struct uint_type_helper
  {
    static_assert(((BitCount >= static_cast<int>(INT8_C(8))) && (BitCount <= static_cast<int>(INT8_C(64)))),
                  "Error: uint_type_helper is not intended to be used for this BitCount");

    using exact_unsigned_type = std::uintmax_t;
  };

  template<const int BitCount> struct uint_type_helper<BitCount, typename std::enable_if<                                              (BitCount <= static_cast<int>(INT8_C( 8)))>::type> { using exact_unsigned_type = std::uint8_t;  };
  template<const int BitCount> struct uint_type_helper<BitCount, typename std::enable_if<(BitCount >= static_cast<int>(INT8_C( 9))) && (BitCount <= static_cast<int>(INT8_C(16)))>::type> { using exact_unsigned_type = std::uint16_t; };
  template<const int BitCount> struct uint_type_helper<BitCount, typename std::enable_if<(BitCount >= static_cast<int>(INT8_C(17))) && (BitCount <= static_cast<int>(INT8_C(32)))>::type> { using exact_unsigned_type = std::uint32_t; };
  template<const int BitCount> struct uint_type_helper<BitCount, typename std::enable_if<(BitCount >= static_cast<int>(INT8_C(33))) && (BitCount <= static_cast<int>(INT8_C(64)))>::type> { using exact_unsigned_type = std::uint64_t; };

  struct uint128_compound
  {
    explicit constexpr uint128_compound(std::uint64_t a = std::uint64_t(), // NOLINT(bugprone-easily-swappable-parameters)
                                        std::uint64_t b = std::uint64_t()) noexcept
      : v0(a),
        v1(b) { }

    std::uint64_t v0; // NOLINT(misc-non-private-member-variables-in-classes)
    std::uint64_t v1; // NOLINT(misc-non-private-member-variables-in-classes)
  };

  template<typename UnsignedIntegralType>
  constexpr auto negate(UnsignedIntegralType u) -> typename std::enable_if<   std::is_integral<UnsignedIntegralType>::value
                                                                           && std::is_unsigned<UnsignedIntegralType>::value, UnsignedIntegralType>::type
  {
    return
      static_cast<UnsignedIntegralType>
      (
          static_cast<UnsignedIntegralType>(~u)
        + static_cast<UnsignedIntegralType>(UINT8_C(1))
      );
  }

  template<typename SignedIntegralType>
  constexpr auto negate(SignedIntegralType n) -> typename std::enable_if<   std::is_integral<SignedIntegralType>::value
                                                                         && std::is_signed  <SignedIntegralType>::value, SignedIntegralType>::type
  {
    return static_cast<SignedIntegralType>(detail::negate(static_cast<unsigned long long>(n))); // NOLINT(google-runtime-int)
  }

  constexpr auto signF32UI(std::uint32_t a) -> bool          { return (static_cast<std::uint_fast8_t>(a >> static_cast<unsigned>(UINT8_C(31))) != static_cast<std::uint_fast8_t>(UINT8_C(0))); }
  constexpr auto expF32UI (std::uint32_t a) -> std::int16_t  { return static_cast<std::int16_t>(static_cast<std::int16_t>(a >> static_cast<unsigned>(UINT8_C(23))) & static_cast<std::int16_t>(INT16_C(0xFF))); } // NOLINT(hicpp-signed-bitwise)
  constexpr auto fracF32UI(std::uint32_t a) -> std::uint32_t { return static_cast<std::uint32_t>(a & static_cast<std::uint32_t>(UINT32_C(0x007FFFFF))); }

  constexpr auto signF64UI(std::uint64_t a) -> bool          { return (static_cast<std::uint_fast8_t>(a >> static_cast<unsigned>(UINT8_C(63))) != static_cast<std::uint_fast8_t>(UINT8_C(0))); }
  constexpr auto expF64UI (std::uint64_t a) -> std::int16_t  { return static_cast<std::int16_t>(static_cast<std::int16_t>(a >> static_cast<unsigned>(UINT8_C(52))) & static_cast<std::int16_t>(INT16_C(0x7FF))); } // NOLINT(hicpp-signed-bitwise)
  constexpr auto fracF64UI(std::uint64_t a) -> std::uint64_t { return static_cast<std::uint64_t>(a & static_cast<std::uint64_t>(UINT64_C(0x000FFFFFFFFFFFFF))); }

  template<typename IntegralTypeExp,
           typename IntegralTypeSig>
  constexpr auto packToF64UI(bool sign, IntegralTypeExp expA, IntegralTypeSig sig) -> std::uint64_t
  {
    using local_unsigned_sig_type =
      typename detail::uint_type_helper<std::numeric_limits<IntegralTypeSig>::digits>::exact_unsigned_type;

    using local_unsigned_exp_type =
      typename detail::uint_type_helper<std::numeric_limits<IntegralTypeExp>::digits>::exact_unsigned_type;

    return
      static_cast<std::uint64_t>
      (
          static_cast<std::uint64_t>(sign ? static_cast<std::uint64_t>(static_cast<std::uint64_t>(UINT8_C(1)) << static_cast<unsigned>(UINT8_C(63))) : static_cast<std::uint64_t>(UINT8_C(0)))
        + static_cast<std::uint64_t>(static_cast<std::uint64_t>(static_cast<local_unsigned_exp_type>(expA)) << static_cast<unsigned>(UINT8_C(52))) // NOLINT(clang-analyzer-core.UndefinedBinaryOperatorResult)
        + static_cast<std::uint64_t>(static_cast<local_unsigned_sig_type>(sig))
      );
  }

  template<typename IntegralTypeExp,
           typename IntegralTypeSig>
  constexpr auto packToF32UI(bool sign, IntegralTypeExp expA, IntegralTypeSig sig) -> std::uint32_t
  {
    return
      static_cast<std::uint32_t>
      (
          static_cast<std::uint32_t>(sign ? static_cast<std::uint32_t>(UINT8_C(1)) << static_cast<unsigned>(UINT8_C(31)) : static_cast<std::uint32_t>(UINT8_C(0)))
        + static_cast<std::uint32_t>(static_cast<std::uint32_t>(expA) << static_cast<unsigned>(UINT8_C(23)))
        + static_cast<std::uint32_t>(sig)
      );
  }

  constexpr auto softfloat_shortShiftRightJam64(std::uint64_t a, std::uint_fast16_t dist) -> std::uint64_t
  {
    return
      static_cast<std::uint64_t>
      (
          static_cast<std::uint64_t>(a >> dist)
        | static_cast<unsigned>
          (
            (static_cast<std::uint64_t>(a << static_cast<unsigned>(negate(dist) & static_cast<unsigned>(UINT8_C(63)))) != static_cast<std::uint64_t>(UINT8_C(0)))
              ? static_cast<unsigned>(UINT8_C(1))
              : static_cast<unsigned>(UINT8_C(0))
          )
      );
  }

  constexpr auto softfloat_shiftRightJam64(std::uint64_t a, std::uint_fast16_t dist) -> std::uint64_t
  {
    return
      static_cast<std::uint64_t>
      (
        (dist < static_cast<std::uint_fast16_t>(UINT8_C(63)))
          ? softfloat_shortShiftRightJam64(a, dist)
          : static_cast<std::uint64_t>
            (
              (a != static_cast<std::uint64_t>(UINT8_C(0)))
                ? static_cast<unsigned>(UINT8_C(1))
                : static_cast<unsigned>(UINT8_C(0))
            )
      );
  }

  constexpr auto softfloat_countLeadingZeros8_z_table(std::uint_fast8_t index) -> std::uint_fast8_t
  {
    // A constant table that translates an 8-bit unsigned integer (the array index)
    // into the number of leading 0 bits before the most-significant 1 of that
    // integer.  For integer zero (index 0), the corresponding table element is 8.
    return
      static_cast<std::uint_fast8_t>
      (
          ((index < static_cast<std::uint_fast8_t>(UINT8_C(0x1))) ? static_cast<std::uint_fast8_t>(UINT8_C(4))
        : ((index < static_cast<std::uint_fast8_t>(UINT8_C(0x2))) ? static_cast<std::uint_fast8_t>(UINT8_C(3))
        : ((index < static_cast<std::uint_fast8_t>(UINT8_C(0x4))) ? static_cast<std::uint_fast8_t>(UINT8_C(2))
        : ((index < static_cast<std::uint_fast8_t>(UINT8_C(0x8))) ? static_cast<std::uint_fast8_t>(UINT8_C(1))
                                                                  : static_cast<std::uint_fast8_t>(UINT8_C(0))))))
      );
  }

  constexpr auto softfloat_countLeadingZeros8(std::uint8_t a) -> std::uint_fast8_t
  {
    return
      static_cast<std::uint_fast8_t>
      (
        (a < static_cast<std::uint_fast8_t>(UINT8_C(0x10)))
          ? static_cast<std::uint_fast8_t>
            (
                static_cast<std::uint_fast8_t>(UINT8_C(4))
              + softfloat_countLeadingZeros8_z_table(static_cast<std::uint_fast8_t>(a & static_cast<std::uint8_t>(UINT8_C(0xF))))
            )
          :     softfloat_countLeadingZeros8_z_table(static_cast<std::uint_fast8_t>(a >> static_cast<unsigned>(UINT8_C(4))))
      );
  }

  constexpr auto softfloat_countLeadingZeros16(std::uint16_t a) -> std::uint_fast8_t
  {
    return
      static_cast<std::uint_fast8_t>
      (
        (a < static_cast<std::uint16_t>(UINT16_C(0x100)))
          ? static_cast<std::uint_fast8_t>
            (
                static_cast<std::uint_fast8_t>(UINT8_C(8))
              + softfloat_countLeadingZeros8(static_cast<std::uint8_t>(a))
            )
          :     softfloat_countLeadingZeros8(static_cast<std::uint8_t>(a >> static_cast<unsigned>(UINT8_C(8))))
      );
  }

  constexpr auto softfloat_countLeadingZeros32(std::uint32_t a) -> std::uint_fast8_t
  {
    return
      static_cast<std::uint_fast8_t>
      (
        (a < static_cast<std::uint32_t>(UINT32_C(0x10000)))
          ? static_cast<std::uint_fast8_t>
            (
                static_cast<std::uint_fast8_t>(UINT8_C(16))
              + softfloat_countLeadingZeros16(static_cast<std::uint16_t>(a))
            )
          :     softfloat_countLeadingZeros16(static_cast<std::uint16_t>(a >> static_cast<unsigned>(UINT8_C(16))))
      );
  }

  constexpr auto softfloat_countLeadingZeros64(std::uint64_t a) -> std::uint_fast8_t
  {
    return
      static_cast<std::uint_fast8_t>
      (
        (a < static_cast<std::uint64_t>(UINT64_C(0x100000000)))
          ? static_cast<std::uint_fast8_t>
            (
                static_cast<unsigned>(UINT8_C(32))
              + softfloat_countLeadingZeros32(static_cast<std::uint32_t>(a))
            )
          :     softfloat_countLeadingZeros32(static_cast<std::uint32_t>(a >> static_cast<unsigned>(UINT8_C(32))))
      );
  }

  constexpr auto softfloat_approxRecip32_1(std::uint32_t a) -> std::uint32_t
  {
    // Returns an approximation to the reciprocal of the number represented by a,
    // where a is interpreted as an unsigned fixed-point number with one integer
    // bit and 31 fraction bits.
    return
      static_cast<std::uint32_t>
      (
          static_cast<std::uint64_t>(UINT64_C(0x7FFFFFFFFFFFFFFF))
        / a
      );
  }

  constexpr auto softfloat_shiftRightJam64Extra(std::uint64_t a,
                                                std::uint64_t extra,
                                                std::uint32_t dist) -> uint128_compound
  {
    // Shifts the 128 bits formed by concatenating a and extra right by 64
    // _plus_ the number of bits given in dist, which must not be zero. This
    // shifted value is at most 64 nonzero bits and is returned in the v field
    // of the struct uint64_extra result.
    return
      uint128_compound
      {
        static_cast<std::uint64_t>
        (
          (dist < static_cast<std::uint32_t>(UINT8_C(64)))
            ? static_cast<std::uint64_t>
              (  static_cast<std::uint64_t>
                (
                  a << static_cast<unsigned>
                       (
                         static_cast<unsigned>(negate(dist)) & static_cast<std::uint32_t>(UINT8_C(63))
                       )
                )
              | static_cast<unsigned>
                (
                  (extra != static_cast<std::uint64_t>(UINT8_C(0)))
                    ? static_cast<unsigned>(UINT8_C(1))
                    : static_cast<unsigned>(UINT8_C(0))
                )
              )
            :
              static_cast<std::uint64_t>
              (
                (dist == static_cast<std::uint32_t>(UINT8_C(64)))
                  ? a
                  : static_cast<std::uint64_t>
                    (
                      ((a != static_cast<std::uint64_t>(UINT8_C(0))) || (extra != static_cast<std::uint64_t>(UINT8_C(0))))
                        ? static_cast<unsigned>(UINT8_C(1))
                        : static_cast<unsigned>(UINT8_C(0))
                    )
              )
        ),
        static_cast<std::uint64_t>
        (
          (dist < static_cast<std::uint32_t>(UINT8_C(64)))
            ? static_cast<std::uint64_t>(a >> static_cast<unsigned>(dist))
            : static_cast<std::uint64_t>(UINT8_C(0))
        )
      };
  }

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

    explicit constexpr uz_type(float_type    f) noexcept : my_f(f) { }
    explicit constexpr uz_type(unsigned_type u) noexcept : my_u(u) { }
  };

  struct nothing { };

  } // namespace detail

  constexpr auto operator+(const soft_double& a, const soft_double& b) -> soft_double;
  constexpr auto operator-(const soft_double& a, const soft_double& b) -> soft_double;
  constexpr auto operator*(const soft_double& a, const soft_double& b) -> soft_double;
  constexpr auto operator/(const soft_double& a, const soft_double& b) -> soft_double;

  template<typename UnsignedIntegralType> constexpr auto operator+(const soft_double& u, UnsignedIntegralType n) -> typename std::enable_if<std::is_integral<UnsignedIntegralType>::value && std::is_unsigned<UnsignedIntegralType>::value, soft_double>::type;
  template<typename UnsignedIntegralType> constexpr auto operator-(const soft_double& u, UnsignedIntegralType n) -> typename std::enable_if<std::is_integral<UnsignedIntegralType>::value && std::is_unsigned<UnsignedIntegralType>::value, soft_double>::type;
  template<typename UnsignedIntegralType> constexpr auto operator*(const soft_double& u, UnsignedIntegralType n) -> typename std::enable_if<std::is_integral<UnsignedIntegralType>::value && std::is_unsigned<UnsignedIntegralType>::value, soft_double>::type;
  template<typename UnsignedIntegralType> constexpr auto operator/(const soft_double& u, UnsignedIntegralType n) -> typename std::enable_if<std::is_integral<UnsignedIntegralType>::value && std::is_unsigned<UnsignedIntegralType>::value, soft_double>::type;

  template<typename UnsignedIntegralType> constexpr auto operator+(UnsignedIntegralType n, const soft_double& u) -> typename std::enable_if<std::is_integral<UnsignedIntegralType>::value && std::is_unsigned<UnsignedIntegralType>::value, soft_double>::type;
  template<typename UnsignedIntegralType> constexpr auto operator-(UnsignedIntegralType n, const soft_double& u) -> typename std::enable_if<std::is_integral<UnsignedIntegralType>::value && std::is_unsigned<UnsignedIntegralType>::value, soft_double>::type;
  template<typename UnsignedIntegralType> constexpr auto operator*(UnsignedIntegralType n, const soft_double& u) -> typename std::enable_if<std::is_integral<UnsignedIntegralType>::value && std::is_unsigned<UnsignedIntegralType>::value, soft_double>::type;
  template<typename UnsignedIntegralType> constexpr auto operator/(UnsignedIntegralType n, const soft_double& u) -> typename std::enable_if<std::is_integral<UnsignedIntegralType>::value && std::is_unsigned<UnsignedIntegralType>::value, soft_double>::type;

  template<typename SignedIntegralType> constexpr auto operator+(const soft_double& u, SignedIntegralType n) -> typename std::enable_if<std::is_integral<SignedIntegralType>::value && std::is_signed<SignedIntegralType>::value, soft_double>::type;
  template<typename SignedIntegralType> constexpr auto operator-(const soft_double& u, SignedIntegralType n) -> typename std::enable_if<std::is_integral<SignedIntegralType>::value && std::is_signed<SignedIntegralType>::value, soft_double>::type;
  template<typename SignedIntegralType> constexpr auto operator*(const soft_double& u, SignedIntegralType n) -> typename std::enable_if<std::is_integral<SignedIntegralType>::value && std::is_signed<SignedIntegralType>::value, soft_double>::type;
  template<typename SignedIntegralType> constexpr auto operator/(const soft_double& u, SignedIntegralType n) -> typename std::enable_if<std::is_integral<SignedIntegralType>::value && std::is_signed<SignedIntegralType>::value, soft_double>::type;

  template<typename SignedIntegralType> constexpr auto operator+(SignedIntegralType n, const soft_double& u) -> typename std::enable_if<std::is_integral<SignedIntegralType>::value && std::is_signed<SignedIntegralType>::value, soft_double>::type;
  template<typename SignedIntegralType> constexpr auto operator-(SignedIntegralType n, const soft_double& u) -> typename std::enable_if<std::is_integral<SignedIntegralType>::value && std::is_signed<SignedIntegralType>::value, soft_double>::type;
  template<typename SignedIntegralType> constexpr auto operator*(SignedIntegralType n, const soft_double& u) -> typename std::enable_if<std::is_integral<SignedIntegralType>::value && std::is_signed<SignedIntegralType>::value, soft_double>::type;
  template<typename SignedIntegralType> constexpr auto operator/(SignedIntegralType n, const soft_double& u) -> typename std::enable_if<std::is_integral<SignedIntegralType>::value && std::is_signed<SignedIntegralType>::value, soft_double>::type;

  constexpr auto operator+(const soft_double& u, float f) -> soft_double;
  constexpr auto operator-(const soft_double& u, float f) -> soft_double;
  constexpr auto operator*(const soft_double& u, float f) -> soft_double;
  constexpr auto operator/(const soft_double& u, float f) -> soft_double;

  constexpr auto operator+(float f, const soft_double& u) -> soft_double;
  constexpr auto operator-(float f, const soft_double& u) -> soft_double;
  constexpr auto operator*(float f, const soft_double& u) -> soft_double;
  constexpr auto operator/(float f, const soft_double& u) -> soft_double;

  constexpr auto operator+(const soft_double& u, double f) -> soft_double;
  constexpr auto operator-(const soft_double& u, double f) -> soft_double;
  constexpr auto operator*(const soft_double& u, double f) -> soft_double;
  constexpr auto operator/(const soft_double& u, double f) -> soft_double;

  constexpr auto operator+(double f, const soft_double& u) -> soft_double;
  constexpr auto operator-(double f, const soft_double& u) -> soft_double;
  constexpr auto operator*(double f, const soft_double& u) -> soft_double;
  constexpr auto operator/(double f, const soft_double& u) -> soft_double;

  constexpr auto operator+(const soft_double& u, long double f) -> soft_double;
  constexpr auto operator-(const soft_double& u, long double f) -> soft_double;
  constexpr auto operator*(const soft_double& u, long double f) -> soft_double;
  constexpr auto operator/(const soft_double& u, long double f) -> soft_double;

  constexpr auto operator+(long double f, const soft_double& u) -> soft_double;
  constexpr auto operator-(long double f, const soft_double& u) -> soft_double;
  constexpr auto operator*(long double f, const soft_double& u) -> soft_double;
  constexpr auto operator/(long double f, const soft_double& u) -> soft_double;

  constexpr auto operator< (const soft_double& a, const soft_double& b) -> bool;
  constexpr auto operator<=(const soft_double& a, const soft_double& b) -> bool;
  constexpr auto operator==(const soft_double& a, const soft_double& b) -> bool;
  constexpr auto operator!=(const soft_double& a, const soft_double& b) -> bool;
  constexpr auto operator>=(const soft_double& a, const soft_double& b) -> bool;
  constexpr auto operator> (const soft_double& a, const soft_double& b) -> bool;

  template<typename UnsignedIntegralType> constexpr auto operator< (const soft_double& a, UnsignedIntegralType u) -> typename std::enable_if<std::is_integral<UnsignedIntegralType>::value && std::is_unsigned<UnsignedIntegralType>::value, bool>::type;
  template<typename UnsignedIntegralType> constexpr auto operator<=(const soft_double& a, UnsignedIntegralType u) -> typename std::enable_if<std::is_integral<UnsignedIntegralType>::value && std::is_unsigned<UnsignedIntegralType>::value, bool>::type;
  template<typename UnsignedIntegralType> constexpr auto operator==(const soft_double& a, UnsignedIntegralType u) -> typename std::enable_if<std::is_integral<UnsignedIntegralType>::value && std::is_unsigned<UnsignedIntegralType>::value, bool>::type;
  template<typename UnsignedIntegralType> constexpr auto operator!=(const soft_double& a, UnsignedIntegralType u) -> typename std::enable_if<std::is_integral<UnsignedIntegralType>::value && std::is_unsigned<UnsignedIntegralType>::value, bool>::type;
  template<typename UnsignedIntegralType> constexpr auto operator>=(const soft_double& a, UnsignedIntegralType u) -> typename std::enable_if<std::is_integral<UnsignedIntegralType>::value && std::is_unsigned<UnsignedIntegralType>::value, bool>::type;
  template<typename UnsignedIntegralType> constexpr auto operator> (const soft_double& a, UnsignedIntegralType u) -> typename std::enable_if<std::is_integral<UnsignedIntegralType>::value && std::is_unsigned<UnsignedIntegralType>::value, bool>::type;

  template<typename UnsignedIntegralType> constexpr auto operator< (UnsignedIntegralType u, const soft_double& a) -> typename std::enable_if<std::is_integral<UnsignedIntegralType>::value && std::is_unsigned<UnsignedIntegralType>::value, bool>::type;
  template<typename UnsignedIntegralType> constexpr auto operator<=(UnsignedIntegralType u, const soft_double& a) -> typename std::enable_if<std::is_integral<UnsignedIntegralType>::value && std::is_unsigned<UnsignedIntegralType>::value, bool>::type;
  template<typename UnsignedIntegralType> constexpr auto operator==(UnsignedIntegralType u, const soft_double& a) -> typename std::enable_if<std::is_integral<UnsignedIntegralType>::value && std::is_unsigned<UnsignedIntegralType>::value, bool>::type;
  template<typename UnsignedIntegralType> constexpr auto operator!=(UnsignedIntegralType u, const soft_double& a) -> typename std::enable_if<std::is_integral<UnsignedIntegralType>::value && std::is_unsigned<UnsignedIntegralType>::value, bool>::type;
  template<typename UnsignedIntegralType> constexpr auto operator>=(UnsignedIntegralType u, const soft_double& a) -> typename std::enable_if<std::is_integral<UnsignedIntegralType>::value && std::is_unsigned<UnsignedIntegralType>::value, bool>::type;
  template<typename UnsignedIntegralType> constexpr auto operator> (UnsignedIntegralType u, const soft_double& a) -> typename std::enable_if<std::is_integral<UnsignedIntegralType>::value && std::is_unsigned<UnsignedIntegralType>::value, bool>::type;

  template<typename SignedIntegralType> constexpr auto operator< (const soft_double& a, SignedIntegralType n) -> typename std::enable_if<std::is_integral<SignedIntegralType>::value && std::is_signed<SignedIntegralType>::value, bool>::type;
  template<typename SignedIntegralType> constexpr auto operator<=(const soft_double& a, SignedIntegralType n) -> typename std::enable_if<std::is_integral<SignedIntegralType>::value && std::is_signed<SignedIntegralType>::value, bool>::type;
  template<typename SignedIntegralType> constexpr auto operator==(const soft_double& a, SignedIntegralType n) -> typename std::enable_if<std::is_integral<SignedIntegralType>::value && std::is_signed<SignedIntegralType>::value, bool>::type;
  template<typename SignedIntegralType> constexpr auto operator!=(const soft_double& a, SignedIntegralType n) -> typename std::enable_if<std::is_integral<SignedIntegralType>::value && std::is_signed<SignedIntegralType>::value, bool>::type;
  template<typename SignedIntegralType> constexpr auto operator>=(const soft_double& a, SignedIntegralType n) -> typename std::enable_if<std::is_integral<SignedIntegralType>::value && std::is_signed<SignedIntegralType>::value, bool>::type;
  template<typename SignedIntegralType> constexpr auto operator> (const soft_double& a, SignedIntegralType n) -> typename std::enable_if<std::is_integral<SignedIntegralType>::value && std::is_signed<SignedIntegralType>::value, bool>::type;

  template<typename SignedIntegralType> constexpr auto operator< (SignedIntegralType n, const soft_double& a) -> typename std::enable_if<std::is_integral<SignedIntegralType>::value && std::is_signed<SignedIntegralType>::value, bool>::type;
  template<typename SignedIntegralType> constexpr auto operator<=(SignedIntegralType n, const soft_double& a) -> typename std::enable_if<std::is_integral<SignedIntegralType>::value && std::is_signed<SignedIntegralType>::value, bool>::type;
  template<typename SignedIntegralType> constexpr auto operator==(SignedIntegralType n, const soft_double& a) -> typename std::enable_if<std::is_integral<SignedIntegralType>::value && std::is_signed<SignedIntegralType>::value, bool>::type;
  template<typename SignedIntegralType> constexpr auto operator!=(SignedIntegralType n, const soft_double& a) -> typename std::enable_if<std::is_integral<SignedIntegralType>::value && std::is_signed<SignedIntegralType>::value, bool>::type;
  template<typename SignedIntegralType> constexpr auto operator>=(SignedIntegralType n, const soft_double& a) -> typename std::enable_if<std::is_integral<SignedIntegralType>::value && std::is_signed<SignedIntegralType>::value, bool>::type;
  template<typename SignedIntegralType> constexpr auto operator> (SignedIntegralType n, const soft_double& a) -> typename std::enable_if<std::is_integral<SignedIntegralType>::value && std::is_signed<SignedIntegralType>::value, bool>::type;

  constexpr auto operator< (const soft_double& a, float f) -> bool;
  constexpr auto operator<=(const soft_double& a, float f) -> bool;
  constexpr auto operator==(const soft_double& a, float f) -> bool;
  constexpr auto operator!=(const soft_double& a, float f) -> bool;
  constexpr auto operator>=(const soft_double& a, float f) -> bool;
  constexpr auto operator> (const soft_double& a, float f) -> bool;

  constexpr auto operator< (float f, const soft_double& a) -> bool;
  constexpr auto operator<=(float f, const soft_double& a) -> bool;
  constexpr auto operator==(float f, const soft_double& a) -> bool;
  constexpr auto operator!=(float f, const soft_double& a) -> bool;
  constexpr auto operator>=(float f, const soft_double& a) -> bool;
  constexpr auto operator> (float f, const soft_double& a) -> bool;

  constexpr auto operator< (const soft_double& a, double f) -> bool;
  constexpr auto operator<=(const soft_double& a, double f) -> bool;
  constexpr auto operator==(const soft_double& a, double f) -> bool;
  constexpr auto operator!=(const soft_double& a, double f) -> bool;
  constexpr auto operator>=(const soft_double& a, double f) -> bool;
  constexpr auto operator> (const soft_double& a, double f) -> bool;

  constexpr auto operator< (double f, const soft_double& a) -> bool;
  constexpr auto operator<=(double f, const soft_double& a) -> bool;
  constexpr auto operator==(double f, const soft_double& a) -> bool;
  constexpr auto operator!=(double f, const soft_double& a) -> bool;
  constexpr auto operator>=(double f, const soft_double& a) -> bool;
  constexpr auto operator> (double f, const soft_double& a) -> bool;

  constexpr auto operator< (const soft_double& a, long double f) -> bool;
  constexpr auto operator<=(const soft_double& a, long double f) -> bool;
  constexpr auto operator==(const soft_double& a, long double f) -> bool;
  constexpr auto operator!=(const soft_double& a, long double f) -> bool;
  constexpr auto operator>=(const soft_double& a, long double f) -> bool;
  constexpr auto operator> (const soft_double& a, long double f) -> bool;

  constexpr auto operator< (long double f, const soft_double& a) -> bool;
  constexpr auto operator<=(long double f, const soft_double& a) -> bool;
  constexpr auto operator==(long double f, const soft_double& a) -> bool;
  constexpr auto operator!=(long double f, const soft_double& a) -> bool;
  constexpr auto operator>=(long double f, const soft_double& a) -> bool;
  constexpr auto operator> (long double f, const soft_double& a) -> bool;

  #if !defined(SOFT_DOUBLE_DISABLE_IOSTREAM)
  template<typename char_type, typename traits_type> auto operator<<(std::basic_ostream<char_type, traits_type>& os, const soft_double& f) -> std::basic_ostream<char_type, traits_type>&;
  template<typename char_type, typename traits_type> auto operator>>(std::basic_istream<char_type, traits_type>& is,       soft_double& f) -> std::basic_istream<char_type, traits_type>&;
  #endif // !WIDE_DECIMAL_DISABLE_IOSTREAM

  constexpr auto (isnan)   (soft_double x) -> bool;
  constexpr auto (isinf)   (soft_double x) -> bool;
  constexpr auto (isfinite)(soft_double x) -> bool;
  constexpr auto  abs      (soft_double x) -> soft_double;
  constexpr auto  fabs     (soft_double x) -> soft_double;
  constexpr auto  fmod     (soft_double v1, soft_double v2) -> soft_double;
  constexpr auto  frexp    (soft_double x, int* expptr) -> soft_double;
  constexpr auto  ldexp    (soft_double x, int expval) -> soft_double;
  constexpr auto  floor    (soft_double x) -> soft_double;
  constexpr auto  ceil     (soft_double x) -> soft_double;
  constexpr auto  sqrt     (soft_double x) -> soft_double;
  constexpr auto  exp      (soft_double x) -> soft_double;
  constexpr auto  log      (soft_double x) -> soft_double;
  constexpr auto  pow      (soft_double x, soft_double a) -> soft_double;
  constexpr auto  sin      (soft_double x) -> soft_double;
  constexpr auto  cos      (soft_double x) -> soft_double;
  constexpr auto  tan      (soft_double x) -> soft_double;
  constexpr auto  sinh     (soft_double x) -> soft_double;
  constexpr auto  cosh     (soft_double x) -> soft_double;
  constexpr auto  tanh     (soft_double x) -> soft_double;

  template<typename UnsignedIntegralType,
           typename std::enable_if<(   std::is_integral<UnsignedIntegralType>::value
                                    && std::is_unsigned<UnsignedIntegralType>::value)>::type const* = nullptr>
  constexpr auto pow(soft_double x, UnsignedIntegralType u) -> soft_double;

  template<typename SignedIntegralType,
           typename std::enable_if<(   std::is_integral<SignedIntegralType>::value
                                    && std::is_signed  <SignedIntegralType>::value)>::type const* = nullptr>
  constexpr auto pow(soft_double x, SignedIntegralType n) -> soft_double;

  class soft_double final
  {
  public:
    static_assert(sizeof(float) == static_cast<std::size_t>(UINT8_C(4)),
                  "Error: This template is designed for built-in float having 4 bytes");

    using representation_type = std::uint64_t;

    constexpr soft_double() noexcept = default;

    template<typename UnsignedIntegralType,
             typename std::enable_if<(   std::is_integral<UnsignedIntegralType>::value
                                      && std::is_unsigned<UnsignedIntegralType>::value
                                      && (sizeof(UnsignedIntegralType) <= sizeof(std::uint32_t)))>::type const* = nullptr>
    constexpr soft_double(UnsignedIntegralType u) noexcept : my_value(my_ui32_to_f64(static_cast<std::uint32_t>(u))) { } // NOLINT(google-explicit-constructor,hicpp-explicit-conversions)

    template<typename UnsignedIntegralType,
             typename std::enable_if<(   std::is_integral<UnsignedIntegralType>::value
                                      && std::is_unsigned<UnsignedIntegralType>::value
                                      && (!(sizeof(UnsignedIntegralType) <= sizeof(std::uint32_t))))>::type const* = nullptr>
    constexpr soft_double(UnsignedIntegralType u) noexcept : my_value(my_ui64_to_f64(static_cast<std::uint64_t>(u))) { } // NOLINT(google-explicit-constructor,hicpp-explicit-conversions)

    template<typename SignedIntegralType,
             typename std::enable_if<(   std::is_integral<SignedIntegralType>::value
                                      && std::is_signed  <SignedIntegralType>::value
                                      && (sizeof(SignedIntegralType) <= sizeof(int32_t)))>::type const* = nullptr>
    constexpr soft_double(SignedIntegralType n) noexcept : my_value(my__i32_to_f64(static_cast<std::int32_t>(n))) { } // NOLINT(google-explicit-constructor,hicpp-explicit-conversions)

    template<typename SignedIntegralType,
             typename std::enable_if<(   std::is_integral<SignedIntegralType>::value
                                      && std::is_signed  <SignedIntegralType>::value
                                      && (!(sizeof(SignedIntegralType) <= sizeof(int32_t))))>::type const* = nullptr>
    constexpr soft_double(SignedIntegralType n) noexcept : my_value(my__i64_to_f64(static_cast<std::int64_t>(n))) { } // NOLINT(google-explicit-constructor,hicpp-explicit-conversions)

    constexpr soft_double(float f) noexcept // NOLINT(google-explicit-constructor,hicpp-explicit-conversions)
      : my_value
        (
          ((detail::expF32UI(detail::uz_type<float>(f).my_u) == static_cast<std::int16_t>(INT8_C(0))) && (detail::fracF32UI(detail::uz_type<float>(f).my_u) == static_cast<std::uint32_t>(UINT8_C(0)))) // NOLINT(cppcoreguidelines-pro-type-union-access)
            ? detail::packToF64UI
              (
                detail::signF32UI(detail::uz_type<float>(f).my_u), // NOLINT(cppcoreguidelines-pro-type-union-access)
                static_cast<int>(INT8_C(0)),
                static_cast<int>(INT8_C(0))
              )
            : detail::packToF64UI
              (
                detail::signF32UI(detail::uz_type<float>(f).my_u), // NOLINT(cppcoreguidelines-pro-type-union-access)
                static_cast<std::int32_t>
                (
                    static_cast<std::int32_t>(detail::expF32UI(detail::uz_type<float>(f).my_u)) // NOLINT(cppcoreguidelines-pro-type-union-access)
                  + static_cast<std::int32_t>(INT16_C(0x380))
                ),
                static_cast<std::uint64_t>
                (
                  static_cast<std::uint64_t>
                  (
                    detail::fracF32UI(detail::uz_type<float>(f).my_u) // NOLINT(cppcoreguidelines-pro-type-union-access)
                  ) << static_cast<unsigned>(UINT8_C(29))
                )
              )
        ) { }

    constexpr soft_double(double d) noexcept          // NOLINT(google-explicit-constructor,hicpp-explicit-conversions)
      : my_value(detail::uz_type<double>(d).my_u) { } // NOLINT(cppcoreguidelines-pro-type-union-access)

    constexpr soft_double(long double ld) noexcept                          // NOLINT(google-explicit-constructor,hicpp-explicit-conversions)
      : my_value(detail::uz_type<double>(static_cast<double>(ld)).my_u) { } // NOLINT(cppcoreguidelines-pro-type-union-access)

    constexpr soft_double(const soft_double& other) noexcept : my_value(other.my_value) { }; // NOLINT(hicpp-use-equals-default,modernize-use-equals-default)

    constexpr soft_double(soft_double&& other) noexcept
      : my_value(other.my_value) { }

    explicit constexpr soft_double(std::uint64_t n, detail::nothing&&) noexcept // NOLINT(hicpp-named-parameter,readability-named-parameter)
      : my_value(static_cast<std::uint64_t>(n)) { }

    constexpr auto operator=(const soft_double& other) noexcept -> soft_double&
    {
      if(this != &other)
      {
        my_value = other.my_value;
      }

      return *this;
    }

    constexpr auto operator=(soft_double&& other) noexcept -> soft_double&
    {
      my_value = other.my_value;

      return *this;
    }

    ~soft_double() = default;

    SOFT_DOUBLE_NODISCARD constexpr auto  representation() const -> representation_type { return my_value; }
    SOFT_DOUBLE_NODISCARD constexpr auto crepresentation() const -> representation_type { return my_value; }

    static constexpr auto get_rep(const soft_double& a) -> representation_type { return a.crepresentation(); }

    constexpr operator   signed char     () const { return static_cast<signed char>     (f64_to__i32(my_value)); } // NOLINT(google-explicit-constructor,hicpp-explicit-conversions)
    constexpr operator   signed short    () const { return static_cast<signed short>    (f64_to__i32(my_value)); } // NOLINT(google-explicit-constructor,hicpp-explicit-conversions,google-runtime-int)
    constexpr operator   signed int      () const { return static_cast<signed int>      (f64_to__i32(my_value)); } // NOLINT(google-explicit-constructor,hicpp-explicit-conversions)
    constexpr operator   signed long     () const { return static_cast<signed long>     (f64_to__i64(my_value)); } // NOLINT(google-explicit-constructor,hicpp-explicit-conversions,google-runtime-int)
    constexpr operator   signed long long() const { return static_cast<signed long long>(f64_to__i64(my_value)); } // NOLINT(google-explicit-constructor,hicpp-explicit-conversions,google-runtime-int)

    constexpr operator unsigned char     () const { return static_cast<unsigned char>     (f64_to_ui32(my_value)); } // NOLINT(google-explicit-constructor,hicpp-explicit-conversions)
    constexpr operator unsigned short    () const { return static_cast<unsigned short>    (f64_to_ui32(my_value)); } // NOLINT(google-explicit-constructor,hicpp-explicit-conversions,google-runtime-int)
    constexpr operator unsigned int      () const { return static_cast<unsigned int>      (f64_to_ui32(my_value)); } // NOLINT(google-explicit-constructor,hicpp-explicit-conversions)
    constexpr operator unsigned long     () const { return static_cast<unsigned long>     (f64_to_ui64(my_value)); } // NOLINT(google-explicit-constructor,hicpp-explicit-conversions,google-runtime-int)
    constexpr operator unsigned long long() const { return static_cast<unsigned long long>(f64_to_ui64(my_value)); } // NOLINT(google-explicit-constructor,hicpp-explicit-conversions,google-runtime-int)

  private:
    template<typename FloatingPointType>
    SOFT_DOUBLE_NODISCARD constexpr auto to_float() const -> typename std::enable_if<(   (sizeof(FloatingPointType) == 4)
                                                                                      && std::numeric_limits<FloatingPointType>::is_iec559), FloatingPointType>::type
    {
      return f64_to_f32(my_value);
    }

    template<typename FloatingPointType>
    SOFT_DOUBLE_NODISCARD constexpr auto to_float() const -> typename std::enable_if<(   (sizeof(FloatingPointType) == 8)
                                                                                      && std::numeric_limits<FloatingPointType>::is_iec559), FloatingPointType>::type
    {
      return static_cast<FloatingPointType>(*static_cast<const volatile FloatingPointType*>(static_cast<const volatile void*>(this)));
    }

  public:
    constexpr operator float      () const noexcept { return to_float<float>(); }                            // NOLINT(google-explicit-constructor,hicpp-explicit-conversions)
    constexpr operator double     () const noexcept { return to_float<double>(); }                           // NOLINT(google-explicit-constructor,hicpp-explicit-conversions)
    constexpr operator long double() const noexcept { return static_cast<long double>(to_float<double>()); } // NOLINT(google-explicit-constructor,hicpp-explicit-conversions)

    constexpr auto operator+=(const soft_double& other) -> soft_double& { my_value = f64_add(my_value, other.my_value); return *this; }
    constexpr auto operator-=(const soft_double& other) -> soft_double& { my_value = f64_sub(my_value, other.my_value); return *this; }
    constexpr auto operator*=(const soft_double& other) -> soft_double& { my_value = f64_mul(my_value, other.my_value); return *this; }
    constexpr auto operator/=(const soft_double& other) -> soft_double& { my_value = f64_div(my_value, other.my_value); return *this; }

    // Operators pre-increment and pre-decrement.
    constexpr auto operator++() -> soft_double& { return *this += my_value_one(); }
    constexpr auto operator--() -> soft_double& { return *this -= my_value_one(); }

    // Operators post-increment and post-decrement.
    constexpr auto operator++(int) -> soft_double { const soft_double w(*this); static_cast<void>(++(*this)); return w; } // NOLINT(performance-no-automatic-move)
    constexpr auto operator--(int) -> soft_double { const soft_double w(*this); static_cast<void>(--(*this)); return w; } // NOLINT(performance-no-automatic-move)

    constexpr auto operator+() const -> const soft_double& { return *this; }
    constexpr auto operator-() const ->       soft_double  { return soft_double { my_value ^ static_cast<std::uint64_t>(static_cast<std::uint64_t>(UINT8_C(1)) << static_cast<unsigned>(UINT8_C(63))), detail::nothing{} }; }

    static constexpr auto my_value_zero   () -> soft_double { return soft_double { static_cast<std::uint64_t>(UINT64_C(0)),                   detail::nothing{} }; }
    static constexpr auto my_value_one    () -> soft_double { return soft_double { static_cast<std::uint64_t>(UINT64_C(0x3FF0000000000000)),  detail::nothing{} }; }
    static constexpr auto my_value_two    () -> soft_double { return soft_double { static_cast<std::uint64_t>(UINT64_C(0x4000000000000000)),  detail::nothing{} }; }
    static constexpr auto my_value_half   () -> soft_double { return soft_double { static_cast<std::uint64_t>(UINT64_C(0x3FE0000000000000)),  detail::nothing{} }; }
    static constexpr auto my_value_pi     () -> soft_double { return soft_double { static_cast<std::uint64_t>(UINT64_C(4614256656552045848)), detail::nothing{} }; }
    static constexpr auto my_value_pi_half() -> soft_double { return soft_double { static_cast<std::uint64_t>(UINT64_C(0x3FF921FB54442D18)),  detail::nothing{} }; }
    static constexpr auto my_value_ln2    () -> soft_double { return soft_double { static_cast<std::uint64_t>(UINT64_C(4604418534313441775)), detail::nothing{} }; }

    static constexpr auto my_value_min()           -> soft_double { return soft_double { static_cast<std::uint64_t>(UINT64_C(4503599627370496)),    detail::nothing{} }; }
    static constexpr auto my_value_max()           -> soft_double { return soft_double { static_cast<std::uint64_t>(UINT64_C(9218868437227405311)), detail::nothing{} }; }
    static constexpr auto my_value_lowest()        -> soft_double { return soft_double { static_cast<std::uint64_t>(UINT64_C(18442240474082181119)),detail::nothing{} }; }
    static constexpr auto my_value_epsilon()       -> soft_double { return soft_double { static_cast<std::uint64_t>(UINT64_C(4372995238176751616)), detail::nothing{} }; }
    static constexpr auto my_value_round_error()   -> soft_double { return soft_double { static_cast<std::uint64_t>(UINT64_C(0x3FE0000000000000)),  detail::nothing{} }; }
    static constexpr auto my_value_denorm_min()    -> soft_double { return soft_double { static_cast<std::uint64_t>(UINT64_C(1)),                   detail::nothing{} }; }
    static constexpr auto my_value_infinity()      -> soft_double { return soft_double { static_cast<std::uint64_t>(UINT64_C(0x7FF0000000000000)),  detail::nothing{} }; }
    static constexpr auto my_value_quiet_NaN()     -> soft_double { return soft_double { static_cast<std::uint64_t>(UINT64_C(0xFFF8000000000000)),  detail::nothing{} }; }
    static constexpr auto my_value_signaling_NaN() -> soft_double { return soft_double { static_cast<std::uint64_t>(UINT64_C(0x7FF8000000000000)),  detail::nothing{} }; }

  private:
    representation_type my_value { };

    static constexpr auto my_le(const soft_double& a, const soft_double& b) -> bool
    {
      return (detail::signF64UI(a.my_value) != detail::signF64UI(b.my_value))
               ? (detail::signF64UI(a.my_value) ||  (static_cast<std::uint64_t>(a.my_value | b.my_value) & static_cast<std::uint64_t>(UINT64_C(0x7FFFFFFFFFFFFFFF))) == static_cast<std::uint64_t>(UINT8_C(0)))
               : (a.my_value == b.my_value)     || ((  static_cast<unsigned>(detail::signF64UI(a.my_value) ? static_cast<unsigned>(UINT8_C(1)) : static_cast<unsigned>(UINT8_C(0)))
                                                     ^ static_cast<unsigned>((a.my_value < b.my_value)     ? static_cast<unsigned>(UINT8_C(1)) : static_cast<unsigned>(UINT8_C(0)))) != static_cast<unsigned>(UINT8_C(0)));
    }

    static constexpr auto my_lt(const soft_double& a, const soft_double& b) -> bool
    {
      return (detail::signF64UI(a.my_value) != detail::signF64UI(b.my_value))
               ? (detail::signF64UI(a.my_value) &&  (static_cast<std::uint64_t>(a.my_value | b.my_value) & static_cast<std::uint64_t>(UINT64_C(0x7FFFFFFFFFFFFFFF))) != static_cast<std::uint64_t>(UINT8_C(0)))
               : (a.my_value != b.my_value)     && ((  static_cast<unsigned>(detail::signF64UI(a.my_value) ? static_cast<unsigned>(UINT8_C(1)) : static_cast<unsigned>(UINT8_C(0)))
                                                     ^ static_cast<unsigned>((a.my_value < b.my_value)     ? static_cast<unsigned>(UINT8_C(1)) : static_cast<unsigned>(UINT8_C(0)))) != static_cast<unsigned>(UINT8_C(0)));
    }

    static constexpr auto sign_ab(const std::uint64_t a, const std::uint64_t b) -> bool
    {
      const auto signA = detail::signF64UI(a);
      const auto signB = detail::signF64UI(b);

      return
        static_cast<std::uint_fast8_t>
        (
            static_cast<std::uint_fast8_t>(signA ? static_cast<std::uint_fast8_t>(UINT8_C(1)) : static_cast<std::uint_fast8_t>(UINT8_C(0)))
          ^ static_cast<std::uint_fast8_t>(signB ? static_cast<std::uint_fast8_t>(UINT8_C(1)) : static_cast<std::uint_fast8_t>(UINT8_C(0)))
        ) != static_cast<std::uint_fast8_t>(UINT8_C(0));
    }

    static constexpr auto f64_add(const std::uint64_t a, const std::uint64_t b) -> std::uint64_t
    {
      const auto signA = detail::signF64UI(a);

      return ((signA == detail::signF64UI(b)) ? softfloat_addMagsF64(a, b, signA)
                                              : softfloat_subMagsF64(a, b, signA));
    }

    static constexpr auto f64_sub(const std::uint64_t a, const std::uint64_t b) -> std::uint64_t
    {
      const auto signA = detail::signF64UI(a);

      return ((signA == detail::signF64UI(b)) ? softfloat_subMagsF64(a, b, signA)
                                              : softfloat_addMagsF64(a, b, signA));
    }

    static constexpr auto f64_mul(const std::uint64_t a, const std::uint64_t b) -> std::uint64_t
    {
      const auto expA  = detail::expF64UI (a);
      const auto expB  = detail::expF64UI (b);

      auto sigA  = detail::fracF64UI(a);
      auto sigB  = detail::fracF64UI(b);

      const auto signZ = sign_ab(a, b);

      auto result = std::uint64_t { };

      const auto a_is_zero = (   (expA == static_cast<std::int16_t> ( INT8_C(0)))
                              && (sigA == static_cast<std::uint64_t>(UINT8_C(0))));

      if(    a_is_zero
          || (   (expB == static_cast<std::int16_t> ( INT8_C(0)))
              && (sigB == static_cast<std::uint64_t>(UINT8_C(0)))))
      {
        result = detail::packToF64UI(signZ, static_cast<int>(INT8_C(0)), static_cast<int>(INT8_C(0)));
      }
      else
      {
        auto expZ =
          static_cast<std::int16_t>
          (
              static_cast<std::int16_t>(expA + expB)
            - static_cast<std::int16_t>(INT16_C(0x3FF))
          );

        sigA =
          static_cast<std::uint64_t>
          (
            static_cast<std::uint64_t>
            (
              sigA | static_cast<std::uint64_t>(UINT64_C(0x0010000000000000))
            ) << static_cast<unsigned>(UINT8_C(10))
          );

        sigB =
          static_cast<std::uint64_t>
          (
            static_cast<std::uint64_t>
            (
              sigB | static_cast<std::uint64_t>(UINT64_C(0x0010000000000000))
            ) << static_cast<unsigned>(UINT8_C(11))
          );

        // Compute the 128-bit product of sigA and sigB.

        const auto a32 = static_cast<std::uint32_t>(sigA >> static_cast<unsigned>(UINT8_C(32)));
        const auto a0  = static_cast<std::uint32_t>(sigA);
        const auto b32 = static_cast<std::uint32_t>(sigB >> static_cast<unsigned>(UINT8_C(32)));
        const auto b0  = static_cast<std::uint32_t>(sigB);

        const auto mid1 = static_cast<std::uint64_t>(                                  (static_cast<std::uint64_t>(a32)) * b0);
              auto mid  = static_cast<std::uint64_t>(mid1 + static_cast<std::uint64_t>((static_cast<std::uint64_t>(b32)) * a0));

        auto sig128Z =
          detail::uint128_compound
          {
            static_cast<std::uint64_t>(static_cast<std::uint64_t>(a0)  * b0),
            static_cast<std::uint64_t>
            (
                static_cast<std::uint64_t>(static_cast<std::uint64_t>(a32) * b32)
              + static_cast<std::uint32_t>(mid >> static_cast<unsigned>(UINT8_C(32)))
            )
          };

        if(mid < mid1)
        {
          sig128Z.v1 =
            static_cast<std::uint64_t>
            (
                 sig128Z.v1
              +  static_cast<std::uint64_t>(UINT64_C(0x100000000))
            );
        }

        mid = static_cast<std::uint64_t>(mid << static_cast<unsigned>(UINT8_C(32)));

        sig128Z.v0 = static_cast<std::uint64_t>(sig128Z.v0 + mid);

        sig128Z.v1 =
          static_cast<std::uint64_t>
          (
              sig128Z.v1
            + static_cast<std::uint_fast8_t>
              (
                (sig128Z.v0 < mid)
                  ? static_cast<std::uint_fast8_t>(UINT8_C(1))
                  : static_cast<std::uint_fast8_t>(UINT8_C(0))
              )
          );

        if(sig128Z.v0 != static_cast<std::uint64_t>(UINT8_C(0)))
        {
          sig128Z.v1 =
            static_cast<std::uint64_t>
            (
                sig128Z.v1
              | static_cast<std::uint_fast8_t>(UINT8_C(1))
            );
        }

        if(sig128Z.v1 < static_cast<std::uint64_t>(UINT64_C(0x4000000000000000)))
        {
          --expZ;

          sig128Z.v1 <<= static_cast<unsigned>(UINT8_C(1));
        }

        result = softfloat_roundPackToF64(signZ, expZ, sig128Z.v1);
      }

      return result;
    }

    static constexpr auto f64_div(const std::uint64_t a, const std::uint64_t b) -> std::uint64_t
    {
      const auto expA  = detail::expF64UI(a);
            auto sigA  = detail::fracF64UI(a);

      const auto signZ = sign_ab(a, b);

      auto result = std::uint64_t { };

      const auto a_is_zero = (   (expA == static_cast<std::int16_t> ( INT8_C(0)))
                              && (sigA == static_cast<std::uint64_t>(UINT8_C(0))));

      if(a_is_zero)
      {
        result = detail::packToF64UI(signZ, static_cast<int>(INT8_C(0)), static_cast<int>(INT8_C(0)));
      }
      else
      {
        auto expZ =
          static_cast<std::int16_t>
          (
              static_cast<std::int16_t>(expA - detail::expF64UI(b))
            + static_cast<std::int16_t>(INT16_C(0x3FE))
          );

        sigA =
          static_cast<std::uint64_t>
          (
              sigA
            | static_cast<std::uint64_t>(UINT64_C(0x0010000000000000))
          );

        auto sigB =
          static_cast<std::uint64_t>
          (
              detail::fracF64UI(b)
            | static_cast<std::uint64_t>(UINT64_C(0x0010000000000000))
          );

        if(sigA < sigB)
        {
          --expZ;

          sigA = static_cast<std::uint64_t>(sigA << static_cast<unsigned>(UINT8_C(11)));
        }
        else
        {
          sigA = static_cast<std::uint64_t>(sigA << static_cast<unsigned>(UINT8_C(10)));
        }

        sigB <<= static_cast<unsigned>(UINT8_C(11));

        const auto recip32 =
          static_cast<std::uint32_t>
          (
              detail::softfloat_approxRecip32_1(static_cast<std::uint32_t>(sigB >> static_cast<unsigned>(UINT8_C(32))))
            - static_cast<unsigned>(UINT8_C(2))
          );

        const auto sig32Z =
          static_cast<std::uint32_t>
          (
            static_cast<std::uint64_t>
            (
                static_cast<std::uint32_t>(sigA >> static_cast<unsigned>(UINT8_C(32)))
              * static_cast<std::uint64_t>(recip32)
            ) >> static_cast<unsigned>(UINT8_C(32))
          );

        auto doubleTerm = static_cast<std::uint32_t>(sig32Z << static_cast<unsigned>(UINT8_C(1)));

        auto rem =
          static_cast<std::uint64_t>
          (
            static_cast<std::uint64_t>
            (
              static_cast<std::uint64_t>
              (
                  sigA
                - static_cast<std::uint64_t>
                  (
                      static_cast<std::uint64_t>(doubleTerm)
                    * static_cast<std::uint32_t>(sigB >> static_cast<unsigned>(UINT8_C(32)))
                  )
              )
              << static_cast<unsigned>(UINT8_C(28))
            )
          - static_cast<std::uint64_t>
            (
                static_cast<std::uint64_t>(doubleTerm)
              * static_cast<std::uint32_t>(static_cast<std::uint32_t>(sigB) >> static_cast<unsigned>(UINT8_C(4)))
            )
          );

        auto q =
          static_cast<std::uint32_t>
          (
              static_cast<std::uint32_t>
              (
                   static_cast<std::uint64_t>
                   (
                       static_cast<std::uint32_t>(rem >> static_cast<unsigned>(UINT8_C(32)))
                     * static_cast<std::uint64_t>(recip32)
                   )
                >> static_cast<unsigned>(UINT8_C(32))
              )
            + static_cast<std::uint_fast8_t>(UINT8_C(4))
          );

        auto sigZ =
          static_cast<std::uint64_t>
          (
              static_cast<std::uint64_t>(static_cast<std::uint64_t>(sig32Z) << static_cast<unsigned>(UINT8_C(32)))
            + static_cast<std::uint64_t>(static_cast<std::uint64_t>(q)      << static_cast<unsigned>(UINT8_C( 4)))
          );

        if(static_cast<std::uint_fast16_t>(sigZ & static_cast<std::uint_fast16_t>(UINT16_C(0x1FF))) < static_cast<std::uint_fast16_t>(static_cast<std::uint_fast16_t>(UINT8_C(4)) << static_cast<unsigned>(UINT8_C(4))))
        {
          q    = static_cast<std::uint32_t>(q    & static_cast<std::uint32_t>(~static_cast<std::uint32_t>(UINT8_C(7))));
          sigZ = static_cast<std::uint64_t>(sigZ & static_cast<std::uint64_t>(~static_cast<std::uint64_t>(UINT8_C(0x7F))));

          doubleTerm = static_cast<std::uint32_t>(q << static_cast<unsigned>(UINT8_C(1)));

          rem =
            static_cast<std::uint64_t>
            (
                static_cast<std::uint64_t>
                (
                  static_cast<std::uint64_t>
                  (
                      rem
                    - static_cast<std::uint64_t>
                      (
                          static_cast<std::uint64_t>(doubleTerm)
                        * static_cast<std::uint32_t>(sigB >> static_cast<unsigned>(UINT8_C(32)))
                      )
                  ) << static_cast<unsigned>(UINT8_C(28))
                )
              - static_cast<std::uint64_t>
                (
                    static_cast<std::uint64_t>(doubleTerm)
                  * static_cast<std::uint32_t>(static_cast<std::uint32_t>(sigB) >> static_cast<unsigned>(UINT8_C(4)))
                )
            );

          if(static_cast<std::uint_fast8_t>(rem >> static_cast<unsigned>(UINT8_C(63))) != static_cast<std::uint_fast8_t>(UINT8_C(0)))
          {
            sigZ =
              static_cast<std::uint64_t>
              (
                  sigZ
                - static_cast<std::uint_fast8_t>
                  (
                    static_cast<std::uint_fast8_t>(UINT8_C(1)) << static_cast<unsigned>(UINT8_C(7))
                  )
              );
          }
          else
          {
            if(rem != static_cast<std::uint64_t>(UINT8_C(0)))
            {
              sigZ = static_cast<std::uint64_t>(sigZ | static_cast<std::uint_fast8_t>(UINT8_C(1)));
            }
          }
        }

        result = softfloat_roundPackToF64(signZ, expZ, sigZ);
      }

      return result;
    }

    static constexpr auto f64_sqrt(const std::uint64_t a) -> std::uint64_t
    {
      auto expA = detail::expF64UI (a);
      auto sigA = detail::fracF64UI(a);

      auto result = std::uint64_t { };

      const auto a_is_zero = (   (expA == static_cast<std::int16_t> ( INT8_C(0)))
                              && (sigA == static_cast<std::uint64_t>(UINT8_C(0))));

      if(a_is_zero || detail::signF64UI(a))
      {
        result = a;
      }
      else
      {
        // sig32Z is guaranteed to be a lower bound on the square root
        // of sig32A, which makes sig32Z also a lower bound on the
        // square root of sigA.

        const auto expZ =
          static_cast<std::int16_t>
          (
              static_cast<std::int_fast16_t>
              (
                static_cast<std::int_fast16_t> // NOLINT(hicpp-signed-bitwise)
                (
                    expA
                  - static_cast<std::int16_t>(INT16_C(0x3FF))
                ) >> static_cast<unsigned>(UINT8_C(1))
              )
            + static_cast<std::int_fast16_t>(INT16_C(0x3FE))
          );

        expA =
          static_cast<std::int16_t>
          (
            static_cast<std::uint_fast8_t>(expA) & static_cast<std::uint_fast8_t>(UINT8_C(1))
          );

        sigA = static_cast<std::uint64_t>(sigA | static_cast<std::uint64_t>(UINT64_C(0x0010000000000000)));

        const auto sig32A      = static_cast<std::uint32_t>(sigA >> static_cast<unsigned>(UINT8_C(21)));
        const auto recipSqrt32 = softfloat_approxRecipSqrt32_1(static_cast<std::uint32_t>(expA), sig32A);
              auto sig32Z      = static_cast<std::uint32_t>
                                 (
                                   static_cast<std::uint64_t>(static_cast<std::uint64_t>(sig32A) * recipSqrt32) >> static_cast<unsigned>(UINT8_C(32))
                                 );

        if(expA != static_cast<std::int16_t>(INT8_C(0)))
        {
          sigA   <<= static_cast<unsigned>(UINT8_C(8));
          sig32Z >>= static_cast<unsigned>(UINT8_C(1));
        }
        else
        {
          sigA <<= static_cast<unsigned>(UINT8_C(9));
        }

        auto rem =
          static_cast<std::uint64_t>
          (
              sigA
            - static_cast<std::uint64_t>(static_cast<std::uint64_t>(sig32Z) * sig32Z)
          );

        const auto q =
          static_cast<std::uint32_t>
          (
            static_cast<std::uint64_t>
            (
                static_cast<std::uint32_t>(rem >> static_cast<unsigned>(UINT8_C(2)))
              * static_cast<std::uint64_t>(recipSqrt32)
            ) >> static_cast<unsigned>(UINT8_C(32))
          );

        auto sigZ =
          static_cast<std::uint64_t>
          (
              static_cast<std::uint64_t>
              (
                  static_cast<std::uint64_t>(static_cast<std::uint64_t>(sig32Z) << static_cast<unsigned>(UINT8_C(32)))
                | static_cast<std::uint_fast8_t>(static_cast<std::uint_fast8_t>(UINT8_C(1)) << static_cast<unsigned>(UINT8_C(5)))
              )
            + static_cast<std::uint64_t>((static_cast<std::uint64_t>(q) << static_cast<unsigned>(UINT8_C(3))))
          );

        const auto sig_small_masked =
          static_cast<std::uint_fast16_t>
          (
            sigZ & static_cast<std::uint_fast16_t>(UINT16_C(0x1FF))
          );

        if(sig_small_masked < static_cast<std::uint_fast16_t>(UINT16_C(0x22)))
        {
          sigZ &= static_cast<std::uint64_t>(~static_cast<std::uint64_t>(UINT8_C(0x3F)));

          const auto shiftedSigZ = static_cast<std::uint64_t>(sigZ >> static_cast<unsigned>(UINT8_C(6)));

          rem =
            static_cast<std::uint64_t>
            (
                static_cast<std::uint64_t>(sigA << static_cast<unsigned>(UINT8_C(52)))
              - static_cast<std::uint64_t>(shiftedSigZ * shiftedSigZ)
            );

          if(static_cast<std::uint_fast8_t>(rem >> static_cast<unsigned>(UINT8_C(63))) != static_cast<std::uint_fast8_t>(UINT8_C(0)))
          {
            --sigZ;
          }
          else
          {
            if(rem != static_cast<std::uint64_t>(UINT8_C(0)))
            {
              sigZ =
                static_cast<std::uint64_t>
                (
                  sigZ | static_cast<std::uint_fast8_t>(UINT8_C(1))
                );
            }
          }
        }

        result = softfloat_roundPackToF64(false, expZ, sigZ);
      }

      return result;
    }

    static constexpr auto f64_to_ui32(const std::uint64_t a) -> std::uint32_t
    {
      const auto expA = detail::expF64UI (a);
            auto sig  = detail::fracF64UI(a);

      if(expA != static_cast<std::int16_t>(INT8_C(0)))
      {
        sig =
          static_cast<std::uint64_t>
          (
              sig
            | static_cast<std::uint64_t>(UINT64_C(0x0010000000000000))
          );
      }

      const auto shiftDist =
        static_cast<std::int16_t>
        (
            static_cast<std::int16_t>(INT16_C(0x427))
          - expA
        );

      if(shiftDist > static_cast<std::int16_t>(INT16_C(0)))
      {
        sig = detail::softfloat_shiftRightJam64(sig, static_cast<std::uint_fast16_t>(shiftDist));
      }

      return softfloat_roundToUI32(detail::signF64UI(a), sig);
    }

    static constexpr auto f64_to__i32(std::uint64_t a) -> std::int32_t // NOLINT(bugprone-reserved-identifier,cert-dcl37-c,cert-dcl51-cpp)
    {
      const auto expA = detail::expF64UI (a);
            auto sig  = detail::fracF64UI(a);

      if(expA != static_cast<std::int16_t>(INT8_C(0)))
      {
        sig =
          static_cast<std::uint64_t>
          (
              sig
            | static_cast<std::uint64_t>(UINT64_C(0x0010000000000000))
          );
      }

      const auto shiftDist =
        static_cast<std::int16_t>
        (
            static_cast<std::int16_t>(INT16_C(0x427))
          - expA
        );

      if(shiftDist > static_cast<std::int16_t>(INT16_C(0)))
      {
        sig = detail::softfloat_shiftRightJam64(sig, static_cast<std::uint_fast16_t>(shiftDist));
      }

      return softfloat_roundToI32(detail::signF64UI(a), sig);
    }

    static constexpr auto f64_to_ui64(std::uint64_t a) -> std::uint64_t
    {
      const auto expA = detail::expF64UI (a);
            auto sig  = detail::fracF64UI(a);

      if(expA != static_cast<std::int16_t>(INT8_C(0)))
      {
        sig =
          static_cast<std::uint64_t>
          (
              sig
            | static_cast<std::uint64_t>(UINT64_C(0x0010000000000000))
          );
      }

      const auto shiftDist =
        static_cast<std::int16_t>
        (
            static_cast<std::int16_t>(INT16_C(0x433))
          - expA
        );

      const auto sigExtra =
        detail::softfloat_shiftRightJam64Extra
        (
          sig,
          static_cast<std::uint64_t>(UINT8_C(0)),
          static_cast<std::uint32_t>(shiftDist)
        );

      return softfloat_roundToUI64(detail::signF64UI(a), sigExtra.v1);
    }

    static constexpr auto f64_to__i64(std::uint64_t a) -> std::int64_t // NOLINT(bugprone-reserved-identifier,cert-dcl37-c,cert-dcl51-cpp)
    {
      const auto expA = detail::expF64UI (a);
            auto sig  = detail::fracF64UI(a);

      if(expA != static_cast<std::int16_t>(INT8_C(0)))
      {
        sig =
          static_cast<std::uint64_t>
          (
              sig
            | static_cast<std::uint64_t>(UINT64_C(0x0010000000000000))
          );
      }

      const auto shiftDist =
        static_cast<std::int16_t>
        (
            static_cast<std::int16_t>(INT16_C(0x433))
          - expA
        );

      const auto sigExtra =
        detail::softfloat_shiftRightJam64Extra
        (
          sig,
          static_cast<std::uint64_t>(UINT8_C(0)),
          static_cast<std::uint32_t>(shiftDist)
        );

      return softfloat_roundToI64(detail::signF64UI(a), sigExtra.v1);
    }

    static constexpr auto f64_to_f32(const std::uint64_t a) -> float
    {
      return
        softfloat_roundPackToF32
        (
          detail::signF64UI(a),
          static_cast<std::int16_t>(detail::expF64UI(a) - static_cast<std::int16_t>(INT16_C(0x381))),
          static_cast<std::uint32_t>
          (
              static_cast<std::uint32_t>
              (
                detail::softfloat_shortShiftRightJam64(detail::fracF64UI(a), static_cast<std::uint_fast16_t>(UINT8_C(22)))
              )
            | static_cast<std::uint32_t>(UINT32_C(0x40000000))
          )
        );
    }

    static constexpr auto softfloat_roundPackToF32(bool sign, std::int16_t expA, std::uint32_t sig) -> float
    {
      constexpr auto roundIncrement = static_cast<std::uint_fast8_t>(UINT8_C(0x40));

      const auto roundBits =
        static_cast<std::uint_fast8_t>
        (
            static_cast<std::uint_fast8_t>(sig)
          & static_cast<std::uint_fast8_t>(UINT8_C(0x7F))
        );

      sig =
        static_cast<std::uint32_t>
        (
          static_cast<std::uint32_t>(sig + roundIncrement) >> static_cast<unsigned>(UINT8_C(7))
        );

      sig =
        static_cast<std::uint32_t>
        (
            sig
          & static_cast<std::uint32_t>
            (
              ~static_cast<std::uint32_t>
               (
                   static_cast<std::uint_fast8_t>
                   (
                     (static_cast<std::uint_fast8_t>(roundBits ^ static_cast<std::uint_fast8_t>(UINT8_C(0x40))) == static_cast<std::uint_fast8_t>(UINT8_C(0)))
                       ? static_cast<std::uint_fast8_t>(UINT8_C(1))
                       : static_cast<std::uint_fast8_t>(UINT8_C(0))
                   )
                 & static_cast<std::uint_fast8_t>(UINT8_C(1))
               )
            )
        );

      if(sig == static_cast<std::uint32_t>(UINT8_C(0)))
      {
        expA = static_cast<std::int16_t>(INT8_C(0));
      }

      return detail::uz_type<float>(detail::packToF32UI(sign, expA, sig)).my_f; // NOLINT(cppcoreguidelines-pro-type-union-access)
    }

    static constexpr auto my__i32_to_f64(const std::int32_t a) -> std::uint64_t // NOLINT(bugprone-reserved-identifier,cert-dcl37-c,cert-dcl51-cpp)
    {
      return
        (a == static_cast<std::int32_t>(INT8_C(0)))
          ? static_cast<std::uint64_t>(UINT8_C(0))
          : detail::packToF64UI
            (
              (a < static_cast<std::int32_t>(INT8_C(0))),
              static_cast<std::int_fast16_t>
              (
                  static_cast<std::int_fast16_t>(INT16_C(0x432))
                - static_cast<std::int_fast16_t>
                  (
                      static_cast<std::uint_fast16_t>
                      (
                        detail::softfloat_countLeadingZeros32
                        (
                          static_cast<std::uint32_t>
                          (
                            (a < static_cast<std::int32_t>(INT8_C(0))) ? detail::negate(static_cast<std::uint32_t>(a))
                                                                       :                static_cast<std::uint32_t>(a)
                          )
                        )
                      )
                    + static_cast<std::uint_fast16_t>(UINT16_C(21))
                  )
              ),
              static_cast<std::uint64_t>
              (
                   static_cast<std::uint64_t>
                   (
                     (a < static_cast<std::int32_t>(INT8_C(0))) ? detail::negate(static_cast<std::uint32_t>(a))
                                                                :                static_cast<std::uint32_t>(a)
                   )
                << static_cast<std::uint_fast16_t>
                   (
                       static_cast<std::uint_fast16_t>
                       (
                         detail::softfloat_countLeadingZeros32
                         (
                           static_cast<std::uint32_t>
                           (
                             (a < static_cast<std::int32_t>(INT8_C(0))) ? detail::negate(static_cast<std::uint32_t>(a))
                                                                        :                static_cast<std::uint32_t>(a)
                           )
                         )
                       )
                     + static_cast<std::uint_fast16_t>(UINT8_C(21))
                   )
              )
            );
    }

    static constexpr auto my__i64_to_f64(const int64_t a) -> std::uint64_t // NOLINT(bugprone-reserved-identifier,cert-dcl37-c,cert-dcl51-cpp)
    {
      return
        (static_cast<std::uint64_t>(static_cast<std::uint64_t>(a) & static_cast<std::uint64_t>(UINT64_C(0x7FFFFFFFFFFFFFFF))) == static_cast<std::uint64_t>(UINT8_C(0)))
          ? static_cast<std::uint64_t>
            (
              (a < static_cast<std::int64_t>(INT8_C(0)))
                ? detail::packToF64UI(true, static_cast<std::int16_t>(INT16_C(0x43E)), static_cast<int>(INT8_C(0)))
                : static_cast<std::uint64_t>(UINT8_C(0))
            )
          : softfloat_normRoundPackToF64
            (
              (a < static_cast<std::int64_t>(INT8_C(0))),
              static_cast<std::int16_t>(INT16_C(0x43C)),
              static_cast<std::uint64_t>
              (
                (a < static_cast<std::int64_t>(INT8_C(0))) ? detail::negate(static_cast<std::uint64_t>(a))
                                                           :                static_cast<std::uint64_t>(a)
              )
            );
    }

    static constexpr auto my_ui32_to_f64(const std::uint32_t a) -> std::uint64_t
    {
      return
        (a == static_cast<std::uint32_t>(UINT8_C(0)))
          ? static_cast<std::uint64_t>(UINT8_C(0))
          : detail::packToF64UI
            (
              false,
              static_cast<std::int_fast16_t>
              (
                  static_cast<std::int_fast16_t>(INT16_C(0x432))
                - static_cast<std::int_fast16_t>
                  (
                      static_cast<std::uint_fast16_t>(detail::softfloat_countLeadingZeros32(a))
                    + static_cast<std::uint_fast16_t>(UINT8_C(21))
                  )
              ),
              static_cast<std::uint64_t>
              (
                    static_cast<std::uint64_t>(a)
                << static_cast<std::uint_fast16_t>
                    (
                        static_cast<std::uint_fast16_t>(detail::softfloat_countLeadingZeros32(a))
                      + static_cast<std::uint_fast16_t>(UINT8_C(21))
                    )
              )
            );
    }

    static constexpr auto my_ui64_to_f64(const std::uint64_t a) -> std::uint64_t
    {
      return
        (a == static_cast<std::uint64_t>(UINT8_C(0)))
          ? static_cast<std::uint64_t>(UINT8_C(0))
          : (static_cast<std::uint64_t>(a & static_cast<std::uint64_t>(UINT64_C(0x8000000000000000))) != static_cast<std::uint64_t>(UINT8_C(0)))
              ? softfloat_roundPackToF64    (false, static_cast<std::int16_t>(INT16_C(0x43D)), detail::softfloat_shortShiftRightJam64(a, static_cast<std::uint_fast16_t>(UINT8_C(1))))
              : softfloat_normRoundPackToF64(false, static_cast<std::int16_t>(INT16_C(0x43C)), a);
    }

    static constexpr auto softfloat_roundToI32(bool sign, std::uint64_t sig) -> std::int32_t
    {
      return
        static_cast<std::int32_t>
        (
          static_cast<std::uint32_t>
          (
            sign ? detail::negate(static_cast<std::uint32_t>(sig >> static_cast<unsigned>(UINT8_C(12))))
                 :                static_cast<std::uint32_t>(sig >> static_cast<unsigned>(UINT8_C(12)))
          )
        );
    }

    static constexpr auto softfloat_roundToI64(bool sign, std::uint64_t sig) -> std::int64_t
    {
      return
        static_cast<std::int64_t>
        (
          static_cast<std::uint64_t>(sign ? detail::negate(sig) : sig)
        );
    }

    static constexpr auto softfloat_roundToUI32(bool sign, std::uint64_t sig) -> std::uint32_t
    {
      return
        static_cast<std::uint32_t>
        (
          (sign && (sig == static_cast<std::uint64_t>(UINT8_C(0))))
            ? static_cast<std::uint32_t>(UINT8_C(0))
            : static_cast<std::uint32_t>(sig >> static_cast<unsigned>(UINT8_C(12)))
        );
    }

    static constexpr auto softfloat_roundToUI64(bool sign, std::uint64_t sig) -> std::uint64_t
    {
      return
        static_cast<std::uint64_t>
        (
          (sign && (sig == static_cast<std::uint64_t>(UINT8_C(0))))
            ? static_cast<std::uint64_t>(UINT8_C(0))
            : sig
        );
    }

    static constexpr auto softfloat_addMagsF64(std::uint64_t uiA, std::uint64_t uiB, bool signZ) -> std::uint64_t
    {
      const auto expA = detail::expF64UI(uiA);
      const auto expB = detail::expF64UI(uiB);
            auto expZ = expA;

      const auto expDiff = static_cast<std::int16_t>(expA - expB);

      auto sigZ = std::uint64_t { };

      if(expDiff == static_cast<std::int16_t>(INT8_C(0)))
      {
        sigZ =
          static_cast<std::uint64_t>
          (
            static_cast<std::uint64_t>
            (
                static_cast<std::uint64_t>
                (
                  detail::fracF64UI(uiA) + static_cast<std::uint64_t>(UINT64_C(0x0020000000000000))
                )
              + detail::fracF64UI(uiB)
            )
            << static_cast<unsigned>(UINT8_C(9))
          );
      }
      else
      {
        auto sigA = static_cast<std::uint64_t>(detail::fracF64UI(uiA) << static_cast<unsigned>(UINT8_C(9)));
        auto sigB = static_cast<std::uint64_t>(detail::fracF64UI(uiB) << static_cast<unsigned>(UINT8_C(9)));

        if(expDiff < static_cast<std::int16_t>(INT8_C(0)))
        {
          expZ = expB;

          sigA =
            static_cast<std::uint64_t>
            (
              (expA != static_cast<std::int16_t>(INT8_C(0)))
                ? static_cast<std::uint64_t>(sigA + static_cast<std::uint64_t>(UINT64_C(0x2000000000000000)))
                : static_cast<std::uint64_t>(sigA << static_cast<unsigned>(UINT8_C(1)))
            );

          sigA = detail::softfloat_shiftRightJam64(sigA, static_cast<std::uint_fast16_t>(-expDiff));
        }
        else
        {
          sigB =
            static_cast<std::uint64_t>
            (
              (expB != static_cast<std::int16_t>(INT8_C(0)))
                ? static_cast<std::uint64_t>(sigB + static_cast<std::uint64_t>(UINT64_C(0x2000000000000000)))
                : static_cast<std::uint64_t>(sigB << static_cast<unsigned>(UINT8_C(1)))
            );

          sigB = detail::softfloat_shiftRightJam64(sigB, static_cast<std::uint_fast16_t>(expDiff));
        }

        sigZ =
          static_cast<std::uint64_t>
          (
              static_cast<std::uint64_t>
              (
                  sigA
                + static_cast<std::uint64_t>(UINT64_C(0x2000000000000000))
              )
            + sigB
          );

        if(sigZ < static_cast<std::uint64_t>(UINT64_C(0x4000000000000000)))
        {
          --expZ;

          sigZ = static_cast<std::uint64_t>(sigZ << static_cast<unsigned>(UINT8_C(1)));
        }
      }

      return softfloat_roundPackToF64(signZ, expZ, sigZ);
    }

    static constexpr auto softfloat_approxRecipSqrt32_1(std::uint32_t oddExpA, std::uint32_t a) -> std::uint32_t
    {
      // Returns an approximation to the reciprocal of the square root of the number
      // represented by a, where a is interpreted as an unsigned fixed-point
      // number either with one integer bit and 31 fraction bits or with two integer
      // bits and 30 fraction bits.
      using softfloat_approx_recip_sqrt_array_type = std::array<std::uint16_t, static_cast<std::size_t>(UINT8_C(16))>;

      constexpr auto softfloat_approxRecipSqrt_1k0s =
        softfloat_approx_recip_sqrt_array_type
        {
          static_cast<std::uint16_t>(UINT16_C(0xB4C9)), static_cast<std::uint16_t>(UINT16_C(0xFFAB)), static_cast<std::uint16_t>(UINT16_C(0xAA7D)), static_cast<std::uint16_t>(UINT16_C(0xF11C)),
          static_cast<std::uint16_t>(UINT16_C(0xA1C5)), static_cast<std::uint16_t>(UINT16_C(0xE4C7)), static_cast<std::uint16_t>(UINT16_C(0x9A43)), static_cast<std::uint16_t>(UINT16_C(0xDA29)),
          static_cast<std::uint16_t>(UINT16_C(0x93B5)), static_cast<std::uint16_t>(UINT16_C(0xD0E5)), static_cast<std::uint16_t>(UINT16_C(0x8DED)), static_cast<std::uint16_t>(UINT16_C(0xC8B7)),
          static_cast<std::uint16_t>(UINT16_C(0x88C6)), static_cast<std::uint16_t>(UINT16_C(0xC16D)), static_cast<std::uint16_t>(UINT16_C(0x8424)), static_cast<std::uint16_t>(UINT16_C(0xBAE1))
        };

      constexpr auto softfloat_approxRecipSqrt_1k1s =
        softfloat_approx_recip_sqrt_array_type
        {
          static_cast<std::uint16_t>(UINT16_C(0xA5A5)), static_cast<std::uint16_t>(UINT16_C(0xEA42)), static_cast<std::uint16_t>(UINT16_C(0x8C21)), static_cast<std::uint16_t>(UINT16_C(0xC62D)),
          static_cast<std::uint16_t>(UINT16_C(0x788F)), static_cast<std::uint16_t>(UINT16_C(0xAA7F)), static_cast<std::uint16_t>(UINT16_C(0x6928)), static_cast<std::uint16_t>(UINT16_C(0x94B6)),
          static_cast<std::uint16_t>(UINT16_C(0x5CC7)), static_cast<std::uint16_t>(UINT16_C(0x8335)), static_cast<std::uint16_t>(UINT16_C(0x52A6)), static_cast<std::uint16_t>(UINT16_C(0x74E2)),
          static_cast<std::uint16_t>(UINT16_C(0x4A3E)), static_cast<std::uint16_t>(UINT16_C(0x68FE)), static_cast<std::uint16_t>(UINT16_C(0x432B)), static_cast<std::uint16_t>(UINT16_C(0x5EFD))
        };

      const auto index  =
        static_cast<std::int16_t>
        (
            static_cast<std::uint32_t>
            (
              static_cast<std::uint32_t>(a >> static_cast<unsigned>(UINT8_C(27))) & static_cast<std::uint32_t>(UINT8_C(0xE))
            )
          + oddExpA
        );

      const auto eps = static_cast<std::uint16_t>(a >> static_cast<unsigned>(UINT8_C(12)));

      const auto r0 =
        static_cast<std::uint16_t>
        (
            softfloat_approxRecipSqrt_1k0s[static_cast<std::size_t>(index)] // NOLINT(cppcoreguidelines-pro-bounds-constant-array-index)
          - static_cast<std::uint16_t>
            (
              static_cast<std::uint32_t>
              (
                  softfloat_approxRecipSqrt_1k1s[static_cast<std::size_t>(index)] // NOLINT(cppcoreguidelines-pro-bounds-constant-array-index)
                * static_cast<std::uint32_t>(eps)
              ) >> static_cast<unsigned>(UINT8_C(20))
            )
        );

      auto ESqrR0 = static_cast<std::uint32_t>(static_cast<std::uint32_t>(r0) * r0);

      if(oddExpA == static_cast<std::uint32_t>(UINT8_C(0)))
      {
        ESqrR0 <<= static_cast<unsigned>(UINT8_C(1));
      }

      const auto sigma0 =
        static_cast<std::uint32_t>
        (
          ~static_cast<std::uint32_t>
           (
             static_cast<std::uint64_t>(ESqrR0 * static_cast<std::uint64_t>(a)) >> static_cast<unsigned>(UINT8_C(23))
           )
        );

      auto r =
        static_cast<std::uint32_t>
        (
            static_cast<std::uint32_t>(static_cast<std::uint32_t>(r0) << static_cast<unsigned>(UINT8_C(16)))
          + static_cast<std::uint32_t>(static_cast<std::uint64_t>(r0 * static_cast<std::uint64_t>(sigma0)) >> static_cast<unsigned>(UINT8_C(25)))
        );

      r +=
        static_cast<std::uint32_t>
        (
          static_cast<std::uint64_t>
          (
              static_cast<std::uint32_t>
              (
                  static_cast<std::uint32_t>
                  (
                    static_cast<std::uint64_t>(r >> static_cast<unsigned>(UINT8_C(1))) + static_cast<std::uint32_t>(r >> static_cast<unsigned>(UINT8_C(3)))
                  )
                - static_cast<std::uint32_t>
                  (
                    static_cast<std::uint32_t>(r0) << static_cast<unsigned>(UINT8_C(14))
                  )
              )
            *
              static_cast<std::uint64_t>
              (
                static_cast<std::uint32_t>
                (
                  static_cast<std::uint64_t>(static_cast<std::uint64_t>(sigma0) * sigma0) >> static_cast<unsigned>(UINT8_C(32))
                )
              )
          ) >> static_cast<unsigned>(UINT8_C(48))
        );

      if(static_cast<std::uint32_t>(r & static_cast<std::uint32_t>(UINT32_C(0x80000000))) == static_cast<std::uint32_t>(UINT8_C(0)))
      {
        r = static_cast<std::uint32_t>(UINT32_C(0x80000000));
      }

      return r;
    }

    static constexpr auto softfloat_normRoundPackToF64(bool sign, std::int16_t expA, std::uint64_t sig) -> std::uint64_t
    {
      auto result = std::uint64_t { };

      const auto shiftDist =
        static_cast<std::int_fast8_t>
        (
            detail::softfloat_countLeadingZeros64(sig)
          - static_cast<std::uint_fast8_t>(UINT8_C(1))
        );

      expA =
        static_cast<std::int16_t>
        (
            expA
          - static_cast<std::int16_t>(shiftDist)
        );

      if(   (shiftDist >= static_cast<std::int_fast8_t>(INT8_C(10)))
         && (static_cast<std::uint_fast16_t>(expA) < static_cast<std::uint_fast16_t>(UINT16_C(0x7FD))))
      {
        result =
          detail::packToF64UI
          (
            sign,
            static_cast<std::int16_t>(sig != static_cast<std::uint64_t>(UINT8_C(0)) ? expA : static_cast<std::int16_t>(INT8_C(0))),
            static_cast<std::uint64_t>(sig << static_cast<unsigned>(shiftDist - static_cast<std::int_fast8_t>(INT8_C(10))))
          );
      }
      else
      {
        const auto safeShiftDist =
          static_cast<std::uint_fast8_t>
          (
            detail::my_max(static_cast<std::int_fast8_t>(INT8_C(0)), shiftDist)
          );

        result = softfloat_roundPackToF64(sign, expA, static_cast<std::uint64_t>(sig << static_cast<unsigned>(safeShiftDist)));
      }

      return result;
    }

    static constexpr auto softfloat_roundPackToF64(bool sign, std::int16_t expA, std::uint64_t sig) -> std::uint64_t
    {
      if(expA < static_cast<std::int16_t>(INT16_C(0)))
      {
        const auto expA_as_unsigned = static_cast<std::uint16_t>(expA);

        if(expA_as_unsigned >= static_cast<std::uint16_t>(UINT16_C(0x7FD)))
        {
          sig  = detail::softfloat_shiftRightJam64(sig, static_cast<std::uint_fast16_t>(-expA));
          expA = static_cast<std::int16_t>(INT8_C(0));
        }
      }

      const auto roundBits = static_cast<std::uint16_t>(sig & static_cast<std::uint64_t>(UINT16_C(0x3FF)));

      sig =
        static_cast<std::uint64_t>
        (
            static_cast<std::uint64_t>
            (
              static_cast<std::uint64_t>(sig + static_cast<std::uint16_t>(UINT16_C(0x200))) >> static_cast<unsigned>(UINT8_C(10))
            )
          & static_cast<std::uint64_t>
            (
              ~static_cast<std::uint64_t>
               (
                 (static_cast<std::uint16_t>(roundBits ^ static_cast<std::uint16_t>(UINT16_C(0x200))) == static_cast<std::uint16_t>(UINT8_C(0)))
                   ? static_cast<unsigned>(UINT8_C(1))
                   : static_cast<unsigned>(UINT8_C(0))
               )
            )
        );

      if(sig == static_cast<std::uint64_t>(UINT8_C(0)))
      {
        expA = static_cast<std::int16_t>(INT8_C(0));
      }

      return detail::packToF64UI(sign, expA, sig);
    }

    static constexpr auto softfloat_subMagsF64(std::uint64_t uiA, std::uint64_t uiB, bool signZ) -> std::uint64_t
    {
      auto uiZ  = std::uint64_t { };
      auto expZ = std::int16_t  { };

            auto expA = detail::expF64UI (uiA);
      const auto expB = detail::expF64UI (uiB);

      const auto expDiff = static_cast<std::int16_t>(expA - expB);

      if(expDiff == static_cast<std::int16_t>(INT8_C(0)))
      {
        const auto sigA = detail::fracF64UI(uiA);
        const auto sigB = detail::fracF64UI(uiB);

        auto sigDiff = static_cast<std::int64_t>(sigA - sigB);

        if(sigDiff == static_cast<std::int64_t>(INT8_C(0)))
        {
          uiZ = detail::packToF64UI(false, static_cast<int>(INT8_C(0)), static_cast<int>(INT8_C(0)));
        }
        else
        {
          if(expA != static_cast<std::int16_t>(INT8_C(0)))
          {
            --expA;
          }

          if(sigDiff < static_cast<std::int64_t>(INT8_C(0)))
          {
            signZ   = (!signZ);
            sigDiff = -sigDiff;
          }

          auto shiftDist =
            static_cast<std::int_fast8_t>
            (
                detail::softfloat_countLeadingZeros64(static_cast<std::uint64_t>(sigDiff))
              - static_cast<std::uint_fast8_t>(UINT8_C(11))
            );

          expZ =
            static_cast<std::int16_t>
            (
                expA
              - static_cast<std::int16_t>(shiftDist)
            );

          if(expZ < static_cast<std::int16_t>(INT8_C(0)))
          {
            shiftDist = static_cast<std::int_fast8_t>(expA);

            expZ = static_cast<std::int16_t>(INT8_C(0));
          }

          const auto safeShiftDist =
            static_cast<std::uint_fast8_t>
            (
              detail::my_max(static_cast<std::int_fast8_t>(INT8_C(0)), shiftDist)
            );

          uiZ =
            detail::packToF64UI
            (
              signZ,
              expZ,
              static_cast<std::uint64_t>(static_cast<std::uint64_t>(sigDiff) << static_cast<unsigned>(safeShiftDist))
            );
        }
      }
      else
      {
        const auto sigA = static_cast<std::uint64_t>(detail::fracF64UI(uiA) << static_cast<unsigned>(UINT8_C(10)));
        const auto sigB = static_cast<std::uint64_t>(detail::fracF64UI(uiB) << static_cast<unsigned>(UINT8_C(10)));

        auto sigZ = std::uint64_t { };

        if(expDiff < static_cast<std::int16_t>(INT8_C(0)))
        {
          signZ = (!signZ);

          const auto sigA_less =
            static_cast<std::uint64_t>
            (
                sigA
              + static_cast<std::uint64_t>
                (
                  (expA != static_cast<std::int16_t>(INT8_C(0)))
                    ? static_cast<std::uint64_t>(UINT64_C(0x4000000000000000))
                    : sigA
                )
            );

          expZ = expB;

          sigZ =
            static_cast<std::uint64_t>
            (
                static_cast<std::uint64_t>(sigB | static_cast<std::uint64_t>(UINT64_C(0x4000000000000000)))
              - detail::softfloat_shiftRightJam64(sigA_less, static_cast<std::uint_fast16_t>(-expDiff))
            );
        }
        else
        {
          const auto sigB_more =
            static_cast<std::uint64_t>
            (
                sigB
              + static_cast<std::uint64_t>
                (
                  (expB != static_cast<std::int16_t>(INT8_C(0)))
                    ? static_cast<std::uint64_t>(UINT64_C(0x4000000000000000))
                    : sigB
                )
            );

          expZ = expA;

          sigZ =
            static_cast<std::uint64_t>
            (
                static_cast<std::uint64_t>(sigA | static_cast<std::uint64_t>(UINT64_C(0x4000000000000000)))
              - detail::softfloat_shiftRightJam64(sigB_more, static_cast<std::uint_fast16_t>(expDiff))
            );
        }

        uiZ = softfloat_normRoundPackToF64(signZ, static_cast<std::int16_t>(expZ - static_cast<std::int16_t>(INT8_C(1))), sigZ);
      }

      return uiZ;
    }

    #if !defined(SOFT_DOUBLE_DISABLE_IOSTREAM)
    template<typename char_type, typename traits_type>
    friend auto operator<<(std::basic_ostream<char_type, traits_type>& os, const soft_double& f) -> std::basic_ostream<char_type, traits_type>&
    {
      // Note that this output stream function relies on
      // the availability of 64-bit native double.

      auto ostr = std::basic_ostringstream<char_type, traits_type> { };

      // Copy all ostream settings from out to local ostr.
      ostr.flags(os.flags());
      ostr.imbue(os.getloc());
      ostr.precision(os.precision());

      static_cast<void>(ostr << static_cast<double>(f));

      return (os << ostr.str());
    }

    template<typename char_type, typename traits_type>
    friend auto operator>>(std::basic_istream<char_type, traits_type>& is, soft_double& f) -> std::basic_istream<char_type, traits_type>&
    {
      // Note that this input stream function relies on
      // the availability of 64-bit native double.

      auto v = double { };

      // Receive a floating-point number from the input stream.
      static_cast<void>(is >> v);

      // Subsequently make a fixed-point object from it.
      f = v;

      return is;
    }
    #endif // !SOFT_DOUBLE_DISABLE_IOSTREAM

    friend constexpr auto (isfinite)(soft_double x) -> bool { return ((!(isnan)(x)) && (!(isinf)(x))); }
    friend constexpr auto (isnan)   (soft_double x) -> bool { return  (x.my_value == my_value_quiet_NaN().my_value); }
    friend constexpr auto (isinf)   (soft_double x) -> bool { return ((x.my_value & my_value_infinity().my_value) == my_value_infinity().my_value); }

    friend constexpr auto abs (soft_double x) -> soft_double { return soft_double { static_cast<std::uint64_t>(x.my_value & static_cast<std::uint64_t>(UINT64_C(0x7FFFFFFFFFFFFFFF))), detail::nothing{} }; } // NOLINT(performance-unnecessary-value-param)
    friend constexpr auto fabs(soft_double x) -> soft_double { return soft_double { static_cast<std::uint64_t>(x.my_value & static_cast<std::uint64_t>(UINT64_C(0x7FFFFFFFFFFFFFFF))), detail::nothing{} }; } // NOLINT(performance-unnecessary-value-param)

    friend constexpr auto fmod(soft_double v1, soft_double v2) -> soft_double // NOLINT(performance-unnecessary-value-param)
    {
      const auto n_mod = ((v1 < static_cast<int>(INT8_C(0))) ? ceil(v1 / v2) : floor(v1 / v2));

      return v1 - (n_mod * v2);
    }

    friend constexpr auto sqrt(soft_double x) -> soft_double { return soft_double { f64_sqrt(x.my_value), detail::nothing{} }; } // NOLINT(performance-unnecessary-value-param)

    friend constexpr auto frexp(soft_double x, int* expptr) -> soft_double // NOLINT(performance-unnecessary-value-param)
    {
      const auto expA =
        static_cast<std::int16_t>
        (
          detail::expF64UI(x.my_value) - static_cast<std::int16_t>(INT16_C(0x3FE))
        );

      if(expptr != nullptr)
      {
        *expptr = static_cast<int>(expA);
      }

      return
        soft_double
        {
          detail::packToF64UI
          (
            detail::signF64UI(x.my_value),
            static_cast<std::int16_t>(INT16_C(0x3FE)),
            detail::fracF64UI(x.my_value)
          ),
          detail::nothing{}
        };
    }

    friend constexpr auto ldexp(soft_double x, int expval) -> soft_double // NOLINT(performance-unnecessary-value-param)
    {
      return
        soft_double
        {
          static_cast<std::uint64_t>
          (
              static_cast<std::uint64_t>
              (
                x.my_value & static_cast<std::uint64_t>(~(static_cast<std::uint64_t>(UINT64_C(0x7FF)) << static_cast<unsigned>(UINT8_C(52))))
              )
            | static_cast<std::uint64_t>
              (
                static_cast<std::int32_t>
                (
                    static_cast<std::int32_t>(detail::expF64UI(x.my_value))
                  + static_cast<std::int32_t>(expval)
                )
              ) << static_cast<unsigned>(UINT8_C(52))
          ),
          detail::nothing{}
        };
    }

    friend constexpr auto floor(soft_double x) -> soft_double;
    friend constexpr auto ceil (soft_double x) -> soft_double;
    friend constexpr auto exp  (soft_double x) -> soft_double;
    friend constexpr auto log  (soft_double x) -> soft_double;

    template<typename UnsignedIntegralType,
             typename std::enable_if<(   std::is_integral<UnsignedIntegralType>::value
                                      && std::is_unsigned<UnsignedIntegralType>::value)>::type const*>
    friend constexpr auto pow(soft_double x, UnsignedIntegralType u) -> soft_double // NOLINT(performance-unnecessary-value-param)
    {
      auto result = soft_double { };

      if     (u == static_cast<UnsignedIntegralType>(UINT8_C(0))) { result = soft_double::my_value_one(); }
      else if(u == static_cast<UnsignedIntegralType>(UINT8_C(1))) { result = x; }
      else if(u == static_cast<UnsignedIntegralType>(UINT8_C(2))) { result = x * x; }
      else
      {
        result = soft_double::my_value_one();

        auto y = x;

        for(auto p_local  = static_cast<std::uint32_t>(u);
                 p_local != static_cast<std::uint32_t>(UINT8_C(0));
                 p_local  = static_cast<std::uint32_t>(p_local >> static_cast<unsigned>(UINT8_C(1))))
        {
          const auto bit_is_set =
            (static_cast<std::uint_fast8_t>(p_local & static_cast<std::uint_fast8_t>(UINT8_C(1))) != static_cast<std::uint_fast8_t>(UINT8_C(0)));

          if(bit_is_set)
          {
            result *= y;
          }

          y *= y;
        }
      }

      return result;
    }

    template<typename SignedIntegralType,
             typename std::enable_if<(   std::is_integral<SignedIntegralType>::value
                                      && std::is_signed  <SignedIntegralType>::value)>::type const*>
    friend constexpr auto pow(soft_double x, SignedIntegralType n) -> soft_double
    {
      auto result = soft_double { };

      if     (n <  static_cast<SignedIntegralType>(INT8_C(0))) { result = soft_double::my_value_one() / pow(x, static_cast<std::make_unsigned_t<SignedIntegralType>>(-n)); }
      else if(n == static_cast<SignedIntegralType>(INT8_C(0))) { result = soft_double::my_value_one(); }
      else if(n == static_cast<SignedIntegralType>(INT8_C(1))) { result = x; }
      else if(n == static_cast<SignedIntegralType>(INT8_C(2))) { result = x * x; }
      else
      {
        result = soft_double::my_value_one();

        auto y = x;

        for(auto p_local  = static_cast<std::uint32_t>(n);
                 p_local != static_cast<std::uint32_t>(UINT8_C(0));
                 p_local  = static_cast<std::uint32_t>(p_local >> static_cast<unsigned>(UINT8_C(1))))
        {
          const auto bit_zero_is_set =
            (static_cast<std::uint_fast8_t>(p_local & static_cast<std::uint_fast8_t>(UINT8_C(1))) != static_cast<std::uint_fast8_t>(UINT8_C(0)));

          if(bit_zero_is_set)
          {
            result *= y;
          }

          y *= y;
        }
      }

      return result;
    } // LCOV_EXCL_LINE
    // Bogus report from LCOV on certain ditros

    friend constexpr auto sin(soft_double x) -> soft_double;
    friend constexpr auto cos(soft_double x) -> soft_double;
    friend constexpr auto tan(soft_double x) -> soft_double;

    friend constexpr auto operator+(const soft_double& a, const soft_double& b) -> soft_double;
    friend constexpr auto operator-(const soft_double& a, const soft_double& b) -> soft_double;
    friend constexpr auto operator*(const soft_double& a, const soft_double& b) -> soft_double;
    friend constexpr auto operator/(const soft_double& a, const soft_double& b) -> soft_double;

    template<typename UnsignedIntegralType> friend constexpr auto operator+(const soft_double& u, UnsignedIntegralType n) -> typename std::enable_if<std::is_integral<UnsignedIntegralType>::value && std::is_unsigned<UnsignedIntegralType>::value, soft_double>::type { return soft_double(u) += soft_double(n); }
    template<typename UnsignedIntegralType> friend constexpr auto operator-(const soft_double& u, UnsignedIntegralType n) -> typename std::enable_if<std::is_integral<UnsignedIntegralType>::value && std::is_unsigned<UnsignedIntegralType>::value, soft_double>::type { return soft_double(u) -= soft_double(n); }
    template<typename UnsignedIntegralType> friend constexpr auto operator*(const soft_double& u, UnsignedIntegralType n) -> typename std::enable_if<std::is_integral<UnsignedIntegralType>::value && std::is_unsigned<UnsignedIntegralType>::value, soft_double>::type { return soft_double(u) *= soft_double(n); }
    template<typename UnsignedIntegralType> friend constexpr auto operator/(const soft_double& u, UnsignedIntegralType n) -> typename std::enable_if<std::is_integral<UnsignedIntegralType>::value && std::is_unsigned<UnsignedIntegralType>::value, soft_double>::type { return soft_double(u) /= soft_double(n); }

    template<typename UnsignedIntegralType> friend constexpr auto operator+(UnsignedIntegralType n, const soft_double& u) -> typename std::enable_if<std::is_integral<UnsignedIntegralType>::value && std::is_unsigned<UnsignedIntegralType>::value, soft_double>::type { return soft_double(n) += u; }
    template<typename UnsignedIntegralType> friend constexpr auto operator-(UnsignedIntegralType n, const soft_double& u) -> typename std::enable_if<std::is_integral<UnsignedIntegralType>::value && std::is_unsigned<UnsignedIntegralType>::value, soft_double>::type { return soft_double(n) -= u; }
    template<typename UnsignedIntegralType> friend constexpr auto operator*(UnsignedIntegralType n, const soft_double& u) -> typename std::enable_if<std::is_integral<UnsignedIntegralType>::value && std::is_unsigned<UnsignedIntegralType>::value, soft_double>::type { return soft_double(n) *= u; }
    template<typename UnsignedIntegralType> friend constexpr auto operator/(UnsignedIntegralType n, const soft_double& u) -> typename std::enable_if<std::is_integral<UnsignedIntegralType>::value && std::is_unsigned<UnsignedIntegralType>::value, soft_double>::type { return soft_double(n) /= u; }

    template<typename SignedIntegralType> friend constexpr auto operator+(const soft_double& u, SignedIntegralType n) -> typename std::enable_if<std::is_integral<SignedIntegralType>::value && std::is_signed<SignedIntegralType>::value, soft_double>::type { return soft_double(u) += soft_double(n); }
    template<typename SignedIntegralType> friend constexpr auto operator-(const soft_double& u, SignedIntegralType n) -> typename std::enable_if<std::is_integral<SignedIntegralType>::value && std::is_signed<SignedIntegralType>::value, soft_double>::type { return soft_double(u) -= soft_double(n); }
    template<typename SignedIntegralType> friend constexpr auto operator*(const soft_double& u, SignedIntegralType n) -> typename std::enable_if<std::is_integral<SignedIntegralType>::value && std::is_signed<SignedIntegralType>::value, soft_double>::type { return soft_double(u) *= soft_double(n); }
    template<typename SignedIntegralType> friend constexpr auto operator/(const soft_double& u, SignedIntegralType n) -> typename std::enable_if<std::is_integral<SignedIntegralType>::value && std::is_signed<SignedIntegralType>::value, soft_double>::type { return soft_double(u) /= soft_double(n); }

    template<typename SignedIntegralType> friend constexpr auto operator+(SignedIntegralType n, const soft_double& u) -> typename std::enable_if<std::is_integral<SignedIntegralType>::value && std::is_signed<SignedIntegralType>::value, soft_double>::type { return soft_double(n) += u; }
    template<typename SignedIntegralType> friend constexpr auto operator-(SignedIntegralType n, const soft_double& u) -> typename std::enable_if<std::is_integral<SignedIntegralType>::value && std::is_signed<SignedIntegralType>::value, soft_double>::type { return soft_double(n) -= u; }
    template<typename SignedIntegralType> friend constexpr auto operator*(SignedIntegralType n, const soft_double& u) -> typename std::enable_if<std::is_integral<SignedIntegralType>::value && std::is_signed<SignedIntegralType>::value, soft_double>::type { return soft_double(n) *= u; }
    template<typename SignedIntegralType> friend constexpr auto operator/(SignedIntegralType n, const soft_double& u) -> typename std::enable_if<std::is_integral<SignedIntegralType>::value && std::is_signed<SignedIntegralType>::value, soft_double>::type { return soft_double(n) /= u; }

    friend constexpr auto operator< (const soft_double& a, const soft_double& b) -> bool;
    friend constexpr auto operator<=(const soft_double& a, const soft_double& b) -> bool;
    friend constexpr auto operator==(const soft_double& a, const soft_double& b) -> bool;

    template<typename UnsignedIntegralType> friend constexpr auto operator< (const soft_double& a, UnsignedIntegralType u) -> typename std::enable_if<std::is_integral<UnsignedIntegralType>::value && std::is_unsigned<UnsignedIntegralType>::value, bool>::type { return soft_double::my_lt(a, soft_double(u)); }
    template<typename UnsignedIntegralType> friend constexpr auto operator<=(const soft_double& a, UnsignedIntegralType u) -> typename std::enable_if<std::is_integral<UnsignedIntegralType>::value && std::is_unsigned<UnsignedIntegralType>::value, bool>::type { return soft_double::my_le(a, soft_double(u)); }
    template<typename UnsignedIntegralType> friend constexpr auto operator==(const soft_double& a, UnsignedIntegralType u) -> typename std::enable_if<std::is_integral<UnsignedIntegralType>::value && std::is_unsigned<UnsignedIntegralType>::value, bool>::type { return  (a.my_value == soft_double(u).my_value); }
    template<typename UnsignedIntegralType> friend constexpr auto operator!=(const soft_double& a, UnsignedIntegralType u) -> typename std::enable_if<std::is_integral<UnsignedIntegralType>::value && std::is_unsigned<UnsignedIntegralType>::value, bool>::type { return (!(a == soft_double(u))); }
    template<typename UnsignedIntegralType> friend constexpr auto operator>=(const soft_double& a, UnsignedIntegralType u) -> typename std::enable_if<std::is_integral<UnsignedIntegralType>::value && std::is_unsigned<UnsignedIntegralType>::value, bool>::type { return (!(a <  soft_double(u))); }
    template<typename UnsignedIntegralType> friend constexpr auto operator> (const soft_double& a, UnsignedIntegralType u) -> typename std::enable_if<std::is_integral<UnsignedIntegralType>::value && std::is_unsigned<UnsignedIntegralType>::value, bool>::type { return (!(a <= soft_double(u))); }

    template<typename UnsignedIntegralType> friend constexpr auto operator< (UnsignedIntegralType u, const soft_double& a) -> typename std::enable_if<std::is_integral<UnsignedIntegralType>::value && std::is_unsigned<UnsignedIntegralType>::value, bool>::type { return soft_double::my_lt(soft_double(u), a); }
    template<typename UnsignedIntegralType> friend constexpr auto operator<=(UnsignedIntegralType u, const soft_double& a) -> typename std::enable_if<std::is_integral<UnsignedIntegralType>::value && std::is_unsigned<UnsignedIntegralType>::value, bool>::type { return soft_double::my_le(soft_double(u), a); }
    template<typename UnsignedIntegralType> friend constexpr auto operator==(UnsignedIntegralType u, const soft_double& a) -> typename std::enable_if<std::is_integral<UnsignedIntegralType>::value && std::is_unsigned<UnsignedIntegralType>::value, bool>::type { return  (soft_double(u).my_value == a.my_value); }
    template<typename UnsignedIntegralType> friend constexpr auto operator!=(UnsignedIntegralType u, const soft_double& a) -> typename std::enable_if<std::is_integral<UnsignedIntegralType>::value && std::is_unsigned<UnsignedIntegralType>::value, bool>::type { return (!(soft_double(u) == a)); }
    template<typename UnsignedIntegralType> friend constexpr auto operator>=(UnsignedIntegralType u, const soft_double& a) -> typename std::enable_if<std::is_integral<UnsignedIntegralType>::value && std::is_unsigned<UnsignedIntegralType>::value, bool>::type { return (!(soft_double(u) <  a)); }
    template<typename UnsignedIntegralType> friend constexpr auto operator> (UnsignedIntegralType u, const soft_double& a) -> typename std::enable_if<std::is_integral<UnsignedIntegralType>::value && std::is_unsigned<UnsignedIntegralType>::value, bool>::type { return (!(soft_double(u) <= a)); }

    template<typename SignedIntegralType> friend constexpr auto operator< (const soft_double& a, SignedIntegralType n) -> typename std::enable_if<std::is_integral<SignedIntegralType>::value && std::is_signed<SignedIntegralType>::value, bool>::type { return soft_double::my_lt(a, soft_double(n)); }
    template<typename SignedIntegralType> friend constexpr auto operator<=(const soft_double& a, SignedIntegralType n) -> typename std::enable_if<std::is_integral<SignedIntegralType>::value && std::is_signed<SignedIntegralType>::value, bool>::type { return soft_double::my_le(a, soft_double(n)); }
    template<typename SignedIntegralType> friend constexpr auto operator==(const soft_double& a, SignedIntegralType n) -> typename std::enable_if<std::is_integral<SignedIntegralType>::value && std::is_signed<SignedIntegralType>::value, bool>::type { return  (a.my_value == soft_double(n).my_value); }
    template<typename SignedIntegralType> friend constexpr auto operator!=(const soft_double& a, SignedIntegralType n) -> typename std::enable_if<std::is_integral<SignedIntegralType>::value && std::is_signed<SignedIntegralType>::value, bool>::type { return (!(a == soft_double(n))); }
    template<typename SignedIntegralType> friend constexpr auto operator>=(const soft_double& a, SignedIntegralType n) -> typename std::enable_if<std::is_integral<SignedIntegralType>::value && std::is_signed<SignedIntegralType>::value, bool>::type { return (!(a <  soft_double(n))); }
    template<typename SignedIntegralType> friend constexpr auto operator> (const soft_double& a, SignedIntegralType n) -> typename std::enable_if<std::is_integral<SignedIntegralType>::value && std::is_signed<SignedIntegralType>::value, bool>::type { return (!(a <= soft_double(n))); }

    template<typename SignedIntegralType> friend constexpr auto operator< (SignedIntegralType n, const soft_double& a) -> typename std::enable_if<std::is_integral<SignedIntegralType>::value && std::is_signed<SignedIntegralType>::value, bool>::type { return soft_double::my_lt(soft_double(n), a); }
    template<typename SignedIntegralType> friend constexpr auto operator<=(SignedIntegralType n, const soft_double& a) -> typename std::enable_if<std::is_integral<SignedIntegralType>::value && std::is_signed<SignedIntegralType>::value, bool>::type { return soft_double::my_le(soft_double(n), a); }
    template<typename SignedIntegralType> friend constexpr auto operator==(SignedIntegralType n, const soft_double& a) -> typename std::enable_if<std::is_integral<SignedIntegralType>::value && std::is_signed<SignedIntegralType>::value, bool>::type { return  (soft_double(n).my_value == a.my_value); }
    template<typename SignedIntegralType> friend constexpr auto operator!=(SignedIntegralType n, const soft_double& a) -> typename std::enable_if<std::is_integral<SignedIntegralType>::value && std::is_signed<SignedIntegralType>::value, bool>::type { return (!(soft_double(n) == a)); }
    template<typename SignedIntegralType> friend constexpr auto operator>=(SignedIntegralType n, const soft_double& a) -> typename std::enable_if<std::is_integral<SignedIntegralType>::value && std::is_signed<SignedIntegralType>::value, bool>::type { return (!(soft_double(n) <  a)); }
    template<typename SignedIntegralType> friend constexpr auto operator> (SignedIntegralType n, const soft_double& a) -> typename std::enable_if<std::is_integral<SignedIntegralType>::value && std::is_signed<SignedIntegralType>::value, bool>::type { return (!(soft_double(n) <= a)); }

    friend constexpr auto operator< (const soft_double& a, float f) -> bool;
    friend constexpr auto operator<=(const soft_double& a, float f) -> bool;
    friend constexpr auto operator==(const soft_double& a, float f) -> bool;

    friend constexpr auto operator< (float f, const soft_double& a) -> bool;
    friend constexpr auto operator<=(float f, const soft_double& a) -> bool;
    friend constexpr auto operator==(float f, const soft_double& a) -> bool;

    friend constexpr auto operator< (const soft_double& a, double f) -> bool;
    friend constexpr auto operator<=(const soft_double& a, double f) -> bool;
    friend constexpr auto operator==(const soft_double& a, double f) -> bool;

    friend constexpr auto operator< (double f, const soft_double& a) -> bool;
    friend constexpr auto operator<=(double f, const soft_double& a) -> bool;
    friend constexpr auto operator==(double f, const soft_double& a) -> bool;

    friend constexpr auto operator< (const soft_double& a, long double f) -> bool;
    friend constexpr auto operator<=(const soft_double& a, long double f) -> bool;
    friend constexpr auto operator==(const soft_double& a, long double f) -> bool;

    friend constexpr auto operator< (long double f, const soft_double& a) -> bool;
    friend constexpr auto operator<=(long double f, const soft_double& a) -> bool;
    friend constexpr auto operator==(long double f, const soft_double& a) -> bool;
  };

  constexpr auto operator+(const soft_double& a, const soft_double& b) -> soft_double { return soft_double { soft_double::f64_add(a.my_value, b.my_value), detail::nothing{} }; }
  constexpr auto operator-(const soft_double& a, const soft_double& b) -> soft_double { return soft_double { soft_double::f64_sub(a.my_value, b.my_value), detail::nothing{} }; }
  constexpr auto operator*(const soft_double& a, const soft_double& b) -> soft_double { return soft_double { soft_double::f64_mul(a.my_value, b.my_value), detail::nothing{} }; }
  constexpr auto operator/(const soft_double& a, const soft_double& b) -> soft_double { return soft_double { soft_double::f64_div(a.my_value, b.my_value), detail::nothing{} }; }

  constexpr auto operator+(const soft_double& u, float f) -> soft_double { return soft_double(u) += soft_double(f); }
  constexpr auto operator-(const soft_double& u, float f) -> soft_double { return soft_double(u) -= soft_double(f); }
  constexpr auto operator*(const soft_double& u, float f) -> soft_double { return soft_double(u) *= soft_double(f); }
  constexpr auto operator/(const soft_double& u, float f) -> soft_double { return soft_double(u) /= soft_double(f); }

  constexpr auto operator+(float f, const soft_double& u) -> soft_double { return soft_double(f) += u; }
  constexpr auto operator-(float f, const soft_double& u) -> soft_double { return soft_double(f) -= u; }
  constexpr auto operator*(float f, const soft_double& u) -> soft_double { return soft_double(f) *= u; }
  constexpr auto operator/(float f, const soft_double& u) -> soft_double { return soft_double(f) /= u; }

  constexpr auto operator+(const soft_double& u, double f) -> soft_double { return soft_double(u) += soft_double(f); }
  constexpr auto operator-(const soft_double& u, double f) -> soft_double { return soft_double(u) -= soft_double(f); }
  constexpr auto operator*(const soft_double& u, double f) -> soft_double { return soft_double(u) *= soft_double(f); }
  constexpr auto operator/(const soft_double& u, double f) -> soft_double { return soft_double(u) /= soft_double(f); }

  constexpr auto operator+(double f, const soft_double& u) -> soft_double { return soft_double(f) += u; }
  constexpr auto operator-(double f, const soft_double& u) -> soft_double { return soft_double(f) -= u; }
  constexpr auto operator*(double f, const soft_double& u) -> soft_double { return soft_double(f) *= u; }
  constexpr auto operator/(double f, const soft_double& u) -> soft_double { return soft_double(f) /= u; }

  constexpr auto operator+(const soft_double& u, long double f) -> soft_double { return soft_double(u) += soft_double(static_cast<double>(f)); }
  constexpr auto operator-(const soft_double& u, long double f) -> soft_double { return soft_double(u) -= soft_double(static_cast<double>(f)); }
  constexpr auto operator*(const soft_double& u, long double f) -> soft_double { return soft_double(u) *= soft_double(static_cast<double>(f)); }
  constexpr auto operator/(const soft_double& u, long double f) -> soft_double { return soft_double(u) /= soft_double(static_cast<double>(f)); }

  constexpr auto operator+(long double f, const soft_double& u) -> soft_double { return soft_double(static_cast<double>(f)) += u; }
  constexpr auto operator-(long double f, const soft_double& u) -> soft_double { return soft_double(static_cast<double>(f)) -= u; }
  constexpr auto operator*(long double f, const soft_double& u) -> soft_double { return soft_double(static_cast<double>(f)) *= u; }
  constexpr auto operator/(long double f, const soft_double& u) -> soft_double { return soft_double(static_cast<double>(f)) /= u; }

  constexpr auto operator< (const soft_double& a, const soft_double& b) -> bool { return soft_double::my_lt(a, b); }
  constexpr auto operator<=(const soft_double& a, const soft_double& b) -> bool { return soft_double::my_le(a, b); }
  constexpr auto operator==(const soft_double& a, const soft_double& b) -> bool { return (a.my_value == b.my_value); }
  constexpr auto operator!=(const soft_double& a, const soft_double& b) -> bool { return (!(a == b)); }
  constexpr auto operator>=(const soft_double& a, const soft_double& b) -> bool { return (!(a <  b)); }
  constexpr auto operator> (const soft_double& a, const soft_double& b) -> bool { return (!(a <= b)); }

  constexpr auto operator< (const soft_double& a, float f) -> bool { return soft_double::my_lt(a, soft_double(f)); }
  constexpr auto operator<=(const soft_double& a, float f) -> bool { return soft_double::my_le(a, soft_double(f)); }
  constexpr auto operator==(const soft_double& a, float f) -> bool { return  (a.my_value == soft_double(f).my_value); }
  constexpr auto operator!=(const soft_double& a, float f) -> bool { return (!(a == soft_double(f))); }
  constexpr auto operator>=(const soft_double& a, float f) -> bool { return (!(a <  soft_double(f))); }
  constexpr auto operator> (const soft_double& a, float f) -> bool { return (!(a <= soft_double(f))); }

  constexpr auto operator< (float f, const soft_double& a) -> bool { return soft_double::my_lt(soft_double(f), a); }
  constexpr auto operator<=(float f, const soft_double& a) -> bool { return soft_double::my_le(soft_double(f), a); }
  constexpr auto operator==(float f, const soft_double& a) -> bool { return  (soft_double(f).my_value == a.my_value); }
  constexpr auto operator!=(float f, const soft_double& a) -> bool { return (!(soft_double(f) == a)); }
  constexpr auto operator>=(float f, const soft_double& a) -> bool { return (!(soft_double(f) <  a)); }
  constexpr auto operator> (float f, const soft_double& a) -> bool { return (!(soft_double(f) <= a)); }

  constexpr auto operator< (const soft_double& a, double f) -> bool { return soft_double::my_lt(a, soft_double(f)); }
  constexpr auto operator<=(const soft_double& a, double f) -> bool { return soft_double::my_le(a, soft_double(f)); }
  constexpr auto operator==(const soft_double& a, double f) -> bool { return  (a.my_value == soft_double(f).my_value); }
  constexpr auto operator!=(const soft_double& a, double f) -> bool { return (!(a == soft_double(f))); }
  constexpr auto operator>=(const soft_double& a, double f) -> bool { return (!(a <  soft_double(f))); }
  constexpr auto operator> (const soft_double& a, double f) -> bool { return (!(a <= soft_double(f))); }

  constexpr auto operator< (double f, const soft_double& a) -> bool { return soft_double::my_lt(soft_double(f), a); }
  constexpr auto operator<=(double f, const soft_double& a) -> bool { return soft_double::my_le(soft_double(f), a); }
  constexpr auto operator==(double f, const soft_double& a) -> bool { return  (soft_double(f).my_value == a.my_value); }
  constexpr auto operator!=(double f, const soft_double& a) -> bool { return (!(soft_double(f) == a)); }
  constexpr auto operator>=(double f, const soft_double& a) -> bool { return (!(soft_double(f) <  a)); }
  constexpr auto operator> (double f, const soft_double& a) -> bool { return (!(soft_double(f) <= a)); }

  constexpr auto operator< (const soft_double& a, long double f) -> bool { return soft_double::my_lt(a, soft_double(static_cast<double>(f))); }
  constexpr auto operator<=(const soft_double& a, long double f) -> bool { return soft_double::my_le(a, soft_double(static_cast<double>(f))); }
  constexpr auto operator==(const soft_double& a, long double f) -> bool { return  (a.my_value == soft_double(static_cast<double>(f)).my_value); }
  constexpr auto operator!=(const soft_double& a, long double f) -> bool { return (!(a == soft_double(static_cast<double>(f)))); }
  constexpr auto operator>=(const soft_double& a, long double f) -> bool { return (!(a <  soft_double(static_cast<double>(f)))); }
  constexpr auto operator> (const soft_double& a, long double f) -> bool { return (!(a <= soft_double(static_cast<double>(f)))); }

  constexpr auto operator< (long double f, const soft_double& a) -> bool { return soft_double::my_lt(soft_double(static_cast<double>(f)), a); }
  constexpr auto operator<=(long double f, const soft_double& a) -> bool { return soft_double::my_le(soft_double(static_cast<double>(f)), a); }
  constexpr auto operator==(long double f, const soft_double& a) -> bool { return  (soft_double(static_cast<double>(f)).my_value == a.my_value); }
  constexpr auto operator!=(long double f, const soft_double& a) -> bool { return (!(soft_double(static_cast<double>(f)) == a)); }
  constexpr auto operator>=(long double f, const soft_double& a) -> bool { return (!(soft_double(static_cast<double>(f)) <  a)); }
  constexpr auto operator> (long double f, const soft_double& a) -> bool { return (!(soft_double(static_cast<double>(f)) <= a)); }

  namespace detail {

  constexpr auto sin_pade(soft_double x) -> soft_double // NOLINT(performance-unnecessary-value-param)
  {
    // PadeApproximant[Sin[x], {x, 0, {7,7}}]
    // FullSimplify[%]

    //    x (11511339840 - 1640635920 x^2 + 52785432 x^4 - 479249 x^6)
    // / (7 ( 1644477120  +  39702960 x^2 +   453960 x^4 +   2623 x^6))

    const soft_double coef_sin_top_0(static_cast<std::uint64_t>(UINT64_C(+11511339840)));
    const soft_double coef_sin_top_1(static_cast<std::int32_t> (INT32_C (-1640635920)));
    const soft_double coef_sin_top_2(static_cast<std::uint32_t>(UINT32_C(+52785432)));
    const soft_double coef_sin_top_3(static_cast<std::int32_t> (INT32_C (-479249)));

    const soft_double coef_sin_bot_0(static_cast<std::uint32_t>(UINT32_C(+1644477120)));
    const soft_double coef_sin_bot_1(static_cast<std::uint32_t>(UINT32_C(+39702960)));
    const soft_double coef_sin_bot_2(static_cast<std::uint32_t>(UINT32_C(+453960)));
    const soft_double coef_sin_bot_3(static_cast<std::uint16_t>(UINT16_C(+2623)));

    const soft_double x2(x * x);

    const soft_double top = ((((     + coef_sin_top_3)
                                * x2 + coef_sin_top_2)
                                * x2 + coef_sin_top_1)
                                * x2 + coef_sin_top_0);

    const soft_double bot = ((((     + coef_sin_bot_3)
                                * x2 + coef_sin_bot_2)
                                * x2 + coef_sin_bot_1)
                                * x2 + coef_sin_bot_0);

    return (x * top) / (bot * static_cast<int>(INT8_C(7)));
  }

  constexpr auto cos_pade(soft_double x) -> soft_double // NOLINT(performance-unnecessary-value-param)
  {
    // PadeApproximant[Cos[x] - 1, {x, 0, {8,6}}]
    // FullSimplify[%]

    //   (x^2 (-5491886400 + 346666320 x^2 - 7038360 x^4 + 45469 x^6))
    // / (24  (  457657200 +   9249240 x^2 +   86030 x^4 +   389 x^6))

    const soft_double coef_cos_top_0(static_cast<std::int64_t> (INT64_C (-5491886400)));
    const soft_double coef_cos_top_1(static_cast<std::uint32_t>(UINT32_C(+346666320)));
    const soft_double coef_cos_top_2(static_cast<std::int32_t> (INT32_C (-7038360)));
    const soft_double coef_cos_top_3(static_cast<std::uint16_t>(UINT16_C(+45469)));

    const soft_double coef_cos_bot_0(static_cast<std::uint32_t>(UINT32_C(457657200)));
    const soft_double coef_cos_bot_1(static_cast<std::uint32_t>(UINT32_C(9249240)));
    const soft_double coef_cos_bot_2(static_cast<std::uint32_t>(UINT32_C(86030)));
    const soft_double coef_cos_bot_3(static_cast<std::uint16_t>(UINT16_C(389)));

    const soft_double x2(x * x);

    const soft_double top = ((((     + coef_cos_top_3)
                                * x2 + coef_cos_top_2)
                                * x2 + coef_cos_top_1)
                                * x2 + coef_cos_top_0);

    const soft_double bot = ((((     + coef_cos_bot_3)
                                * x2 + coef_cos_bot_2)
                                * x2 + coef_cos_bot_1)
                                * x2 + coef_cos_bot_0);

    return soft_double::my_value_one() + ((x2 * top) / (bot * static_cast<int>(INT8_C(24))));
  }

  } // namespace detail

  constexpr auto sin(soft_double x) -> soft_double // NOLINT(misc-no-recursion)
  {
    auto s = soft_double { };

    if(x < static_cast<int>(INT8_C(0)))
    {
      s = -sin(-x);
    }
    else if(x > static_cast<int>(INT8_C(0)))
    {
      // Remove even multiples of pi.

      auto b_negate_sin = false;

      const auto n_pi = static_cast<std::uint32_t>(x / soft_double::my_value_pi());

      if(n_pi != static_cast<std::uint32_t>(UINT8_C(0)))
      {
        x -= (soft_double::my_value_pi() * n_pi);

        if(static_cast<std::uint_fast8_t>(n_pi % static_cast<std::uint_fast8_t>(UINT8_C(2))) != static_cast<std::uint_fast8_t>(UINT8_C(0)))
        {
          b_negate_sin = (!b_negate_sin);
        }
      }

      // Check if the reduced argument is very close to pi/2.
      const soft_double delta_pi_half  = soft_double::my_value_pi_half() - x;
      const bool        b_near_pi_half = (fabs(delta_pi_half) < soft_double(static_cast<std::uint64_t>(UINT64_C(0x3FE0C152382D7366)), detail::nothing{}));

      if(b_near_pi_half)
      {
        // PadeApproximant[Hypergeometric0F1[1/2, -(dx^2)/4], {dx, 0, {6, 6}}]
        // FullSimplify[%]
        //   (39251520 - 18471600 dx^2 + 1075032 dx^4 - 14615 dx^6)
        // / (39251520 +  1154160 dx^2 +   16632 dx^4 +   127 dx^6)

        const soft_double coef_top_0(static_cast<std::uint32_t>(UINT32_C(+39251520)));
        const soft_double coef_top_1(static_cast<std::int32_t> (INT32_C (-18471600)));
        const soft_double coef_top_2(static_cast<std::uint32_t>(UINT32_C(+1075032)));
        const soft_double coef_top_3(static_cast<std::int16_t> (INT16_C (-14615)));

        const soft_double coef_bot_0(static_cast<std::uint32_t>(UINT32_C(39251520)));
        const soft_double coef_bot_1(static_cast<std::uint32_t>(UINT32_C(1154160)));
        const soft_double coef_bot_2(static_cast<std::uint16_t>(UINT16_C(16632)));
        const soft_double coef_bot_3(static_cast<std::uint8_t> (UINT8_C (127)));

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

        if(x > soft_double(static_cast<std::uint64_t>(UINT64_C(0x3FE0C152382D7366)), detail::nothing{}))
        {
          // x is larger than pi/6, scale by 9.
          x /= static_cast<unsigned>(UINT8_C(9));

          s = detail::sin_pade(x);

          s = (s * static_cast<unsigned>(UINT8_C(3))) - (((s * s) * s) * static_cast<unsigned>(UINT8_C(4)));
          s = (s * static_cast<unsigned>(UINT8_C(3))) - (((s * s) * s) * static_cast<unsigned>(UINT8_C(4)));
        }
        else if(x > soft_double(static_cast<std::uint64_t>(UINT64_C(0x3FC657184AE74487)), detail::nothing{}))
        {
          // x is larger than pi/18, scale by 3.
          x /= static_cast<unsigned>(UINT8_C(3));

          s = detail::sin_pade(x);

          s = (s * static_cast<unsigned>(UINT8_C(3))) - (((s * s) * s) * static_cast<unsigned>(UINT8_C(4)));
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
      s = static_cast<int>(INT8_C(0));
    }

    return s;
  }

  constexpr auto cos(soft_double x) -> soft_double // NOLINT(misc-no-recursion)
  {
    auto c = soft_double { };

    if(x < static_cast<int>(INT8_C(0)))
    {
      c = cos(-x);
    }
    else if(x > static_cast<int>(INT8_C(0)))
    {
      // Remove even multiples of pi.

      auto b_negate_cos = false;

      const auto n_pi = static_cast<std::uint32_t>(x / soft_double::my_value_pi());

      if(n_pi != static_cast<std::uint32_t>(UINT8_C(0)))
      {
        x -= (soft_double::my_value_pi() * n_pi);

        if(static_cast<std::uint_fast8_t>(n_pi % static_cast<std::uint_fast8_t>(UINT8_C(2))) != static_cast<std::uint_fast8_t>(UINT8_C(0)))
        {
          b_negate_cos = (!b_negate_cos);
        }
      }

      // Check if the reduced argument is very close to pi/2.
      const soft_double delta_pi_half  = soft_double::my_value_pi_half() - x;
      const bool        b_near_pi_half = (fabs(delta_pi_half) < soft_double(static_cast<std::uint64_t>(UINT64_C(0x3FE0C152382D7366)), detail::nothing{}));

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

        if(x > soft_double(static_cast<std::uint64_t>(UINT64_C(0x3FE0C152382D7366)), detail::nothing{}))
        {
          // x is larger than pi/6, scale by 9.
          x /= static_cast<unsigned>(UINT8_C(9));

          c = detail::cos_pade(x);

          c = (((c * c) * c) * static_cast<unsigned>(UINT8_C(4))) - (c * static_cast<unsigned>(UINT8_C(3)));
          c = (((c * c) * c) * static_cast<unsigned>(UINT8_C(4))) - (c * static_cast<unsigned>(UINT8_C(3)));
        }
        else if(x > soft_double(static_cast<std::uint64_t>(UINT64_C(0x3FC657184AE74487)), detail::nothing{}))
        {
          // x is larger than pi/18, scale by 3.
          x /= static_cast<unsigned>(UINT8_C(3));

          c = detail::cos_pade(x);

          c = (((c * c) * c) * static_cast<unsigned>(UINT8_C(4))) - (c * static_cast<unsigned>(UINT8_C(3)));
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

  constexpr auto floor(soft_double x) -> soft_double // NOLINT(performance-unnecessary-value-param)
  {
    auto result = soft_double { };

    if(x < static_cast<int>(INT8_C(0)))
    {
      const auto xn = static_cast<std::int64_t>(x);
      const auto fn = soft_double(xn);

      const auto is_pure_integer = (fn.my_value == x.my_value);

      result =
        (is_pure_integer ? fn : soft_double(static_cast<std::int64_t>(x - soft_double::my_value_one())));
    }
    else
    {
      result = soft_double(static_cast<std::int64_t>(x));
    }

    return result;
  }

  constexpr auto ceil(soft_double x) -> soft_double // NOLINT(performance-unnecessary-value-param)
  {
    auto result = soft_double { };

    if(x < static_cast<int>(INT8_C(0)))
    {
      result = soft_double(static_cast<std::int64_t>(x));
    }
    else
    {
      const auto xn = static_cast<std::int64_t>(x);
      const auto fn = soft_double(xn);

      const auto is_pure_integer = (fn.my_value == x.my_value);

      result =
        (is_pure_integer ? fn : soft_double(static_cast<std::int64_t>(x + soft_double::my_value_one())));
    }

    return result;
  }

  constexpr auto exp(soft_double x) -> soft_double // NOLINT(performance-unnecessary-value-param)
  {
    // PadeApproximant[Exp[x] - 1, {x, 0, {6, 6}}]
    // FullSimplify[%]
    //   (84 x (7920 + 240 x^2 + x^4))
    // / (665280 + x (-332640 + x (75600 + x (-10080 + x (840 + (-42 + x) x)))))

    const auto n = static_cast<int>(x / soft_double::my_value_ln2());

    // Scale the argument such that Exp[x] = Exp[a + n * ln2].
    auto a = x - (n * soft_double::my_value_ln2());

    // Scale the argument yet again with division by 4.
    const auto expA = static_cast<int>(detail::expF64UI(a.my_value) - static_cast<int>(INT8_C(2)));

    a.my_value &= static_cast<std::uint64_t>(~static_cast<std::uint64_t>(static_cast<std::uint64_t>(UINT64_C(0x7FF)) << static_cast<unsigned>(UINT8_C(52))));
    a.my_value |= static_cast<std::uint64_t>(static_cast<std::uint64_t>(expA) << static_cast<unsigned>(UINT8_C(52)));

    const auto a2 = a * a;

    // Use the small-argument Pade approximation having coefficients shown above.
    const soft_double top = static_cast<std::uint_fast8_t>(UINT8_C(84)) * a * (static_cast<std::uint_fast16_t>(UINT16_C(7920)) + (static_cast<std::uint_fast8_t>(UINT8_C(240)) + a2) * a2);
    const soft_double bot = static_cast<std::uint_fast32_t>(UINT32_C(665280)) + a * (static_cast<std::int_fast32_t>(INT32_C(-332640)) + a * (static_cast<std::uint_fast32_t>(UINT32_C(75600)) + a * (static_cast<std::int_fast16_t>(INT16_C(-10080)) + a * (static_cast<std::uint_fast16_t>(UINT16_C(840)) + (static_cast<std::int_fast8_t>(INT8_C(-42)) + a) * a))));

    auto result  = soft_double::my_value_one() + (top / bot);

    result *= result;
    result *= result;

    return ((n != static_cast<int>(INT8_C(0))) ? ldexp(result, n) : result);
  }

  constexpr auto log(soft_double x) -> soft_double // NOLINT(misc-no-recursion,performance-unnecessary-value-param)
  {
    auto result = soft_double { };

    if(x < soft_double::my_value_one())
    {
      result = -log(soft_double::my_value_one() / x);
    }
    else if(x > soft_double::my_value_one())
    {
      // See J.F. Hart et al., "Computer Approximations" (Krieger Publishing 1978),
      // page 111 (with correction) log_e = zP(z^2) / Q(z^2), where the leading z
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
      const auto n =
        static_cast<std::int_fast16_t>
        (
          detail::expF64UI(x.my_value) - static_cast<std::int16_t>(INT16_C(0x3FF))
        );

      const auto val_scaled =
        static_cast<std::uint64_t>
        (
            static_cast<std::uint64_t>
            (
                x.my_value
              & static_cast<std::uint64_t>
                (
                  ~(static_cast<std::uint64_t>(UINT64_C(0x7FF)) << static_cast<unsigned>(UINT8_C(52)))
                )
            )
          |
            static_cast<std::uint64_t>
            (
              static_cast<std::uint64_t>(UINT64_C(0x3FF)) << static_cast<unsigned>(UINT8_C(52))
            )
        );

      const auto a = soft_double { val_scaled, detail::nothing{} };

      const auto z  = (a - static_cast<int>(INT8_C(1))) / (a + static_cast<int>(INT8_C(1)));
      const auto z2 = z * z;

      const soft_double pz2 =  (((((     + soft_double(static_cast<std::uint64_t>(UINT64_C(0xC03C92E6C89EC9E1)), detail::nothing{}))
                                    * z2 + soft_double(static_cast<std::uint64_t>(UINT64_C(0x4078BFE6581C8213)), detail::nothing{}))
                                    * z2 + soft_double(static_cast<std::uint64_t>(UINT64_C(0xC0975FE114047504)), detail::nothing{}))
                                    * z2 + soft_double(static_cast<std::uint64_t>(UINT64_C(0x40A0655C8A1C19C3)), detail::nothing{}))
                                    * z2 + soft_double(static_cast<std::uint64_t>(UINT64_C(0xC08EAA3CA575191A)), detail::nothing{}));

      const soft_double qz2 = ((((((     + soft_double(static_cast<std::uint64_t>(UINT64_C(0x3FF0000000000000)), detail::nothing{}))
                                    * z2 + soft_double(static_cast<std::uint64_t>(UINT64_C(0xC047EBCAB384C2B9)), detail::nothing{}))
                                    * z2 + soft_double(static_cast<std::uint64_t>(UINT64_C(0x40778E5238FAC622)), detail::nothing{}))
                                    * z2 + soft_double(static_cast<std::uint64_t>(UINT64_C(0xC090789C42975D7D)), detail::nothing{}))
                                    * z2 + soft_double(static_cast<std::uint64_t>(UINT64_C(0x4092F38C42908712)), detail::nothing{}))
                                    * z2 + soft_double(static_cast<std::uint64_t>(UINT64_C(0xC07EAA3CA575191C)), detail::nothing{}));

      result  = ((z * pz2) / qz2) + (n * soft_double::my_value_ln2());
    }
    else
    {
      result = soft_double::my_value_zero();
    }

    return result;
  }

  constexpr auto pow(soft_double x, soft_double a) -> soft_double // NOLINT(performance-unnecessary-value-param)
  {
    return exp(a * log(x)); // NOLINT(performance-unnecessary-value-param)
  }

  constexpr auto tan(soft_double x) -> soft_double // NOLINT(performance-unnecessary-value-param)
  {
    return sin(x) / cos(x);
  }

  constexpr auto sinh(soft_double x) -> soft_double // NOLINT(performance-unnecessary-value-param)
  {
    const soft_double ep = exp(x); // NOLINT(performance-unnecessary-value-param)

    return (ep - (soft_double::my_value_one() / ep)) / static_cast<int>(INT8_C(2));
  }

  constexpr auto cosh(soft_double x) -> soft_double // NOLINT(performance-unnecessary-value-param)
  {
    const soft_double ep = exp(x); // NOLINT(performance-unnecessary-value-param)

    return (ep + (soft_double::my_value_one() / ep)) / static_cast<int>(INT8_C(2));
  }

  constexpr auto tanh(soft_double x) -> soft_double // NOLINT(performance-unnecessary-value-param)
  {
    const soft_double ep = exp(x); // NOLINT(performance-unnecessary-value-param)
    const soft_double em = soft_double::my_value_one() / ep;

    return (ep - em) / (ep + em);
  }

  using float64_t = soft_double;

  #if(__cplusplus >= 201703L)
  } // namespace math::softfloat
  #else
  } // namespace softfloat
  } // namespace math
  #endif

  namespace std {

  // Specialization of numeric_limits for soft_double.
  template<>
  SOFT_DOUBLE_NUM_LIMITS_CLASS_TYPE numeric_limits<::math::softfloat::soft_double>
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
    static constexpr int                radix             = static_cast<int>(INT8_C(2));

    static constexpr int                digits            = static_cast<int>(INT8_C(53));
    static constexpr int                digits10          = static_cast<int>(INT8_C(15));
    static constexpr int                max_digits10      = static_cast<int>(INT8_C(17));
    static constexpr int                max_exponent      = static_cast<int>(INT16_C(1024));
    static constexpr int                max_exponent10    = static_cast<int>(INT16_C(308));
    static constexpr int                min_exponent      = static_cast<int>(INT16_C(-1021));
    static constexpr int                min_exponent10    = static_cast<int>(INT16_C(-307));

    static constexpr auto (min)        () noexcept -> math::softfloat::soft_double { return math::softfloat::soft_double::my_value_min(); }
    static constexpr auto (max)        () noexcept -> math::softfloat::soft_double { return math::softfloat::soft_double::my_value_max(); }
    static constexpr auto lowest       () noexcept -> math::softfloat::soft_double { return math::softfloat::soft_double::my_value_lowest(); }
    static constexpr auto epsilon      () noexcept -> math::softfloat::soft_double { return math::softfloat::soft_double::my_value_epsilon(); }
    static constexpr auto round_error  () noexcept -> math::softfloat::soft_double { return math::softfloat::soft_double::my_value_round_error(); }
    static constexpr auto denorm_min   () noexcept -> math::softfloat::soft_double { return math::softfloat::soft_double::my_value_denorm_min(); }
    static constexpr auto infinity     () noexcept -> math::softfloat::soft_double { return math::softfloat::soft_double::my_value_infinity(); }
    static constexpr auto quiet_NaN    () noexcept -> math::softfloat::soft_double { return math::softfloat::soft_double::my_value_quiet_NaN(); }
    static constexpr auto signaling_NaN() noexcept -> math::softfloat::soft_double { return math::softfloat::soft_double::my_value_signaling_NaN(); }
  };

  } // namespace std

#endif // SOFT_DOUBLE_2020_10_27_H
