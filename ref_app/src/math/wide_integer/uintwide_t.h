///////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 1999 - 2021.                 //
//  Distributed under the Boost Software License,                //
//  Version 1.0. (See accompanying file LICENSE_1_0.txt          //
//  or copy at http://www.boost.org/LICENSE_1_0.txt)             //
///////////////////////////////////////////////////////////////////

#ifndef UINTWIDE_T_2018_10_02_H_
  #define UINTWIDE_T_2018_10_02_H_

  #if defined(__GNUC__) || defined(__clang__)
  #if defined(WIDE_INTEGER_HAS_LIMB_TYPE_UINT64)
  #include <inttypes.h>
  #endif
  #endif

  #include <algorithm>
  #include <array>
  #include <cstddef>
  #include <cstdint>
  #include <cstring>
  #include <initializer_list>
  #include <iterator>
  #include <limits>
  #include <type_traits>

  #if !defined(WIDE_INTEGER_DISABLE_FLOAT_INTEROP)
  #include <cmath>
  #endif

  #if !defined(WIDE_INTEGER_DISABLE_IOSTREAM)
  #include <iomanip>
  #include <istream>
  #include <ostream>
  #include <sstream>
  #endif

  #include <util/utility/util_dynamic_array.h>

  #if defined(_MSC_VER)
    #if (_MSC_VER >= 1900) && defined(_HAS_CXX20) && (_HAS_CXX20 != 0)
      #define WIDE_INTEGER_CONSTEXPR constexpr
      #define WIDE_INTEGER_CONSTEXPR_IS_COMPILE_TIME_CONST 1
    #else
      #define WIDE_INTEGER_CONSTEXPR
      #define WIDE_INTEGER_CONSTEXPR_IS_COMPILE_TIME_CONST 0
    #endif
  #else
    #if (defined(__cplusplus) && (__cplusplus >= 201402L))
      #if defined(__AVR__) && (!defined(__GNUC__) || (defined(__GNUC__) && (__GNUC__ > 6)))
      #define WIDE_INTEGER_CONSTEXPR constexpr
      #define WIDE_INTEGER_CONSTEXPR_IS_COMPILE_TIME_CONST 1
      #elif (defined(__cpp_lib_constexpr_algorithms) && (__cpp_lib_constexpr_algorithms>=201806))
        #if defined(__clang__)
          #if (__clang_major__ > 9)
          #define WIDE_INTEGER_CONSTEXPR constexpr
          #define WIDE_INTEGER_CONSTEXPR_IS_COMPILE_TIME_CONST 1
          #else
          #define WIDE_INTEGER_CONSTEXPR
          #define WIDE_INTEGER_CONSTEXPR_IS_COMPILE_TIME_CONST 0
          #endif
        #else
        #define WIDE_INTEGER_CONSTEXPR constexpr
        #define WIDE_INTEGER_CONSTEXPR_IS_COMPILE_TIME_CONST 1
        #endif
      #else
      #define WIDE_INTEGER_CONSTEXPR
      #define WIDE_INTEGER_CONSTEXPR_IS_COMPILE_TIME_CONST 0
      #endif
    #else
      #define WIDE_INTEGER_CONSTEXPR
      #define WIDE_INTEGER_CONSTEXPR_IS_COMPILE_TIME_CONST 0
    #endif
  #endif

  namespace math { namespace wide_integer {

  namespace detail {

  using size_t    = std::uint32_t;
  using ptrdiff_t = std::int32_t;

  }

  using detail::size_t;
  using detail::ptrdiff_t;

  // Forward declaration of the uintwide_t template class.
  template<const size_t Width2,
           typename LimbType = std::uint32_t,
           typename AllocatorType = void,
           const bool IsSigned = false>
  class uintwide_t;

  // Forward declarations of non-member binary add, sub, mul, div, mod of (uintwide_t op uintwide_t).
  template<const size_t Width2, typename LimbType, typename AllocatorType, const bool IsSigned> constexpr uintwide_t<Width2, LimbType, AllocatorType, IsSigned> operator+(const uintwide_t<Width2, LimbType, AllocatorType, IsSigned>& u, const uintwide_t<Width2, LimbType, AllocatorType, IsSigned>& v);
  template<const size_t Width2, typename LimbType, typename AllocatorType, const bool IsSigned> constexpr uintwide_t<Width2, LimbType, AllocatorType, IsSigned> operator-(const uintwide_t<Width2, LimbType, AllocatorType, IsSigned>& u, const uintwide_t<Width2, LimbType, AllocatorType, IsSigned>& v);
  template<const size_t Width2, typename LimbType, typename AllocatorType, const bool IsSigned> constexpr uintwide_t<Width2, LimbType, AllocatorType, IsSigned> operator*(const uintwide_t<Width2, LimbType, AllocatorType, IsSigned>& u, const uintwide_t<Width2, LimbType, AllocatorType, IsSigned>& v);
  template<const size_t Width2, typename LimbType, typename AllocatorType, const bool IsSigned> constexpr uintwide_t<Width2, LimbType, AllocatorType, IsSigned> operator/(const uintwide_t<Width2, LimbType, AllocatorType, IsSigned>& u, const uintwide_t<Width2, LimbType, AllocatorType, IsSigned>& v);
  template<const size_t Width2, typename LimbType, typename AllocatorType, const bool IsSigned> constexpr uintwide_t<Width2, LimbType, AllocatorType, IsSigned> operator%(const uintwide_t<Width2, LimbType, AllocatorType, IsSigned>& u, const uintwide_t<Width2, LimbType, AllocatorType, IsSigned>& v);

  // Forward declarations of non-member binary add, sub, mul, div, mod of (uintwide_t op IntegralType).
  template<typename IntegralType, const size_t Width2, typename LimbType, typename AllocatorType, const bool IsSigned> constexpr typename std::enable_if<((std::is_fundamental<IntegralType>::value == true) && (std::is_integral   <IntegralType>::value == true)), uintwide_t<Width2, LimbType, AllocatorType, IsSigned>>::type operator+(const uintwide_t<Width2, LimbType, AllocatorType, IsSigned>& u, const IntegralType& v);
  template<typename IntegralType, const size_t Width2, typename LimbType, typename AllocatorType, const bool IsSigned> constexpr typename std::enable_if<((std::is_fundamental<IntegralType>::value == true) && (std::is_integral   <IntegralType>::value == true)), uintwide_t<Width2, LimbType, AllocatorType, IsSigned>>::type operator-(const uintwide_t<Width2, LimbType, AllocatorType, IsSigned>& u, const IntegralType& v);
  template<typename IntegralType, const size_t Width2, typename LimbType, typename AllocatorType, const bool IsSigned> constexpr typename std::enable_if<((std::is_fundamental<IntegralType>::value == true) && (std::is_integral   <IntegralType>::value == true)), uintwide_t<Width2, LimbType, AllocatorType, IsSigned>>::type operator*(const uintwide_t<Width2, LimbType, AllocatorType, IsSigned>& u, const IntegralType& v);
  template<typename IntegralType, const size_t Width2, typename LimbType, typename AllocatorType, const bool IsSigned> constexpr typename std::enable_if<((std::is_fundamental<IntegralType>::value == true) && (std::is_integral   <IntegralType>::value == true)), uintwide_t<Width2, LimbType, AllocatorType, IsSigned>>::type operator/(const uintwide_t<Width2, LimbType, AllocatorType, IsSigned>& u, const IntegralType& v);

  template<typename IntegralType, const size_t Width2, typename LimbType, typename AllocatorType, const bool IsSigned>
  WIDE_INTEGER_CONSTEXPR typename std::enable_if<(   (std::is_fundamental<IntegralType>::value == true)
                                                  && (std::is_integral   <IntegralType>::value == true)
                                                  && (std::is_unsigned   <IntegralType>::value == true)
                                                  && (std::numeric_limits<IntegralType>::digits <= std::numeric_limits<LimbType>::digits)), typename uintwide_t<Width2, LimbType, AllocatorType, IsSigned>::limb_type>::type
  operator%(const uintwide_t<Width2, LimbType, AllocatorType, IsSigned>& u, const IntegralType& v);

  template<typename IntegralType, const size_t Width2, typename LimbType, typename AllocatorType, const bool IsSigned>
  constexpr typename std::enable_if<(   (std::is_fundamental<IntegralType>::value == true)
                                     && (std::is_integral   <IntegralType>::value == true)
                                     && (std::is_unsigned   <IntegralType>::value == true)
                                     && (std::numeric_limits<IntegralType>::digits > std::numeric_limits<LimbType>::digits)), uintwide_t<Width2, LimbType, AllocatorType, IsSigned>>::type
  operator%(const uintwide_t<Width2, LimbType, AllocatorType, IsSigned>& u, const IntegralType& v);

  // Forward declarations of non-member binary add, sub, mul, div, mod of (IntegralType op uintwide_t).
  template<typename IntegralType, const size_t Width2, typename LimbType, typename AllocatorType, const bool IsSigned> constexpr typename std::enable_if<((std::is_fundamental<IntegralType>::value == true) && (std::is_integral<IntegralType>::value == true)), uintwide_t<Width2, LimbType, AllocatorType, IsSigned>>::type operator+(const IntegralType& u, const uintwide_t<Width2, LimbType, AllocatorType, IsSigned>& v);
  template<typename IntegralType, const size_t Width2, typename LimbType, typename AllocatorType, const bool IsSigned> constexpr typename std::enable_if<((std::is_fundamental<IntegralType>::value == true) && (std::is_integral<IntegralType>::value == true)), uintwide_t<Width2, LimbType, AllocatorType, IsSigned>>::type operator-(const IntegralType& u, const uintwide_t<Width2, LimbType, AllocatorType, IsSigned>& v);
  template<typename IntegralType, const size_t Width2, typename LimbType, typename AllocatorType, const bool IsSigned> constexpr typename std::enable_if<((std::is_fundamental<IntegralType>::value == true) && (std::is_integral<IntegralType>::value == true)), uintwide_t<Width2, LimbType, AllocatorType, IsSigned>>::type operator*(const IntegralType& u, const uintwide_t<Width2, LimbType, AllocatorType, IsSigned>& v);
  template<typename IntegralType, const size_t Width2, typename LimbType, typename AllocatorType, const bool IsSigned> constexpr typename std::enable_if<((std::is_fundamental<IntegralType>::value == true) && (std::is_integral<IntegralType>::value == true)), uintwide_t<Width2, LimbType, AllocatorType, IsSigned>>::type operator/(const IntegralType& u, const uintwide_t<Width2, LimbType, AllocatorType, IsSigned>& v);
  template<typename IntegralType, const size_t Width2, typename LimbType, typename AllocatorType, const bool IsSigned> constexpr typename std::enable_if<((std::is_fundamental<IntegralType>::value == true) && (std::is_integral<IntegralType>::value == true)), uintwide_t<Width2, LimbType, AllocatorType, IsSigned>>::type operator%(const IntegralType& u, const uintwide_t<Width2, LimbType, AllocatorType, IsSigned>& v);

  #if !defined(WIDE_INTEGER_DISABLE_FLOAT_INTEROP)
  // Forward declarations of non-member binary add, sub, mul, div, mod of (uintwide_t op FloatingPointType).
  template<typename FloatingPointType, const size_t Width2, typename LimbType, typename AllocatorType, const bool IsSigned> constexpr typename std::enable_if<((std::is_fundamental<FloatingPointType>::value == true) && (std::is_floating_point<FloatingPointType>::value == true)), uintwide_t<Width2, LimbType, AllocatorType, IsSigned>>::type operator+(const uintwide_t<Width2, LimbType, AllocatorType, IsSigned>& u, const FloatingPointType& f);
  template<typename FloatingPointType, const size_t Width2, typename LimbType, typename AllocatorType, const bool IsSigned> constexpr typename std::enable_if<((std::is_fundamental<FloatingPointType>::value == true) && (std::is_floating_point<FloatingPointType>::value == true)), uintwide_t<Width2, LimbType, AllocatorType, IsSigned>>::type operator-(const uintwide_t<Width2, LimbType, AllocatorType, IsSigned>& u, const FloatingPointType& f);
  template<typename FloatingPointType, const size_t Width2, typename LimbType, typename AllocatorType, const bool IsSigned> constexpr typename std::enable_if<((std::is_fundamental<FloatingPointType>::value == true) && (std::is_floating_point<FloatingPointType>::value == true)), uintwide_t<Width2, LimbType, AllocatorType, IsSigned>>::type operator*(const uintwide_t<Width2, LimbType, AllocatorType, IsSigned>& u, const FloatingPointType& f);
  template<typename FloatingPointType, const size_t Width2, typename LimbType, typename AllocatorType, const bool IsSigned> constexpr typename std::enable_if<((std::is_fundamental<FloatingPointType>::value == true) && (std::is_floating_point<FloatingPointType>::value == true)), uintwide_t<Width2, LimbType, AllocatorType, IsSigned>>::type operator/(const uintwide_t<Width2, LimbType, AllocatorType, IsSigned>& u, const FloatingPointType& f);
  template<typename FloatingPointType, const size_t Width2, typename LimbType, typename AllocatorType, const bool IsSigned> constexpr typename std::enable_if<((std::is_fundamental<FloatingPointType>::value == true) && (std::is_floating_point<FloatingPointType>::value == true)), uintwide_t<Width2, LimbType, AllocatorType, IsSigned>>::type operator%(const uintwide_t<Width2, LimbType, AllocatorType, IsSigned>& u, const FloatingPointType& f);

  // Forward declarations of non-member binary add, sub, mul, div, mod of (FloatingPointType op uintwide_t).
  template<typename FloatingPointType, const size_t Width2, typename LimbType, typename AllocatorType, const bool IsSigned> constexpr typename std::enable_if<((std::is_fundamental<FloatingPointType>::value == true) && (std::is_floating_point<FloatingPointType>::value == true)), uintwide_t<Width2, LimbType, AllocatorType, IsSigned>>::type operator+(const FloatingPointType& f, const uintwide_t<Width2, LimbType, AllocatorType, IsSigned>& v);
  template<typename FloatingPointType, const size_t Width2, typename LimbType, typename AllocatorType, const bool IsSigned> constexpr typename std::enable_if<((std::is_fundamental<FloatingPointType>::value == true) && (std::is_floating_point<FloatingPointType>::value == true)), uintwide_t<Width2, LimbType, AllocatorType, IsSigned>>::type operator-(const FloatingPointType& f, const uintwide_t<Width2, LimbType, AllocatorType, IsSigned>& v);
  template<typename FloatingPointType, const size_t Width2, typename LimbType, typename AllocatorType, const bool IsSigned> constexpr typename std::enable_if<((std::is_fundamental<FloatingPointType>::value == true) && (std::is_floating_point<FloatingPointType>::value == true)), uintwide_t<Width2, LimbType, AllocatorType, IsSigned>>::type operator*(const FloatingPointType& f, const uintwide_t<Width2, LimbType, AllocatorType, IsSigned>& v);
  template<typename FloatingPointType, const size_t Width2, typename LimbType, typename AllocatorType, const bool IsSigned> constexpr typename std::enable_if<((std::is_fundamental<FloatingPointType>::value == true) && (std::is_floating_point<FloatingPointType>::value == true)), uintwide_t<Width2, LimbType, AllocatorType, IsSigned>>::type operator/(const FloatingPointType& f, const uintwide_t<Width2, LimbType, AllocatorType, IsSigned>& v);
  template<typename FloatingPointType, const size_t Width2, typename LimbType, typename AllocatorType, const bool IsSigned> constexpr typename std::enable_if<((std::is_fundamental<FloatingPointType>::value == true) && (std::is_floating_point<FloatingPointType>::value == true)), uintwide_t<Width2, LimbType, AllocatorType, IsSigned>>::type operator%(const FloatingPointType& f, const uintwide_t<Width2, LimbType, AllocatorType, IsSigned>& v);
  #endif

  // Forward declarations of non-member binary logic operations of (uintwide_t op uintwide_t).
  template<const size_t Width2, typename LimbType, typename AllocatorType, const bool IsSigned> constexpr uintwide_t<Width2, LimbType, AllocatorType, IsSigned> operator|(const uintwide_t<Width2, LimbType, AllocatorType, IsSigned>& u, const uintwide_t<Width2, LimbType, AllocatorType, IsSigned>& v);
  template<const size_t Width2, typename LimbType, typename AllocatorType, const bool IsSigned> constexpr uintwide_t<Width2, LimbType, AllocatorType, IsSigned> operator^(const uintwide_t<Width2, LimbType, AllocatorType, IsSigned>& u, const uintwide_t<Width2, LimbType, AllocatorType, IsSigned>& v);
  template<const size_t Width2, typename LimbType, typename AllocatorType, const bool IsSigned> constexpr uintwide_t<Width2, LimbType, AllocatorType, IsSigned> operator&(const uintwide_t<Width2, LimbType, AllocatorType, IsSigned>& u, const uintwide_t<Width2, LimbType, AllocatorType, IsSigned>& v);

  // Forward declarations of non-member binary logic operations of (uintwide_t op IntegralType).
  template<typename IntegralType, const size_t Width2, typename LimbType, typename AllocatorType, const bool IsSigned> constexpr typename std::enable_if<((std::is_fundamental<IntegralType>::value == true) && (std::is_integral<IntegralType>::value == true)), uintwide_t<Width2, LimbType, AllocatorType, IsSigned>>::type operator|(const uintwide_t<Width2, LimbType, AllocatorType, IsSigned>& u, const IntegralType& v);
  template<typename IntegralType, const size_t Width2, typename LimbType, typename AllocatorType, const bool IsSigned> constexpr typename std::enable_if<((std::is_fundamental<IntegralType>::value == true) && (std::is_integral<IntegralType>::value == true)), uintwide_t<Width2, LimbType, AllocatorType, IsSigned>>::type operator^(const uintwide_t<Width2, LimbType, AllocatorType, IsSigned>& u, const IntegralType& v);
  template<typename IntegralType, const size_t Width2, typename LimbType, typename AllocatorType, const bool IsSigned> constexpr typename std::enable_if<((std::is_fundamental<IntegralType>::value == true) && (std::is_integral<IntegralType>::value == true)), uintwide_t<Width2, LimbType, AllocatorType, IsSigned>>::type operator&(const uintwide_t<Width2, LimbType, AllocatorType, IsSigned>& u, const IntegralType& v);

  // Forward declarations of non-member binary binary logic operations of (IntegralType op uintwide_t).
  template<typename IntegralType, const size_t Width2, typename LimbType, typename AllocatorType, const bool IsSigned> constexpr typename std::enable_if<((std::is_fundamental<IntegralType>::value == true) && (std::is_integral<IntegralType>::value == true)), uintwide_t<Width2, LimbType, AllocatorType, IsSigned>>::type operator|(const IntegralType& u, const uintwide_t<Width2, LimbType, AllocatorType, IsSigned>& v);
  template<typename IntegralType, const size_t Width2, typename LimbType, typename AllocatorType, const bool IsSigned> constexpr typename std::enable_if<((std::is_fundamental<IntegralType>::value == true) && (std::is_integral<IntegralType>::value == true)), uintwide_t<Width2, LimbType, AllocatorType, IsSigned>>::type operator^(const IntegralType& u, const uintwide_t<Width2, LimbType, AllocatorType, IsSigned>& v);
  template<typename IntegralType, const size_t Width2, typename LimbType, typename AllocatorType, const bool IsSigned> constexpr typename std::enable_if<((std::is_fundamental<IntegralType>::value == true) && (std::is_integral<IntegralType>::value == true)), uintwide_t<Width2, LimbType, AllocatorType, IsSigned>>::type operator&(const IntegralType& u, const uintwide_t<Width2, LimbType, AllocatorType, IsSigned>& v);

  // Forward declarations of non-member shift functions of (uintwide_t shift IntegralType).
  template<typename IntegralType, const size_t Width2, typename LimbType, typename AllocatorType, const bool IsSigned> constexpr typename std::enable_if<((std::is_fundamental<IntegralType>::value == true) && (std::is_integral<IntegralType>::value == true)), uintwide_t<Width2, LimbType, AllocatorType, IsSigned>>::type operator<<(const uintwide_t<Width2, LimbType, AllocatorType, IsSigned>& u, const IntegralType n);
  template<typename IntegralType, const size_t Width2, typename LimbType, typename AllocatorType, const bool IsSigned> constexpr typename std::enable_if<((std::is_fundamental<IntegralType>::value == true) && (std::is_integral<IntegralType>::value == true)), uintwide_t<Width2, LimbType, AllocatorType, IsSigned>>::type operator>>(const uintwide_t<Width2, LimbType, AllocatorType, IsSigned>& u, const IntegralType n);

  // Forward declarations of non-member comparison functions of (uintwide_t cmp uintwide_t).
  template<const size_t Width2, typename LimbType, typename AllocatorType, const bool IsSigned> constexpr bool operator==(const uintwide_t<Width2, LimbType, AllocatorType, IsSigned>& u, const uintwide_t<Width2, LimbType, AllocatorType, IsSigned>& v);
  template<const size_t Width2, typename LimbType, typename AllocatorType, const bool IsSigned> constexpr bool operator!=(const uintwide_t<Width2, LimbType, AllocatorType, IsSigned>& u, const uintwide_t<Width2, LimbType, AllocatorType, IsSigned>& v);
  template<const size_t Width2, typename LimbType, typename AllocatorType, const bool IsSigned> constexpr bool operator> (const uintwide_t<Width2, LimbType, AllocatorType, IsSigned>& u, const uintwide_t<Width2, LimbType, AllocatorType, IsSigned>& v);
  template<const size_t Width2, typename LimbType, typename AllocatorType, const bool IsSigned> constexpr bool operator< (const uintwide_t<Width2, LimbType, AllocatorType, IsSigned>& u, const uintwide_t<Width2, LimbType, AllocatorType, IsSigned>& v);
  template<const size_t Width2, typename LimbType, typename AllocatorType, const bool IsSigned> constexpr bool operator>=(const uintwide_t<Width2, LimbType, AllocatorType, IsSigned>& u, const uintwide_t<Width2, LimbType, AllocatorType, IsSigned>& v);
  template<const size_t Width2, typename LimbType, typename AllocatorType, const bool IsSigned> constexpr bool operator<=(const uintwide_t<Width2, LimbType, AllocatorType, IsSigned>& u, const uintwide_t<Width2, LimbType, AllocatorType, IsSigned>& v);

  // Forward declarations of non-member comparison functions of (uintwide_t cmp IntegralType).
  template<typename IntegralType, const size_t Width2, typename LimbType, typename AllocatorType, const bool IsSigned> constexpr typename std::enable_if<((std::is_fundamental<IntegralType>::value == true) && (std::is_integral<IntegralType>::value == true)), bool>::type operator==(const uintwide_t<Width2, LimbType, AllocatorType, IsSigned>& u, const IntegralType& v);
  template<typename IntegralType, const size_t Width2, typename LimbType, typename AllocatorType, const bool IsSigned> constexpr typename std::enable_if<((std::is_fundamental<IntegralType>::value == true) && (std::is_integral<IntegralType>::value == true)), bool>::type operator!=(const uintwide_t<Width2, LimbType, AllocatorType, IsSigned>& u, const IntegralType& v);
  template<typename IntegralType, const size_t Width2, typename LimbType, typename AllocatorType, const bool IsSigned> constexpr typename std::enable_if<((std::is_fundamental<IntegralType>::value == true) && (std::is_integral<IntegralType>::value == true)), bool>::type operator> (const uintwide_t<Width2, LimbType, AllocatorType, IsSigned>& u, const IntegralType& v);
  template<typename IntegralType, const size_t Width2, typename LimbType, typename AllocatorType, const bool IsSigned> constexpr typename std::enable_if<((std::is_fundamental<IntegralType>::value == true) && (std::is_integral<IntegralType>::value == true)), bool>::type operator< (const uintwide_t<Width2, LimbType, AllocatorType, IsSigned>& u, const IntegralType& v);
  template<typename IntegralType, const size_t Width2, typename LimbType, typename AllocatorType, const bool IsSigned> constexpr typename std::enable_if<((std::is_fundamental<IntegralType>::value == true) && (std::is_integral<IntegralType>::value == true)), bool>::type operator>=(const uintwide_t<Width2, LimbType, AllocatorType, IsSigned>& u, const IntegralType& v);
  template<typename IntegralType, const size_t Width2, typename LimbType, typename AllocatorType, const bool IsSigned> constexpr typename std::enable_if<((std::is_fundamental<IntegralType>::value == true) && (std::is_integral<IntegralType>::value == true)), bool>::type operator<=(const uintwide_t<Width2, LimbType, AllocatorType, IsSigned>& u, const IntegralType& v);

  // Forward declarations of non-member comparison functions of (IntegralType cmp uintwide_t).
  template<typename IntegralType, const size_t Width2, typename LimbType, typename AllocatorType, const bool IsSigned> constexpr typename std::enable_if<((std::is_fundamental<IntegralType>::value == true) && (std::is_integral   <IntegralType>::value == true)), bool>::type operator==(const IntegralType& u, const uintwide_t<Width2, LimbType, AllocatorType, IsSigned>& v);
  template<typename IntegralType, const size_t Width2, typename LimbType, typename AllocatorType, const bool IsSigned> constexpr typename std::enable_if<((std::is_fundamental<IntegralType>::value == true) && (std::is_integral   <IntegralType>::value == true)), bool>::type operator!=(const IntegralType& u, const uintwide_t<Width2, LimbType, AllocatorType, IsSigned>& v);
  template<typename IntegralType, const size_t Width2, typename LimbType, typename AllocatorType, const bool IsSigned> constexpr typename std::enable_if<((std::is_fundamental<IntegralType>::value == true) && (std::is_integral   <IntegralType>::value == true)), bool>::type operator> (const IntegralType& u, const uintwide_t<Width2, LimbType, AllocatorType, IsSigned>& v);
  template<typename IntegralType, const size_t Width2, typename LimbType, typename AllocatorType, const bool IsSigned> constexpr typename std::enable_if<((std::is_fundamental<IntegralType>::value == true) && (std::is_integral   <IntegralType>::value == true)), bool>::type operator< (const IntegralType& u, const uintwide_t<Width2, LimbType, AllocatorType, IsSigned>& v);
  template<typename IntegralType, const size_t Width2, typename LimbType, typename AllocatorType, const bool IsSigned> constexpr typename std::enable_if<((std::is_fundamental<IntegralType>::value == true) && (std::is_integral   <IntegralType>::value == true)), bool>::type operator>=(const IntegralType& u, const uintwide_t<Width2, LimbType, AllocatorType, IsSigned>& v);
  template<typename IntegralType, const size_t Width2, typename LimbType, typename AllocatorType, const bool IsSigned> constexpr typename std::enable_if<((std::is_fundamental<IntegralType>::value == true) && (std::is_integral   <IntegralType>::value == true)), bool>::type operator<=(const IntegralType& u, const uintwide_t<Width2, LimbType, AllocatorType, IsSigned>& v);

  #if !defined(WIDE_INTEGER_DISABLE_FLOAT_INTEROP)
  // Non-member comparison functions of (uintwide_t cmp FloatingPointType).
  template<typename FloatingPointType, const size_t Width2, typename LimbType, typename AllocatorType, const bool IsSigned> constexpr typename std::enable_if<((std::is_fundamental<FloatingPointType>::value == true) && (std::is_floating_point<FloatingPointType>::value == true)), bool>::type operator==(const uintwide_t<Width2, LimbType, AllocatorType, IsSigned>& u, const FloatingPointType& f);
  template<typename FloatingPointType, const size_t Width2, typename LimbType, typename AllocatorType, const bool IsSigned> constexpr typename std::enable_if<((std::is_fundamental<FloatingPointType>::value == true) && (std::is_floating_point<FloatingPointType>::value == true)), bool>::type operator!=(const uintwide_t<Width2, LimbType, AllocatorType, IsSigned>& u, const FloatingPointType& f);
  template<typename FloatingPointType, const size_t Width2, typename LimbType, typename AllocatorType, const bool IsSigned> constexpr typename std::enable_if<((std::is_fundamental<FloatingPointType>::value == true) && (std::is_floating_point<FloatingPointType>::value == true)), bool>::type operator> (const uintwide_t<Width2, LimbType, AllocatorType, IsSigned>& u, const FloatingPointType& f);
  template<typename FloatingPointType, const size_t Width2, typename LimbType, typename AllocatorType, const bool IsSigned> constexpr typename std::enable_if<((std::is_fundamental<FloatingPointType>::value == true) && (std::is_floating_point<FloatingPointType>::value == true)), bool>::type operator< (const uintwide_t<Width2, LimbType, AllocatorType, IsSigned>& u, const FloatingPointType& f);
  template<typename FloatingPointType, const size_t Width2, typename LimbType, typename AllocatorType, const bool IsSigned> constexpr typename std::enable_if<((std::is_fundamental<FloatingPointType>::value == true) && (std::is_floating_point<FloatingPointType>::value == true)), bool>::type operator>=(const uintwide_t<Width2, LimbType, AllocatorType, IsSigned>& u, const FloatingPointType& f);
  template<typename FloatingPointType, const size_t Width2, typename LimbType, typename AllocatorType, const bool IsSigned> constexpr typename std::enable_if<((std::is_fundamental<FloatingPointType>::value == true) && (std::is_floating_point<FloatingPointType>::value == true)), bool>::type operator<=(const uintwide_t<Width2, LimbType, AllocatorType, IsSigned>& u, const FloatingPointType& f);

  // Non-member comparison functions of (FloatingPointType cmp uintwide_t).
  template<typename FloatingPointType, const size_t Width2, typename LimbType, typename AllocatorType, const bool IsSigned> constexpr typename std::enable_if<((std::is_fundamental<FloatingPointType>::value == true) && (std::is_floating_point<FloatingPointType>::value == true)), bool>::type operator==(const FloatingPointType& f, const uintwide_t<Width2, LimbType, AllocatorType, IsSigned>& v);
  template<typename FloatingPointType, const size_t Width2, typename LimbType, typename AllocatorType, const bool IsSigned> constexpr typename std::enable_if<((std::is_fundamental<FloatingPointType>::value == true) && (std::is_floating_point<FloatingPointType>::value == true)), bool>::type operator!=(const FloatingPointType& f, const uintwide_t<Width2, LimbType, AllocatorType, IsSigned>& v);
  template<typename FloatingPointType, const size_t Width2, typename LimbType, typename AllocatorType, const bool IsSigned> constexpr typename std::enable_if<((std::is_fundamental<FloatingPointType>::value == true) && (std::is_floating_point<FloatingPointType>::value == true)), bool>::type operator> (const FloatingPointType& f, const uintwide_t<Width2, LimbType, AllocatorType, IsSigned>& v);
  template<typename FloatingPointType, const size_t Width2, typename LimbType, typename AllocatorType, const bool IsSigned> constexpr typename std::enable_if<((std::is_fundamental<FloatingPointType>::value == true) && (std::is_floating_point<FloatingPointType>::value == true)), bool>::type operator< (const FloatingPointType& f, const uintwide_t<Width2, LimbType, AllocatorType, IsSigned>& v);
  template<typename FloatingPointType, const size_t Width2, typename LimbType, typename AllocatorType, const bool IsSigned> constexpr typename std::enable_if<((std::is_fundamental<FloatingPointType>::value == true) && (std::is_floating_point<FloatingPointType>::value == true)), bool>::type operator>=(const FloatingPointType& f, const uintwide_t<Width2, LimbType, AllocatorType, IsSigned>& v);
  template<typename FloatingPointType, const size_t Width2, typename LimbType, typename AllocatorType, const bool IsSigned> constexpr typename std::enable_if<((std::is_fundamental<FloatingPointType>::value == true) && (std::is_floating_point<FloatingPointType>::value == true)), bool>::type operator<=(const FloatingPointType& f, const uintwide_t<Width2, LimbType, AllocatorType, IsSigned>& v);
  #endif

  #if !defined(WIDE_INTEGER_DISABLE_IOSTREAM)

  // Forward declarations of I/O streaming functions.
  template<typename char_type,
           typename traits_type,
           const size_t Width2,
           typename LimbType,
           typename AllocatorType,
           const bool IsSigned>
  std::basic_ostream<char_type,
                     traits_type>& operator<<(std::basic_ostream<char_type, traits_type>& out,
                                              const uintwide_t<Width2, LimbType, AllocatorType, IsSigned>& x);

  template<typename char_type,
           typename traits_type,
           const size_t Width2,
           typename LimbType,
           typename AllocatorType,
           const bool IsSigned>
  std::basic_istream<char_type,
                     traits_type>& operator>>(std::basic_istream<char_type, traits_type>& in,
                                              uintwide_t<Width2, LimbType, AllocatorType, IsSigned>& x);

  #endif

  // Forward declarations of various number-theoretical tools.
  template<const size_t Width2,
           typename LimbType,
           typename AllocatorType,
           const bool IsSigned>
  WIDE_INTEGER_CONSTEXPR void swap(uintwide_t<Width2, LimbType, AllocatorType, IsSigned>& x,
                                   uintwide_t<Width2, LimbType, AllocatorType, IsSigned>& y);

  template<const size_t Width2,
           typename LimbType,
           typename AllocatorType,
           const bool IsSigned>
  WIDE_INTEGER_CONSTEXPR std::uint_fast32_t lsb(const uintwide_t<Width2, LimbType, AllocatorType, IsSigned>& x);

  template<const size_t Width2,
           typename LimbType,
           typename AllocatorType,
           const bool IsSigned>
  WIDE_INTEGER_CONSTEXPR std::uint_fast32_t msb(const uintwide_t<Width2, LimbType, AllocatorType, IsSigned>& x);

  template<const size_t Width2,
           typename LimbType,
           typename AllocatorType,
           const bool IsSigned>
  WIDE_INTEGER_CONSTEXPR uintwide_t<Width2, LimbType, AllocatorType, IsSigned> sqrt(const uintwide_t<Width2, LimbType, AllocatorType, IsSigned>& m);

  template<const size_t Width2,
           typename LimbType,
           typename AllocatorType,
           const bool IsSigned>
  WIDE_INTEGER_CONSTEXPR uintwide_t<Width2, LimbType, AllocatorType, IsSigned> cbrt(const uintwide_t<Width2, LimbType, AllocatorType, IsSigned>& m);

  template<const size_t Width2,
           typename LimbType,
           typename AllocatorType,
           const bool IsSigned>
  WIDE_INTEGER_CONSTEXPR uintwide_t<Width2, LimbType, AllocatorType, IsSigned> rootk(const uintwide_t<Width2, LimbType, AllocatorType, IsSigned>& m,
                                                                                     const std::uint_fast8_t k);

  template<typename OtherUnsignedIntegralTypeP,
           const size_t Width2,
           typename LimbType,
           typename AllocatorType,
           const bool IsSigned>
  WIDE_INTEGER_CONSTEXPR uintwide_t<Width2, LimbType, AllocatorType, IsSigned> pow(const uintwide_t<Width2, LimbType, AllocatorType, IsSigned>& b,
                                                                                   const OtherUnsignedIntegralTypeP& p);

  template<typename OtherUnsignedIntegralTypeP,
           typename OtherUnsignedIntegralTypeM,
           const size_t Width2,
           typename LimbType,
           typename AllocatorType,
           const bool IsSigned>
  WIDE_INTEGER_CONSTEXPR uintwide_t<Width2, LimbType, AllocatorType, IsSigned> powm(const uintwide_t<Width2, LimbType, AllocatorType, IsSigned>& b,
                                                                                    const OtherUnsignedIntegralTypeP&    p,
                                                                                    const OtherUnsignedIntegralTypeM&    m);

  template<const size_t Width2,
           typename LimbType,
           typename AllocatorType,
           const bool IsSigned>
  WIDE_INTEGER_CONSTEXPR uintwide_t<Width2, LimbType, AllocatorType, IsSigned> gcd(const uintwide_t<Width2, LimbType, AllocatorType, IsSigned>& a,
                                                                                   const uintwide_t<Width2, LimbType, AllocatorType, IsSigned>& b);

  template<typename UnsignedShortType>
  WIDE_INTEGER_CONSTEXPR typename std::enable_if<(   (std::is_fundamental<UnsignedShortType>::value == true)
                                                  && (std::is_integral   <UnsignedShortType>::value == true)
                                                  && (std::is_unsigned   <UnsignedShortType>::value == true)), UnsignedShortType>::type
  gcd(const UnsignedShortType& u, const UnsignedShortType& v);

  template<const size_t Width2,
           typename LimbType = std::uint32_t,
           typename AllocatorType = void,
           const bool IsSigned = false>
  class default_random_engine;

  template<const size_t Width2,
           typename LimbType = std::uint32_t,
           typename AllocatorType = void,
           const bool IsSigned = false>
  class uniform_int_distribution;

  template<const size_t Width2,
           typename LimbType,
           typename AllocatorType,
           const bool IsSigned>
  constexpr bool operator==(const uniform_int_distribution<Width2, LimbType, AllocatorType, IsSigned>& lhs,
                            const uniform_int_distribution<Width2, LimbType, AllocatorType, IsSigned>& rhs);

  template<const size_t Width2,
           typename LimbType,
           typename AllocatorType,
           const bool IsSigned>
  constexpr bool operator!=(const uniform_int_distribution<Width2, LimbType, AllocatorType, IsSigned>& lhs,
                            const uniform_int_distribution<Width2, LimbType, AllocatorType, IsSigned>& rhs);

  template<typename DistributionType,
           typename GeneratorType,
           const size_t Width2,
           typename LimbType,
           typename AllocatorType,
           const bool IsSigned>
  bool miller_rabin(const uintwide_t<Width2, LimbType, AllocatorType, IsSigned>& n,
                    const std::uint_fast32_t                                     number_of_trials,
                    DistributionType&                                            distribution,
                    GeneratorType&                                               generator);

  } } // namespace math::wide_integer

  namespace std
  {
    // Forward declaration of specialization of std::numeric_limits<uintwide_t>.
    template<const math::wide_integer::size_t Width2,
             typename LimbType,
             typename AllocatorType,
             const bool IsSigned>
    class numeric_limits<math::wide_integer::uintwide_t<Width2, LimbType, AllocatorType, IsSigned>>;
  }

  namespace math { namespace wide_integer { namespace detail {

  template<typename MyType,
           const std::uint_fast32_t MySize,
           typename MyAlloc>
  class fixed_dynamic_array final : public util::dynamic_array<MyType, MyAlloc, std::uint_fast32_t, std::int_fast32_t>
  {
  private:
    using base_class_type = util::dynamic_array<MyType, MyAlloc, std::uint_fast32_t, std::int_fast32_t>;

  public:
    static constexpr std::uint_fast32_t static_size() { return MySize; }

    fixed_dynamic_array(const typename base_class_type::size_type       s = MySize,
                        const typename base_class_type::value_type&     v = typename base_class_type::value_type(),
                        const typename base_class_type::allocator_type& a = typename base_class_type::allocator_type())
      : base_class_type(MySize, typename base_class_type::value_type(), a)
    {
      std::fill(base_class_type::begin(),
                base_class_type::begin() + (std::min)(MySize, (std::uint_fast32_t) s),
                v);
    }

    constexpr fixed_dynamic_array(const fixed_dynamic_array& other_array)
      : base_class_type((const base_class_type&) other_array) { }

    explicit fixed_dynamic_array(std::initializer_list<typename base_class_type::value_type> lst)
      : base_class_type(MySize)
    {
      std::copy(lst.begin(),
                lst.begin() + (std::min)((std::uint_fast32_t) lst.size(), MySize),
                base_class_type::begin());
    }

    constexpr fixed_dynamic_array(fixed_dynamic_array&& other_array)
      : base_class_type((base_class_type&&) other_array) { }

    fixed_dynamic_array& operator=(const fixed_dynamic_array& other_array)
    {
      base_class_type::operator=((const base_class_type&) other_array);

      return *this;
    }

    fixed_dynamic_array& operator=(fixed_dynamic_array&& other_array)
    {
      base_class_type::operator=((base_class_type&&) other_array);

      return *this;
    }

    virtual ~fixed_dynamic_array() = default;
  };

  template<typename MyType,
           const std::uint_fast32_t MySize>
  class fixed_static_array final : public std::array<MyType, MySize>
  {
  private:
    using base_class_type = std::array<MyType, MySize>;

  public:
    static constexpr std::uint_fast32_t static_size() { return MySize; }

    constexpr fixed_static_array() { }

    WIDE_INTEGER_CONSTEXPR fixed_static_array(const typename base_class_type::size_type   s,
                                              const typename base_class_type::value_type& v = typename base_class_type::value_type())
    {
      std::fill(base_class_type::begin(),
                base_class_type::begin() + (std::min)(MySize, (std::uint_fast32_t) s),
                v);

      std::fill(base_class_type::begin() + (std::min)(MySize, (std::uint_fast32_t) s),
                base_class_type::end(),
                typename base_class_type::value_type());
    }

    constexpr fixed_static_array(const fixed_static_array& other_array)
      : base_class_type(static_cast<const base_class_type&>(other_array)) { }

    template<const std::uint_fast32_t OtherSize>
    WIDE_INTEGER_CONSTEXPR fixed_static_array(const fixed_static_array<std::uint_fast32_t, OtherSize>& other_array)
    {
      std::copy(other_array.cbegin(),
                other_array.cbegin() + (std::min)(OtherSize, MySize),
                base_class_type::begin());

      std::fill(base_class_type::begin() + (std::min)(OtherSize, MySize),
                base_class_type::end(),
                typename base_class_type::value_type());
    }

    explicit WIDE_INTEGER_CONSTEXPR fixed_static_array(std::initializer_list<typename base_class_type::value_type> lst)
    {
      std::copy(lst.begin(),
                lst.begin() + (std::min)((std::uint_fast32_t) lst.size(), MySize),
                base_class_type::begin());

      std::fill(base_class_type::begin() + (std::min)((std::uint_fast32_t) lst.size(), MySize),
                base_class_type::end(),
                typename base_class_type::value_type());
    }

    constexpr fixed_static_array(fixed_static_array&& other_array)
      : base_class_type(static_cast<base_class_type&&>(other_array)) { }

    WIDE_INTEGER_CONSTEXPR fixed_static_array& operator=(const fixed_static_array& other_array)
    {
      base_class_type::operator=((const base_class_type&) other_array);

      return *this;
    }

    WIDE_INTEGER_CONSTEXPR fixed_static_array& operator=(fixed_static_array&& other_array)
    {
      base_class_type::operator=((base_class_type&&) other_array);

      return *this;
    }
  };

  template<const size_t Width2> struct verify_power_of_two
  {
    static constexpr bool conditional_value =
         (Width2 == size_t(1ULL <<  0U)) || (Width2 == size_t(1ULL <<  1U)) || (Width2 == size_t(1ULL <<  2U)) || (Width2 == size_t(1ULL <<  3U))
      || (Width2 == size_t(1ULL <<  4U)) || (Width2 == size_t(1ULL <<  5U)) || (Width2 == size_t(1ULL <<  6U)) || (Width2 == size_t(1ULL <<  7U))
      || (Width2 == size_t(1ULL <<  8U)) || (Width2 == size_t(1ULL <<  9U)) || (Width2 == size_t(1ULL << 10U)) || (Width2 == size_t(1ULL << 11U))
      || (Width2 == size_t(1ULL << 12U)) || (Width2 == size_t(1ULL << 13U)) || (Width2 == size_t(1ULL << 14U)) || (Width2 == size_t(1ULL << 15U))
      || (Width2 == size_t(1ULL << 16U)) || (Width2 == size_t(1ULL << 17U)) || (Width2 == size_t(1ULL << 18U)) || (Width2 == size_t(1ULL << 19U))
      || (Width2 == size_t(1ULL << 20U)) || (Width2 == size_t(1ULL << 21U)) || (Width2 == size_t(1ULL << 22U)) || (Width2 == size_t(1ULL << 23U))
      || (Width2 == size_t(1ULL << 24U)) || (Width2 == size_t(1ULL << 25U)) || (Width2 == size_t(1ULL << 26U)) || (Width2 == size_t(1ULL << 27U))
      || (Width2 == size_t(1ULL << 28U)) || (Width2 == size_t(1ULL << 29U)) || (Width2 == size_t(1ULL << 30U)) || (Width2 == size_t(1ULL << 31U))
      ;
  };

  template<const size_t Width2> struct verify_power_of_two_times_granularity_one_sixty_fourth
  {
    // List of numbers used to identify the form 2^n times 1...63.
    static constexpr bool conditional_value =
       (   verify_power_of_two<size_t(Width2 /  1U)>::conditional_value || verify_power_of_two<size_t(Width2 /  3U)>::conditional_value
        || verify_power_of_two<size_t(Width2 /  5U)>::conditional_value || verify_power_of_two<size_t(Width2 /  7U)>::conditional_value
        || verify_power_of_two<size_t(Width2 /  9U)>::conditional_value || verify_power_of_two<size_t(Width2 / 11U)>::conditional_value
        || verify_power_of_two<size_t(Width2 / 13U)>::conditional_value || verify_power_of_two<size_t(Width2 / 15U)>::conditional_value
        || verify_power_of_two<size_t(Width2 / 17U)>::conditional_value || verify_power_of_two<size_t(Width2 / 19U)>::conditional_value
        || verify_power_of_two<size_t(Width2 / 21U)>::conditional_value || verify_power_of_two<size_t(Width2 / 23U)>::conditional_value
        || verify_power_of_two<size_t(Width2 / 25U)>::conditional_value || verify_power_of_two<size_t(Width2 / 27U)>::conditional_value
        || verify_power_of_two<size_t(Width2 / 29U)>::conditional_value || verify_power_of_two<size_t(Width2 / 31U)>::conditional_value
        || verify_power_of_two<size_t(Width2 / 33U)>::conditional_value || verify_power_of_two<size_t(Width2 / 35U)>::conditional_value
        || verify_power_of_two<size_t(Width2 / 37U)>::conditional_value || verify_power_of_two<size_t(Width2 / 39U)>::conditional_value
        || verify_power_of_two<size_t(Width2 / 41U)>::conditional_value || verify_power_of_two<size_t(Width2 / 43U)>::conditional_value
        || verify_power_of_two<size_t(Width2 / 45U)>::conditional_value || verify_power_of_two<size_t(Width2 / 47U)>::conditional_value
        || verify_power_of_two<size_t(Width2 / 49U)>::conditional_value || verify_power_of_two<size_t(Width2 / 51U)>::conditional_value
        || verify_power_of_two<size_t(Width2 / 53U)>::conditional_value || verify_power_of_two<size_t(Width2 / 55U)>::conditional_value
        || verify_power_of_two<size_t(Width2 / 57U)>::conditional_value || verify_power_of_two<size_t(Width2 / 59U)>::conditional_value
        || verify_power_of_two<size_t(Width2 / 61U)>::conditional_value || verify_power_of_two<size_t(Width2 / 63U)>::conditional_value);
  };

  template<const size_t BitCount,
           typename EnableType = void>
  struct uint_type_helper
  {
    #if defined(WIDE_INTEGER_HAS_LIMB_TYPE_UINT64)
    static_assert((   ((BitCount >= 8U) && (BitCount <= 128U))
                   && (verify_power_of_two<BitCount>::conditional_value == true)),
                  "Error: uint_type_helper is not intended to be used for this BitCount");
    #else
    static_assert((   ((BitCount >= 8U) && (BitCount <= 64U))
                   && (verify_power_of_two<BitCount>::conditional_value == true)),
                  "Error: uint_type_helper is not intended to be used for this BitCount");
    #endif

    using exact_unsigned_type = std::uintmax_t;
  };

  template<const size_t BitCount> struct uint_type_helper<BitCount, typename std::enable_if<                     (BitCount <=   8U)>::type> { using exact_unsigned_type = std::uint8_t;  };
  template<const size_t BitCount> struct uint_type_helper<BitCount, typename std::enable_if<(BitCount >=  9U) && (BitCount <=  16U)>::type> { using exact_unsigned_type = std::uint16_t; };
  template<const size_t BitCount> struct uint_type_helper<BitCount, typename std::enable_if<(BitCount >= 17U) && (BitCount <=  32U)>::type> { using exact_unsigned_type = std::uint32_t; };
  template<const size_t BitCount> struct uint_type_helper<BitCount, typename std::enable_if<(BitCount >= 33U) && (BitCount <=  64U)>::type> { using exact_unsigned_type = std::uint64_t; };
  #if defined(WIDE_INTEGER_HAS_LIMB_TYPE_UINT64)
  template<const size_t BitCount> struct uint_type_helper<BitCount, typename std::enable_if<(BitCount >= 65U) && (BitCount <= 128U)>::type> { using exact_unsigned_type = unsigned __int128; };
  #endif

  template<typename UnsignedIntegralType>
  inline WIDE_INTEGER_CONSTEXPR std::uint_fast32_t lsb_helper(const UnsignedIntegralType& x);

  template<typename UnsignedIntegralType>
  inline WIDE_INTEGER_CONSTEXPR std::uint_fast32_t msb_helper(const UnsignedIntegralType& x);

  template<>
  inline WIDE_INTEGER_CONSTEXPR std::uint_fast32_t msb_helper<std::uint32_t>(const std::uint32_t& x);

  template<>
  inline WIDE_INTEGER_CONSTEXPR std::uint_fast32_t msb_helper<std::uint16_t>(const std::uint16_t& x);

  template<>
  inline WIDE_INTEGER_CONSTEXPR std::uint_fast32_t msb_helper<std::uint8_t>(const std::uint8_t& x);

  // Use a local implementation of string copy.
  inline WIDE_INTEGER_CONSTEXPR char* strcpy_unsafe(char* dst, const char* src)
  {
    while((*dst++ = *src++) != char('\0')) { ; }

    return dst;
  }

  // Use a local implementation of string length.
  inline WIDE_INTEGER_CONSTEXPR std::uint_fast32_t strlen_unsafe(const char* p_str)
  {
    const char* p_str_copy{};

    for(p_str_copy = p_str; (*p_str_copy != char('\0')); ++p_str_copy) { ; }

    return std::uint_fast32_t(p_str_copy - p_str);
  }

  template<typename UnsignedShortType,
           typename UnsignedLargeType = typename detail::uint_type_helper<std::uint32_t(std::numeric_limits<UnsignedShortType>::digits * 2)>::exact_unsigned_type>
  constexpr UnsignedShortType make_lo(const UnsignedLargeType& u)
  {
    // From an unsigned integral input parameter of type UnsignedLargeType,
    // extract the low part of it. The type of the extracted
    // low part is UnsignedShortType, which has half the width of UnsignedLargeType.

    using local_ushort_type = UnsignedShortType;
    using local_ularge_type = UnsignedLargeType;

    // Compile-time checks.
    #if defined(WIDE_INTEGER_HAS_LIMB_TYPE_UINT64)
    static_assert(((sizeof(local_ushort_type) * 2U) == sizeof(local_ularge_type)),
                   "Error: Please check the characteristics of the template parameters UnsignedShortType and UnsignedLargeType");
    #else
    static_assert((    (std::numeric_limits<local_ushort_type>::is_integer == true)
                   &&  (std::numeric_limits<local_ularge_type>::is_integer == true)
                   &&  (std::numeric_limits<local_ushort_type>::is_signed  == false)
                   &&  (std::numeric_limits<local_ularge_type>::is_signed  == false)
                   &&  ((sizeof(local_ushort_type) * 2U)                   == sizeof(local_ularge_type))),
                   "Error: Please check the characteristics of the template parameters UnsignedShortType and UnsignedLargeType");
    #endif

    return static_cast<local_ushort_type>(u);
  }

  template<typename UnsignedShortType,
           typename UnsignedLargeType = typename detail::uint_type_helper<std::uint32_t(std::numeric_limits<UnsignedShortType>::digits * 2)>::exact_unsigned_type>
  constexpr UnsignedShortType make_hi(const UnsignedLargeType& u)
  {
    // From an unsigned integral input parameter of type UnsignedLargeType,
    // extract the high part of it. The type of the extracted
    // high part is UnsignedShortType, which has half the width of UnsignedLargeType.

    using local_ushort_type = UnsignedShortType;
    using local_ularge_type = UnsignedLargeType;

    // Compile-time checks.
    #if defined(WIDE_INTEGER_HAS_LIMB_TYPE_UINT64)
    static_assert(((sizeof(local_ushort_type) * 2U) == sizeof(local_ularge_type)),
                   "Error: Please check the characteristics of the template parameters UnsignedShortType and UnsignedLargeType");
    #else
    static_assert((    (std::numeric_limits<local_ushort_type>::is_integer == true)
                   &&  (std::numeric_limits<local_ularge_type>::is_integer == true)
                   &&  (std::numeric_limits<local_ushort_type>::is_signed  == false)
                   &&  (std::numeric_limits<local_ularge_type>::is_signed  == false)
                   &&  ((sizeof(local_ushort_type) * 2U)                   == sizeof(local_ularge_type))),
                   "Error: Please check the characteristics of the template parameters UnsignedShortType and UnsignedLargeType");
    #endif

    return static_cast<local_ushort_type>(u >> std::numeric_limits<local_ushort_type>::digits);
  }

  template<typename UnsignedShortType,
           typename UnsignedLargeType = typename detail::uint_type_helper<std::uint32_t(std::numeric_limits<UnsignedShortType>::digits * 2)>::exact_unsigned_type>
  constexpr UnsignedLargeType make_large(const UnsignedShortType& lo, const UnsignedShortType& hi)
  {
    // Create a composite unsigned integral value having type UnsignedLargeType.
    // Two constituents are used having type UnsignedShortType, whereby the
    // width of UnsignedShortType is half the width of UnsignedLargeType.

    using local_ushort_type = UnsignedShortType;
    using local_ularge_type = UnsignedLargeType;

    // Compile-time checks.
    #if defined(WIDE_INTEGER_HAS_LIMB_TYPE_UINT64)
    static_assert(((sizeof(local_ushort_type) * 2U) == sizeof(local_ularge_type)),
                   "Error: Please check the characteristics of the template parameters UnsignedShortType and UnsignedLargeType");
    #else
    static_assert((    (std::numeric_limits<local_ushort_type>::is_integer == true)
                   &&  (std::numeric_limits<local_ularge_type>::is_integer == true)
                   &&  (std::numeric_limits<local_ushort_type>::is_signed  == false)
                   &&  (std::numeric_limits<local_ularge_type>::is_signed  == false)
                   &&  ((sizeof(local_ushort_type) * 2U)                   == sizeof(local_ularge_type))),
                   "Error: Please check the characteristics of the template parameters UnsignedShortType and UnsignedLargeType");
    #endif

    return local_ularge_type(local_ularge_type(static_cast<local_ularge_type>(hi) << std::numeric_limits<UnsignedShortType>::digits) | lo);
  }

  struct uint64_extra { uint64_t extra, v; };

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

  #if !defined(WIDE_INTEGER_DISABLE_FLOAT_INTEROP)
  template<typename FloatingPointType>
  class native_float_parts final
  {
  public:
    // Emphasize: This template class can be used with native floating-point
    // types like float, double and long double. Note: For long double,
    // you need to verify that the mantissa fits in unsigned long long.
    WIDE_INTEGER_CONSTEXPR native_float_parts(const FloatingPointType f)
      : my_mantissa_part(0ULL),
        my_exponent_part(0)
    {
      using native_float_type = FloatingPointType;

      static_assert(std::numeric_limits<native_float_type>::digits <= std::numeric_limits<unsigned long long>::digits,
                    "Error: The width of the mantissa does not fit in unsigned long long");

      const native_float_type ff = ((f < static_cast<native_float_type>(0)) ? -f : f);

      if(ff < (std::numeric_limits<native_float_type>::min)())
      {
        return;
      }

      using std::frexp;

      // Get the fraction and base-2 exponent.
      native_float_type man = (native_float_type) frexp(f, &my_exponent_part);

      unsigned n2 = 0U;

      for(std::uint_fast16_t i = static_cast<std::uint_fast16_t>(0U); i < static_cast<std::uint_fast16_t>(std::numeric_limits<native_float_type>::digits); ++i)
      {
        // Extract the mantissa of the floating-point type in base-2
        // (one bit at a time) and store it in an unsigned long long.
        man *= 2;

        n2   = static_cast<unsigned>(man);
        man -= static_cast<native_float_type>(n2);

        if(n2 != static_cast<unsigned>(0U))
        {
          my_mantissa_part |= 1U;
        }

        if(i < static_cast<unsigned>(std::numeric_limits<native_float_type>::digits - 1))
        {
          my_mantissa_part <<= 1U;
        }
      }

      // Ensure that the value is normalized and adjust the exponent.
      my_mantissa_part |= static_cast<unsigned long long>(1ULL << (std::numeric_limits<native_float_type>::digits - 1));
      my_exponent_part -= 1;
    }

    WIDE_INTEGER_CONSTEXPR unsigned long long get_mantissa() const { return my_mantissa_part; }
    WIDE_INTEGER_CONSTEXPR int                get_exponent() const { return my_exponent_part; }

  private:
    WIDE_INTEGER_CONSTEXPR native_float_parts() = delete;
    WIDE_INTEGER_CONSTEXPR native_float_parts(const native_float_parts&) = delete;

    WIDE_INTEGER_CONSTEXPR const native_float_parts& operator=(const native_float_parts&) = delete;

    unsigned long long my_mantissa_part;
    int                my_exponent_part;
  };
  #endif

  } } } // namespace math::wide_integer::detail

  namespace math { namespace wide_integer {

  template<const size_t Width2,
           typename LimbType,
           typename AllocatorType,
           const bool IsSigned>
  class uintwide_t
  {
  public:
    template<const size_t OtherWidth2,
             typename OtherLimbType,
             typename OtherAllocatorType,
             const bool OtherIsSigned>
    friend class uintwide_t;

    // Class-local type definitions.
    using limb_type = LimbType;

    using double_limb_type =
      typename detail::uint_type_helper<std::uint32_t(std::numeric_limits<limb_type>::digits * 2)>::exact_unsigned_type;

    // Legacy ularge and ushort types. These are no longer used
    // in the class, but provided for legacy compatibility.
    using ushort_type = limb_type;
    using ularge_type = double_limb_type;

    // More compile-time checks.
    #if defined(WIDE_INTEGER_HAS_LIMB_TYPE_UINT64)
    static_assert(((sizeof(limb_type) * 2U) == sizeof(double_limb_type)),
                   "Error: Please check the characteristics of the template parameters UnsignedShortType and UnsignedLargeType");
    #else
    static_assert((    (std::numeric_limits<limb_type>::is_integer        == true)
                   &&  (std::numeric_limits<double_limb_type>::is_integer == true)
                   &&  (std::numeric_limits<limb_type>::is_signed         == false)
                   &&  (std::numeric_limits<double_limb_type>::is_signed  == false)
                   &&  ((sizeof(limb_type) * 2U)                          == sizeof(double_limb_type))),
                   "Error: Please check the characteristics of the template parameters UnsignedShortType and UnsignedLargeType");
    #endif

    // Helper constants for the digit characteristics.
    static constexpr size_t my_width2 = Width2;

    // The number of limbs.
    static constexpr size_t number_of_limbs =
      size_t(my_width2 / size_t(std::numeric_limits<limb_type>::digits));

    static constexpr size_t number_of_limbs_karatsuba_threshold = size_t(128U + 1U);

    // Verify that the Width2 template parameter (mirrored with my_width2):
    //   * Is equal to 2^n times 1...63.
    //   * And that there are at least 16, 24 or 32 binary digits, or more.
    //   * And that the number of binary digits is an exact multiple of the number of limbs.
    static_assert(   (detail::verify_power_of_two_times_granularity_one_sixty_fourth<my_width2>::conditional_value == true)
                  && ((my_width2 >= 16U) || (my_width2 >= 24U) || (my_width2 >= 32U))
                  && (my_width2 == (number_of_limbs * size_t(std::numeric_limits<limb_type>::digits))),
                  "Error: Width2 must be 2^n times 1...63 (with n >= 3), while being 16, 24, 32 or larger, and exactly divisible by limb count");

    // The type of the internal data representation.
    using representation_type =
      typename std::conditional
        <std::is_same<AllocatorType, void>::value,
         detail::fixed_static_array <limb_type,
                                     number_of_limbs>,
         detail::fixed_dynamic_array<limb_type,
                                     number_of_limbs,
                                     typename std::allocator_traits<typename std::conditional<std::is_same<AllocatorType, void>::value,
                                                                                              std::allocator<void>,
                                                                                              AllocatorType>::type>::template rebind_alloc<limb_type>>
      >::type;

    // The iterator types of the internal data representation.
    using iterator               = typename representation_type::iterator;
    using const_iterator         = typename representation_type::const_iterator;
    using reverse_iterator       = typename representation_type::reverse_iterator;
    using const_reverse_iterator = typename representation_type::const_reverse_iterator;

    // Define a class-local type that has double the width of *this.
    using double_width_type = uintwide_t<my_width2 * 2U, limb_type>;

    // Default constructor.
    constexpr uintwide_t() { }

    // Constructors from built-in unsigned integral types that
    // are less wide than limb_type or exactly as wide as limb_type.
    template<typename UnsignedIntegralType>
    constexpr uintwide_t(const UnsignedIntegralType v,
                         typename std::enable_if<(   (std::is_fundamental<UnsignedIntegralType>::value == true)
                                                  && (std::is_integral   <UnsignedIntegralType>::value == true)
                                                  && (std::is_unsigned   <UnsignedIntegralType>::value == true)
                                                  && (std::numeric_limits<UnsignedIntegralType>::digits <= std::numeric_limits<limb_type>::digits))>::type* = nullptr)
      : values(1U, v) { }

    // Constructors from built-in unsigned integral types that
    // are wider than limb_type, and do not have exactly the
    // same width as limb_type.
    template<typename UnsignedIntegralType>
    WIDE_INTEGER_CONSTEXPR uintwide_t(const UnsignedIntegralType v,
               typename std::enable_if<(   (std::is_fundamental<UnsignedIntegralType>::value == true)
                                        && (std::is_integral   <UnsignedIntegralType>::value == true)
                                        && (std::is_unsigned   <UnsignedIntegralType>::value == true)
                                        && (std::numeric_limits<UnsignedIntegralType>::digits > std::numeric_limits<limb_type>::digits))>::type* = nullptr)
    {
      std::uint_fast32_t right_shift_amount_v = 0U;
      std::uint_fast8_t  index_u              = 0U;

      for( ; (   (index_u < values.size())
              && (right_shift_amount_v < std::uint_fast32_t(std::numeric_limits<UnsignedIntegralType>::digits)));
             ++index_u)
      {
        values[index_u] = limb_type(v >> (int) right_shift_amount_v);

        right_shift_amount_v += std::uint_fast32_t(std::numeric_limits<limb_type>::digits);
      }

      std::fill(values.begin() + index_u, values.end(), limb_type(0U));
    }

    // Constructors from built-in signed integral types.
    template<typename SignedIntegralType>
    WIDE_INTEGER_CONSTEXPR uintwide_t(const SignedIntegralType v,
                                       typename std::enable_if<(   (std::is_fundamental<SignedIntegralType>::value == true)
                                                                && (std::is_integral   <SignedIntegralType>::value == true)
                                                                && (std::is_signed     <SignedIntegralType>::value == true))>::type* = nullptr)
    {
      using local_signed_integral_type   = SignedIntegralType;
      using local_unsigned_integral_type =
        typename detail::uint_type_helper<std::uint32_t(std::numeric_limits<local_signed_integral_type>::digits + 1)>::exact_unsigned_type;

      const bool v_is_neg = (v < local_signed_integral_type(0));

      const local_unsigned_integral_type u =
        ((v_is_neg == false) ? local_unsigned_integral_type(v) : local_unsigned_integral_type(-v));

      operator=(uintwide_t(u));

      if(v_is_neg) { negate(); }
    }

    #if !defined(WIDE_INTEGER_DISABLE_FLOAT_INTEROP)
    template<typename FloatingPointType,
             typename std::enable_if<std::is_floating_point<FloatingPointType>::value == true>::type const* = nullptr>
    WIDE_INTEGER_CONSTEXPR uintwide_t(const FloatingPointType f)
    {
      using std::isfinite;

      using local_builtin_float_type = FloatingPointType;

      const bool f_is_finite = isfinite(f);

      if(f_is_finite == false)
      {
      }
      else
      {
        const bool f_is_neg = (f < local_builtin_float_type(0.0F));

        const local_builtin_float_type a = ((f_is_neg == false) ? f : -f);

        const bool a_is_zero = (a < local_builtin_float_type(1.0F));

        if(a_is_zero == false)
        {
          const detail::native_float_parts<local_builtin_float_type> ld_parts(a);

          // Create a decwide_t from the fractional part of the
          // mantissa expressed as an unsigned long long.
          *this = uintwide_t(ld_parts.get_mantissa());

          // Scale the unsigned long long representation to the fractional
          // part of the long double and multiply with the base-2 exponent.
          const int p2 = ld_parts.get_exponent() - (std::numeric_limits<FloatingPointType>::digits - 1);

          if     (p2 <   0) { *this >>= (unsigned) -p2; }
          else if(p2 ==  0) { ; }
          else              { *this <<= (unsigned) p2; }

          if(f_is_neg)
          {
            negate();
          }
        }
        else
        {
          operator=(0U);
        }
      }
    }
    #endif

    // Copy constructor.
    constexpr uintwide_t(const uintwide_t& other) : values(other.values) { }

    // Copy-like constructor from the other signed-ness type.
    template<const bool OtherIsSigned,
             typename std::enable_if<(OtherIsSigned != IsSigned)>::type const* = nullptr>
    constexpr uintwide_t(const uintwide_t<Width2, LimbType, AllocatorType, OtherIsSigned>& other)
      : values(other.values) { }

    // Constructor from the another type having a different width but the same limb type.
    // This constructor is explicit because it is a non-trivial conversion.
    template<const size_t OtherWidth2>
    WIDE_INTEGER_CONSTEXPR uintwide_t(const uintwide_t<OtherWidth2, LimbType, AllocatorType, IsSigned>& v)
    {
      const std::uint_fast32_t sz =
        (std::min)(std::uint_fast32_t(v.crepresentation().size()),
                   std::uint_fast32_t(number_of_limbs));

      std::copy(v.crepresentation().cbegin(),
                v.crepresentation().cbegin() + sz,
                values.begin());

      std::fill(values.begin() + sz, values.end(), limb_type(0U));
    }

    // Constructor from a constant character string.
    WIDE_INTEGER_CONSTEXPR uintwide_t(const char* str_input)
    {
      if(rd_string(str_input) == false)
      {
        std::fill(values.begin(), values.end(), (std::numeric_limits<limb_type>::max)());
      }
    }

    // Move constructor.
    constexpr uintwide_t(uintwide_t&& other) : values(static_cast<representation_type&&>(other.values)) { }

    // Move-like constructor from the other signed-ness type.
    template<const bool OtherIsSigned,
             typename std::enable_if<(OtherIsSigned != IsSigned)>::type const* = nullptr>
    constexpr uintwide_t(uintwide_t<Width2, LimbType, AllocatorType, OtherIsSigned>&& other)
      : values(static_cast<representation_type&&>(other.values)) { }

    // Assignment operator.
    WIDE_INTEGER_CONSTEXPR uintwide_t& operator=(const uintwide_t& other)
    {
      if(this != &other)
      {
        values = other.values;
      }

      return *this;
    }

    // Assignment operator from the other signed-ness type.
    template<const bool OtherIsSigned,
             typename std::enable_if<(OtherIsSigned != IsSigned)>::type const* = nullptr>
    WIDE_INTEGER_CONSTEXPR uintwide_t& operator=(const uintwide_t<Width2, LimbType, AllocatorType, OtherIsSigned>& other)
    {
      values = other.values;

      return *this;
    }

    // Trivial move assignment operator.
    WIDE_INTEGER_CONSTEXPR uintwide_t& operator=(uintwide_t&& other)
    {
      values = static_cast<representation_type&&>(other.values);

      return *this;
    }

    // Trivial move assignment operator from the other signed-ness type.
    template<const bool OtherIsSigned,
             typename std::enable_if<(OtherIsSigned != IsSigned)>::type const* = nullptr>
    WIDE_INTEGER_CONSTEXPR uintwide_t& operator=(uintwide_t<Width2, LimbType, AllocatorType, OtherIsSigned>&& other)
    {
      values = static_cast<representation_type&&>(other.values);

      return *this;
    }

    #if !defined(WIDE_INTEGER_DISABLE_FLOAT_INTEROP)
    explicit WIDE_INTEGER_CONSTEXPR operator long double       () const { return extract_builtin_floating_point_type<long double>(); }
    explicit WIDE_INTEGER_CONSTEXPR operator double            () const { return extract_builtin_floating_point_type<double>     (); }
    explicit WIDE_INTEGER_CONSTEXPR operator float             () const { return extract_builtin_floating_point_type<float>      (); }
    #endif

    explicit WIDE_INTEGER_CONSTEXPR operator signed char       () const { return extract_builtin_integral_type<signed char>       (); }
    explicit WIDE_INTEGER_CONSTEXPR operator unsigned char     () const { return extract_builtin_integral_type<unsigned char>     (); }
    explicit WIDE_INTEGER_CONSTEXPR operator signed short      () const { return extract_builtin_integral_type<signed short>      (); }
    explicit WIDE_INTEGER_CONSTEXPR operator unsigned short    () const { return extract_builtin_integral_type<unsigned short>    (); }
    explicit WIDE_INTEGER_CONSTEXPR operator signed int        () const { return extract_builtin_integral_type<signed int>        (); }
    explicit WIDE_INTEGER_CONSTEXPR operator unsigned int      () const { return extract_builtin_integral_type<unsigned int>      (); }
    explicit WIDE_INTEGER_CONSTEXPR operator signed long       () const { return extract_builtin_integral_type<signed long >      (); }
    explicit WIDE_INTEGER_CONSTEXPR operator unsigned long     () const { return extract_builtin_integral_type<unsigned long>     (); }
    explicit WIDE_INTEGER_CONSTEXPR operator signed long long  () const { return extract_builtin_integral_type<signed long long>  (); }
    explicit WIDE_INTEGER_CONSTEXPR operator unsigned long long() const { return extract_builtin_integral_type<unsigned long long>(); }


    // Implement the cast operator that casts to the double-width type.
    template<typename UnknownUnsignedWideIntegralType,
             typename = typename std::enable_if<(std::is_same<UnknownUnsignedWideIntegralType, double_width_type>::value == true)>::type>
    WIDE_INTEGER_CONSTEXPR operator double_width_type() const
    {
      double_width_type local_double_width_instance;

      std::copy(values.cbegin(),
                values.cend(),
                local_double_width_instance.representation().begin());

      std::fill(local_double_width_instance.representation().begin() + number_of_limbs,
                local_double_width_instance.representation().end(),
                limb_type(0U));

      return local_double_width_instance;
    }

    // Implement a cast operator that casts to a uintwide_t having the other signed-ness type.
    template<const bool OtherIsSigned,
             typename std::enable_if<(OtherIsSigned != IsSigned)>::type const* = nullptr>
    explicit WIDE_INTEGER_CONSTEXPR operator uintwide_t<Width2, LimbType, AllocatorType, OtherIsSigned>() const
    {
      return uintwide_t<Width2, LimbType, AllocatorType, OtherIsSigned>(values);
    }

    // Provide a user interface to the internal data representation.
    WIDE_INTEGER_CONSTEXPR       representation_type&  representation()       { return values; }
    WIDE_INTEGER_CONSTEXPR const representation_type&  representation() const { return values; }
    WIDE_INTEGER_CONSTEXPR const representation_type& crepresentation() const { return values; }

    // Unary operators: not, plus and minus.
    WIDE_INTEGER_CONSTEXPR const uintwide_t& operator+() const { return *this; }
    WIDE_INTEGER_CONSTEXPR       uintwide_t  operator-() const { uintwide_t tmp(*this); tmp.negate(); return tmp; }

    WIDE_INTEGER_CONSTEXPR uintwide_t& operator+=(const uintwide_t& other)
    {
      if(this == &other)
      {
        operator+=(uintwide_t(other));
      }
      else
      {
        // Unary addition function.
        const limb_type carry = eval_add_n(values.data(),
                                           values.data(),
                                           other.values.data(),
                                           number_of_limbs,
                                           limb_type(0U));

        static_cast<void>(carry);
      }

      return *this;
    }

    WIDE_INTEGER_CONSTEXPR uintwide_t& operator-=(const uintwide_t& other)
    {
      if(this == &other)
      {
        values.fill(0U);
      }
      else
      {
        // Unary subtraction function.
        const limb_type has_borrow = eval_subtract_n(values.data(),
                                                     values.data(),
                                                     other.values.data(),
                                                     number_of_limbs,
                                                     false);

        static_cast<void>(has_borrow);
      }

      return *this;
    }

    WIDE_INTEGER_CONSTEXPR uintwide_t& operator*=(const uintwide_t& other)
    {
      if(this == &other)
      {
        operator*=(uintwide_t(other));
      }
      else
      {
        eval_mul_unary(*this, other);
      }

      return *this;
    }

    WIDE_INTEGER_CONSTEXPR uintwide_t& mul_by_limb(const limb_type v)
    {
      if(v == 0U)
      {
        values.fill(0U);
      }
      else if(v > 1U)
      {
        static_cast<void>(eval_multiply_1d(values.data(),
                                           values.data(),
                                           v,
                                           number_of_limbs));
      }

      return *this;
    }

    WIDE_INTEGER_CONSTEXPR uintwide_t& operator/=(const uintwide_t& other)
    {
      if(this == &other)
      {
        values.front() = 1U;

        std::fill(values.begin() + 1U, values.end(), limb_type(0U));
      }
      else if(other.is_zero())
      {
        values.fill((std::numeric_limits<limb_type>::max)());
      }
      else
      {
        // Unary division function.
        const bool denom_was_neg = is_neg(other);

        eval_divide_knuth(denom_was_neg == false ? other : -other, nullptr, denom_was_neg);
      }

      return *this;
    }

    WIDE_INTEGER_CONSTEXPR uintwide_t& operator%=(const uintwide_t& other)
    {
      if(this == &other)
      {
        std::fill(values.begin(), values.end(), limb_type(0U));
      }
      else
      {
        // Unary modulus function.
        uintwide_t remainder;

        const bool denom_was_neg = is_neg(other);

        eval_divide_knuth(denom_was_neg == false ? other : -other, &remainder, denom_was_neg);

        values = remainder.values;
      }

      return *this;
    }

    // Operators pre-increment and pre-decrement.
    WIDE_INTEGER_CONSTEXPR uintwide_t& operator++() { preincrement(); return *this; }
    WIDE_INTEGER_CONSTEXPR uintwide_t& operator--() { predecrement(); return *this; }

    // Operators post-increment and post-decrement.
    WIDE_INTEGER_CONSTEXPR uintwide_t operator++(int) { const uintwide_t w(*this); preincrement(); return w; }
    WIDE_INTEGER_CONSTEXPR uintwide_t operator--(int) { const uintwide_t w(*this); predecrement(); return w; }

    WIDE_INTEGER_CONSTEXPR uintwide_t& operator~()
    {
      // Bitwise NOT.
      bitwise_not();

      return *this;
    }

    WIDE_INTEGER_CONSTEXPR uintwide_t& operator|=(const uintwide_t& other)
    {
      if(this != &other)
      {
        // Bitwise OR.
        for(std::uint_fast32_t i = 0U; i < number_of_limbs; ++i)
        {
          values[i] = limb_type(values[i] | other.values[i]);
        }
      }

      return *this;
    }

    WIDE_INTEGER_CONSTEXPR uintwide_t& operator^=(const uintwide_t& other)
    {
      if(this == &other)
      {
        values.fill(0U);
      }
      else
      {
        // Bitwise XOR.
        for(std::uint_fast32_t i = 0U; i < number_of_limbs; ++i)
        {
          values[i] = limb_type(values[i] ^ other.values[i]);
        }
      }

      return *this;
    }

    WIDE_INTEGER_CONSTEXPR uintwide_t& operator&=(const uintwide_t& other)
    {
      if(this != &other)
      {
        // Bitwise AND.
        for(std::uint_fast32_t i = 0U; i < number_of_limbs; ++i)
        {
          values[i] = limb_type(values[i] & other.values[i]);
        }
      }

      return *this;
    }

    template<typename SignedIntegralType>
    WIDE_INTEGER_CONSTEXPR typename std::enable_if<(   (std::is_fundamental<SignedIntegralType>::value == true)
                                                    && (std::is_integral   <SignedIntegralType>::value == true)
                                                    && (std::is_signed     <SignedIntegralType>::value == true)), uintwide_t>::type&
    operator<<=(const SignedIntegralType n)
    {
      // Left-shift operator.
      if(n <  0)
      {
        operator>>=(-n);
      }
      else if(n == 0)
      {
        ;
      }
      else if(std::uint_fast32_t(n) >= my_width2)
      {
        std::fill(values.begin(), values.end(), limb_type(0U));
      }
      else
      {
        const std::uint_fast32_t offset            =                    std::uint_fast32_t(n) / std::uint_fast32_t(std::numeric_limits<limb_type>::digits);
        const std::uint_fast16_t left_shift_amount = std::uint_fast16_t(std::uint_fast32_t(n) % std::uint_fast32_t(std::numeric_limits<limb_type>::digits));

        shl(offset, left_shift_amount);
      }

      return *this;
    }

    template<typename UnsignedIntegralType>
    WIDE_INTEGER_CONSTEXPR typename std::enable_if<(   (std::is_fundamental<UnsignedIntegralType>::value == true)
                                                    && (std::is_integral   <UnsignedIntegralType>::value == true)
                                                    && (std::is_signed     <UnsignedIntegralType>::value == false)), uintwide_t>::type&
    operator<<=(const UnsignedIntegralType n)
    {
      // Left-shift operator.
      if(n == 0)
      {
        ;
      }
      else if(std::uint_fast32_t(n) >= my_width2)
      {
        std::fill(values.begin(), values.end(), limb_type(0U));
      }
      else
      {
        const std::uint_fast32_t offset            =                    std::uint_fast32_t(n) / std::uint_fast32_t(std::numeric_limits<limb_type>::digits);
        const std::uint_fast16_t left_shift_amount = std::uint_fast16_t(std::uint_fast32_t(n) % std::uint_fast32_t(std::numeric_limits<limb_type>::digits));

        shl(offset, left_shift_amount);
      }

      return *this;
    }

    template<typename SignedIntegralType>
    WIDE_INTEGER_CONSTEXPR typename std::enable_if<(   (std::is_fundamental<SignedIntegralType>::value == true)
                                                    && (std::is_integral   <SignedIntegralType>::value == true)
                                                    && (std::is_signed     <SignedIntegralType>::value == true)), uintwide_t>::type&
    operator>>=(const SignedIntegralType n)
    {
      // Right-shift operator.
      if(n <  0)
      {
        operator<<=(-n);
      }
      else if(n == 0)
      {
        ;
      }
      else if(std::uint_fast32_t(n) >= my_width2)
      {
        // Fill with either 0's or 1's. Note also the implementation-defined
        // behavior of excessive right-shift of negative value.
        if(is_neg(*this) == false)
        {
          std::fill(values.begin(), values.end(), limb_type(0U));
        }
        else
        {
          std::fill(values.begin(), values.end(), (std::numeric_limits<limb_type>::max)());
        }
      }
      else
      {
        const std::uint_fast32_t offset             =                    std::uint_fast32_t(n) / std::uint_fast32_t(std::numeric_limits<limb_type>::digits);
        const std::uint_fast16_t right_shift_amount = std::uint_fast16_t(std::uint_fast32_t(n) % std::uint_fast32_t(std::numeric_limits<limb_type>::digits));

        shr(offset, right_shift_amount);
      }

      return *this;
    }

    template<typename UnsignedIntegralType>
    WIDE_INTEGER_CONSTEXPR typename std::enable_if<(   (std::is_fundamental<UnsignedIntegralType>::value == true)
                                                    && (std::is_integral   <UnsignedIntegralType>::value == true)
                                                    && (std::is_signed     <UnsignedIntegralType>::value == false)), uintwide_t>::type&
    operator>>=(const UnsignedIntegralType n)
    {
      // Right-shift operator.
      if(n == 0)
      {
        ;
      }
      else if(std::uint_fast32_t(n) >= my_width2)
      {
        std::fill(values.begin(), values.end(), limb_type(0U));
      }
      else
      {
        const std::uint_fast32_t offset             =                    std::uint_fast32_t(n) / std::uint_fast32_t(std::numeric_limits<limb_type>::digits);
        const std::uint_fast16_t right_shift_amount = std::uint_fast16_t(std::uint_fast32_t(n) % std::uint_fast32_t(std::numeric_limits<limb_type>::digits));

        shr(offset, right_shift_amount);
      }

      return *this;
    }

    // Implement comparison operators.
    constexpr bool operator==(const uintwide_t& other) const { return (compare(other) == std::int_fast8_t( 0)); }
    constexpr bool operator< (const uintwide_t& other) const { return (compare(other) == std::int_fast8_t(-1)); }
    constexpr bool operator> (const uintwide_t& other) const { return (compare(other) == std::int_fast8_t( 1)); }
    constexpr bool operator!=(const uintwide_t& other) const { return (compare(other) != std::int_fast8_t( 0)); }
    constexpr bool operator<=(const uintwide_t& other) const { return (compare(other) <= std::int_fast8_t( 0)); }
    constexpr bool operator>=(const uintwide_t& other) const { return (compare(other) >= std::int_fast8_t( 0)); }

    // Helper functions for supporting std::numeric_limits<>.
    static WIDE_INTEGER_CONSTEXPR uintwide_t limits_helper_max(bool is_signed)
    {
      return
      is_signed == false
        ? from_rep
          (
            representation_type
            (
              number_of_limbs, (std::numeric_limits<limb_type>::max)()
            )
          )
        : from_rep
          (
            representation_type
            (
              number_of_limbs, (std::numeric_limits<limb_type>::max)()
            )
          ) ^ (uintwide_t(1U) << (my_width2 - 1))
        ;
    }

    static WIDE_INTEGER_CONSTEXPR uintwide_t limits_helper_min(bool is_signed)
    {
      return
      is_signed == false
        ? from_rep
          (
            representation_type
            (
              number_of_limbs, limb_type(0U)
            )
          )
        : from_rep
          (
            representation_type
            (
              number_of_limbs, limb_type(0U)
            )
          ) | (uintwide_t(1U) << (my_width2 - 1))
        ;
    }

    static constexpr uintwide_t limits_helper_min()
    {
      return uintwide_t(representation_type(number_of_limbs, limb_type(0U)));
    }

    // Define the maximum buffer sizes for extracting
    // octal, decimal and hexadecimal string representations.
    static constexpr size_t wr_string_max_buffer_size_oct = (16U + (my_width2 / 3U)) + size_t(((my_width2 % 3U) != 0U) ? 1U : 0U) + 1U;
    static constexpr size_t wr_string_max_buffer_size_hex = (32U + (my_width2 / 4U)) + 1U;
    static constexpr size_t wr_string_max_buffer_size_dec = (20U + size_t((std::uintmax_t(my_width2) * UINTMAX_C(301)) / UINTMAX_C(1000))) + 1U;

    // Write string function.
    bool wr_string(      char*              str_result,
                   const std::uint_fast8_t  base_rep     = 0x10U,
                   const bool               show_base    = true,
                   const bool               show_pos     = false,
                   const bool               is_uppercase = true,
                         std::uint_fast32_t field_width  = 0U,
                   const char               fill_char    = char('0')) const
    {
      bool wr_string_is_ok = true;

      if(base_rep == 8U)
      {
        uintwide_t t(*this);

        const limb_type mask(std::uint8_t(0x7U));

        char str_temp[wr_string_max_buffer_size_oct];

        std::uint_fast32_t pos = (sizeof(str_temp) - 1U);

        if(t.is_zero())
        {
          --pos;

          str_temp[pos] = char('0');
        }
        else
        {
          if(is_neg(t) == false)
          {
            while(t.is_zero() == false)
            {
              char c = char(t.values[0U] & mask);

              if(c <= 8) { c += char(0x30); }

              --pos;

              str_temp[pos] = c;

              t >>= 3;
            }
          }
          else
          {
            uintwide_t<my_width2, limb_type, AllocatorType, false> tu(t);

            while(tu.is_zero() == false)
            {
              char c = char(tu.values[0U] & mask);

              if(c <= 8) { c += char(0x30); }

              --pos;

              str_temp[pos] = c;

              tu >>= 3;
            }
          }
        }

        if(show_base)
        {
          --pos;

          str_temp[pos] = char('0');
        }

        if(show_pos)
        {
          --pos;

          str_temp[pos] = char('+');
        }

        if(field_width != 0U)
        {
          field_width = (std::min)(field_width, std::uint_fast32_t(sizeof(str_temp) - 1U));

          while(std::int_fast32_t(pos) > std::int_fast32_t((sizeof(str_temp) - 1U) - field_width))
          {
            --pos;

            str_temp[pos] = fill_char;
          }
        }

        str_temp[(sizeof(str_temp) - 1U)] = char('\0');

        detail::strcpy_unsafe(str_result, str_temp + pos);
      }
      else if(base_rep == 10U)
      {
        uintwide_t t(*this);

        const bool str_has_neg_sign = is_neg(t);

        if(str_has_neg_sign)
        {
          t.negate();
        }

        char str_temp[wr_string_max_buffer_size_dec];

        std::uint_fast32_t pos = (sizeof(str_temp) - 1U);

        if(t.is_zero() == true)
        {
          --pos;

          str_temp[pos] = char('0');
        }
        else
        {
          while(t.is_zero() == false)
          {
            const uintwide_t tmp(t);

            t.eval_divide_by_single_limb(limb_type(10U), 0U, nullptr);

            --pos;

            str_temp[pos] = (char) ((limb_type) (tmp - (uintwide_t(t).mul_by_limb(10U))) + 0x30U);
          }
        }

        if(show_pos && (!str_has_neg_sign))
        {
          --pos;

          str_temp[pos] = char('+');
        }
        else if(str_has_neg_sign)
        {
          --pos;

          str_temp[pos] = char('-');
        }

        if(field_width != 0U)
        {
          field_width = (std::min)(field_width, std::uint_fast32_t(sizeof(str_temp) - 1U));

          while(std::int_fast32_t(pos) > std::int_fast32_t((sizeof(str_temp) - 1U) - field_width))
          {
            --pos;

            str_temp[pos] = fill_char;
          }
        }

        str_temp[(sizeof(str_temp) - 1U)] = char('\0');

        detail::strcpy_unsafe(str_result, str_temp + pos);
      }
      else if(base_rep == 16U)
      {
        uintwide_t t(*this);

        const limb_type mask(std::uint8_t(0xFU));

        char str_temp[wr_string_max_buffer_size_hex];

        std::uint_fast32_t pos = (sizeof(str_temp) - 1U);

        if(t.is_zero() == true)
        {
          --pos;

          str_temp[pos] = char('0');
        }
        else
        {
          if(is_neg(t) == false)
          {
            while(t.is_zero() == false)
            {
              char c(t.values[0U] & mask);

              if      (c <= char(  9))                      { c += char(0x30); }
              else if((c >= char(0xA)) && (c <= char(0xF))) { c += (is_uppercase ? char(55) : char(87)); }

              --pos;

              str_temp[pos] = c;

              t >>= 4;
            }
          }
          else
          {
            uintwide_t<my_width2, limb_type, AllocatorType, false> tu(t);

            while(tu.is_zero() == false)
            {
              char c(tu.values[0U] & mask);

              if      (c <= char(  9))                      { c += char(0x30); }
              else if((c >= char(0xA)) && (c <= char(0xF))) { c += (is_uppercase ? char(55) : char(87)); }

              --pos;

              str_temp[pos] = c;

              tu >>= 4;
            }
          }
        }

        if(show_base)
        {
          --pos;

          str_temp[pos] = (is_uppercase ? char('X') : char('x'));

          --pos;

          str_temp[pos] = char('0');
        }

        if(show_pos)
        {
          --pos;

          str_temp[pos] = char('+');
        }

        if(field_width != 0U)
        {
          field_width = (std::min)(field_width, std::uint_fast32_t(sizeof(str_temp) - 1U));

          while(std::int_fast32_t(pos) > std::int_fast32_t((sizeof(str_temp) - 1U) - field_width))
          {
            --pos;

            str_temp[pos] = fill_char;
          }
        }

        str_temp[(sizeof(str_temp) - 1U)] = char('\0');

        detail::strcpy_unsafe(str_result, str_temp + pos);
      }
      else
      {
        wr_string_is_ok = false;
      }

      return wr_string_is_ok;
    }

    template<const bool RePhraseIsSigned = IsSigned,
             typename std::enable_if<(RePhraseIsSigned == false)>::type const* = nullptr>
    WIDE_INTEGER_CONSTEXPR std::int_fast8_t compare(const uintwide_t<Width2, LimbType, AllocatorType, RePhraseIsSigned>& other) const
    {
      constexpr size_t local_number_of_limbs =
        uintwide_t<Width2, LimbType, AllocatorType, RePhraseIsSigned>::number_of_limbs;

      return compare_ranges(values.data(), other.values.data(), local_number_of_limbs);
    }

    template<const bool RePhraseIsSigned = IsSigned,
             typename std::enable_if<(RePhraseIsSigned == true)>::type const* = nullptr>
    WIDE_INTEGER_CONSTEXPR std::int_fast8_t compare(const uintwide_t<Width2, LimbType, AllocatorType, RePhraseIsSigned>& other) const
    {
      constexpr size_t local_number_of_limbs =
        uintwide_t<Width2, LimbType, AllocatorType, RePhraseIsSigned>::number_of_limbs;

      std::int_fast8_t n_result;

      if(is_neg(*this))
      {
        if(is_neg(other))
        {
          n_result = compare_ranges(values.data(), other.values.data(), local_number_of_limbs);
        }
        else
        {
          n_result = INT8_C(-1);
        }
      }
      else
      {
        if(is_neg(other))
        {
          n_result = INT8_C(1);
        }
        else
        {
          n_result = compare_ranges(values.data(), other.values.data(), local_number_of_limbs);
        }
      }

      return n_result;
    }

    WIDE_INTEGER_CONSTEXPR void negate()
    {
      bitwise_not();

      preincrement();
    }

    WIDE_INTEGER_CONSTEXPR void eval_divide_by_single_limb(const limb_type          short_denominator,
                                                           const std::uint_fast32_t u_offset,
                                                                 uintwide_t*        remainder)
    {
      // The denominator has one single limb.
      // Use a one-dimensional division algorithm.

      double_limb_type long_numerator = double_limb_type(0U);

      limb_type hi_part = limb_type(0U);

      for(std::int_fast32_t i = std::int_fast32_t((number_of_limbs - 1U) - u_offset); std::int_fast32_t(i) >= 0; --i)
      {
        long_numerator =
          double_limb_type
          (
             double_limb_type(values[std::uint_fast32_t(i)])
           + double_limb_type(double_limb_type(long_numerator - double_limb_type(double_limb_type(short_denominator) * hi_part)) << std::numeric_limits<limb_type>::digits)
          );

        values[std::uint_fast32_t(i)] =
          detail::make_lo<limb_type>(double_limb_type(long_numerator / short_denominator));

        hi_part = values[std::uint_fast32_t(i)];
      }

      if(remainder != nullptr)
      {
        long_numerator =
          double_limb_type
          (
             double_limb_type(values[0U])
           + double_limb_type(double_limb_type(long_numerator - double_limb_type(double_limb_type(short_denominator) * hi_part)) << std::numeric_limits<limb_type>::digits)
          );

        *remainder = limb_type(long_numerator >> std::numeric_limits<limb_type>::digits);
      }
    }

    WIDE_INTEGER_CONSTEXPR bool is_zero() const
    {
      auto it = values.cbegin();

      while((it != values.cend()) && (*it == limb_type(0U)))
      {
        ++it;
      }

      return (it == values.cend());
    }

    template<const bool RePhraseIsSigned = IsSigned,
             typename std::enable_if<(RePhraseIsSigned == false)>::type const* = nullptr>
    static constexpr bool is_neg(uintwide_t<Width2, LimbType, AllocatorType, RePhraseIsSigned>)
    {
      return false;
    }

    template<const bool RePhraseIsSigned = IsSigned,
             typename std::enable_if<(RePhraseIsSigned == true)>::type const* = nullptr>
    static constexpr bool is_neg(uintwide_t<Width2, LimbType, AllocatorType, RePhraseIsSigned> a)
    {
      return (std::uint_fast8_t(std::uint_fast8_t(a.values.back() >> (std::numeric_limits<typename uintwide_t<Width2, LimbType, AllocatorType, RePhraseIsSigned>::limb_type>::digits - 1)) & 1U) != 0U);
    }

  private:
    representation_type values { };

    // Constructor from the internal data representation.
    static WIDE_INTEGER_CONSTEXPR uintwide_t from_rep(const representation_type& other_rep)
    {
      uintwide_t a;

      a.values = other_rep;

      return a;
    }

    static WIDE_INTEGER_CONSTEXPR std::int_fast8_t compare_ranges(const limb_type*         a,
                                                                  const limb_type*         b,
                                                                  const std::uint_fast32_t count)
    {
      std::int_fast8_t n_return = 0;

      std::reverse_iterator<const limb_type*> pa(a + count);
      std::reverse_iterator<const limb_type*> pb(b + count);

      for( ; pa != std::reverse_iterator<const limb_type*>(a); ++pa, ++pb)
      {
        if     (*pa > *pb) { n_return =  1; break; }
        else if(*pa < *pb) { n_return = -1; break; }
      }

      return n_return;
    }

    // Implement a function that extracts any built-in signed or unsigned integral type.
    template<typename UnknownBuiltInIntegralType,
             typename = typename std::enable_if<(   (std::is_fundamental<UnknownBuiltInIntegralType>::value == true)
                                                 && (std::is_integral   <UnknownBuiltInIntegralType>::value == true))>::type>
    WIDE_INTEGER_CONSTEXPR UnknownBuiltInIntegralType extract_builtin_integral_type() const
    {
      using local_unknown_integral_type  = UnknownBuiltInIntegralType;

      using local_unsigned_integral_type =
        typename detail::uint_type_helper<
          std::numeric_limits<local_unknown_integral_type>::is_signed
            ? std::uint32_t(std::numeric_limits<local_unknown_integral_type>::digits + 1)
            : std::uint32_t(std::numeric_limits<local_unknown_integral_type>::digits + 0)>::exact_unsigned_type;

      local_unsigned_integral_type cast_result;

      const std::uint_fast8_t digits_ratio = 
        std::uint_fast8_t(  std::numeric_limits<local_unsigned_integral_type>::digits
                          / std::numeric_limits<limb_type>::digits);

      switch(digits_ratio)
      {
        case 0:
        case 1:
          // The input parameter is less wide or equally as wide as the limb width.
          cast_result = static_cast<local_unsigned_integral_type>(values[0U]);
          break;

        default:
          // The input parameter is wider than the limb width.
          cast_result = 0U;

          for(std::uint_fast8_t i = 0U; i < digits_ratio; ++i)
          {
            const local_unsigned_integral_type u =
              ((typename representation_type::size_type(i) < values.size())
                ? local_unsigned_integral_type(local_unsigned_integral_type(values[i]) << unsigned(std::numeric_limits<limb_type>::digits * int(i)))
                : local_unsigned_integral_type(0U));

            cast_result |= u;
          }
          break;
      }

      return local_unknown_integral_type(cast_result);
    }


    #if !defined(WIDE_INTEGER_DISABLE_FLOAT_INTEROP)
    // Implement a function that extracts any built-in floating-point type.
    template<typename FloatingPointType,
             typename = typename std::enable_if<(   (std::is_fundamental   <FloatingPointType>::value == true)
                                                 && (std::is_floating_point<FloatingPointType>::value == true))>::type>
    WIDE_INTEGER_CONSTEXPR FloatingPointType extract_builtin_floating_point_type() const
    {
      using local_unsigned_wide_integer_type = uintwide_t<Width2, limb_type, AllocatorType, false>;
      using local_builtin_float_type         = FloatingPointType;

      const bool u_is_neg = is_neg(*this);

      local_unsigned_wide_integer_type u(*this);

      if(u_is_neg)
      {
        u.negate();
      }

      const size_t my_msb = static_cast<size_t>(msb(u));
      const size_t ilim   = size_t
                            (
                               size_t(  size_t(my_msb + 1U) / size_t(std::numeric_limits<limb_type>::digits))
                             + size_t(((size_t(my_msb + 1U) % size_t(std::numeric_limits<limb_type>::digits)) != 0U) ? size_t(1U) : size_t(0U))
                            );

      const size_t jlim   = (std::max)
                            (
                              size_t(size_t(std::numeric_limits<limb_type>::digits) / size_t(std::numeric_limits<std::uint8_t>::digits)),
                              size_t(1U)
                            );

      local_builtin_float_type a = local_builtin_float_type(0.0F);

      size_t e2 = 0U;

      for(size_t i = size_t(0U); i < ilim; ++i)
      {
        limb_type lm = u.values[i];

        long double ld = 0.0L;

        for(size_t j = size_t(0U); j < jlim; ++j)
        {
          using std::ldexp;

          const long double f8 = ldexp((long double) static_cast<std::uint8_t>(lm), (int) e2);

          ld += f8;

          lm = limb_type(lm >> 8U);

          e2 = size_t(e2 + 8U);
        }

        a += (local_builtin_float_type) ld;
      }

      const local_builtin_float_type f = ((u_is_neg == false) ? a : -a);

      return f;
    }
    #endif

    template<const size_t OtherWidth2>
    static WIDE_INTEGER_CONSTEXPR void eval_mul_unary(      uintwide_t<OtherWidth2, LimbType, AllocatorType, IsSigned>& u,
                                                      const uintwide_t<OtherWidth2, LimbType, AllocatorType, IsSigned>& v,
                                                      typename std::enable_if<((OtherWidth2 / std::numeric_limits<LimbType>::digits) < number_of_limbs_karatsuba_threshold)>::type* = nullptr)
    {
      // Unary multiplication function using schoolbook multiplication,
      // but we only need to retain the low half of the n*n algorithm.
      // In other words, this is an n*n->n bit multiplication.

      constexpr size_t local_number_of_limbs =
        uintwide_t<OtherWidth2, LimbType, AllocatorType, IsSigned>::number_of_limbs;

      representation_type result{};

      eval_multiply_n_by_n_to_lo_part(result.data(),
                                      u.values.data(),
                                      v.values.data(),
                                      local_number_of_limbs);

      std::copy(result.cbegin(),
                result.cbegin() + local_number_of_limbs,
                u.values.begin());
    }

    template<const size_t OtherWidth2>
    static WIDE_INTEGER_CONSTEXPR void eval_mul_unary(      uintwide_t<OtherWidth2, LimbType, AllocatorType, IsSigned>& u,
                                                      const uintwide_t<OtherWidth2, LimbType, AllocatorType, IsSigned>& v,
                                                      typename std::enable_if<((OtherWidth2 / std::numeric_limits<LimbType>::digits) >= number_of_limbs_karatsuba_threshold)>::type* = nullptr)
    {
      // Unary multiplication function using Karatsuba multiplication.

      constexpr size_t local_number_of_limbs =
        uintwide_t<OtherWidth2, LimbType, AllocatorType, IsSigned>::number_of_limbs;

      // TBD: Can use specialized allocator or memory pool for these arrays.
      // Good examples for this (both threaded as well as non-threaded)
      // can be found in the wide_decimal project.
      typename std::conditional<std::is_same<AllocatorType, void>::value,
                                detail::fixed_static_array <limb_type, local_number_of_limbs * 2U>,
                                detail::fixed_dynamic_array<limb_type, local_number_of_limbs * 2U, AllocatorType>>::type result;

      typename std::conditional<std::is_same<AllocatorType, void>::value,
                                detail::fixed_static_array <limb_type, local_number_of_limbs * 4U>,
                                detail::fixed_dynamic_array<limb_type, local_number_of_limbs * 4U, AllocatorType>>::type t;

      eval_multiply_kara_n_by_n_to_2n(result.data(),
                                      u.values.data(),
                                      v.values.data(),
                                      local_number_of_limbs,
                                      t.data());

      std::copy(result.cbegin(),
                result.cbegin() + local_number_of_limbs,
                u.values.begin());
    }

    static WIDE_INTEGER_CONSTEXPR limb_type eval_add_n(      limb_type*          r,
                                                       const limb_type*          u,
                                                       const limb_type*          v,
                                                       const std::uint_fast32_t  count,
                                                       const limb_type           carry_in = 0U)
    {
      std::uint_fast8_t carry_out = static_cast<std::uint_fast8_t>(carry_in);

      for(std::uint_fast32_t i = 0U; i < count; ++i)
      {
        const double_limb_type uv_as_ularge = double_limb_type(double_limb_type(double_limb_type(u[i]) + v[i]) + carry_out);

        carry_out = static_cast<std::uint_fast8_t>(detail::make_hi<limb_type>(uv_as_ularge));

        r[i] = static_cast<limb_type>(uv_as_ularge);
      }

      return static_cast<limb_type>(carry_out);
    }

    static WIDE_INTEGER_CONSTEXPR bool eval_subtract_n(      limb_type*         r,
                                                       const limb_type*         u,
                                                       const limb_type*         v,
                                                       const std::uint_fast32_t count,
                                                       const bool               has_borrow_in = false)
    {
      std::uint_fast8_t has_borrow_out = (has_borrow_in ? 1U : 0U);

      for(std::uint_fast32_t i = 0U; i < count; ++i)
      {
        const double_limb_type uv_as_ularge = double_limb_type(double_limb_type(double_limb_type(u[i]) - v[i]) - has_borrow_out);

        has_borrow_out = (detail::make_hi<limb_type>(uv_as_ularge) != limb_type(0U)) ? 1U : 0U;

        r[i] = limb_type(uv_as_ularge);
      }

      return (has_borrow_out != 0U);
    }

    template<const size_t RePhraseWidth2 = Width2,
             typename std::enable_if<(uintwide_t<RePhraseWidth2, LimbType, AllocatorType, IsSigned>::number_of_limbs == 4U)>::type const* = nullptr>
    static WIDE_INTEGER_CONSTEXPR void eval_multiply_n_by_n_to_lo_part(      LimbType*          r,
                                                                       const LimbType*          a,
                                                                       const LimbType*          b,
                                                                       const std::uint_fast32_t count)
    {
      static_cast<void>(count);

      using local_limb_type        = typename uintwide_t<RePhraseWidth2, LimbType, AllocatorType, IsSigned>::limb_type;
      using local_double_limb_type = typename uintwide_t<RePhraseWidth2, LimbType, AllocatorType, IsSigned>::double_limb_type;

      // The algorithm has been derived from the polynomial multiplication.
      // After the multiplication terms of equal order are grouped
      // together and retained up to order(3). The carries from the
      // multiplications are included when adding up the terms.
      // The results of the intermediate multiplications are stored
      // in local variables in memory.

      //   Column[CoefficientList[Expand[(a0 + a1 x + a2 x^2 + a3 x^3) (b0 + b1 x + b2 x^2 + b3 x^3)], x]]
      //   a0b0
      //   a1b0 + a0b1
      //   a2b0 + a1b1 + a0b2
      //   a3b0 + a2b1 + a1b2 + a0b3

      // See also Wolfram Alpha at:
      // https://www.wolframalpha.com/input/?i=Column%5BCoefficientList%5B+++Expand%5B%28a0+%2B+a1+x+%2B+a2+x%5E2+%2B+a3+x%5E3%29+%28b0+%2B+b1+x+%2B+b2+x%5E2+%2B+b3+x%5E3%29%5D%2C++++x%5D%5D
      // ... and take the upper half of the pyramid.

      // Performance improvement:
      //   (old) kops_per_sec: 33173.50
      //   (new) kops_per_sec: 95069.43

      local_double_limb_type r1;
      local_double_limb_type r2;

      const local_double_limb_type a0b0 = a[0U] * local_double_limb_type(b[0U]);
      const local_double_limb_type a0b1 = a[0U] * local_double_limb_type(b[1U]);
      const local_double_limb_type a1b0 = a[1U] * local_double_limb_type(b[0U]);
      const local_double_limb_type a1b1 = a[1U] * local_double_limb_type(b[1U]);

      // One special case is considered, the case of multiplication
      // of the form BITS/2 * BITS/2 = BITS. In this case, the algorithm
      // can be significantly simplified by using only the 'lower-halves'
      // of the data.
      if(    (a[2U] == 0U) && (b[2U] == 0U)
          && (a[3U] == 0U) && (b[3U] == 0U))
      {
        r1    = local_double_limb_type
                (
                  detail::make_hi<local_limb_type>(a0b0)
                )
                + detail::make_lo<local_limb_type>(a1b0)
                + detail::make_lo<local_limb_type>(a0b1)
                ;
        r2    = local_double_limb_type
                (
                  detail::make_hi<local_limb_type>(r1)
                )
                + detail::make_lo<local_limb_type>(a1b1)
                + detail::make_hi<local_limb_type>(a0b1)
                + detail::make_hi<local_limb_type>(a1b0)
                ;
        r[3U] =   detail::make_hi<local_limb_type>(r2)
                + detail::make_hi<local_limb_type>(a1b1)
                ;
      }
      else
      {
        const local_double_limb_type a0b2 = a[0U] * local_double_limb_type(b[2U]);
        const local_double_limb_type a2b0 = a[2U] * local_double_limb_type(b[0U]);

        r1    = local_double_limb_type
                (
                  detail::make_hi<local_limb_type>(a0b0)
                )
                + detail::make_lo<local_limb_type>(a1b0)
                + detail::make_lo<local_limb_type>(a0b1)
                ;
        r2    = local_double_limb_type
                (
                  detail::make_hi<local_limb_type>(r1)
                )
                + detail::make_lo<local_limb_type>(a2b0)
                + detail::make_lo<local_limb_type>(a1b1)
                + detail::make_lo<local_limb_type>(a0b2)
                + detail::make_hi<local_limb_type>(a1b0)
                + detail::make_hi<local_limb_type>(a0b1)
                ;
        r[3U] =   detail::make_hi<local_limb_type>(r2)
                + static_cast<local_limb_type>    (a[3U] * local_double_limb_type(b[0U]))
                + static_cast<local_limb_type>    (a[2U] * local_double_limb_type(b[1U]))
                + static_cast<local_limb_type>    (a[1U] * local_double_limb_type(b[2U]))
                + static_cast<local_limb_type>    (a[0U] * local_double_limb_type(b[3U]))
                + detail::make_hi<local_limb_type>(a2b0)
                + detail::make_hi<local_limb_type>(a1b1)
                + detail::make_hi<local_limb_type>(a0b2)
                ;
      }

      r[0U] = local_limb_type(a0b0);
      r[1U] = local_limb_type(r1);
      r[2U] = local_limb_type(r2);
    }

    #if defined(WIDE_INTEGER_HAS_MUL_8_BY_8_UNROLL)
    template<const size_t RePhraseWidth2 = Width2,
             typename std::enable_if<(uintwide_t<RePhraseWidth2, LimbType, AllocatorType, IsSigned>::number_of_limbs == 8U)>::type const* = nullptr>
    static WIDE_INTEGER_CONSTEXPR void eval_multiply_n_by_n_to_lo_part(      LimbType*          r,
                                                                       const LimbType*          a,
                                                                       const LimbType*          b,
                                                                       const std::uint_fast32_t count)
    {
      static_cast<void>(count);

      using local_limb_type        = typename uintwide_t<RePhraseWidth2, LimbType, AllocatorType, IsSigned>::limb_type;
      using local_double_limb_type = typename uintwide_t<RePhraseWidth2, LimbType, AllocatorType, IsSigned>::double_limb_type;

      // The algorithm has been derived from the polynomial multiplication.
      // After the multiplication terms of equal order are grouped
      // together and retained up to order(3). The carries from the
      // multiplications are included when adding up the terms.
      // The results of the intermediate multiplications are stored
      // in local variables in memory.

      //   Column[CoefficientList[Expand[(a0 + a1 x + a2 x^2 + a3 x^3 + a4 x^4 + a5 x^5 + a6 x^6 + a7 x^7) (b0 + b1 x + b2 x^2 + b3 x^3 + b4 x^4 + b5 x^5 + b6 x^6 + b7 x^7)], x]]
      //   a0b0
      //   a1b0 + a0b1
      //   a2b0 + a1b1 + a0b2
      //   a3b0 + a2b1 + a1b2 + a0b3
      //   a4b0 + a3b1 + a2b2 + a1b3 + a0b4
      //   a5b0 + a4b1 + a3b2 + a2b3 + a1b4 + a0b5
      //   a6b0 + a5b1 + a4b2 + a3b3 + a2b4 + a1b5 + a0b6
      //   a7b0 + a6b1 + a5b2 + a4b3 + a3b4 + a2b5 + a1b6 + a0b7

      // See also Wolfram Alpha at:
      // https://www.wolframalpha.com/input/?i=Column%5BCoefficientList%5B+++Expand%5B%28a0+%2B+a1+x+%2B+a2+x%5E2+%2B+a3+x%5E3%29+%28b0+%2B+b1+x+%2B+b2+x%5E2+%2B+b3+x%5E3%29%5D%2C++++x%5D%5D
      // ... and take the upper half of the pyramid.

      const local_double_limb_type a0b0 = a[0U] * local_double_limb_type(b[0U]);

      const local_double_limb_type a1b0 = a[1U] * local_double_limb_type(b[0U]);
      const local_double_limb_type a0b1 = a[0U] * local_double_limb_type(b[1U]);

      const local_double_limb_type a2b0 = a[2U] * local_double_limb_type(b[0U]);
      const local_double_limb_type a1b1 = a[1U] * local_double_limb_type(b[1U]);
      const local_double_limb_type a0b2 = a[0U] * local_double_limb_type(b[2U]);

      const local_double_limb_type a3b0 = a[3U] * local_double_limb_type(b[0U]);
      const local_double_limb_type a2b1 = a[2U] * local_double_limb_type(b[1U]);
      const local_double_limb_type a1b2 = a[1U] * local_double_limb_type(b[2U]);
      const local_double_limb_type a0b3 = a[0U] * local_double_limb_type(b[3U]);

      const local_double_limb_type a3b1 = a[3U] * local_double_limb_type(b[1U]);
      const local_double_limb_type a2b2 = a[2U] * local_double_limb_type(b[2U]);
      const local_double_limb_type a1b3 = a[1U] * local_double_limb_type(b[3U]);

      const local_double_limb_type a3b2 = a[3U] * local_double_limb_type(b[2U]);
      const local_double_limb_type a2b3 = a[2U] * local_double_limb_type(b[3U]);

      const local_double_limb_type a3b3 = a[3U] * local_double_limb_type(b[3U]);

            local_double_limb_type rd1;
            local_double_limb_type rd2;
            local_double_limb_type rd3;
            local_double_limb_type rd4;
            local_double_limb_type rd5;
            local_double_limb_type rd6;

      // One special case is considered, the case of multiplication
      // of the form BITS/2 * BITS/2 = BITS. In this case, the algorithm
      // can be significantly simplified by using only the 'lower-halves'
      // of the data.
      if(    (a[7U] == 0U) && (b[7U] == 0U)
          && (a[6U] == 0U) && (b[6U] == 0U)
          && (a[5U] == 0U) && (b[5U] == 0U)
          && (a[4U] == 0U) && (b[4U] == 0U))
      {
        rd1   = local_double_limb_type
                (
                  detail::make_hi<local_limb_type>(a0b0)
                )
                + detail::make_lo<local_limb_type>(a1b0)
                + detail::make_lo<local_limb_type>(a0b1)
                ;

        rd2   = local_double_limb_type
                (
                  detail::make_hi<local_limb_type>(rd1)
                )
                + detail::make_lo<local_limb_type>(a2b0)
                + detail::make_lo<local_limb_type>(a1b1)
                + detail::make_lo<local_limb_type>(a0b2)
                + detail::make_hi<local_limb_type>(a1b0)
                + detail::make_hi<local_limb_type>(a0b1)
                ;

        rd3   = local_double_limb_type
                (
                  detail::make_hi<local_limb_type>(rd2)
                )
                + detail::make_lo<local_limb_type>(a3b0)
                + detail::make_lo<local_limb_type>(a2b1)
                + detail::make_lo<local_limb_type>(a1b2)
                + detail::make_lo<local_limb_type>(a0b3)
                + detail::make_hi<local_limb_type>(a2b0)
                + detail::make_hi<local_limb_type>(a1b1)
                + detail::make_hi<local_limb_type>(a0b2)
                ;

        rd4   = local_double_limb_type
                (
                  detail::make_hi<local_limb_type>(rd3)
                )
                + detail::make_lo<local_limb_type>(a3b1)
                + detail::make_lo<local_limb_type>(a2b2)
                + detail::make_lo<local_limb_type>(a1b3)
                + detail::make_hi<local_limb_type>(a3b0)
                + detail::make_hi<local_limb_type>(a2b1)
                + detail::make_hi<local_limb_type>(a1b2)
                + detail::make_hi<local_limb_type>(a0b3)
                ;

        rd5   = local_double_limb_type
                (
                  detail::make_hi<local_limb_type>(rd4)
                )
                + detail::make_lo<local_limb_type>(a3b2)
                + detail::make_lo<local_limb_type>(a2b3)
                + detail::make_hi<local_limb_type>(a3b1)
                + detail::make_hi<local_limb_type>(a2b2)
                + detail::make_hi<local_limb_type>(a1b3)
                ;

        rd6   = local_double_limb_type
                (
                  detail::make_hi<local_limb_type>(rd5)
                )
                + detail::make_lo<local_limb_type>(a3b3)
                + detail::make_hi<local_limb_type>(a3b2)
                + detail::make_hi<local_limb_type>(a2b3)
                ;

        r[7U] = local_limb_type
                (local_double_limb_type
                  (
                    detail::make_hi<local_limb_type>(rd6)
                  )
                  + detail::make_hi<local_limb_type>(a3b3)
                )
                ;
      }
      else
      {
        const local_double_limb_type a4b0 = a[4U] * local_double_limb_type(b[0U]);
        const local_double_limb_type a0b4 = a[0U] * local_double_limb_type(b[4U]);

        const local_double_limb_type a5b0 = a[5U] * local_double_limb_type(b[0U]);
        const local_double_limb_type a4b1 = a[4U] * local_double_limb_type(b[1U]);

        const local_double_limb_type a1b4 = a[1U] * local_double_limb_type(b[4U]);
        const local_double_limb_type a0b5 = a[0U] * local_double_limb_type(b[5U]);

        const local_double_limb_type a6b0 = a[6U] * local_double_limb_type(b[0U]);
        const local_double_limb_type a5b1 = a[5U] * local_double_limb_type(b[1U]);
        const local_double_limb_type a4b2 = a[4U] * local_double_limb_type(b[2U]);

        const local_double_limb_type a2b4 = a[2U] * local_double_limb_type(b[4U]);
        const local_double_limb_type a1b5 = a[1U] * local_double_limb_type(b[5U]);
        const local_double_limb_type a0b6 = a[0U] * local_double_limb_type(b[6U]);

        rd1   = local_double_limb_type
                (
                  detail::make_hi<local_limb_type>(a0b0)
                )
                + detail::make_lo<local_limb_type>(a1b0)
                + detail::make_lo<local_limb_type>(a0b1)
                ;

        rd2   = local_double_limb_type
                (
                  detail::make_hi<local_limb_type>(rd1)
                )
                + detail::make_lo<local_limb_type>(a2b0)
                + detail::make_lo<local_limb_type>(a1b1)
                + detail::make_lo<local_limb_type>(a0b2)
                + detail::make_hi<local_limb_type>(a1b0)
                + detail::make_hi<local_limb_type>(a0b1)
                ;

        rd3   = local_double_limb_type
                (
                  detail::make_hi<local_limb_type>(rd2)
                )
                + detail::make_lo<local_limb_type>(a3b0)
                + detail::make_lo<local_limb_type>(a2b1)
                + detail::make_lo<local_limb_type>(a1b2)
                + detail::make_lo<local_limb_type>(a0b3)
                + detail::make_hi<local_limb_type>(a2b0)
                + detail::make_hi<local_limb_type>(a1b1)
                + detail::make_hi<local_limb_type>(a0b2)
                ;

        rd4   = local_double_limb_type
                (
                  detail::make_hi<local_limb_type>(rd3)
                )
                + detail::make_lo<local_limb_type>(a4b0)
                + detail::make_lo<local_limb_type>(a3b1)
                + detail::make_lo<local_limb_type>(a2b2)
                + detail::make_lo<local_limb_type>(a1b3)
                + detail::make_lo<local_limb_type>(a0b4)
                + detail::make_hi<local_limb_type>(a3b0)
                + detail::make_hi<local_limb_type>(a2b1)
                + detail::make_hi<local_limb_type>(a1b2)
                + detail::make_hi<local_limb_type>(a0b3)
                ;

        rd5   = local_double_limb_type
                (
                  detail::make_hi<local_limb_type>(rd4)
                )
                + detail::make_lo<local_limb_type>(a5b0)
                + detail::make_lo<local_limb_type>(a4b1)
                + detail::make_lo<local_limb_type>(a3b2)
                + detail::make_lo<local_limb_type>(a2b3)
                + detail::make_lo<local_limb_type>(a1b4)
                + detail::make_lo<local_limb_type>(a0b5)
                + detail::make_hi<local_limb_type>(a4b0)
                + detail::make_hi<local_limb_type>(a3b1)
                + detail::make_hi<local_limb_type>(a2b2)
                + detail::make_hi<local_limb_type>(a1b3)
                + detail::make_hi<local_limb_type>(a0b4)
                ;

        rd6   = local_double_limb_type
                (
                  detail::make_hi<local_limb_type>(rd5)
                )
                + detail::make_lo<local_limb_type>(a6b0)
                + detail::make_lo<local_limb_type>(a5b1)
                + detail::make_lo<local_limb_type>(a4b2)
                + detail::make_lo<local_limb_type>(a3b3)
                + detail::make_lo<local_limb_type>(a2b4)
                + detail::make_lo<local_limb_type>(a1b5)
                + detail::make_lo<local_limb_type>(a0b6)
                + detail::make_hi<local_limb_type>(a5b0)
                + detail::make_hi<local_limb_type>(a4b1)
                + detail::make_hi<local_limb_type>(a3b2)
                + detail::make_hi<local_limb_type>(a2b3)
                + detail::make_hi<local_limb_type>(a1b4)
                + detail::make_hi<local_limb_type>(a0b5)
                ;

        r[7U] = local_limb_type
                (
                  local_double_limb_type
                  (
                    detail::make_hi<local_limb_type>(rd6)
                  )
                  + static_cast<local_limb_type>    (a[7U] * local_double_limb_type(b[0U]))
                  + static_cast<local_limb_type>    (a[6U] * local_double_limb_type(b[1U]))
                  + static_cast<local_limb_type>    (a[5U] * local_double_limb_type(b[2U]))
                  + static_cast<local_limb_type>    (a[4U] * local_double_limb_type(b[3U]))
                  + static_cast<local_limb_type>    (a[3U] * local_double_limb_type(b[4U]))
                  + static_cast<local_limb_type>    (a[2U] * local_double_limb_type(b[5U]))
                  + static_cast<local_limb_type>    (a[1U] * local_double_limb_type(b[6U]))
                  + static_cast<local_limb_type>    (a[0U] * local_double_limb_type(b[7U]))
                  + detail::make_hi<local_limb_type>(a6b0)
                  + detail::make_hi<local_limb_type>(a5b1)
                  + detail::make_hi<local_limb_type>(a4b2)
                  + detail::make_hi<local_limb_type>(a3b3)
                  + detail::make_hi<local_limb_type>(a2b4)
                  + detail::make_hi<local_limb_type>(a1b5)
                  + detail::make_hi<local_limb_type>(a0b6)
                )
                ;
      }

      r[0U] = static_cast<local_limb_type>(a0b0);
      r[1U] = static_cast<local_limb_type>(rd1);
      r[2U] = static_cast<local_limb_type>(rd2);
      r[3U] = static_cast<local_limb_type>(rd3);
      r[4U] = static_cast<local_limb_type>(rd4);
      r[5U] = static_cast<local_limb_type>(rd5);
      r[6U] = static_cast<local_limb_type>(rd6);
    }
    #endif

    template<const size_t RePhraseWidth2 = Width2,
             typename std::enable_if<(   (uintwide_t<RePhraseWidth2, LimbType, AllocatorType>::number_of_limbs != 4U)
    #if defined(WIDE_INTEGER_HAS_MUL_8_BY_8_UNROLL)
                                      && (uintwide_t<RePhraseWidth2, LimbType, AllocatorType>::number_of_limbs != 8U)
    #endif
                                     )>::type const* = nullptr>
    static WIDE_INTEGER_CONSTEXPR void eval_multiply_n_by_n_to_lo_part(      LimbType*          r,
                                                                       const LimbType*          a,
                                                                       const LimbType*          b,
                                                                       const std::uint_fast32_t count)
    {
      using local_limb_type        = typename uintwide_t<RePhraseWidth2, LimbType, AllocatorType>::limb_type;
      using local_double_limb_type = typename uintwide_t<RePhraseWidth2, LimbType, AllocatorType>::double_limb_type;

      std::fill_n(r, count, local_limb_type(0U));

      for(std::uint_fast32_t i = 0U; i < count; ++i)
      {
        if(a[i] != local_limb_type(0U))
        {
          local_double_limb_type carry = 0U;

          for(std::uint_fast32_t j = 0U; j < (count - i); ++j)
          {
            carry = local_double_limb_type(carry + local_double_limb_type(local_double_limb_type(a[i]) * b[j]));
            carry = local_double_limb_type(carry + r[i + j]);

            r[i + j] = local_limb_type(carry);
            carry    = detail::make_hi<local_limb_type>(carry);
          }
        }
      }
    }

    static WIDE_INTEGER_CONSTEXPR void eval_multiply_n_by_n_to_2n(      limb_type*         r,
                                                                  const limb_type*         a,
                                                                  const limb_type*         b,
                                                                  const std::uint_fast32_t count)
    {
      std::fill_n(r, (count * 2U), limb_type(0U));

      for(std::uint_fast32_t i = 0U; i < count; ++i)
      {
        if(a[i] != limb_type(0U))
        {
          std::uint_fast32_t j = 0U;

          double_limb_type carry = 0U;

          for( ; j < count; ++j)
          {
            carry    = double_limb_type(carry + double_limb_type(double_limb_type(a[i]) * b[j]));
            carry    = double_limb_type(carry + r[i + j]);

            r[i + j] = limb_type(carry);
            carry    = detail::make_hi<limb_type>(carry);
          }

          r[i + j] = limb_type(carry);
        }
      }
    }

    static WIDE_INTEGER_CONSTEXPR limb_type eval_multiply_1d(      limb_type*         r,
                                                             const limb_type*         a,
                                                             const limb_type          b,
                                                             const std::uint_fast32_t count)
    {
      double_limb_type carry = 0U;

      if(b == 0U)
      {
        std::fill(r, r + count, limb_type(0U));
      }
      else
      {
        for(std::uint_fast32_t i = 0U ; i < count; ++i)
        {
          carry = double_limb_type(carry + double_limb_type(double_limb_type(a[i]) * b));

          r[i]  = limb_type(carry);
          carry = detail::make_hi<limb_type>(carry);
        }
      }

      return limb_type(carry);
    }

    static void eval_multiply_kara_propagate_carry(limb_type* t, const std::uint_fast32_t n, const limb_type carry)
    {
      std::uint_fast32_t i = 0U;

      limb_type carry_out = carry;

      while((i < n) && (carry_out != 0U))
      {
        const double_limb_type uv_as_ularge = double_limb_type(t[i]) + carry_out;

        carry_out = detail::make_hi<limb_type>(uv_as_ularge);

        t[i] = limb_type(uv_as_ularge);

        ++i;
      }
    }

    static void eval_multiply_kara_propagate_borrow(limb_type* t, const std::uint_fast32_t n, const bool has_borrow)
    {
      std::uint_fast32_t i = 0U;

      bool has_borrow_out = has_borrow;

      while((i < n) && (has_borrow_out == true))
      {
        double_limb_type uv_as_ularge = double_limb_type(t[i]);

        if(has_borrow_out)
        {
          --uv_as_ularge;
        }

        has_borrow_out = (detail::make_hi<limb_type>(uv_as_ularge) != limb_type(0U));

        t[i] = limb_type(uv_as_ularge);

        ++i;
      }
    }

    static void eval_multiply_kara_n_by_n_to_2n(      limb_type*         r,
                                                const limb_type*         a,
                                                const limb_type*         b,
                                                const std::uint_fast32_t n,
                                                      limb_type*         t)
    {
      if(n <= 48U)
      {
        static_cast<void>(t);

        eval_multiply_n_by_n_to_2n(r, a, b, n);
      }
      else
      {
        // Based on "Algorithm 1.3 KaratsubaMultiply", Sect. 1.3.2, page 5
        // of R.P. Brent and P. Zimmermann, "Modern Computer Arithmetic",
        // Cambridge University Press (2011).

        // The Karatsuba multipliation computes the product of u*v as:
        // [b^N + b^(N/2)] a1*b1 + [b^(N/2)](a1 - a0)(b0 - b1) + [b^(N/2) + 1] a0*b0

        // Here we visualize u and v in two components 0,1 corresponding
        // to the high and low order parts, respectively.

        // Step 1
        // Calculate a1*b1 and store it in the upper part of r.
        // Calculate a0*b0 and store it in the lower part of r.
        // copy r to t0.

        // Step 2
        // Add a1*b1 (which is t2) to the middle two-quarters of r (which is r1)
        // Add a0*b0 (which is t0) to the middle two-quarters of r (which is r1)

        // Step 3
        // Calculate |a1-a0| in t0 and note the sign (i.e., the borrow flag)

        // Step 4
        // Calculate |b0-b1| in t1 and note the sign (i.e., the borrow flag)

        // Step 5
        // Call kara mul to calculate |a1-a0|*|b0-b1| in (t2),
        // while using temporary storage in t4 along the way.

        // Step 6
        // Check the borrow signs. If a1-a0 and b0-b1 have the same signs,
        // then add |a1-a0|*|b0-b1| to r1, otherwise subtract it from r1.

        const std::uint_fast32_t  nh = n / 2U;

        const limb_type* a0 = a + 0U;
        const limb_type* a1 = a + nh;

        const limb_type* b0 = b + 0U;
        const limb_type* b1 = b + nh;

              limb_type* r0 = r + 0U;
              limb_type* r1 = r + nh;
              limb_type* r2 = r + n;
              limb_type* r3 = r + (n + nh);

              limb_type* t0 = t + 0U;
              limb_type* t1 = t + nh;
              limb_type* t2 = t + n;
              limb_type* t4 = t + (n + n);

        // Step 1
        //   a1*b1 -> r2
        //   a0*b0 -> r0
        //   r -> t0
        eval_multiply_kara_n_by_n_to_2n(r2, a1, b1, nh, t0);
        eval_multiply_kara_n_by_n_to_2n(r0, a0, b0, nh, t0);
        std::copy(r0, r0 + (2U * n), t0);

        // Step 2
        //   r1 += a1*b1
        //   r1 += a0*b0
        limb_type carry;
        carry = eval_add_n(r1, r1, t2, n);
        eval_multiply_kara_propagate_carry(r3, nh, carry);
        carry = eval_add_n(r1, r1, t0, n);
        eval_multiply_kara_propagate_carry(r3, nh, carry);

        // Step 3
        //   |a1-a0| -> t0
        const std::int_fast8_t cmp_result_a1a0 = compare_ranges(a1, a0, nh);

        if(cmp_result_a1a0 == 1)
        {
          static_cast<void>(eval_subtract_n(t0, a1, a0, nh));
        }
        else if(cmp_result_a1a0 == -1)
        {
          static_cast<void>(eval_subtract_n(t0, a0, a1, nh));
        }

        // Step 4
        //   |b0-b1| -> t1
        const std::int_fast8_t cmp_result_b0b1 = compare_ranges(b0, b1, nh);

        if(cmp_result_b0b1 == 1)
        {
          static_cast<void>(eval_subtract_n(t1, b0, b1, nh));
        }
        else if(cmp_result_b0b1 == -1)
        {
          static_cast<void>(eval_subtract_n(t1, b1, b0, nh));
        }

        // Step 5
        //   |a1-a0|*|b0-b1| -> t2
        eval_multiply_kara_n_by_n_to_2n(t2, t0, t1, nh, t4);

        // Step 6
        //   either r1 += |a1-a0|*|b0-b1|
        //   or     r1 -= |a1-a0|*|b0-b1|
        if((cmp_result_a1a0 * cmp_result_b0b1) == 1)
        {
          carry = eval_add_n(r1, r1, t2, n);

          eval_multiply_kara_propagate_carry(r3, nh, carry);
        }
        else if((cmp_result_a1a0 * cmp_result_b0b1) == -1)
        {
          const bool has_borrow = eval_subtract_n(r1, r1, t2, n);

          eval_multiply_kara_propagate_borrow(r3, nh, has_borrow);
        }
      }
    }

    #if 0
    static void eval_multiply_toomcook3(      limb_type*         r,
                                        const limb_type*         u,
                                        const limb_type*         v,
                                        const std::uint_fast32_t n,
                                              limb_type*         t)
    {
      if(n == 3072U)
      {
        // TBD: Tune the threshold for the transition
        // from Toom-Cook3 back to base case Karatsuba.

        // Base case Karatsuba multiplication.
        eval_multiply_kara_n_by_n_to_2n(r, u, v, n, t);
      }
      else
      {
        // Based on "Algorithm 1.4 ToomCook3", Sect. 1.3.3, page 7 of
        // R.P. Brent and P. Zimmermann, "Modern Computer Arithmetic",
        // Cambridge University Press (2011).

        // TBD: Toom-Cook3
        eval_multiply_kara_n_by_n_to_2n(r, u, v, n, t);
      }
    }

    static void eval_multiply_toomcook4(      limb_type*         r,
                                        const limb_type*         u,
                                        const limb_type*         v,
                                        const std::uint_fast32_t n,
                                              limb_type*         t)
    {
      if(n == 2048U)
      {
        // TBD: Tune the threshold for the transition
        // from Toom-Cook4 back to base case Karatsuba.

        // Base case Karatsuba multiplication.
        eval_multiply_kara_n_by_n_to_2n(r, u, v, n, t);
      }
      else
      {
        // TBD: Toom-Cook4
        eval_multiply_kara_n_by_n_to_2n(r, u, v, n, t);
      }
    }
    #endif

    WIDE_INTEGER_CONSTEXPR void eval_divide_knuth(const uintwide_t& other,
                                                        uintwide_t* remainder,
                                                  const bool        denom_was_neg = false)
    {
      // Use Knuth's long division algorithm.
      // The loop-ordering of indexes in Knuth's original
      // algorithm has been reversed due to the data format
      // used here. Several optimizations and combinations
      // of logic have been carried out in the source code.

      bool bNegQuot = false;
      bool bNegRem  = false;

      // Make *this (the numerator) positive. The sign of the
      // remainder will match the sign of the denominator.
      if(is_neg(*this))
      {
        bNegRem = true;

        negate();
      }

      // The denominator has (already) been made positive and its sign has
      // been provided in the denom_was_neg flag. The sign of the quotient
      // will be negative if the sign of the divisor and dividend do not match,
      // else positive.
      if(denom_was_neg)
      {
        bNegQuot = !bNegRem;
      }
      else
      {
        bNegQuot = bNegRem;
      }

      // See also:
      // D.E. Knuth, "The Art of Computer Programming, Volume 2:
      // Seminumerical Algorithms", Addison-Wesley (1998),
      // Section 4.3.1 Algorithm D and Exercise 16.

      using local_uint_index_type = std::uint_fast32_t;

      local_uint_index_type u_offset = local_uint_index_type(0U);
      local_uint_index_type v_offset = local_uint_index_type(0U);

      // Compute the offsets for u and v.
      for(local_uint_index_type i = 0U; (i < number_of_limbs) && (      values[(number_of_limbs - 1U) - i] == limb_type(0U)); ++i) { ++u_offset; }
      for(local_uint_index_type i = 0U; (i < number_of_limbs) && (other.values[(number_of_limbs - 1U) - i] == limb_type(0U)); ++i) { ++v_offset; }

      if(v_offset == local_uint_index_type(number_of_limbs))
      {
        // The denominator is zero. Set the maximum value and return.
        // This also catches (0 / 0) and sets the maximum value for it.
        operator=(limits_helper_max(IsSigned));

        if(remainder != nullptr)
        {
          *remainder = uintwide_t(std::uint8_t(0U));
        }
      }
      else if(u_offset == local_uint_index_type(number_of_limbs))
      {
        // The numerator is zero. Do nothing and return.

        if(remainder != nullptr)
        {
          *remainder = uintwide_t(std::uint8_t(0U));
        }
      }
      else
      {
        const int result_of_compare_left_with_right = compare(other);

        const bool left_is_less_than_right = (result_of_compare_left_with_right == -1);
        const bool left_is_equal_to_right  = (result_of_compare_left_with_right ==  0);

        if(left_is_less_than_right)
        {
          // If the denominator is larger than the numerator,
          // then the result of the division is zero.
          if(remainder != nullptr)
          {
            *remainder = *this;

            if(bNegRem) { remainder->negate(); }
          }

          operator=(std::uint8_t(0U));
        }
        else if(left_is_equal_to_right)
        {
          // If the denominator is equal to the numerator,
          // then the result of the division is one.
          operator=(std::uint8_t(1U));

          if(remainder != nullptr)
          {
            *remainder = uintwide_t(std::uint8_t(0U));
          }
        }
        else if(v_offset == local_uint_index_type(number_of_limbs - 1U))
        {
          // The denominator has one single limb.
          // Use a one-dimensional division algorithm.
          const limb_type short_denominator = other.values[0U];

          eval_divide_by_single_limb(short_denominator, u_offset, remainder);

          if(bNegQuot) { negate(); }
          if(bNegRem && remainder != nullptr)  { remainder->negate(); }
        }
        else
        {
          // We will now use the Knuth long division algorithm.

          // Compute the normalization factor d.
          const limb_type d =
            limb_type(double_limb_type(  double_limb_type(double_limb_type(1U) << std::numeric_limits<limb_type>::digits)
                                       / double_limb_type(double_limb_type(other.values[(number_of_limbs - 1U) - v_offset]) + limb_type(1U))));

          // Step D1(b), normalize u -> u * d = uu.
          // Step D1(c): normalize v -> v * d = vv.

          using uu_array_type =
            typename std::conditional<std::is_same<AllocatorType, void>::value,
                                      detail::fixed_static_array <limb_type, number_of_limbs + 1U>,
                                      detail::fixed_dynamic_array<limb_type, number_of_limbs + 1U, AllocatorType>>::type;

          uu_array_type       uu;
          representation_type vv;

          if(d > limb_type(1U))
          {
            uu[number_of_limbs - u_offset] =
              eval_multiply_1d(uu.data(), values.data(), d, number_of_limbs - u_offset);

            static_cast<void>(eval_multiply_1d(vv.data(), other.values.data(), d, number_of_limbs - v_offset));
          }
          else
          {
            std::copy(values.cbegin(), values.cend(), uu.begin());

            uu[number_of_limbs - u_offset] = limb_type(0U);

            vv = other.values;
          }

          // Step D2: Initialize j.
          // Step D7: Loop on j from m to 0.

          const local_uint_index_type n   = local_uint_index_type(number_of_limbs - v_offset);
          const local_uint_index_type m   = local_uint_index_type(number_of_limbs - u_offset) - n;
          const local_uint_index_type vj0 = (number_of_limbs - 1U) - v_offset;

          for(local_uint_index_type j = local_uint_index_type(0U); j <= m; ++j)
          {
            // Step D3 [Calculate q_hat].
            //   if u[j] == v[j0]
            //     set q_hat = b - 1
            //   else
            //     set q_hat = (u[j] * b + u[j + 1]) / v[1]

            const local_uint_index_type uj     = (((number_of_limbs + 1U) - 1U) - u_offset) - j;
            const double_limb_type      u_j_j1 = double_limb_type(double_limb_type(double_limb_type(uu[uj]) << std::numeric_limits<limb_type>::digits) + uu[uj - 1U]);

            limb_type q_hat = ((uu[uj] == vv[vj0]) ? (std::numeric_limits<limb_type>::max)()
                                                   : limb_type(u_j_j1 / vv[vj0]));

            // Decrease q_hat if necessary.
            // This means that q_hat must be decreased if the
            // expression [(u[uj] * b + u[uj - 1] - q_hat * v[vj0 - 1]) * b]
            // exceeds the range of uintwide_t.

            for(double_limb_type t = double_limb_type(u_j_j1 - double_limb_type(q_hat * double_limb_type(vv[vj0]))); ; --q_hat, t = double_limb_type(t + vv[vj0]))
            {
              if(   (detail::make_hi<limb_type>(t) != limb_type(0U))
                 || (   double_limb_type(double_limb_type(vv[vj0 - 1U]) * q_hat)
                     <= double_limb_type(double_limb_type(t << std::numeric_limits<limb_type>::digits) + uu[uj - 2U])))
              {
                break;
              }
            }

            // Step D4: Multiply and subtract.
            // Replace u[j, ... j + n] by u[j, ... j + n] - q_hat * v[1, ... n].

            // Set nv = q_hat * (v[1, ... n]).
            uu_array_type nv;

            nv[n] = eval_multiply_1d(nv.data(), vv.data(), q_hat, n);

            const bool has_borrow =
              eval_subtract_n(uu.data() + (uj - n), uu.data() + (uj - n), nv.data(), n + 1U);


            // Get the result data.
            values[m - j] = limb_type(q_hat - (has_borrow ? 1U : 0U));

            // Step D5: Test the remainder.
            // Set the result value: Set result.m_data[m - j] = q_hat.
            // Use the condition (u[j] < 0), in other words if the borrow
            // is non-zero, then step D6 needs to be carried out.

            if(has_borrow)
            {
              // Step D6: Add back.
              // Add v[1, ... n] back to u[j, ... j + n],
              // and decrease the result by 1.

              static_cast<void>(eval_add_n(uu.data() + (uj - n), uu.data() + (uj - n), vv.data(), n));
            }
          }

          // Clear the data elements that have not
          // been computed in the division algorithm.
          std::fill(values.begin() + (m + 1U), values.end(), limb_type(0U));

          if(remainder != nullptr)
          {
            if(d == 1U)
            {
              std::copy(uu.cbegin(),
                        uu.cbegin() + (number_of_limbs - v_offset),
                        remainder->values.begin());
            }
            else
            {
              limb_type previous_u = limb_type(0U);

              for(std::int_fast32_t rl = std::int_fast32_t(n - 1U), ul = std::int_fast32_t(number_of_limbs - (v_offset + 1U)); rl >= 0; --rl, --ul)
              {
                const double_limb_type t =
                  double_limb_type(  uu[std::uint_fast32_t(ul)]
                                   + double_limb_type(double_limb_type(previous_u) << std::numeric_limits<limb_type>::digits));

                remainder->values[std::uint_fast32_t(rl)] = limb_type(double_limb_type(t / d));
                previous_u                                = limb_type(double_limb_type(t - double_limb_type(double_limb_type(d) * remainder->values[std::uint_fast32_t(rl)])));
              }
            }

            std::fill(remainder->values.begin() + n,
                      remainder->values.end(),
                      limb_type(0U));
          }

          if(bNegQuot) { negate(); }
          if(bNegRem && remainder != nullptr)  { remainder->negate(); }
        }
      }
    }

    WIDE_INTEGER_CONSTEXPR void shl(const std::uint_fast32_t offset,
                                    const std::uint_fast16_t left_shift_amount)
    {
      if(offset > 0U)
      {
        std::copy_backward(values.data(),
                           values.data() + (number_of_limbs - offset),
                           values.data() +  number_of_limbs);

        std::fill(values.begin(), values.begin() + offset, limb_type(0U));
      }

      using local_integral_type = std::uint_fast32_t;

      if(left_shift_amount != local_integral_type(0U))
      {
        limb_type part_from_previous_value = limb_type(0U);

        for(std::uint_fast32_t i = offset; i < number_of_limbs; ++i)
        {
          const limb_type t = values[i];

          values[i] = limb_type(limb_type(t << local_integral_type(left_shift_amount)) | part_from_previous_value);

          part_from_previous_value = limb_type(t >> local_integral_type(std::uint_fast32_t(std::numeric_limits<limb_type>::digits - left_shift_amount)));
        }
      }
    }

    WIDE_INTEGER_CONSTEXPR void shr(const std::uint_fast32_t offset,
                                    const std::uint_fast16_t right_shift_amount)
    {
      if(offset > 0U)
      {
        std::copy(values.begin() + offset,
                  values.begin() + number_of_limbs,
                  values.begin());

        std::fill(values.end() - offset,
                  values.end(),
                  (is_neg(*this) == false) ? limb_type(0U) : limb_type((std::numeric_limits<limb_type>::max)()));
      }

      using local_integral_type = std::uint_fast32_t;

      if(right_shift_amount != local_integral_type(0U))
      {
        limb_type part_from_previous_value =
          (is_neg(*this) == false)
            ? limb_type(0U)
            : limb_type((std::numeric_limits<limb_type>::max)() << std::uint_fast16_t(std::uint_fast16_t(std::numeric_limits<limb_type>::digits) - right_shift_amount));

        for(std::int_fast32_t i = std::int_fast32_t((number_of_limbs - 1U) - offset); i >= 0; --i)
        {
          const limb_type t = values[std::uint_fast32_t(i)];

          values[std::uint_fast32_t(i)] = (t >> local_integral_type(right_shift_amount)) | part_from_previous_value;

          part_from_previous_value = limb_type(t << local_integral_type(std::uint_fast32_t(std::numeric_limits<limb_type>::digits - right_shift_amount)));
        }
      }
    }

    // Read string function.
    WIDE_INTEGER_CONSTEXPR bool rd_string(const char* str_input)
    {
      std::fill(values.begin(), values.end(), limb_type(0U));

      const std::uint_fast32_t str_length = detail::strlen_unsafe(str_input);

      std::uint_fast8_t base = 10U;

      std::uint_fast32_t pos = 0U;

      // Detect: Is there a plus sign?
      // And if there is a plus sign, skip over the plus sign.
      if((str_length > 0U) && (str_input[0U] == char('+')))
      {
        ++pos;
      }

      bool str_has_neg_sign = false;

      // Detect: Is there a minus sign?
      // And if there is a minus sign, skip over the minus sign.
      if((str_length > 0U) && (str_input[0U] == char('-')))
      {
        str_has_neg_sign = true;

        ++pos;
      }

      // Perform a dynamic detection of the base.
      if(str_length > (pos + 0U))
      {
        const bool might_be_oct_or_hex = ((str_input[pos + 0U] == char('0')) && (str_length > (pos + 1U)));

        if(might_be_oct_or_hex)
        {
          if((str_input[pos + 1U] >= char('0')) && (str_input[pos + 1U] <= char('8')))
          {
            // The input format is octal.
            base = 8U;

            pos += 1U;
          }
          else if((str_input[pos + 1U] == char('x')) || (str_input[pos + 1U] == char('X')))
          {
            // The input format is hexadecimal.
            base = 16U;

            pos += 2U;
          }
        }
        else if((str_input[pos + 0U] >= char('0')) && (str_input[pos + 0U] <= char('9')))
        {
          // The input format is decimal.
          ;
        }
      }

      bool char_is_valid = true;

      for( ; ((pos < str_length) && char_is_valid); ++pos)
      {
        std::uint8_t c = std::uint8_t(str_input[pos]);

        const bool char_is_apostrophe = (c == char(39));

        if(char_is_apostrophe == false)
        {
          if(base == 8U)
          {
            if  ((c >= char('0')) && (c <= char('8'))) { c = std::uint8_t(c - std::uint8_t(0x30U)); }
            else                                       { char_is_valid = false; }

            if(char_is_valid)
            {
              operator<<=(3);

              values[0U] |= std::uint8_t(c);
            }
          }
          else if(base == 10U)
          {
            if   ((c >= std::uint8_t('0')) && (c <= std::uint8_t('9'))) { c = std::uint8_t(c - std::uint8_t(0x30U)); }
            else                                                        { char_is_valid = false; }

            if(char_is_valid)
            {
              mul_by_limb(10U);

              operator+=(c);
            }
          }
          else if(base == 16U)
          {
            if     ((c >= std::uint8_t('a')) && (c <= std::uint8_t('f'))) { c = std::uint8_t(c - std::uint8_t(  87U)); }
            else if((c >= std::uint8_t('A')) && (c <= std::uint8_t('F'))) { c = std::uint8_t(c - std::uint8_t(  55U)); }
            else if((c >= std::uint8_t('0')) && (c <= std::uint8_t('9'))) { c = std::uint8_t(c - std::uint8_t(0x30U)); }
            else                                                          { char_is_valid = false; }

            if(char_is_valid)
            {
              operator<<=(4);

              values[0U] |= c;
            }
          }
        }
      }

      if(str_has_neg_sign)
      {
        negate();
      }

      return char_is_valid;
    }

    WIDE_INTEGER_CONSTEXPR void bitwise_not()
    {
      for(std::uint_fast32_t i = 0U; i < number_of_limbs; ++i)
      {
        values[i] = limb_type(~values[i]);
      }
    }

    WIDE_INTEGER_CONSTEXPR void preincrement()
    {
      // Implement pre-increment.
      std::uint_fast32_t i = 0U;

      for( ; (i < std::uint_fast32_t(values.size() - 1U)) && (++values[i] == limb_type(0U)); ++i)
      {
        ;
      }

      if(i == std::uint_fast32_t(values.size() - 1U))
      {
        ++values[i];
      }
    }

    WIDE_INTEGER_CONSTEXPR void predecrement()
    {
      // Implement pre-decrement.
      std::uint_fast32_t i = 0U;

      for( ; (i < std::uint_fast32_t(values.size() - 1U)) && (values[i]-- == limb_type(0U)); ++i)
      {
        ;
      }

      if(i == std::uint_fast32_t(values.size() - 1U))
      {
        --values[i];
      }
    }
  };

  // Define some convenient unsigned wide integer types.
  using uint64_t    = uintwide_t<   64U, std::uint16_t>;
  using uint128_t   = uintwide_t<  128U, std::uint32_t>;
  using uint256_t   = uintwide_t<  256U, std::uint32_t>;
  using uint512_t   = uintwide_t<  512U, std::uint32_t>;
  using uint1024_t  = uintwide_t< 1024U, std::uint32_t>;
  using uint2048_t  = uintwide_t< 2048U, std::uint32_t>;
  using uint4096_t  = uintwide_t< 4096U, std::uint32_t>;
  using uint8192_t  = uintwide_t< 8192U, std::uint32_t>;
  using uint16384_t = uintwide_t<16384U, std::uint32_t>;
  using uint32768_t = uintwide_t<32768U, std::uint32_t>;

  using  int64_t    = uintwide_t<   64U, std::uint16_t, void, true>;
  using  int128_t   = uintwide_t<  128U, std::uint32_t, void, true>;
  using  int256_t   = uintwide_t<  256U, std::uint32_t, void, true>;
  using  int512_t   = uintwide_t<  512U, std::uint32_t, void, true>;
  using  int1024_t  = uintwide_t< 1024U, std::uint32_t, void, true>;
  using  int2048_t  = uintwide_t< 2048U, std::uint32_t, void, true>;
  using  int4096_t  = uintwide_t< 4096U, std::uint32_t, void, true>;
  using  int8192_t  = uintwide_t< 8192U, std::uint32_t, void, true>;
  using  int16384_t = uintwide_t<16384U, std::uint32_t, void, true>;
  using  int32768_t = uintwide_t<32768U, std::uint32_t, void, true>;

  // Insert a base class for numeric_limits<> support.
  // This class inherits from std::numeric_limits<unsigned int>
  // in order to provide limits for a non-specific unsigned type.

  template<const size_t Width2,
           typename LimbType,
           typename AllocatorType,
           const bool IsSigned>
  class numeric_limits_uintwide_t_base
    : public std::numeric_limits<typename std::conditional<IsSigned == false, unsigned int, signed int>::type>
  {
  private:
    using local_wide_integer_type = uintwide_t<Width2, LimbType, AllocatorType, IsSigned>;

  public:
    static constexpr int digits          = (IsSigned == false)
                                             ? static_cast<int>(local_wide_integer_type::my_width2)
                                             : static_cast<int>(local_wide_integer_type::my_width2 - 1U);

    static constexpr int digits10        = static_cast<int>((std::uintmax_t(digits)       * UINTMAX_C(75257499)) / UINTMAX_C(250000000));
    static constexpr int max_digits10    = digits10;
    static constexpr int max_exponent    = digits;
    static constexpr int max_exponent10  = static_cast<int>((std::uintmax_t(max_exponent) * UINTMAX_C(75257499)) / UINTMAX_C(250000000));

    static constexpr local_wide_integer_type (max)() { return local_wide_integer_type::limits_helper_max(IsSigned); }
    static constexpr local_wide_integer_type (min)() { return local_wide_integer_type::limits_helper_min(IsSigned); }
  };

  template<class T>
  struct is_integral : public std::is_integral<T> { };

  template<const size_t Width2,
           typename LimbType,
           typename AllocatorType,
           const bool IsSigned>
  struct is_integral<math::wide_integer::uintwide_t<Width2, LimbType, AllocatorType, IsSigned>>
    : public std::integral_constant<bool, true> { };

  } } // namespace math::wide_integer

  namespace std
  {
    // Specialization of std::numeric_limits<uintwide_t>.
    template<const math::wide_integer::size_t Width2,
             typename LimbType,
             typename AllocatorType,
             const bool IsSigned>
    class numeric_limits<math::wide_integer::uintwide_t<Width2, LimbType, AllocatorType, IsSigned>>
      : public math::wide_integer::numeric_limits_uintwide_t_base<Width2, LimbType, AllocatorType, IsSigned> { };
  }

  namespace math { namespace wide_integer {

  // Non-member binary add, sub, mul, div, mod of (uintwide_t op uintwide_t).
  template<const size_t Width2, typename LimbType, typename AllocatorType, const bool IsSigned> constexpr uintwide_t<Width2, LimbType, AllocatorType, IsSigned> operator+ (const uintwide_t<Width2, LimbType, AllocatorType, IsSigned>& left, const uintwide_t<Width2, LimbType, AllocatorType, IsSigned>& right) { return uintwide_t<Width2, LimbType, AllocatorType, IsSigned>(left).operator+=(right); }
  template<const size_t Width2, typename LimbType, typename AllocatorType, const bool IsSigned> constexpr uintwide_t<Width2, LimbType, AllocatorType, IsSigned> operator- (const uintwide_t<Width2, LimbType, AllocatorType, IsSigned>& left, const uintwide_t<Width2, LimbType, AllocatorType, IsSigned>& right) { return uintwide_t<Width2, LimbType, AllocatorType, IsSigned>(left).operator-=(right); }
  template<const size_t Width2, typename LimbType, typename AllocatorType, const bool IsSigned> constexpr uintwide_t<Width2, LimbType, AllocatorType, IsSigned> operator* (const uintwide_t<Width2, LimbType, AllocatorType, IsSigned>& left, const uintwide_t<Width2, LimbType, AllocatorType, IsSigned>& right) { return uintwide_t<Width2, LimbType, AllocatorType, IsSigned>(left).operator*=(right); }
  template<const size_t Width2, typename LimbType, typename AllocatorType, const bool IsSigned> constexpr uintwide_t<Width2, LimbType, AllocatorType, IsSigned> operator/ (const uintwide_t<Width2, LimbType, AllocatorType, IsSigned>& left, const uintwide_t<Width2, LimbType, AllocatorType, IsSigned>& right) { return uintwide_t<Width2, LimbType, AllocatorType, IsSigned>(left).operator/=(right); }
  template<const size_t Width2, typename LimbType, typename AllocatorType, const bool IsSigned> constexpr uintwide_t<Width2, LimbType, AllocatorType, IsSigned> operator% (const uintwide_t<Width2, LimbType, AllocatorType, IsSigned>& left, const uintwide_t<Width2, LimbType, AllocatorType, IsSigned>& right) { return uintwide_t<Width2, LimbType, AllocatorType, IsSigned>(left).operator%=(right); }

  // Non-member binary logic operations of (uintwide_t op uintwide_t).
  template<const size_t Width2, typename LimbType, typename AllocatorType, const bool IsSigned> constexpr uintwide_t<Width2, LimbType, AllocatorType, IsSigned> operator| (const uintwide_t<Width2, LimbType, AllocatorType, IsSigned>& left, const uintwide_t<Width2, LimbType, AllocatorType, IsSigned>& right) { return uintwide_t<Width2, LimbType, AllocatorType, IsSigned>(left).operator|=(right); }
  template<const size_t Width2, typename LimbType, typename AllocatorType, const bool IsSigned> constexpr uintwide_t<Width2, LimbType, AllocatorType, IsSigned> operator^ (const uintwide_t<Width2, LimbType, AllocatorType, IsSigned>& left, const uintwide_t<Width2, LimbType, AllocatorType, IsSigned>& right) { return uintwide_t<Width2, LimbType, AllocatorType, IsSigned>(left).operator^=(right); }
  template<const size_t Width2, typename LimbType, typename AllocatorType, const bool IsSigned> constexpr uintwide_t<Width2, LimbType, AllocatorType, IsSigned> operator& (const uintwide_t<Width2, LimbType, AllocatorType, IsSigned>& left, const uintwide_t<Width2, LimbType, AllocatorType, IsSigned>& right) { return uintwide_t<Width2, LimbType, AllocatorType, IsSigned>(left).operator&=(right); }

  // Non-member binary add, sub, mul, div, mod of (uintwide_t op IntegralType).
  template<typename IntegralType, const size_t Width2, typename LimbType, typename AllocatorType, const bool IsSigned> constexpr typename std::enable_if<((std::is_fundamental<IntegralType>::value == true) && (std::is_integral<IntegralType>::value == true)), uintwide_t<Width2, LimbType, AllocatorType, IsSigned>>::type operator+(const uintwide_t<Width2, LimbType, AllocatorType, IsSigned>& u, const IntegralType& v) { return uintwide_t<Width2, LimbType, AllocatorType, IsSigned>(u).operator+=(uintwide_t<Width2, LimbType, AllocatorType, IsSigned>(v)); }
  template<typename IntegralType, const size_t Width2, typename LimbType, typename AllocatorType, const bool IsSigned> constexpr typename std::enable_if<((std::is_fundamental<IntegralType>::value == true) && (std::is_integral<IntegralType>::value == true)), uintwide_t<Width2, LimbType, AllocatorType, IsSigned>>::type operator-(const uintwide_t<Width2, LimbType, AllocatorType, IsSigned>& u, const IntegralType& v) { return uintwide_t<Width2, LimbType, AllocatorType, IsSigned>(u).operator-=(uintwide_t<Width2, LimbType, AllocatorType, IsSigned>(v)); }
  template<typename IntegralType, const size_t Width2, typename LimbType, typename AllocatorType, const bool IsSigned> constexpr typename std::enable_if<((std::is_fundamental<IntegralType>::value == true) && (std::is_integral<IntegralType>::value == true)), uintwide_t<Width2, LimbType, AllocatorType, IsSigned>>::type operator*(const uintwide_t<Width2, LimbType, AllocatorType, IsSigned>& u, const IntegralType& v) { return uintwide_t<Width2, LimbType, AllocatorType, IsSigned>(u).operator*=(uintwide_t<Width2, LimbType, AllocatorType, IsSigned>(v)); }
  template<typename IntegralType, const size_t Width2, typename LimbType, typename AllocatorType, const bool IsSigned> constexpr typename std::enable_if<((std::is_fundamental<IntegralType>::value == true) && (std::is_integral<IntegralType>::value == true)), uintwide_t<Width2, LimbType, AllocatorType, IsSigned>>::type operator/(const uintwide_t<Width2, LimbType, AllocatorType, IsSigned>& u, const IntegralType& v) { return uintwide_t<Width2, LimbType, AllocatorType, IsSigned>(u).operator/=(uintwide_t<Width2, LimbType, AllocatorType, IsSigned>(v)); }

  template<typename IntegralType, const size_t Width2, typename LimbType, typename AllocatorType, const bool IsSigned>
  constexpr typename std::enable_if<(   (std::is_fundamental<IntegralType>::value == true)
                                     && (std::is_integral   <IntegralType>::value == true)
                                     && (std::is_unsigned   <IntegralType>::value == false)), uintwide_t<Width2, LimbType, AllocatorType, IsSigned>>::type
  operator%(const uintwide_t<Width2, LimbType, AllocatorType, IsSigned>& u, const IntegralType& v) { return uintwide_t<Width2, LimbType, AllocatorType, IsSigned>(u).operator%=(uintwide_t<Width2, LimbType, AllocatorType, IsSigned>(v)); }

  template<typename IntegralType, const size_t Width2, typename LimbType, typename AllocatorType, const bool IsSigned>
  WIDE_INTEGER_CONSTEXPR typename std::enable_if<(   (std::is_fundamental<IntegralType>::value == true)
                                                  && (std::is_integral   <IntegralType>::value == true)
                                                  && (std::is_unsigned   <IntegralType>::value == true)
                                                  && (std::numeric_limits<IntegralType>::digits <= std::numeric_limits<LimbType>::digits)), typename uintwide_t<Width2, LimbType, AllocatorType, IsSigned>::limb_type>::type
  operator%(const uintwide_t<Width2, LimbType, AllocatorType, IsSigned>& u, const IntegralType& v)
  {
    const bool u_is_neg = uintwide_t<Width2, LimbType, AllocatorType, IsSigned>::is_neg(u);

    uintwide_t<Width2, LimbType, AllocatorType, IsSigned> remainder;

    uintwide_t<Width2, LimbType, AllocatorType, IsSigned>
    (
      (u_is_neg == false) ? u : -u
    ).eval_divide_by_single_limb(v, 0U, &remainder);

    using local_limb_type = typename uintwide_t<Width2, LimbType, AllocatorType, IsSigned>::limb_type;

    local_limb_type u_rem = (local_limb_type) remainder;

    return ((u_is_neg == false) ? u_rem : local_limb_type(~local_limb_type(u_rem) + 1U));
  }

  template<typename IntegralType, const size_t Width2, typename LimbType, typename AllocatorType, const bool IsSigned>
  constexpr typename std::enable_if<(   (std::is_fundamental<IntegralType>::value == true)
                                     && (std::is_integral   <IntegralType>::value == true)
                                     && (std::is_unsigned   <IntegralType>::value == true)
                                     && (std::numeric_limits<IntegralType>::digits > std::numeric_limits<LimbType>::digits)), uintwide_t<Width2, LimbType, AllocatorType, IsSigned>>::type
  operator%(const uintwide_t<Width2, LimbType, AllocatorType, IsSigned>& u, const IntegralType& v) { return uintwide_t<Width2, LimbType, AllocatorType, IsSigned>(u).operator%=(uintwide_t<Width2, LimbType, AllocatorType, IsSigned>(v)); }

  // Non-member binary add, sub, mul, div, mod of (IntegralType op uintwide_t).
  template<typename IntegralType, const size_t Width2, typename LimbType, typename AllocatorType, const bool IsSigned> constexpr typename std::enable_if<((std::is_fundamental<IntegralType>::value == true) && (std::is_integral<IntegralType>::value == true)), uintwide_t<Width2, LimbType, AllocatorType, IsSigned>>::type operator+(const IntegralType& u, const uintwide_t<Width2, LimbType, AllocatorType, IsSigned>& v) { return uintwide_t<Width2, LimbType, AllocatorType, IsSigned>(u).operator+=(v); }
  template<typename IntegralType, const size_t Width2, typename LimbType, typename AllocatorType, const bool IsSigned> constexpr typename std::enable_if<((std::is_fundamental<IntegralType>::value == true) && (std::is_integral<IntegralType>::value == true)), uintwide_t<Width2, LimbType, AllocatorType, IsSigned>>::type operator-(const IntegralType& u, const uintwide_t<Width2, LimbType, AllocatorType, IsSigned>& v) { return uintwide_t<Width2, LimbType, AllocatorType, IsSigned>(u).operator-=(v); }
  template<typename IntegralType, const size_t Width2, typename LimbType, typename AllocatorType, const bool IsSigned> constexpr typename std::enable_if<((std::is_fundamental<IntegralType>::value == true) && (std::is_integral<IntegralType>::value == true)), uintwide_t<Width2, LimbType, AllocatorType, IsSigned>>::type operator*(const IntegralType& u, const uintwide_t<Width2, LimbType, AllocatorType, IsSigned>& v) { return uintwide_t<Width2, LimbType, AllocatorType, IsSigned>(u).operator*=(v); }
  template<typename IntegralType, const size_t Width2, typename LimbType, typename AllocatorType, const bool IsSigned> constexpr typename std::enable_if<((std::is_fundamental<IntegralType>::value == true) && (std::is_integral<IntegralType>::value == true)), uintwide_t<Width2, LimbType, AllocatorType, IsSigned>>::type operator/(const IntegralType& u, const uintwide_t<Width2, LimbType, AllocatorType, IsSigned>& v) { return uintwide_t<Width2, LimbType, AllocatorType, IsSigned>(u).operator/=(v); }
  template<typename IntegralType, const size_t Width2, typename LimbType, typename AllocatorType, const bool IsSigned> constexpr typename std::enable_if<((std::is_fundamental<IntegralType>::value == true) && (std::is_integral<IntegralType>::value == true)), uintwide_t<Width2, LimbType, AllocatorType, IsSigned>>::type operator%(const IntegralType& u, const uintwide_t<Width2, LimbType, AllocatorType, IsSigned>& v) { return uintwide_t<Width2, LimbType, AllocatorType, IsSigned>(u).operator%=(v); }

  #if !defined(WIDE_INTEGER_DISABLE_FLOAT_INTEROP)
  // Non-member binary add, sub, mul, div, mod of (uintwide_t op FloatingPointType).
  template<typename FloatingPointType, const size_t Width2, typename LimbType, typename AllocatorType, const bool IsSigned> constexpr typename std::enable_if<((std::is_fundamental<FloatingPointType>::value == true) && (std::is_floating_point<FloatingPointType>::value == true)), uintwide_t<Width2, LimbType, AllocatorType, IsSigned>>::type operator+(const uintwide_t<Width2, LimbType, AllocatorType, IsSigned>& u, const FloatingPointType& f) { return uintwide_t<Width2, LimbType, AllocatorType, IsSigned>(u).operator+=(uintwide_t<Width2, LimbType, AllocatorType, IsSigned>(f)); }
  template<typename FloatingPointType, const size_t Width2, typename LimbType, typename AllocatorType, const bool IsSigned> constexpr typename std::enable_if<((std::is_fundamental<FloatingPointType>::value == true) && (std::is_floating_point<FloatingPointType>::value == true)), uintwide_t<Width2, LimbType, AllocatorType, IsSigned>>::type operator-(const uintwide_t<Width2, LimbType, AllocatorType, IsSigned>& u, const FloatingPointType& f) { return uintwide_t<Width2, LimbType, AllocatorType, IsSigned>(u).operator-=(uintwide_t<Width2, LimbType, AllocatorType, IsSigned>(f)); }
  template<typename FloatingPointType, const size_t Width2, typename LimbType, typename AllocatorType, const bool IsSigned> constexpr typename std::enable_if<((std::is_fundamental<FloatingPointType>::value == true) && (std::is_floating_point<FloatingPointType>::value == true)), uintwide_t<Width2, LimbType, AllocatorType, IsSigned>>::type operator*(const uintwide_t<Width2, LimbType, AllocatorType, IsSigned>& u, const FloatingPointType& f) { return uintwide_t<Width2, LimbType, AllocatorType, IsSigned>(u).operator*=(uintwide_t<Width2, LimbType, AllocatorType, IsSigned>(f)); }
  template<typename FloatingPointType, const size_t Width2, typename LimbType, typename AllocatorType, const bool IsSigned> constexpr typename std::enable_if<((std::is_fundamental<FloatingPointType>::value == true) && (std::is_floating_point<FloatingPointType>::value == true)), uintwide_t<Width2, LimbType, AllocatorType, IsSigned>>::type operator/(const uintwide_t<Width2, LimbType, AllocatorType, IsSigned>& u, const FloatingPointType& f) { return uintwide_t<Width2, LimbType, AllocatorType, IsSigned>(u).operator/=(uintwide_t<Width2, LimbType, AllocatorType, IsSigned>(f)); }
  template<typename FloatingPointType, const size_t Width2, typename LimbType, typename AllocatorType, const bool IsSigned> constexpr typename std::enable_if<((std::is_fundamental<FloatingPointType>::value == true) && (std::is_floating_point<FloatingPointType>::value == true)), uintwide_t<Width2, LimbType, AllocatorType, IsSigned>>::type operator%(const uintwide_t<Width2, LimbType, AllocatorType, IsSigned>& u, const FloatingPointType& f) { return uintwide_t<Width2, LimbType, AllocatorType, IsSigned>(u).operator%=(uintwide_t<Width2, LimbType, AllocatorType, IsSigned>(f)); }

  // Non-member binary add, sub, mul, div, mod of (FloatingPointType op uintwide_t).
  template<typename FloatingPointType, const size_t Width2, typename LimbType, typename AllocatorType, const bool IsSigned> constexpr typename std::enable_if<((std::is_fundamental<FloatingPointType>::value == true) && (std::is_floating_point<FloatingPointType>::value == true)), uintwide_t<Width2, LimbType, AllocatorType, IsSigned>>::type operator+(const FloatingPointType& f, const uintwide_t<Width2, LimbType, AllocatorType, IsSigned>& v) { return uintwide_t<Width2, LimbType, AllocatorType, IsSigned>(f).operator+=(v); }
  template<typename FloatingPointType, const size_t Width2, typename LimbType, typename AllocatorType, const bool IsSigned> constexpr typename std::enable_if<((std::is_fundamental<FloatingPointType>::value == true) && (std::is_floating_point<FloatingPointType>::value == true)), uintwide_t<Width2, LimbType, AllocatorType, IsSigned>>::type operator-(const FloatingPointType& f, const uintwide_t<Width2, LimbType, AllocatorType, IsSigned>& v) { return uintwide_t<Width2, LimbType, AllocatorType, IsSigned>(f).operator-=(v); }
  template<typename FloatingPointType, const size_t Width2, typename LimbType, typename AllocatorType, const bool IsSigned> constexpr typename std::enable_if<((std::is_fundamental<FloatingPointType>::value == true) && (std::is_floating_point<FloatingPointType>::value == true)), uintwide_t<Width2, LimbType, AllocatorType, IsSigned>>::type operator*(const FloatingPointType& f, const uintwide_t<Width2, LimbType, AllocatorType, IsSigned>& v) { return uintwide_t<Width2, LimbType, AllocatorType, IsSigned>(f).operator*=(v); }
  template<typename FloatingPointType, const size_t Width2, typename LimbType, typename AllocatorType, const bool IsSigned> constexpr typename std::enable_if<((std::is_fundamental<FloatingPointType>::value == true) && (std::is_floating_point<FloatingPointType>::value == true)), uintwide_t<Width2, LimbType, AllocatorType, IsSigned>>::type operator/(const FloatingPointType& f, const uintwide_t<Width2, LimbType, AllocatorType, IsSigned>& v) { return uintwide_t<Width2, LimbType, AllocatorType, IsSigned>(f).operator/=(v); }
  template<typename FloatingPointType, const size_t Width2, typename LimbType, typename AllocatorType, const bool IsSigned> constexpr typename std::enable_if<((std::is_fundamental<FloatingPointType>::value == true) && (std::is_floating_point<FloatingPointType>::value == true)), uintwide_t<Width2, LimbType, AllocatorType, IsSigned>>::type operator%(const FloatingPointType& f, const uintwide_t<Width2, LimbType, AllocatorType, IsSigned>& v) { return uintwide_t<Width2, LimbType, AllocatorType, IsSigned>(f).operator%=(v); }
  #endif

  // Non-member binary logic operations of (uintwide_t op IntegralType).
  template<typename IntegralType, const size_t Width2, typename LimbType, typename AllocatorType, const bool IsSigned> constexpr typename std::enable_if<((std::is_fundamental<IntegralType>::value == true) && (std::is_integral<IntegralType>::value == true)), uintwide_t<Width2, LimbType, AllocatorType, IsSigned>>::type operator|(const uintwide_t<Width2, LimbType, AllocatorType, IsSigned>& u, const IntegralType& v) { return uintwide_t<Width2, LimbType, AllocatorType, IsSigned>(u).operator|=(uintwide_t<Width2, LimbType, AllocatorType, IsSigned>(v)); }
  template<typename IntegralType, const size_t Width2, typename LimbType, typename AllocatorType, const bool IsSigned> constexpr typename std::enable_if<((std::is_fundamental<IntegralType>::value == true) && (std::is_integral<IntegralType>::value == true)), uintwide_t<Width2, LimbType, AllocatorType, IsSigned>>::type operator^(const uintwide_t<Width2, LimbType, AllocatorType, IsSigned>& u, const IntegralType& v) { return uintwide_t<Width2, LimbType, AllocatorType, IsSigned>(u).operator^=(uintwide_t<Width2, LimbType, AllocatorType, IsSigned>(v)); }
  template<typename IntegralType, const size_t Width2, typename LimbType, typename AllocatorType, const bool IsSigned> constexpr typename std::enable_if<((std::is_fundamental<IntegralType>::value == true) && (std::is_integral<IntegralType>::value == true)), uintwide_t<Width2, LimbType, AllocatorType, IsSigned>>::type operator&(const uintwide_t<Width2, LimbType, AllocatorType, IsSigned>& u, const IntegralType& v) { return uintwide_t<Width2, LimbType, AllocatorType, IsSigned>(u).operator&=(uintwide_t<Width2, LimbType, AllocatorType, IsSigned>(v)); }

  // Non-member binary binary logic operations of (IntegralType op uintwide_t).
  template<typename IntegralType, const size_t Width2, typename LimbType, typename AllocatorType, const bool IsSigned> constexpr typename std::enable_if<((std::is_fundamental<IntegralType>::value == true) && (std::is_integral<IntegralType>::value == true)), uintwide_t<Width2, LimbType, AllocatorType, IsSigned>>::type operator|(const IntegralType& u, const uintwide_t<Width2, LimbType, AllocatorType, IsSigned>& v) { return uintwide_t<Width2, LimbType, AllocatorType, IsSigned>(u).operator|=(v); }
  template<typename IntegralType, const size_t Width2, typename LimbType, typename AllocatorType, const bool IsSigned> constexpr typename std::enable_if<((std::is_fundamental<IntegralType>::value == true) && (std::is_integral<IntegralType>::value == true)), uintwide_t<Width2, LimbType, AllocatorType, IsSigned>>::type operator^(const IntegralType& u, const uintwide_t<Width2, LimbType, AllocatorType, IsSigned>& v) { return uintwide_t<Width2, LimbType, AllocatorType, IsSigned>(u).operator^=(v); }
  template<typename IntegralType, const size_t Width2, typename LimbType, typename AllocatorType, const bool IsSigned> constexpr typename std::enable_if<((std::is_fundamental<IntegralType>::value == true) && (std::is_integral<IntegralType>::value == true)), uintwide_t<Width2, LimbType, AllocatorType, IsSigned>>::type operator&(const IntegralType& u, const uintwide_t<Width2, LimbType, AllocatorType, IsSigned>& v) { return uintwide_t<Width2, LimbType, AllocatorType, IsSigned>(u).operator&=(v); }

  // Non-member shift functions of (uintwide_t shift IntegralType).
  template<typename IntegralType, const size_t Width2, typename LimbType, typename AllocatorType, const bool IsSigned> constexpr typename std::enable_if<((std::is_fundamental<IntegralType>::value == true) && (std::is_integral<IntegralType>::value == true)), uintwide_t<Width2, LimbType, AllocatorType, IsSigned>>::type operator<<(const uintwide_t<Width2, LimbType, AllocatorType, IsSigned>& u, const IntegralType n) { return uintwide_t<Width2, LimbType, AllocatorType, IsSigned>(u).operator<<=(n); }
  template<typename IntegralType, const size_t Width2, typename LimbType, typename AllocatorType, const bool IsSigned> constexpr typename std::enable_if<((std::is_fundamental<IntegralType>::value == true) && (std::is_integral<IntegralType>::value == true)), uintwide_t<Width2, LimbType, AllocatorType, IsSigned>>::type operator>>(const uintwide_t<Width2, LimbType, AllocatorType, IsSigned>& u, const IntegralType n) { return uintwide_t<Width2, LimbType, AllocatorType, IsSigned>(u).operator>>=(n); }

  // Non-member comparison functions of (uintwide_t cmp uintwide_t).
  template<const size_t Width2, typename LimbType, typename AllocatorType, const bool IsSigned> constexpr bool operator==(const uintwide_t<Width2, LimbType, AllocatorType, IsSigned>& u, const uintwide_t<Width2, LimbType, AllocatorType, IsSigned>& v) { return u.operator==(v); }
  template<const size_t Width2, typename LimbType, typename AllocatorType, const bool IsSigned> constexpr bool operator!=(const uintwide_t<Width2, LimbType, AllocatorType, IsSigned>& u, const uintwide_t<Width2, LimbType, AllocatorType, IsSigned>& v) { return u.operator!=(v); }
  template<const size_t Width2, typename LimbType, typename AllocatorType, const bool IsSigned> constexpr bool operator> (const uintwide_t<Width2, LimbType, AllocatorType, IsSigned>& u, const uintwide_t<Width2, LimbType, AllocatorType, IsSigned>& v) { return u.operator> (v); }
  template<const size_t Width2, typename LimbType, typename AllocatorType, const bool IsSigned> constexpr bool operator< (const uintwide_t<Width2, LimbType, AllocatorType, IsSigned>& u, const uintwide_t<Width2, LimbType, AllocatorType, IsSigned>& v) { return u.operator< (v); }
  template<const size_t Width2, typename LimbType, typename AllocatorType, const bool IsSigned> constexpr bool operator>=(const uintwide_t<Width2, LimbType, AllocatorType, IsSigned>& u, const uintwide_t<Width2, LimbType, AllocatorType, IsSigned>& v) { return u.operator>=(v); }
  template<const size_t Width2, typename LimbType, typename AllocatorType, const bool IsSigned> constexpr bool operator<=(const uintwide_t<Width2, LimbType, AllocatorType, IsSigned>& u, const uintwide_t<Width2, LimbType, AllocatorType, IsSigned>& v) { return u.operator<=(v); }

  // Non-member comparison functions of (uintwide_t cmp IntegralType).
  template<typename IntegralType, const size_t Width2, typename LimbType, typename AllocatorType, const bool IsSigned> constexpr typename std::enable_if<((std::is_fundamental<IntegralType>::value == true) && (std::is_integral<IntegralType>::value == true)), bool>::type operator==(const uintwide_t<Width2, LimbType, AllocatorType, IsSigned>& u, const IntegralType& v) { return u.operator==(uintwide_t<Width2, LimbType, AllocatorType, IsSigned>(v)); }
  template<typename IntegralType, const size_t Width2, typename LimbType, typename AllocatorType, const bool IsSigned> constexpr typename std::enable_if<((std::is_fundamental<IntegralType>::value == true) && (std::is_integral<IntegralType>::value == true)), bool>::type operator!=(const uintwide_t<Width2, LimbType, AllocatorType, IsSigned>& u, const IntegralType& v) { return u.operator!=(uintwide_t<Width2, LimbType, AllocatorType, IsSigned>(v)); }
  template<typename IntegralType, const size_t Width2, typename LimbType, typename AllocatorType, const bool IsSigned> constexpr typename std::enable_if<((std::is_fundamental<IntegralType>::value == true) && (std::is_integral<IntegralType>::value == true)), bool>::type operator> (const uintwide_t<Width2, LimbType, AllocatorType, IsSigned>& u, const IntegralType& v) { return u.operator> (uintwide_t<Width2, LimbType, AllocatorType, IsSigned>(v)); }
  template<typename IntegralType, const size_t Width2, typename LimbType, typename AllocatorType, const bool IsSigned> constexpr typename std::enable_if<((std::is_fundamental<IntegralType>::value == true) && (std::is_integral<IntegralType>::value == true)), bool>::type operator< (const uintwide_t<Width2, LimbType, AllocatorType, IsSigned>& u, const IntegralType& v) { return u.operator< (uintwide_t<Width2, LimbType, AllocatorType, IsSigned>(v)); }
  template<typename IntegralType, const size_t Width2, typename LimbType, typename AllocatorType, const bool IsSigned> constexpr typename std::enable_if<((std::is_fundamental<IntegralType>::value == true) && (std::is_integral<IntegralType>::value == true)), bool>::type operator>=(const uintwide_t<Width2, LimbType, AllocatorType, IsSigned>& u, const IntegralType& v) { return u.operator>=(uintwide_t<Width2, LimbType, AllocatorType, IsSigned>(v)); }
  template<typename IntegralType, const size_t Width2, typename LimbType, typename AllocatorType, const bool IsSigned> constexpr typename std::enable_if<((std::is_fundamental<IntegralType>::value == true) && (std::is_integral<IntegralType>::value == true)), bool>::type operator<=(const uintwide_t<Width2, LimbType, AllocatorType, IsSigned>& u, const IntegralType& v) { return u.operator<=(uintwide_t<Width2, LimbType, AllocatorType, IsSigned>(v)); }

  // Non-member comparison functions of (IntegralType cmp uintwide_t).
  template<typename IntegralType, const size_t Width2, typename LimbType, typename AllocatorType, const bool IsSigned> constexpr typename std::enable_if<((std::is_fundamental<IntegralType>::value == true) && (std::is_integral<IntegralType>::value == true)), bool>::type operator==(const IntegralType& u, const uintwide_t<Width2, LimbType, AllocatorType, IsSigned>& v) { return uintwide_t<Width2, LimbType, AllocatorType, IsSigned>(u).operator==(v); }
  template<typename IntegralType, const size_t Width2, typename LimbType, typename AllocatorType, const bool IsSigned> constexpr typename std::enable_if<((std::is_fundamental<IntegralType>::value == true) && (std::is_integral<IntegralType>::value == true)), bool>::type operator!=(const IntegralType& u, const uintwide_t<Width2, LimbType, AllocatorType, IsSigned>& v) { return uintwide_t<Width2, LimbType, AllocatorType, IsSigned>(u).operator!=(v); }
  template<typename IntegralType, const size_t Width2, typename LimbType, typename AllocatorType, const bool IsSigned> constexpr typename std::enable_if<((std::is_fundamental<IntegralType>::value == true) && (std::is_integral<IntegralType>::value == true)), bool>::type operator> (const IntegralType& u, const uintwide_t<Width2, LimbType, AllocatorType, IsSigned>& v) { return uintwide_t<Width2, LimbType, AllocatorType, IsSigned>(u).operator> (v); }
  template<typename IntegralType, const size_t Width2, typename LimbType, typename AllocatorType, const bool IsSigned> constexpr typename std::enable_if<((std::is_fundamental<IntegralType>::value == true) && (std::is_integral<IntegralType>::value == true)), bool>::type operator< (const IntegralType& u, const uintwide_t<Width2, LimbType, AllocatorType, IsSigned>& v) { return uintwide_t<Width2, LimbType, AllocatorType, IsSigned>(u).operator< (v); }
  template<typename IntegralType, const size_t Width2, typename LimbType, typename AllocatorType, const bool IsSigned> constexpr typename std::enable_if<((std::is_fundamental<IntegralType>::value == true) && (std::is_integral<IntegralType>::value == true)), bool>::type operator>=(const IntegralType& u, const uintwide_t<Width2, LimbType, AllocatorType, IsSigned>& v) { return uintwide_t<Width2, LimbType, AllocatorType, IsSigned>(u).operator>=(v); }
  template<typename IntegralType, const size_t Width2, typename LimbType, typename AllocatorType, const bool IsSigned> constexpr typename std::enable_if<((std::is_fundamental<IntegralType>::value == true) && (std::is_integral<IntegralType>::value == true)), bool>::type operator<=(const IntegralType& u, const uintwide_t<Width2, LimbType, AllocatorType, IsSigned>& v) { return uintwide_t<Width2, LimbType, AllocatorType, IsSigned>(u).operator<=(v); }

  #if !defined(WIDE_INTEGER_DISABLE_FLOAT_INTEROP)
  // Non-member comparison functions of (uintwide_t cmp FloatingPointType).
  template<typename FloatingPointType, const size_t Width2, typename LimbType, typename AllocatorType, const bool IsSigned> constexpr typename std::enable_if<((std::is_fundamental<FloatingPointType>::value == true) && (std::is_floating_point<FloatingPointType>::value == true)), bool>::type operator==(const uintwide_t<Width2, LimbType, AllocatorType, IsSigned>& u, const FloatingPointType& f) { return u.operator==(uintwide_t<Width2, LimbType, AllocatorType, IsSigned>(f)); }
  template<typename FloatingPointType, const size_t Width2, typename LimbType, typename AllocatorType, const bool IsSigned> constexpr typename std::enable_if<((std::is_fundamental<FloatingPointType>::value == true) && (std::is_floating_point<FloatingPointType>::value == true)), bool>::type operator!=(const uintwide_t<Width2, LimbType, AllocatorType, IsSigned>& u, const FloatingPointType& f) { return u.operator!=(uintwide_t<Width2, LimbType, AllocatorType, IsSigned>(f)); }
  template<typename FloatingPointType, const size_t Width2, typename LimbType, typename AllocatorType, const bool IsSigned> constexpr typename std::enable_if<((std::is_fundamental<FloatingPointType>::value == true) && (std::is_floating_point<FloatingPointType>::value == true)), bool>::type operator> (const uintwide_t<Width2, LimbType, AllocatorType, IsSigned>& u, const FloatingPointType& f) { return u.operator> (uintwide_t<Width2, LimbType, AllocatorType, IsSigned>(f)); }
  template<typename FloatingPointType, const size_t Width2, typename LimbType, typename AllocatorType, const bool IsSigned> constexpr typename std::enable_if<((std::is_fundamental<FloatingPointType>::value == true) && (std::is_floating_point<FloatingPointType>::value == true)), bool>::type operator< (const uintwide_t<Width2, LimbType, AllocatorType, IsSigned>& u, const FloatingPointType& f) { return u.operator< (uintwide_t<Width2, LimbType, AllocatorType, IsSigned>(f)); }
  template<typename FloatingPointType, const size_t Width2, typename LimbType, typename AllocatorType, const bool IsSigned> constexpr typename std::enable_if<((std::is_fundamental<FloatingPointType>::value == true) && (std::is_floating_point<FloatingPointType>::value == true)), bool>::type operator>=(const uintwide_t<Width2, LimbType, AllocatorType, IsSigned>& u, const FloatingPointType& f) { return u.operator>=(uintwide_t<Width2, LimbType, AllocatorType, IsSigned>(f)); }
  template<typename FloatingPointType, const size_t Width2, typename LimbType, typename AllocatorType, const bool IsSigned> constexpr typename std::enable_if<((std::is_fundamental<FloatingPointType>::value == true) && (std::is_floating_point<FloatingPointType>::value == true)), bool>::type operator<=(const uintwide_t<Width2, LimbType, AllocatorType, IsSigned>& u, const FloatingPointType& f) { return u.operator<=(uintwide_t<Width2, LimbType, AllocatorType, IsSigned>(f)); }

  // Non-member comparison functions of (FloatingPointType cmp uintwide_t).
  template<typename FloatingPointType, const size_t Width2, typename LimbType, typename AllocatorType, const bool IsSigned> constexpr typename std::enable_if<((std::is_fundamental<FloatingPointType>::value == true) && (std::is_floating_point<FloatingPointType>::value == true)), bool>::type operator==(const FloatingPointType& f, const uintwide_t<Width2, LimbType, AllocatorType, IsSigned>& v) { return uintwide_t<Width2, LimbType, AllocatorType, IsSigned>(f).operator==(v); }
  template<typename FloatingPointType, const size_t Width2, typename LimbType, typename AllocatorType, const bool IsSigned> constexpr typename std::enable_if<((std::is_fundamental<FloatingPointType>::value == true) && (std::is_floating_point<FloatingPointType>::value == true)), bool>::type operator!=(const FloatingPointType& f, const uintwide_t<Width2, LimbType, AllocatorType, IsSigned>& v) { return uintwide_t<Width2, LimbType, AllocatorType, IsSigned>(f).operator!=(v); }
  template<typename FloatingPointType, const size_t Width2, typename LimbType, typename AllocatorType, const bool IsSigned> constexpr typename std::enable_if<((std::is_fundamental<FloatingPointType>::value == true) && (std::is_floating_point<FloatingPointType>::value == true)), bool>::type operator> (const FloatingPointType& f, const uintwide_t<Width2, LimbType, AllocatorType, IsSigned>& v) { return uintwide_t<Width2, LimbType, AllocatorType, IsSigned>(f).operator> (v); }
  template<typename FloatingPointType, const size_t Width2, typename LimbType, typename AllocatorType, const bool IsSigned> constexpr typename std::enable_if<((std::is_fundamental<FloatingPointType>::value == true) && (std::is_floating_point<FloatingPointType>::value == true)), bool>::type operator< (const FloatingPointType& f, const uintwide_t<Width2, LimbType, AllocatorType, IsSigned>& v) { return uintwide_t<Width2, LimbType, AllocatorType, IsSigned>(f).operator< (v); }
  template<typename FloatingPointType, const size_t Width2, typename LimbType, typename AllocatorType, const bool IsSigned> constexpr typename std::enable_if<((std::is_fundamental<FloatingPointType>::value == true) && (std::is_floating_point<FloatingPointType>::value == true)), bool>::type operator>=(const FloatingPointType& f, const uintwide_t<Width2, LimbType, AllocatorType, IsSigned>& v) { return uintwide_t<Width2, LimbType, AllocatorType, IsSigned>(f).operator>=(v); }
  template<typename FloatingPointType, const size_t Width2, typename LimbType, typename AllocatorType, const bool IsSigned> constexpr typename std::enable_if<((std::is_fundamental<FloatingPointType>::value == true) && (std::is_floating_point<FloatingPointType>::value == true)), bool>::type operator<=(const FloatingPointType& f, const uintwide_t<Width2, LimbType, AllocatorType, IsSigned>& v) { return uintwide_t<Width2, LimbType, AllocatorType, IsSigned>(f).operator<=(v); }
  #endif

  #if !defined(WIDE_INTEGER_DISABLE_IOSTREAM)

  // I/O streaming functions.
  template<typename char_type,
           typename traits_type,
           const size_t Width2,
           typename LimbType,
           typename AllocatorType,
           const bool IsSigned>
  std::basic_ostream<char_type, traits_type>&
  operator<<(std::basic_ostream<char_type, traits_type>& out,
             const uintwide_t<Width2, LimbType, AllocatorType, IsSigned>& x)
  {
    std::basic_ostringstream<char_type, traits_type> ostr;

    const std::ios::fmtflags my_flags = out.flags();

    const bool show_pos     = ((my_flags & std::ios::showpos)   == std::ios::showpos);
    const bool show_base    = ((my_flags & std::ios::showbase)  == std::ios::showbase);
    const bool is_uppercase = ((my_flags & std::ios::uppercase) == std::ios::uppercase);

    std::uint_fast8_t base_rep;

    if     ((my_flags & std::ios::oct) == std::ios::oct) { base_rep =  8U; }
    else if((my_flags & std::ios::hex) == std::ios::hex) { base_rep = 16U; }
    else                                                 { base_rep = 10U; }

    const std::uint_fast32_t field_width = std::uint_fast32_t(out.width());
    const char               fill_char   = out.fill();

    using local_wide_integer_type = uintwide_t<Width2, LimbType, AllocatorType, IsSigned>;

    if(base_rep == 8U)
    {
      char str_result[local_wide_integer_type::wr_string_max_buffer_size_oct];

      x.wr_string(str_result, base_rep, show_base, show_pos, is_uppercase, field_width, fill_char);

      static_cast<void>(ostr << str_result);
    }
    else if(base_rep == 10U)
    {
      char str_result[local_wide_integer_type::wr_string_max_buffer_size_dec];

      x.wr_string(str_result, base_rep, show_base, show_pos, is_uppercase, field_width, fill_char);

      static_cast<void>(ostr << str_result);
    }
    else if(base_rep == 16U)
    {
      char str_result[local_wide_integer_type::wr_string_max_buffer_size_hex];

      x.wr_string(str_result, base_rep, show_base, show_pos, is_uppercase, field_width, fill_char);

      static_cast<void>(ostr << str_result);
    }

    return (out << ostr.str());
  }

  template<typename char_type,
           typename traits_type,
           const size_t Width2,
           typename LimbType,
           typename AllocatorType,
           const bool IsSigned>
  std::basic_istream<char_type, traits_type>&
  operator>>(std::basic_istream<char_type, traits_type>& in,
             uintwide_t<Width2, LimbType, AllocatorType, IsSigned>& x)
  {
    std::string str_in;

    in >> str_in;

    using local_wide_integer_type = uintwide_t<Width2, LimbType, AllocatorType, IsSigned>;

    x = local_wide_integer_type(str_in.c_str());

    return in;
  }

  #endif

  } } // namespace math::wide_integer

  // Implement various number-theoretical tools.

  namespace math { namespace wide_integer {

  namespace detail {

  template<typename UnsignedIntegralType>
  inline WIDE_INTEGER_CONSTEXPR std::uint_fast32_t lsb_helper(const UnsignedIntegralType& x)
  {
    // Compile-time checks.
    static_assert((   (std::is_fundamental<UnsignedIntegralType>::value == true)
                   && (std::is_integral<UnsignedIntegralType>::value    == true)
                   && (std::is_unsigned<UnsignedIntegralType>::value    == true)),
                   "Error: Please check the characteristics of UnsignedIntegralType");

    std::uint_fast32_t result = 0U;

    UnsignedIntegralType mask(x);

    // This assumes that at least one bit is set.
    // Otherwise saturation of the index will occur.

    // Naive and basic LSB search.
    // TBD: This could be improved with a binary search
    // on the lowest bit position of the fundamental type.
    while((std::uint_fast32_t(mask) & 1U) == 0U)
    {
      mask >>= 1U;

      ++result;
    }

    return result;
  }

  template<typename UnsignedIntegralType>
  inline WIDE_INTEGER_CONSTEXPR std::uint_fast32_t msb_helper(const UnsignedIntegralType& u)
  {
    // Compile-time checks.
    static_assert((   (std::is_fundamental<UnsignedIntegralType>::value == true)
                   && (std::is_integral<UnsignedIntegralType>::value    == true)
                   && (std::is_unsigned<UnsignedIntegralType>::value    == true)),
                   "Error: Please check the characteristics of UnsignedIntegralType");

    using local_unsigned_integral_type = UnsignedIntegralType;

    std::int_fast32_t i { };

    // TBD: This could potentially be improved with a binary
    // search for the highest bit position in the type.

    for(i = std::int_fast32_t(std::numeric_limits<local_unsigned_integral_type>::digits - 1); i >= 0; --i)
    {
      if((u & UnsignedIntegralType(local_unsigned_integral_type(1U) << i)) != 0U)
      {
        break;
      }
    }

    return std::uint_fast32_t((std::max)(std::int_fast32_t(0), i));
  }

  template<>
  inline WIDE_INTEGER_CONSTEXPR std::uint_fast32_t msb_helper<std::uint32_t>(const std::uint32_t& u)
  {
    std::uint_fast32_t r(0);

    std::uint32_t x = u;

    // Use O(log2[N]) binary-halving in an unrolled loop to find the msb.
    if((x & UINT32_C(0xFFFF0000)) != UINT32_C(0)) { x = std::uint32_t(x >> 16U); r |= UINT8_C(16); }
    if((x & UINT32_C(0x0000FF00)) != UINT32_C(0)) { x = std::uint32_t(x >>  8U); r |= UINT8_C( 8); }
    if((x & UINT32_C(0x000000F0)) != UINT32_C(0)) { x = std::uint32_t(x >>  4U); r |= UINT8_C( 4); }
    if((x & UINT32_C(0x0000000C)) != UINT32_C(0)) { x = std::uint32_t(x >>  2U); r |= UINT8_C( 2); }
    if((x & UINT32_C(0x00000002)) != UINT32_C(0)) { x = std::uint32_t(x >>  1U); r |= UINT8_C( 1); }

    return std::uint_fast32_t(r);
  }

  template<>
  inline WIDE_INTEGER_CONSTEXPR std::uint_fast32_t msb_helper<std::uint16_t>(const std::uint16_t& u)
  {
    std::uint_fast32_t r(0);

    std::uint16_t x = u;

    // Use O(log2[N]) binary-halving in an unrolled loop to find the msb.
    if((x & UINT16_C(0xFF00)) != UINT16_C(0)) { x = std::uint16_t(x >> 8U); r |= UINT8_C(8); }
    if((x & UINT16_C(0x00F0)) != UINT16_C(0)) { x = std::uint16_t(x >> 4U); r |= UINT8_C(4); }
    if((x & UINT16_C(0x000C)) != UINT16_C(0)) { x = std::uint16_t(x >> 2U); r |= UINT8_C(2); }
    if((x & UINT16_C(0x0002)) != UINT16_C(0)) { x = std::uint16_t(x >> 1U); r |= UINT8_C(1); }

    return std::uint_fast32_t(r);
  }

  template<>
  inline WIDE_INTEGER_CONSTEXPR std::uint_fast32_t msb_helper<std::uint8_t>(const std::uint8_t& u)
  {
    std::uint_fast32_t r(0);

    std::uint8_t x = u;

    // Use O(log2[N]) binary-halving in an unrolled loop to find the msb.
    if((x & UINT8_C(0xF0)) != UINT8_C(0)) { x = std::uint8_t(x >> 4U); r |= UINT8_C(4); }
    if((x & UINT8_C(0x0C)) != UINT8_C(0)) { x = std::uint8_t(x >> 2U); r |= UINT8_C(2); }
    if((x & UINT8_C(0x02)) != UINT8_C(0)) { x = std::uint8_t(x >> 1U); r |= UINT8_C(1); }

    return std::uint_fast32_t(r);
  }

  }

  template<const std::uint32_t Width2,
           typename LimbType,
           typename AllocatorType,
           const bool IsSigned>
  WIDE_INTEGER_CONSTEXPR void swap(uintwide_t<Width2, LimbType, AllocatorType, IsSigned>& x,
                                   uintwide_t<Width2, LimbType, AllocatorType, IsSigned>& y)
  {
    if(&x != &y)
    {
      using local_wide_integer_type = uintwide_t<Width2, LimbType, AllocatorType, IsSigned>;

      const local_wide_integer_type tmp_x(x);

      x = y;
      y = tmp_x;
    }
  }

  template<const size_t Width2,
           typename LimbType,
           typename AllocatorType,
           const bool IsSigned>
  inline WIDE_INTEGER_CONSTEXPR std::uint_fast32_t lsb(const uintwide_t<Width2, LimbType, AllocatorType, IsSigned>& x)
  {
    // Calculate the position of the least-significant bit.
    // Use a linear search starting from the least significant limbs.

    using local_wide_integer_type   = uintwide_t<Width2, LimbType, AllocatorType, IsSigned>;
    using local_const_iterator_type = typename local_wide_integer_type::const_iterator;
    using local_value_type          = typename local_wide_integer_type::limb_type;

    std::uint_fast32_t bpos = 0U;

    for(local_const_iterator_type it = x.crepresentation().cbegin(); it != x.crepresentation().cend(); ++it)
    {
      if((*it & (std::numeric_limits<local_value_type>::max)()) != 0U)
      {
        const std::uint_fast32_t offset = std::uint_fast32_t(it - x.crepresentation().cbegin());

        bpos =   detail::lsb_helper(*it)
               + std::uint_fast32_t(std::uint_fast32_t(std::numeric_limits<local_value_type>::digits) * offset);

        break;
      }
    }

    return bpos;
  }

  template<const size_t Width2,
           typename LimbType,
           typename AllocatorType,
           const bool IsSigned>
  WIDE_INTEGER_CONSTEXPR std::uint_fast32_t msb(const uintwide_t<Width2, LimbType, AllocatorType, IsSigned>& x)
  {
    // Calculate the position of the most-significant bit.
    // Use a linear search starting from the most significant limbs.

    using local_wide_integer_type           = uintwide_t<Width2, LimbType, AllocatorType, IsSigned>;
    using local_const_reverse_iterator_type = typename local_wide_integer_type::const_reverse_iterator;
    using local_value_type                  = typename local_wide_integer_type::limb_type;

    std::uint_fast32_t bpos = 0U;

    for(local_const_reverse_iterator_type ri = x.crepresentation().crbegin(); ri != x.crepresentation().crend(); ++ri)
    {
      if((*ri & (std::numeric_limits<local_value_type>::max)()) != 0U)
      {
        const std::uint_fast32_t offset = std::uint_fast32_t((x.crepresentation().crend() - 1U) - ri);

        bpos =   detail::msb_helper(*ri)
               + std::uint_fast32_t(std::uint_fast32_t(std::numeric_limits<local_value_type>::digits) * offset);

        break;
      }
    }

    return bpos;
  }

  template<const std::uint32_t Width2,
           typename LimbType,
           typename AllocatorType,
           const bool IsSigned>
  WIDE_INTEGER_CONSTEXPR uintwide_t<Width2, LimbType, AllocatorType, IsSigned> sqrt(const uintwide_t<Width2, LimbType, AllocatorType, IsSigned>& m)
  {
    // Calculate the square root.

    using local_wide_integer_type = uintwide_t<Width2, LimbType, AllocatorType, IsSigned>;

    local_wide_integer_type s;

    if(m.is_zero() || local_wide_integer_type::is_neg(m))
    {
      s = local_wide_integer_type(std::uint_fast8_t(0U));
    }
    else
    {
      // Obtain the initial guess via algorithms
      // involving the position of the msb.
      const std::uint_fast32_t msb_pos = msb(m);

      // Obtain the initial value.
      const std::uint_fast32_t left_shift_amount =
        ((std::uint_fast32_t(msb_pos % 2U) == 0U)
          ? 1U + std::uint_fast32_t((msb_pos + 0U) / 2U)
          : 1U + std::uint_fast32_t((msb_pos + 1U) / 2U));

      local_wide_integer_type u(local_wide_integer_type(std::uint_fast8_t(1U)) << left_shift_amount);

      // Perform the iteration for the square root.
      // See Algorithm 1.13 SqrtInt, Sect. 1.5.1
      // in R.P. Brent and Paul Zimmermann, "Modern Computer Arithmetic",
      // Cambridge University Press, 2011.

      for(std::uint_fast32_t i = 0U; i < 64U; ++i)
      {
        s = u;

        u = (s + (m / s)) >> 1;

        if(u >= s)
        {
          break;
        }
      }
    }

    return s;
  }

  template<const size_t Width2,
           typename LimbType,
           typename AllocatorType,
           const bool IsSigned>
  WIDE_INTEGER_CONSTEXPR uintwide_t<Width2, LimbType, AllocatorType, IsSigned> cbrt(const uintwide_t<Width2, LimbType, AllocatorType, IsSigned>& m)
  {
    // Calculate the cube root.

    using local_wide_integer_type = uintwide_t<Width2, LimbType, AllocatorType, IsSigned>;

    local_wide_integer_type s;

    if(local_wide_integer_type::is_neg(m))
    {
      s = -cbrt(-m);
    }
    else if(m.is_zero())
    {
      s = local_wide_integer_type(std::uint_fast8_t(0U));
    }
    else
    {
      // Obtain the initial guess via algorithms
      // involving the position of the msb.
      const std::uint_fast32_t msb_pos = msb(m);

      // Obtain the initial value.
      const std::uint_fast32_t msb_pos_mod_3 = msb_pos % 3;

      const std::uint_fast32_t left_shift_amount =
        ((msb_pos_mod_3 == 0U)
          ? 1U + std::uint_fast32_t((msb_pos +                  0U ) / 3U)
          : 1U + std::uint_fast32_t((msb_pos + (3U - msb_pos_mod_3)) / 3U));

      local_wide_integer_type u(local_wide_integer_type(std::uint_fast8_t(1U)) << left_shift_amount);

      // Perform the iteration for the k'th root.
      // See Algorithm 1.14 RootInt, Sect. 1.5.2
      // in R.P. Brent and Paul Zimmermann, "Modern Computer Arithmetic",
      // Cambridge University Press, 2011.

      const std::uint_fast32_t three_minus_one(3U - 1U);

      for(std::uint_fast32_t i = 0U; i < 64U; ++i)
      {
        s = u;

        local_wide_integer_type m_over_s_pow_3_minus_one = m;

        for(std::uint_fast32_t j = 0U; j < 3U - 1U; ++j)
        {
          // Use a loop here to divide by s^(3 - 1) because
          // without a loop, s^(3 - 1) is likely to overflow.

          m_over_s_pow_3_minus_one /= s;
        }

        u = ((s * three_minus_one) + m_over_s_pow_3_minus_one) / 3U;

        if(u >= s)
        {
          break;
        }
      }
    }

    return s;
  }

  template<const size_t Width2,
           typename LimbType,
           typename AllocatorType,
           const bool IsSigned>
  WIDE_INTEGER_CONSTEXPR uintwide_t<Width2, LimbType, AllocatorType, IsSigned> rootk(const uintwide_t<Width2, LimbType, AllocatorType, IsSigned>& m,
                                                                                     const std::uint_fast8_t k)
  {
    // Calculate the k'th root.

    using local_wide_integer_type = uintwide_t<Width2, LimbType, AllocatorType, IsSigned>;

    local_wide_integer_type s;

    if(k < 2U)
    {
      s = m;
    }
    else if(k == 2U)
    {
      s = sqrt(m);
    }
    else if(k == 3U)
    {
      s = cbrt(m);
    }
    else
    {
      if(m.is_zero() || local_wide_integer_type::is_neg(m))
      {
        s = local_wide_integer_type(std::uint_fast8_t(0U));
      }
      else
      {
        // Obtain the initial guess via algorithms
        // involving the position of the msb.
        const std::uint_fast32_t msb_pos = msb(m);

        // Obtain the initial value.
        const std::uint_fast32_t msb_pos_mod_k = msb_pos % k;

        const std::uint_fast32_t left_shift_amount =
          ((msb_pos_mod_k == 0U)
            ? 1U + std::uint_fast32_t((msb_pos +                 0U ) / k)
            : 1U + std::uint_fast32_t((msb_pos + (k - msb_pos_mod_k)) / k));

        local_wide_integer_type u(local_wide_integer_type(std::uint_fast8_t(1U)) << left_shift_amount);

        // Perform the iteration for the k'th root.
        // See Algorithm 1.14 RootInt, Sect. 1.5.2
        // in R.P. Brent and Paul Zimmermann, "Modern Computer Arithmetic",
        // Cambridge University Press, 2011.

        const std::uint_fast32_t k_minus_one(k - 1U);

        for(std::uint_fast32_t i = 0U; i < 64U; ++i)
        {
          s = u;

          local_wide_integer_type m_over_s_pow_k_minus_one = m;

          for(std::uint_fast32_t j = 0U; j < k - 1U; ++j)
          {
            // Use a loop here to divide by s^(k - 1) because
            // without a loop, s^(k - 1) is likely to overflow.

            m_over_s_pow_k_minus_one /= s;
          }

          u = ((s * k_minus_one) + m_over_s_pow_k_minus_one) / k;

          if(u >= s)
          {
            break;
          }
        }
      }
    }

    return s;
  }

  template<typename OtherUnsignedIntegralTypeP,
           const size_t Width2,
           typename LimbType,
           typename AllocatorType,
           const bool IsSigned>
  WIDE_INTEGER_CONSTEXPR uintwide_t<Width2, LimbType, AllocatorType, IsSigned> pow(const uintwide_t<Width2, LimbType, AllocatorType, IsSigned>& b,
                                                                                   const OtherUnsignedIntegralTypeP&    p)
  {
    // Calculate (b ^ p).

    using local_wide_integer_type = uintwide_t<Width2, LimbType, AllocatorType, IsSigned>;
    using local_limb_type         = typename local_wide_integer_type::limb_type;

    local_wide_integer_type result;
    local_limb_type         p0(p);

    if((p0 == 0U) && (p == 0U))
    {
      result = local_wide_integer_type(std::uint8_t(1U));
    }
    else if((p0 == 1U) && (p == 1U))
    {
      result = b;
    }
    else if((p0 == 2U) && (p == 2U))
    {
      result  = b;
      result *= b;
    }
    else
    {
      result = local_wide_integer_type(std::uint8_t(1U));

      local_wide_integer_type y      (b);
      local_wide_integer_type p_local(p);

      while(((p0 = local_limb_type(p_local)) != 0U) || (p_local != 0U))
      {
        if((p0 & 1U) != 0U)
        {
          result *= y;
        }

        y *= y;

        p_local >>= 1;
      }
    }

    return result;
  }

  template<typename OtherUnsignedIntegralTypeP,
           typename OtherUnsignedIntegralTypeM,
           const size_t Width2,
           typename LimbType,
           typename AllocatorType,
           const bool IsSigned>
  WIDE_INTEGER_CONSTEXPR uintwide_t<Width2, LimbType, AllocatorType, IsSigned> powm(const uintwide_t<Width2, LimbType, AllocatorType, IsSigned>& b,
                                                                                     const OtherUnsignedIntegralTypeP& p,
                                                                                     const OtherUnsignedIntegralTypeM& m)
  {
    // Calculate (b ^ p) % m.

    using local_normal_width_type = uintwide_t<Width2, LimbType, AllocatorType, IsSigned>;
    using local_double_width_type = typename local_normal_width_type::double_width_type;
    using local_limb_type         = typename local_normal_width_type::limb_type;

          local_normal_width_type result;
          local_double_width_type y      (b);
    const local_double_width_type m_local(m);
          local_limb_type         p0     (p);

    if((p0 == 0U) && (p == 0U))
    {
      result = local_normal_width_type((m != 1U) ? std::uint8_t(1U) : std::uint8_t(0U));
    }
    else if((p0 == 1U) && (p == 1U))
    {
      result = b % m;
    }
    else if((p0 == 2U) && (p == 2U))
    {
      y *= y;
      y %= m_local;

      result = local_normal_width_type(y);
    }
    else
    {
      local_double_width_type    x      (std::uint8_t(1U));
      OtherUnsignedIntegralTypeP p_local(p);

      while(((p0 = local_limb_type(p_local)) != 0U) || (p_local != 0U))
      {
        if((p0 & 1U) != 0U)
        {
          x *= y;
          x %= m_local;
        }

        y *= y;
        y %= m_local;

        p_local >>= 1;
      }

      result = local_normal_width_type(x);
    }

    return result;
  }

  namespace detail {

  template<typename UnsignedShortType>
  WIDE_INTEGER_CONSTEXPR UnsignedShortType integer_gcd_reduce_short(UnsignedShortType u, UnsignedShortType v)
  {
    // This implementation of GCD reduction is based on an
    // adaptation of existing code from Boost.Multiprecision.

    for(;;)
    {
      if(u > v)
      {
        std::swap(u, v);
      }

      if(u == v)
      {
        break;
      }

      v  -= u;
      v >>= detail::lsb_helper(v);
    }

    return u;
  }

  template<typename UnsignedLargeType>
  WIDE_INTEGER_CONSTEXPR UnsignedLargeType integer_gcd_reduce_large(UnsignedLargeType u, UnsignedLargeType v)
  {
    // This implementation of GCD reduction is based on an
    // adaptation of existing code from Boost.Multiprecision.

    using local_ularge_type = UnsignedLargeType;
    using local_ushort_type = typename detail::uint_type_helper<std::uint32_t(std::numeric_limits<local_ularge_type>::digits / 2)>::exact_unsigned_type;

    for(;;)
    {
      if(u > v)
      {
        std::swap(u, v);
      }

      if(u == v)
      {
        break;
      }

      if(v <= local_ularge_type((std::numeric_limits<local_ushort_type>::max)()))
      {
        u = integer_gcd_reduce_short(local_ushort_type(v),
                                     local_ushort_type(u));

        break;
      }

      v -= u;

      while((local_ushort_type(v) & 1U) == 0U)
      {
        v >>= 1;
      }
    }

    return u;
  }

  }

  template<const size_t Width2,
           typename LimbType,
           typename AllocatorType,
           const bool IsSigned>
  WIDE_INTEGER_CONSTEXPR uintwide_t<Width2, LimbType, AllocatorType, IsSigned> gcd(const uintwide_t<Width2, LimbType, AllocatorType, IsSigned>& a,
                                                                                   const uintwide_t<Width2, LimbType, AllocatorType, IsSigned>& b)
  {
    // This implementation of GCD is an adaptation
    // of existing code from Boost.Multiprecision.

    using local_wide_integer_type = uintwide_t<Width2, LimbType, AllocatorType, IsSigned>;
    using local_ushort_type       = typename local_wide_integer_type::limb_type;
    using local_ularge_type       = typename local_wide_integer_type::double_limb_type;

    const bool u_is_neg = local_wide_integer_type::is_neg(a);
    const bool v_is_neg = local_wide_integer_type::is_neg(b);

    local_wide_integer_type u((u_is_neg == false) ? a : -a);
    local_wide_integer_type v((v_is_neg == false) ? b : -b);

    local_wide_integer_type result;

    if(u == v)
    {
      // This handles cases having (u = v) and also (u = v = 0).
      result = u;
    }
    else if((static_cast<local_ushort_type>(v) == 0U) && (v == 0U))
    {
      // This handles cases having (v = 0) with (u != 0).
      result = u;
    }
    else if((static_cast<local_ushort_type>(u) == 0U) && (u == 0U))
    {
      // This handles cases having (u = 0) with (v != 0).
      result = v;
    }
    else
    {
      // Now we handle cases having (u != 0) and (v != 0).

      // Let shift := lg K, where K is the greatest
      // power of 2 dividing both u and v.

      const std::uint_fast32_t u_shift = lsb(u);
      const std::uint_fast32_t v_shift = lsb(v);

      const std::uint_fast32_t left_shift_amount = (std::min)(u_shift, v_shift);

      u >>= u_shift;
      v >>= v_shift;

      for(;;)
      {
        // Now u and v are both odd, so diff(u, v) is even.
        // Let u = min(u, v), v = diff(u, v) / 2.

        if(u > v)
        {
          swap(u, v);
        }

        if(u == v)
        {
          break;
        }

        if(v <= (std::numeric_limits<local_ularge_type>::max)())
        {
          if(v <= (std::numeric_limits<local_ushort_type>::max)())
          {
            u = detail::integer_gcd_reduce_short(v.crepresentation()[0U],
                                                 u.crepresentation()[0U]);
          }
          else
          {
            const local_ularge_type v_large =
              detail::make_large(v.crepresentation()[0U],
                                 v.crepresentation()[1U]);

            const local_ularge_type u_large =
              detail::make_large(u.crepresentation()[0U],
                                 u.crepresentation()[1U]);

            u = detail::integer_gcd_reduce_large(v_large, u_large);
          }

          break;
        }

        v  -= u;
        v >>= lsb(v);
      }

      result = (u << left_shift_amount);
    }

    return ((u_is_neg == v_is_neg) ? result : -result);
  }

  template<typename UnsignedShortType>
  WIDE_INTEGER_CONSTEXPR typename std::enable_if<(   (std::is_fundamental<UnsignedShortType>::value == true)
                                                  && (std::is_integral   <UnsignedShortType>::value == true)
                                                  && (std::is_unsigned   <UnsignedShortType>::value == true)), UnsignedShortType>::type
  gcd(const UnsignedShortType& u, const UnsignedShortType& v)
  {
    UnsignedShortType result;

    if(u > v)
    {
      result = gcd(v, u);
    }
    else if(u == v)
    {
      // This handles cases having (u = v) and also (u = v = 0).
      result = u;
    }
    else if(v == 0U)
    {
      // This handles cases having (v = 0) with (u != 0).
      result = u;
    }
    else if(u == 0U)
    {
      // This handles cases having (u = 0) with (v != 0).
      result = v;
    }
    else
    {
      result = detail::integer_gcd_reduce_short(u, v);
    }

    return result;
  }

  template<const size_t Width2,
           typename LimbType,
           typename AllocatorType,
           const bool IsSigned>
  class uniform_int_distribution
  {
  public:
    using result_type = uintwide_t<Width2, LimbType, AllocatorType, IsSigned>;

    struct param_type
    {
    public:
      param_type(const result_type& a = (std::numeric_limits<result_type>::min)(),
                 const result_type& b = (std::numeric_limits<result_type>::max)())
        : param_a(a),
          param_b(b) { }

      ~param_type() = default;

      param_type(const param_type& other_params) : param_a(other_params.param_a),
                                                   param_b(other_params.param_b) { }

      param_type& operator=(const param_type& other_params)
      {
        if(this != &other_params)
        {
          param_a = other_params.param_a;
          param_b = other_params.param_b;
        }

        return *this;
      }

      constexpr result_type get_a() const { return param_a; }
      constexpr result_type get_b() const { return param_b; }

      void set_a(const result_type& a) { param_a = a; }
      void set_b(const result_type& b) { param_b = b; }

    private:
      result_type param_a;
      result_type param_b;

      friend inline constexpr bool operator==(const param_type& lhs,
                                              const param_type& rhs)
      {
        return (   (lhs.param_a == rhs.param_a)
                && (lhs.param_b == rhs.param_b));
      }

      friend inline constexpr bool operator!=(const param_type& lhs,
                                              const param_type& rhs)
      {
        return (   (lhs.param_a != rhs.param_a)
                || (lhs.param_b != rhs.param_b));
      }
    };

    uniform_int_distribution() : my_params() { }

    explicit uniform_int_distribution(const result_type& a,
                                      const result_type& b = (std::numeric_limits<result_type>::max)())
        : my_params(param_type(a, b)) { }

    explicit uniform_int_distribution(const param_type& other_params)
      : my_params(other_params) { }

    uniform_int_distribution(const uniform_int_distribution& other_distribution) = delete;

    ~uniform_int_distribution() = default;

    uniform_int_distribution& operator=(const uniform_int_distribution&) = delete;

    void param(const param_type& new_params)
    {
      my_params = new_params;
    }

    const param_type& param() const { return my_params; }

    result_type a() const { return my_params.get_a(); }
    result_type b() const { return my_params.get_b(); }

    template<typename GeneratorType,
             const int GeneratorResultBits = std::numeric_limits<typename GeneratorType::result_type>::digits>
    WIDE_INTEGER_CONSTEXPR result_type operator()(GeneratorType& generator)
    {
      return generate<GeneratorType, GeneratorResultBits>(generator, my_params);
    }

    template<typename GeneratorType,
             const int GeneratorResultBits = std::numeric_limits<typename GeneratorType::result_type>::digits>
    WIDE_INTEGER_CONSTEXPR result_type operator()(GeneratorType& input_generator,
                                                  const param_type& input_params)
    {
      return generate<GeneratorType, GeneratorResultBits>(input_generator, input_params);
    }

  private:
    param_type my_params;

    template<typename GeneratorType,
             const int GeneratorResultBits = std::numeric_limits<typename GeneratorType::result_type>::digits>
    WIDE_INTEGER_CONSTEXPR result_type generate(GeneratorType& input_generator,
                                                const param_type& input_params) const
    {
      // Generate random numbers r, where a <= r <= b.

      result_type result(std::uint8_t(0U));

      using local_limb_type = typename result_type::limb_type;

      using generator_result_type = typename GeneratorType::result_type;

      constexpr std::uint32_t digits_generator_result_type = static_cast<std::uint32_t>(GeneratorResultBits);

      static_assert((digits_generator_result_type % 8U) == 0U,
                    "Error: Generator result type must have a multiple of 8 bits.");

      constexpr std::uint32_t digits_limb_ratio = 
        std::uint32_t(std::numeric_limits<local_limb_type>::digits / 8U);

      constexpr std::uint32_t digits_gtor_ratio = std::uint32_t(digits_generator_result_type / 8U);

      generator_result_type value = generator_result_type();

      typename result_type::iterator it = result.representation().begin();

      std::uint_fast32_t j = 0U;

      while(it < result.representation().end())
      {
        if((j % digits_gtor_ratio) == 0U)
        {
          value = input_generator();
        }

        const std::uint8_t next_byte = std::uint8_t(value >> unsigned((j % digits_gtor_ratio) * 8U));

        *it =
          static_cast<typename result_type::limb_type>
          (
            *it | local_limb_type(local_limb_type(next_byte) << unsigned((j % digits_limb_ratio) * 8U))
          );

        ++j;

        if((j % digits_limb_ratio) == 0U)
        {
          ++it;
        }
      }

      if(   (input_params.get_a() != (std::numeric_limits<result_type>::min)())
         || (input_params.get_b() != (std::numeric_limits<result_type>::max)()))
      {
        // Note that this restricts the range r to:
        //   r = {[input_generator() % ((b - a) + 1)] + a}

        result_type range(input_params.get_b() - input_params.get_a());
        ++range;

        result %= range;
        result += input_params.get_a();
      }

      return result;
    }
  };

  template<const size_t Width2,
           typename LimbType,
           typename AllocatorType,
           const bool IsSigned>
  constexpr bool operator==(const uniform_int_distribution<Width2, LimbType, AllocatorType, IsSigned>& lhs,
                            const uniform_int_distribution<Width2, LimbType, AllocatorType, IsSigned>& rhs)
  {
    return (lhs.param() == rhs.param());
  }

  template<const size_t Width2,
           typename LimbType,
           typename AllocatorType,
           const bool IsSigned>
  constexpr bool operator!=(const uniform_int_distribution<Width2, LimbType, AllocatorType, IsSigned>& lhs,
                            const uniform_int_distribution<Width2, LimbType, AllocatorType, IsSigned>& rhs)
  {
    return (lhs.param() != rhs.param());
  }

  template<typename DistributionType,
           typename GeneratorType,
           const size_t Width2,
           typename LimbType,
           typename AllocatorType,
           const bool IsSigned>
  bool miller_rabin(const uintwide_t<Width2, LimbType, AllocatorType, IsSigned>& n,
                    const std::uint_fast32_t                                     number_of_trials,
                    DistributionType&                                            distribution,
                    GeneratorType&                                               generator)
  {
    // This Miller-Rabin primality test is loosely based on
    // an adaptation of some code from Boost.Multiprecision.
    // The Boost.Multiprecision code can be found here:
    // https://www.boost.org/doc/libs/1_73_0/libs/multiprecision/doc/html/boost_multiprecision/tut/primetest.html

    // Note: Some comments in this subroutine use the Wolfram Language(TM).

    using local_wide_integer_type = uintwide_t<Width2, LimbType, AllocatorType, IsSigned>;
    using local_limb_type         = typename local_wide_integer_type::limb_type;

    const local_wide_integer_type np((local_wide_integer_type::is_neg(n) == false) ? n : -n);

    {
      const local_limb_type n0(np);

      if((n0 & 1U) == 0U)
      {
        // Not prime because n is even.
        return false;
      }

      if((n0 <= 227U) && (np <= 227U))
      {
        if((n0 == 2U) && (np == 2U))
        {
          // Trivial special case of (n = 2).
          return true;
        }

        // Table[Prime[i], {i, 2, 49}] =
        // {
        //     3,   5,   7,  11,  13,  17,  19,  23,
        //    29,  31,  37,  41,  43,  47,  53,  59,
        //    61,  67,  71,  73,  79,  83,  89,  97,
        //   101, 103, 107, 109, 113, 127, 131, 137,
        //   139, 149, 151, 157, 163, 167, 173, 179,
        //   181, 191, 193, 197, 199, 211, 223, 227
        // }

        // Exclude pure small primes from 3...227.
        constexpr std::array<local_limb_type, 48U> small_primes = 
        {{
          UINT8_C(  3), UINT8_C(  5), UINT8_C(  7), UINT8_C( 11), UINT8_C( 13), UINT8_C( 17), UINT8_C( 19), UINT8_C( 23),
          UINT8_C( 29), UINT8_C( 31), UINT8_C( 37), UINT8_C( 41), UINT8_C( 43), UINT8_C( 47), UINT8_C( 53), UINT8_C( 59),
          UINT8_C( 61), UINT8_C( 67), UINT8_C( 71), UINT8_C( 73), UINT8_C( 79), UINT8_C( 83), UINT8_C( 89), UINT8_C( 97),
          UINT8_C(101), UINT8_C(103), UINT8_C(107), UINT8_C(109), UINT8_C(113), UINT8_C(127), UINT8_C(131), UINT8_C(137),
          UINT8_C(139), UINT8_C(149), UINT8_C(151), UINT8_C(157), UINT8_C(163), UINT8_C(167), UINT8_C(173), UINT8_C(179),
          UINT8_C(181), UINT8_C(191), UINT8_C(193), UINT8_C(197), UINT8_C(199), UINT8_C(211), UINT8_C(223), UINT8_C(227)
        }};

        return std::binary_search(small_primes.cbegin(),
                                  small_primes.cend(),
                                  n0);
      }
    }

    // Check small factors.
    {
      // Product[Prime[i], {i, 2, 16}] = 16294579238595022365
      // Exclude small prime factors from { 3 ...  53 }.
      constexpr std::uint64_t pp0 = UINT64_C(16294579238595022365);

      const std::uint64_t m0(np % pp0);

      if(detail::integer_gcd_reduce_large(m0, pp0) != 1U)
      {
        return false;
      }
    }

    {
      // Product[Prime[i], {i, 17, 26}] = 7145393598349078859
      // Exclude small prime factors from { 59 ... 101 }.
      constexpr std::uint64_t pp1 = UINT64_C(7145393598349078859);

      const std::uint64_t m1(np % pp1);

      if(detail::integer_gcd_reduce_large(m1, pp1) != 1U)
      {
        return false;
      }
    }

    {
      // Product[Prime[i], {i, 27, 35}] = 6408001374760705163
      // Exclude small prime factors from { 103 ... 149 }.
      constexpr std::uint64_t pp2 = UINT64_C(6408001374760705163);

      const std::uint64_t m2(np % pp2);

      if(detail::integer_gcd_reduce_large(m2, pp2) != 1U)
      {
        return false;
      }
    }

    {
      // Product[Prime[i], {i, 36, 43}] = 690862709424854779
      // Exclude small prime factors from { 151 ... 191 }.
      constexpr std::uint64_t pp3 = UINT64_C(690862709424854779);

      const std::uint64_t m3(np % pp3);

      if(detail::integer_gcd_reduce_large(m3, pp3) != 1U)
      {
        return false;
      }
    }

    {
      // Product[Prime[i], {i, 44, 49}] = 80814592450549
      // Exclude small prime factors from { 193 ... 227 }.
      constexpr std::uint64_t pp4 = UINT64_C(80814592450549);

      const std::uint64_t m4(np % pp4);

      if(detail::integer_gcd_reduce_large(m4, pp4) != 1U)
      {
        return false;
      }
    }

    const local_wide_integer_type nm1(np - 1U);

    // Since we have already excluded all small factors
    // up to and including 227, n is greater than 227.

    {
      // Perform a single Fermat test which will
      // exclude many non-prime candidates.

      static const local_wide_integer_type n228(local_limb_type(228U));

      const local_wide_integer_type fn = powm(n228, nm1, np);

      const local_limb_type fn0 = static_cast<local_limb_type>(fn);

      if((fn0 != 1U) && (fn != 1U))
      {
        return false;
      }
    }

    const std::uint_fast32_t k = lsb(nm1);

    const local_wide_integer_type q = nm1 >> k;

    using local_param_type = typename DistributionType::param_type;

    const local_param_type params(local_wide_integer_type(2U), np - 2U);

    bool is_probably_prime = true;

    std::uint_fast32_t i = 0U;

    local_wide_integer_type x;
    local_wide_integer_type y;

    // Execute the random trials.
    do
    {
      x = distribution(generator, params);
      y = powm(x, q, np);

      std::uint_fast32_t j = 0U;

      while(y != nm1)
      {
        const local_limb_type y0(y);

        if((y0 == 1U) && (y == 1U))
        {
          if(j == 0U)
          {
            break;
          }
          else
          {
            is_probably_prime = false;
          }
        }
        else
        {
          ++j;

          if(j == k)
          {
            is_probably_prime = false;
          }
          else
          {
            y = powm(y, 2U, np);
          }
        }
      }

      ++i;
    }
    while((i < number_of_trials) && is_probably_prime);

    // Probably prime.
    return is_probably_prime;
  }

  } } // namespace math::wide_integer

#endif // UINTWIDE_T_2018_10_02_H_
