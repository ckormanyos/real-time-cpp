///////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 1999 - 2021.                 //
//  Distributed under the Boost Software License,                //
//  Version 1.0. (See accompanying file LICENSE_1_0.txt          //
//  or copy at http://www.boost.org/LICENSE_1_0.txt)             //
///////////////////////////////////////////////////////////////////

// This work is also based on an earlier work:
// "Algorithm 910: A Portable C++ Multiple-Precision System for Special-Function Calculations",
// in ACM TOMS, {VOL 37, ISSUE 4, (February 2011)} (C) ACM, 2011. http://doi.acm.org/10.1145/1916461.1916469

// This file implements the class decwide_t and most of its
// basic functions including constructors, binary arithmetic
// operations, comparison operators and more.

#ifndef DECWIDE_T_2004_06_01_H_
  #define DECWIDE_T_2004_06_01_H_

  //#define WIDE_DECIMAL_DISABLE_IOSTREAM
  //#define WIDE_DECIMAL_DISABLE_DYNAMIC_MEMORY_ALLOCATION
  //#define WIDE_DECIMAL_DISABLE_CONSTRUCT_FROM_STRING
  //#define WIDE_DECIMAL_DISABLE_CACHED_CONSTANTS

  #include <algorithm>
  #include <cmath>
  #include <cstddef>
  #include <limits>
  #if !defined(WIDE_DECIMAL_DISABLE_IOSTREAM)
  #include <iomanip>
  #include <iostream>
  #include <sstream>
  #endif
  #if !defined(WIDE_DECIMAL_DISABLE_CONSTRUCT_FROM_STRING)
  #include <string>
  #endif
  #include <type_traits>

  #include <math/wide_decimal/decwide_t_detail_ops.h>

  #include <util/utility/util_baselexical_cast.h>

  #if !defined(WIDE_DECIMAL_DISABLE_CONSTRUCT_FROM_STRING)
  #include <util/utility/util_numeric_cast.h>
  #endif

  namespace math { namespace wide_decimal {

  // Forward declaration of the decwide_t template class.
  template<const std::int32_t MyDigits10,
           typename LimbType = std::uint32_t,
           typename AllocatorType = std::allocator<void>,
           typename InternalFloatType = double,
           typename ExponentType = std::int64_t,
           typename FftFloatType = double>
  class decwide_t;

  // Forward declarations of various decwide_t namespace functions.
  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType>
  constexpr decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType> zero();

  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType>
  constexpr decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType> one();

  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType>
  constexpr decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType> two();

  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType>
  constexpr decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType> half();

  #if !defined(WIDE_DECIMAL_DISABLE_CACHED_CONSTANTS)
  template<const std::int32_t MyDigits10,
           typename LimbType = std::uint32_t,
           typename AllocatorType = std::allocator<void>,
           typename InternalFloatType = double,
           typename ExponentType = std::int64_t,
           typename FftFloatType = double>
  const decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>& pi(void(*pfn_callback_to_report_digits10)(const std::uint32_t) = nullptr);
  #else
  template<const std::int32_t MyDigits10,
           typename LimbType = std::uint32_t,
           typename AllocatorType = std::allocator<void>,
           typename InternalFloatType = double,
           typename ExponentType = std::int64_t,
           typename FftFloatType = double>
  decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType> pi(void(*pfn_callback_to_report_digits10)(const std::uint32_t) = nullptr);
  #endif

  #if !defined(WIDE_DECIMAL_DISABLE_CACHED_CONSTANTS)
  template<const std::int32_t MyDigits10,
           typename LimbType = std::uint32_t,
           typename AllocatorType = std::allocator<void>,
           typename InternalFloatType = double,
           typename ExponentType = std::int64_t,
           typename FftFloatType = double>
  const decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>& ln_two();
  #else
  template<const std::int32_t MyDigits10,
           typename LimbType = std::uint32_t,
           typename AllocatorType = std::allocator<void>,
           typename InternalFloatType = double,
           typename ExponentType = std::int64_t,
           typename FftFloatType = double>
  decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType> ln_two();
  #endif

  template<const std::int32_t MyDigits10,
           typename LimbType = std::uint32_t,
           typename AllocatorType = std::allocator<void>,
           typename InternalFloatType = double,
           typename ExponentType = std::int64_t,
           typename FftFloatType = double>
  decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType> calc_pi(void(*pfn_callback_to_report_digits10)(const std::uint32_t) = nullptr);

  template<const std::int32_t MyDigits10,
           typename LimbType = std::uint32_t,
           typename AllocatorType = std::allocator<void>,
           typename InternalFloatType = double,
           typename ExponentType = std::int64_t,
           typename FftFloatType = double>
  decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType> calc_ln_two();

  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType> const decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType> constexpr unsigned_long_long_max();
  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType> const decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType> constexpr signed_long_long_min  ();
  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType> const decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType> constexpr signed_long_long_max  ();
  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType> const decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType> constexpr long_double_min       ();
  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType> const decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType> constexpr long_double_max       ();

  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType> bool (isnan)   (decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType> x);
  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType> bool (isfinite)(decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType> x);
  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType> bool (isinf)   (decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType> x);
  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType> int   sign     (decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType> x);

  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType> decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType> fabs         (decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType> x);
  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType> decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>  abs         (decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType> x);
  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType> decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType> floor        (decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType> x);
  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType> decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType> ceil         (decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType> x);
  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType> std::int32_t                                                                    sgn          (decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType> x);
  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType> decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType> ldexp        (decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType> v, int e);
  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType> decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType> frexp        (decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType> v, int* expon);
  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType> decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType> fmod         (decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType> v1, decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType> v2);
  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType> std::int32_t                                                                    ilogb        (decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType> x);
  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType> decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType> sqrt         (decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType> x);
  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType> decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType> cbrt         (decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType> x);
  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType> decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType> rootn        (decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType> x, std::int32_t p);
  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType> decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType> rootn_inverse(decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType> x, std::int32_t p);
  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType> decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType> log          (decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType> x);
  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType> decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType> exp          (decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType> x);
  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType> decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType> pow          (decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType> x, const std::int64_t n);
  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType> decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType> pow          (decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType> x,
                                                                                                                                                                                                                                      decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType> a);

  #if !defined(WIDE_DECIMAL_DISABLE_IOSTREAM)
  template<typename char_type, typename traits_type, const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType> std::basic_ostream<char_type, traits_type>& operator<<(std::basic_ostream<char_type, traits_type>& os, const decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>& f);
  template<typename char_type, typename traits_type, const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType> std::basic_istream<char_type, traits_type>& operator>>(std::basic_istream<char_type, traits_type>& is,       decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>& f);
  #endif // !WIDE_DECIMAL_DISABLE_IOSTREAM

  // Global unary operators of decwide_t reference.
  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType> decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType> operator+(const decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>& self);
  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType> decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType> operator-(const decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>& self);

  // Global add/sub/mul/div of const decwide_t& with const decwide_t&.
  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType> decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType> operator+(const decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>& u, const decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>& v);
  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType> decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType> operator-(const decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>& u, const decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>& v);
  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType> decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType> operator*(const decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>& u, const decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>& v);
  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType> decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType> operator/(const decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>& u, const decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>& v);

  // Global add/sub/mul/div of const decwide_t& with all built-in types.
  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType, typename SignedIntegralType>
  typename std::enable_if<   (std::is_integral<SignedIntegralType>::value == true)
                          && (std::is_unsigned<SignedIntegralType>::value == false), decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>>::type operator+(const decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>& u, const SignedIntegralType& n);

  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType, typename UnsignedIntegralType>
  typename std::enable_if<   (std::is_integral<UnsignedIntegralType>::value == true)
                          && (std::is_unsigned<UnsignedIntegralType>::value == true), decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>>::type operator+(const decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>& u, const UnsignedIntegralType& n);

  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType, typename FloatingPointType>
  typename std::enable_if<(std::is_floating_point<FloatingPointType>::value == true), decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>>::type operator+(const decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>& u, const FloatingPointType& f);

  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType, typename SignedIntegralType>
  typename std::enable_if<   (std::is_integral<SignedIntegralType>::value == true)
                          && (std::is_unsigned<SignedIntegralType>::value == false), decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>>::type operator-(const decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>& u, const SignedIntegralType& n);

  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType, typename UnsignedIntegralType>
  typename std::enable_if<   (std::is_integral<UnsignedIntegralType>::value == true)
                          && (std::is_unsigned<UnsignedIntegralType>::value == true), decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>>::type operator-(const decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>& u, const UnsignedIntegralType& n);

  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType, typename FloatingPointType>
  typename std::enable_if<(std::is_floating_point<FloatingPointType>::value == true), decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>>::type operator-(const decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>& u, const FloatingPointType& f);

  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType, typename SignedIntegralType>
  typename std::enable_if<   (std::is_integral<SignedIntegralType>::value == true)
                          && (std::is_unsigned<SignedIntegralType>::value == false), decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>>::type operator*(const decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>& u, const SignedIntegralType& n);

  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType, typename UnsignedIntegralType>
  typename std::enable_if<   (std::is_integral<UnsignedIntegralType>::value == true)
                          && (std::is_unsigned<UnsignedIntegralType>::value == true), decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>>::type operator*(const decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>& u, const UnsignedIntegralType& n);

  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType, typename FloatingPointType>
  typename std::enable_if<(std::is_floating_point<FloatingPointType>::value == true), decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>>::type operator*(const decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>& u, const FloatingPointType& f);

  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType, typename SignedIntegralType>
  typename std::enable_if<   (std::is_integral<SignedIntegralType>::value == true)
                          && (std::is_unsigned<SignedIntegralType>::value == false), decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>>::type operator/(const decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>& u, const SignedIntegralType& n);

  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType, typename UnsignedIntegralType>
  typename std::enable_if<   (std::is_integral<UnsignedIntegralType>::value == true)
                          && (std::is_unsigned<UnsignedIntegralType>::value == true), decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>>::type operator/(const decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>& u, const UnsignedIntegralType& n);

  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType, typename FloatingPointType>
  typename std::enable_if<(std::is_floating_point<FloatingPointType>::value == true), decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>>::type operator/(const decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>& u, const FloatingPointType& f);

  // Global add/sub/mul/div of all built-in types with const decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>&.
  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType, typename SignedIntegralType>
  typename std::enable_if<   (std::is_integral<SignedIntegralType>::value == true)
                          && (std::is_unsigned<SignedIntegralType>::value == false), decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>>::type operator+(const SignedIntegralType& n, const decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>& u);

  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType, typename UnsignedIntegralType>
  typename std::enable_if<   (std::is_integral<UnsignedIntegralType>::value == true)
                          && (std::is_unsigned<UnsignedIntegralType>::value == true), decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>>::type operator+(const UnsignedIntegralType& n, const decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>& u);

  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType, typename FloatingPointType>
  typename std::enable_if<(std::is_floating_point<FloatingPointType>::value == true), decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>>::type operator+(const FloatingPointType& f, const decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>& u);

  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType, typename ArithmeticType>
  typename std::enable_if<(std::is_arithmetic<ArithmeticType>::value == true), decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>>::type operator-(const ArithmeticType& n, const decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>& u);

  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType, typename SignedIntegralType>
  typename std::enable_if<   (std::is_integral<SignedIntegralType>::value == true)
                          && (std::is_unsigned<SignedIntegralType>::value == false), decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>>::type operator*(const SignedIntegralType& n, const decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>& u);

  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType, typename UnsignedIntegralType>
  typename std::enable_if<   (std::is_integral<UnsignedIntegralType>::value == true)
                          && (std::is_unsigned<UnsignedIntegralType>::value == true), decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>>::type operator*(const UnsignedIntegralType& n, const decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>& u);

  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType, typename FloatingPointType>
  typename std::enable_if<(std::is_floating_point<FloatingPointType>::value == true), decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>>::type operator*(const FloatingPointType& f, const decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>& u);

  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType, typename ArithmeticType>
  typename std::enable_if<(std::is_arithmetic<ArithmeticType>::value == true), decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>>::type operator/(const ArithmeticType& n, const decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>& u);

  // Global self add/sub/mul/div of decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>& with all built-in types.
  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType, typename SignedIntegralType>
  typename std::enable_if<   (std::is_integral<SignedIntegralType>::value == true)
                          && (std::is_unsigned<SignedIntegralType>::value == false), decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>>::type operator+=(decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>& u, const SignedIntegralType& n);

  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType, typename UnsignedIntegralType>
  typename std::enable_if<   (std::is_integral<UnsignedIntegralType>::value == true)
                          && (std::is_unsigned<UnsignedIntegralType>::value == true), decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>>::type operator+=(decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>& u, const UnsignedIntegralType& n);

  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType, typename FloatingPointType>
  typename std::enable_if<(std::is_floating_point<FloatingPointType>::value == true), decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>>::type operator+=(decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>& u, const FloatingPointType& f);

  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType, typename SignedIntegralType>
  typename std::enable_if<   (std::is_integral<SignedIntegralType>::value == true)
                          && (std::is_unsigned<SignedIntegralType>::value == false), decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>>::type operator-=(decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>& u, const SignedIntegralType& n);

  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType, typename UnsignedIntegralType>
  typename std::enable_if<   (std::is_integral<UnsignedIntegralType>::value == true)
                          && (std::is_unsigned<UnsignedIntegralType>::value == true), decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>>::type operator-=(decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>& u, const UnsignedIntegralType& n);

  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType, typename FloatingPointType>
  typename std::enable_if<(std::is_floating_point<FloatingPointType>::value == true), decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>>::type operator-=(decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>& u, const FloatingPointType& f);

  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType, typename SignedIntegralType>
  typename std::enable_if<   (std::is_integral<SignedIntegralType>::value == true)
                          && (std::is_unsigned<SignedIntegralType>::value == false), decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>>::type operator*=(decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>& u, const SignedIntegralType& n);

  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType, typename UnsignedIntegralType>
  typename std::enable_if<   (std::is_integral<UnsignedIntegralType>::value == true)
                          && (std::is_unsigned<UnsignedIntegralType>::value == true), decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>>::type operator*=(decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>& u, const UnsignedIntegralType& n);

  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType, typename FloatingPointType>
  typename std::enable_if<(std::is_floating_point<FloatingPointType>::value == true), decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>>::type operator*=(decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>& u, const FloatingPointType& f);

  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType, typename SignedIntegralType>
  typename std::enable_if<   (std::is_integral<SignedIntegralType>::value == true)
                          && (std::is_unsigned<SignedIntegralType>::value == false), decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>>::type operator/=(decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>& u, const SignedIntegralType& n);

  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType, typename UnsignedIntegralType>
  typename std::enable_if<   (std::is_integral<UnsignedIntegralType>::value == true)
                          && (std::is_unsigned<UnsignedIntegralType>::value == true), decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>>::type operator/=(decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>& u, const UnsignedIntegralType& n);

  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType, typename FloatingPointType>
  typename std::enable_if<(std::is_floating_point<FloatingPointType>::value == true), decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>>::type operator/=(decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>& u, const FloatingPointType& f);

  // Global comparison operators of const decwide_t& with const decwide_t&.
  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType> bool operator< (const decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>& u, const decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>& v);
  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType> bool operator<=(const decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>& u, const decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>& v);
  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType> bool operator==(const decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>& u, const decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>& v);
  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType> bool operator!=(const decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>& u, const decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>& v);
  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType> bool operator>=(const decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>& u, const decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>& v);
  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType> bool operator> (const decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>& u, const decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>& v);

  // Global comparison operators of const decwide_t& with all built-in types.
  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType, typename ArithmeticType> typename std::enable_if<std::is_arithmetic<ArithmeticType>::value == true, bool>::type operator< (const decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>& u, const ArithmeticType& v);
  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType, typename ArithmeticType> typename std::enable_if<std::is_arithmetic<ArithmeticType>::value == true, bool>::type operator<=(const decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>& u, const ArithmeticType& v);
  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType, typename ArithmeticType> typename std::enable_if<std::is_arithmetic<ArithmeticType>::value == true, bool>::type operator==(const decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>& u, const ArithmeticType& v);
  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType, typename ArithmeticType> typename std::enable_if<std::is_arithmetic<ArithmeticType>::value == true, bool>::type operator!=(const decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>& u, const ArithmeticType& v);
  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType, typename ArithmeticType> typename std::enable_if<std::is_arithmetic<ArithmeticType>::value == true, bool>::type operator>=(const decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>& u, const ArithmeticType& v);
  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType, typename ArithmeticType> typename std::enable_if<std::is_arithmetic<ArithmeticType>::value == true, bool>::type operator> (const decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>& u, const ArithmeticType& v);

  // Global comparison operators of all built-in types with const decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>&.
  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType, typename ArithmeticType> typename std::enable_if<std::is_arithmetic<ArithmeticType>::value == true, bool>::type operator< (ArithmeticType u, const decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>& v);
  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType, typename ArithmeticType> typename std::enable_if<std::is_arithmetic<ArithmeticType>::value == true, bool>::type operator<=(ArithmeticType u, const decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>& v);
  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType, typename ArithmeticType> typename std::enable_if<std::is_arithmetic<ArithmeticType>::value == true, bool>::type operator==(ArithmeticType u, const decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>& v);
  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType, typename ArithmeticType> typename std::enable_if<std::is_arithmetic<ArithmeticType>::value == true, bool>::type operator!=(ArithmeticType u, const decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>& v);
  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType, typename ArithmeticType> typename std::enable_if<std::is_arithmetic<ArithmeticType>::value == true, bool>::type operator>=(ArithmeticType u, const decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>& v);
  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType, typename ArithmeticType> typename std::enable_if<std::is_arithmetic<ArithmeticType>::value == true, bool>::type operator> (ArithmeticType u, const decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>& v);

  template<const std::int32_t MyDigits10,
           typename LimbType,
           typename AllocatorType,
           typename InternalFloatType,
           typename ExponentType,
           typename FftFloatType>
  class decwide_t
  {
  public:
    // Define the decwide_t digits characteristics.

    using exponent_type  = ExponentType;
    using fft_float_type = FftFloatType;

    static_assert((   (std::is_same<std::int8_t,  exponent_type>::value == true)
                   || (std::is_same<std::int16_t, exponent_type>::value == true)
                   || (std::is_same<std::int32_t, exponent_type>::value == true)
                   || (std::is_same<std::int64_t, exponent_type>::value == true)),
                   "Error: exponent_type (determined via the template parameter ExponentType) must be one of int8_t, int16_t, int32_t or int64_t.");

    static constexpr std::int32_t  decwide_t_digits10       = detail::decwide_t_helper<MyDigits10, LimbType>::digits10;
    static constexpr std::int32_t  decwide_t_digits         = detail::decwide_t_helper<MyDigits10, LimbType>::digits;
    static constexpr std::int32_t  decwide_t_max_digits10   = detail::decwide_t_helper<MyDigits10, LimbType>::max_digits10;
    static constexpr std::int32_t  decwide_t_radix          = detail::decwide_t_helper<MyDigits10, LimbType>::radix;

    static constexpr std::int32_t  decwide_t_elem_digits10  = detail::decwide_t_helper<MyDigits10, LimbType>::elem_digits10;
    static constexpr std::int32_t  decwide_t_elem_number    = detail::decwide_t_helper<MyDigits10, LimbType>::elem_number;
    static constexpr std::int32_t  decwide_t_elem_mask      = detail::decwide_t_helper<MyDigits10, LimbType>::elem_mask;
    static constexpr std::int32_t  decwide_t_elem_mask_half = detail::decwide_t_helper<MyDigits10, LimbType>::elem_mask_half;

    static constexpr exponent_type decwide_t_max_exp10      =  static_cast<exponent_type>(1) << (std::numeric_limits<exponent_type>::digits - ((std::is_same<exponent_type, std::int64_t>::value == true) ? 4 : ((std::is_same<exponent_type, std::int32_t>::value == true) ? 3 : ((std::is_same<exponent_type, std::int16_t>::value == true) ? 2 : 1))));
    static constexpr exponent_type decwide_t_min_exp10      = -static_cast<exponent_type>(decwide_t_max_exp10);
    static constexpr exponent_type decwide_t_max_exp        = decwide_t_max_exp10;
    static constexpr exponent_type decwide_t_min_exp        = decwide_t_min_exp10;

    static constexpr std::int32_t  decwide_t_elems_for_kara = static_cast<std::int32_t>( 112 + 1);
    static constexpr std::int32_t  decwide_t_elems_for_fft  = static_cast<std::int32_t>(1280 + 1);

    // Obtain the limb_type from template parameter.
    using limb_type = LimbType;

    // Rebind the decwide_t allocator to the granularity of the LimbType.
    using allocator_type =
      typename std::allocator_traits<typename std::conditional<std::is_same<AllocatorType, void>::value,
                                                               std::allocator<void>,
                                                               AllocatorType>::type>::template rebind_alloc<limb_type>;

    // Define the array type, which is the internal
    // representation of the data field of a decwide_t.
    using representation_type =
      typename std::conditional<std::is_same<AllocatorType, void>::value,
                                detail::fixed_static_array <limb_type, static_cast<std::uint_fast32_t>(decwide_t_elem_number)>,
                                detail::fixed_dynamic_array<limb_type, static_cast<std::uint_fast32_t>(decwide_t_elem_number), allocator_type>>::type;

    // Check thw width of the limb type.
    static_assert((   (std::is_same<std::uint8_t,  limb_type>::value == true)
                   || (std::is_same<std::uint16_t, limb_type>::value == true)
                   || (std::is_same<std::uint32_t, limb_type>::value == true)),
                   "Error: limb_type (determined via the template parameter LimbType) must be one of uint8_t, uint16_t or uint32_t.");

    using double_limb_type =
      typename std::conditional<(std::is_same<limb_type, std::uint32_t>::value == true),
                                 std::uint64_t,
                                 typename std::conditional<(std::is_same<limb_type, std::uint16_t>::value == true),
                                                            std::uint32_t,
                                                            std::uint16_t>::type>::type;

    using signed_limb_type =
      typename std::conditional<(std::is_same<limb_type, std::uint32_t>::value == true),
                                 std::int32_t,
                                 typename std::conditional<(std::is_same<limb_type, std::uint16_t>::value == true),
                                                            std::int16_t,
                                                            std::int8_t>::type>::type;

    using unsigned_exponent_type =
      typename std::conditional<(std::is_same<exponent_type, std::int64_t>::value == true),
                                 std::uint64_t,
                                 typename std::conditional<(std::is_same<exponent_type, std::int32_t>::value == true),
                                                            std::uint32_t,
                                                            typename std::conditional<(std::is_same<exponent_type, std::int16_t>::value == true),
                                                                                       std::uint16_t,
                                                                                       std::uint8_t>::type>::type>::type;

    typedef enum fpclass_type
    {
      decwide_t_finite
    }
    fpclass_type;

  private:
    template<typename native_float_type>
    class native_float_parts final
    {
    public:
      // Emphasize: This template class can be used with native floating-point
      // types like float, double and long double. Note: For long double,
      // you need to verify that the mantissa fits in unsigned long long.
      native_float_parts(const native_float_type f)
        : my_mantissa_part(0ULL),
          my_exponent_part(0)
      {
        const native_float_type ff = ((f < static_cast<native_float_type>(0)) ? -f : f);

        if(ff < (std::numeric_limits<native_float_type>::min)())
        {
          return;
        }

        using std::frexp;

        // Get the fraction and base-2 exponent.
        native_float_type man = (native_float_type) frexp(f, &my_exponent_part);

        limb_type n2 = 0U;

        for(std::uint_fast16_t i = static_cast<std::uint_fast16_t>(0U); i < static_cast<std::uint_fast16_t>(std::numeric_limits<native_float_type>::digits); ++i)
        {
          // Extract the mantissa of the floating-point type in base-2
          // (one bit at a time) and store it in an unsigned long long.
          man *= 2;

          n2   = static_cast<limb_type>(man);
          man -= static_cast<native_float_type>(n2);

          if(n2 != static_cast<limb_type>(0U))
          {
            my_mantissa_part |= 1U;
          }

          if(i < static_cast<limb_type>(std::numeric_limits<native_float_type>::digits - 1))
          {
            my_mantissa_part <<= 1U;
          }
        }

        // Ensure that the value is normalized and adjust the exponent.
        my_mantissa_part |= static_cast<unsigned long long>(1ULL << (std::numeric_limits<native_float_type>::digits - 1));
        my_exponent_part -= 1;
      }

      const unsigned long long& get_mantissa() const { return my_mantissa_part; }
      const int&                get_exponent() const { return my_exponent_part; }

    private:
      native_float_parts() = delete;
      native_float_parts(const native_float_parts&) = delete;

      const native_float_parts& operator=(const native_float_parts&) = delete;

      unsigned long long my_mantissa_part;
      int                my_exponent_part;
    };

    #if !defined(WIDE_DECIMAL_DISABLE_CACHED_CONSTANTS)
    // Static data initializer
    struct initializer
    {
      initializer()
      {
        decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>::my_value_pi    ();
        decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>::my_value_ln_two();
      }

      void do_nothing() { }
    };

    static initializer init;
    #endif

  public:
    // Default constructor.
    constexpr decwide_t() : my_data     (),
                            my_exp      (static_cast<exponent_type>(0)),
                            my_neg      (false),
                            my_fpclass  (decwide_t_finite),
                            my_prec_elem(decwide_t_elem_number) { }

    // Constructors from built-in unsigned integral types.
    template<typename UnsignedIntegralType,
             typename std::enable_if<(   (std::is_integral<UnsignedIntegralType>::value == true)
                                      && (std::is_unsigned<UnsignedIntegralType>::value == true)
                                      && (std::numeric_limits<UnsignedIntegralType>::digits <= std::numeric_limits<limb_type>::digits))>::type const* = nullptr>
    constexpr decwide_t(const UnsignedIntegralType u)
      : my_data
        (
          {
            (u < decwide_t_elem_mask) ? u             : u / (limb_type) decwide_t_elem_mask,
            (u < decwide_t_elem_mask) ? limb_type(0U) : u % (limb_type) decwide_t_elem_mask
          }
        ),
        my_exp      ((u < decwide_t_elem_mask) ? exponent_type(0) : exponent_type(decwide_t_elem_digits10)),
        my_neg      (false),
        my_fpclass  (decwide_t_finite),
        my_prec_elem(decwide_t_elem_number) { }

    // Constructors from built-in unsigned integral types.
    template<typename UnsignedIntegralType,
             typename std::enable_if<(   (std::is_integral<UnsignedIntegralType>::value == true)
                                      && (std::is_unsigned<UnsignedIntegralType>::value == true)
                                      && (std::numeric_limits<limb_type>::digits) < std::numeric_limits<UnsignedIntegralType>::digits)>::type const* = nullptr>
    decwide_t(const UnsignedIntegralType u) : my_data     (),
                                              my_exp      (static_cast<exponent_type>(0)),
                                              my_neg      (false),
                                              my_fpclass  (decwide_t_finite),
                                              my_prec_elem(decwide_t_elem_number)
    {
      from_unsigned_long_long(u);
    }

    // Constructors from built-in signed integral types.
    template<typename SignedIntegralType,
             typename std::enable_if<(   (std::is_integral<SignedIntegralType>::value == true)
                                      && (std::is_signed  <SignedIntegralType>::value == true))>::type const* = nullptr>
    decwide_t(const SignedIntegralType n) : my_data     (),
                                            my_exp      (static_cast<exponent_type>(0)),
                                            my_neg      (n < static_cast<signed long long>(0)),
                                            my_fpclass  (decwide_t_finite),
                                            my_prec_elem(decwide_t_elem_number)
    {
      const unsigned long long u =
        ((!my_neg) ? static_cast<unsigned long long>(n)
                   : static_cast<unsigned long long>(1U) + static_cast<unsigned long long>(-(n + 1)));

      from_unsigned_long_long(u);
    }

    // Constructors from built-in floating-point types.
    template<typename FloatingPointType,
              typename std::enable_if<std::is_floating_point<FloatingPointType>::value == true>::type const* = nullptr>
    decwide_t(const FloatingPointType f) : my_data     (),
                                           my_exp      (static_cast<exponent_type>(0)),
                                           my_neg      (false),
                                           my_fpclass  (decwide_t_finite),
                                           my_prec_elem(decwide_t_elem_number)
    {
      from_builtin_float_type(f);
    }

    #if !defined(WIDE_DECIMAL_DISABLE_CONSTRUCT_FROM_STRING)
    // Constructors from character representations.
    decwide_t(const char* s) : my_data     (),
                               my_exp      (static_cast<exponent_type>(0)),
                               my_neg      (false),
                               my_fpclass  (decwide_t_finite),
                               my_prec_elem(decwide_t_elem_number)
    {
      if(rd_string(s) == false)
      {
        std::fill(my_data.begin(), my_data.end(), static_cast<limb_type>(0U));
      }
    }

    #endif // !WIDE_DECIMAL_DISABLE_CONSTRUCT_FROM_STRING

    // Copy constructor.
    constexpr decwide_t(const decwide_t& other) : my_data     (other.my_data),
                                                  my_exp      (other.my_exp),
                                                  my_neg      (other.my_neg),
                                                  my_fpclass  (other.my_fpclass),
                                                  my_prec_elem(other.my_prec_elem) { }

    // Move constructor.
    constexpr decwide_t(decwide_t&& other) : my_data     ((representation_type&&) other.my_data),
                                             my_exp      (other.my_exp),
                                             my_neg      (other.my_neg),
                                             my_fpclass  (other.my_fpclass),
                                             my_prec_elem(other.my_prec_elem) { }

    // Constructor from floating-point class type, even though
    // (at the moment) decwide_t instances can only be finite.
    explicit constexpr decwide_t(const fpclass_type)
      : my_data     (),
        my_exp      (0),
        my_neg      (false),
        my_fpclass  (decwide_t_finite),
        my_prec_elem(decwide_t_elem_number) { }

  private:
    // Constructor from mantissa and exponent.
    explicit decwide_t(const InternalFloatType mantissa,
                       const exponent_type     exponent)
      : my_data     (),
        my_exp      (static_cast<exponent_type>(0)),
        my_neg      (false),
        my_fpclass  (decwide_t_finite),
        my_prec_elem(decwide_t_elem_number)
    {
      // Create a decwide_t from mantissa and exponent.
      // This constructor is intended to maintain the
      // full precision of the InternalFloatType.

      using std::fabs;

      const InternalFloatType close_to_zero =
        (  (std::numeric_limits<InternalFloatType>::min)()
         * (InternalFloatType(1) + std::numeric_limits<InternalFloatType>::epsilon()));

      const bool mantissa_is_iszero = (fabs(mantissa) < close_to_zero);

      if(mantissa_is_iszero)
      {
        my_data.fill(static_cast<limb_type>(0));

        if(exponent == static_cast<exponent_type>(0))
        {
          my_data[0U] = limb_type(1U);
        }
      }
      else
      {
        const bool b_neg = (mantissa < InternalFloatType(0));

        InternalFloatType d = ((!b_neg) ? mantissa : -mantissa);
        exponent_type     e = exponent;

        constexpr InternalFloatType f10(10U);

        while(d > f10)                     { d /= f10; ++e; }
        while(d < InternalFloatType(1.0F)) { d *= f10; --e; }

        {
          std::int32_t shift = static_cast<std::int32_t>(e % static_cast<std::int32_t>(decwide_t_elem_digits10));

          while(static_cast<std::int32_t>(shift % decwide_t_elem_digits10) != static_cast<std::int32_t>(0))
          {
            d *= f10;
            --e;
            --shift;
          }
        }

        my_exp = e;
        my_neg = b_neg;

        constexpr std::int32_t digit_loops = static_cast<std::int32_t>(  static_cast<std::int32_t>(std::numeric_limits<InternalFloatType>::max_digits10)
                                                                       / static_cast<std::int32_t>(decwide_t_elem_digits10))
                 + static_cast<std::int32_t>(static_cast<std::int32_t>(  static_cast<std::int32_t>(std::numeric_limits<InternalFloatType>::max_digits10)
                                                                       % static_cast<std::int32_t>(decwide_t_elem_digits10)) != 0 ? 1 : 0);

        typename representation_type::size_type limb_index;

        for(  limb_index = static_cast<typename representation_type::size_type>(0);
              limb_index < static_cast<typename representation_type::size_type>(digit_loops);
            ++limb_index)
        {
          const limb_type n = static_cast<limb_type>(d);

          my_data[limb_index]  = static_cast<limb_type>(n);
          d                   -= static_cast<InternalFloatType>(n);
          d                   *= static_cast<InternalFloatType>(decwide_t_elem_mask);
        }

        std::fill(my_data.begin() + limb_index, my_data.end(), static_cast<limb_type>(0));
      }
    }

  public:
    ~decwide_t() = default;

    // Assignment operator.
    decwide_t& operator=(const decwide_t& other)
    {
      if(this != &other)
      {
        my_data      = other.my_data;
        my_exp       = other.my_exp;
        my_neg       = other.my_neg;
        my_fpclass   = other.my_fpclass;
        my_prec_elem = other.my_prec_elem;
      }

      return *this;
    }

    // Move assignment operator.
    decwide_t& operator=(decwide_t&& other)
    {
      my_data      = (representation_type&&) other.my_data;
      my_exp       = other.my_exp;
      my_neg       = other.my_neg;
      my_fpclass   = other.my_fpclass;
      my_prec_elem = other.my_prec_elem;

      return *this;
    }

          representation_type&  representation()       { return my_data; }
    const representation_type&  representation() const { return my_data; }
    const representation_type& crepresentation() const { return my_data; }

    // Binary arithmetic operators.
    decwide_t& operator+=(const decwide_t& v)
    {
      // TBD: Eliminate the temporary storage array my_n_data_for_add_sub.

      // TBD: Limit the length of add/sub to only those ranges needed,
      // whereby propagate borrow/carry may be necessary as well.

      if(iszero())
      {
        return operator=(v);
      }

      const std::int32_t prec_elems_for_add_sub = (std::min)(my_prec_elem, v.my_prec_elem);

      // Get the offset for the add/sub operation.
      const exponent_type max_delta_exp =
        static_cast<exponent_type>(prec_elems_for_add_sub * decwide_t_elem_digits10);

      using local_unsigned_wrap_type = detail::unsigned_wrap<unsigned_exponent_type, exponent_type>;

      local_unsigned_wrap_type u_exp(  my_exp);
      local_unsigned_wrap_type v_exp(v.my_exp);

      const local_unsigned_wrap_type ofs_exp = (u_exp - v_exp);

      // Check if the operation is out of range, requiring special handling.
      if(   v.iszero()
         || ((ofs_exp.get_is_neg() == false) && (ofs_exp.get_value_unsigned() >= (unsigned_exponent_type) max_delta_exp)))
      {
        // Result is *this unchanged since v is negligible compared to *this.
        return *this;
      }
      else if((ofs_exp.get_is_neg() == true) && (ofs_exp.get_value_unsigned() >= (unsigned_exponent_type) max_delta_exp))
      {
        // Result is *this = v since *this is negligible compared to v.
        return operator=(v);
      }

      // Do the add/sub operation.

      typename representation_type::pointer       p_u    =   my_data.data();
      typename representation_type::const_pointer p_v    = v.my_data.data();
      bool                                        b_copy = false;
      const std::int32_t                          ofs    = ((ofs_exp.get_is_neg() == false) ? +static_cast<std::int32_t>(ofs_exp.get_value_unsigned() / (unsigned_exponent_type) decwide_t_elem_digits10)
                                                                                   : -static_cast<std::int32_t>(ofs_exp.get_value_unsigned() / (unsigned_exponent_type) decwide_t_elem_digits10));

      #if !defined(WIDE_DECIMAL_DISABLE_DYNAMIC_MEMORY_ALLOCATION)
      representation_type my_n_data_for_add_sub;
      #endif

      if(my_neg == v.my_neg)
      {
        // Add v to *this, where the data array of either *this or v
        // might have to be treated with a positive, negative or zero offset.
        // The result is stored in *this. The data are added one element
        // at a time, each element with carry.
        if(ofs >= static_cast<std::int32_t>(0))
        {
          std::copy(v.my_data.cbegin(),
                    v.my_data.cend() - static_cast<std::ptrdiff_t>(ofs),
                    my_n_data_for_add_sub.begin() + static_cast<std::ptrdiff_t>(ofs));

          std::fill(my_n_data_for_add_sub.begin(),
                    my_n_data_for_add_sub.begin() + static_cast<std::ptrdiff_t>(ofs),
                    static_cast<limb_type>(0));

          p_v = my_n_data_for_add_sub.data();
        }
        else
        {
          std::copy(my_data.cbegin(),
                    my_data.cend() - static_cast<std::ptrdiff_t>(-ofs),
                    my_n_data_for_add_sub.begin() + static_cast<std::ptrdiff_t>(-ofs));

          std::fill(my_n_data_for_add_sub.begin(),
                    my_n_data_for_add_sub.begin() + static_cast<std::ptrdiff_t>(-ofs),
                    static_cast<limb_type>(0));

          p_u = my_n_data_for_add_sub.data();
          b_copy = true;
        }

        // Addition.
        const limb_type carry =
          detail::eval_add_n(p_u,
                             typename std::add_const<limb_type*>::type(p_u),
                             typename std::add_const<limb_type*>::type(p_v),
                             prec_elems_for_add_sub);

        if(b_copy)
        {
          std::copy(my_n_data_for_add_sub.cbegin(),
                    my_n_data_for_add_sub.cbegin() + prec_elems_for_add_sub,
                    my_data.begin());
          my_exp  = v.my_exp;
        }

        // There needs to be a carry into the element -1 of the array data
        if(carry != static_cast<limb_type>(0U))
        {
          std::copy_backward(my_data.cbegin(),
                             my_data.cend() - static_cast<std::uint_fast32_t>((std::int32_t(my_data.size()) - prec_elems_for_add_sub) + 1),
                             my_data.end());

          my_data[0U] = carry;

          my_exp = static_cast<exponent_type>(my_exp + static_cast<exponent_type>(decwide_t_elem_digits10));
        }
      }
      else
      {
        // Subtract v from *this, where the data array of either *this or v
        // might have to be treated with a positive, negative or zero offset.
        if(       (ofs >  static_cast<std::int32_t>(0))
           || (   (ofs == static_cast<std::int32_t>(0))
               && (detail::compare_ranges(my_data.data(), v.my_data.data(), static_cast<std::uint_fast32_t>(prec_elems_for_add_sub)) > 0)))
        {
          // In this case, |u| > |v| and ofs is positive.
          // Copy the data of v, shifted down to a lower value
          // into the data array m_n. Set the operand pointer p_v
          // to point to the copied, shifted data m_n.
          std::copy(v.my_data.cbegin(),
                    v.my_data.cend()  - static_cast<std::ptrdiff_t>(ofs),
                    my_n_data_for_add_sub.begin() + static_cast<std::ptrdiff_t>(ofs));

          std::fill(my_n_data_for_add_sub.begin(),
                    my_n_data_for_add_sub.begin() + static_cast<std::ptrdiff_t>(ofs),
                    static_cast<limb_type>(0));

          p_v = my_n_data_for_add_sub.data();
        }
        else
        {
          if(ofs != static_cast<std::int32_t>(0))
          {
            // In this case, |u| < |v| and ofs is negative.
            // Shift the data of u down to a lower value.
            std::copy_backward(my_data.cbegin(),
                               my_data.cend() - static_cast<std::ptrdiff_t>(-ofs),
                               my_data.end());

            std::fill(my_data.begin(),
                      my_data.begin() + static_cast<std::ptrdiff_t>(-ofs),
                      static_cast<limb_type>(0));
          }

          // Copy the data of v into the data array my_n_data_for_add_sub.
          // Set the u-pointer p_u to point to m_n and the
          // operand pointer p_v to point to the shifted
          // data m_data.
          std::copy(v.my_data.cbegin(),
                    v.my_data.cbegin() + prec_elems_for_add_sub,
                    my_n_data_for_add_sub.begin());
          p_u    = my_n_data_for_add_sub.data();
          p_v    = my_data.data();
          b_copy = true;
        }

        // Subtraction.
        const bool has_borrow =
          detail::eval_subtract_n(p_u,
                                  typename std::add_const<limb_type*>::type(p_u),
                                  typename std::add_const<limb_type*>::type(p_v),
                                  prec_elems_for_add_sub);

        static_cast<void>(has_borrow);

        if(b_copy)
        {
          std::copy(my_n_data_for_add_sub.cbegin(),
                    my_n_data_for_add_sub.cbegin() + prec_elems_for_add_sub,
                    my_data.begin());
          my_exp  = v.my_exp;
          my_neg  = v.my_neg;
        }

        // Is it necessary to justify the data?
        const typename representation_type::const_iterator first_nonzero_elem =
          std::find_if(my_data.cbegin(),
                       my_data.cbegin() + prec_elems_for_add_sub,
                       [](const limb_type& d) -> bool
                       {
                         return (d != static_cast<limb_type>(0U));
                       });

        if(first_nonzero_elem != my_data.cbegin())
        {
          if(first_nonzero_elem == my_data.cbegin() + prec_elems_for_add_sub)
          {
            // This result of the subtraction is exactly zero (within precision).
            // Reset the sign and the exponent.
            my_neg = false;
            my_exp = static_cast<exponent_type>(0);
          }
          else
          {
            // Justify the data
            const std::ptrdiff_t sj =
              static_cast<std::ptrdiff_t>(first_nonzero_elem - my_data.cbegin());

            std::copy(my_data.cbegin() + static_cast<std::ptrdiff_t>(sj),
                      my_data.cend(),
                      my_data.begin());

            std::fill(my_data.end() - static_cast<std::ptrdiff_t>(sj),
                      my_data.end(),
                      static_cast<limb_type>(0));

            my_exp = static_cast<exponent_type>(my_exp - static_cast<exponent_type>(sj * static_cast<std::ptrdiff_t>(decwide_t_elem_digits10)));
          }
        }
      }

      // Check for underflow.
      if(iszero())
      {
        return (*this = zero<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>());
      }

      return *this;
    }

    decwide_t& operator-=(const decwide_t& v)
    {
      // Use *this - v = -(-*this + v).
      return (negate().operator+=(v)).negate();
    }

    decwide_t& operator*=(const decwide_t& v)
    {
      // Evaluate the sign of the result.
      const bool b_result_is_neg = (my_neg != v.my_neg);

      // Artificially set the sign of the result to be positive.
      my_neg = false;

      // Handle multiplication by zero.
      if(iszero() || v.iszero())
      {
        *this = zero<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>();
      }
      else
      {
        // Set the exponent of the result.
        using local_unsigned_wrap_type = detail::unsigned_wrap<unsigned_exponent_type, exponent_type>;

        local_unsigned_wrap_type u_exp(  my_exp);
        local_unsigned_wrap_type v_exp(v.my_exp);

        const local_unsigned_wrap_type result_exp = (u_exp + v_exp);

        if((result_exp.get_is_neg() == false) && (result_exp.get_value_unsigned() >= decwide_t_max_exp10))
        {
          operator=(my_value_max());
        }
        else if((result_exp.get_is_neg() == true) && (result_exp.get_value_unsigned() >= decwide_t_max_exp10))
        {
          operator=(my_value_min());
        }
        else
        {
          my_exp = static_cast<exponent_type>((result_exp.get_is_neg() == false) ? static_cast<exponent_type>(result_exp.get_value_unsigned())
                                                                                 : static_cast<exponent_type>(unsigned_exponent_type(unsigned_exponent_type(~result_exp.get_value_unsigned()) + 1U)));

          const std::int32_t prec_elems_for_multiply = (std::min)(my_prec_elem, v.my_prec_elem);

          eval_mul_dispatch_multiplication_method(v, prec_elems_for_multiply);
        }
      }

      // Set the sign of the result.
      my_neg = b_result_is_neg;

      return *this;
    }

    decwide_t& operator/=(const decwide_t& v)
    {
      const bool u_and_v_are_identical =
        (   (my_fpclass == v.my_fpclass)
         && (my_exp     == v.my_exp)
         && (detail::compare_ranges(my_data.data(), v.my_data.data(), static_cast<std::uint_fast32_t>(decwide_t_elem_number)) == 0));

      if(u_and_v_are_identical)
      {
        *this = one<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>();

        if(my_neg != v.my_neg)
        {
          negate();
        }
      }
      else
      {
        operator*=(decwide_t(v).calculate_inv());
      }

      return *this;
    }

    // Arithmetic operators with unsigned long long.
    decwide_t& add_unsigned_long_long(const unsigned long long n)
    {
      // Non-optimized addition of unsigned long long.
      return operator+=(decwide_t(n));
    }

    decwide_t& sub_unsigned_long_long(const unsigned long long n)
    {
      // Non-optimized subtraction of unsigned long long.
      return operator-=(decwide_t(n));
    }

    decwide_t& mul_unsigned_long_long(const unsigned long long n)
    {
      // Multiply *this with a constant unsigned long long.

      // Evaluate the sign of the result.
      const bool b_neg = my_neg;

      // Artificially set the sign of the result to be positive.
      my_neg = false;

      // Handle special cases like zero, inf and NaN.
      const bool b_n_is_zero = (n == static_cast<std::int32_t>(0));

      if(iszero() || b_n_is_zero)
      {
        // Multiplication by zero.
        return (*this = zero<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>());
      }

      if(n >= static_cast<unsigned long long>(decwide_t_elem_mask))
      {
        my_neg = b_neg;

        return operator*=(decwide_t(n));
      }

      if(n == static_cast<unsigned long long>(1U))
      {
        my_neg = b_neg;

        return *this;
      }

      // Set up the multiplication loop.
      const limb_type nn    = static_cast<limb_type>(n);
      const limb_type carry = detail::mul_loop_n(my_data.data(), nn, my_prec_elem);

      // Handle the carry and adjust the exponent.
      if(carry != static_cast<limb_type>(0U))
      {
        my_exp = static_cast<exponent_type>(my_exp + static_cast<exponent_type>(decwide_t_elem_digits10));

        // Shift the result of the multiplication one element to the right.
        std::copy_backward(my_data.cbegin(),
                           my_data.cbegin() + static_cast<std::ptrdiff_t>(my_prec_elem - 1),
                           my_data.begin()  + static_cast<std::ptrdiff_t>(my_prec_elem));

        my_data.front() = static_cast<limb_type>(carry);
      }

      // Set the sign.
      my_neg = b_neg;

      return *this;
    }

    decwide_t& div_unsigned_long_long(const unsigned long long n)
    {
      // Divide *this by a constant unsigned long long.

      // Evaluate the sign of the result.
      const bool b_neg = my_neg;

      // Artificially set the sign of the result to be positive.
      my_neg = false;

      // Handle special cases of zero.
      if(n == static_cast<unsigned long long>(0U))
      {
        // Divide by 0.
        return (*this = zero<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>());
      }

      if(iszero())
      {
        return *this;
      }

      if(n >= static_cast<unsigned long long>(decwide_t_elem_mask))
      {
        my_neg = b_neg;

        return operator/=(decwide_t(n));
      }

      const limb_type nn = static_cast<limb_type>(n);

      if(nn > static_cast<limb_type>(1U))
      {
        // Do the division loop.
        const limb_type prev = detail::div_loop_n(my_data.data(), nn, my_prec_elem);

        // Determine if one leading zero is in the result data.
        if(my_data[0] == static_cast<limb_type>(0U))
        {
          // Adjust the exponent
          my_exp = static_cast<exponent_type>(my_exp - static_cast<exponent_type>(decwide_t_elem_digits10));

          // Shift result of the division one element to the left.
          std::copy(my_data.cbegin() + static_cast<std::ptrdiff_t>(1),
                    my_data.cbegin() + static_cast<std::ptrdiff_t>(my_prec_elem - 1),
                    my_data.begin());

          const typename representation_type::size_type ip = static_cast<typename representation_type::size_type>(my_prec_elem - 1);

          my_data[ip] = static_cast<limb_type>(static_cast<std::uint64_t>(prev * static_cast<std::uint64_t>(decwide_t_elem_mask)) / nn);
        }
      }

      // Check for underflow.
      if(iszero())
      {
        return (*this = zero<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>());
      }

      // Set the sign of the result.
      my_neg = b_neg;

      return *this;
    }

    // Arithmetic operators with signed long long.
    decwide_t& add_signed_long_long(const signed long long n)
    {
      if(n < static_cast<signed long long>(0))
      {
        negate();
        add_unsigned_long_long(static_cast<unsigned long long>(-n));
        negate();
      }
      else
      {
        add_unsigned_long_long(static_cast<unsigned long long>(n));
      }

      return static_cast<decwide_t&>(*this);
    }

    decwide_t& sub_signed_long_long(const signed long long n)
    {
      return add_signed_long_long(static_cast<signed long long>(-n));
    }

    decwide_t& mul_signed_long_long(const signed long long n)
    {
      const bool b_neg = (n < static_cast<signed long long>(0));

      mul_unsigned_long_long((!b_neg) ? static_cast<unsigned long long>(n) : static_cast<unsigned long long>(-n));

      if(b_neg)
      {
        negate();
      }

      return static_cast<decwide_t&>(*this);
    }

    decwide_t& div_signed_long_long(const signed long long n)
    {
      const bool b_neg = (n < static_cast<signed long long>(0));

      div_unsigned_long_long((!b_neg) ? static_cast<unsigned long long>(n) : static_cast<unsigned long long>(-n));

      if(b_neg)
      {
        negate();
      }

      return static_cast<decwide_t&>(*this);
    }

    std::int_fast8_t cmp(const decwide_t& v) const
    {
      // Compare v with *this.
      //         Return +1 for *this > v
      //                 0 for *this = v
      //                -1 for *this < v

      // Handle all *finite* cases only.
      if(iszero())
      {
        // The value of *this is zero and v is either zero or non-zero.
        return (v.iszero() ? static_cast<std::int_fast8_t>(0)
                           : (v.my_neg ? static_cast<std::int_fast8_t>(1) : static_cast<std::int_fast8_t>(-1)));
      }
      else if(v.iszero())
      {
        // The value of v is zero and *this is non-zero.
        return (my_neg ? static_cast<std::int_fast8_t>(-1) : static_cast<std::int_fast8_t>(1));
      }
      else
      {
        // Both *this and v are non-zero.

        if(my_neg != v.my_neg)
        {
          // The signs are different.
          return (my_neg ? static_cast<std::int_fast8_t>(-1) : static_cast<std::int_fast8_t>(1));
        }
        else if(my_exp != v.my_exp)
        {
          // The signs are the same and the exponents are different.
          const std::int_fast8_t val_cmp_exp =
            ((my_exp < v.my_exp) ? static_cast<std::int_fast8_t>(1) : static_cast<std::int_fast8_t>(-1));

          return (my_neg ? val_cmp_exp : static_cast<std::int_fast8_t>(-val_cmp_exp));
        }
        else
        {
          // The signs are the same and the exponents are the same.
          // Compare the data.
          const std::int_fast8_t val_cmp_data =
            detail::compare_ranges(my_data.data(), v.my_data.data(), static_cast<std::uint_fast32_t>(decwide_t_elem_number));

          return ((!my_neg) ? val_cmp_data : static_cast<std::int_fast8_t>(-val_cmp_data));
        }
      }
    }

    // Specific special values.
    static constexpr decwide_t my_value_max() { return from_lst( { limb_type(9U) }, decwide_t_max_exp10 ); }
    static constexpr decwide_t my_value_min() { return from_lst( { limb_type(1U) }, decwide_t_min_exp10 ); }
    static constexpr decwide_t my_value_eps()
    {
      return
      from_lst
      (
        {
          (limb_type) detail::pow10_maker((std::uint32_t) ((std::int32_t) (INT32_C(1) + (std::int32_t) (((decwide_t_digits10 / decwide_t_elem_digits10) + ((decwide_t_digits10 % decwide_t_elem_digits10) != 0 ? 1 : 0)) * decwide_t_elem_digits10)) - decwide_t_digits10))
        },
        -(exponent_type) (((decwide_t_digits10 / decwide_t_elem_digits10) + ((decwide_t_digits10 % decwide_t_elem_digits10) != 0 ? 1 : 0)) * decwide_t_elem_digits10)
      );
    }

    #if !defined(WIDE_DECIMAL_DISABLE_CACHED_CONSTANTS)
    static const decwide_t& my_value_pi()
    {
      init.do_nothing();
      static const decwide_t val(calc_pi<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>());
      return val;
    }

    static const decwide_t& my_value_ln_two()
    {
      init.do_nothing();
      static const decwide_t val(calc_ln_two<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>());
      return val;
    }
    #endif

    void precision(const std::int32_t prec_digits)
    {
      const std::int32_t elems =
        static_cast<std::int32_t>(    static_cast<std::int32_t>(prec_digits / decwide_t_elem_digits10)
                                  +                          (((prec_digits % decwide_t_elem_digits10) != 0) ? 1 : 0));

      my_prec_elem = (std::min)(decwide_t_elem_number, (std::max)(elems, static_cast<std::int32_t>(2)));
    }

    void swap(decwide_t& other_decwide_t)
    {
      if(this != &other_decwide_t)
      {
        const decwide_t tmp_value_this(*this);

        *this = other_decwide_t;

        other_decwide_t = tmp_value_this;
      }
    }

    // Elementary primitives.
    decwide_t& calculate_inv()
    {
      // Compute the inverse of *this.
      const bool b_neg = my_neg;

      my_neg = false;

      // Handle special cases of zero.
      if(iszero())
      {
        return (*this = zero<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>());
      }

      if(isone())
      {
        *this = ((!b_neg) ?  one<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>()
                          : -one<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>());

        return *this;
      }

      // Use the original value of *this for iteration below.
      decwide_t x(*this);

      // Generate the initial estimate using division.
      // Extract the mantissa and exponent for a "manual"
      // computation of the estimate.
      InternalFloatType dd;
      exponent_type     ne;

      x.extract_parts(dd, ne);

      const std::int32_t original_prec_elem = my_prec_elem;

      // Do the inverse estimate using InternalFloatType precision estimates of mantissa and exponent.
      operator=(decwide_t(InternalFloatType(1) / dd, static_cast<exponent_type>(-ne)));

      // Compute the inverse of *this. Quadratically convergent Newton-Raphson iteration
      // is used. During the iterative steps, the precision of the calculation is limited
      // to the minimum required in order to minimize the run-time.

      for(std::int32_t digits  = (std::int32_t) (std::numeric_limits<InternalFloatType>::digits10 - 1);
                       digits  < (std::int32_t) (original_prec_elem * decwide_t_elem_digits10);
                       digits *= static_cast<std::int32_t>(2))
      {
        // Adjust precision of the terms.
        const std::int32_t new_prec_as_digits10 =
            (std::int32_t) (digits * 2)
          + (std::max)((std::int32_t) (decwide_t_elem_digits10  + 1), (std::int32_t) 9);

          precision(new_prec_as_digits10);
        x.precision(new_prec_as_digits10);

        // Next iteration.
        operator=(*this * (two<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>() - (*this * x)));
      }

      my_neg = b_neg;

      my_prec_elem = original_prec_elem;

      return *this;
    }

    decwide_t& calculate_sqrt()
    {
      // Compute the square root of *this.

      if(isneg())
      {
        return (*this = zero<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>());
      }

      if(iszero() || isone())
      {
        return *this;
      }

      // Use the original value of *this for iteration below.
      decwide_t x(*this);

      // Generate the initial estimate using division.
      // Extract the mantissa and exponent for a "manual"
      // computation of the estimate.
      InternalFloatType dd;
      exponent_type     ne;

      extract_parts(dd, ne);

      // Force the exponent to be an even multiple of two.
      if((ne % 2) != static_cast<exponent_type>(0))
      {
        ++ne;
        dd /= InternalFloatType(10);
      }

      using std::sqrt;

      // Setup the iteration.
      // Estimate the square root using simple manipulations.
      const InternalFloatType sqd = sqrt(dd);

      const std::int32_t original_prec_elem = my_prec_elem;

      *this = decwide_t(sqd, static_cast<exponent_type>(ne / 2));

      // Estimate 1.0 / (2.0 * x0) using simple manipulations.
      decwide_t vi(InternalFloatType(0.5F) / sqd, static_cast<exponent_type>(static_cast<exponent_type>(-ne) / 2));

      // Compute the square root of x. Coupled Newton iteration
      // as described in "Pi Unleashed" is used. During the
      // iterative steps, the precision of the calculation is
      // limited to the minimum required in order to minimize
      // the run-time.
      //
      // Book references:
      // http://www.jjj.de/pibook/pibook.html
      // http://www.springer.com/gp/book/9783642567353

      for(std::int32_t digits  = (std::int32_t) (std::numeric_limits<InternalFloatType>::digits10 - 1);
                       digits  < (std::int32_t) (original_prec_elem * decwide_t_elem_digits10);
                       digits *= static_cast<std::int32_t>(2))
      {
        // Adjust precision of the terms.
        const std::int32_t new_prec_as_digits10 =
            (std::int32_t) (digits * 2)
          + (std::max)((std::int32_t) (decwide_t_elem_digits10  + 1), (std::int32_t) 9);

           precision(new_prec_as_digits10);
        vi.precision(new_prec_as_digits10);
         x.precision(new_prec_as_digits10);

        // Next iteration of vi
        vi += vi * (((*this * vi) * static_cast<std::int32_t>(-2)) + one<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>());

        // Next iteration of *this
        *this += (vi * (-((*this) * (*this)) + x));
      }

      my_prec_elem = original_prec_elem;

      return *this;
    }

    decwide_t& negate()
    {
      if((iszero)() == false)
      {
        my_neg = (!my_neg);
      }

      return *this;
    }

    friend inline decwide_t rootn_inverse(decwide_t x, const std::int32_t p)
    {
      decwide_t result;

      if(p < static_cast<std::int32_t>(0))
      {
        result = pow(x, -p);
      }
      else if((p == 0) || ((x.isneg)() == true))
      {
        return std::numeric_limits<decwide_t>::quiet_NaN();
      }
      else if(p == 1)
      {
        result = x;
      }
      else if(p == 2)
      {
        result = 1 / sqrt(x);
      }
      else
      {
        // Compute the value of [1 / (rootn of x)] with n = p.

        // Generate the initial estimate using 1 / rootn.
        // Extract the mantissa and exponent for a "manual"
        // computation of the estimate.
        InternalFloatType dd;
        exponent_type     ne;

        x.extract_parts(dd, ne);

        // Adjust exponent and mantissa such that ne is an even power of p.
        while(ne % static_cast<exponent_type>(p))
        {
          ++ne;
          dd /= 10.0;
        }

        const std::int32_t original_prec_elem = x.my_prec_elem;

        using std::pow;

        // Estimate the initial guess of one over the root using simple manipulations.
        const InternalFloatType one_over_rtn_d = pow(dd, InternalFloatType(-1) / static_cast<InternalFloatType>(p));

        // Set the result equal to the initial guess.
        result = decwide_t(one_over_rtn_d, static_cast<exponent_type>(-ne / p));

        const decwide_t my_local_one(one<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>());

        for(std::int32_t digits  = (std::int32_t) (std::numeric_limits<InternalFloatType>::digits10 - 1);
                         digits  < (std::int32_t) (original_prec_elem * decwide_t_elem_digits10);
                         digits *= static_cast<std::int32_t>(2))
        {
          // Adjust precision of the terms.
          const std::int32_t new_prec_as_digits10 =
              (std::int32_t) (digits * 2)
            + (std::max)((std::int32_t) (decwide_t_elem_digits10  + 1), (std::int32_t) 9);

          result.precision(new_prec_as_digits10);
               x.precision(new_prec_as_digits10);

          // Perform the next iteration.
          decwide_t term = (((-pow(result, p) * x) + my_local_one) / p) + my_local_one;

          term.precision(new_prec_as_digits10);

          result *= term;
        }

             x.my_prec_elem = original_prec_elem;
        result.my_prec_elem = original_prec_elem;
      }

      return result;
    }

    // Comparison functions.
    bool (isnan)   () const { return false; }
    bool (isinf)   () const { return false; }
    bool (isfinite)() const { return true; }

    bool iszero() const
    {
      return (my_data[0U] == static_cast<limb_type>(0U));
    }

    bool isone() const
    {
      // Check if the value of *this is identically 1 or very close to 1.

      const bool not_negative = (my_neg == false);

      if(not_negative)
      {
        if((my_data[0U] == static_cast<limb_type>(1U)) && (my_exp == static_cast<exponent_type>(0)))
        {
          const typename representation_type::const_iterator it_non_zero =
            std::find_if(my_data.cbegin(),
                         my_data.cend(),
                         [](const limb_type& d) -> bool
                         {
                           return (d != static_cast<limb_type>(0U));
                         });

          return (it_non_zero == my_data.cend());
        }
        else if((my_data[0U] == static_cast<limb_type>(decwide_t_elem_mask - 1)) && (my_exp == static_cast<exponent_type>(-decwide_t_elem_digits10)))
        {
          const typename representation_type::const_iterator it_non_nine =
            std::find_if(my_data.cbegin(),
                         my_data.cend(),
                         [](const limb_type& d) -> bool
                         {
                           return (d != static_cast<limb_type>(decwide_t::decwide_t_elem_mask - 1));
                         });

          return (it_non_nine == my_data.cend());
        }
      }

      return false;
    }

    bool isint() const
    {
      if(my_fpclass != decwide_t_finite) { return false; }

      if(iszero())
      {
        return true;
      }

      if(my_exp < static_cast<exponent_type>(0))
      {
        // Here, we have |*this| < 1, so *this can not be int.
        return false;
      }

      const typename representation_type::size_type offset_decimal_part =
        static_cast<typename representation_type::size_type>(my_exp / decwide_t_elem_digits10) + 1U;

      if(offset_decimal_part >= static_cast<typename representation_type::size_type>(decwide_t_elem_number))
      {
        // The number is too large to resolve the integer part.
        // It considered to be a pure integer.
        return true;
      }

      typename representation_type::const_iterator it_non_zero =
        std::find_if(my_data.cbegin() + static_cast<std::ptrdiff_t>(offset_decimal_part),
                     my_data.cend(),
                     [](const limb_type& d) -> bool
                     {
                       return (d != static_cast<limb_type>(0U));
                     });

      return (it_non_zero == my_data.cend());
    }

    bool isneg() const { return my_neg; }
    bool ispos() const { return (!isneg()); }

    // Operators pre-increment and pre-decrement.
    decwide_t& operator++() { return *this += one<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>(); }
    decwide_t& operator--() { return *this -= one<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>(); }

    // Operators post-increment and post-decrement.
    decwide_t operator++(int) { const decwide_t w(*this); static_cast<void>(++(*this)); return w; }
    decwide_t operator--(int) { const decwide_t w(*this); static_cast<void>(--(*this)); return w; }

    // Conversion routines.
    void extract_parts(InternalFloatType& mantissa, exponent_type& exponent) const
    {
      // Extracts the mantissa as a decimal part less in magnitude
      // than 1 and the base-10 exponent parts of this decwide_t.
      // For instance 45.67e8 will be extracted as 0.4567 * e10.

      exponent = my_exp;
      mantissa = InternalFloatType(0.0F);

      limb_type p10 = static_cast<limb_type>(1U);

      {
        limb_type d0  = my_data[0U];

        for(;;)
        {
          d0 = static_cast<limb_type>(d0 / static_cast<limb_type>(10U));

          if(d0 == static_cast<limb_type>(0U))
          {
            break;
          }

          p10 = static_cast<limb_type>(p10 * static_cast<limb_type>(10U));

          ++exponent;
        }
      }

      InternalFloatType scale = InternalFloatType(1.0F) / static_cast<InternalFloatType>(p10);

     constexpr std::int32_t digit_loops = static_cast<std::int32_t>(  static_cast<std::int32_t>(std::numeric_limits<InternalFloatType>::max_digits10)
                                                                    / static_cast<std::int32_t>(decwide_t_elem_digits10))
              + static_cast<std::int32_t>(static_cast<std::int32_t>(  static_cast<std::int32_t>(std::numeric_limits<InternalFloatType>::max_digits10)
                                                                    % static_cast<std::int32_t>(decwide_t_elem_digits10)) != 0 ? 1 : 0);

      for(typename representation_type::size_type
            limb_index = 0U;
          ((limb_index < my_data.size()) && (limb_index < typename representation_type::size_type(digit_loops)));
          ++limb_index)
      {
        mantissa += (static_cast<InternalFloatType>(my_data[limb_index]) * scale);

        scale /= static_cast<InternalFloatType>(decwide_t_elem_mask);
      }

      if(my_neg)
      {
        mantissa = -mantissa;
      }
    }

    decwide_t extract_integer_part() const
    {
      // Compute the signed integer part of x.

      if(my_exp < static_cast<exponent_type>(0))
      {
        // The absolute value of the number is smaller than 1.
        // Thus the integer part is zero.
        return zero<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>();
      }
      else if(my_exp >= static_cast<exponent_type>(decwide_t_digits10 - 1))
      {
        // The number is too large to resolve the integer part.
        // Thus it is already a pure integer part.
        return *this;
      }

      // Make a local copy.
      decwide_t x = *this;

      // Clear out the decimal portion
      const std::ptrdiff_t first_clear = (static_cast<std::ptrdiff_t>(x.my_exp) / static_cast<std::ptrdiff_t>(decwide_t_elem_digits10)) + 1;
      const std::ptrdiff_t last_clear  =  static_cast<std::ptrdiff_t>(decwide_t_elem_number);

      std::fill(x.my_data.begin() + first_clear,
                x.my_data.begin() + last_clear,
                static_cast<limb_type>(0U));

      return x;
    }

    long double extract_long_double() const
    {
      // Returns the long double conversion of a decwide_t.

      long double ld;

      // Check for non-normal decwide_t.
      const decwide_t xx(fabs(*this));

      // Check for zero decwide_t.
      if(iszero() || (xx < long_double_min<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>()))
      {
        ld = 0.0L;
      }
      else
      if(xx > long_double_max<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>())
      {
        // Check if decwide_t exceeds the maximum of double.
        ld = ((my_neg == false) ?  std::numeric_limits<long double>::infinity()
                                : -std::numeric_limits<long double>::infinity());
      }
      else
      {
        ld = (long double) my_data[0U];

        long double scale = 1.0L;

        for(typename representation_type::size_type i  = (typename representation_type::size_type) decwide_t_elem_digits10;
                                                    i  < (typename representation_type::size_type) (std::numeric_limits<long double>::digits10 + 3);
                                                    i += (typename representation_type::size_type) decwide_t_elem_digits10)
        {
          scale /= (long double) decwide_t_elem_mask;

          ld += (long double) my_data[i / decwide_t_elem_digits10] * scale;
        }

        if(my_neg) { ld = -ld; }
      }

      return ld;
    }

    signed long long extract_signed_long_long() const
    {
      // Extracts a signed long long from *this.
      // If (x > maximum of signed long long) or (x < minimum of signed long long),
      // then the maximum or minimum of signed long long is returned accordingly.

      if(my_exp < static_cast<exponent_type>(0))
      {
        return static_cast<signed long long>(0);
      }

      const bool b_neg = isneg();

      unsigned long long val;

      if((!b_neg) && (*this > signed_long_long_max<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>()))
      {
        return (std::numeric_limits<signed long long>::max)();
      }
      else if(b_neg &&  (*this < signed_long_long_min<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>()))
      {
        return (std::numeric_limits<signed long long>::min)();
      }
      else
      {
        // Extract the data into an unsigned long long value.
        const decwide_t xn(fabs(extract_integer_part()));

        val = static_cast<unsigned long long>(xn.my_data[0]);

        const std::int32_t imax = (std::min)(static_cast<std::int32_t>(static_cast<std::int32_t>(xn.my_exp) / decwide_t_elem_digits10), static_cast<std::int32_t>(decwide_t_elem_number - static_cast<std::int32_t>(1)));

        for(typename representation_type::size_type
              limb_index  = static_cast<typename representation_type::size_type>(1);
              limb_index <= static_cast<typename representation_type::size_type>(imax);
            ++limb_index)
        {
          val *= static_cast<unsigned long long>(decwide_t_elem_mask);
          val += static_cast<unsigned long long>(xn.my_data[limb_index]);
        }
      }

      return ((!b_neg) ? static_cast<signed long long>(val) : static_cast<signed long long>(-static_cast<signed long long>(val)));
    }

    unsigned long long extract_unsigned_long_long() const
    {
      // Extracts an unsigned long long from *this.
      // If x exceeds the maximum of unsigned long long,
      // then the maximum of unsigned long long is returned.
      // If x is negative, then the unsigned long long cast of
      // the signed long long extracted value is returned.

      if(isneg())
      {
        return static_cast<unsigned long long>(extract_signed_long_long());
      }

      if(my_exp < static_cast<exponent_type>(0))
      {
        return static_cast<unsigned long long>(0U);
      }

      const decwide_t xn(extract_integer_part());

      unsigned long long val;

      if(xn > unsigned_long_long_max<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>())
      {
        return (std::numeric_limits<unsigned long long>::max)();
      }
      else
      {
        // Extract the data into an unsigned long long value.
        val = static_cast<unsigned long long>(xn.my_data[0]);

        const std::int32_t imax =
          (std::min)(static_cast<std::int32_t>(static_cast<std::int32_t>(xn.my_exp) / decwide_t_elem_digits10),
                     static_cast<std::int32_t>(decwide_t_elem_number - static_cast<std::int32_t>(1)));

        for(typename representation_type::size_type
              limb_index  = static_cast<typename representation_type::size_type>(1);
              limb_index <= static_cast<typename representation_type::size_type>(imax);
            ++limb_index)
        {
          val *= static_cast<unsigned long long>(decwide_t_elem_mask);
          val += static_cast<unsigned long long>(xn.my_data[limb_index]);
        }
      }

      return val;
    }

    explicit operator long double       () const { return extract_long_double(); }
    explicit operator double            () const { return (double) extract_long_double(); }
    explicit operator float             () const { return (float) extract_long_double(); }
    explicit operator signed char       () const { return (signed char) extract_signed_long_long(); }
    explicit operator unsigned char     () const { return (unsigned char) extract_unsigned_long_long(); }
    explicit operator signed short      () const { return (signed short) extract_signed_long_long(); }
    explicit operator unsigned short    () const { return (unsigned short) extract_unsigned_long_long(); }
    explicit operator signed int        () const { return (signed int) extract_signed_long_long(); }
    explicit operator unsigned int      () const { return (unsigned int) extract_unsigned_long_long(); }
    explicit operator signed long       () const { return (signed long) extract_signed_long_long(); }
    explicit operator unsigned long     () const { return (unsigned long) extract_unsigned_long_long(); }
    explicit operator signed long long  () const { return extract_signed_long_long(); }
    explicit operator unsigned long long() const { return extract_unsigned_long_long(); }

  private:
    #if !defined(WIDE_DECIMAL_DISABLE_DYNAMIC_MEMORY_ALLOCATION)
    #else
    static limb_type           my_school_mul_pool[std::uint32_t((decwide_t_elems_for_kara - 1) * 2)];
    static limb_type           my_kara_mul_pool  [detail::a029750::a029750_as_constexpr(std::uint32_t(decwide_t_elems_for_fft - 1)) * 8UL];
    static fft_float_type      my_af_fft_mul_pool[detail::a000079::a000079_as_constexpr(std::uint32_t(decwide_t_elem_number)) * 4UL];
    static fft_float_type      my_bf_fft_mul_pool[detail::a000079::a000079_as_constexpr(std::uint32_t(decwide_t_elem_number)) * 4UL];
    static representation_type my_n_data_for_add_sub;
    #endif

    representation_type my_data;
    exponent_type       my_exp;
    bool                my_neg;
    fpclass_type        my_fpclass;
    std::int32_t        my_prec_elem;

    static decwide_t from_lst(std::initializer_list<limb_type> limb_values,
                              const exponent_type e = 0,
                              const bool is_neg = false)
    {
      // Initialization from initializer list of limbs,
      // exponent value (normed to limb granularity)
      // and optional sign flag.
      decwide_t a;

      a.my_data      = representation_type(limb_values);
      a.my_exp       = e;
      a.my_neg       = is_neg;
      a.my_fpclass   = decwide_t_finite;
      a.my_prec_elem = decwide_t_elem_number;

      return a;
    }

    void from_unsigned_long_long(const unsigned long long u)
    {
      my_exp = static_cast<exponent_type>(0);

      std::uint_fast32_t i = static_cast<std::uint_fast32_t>(0U);

      unsigned long long uu = u;

      using local_tmp_array_type =
        std::array<limb_type, std::size_t(std::numeric_limits<unsigned long long>::digits10 / static_cast<int>(decwide_t_elem_digits10)) + 3U>;

      local_tmp_array_type tmp;
      tmp.fill(static_cast<limb_type>(0U));

      while
      (
        (   (uu != static_cast<unsigned long long>(0U))
         && ( i <  static_cast<std::uint_fast32_t>(std::tuple_size<local_tmp_array_type>::value)))
      )
      {
        tmp[i] = static_cast<limb_type>(uu % static_cast<unsigned long long>(decwide_t_elem_mask));

        uu = static_cast<unsigned long long>(uu / static_cast<unsigned long long>(decwide_t_elem_mask));

        ++i;
      }

      if(i > static_cast<std::uint_fast32_t>(1U))
      {
        my_exp = static_cast<exponent_type>(my_exp + static_cast<exponent_type>((i - 1U) * static_cast<std::uint_fast32_t>(decwide_t_elem_digits10)));
      }

      std::reverse(tmp.begin(), tmp.begin() + i);

      const std::uint_fast32_t copy_limit =
        (std::min)(static_cast<std::uint_fast32_t>(std::tuple_size<local_tmp_array_type>::value),
                   static_cast<std::uint_fast32_t>(decwide_t_elem_number));

      std::copy(tmp.cbegin(),
                tmp.cbegin() + std::ptrdiff_t((std::min)(i, copy_limit)),
                my_data.begin());

      std::fill(my_data.begin() + std::ptrdiff_t((std::min)(i, copy_limit)),
                my_data.end(),
                limb_type(0U));
    }

    template<typename FloatingPointType>
    void from_builtin_float_type(const FloatingPointType l)
    {
      const bool b_neg = (l < static_cast<FloatingPointType>(0.0L));

      const FloatingPointType my_ld = ((!b_neg) ? l : -l);

      if(my_ld < (std::numeric_limits<FloatingPointType>::min)())
      {
        operator=(zero<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>());
      }
      else
      {
        const native_float_parts<FloatingPointType> ld_parts(my_ld);

        // Create a decwide_t from the fractional part of the
        // mantissa expressed as an unsigned long long.
        from_unsigned_long_long(ld_parts.get_mantissa());

        // Scale the unsigned long long representation to the fractional
        // part of the long double and multiply with the base-2 exponent.
        const int p2 = ld_parts.get_exponent() - (std::numeric_limits<FloatingPointType>::digits - 1);

        if     (p2 <  -1) { *this *= pow(half<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>(), -p2); }
        else if(p2 == -1) { *this *=     half<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>(); }
        else if(p2 ==  0) { ; }
        else if(p2 ==  1) { *this *= 2U; }
        else              { *this *= pow(two<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>(), p2); }

        my_neg = b_neg;
      }
    }

    template<const std::int32_t OtherDigits10>
    void eval_mul_dispatch_multiplication_method(
      const decwide_t<OtherDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>& v,
      const std::int32_t prec_elems_for_multiply,
      const typename std::enable_if<(    (OtherDigits10 == MyDigits10)
                                     && !(decwide_t<OtherDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>::decwide_t_elem_number >= decwide_t_elems_for_kara))>::type* = nullptr)
    {
      // Use school multiplication.
      #if !defined(WIDE_DECIMAL_DISABLE_DYNAMIC_MEMORY_ALLOCATION)
      limb_type* my_school_mul_pool = new limb_type[(std::size_t) ((std::size_t) prec_elems_for_multiply * 2U)];
      #endif

      limb_type* result = my_school_mul_pool;

      detail::eval_multiply_n_by_n_to_2n(result,
                                         typename std::add_const<limb_type*>::type(my_data.data()),
                                         typename std::add_const<limb_type*>::type(v.my_data.data()),
                                         prec_elems_for_multiply);

      // Handle a potential carry.
      if(result[0U] != static_cast<limb_type>(0U))
      {
        my_exp = static_cast<exponent_type>(my_exp + static_cast<exponent_type>(decwide_t_elem_digits10));

        // Shift the result of the multiplication one element to the right.
        std::copy(result,
                  result + static_cast<std::ptrdiff_t>(prec_elems_for_multiply),
                  my_data.begin());
      }
      else
      {
        std::copy(result + 1,
                  result + (std::min)(static_cast<std::int32_t>(prec_elems_for_multiply + 1), decwide_t_elem_number),
                  my_data.begin());
      }

      #if !defined(WIDE_DECIMAL_DISABLE_DYNAMIC_MEMORY_ALLOCATION)
      // De-allocate the dynamic memory for school multiplication arrays.
      delete [] my_school_mul_pool;
      #endif
    }

    template<const std::int32_t OtherDigits10>
    void eval_mul_dispatch_multiplication_method(
      const decwide_t<OtherDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>& v,
      const std::int32_t prec_elems_for_multiply,
      const typename std::enable_if<(   (OtherDigits10 == MyDigits10)
                                     && (decwide_t<OtherDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>::decwide_t_elem_number >= decwide_t_elems_for_kara)
                                     && (decwide_t<OtherDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>::decwide_t_elem_number <  decwide_t_elems_for_fft))>::type* = nullptr)
    {
      if(prec_elems_for_multiply < decwide_t_elems_for_kara)
      {
        // Use school multiplication.
        #if !defined(WIDE_DECIMAL_DISABLE_DYNAMIC_MEMORY_ALLOCATION)
        limb_type* my_school_mul_pool = new limb_type[(std::size_t) ((std::size_t) prec_elems_for_multiply * 2U)];
        #endif

        limb_type* result = my_school_mul_pool;

        detail::eval_multiply_n_by_n_to_2n(result,
                                           typename std::add_const<limb_type*>::type(my_data.data()),
                                           typename std::add_const<limb_type*>::type(v.my_data.data()),
                                           prec_elems_for_multiply);

        // Handle a potential carry.
        if(result[0U] != static_cast<limb_type>(0U))
        {
          my_exp = static_cast<exponent_type>(my_exp + static_cast<exponent_type>(decwide_t_elem_digits10));

          // Shift the result of the multiplication one element to the right.
          std::copy(result,
                    result + (std::min)(prec_elems_for_multiply, decwide_t_elems_for_kara),
                    my_data.begin());
        }
        else
        {
          std::copy(result + 1,
                    result + (std::min)(static_cast<std::int32_t>(prec_elems_for_multiply + 1), decwide_t_elems_for_kara),
                    my_data.begin());
        }

        #if !defined(WIDE_DECIMAL_DISABLE_DYNAMIC_MEMORY_ALLOCATION)
        // De-allocate the dynamic memory for the school multiplication arrays.
        delete [] my_school_mul_pool;
        #endif
      }
      else if(   (prec_elems_for_multiply >= decwide_t_elems_for_kara)
              && (prec_elems_for_multiply <  decwide_t_elems_for_fft))
      {
        // Karatsuba multiplication.

        // Sloanes's A029750: Numbers of the form 2^k times 1, 3, 5 or 7.
        const std::uint32_t kara_elems_for_multiply =
          detail::a029750::a029750_as_runtime_value(static_cast<std::uint32_t>(prec_elems_for_multiply));

        #if !defined(WIDE_DECIMAL_DISABLE_DYNAMIC_MEMORY_ALLOCATION)
        limb_type* my_kara_mul_pool = new limb_type[kara_elems_for_multiply * 8U];
        #endif

        limb_type* u_local = my_kara_mul_pool + (kara_elems_for_multiply * 0U);
        limb_type* v_local = my_kara_mul_pool + (kara_elems_for_multiply * 1U);
        limb_type* result  = my_kara_mul_pool + (kara_elems_for_multiply * 2U);
        limb_type* t       = my_kara_mul_pool + (kara_elems_for_multiply * 4U);

        std::copy(  my_data.cbegin(),   my_data.cbegin() + prec_elems_for_multiply, u_local);
        std::copy(v.my_data.cbegin(), v.my_data.cbegin() + prec_elems_for_multiply, v_local);
        std::fill(u_local + prec_elems_for_multiply, u_local + kara_elems_for_multiply, limb_type(0U));
        std::fill(v_local + prec_elems_for_multiply, v_local + kara_elems_for_multiply, limb_type(0U));

        detail::eval_multiply_kara_n_by_n_to_2n(result,
                                                u_local,
                                                v_local,
                                                kara_elems_for_multiply,
                                                t);

        // Handle a potential carry.
        if(result[0U] != static_cast<limb_type>(0U))
        {
          my_exp = static_cast<exponent_type>(my_exp + static_cast<exponent_type>(decwide_t_elem_digits10));

          // Shift the result of the multiplication one element to the right.
          std::copy(result,
                    result + (std::min)(prec_elems_for_multiply, decwide_t_elem_number),
                    my_data.begin());
        }
        else
        {
          std::copy(result + 1,
                    result + (std::min)(static_cast<std::int32_t>(prec_elems_for_multiply + 1), decwide_t_elem_number),
                    my_data.begin());
        }

        #if !defined(WIDE_DECIMAL_DISABLE_DYNAMIC_MEMORY_ALLOCATION)
        // De-allocate the dynamic memory for the Karatsuba multiplication arrays.
        delete [] my_kara_mul_pool;
        #endif
      }
      else
      {
      }
    }

    template<const std::int32_t OtherDigits10>
    void eval_mul_dispatch_multiplication_method(
      const decwide_t<OtherDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>& v,
      const std::int32_t prec_elems_for_multiply,
      const typename std::enable_if<(   (OtherDigits10 == MyDigits10)
                                     && (decwide_t<OtherDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>::decwide_t_elem_number >= decwide_t_elems_for_fft))>::type* = nullptr)
    {
      if(prec_elems_for_multiply < decwide_t_elems_for_kara)
      {
        // Use school multiplication.
        #if !defined(WIDE_DECIMAL_DISABLE_DYNAMIC_MEMORY_ALLOCATION)
        limb_type* my_school_mul_pool = new limb_type[prec_elems_for_multiply * 2];
        #endif

        limb_type* result = my_school_mul_pool;

        detail::eval_multiply_n_by_n_to_2n(result,
                                           typename std::add_const<limb_type*>::type(my_data.data()),
                                           typename std::add_const<limb_type*>::type(v.my_data.data()),
                                           prec_elems_for_multiply);

        // Handle a potential carry.
        if(result[0U] != static_cast<limb_type>(0U))
        {
          my_exp += static_cast<exponent_type>(decwide_t_elem_digits10);

          // Shift the result of the multiplication one element to the right.
          std::copy(result,
                    result + (std::min)(prec_elems_for_multiply, decwide_t_elems_for_kara),
                    my_data.begin());
        }
        else
        {
          std::copy(result + 1,
                    result + (std::min)(static_cast<std::int32_t>(prec_elems_for_multiply + 1), decwide_t_elems_for_kara),
                    my_data.begin());
        }

        #if !defined(WIDE_DECIMAL_DISABLE_DYNAMIC_MEMORY_ALLOCATION)
        // De-allocate the dynamic memory for the school multiplication arrays.
        delete [] my_school_mul_pool;
        #endif
      }
      else if(   (prec_elems_for_multiply >= decwide_t_elems_for_kara)
              && (prec_elems_for_multiply <  decwide_t_elems_for_fft))
      {
        // Use Karatsuba multiplication multiplication.

        // Sloanes's A029750: Numbers of the form 2^k times 1, 3, 5 or 7.
        const std::uint32_t kara_elems_for_multiply =
          (std::min)(detail::a029750::a029750_as_runtime_value(static_cast<std::uint32_t>(prec_elems_for_multiply)),
                     std::uint32_t(detail::a029750::a029750_as_runtime_value(decwide_t_elems_for_fft - 1) * 8UL));

        #if !defined(WIDE_DECIMAL_DISABLE_DYNAMIC_MEMORY_ALLOCATION)
        limb_type* my_kara_mul_pool = new limb_type[kara_elems_for_multiply * 8U];
        #endif

        limb_type* u_local = my_kara_mul_pool + (kara_elems_for_multiply * 0U);
        limb_type* v_local = my_kara_mul_pool + (kara_elems_for_multiply * 1U);
        limb_type* result  = my_kara_mul_pool + (kara_elems_for_multiply * 2U);
        limb_type* t       = my_kara_mul_pool + (kara_elems_for_multiply * 4U);

        std::copy(  my_data.cbegin(),   my_data.cbegin() + prec_elems_for_multiply, u_local);
        std::copy(v.my_data.cbegin(), v.my_data.cbegin() + prec_elems_for_multiply, v_local);
        std::fill(u_local + prec_elems_for_multiply, u_local + kara_elems_for_multiply, limb_type(0U));
        std::fill(v_local + prec_elems_for_multiply, v_local + kara_elems_for_multiply, limb_type(0U));

        detail::eval_multiply_kara_n_by_n_to_2n(result,
                                                u_local,
                                                v_local,
                                                kara_elems_for_multiply,
                                                t);

        // Handle a potential carry.
        if(result[0U] != static_cast<limb_type>(0U))
        {
          my_exp += static_cast<exponent_type>(decwide_t_elem_digits10);

          // Shift the result of the multiplication one element to the right.
          std::copy(result,
                    result + (std::min)(prec_elems_for_multiply, decwide_t_elems_for_fft),
                    my_data.begin());
        }
        else
        {
          std::copy(result + 1,
                    result + (std::min)(static_cast<std::int32_t>(prec_elems_for_multiply + 1), decwide_t_elems_for_fft),
                    my_data.begin());
        }

        #if !defined(WIDE_DECIMAL_DISABLE_DYNAMIC_MEMORY_ALLOCATION)
        // De-allocate the dynamic memory for the Karatsuba multiplication arrays.
        delete [] my_kara_mul_pool;
        #endif
      }
      else if(prec_elems_for_multiply >= decwide_t_elems_for_fft)
      {
        // Use FFT-based multiplication.

        // Determine the required FFT size n_fft,
        // where n_fft must be a power of two.

        // We use half-limbs in the FFT in order to reduce
        // the size of the data points in the FFTs.
        // This helps preserve precision for large
        // array lengths.

        // The size is doubled in order to contain the multiplication
        // result. This is because we are performing (n * n -> 2n)
        // multiplication. Furthermore, the FFT size is doubled again
        // since half-limbs are used.

        // Obtain the needed FFT size doubled (and doubled again),
        // with the added condition of needing to be a power of 2.
        const std::uint32_t n_fft = static_cast<std::uint32_t>(detail::a000079::a000079_as_constexpr(std::uint32_t(prec_elems_for_multiply)) * UINT32_C(4));

        #if !defined(WIDE_DECIMAL_DISABLE_DYNAMIC_MEMORY_ALLOCATION)
        fft_float_type* my_af_fft_mul_pool = new fft_float_type[n_fft];
        fft_float_type* my_bf_fft_mul_pool = new fft_float_type[n_fft];
        #endif

        fft_float_type* af = my_af_fft_mul_pool;
        fft_float_type* bf = my_bf_fft_mul_pool;

        detail::mul_loop_fft(my_data.data(),
                             typename std::add_const<limb_type*>::type(my_data.data()),
                             typename std::add_const<limb_type*>::type(v.my_data.data()),
                             af,
                             bf,
                             static_cast<std::int32_t>(prec_elems_for_multiply),
                             n_fft);

        if(my_data.front() != static_cast<limb_type>(0U))
        {
          // Adjust the exponent because of the internal scaling of the FFT multiplication.
          my_exp += static_cast<exponent_type>(decwide_t_elem_digits10);
        }
        else
        {
          // Justify the data if necessary.
          std::copy(my_data.cbegin() +  1,
                    my_data.cbegin() + (std::min)(static_cast<std::int32_t>(prec_elems_for_multiply + 1), decwide_t_elem_number),
                    my_data.begin());

          my_data.back() = static_cast<limb_type>(0U);
        }

        #if !defined(WIDE_DECIMAL_DISABLE_DYNAMIC_MEMORY_ALLOCATION)
        // De-allocate the dynamic memory for the FFT result arrays.
        delete [] my_af_fft_mul_pool;
        delete [] my_bf_fft_mul_pool;
        #endif
      }
      else
      {
      }
    }

    #if !defined(WIDE_DECIMAL_DISABLE_CONSTRUCT_FROM_STRING)
    bool rd_string(const char* s)
    {
      std::string str(s);

      // Get a possible exponent and remove it.
      my_exp = static_cast<exponent_type>(0);

      std::size_t pos;

      if(   ((pos = str.find('e')) != std::string::npos)
         || ((pos = str.find('E')) != std::string::npos)
        )
      {
        // Remove the exponent part from the string.
        my_exp = Util::numeric_cast<exponent_type>(static_cast<const char*>(str.c_str() + (pos + 1U)));

        str = str.substr(static_cast<std::size_t>(0U), pos);
      }

      // Get a possible +/- sign and remove it.
      my_neg = false;

      if((pos = str.find(static_cast<char>('-'))) != std::string::npos)
      {
        my_neg = true;

        str.erase(pos, static_cast<std::uint_fast32_t>(1U));
      }

      if((pos = str.find(static_cast<char>('+'))) != std::string::npos)
      {
        str.erase(pos, static_cast<std::uint_fast32_t>(1U));
      }

      // Remove leading zeros for all input types.
      const std::string::const_iterator fwd_it_leading_zero =
        std::find_if(str.cbegin(),
                     str.cend(),
                     [](const char& c) -> bool
                     {
                       return (c != static_cast<char>('0'));
                     });

      if(fwd_it_leading_zero != str.cbegin())
      {
        if(fwd_it_leading_zero == str.cend())
        {
          // The string contains nothing but leading zeros.
          // This string represents zero.
          operator=(zero<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>());

          return true;
        }
        else
        {
          str.erase(str.cbegin(), fwd_it_leading_zero);
        }
      }

      // Put the input string into the standard decwide_t input form
      // aaa.bbbbE+/-n, where aa has 1...decwide_t_elem_digits10, bbbb has an
      // even multiple of decwide_t_elem_digits10 which are possibly zero padded
      // on the right-end, and n is a signed 32-bit integer which is an
      // even multiple of decwide_t_elem_digits10.

      // Find a possible decimal point.
      pos = str.find(static_cast<char>('.'));

      if(pos != std::string::npos)
      {
        // Remove all trailing insignificant zeros.
        const std::string::const_reverse_iterator rit_non_zero =
          std::find_if(str.crbegin(),
                       str.crend(),
                       [](const char& c) -> bool
                       {
                         return (c != static_cast<char>('0'));
                       });

        if(rit_non_zero != str.crbegin())
        {
          const std::string::difference_type ofs =   static_cast<std::string::difference_type>(str.length())
                                                   - std::distance<std::string::const_reverse_iterator>(str.crbegin(), rit_non_zero);

          str.erase(str.cbegin() + ofs, str.cend());
        }

        // Check if the input is identically zero.
        if(str == std::string("."))
        {
          operator=(zero<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>());
          return true;
        }

        // Remove leading significant zeros just after the decimal point
        // and adjust the exponent accordingly.
        // Note that the while-loop operates only on strings of the form ".000abcd..."
        // and peels away the zeros just after the decimal point.
        if(str.at(static_cast<std::uint_fast32_t>(0U)) == static_cast<char>('.'))
        {
          const std::string::const_iterator it_non_zero =
            std::find_if(str.cbegin() + 1U,
                         str.cend(),
                         [](const char& c) -> bool
                         {
                           return (c != static_cast<char>('0'));
                         });

          std::uint_fast32_t delta_exp = static_cast<std::uint_fast32_t>(0U);

          if(str.at(static_cast<std::uint_fast32_t>(1U)) == static_cast<char>('0'))
          {
            delta_exp = static_cast<std::uint_fast32_t>(it_non_zero - (str.cbegin() + 1U));
          }

          // Bring one single digit into the mantissa and adjust exponent accordingly.
          str.erase(str.cbegin(), it_non_zero);

          str.insert(static_cast<std::uint_fast32_t>(1U), ".");

          my_exp = static_cast<exponent_type>(my_exp - static_cast<exponent_type>(delta_exp + 1U));
        }
      }
      else
      {
        // Input string has no decimal point: Append decimal point.
        str.append(".");
      }

      // Shift the decimal point such that the exponent is an even multiple of decwide_t_elem_digits10.
            std::ptrdiff_t n_shift   = static_cast<std::ptrdiff_t>(0);
      const std::ptrdiff_t n_exp_rem = static_cast<std::ptrdiff_t>(my_exp % static_cast<exponent_type>(decwide_t_elem_digits10));

      if((my_exp % static_cast<exponent_type>(decwide_t_elem_digits10)) != static_cast<exponent_type>(0))
      {
        n_shift = ((my_exp < static_cast<exponent_type>(0))
                    ? static_cast<std::ptrdiff_t>(n_exp_rem + static_cast<std::ptrdiff_t>(decwide_t_elem_digits10))
                    : static_cast<std::ptrdiff_t>(n_exp_rem));
      }

      // Make sure that there are enough digits for the decimal point shift.
      pos = str.find(static_cast<char>('.'));

      std::ptrdiff_t pos_plus_one = static_cast<std::ptrdiff_t>(pos + 1);

      if((static_cast<std::ptrdiff_t>(str.length()) - pos_plus_one) < n_shift)
      {
        const std::ptrdiff_t sz = static_cast<std::ptrdiff_t>(n_shift - (static_cast<std::ptrdiff_t>(str.length()) - pos_plus_one));

        str.append(std::string(static_cast<std::string::size_type>(sz), static_cast<char>('0')));
      }

      // Do the decimal point shift.
      if(n_shift != static_cast<std::ptrdiff_t>(0))
      {
        str.insert(static_cast<std::string::size_type>(pos_plus_one + n_shift), ".");

        str.erase(pos, static_cast<std::ptrdiff_t>(1));

        my_exp = static_cast<exponent_type>(my_exp - static_cast<exponent_type>(n_shift));
      }

      // Cut the size of the mantissa to <= decwide_t_elem_digits10.
      pos          = str.find(static_cast<char>('.'));
      pos_plus_one = static_cast<std::ptrdiff_t>(pos + 1U);

      if(pos > static_cast<std::ptrdiff_t>(decwide_t_elem_digits10))
      {
        const std::int32_t n_pos         = static_cast<std::int32_t>(pos);
        const std::int32_t n_rem_is_zero = ((static_cast<std::int32_t>(n_pos % decwide_t_elem_digits10) == static_cast<std::int32_t>(0)) ? static_cast<std::int32_t>(1) : static_cast<std::int32_t>(0));
        const std::int32_t n             = static_cast<std::int32_t>(static_cast<std::int32_t>(n_pos / decwide_t_elem_digits10) - n_rem_is_zero);

        str.insert(static_cast<std::uint_fast32_t>(static_cast<std::int32_t>(n_pos - static_cast<std::int32_t>(n * decwide_t_elem_digits10))), ".");

        str.erase(static_cast<std::string::size_type>(pos_plus_one), static_cast<std::uint_fast32_t>(1U));

        my_exp = static_cast<exponent_type>(my_exp + static_cast<exponent_type>(static_cast<exponent_type>(n) * static_cast<exponent_type>(decwide_t_elem_digits10)));
      }

      // Pad the decimal part such that its value is an even
      // multiple of decwide_t_elem_digits10.
      pos          = str.find(static_cast<char>('.'));
      pos_plus_one = static_cast<std::ptrdiff_t>(pos + 1);

      const std::int32_t n_dec = static_cast<std::int32_t>(static_cast<std::int32_t>(str.length() - 1U) - static_cast<std::int32_t>(pos));
      const std::int32_t n_rem = static_cast<std::int32_t>(n_dec % decwide_t_elem_digits10);
            std::int32_t n_cnt = ((n_rem != static_cast<std::int32_t>(0)) ? static_cast<std::int32_t>(decwide_t_elem_digits10 - n_rem)
                                                                          : static_cast<std::int32_t>(0));

      if(n_cnt != static_cast<std::int32_t>(0))
      {
        str.append(static_cast<std::string::size_type>(n_cnt), static_cast<char>('0'));
      }

      // Truncate decimal part if it is too long.
      const std::ptrdiff_t max_dec = static_cast<std::ptrdiff_t>((decwide_t_elem_number - 1) * decwide_t_elem_digits10);

      if(static_cast<std::ptrdiff_t>(str.length() - pos) > max_dec)
      {
        str = str.substr(static_cast<std::string::size_type>(0),
                         static_cast<std::string::size_type>(pos_plus_one + max_dec));
      }

      // Now the input string has the standard decwide_t input form.
      // (See the comment above.)

      // Set all the data elements to 0.
      std::fill(my_data.begin(), my_data.end(), static_cast<limb_type>(0));

      // Extract the data.

      // First get the digits to the left of the decimal point...
      my_data[static_cast<typename representation_type::size_type>(0U)] =
        Util::numeric_cast<limb_type>(str.substr(static_cast<std::ptrdiff_t>(0), pos));

      // ...then get the remaining digits to the right of the decimal point.
      const std::string::difference_type i_end = ((static_cast<std::string::difference_type>(str.length()) - pos_plus_one) / static_cast<std::string::difference_type>(decwide_t_elem_digits10));

      for(std::string::difference_type i = static_cast<std::string::difference_type>(0); i < i_end; ++i)
      {
        const std::string::const_iterator it =   str.cbegin()
                                               + static_cast<std::string::difference_type>(pos_plus_one)
                                               + (i * static_cast<std::string::difference_type>(decwide_t_elem_digits10));

        const typename representation_type::size_type i1 = static_cast<typename representation_type::size_type>(i + 1);

        const std::string str_i1(it,
                                 it + static_cast<std::string::difference_type>(decwide_t_elem_digits10));

        my_data[i1] = Util::numeric_cast<limb_type>(str_i1);
      }

      return true;
    }
    #endif //!(WIDE_DECIMAL_DISABLE_CONSTRUCT_FROM_STRING)

    #if !defined(WIDE_DECIMAL_DISABLE_IOSTREAM)
    void get_output_string(std::string& str, exponent_type& the_exp, const std::uint_fast32_t number_of_digits) const
    {
      // Determine the number of elements needed to provide the requested digits from decwide_t.
      const std::uint_fast32_t number_of_elements =
        (std::min)(static_cast<std::uint_fast32_t>((number_of_digits / static_cast<std::uint_fast32_t>(decwide_t_elem_digits10)) + 2U),
                   static_cast<std::uint_fast32_t>(decwide_t_elem_number));

      // Extract the remaining digits from decwide_t after the decimal point.
      char p_str[10U] = { 0 };
      char* p_end = util::baselexical_cast(my_data[0], p_str);

      str = std::string(p_str, p_end);

      // Extract all of the digits from decwide_t, beginning with the first data element.
      for(std::uint_fast32_t i = static_cast<std::uint_fast32_t>(1U); i < number_of_elements; i++)
      {
        using data_element_rep_type = typename std::conditional<(std::numeric_limits<limb_type>::digits <= 32),
                                                                 std::uint32_t,
                                                                 limb_type>::type;

        std::stringstream ss;

        ss << std::setw(static_cast<std::streamsize>(decwide_t_elem_digits10))
           << std::setfill(static_cast<char>('0'))
           << data_element_rep_type(my_data[i]);

        str += ss.str();
      }

      // Cut the output to the size of the precision.
      if(str.length() > number_of_digits)
      {
        // Get the digit after the last needed digit for rounding
        const std::uint32_t round = static_cast<std::uint32_t>(static_cast<std::uint32_t>(str.at(number_of_digits)) - static_cast<std::uint32_t>('0'));

        // Truncate the string
        str = str.substr(static_cast<std::uint_fast32_t>(0U), number_of_digits);

        if(round >= static_cast<std::uint32_t>(5U))
        {
          std::uint_fast32_t ix = static_cast<std::uint_fast32_t>(str.length() - 1U);

          // Every trailing 9 must be rounded up
          while(ix && (static_cast<std::int32_t>(str.at(ix)) - static_cast<std::int32_t>('0') == static_cast<std::int32_t>(9)))
          {
            str.at(ix) = static_cast<char>('0');
            --ix;
          }

          if(!ix)
          {
            // There were nothing but trailing nines.
            if(static_cast<std::int32_t>(static_cast<std::int32_t>(str.at(ix)) - static_cast<std::int32_t>(0x30)) == static_cast<std::int32_t>(9))
            {
              // Increment up to the next order and adjust exponent.
              str.at(ix) = static_cast<char>('1');
              ++the_exp;
            }
            else
            {
              // Round up this digit.
              ++str.at(ix);
            }
          }
          else
          {
            // Round up the last digit.
            ++str[ix];
          }
        }
      }
    }

    void wr_string(std::string& str, std::ostream& os) const
    {
      // Assess the format flags.
      const std::ios::fmtflags my_flags = os.flags();

      // Obtain the showpos flag.
      const bool my_showpos   = ((my_flags & std::ios::showpos)   != static_cast<std::ios::fmtflags>(0U));
      const bool my_uppercase = ((my_flags & std::ios::uppercase) != static_cast<std::ios::fmtflags>(0U));

      // Get the base-10 exponent.
      exponent_type the_exp = (exponent_type) ilogb(*this);

      // Get the output stream's precision and limit it to max_digits10.
      // Erroneous zero or negative precision (theoretically impossible)
      // will be set to ostream's default precision.
      static const std::stringstream str_default;
      static const std::streamsize   prec_default = str_default.precision();

      const std::uint_fast32_t os_precision  = ((os.precision() <= static_cast<std::streamsize>(0)) ? static_cast<std::uint_fast32_t>(prec_default) : static_cast<std::uint_fast32_t>(os.precision()));

      // Determine the kind of output format requested (scientific, fixed, none).
      detail::os_float_field_type my_float_field;

      if     ((my_flags & std::ios::scientific) != static_cast<std::ios::fmtflags>(0U)) { my_float_field = detail::os_float_field_scientific; }
      else if((my_flags & std::ios::fixed)      != static_cast<std::ios::fmtflags>(0U)) { my_float_field = detail::os_float_field_fixed; }
      else { my_float_field = detail::os_float_field_none; }

      bool use_scientific = false;
      bool use_fixed      = false;

      if     (my_float_field == detail::os_float_field_scientific) { use_scientific = true; }
      else if(my_float_field == detail::os_float_field_fixed)      { use_fixed      = true; }
      else // os_float_field_none
      {
        // Set up the range for dynamic detection of scientific notation.
        // If the exponent is less than -4 or larger than a precision-dependent
        // positive bound, then scientific notation is used.
        static const exponent_type neg_bound_for_scientific_neg_exp = static_cast<exponent_type>(-4);
               const exponent_type min_bound_for_scientific_pos_exp = (std::max)(static_cast<exponent_type>(os_precision), static_cast<exponent_type>(prec_default));
               const exponent_type pos_bound_for_scientific_pos_exp = (std::min)(static_cast<exponent_type>(decwide_t_digits10), min_bound_for_scientific_pos_exp);

        if(   (the_exp <  neg_bound_for_scientific_neg_exp)
           || (the_exp >= pos_bound_for_scientific_pos_exp)
          )
        {
          use_scientific = true;
        }
        else
        {
          use_fixed = true;
        }
      }

      // Ascertain the number of digits requested from decwide_t.
      std::uint_fast32_t the_number_of_digits_i_want_from_decwide_t = static_cast<std::uint_fast32_t>(0U);

      const std::uint_fast32_t max10_plus_one = static_cast<std::uint_fast32_t>(decwide_t_max_digits10 + 1);

      if(use_scientific)
      {
        // The float-field is scientific. The number of digits is given by
        // (1 + the ostream's precision), not to exceed (max_digits10 + 1).
        const std::uint_fast32_t prec_plus_one  = static_cast<std::uint_fast32_t>(1U + os_precision);
        the_number_of_digits_i_want_from_decwide_t = (std::min)(max10_plus_one, prec_plus_one);
      }
      else if(use_fixed)
      {
        // The float-field is scientific. The number of all-digits depends
        // on the form of the number.

        if(the_exp >= static_cast<exponent_type>(0))
        {
          // If the number is larger than 1 in absolute value, then the number of
          // digits is given by the width of the integer part plus the ostream's
          // precision, not to exceed (max_digits10 + 1).
          const std::uint_fast32_t exp_plus_one = static_cast<std::uint_fast32_t>(the_exp + 1);
          const std::uint_fast32_t exp_plus_one_plus_my_precision = static_cast<std::uint_fast32_t>(exp_plus_one + os_precision);

          the_number_of_digits_i_want_from_decwide_t = (std::min)(exp_plus_one_plus_my_precision, max10_plus_one);
        }
        else
        {
          const exponent_type exp_plus_one = static_cast<exponent_type>(the_exp + 1);
          const exponent_type exp_plus_one_plus_my_precision = static_cast<exponent_type>(exp_plus_one + static_cast<exponent_type>(os_precision));

          the_number_of_digits_i_want_from_decwide_t = (std::min)(static_cast<std::uint_fast32_t>((std::max)(exp_plus_one_plus_my_precision, static_cast<exponent_type>(0))), max10_plus_one);
        }
      }

      // If the float field is not set, reduce the number of digits requested
      // from decwide_t such that it neither exceeds the ostream's precision
      // nor decwide_t's max_digits10.
      if(my_float_field == detail::os_float_field_none)
      {
        const std::uint_fast32_t max_digits = (std::min)(os_precision, static_cast<std::uint_fast32_t>(decwide_t_max_digits10));
        the_number_of_digits_i_want_from_decwide_t = (std::min)(the_number_of_digits_i_want_from_decwide_t, max_digits);
      }

      // Extract the rounded output string with the desired number of digits.
      get_output_string(str, the_exp, the_number_of_digits_i_want_from_decwide_t);

      // Obtain additional format information.
      const bool my_showpoint  = ((my_flags & std::ios::showpoint)  != static_cast<std::ios::fmtflags>(0U));

      // Write the output string in the desired format.
      if     (my_float_field == detail::os_float_field_scientific) { wr_string_scientific(str, the_exp, os_precision, my_showpoint, my_uppercase); }
      else if(my_float_field == detail::os_float_field_fixed)      { wr_string_fixed     (str, the_exp, os_precision, my_showpoint); }
      else // os_float_field_none
      {
        (use_scientific ? wr_string_scientific(str, the_exp, os_precision, my_showpoint, my_uppercase, true)
                        : wr_string_fixed     (str, the_exp, os_precision, my_showpoint, true));
      }

      // Append the sign.
      if     (isneg())    { str.insert(static_cast<std::uint_fast32_t>(0U), "-"); }
      else if(my_showpos) { str.insert(static_cast<std::uint_fast32_t>(0U), "+"); }

      // Handle std::setw(...), std::setfill(...), std::left, std::right, std::internal.
      const std::uint_fast32_t my_width = ((os.width() >= static_cast<std::streamsize>(0)) ? static_cast<std::uint_fast32_t>(os.width())
                                                                                    : static_cast<std::uint_fast32_t>(0U));

      if(my_width > str.length())
      {
        // Get the number of fill characters.
        const std::uint_fast32_t n_fill = static_cast<std::uint_fast32_t>(my_width - str.length());

        // Left-justify is the exception, std::right and std::internal justify right.
        const bool my_left = ((my_flags & std::ios::left)  != static_cast<std::ios::fmtflags>(0U));

        // Justify left or right and insert the fill characters.
        str.insert((my_left ? str.cend() : str.cbegin()), n_fill, os.fill());
      }
    }

    static void wr_string_scientific(std::string& str,
                                      const exponent_type the_exp,
                                      const std::uint_fast32_t os_precision,
                                      const bool my_showpoint,
                                      const bool my_uppercase,
                                      const bool trim_trailing_zeros = false)
    {
      if(os_precision > static_cast<std::uint_fast32_t>(str.length() - 1U))
      {
        // Zero-extend the string to the given precision if necessary.
        const std::uint_fast32_t n_pad = static_cast<std::uint_fast32_t>(os_precision - (str.length() - 1U));

        str.insert(str.cend(), n_pad, static_cast<char>('0'));
      }

      // Insert the decimal point.
      str.insert(static_cast<std::uint_fast32_t>(1U), ".");

      // Trim the trailing zeros, where the trim-characteristics depend on the showpoint flag.
      if(trim_trailing_zeros)
      {
        const std::string::const_reverse_iterator rit_non_zero = std::find_if(str.crbegin(),
                                                                              str.crend(),
                                                                              [](const char& c) -> bool
                                                                              {
                                                                                return (c != static_cast<char>('0'));
                                                                              });

        if(rit_non_zero != str.rbegin())
        {
          const std::ptrdiff_t ofs =   static_cast<std::ptrdiff_t>(str.length())
                                     - static_cast<std::ptrdiff_t>(rit_non_zero - str.crbegin());

          str.erase(str.cbegin() + ofs, str.cend());
        }
      }

      // Perform the final manipulations on the digits of the string.
      if(my_showpoint)
      {
        if(trim_trailing_zeros) { special_extend_string_to_precision(str, os_precision); }
      }
      else
      {
        // Remove the trailing decimal point if necessary.
        if(*(str.cend() - 1U) == static_cast<char>('.'))
        {
          str.erase(str.cend() - 1U, str.cend());
        }
      }

      // Append the exponent in uppercase or lower case, including its sign.
      const bool          b_exp_is_neg = (the_exp < static_cast<exponent_type>(0));
      const std::uint64_t u_exp        = static_cast<std::uint64_t>(!b_exp_is_neg ? the_exp : static_cast<exponent_type>(-the_exp));

      str += (my_uppercase ? "E" : "e");
      str += (b_exp_is_neg ? "-" : "+");

      char p_str[20U] = { 0 };
      char* p_end = util::baselexical_cast(u_exp, p_str);

      std::string str_exp = std::string(p_str, p_end);

      // Format the exponent string to have a width that is an even multiple of three.
      const std::size_t str_exp_len      = str_exp.length();
      const std::size_t str_exp_len_mod3 = static_cast<std::size_t>(str_exp_len % 3U);
      const std::size_t str_exp_len_pad  = ((str_exp_len_mod3 != static_cast<std::size_t>(0U)) ? static_cast<std::uint_fast32_t>(3U - (str_exp_len % 3U))
                                                                                               : static_cast<std::uint_fast32_t>(0U));

      str += std::string(str_exp_len_pad, static_cast<char>('0'));
      str += str_exp;
    }

    static void wr_string_fixed(std::string& str,
                                const exponent_type the_exp,
                                const std::uint_fast32_t os_precision,
                                const bool my_showpoint,
                                const bool trim_trailing_zeros = false)
    {
      const std::size_t input_str_len = str.length();

      if(the_exp < static_cast<exponent_type>(0))
      {
        // The number is less than one in magnitude. Insert the decimal
        // point using "0." as well as the needed number of leading zeros.
        const std::uint_fast32_t minus_exp_minus_one = static_cast<std::uint_fast32_t>(-the_exp - 1);

        const std::string str_zero_insert((std::min)(minus_exp_minus_one, os_precision), static_cast<char>('0'));

        const exponent_type n_pad = static_cast<exponent_type>(static_cast<exponent_type>(os_precision) - static_cast<exponent_type>(str.length() + str_zero_insert.length()));

        str.insert(0U, "0." + str_zero_insert);

        // Zero-extend the string to the given precision if necessary.
        if(n_pad > static_cast<exponent_type>(0))
        {
          str.insert(str.cend(), static_cast<std::uint_fast32_t>(n_pad), static_cast<char>('0'));
        }
      }
      else
      {
        // Insert the decimal point.
        const std::uint_fast32_t my_exp_plus_one = static_cast<std::uint_fast32_t>(the_exp + 1);

        // The number string is not large enough to hold the integer part of the number.
        // Zero extend the integer part of the string.
        if(input_str_len < my_exp_plus_one)
        {
          str.insert(str.cend(), static_cast<std::uint_fast32_t>(my_exp_plus_one- str.length()), static_cast<char>('0'));
        }

        str.insert(my_exp_plus_one, ".");

        // Zero-extend the string to the given precision if necessary.
        const exponent_type n_pad = static_cast<exponent_type>(os_precision) - static_cast<exponent_type>(static_cast<exponent_type>(str.length() - 1U) - (the_exp + 1));

        if(n_pad > static_cast<exponent_type>(0))
        {
          str.insert(str.cend(), static_cast<std::uint_fast32_t>(n_pad), static_cast<char>('0'));
        }
      }

      // Trim the trailing zeros, where the trim-characteristics depend on the showpoint flag.
      if(trim_trailing_zeros)
      {
        const std::string::const_reverse_iterator rit_non_zero =
          std::find_if(str.crbegin(),
                        str.crend(),
                        [](const char& c) -> bool
                        {
                          return (c != static_cast<char>('0'));
                        });

        if(rit_non_zero != str.rbegin())
        {
          const std::ptrdiff_t ofs =   static_cast<std::ptrdiff_t>(str.length())
                                     - std::distance<std::string::const_reverse_iterator>(str.crbegin(), rit_non_zero);

          str.erase(str.cbegin() + ofs, str.cend());
        }
      }

      // Perform the final manipulations on the digits of the string.
      if(my_showpoint)
      {
        if(trim_trailing_zeros)
        {
          special_extend_string_to_precision(str, os_precision);
        }
      }
      else
      {
        // Remove the trailing decimal point if necessary.
        if(*(str.cend() - 1U) == static_cast<char>('.'))
        {
          str.erase(str.cend() - 1U, str.cend());
        }
      }
    }

    static void special_extend_string_to_precision(std::string& str, const std::uint_fast32_t os_precision)
    {
      // This is the special case of showpoint in combination with
      // a non-fixed, non-scientific representation. The string has
      // to be zero extended such that the total width of its entire
      // non-zero part exactly equals the precision.

      // Check if the number is less than 1.
      if(   (str.at(static_cast<std::uint_fast32_t>(0U)) == static_cast<char>('0'))
          && (str.at(static_cast<std::uint_fast32_t>(1U)) == static_cast<char>('.'))
        )
      {
        if(str.length() == static_cast<std::uint_fast32_t>(2U))
        {
          // This string represents zero and needs zero extension.
          str.insert(str.cend(), os_precision, static_cast<char>('0'));
        }
        else
        {
          // This is a non-zero decimal less than 1 that needs zero extension.
          const std::string::const_iterator it_non_zero =
            std::find_if(str.cbegin() + 2U,
                          str.cend(),
                          [](const char& c) -> bool
                          {
                            return (c != static_cast<char>('0'));
                          });

          const std::uint_fast32_t len_non_zero_part = static_cast<std::uint_fast32_t>(str.cend() - it_non_zero);

          const std::uint_fast32_t u_pad = static_cast<std::uint_fast32_t>(os_precision - len_non_zero_part);

          str.insert(str.cend(), u_pad, static_cast<char>('0'));
        }
      }
      else
      {
        // This is a number greater than or equal to 1 that needs zero extension.
        const std::uint_fast32_t u_pad = static_cast<std::uint_fast32_t>(os_precision - static_cast<std::uint_fast32_t>(str.length() - static_cast<std::uint_fast32_t>(1U)));

        str.insert(str.cend(), u_pad, static_cast<char>('0'));
      }
    }

    template<typename char_type, typename traits_type>
    friend std::basic_ostream<char_type, traits_type>& operator<<(std::basic_ostream<char_type, traits_type>& os, const decwide_t& f)
    {
      std::string str;

      f.wr_string(str, os);

      return (os << str);
    }

    template<typename char_type, typename traits_type>
    friend std::basic_istream<char_type, traits_type>& operator>>(std::basic_istream<char_type, traits_type>& is, decwide_t& f)
    {
      std::string str;

      static_cast<void>(is >> str);

      static_cast<void>(f.rd_string(str.c_str()));

      return is;
    }
    #endif // !WIDE_DECIMAL_DISABLE_IOSTREAM

    friend inline decwide_t fabs(decwide_t x)
    {
      return (x.isneg() ? decwide_t(x).negate() : x);
    }

    friend inline decwide_t abs(decwide_t x)
    {
      return fabs(x);
    }

    friend inline std::int32_t sgn(decwide_t x)
    {
      return (x.iszero() ? static_cast<std::int32_t>(0)
                         : (x.isneg() ? static_cast<std::int32_t>(-1)
                                      : static_cast<std::int32_t>(1)));
    }

    friend inline decwide_t floor(decwide_t x)
    {
      return ((((x.isfinite)() == false) || x.isint())
               ?  x
               : (x.isneg() ? (x - one<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>()).extract_integer_part()
                            :  x.extract_integer_part()));
    }

    friend inline decwide_t ceil(decwide_t x)
    {
      return ((((x.isfinite)() == false) || x.isint())
               ?  x
               : (x.isneg() ?  x.extract_integer_part()
                            : (x + one<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>()).extract_integer_part()));
    }

    friend inline std::int32_t ilogb(decwide_t x)
    {
      exponent_type e10;

      limb_type xx = x.my_data[0U];

      std::int_fast16_t n10 = 0;

      while(limb_type(xx + 5U) > 10U)
      {
        xx /= 10U;

        ++n10;
      }

      e10 = static_cast<exponent_type>(x.my_exp + n10);

      return (std::max)(           (std::numeric_limits<std::int32_t>::min)(),
                        (std::min)((std::numeric_limits<std::int32_t>::max)(), (std::int32_t) e10));
    }

    template<const std::int32_t OtherMyDigits10, typename OtherLimbType, typename OtherAllocatorType, typename OtherInternalFloatType, typename OtherExponentType, typename OtherFftFloatType>
    friend constexpr decwide_t<OtherMyDigits10, OtherLimbType, OtherAllocatorType, OtherInternalFloatType, OtherExponentType, OtherFftFloatType> zero();

    template<const std::int32_t OtherMyDigits10, typename OtherLimbType, typename OtherAllocatorType, typename OtherInternalFloatType, typename OtherExponentType, typename OtherFftFloatType>
    friend constexpr decwide_t<OtherMyDigits10, OtherLimbType, OtherAllocatorType, OtherInternalFloatType, OtherExponentType, OtherFftFloatType> one();

    template<const std::int32_t OtherMyDigits10, typename OtherLimbType, typename OtherAllocatorType, typename OtherInternalFloatType, typename OtherExponentType, typename OtherFftFloatType>
    friend constexpr decwide_t<OtherMyDigits10, OtherLimbType, OtherAllocatorType, OtherInternalFloatType, OtherExponentType, OtherFftFloatType> two();

    template<const std::int32_t OtherMyDigits10, typename OtherLimbType, typename OtherAllocatorType, typename OtherInternalFloatType, typename OtherExponentType, typename OtherFftFloatType>
    friend constexpr decwide_t<OtherMyDigits10, OtherLimbType, OtherAllocatorType, OtherInternalFloatType, OtherExponentType, OtherFftFloatType> half();
  };

  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType>
  constexpr decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType> zero()
  {
    using other_wide_decimal_type = decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>;

    return other_wide_decimal_type::from_lst( { typename other_wide_decimal_type::limb_type(0U) } );
  }

  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType>
  constexpr decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType> one()
  {
    using other_wide_decimal_type = decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>;

    return other_wide_decimal_type::from_lst( { typename other_wide_decimal_type::limb_type(1U) } );
  }

  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType>
  constexpr decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType> two()
  {
    using other_wide_decimal_type = decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>;

    return other_wide_decimal_type::from_lst( { typename other_wide_decimal_type::limb_type(2U) } );
  }

  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType>
  constexpr decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType> half()
  {
    using other_wide_decimal_type = decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>;

    return
    other_wide_decimal_type::from_lst
    (
      {
        typename other_wide_decimal_type::limb_type(other_wide_decimal_type::decwide_t_elem_mask / 2)
      },
      -other_wide_decimal_type::decwide_t_elem_digits10
    );
  }

  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType> constexpr std::int32_t decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>::decwide_t_digits10;
  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType> constexpr std::int32_t decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>::decwide_t_digits;
  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType> constexpr std::int32_t decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>::decwide_t_max_digits10;
  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType> constexpr std::int32_t decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>::decwide_t_radix;
  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType> constexpr std::int32_t decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>::decwide_t_elem_digits10;
  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType> constexpr std::int32_t decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>::decwide_t_elem_number;
  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType> constexpr std::int32_t decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>::decwide_t_elem_mask;
  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType> constexpr std::int32_t decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>::decwide_t_elem_mask_half;
  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType> constexpr std::int32_t decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>::decwide_t_elems_for_kara;
  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType> constexpr std::int32_t decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>::decwide_t_elems_for_fft;

  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType> constexpr typename decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>::exponent_type decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>::decwide_t_max_exp10;
  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType> constexpr typename decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>::exponent_type decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>::decwide_t_min_exp10;
  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType> constexpr typename decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>::exponent_type decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>::decwide_t_max_exp;
  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType> constexpr typename decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>::exponent_type decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>::decwide_t_min_exp;

  #if !defined(WIDE_DECIMAL_DISABLE_CACHED_CONSTANTS)
  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType>
  typename decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>::initializer decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>::init;
  #endif

  #if !defined(WIDE_DECIMAL_DISABLE_DYNAMIC_MEMORY_ALLOCATION)
  #else
  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType> typename decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>::limb_type      decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>::my_school_mul_pool[std::uint32_t((decwide_t_elems_for_kara - 1) * 2)];
  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType> typename decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>::limb_type      decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>::my_kara_mul_pool  [detail::a029750::a029750_as_constexpr(std::uint32_t(decwide_t_elems_for_fft - 1)) * 8UL];
  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType> typename decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>::fft_float_type decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>::my_af_fft_mul_pool[detail::a000079::a000079_as_constexpr(std::uint32_t(decwide_t_elem_number)) * 4UL];
  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType> typename decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>::fft_float_type decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>::my_bf_fft_mul_pool[detail::a000079::a000079_as_constexpr(std::uint32_t(decwide_t_elem_number)) * 4UL];
  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType> typename decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>::representation_type     decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>::my_n_data_for_add_sub;
  #endif

  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType>
  decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType> calc_pi(void(*pfn_callback_to_report_digits10)(const std::uint32_t))
  {
    // Description : Compute pi using the quadratically convergent Gauss AGM,
    //               in particular the Schoenhage variant.
    //               For a description of the algorithm see the book "Pi Unleashed":
    //               An optional input callback function pointer can be provided
    //               for printing digit-related messages at various points.
    //
    //               Book reference:
    //               http://www.jjj.de/pibook/pibook.html
    //               http://www.springer.com/gp/book/9783642567353

    if(pfn_callback_to_report_digits10 != nullptr)
    {
      pfn_callback_to_report_digits10((std::uint32_t) 0U);
    }

    using floating_point_type = decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>;

    floating_point_type val_pi;

    floating_point_type a(1U);

    // Initialize bB to 0.5.
    floating_point_type bB(half<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>());

    // Initialize t to 0.375.
    floating_point_type t(floating_point_type(3U) / 8U);

    floating_point_type s(bB);

    // This loop is designed for a maximum of several million
    // decimal digits of pi. The index k should reach no higher
    // than about 25 or 30. After about 20 iterations, the precision
    // is about one million decimal digits.

    const std::uint32_t digits10_iteration_goal =
        (std::uint32_t) (std::numeric_limits<floating_point_type>::digits10 / 2)
      + (std::max)((std::uint32_t) (floating_point_type::decwide_t_elem_digits10  + 1), (std::uint32_t) 9U);

    using std::log;

    const std::uint32_t digits10_scale =
      (std::uint32_t) (0.5F + (1000.0F * log((float) std::numeric_limits<floating_point_type>::radix)) / log(10.0F));

    for(unsigned k = 0U; k < 48U; ++k)
    {
      using std::sqrt;

      a      += sqrt(bB);
      a      /= 2U;
      val_pi  = a;
      val_pi *= a;
      bB      = val_pi;
      bB     -= t;
      bB     *= 2U;

      floating_point_type iterate_term(bB);

      iterate_term -= val_pi;
      iterate_term *= (unsigned long long) (1ULL << (k + 1U));

      s += iterate_term;

      // Test the number of precise digits from this iteration.
      // If it is there are enough precise digits, then the calculation
      // is finished.
      const std::int32_t ib = (std::max)(std::int32_t(0), -ilogb(iterate_term));

      const std::uint32_t digits10_of_iteration =
        (std::uint32_t) ((std::uint64_t) ((std::uint64_t) ib * digits10_scale) / 1000U);

      if(pfn_callback_to_report_digits10 != nullptr)
      {
        pfn_callback_to_report_digits10(digits10_of_iteration);
      }

      // Estimate the approximate decimal digits of this iteration term.
      // If we have attained about half of the total desired digits
      // with this iteration term, then the calculation is finished
      // because the change from the next iteration will be
      // insignificantly small.

      if(digits10_of_iteration > digits10_iteration_goal)
      {
        break;
      }

      t  = val_pi;
      t += bB;
      t /= 4U;
    }

    val_pi += bB;
    val_pi /= s;

    if(pfn_callback_to_report_digits10 != nullptr)
    {
      pfn_callback_to_report_digits10((std::uint32_t) std::numeric_limits<floating_point_type>::digits10);
    }

    return val_pi;
  }

  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType> decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType> calc_ln_two()
  {
    using floating_point_type = decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>;

    // Use an AGM method to compute log(2).

    // Set a0 = 1
    // Set b0 = 1 / (2^(m-2))

    floating_point_type ak(1U);

    constexpr float n_times_factor = ((float) std::numeric_limits<floating_point_type>::digits10) * 1.67F;

    // Ensure that the resulting power is non-negative.
    // Also enforce that m >= 3.
    const std::int32_t m = (std::max)((std::int32_t) n_times_factor, (std::int32_t) 3);

    floating_point_type bk =
      ldexp(one<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>(), (std::int32_t) (2 - m));

    const std::uint32_t digits10_iteration_goal =
        (std::uint32_t) (std::numeric_limits<floating_point_type>::digits10 / 2)
      + (std::max)((std::uint32_t) (floating_point_type::decwide_t_elem_digits10 + 1), (std::uint32_t) 9U);

    using std::log;

    const std::uint32_t digits10_scale =
      (std::uint32_t) (0.5F + (1000.0F * log((float) std::numeric_limits<floating_point_type>::radix)) / log(10.0F));

    for(std::int32_t k = static_cast<std::int32_t>(0); k < static_cast<std::int32_t>(64); ++k)
    {
      using std::ilogb;

      // Check for the number of significant digits to be
      // at least half of the requested digits. If at least
      // half of the requested digits have been achieved,
      // then break after the upcoming iteration.

      const std::int32_t ib = (std::max)(std::int32_t(0), -ilogb(ak - bk));

      const std::uint32_t digits10_of_iteration =
        (std::uint32_t) ((std::uint64_t) ((std::uint64_t) ib * digits10_scale) / 1000U);

      const floating_point_type ak_tmp(ak);

      ak += bk;

      if(digits10_of_iteration > digits10_iteration_goal)
      {
        break;
      }

      using std::sqrt;

      ak /= 2;
      bk *= ak_tmp;
      bk  = sqrt(bk);
    }

    // We are now finished with the AGM iteration for log(2).
    // Note at this time that (ak = bk) = AGM(...)
    // Retrieve the value of pi and divide by (a * (2 * m)).

    const floating_point_type result =
         pi<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>() / (ak * m);

    return result;
  }

  #if !defined(WIDE_DECIMAL_DISABLE_CACHED_CONSTANTS)
  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType>
  const decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>& pi(void(*pfn_callback_to_report_digits10)(const std::uint32_t))
  {
    (void) pfn_callback_to_report_digits10;

    return decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>::my_value_pi();
  }
  #else
  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType>
  decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType> pi(void(*pfn_callback_to_report_digits10)(const std::uint32_t))
  {
    return calc_pi<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>(pfn_callback_to_report_digits10);
  }
  #endif

  #if !defined(WIDE_DECIMAL_DISABLE_CACHED_CONSTANTS)
  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType> const decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>& ln_two()
  {
    return decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>::my_value_ln_two();
  }
  #else
  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType> decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType> ln_two()
  {
    return calc_ln_two<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>();
  }
  #endif

  // Global unary operators of decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType> reference.
  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType> decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType> operator+(const decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>& self) { return decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>(self); }
  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType> decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType> operator-(const decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>& self) { decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType> tmp(self); tmp.negate(); return tmp; }

  // Global add/sub/mul/div of const decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>& with const decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>&.
  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType> decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType> operator+(const decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>& u, const decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>& v) { return decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>(u) += v; }
  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType> decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType> operator-(const decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>& u, const decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>& v) { return decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>(u) -= v; }
  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType> decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType> operator*(const decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>& u, const decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>& v) { return decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>(u) *= v; }
  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType> decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType> operator/(const decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>& u, const decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>& v) { return decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>(u) /= v; }

  // Global add/sub/mul/div of const decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>& with all built-in types.
  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType, typename SignedIntegralType>
  typename std::enable_if<   (std::is_integral<SignedIntegralType>::value == true)
                          && (std::is_unsigned<SignedIntegralType>::value == false), decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>>::type operator+(const decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>& u, const SignedIntegralType& n)
  {
    return decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>(u).add_signed_long_long(n);
  }

  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType, typename UnsignedIntegralType>
  typename std::enable_if<   (std::is_integral<UnsignedIntegralType>::value == true)
                          && (std::is_unsigned<UnsignedIntegralType>::value == true), decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>>::type operator+(const decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>& u, const UnsignedIntegralType& n)
  {
    return decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>(u).add_unsigned_long_long(n);
  }

  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType, typename FloatingPointType>
  typename std::enable_if<(std::is_floating_point<FloatingPointType>::value == true), decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>>::type operator+(const decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>& u, const FloatingPointType& f)
  {
    return decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>(u) += decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>(f);
  }

  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType, typename SignedIntegralType>
  typename std::enable_if<   (std::is_integral<SignedIntegralType>::value == true)
                          && (std::is_unsigned<SignedIntegralType>::value == false), decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>>::type operator-(const decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>& u, const SignedIntegralType& n)
  {
    return decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>(u).sub_signed_long_long(n);
  }

  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType, typename UnsignedIntegralType>
  typename std::enable_if<   (std::is_integral<UnsignedIntegralType>::value == true)
                          && (std::is_unsigned<UnsignedIntegralType>::value == true), decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>>::type operator-(const decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>& u, const UnsignedIntegralType& n)
  {
    return decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>(u).sub_unsigned_long_long(n);
  }

  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType, typename FloatingPointType>
  typename std::enable_if<(std::is_floating_point<FloatingPointType>::value == true), decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>>::type operator-(const decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>& u, const FloatingPointType& f)
  {
    return decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>(u) -= decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>(f);
  }

  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType, typename SignedIntegralType>
  typename std::enable_if<   (std::is_integral<SignedIntegralType>::value == true)
                          && (std::is_unsigned<SignedIntegralType>::value == false), decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>>::type operator*(const decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>& u, const SignedIntegralType& n)
  {
    return decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>(u).mul_signed_long_long(n);
  }

  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType, typename UnsignedIntegralType>
  typename std::enable_if<   (std::is_integral<UnsignedIntegralType>::value == true)
                          && (std::is_unsigned<UnsignedIntegralType>::value == true), decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>>::type operator*(const decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>& u, const UnsignedIntegralType& n)
  {
    return decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>(u).mul_unsigned_long_long(n);
  }

  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType, typename FloatingPointType>
  typename std::enable_if<(std::is_floating_point<FloatingPointType>::value == true), decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>>::type operator*(const decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>& u, const FloatingPointType& f)
  {
    return decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>(u) *= decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>(f);
  }

  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType, typename SignedIntegralType>
  typename std::enable_if<   (std::is_integral<SignedIntegralType>::value == true)
                          && (std::is_unsigned<SignedIntegralType>::value == false), decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>>::type operator/(const decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>& u, const SignedIntegralType& n)
  {
    return decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>(u).div_signed_long_long(n);
  }

  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType, typename UnsignedIntegralType>
  typename std::enable_if<   (std::is_integral<UnsignedIntegralType>::value == true)
                          && (std::is_unsigned<UnsignedIntegralType>::value == true), decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>>::type operator/(const decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>& u, const UnsignedIntegralType& n)
  {
    return decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>(u).div_unsigned_long_long(n);
  }

  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType, typename FloatingPointType>
  typename std::enable_if<(std::is_floating_point<FloatingPointType>::value == true), decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>>::type operator/(const decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>& u, const FloatingPointType& f)
  {
    return decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>(u) /= decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>(f);
  }

  // Global add/sub/mul/div of all built-in types with const decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>&.
  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType, typename SignedIntegralType>
  typename std::enable_if<   (std::is_integral<SignedIntegralType>::value == true)
                          && (std::is_unsigned<SignedIntegralType>::value == false), decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>>::type operator+(const SignedIntegralType& n, const decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>& u)
  {
    return decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>(u).add_signed_long_long(n);
  }

  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType, typename UnsignedIntegralType>
  typename std::enable_if<   (std::is_integral<UnsignedIntegralType>::value == true)
                          && (std::is_unsigned<UnsignedIntegralType>::value == true), decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>>::type operator+(const UnsignedIntegralType& n, const decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>& u)
  {
    return decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>(u).add_unsigned_long_long(n);
  }

  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType, typename FloatingPointType>
  typename std::enable_if<(std::is_floating_point<FloatingPointType>::value == true), decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>>::type operator+(const FloatingPointType& f, const decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>& u)
  {
    return decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>(f) += u;
  }

  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType, typename ArithmeticType>
  typename std::enable_if<(std::is_arithmetic<ArithmeticType>::value == true), decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>>::type operator-(const ArithmeticType& n, const decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>& u)
  {
    return decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>(n) -= u;
  }

  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType, typename SignedIntegralType>
  typename std::enable_if<   (std::is_integral<SignedIntegralType>::value == true)
                          && (std::is_unsigned<SignedIntegralType>::value == false), decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>>::type operator*(const SignedIntegralType& n, const decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>& u)
  {
    return decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>(u).mul_signed_long_long(n);
  }

  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType, typename UnsignedIntegralType>
  typename std::enable_if<   (std::is_integral<UnsignedIntegralType>::value == true)
                          && (std::is_unsigned<UnsignedIntegralType>::value == true), decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>>::type operator*(const UnsignedIntegralType& n, const decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>& u)
  {
    return decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>(u).mul_unsigned_long_long(n);
  }

  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType, typename FloatingPointType>
  typename std::enable_if<(std::is_floating_point<FloatingPointType>::value == true), decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>>::type operator*(const FloatingPointType& f, const decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>& u)
  {
    return decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>(f) *= u;
  }

  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType, typename ArithmeticType>
  typename std::enable_if<(std::is_arithmetic<ArithmeticType>::value == true), decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>>::type operator/(const ArithmeticType& n, const decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>& u)
  {
    return decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>(n) /= u;
  }

  // Global self add/sub/mul/div of decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>& with all built-in types.
  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType, typename SignedIntegralType>
  typename std::enable_if<   (std::is_integral<SignedIntegralType>::value == true)
                          && (std::is_unsigned<SignedIntegralType>::value == false), decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>>::type operator+=(decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>& u, const SignedIntegralType& n)
  {
    return u.add_signed_long_long(n);
  }

  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType, typename UnsignedIntegralType>
  typename std::enable_if<   (std::is_integral<UnsignedIntegralType>::value == true)
                          && (std::is_unsigned<UnsignedIntegralType>::value == true), decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>>::type operator+=(decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>& u, const UnsignedIntegralType& n)
  {
    return u.add_unsigned_long_long(n);
  }

  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType, typename FloatingPointType>
  typename std::enable_if<(std::is_floating_point<FloatingPointType>::value == true), decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>>::type operator+=(decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>& u, const FloatingPointType& f)
  {
    return u += decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>(f);
  }

  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType, typename SignedIntegralType>
  typename std::enable_if<   (std::is_integral<SignedIntegralType>::value == true)
                          && (std::is_unsigned<SignedIntegralType>::value == false), decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>>::type operator-=(decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>& u, const SignedIntegralType& n)
  {
    return u.sub_signed_long_long(n);
  }

  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType, typename UnsignedIntegralType>
  typename std::enable_if<   (std::is_integral<UnsignedIntegralType>::value == true)
                          && (std::is_unsigned<UnsignedIntegralType>::value == true), decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>>::type operator-=(decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>& u, const UnsignedIntegralType& n)
  {
    return u.sub_unsigned_long_long(n);
  }

  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType, typename FloatingPointType>
  typename std::enable_if<(std::is_floating_point<FloatingPointType>::value == true), decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>>::type operator-=(decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>& u, const FloatingPointType& f)
  {
    return u -= decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>(f);
  }

  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType, typename SignedIntegralType>
  typename std::enable_if<   (std::is_integral<SignedIntegralType>::value == true)
                          && (std::is_unsigned<SignedIntegralType>::value == false), decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>>::type operator*=(decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>& u, const SignedIntegralType& n)
  {
    return u.mul_signed_long_long(n);
  }

  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType, typename UnsignedIntegralType>
  typename std::enable_if<   (std::is_integral<UnsignedIntegralType>::value == true)
                          && (std::is_unsigned<UnsignedIntegralType>::value == true), decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>>::type operator*=(decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>& u, const UnsignedIntegralType& n)
  {
    return u.mul_unsigned_long_long(n);
  }

  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType, typename FloatingPointType>
  typename std::enable_if<(std::is_floating_point<FloatingPointType>::value == true), decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>>::type operator*=(decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>& u, const FloatingPointType& f)
  {
    return u *= decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>(f);
  }

  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType, typename SignedIntegralType>
  typename std::enable_if<   (std::is_integral<SignedIntegralType>::value == true)
                          && (std::is_unsigned<SignedIntegralType>::value == false), decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>>::type operator/=(decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>& u, const SignedIntegralType& n)
  {
    return u.div_signed_long_long(n);
  }

  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType, typename UnsignedIntegralType>
  typename std::enable_if<   (std::is_integral<UnsignedIntegralType>::value == true)
                          && (std::is_unsigned<UnsignedIntegralType>::value == true), decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>>::type operator/=(decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>& u, const UnsignedIntegralType& n)
  {
    return u.div_unsigned_long_long(n);
  }

  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType, typename FloatingPointType>
  typename std::enable_if<(std::is_floating_point<FloatingPointType>::value == true), decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>>::type operator/=(decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>& u, const FloatingPointType& f)
  {
    return u /= decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>(f);
  }

  // Global comparison operators of const decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, typename ExponentType>& with const decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>&.
  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType> bool operator< (const decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>& u, const decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>& v) { return (u.cmp(v) <  static_cast<std::int_fast8_t>(0)); }
  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType> bool operator<=(const decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>& u, const decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>& v) { return (u.cmp(v) <= static_cast<std::int_fast8_t>(0)); }
  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType> bool operator==(const decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>& u, const decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>& v) { return (u.cmp(v) == static_cast<std::int_fast8_t>(0)); }
  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType> bool operator!=(const decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>& u, const decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>& v) { return (u.cmp(v) != static_cast<std::int_fast8_t>(0)); }
  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType> bool operator>=(const decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>& u, const decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>& v) { return (u.cmp(v) >= static_cast<std::int_fast8_t>(0)); }
  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType> bool operator> (const decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>& u, const decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>& v) { return (u.cmp(v) >  static_cast<std::int_fast8_t>(0)); }

  // Global comparison operators of const decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>& with all built-in types.
  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType, typename ArithmeticType> typename std::enable_if<std::is_arithmetic<ArithmeticType>::value == true, bool>::type operator< (const decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>& u, const ArithmeticType& v) { return (u.cmp(decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>(v)) <  static_cast<std::int_fast8_t>(0)); }
  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType, typename ArithmeticType> typename std::enable_if<std::is_arithmetic<ArithmeticType>::value == true, bool>::type operator<=(const decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>& u, const ArithmeticType& v) { return (u.cmp(decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>(v)) <= static_cast<std::int_fast8_t>(0)); }
  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType, typename ArithmeticType> typename std::enable_if<std::is_arithmetic<ArithmeticType>::value == true, bool>::type operator==(const decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>& u, const ArithmeticType& v) { return (u.cmp(decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>(v)) == static_cast<std::int_fast8_t>(0)); }
  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType, typename ArithmeticType> typename std::enable_if<std::is_arithmetic<ArithmeticType>::value == true, bool>::type operator!=(const decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>& u, const ArithmeticType& v) { return (u.cmp(decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>(v)) != static_cast<std::int_fast8_t>(0)); }
  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType, typename ArithmeticType> typename std::enable_if<std::is_arithmetic<ArithmeticType>::value == true, bool>::type operator>=(const decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>& u, const ArithmeticType& v) { return (u.cmp(decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>(v)) >= static_cast<std::int_fast8_t>(0)); }
  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType, typename ArithmeticType> typename std::enable_if<std::is_arithmetic<ArithmeticType>::value == true, bool>::type operator> (const decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>& u, const ArithmeticType& v) { return (u.cmp(decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>(v)) >  static_cast<std::int_fast8_t>(0)); }

  // Global comparison operators of all built-in types with const decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>&.
  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType, typename ArithmeticType> typename std::enable_if<std::is_arithmetic<ArithmeticType>::value == true, bool>::type operator< (ArithmeticType u, const decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>& v) { return (decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>(u).cmp(v) <  static_cast<std::int_fast8_t>(0)); }
  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType, typename ArithmeticType> typename std::enable_if<std::is_arithmetic<ArithmeticType>::value == true, bool>::type operator<=(ArithmeticType u, const decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>& v) { return (decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>(u).cmp(v) <= static_cast<std::int_fast8_t>(0)); }
  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType, typename ArithmeticType> typename std::enable_if<std::is_arithmetic<ArithmeticType>::value == true, bool>::type operator==(ArithmeticType u, const decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>& v) { return (decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>(u).cmp(v) == static_cast<std::int_fast8_t>(0)); }
  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType, typename ArithmeticType> typename std::enable_if<std::is_arithmetic<ArithmeticType>::value == true, bool>::type operator!=(ArithmeticType u, const decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>& v) { return (decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>(u).cmp(v) != static_cast<std::int_fast8_t>(0)); }
  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType, typename ArithmeticType> typename std::enable_if<std::is_arithmetic<ArithmeticType>::value == true, bool>::type operator>=(ArithmeticType u, const decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>& v) { return (decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>(u).cmp(v) >= static_cast<std::int_fast8_t>(0)); }
  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType, typename ArithmeticType> typename std::enable_if<std::is_arithmetic<ArithmeticType>::value == true, bool>::type operator> (ArithmeticType u, const decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>& v) { return (decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>(u).cmp(v) >  static_cast<std::int_fast8_t>(0)); }

  } } // namespace math::wide_decimal

  // Specialization of std::numeric_limits<decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>>.
  namespace std
  {
    template<const std::int32_t MyDigits10,
             typename LimbType,
             typename AllocatorType,
             typename InternalFloatType,
             typename ExponentType,
             typename FftFloatType>
    class numeric_limits<math::wide_decimal::decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>>
    {
    private:
      using exponent_type =
        typename math::wide_decimal::decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>::exponent_type;

    public:
      static constexpr bool                    is_specialized    = true;
      static constexpr bool                    is_signed         = true;
      static constexpr bool                    is_integer        = false;
      static constexpr bool                    is_exact          = false;
      static constexpr bool                    is_bounded        = true;
      static constexpr bool                    is_modulo         = false;
      static constexpr bool                    is_iec559         = false;
      static constexpr std::int32_t            digits            = math::wide_decimal::decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>::decwide_t_digits;       // Type differs from int.
      static constexpr std::int32_t            digits10          = math::wide_decimal::decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>::decwide_t_digits10;     // Type differs from int.
      static constexpr std::int32_t            max_digits10      = math::wide_decimal::decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>::decwide_t_max_digits10; // Type differs from int.
      static constexpr exponent_type           min_exponent      = math::wide_decimal::decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>::decwide_t_min_exp;      // Type differs from int.
      static constexpr exponent_type           min_exponent10    = math::wide_decimal::decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>::decwide_t_min_exp10;    // Type differs from int.
      static constexpr exponent_type           max_exponent      = math::wide_decimal::decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>::decwide_t_max_exp;      // Type differs from int.
      static constexpr exponent_type           max_exponent10    = math::wide_decimal::decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>::decwide_t_max_exp10;    // Type differs from int.
      static constexpr int                     radix             = math::wide_decimal::decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>::decwide_t_radix;
      static constexpr std::float_round_style  round_style       = std::round_to_nearest;
      static constexpr bool                    has_infinity      = false;
      static constexpr bool                    has_quiet_NaN     = false;
      static constexpr bool                    has_signaling_NaN = false;
      static constexpr std::float_denorm_style has_denorm        = std::denorm_absent;
      static constexpr bool                    has_denorm_loss   = false;
      static constexpr bool                    traps             = false;
      static constexpr bool                    tinyness_before   = false;

      static constexpr math::wide_decimal::decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType> (min)        () { return math::wide_decimal::decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>::my_value_min(); }
      static constexpr math::wide_decimal::decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType> (max)        () { return math::wide_decimal::decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>::my_value_max(); }
      static constexpr math::wide_decimal::decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType> lowest       () { return math::wide_decimal::zero<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>(); }
      static constexpr math::wide_decimal::decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType> epsilon      () { return math::wide_decimal::decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>::my_value_eps(); }
      static constexpr math::wide_decimal::decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType> round_error  () { return math::wide_decimal::half<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>(); }
      static constexpr math::wide_decimal::decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType> infinity     () { return math::wide_decimal::zero<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>(); }
      static constexpr math::wide_decimal::decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType> quiet_NaN    () { return math::wide_decimal::zero<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>(); }
      static constexpr math::wide_decimal::decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType> signaling_NaN() { return math::wide_decimal::zero<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>(); }
      static constexpr math::wide_decimal::decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType> denorm_min   () { return math::wide_decimal::zero<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>(); }
    };
  } // namespace std

  namespace math { namespace wide_decimal {

  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType> const decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType> constexpr unsigned_long_long_max() { return decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>((std::numeric_limits<unsigned long long>::max)()); }
  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType> const decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType> constexpr signed_long_long_min  () { return decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>((std::numeric_limits<signed long long>::min)()); }
  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType> const decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType> constexpr signed_long_long_max  () { return decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>((std::numeric_limits<signed long long>::max)()); }
  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType> const decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType> constexpr long_double_min       () { return decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>((std::numeric_limits<long double>::min)());}
  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType> const decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType> constexpr long_double_max       () { return decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>((std::numeric_limits<long double>::max)());}

  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType> bool (isnan)   (decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType> x) { return  (x.isnan)(); }
  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType> bool (isfinite)(decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType> x) { return  (x.isfinite)(); }
  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType> bool (isinf)   (decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType> x) { return  (x.isinf)(); }
  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType> int   sign     (decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType> x) { return ((x.iszero)() ? 0 : ((x.isneg)() ? -1 : 1)); }

  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType>
  decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType> pow(decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType> x,
                                                                                                    decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType> a)
  {
    return exp(a * log(x));
  }

  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType>
  decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType> ldexp(decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType> v, int e)
  {
    decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType> ldexp_result = v;

    if(e == 0) { }
    else if((e > 0) && (e < 64))
    {
      ldexp_result *= (std::uint64_t) (1ULL << (unsigned) e);
    }
    else if((e > -64) && (e < 0))
    {
      ldexp_result /= (std::uint64_t) (1ULL << (unsigned) -e);
    }
    else
    {
      ldexp_result *= pow(two<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>(), e);
    }

    return ldexp_result;
  }

  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType>
  decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType> frexp(decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType> v, int* expon)
  {
    using exponent_type =
      typename decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>::exponent_type;

    double        d;
    exponent_type i;

    v.extract_parts(d, i);

    *expon = static_cast<int>(i);

    return v * ldexp(one<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>(), (int) -i);
  }

  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType>
  decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType> fmod(decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType> v1, decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType> v2)
  {
    const decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType> n = ((v1 < 0) ? ceil(v1 / v2) : floor(v1 / v2));

    return v1 - (n * v2);
  }

  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType>
  decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType> sqrt(decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType> x)
  {
    return x.calculate_sqrt();
  }

  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType>
  decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType> cbrt(decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType> x)
  {
    return rootn(x, static_cast<std::int32_t>(3));
  }

  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType>
  decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType> rootn(decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType> x, std::int32_t p)
  {
    decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType> rtn;

    if(p < static_cast<std::int32_t>(0))
    {
      rtn = rootn(one<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>() / x, static_cast<std::int32_t>(-p));
    }
    else if((p == static_cast<std::int32_t>(0)) || ((x < 0) && (p != static_cast<std::int32_t>(3))))
    {
      rtn = std::numeric_limits<decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>>::quiet_NaN();
    }
    else if(p == static_cast<std::int32_t>(1))
    {
      rtn = x;
    }
    else if(p == static_cast<std::int32_t>(2))
    {
      using std::sqrt;

      rtn = sqrt(x);
    }
    else if(p == static_cast<std::int32_t>(3))
    {
      const bool b_neg = (x < 0);

      using std::fabs;

      rtn = 1 / rootn_inverse(fabs(x), 3);

      if(b_neg) { rtn = -rtn; }
    }
    else
    {
      rtn = 1 / rootn_inverse(x, p);
    }

    return rtn;
  }

  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType>
  decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType> log(decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType> x)
  {
    using floating_point_type = decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>;

    // For values less than 1 invert the argument and
    // remember (in this case) to negate the result below.
    const bool b_negate = (x < 1);

    const floating_point_type xx((b_negate == false) ? x : 1 / x);

    // Use an AGM method to compute the logarithm of x.
    // Set a0 = 1
    // Set b0 = 4 / (x * 2^m)
    //        = 1 / (x * 2^(m - 2))

    floating_point_type ak(1U);

    const float n_times_factor = ((float) std::numeric_limits<floating_point_type>::digits10) * 1.67F;

    // Extract lg_xx = Log[mantissa * radix^ib]
    //               = Log[mantissa] + ib * Log[radix],
    // where the logarithm of the mantissa is simply neglected
    // in the approximation.

    using std::ilogb;
    using std::log;

    const float lg_xx_approx = (float) ilogb(xx) * log((float) std::numeric_limits<floating_point_type>::radix);

    const float lg_xx_over_lg2 = lg_xx_approx / log(2.0F);

    // Ensure that the resulting power is non-negative.
    // Also enforce that m >= 3.
    const std::int32_t m = (std::max)((std::int32_t) (n_times_factor - lg_xx_over_lg2), (std::int32_t) 3);

    floating_point_type bk =
      ldexp(one<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>(), (std::int32_t) (2 - m)) / xx;

    // TBD: Tolerance should have the log of the argument added to it (usually negligible).
    const std::uint32_t digits10_iteration_goal =
        (std::uint32_t) (std::numeric_limits<floating_point_type>::digits10 / 2)
      + (std::max)((std::uint32_t) (floating_point_type::decwide_t_elem_digits10 + 1), (std::uint32_t) 9U);

    const std::uint32_t digits10_scale =
      (std::uint32_t) (0.5F + (1000.0F * log((float) std::numeric_limits<floating_point_type>::radix)) / log(10.0F));

    for(std::int32_t k = static_cast<std::int32_t>(0); k < static_cast<std::int32_t>(128); ++k)
    {
      // Check for the number of significant digits to be
      // at least half of the requested digits. If at least
      // half of the requested digits have been achieved,
      // then break after the upcoming iteration.

      const std::int32_t ilogb_of_ak_minus_bk = (std::max)(std::int32_t(0), -ilogb(ak - bk));

      const std::uint32_t digits10_of_iteration =
        (std::uint32_t) ((std::uint64_t) ((std::uint64_t) ilogb_of_ak_minus_bk * digits10_scale) / 1000U);

      const floating_point_type ak_tmp(ak);

      ak += bk;

      if(digits10_of_iteration > digits10_iteration_goal)
      {
        break;
      }

      using std::sqrt;

      ak /= 2;
      bk *= ak_tmp;
      bk  = sqrt(bk);
    }

    // We are now finished with the AGM iteration for log(x).
    // Compute log(x) = {pi / [2 * AGM(1, 4 / 2^m)]} - (m * ln2)
    // Note at this time that (ak = bk) = AGM(...)
    // Retrieve the value of pi, divide by (2 * a) and subtract (m * ln2).

    const floating_point_type result =
            (pi<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>() / ak)
      - (ln_two<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>() * m);

    return ((b_negate == true) ? -result : result);
  }

  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType>
  decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType> exp(decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType> x)
  {
    using floating_point_type = decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>;

    floating_point_type exp_result;

    using std::isfinite;
    using math::wide_decimal::isfinite;

    if(x == 0)
    {
      exp_result = floating_point_type(1U);
    }
    else
    {
      const bool b_neg = (x < 0);

      const floating_point_type xx = ((b_neg == false) ? x : -x);

      // The algorithm for exp has been taken from MPFUN.
      // exp(t) = [ (1 + r + r^2/2! + r^3/3! + r^4/4! ...)^p2 ] * 2^n
      // where p2 is a power of 2 such as 2048, r = t_prime / p2, and
      // t_prime = t - n*ln2, with n chosen to minimize the absolute
      // value of t_prime. In the resulting Taylor series, which is
      // implemented as a hypergeometric function, |r| is bounded by
      // ln2 / p2.

      // Compute ln2 as a constant value.
      const floating_point_type ln2 = ln_two<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>();

      const std::uint32_t nf = (std::uint32_t) (xx / ln2);

      // Compute the exponential series of the scaled argument.
      // The scaling is 2^11 = 2048.
      const std::uint32_t p2 = (std::uint32_t) (1ULL << 11U);

      // Compute the series representation of Hypergeometric0F0 taken from
      // http://functions.wolfram.com/HypergeometricFunctions/Hypergeometric0F0/06/01/
      // There are no checks on input range or parameter boundaries.

      const floating_point_type xh((xx - (nf * ln2)) / p2);

      floating_point_type x_pow_n_div_n_fact(xh);

      floating_point_type h0f0 = 1 + x_pow_n_div_n_fact;

      const floating_point_type tol = std::numeric_limits<floating_point_type>::epsilon();

      // Series expansion of hypergeometric_0f0(; ; x).
      for(std::uint32_t n = 2U; n < UINT32_C(10000000); ++n)
      {
        x_pow_n_div_n_fact *= xh;
        x_pow_n_div_n_fact /= n;

        using std::fabs;

        if((n > 4U) && (fabs(x_pow_n_div_n_fact) < tol))
        {
          break;
        }

        h0f0 += x_pow_n_div_n_fact;
      }

      using std::ldexp;
      using std::pow;

      const floating_point_type exp_series = pow(h0f0, p2) * ldexp(floating_point_type(1U), (int) nf);

      exp_result = ((b_neg == false) ? exp_series : 1 / exp_series);
    }

    return exp_result;
  }

  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType>
  decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType> pow(decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType> b, const std::int64_t p)
  {
    // Calculate (b ^ p).

    using floating_point_type = decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>;

    floating_point_type result;

    if     (p <  0) { result = 1 / pow(b, -p); }
    else if(p == 0) { result = floating_point_type(1U); }
    else if(p == 1) { result = b; }
    else if(p == 2) { result = b; result *= b; }
    else if(p == 3) { result = b; result *= b; result *= b; }
    else if(p == 4) { result = b; result *= b; result *= result; }
    else
    {
      result = floating_point_type(1U);

      floating_point_type y(b);

      for(std::uint64_t p_local = (std::uint64_t) p; p_local != 0U; p_local >>= 1U)
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

  } } // namespace math::wide_decimal

#endif // DECWIDE_T_2004_06_01_H_
