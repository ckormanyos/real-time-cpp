///////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 1999 - 2022.                 //
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

#ifndef DECWIDE_T_2004_06_01_H // NOLINT(llvm-header-guard)
  #define DECWIDE_T_2004_06_01_H

  //#define WIDE_DECIMAL_DISABLE_IOSTREAM
  //#define WIDE_DECIMAL_DISABLE_DYNAMIC_MEMORY_ALLOCATION
  //#define WIDE_DECIMAL_DISABLE_CONSTRUCT_FROM_STRING
  //#define WIDE_DECIMAL_DISABLE_CACHED_CONSTANTS
  //#define WIDE_DECIMAL_DISABLE_USE_STD_FUNCTION
  //#define WIDE_DECIMAL_NAMESPACE=something_unique // (best if done on the command line)

  #include <algorithm>
  #include <cmath>
  #include <cstddef>
  #if !defined(WIDE_DECIMAL_DISABLE_CONSTRUCT_FROM_STRING)
  #include <cstdlib>
  #endif
  #if (defined(__GNUC__) && !defined(__clang__) && (__GNUC__ >= 12))
  #include <cstring>
  #endif
  #if !defined(WIDE_DECIMAL_DISABLE_USE_STD_FUNCTION)
  #include <functional>
  #endif
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

  #if !defined(WIDE_DECIMAL_NAMESPACE_BEGIN)
  #error WIDE_DECIMAL_NAMESPACE_BEGIN is not defined. Ensure that <decwide_t_detail_namespace.h> is properly included.
  #endif

  #if !defined(WIDE_DECIMAL_NAMESPACE_END)
  #error WIDE_DECIMAL_NAMESPACE_END is not defined. Ensure that <decwide_t_detail_namespace.h> is properly included.
  #endif

  #if (defined(__GNUC__) && defined(__RL78__))
  namespace std { using ::ilogb; }
  #endif

  WIDE_DECIMAL_NAMESPACE_BEGIN

  #if(__cplusplus >= 201703L)
  namespace math::wide_decimal {
  #else
  namespace math { namespace wide_decimal { // NOLINT(modernize-concat-nested-namespaces)
  #endif

  // Forward declaration of the decwide_t template class.
  template<const std::int32_t ParamDigitsBaseTen,
           typename LimbType = std::uint32_t,
           typename AllocatorType = std::allocator<void>,
           typename InternalFloatType = double,
           typename ExponentType = std::int64_t,
           typename FftFloatType = double>
  class decwide_t;

  // Forward declarations of various decwide_t namespace functions.
  template<const std::int32_t ParamDigitsBaseTen, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType>
  constexpr auto zero() -> decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>;

  template<const std::int32_t ParamDigitsBaseTen, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType>
  constexpr auto one() -> decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>;

  template<const std::int32_t ParamDigitsBaseTen, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType>
  constexpr auto two() -> decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>;

  template<const std::int32_t ParamDigitsBaseTen, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType>
  constexpr auto half() -> decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>;

  #if !defined(WIDE_DECIMAL_DISABLE_CACHED_CONSTANTS)
  template<const std::int32_t ParamDigitsBaseTen,
           typename LimbType = std::uint32_t,
           typename AllocatorType = std::allocator<void>,
           typename InternalFloatType = double,
           typename ExponentType = std::int64_t,
           typename FftFloatType = double>
  #if !defined(WIDE_DECIMAL_DISABLE_USE_STD_FUNCTION)
  auto pi(const std::function<void(const std::uint32_t)>& pfn_callback_to_report_digits10 = nullptr) -> const decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>&;
  #else
  auto pi(void(*pfn_callback_to_report_digits10)(const std::uint32_t) = nullptr) -> const decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>&;
  #endif
  #else
  template<const std::int32_t ParamDigitsBaseTen,
           typename LimbType = std::uint32_t,
           typename AllocatorType = std::allocator<void>,
           typename InternalFloatType = double,
           typename ExponentType = std::int64_t,
           typename FftFloatType = double>
  #if !defined(WIDE_DECIMAL_DISABLE_USE_STD_FUNCTION)
  auto pi(const std::function<void(const std::uint32_t)>& pfn_callback_to_report_digits10 = nullptr) -> decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>;
  #else
  auto pi(void(*pfn_callback_to_report_digits10)(const std::uint32_t) = nullptr) -> decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>;
  #endif
  #endif

  #if !defined(WIDE_DECIMAL_DISABLE_CACHED_CONSTANTS)
  template<const std::int32_t ParamDigitsBaseTen,
           typename LimbType = std::uint32_t,
           typename AllocatorType = std::allocator<void>,
           typename InternalFloatType = double,
           typename ExponentType = std::int64_t,
           typename FftFloatType = double>
  auto ln_two() -> const decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>&;
  #else
  template<const std::int32_t ParamDigitsBaseTen,
           typename LimbType = std::uint32_t,
           typename AllocatorType = std::allocator<void>,
           typename InternalFloatType = double,
           typename ExponentType = std::int64_t,
           typename FftFloatType = double>
  auto ln_two() -> decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>;
  #endif

  template<const std::int32_t ParamDigitsBaseTen,
           typename LimbType = std::uint32_t,
           typename AllocatorType = std::allocator<void>,
           typename InternalFloatType = double,
           typename ExponentType = std::int64_t,
           typename FftFloatType = double>
  #if !defined(WIDE_DECIMAL_DISABLE_USE_STD_FUNCTION)
  auto calc_pi(const std::function<void(const std::uint32_t)>& pfn_callback_to_report_digits10 = nullptr) -> typename std::enable_if<(ParamDigitsBaseTen > static_cast<std::int32_t>(INT8_C(51))), decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>>::type;
  #else
  auto calc_pi(void(*pfn_callback_to_report_digits10)(const std::uint32_t) = nullptr) -> typename std::enable_if<(ParamDigitsBaseTen > static_cast<std::int32_t>(INT8_C(51))), decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>>::type;
  #endif

  template<const std::int32_t ParamDigitsBaseTen,
           typename LimbType = std::uint32_t,
           typename AllocatorType = std::allocator<void>,
           typename InternalFloatType = double,
           typename ExponentType = std::int64_t,
           typename FftFloatType = double>
  #if !defined(WIDE_DECIMAL_DISABLE_USE_STD_FUNCTION)
  auto calc_pi(const std::function<void(const std::uint32_t)>& pfn_callback_to_report_digits10 = nullptr) -> typename std::enable_if<((ParamDigitsBaseTen <= static_cast<std::int32_t>(INT8_C(51))) && std::is_same<LimbType, std::uint8_t>::value), decwide_t<ParamDigitsBaseTen, std::uint8_t, AllocatorType, InternalFloatType, ExponentType, FftFloatType>>::type;
  #else
  auto calc_pi(void(*pfn_callback_to_report_digits10)(const std::uint32_t) = nullptr) -> typename std::enable_if<((ParamDigitsBaseTen <= static_cast<std::int32_t>(INT8_C(51))) && std::is_same<LimbType, std::uint8_t>::value), decwide_t<ParamDigitsBaseTen, std::uint8_t, AllocatorType, InternalFloatType, ExponentType, FftFloatType>>::type;
  #endif

  template<const std::int32_t ParamDigitsBaseTen,
           typename LimbType = std::uint32_t,
           typename AllocatorType = std::allocator<void>,
           typename InternalFloatType = double,
           typename ExponentType = std::int64_t,
           typename FftFloatType = double>
  #if !defined(WIDE_DECIMAL_DISABLE_USE_STD_FUNCTION)
  auto calc_pi(const std::function<void(const std::uint32_t)>& pfn_callback_to_report_digits10 = nullptr) -> typename std::enable_if<((ParamDigitsBaseTen <= static_cast<std::int32_t>(INT8_C(51))) && std::is_same<LimbType, std::uint16_t>::value), decwide_t<ParamDigitsBaseTen, std::uint16_t, AllocatorType, InternalFloatType, ExponentType, FftFloatType>>::type;
  #else
  auto calc_pi(void(*pfn_callback_to_report_digits10)(const std::uint32_t) = nullptr) -> typename std::enable_if<((ParamDigitsBaseTen <= static_cast<std::int32_t>(INT8_C(51))) && std::is_same<LimbType, std::uint16_t>::value), decwide_t<ParamDigitsBaseTen, std::uint16_t, AllocatorType, InternalFloatType, ExponentType, FftFloatType>>::type;
  #endif

  template<const std::int32_t ParamDigitsBaseTen,
           typename LimbType = std::uint32_t,
           typename AllocatorType = std::allocator<void>,
           typename InternalFloatType = double,
           typename ExponentType = std::int64_t,
           typename FftFloatType = double>
  #if !defined(WIDE_DECIMAL_DISABLE_USE_STD_FUNCTION)
  auto calc_pi(const std::function<void(const std::uint32_t)>& pfn_callback_to_report_digits10 = nullptr) -> typename std::enable_if<((ParamDigitsBaseTen <= static_cast<std::int32_t>(INT8_C(51))) && std::is_same<LimbType, std::uint32_t>::value), decwide_t<ParamDigitsBaseTen, std::uint32_t, AllocatorType, InternalFloatType, ExponentType, FftFloatType>>::type;
  #else
  auto calc_pi(void(*pfn_callback_to_report_digits10)(const std::uint32_t) = nullptr) -> typename std::enable_if<((ParamDigitsBaseTen <= static_cast<std::int32_t>(INT8_C(51))) && std::is_same<LimbType, std::uint32_t>::value), decwide_t<ParamDigitsBaseTen, std::uint16_t, AllocatorType, InternalFloatType, ExponentType, FftFloatType>>::type;
  #endif

  template<const std::int32_t ParamDigitsBaseTen,
           typename LimbType = std::uint32_t,
           typename AllocatorType = std::allocator<void>,
           typename InternalFloatType = double,
           typename ExponentType = std::int64_t,
           typename FftFloatType = double>
  auto calc_ln_two() -> typename std::enable_if<(ParamDigitsBaseTen > static_cast<std::int32_t>(INT8_C(51))), decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>>::type;

  template<const std::int32_t ParamDigitsBaseTen,
           typename LimbType = std::uint32_t,
           typename AllocatorType = std::allocator<void>,
           typename InternalFloatType = double,
           typename ExponentType = std::int64_t,
           typename FftFloatType = double>
  auto calc_ln_two() -> typename std::enable_if<((ParamDigitsBaseTen <= static_cast<std::int32_t>(INT8_C(51))) && std::is_same<LimbType, std::uint8_t>::value), decwide_t<ParamDigitsBaseTen, std::uint8_t, AllocatorType, InternalFloatType, ExponentType, FftFloatType>>::type;

  template<const std::int32_t ParamDigitsBaseTen,
           typename LimbType = std::uint32_t,
           typename AllocatorType = std::allocator<void>,
           typename InternalFloatType = double,
           typename ExponentType = std::int64_t,
           typename FftFloatType = double>
  auto calc_ln_two() -> typename std::enable_if<((ParamDigitsBaseTen <= static_cast<std::int32_t>(INT8_C(51))) && std::is_same<LimbType, std::uint16_t>::value), decwide_t<ParamDigitsBaseTen, std::uint16_t, AllocatorType, InternalFloatType, ExponentType, FftFloatType>>::type;

  template<const std::int32_t ParamDigitsBaseTen,
           typename LimbType = std::uint32_t,
           typename AllocatorType = std::allocator<void>,
           typename InternalFloatType = double,
           typename ExponentType = std::int64_t,
           typename FftFloatType = double>
  auto calc_ln_two() -> typename std::enable_if<((ParamDigitsBaseTen <= static_cast<std::int32_t>(INT8_C(51))) && std::is_same<LimbType, std::uint32_t>::value), decwide_t<ParamDigitsBaseTen, std::uint32_t, AllocatorType, InternalFloatType, ExponentType, FftFloatType>>::type;

  template<const std::int32_t ParamDigitsBaseTen,
           typename LimbType = std::uint32_t,
           typename AllocatorType = std::allocator<void>,
           typename InternalFloatType = double,
           typename ExponentType = std::int64_t,
           typename FftFloatType = double>
  auto calc_ln_ten_low_precision() -> typename std::enable_if<((ParamDigitsBaseTen <= static_cast<std::int32_t>(INT8_C(51))) && std::is_same<LimbType, std::uint8_t>::value), decwide_t<ParamDigitsBaseTen, std::uint8_t, AllocatorType, InternalFloatType, ExponentType, FftFloatType>>::type;

  template<const std::int32_t ParamDigitsBaseTen,
           typename LimbType = std::uint32_t,
           typename AllocatorType = std::allocator<void>,
           typename InternalFloatType = double,
           typename ExponentType = std::int64_t,
           typename FftFloatType = double>
  auto calc_ln_ten_low_precision() -> typename std::enable_if<((ParamDigitsBaseTen <= static_cast<std::int32_t>(INT8_C(51))) && std::is_same<LimbType, std::uint16_t>::value), decwide_t<ParamDigitsBaseTen, std::uint16_t, AllocatorType, InternalFloatType, ExponentType, FftFloatType>>::type;

  template<const std::int32_t ParamDigitsBaseTen,
           typename LimbType = std::uint32_t,
           typename AllocatorType = std::allocator<void>,
           typename InternalFloatType = double,
           typename ExponentType = std::int64_t,
           typename FftFloatType = double>
  auto calc_ln_ten_low_precision() -> typename std::enable_if<((ParamDigitsBaseTen <= static_cast<std::int32_t>(INT8_C(51))) && std::is_same<LimbType, std::uint32_t>::value), decwide_t<ParamDigitsBaseTen, std::uint32_t, AllocatorType, InternalFloatType, ExponentType, FftFloatType>>::type;

  template<const std::int32_t ParamDigitsBaseTen, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType> auto constexpr unsigned_long_long_max() -> decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>;
  template<const std::int32_t ParamDigitsBaseTen, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType> auto constexpr signed_long_long_min  () -> decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>;
  template<const std::int32_t ParamDigitsBaseTen, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType> auto constexpr signed_long_long_max  () -> decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>;
  template<const std::int32_t ParamDigitsBaseTen, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType> auto constexpr long_double_min       () -> decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>;
  template<const std::int32_t ParamDigitsBaseTen, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType> auto constexpr long_double_max       () -> decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>;

  template<const std::int32_t ParamDigitsBaseTen, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType> auto (isnan)   (const decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>& x) -> bool;
  template<const std::int32_t ParamDigitsBaseTen, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType> auto (isfinite)(const decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>& x) -> bool;
  template<const std::int32_t ParamDigitsBaseTen, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType> auto (isinf)   (const decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>& x) -> bool;
  template<const std::int32_t ParamDigitsBaseTen, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType> auto (signbit) (const decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>& x) -> bool;

  template<const std::int32_t ParamDigitsBaseTen, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType> auto fabs     (const decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>& x)  ->          decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>;
  template<const std::int32_t ParamDigitsBaseTen, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType> auto abs      (const decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>& x)  ->          decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>;
  template<const std::int32_t ParamDigitsBaseTen, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType> auto floor    (const decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>& x)  ->          decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>;
  template<const std::int32_t ParamDigitsBaseTen, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType> auto ceil     (const decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>& x)  ->          decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>;
  template<const std::int32_t ParamDigitsBaseTen, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType> auto ldexp    (const decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>& v,
                                                                                                                                                                                      int e)                                                                                                           ->          decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>;
  template<const std::int32_t ParamDigitsBaseTen, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType> auto frexp    (const decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>& v,                             
                                                                                                                                                                                      int* expon)                                                                                                      ->          decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>;
  template<const std::int32_t ParamDigitsBaseTen, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType> auto fmod     (const decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>& v1,
                                                                                                                                                                                      const decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>& v2) ->          decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>;
  template<const std::int32_t ParamDigitsBaseTen, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType> auto ilogb    (const decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>& x)  -> typename decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>::exponent_type;
  template<const std::int32_t ParamDigitsBaseTen, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType> auto sqrt     (const decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>& x)  ->          decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>;
  template<const std::int32_t ParamDigitsBaseTen, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType> auto cbrt     (const decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>& x)  ->          decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>;
  template<const std::int32_t ParamDigitsBaseTen, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType> auto rootn    (const decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>& x, // NOLINT(misc-no-recursion)
                                                                                                                                                                                      std::int32_t p)                                                                                                  ->          decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>;
  template<const std::int32_t ParamDigitsBaseTen, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType> auto rootn_inv(const decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>& x,
                                                                                                                                                                                      std::int32_t p)                                                                                                  ->          decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>;
  template<const std::int32_t ParamDigitsBaseTen, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType> auto log      (const decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>& x)  ->          typename std::enable_if<(ParamDigitsBaseTen > static_cast<std::int32_t>(INT8_C(51))), decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>>::type; // NOLINT(misc-no-recursion)
  template<const std::int32_t ParamDigitsBaseTen, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType> auto log      (const decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>& x)  ->          typename std::enable_if<(ParamDigitsBaseTen <= static_cast<std::int32_t>(INT8_C(51))), decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>>::type; // NOLINT(misc-no-recursion)
  template<const std::int32_t ParamDigitsBaseTen, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType> auto exp      (const decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>& x)  ->          typename std::enable_if<(ParamDigitsBaseTen > static_cast<std::int32_t>(INT32_C(2000))), decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>>::type;
  template<const std::int32_t ParamDigitsBaseTen, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType> auto exp      (const decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>& x)  ->          typename std::enable_if<(ParamDigitsBaseTen <= static_cast<std::int32_t>(INT32_C(2000))), decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>>::type;
  template<const std::int32_t ParamDigitsBaseTen, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType> auto sinh     (const decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>& x)  ->          decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>;
  template<const std::int32_t ParamDigitsBaseTen, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType> auto cosh     (const decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>& x)  ->          decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>;
  template<const std::int32_t ParamDigitsBaseTen, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType> auto tanh     (const decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>& x)  ->          decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>;
  template<const std::int32_t ParamDigitsBaseTen, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType> auto pow      (const decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>& b, // NOLINT(misc-no-recursion)
                                                                                                                                                                                      std::int64_t p)                                                                                                  ->          decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>;
  template<const std::int32_t ParamDigitsBaseTen, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType> auto pow      (const decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>& x,
                                                                                                                                                                                      const decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>& a)  ->          decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>;

  #if !defined(WIDE_DECIMAL_DISABLE_IOSTREAM)
  template<typename char_type, typename traits_type,
           const std::int32_t ParamDigitsBaseTen, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType> auto operator<<(std::basic_ostream<char_type, traits_type>& os, const decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>& f) -> std::basic_ostream<char_type, traits_type>&;
  template<typename char_type, typename traits_type,
           const std::int32_t ParamDigitsBaseTen, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType> auto operator>>(std::basic_istream<char_type, traits_type>& is,       decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>& f) -> std::basic_istream<char_type, traits_type>&;
  #endif // !WIDE_DECIMAL_DISABLE_IOSTREAM

  // Global unary operators of decwide_t reference.
  template<const std::int32_t ParamDigitsBaseTen, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType> auto operator+(const decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>& self) -> decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>;
  template<const std::int32_t ParamDigitsBaseTen, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType> auto operator-(const decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>& self) -> decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>;

  // Global add/sub/mul/div of const decwide_t& with const decwide_t&.
  template<const std::int32_t ParamDigitsBaseTen, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType> auto operator+(const decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>& u, const decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>& v) -> decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>;
  template<const std::int32_t ParamDigitsBaseTen, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType> auto operator-(const decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>& u, const decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>& v) -> decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>;
  template<const std::int32_t ParamDigitsBaseTen, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType> auto operator*(const decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>& u, const decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>& v) -> decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>;
  template<const std::int32_t ParamDigitsBaseTen, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType> auto operator/(const decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>& u, const decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>& v) -> decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>;

  // Global add/sub/mul/div of const decwide_t& with all built-in types.
  template<const std::int32_t ParamDigitsBaseTen, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType, typename SignedIntegralType>
  auto operator+(const decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>& u,
                 SignedIntegralType n) -> typename std::enable_if<     std::is_integral<SignedIntegralType>::value
                                                                  && (!std::is_unsigned<SignedIntegralType>::value),
                                                                  decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>>::type;

  template<const std::int32_t ParamDigitsBaseTen, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType, typename UnsignedIntegralType>
  auto operator+(const decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>& u,
                 UnsignedIntegralType n) -> typename std::enable_if<   std::is_integral<UnsignedIntegralType>::value
                                                                    && std::is_unsigned<UnsignedIntegralType>::value,
                                                                    decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>>::type;

  template<const std::int32_t ParamDigitsBaseTen, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType, typename FloatingPointType>
  auto operator+(const decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>& u,
                 FloatingPointType f) -> typename std::enable_if<std::is_floating_point<FloatingPointType>::value,
                                                                 decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>>::type;

  template<const std::int32_t ParamDigitsBaseTen, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType, typename SignedIntegralType>
  auto operator-(const decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>& u,
                 SignedIntegralType n) -> typename std::enable_if<     std::is_integral<SignedIntegralType>::value
                                                                  && (!std::is_unsigned<SignedIntegralType>::value),
                                                                  decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>>::type;

  template<const std::int32_t ParamDigitsBaseTen, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType, typename UnsignedIntegralType>
  auto operator-(const decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>& u,
                 UnsignedIntegralType n) -> typename std::enable_if<   std::is_integral<UnsignedIntegralType>::value
                                                                    && std::is_unsigned<UnsignedIntegralType>::value,
                                                                    decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>>::type;

  template<const std::int32_t ParamDigitsBaseTen, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType, typename FloatingPointType>
  auto operator-(const decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>& u,
                 FloatingPointType f) -> typename std::enable_if<std::is_floating_point<FloatingPointType>::value,
                                                                 decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>>::type;

  template<const std::int32_t ParamDigitsBaseTen, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType, typename SignedIntegralType>
  auto operator*(const decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>& u,
                 SignedIntegralType n) -> typename std::enable_if<     std::is_integral<SignedIntegralType>::value
                                                                  && (!std::is_unsigned<SignedIntegralType>::value),
                                                                  decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>>::type;

  template<const std::int32_t ParamDigitsBaseTen, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType, typename UnsignedIntegralType>
  auto operator*(const decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>& u,
                 UnsignedIntegralType n) -> typename std::enable_if<   std::is_integral<UnsignedIntegralType>::value
                                                                    && std::is_unsigned<UnsignedIntegralType>::value,
                                                                    decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>>::type;

  template<const std::int32_t ParamDigitsBaseTen, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType, typename FloatingPointType>
  auto operator*(const decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>& u,
                 FloatingPointType f) -> typename std::enable_if<std::is_floating_point<FloatingPointType>::value,
                                                                 decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>>::type;

  template<const std::int32_t ParamDigitsBaseTen, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType, typename SignedIntegralType>
  auto operator/(const decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>& u,
                 SignedIntegralType n) -> typename std::enable_if<     std::is_integral<SignedIntegralType>::value
                                                                  && (!std::is_unsigned<SignedIntegralType>::value),
                                                                      decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>>::type;

  template<const std::int32_t ParamDigitsBaseTen, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType, typename UnsignedIntegralType>
  auto operator/(const decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>& u,
                 UnsignedIntegralType n) -> typename std::enable_if<   std::is_integral<UnsignedIntegralType>::value
                                                                    && std::is_unsigned<UnsignedIntegralType>::value,
                                                                    decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>>::type;

  template<const std::int32_t ParamDigitsBaseTen, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType, typename FloatingPointType>
  auto operator/(const decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>& u,
                 FloatingPointType f) -> typename std::enable_if<std::is_floating_point<FloatingPointType>::value,
                                                                 decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>>::type;

  // Global add/sub/mul/div of all built-in types with const decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>&.
  template<const std::int32_t ParamDigitsBaseTen, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType, typename SignedIntegralType>
  auto operator+(SignedIntegralType n,
                 const decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>& u) -> typename std::enable_if<     std::is_integral<SignedIntegralType>::value
                                                                                                                                                            && (!std::is_unsigned<SignedIntegralType>::value),
                                                                                                                                                            decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>>::type;

  template<const std::int32_t ParamDigitsBaseTen, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType, typename UnsignedIntegralType>
  auto operator+(UnsignedIntegralType n,
                 const decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>& u) -> typename std::enable_if<   std::is_integral<UnsignedIntegralType>::value
                                                                                                                                                            && std::is_unsigned<UnsignedIntegralType>::value,
                                                                                                                                                            decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>>::type;

  template<const std::int32_t ParamDigitsBaseTen, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType, typename FloatingPointType>
  auto operator+(FloatingPointType f,
                 const decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>& u) -> typename std::enable_if<std::is_floating_point<FloatingPointType>::value,
                                                                                                                                                            decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>>::type;

  template<const std::int32_t ParamDigitsBaseTen, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType, typename ArithmeticType>
  auto operator-(ArithmeticType n,
                 const decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>& u) -> typename std::enable_if<std::is_arithmetic<ArithmeticType>::value,
                                                                                                                                                            decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>>::type;

  template<const std::int32_t ParamDigitsBaseTen, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType, typename SignedIntegralType>
  auto operator*(SignedIntegralType n,
                 const decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>& u) -> typename std::enable_if<     std::is_integral<SignedIntegralType>::value
                                                                                                                                                            && (!std::is_unsigned<SignedIntegralType>::value),
                                                                                                                                                            decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>>::type;

  template<const std::int32_t ParamDigitsBaseTen, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType, typename UnsignedIntegralType>
  auto operator*(UnsignedIntegralType n,
                 const decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>& u) -> typename std::enable_if<   std::is_integral<UnsignedIntegralType>::value
                                                                                                                                                            && std::is_unsigned<UnsignedIntegralType>::value,
                                                                                                                                                            decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>>::type;

  template<const std::int32_t ParamDigitsBaseTen, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType, typename FloatingPointType>
  auto operator*(FloatingPointType f,
                 const decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>& u) -> typename std::enable_if<std::is_floating_point<FloatingPointType>::value,
                                                                                                                                                            decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>>::type;

  template<const std::int32_t ParamDigitsBaseTen, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType, typename ArithmeticType>
  auto operator/(ArithmeticType n,
                 const decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>& u) -> typename std::enable_if<std::is_arithmetic<ArithmeticType>::value,
                                                                                                                                                            decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>>::type;

  // Global self add/sub/mul/div of decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>& with all built-in types.
  template<const std::int32_t ParamDigitsBaseTen, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType, typename SignedIntegralType>
  auto operator+=(decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>& u,
                  SignedIntegralType n) -> typename std::enable_if<     std::is_integral<SignedIntegralType>::value
                                                                   && (!std::is_unsigned<SignedIntegralType>::value),
                                                                   decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>>::type;

  template<const std::int32_t ParamDigitsBaseTen, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType, typename UnsignedIntegralType>
  auto operator+=(decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>& u,
                  UnsignedIntegralType n) -> typename std::enable_if<   std::is_integral<UnsignedIntegralType>::value
                                                                     && std::is_unsigned<UnsignedIntegralType>::value,
                                                                     decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>>::type;

  template<const std::int32_t ParamDigitsBaseTen, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType, typename FloatingPointType>
  auto operator+=(decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>& u,
                  FloatingPointType f) -> typename std::enable_if<std::is_floating_point<FloatingPointType>::value,
                                                                  decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>>::type;

  template<const std::int32_t ParamDigitsBaseTen, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType, typename SignedIntegralType>
  auto operator-=(decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>& u,
                  SignedIntegralType n) -> typename std::enable_if<     std::is_integral<SignedIntegralType>::value
                                                                   && (!std::is_unsigned<SignedIntegralType>::value),
                                                                   decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>>::type;

  template<const std::int32_t ParamDigitsBaseTen, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType, typename UnsignedIntegralType>
  auto operator-=(decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>& u,
                  UnsignedIntegralType n) -> typename std::enable_if<   std::is_integral<UnsignedIntegralType>::value
                                                                     && std::is_unsigned<UnsignedIntegralType>::value,
                                                                     decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>>::type;

  template<const std::int32_t ParamDigitsBaseTen, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType, typename FloatingPointType>
  auto operator-=(decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>& u,
                  FloatingPointType f) -> typename std::enable_if<std::is_floating_point<FloatingPointType>::value,
                                                                  decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>>::type;

  template<const std::int32_t ParamDigitsBaseTen, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType, typename SignedIntegralType>
  auto operator*=(decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>& u,
                  SignedIntegralType n) -> typename std::enable_if<     std::is_integral<SignedIntegralType>::value
                                                                   && (!std::is_unsigned<SignedIntegralType>::value),
                                                                   decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>>::type;

  template<const std::int32_t ParamDigitsBaseTen, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType, typename UnsignedIntegralType>
  auto operator*=(decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>& u,
                  UnsignedIntegralType n) -> typename std::enable_if<   std::is_integral<UnsignedIntegralType>::value
                                                                     && std::is_unsigned<UnsignedIntegralType>::value,
                                                                     decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>>::type;

  template<const std::int32_t ParamDigitsBaseTen, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType, typename FloatingPointType>
  auto operator*=(decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>& u,
                  FloatingPointType f) -> typename std::enable_if<std::is_floating_point<FloatingPointType>::value,
                                                                  decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>>::type;

  template<const std::int32_t ParamDigitsBaseTen, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType, typename SignedIntegralType>
  auto operator/=(decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>& u,
                  SignedIntegralType n) -> typename std::enable_if<   std::is_integral<SignedIntegralType>::value
                                                                   && (!std::is_unsigned<SignedIntegralType>::value),
                                                                   decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>>::type;

  template<const std::int32_t ParamDigitsBaseTen, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType, typename UnsignedIntegralType>
  auto operator/=(decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>& u,
                  UnsignedIntegralType n) -> typename std::enable_if<   std::is_integral<UnsignedIntegralType>::value
                                                                     && std::is_unsigned<UnsignedIntegralType>::value,
                                                                     decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>>::type;

  template<const std::int32_t ParamDigitsBaseTen, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType, typename FloatingPointType>
  auto operator/=(decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>& u,
                  FloatingPointType f) -> typename std::enable_if<std::is_floating_point<FloatingPointType>::value,
                                                                  decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>>::type;

  // Global comparison operators of const decwide_t& with const decwide_t&.
  template<const std::int32_t ParamDigitsBaseTen, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType> auto operator< (const decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>& u, const decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>& v) -> bool;
  template<const std::int32_t ParamDigitsBaseTen, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType> auto operator<=(const decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>& u, const decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>& v) -> bool;
  template<const std::int32_t ParamDigitsBaseTen, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType> auto operator==(const decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>& u, const decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>& v) -> bool;
  template<const std::int32_t ParamDigitsBaseTen, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType> auto operator!=(const decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>& u, const decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>& v) -> bool;
  template<const std::int32_t ParamDigitsBaseTen, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType> auto operator>=(const decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>& u, const decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>& v) -> bool;
  template<const std::int32_t ParamDigitsBaseTen, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType> auto operator> (const decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>& u, const decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>& v) -> bool;

  // Global comparison operators of const decwide_t& with all built-in types.
  template<const std::int32_t ParamDigitsBaseTen, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType, typename ArithmeticType> auto operator< (const decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>& u, const ArithmeticType& v) -> typename std::enable_if<std::is_arithmetic<ArithmeticType>::value, bool>::type;
  template<const std::int32_t ParamDigitsBaseTen, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType, typename ArithmeticType> auto operator<=(const decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>& u, const ArithmeticType& v) -> typename std::enable_if<std::is_arithmetic<ArithmeticType>::value, bool>::type;
  template<const std::int32_t ParamDigitsBaseTen, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType, typename ArithmeticType> auto operator==(const decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>& u, const ArithmeticType& v) -> typename std::enable_if<std::is_arithmetic<ArithmeticType>::value, bool>::type;
  template<const std::int32_t ParamDigitsBaseTen, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType, typename ArithmeticType> auto operator!=(const decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>& u, const ArithmeticType& v) -> typename std::enable_if<std::is_arithmetic<ArithmeticType>::value, bool>::type;
  template<const std::int32_t ParamDigitsBaseTen, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType, typename ArithmeticType> auto operator>=(const decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>& u, const ArithmeticType& v) -> typename std::enable_if<std::is_arithmetic<ArithmeticType>::value, bool>::type;
  template<const std::int32_t ParamDigitsBaseTen, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType, typename ArithmeticType> auto operator> (const decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>& u, const ArithmeticType& v) -> typename std::enable_if<std::is_arithmetic<ArithmeticType>::value, bool>::type;

  // Global comparison operators of all built-in types with const decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>&.
  template<const std::int32_t ParamDigitsBaseTen, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType, typename ArithmeticType> auto operator< (ArithmeticType u, const decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>& v) -> typename std::enable_if<std::is_arithmetic<ArithmeticType>::value, bool>::type;
  template<const std::int32_t ParamDigitsBaseTen, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType, typename ArithmeticType> auto operator<=(ArithmeticType u, const decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>& v) -> typename std::enable_if<std::is_arithmetic<ArithmeticType>::value, bool>::type;
  template<const std::int32_t ParamDigitsBaseTen, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType, typename ArithmeticType> auto operator==(ArithmeticType u, const decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>& v) -> typename std::enable_if<std::is_arithmetic<ArithmeticType>::value, bool>::type;
  template<const std::int32_t ParamDigitsBaseTen, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType, typename ArithmeticType> auto operator!=(ArithmeticType u, const decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>& v) -> typename std::enable_if<std::is_arithmetic<ArithmeticType>::value, bool>::type;
  template<const std::int32_t ParamDigitsBaseTen, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType, typename ArithmeticType> auto operator>=(ArithmeticType u, const decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>& v) -> typename std::enable_if<std::is_arithmetic<ArithmeticType>::value, bool>::type;
  template<const std::int32_t ParamDigitsBaseTen, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType, typename ArithmeticType> auto operator> (ArithmeticType u, const decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>& v) -> typename std::enable_if<std::is_arithmetic<ArithmeticType>::value, bool>::type;

  template<const std::int32_t ParamDigitsBaseTen,
           typename LimbType,
           typename AllocatorType,
           typename InternalFloatType,
           typename ExponentType,
           typename FftFloatType>
  class decwide_t // NOLINT(clang-analyzer-optin.performance.Padding)
  {
  public:
    // Define the decwide_t digits characteristics.

    using exponent_type  = ExponentType;
    using fft_float_type = FftFloatType;

    static_assert((   std::is_same<std::int8_t,  exponent_type>::value
                   || std::is_same<std::int16_t, exponent_type>::value
                   || std::is_same<std::int32_t, exponent_type>::value
                   || std::is_same<std::int64_t, exponent_type>::value),
                   "Error: exponent_type (template parameter ExponentType) "
                   "must be one of int8_t, int16_t, int32_t or int64_t.");

    static constexpr std::int32_t  decwide_t_digits10       = detail::decwide_t_helper<ParamDigitsBaseTen, LimbType>::digits10;
    static constexpr std::int32_t  decwide_t_digits         = detail::decwide_t_helper<ParamDigitsBaseTen, LimbType>::digits;
    static constexpr std::int32_t  decwide_t_max_digits10   = detail::decwide_t_helper<ParamDigitsBaseTen, LimbType>::max_digits10;
    static constexpr std::int32_t  decwide_t_radix          = detail::decwide_t_helper<ParamDigitsBaseTen, LimbType>::radix;

    static constexpr std::int32_t  decwide_t_elem_digits10  = detail::decwide_t_helper<ParamDigitsBaseTen, LimbType>::elem_digits10;
    static constexpr std::int32_t  decwide_t_elem_number    = detail::decwide_t_helper<ParamDigitsBaseTen, LimbType>::elem_number;
    static constexpr std::int32_t  decwide_t_elem_mask      = detail::decwide_t_helper<ParamDigitsBaseTen, LimbType>::elem_mask;
    static constexpr std::int32_t  decwide_t_elem_mask_half = detail::decwide_t_helper<ParamDigitsBaseTen, LimbType>::elem_mask_half;

    static constexpr std::int32_t  decwide_t_elems_for_kara = static_cast<std::int32_t>( 112 + 1);
    static constexpr std::int32_t  decwide_t_elems_for_fft  = static_cast<std::int32_t>(1792 + 1);

    static constexpr exponent_type decwide_t_max_exp10      =  static_cast<exponent_type>(UINTMAX_C(1) << static_cast<unsigned>(std::numeric_limits<exponent_type>::digits - (std::is_same<exponent_type, std::int64_t>::value ? 4 : (std::is_same<exponent_type, std::int32_t>::value ? 3 : (std::is_same<exponent_type, std::int16_t>::value ? 2 : 1)))));
    static constexpr exponent_type decwide_t_min_exp10      = -static_cast<exponent_type>(decwide_t_max_exp10);
    static constexpr exponent_type decwide_t_max_exp        = decwide_t_max_exp10;
    static constexpr exponent_type decwide_t_min_exp        = decwide_t_min_exp10;

    // Obtain the limb_type from template parameter.
    using limb_type = LimbType;

  private:
    // Rebind the decwide_t allocator to the granularity of the LimbType.
    using allocator_conditional_type =
      typename std::conditional<std::is_same<AllocatorType, void>::value,
                                std::allocator<void>,
                                AllocatorType>::type;

  public:
    using allocator_type =
      typename std::allocator_traits<allocator_conditional_type>::template rebind_alloc<limb_type>;

    // Define the array type, which is the internal
    // representation of the data field of a decwide_t.
    using representation_type =
      typename std::conditional<std::is_same<AllocatorType, void>::value,
                                detail::fixed_static_array <limb_type, static_cast<std::uint_fast32_t>(decwide_t_elem_number)>,
                                detail::fixed_dynamic_array<limb_type, static_cast<std::uint_fast32_t>(decwide_t_elem_number), allocator_type>>::type;

    // Check the width of the limb type.
    static_assert((   std::is_same<std::uint8_t,  limb_type>::value
                   || std::is_same<std::uint16_t, limb_type>::value
                   || std::is_same<std::uint32_t, limb_type>::value),
                   "Error: limb_type (template parameter LimbType) "
                   "must be one of uint8_t, uint16_t or uint32_t.");

    using double_limb_type =
      typename std::conditional<std::is_same<limb_type, std::uint32_t>::value,
                                std::uint64_t,
                                typename std::conditional<std::is_same<limb_type, std::uint16_t>::value,
                                                          std::uint32_t,
                                                          std::uint16_t>::type>::type;

    using signed_limb_type =
      typename std::conditional<std::is_same<limb_type, std::uint32_t>::value,
                                std::int32_t,
                                typename std::conditional<std::is_same<limb_type, std::uint16_t>::value,
                                                          std::int16_t,
                                                          std::int8_t>::type>::type;

    using unsigned_exponent_type =
      typename std::conditional<std::is_same<exponent_type, std::int64_t>::value,
                                std::uint64_t,
                                typename std::conditional<std::is_same<exponent_type, std::int32_t>::value,
                                                          std::uint32_t,
                                                          typename std::conditional<std::is_same<exponent_type, std::int16_t>::value,
                                                                                    std::uint16_t,
                                                                                    std::uint8_t>::type>::type>::type;

    // TBD: Consider supporting more floating-point classes.
    // In particular, support for NaN is already being
    // partially used through the specialization of limits.
    // When starting, maybe begin with FP-class NaN.
    enum class fpclass_type
    {
      decwide_t_finite
    };

  private:
    template<typename FloatingPointType>
    class native_float_parts final
    {
    public:
      // Emphasize: This template class can be used with native
      // floating-point types like float, double and long double.

      // Note: For long double, you need to verify that the
      // mantissa fits in unsigned long long.

      explicit native_float_parts(FloatingPointType f)
      {
        using native_float_type = FloatingPointType;

        static_assert(std::numeric_limits<native_float_type>::digits <= std::numeric_limits<unsigned long long>::digits, // NOLINT(google-runtime-int)
                      "Error: The width of the mantissa does not fit in unsigned long long");

        const native_float_type ff = ((f < static_cast<native_float_type>(0)) ? static_cast<native_float_type>(-f) : f);

        if(ff < (std::numeric_limits<native_float_type>::min)())
        {
          return;
        }

        using std::frexp;

        // Get the fraction and base-2 exponent.

        // TBD: Need to properly handle frexp when GCC's __float128
        // is active (in case of -std=gnu++XX).
        // This happens when native_float_type is of type __float128.

        auto man = static_cast<native_float_type>(frexp(static_cast<long double>(f), &my_exponent_part));

        auto n2 = static_cast<unsigned>(0U);

        for(auto   i = static_cast<std::uint_fast16_t>(0U);
                   i < static_cast<std::uint_fast16_t>(std::numeric_limits<native_float_type>::digits);
                 ++i)
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

        // TBD: Need to properly handle this left shif amount
        // when GCC's __float128 is active (in case of -std=gnu++XX).
        // This happens when native_float_type is of type __float128.
        const auto max_left_shift_amount =
          (std::min)
          (
            std::numeric_limits<native_float_type>::digits,
            std::numeric_limits<long double>::digits
          );

        my_mantissa_part |= static_cast<unsigned long long>(1ULL << static_cast<unsigned>(max_left_shift_amount - 1)); // NOLINT(google-runtime-int)
        my_exponent_part -= 1;
      }

      constexpr native_float_parts(const native_float_parts& other)
        : my_mantissa_part(other.my_mantissa_part),
          my_exponent_part(other.my_exponent_part) { }

      constexpr native_float_parts(native_float_parts&& other) noexcept
        : my_mantissa_part(other.my_mantissa_part),
          my_exponent_part(other.my_exponent_part) { }

      native_float_parts() = delete;

      ~native_float_parts() = default;

      auto operator=(const native_float_parts& other) noexcept -> native_float_parts& // NOLINT(cert-oop54-cpp)
      {
        if(this != &other)
        {
          my_mantissa_part = other.my_mantissa_part;
          my_exponent_part = other.my_exponent_part;
        }

        return *this;
      }

      auto operator=(native_float_parts&& other) noexcept -> native_float_parts&
      {
        my_mantissa_part = other.my_mantissa_part;
        my_exponent_part = other.my_exponent_part;

        return *this;
      }

     WIDE_DECIMAL_NODISCARD constexpr auto get_mantissa() const -> unsigned long long { return my_mantissa_part; } // NOLINT(google-runtime-int)
     WIDE_DECIMAL_NODISCARD constexpr auto get_exponent() const -> int                { return my_exponent_part; }

    private:
      unsigned long long my_mantissa_part { }; // NOLINT(readability-identifier-naming,google-runtime-int)
      int                my_exponent_part { }; // NOLINT(readability-identifier-naming)
    };

    #if !defined(WIDE_DECIMAL_DISABLE_CACHED_CONSTANTS)
    // Static data initializer
    struct initializer
    {
      initializer() noexcept
      {
        static_cast<void>(decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>::my_value_pi());
        static_cast<void>(decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>::my_value_ln_two());
      }

      initializer(const initializer&) = delete;
      initializer(initializer&&) = delete;

      auto operator=(const initializer&) -> initializer& = delete;
      auto operator=(initializer&&) noexcept -> initializer& = delete;

      ~initializer() noexcept = default;

      auto do_nothing() const noexcept -> void
      {
        // Do nothing on purpose.
      }
    };

    static const initializer my_initializer;
    #endif

  public:
    // Default constructor.
    constexpr decwide_t() : my_data     (),
                            my_exp      (static_cast<exponent_type>(0)),
                            my_neg      (false),
                            my_fpclass  (fpclass_type::decwide_t_finite),
                            my_prec_elem(decwide_t_elem_number) { }

    // Constructors from built-in unsigned integral types.
    template<typename UnsignedIntegralType,
             typename std::enable_if<(    std::is_integral<UnsignedIntegralType>::value
                                      &&  std::is_unsigned<UnsignedIntegralType>::value
                                      && (std::numeric_limits<UnsignedIntegralType>::digits <= std::numeric_limits<limb_type>::digits))>::type const* = nullptr>
    decwide_t(const UnsignedIntegralType u) // NOLINT(google-explicit-constructor,hicpp-explicit-conversions)
      : my_data     (decwide_t_elem_number),
        my_exp      (static_cast<exponent_type>(0)),
        my_neg      (false),
        my_fpclass  (fpclass_type::decwide_t_finite),
        my_prec_elem(decwide_t_elem_number)
    {
      const auto u_is_less_than_mask =
        (
          static_cast<limb_type>(u) < static_cast<limb_type>(decwide_t_elem_mask)
        );

      if(u_is_less_than_mask)
      {
        my_data[0U] = static_cast<limb_type>(u);
      }
      else
      {
        my_data[0U] = static_cast<limb_type>(u / static_cast<limb_type>(decwide_t_elem_mask));
        my_data[1U] = static_cast<limb_type>(u % static_cast<limb_type>(decwide_t_elem_mask));

        my_exp = static_cast<exponent_type>(decwide_t_elem_digits10);
      }
    }

    // Constructors from built-in unsigned integral types.
    template<typename UnsignedIntegralType,
             typename std::enable_if<(    std::is_integral<UnsignedIntegralType>::value
                                      &&  std::is_unsigned<UnsignedIntegralType>::value
                                      && (std::numeric_limits<limb_type>::digits < std::numeric_limits<UnsignedIntegralType>::digits))>::type const* = nullptr>
    decwide_t(const UnsignedIntegralType u) : my_data     (), // NOLINT(google-explicit-constructor,hicpp-explicit-conversions)
                                              my_exp      (static_cast<exponent_type>(0)),
                                              my_neg      (false),
                                              my_fpclass  (fpclass_type::decwide_t_finite),
                                              my_prec_elem(decwide_t_elem_number)
    {
      from_unsigned_long_long(u);
    }

    // Constructors from built-in signed integral types.
    template<typename SignedIntegralType,
             typename std::enable_if<(   std::is_integral<SignedIntegralType>::value
                                      && std::is_signed  <SignedIntegralType>::value)>::type const* = nullptr>
    decwide_t(const SignedIntegralType n) : my_data     (), // NOLINT(google-explicit-constructor,hicpp-explicit-conversions)
                                            my_exp      (static_cast<exponent_type>(0)),
                                            my_neg      (n < static_cast<signed long long>(0)), // NOLINT(google-runtime-int)
                                            my_fpclass  (fpclass_type::decwide_t_finite),
                                            my_prec_elem(decwide_t_elem_number)
    {
      const auto u =
        static_cast<unsigned long long> // NOLINT(google-runtime-int)
        (
          ((!my_neg) ?                static_cast<unsigned long long>(n)   // NOLINT(google-runtime-int)
                     : detail::negate(static_cast<unsigned long long>(n))) // NOLINT(google-runtime-int)
        );

      from_unsigned_long_long(u);
    }

    // Constructors from built-in floating-point types.
    template<typename FloatingPointType,
              typename std::enable_if<std::is_floating_point<FloatingPointType>::value == true>::type const* = nullptr>
    decwide_t(const FloatingPointType f) : my_data     (), // NOLINT(google-explicit-constructor,hicpp-explicit-conversions)
                                           my_exp      (static_cast<exponent_type>(0)),
                                           my_neg      (false),
                                           my_fpclass  (fpclass_type::decwide_t_finite),
                                           my_prec_elem(decwide_t_elem_number)
    {
      from_builtin_float_type(f);
    }

    #if !defined(WIDE_DECIMAL_DISABLE_CONSTRUCT_FROM_STRING)
    // Constructors from character representations.
    explicit decwide_t(const char* s) : my_data     (),
                                        my_exp      (static_cast<exponent_type>(0)),
                                        my_neg      (false),
                                        my_fpclass  (fpclass_type::decwide_t_finite),
                                        my_prec_elem(decwide_t_elem_number)
    {
      static_cast<void>(rd_string(s));
    }

    #endif // !WIDE_DECIMAL_DISABLE_CONSTRUCT_FROM_STRING

    // Copy constructor.
    constexpr decwide_t(const decwide_t& other) : my_data     (other.my_data),
                                                  my_exp      (other.my_exp),
                                                  my_neg      (other.my_neg),
                                                  my_fpclass  (other.my_fpclass),
                                                  my_prec_elem(other.my_prec_elem) { }

    // Move constructor.
    constexpr decwide_t(decwide_t&& other) noexcept : my_data     (static_cast<representation_type&&>(other.my_data)),
                                                      my_exp      (other.my_exp),
                                                      my_neg      (other.my_neg),
                                                      my_fpclass  (other.my_fpclass),
                                                      my_prec_elem(other.my_prec_elem) { }

    // Constructor from floating-point class type, even though
    // (at the moment) decwide_t instances can only be finite.
    explicit constexpr decwide_t(fpclass_type) // NOLINT(hicpp-named-parameter,readability-named-parameter)
      : my_data     (),
        my_exp      (0),
        my_neg      (false),
        my_fpclass  (fpclass_type::decwide_t_finite),
        my_prec_elem(decwide_t_elem_number) { }

  private:
    // Constructor from mantissa and exponent.
    explicit decwide_t(const InternalFloatType mantissa,
                       const exponent_type     exponent)
      : my_data     (),
        my_exp      (static_cast<exponent_type>(0)),
        my_neg      (false),
        my_fpclass  (fpclass_type::decwide_t_finite),
        my_prec_elem(decwide_t_elem_number)
    {
      // Create a decwide_t from mantissa and exponent.
      // This constructor is intended to maintain the
      // full precision of the InternalFloatType.

      const auto delta_zero =
        static_cast<InternalFloatType>
        (
          (
              (std::numeric_limits<InternalFloatType>::min)()
            * (static_cast<InternalFloatType>(1) + std::numeric_limits<InternalFloatType>::epsilon())
          )
        );

      using std::fabs;

      const auto mantissa_is_iszero = (fabs(mantissa) < delta_zero);

      if(mantissa_is_iszero)
      {
        my_data.fill(static_cast<limb_type>(UINT8_C(0)));
      }
      else
      {
        const auto b_neg = (mantissa < static_cast<InternalFloatType>(0));

        InternalFloatType d = ((!b_neg) ? mantissa : -mantissa);
        exponent_type     e = exponent;

        constexpr InternalFloatType f10(static_cast<std::uint_fast8_t>(UINT8_C(10)));

        while(d > f10)                                  { d /= f10; ++e; }
        while(d < static_cast<InternalFloatType>(1.0F)) { d *= f10; --e; }

        {
          auto shift = static_cast<std::int32_t>(e % static_cast<std::int32_t>(decwide_t_elem_digits10));

          while(static_cast<std::int32_t>(shift % decwide_t_elem_digits10) != static_cast<std::int32_t>(0))
          {
            d *= f10;
            --e;
            --shift;
          }
        }

        my_exp = e;
        my_neg = b_neg;

        constexpr auto digit_loops =
          static_cast<std::int32_t>
          (
              static_cast<std::int32_t>(  static_cast<std::int32_t>(std::numeric_limits<InternalFloatType>::max_digits10)
                                        / static_cast<std::int32_t>(decwide_t_elem_digits10))
            + static_cast<std::int32_t>(static_cast<std::int32_t>(  static_cast<std::int32_t>(std::numeric_limits<InternalFloatType>::max_digits10)
                                                                  % static_cast<std::int32_t>(decwide_t_elem_digits10)) != 0 ? 1 : 0)
          );

        using local_size_type = typename representation_type::size_type;

        local_size_type limb_index;

        for(  limb_index = static_cast<local_size_type>(0);
              limb_index < static_cast<local_size_type>(digit_loops);
            ++limb_index)
        {
          const auto n = static_cast<limb_type>(d);

          my_data[limb_index]  = static_cast<limb_type>(n);
          d                   -= static_cast<InternalFloatType>(n);
          d                   *= static_cast<InternalFloatType>(decwide_t_elem_mask);
        }

        std::fill(my_data.begin() + static_cast<std::ptrdiff_t>(limb_index),
                  my_data.end(),
                  static_cast<limb_type>(UINT8_C(0)));
      }
    }

  public:
    ~decwide_t() = default;

    // Assignment operator.
    auto operator=(const decwide_t& other) -> decwide_t& // NOLINT(cert-oop54-cpp)
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
    auto operator=(decwide_t&& other) noexcept -> decwide_t&
    {
      my_data      = static_cast<representation_type&&>(other.my_data);
      my_exp       = other.my_exp;
      my_neg       = other.my_neg;
      my_fpclass   = other.my_fpclass;
      my_prec_elem = other.my_prec_elem;

      return *this;
    }

    WIDE_DECIMAL_NODISCARD auto  representation()       noexcept ->       representation_type& { return my_data; }
    WIDE_DECIMAL_NODISCARD auto  representation() const noexcept -> const representation_type& { return my_data; }
    WIDE_DECIMAL_NODISCARD auto crepresentation() const noexcept -> const representation_type& { return my_data; }

    // Binary arithmetic operators.
    auto operator+=(const decwide_t& v) -> decwide_t& // NOLINT(readability-function-cognitive-complexity)
    {
      // TBD: Eliminate the temporary storage array my_n_data_for_add_sub.

      // TBD: Limit the length of add/sub to only those ranges needed,
      // whereby propagate borrow/carry may be necessary as well.

      if(iszero())
      {
        return operator=(v);
      }

      const auto prec_elems_for_add_sub =
        static_cast<std::int32_t>
        (
          (std::min)(my_prec_elem, v.my_prec_elem)
        );

      // Get the offset for the add/sub operation.
      const auto max_delta_exp =
        static_cast<exponent_type>
        (
          static_cast<exponent_type>(prec_elems_for_add_sub) * decwide_t_elem_digits10
        );

      using local_unsigned_exponent_wrap_type = detail::unsigned_wrap<unsigned_exponent_type, exponent_type>;

      local_unsigned_exponent_wrap_type u_exp(  my_exp);
      local_unsigned_exponent_wrap_type v_exp(v.my_exp);

      const local_unsigned_exponent_wrap_type ofs_exp = (u_exp - v_exp);

      // Check if the operation is out of range, requiring special handling.
      if(   v.iszero()
         || ((!ofs_exp.get_is_neg()) && (ofs_exp.get_value_unsigned() >= static_cast<unsigned_exponent_type>(max_delta_exp))))
      {
        // Result is *this unchanged since v is negligible compared to *this.
        return *this;
      }

      if((ofs_exp.get_is_neg()) && (ofs_exp.get_value_unsigned() >= static_cast<unsigned_exponent_type>(max_delta_exp)))
      {
        // Result is *this = v since *this is negligible compared to v.
        return operator=(v);
      }

      // Do the add/sub operation.

      typename representation_type::pointer       p_u    =   my_data.data();
      typename representation_type::const_pointer p_v    = v.my_data.data();
      bool                                        b_copy = false;
      const std::int32_t                          ofs    = ((!ofs_exp.get_is_neg()) ? +static_cast<std::int32_t>(ofs_exp.get_value_unsigned() / static_cast<unsigned_exponent_type>(decwide_t_elem_digits10))
                                                                                    : -static_cast<std::int32_t>(ofs_exp.get_value_unsigned() / static_cast<unsigned_exponent_type>(decwide_t_elem_digits10)));

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

        using const_limb_pointer_type = typename std::add_const<limb_type*>::type;

        // Addition.
        const limb_type carry =
          detail::eval_add_n(p_u,
                             const_limb_pointer_type(p_u),
                             const_limb_pointer_type(p_v),
                             prec_elems_for_add_sub);

        if(b_copy)
        {
          #if (defined(__GNUC__) && !defined(__clang__) && (__GNUC__ >= 12))
          const auto memmove_dif =
            static_cast<std::ptrdiff_t>
            (
                static_cast<std::ptrdiff_t>(prec_elems_for_add_sub)
              * static_cast<std::ptrdiff_t>(sizeof(limb_type))
            );

          std::memmove(my_data.data(), my_n_data_for_add_sub.data(), static_cast<std::size_t>(memmove_dif));
          #else
          std::copy(my_n_data_for_add_sub.data(),
                    my_n_data_for_add_sub.data() + static_cast<std::size_t>(prec_elems_for_add_sub),
                    my_data.begin());
          #endif

          my_exp = v.my_exp;
        }

        if(carry != static_cast<limb_type>(0U))
        {
          // There needs to be a carry into the element -1 of the array data.
          // But since this can't be done, shift the data to make place for the
          // carry result and adjust the exponent accordingly.

          const auto offset_to_end =
            static_cast<std::ptrdiff_t>
            (
                static_cast<std::ptrdiff_t>(static_cast<std::ptrdiff_t>(my_data.size()) - static_cast<std::ptrdiff_t>(prec_elems_for_add_sub))
              + static_cast<std::ptrdiff_t>(INT32_C(1))
            );

          std::copy_backward(my_data.cbegin(),
                             my_data.cend() - offset_to_end,
                             my_data.end());

          my_data[0U] = carry;

          my_exp =
            static_cast<exponent_type>
            (
              my_exp + static_cast<exponent_type>(decwide_t_elem_digits10)
            );
        }
      }
      else
      {
        // Subtract v from *this, where the data array of either *this or v
        // might have to be treated with a positive, negative or zero offset.
        if(       (ofs >  static_cast<std::int32_t>(0))
           || (   (ofs == static_cast<std::int32_t>(0))
               && (detail::compare_ranges(  my_data.data(),
                                          v.my_data.data(),
                                          static_cast<std::uint_fast32_t>(prec_elems_for_add_sub)) > static_cast<std::int_fast8_t>(0))))
        {
          // In this case, |u| > |v| and ofs is positive.
          // Copy the data of v, shifted down to a lower value
          // into the data array m_n. Set the operand pointer p_v
          // to point to the copied, shifted data m_n.
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
                    v.my_data.cbegin() + static_cast<std::ptrdiff_t>(prec_elems_for_add_sub),
                    my_n_data_for_add_sub.begin());
          p_u    = my_n_data_for_add_sub.data();
          p_v    = my_data.data();
          b_copy = true;
        }

        // Subtraction.
        {
          using const_limb_pointer_type = typename std::add_const<limb_type*>::type;

          const auto has_borrow =
            detail::eval_subtract_n(p_u,
                                    const_limb_pointer_type(p_u),
                                    const_limb_pointer_type(p_v),
                                    prec_elems_for_add_sub);

          static_cast<void>(has_borrow);
        }

        if(b_copy)
        {
          std::copy(my_n_data_for_add_sub.cbegin(),
                    my_n_data_for_add_sub.cbegin() + static_cast<std::ptrdiff_t>(prec_elems_for_add_sub),
                    my_data.begin());
          my_exp  = v.my_exp;
          my_neg  = v.my_neg;
        }

        // Is it necessary to justify the data?
        const auto first_nonzero_elem = // NOLINT(llvm-qualified-auto,readability-qualified-auto)
          std::find_if(my_data.cbegin(),
                       my_data.cbegin() + static_cast<std::ptrdiff_t>(prec_elems_for_add_sub),
                       [](const limb_type& d) // NOLINT(modernize-use-trailing-return-type)
                       {
                         return (d != static_cast<limb_type>(UINT8_C(0)));
                       });

        if(first_nonzero_elem != my_data.cbegin())
        {
          if(first_nonzero_elem == (my_data.cbegin() + static_cast<std::ptrdiff_t>(prec_elems_for_add_sub)))
          {
            // This result of the subtraction is exactly zero (within precision).
            // Reset the sign and the exponent.
            my_neg = false;
            my_exp = static_cast<exponent_type>(0);
          }
          else
          {
            // Justify the data
            const auto sj =
              static_cast<std::ptrdiff_t>(first_nonzero_elem - my_data.cbegin());

            std::copy(my_data.cbegin() + static_cast<std::ptrdiff_t>(sj),
                      my_data.cend(),
                      my_data.begin());

            std::fill(my_data.end() - static_cast<std::ptrdiff_t>(sj),
                      my_data.end(),
                      static_cast<limb_type>(0));

            my_exp =
              static_cast<exponent_type>
              (
                  my_exp
                - static_cast<exponent_type>
                  (
                    sj * static_cast<std::ptrdiff_t>(decwide_t_elem_digits10)
                  )
              );
          }
        }

        // Check for underflow.
        if(iszero())
        {
          *this = zero<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>();
        }
      }

      return *this;
    }

    auto operator-=(const decwide_t& v) -> decwide_t&
    {
      // Use *this - v = -(-*this + v).
      return (negate().operator+=(v)).negate();
    }

    auto operator*=(const decwide_t& v) -> decwide_t&
    {
      // Evaluate the sign of the result.
      const auto b_result_is_neg = (my_neg != v.my_neg);

      // Artificially set the sign of the result to be positive.
      my_neg = false;

      // Handle multiplication by zero.
      if(iszero() || v.iszero())
      {
        *this = zero<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>();
      }
      else
      {
        // Set the exponent of the result.
        using local_unsigned_wrap_type = detail::unsigned_wrap<unsigned_exponent_type, exponent_type>;

        local_unsigned_wrap_type u_exp(  my_exp);
        local_unsigned_wrap_type v_exp(v.my_exp);

        const local_unsigned_wrap_type result_exp = (u_exp + v_exp);

        if((!result_exp.get_is_neg()) && (result_exp.get_value_unsigned() >= decwide_t_max_exp10))
        {
          operator=(my_value_max());
        }
        else if((result_exp.get_is_neg()) && (result_exp.get_value_unsigned() >= decwide_t_max_exp10))
        {
          operator=(my_value_min());
        }
        else
        {
          my_exp =
            static_cast<exponent_type>
            (
              (!result_exp.get_is_neg())
                ?                static_cast<exponent_type>(result_exp.get_value_unsigned())
                : detail::negate(static_cast<exponent_type>(result_exp.get_value_unsigned()))
            );

          const auto prec_elems_for_multiply =
            static_cast<std::int32_t>
            (
              (std::min)(my_prec_elem, v.my_prec_elem)
            );

          eval_mul_dispatch_multiplication_method(v, prec_elems_for_multiply);
        }
      }

      // Set the sign of the result.
      my_neg = b_result_is_neg;

      return *this;
    }

    auto operator/=(const decwide_t& v) -> decwide_t&
    {
      const auto u_and_v_are_identical =
        (   (my_fpclass == v.my_fpclass)
         && (my_exp     == v.my_exp)
         && (detail::compare_ranges(  my_data.data(),
                                    v.my_data.data(),
                                    static_cast<std::uint_fast32_t>(decwide_t_elem_number)) == static_cast<std::int_fast8_t>(0)));

      if(u_and_v_are_identical)
      {
        const auto negate_one = (my_neg != v.my_neg);

        *this = one<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>();

        if(negate_one)
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
    auto add_unsigned_long_long(unsigned long long n) -> decwide_t& // NOLINT(google-runtime-int)
    {
      // Non-optimized addition of unsigned long long.
      static_cast<void>(operator+=(decwide_t(n)));

      return *this;
    }

    auto sub_unsigned_long_long(unsigned long long n) -> decwide_t& // NOLINT(google-runtime-int)
    {
      // Non-optimized subtraction of unsigned long long.
      static_cast<void>(operator-=(decwide_t(n)));

      return *this;
    }

    auto mul_unsigned_long_long(unsigned long long n) -> decwide_t& // NOLINT(google-runtime-int)
    {
      // Multiply *this with a constant unsigned long long.

      // Evaluate the sign of the result.
      const auto b_neg = my_neg;

      // Artificially set the sign of the result to be positive.
      my_neg = false;

      // Handle special cases like zero, inf and NaN.
      const auto b_n_is_zero = (n == static_cast<std::int32_t>(0));

      if(iszero() || b_n_is_zero)
      {
        // Multiplication by zero.
        return (*this = zero<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>());
      }

      if(n >= static_cast<unsigned long long>(decwide_t_elem_mask)) // NOLINT(google-runtime-int)
      {
        my_neg = b_neg;

        return operator*=(decwide_t(n));
      }

      if(n == static_cast<unsigned long long>(1U)) // NOLINT(google-runtime-int)
      {
        my_neg = b_neg;

        return *this;
      }

      // Set up the multiplication loop.
      const auto nn    = static_cast<limb_type>(n);
      const auto carry = detail::mul_loop_n(my_data.data(), nn, my_prec_elem);

      // Handle the carry and adjust the exponent.
      if(carry != static_cast<limb_type>(0U))
      {
        my_exp = static_cast<exponent_type>(my_exp + static_cast<exponent_type>(decwide_t_elem_digits10));

        // Shift the result of the multiplication one element to the right.
        std::copy_backward(my_data.cbegin(),
                           my_data.cbegin() + static_cast<std::ptrdiff_t>(static_cast<std::ptrdiff_t>(my_prec_elem) - static_cast<std::ptrdiff_t>(1)),
                           my_data.begin()  + static_cast<std::ptrdiff_t>(my_prec_elem));

        my_data.front() = static_cast<limb_type>(carry);
      }

      // Set the sign.
      my_neg = b_neg;

      return *this;
    }

    auto div_unsigned_long_long(unsigned long long n) -> decwide_t& // NOLINT(google-runtime-int)
    {
      // Divide *this by a constant unsigned long long.

      // Evaluate the sign of the result.
      const auto b_neg = my_neg;

      // Artificially set the sign of the result to be positive.
      my_neg = false;

      // Handle special cases of zero.
      if(n == static_cast<unsigned long long>(0U)) // NOLINT(google-runtime-int)
      {
        // Divide by 0.
        return (*this = zero<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>());
      }

      if(iszero())
      {
        return *this;
      }

      if(n >= static_cast<unsigned long long>(decwide_t_elem_mask)) // NOLINT(google-runtime-int)
      {
        my_neg = b_neg;

        return operator/=(decwide_t(n));
      }

      const auto nn = static_cast<limb_type>(n);

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
                    my_data.cbegin() + static_cast<std::ptrdiff_t>(static_cast<std::ptrdiff_t>(my_prec_elem) - static_cast<std::ptrdiff_t>(1)),
                    my_data.begin());

          {
            using local_size_type = typename representation_type::size_type;

            const auto index_prev =
              static_cast<local_size_type>
              (
                static_cast<std::ptrdiff_t>(my_prec_elem) - static_cast<std::ptrdiff_t>(1)
              );

            const auto val_prev =
              static_cast<limb_type>
              (
                  static_cast<std::uint64_t>
                  (
                    prev * static_cast<std::uint64_t>(decwide_t_elem_mask)
                  )
                / nn
              );

            my_data[index_prev] = val_prev;
          }
        }
      }

      // Check for underflow.
      if(iszero())
      {
        return (*this = zero<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>());
      }

      // Set the sign of the result.
      my_neg = b_neg;

      return *this;
    }

    // Arithmetic operators with signed long long.
    auto add_signed_long_long(signed long long n) -> decwide_t& // NOLINT(google-runtime-int)
    {
      if(n < static_cast<signed long long>(0)) // NOLINT(google-runtime-int)
      {
        negate();
        add_unsigned_long_long(detail::negate(static_cast<unsigned long long>(n))); // NOLINT(google-runtime-int)
        negate();
      }
      else
      {
        add_unsigned_long_long(static_cast<unsigned long long>(n)); // NOLINT(google-runtime-int)
      }

      return *this;
    }

    auto sub_signed_long_long(signed long long n) -> decwide_t& // NOLINT(google-runtime-int)
    {
      return add_signed_long_long(static_cast<signed long long>(-n)); // NOLINT(google-runtime-int)
    }

    auto mul_signed_long_long(signed long long n) -> decwide_t& // NOLINT(google-runtime-int)
    {
      const auto b_neg = (n < static_cast<signed long long>(0)); // NOLINT(google-runtime-int)

      mul_unsigned_long_long
      (
        (!b_neg) ?                static_cast<unsigned long long>(n)  // NOLINT(google-runtime-int)
                 : detail::negate(static_cast<unsigned long long>(n)) // NOLINT(google-runtime-int)
      );

      return ((!b_neg) ? *this : negate());
    }

    auto div_signed_long_long(signed long long n) -> decwide_t& // NOLINT(google-runtime-int)
    {
      const auto b_neg = (n < static_cast<signed long long>(0)); // NOLINT(google-runtime-int)

      div_unsigned_long_long
      (
        (!b_neg) ?                static_cast<unsigned long long>(n)  // NOLINT(google-runtime-int)
                 : detail::negate(static_cast<unsigned long long>(n)) // NOLINT(google-runtime-int)
      );

      return ((!b_neg) ? *this : negate());
    }

    WIDE_DECIMAL_NODISCARD auto cmp(const decwide_t& v) const -> std::int_fast8_t // NOLINT(readability-function-cognitive-complexity)
    {
      // Compare v with *this.
      //         Return +1 for *this > v
      //                 0 for *this = v
      //                -1 for *this < v

      std::int_fast8_t n_result { };

      // Handle all *finite* cases only.
      if(iszero())
      {
        // The value of *this is zero and v is either zero or non-zero.
        n_result = (v.iszero() ? static_cast<std::int_fast8_t>(0)
                               : (v.my_neg ? static_cast<std::int_fast8_t>(1)
                                           : static_cast<std::int_fast8_t>(-1)));
      }
      else
      {
        if(v.iszero())
        {
          // The value of v is zero and *this is non-zero.
          n_result = (my_neg ? static_cast<std::int_fast8_t>(-1)
                             : static_cast<std::int_fast8_t>(1));
        }
        else
        {
          // Both *this and v are non-zero.

          if(my_neg != v.my_neg)
          {
            // The signs are different.
            n_result = (my_neg ? static_cast<std::int_fast8_t>(-1)
                               : static_cast<std::int_fast8_t>(1));
          }
          else
          {
            if(my_exp != v.my_exp)
            {
              // The signs are the same and the exponents are different.
              const auto val_cmp_exp =
                static_cast<std::int_fast8_t>
                (
                  ((my_exp < v.my_exp) ? static_cast<std::int_fast8_t>(1)
                                       : static_cast<std::int_fast8_t>(-1))
                );

              n_result =
                static_cast<std::int_fast8_t>
                (
                  my_neg ? val_cmp_exp : static_cast<std::int_fast8_t>(-val_cmp_exp)
                );
            }
            else
            {
              // The signs are the same and the exponents are the same.
              // Compare the data.

              // TBD: Compare the limbs and on the final limb (if reached)
              // assess the result of comparison on the relevant digit-level.
              // This might be needed within the compare_ranges subroutine.
              const auto val_cmp_data =
                detail::compare_ranges(  my_data.data(),
                                       v.my_data.data(),
                                       static_cast<std::uint_fast32_t>(decwide_t_elem_number));

              n_result =
                static_cast<std::int_fast8_t>
                (
                  (!my_neg) ? val_cmp_data : static_cast<std::int_fast8_t>(-val_cmp_data)
                );
            }
          }
        }
      }

      return n_result;
    }

    // Specific special values.
    static constexpr auto my_value_max() -> decwide_t { return from_lst( { static_cast<limb_type>(UINT8_C(9)) }, decwide_t_max_exp10 ); } // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
    static constexpr auto my_value_min() -> decwide_t { return from_lst( { static_cast<limb_type>(UINT8_C(1)) }, decwide_t_min_exp10 ); }

    static constexpr auto my_value_eps() -> decwide_t
    {
      return
        from_lst
        (
          { static_cast<limb_type>(detail::pow10_maker(decwide_t_power10_limb0_for_epsilon())) },
          static_cast<exponent_type>(static_cast<std::int32_t>(-decwide_t_digits10_for_epsilon()))
        );
    }

    #if !defined(WIDE_DECIMAL_DISABLE_CACHED_CONSTANTS)
    static auto my_value_pi() -> const decwide_t&
    {
      my_initializer.do_nothing();

      static const decwide_t
        val
        (
          calc_pi<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>()
        );

      return val;
    }

    static auto my_value_ln_two() -> const decwide_t&
    {
      my_initializer.do_nothing();

      static const decwide_t
        val
        (
          calc_ln_two<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>()
        );

      return val;
    }
    #endif

    auto precision(std::int32_t prec_digits) noexcept -> void
    {
      const auto elems_needed_for_digits =
        static_cast<std::int32_t>
        (
            static_cast<std::int32_t>  (prec_digits / decwide_t_elem_digits10)
          + static_cast<std::int32_t>(((prec_digits % decwide_t_elem_digits10) != 0) ? 1 : 0)
        );

      {
        const auto elems_least = (std::max)(elems_needed_for_digits, static_cast<std::int32_t>(2));

        my_prec_elem = (std::min)(decwide_t_elem_number, elems_least);
      }
    }

    WIDE_DECIMAL_NODISCARD static constexpr auto get_precision(const decwide_t& x) noexcept -> std::int32_t
    {
      return static_cast<std::int32_t>(x.my_prec_elem * decwide_t_elem_digits10);
    }

    auto swap(decwide_t& other) noexcept -> void
    {
      if(this != &other)
      {
        const decwide_t tmp(*this);

        *this = other;

        other = tmp;
      }
    }

    auto swap(decwide_t&& other) noexcept -> void
    {
      my_data.swap(static_cast<representation_type&&>(other.my_data));

      std::swap(my_exp,       other.my_exp);
      std::swap(my_neg,       other.my_neg);
      std::swap(my_fpclass,   other.my_fpclass);
      std::swap(my_prec_elem, other.my_prec_elem);
    }

    // Elementary primitives.
    auto calculate_inv() -> decwide_t&
    {
      // Compute the inverse of *this.
      const auto b_neg = my_neg;

      my_neg = false;

      // Handle special cases of zero.
      if(iszero())
      {
        return (*this = zero<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>());
      }

      if(isone())
      {
        *this = ((!b_neg) ?  one<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>()
                          : -one<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>());

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
      {
        const auto one_over_d =
          static_cast<InternalFloatType>
          (
            static_cast<InternalFloatType>(1.0F) / dd
          );

        operator=(decwide_t(one_over_d, static_cast<exponent_type>(-ne)));
      }

      // Compute the inverse of *this. Quadratically convergent Newton-Raphson iteration
      // is used. During the iterative steps, the precision of the calculation is limited
      // to the minimum required in order to minimize the run-time.

      for(auto digits  = static_cast<std::int32_t>(std::numeric_limits<InternalFloatType>::digits10 - 1);
               digits  < static_cast<std::int32_t>(original_prec_elem * decwide_t_elem_digits10);
               digits *= static_cast<std::int32_t>(2))
      {
        // Adjust precision of the terms.
        const auto min_elem_digits10_plus_one =
          (std::min)
          (
            static_cast<std::int32_t>(decwide_t_elem_digits10 + 1),
            static_cast<std::int32_t>(INT8_C(9))
          );

        const auto new_prec_as_digits10 =
          static_cast<std::int32_t>
          (
              static_cast<std::int32_t>(digits * static_cast<std::int8_t>(INT8_C(2)))
            + min_elem_digits10_plus_one
          );

          precision(new_prec_as_digits10);
        x.precision(new_prec_as_digits10);

        // Next iteration of *this.
        operator=(*this * (two<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>() - (*this * x)));
      }

      my_neg = b_neg;

      my_prec_elem = original_prec_elem;

      return *this;
    }

    auto calculate_sqrt() -> decwide_t&
    {
      // Compute the square root of *this.

      if(isneg())
      {
        return (*this = zero<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>());
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
        dd /= static_cast<InternalFloatType>(10); // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
      }

      using std::sqrt;

      // Setup the iteration.
      // Estimate the square root using simple manipulations.
      const InternalFloatType sqd = sqrt(dd);

      const std::int32_t original_prec_elem = my_prec_elem;

      *this = decwide_t(sqd, static_cast<exponent_type>(ne / 2));

      // Estimate 1.0 / (2.0 * x0) using simple manipulations.
      const auto inv_half_sqd =
        static_cast<InternalFloatType>
        (
          static_cast<InternalFloatType>(0.5F) / sqd
        );

      const auto minus_half_ne =
        static_cast<exponent_type>
        (
          static_cast<exponent_type>(-ne) / static_cast<std::int8_t>(INT8_C(2))
        );

      decwide_t vi(inv_half_sqd, minus_half_ne);

      // Compute the square root of x. Coupled Newton iteration
      // as described in "Pi Unleashed" is used. During the
      // iterative steps, the precision of the calculation is
      // limited to the minimum required in order to minimize
      // the run-time.
      //
      // Book references:
      // http://www.jjj.de/pibook/pibook.html
      // http://www.springer.com/gp/book/9783642567353

      for(auto digits  = static_cast<std::int32_t>(std::numeric_limits<InternalFloatType>::digits10 - 1);
               digits  < static_cast<std::int32_t>(original_prec_elem * decwide_t_elem_digits10);
               digits *= static_cast<std::int32_t>(INT8_C(2)))
      {
        // Adjust precision of the terms.
        const auto min_elem_digits10_plus_one =
          (std::min)
          (
            static_cast<std::int32_t>(decwide_t_elem_digits10 + 1),
            static_cast<std::int32_t>(INT8_C(9))
          );

        const auto new_prec_as_digits10 =
          static_cast<std::int32_t>
          (
              static_cast<std::int32_t>(digits * static_cast<std::int8_t>(INT8_C(2)))
            + min_elem_digits10_plus_one
          );

           precision(new_prec_as_digits10);
        vi.precision(new_prec_as_digits10);
         x.precision(new_prec_as_digits10);

        // Next iteration of vi
        vi += vi * (((*this * vi) * static_cast<std::int32_t>(INT8_C(-2))) + one<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>());

        // Next iteration of *this
        *this += (vi * (-((*this) * (*this)) + x));
      }

      my_prec_elem = original_prec_elem;

      return *this;
    }

    auto calculate_rootn_inv(std::int32_t p) -> decwide_t&
    {
      if(p < static_cast<std::int32_t>(0))
      {
        *this = pow(*this, static_cast<std::int32_t>(-p));
      }
      else if((p == static_cast<std::int32_t>(0)) || isneg())
      {
        *this = std::numeric_limits<decwide_t>::quiet_NaN();
      }
      else if(p > static_cast<std::int32_t>(1))
      {
        // Compute the value of [1 / (rootn of x)] with n = p.

        // Use the original value of *this for iteration below.
        decwide_t x(*this);

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
          dd /= static_cast<InternalFloatType>(10.0L); // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
        }

        const std::int32_t original_prec_elem = x.my_prec_elem;

        using std::pow;

        // Estimate the initial guess of one over the root using simple manipulations.
        const InternalFloatType one_over_rtn_d = pow(dd, static_cast<InternalFloatType>(-1) / static_cast<InternalFloatType>(p));

        // Set the result equal to the initial guess.
        *this = decwide_t(one_over_rtn_d, static_cast<exponent_type>(static_cast<exponent_type>(-ne) / p));

        for(auto digits  = static_cast<std::int32_t>(std::numeric_limits<InternalFloatType>::digits10 - 1);
                 digits  < static_cast<std::int32_t>(original_prec_elem * decwide_t_elem_digits10);
                 digits *= static_cast<std::int32_t>(2))
        {
          // Adjust precision of the terms.
          const auto min_elem_digits10_plus_one =
            (std::min)
            (
              static_cast<std::int32_t>(decwide_t_elem_digits10 + 1),
              static_cast<std::int32_t>(INT8_C(9))
            );

          const auto new_prec_as_digits10 =
            static_cast<std::int32_t>
            (
                static_cast<std::int32_t>(digits * static_cast<std::int8_t>(INT8_C(2)))
              + min_elem_digits10_plus_one
            );

            precision(new_prec_as_digits10);
          x.precision(new_prec_as_digits10);

          // Perform the next iteration.
          decwide_t
            term
            (
                (((-pow(*this, p) * x) + one<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>()) / p)
              + one<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>()
            );

          term.precision(new_prec_as_digits10);

          operator*=(term);
        }

        my_prec_elem = original_prec_elem;
      }

      return *this;
    }

    auto negate() -> decwide_t&
    {
      if(!iszero())
      {
        my_neg = (!my_neg);
      }

      return *this;
    }

    // Comparison functions.
    WIDE_DECIMAL_NODISCARD constexpr auto (isnan)   () const noexcept -> bool { return false; }
    WIDE_DECIMAL_NODISCARD constexpr auto (isinf)   () const noexcept -> bool { return false; }
    WIDE_DECIMAL_NODISCARD constexpr auto (isfinite)() const noexcept -> bool { return true; }

    WIDE_DECIMAL_NODISCARD constexpr auto iszero() const noexcept -> bool
    {
      return (my_data[0U] == static_cast<limb_type>(0U));
    }

    WIDE_DECIMAL_NODISCARD auto isone() const -> bool
    {
      // Check if the value of *this is identically 1 or very close to 1.

      const auto not_negative = (!my_neg);

      bool value_is_one = false;

      if(not_negative)
      {
        if((my_data[0U] == static_cast<limb_type>(1U)) && (my_exp == static_cast<exponent_type>(0)))
        {
          const auto it_non_zero = // NOLINT(llvm-qualified-auto,readability-qualified-auto)
            std::find_if(my_data.cbegin() + 1U,
                         my_data.cend(),
                         [](const limb_type& d) // NOLINT(modernize-use-trailing-return-type)
                         {
                           return (d != static_cast<limb_type>(0U));
                         });

          value_is_one = (it_non_zero == my_data.cend());
        }
        else if((my_data[0U] == static_cast<limb_type>(decwide_t_elem_mask - INT32_C(1))) && (my_exp == static_cast<exponent_type>(-decwide_t_elem_digits10)))
        {
          const auto it_non_nine = // NOLINT(llvm-qualified-auto,readability-qualified-auto)
            std::find_if(my_data.cbegin() + 1U,
                         my_data.cend(),
                         [](const limb_type& d) // NOLINT(modernize-use-trailing-return-type)
                         {
                           return (d != static_cast<limb_type>(decwide_t_elem_mask - INT32_C(1)));
                         });

          value_is_one = (it_non_nine == my_data.cend());
        }
      }

      return value_is_one;
    }

    WIDE_DECIMAL_NODISCARD auto isint() const -> bool
    {
      bool value_is_int { };

      if(my_fpclass != fpclass_type::decwide_t_finite)
      {
        value_is_int = false;
      }
      else
      {
        if(iszero())
        {
          value_is_int = true;
        }
        else
        {
          if(my_exp < static_cast<exponent_type>(0))
          {
            // Here, we have |*this| < 1, so *this can not be int.
            value_is_int = false;
          }
          else
          {
            using local_size_type = typename representation_type::size_type;

            const auto offset_decimal_part =
              static_cast<local_size_type>
              (
                  static_cast<local_size_type>(my_exp / decwide_t_elem_digits10)
                + static_cast<local_size_type>(UINT8_C(1))
              );

            if(offset_decimal_part >= static_cast<local_size_type>(decwide_t_elem_number))
            {
              // The number is too large to resolve the integer part.
              // It considered to be a pure integer.
              value_is_int = true;
            }
            else
            {
              const auto it_non_zero = // NOLINT(llvm-qualified-auto,readability-qualified-auto)
                std::find_if(my_data.cbegin() + static_cast<std::ptrdiff_t>(offset_decimal_part),
                             my_data.cend(),
                             [](const limb_type& d) // NOLINT(modernize-use-trailing-return-type)
                             {
                               return (d != static_cast<limb_type>(0U));
                             });

              value_is_int = (it_non_zero == my_data.cend());
            }
          }
        }
      }

      return value_is_int;
    }

    WIDE_DECIMAL_NODISCARD constexpr auto isneg() const -> bool { return my_neg; }
    WIDE_DECIMAL_NODISCARD constexpr auto ispos() const -> bool { return (!isneg()); }

    // Operators pre-increment and pre-decrement.
    auto operator++() -> decwide_t& { return *this += one<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>(); }
    auto operator--() -> decwide_t& { return *this -= one<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>(); }

    // Operators post-increment and post-decrement.
    auto operator++(int) -> decwide_t { const decwide_t w(*this); static_cast<void>(++(*this)); return w; }
    auto operator--(int) -> decwide_t { const decwide_t w(*this); static_cast<void>(--(*this)); return w; }

    // Conversion routines.
    auto extract_parts(InternalFloatType& mantissa, exponent_type& exponent) const -> void
    {
      // Extracts the mantissa as a decimal part less in magnitude
      // than 1 and the base-10 exponent parts of this decwide_t.
      // For instance 45.67e8 will be extracted as 0.4567 * e10.

      exponent = my_exp;
      mantissa = static_cast<InternalFloatType>(0.0F);

      auto p10 = static_cast<limb_type>(1U);

      {
        auto d0 = my_data[0U];

        for(;;)
        {
          d0 = static_cast<limb_type>(d0 / static_cast<limb_type>(UINT8_C(10)));

          if(d0 == static_cast<limb_type>(0U))
          {
            break;
          }

          p10 = static_cast<limb_type>(p10 * static_cast<limb_type>(UINT8_C(10)));

          ++exponent;
        }
      }

      auto scale =
        static_cast<InternalFloatType>
        (
          static_cast<InternalFloatType>(1.0F) / static_cast<InternalFloatType>(p10)
        );

      constexpr auto digit_loops =
        static_cast<std::int32_t>
        (
            static_cast<std::int32_t>(  static_cast<std::int32_t>(std::numeric_limits<InternalFloatType>::max_digits10)
                                      / static_cast<std::int32_t>(decwide_t_elem_digits10))
          + static_cast<std::int32_t>(static_cast<std::int32_t>(  static_cast<std::int32_t>(std::numeric_limits<InternalFloatType>::max_digits10)
                                                                % static_cast<std::int32_t>(decwide_t_elem_digits10)) != 0 ? 1 : 0)
        );

      using local_size_type = typename representation_type::size_type;

      for(auto   limb_index = static_cast<local_size_type>(0U);
               ((limb_index < my_data.size()) && (limb_index < static_cast<local_size_type>(digit_loops)));
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

    WIDE_DECIMAL_NODISCARD auto extract_integer_part() const -> decwide_t
    {
      // Compute the signed integer part of x.

      if(my_exp < static_cast<exponent_type>(0))
      {
        // The absolute value of the number is smaller than 1.
        // Thus the integer part is zero.
        return zero<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>();
      }

      if(my_exp >= static_cast<exponent_type>(decwide_t_digits10 - 1))
      {
        // The number is too large to resolve the integer part.
        // Thus it is already a pure integer part.
        return *this;
      }

      // Make a local copy.
      decwide_t x = *this;

      // Clear out the decimal portion
      const auto first_clear = static_cast<std::ptrdiff_t>((static_cast<std::ptrdiff_t>(x.my_exp) / static_cast<std::ptrdiff_t>(decwide_t_elem_digits10)) + 1);
      const auto last_clear  = static_cast<std::ptrdiff_t>(decwide_t_elem_number);

      std::fill(x.my_data.begin() + first_clear,
                x.my_data.begin() + last_clear,
                static_cast<limb_type>(0U));

      return x;
    }

    WIDE_DECIMAL_NODISCARD auto extract_long_double() const -> long double
    {
      // Returns the long double conversion of a decwide_t.

      auto ld = static_cast<long double>(0.0L);

      // Check for non-normal decwide_t.
      const decwide_t xx(fabs(*this));

      const auto is_essentially_zero =
        (
              iszero()
          || (xx < long_double_min<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>())
        );

      // Check for zero decwide_t.
      if(!is_essentially_zero)
      {
        if(xx > long_double_max<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>())
        {
          // Check if decwide_t exceeds the maximum of long double.
          ld = std::numeric_limits<long double>::infinity();
        }
        else
        {
          ld = static_cast<long double>(my_data[0U]);

          auto scale = static_cast<long double>(1.0L); // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)

          for(auto i = decwide_t_elem_digits10;
                   i < static_cast<std::int32_t>(std::numeric_limits<long double>::max_digits10 + 2);
                   i = static_cast<std::int32_t>(i + decwide_t_elem_digits10))
          {
            scale = static_cast<long double>(scale / static_cast<long double>(decwide_t_elem_mask));

            {
              using local_size_type = typename representation_type::size_type;

              const auto idx = static_cast<std::int32_t>(i / decwide_t_elem_digits10);

              if(idx == static_cast<std::int32_t>(my_data.size()))
              {
                break;
              }

              ld =
                static_cast<long double>
                (
                  ld + static_cast<long double>(static_cast<long double>(my_data[static_cast<local_size_type>(idx)]) * scale)
                );
            }
          }
        }

        if(my_exp != static_cast<exponent_type>(0))
        {
          using std::pow;

          ld =
            static_cast<long double>
            (
                ld
              * pow(static_cast<long double>(10.0L), static_cast<long double>(my_exp)) // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
            );
        }

        if(my_neg)
        {
          ld = -ld;
        }
      }

      return ld;
    }

    WIDE_DECIMAL_NODISCARD auto extract_signed_long_long() const -> signed long long // NOLINT(google-runtime-int)
    {
      // Extracts a signed long long from *this.
      // If either (x > maximum of signed long long)
      // or (x < minimum of signed long long), then
      // the maximum or minimum of signed long long
      // is returned accordingly.

      auto signed_long_long_result = static_cast<signed long long>(0); // NOLINT(google-runtime-int)

      if(my_exp >= static_cast<exponent_type>(0))
      {
        const auto b_neg = isneg();

        if((!b_neg) && (*this > signed_long_long_max<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>()))
        {
          signed_long_long_result = (std::numeric_limits<signed long long>::max)(); // NOLINT(google-runtime-int)
        }
        else
        {
          if(b_neg &&  (*this < signed_long_long_min<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>()))
          {
            signed_long_long_result = (std::numeric_limits<signed long long>::min)(); // NOLINT(google-runtime-int)
          }
          else
          {
            // Extract the data of *this into an unsigned long long value.
            decwide_t xn(*this);

            xn.eval_round_self();

            xn = fabs(xn.extract_integer_part());

            auto val = static_cast<unsigned long long>(xn.my_data[0]); // NOLINT(google-runtime-int)

            const auto imax =
              (std::min)
              (
                static_cast<std::int32_t>(static_cast<std::int32_t>(xn.my_exp) / decwide_t_elem_digits10),
                static_cast<std::int32_t>(decwide_t_elem_number - static_cast<std::int32_t>(1))
              );

            using local_size_type = typename representation_type::size_type;

            for(auto  limb_index  = static_cast<local_size_type>(UINT8_C(1));
                      limb_index <= static_cast<local_size_type>(static_cast<std::uint32_t>(imax));
                    ++limb_index)
            {
              val *= static_cast<unsigned long long>(decwide_t_elem_mask);    // NOLINT(google-runtime-int)
              val += static_cast<unsigned long long>(xn.my_data[limb_index]); // NOLINT(google-runtime-int)
            }

            signed_long_long_result = ((!b_neg) ? static_cast<signed long long>(val) // NOLINT(google-runtime-int)
                                                : static_cast<signed long long>(-static_cast<signed long long>(val))); // NOLINT(google-runtime-int)
          }
        }
      }

      return signed_long_long_result;
    }

    WIDE_DECIMAL_NODISCARD auto extract_unsigned_long_long() const -> unsigned long long // NOLINT(google-runtime-int)
    {
      // Extracts an unsigned long long from *this.
      // If x exceeds the maximum of unsigned long long,
      // then the maximum of unsigned long long is returned.
      // If x is negative, then the unsigned long long cast of
      // the signed long long extracted value is returned.

      auto unsigned_long_long_result = static_cast<unsigned long long>(0U); // NOLINT(google-runtime-int)

      if(isneg())
      {
        unsigned_long_long_result = static_cast<unsigned long long>(extract_signed_long_long()); // NOLINT(google-runtime-int)
      }
      else
      {
        if(my_exp >= static_cast<exponent_type>(0))
        {
          decwide_t xn(*this);

          xn.eval_round_self();

          xn = xn.extract_integer_part();

          if(xn > unsigned_long_long_max<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>())
          {
            unsigned_long_long_result = (std::numeric_limits<unsigned long long>::max)(); // NOLINT(google-runtime-int)
          }
          else
          {
            // Extract the data into an unsigned long long value.
            auto val = static_cast<unsigned long long>(xn.my_data[0]); // NOLINT(google-runtime-int)

            const auto imax =
              static_cast<std::int32_t>
              (
                (std::min)(static_cast<std::int32_t>(static_cast<std::int32_t>(xn.my_exp) / decwide_t_elem_digits10),
                           static_cast<std::int32_t>(decwide_t_elem_number - static_cast<std::int32_t>(1)))
              );

            using local_size_type = typename representation_type::size_type;

            for(auto   limb_index  = static_cast<local_size_type>(UINT8_C(1));
                       limb_index <= static_cast<local_size_type>(static_cast<std::uint32_t>(imax));
                     ++limb_index)
            {
              val *= static_cast<unsigned long long>(decwide_t_elem_mask);    // NOLINT(google-runtime-int)
              val += static_cast<unsigned long long>(xn.my_data[limb_index]); // NOLINT(google-runtime-int)
            }

            unsigned_long_long_result = val;
          }
        }
      }

      return unsigned_long_long_result;
    }

    explicit operator long double() const { return                     extract_long_double(); }
    explicit operator double     () const { return static_cast<double>(extract_long_double()); }
    explicit operator float      () const { return static_cast<float> (extract_long_double()); }

    template<typename IntegralType,
             typename = typename std::enable_if<std::is_integral<IntegralType>::value>::type>
    explicit constexpr operator IntegralType() const
    {
      return (std::is_signed<IntegralType>::value
               ? static_cast<IntegralType>(extract_signed_long_long())
               : static_cast<IntegralType>(extract_unsigned_long_long()));
    }

    // Cast operator to built-in Boolean type.
    explicit constexpr operator bool() const { return (!iszero()); }

    static auto from_lst(      std::initializer_list<limb_type> limb_values,
                         const exponent_type                    e = static_cast<exponent_type>(0),
                         const bool                             is_neg = false) -> decwide_t
    {
      // Initialization from initializer list of limbs,
      // exponent value (normed to limb granularity)
      // and optional sign flag.
      decwide_t a;

      if(limb_values.size() < a.my_data.size())
      {
        std::copy(limb_values.begin(),
                  limb_values.end(),
                  a.my_data.begin());

        std::fill(a.my_data.begin() + limb_values.size(),
                  a.my_data.end(),
                  static_cast<limb_type>(0U));
      }
      else
      {
        std::copy(limb_values.begin(),
                  limb_values.begin() + a.my_data.size(),
                  a.my_data.begin());
      }

      a.my_exp       = e;
      a.my_neg       = is_neg;
      a.my_fpclass   = fpclass_type::decwide_t_finite;
      a.my_prec_elem = decwide_t_elem_number;

      return a;
    }

  private:
    #if !defined(WIDE_DECIMAL_DISABLE_DYNAMIC_MEMORY_ALLOCATION)
    #else
    static std::array<limb_type,      static_cast<std::size_t>((decwide_t_elems_for_kara - 1) * 2)>                                                                                               my_school_mul_pool;  // NOLINT(cppcoreguidelines-avoid-non-const-global-variables)
    static std::array<limb_type,      static_cast<std::size_t>(detail::a029750::a029750_as_constexpr(static_cast<std::uint32_t>(static_cast<std::uint32_t>(decwide_t_elems_for_fft - 1)) * 8UL))> my_kara_mul_pool;    // NOLINT(cppcoreguidelines-avoid-non-const-global-variables,cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
    static std::array<fft_float_type, static_cast<std::size_t>(detail::a000079::a000079_as_constexpr(static_cast<std::uint32_t>(static_cast<std::uint32_t>(decwide_t_elem_number)) * 4UL))>       my_af_fft_mul_pool;  // NOLINT(cppcoreguidelines-avoid-non-const-global-variables)
    static std::array<fft_float_type, static_cast<std::size_t>(detail::a000079::a000079_as_constexpr(static_cast<std::uint32_t>(static_cast<std::uint32_t>(decwide_t_elem_number)) * 4UL))>       my_bf_fft_mul_pool;  // NOLINT(cppcoreguidelines-avoid-non-const-global-variables)
    static representation_type my_n_data_for_add_sub; // NOLINT(cppcoreguidelines-avoid-non-const-global-variables)
    #endif

    representation_type my_data;      // NOLINT(readability-identifier-naming)
    exponent_type       my_exp;       // NOLINT(readability-identifier-naming)
    bool                my_neg;       // NOLINT(readability-identifier-naming,modernize-use-default-member-init)
    fpclass_type        my_fpclass;   // NOLINT(readability-identifier-naming)
    std::int32_t        my_prec_elem; // NOLINT(readability-identifier-naming)

    static constexpr auto decwide_t_digits10_for_epsilon() -> std::int32_t
    {
      return
        static_cast<std::int32_t>
        (
            static_cast<std::int32_t>
            (
                static_cast<std::int32_t> (decwide_t_digits10 / decwide_t_elem_digits10)
              + static_cast<std::int32_t>((decwide_t_digits10 % decwide_t_elem_digits10) != 0 ? 1 : 0)
            )
          * decwide_t_elem_digits10
        );
    }

    static constexpr auto decwide_t_power10_limb0_for_epsilon() -> std::uint32_t
    {
      return
        static_cast<std::uint32_t>
        (
          static_cast<std::int32_t>
          (
            static_cast<std::int32_t>(INT32_C(1) + decwide_t_digits10_for_epsilon()) - decwide_t_digits10
          )
        );
    }

    auto from_unsigned_long_long(unsigned long long u) -> void // NOLINT(google-runtime-int)
    {
      my_exp = static_cast<exponent_type>(0);

      auto i = static_cast<std::uint_fast32_t>(0U);

      auto uu = u;

      constexpr auto local_tmp_array_size =
        static_cast<std::size_t>
        (
            static_cast<std::size_t>
            (
              std::numeric_limits<unsigned long long>::digits10 / static_cast<int>(decwide_t_elem_digits10) // NOLINT(google-runtime-int)
            )
          + static_cast<std::size_t>(UINT8_C(3))
        );

      using local_tmp_array_type = std::array<limb_type, local_tmp_array_size>;

      local_tmp_array_type tmp;

      tmp.fill(static_cast<limb_type>(0U));

      while
      (
           (uu != static_cast<unsigned long long>(UINT8_C(0))) // NOLINT(google-runtime-int)
        && (i  <  static_cast<std::uint_fast32_t>(std::tuple_size<local_tmp_array_type>::value))
      )
      {
        tmp[static_cast<std::size_t>(i)] =
          static_cast<limb_type>(uu % static_cast<unsigned long long>(decwide_t_elem_mask)); // NOLINT(google-runtime-int)

        uu = static_cast<unsigned long long>(uu / static_cast<unsigned long long>(decwide_t_elem_mask)); // NOLINT(google-runtime-int)

        ++i;
      }

      if(i > static_cast<std::uint_fast32_t>(1U))
      {
        my_exp = static_cast<exponent_type>(my_exp + static_cast<exponent_type>((i - 1U) * static_cast<std::uint_fast32_t>(decwide_t_elem_digits10)));
      }

      std::reverse(tmp.begin(), tmp.begin() + i);

      const auto copy_limit =
        static_cast<std::ptrdiff_t>
        (
          (std::min)(static_cast<std::uint_fast32_t>(std::tuple_size<local_tmp_array_type>::value),
                     static_cast<std::uint_fast32_t>(decwide_t_elem_number))
        );

      std::copy(tmp.cbegin(),
                tmp.cbegin() + static_cast<std::ptrdiff_t>((std::min)(static_cast<std::ptrdiff_t>(i), copy_limit)),
                my_data.begin());

      std::fill(my_data.begin() + static_cast<std::ptrdiff_t>((std::min)(static_cast<std::ptrdiff_t>(i), copy_limit)),
                my_data.end(),
                static_cast<limb_type>(0U));
    }

    template<typename FloatingPointType>
    auto from_builtin_float_type(FloatingPointType l) -> void
    {
      const auto b_neg = (l < static_cast<FloatingPointType>(0.0L));

      const FloatingPointType my_ld = ((!b_neg) ? l : -l);

      if(my_ld < (std::numeric_limits<FloatingPointType>::min)())
      {
        operator=(zero<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>());
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

        if     (p2 <  -1) { *this *= pow(half<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>(), -p2); }
        else if(p2 == -1) { *this *=     half<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>(); }
        else if(p2 ==  0) { ; }
        else if(p2 ==  1) { *this *= 2U; }
        else              { *this *= pow(two<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>(), p2); }

        my_neg = b_neg;
      }
    }

    template<const std::int32_t OtherDigits10>
    auto eval_mul_dispatch_multiplication_method
    (
      const decwide_t<OtherDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>& v,
      const std::int32_t prec_elems_for_multiply,
      const typename std::enable_if<(    (OtherDigits10 == ParamDigitsBaseTen)
                                     && !(decwide_t<OtherDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>::decwide_t_elem_number >= decwide_t_elems_for_kara))>::type* p_nullparam = nullptr
    ) -> void
    {
      static_cast<void>(p_nullparam);

      // Use school multiplication.
      #if !defined(WIDE_DECIMAL_DISABLE_DYNAMIC_MEMORY_ALLOCATION)
      using school_mul_pool_type = util::dynamic_array<limb_type>;

      auto my_school_mul_pool =
        school_mul_pool_type
        (
          static_cast<typename school_mul_pool_type::size_type>
          (
            static_cast<typename school_mul_pool_type::size_type>(prec_elems_for_multiply) * 2U
          )
        );
      #endif

      limb_type* result = my_school_mul_pool.data();

      using const_limb_pointer_type = typename std::add_const<limb_type*>::type;

      detail::eval_multiply_n_by_n_to_2n(result,
                                         const_limb_pointer_type(my_data.data()),
                                         const_limb_pointer_type(v.my_data.data()),
                                         prec_elems_for_multiply);

      // Handle a potential carry.
      if(result[0U] != static_cast<limb_type>(0U)) // NOLINT(cppcoreguidelines-pro-bounds-pointer-arithmetic)
      {
        my_exp = static_cast<exponent_type>(my_exp + static_cast<exponent_type>(decwide_t_elem_digits10));

        // Shift the result of the multiplication one element to the right.
        std::copy(result,
                  result + static_cast<std::ptrdiff_t>(prec_elems_for_multiply), // NOLINT(cppcoreguidelines-pro-bounds-pointer-arithmetic)
                  my_data.begin());
      }
      else
      {
        const auto copy_limit =
          static_cast<std::ptrdiff_t>
          (
            (std::min)(static_cast<std::int32_t>(prec_elems_for_multiply + static_cast<std::int32_t>(1)),
                       decwide_t_elem_number)
          );

        std::copy(result + static_cast<std::ptrdiff_t>(1), // NOLINT(cppcoreguidelines-pro-bounds-pointer-arithmetic)
                  result + copy_limit,                     // NOLINT(cppcoreguidelines-pro-bounds-pointer-arithmetic)
                  my_data.begin());
      }
    }

    template<const std::int32_t OtherDigits10>
    auto eval_mul_dispatch_multiplication_method
    (
      const decwide_t<OtherDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>& v,
      const std::int32_t prec_elems_for_multiply,
      const typename std::enable_if<(   (OtherDigits10 == ParamDigitsBaseTen)
                                     && (decwide_t<OtherDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>::decwide_t_elem_number >= decwide_t_elems_for_kara)
                                     && (decwide_t<OtherDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>::decwide_t_elem_number <  decwide_t_elems_for_fft))>::type* p_nullparam = nullptr
    ) -> void
    {
      static_cast<void>(p_nullparam);

      if(prec_elems_for_multiply < decwide_t_elems_for_kara)
      {
        // Use school multiplication.
        #if !defined(WIDE_DECIMAL_DISABLE_DYNAMIC_MEMORY_ALLOCATION)
        using school_mul_pool_type = util::dynamic_array<limb_type>;

        auto my_school_mul_pool =
          school_mul_pool_type
          (
            static_cast<typename school_mul_pool_type::size_type>
            (
              static_cast<typename school_mul_pool_type::size_type>(prec_elems_for_multiply) * 2U
            )
          );
        #endif

        limb_type* result = my_school_mul_pool.data();

        using const_limb_pointer_type = typename std::add_const<limb_type*>::type;

        detail::eval_multiply_n_by_n_to_2n(result,
                                           const_limb_pointer_type(my_data.data()),
                                           const_limb_pointer_type(v.my_data.data()),
                                           prec_elems_for_multiply);

        // Handle a potential carry.
        if(result[0U] != static_cast<limb_type>(0U)) // NOLINT(cppcoreguidelines-pro-bounds-pointer-arithmetic)
        {
          my_exp = static_cast<exponent_type>(my_exp + static_cast<exponent_type>(decwide_t_elem_digits10));

          const auto copy_limit =
            static_cast<std::ptrdiff_t>
            (
              (std::min)(prec_elems_for_multiply, decwide_t_elems_for_kara)
            );

          // Shift the result of the multiplication one element to the right.
          std::copy(result,
                    result + copy_limit, // NOLINT(cppcoreguidelines-pro-bounds-pointer-arithmetic)
                    my_data.begin());
        }
        else
        {
          const auto copy_limit =
            static_cast<std::ptrdiff_t>
            (
              (std::min)(static_cast<std::int32_t>(prec_elems_for_multiply + static_cast<std::int32_t>(1)),
                         decwide_t_elems_for_kara)
            );

          std::copy(result + static_cast<std::ptrdiff_t>(1), // NOLINT(cppcoreguidelines-pro-bounds-pointer-arithmetic)
                    result + copy_limit,                     // NOLINT(cppcoreguidelines-pro-bounds-pointer-arithmetic)
                    my_data.begin());
        }
      }
      else if(   (prec_elems_for_multiply >= decwide_t_elems_for_kara)
              && (prec_elems_for_multiply <  decwide_t_elems_for_fft))
      {
        // Karatsuba multiplication.

        // Sloanes's A029750: Numbers of the form 2^k times 1, 3, 5 or 7.
        const auto kara_elems_for_multiply =
          detail::a029750::a029750_as_runtime_value(static_cast<std::uint32_t>(prec_elems_for_multiply));

        #if !defined(WIDE_DECIMAL_DISABLE_DYNAMIC_MEMORY_ALLOCATION)
        using kara_mul_pool_type = util::dynamic_array<limb_type>;

        auto my_kara_mul_pool =
          kara_mul_pool_type
          (
            static_cast<typename kara_mul_pool_type::size_type>
            (
              static_cast<typename kara_mul_pool_type::size_type>(kara_elems_for_multiply) * static_cast<std::size_t>(UINT8_C(8))
            )
          );
        #endif

        limb_type* u_local = my_kara_mul_pool.data() + static_cast<std::size_t>(static_cast<std::size_t>(kara_elems_for_multiply) * static_cast<std::size_t>(UINT8_C(0))); // NOLINT(cppcoreguidelines-pro-bounds-pointer-arithmetic)
        limb_type* v_local = my_kara_mul_pool.data() + static_cast<std::size_t>(static_cast<std::size_t>(kara_elems_for_multiply) * static_cast<std::size_t>(UINT8_C(1))); // NOLINT(cppcoreguidelines-pro-bounds-pointer-arithmetic)
        limb_type* result  = my_kara_mul_pool.data() + static_cast<std::size_t>(static_cast<std::size_t>(kara_elems_for_multiply) * static_cast<std::size_t>(UINT8_C(2))); // NOLINT(cppcoreguidelines-pro-bounds-pointer-arithmetic)
        limb_type* t       = my_kara_mul_pool.data() + static_cast<std::size_t>(static_cast<std::size_t>(kara_elems_for_multiply) * static_cast<std::size_t>(UINT8_C(4))); // NOLINT(cppcoreguidelines-pro-bounds-pointer-arithmetic)

        std::copy(  my_data.cbegin(),   my_data.cbegin() + prec_elems_for_multiply, u_local);
        std::copy(v.my_data.cbegin(), v.my_data.cbegin() + prec_elems_for_multiply, v_local);
        std::fill(u_local + prec_elems_for_multiply, u_local + kara_elems_for_multiply, static_cast<limb_type>(0U)); // NOLINT(cppcoreguidelines-pro-bounds-pointer-arithmetic)
        std::fill(v_local + prec_elems_for_multiply, v_local + kara_elems_for_multiply, static_cast<limb_type>(0U)); // NOLINT(cppcoreguidelines-pro-bounds-pointer-arithmetic)

        detail::eval_multiply_kara_n_by_n_to_2n(result,
                                                u_local,
                                                v_local,
                                                kara_elems_for_multiply,
                                                t);

        // Handle a potential carry.
        if(result[0U] != static_cast<limb_type>(0U)) // NOLINT(cppcoreguidelines-pro-bounds-pointer-arithmetic)
        {
          my_exp = static_cast<exponent_type>(my_exp + static_cast<exponent_type>(decwide_t_elem_digits10));

          const auto copy_limit =
            static_cast<std::ptrdiff_t>
            (
              (std::min)(prec_elems_for_multiply, decwide_t_elem_number)
            );

          // Shift the result of the multiplication one element to the right.
          std::copy(result,
                    result + copy_limit, // NOLINT(cppcoreguidelines-pro-bounds-pointer-arithmetic)
                    my_data.begin());
        }
        else
        {
          const auto copy_limit =
            static_cast<std::ptrdiff_t>
            (
              (std::min)(static_cast<std::int32_t>(prec_elems_for_multiply + INT32_C(1)),
                         decwide_t_elem_number)
            );

          std::copy(result + static_cast<std::ptrdiff_t>(1), // NOLINT(cppcoreguidelines-pro-bounds-pointer-arithmetic)
                    result + copy_limit,                     // NOLINT(cppcoreguidelines-pro-bounds-pointer-arithmetic)
                    my_data.begin());
        }
      }
    }

    template<const std::int32_t OtherDigits10>
    auto eval_mul_dispatch_multiplication_method
    (
      const decwide_t<OtherDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>& v,
      const std::int32_t prec_elems_for_multiply,
      const typename std::enable_if<(   (OtherDigits10 == ParamDigitsBaseTen)
                                     && (decwide_t<OtherDigits10, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>::decwide_t_elem_number >= decwide_t_elems_for_fft))>::type* p_nullparam = nullptr
    ) -> void
    {
      static_cast<void>(p_nullparam);

      if(prec_elems_for_multiply < decwide_t_elems_for_kara)
      {
        // Use school multiplication.
        #if !defined(WIDE_DECIMAL_DISABLE_DYNAMIC_MEMORY_ALLOCATION)
        using school_mul_pool_type = util::dynamic_array<limb_type>;

        auto my_school_mul_pool =
          school_mul_pool_type
          (
            static_cast<typename school_mul_pool_type::size_type>
            (
              static_cast<typename school_mul_pool_type::size_type>(prec_elems_for_multiply) * 2U
            )
          );

        #endif

        limb_type* result = my_school_mul_pool.data();

        using const_limb_pointer_type = typename std::add_const<limb_type*>::type;

        detail::eval_multiply_n_by_n_to_2n(result,
                                           const_limb_pointer_type(my_data.data()),
                                           const_limb_pointer_type(v.my_data.data()),
                                           prec_elems_for_multiply);

        // Handle a potential carry.
        if(result[0U] != static_cast<limb_type>(0U)) // NOLINT(cppcoreguidelines-pro-bounds-pointer-arithmetic)
        {
          my_exp += static_cast<exponent_type>(decwide_t_elem_digits10);

          const auto copy_limit =
            static_cast<std::ptrdiff_t>
            (
              (std::min)(prec_elems_for_multiply, decwide_t_elems_for_kara)
            );

          // Shift the result of the multiplication one element to the right.
          std::copy(result,
                    result + copy_limit, // NOLINT(cppcoreguidelines-pro-bounds-pointer-arithmetic)
                    my_data.begin());
        }
        else
        {
          const auto copy_limit =
            static_cast<std::ptrdiff_t>
            (
              (std::min)(static_cast<std::int32_t>(prec_elems_for_multiply + static_cast<std::int32_t>(1)),
                         decwide_t_elems_for_kara)
            );

          std::copy(result + static_cast<std::ptrdiff_t>(1), // NOLINT(cppcoreguidelines-pro-bounds-pointer-arithmetic)
                    result + copy_limit,                      // NOLINT(cppcoreguidelines-pro-bounds-pointer-arithmetic)
                    my_data.begin());
        }
      }
      else if(   (prec_elems_for_multiply >= decwide_t_elems_for_kara)
              && (prec_elems_for_multiply <  decwide_t_elems_for_fft))
      {
        // Use Karatsuba multiplication multiplication.

        // Sloanes's A029750: Numbers of the form 2^k times 1, 3, 5 or 7.
        const auto kara_elems_for_multiply =
          (std::min)(detail::a029750::a029750_as_runtime_value(static_cast<std::uint32_t>(prec_elems_for_multiply)),
                     static_cast<std::uint32_t>(detail::a029750::a029750_as_runtime_value(decwide_t_elems_for_fft - 1) * static_cast<std::uint32_t>(UINT8_C(8))));

        #if !defined(WIDE_DECIMAL_DISABLE_DYNAMIC_MEMORY_ALLOCATION)
        using kara_mul_pool_type = util::dynamic_array<limb_type>;

        auto my_kara_mul_pool =
          kara_mul_pool_type
          (
            static_cast<typename kara_mul_pool_type::size_type>
            (
              static_cast<typename kara_mul_pool_type::size_type>(kara_elems_for_multiply) * static_cast<std::size_t>(UINT8_C(8))
            )
          );

        #endif

        limb_type* u_local = my_kara_mul_pool.data() + static_cast<std::size_t>(static_cast<std::size_t>(kara_elems_for_multiply) * static_cast<std::size_t>(UINT8_C(0))); // NOLINT(cppcoreguidelines-pro-bounds-pointer-arithmetic)
        limb_type* v_local = my_kara_mul_pool.data() + static_cast<std::size_t>(static_cast<std::size_t>(kara_elems_for_multiply) * static_cast<std::size_t>(UINT8_C(1))); // NOLINT(cppcoreguidelines-pro-bounds-pointer-arithmetic)
        limb_type* result  = my_kara_mul_pool.data() + static_cast<std::size_t>(static_cast<std::size_t>(kara_elems_for_multiply) * static_cast<std::size_t>(UINT8_C(2))); // NOLINT(cppcoreguidelines-pro-bounds-pointer-arithmetic)
        limb_type* t       = my_kara_mul_pool.data() + static_cast<std::size_t>(static_cast<std::size_t>(kara_elems_for_multiply) * static_cast<std::size_t>(UINT8_C(4))); // NOLINT(cppcoreguidelines-pro-bounds-pointer-arithmetic)

        std::copy(  my_data.cbegin(),   my_data.cbegin() + prec_elems_for_multiply, u_local);
        std::copy(v.my_data.cbegin(), v.my_data.cbegin() + prec_elems_for_multiply, v_local);
        std::fill(u_local + prec_elems_for_multiply, u_local + kara_elems_for_multiply, static_cast<limb_type>(0U)); // NOLINT(cppcoreguidelines-pro-bounds-pointer-arithmetic)
        std::fill(v_local + prec_elems_for_multiply, v_local + kara_elems_for_multiply, static_cast<limb_type>(0U)); // NOLINT(cppcoreguidelines-pro-bounds-pointer-arithmetic)

        detail::eval_multiply_kara_n_by_n_to_2n(result,
                                                u_local,
                                                v_local,
                                                kara_elems_for_multiply,
                                                t);

        // Handle a potential carry.
        if(result[0U] != static_cast<limb_type>(0U)) // NOLINT(cppcoreguidelines-pro-bounds-pointer-arithmetic)
        {
          my_exp = static_cast<exponent_type>(my_exp + static_cast<exponent_type>(decwide_t_elem_digits10));

          const auto copy_limit =
            static_cast<std::ptrdiff_t>
            (
              (std::min)(prec_elems_for_multiply, decwide_t_elems_for_fft)
            );

          // Shift the result of the multiplication one element to the right.
          std::copy(result,
                    result + copy_limit, // NOLINT(cppcoreguidelines-pro-bounds-pointer-arithmetic)
                    my_data.begin());
        }
        else
        {
          const auto copy_limit =
            static_cast<std::ptrdiff_t>
            (
              (std::min)(static_cast<std::int32_t>(prec_elems_for_multiply + static_cast<std::int32_t>(1)),
                         decwide_t_elems_for_fft)
            );

          std::copy(result + static_cast<std::ptrdiff_t>(1), // NOLINT(cppcoreguidelines-pro-bounds-pointer-arithmetic)
                    result + copy_limit,                     // NOLINT(cppcoreguidelines-pro-bounds-pointer-arithmetic)
                    my_data.begin());
        }
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
        const auto n_fft =
          static_cast<std::uint32_t>
          (
              detail::a000079::a000079_as_constexpr(static_cast<std::uint32_t>(prec_elems_for_multiply))
            * static_cast<std::uint32_t>(UINT8_C(4))
          );

        #if !defined(WIDE_DECIMAL_DISABLE_DYNAMIC_MEMORY_ALLOCATION)
        using fft_mul_storage_type = util::dynamic_array<fft_float_type>;

        auto my_af_fft_mul_pool = fft_mul_storage_type(static_cast<typename fft_mul_storage_type::size_type>(n_fft));
        auto my_bf_fft_mul_pool = fft_mul_storage_type(static_cast<typename fft_mul_storage_type::size_type>(n_fft));
        #endif

        fft_float_type* af = my_af_fft_mul_pool.data();
        fft_float_type* bf = my_bf_fft_mul_pool.data();

        using const_limb_pointer_type = typename std::add_const<limb_type*>::type;

        detail::mul_loop_fft(my_data.data(),
                             const_limb_pointer_type(my_data.data()),
                             const_limb_pointer_type(v.my_data.data()),
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
          const auto copy_limit =
            static_cast<std::ptrdiff_t>
            (
              (std::min)(static_cast<std::int32_t>(prec_elems_for_multiply + static_cast<std::int32_t>(1)),
                         decwide_t_elem_number)
            );

          // Justify the data if necessary.
          std::copy(my_data.cbegin() + static_cast<std::ptrdiff_t>(1), // NOLINT(cppcoreguidelines-pro-bounds-pointer-arithmetic)
                    my_data.cbegin() + copy_limit,                     // NOLINT(cppcoreguidelines-pro-bounds-pointer-arithmetic)
                    my_data.begin());

          my_data.back() = static_cast<limb_type>(0U);
        }
      }
    }

    auto eval_round_self() -> void // NOLINT(readability-function-cognitive-complexity)
    {
      const auto needs_rounding = ((isfinite)() && (!iszero()));

      if(needs_rounding)
      {
        using local_size_type = typename representation_type::size_type;
        using local_limb_type = typename representation_type::value_type;

        auto digits_limb_0 = static_cast<std::int32_t>(0);

        auto tmp_limb_0 = my_data[0U];

        // Manually count the number of base-10 digits on the zero'th limb.
        while(tmp_limb_0 > static_cast<local_limb_type>(0U))
        {
          tmp_limb_0 = static_cast<local_limb_type>(tmp_limb_0 / 10U); // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)

          ++digits_limb_0;
        }

        constexpr auto local_max_digits10 = static_cast<std::int32_t>(decwide_t_max_digits10);

        const auto digits_limb_1_to_n = static_cast<std::int32_t>(local_max_digits10 - digits_limb_0);

        // Find the index of the element that contains the least-significant base-10 digit.
        auto least_digit_idx =
          static_cast<std::int32_t>
          (
              static_cast<std::int32_t> (digits_limb_1_to_n / decwide_t_elem_digits10)
            + static_cast<std::int32_t>((digits_limb_1_to_n % decwide_t_elem_digits10) != 0 ? 1 : 0)
          );

        // Set the index of the element that contains the rounding base-10 digit.
        const auto round_digit_idx =
          static_cast<std::int32_t>
          (
            ((digits_limb_1_to_n % decwide_t_elem_digits10) != 0)
              ?                           least_digit_idx
              : static_cast<std::int32_t>(least_digit_idx + static_cast<std::int32_t>(1))
          );

        // Find the base-10 order (position) of the least-significant base-10 digit.
        const auto least_digit_pos =
          static_cast<std::int32_t>
          (
            (static_cast<std::int32_t>(digits_limb_1_to_n % decwide_t_elem_digits10) != INT32_C(0))
                ? static_cast<std::int32_t>
                  (
                      decwide_t_elem_digits10
                    - static_cast<std::int32_t>(digits_limb_1_to_n % decwide_t_elem_digits10)
                  )
                : static_cast<std::int32_t>(0)
          );

        // Find the base-10 order (position) of the rounding base-10 digit.
        const auto round_digit_pos =
          static_cast<std::int32_t>((least_digit_pos != 0) ? least_digit_pos - 1 : decwide_t_elem_digits10 - 1);

        using digit_helper_struct_type = detail::decwide_t_helper<decwide_t_elem_digits10, limb_type>;

        // Get the value of the rounding base-10 digit.
        const auto round_digit_value =
          digit_helper_struct_type::digit_at_pos_in_limb
          (
             my_data[static_cast<local_size_type>(round_digit_idx)],
             static_cast<unsigned>(round_digit_pos)
          );

        const auto least_digit_p10 = detail::pow10_maker_as_runtime_value(static_cast<std::uint32_t>(least_digit_pos));

        // Clear the lower base-10 digits of the rounded element.
        my_data[static_cast<local_size_type>(least_digit_idx)] =
          static_cast<local_limb_type>
          (
              my_data[static_cast<local_size_type>(least_digit_idx)]
            - static_cast<local_limb_type>
              (
                  my_data[static_cast<local_size_type>(least_digit_idx)]
                % static_cast<local_limb_type>(least_digit_p10)
              )
          );

        // Clear the lower base-10 limbs.
        {
          const auto least_digit_idx_plus_one = static_cast<std::int32_t>(least_digit_idx + 1);

          const auto do_clear_lower_limbs =
            (least_digit_idx_plus_one < static_cast<std::int32_t>(my_data.size() - 1U));

          if(do_clear_lower_limbs)
          {
            std::fill(my_data.begin() + static_cast<local_size_type>(least_digit_idx_plus_one),
                      my_data.end(),
                      static_cast<local_limb_type>(0U));
          }
        }

        // Perform round-to-nearest with no tie-breaking whatsoever.
        if(round_digit_value >= static_cast<std::uint8_t>(UINT8_C(5)))
        {
          my_data[static_cast<local_size_type>(least_digit_idx)] =
            static_cast<local_limb_type>
            (
                my_data[static_cast<local_size_type>(least_digit_idx)]
              + static_cast<local_limb_type>(least_digit_p10)
            );

          // There is a carry from rounding up.
          std::uint_fast8_t carry_out =
            ((my_data[static_cast<local_size_type>(least_digit_idx)] >= decwide_t_elem_mask)
              ? static_cast<std::uint_fast8_t>(1U)
              : static_cast<std::uint_fast8_t>(0U));

          // Propogate the carry into the limbs of higher significance as needed.
          if(carry_out != static_cast<std::uint_fast8_t>(UINT8_C(0)))
          {
            my_data[static_cast<local_size_type>(least_digit_idx)] =
              static_cast<limb_type>
              (
                  my_data[static_cast<local_size_type>(least_digit_idx)]
                - static_cast<limb_type>(decwide_t_elem_mask)
              );

            while(   (--least_digit_idx >= static_cast<std::int32_t>(0))
                  && (carry_out != static_cast<std::uint_fast8_t>(UINT8_C(0))))
            {
              const auto tt =
                static_cast<local_limb_type>
                (
                    my_data[static_cast<local_size_type>(least_digit_idx)]
                  + static_cast<local_limb_type>(carry_out)
                );

              carry_out = ((tt >= decwide_t_elem_mask) ? static_cast<std::uint_fast8_t>(1U)
                                                       : static_cast<std::uint_fast8_t>(0U));

              my_data[static_cast<local_size_type>(least_digit_idx)] =
                static_cast<local_limb_type>
                (
                  tt - ((carry_out != 0U) ? decwide_t_elem_mask
                                          : static_cast<local_limb_type>(0U))
                );
            }

            if(   (least_digit_idx < static_cast<std::int32_t>(0))
               && (carry_out != static_cast<std::uint_fast8_t>(UINT8_C(0))))
            {
              // In rare cases, propagation of the carry reaches the zero'th limb
              // of highest significance, and we must shift the data, create a new limb
              // with the carry value of 1 and adjust the exponent accordingly.
              std::copy_backward(my_data.cbegin(),
                                 my_data.cend() - 1,
                                 my_data.end());

              my_data[0U] = carry_out;

              my_exp = static_cast<exponent_type>(my_exp + static_cast<exponent_type>(decwide_t_elem_digits10));
            }
          }
        }
      }
    }

    #if !defined(WIDE_DECIMAL_DISABLE_CONSTRUCT_FROM_STRING)
    auto rd_string(const char* s) -> bool // NOLINT(readability-function-cognitive-complexity)
    {
      std::string str(s);

      // Get a possible exponent and remove it.
      my_exp = static_cast<exponent_type>(0);

      auto pos_of_e_func =
        [](const std::string& local_str) // NOLINT(modernize-use-trailing-return-type)
        {
          std::string::size_type pos_of_e = std::string::npos;

          const auto pos_of_e_lo = local_str.find('e');

          if(pos_of_e_lo != std::string::npos)
          {
            pos_of_e = pos_of_e_lo;
          }
          else
          {
            const auto pos_of_e_hi = local_str.find('E');

            if(pos_of_e_hi != std::string::npos)
            {
              pos_of_e = pos_of_e_hi;
            }
          }

          return pos_of_e;
        };

      auto pos = pos_of_e_func(str);

      if(pos != std::string::npos)
      {
        // Remove the exponent part from the string.
        static_assert(std::numeric_limits<signed long long>::digits >= std::numeric_limits<exponent_type>::digits, // NOLINT(google-runtime-int)
                      "Error: Type long long is not wide enough to hold result of type exponent_type");

        char* ptr_end; // NOLINT(cppcoreguidelines-pro-type-vararg,hicpp-vararg,cppcoreguidelines-init-variables)

        my_exp =
          static_cast<exponent_type>
          (
            std::strtoll(static_cast<const char*>(str.c_str() + (pos + 1U)), &ptr_end, 10) // NOLINT(cppcoreguidelines-pro-bounds-pointer-arithmetic,cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
          );

        str = str.substr(static_cast<std::size_t>(0U), pos);
      }

      // Get a possible +/- sign and remove it.
      my_neg = false;

      if((pos = str.find('-')) != std::string::npos)
      {
        my_neg = true;

        str.erase(pos, static_cast<std::uint_fast32_t>(1U));
      }

      if((pos = str.find('+')) != std::string::npos)
      {
        str.erase(pos, static_cast<std::uint_fast32_t>(1U));
      }

      // Remove leading zeros for all input types.
      const auto fwd_it_leading_zero =
        std::find_if(str.begin(),
                     str.end(),
                     [](const char& c) // NOLINT(modernize-use-trailing-return-type)
                     {
                       return (c != '0');
                     });

      if(fwd_it_leading_zero != str.begin())
      {
        if(fwd_it_leading_zero == str.end())
        {
          // The string contains nothing but leading zeros.
          // This string represents zero.
          operator=(zero<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>());

          return true;
        }

        str.erase(str.begin(), fwd_it_leading_zero);
      }

      // Put the input string into the standard decwide_t input form
      // aaa.bbbbE+/-n, where aa has 1...decwide_t_elem_digits10, bbbb has an
      // even multiple of decwide_t_elem_digits10 which are possibly zero padded
      // on the right-end, and n is a signed 32-bit integer which is an
      // even multiple of decwide_t_elem_digits10.

      // Find a possible decimal point.
      pos = str.find('.');

      if(pos != std::string::npos)
      {
        // Remove all trailing insignificant zeros.
        const auto rit_non_zero =
          std::find_if(str.crbegin(),
                       str.crend(),
                       [](const char& c) // NOLINT(modernize-use-trailing-return-type)
                       {
                         return (c != '0');
                       });

        if(rit_non_zero != str.crbegin())
        {
          const auto ofs =
            static_cast<std::string::difference_type>
            (
                static_cast<std::ptrdiff_t>(str.length())
              - std::distance<std::string::const_reverse_iterator>(str.crbegin(), rit_non_zero)
            );

          const auto cnt =
            static_cast<std::size_t>
            (
              static_cast<std::ptrdiff_t>(str.size()) - ofs
            );

          str.erase(static_cast<std::size_t>(ofs), cnt);
        }

        // Check if the input is identically zero.
        {
          const auto input_is_identically_zero =
            (
                 (str.size()  == static_cast<std::size_t>(1U))
              && (str.front() == '.')
            );

          if(input_is_identically_zero)
          {
            operator=(zero<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>());

            return true;
          }
        }

        // Remove leading significant zeros just after the decimal point
        // and adjust the exponent accordingly.
        // Note that the while-loop operates only on strings of the form ".000abcd..."
        // and peels away the zeros just after the decimal point.
        if(str.at(static_cast<std::uint_fast32_t>(0U)) == '.')
        {
          const auto it_non_zero =
            std::find_if(str.begin() + 1U,
                         str.end(),
                         [](const char& c) // NOLINT(modernize-use-trailing-return-type)
                         {
                           return (c != '0');
                         });

          auto delta_exp = static_cast<std::uint_fast32_t>(0U);

          if(str.at(static_cast<std::uint_fast32_t>(1U)) == '0')
          {
            delta_exp = static_cast<std::uint_fast32_t>(it_non_zero - (str.begin() + 1U));
          }

          // Bring one single digit into the mantissa and adjust exponent accordingly.
          str.erase(str.begin(), it_non_zero);

          str.insert(static_cast<std::size_t>(1U), static_cast<std::size_t>(1U), '.');

          my_exp = static_cast<exponent_type>(my_exp - static_cast<exponent_type>(delta_exp + 1U));
        }
      }
      else
      {
        // Input string has no decimal point: Append decimal point.
        str.append(static_cast<std::size_t>(1U), '.');
      }

      // Shift the decimal point such that the exponent is an even multiple of decwide_t_elem_digits10.
      auto n_shift   = static_cast<std::ptrdiff_t>(0);

      {
        const auto n_exp_rem =
          static_cast<std::ptrdiff_t>
          (
            my_exp % static_cast<exponent_type>(decwide_t_elem_digits10)
          );

        const auto n_exp_mod =
          static_cast<exponent_type>
          (
            my_exp % static_cast<exponent_type>(decwide_t_elem_digits10)
          );

        if(n_exp_mod != static_cast<exponent_type>(0))
        {
          n_shift = ((my_exp < static_cast<exponent_type>(0))
                      ? static_cast<std::ptrdiff_t>(n_exp_rem + static_cast<std::ptrdiff_t>(decwide_t_elem_digits10))
                      : static_cast<std::ptrdiff_t>(n_exp_rem));
        }
      }

      // Make sure that there are enough digits for the decimal point shift.
      pos = str.find('.');

      auto pos_plus_one = static_cast<std::ptrdiff_t>(pos + 1U);

      if((static_cast<std::ptrdiff_t>(str.length()) - pos_plus_one) < n_shift)
      {
        const auto cnt =
          static_cast<std::ptrdiff_t>
          (
            n_shift - (static_cast<std::ptrdiff_t>(str.length()) - pos_plus_one)
          );

        str.append(static_cast<std::size_t>(cnt), '0');
      }

      // Perform the shift of the decimal point.
      if(n_shift != static_cast<std::ptrdiff_t>(0))
      {
        str.insert(static_cast<std::size_t>(pos_plus_one + n_shift), static_cast<std::size_t>(1U), '.');

        str.erase(pos, static_cast<std::ptrdiff_t>(1));

        my_exp = static_cast<exponent_type>(my_exp - static_cast<exponent_type>(n_shift));
      }

      // Reduce the size of the mantissa to <= decwide_t_elem_digits10.
      pos          = str.find('.');
      pos_plus_one = static_cast<std::ptrdiff_t>(pos + 1U);

      if(pos > static_cast<std::ptrdiff_t>(decwide_t_elem_digits10))
      {
        const auto n_pos         = static_cast<std::int32_t>(pos);
        const auto n_rem_is_zero = static_cast<std::int32_t>((static_cast<std::int32_t>(n_pos % decwide_t_elem_digits10) == static_cast<std::int32_t>(0)) ? static_cast<std::int32_t>(1) : static_cast<std::int32_t>(0));
        const auto n             = static_cast<std::int32_t> (static_cast<std::int32_t>(n_pos / decwide_t_elem_digits10) - n_rem_is_zero);

        const auto pos_to_insert =
          static_cast<std::size_t>
          (
            static_cast<std::int32_t>(n_pos - static_cast<std::int32_t>(n * decwide_t_elem_digits10))
          );

        str.insert(pos_to_insert, static_cast<std::size_t>(1U), '.');

        str.erase(static_cast<std::string::size_type>(pos_plus_one), static_cast<std::uint_fast32_t>(1U));

        my_exp =
          static_cast<exponent_type>
          (
              my_exp
            + static_cast<exponent_type>
              (
                static_cast<exponent_type>(n) * static_cast<exponent_type>(decwide_t_elem_digits10)
              )
          );
      }

      // Pad the decimal part such that its value is an even
      // multiple of decwide_t_elem_digits10.
      pos          = str.find('.');
      pos_plus_one = static_cast<std::ptrdiff_t>(pos + 1U);

      const auto n_dec = static_cast<std::int32_t> (static_cast<std::int32_t>(str.length() - 1U) - static_cast<std::int32_t>(pos));
      const auto n_rem = static_cast<std::int32_t> (n_dec % decwide_t_elem_digits10);
            auto n_cnt = static_cast<std::int32_t>((n_rem != static_cast<std::int32_t>(0)) ? static_cast<std::int32_t>(decwide_t_elem_digits10 - n_rem)
                                                                                           : static_cast<std::int32_t>(0));

      if(n_cnt != static_cast<std::int32_t>(0))
      {
        str.append(static_cast<std::size_t>(n_cnt), '0');
      }

      // Truncate decimal part if it is too long.
      const auto max_dec =
        static_cast<std::ptrdiff_t>
        (
            static_cast<std::ptrdiff_t>(decwide_t_elem_number - INT32_C(1))
          * static_cast<std::ptrdiff_t>(decwide_t_elem_digits10)
        );

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

      using local_size_type = typename representation_type::size_type;

      {
        static_assert(std::numeric_limits<unsigned long>::digits >= std::numeric_limits<limb_type>::digits, // NOLINT(google-runtime-int)
                      "Error: Type unsigned long is not wide enough to hold result of type limb_type");

        char* ptr_end { }; // NOLINT(cppcoreguidelines-pro-type-vararg,hicpp-vararg)

        // First get the digits to the left of the decimal point...

        const auto str_zeroth_limb = str.substr(static_cast<std::ptrdiff_t>(0), pos);

        my_data[static_cast<local_size_type>(0U)] =
          static_cast<limb_type>
          (
            std::strtoul(str_zeroth_limb.c_str(), &ptr_end, 10) // NOLINT(,cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
          );
      }

      // ...then get the remaining digits to the right of the decimal point.
      const auto i_end =
        static_cast<std::string::difference_type>
        (
            static_cast<std::string::difference_type>(static_cast<std::string::difference_type>(str.length()) - pos_plus_one)
          / static_cast<std::string::difference_type>(decwide_t_elem_digits10)
        );

      for(auto i = static_cast<std::string::difference_type>(0); i < i_end; ++i)
      {
        const auto idigits =
          static_cast<std::string::difference_type>
          (
            i * static_cast<std::string::difference_type>(decwide_t_elem_digits10)
          );

        const auto it =   str.begin()
                        + static_cast<std::string::difference_type>(static_cast<std::string::difference_type>(pos_plus_one) + idigits);

        const auto str_next_limb =
          std::string
          (
            it,
            it + static_cast<std::string::difference_type>(decwide_t_elem_digits10)
          );

        const auto i1 =
          static_cast<local_size_type>
          (
            i + static_cast<std::string::difference_type>(1)
          );

        static_assert(std::numeric_limits<unsigned long>::digits >= std::numeric_limits<limb_type>::digits, // NOLINT(google-runtime-int)
                      "Error: Type unsigned long is not wide enough to hold result of type limb_type");

        char* ptr_end { }; // NOLINT(cppcoreguidelines-pro-type-vararg,hicpp-vararg)

        my_data[i1] =
          static_cast<limb_type>
          (
            std::strtoul(str_next_limb.c_str(), &ptr_end, static_cast<int>(INT8_C(10)))
          );
      }

      return true;
    }
    #endif //!(WIDE_DECIMAL_DISABLE_CONSTRUCT_FROM_STRING)

    #if !defined(WIDE_DECIMAL_DISABLE_IOSTREAM)
    auto get_output_string(      std::string&       str, // NOLINT(google-runtime-references)
                                 exponent_type&     the_exp,
                           const std::uint_fast32_t number_of_digits) const -> void
    {
      // Determine the number of elements needed to provide the requested digits from decwide_t.
      const std::uint_fast32_t number_of_elements =
        (std::min)(static_cast<std::uint_fast32_t>((number_of_digits / static_cast<std::uint_fast32_t>(decwide_t_elem_digits10)) + 2U),
                   static_cast<std::uint_fast32_t>(decwide_t_elem_number));

      // Extract the remaining digits from decwide_t after the decimal point.
      std::array<char, static_cast<std::size_t>(UINT8_C(10))> ptr_str = {{ '\0' }};

      char* ptr_end = util::baselexical_cast(my_data[0], ptr_str.data()); // NOLINT(cppcoreguidelines-pro-type-vararg,hicpp-vararg)

      str = std::string(ptr_str.data(), ptr_end);

      // Extract all of the digits from decwide_t, beginning with the first data element.
      for(auto i = static_cast<std::uint_fast32_t>(1U); i < number_of_elements; i++)
      {
        using data_element_rep_type = typename std::conditional<(std::numeric_limits<limb_type>::digits <= static_cast<int>(INT8_C(32))),
                                                                 std::uint32_t,
                                                                 limb_type>::type;

        std::stringstream ss;

        // TBD: Avoid using string-streaming here.
        ss << std::setw(static_cast<std::streamsize>(decwide_t_elem_digits10))
           << std::setfill('0')
           << data_element_rep_type(my_data[i]);

        str += ss.str();
      }

      // Cut the output to the size of the precision.
      if(str.length() > number_of_digits)
      {
        // Get the digit after the last needed digit for rounding
        const auto round =
          static_cast<std::uint32_t>
          (
            static_cast<std::uint32_t>(str.at(number_of_digits)) - static_cast<std::uint32_t>('0')
          );

        // Truncate the string
        str = str.substr(static_cast<std::uint_fast32_t>(0U), number_of_digits);

        if(round >= static_cast<std::uint32_t>(UINT8_C(5)))
        {
          auto ix = static_cast<std::string::size_type>(str.length() - 1U);

          // Every trailing 9 must be rounded up.
          while(   (ix != static_cast<std::size_t>(0U))
                && (static_cast<int>(static_cast<int>(str.at(ix)) - static_cast<int>('0')) == static_cast<int>(INT8_C(9))))
          {
            str.at(ix) = '0';

            --ix;
          }

          if(ix == 0U)
          {
            // There were nothing but trailing nines.
            if(static_cast<int>(static_cast<int>(str.at(ix)) - static_cast<int>(INT8_C(0x30))) == static_cast<int>(INT8_C(9)))
            {
              // Increment up to the next order and adjust exponent.
              str.at(ix) = '1';
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

    auto wr_string(std::string& str, std::ostream& os) const -> void // NOLINT(readability-function-cognitive-complexity,google-runtime-references)
    {
      using local_flags_type = std::ios::fmtflags;

      // Assess the format flags.
      const local_flags_type my_flags = os.flags();

      // Obtain the showpos flag.
      const auto my_showpos   = (static_cast<local_flags_type>(my_flags & std::ios::showpos)   != static_cast<local_flags_type>(0U));
      const auto my_uppercase = (static_cast<local_flags_type>(my_flags & std::ios::uppercase) != static_cast<local_flags_type>(0U));

      // Get the base-10 exponent.
      auto the_exp = static_cast<exponent_type>(ilogb(*this));

      // Get the output stream's precision and limit it to max_digits10.
      // Erroneous zero or negative precision (theoretically impossible)
      // will be set to ostream's default precision.
      static const std::stringstream str_default;
      static const std::streamsize   prec_default = str_default.precision();

      const auto os_precision =
        static_cast<std::uint_fast32_t>
        (
          ((os.precision() <= static_cast<std::streamsize>(0))
            ? static_cast<std::uint_fast32_t>(prec_default)
            : static_cast<std::uint_fast32_t>(os.precision()))
        );

      // Determine the kind of output format requested (scientific, fixed, none).
      detail::os_float_field_type my_float_field { };

      if     ((my_flags & std::ios::scientific) != static_cast<local_flags_type>(0U)) { my_float_field = detail::os_float_field_type::scientific; }
      else if((my_flags & std::ios::fixed)      != static_cast<local_flags_type>(0U)) { my_float_field = detail::os_float_field_type::fixed; }
      else                                                                            { my_float_field = detail::os_float_field_type::none; }

      bool use_scientific = false;
      bool use_fixed      = false;

      if     (my_float_field == detail::os_float_field_type::scientific) { use_scientific = true; }
      else if(my_float_field == detail::os_float_field_type::fixed)      { use_fixed      = true; }
      else // os_float_field_none
      {
        // Set up the range for dynamic detection of scientific notation.
        // If the exponent is less than -4 or larger than a precision-dependent
        // positive bound, then scientific notation is used.
        static const auto neg_bound_for_scientific_neg_exp = static_cast<exponent_type>(-4);
               const auto min_bound_for_scientific_pos_exp = (std::max)(static_cast<exponent_type>(os_precision), static_cast<exponent_type>(prec_default));
               const auto pos_bound_for_scientific_pos_exp = (std::min)(static_cast<exponent_type>(decwide_t_digits10), min_bound_for_scientific_pos_exp);

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
      auto the_number_of_digits_i_want_from_decwide_t = static_cast<std::uint_fast32_t>(0U);

      const auto max10_plus_one =
        static_cast<std::uint_fast32_t>
        (
          static_cast<std::uint_fast32_t>(decwide_t_max_digits10) + 1U
        );

      if(use_scientific)
      {
        // The float-field is scientific. The number of digits is given by
        // (1 + the ostream's precision), not to exceed (max_digits10 + 1).
        const auto prec_plus_one  = static_cast<std::uint_fast32_t>(1U + os_precision);

        the_number_of_digits_i_want_from_decwide_t = (std::min)(max10_plus_one, prec_plus_one);
      }
      else if(use_fixed)
      {
        // The float-field is scientific. The number of all-digits depends
        // on the form of the number.

        const auto exp_plus_one                   = static_cast<exponent_type>(the_exp      + static_cast<exponent_type>(1));
        const auto exp_plus_one_plus_my_precision = static_cast<exponent_type>(exp_plus_one + static_cast<exponent_type>(os_precision));

        if(the_exp >= static_cast<exponent_type>(0))
        {
          // If the number is larger than 1 in absolute value, then the number of
          // digits is given by the width of the integer part plus the ostream's
          // precision, not to exceed (max_digits10 + 1).
          the_number_of_digits_i_want_from_decwide_t =
            static_cast<std::uint_fast32_t>
            (
              (std::min)(exp_plus_one_plus_my_precision, static_cast<exponent_type>(max10_plus_one))
            );
        }
        else
        {
          the_number_of_digits_i_want_from_decwide_t = (std::min)(os_precision, max10_plus_one);
        }
      }

      // If the float field is not set, reduce the number of digits requested
      // from decwide_t such that it neither exceeds the ostream's precision
      // nor decwide_t's max_digits10.
      if(my_float_field == detail::os_float_field_type::none)
      {
        const auto max_digits = (std::min)(os_precision, static_cast<std::uint_fast32_t>(decwide_t_max_digits10));

        the_number_of_digits_i_want_from_decwide_t = (std::min)(the_number_of_digits_i_want_from_decwide_t, max_digits);
      }

      // Extract the rounded output string with the desired number of digits.
      get_output_string(str, the_exp, the_number_of_digits_i_want_from_decwide_t);

      // Obtain additional format information.
      const auto my_showpoint = ((my_flags & std::ios::showpoint) != static_cast<local_flags_type>(0U));

      // Write the output string in the desired format.
      if     (my_float_field == detail::os_float_field_type::scientific) { wr_string_scientific(str, the_exp, os_precision, my_showpoint, my_uppercase); }
      else if(my_float_field == detail::os_float_field_type::fixed)      { wr_string_fixed     (str, the_exp, os_precision, my_showpoint); }
      else // os_float_field_none
      {
        (use_scientific ? wr_string_scientific(str, the_exp, os_precision, my_showpoint, my_uppercase, true)
                        : wr_string_fixed     (str, the_exp, os_precision, my_showpoint, true));
      }

      // Append the sign.
      if     (isneg())    { str.insert(static_cast<std::size_t>(0U), static_cast<std::size_t>(1U), '-'); }
      else if(my_showpos) { str.insert(static_cast<std::size_t>(0U), static_cast<std::size_t>(1U), '+'); }

      // Handle std::setw(...), std::setfill(...), std::left, std::right, std::internal.
      const auto my_width =
        static_cast<std::uint_fast32_t>
        (
          (os.width() >= static_cast<std::streamsize>(0)) ? static_cast<std::uint_fast32_t>(os.width())
                                                          : static_cast<std::uint_fast32_t>(0U)
        );

      if(my_width > str.length())
      {
        // Get the number of fill characters.
        const auto n_fill = static_cast<std::uint_fast32_t>(my_width - str.length());

        // Left-justify is the exception, std::right and std::internal justify right.
        const auto my_left =
        (
          static_cast<local_flags_type>(my_flags & std::ios::left) != static_cast<local_flags_type>(0U)
        );

        // Justify left or right and insert the fill characters.
        str.insert((my_left ? str.end() : str.begin()), static_cast<std::size_t>(n_fill), os.fill());
      }
    }

    static auto wr_string_scientific(      std::string&       str, // NOLINT(google-runtime-references)
                                     const exponent_type      the_exp,
                                     const std::uint_fast32_t os_precision,
                                     const bool               my_showpoint,
                                     const bool               my_uppercase,
                                     const bool               trim_trailing_zeros = false) -> void
    {
      if(os_precision > static_cast<std::uint_fast32_t>(str.length() - 1U))
      {
        // Zero-extend the string to the given precision if necessary.
        const auto n_pad = static_cast<std::uint_fast32_t>(os_precision - (str.length() - 1U));

        str.insert(str.end(), static_cast<std::size_t>(n_pad), '0');
      }

      // Insert the decimal point.
      str.insert(static_cast<std::size_t>(1U), static_cast<std::size_t>(1U), '.');

      // Trim the trailing zeros, where the trim-characteristics depend on the showpoint flag.
      if(trim_trailing_zeros)
      {
        const std::string::const_reverse_iterator rit_non_zero =
          std::find_if(str.crbegin(),
                       str.crend(),
                       [](const char& c) // NOLINT(modernize-use-trailing-return-type)
                       {
                         return (c != '0');
                       });

        if(rit_non_zero != str.rbegin())
        {
          const std::ptrdiff_t ofs =   static_cast<std::ptrdiff_t>(str.length())
                                     - static_cast<std::ptrdiff_t>(rit_non_zero - str.crbegin());

          str.erase(str.begin() + ofs, str.end());
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
        if(*(str.end() - 1U) == '.')
        {
          str.erase(str.end() - 1U, str.end());
        }
      }

      // Append the exponent in uppercase or lower case, including its sign.
      const auto b_exp_is_neg = (the_exp < static_cast<exponent_type>(0));

      const auto u_exp =
        static_cast<std::uint64_t>
        (
          (!b_exp_is_neg) ? the_exp : static_cast<exponent_type>(-the_exp)
        );

      str.push_back(my_uppercase ? 'E' : 'e');

      str.push_back((!b_exp_is_neg) ? '+' : '-');

      std::array<char, 20U> ptr_str = {{ '\0' }}; // NOLINT(,cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)

      char* ptr_end = util::baselexical_cast(u_exp, ptr_str.data()); // NOLINT(cppcoreguidelines-pro-type-vararg,hicpp-vararg)

      auto str_exp = std::string(ptr_str.data(), ptr_end);

      // Format the exponent string to have a width that is an even multiple of three.
      const auto str_exp_len      = static_cast<std::size_t>(str_exp.length());
      const auto str_exp_len_mod3 = static_cast<std::size_t>(str_exp_len % 3U);

      const auto str_exp_len_pad =
        static_cast<std::size_t>
        (
          ((str_exp_len_mod3 != static_cast<std::size_t>(0U)) ? static_cast<std::uint_fast32_t>(3U - (str_exp_len % 3U))
                                                              : static_cast<std::uint_fast32_t>(0U))
        );

      str.insert(str.end(), static_cast<std::size_t>(str_exp_len_pad), '0');

      str += str_exp;
    }

    static auto wr_string_fixed(      std::string&       str, // NOLINT(google-runtime-references)
                                const exponent_type      the_exp,
                                const std::uint_fast32_t os_precision,
                                const bool               my_showpoint,
                                const bool               trim_trailing_zeros = false) -> void
    {
      const auto input_str_len = static_cast<std::size_t>(str.length());

      if(the_exp < static_cast<exponent_type>(0))
      {
        // The number is less than one in magnitude. Insert the decimal
        // point using "0." as well as the needed number of leading zeros.
        const auto zero_insert_length =
          static_cast<std::size_t>
          (
            static_cast<exponent_type>(-the_exp) - 1
          );

        const auto n_pad =
          static_cast<exponent_type>
          (
              static_cast<exponent_type>(os_precision)
            - static_cast<exponent_type>(str.length() + zero_insert_length)
          );

        str.insert(static_cast<std::size_t>(0U), zero_insert_length, '0');
        str.insert(static_cast<std::size_t>(0U), static_cast<std::size_t>(1U), '.');
        str.insert(static_cast<std::size_t>(0U), static_cast<std::size_t>(1U), '0');

        // Zero-extend the string to the given precision if necessary.
        if(n_pad > static_cast<exponent_type>(0))
        {
          str.insert(str.end(), static_cast<std::size_t>(n_pad), '0');
        }
      }
      else
      {
        // Insert the decimal point.
        const auto my_exp_plus_one = static_cast<std::uint_fast32_t>(static_cast<exponent_type>(the_exp + 1));

        // The number string is not large enough to hold the integer part of the number.
        // Zero extend the integer part of the string.
        if(input_str_len < static_cast<std::size_t>(my_exp_plus_one))
        {
          str.insert(str.end(), static_cast<std::size_t>(my_exp_plus_one - static_cast<std::uint_fast32_t>(str.length())), '0');
        }

        str.insert(static_cast<std::size_t>(my_exp_plus_one), static_cast<std::size_t>(1U), '.');

        // Zero-extend the string to the given precision if necessary.
        const auto n_pad =
          static_cast<exponent_type>
          (
              static_cast<exponent_type>(os_precision)
            - static_cast<exponent_type>
              (
                  static_cast<exponent_type>(str.length() - static_cast<std::size_t>(1U))
                - static_cast<exponent_type>(the_exp + static_cast<exponent_type>(1))
              )
          );

        if(n_pad > static_cast<exponent_type>(0))
        {
          str.insert(str.end(), static_cast<std::size_t>(n_pad), '0');
        }
      }

      // Trim the trailing zeros, where the trim-characteristics depend on the showpoint flag.
      if(trim_trailing_zeros)
      {
        const auto rit_non_zero =
          std::find_if(str.crbegin(),
                        str.crend(),
                        [](const char& c) // NOLINT(modernize-use-trailing-return-type)
                        {
                          return (c != '0');
                        });

        if(rit_non_zero != str.rbegin())
        {
          const auto ofs =
            static_cast<std::ptrdiff_t>
            (
                static_cast<std::ptrdiff_t>(str.length())
              - std::distance<std::string::const_reverse_iterator>(str.crbegin(), rit_non_zero)
            );

          str.erase(str.begin() + ofs, str.end());
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
        if(str.back() == '.')
        {
          str.pop_back();
        }
      }
    }

    static auto special_extend_string_to_precision(std::string& str, // NOLINT(google-runtime-references)
                                                   std::uint_fast32_t os_precision) -> void
    {
      // This is the special case of showpoint in combination with
      // a non-fixed, non-scientific representation. The string has
      // to be zero extended such that the total width of its entire
      // non-zero part exactly equals the precision.

      // Check if the input number is less than 1.
      if(   (str.at(static_cast<std::uint_fast32_t>(0U)) == '0')
         && (str.at(static_cast<std::uint_fast32_t>(1U)) == '.')
        )
      {
        if(str.length() == static_cast<std::uint_fast32_t>(2U))
        {
          // This string represents zero and needs zero extension.
          str.insert(str.end(), static_cast<std::size_t>(os_precision), '0');
        }
        else
        {
          // This is a non-zero decimal less than 1 that needs zero extension.
          const auto it_non_zero =
            std::find_if(str.begin() + 2U,
                         str.end(),
                         [](const char& c) // NOLINT(modernize-use-trailing-return-type)
                         {
                           return (c != '0');
                         });

          const auto len_non_zero_part = static_cast<std::uint_fast32_t>(str.end() - it_non_zero);

          const auto u_pad = static_cast<std::uint_fast32_t>(os_precision - len_non_zero_part);

          str.insert(str.end(), static_cast<std::size_t>(u_pad), '0');
        }
      }
      else
      {
        // This is a number greater than or equal to 1 that needs zero extension.
        const auto u_pad =
          static_cast<std::uint_fast32_t>
          (
              os_precision
            - static_cast<std::uint_fast32_t>
              (
                str.length() - static_cast<std::uint_fast32_t>(1U)
              )
          );

        str.insert(str.end(), static_cast<std::size_t>(u_pad), '0');
      }
    }

    template<typename char_type, typename traits_type>
    friend auto operator<<(std::basic_ostream<char_type, traits_type>& os, const decwide_t& f) -> std::basic_ostream<char_type, traits_type>&
    {
      std::string str;

      f.wr_string(str, os);

      return (os << str);
    }

    template<typename char_type, typename traits_type>
    friend auto operator>>(std::basic_istream<char_type, traits_type>& is, decwide_t& f) -> std::basic_istream<char_type, traits_type>&
    {
      std::string str;

      static_cast<void>(is >> str);

      static_cast<void>(f.rd_string(str.c_str()));

      return is;
    }
    #endif // !WIDE_DECIMAL_DISABLE_IOSTREAM

    friend inline auto fabs(const decwide_t& x) -> decwide_t
    {
      return (x.isneg() ? decwide_t(x).negate() : x);
    }

    friend inline auto abs(const decwide_t& x) -> decwide_t
    {
      return fabs(x);
    }

    friend inline auto floor(const decwide_t& x) -> decwide_t
    {
      auto result(x);

      if((x.isfinite)())
      {
        result.eval_round_self();

        if(!result.isint())
        {
          if(result.isneg())
          {
            result -= one<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>();
          }

          result = result.extract_integer_part();
        }
      }

      return result;
    }

    friend inline auto ceil(const decwide_t& x) -> decwide_t
    {
      auto result(x);

      if((x.isfinite)())
      {
        result.eval_round_self();

        if(!result.isint())
        {
          if(!result.isneg())
          {
            result += one<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>();
          }

          result = result.extract_integer_part();
        }
      }

      return result;
    }

    friend inline auto ilogb(const decwide_t& x) -> exponent_type
    {
      auto xx = x.my_data[0U];

      auto p10 = static_cast<exponent_type>(-1);

      while(static_cast<limb_type>(static_cast<limb_type>(xx + static_cast<std::uint8_t>(UINT8_C(9))) / static_cast<std::uint8_t>(UINT8_C(10))) > static_cast<std::uint8_t>(UINT8_C(0)))
      {
        xx = static_cast<limb_type>(xx / static_cast<std::uint8_t>(UINT8_C(10)));

        ++p10;
      }

      return static_cast<exponent_type>(x.my_exp + p10);
    }

    template<const std::int32_t OtherMyDigits10, typename OtherLimbType, typename OtherAllocatorType, typename OtherInternalFloatType, typename OtherExponentType, typename OtherFftFloatType>
    friend constexpr auto zero() -> decwide_t<OtherMyDigits10, OtherLimbType, OtherAllocatorType, OtherInternalFloatType, OtherExponentType, OtherFftFloatType>; // NOLINT(readability-redundant-declaration)

    template<const std::int32_t OtherMyDigits10, typename OtherLimbType, typename OtherAllocatorType, typename OtherInternalFloatType, typename OtherExponentType, typename OtherFftFloatType>
    friend constexpr auto one() -> decwide_t<OtherMyDigits10, OtherLimbType, OtherAllocatorType, OtherInternalFloatType, OtherExponentType, OtherFftFloatType>; // NOLINT(readability-redundant-declaration)

    template<const std::int32_t OtherMyDigits10, typename OtherLimbType, typename OtherAllocatorType, typename OtherInternalFloatType, typename OtherExponentType, typename OtherFftFloatType>
    friend constexpr auto two() -> decwide_t<OtherMyDigits10, OtherLimbType, OtherAllocatorType, OtherInternalFloatType, OtherExponentType, OtherFftFloatType>; // NOLINT(readability-redundant-declaration)

    template<const std::int32_t OtherMyDigits10, typename OtherLimbType, typename OtherAllocatorType, typename OtherInternalFloatType, typename OtherExponentType, typename OtherFftFloatType>
    friend constexpr auto half() -> decwide_t<OtherMyDigits10, OtherLimbType, OtherAllocatorType, OtherInternalFloatType, OtherExponentType, OtherFftFloatType>; // NOLINT(readability-redundant-declaration)
  };

  template<const std::int32_t ParamDigitsBaseTen, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType>
  constexpr auto zero() -> decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>
  {
    using other_wide_decimal_type =
      decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>;

    return
      other_wide_decimal_type::from_lst
      (
        { static_cast<typename other_wide_decimal_type::limb_type>(0U) }
      );
  }

  template<const std::int32_t ParamDigitsBaseTen, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType>
  constexpr auto one() -> decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>
  {
    using other_wide_decimal_type =
      decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>;

    return
      other_wide_decimal_type::from_lst
      (
        { static_cast<typename other_wide_decimal_type::limb_type>(1U) }
      );
  }

  template<const std::int32_t ParamDigitsBaseTen, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType>
  constexpr auto two() -> decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>
  {
    using other_wide_decimal_type =
      decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>;

    return
      other_wide_decimal_type::from_lst
      (
        { static_cast<typename other_wide_decimal_type::limb_type>(2U) }
      );
  }

  template<const std::int32_t ParamDigitsBaseTen, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType>
  constexpr auto half() -> decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>
  {
    using other_wide_decimal_type =
      decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>;

    return
      other_wide_decimal_type::from_lst
      (
        {
          static_cast<typename other_wide_decimal_type::limb_type>(other_wide_decimal_type::decwide_t_elem_mask / 2)
        },
        -other_wide_decimal_type::decwide_t_elem_digits10
      );
  }

  template<const std::int32_t ParamDigitsBaseTen, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType> constexpr std::int32_t decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>::decwide_t_digits10;       // NOLINT(readability-redundant-declaration,hicpp-uppercase-literal-suffix,readability-uppercase-literal-suffix)
  template<const std::int32_t ParamDigitsBaseTen, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType> constexpr std::int32_t decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>::decwide_t_digits;         // NOLINT(readability-redundant-declaration,hicpp-uppercase-literal-suffix,readability-uppercase-literal-suffix)
  template<const std::int32_t ParamDigitsBaseTen, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType> constexpr std::int32_t decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>::decwide_t_max_digits10;   // NOLINT(readability-redundant-declaration,hicpp-uppercase-literal-suffix,readability-uppercase-literal-suffix)
  template<const std::int32_t ParamDigitsBaseTen, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType> constexpr std::int32_t decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>::decwide_t_radix;          // NOLINT(readability-redundant-declaration,hicpp-uppercase-literal-suffix,readability-uppercase-literal-suffix)
  template<const std::int32_t ParamDigitsBaseTen, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType> constexpr std::int32_t decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>::decwide_t_elem_digits10;  // NOLINT(readability-redundant-declaration,hicpp-uppercase-literal-suffix,readability-uppercase-literal-suffix)
  template<const std::int32_t ParamDigitsBaseTen, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType> constexpr std::int32_t decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>::decwide_t_elem_number;    // NOLINT(readability-redundant-declaration,hicpp-uppercase-literal-suffix,readability-uppercase-literal-suffix)
  template<const std::int32_t ParamDigitsBaseTen, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType> constexpr std::int32_t decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>::decwide_t_elem_mask;      // NOLINT(readability-redundant-declaration,hicpp-uppercase-literal-suffix,readability-uppercase-literal-suffix)
  template<const std::int32_t ParamDigitsBaseTen, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType> constexpr std::int32_t decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>::decwide_t_elem_mask_half; // NOLINT(readability-redundant-declaration,hicpp-uppercase-literal-suffix,readability-uppercase-literal-suffix)
  template<const std::int32_t ParamDigitsBaseTen, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType> constexpr std::int32_t decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>::decwide_t_elems_for_kara; // NOLINT(readability-redundant-declaration,hicpp-uppercase-literal-suffix,readability-uppercase-literal-suffix)
  template<const std::int32_t ParamDigitsBaseTen, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType> constexpr std::int32_t decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>::decwide_t_elems_for_fft;  // NOLINT(readability-redundant-declaration,hicpp-uppercase-literal-suffix,readability-uppercase-literal-suffix)

  template<const std::int32_t ParamDigitsBaseTen, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType> constexpr typename decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>::exponent_type decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>::decwide_t_max_exp10; // NOLINT(readability-redundant-declaration,hicpp-uppercase-literal-suffix,readability-uppercase-literal-suffix)
  template<const std::int32_t ParamDigitsBaseTen, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType> constexpr typename decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>::exponent_type decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>::decwide_t_min_exp10; // NOLINT(readability-redundant-declaration,hicpp-uppercase-literal-suffix,readability-uppercase-literal-suffix)
  template<const std::int32_t ParamDigitsBaseTen, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType> constexpr typename decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>::exponent_type decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>::decwide_t_max_exp;   // NOLINT(readability-redundant-declaration,hicpp-uppercase-literal-suffix,readability-uppercase-literal-suffix)
  template<const std::int32_t ParamDigitsBaseTen, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType> constexpr typename decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>::exponent_type decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>::decwide_t_min_exp;   // NOLINT(readability-redundant-declaration,hicpp-uppercase-literal-suffix,readability-uppercase-literal-suffix)

  #if !defined(WIDE_DECIMAL_DISABLE_CACHED_CONSTANTS)
  template<const std::int32_t ParamDigitsBaseTen, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType>
  const typename decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>::initializer decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>::my_initializer; // NOLINT(hicpp-uppercase-literal-suffix,readability-uppercase-literal-suffix)
  #endif

  #if !defined(WIDE_DECIMAL_DISABLE_DYNAMIC_MEMORY_ALLOCATION)
  #else
  template<const std::int32_t ParamDigitsBaseTen, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType> std::array<typename decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>::limb_type, static_cast<std::size_t>((decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>::decwide_t_elems_for_kara - 1) * 2)>                                                                                                    decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>::my_school_mul_pool; // NOLINT(hicpp-uppercase-literal-suffix,readability-uppercase-literal-suffix,cppcoreguidelines-avoid-non-const-global-variables)
  template<const std::int32_t ParamDigitsBaseTen, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType> std::array<typename decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>::limb_type, static_cast<std::size_t>(detail::a029750::a029750_as_constexpr     (static_cast<std::uint32_t>(static_cast<std::uint32_t>(decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>::decwide_t_elems_for_fft - 1)) * 8UL))> decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>::my_kara_mul_pool;   // NOLINT(hicpp-uppercase-literal-suffix,readability-uppercase-literal-suffix,cppcoreguidelines-avoid-non-const-global-variables,cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
  template<const std::int32_t ParamDigitsBaseTen, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType> std::array<typename decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>::fft_float_type, static_cast<std::size_t>(detail::a000079::a000079_as_constexpr(static_cast<std::uint32_t>(static_cast<std::uint32_t>(decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>::decwide_t_elem_number)) * 4UL))>       decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>::my_af_fft_mul_pool; // NOLINT(hicpp-uppercase-literal-suffix,readability-uppercase-literal-suffix,cppcoreguidelines-avoid-non-const-global-variables)
  template<const std::int32_t ParamDigitsBaseTen, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType> std::array<typename decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>::fft_float_type, static_cast<std::size_t>(detail::a000079::a000079_as_constexpr(static_cast<std::uint32_t>(static_cast<std::uint32_t>(decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>::decwide_t_elem_number)) * 4UL))>       decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>::my_bf_fft_mul_pool; // NOLINT(hicpp-uppercase-literal-suffix,readability-uppercase-literal-suffix,cppcoreguidelines-avoid-non-const-global-variables)
  template<const std::int32_t ParamDigitsBaseTen, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType> typename decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>::representation_type decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>::my_n_data_for_add_sub;                                                                                                                                                                                                                                                                        // NOLINT(hicpp-uppercase-literal-suffix,readability-uppercase-literal-suffix,cppcoreguidelines-avoid-non-const-global-variables,cert-err58-cpp)
  #endif

  template<const std::int32_t ParamDigitsBaseTen,
           typename LimbType,
           typename AllocatorType,
           typename InternalFloatType,
           typename ExponentType,
           typename FftFloatType>
  #if !defined(WIDE_DECIMAL_DISABLE_USE_STD_FUNCTION)
  auto calc_pi(const std::function<void(const std::uint32_t)>& pfn_callback_to_report_digits10) -> typename std::enable_if<(ParamDigitsBaseTen > static_cast<std::int32_t>(INT8_C(51))), decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>>::type
  #else
  auto calc_pi(void(*pfn_callback_to_report_digits10)(const std::uint32_t)) -> typename std::enable_if<(ParamDigitsBaseTen > static_cast<std::int32_t>(INT8_C(51))), decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>>::type
  #endif
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
      pfn_callback_to_report_digits10(UINT32_C(0));
    }

    using floating_point_type =
      decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>;

    floating_point_type val_pi;

    floating_point_type a(1U);

    // Initialize bB to 0.5.
    floating_point_type bB(half<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>()); // NOLINT(readability-identifier-naming)

    // Initialize t to 0.375.
    floating_point_type t(static_cast<floating_point_type>(3U) / 8U); // NOLINT(,cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)

    floating_point_type s(bB);

    // This loop is designed for a maximum of several million
    // decimal digits of pi. The index k should reach no higher
    // than about 25 or 30. After about 20 iterations, the precision
    // is about one million decimal digits.

    const auto digits10_iteration_goal =
      static_cast<std::uint32_t>
      (
          static_cast<std::uint32_t>(std::numeric_limits<floating_point_type>::digits10 / 2)
        + (std::max)(static_cast<std::uint32_t>(floating_point_type::decwide_t_elem_digits10  + 1),
                     static_cast<std::uint32_t>(UINT8_C(9)))
      );

    using std::log;
    using std::lround;

    const auto digits10_scale =
      static_cast<std::uint32_t>
      (
        lround
        (
          static_cast<float>
          (
              static_cast<float>
              (
                1000.0F * log(static_cast<float>(std::numeric_limits<floating_point_type>::radix))
              )
            / log(10.0F)
          )
        )
      );

    for(auto   k = static_cast<unsigned>(UINT8_C(0));
               k < static_cast<unsigned>(UINT8_C(48));
             ++k)
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
      iterate_term *= static_cast<unsigned long long>(1ULL << (k + 1U)); // NOLINT(google-runtime-int)

      s += iterate_term;

      // Test the number of precise digits from this iteration.
      // If it is there are enough precise digits, then the calculation
      // is finished.
      const auto ib =
        static_cast<std::int32_t>
        (
          (std::max)(static_cast<std::int32_t>(0),
                     static_cast<std::int32_t>(-ilogb(iterate_term)))
        );

      const auto digits10_of_iteration =
        static_cast<std::uint32_t>
        (
            static_cast<std::uint64_t>(static_cast<std::uint64_t>(ib) * digits10_scale)
          / static_cast<std::uint32_t>(UINT16_C(1000))
        );

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
      pfn_callback_to_report_digits10(static_cast<std::uint32_t>(std::numeric_limits<floating_point_type>::digits10));
    }

    return val_pi;
  }

  template<const std::int32_t ParamDigitsBaseTen,
           typename LimbType,
           typename AllocatorType,
           typename InternalFloatType,
           typename ExponentType,
           typename FftFloatType>
  #if !defined(WIDE_DECIMAL_DISABLE_USE_STD_FUNCTION)
  auto calc_pi(const std::function<void(const std::uint32_t)>& pfn_callback_to_report_digits10) -> typename std::enable_if<((ParamDigitsBaseTen <= static_cast<std::int32_t>(INT8_C(51))) && std::is_same<LimbType, std::uint8_t>::value), decwide_t<ParamDigitsBaseTen, std::uint8_t, AllocatorType, InternalFloatType, ExponentType, FftFloatType>>::type
  #else
  auto calc_pi(void(*pfn_callback_to_report_digits10)(const std::uint32_t)) -> typename std::enable_if<((ParamDigitsBaseTen <= static_cast<std::int32_t>(INT8_C(51))) && std::is_same<LimbType, std::uint8_t>::value), decwide_t<ParamDigitsBaseTen, std::uint8_t, AllocatorType, InternalFloatType, ExponentType, FftFloatType>>::type
  #endif
  {
    // N[Pi, 121]
    // 3.141592653589793238462643383279502884197169399375105820974944592307816406286208998628034825342117067982148086513282306647

    static_cast<void>(pfn_callback_to_report_digits10);

    using floating_point_type =
      decwide_t<ParamDigitsBaseTen, std::uint8_t, AllocatorType, InternalFloatType, ExponentType, FftFloatType>;

    return
      floating_point_type::from_lst
      (
        {
          UINT8_C( 3),
          UINT8_C(14), UINT8_C(15), UINT8_C(92), UINT8_C(65), UINT8_C(35), UINT8_C(89), UINT8_C(79), UINT8_C(32),
          UINT8_C(38), UINT8_C(46), UINT8_C(26), UINT8_C(43), UINT8_C(38), UINT8_C(32), UINT8_C(79), UINT8_C(50),
          UINT8_C(28), UINT8_C(84), UINT8_C(19), UINT8_C(71), UINT8_C(69), UINT8_C(39), UINT8_C(93), UINT8_C(75),
          UINT8_C(10), UINT8_C(58), UINT8_C(20), UINT8_C(97), UINT8_C(49), UINT8_C(44), UINT8_C(59), UINT8_C(23),
          UINT8_C( 7), UINT8_C(81), UINT8_C(64), UINT8_C( 6), UINT8_C(28), UINT8_C(62), UINT8_C( 8), UINT8_C(99),
          UINT8_C(86), UINT8_C(28), UINT8_C( 3), UINT8_C(48), UINT8_C(25), UINT8_C(34), UINT8_C(21), UINT8_C(17)
        }
      );
  }

  template<const std::int32_t ParamDigitsBaseTen,
           typename LimbType,
           typename AllocatorType,
           typename InternalFloatType,
           typename ExponentType,
           typename FftFloatType>
  #if !defined(WIDE_DECIMAL_DISABLE_USE_STD_FUNCTION)
  auto calc_pi(const std::function<void(const std::uint32_t)>& pfn_callback_to_report_digits10) -> typename std::enable_if<((ParamDigitsBaseTen <= static_cast<std::int32_t>(INT8_C(51))) && std::is_same<LimbType, std::uint16_t>::value), decwide_t<ParamDigitsBaseTen, std::uint16_t, AllocatorType, InternalFloatType, ExponentType, FftFloatType>>::type
  #else
  auto calc_pi(void(*pfn_callback_to_report_digits10)(const std::uint32_t)) -> typename std::enable_if<((ParamDigitsBaseTen <= static_cast<std::int32_t>(INT8_C(51))) && std::is_same<LimbType, std::uint16_t>::value), decwide_t<ParamDigitsBaseTen, std::uint16_t, AllocatorType, InternalFloatType, ExponentType, FftFloatType>>::type
  #endif
  {
    // N[Pi, 121]
    // 3.141592653589793238462643383279502884197169399375105820974944592307816406286208998628034825342117067982148086513282306647

    static_cast<void>(pfn_callback_to_report_digits10);

    using floating_point_type =
      decwide_t<ParamDigitsBaseTen, std::uint16_t, AllocatorType, InternalFloatType, ExponentType, FftFloatType>;

    return
      floating_point_type::from_lst
      (
        {
          UINT16_C(   3),
          UINT16_C(1415), UINT16_C(9265), UINT16_C(3589), UINT16_C(7932),
          UINT16_C(3846), UINT16_C(2643), UINT16_C(3832), UINT16_C(7950),
          UINT16_C(2884), UINT16_C(1971), UINT16_C(6939), UINT16_C(9375),
          UINT16_C(1058), UINT16_C(2097), UINT16_C(4944), UINT16_C(5923),
          UINT16_C( 781), UINT16_C(6406), UINT16_C(2862), UINT16_C( 899),
          UINT16_C(8628), UINT16_C( 348), UINT16_C(2534), UINT16_C(2117)
        }
      );
  }

  template<const std::int32_t ParamDigitsBaseTen,
           typename LimbType,
           typename AllocatorType,
           typename InternalFloatType,
           typename ExponentType,
           typename FftFloatType>
  #if !defined(WIDE_DECIMAL_DISABLE_USE_STD_FUNCTION)
  auto calc_pi(const std::function<void(const std::uint32_t)>& pfn_callback_to_report_digits10) -> typename std::enable_if<((ParamDigitsBaseTen <= static_cast<std::int32_t>(INT8_C(51))) && std::is_same<LimbType, std::uint32_t>::value), decwide_t<ParamDigitsBaseTen, std::uint32_t, AllocatorType, InternalFloatType, ExponentType, FftFloatType>>::type
  #else
  auto calc_pi(void(*pfn_callback_to_report_digits10)(const std::uint32_t)) -> typename std::enable_if<((ParamDigitsBaseTen <= static_cast<std::int32_t>(INT8_C(51))) && std::is_same<LimbType, std::uint32_t>::value), decwide_t<ParamDigitsBaseTen, std::uint32_t, AllocatorType, InternalFloatType, ExponentType, FftFloatType>>::type
  #endif
  {
    // N[Pi, 121]
    // 3.141592653589793238462643383279502884197169399375105820974944592307816406286208998628034825342117067982148086513282306647

    static_cast<void>(pfn_callback_to_report_digits10);

    using floating_point_type =
      decwide_t<ParamDigitsBaseTen, std::uint32_t, AllocatorType, InternalFloatType, ExponentType, FftFloatType>;

    return
      floating_point_type::from_lst
      (
        {
          UINT32_C(       3),
          UINT32_C(14159265), UINT32_C(35897932),
          UINT32_C(38462643), UINT32_C(38327950),
          UINT32_C(28841971), UINT32_C(69399375),
          UINT32_C(10582097), UINT32_C(49445923),
          UINT32_C( 7816406), UINT32_C(28620899),
          UINT32_C(86280348), UINT32_C(25342117)
        }
      );
  }

  template<const std::int32_t ParamDigitsBaseTen, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType>
  auto calc_ln_two() -> typename std::enable_if<(ParamDigitsBaseTen > static_cast<std::int32_t>(INT8_C(51))), decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>>::type
  {
    using floating_point_type = decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>;

    // Use an AGM method to compute log(2).

    // Set a0 = 1
    // Set b0 = 1 / (2^(m-2))

    floating_point_type ak(1U);

    constexpr auto n_times_factor =
      static_cast<float>
      (
        static_cast<float>(std::numeric_limits<floating_point_type>::digits10) * 1.67F
      );

    // Ensure that the resulting power is non-negative.
    // Also enforce that m >= 3.
    const auto m =
      (std::max)
      (
        static_cast<std::int32_t>(n_times_factor),
        static_cast<std::int32_t>(3)
      );

    floating_point_type bk =
      ldexp(one<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>(), static_cast<std::int32_t>(2 - m));

    const auto digits10_iteration_goal =
      static_cast<std::uint32_t>
      (
          static_cast<std::uint32_t>(std::numeric_limits<floating_point_type>::digits10 / 2)
        + (std::max)(static_cast<std::uint32_t>(floating_point_type::decwide_t_elem_digits10 + 1),
                     static_cast<std::uint32_t>(UINT8_C(9)))
      );

    using std::log;
    using std::lround;

    const auto digits10_scale =
      static_cast<std::uint32_t>
      (
        lround
        (
          static_cast<float>
          (
              static_cast<float>
              (
                1000.0F * log(static_cast<float>(std::numeric_limits<floating_point_type>::radix))
              )
            / log(10.0F)
          )
        )
      );

    for(auto   k = static_cast<std::uint32_t>(UINT8_C(0));
               k < static_cast<std::uint32_t>(UINT8_C(128));
             ++k)
    {
      using std::ilogb;

      // Check for the number of significant digits to be
      // at least half of the requested digits. If at least
      // half of the requested digits have been achieved,
      // then break after the upcoming iteration.

      const auto ib = (std::max)(static_cast<std::int32_t>(0),
                                 static_cast<std::int32_t>(-ilogb(ak - bk)));

      const auto digits10_of_iteration =
        static_cast<std::uint32_t>
        (
            static_cast<std::uint64_t>(static_cast<std::uint64_t>(ib) * digits10_scale)
          / static_cast<std::uint32_t>(UINT16_C(1000))
        );

      const floating_point_type ak_tmp(ak);

      ak += bk;

      if(digits10_of_iteration > digits10_iteration_goal)
      {
        break;
      }

      using std::sqrt;

      ak /= 2U;
      bk *= ak_tmp;
      bk  = sqrt(bk);
    }

    // We are now finished with the AGM iteration for log(2).
    // Note at this time that (ak = bk) = AGM(...)
    // Retrieve the value of pi and divide by (a * (2 * m)).

    return
      (
          pi<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>()
        * ak.calculate_inv()
      )
      / m;
  }

  template<const std::int32_t ParamDigitsBaseTen, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType>
  auto calc_ln_two() -> typename std::enable_if<((ParamDigitsBaseTen <= static_cast<std::int32_t>(INT8_C(51))) && std::is_same<LimbType, std::uint8_t>::value), decwide_t<ParamDigitsBaseTen, std::uint8_t, AllocatorType, InternalFloatType, ExponentType, FftFloatType>>::type
  {
    // N[Log[2], 121]
    // 0.6931471805599453094172321214581765680755001343602552541206800094933936219696947156058633269964186875420014810205706857337

    using floating_point_type =
      decwide_t<ParamDigitsBaseTen, std::uint8_t, AllocatorType, InternalFloatType, ExponentType, FftFloatType>;

    return
      floating_point_type::from_lst
      (
        {
          UINT8_C(69), UINT8_C(31), UINT8_C(47), UINT8_C(18),
          UINT8_C( 5), UINT8_C(59), UINT8_C(94), UINT8_C(53), UINT8_C( 9), UINT8_C(41), UINT8_C(72), UINT8_C(32),
          UINT8_C(12), UINT8_C(14), UINT8_C(58), UINT8_C(17), UINT8_C(65), UINT8_C(68), UINT8_C( 7), UINT8_C(55),
          UINT8_C( 0), UINT8_C(13), UINT8_C(43), UINT8_C(60), UINT8_C(25), UINT8_C(52), UINT8_C(54), UINT8_C(12),
          UINT8_C( 6), UINT8_C(80), UINT8_C( 0), UINT8_C(94), UINT8_C(93), UINT8_C(39), UINT8_C(36), UINT8_C(21),
          UINT8_C(96), UINT8_C(96), UINT8_C(94), UINT8_C(71), UINT8_C(56), UINT8_C( 5), UINT8_C(86), UINT8_C(33),
          UINT8_C(26), UINT8_C(99), UINT8_C(64), UINT8_C(18), UINT8_C(68), UINT8_C(75), UINT8_C(42), UINT8_C( 0),
        },
        static_cast<typename floating_point_type::exponent_type>(INT8_C(-8))
      );
  }

  template<const std::int32_t ParamDigitsBaseTen, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType>
  auto calc_ln_two() -> typename std::enable_if<((ParamDigitsBaseTen <= static_cast<std::int32_t>(INT8_C(51))) && std::is_same<LimbType, std::uint16_t>::value), decwide_t<ParamDigitsBaseTen, std::uint16_t, AllocatorType, InternalFloatType, ExponentType, FftFloatType>>::type
  {
    // N[Log[2], 121]
    // 0.6931471805599453094172321214581765680755001343602552541206800094933936219696947156058633269964186875420014810205706857337

    using floating_point_type =
      decwide_t<ParamDigitsBaseTen, std::uint16_t, AllocatorType, InternalFloatType, ExponentType, FftFloatType>;

    return
      floating_point_type::from_lst
      (
        {
          UINT16_C(6931), UINT16_C(4718),
          UINT16_C( 559), UINT16_C(9453), UINT16_C( 941), UINT16_C(7232),
          UINT16_C(1214), UINT16_C(5817), UINT16_C(6568), UINT16_C( 755),
          UINT16_C(  13), UINT16_C(4360), UINT16_C(2552), UINT16_C(5412),
          UINT16_C( 680), UINT16_C(  94), UINT16_C(9339), UINT16_C(3621),
          UINT16_C(9696), UINT16_C(9471), UINT16_C(5605), UINT16_C(8633),
          UINT16_C(2699), UINT16_C(6418), UINT16_C(6875), UINT16_C(4200),
        },
        static_cast<typename floating_point_type::exponent_type>(INT8_C(-8))
      );
  }

  template<const std::int32_t ParamDigitsBaseTen, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType>
  auto calc_ln_two() -> typename std::enable_if<((ParamDigitsBaseTen <= static_cast<std::int32_t>(INT8_C(51))) && std::is_same<LimbType, std::uint32_t>::value), decwide_t<ParamDigitsBaseTen, std::uint32_t, AllocatorType, InternalFloatType, ExponentType, FftFloatType>>::type
  {
    // N[Log[2], 121]
    // 0.6931471805599453094172321214581765680755001343602552541206800094933936219696947156058633269964186875420014810205706857337

    using floating_point_type =
      decwide_t<ParamDigitsBaseTen, std::uint32_t, AllocatorType, InternalFloatType, ExponentType, FftFloatType>;

    return
      floating_point_type::from_lst
      (
        {
          UINT32_C(69314718),
          UINT32_C( 5599453), UINT32_C( 9417232),
          UINT32_C(12145817), UINT32_C(65680755),
          UINT32_C(  134360), UINT32_C(25525412),
          UINT32_C( 6800094), UINT32_C(93393621),
          UINT32_C(96969471), UINT32_C(56058633),
          UINT32_C(26996418), UINT32_C(68754200),
        },
        static_cast<typename floating_point_type::exponent_type>(INT8_C(-8))
      );
  }

  template<const std::int32_t ParamDigitsBaseTen, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType>
  auto calc_ln_ten_low_precision() -> typename std::enable_if<((ParamDigitsBaseTen <= static_cast<std::int32_t>(INT8_C(51))) && std::is_same<LimbType, std::uint8_t>::value), decwide_t<ParamDigitsBaseTen, std::uint8_t, AllocatorType, InternalFloatType, ExponentType, FftFloatType>>::type
  {
    // N[Log[10], 121]
    // 2.302585092994045684017991454684364207601101488628772976033327900967572609677352480235997205089598298341967784042286248633

    using floating_point_type =
      decwide_t<ParamDigitsBaseTen, std::uint8_t, AllocatorType, InternalFloatType, ExponentType, FftFloatType>;

    return
      floating_point_type::from_lst
      (
        {
          UINT8_C( 2),
          UINT8_C(30), UINT8_C(25), UINT8_C(85), UINT8_C( 9), UINT8_C(29), UINT8_C(94), UINT8_C( 4), UINT8_C(56),
          UINT8_C(84), UINT8_C( 1), UINT8_C(79), UINT8_C(91), UINT8_C(45), UINT8_C(46), UINT8_C(84), UINT8_C(36),
          UINT8_C(42), UINT8_C( 7), UINT8_C(60), UINT8_C(11), UINT8_C( 1), UINT8_C(48), UINT8_C(86), UINT8_C(28),
          UINT8_C(77), UINT8_C(29), UINT8_C(76), UINT8_C( 3), UINT8_C(33), UINT8_C(27), UINT8_C(90), UINT8_C( 9),
          UINT8_C(67), UINT8_C(57), UINT8_C(26), UINT8_C( 9), UINT8_C(67), UINT8_C(73), UINT8_C(52), UINT8_C(48),
          UINT8_C( 2), UINT8_C(35), UINT8_C(99), UINT8_C(72), UINT8_C( 5), UINT8_C( 8), UINT8_C(95), UINT8_C(98),
        }
      );
  }

  template<const std::int32_t ParamDigitsBaseTen, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType>
  auto calc_ln_ten_low_precision() -> typename std::enable_if<((ParamDigitsBaseTen <= static_cast<std::int32_t>(INT8_C(51))) && std::is_same<LimbType, std::uint16_t>::value), decwide_t<ParamDigitsBaseTen, std::uint16_t, AllocatorType, InternalFloatType, ExponentType, FftFloatType>>::type
  {
    // N[Log[10], 121]
    // 2.302585092994045684017991454684364207601101488628772976033327900967572609677352480235997205089598298341967784042286248633

    using floating_point_type =
      decwide_t<ParamDigitsBaseTen, std::uint16_t, AllocatorType, InternalFloatType, ExponentType, FftFloatType>;

    return
      floating_point_type::from_lst
      (
        {
          UINT16_C(   2),
          UINT16_C(3025), UINT16_C(8509), UINT16_C(2994), UINT16_C( 456),
          UINT16_C(8401), UINT16_C(7991), UINT16_C(4546), UINT16_C(8436),
          UINT16_C(4207), UINT16_C(6011), UINT16_C( 148), UINT16_C(8628),
          UINT16_C(7729), UINT16_C(7603), UINT16_C(3327), UINT16_C(9009),
          UINT16_C(6757), UINT16_C(2609), UINT16_C(6773), UINT16_C(5248),
          UINT16_C( 235), UINT16_C(9972), UINT16_C( 508), UINT16_C(9598)
        }
      );
  }

  template<const std::int32_t ParamDigitsBaseTen, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType>
  auto calc_ln_ten_low_precision() -> typename std::enable_if<((ParamDigitsBaseTen <= static_cast<std::int32_t>(INT8_C(51))) && std::is_same<LimbType, std::uint32_t>::value), decwide_t<ParamDigitsBaseTen, std::uint32_t, AllocatorType, InternalFloatType, ExponentType, FftFloatType>>::type
  {
    // N[Log[10], 121]
    // 2.302585092994045684017991454684364207601101488628772976033327900967572609677352480235997205089598298341967784042286248633

    using floating_point_type =
      decwide_t<ParamDigitsBaseTen, std::uint32_t, AllocatorType, InternalFloatType, ExponentType, FftFloatType>;

    return
      floating_point_type::from_lst
      (
        {
          UINT32_C(       2),
          UINT32_C(30258509), UINT32_C(29940456),
          UINT32_C(84017991), UINT32_C(45468436),
          UINT32_C(42076011), UINT32_C( 1488628),
          UINT32_C(77297603), UINT32_C(33279009),
          UINT32_C(67572609), UINT32_C(67735248),
          UINT32_C( 2359972), UINT32_C( 5089598)
        }
      );
  }

  #if !defined(WIDE_DECIMAL_DISABLE_CACHED_CONSTANTS)
  template<const std::int32_t ParamDigitsBaseTen, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType>
  #if !defined(WIDE_DECIMAL_DISABLE_USE_STD_FUNCTION)
  auto pi(const std::function<void(const std::uint32_t)>& pfn_callback_to_report_digits10) -> const decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>&
  #else
  auto pi(void(*pfn_callback_to_report_digits10)(const std::uint32_t)) -> const decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>&
  #endif
  {
    static_cast<void>(pfn_callback_to_report_digits10);

    return decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>::my_value_pi();
  }
  #else
  template<const std::int32_t ParamDigitsBaseTen, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType>
  #if !defined(WIDE_DECIMAL_DISABLE_USE_STD_FUNCTION)
  auto pi(const std::function<void(const std::uint32_t)>& pfn_callback_to_report_digits10) -> decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>
  #else
  auto pi(void(*pfn_callback_to_report_digits10)(const std::uint32_t)) -> decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>
  #endif
  {
    return calc_pi<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>(pfn_callback_to_report_digits10);
  }
  #endif

  #if !defined(WIDE_DECIMAL_DISABLE_CACHED_CONSTANTS)
  template<const std::int32_t ParamDigitsBaseTen, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType>
  auto ln_two() -> const decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>&
  {
    return decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>::my_value_ln_two();
  }
  #else
  template<const std::int32_t ParamDigitsBaseTen, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType>
  auto ln_two() -> decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>
  {
    return calc_ln_two<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>();
  }
  #endif

  // Global unary operators of decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType> reference.
  template<const std::int32_t ParamDigitsBaseTen, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType> auto operator+(const decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>& self) -> decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType> { return decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>(self); }
  template<const std::int32_t ParamDigitsBaseTen, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType> auto operator-(const decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>& self) -> decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType> { decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType> tmp(self); return tmp.negate(); }

  // Global add/sub/mul/div of const decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>& with const decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>&.
  template<const std::int32_t ParamDigitsBaseTen, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType>auto operator+(const decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>& u, const decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>& v) -> decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType> { return decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>(u) += v; }
  template<const std::int32_t ParamDigitsBaseTen, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType>auto operator-(const decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>& u, const decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>& v) -> decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType> { return decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>(u) -= v; }
  template<const std::int32_t ParamDigitsBaseTen, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType>auto operator*(const decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>& u, const decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>& v) -> decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType> { return decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>(u) *= v; }
  template<const std::int32_t ParamDigitsBaseTen, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType>auto operator/(const decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>& u, const decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>& v) -> decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType> { return decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>(u) /= v; }

  // Global add/sub/mul/div of const decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>& with all built-in types.
  template<const std::int32_t ParamDigitsBaseTen, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType, typename SignedIntegralType>
  auto operator+(const decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>& u,
                 SignedIntegralType n) -> typename std::enable_if<     std::is_integral<SignedIntegralType>::value
                                                                  && (!std::is_unsigned<SignedIntegralType>::value),
                                                                  decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>>::type
  {
    return decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>(u).add_signed_long_long(n);
  }

  template<const std::int32_t ParamDigitsBaseTen, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType, typename UnsignedIntegralType>
  auto operator+(const decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>& u,
                 UnsignedIntegralType n) -> typename std::enable_if<   std::is_integral<UnsignedIntegralType>::value
                                                                    && std::is_unsigned<UnsignedIntegralType>::value,
                                                                    decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>>::type
  {
    return decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>(u).add_unsigned_long_long(n);
  }

  template<const std::int32_t ParamDigitsBaseTen, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType, typename FloatingPointType>
  auto operator+(const decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>& u,
                 FloatingPointType f) -> typename std::enable_if<std::is_floating_point<FloatingPointType>::value,
                                                                 decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>>::type
  {
    return decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>(u) += decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>(f);
  }

  template<const std::int32_t ParamDigitsBaseTen, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType, typename SignedIntegralType>
  auto operator-(const decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>& u,
                 SignedIntegralType n) -> typename std::enable_if<     std::is_integral<SignedIntegralType>::value
                                                                  && (!std::is_unsigned<SignedIntegralType>::value),
                                                                  decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>>::type
  {
    return decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>(u).sub_signed_long_long(n);
  }

  template<const std::int32_t ParamDigitsBaseTen, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType, typename UnsignedIntegralType>
  auto operator-(const decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>& u,
                 UnsignedIntegralType n) -> typename std::enable_if<   std::is_integral<UnsignedIntegralType>::value
                                                                    && std::is_unsigned<UnsignedIntegralType>::value,
                                                                    decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>>::type
  {
    return decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>(u).sub_unsigned_long_long(n);
  }

  template<const std::int32_t ParamDigitsBaseTen, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType, typename FloatingPointType>
  auto operator-(const decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>& u,
                 FloatingPointType f) -> typename std::enable_if<std::is_floating_point<FloatingPointType>::value,
                                                                 decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>>::type
  {
    return decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>(u) -= decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>(f);
  }

  template<const std::int32_t ParamDigitsBaseTen, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType, typename SignedIntegralType>
  auto operator*(const decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>& u,
                 SignedIntegralType n) -> typename std::enable_if<   std::is_integral<SignedIntegralType>::value
                                                                  && (!std::is_unsigned<SignedIntegralType>::value),
                                                                  decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>>::type
  {
    return decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>(u).mul_signed_long_long(n);
  }

  template<const std::int32_t ParamDigitsBaseTen, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType, typename UnsignedIntegralType>
  auto operator*(const decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>& u,
                 UnsignedIntegralType n) -> typename std::enable_if<   std::is_integral<UnsignedIntegralType>::value
                                                                    && std::is_unsigned<UnsignedIntegralType>::value,
                                                                    decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>>::type
  {
    return decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>(u).mul_unsigned_long_long(n);
  }

  template<const std::int32_t ParamDigitsBaseTen, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType, typename FloatingPointType>
  auto operator*(const decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>& u,
                 FloatingPointType f) -> typename std::enable_if<std::is_floating_point<FloatingPointType>::value,
                                                                 decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>>::type
  {
    return decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>(u) *= decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>(f);
  }

  template<const std::int32_t ParamDigitsBaseTen, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType, typename SignedIntegralType>
  auto operator/(const decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>& u,
                 SignedIntegralType n) -> typename std::enable_if<     std::is_integral<SignedIntegralType>::value
                                                                  && (!std::is_unsigned<SignedIntegralType>::value),
                                                                  decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>>::type
  {
    return decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>(u).div_signed_long_long(n);
  }

  template<const std::int32_t ParamDigitsBaseTen, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType, typename UnsignedIntegralType>
  auto operator/(const decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>& u,
                 UnsignedIntegralType n) -> typename std::enable_if<   std::is_integral<UnsignedIntegralType>::value
                                                                    && std::is_unsigned<UnsignedIntegralType>::value,
                                                                    decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>>::type
  {
    return decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>(u).div_unsigned_long_long(n);
  }

  template<const std::int32_t ParamDigitsBaseTen, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType, typename FloatingPointType>
  auto operator/(const decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>& u,
                 FloatingPointType f) -> typename std::enable_if<std::is_floating_point<FloatingPointType>::value,
                                                                 decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>>::type
  {
    return decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>(u) /= decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>(f);
  }

  // Global add/sub/mul/div of all built-in types with const decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>&.
  template<const std::int32_t ParamDigitsBaseTen, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType, typename SignedIntegralType>
  auto operator+(SignedIntegralType n,
                 const decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>& u) -> typename std::enable_if<   std::is_integral<SignedIntegralType>::value
                                                                                                                                                    && (!std::is_unsigned<SignedIntegralType>::value),
                                                                                                                                                    decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>>::type
  {
    return decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>(u).add_signed_long_long(n);
  }

  template<const std::int32_t ParamDigitsBaseTen, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType, typename UnsignedIntegralType>
  auto operator+(UnsignedIntegralType n,
                 const decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>& u) -> typename std::enable_if<   std::is_integral<UnsignedIntegralType>::value
                                                                                                                                                    && std::is_unsigned<UnsignedIntegralType>::value,
                                                                                                                                                    decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>>::type
  {
    return decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>(u).add_unsigned_long_long(n);
  }

  template<const std::int32_t ParamDigitsBaseTen, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType, typename FloatingPointType>
  auto operator+(FloatingPointType f,
                 const decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>& u) -> typename std::enable_if<std::is_floating_point<FloatingPointType>::value,
                                                                                                                                                            decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>>::type
  {
    return decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>(f) += u;
  }

  template<const std::int32_t ParamDigitsBaseTen, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType, typename ArithmeticType>
  auto operator-(ArithmeticType n,
                 const decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>& u) -> typename std::enable_if<std::is_arithmetic<ArithmeticType>::value,
                                                                                                                                                            decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>>::type
  {
    return decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>(n) -= u;
  }

  template<const std::int32_t ParamDigitsBaseTen, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType, typename SignedIntegralType>
  auto operator*(SignedIntegralType n,
                 const decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>& u) -> typename std::enable_if<     std::is_integral<SignedIntegralType>::value
                                                                                                                                                            && (!std::is_unsigned<SignedIntegralType>::value),
                                                                                                                                                            decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>>::type
  {
    return decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>(u).mul_signed_long_long(n);
  }

  template<const std::int32_t ParamDigitsBaseTen, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType, typename UnsignedIntegralType>
  auto operator*(UnsignedIntegralType n,
                 const decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>& u) -> typename std::enable_if<   std::is_integral<UnsignedIntegralType>::value
                                                                                                                                                            && std::is_unsigned<UnsignedIntegralType>::value,
                                                                                                                                                            decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>>::type
  {
    return decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>(u).mul_unsigned_long_long(n);
  }

  template<const std::int32_t ParamDigitsBaseTen, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType, typename FloatingPointType>
  auto operator*(FloatingPointType f,
                 const decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>& u) -> typename std::enable_if<std::is_floating_point<FloatingPointType>::value,
                                                                                                                                                            decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>>::type
  {
    return decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>(f) *= u;
  }

  template<const std::int32_t ParamDigitsBaseTen, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType, typename ArithmeticType>
  auto operator/(ArithmeticType n,
                 const decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>& u) -> typename std::enable_if<std::is_arithmetic<ArithmeticType>::value,
                                                                                                                                                            decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>>::type
  {
    return decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>(n) /= u;
  }

  // Global self add/sub/mul/div of decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>& with all built-in types.
  template<const std::int32_t ParamDigitsBaseTen, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType, typename SignedIntegralType>
  auto operator+=(decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>& u,
                  SignedIntegralType n) -> typename std::enable_if<     std::is_integral<SignedIntegralType>::value
                                                                   && (!std::is_unsigned<SignedIntegralType>::value),
                                                                   decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>>::type
  {
    return u.add_signed_long_long(n);
  }

  template<const std::int32_t ParamDigitsBaseTen, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType, typename UnsignedIntegralType>
  auto operator+=(decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>& u,
                  UnsignedIntegralType n) -> typename std::enable_if<   std::is_integral<UnsignedIntegralType>::value
                                                                     && std::is_unsigned<UnsignedIntegralType>::value,
                                                                     decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>>::type
  {
    return u.add_unsigned_long_long(n);
  }

  template<const std::int32_t ParamDigitsBaseTen, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType, typename FloatingPointType>
  auto operator+=(decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>& u,
                  FloatingPointType f) -> typename std::enable_if<std::is_floating_point<FloatingPointType>::value,
                                                                  decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>>::type
  {
    return u += decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>(f);
  }

  template<const std::int32_t ParamDigitsBaseTen, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType, typename SignedIntegralType>
  auto operator-=(decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>& u,
                  SignedIntegralType n) -> typename std::enable_if<     std::is_integral<SignedIntegralType>::value
                                                                   && (!std::is_unsigned<SignedIntegralType>::value),
                                                                   decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>>::type
  {
    return u.sub_signed_long_long(n);
  }

  template<const std::int32_t ParamDigitsBaseTen, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType, typename UnsignedIntegralType>
  auto operator-=(decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>& u,
                  UnsignedIntegralType n) -> typename std::enable_if<   std::is_integral<UnsignedIntegralType>::value
                                                                     && std::is_unsigned<UnsignedIntegralType>::value,
                                                                     decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>>::type
  {
    return u.sub_unsigned_long_long(n);
  }

  template<const std::int32_t ParamDigitsBaseTen, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType, typename FloatingPointType>
  auto operator-=(decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>& u,
                  FloatingPointType f) -> typename std::enable_if<std::is_floating_point<FloatingPointType>::value,
                                                                  decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>>::type
  {
    return u -= decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>(f);
  }

  template<const std::int32_t ParamDigitsBaseTen, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType, typename SignedIntegralType>
  auto operator*=(decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>& u,
                  SignedIntegralType n) -> typename std::enable_if<     std::is_integral<SignedIntegralType>::value
                                                                   && (!std::is_unsigned<SignedIntegralType>::value),
                                                                   decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>>::type
  {
    return u.mul_signed_long_long(n);
  }

  template<const std::int32_t ParamDigitsBaseTen, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType, typename UnsignedIntegralType>
  auto operator*=(decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>& u,
                  UnsignedIntegralType n) -> typename std::enable_if<   std::is_integral<UnsignedIntegralType>::value
                                                                     && std::is_unsigned<UnsignedIntegralType>::value,
                                                                     decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>>::type
  {
    return u.mul_unsigned_long_long(n);
  }

  template<const std::int32_t ParamDigitsBaseTen, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType, typename FloatingPointType>
  auto operator*=(decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>& u,
                  FloatingPointType f) -> typename std::enable_if<std::is_floating_point<FloatingPointType>::value,
                                                                  decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>>::type
  {
    return u *= decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>(f);
  }

  template<const std::int32_t ParamDigitsBaseTen, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType, typename SignedIntegralType>
  auto operator/=(decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>& u,
                  SignedIntegralType n) -> typename std::enable_if<   std::is_integral<SignedIntegralType>::value
                                                                   && (!std::is_unsigned<SignedIntegralType>::value),
                                                                   decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>>::type
  {
    return u.div_signed_long_long(n);
  }

  template<const std::int32_t ParamDigitsBaseTen, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType, typename UnsignedIntegralType>
  auto operator/=(decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>& u,
                  UnsignedIntegralType n) -> typename std::enable_if<   std::is_integral<UnsignedIntegralType>::value
                                                                     && std::is_unsigned<UnsignedIntegralType>::value,
                                                                     decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>>::type
  {
    return u.div_unsigned_long_long(n);
  }

  template<const std::int32_t ParamDigitsBaseTen, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType, typename FloatingPointType>
  auto operator/=(decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>& u,
                  FloatingPointType f) -> typename std::enable_if<std::is_floating_point<FloatingPointType>::value,
                                                                  decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>>::type
  {
    return u /= decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>(f);
  }

  // Global comparison operators of const decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, typename ExponentType>& with const decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>&.
  template<const std::int32_t ParamDigitsBaseTen, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType> auto operator< (const decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>& u, const decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>& v) -> bool { return (u.cmp(v) <  static_cast<std::int_fast8_t>(0)); }
  template<const std::int32_t ParamDigitsBaseTen, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType> auto operator<=(const decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>& u, const decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>& v) -> bool { return (u.cmp(v) <= static_cast<std::int_fast8_t>(0)); }
  template<const std::int32_t ParamDigitsBaseTen, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType> auto operator==(const decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>& u, const decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>& v) -> bool { return (u.cmp(v) == static_cast<std::int_fast8_t>(0)); }
  template<const std::int32_t ParamDigitsBaseTen, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType> auto operator!=(const decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>& u, const decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>& v) -> bool { return (u.cmp(v) != static_cast<std::int_fast8_t>(0)); }
  template<const std::int32_t ParamDigitsBaseTen, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType> auto operator>=(const decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>& u, const decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>& v) -> bool { return (u.cmp(v) >= static_cast<std::int_fast8_t>(0)); }
  template<const std::int32_t ParamDigitsBaseTen, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType> auto operator> (const decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>& u, const decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>& v) -> bool { return (u.cmp(v) >  static_cast<std::int_fast8_t>(0)); }

  // Global comparison operators of const decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>& with all built-in types.
  template<const std::int32_t ParamDigitsBaseTen, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType, typename ArithmeticType> auto operator< (const decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>& u, const ArithmeticType& v) -> typename std::enable_if<std::is_arithmetic<ArithmeticType>::value, bool>::type { return (u.cmp(decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>(v)) <  static_cast<std::int_fast8_t>(0)); }
  template<const std::int32_t ParamDigitsBaseTen, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType, typename ArithmeticType> auto operator<=(const decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>& u, const ArithmeticType& v) -> typename std::enable_if<std::is_arithmetic<ArithmeticType>::value, bool>::type { return (u.cmp(decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>(v)) <= static_cast<std::int_fast8_t>(0)); }
  template<const std::int32_t ParamDigitsBaseTen, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType, typename ArithmeticType> auto operator==(const decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>& u, const ArithmeticType& v) -> typename std::enable_if<std::is_arithmetic<ArithmeticType>::value, bool>::type { return (u.cmp(decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>(v)) == static_cast<std::int_fast8_t>(0)); }
  template<const std::int32_t ParamDigitsBaseTen, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType, typename ArithmeticType> auto operator!=(const decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>& u, const ArithmeticType& v) -> typename std::enable_if<std::is_arithmetic<ArithmeticType>::value, bool>::type { return (u.cmp(decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>(v)) != static_cast<std::int_fast8_t>(0)); }
  template<const std::int32_t ParamDigitsBaseTen, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType, typename ArithmeticType> auto operator>=(const decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>& u, const ArithmeticType& v) -> typename std::enable_if<std::is_arithmetic<ArithmeticType>::value, bool>::type { return (u.cmp(decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>(v)) >= static_cast<std::int_fast8_t>(0)); }
  template<const std::int32_t ParamDigitsBaseTen, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType, typename ArithmeticType> auto operator> (const decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>& u, const ArithmeticType& v) -> typename std::enable_if<std::is_arithmetic<ArithmeticType>::value, bool>::type { return (u.cmp(decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>(v)) >  static_cast<std::int_fast8_t>(0)); }

  // Global comparison operators of all built-in types with const decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>&.
  template<const std::int32_t ParamDigitsBaseTen, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType, typename ArithmeticType> auto operator< (ArithmeticType u, const decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>& v) -> typename std::enable_if<std::is_arithmetic<ArithmeticType>::value, bool>::type { return (decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>(u).cmp(v) <  static_cast<std::int_fast8_t>(0)); }
  template<const std::int32_t ParamDigitsBaseTen, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType, typename ArithmeticType> auto operator<=(ArithmeticType u, const decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>& v) -> typename std::enable_if<std::is_arithmetic<ArithmeticType>::value, bool>::type { return (decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>(u).cmp(v) <= static_cast<std::int_fast8_t>(0)); }
  template<const std::int32_t ParamDigitsBaseTen, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType, typename ArithmeticType> auto operator==(ArithmeticType u, const decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>& v) -> typename std::enable_if<std::is_arithmetic<ArithmeticType>::value, bool>::type { return (decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>(u).cmp(v) == static_cast<std::int_fast8_t>(0)); }
  template<const std::int32_t ParamDigitsBaseTen, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType, typename ArithmeticType> auto operator!=(ArithmeticType u, const decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>& v) -> typename std::enable_if<std::is_arithmetic<ArithmeticType>::value, bool>::type { return (decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>(u).cmp(v) != static_cast<std::int_fast8_t>(0)); }
  template<const std::int32_t ParamDigitsBaseTen, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType, typename ArithmeticType> auto operator>=(ArithmeticType u, const decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>& v) -> typename std::enable_if<std::is_arithmetic<ArithmeticType>::value, bool>::type { return (decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>(u).cmp(v) >= static_cast<std::int_fast8_t>(0)); }
  template<const std::int32_t ParamDigitsBaseTen, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType, typename ArithmeticType> auto operator> (ArithmeticType u, const decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>& v) -> typename std::enable_if<std::is_arithmetic<ArithmeticType>::value, bool>::type { return (decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>(u).cmp(v) >  static_cast<std::int_fast8_t>(0)); }

  #if(__cplusplus >= 201703L)
  } // namespace math::wide_decimal
  #else
  } // namespace wide_decimal
  } // namespace math
  #endif

  WIDE_DECIMAL_NAMESPACE_END

  // Specialization of std::numeric_limits<decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>>.
  namespace std
  {
    template<const std::int32_t ParamDigitsBaseTen,
             typename LimbType,
             typename AllocatorType,
             typename InternalFloatType,
             typename ExponentType,
             typename FftFloatType>
    #if defined(WIDE_DECIMAL_NAMESPACE)
    class numeric_limits<WIDE_DECIMAL_NAMESPACE::math::wide_decimal::decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>>
    #else
    class numeric_limits<math::wide_decimal::decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>>
    #endif
    {
    public:
      #if defined(WIDE_DECIMAL_NAMESPACE)
      using local_wide_decimal_type =
        WIDE_DECIMAL_NAMESPACE::math::wide_decimal::decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>;
      #else
      using local_wide_decimal_type =
        math::wide_decimal::decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>;
      #endif

      using local_exponent_type =
        typename local_wide_decimal_type::exponent_type;

      static constexpr bool                    is_specialized    = true;
      static constexpr bool                    is_signed         = true;
      static constexpr bool                    is_integer        = false;
      static constexpr bool                    is_exact          = false;
      static constexpr bool                    is_bounded        = true;
      static constexpr bool                    is_modulo         = false;
      static constexpr bool                    is_iec559         = false;
      #if defined(WIDE_DECIMAL_NAMESPACE)
      static constexpr std::int32_t            digits            = WIDE_DECIMAL_NAMESPACE::math::wide_decimal::decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>::decwide_t_digits;       // Type differs from int.
      static constexpr std::int32_t            digits10          = WIDE_DECIMAL_NAMESPACE::math::wide_decimal::decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>::decwide_t_digits10;     // Type differs from int.
      static constexpr std::int32_t            max_digits10      = WIDE_DECIMAL_NAMESPACE::math::wide_decimal::decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>::decwide_t_max_digits10; // Type differs from int.
      static constexpr local_exponent_type     min_exponent      = WIDE_DECIMAL_NAMESPACE::math::wide_decimal::decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>::decwide_t_min_exp;      // Type differs from int.
      static constexpr local_exponent_type     min_exponent10    = WIDE_DECIMAL_NAMESPACE::math::wide_decimal::decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>::decwide_t_min_exp10;    // Type differs from int.
      static constexpr local_exponent_type     max_exponent      = WIDE_DECIMAL_NAMESPACE::math::wide_decimal::decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>::decwide_t_max_exp;      // Type differs from int.
      static constexpr local_exponent_type     max_exponent10    = WIDE_DECIMAL_NAMESPACE::math::wide_decimal::decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>::decwide_t_max_exp10;    // Type differs from int.
      static constexpr int                     radix             = WIDE_DECIMAL_NAMESPACE::math::wide_decimal::decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>::decwide_t_radix;
      #else
      static constexpr std::int32_t            digits            = math::wide_decimal::decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>::decwide_t_digits;       // Type differs from int.
      static constexpr std::int32_t            digits10          = math::wide_decimal::decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>::decwide_t_digits10;     // Type differs from int.
      static constexpr std::int32_t            max_digits10      = math::wide_decimal::decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>::decwide_t_max_digits10; // Type differs from int.
      static constexpr local_exponent_type     min_exponent      = math::wide_decimal::decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>::decwide_t_min_exp;      // Type differs from int.
      static constexpr local_exponent_type     min_exponent10    = math::wide_decimal::decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>::decwide_t_min_exp10;    // Type differs from int.
      static constexpr local_exponent_type     max_exponent      = math::wide_decimal::decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>::decwide_t_max_exp;      // Type differs from int.
      static constexpr local_exponent_type     max_exponent10    = math::wide_decimal::decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>::decwide_t_max_exp10;    // Type differs from int.
      static constexpr int                     radix             = math::wide_decimal::decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>::decwide_t_radix;
      #endif
      static constexpr std::float_round_style  round_style       = std::round_to_nearest;
      static constexpr bool                    has_infinity      = false;
      static constexpr bool                    has_quiet_NaN     = false;
      static constexpr bool                    has_signaling_NaN = false;
      static constexpr std::float_denorm_style has_denorm        = std::denorm_absent;
      static constexpr bool                    has_denorm_loss   = false;
      static constexpr bool                    traps             = false;
      static constexpr bool                    tinyness_before   = false;

      static constexpr auto (min)        () -> local_wide_decimal_type { return local_wide_decimal_type::my_value_min(); }
      static constexpr auto (max)        () -> local_wide_decimal_type { return local_wide_decimal_type::my_value_max(); }
      #if defined(WIDE_DECIMAL_NAMESPACE)
      static constexpr auto lowest       () -> local_wide_decimal_type { return WIDE_DECIMAL_NAMESPACE::math::wide_decimal::zero<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>(); }
      #else
      static constexpr auto lowest       () -> local_wide_decimal_type { return math::wide_decimal::zero<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>(); }
      #endif
      static constexpr auto epsilon      () -> local_wide_decimal_type { return local_wide_decimal_type::my_value_eps(); }
      #if defined(WIDE_DECIMAL_NAMESPACE)
      static constexpr auto round_error  () -> local_wide_decimal_type { return WIDE_DECIMAL_NAMESPACE::math::wide_decimal::half<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>(); }
      static constexpr auto infinity     () -> local_wide_decimal_type { return WIDE_DECIMAL_NAMESPACE::math::wide_decimal::zero<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>(); }
      static constexpr auto quiet_NaN    () -> local_wide_decimal_type { return WIDE_DECIMAL_NAMESPACE::math::wide_decimal::zero<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>(); }
      static constexpr auto signaling_NaN() -> local_wide_decimal_type { return WIDE_DECIMAL_NAMESPACE::math::wide_decimal::zero<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>(); }
      static constexpr auto denorm_min   () -> local_wide_decimal_type { return WIDE_DECIMAL_NAMESPACE::math::wide_decimal::zero<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>(); }
      #else
      static constexpr auto round_error  () -> local_wide_decimal_type { return math::wide_decimal::half<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>(); }
      static constexpr auto infinity     () -> local_wide_decimal_type { return math::wide_decimal::zero<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>(); }
      static constexpr auto quiet_NaN    () -> local_wide_decimal_type { return math::wide_decimal::zero<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>(); } // NOLINT(readability-identifier-naming)
      static constexpr auto signaling_NaN() -> local_wide_decimal_type { return math::wide_decimal::zero<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>(); } // NOLINT(readability-identifier-naming)
      static constexpr auto denorm_min   () -> local_wide_decimal_type { return math::wide_decimal::zero<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>(); }
      #endif
    };
  } // namespace std

  WIDE_DECIMAL_NAMESPACE_BEGIN

  #if(__cplusplus >= 201703L)
  namespace math::wide_decimal {
  #else
  namespace math { namespace wide_decimal { // NOLINT(modernize-concat-nested-namespaces)
  #endif

  template<const std::int32_t ParamDigitsBaseTen, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType> constexpr auto unsigned_long_long_max() -> decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType> { return decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>((std::numeric_limits<unsigned long long>::max)()); } // NOLINT(google-runtime-int)
  template<const std::int32_t ParamDigitsBaseTen, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType> constexpr auto signed_long_long_min  () -> decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType> { return decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>((std::numeric_limits<signed long long>::min)()); }   // NOLINT(google-runtime-int)
  template<const std::int32_t ParamDigitsBaseTen, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType> constexpr auto signed_long_long_max  () -> decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType> { return decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>((std::numeric_limits<signed long long>::max)()); }   // NOLINT(google-runtime-int)
  template<const std::int32_t ParamDigitsBaseTen, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType> constexpr auto long_double_min       () -> decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType> { return decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>((std::numeric_limits<long double>::min)());}
  template<const std::int32_t ParamDigitsBaseTen, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType> constexpr auto long_double_max       () -> decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType> { return decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>((std::numeric_limits<long double>::max)());}

  template<const std::int32_t ParamDigitsBaseTen, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType> auto (isnan)   (const decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>& x) -> bool { return (x.isnan)(); }
  template<const std::int32_t ParamDigitsBaseTen, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType> auto (isfinite)(const decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>& x) -> bool { return (x.isfinite)(); }
  template<const std::int32_t ParamDigitsBaseTen, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType> auto (isinf)   (const decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>& x) -> bool { return (x.isinf)(); }
  template<const std::int32_t ParamDigitsBaseTen, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType> auto (signbit) (const decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>& x) -> bool { return  x.isneg(); }

  template<const std::int32_t ParamDigitsBaseTen, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType>
  auto pow(const decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>& x,
           const decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>& a) -> decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>
  {
    decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType> pow_result;

    if(a.iszero())
    {
      pow_result = one<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>();
    }
    else
    {
      pow_result = exp(a * log(x));
    }

    return pow_result;
  }

  template<const std::int32_t ParamDigitsBaseTen, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType>
  auto ldexp(const decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>& v, int e) -> decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>
  {
    decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType> ldexp_result(v);

    if((e > 0) && (e < 64)) // NOLINT(,cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
    {
      ldexp_result *= static_cast<std::uint64_t>(1ULL << static_cast<unsigned>(e));
    }
    else if((e > -64) && (e < 0)) // NOLINT(,cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
    {
      ldexp_result /= static_cast<std::uint64_t>(1ULL << static_cast<unsigned>(-e));
    }
    else if(e != 0)
    {
      ldexp_result *= pow(two<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>(), e);
    }

    return ldexp_result;
  }

  template<const std::int32_t ParamDigitsBaseTen, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType>
  auto frexp(const decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>& v,
             int* expon) -> decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>
  {
    using exponent_type =
      typename decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>::exponent_type;

    double        d { };
    exponent_type i { };

    v.extract_parts(d, i);

    *expon = static_cast<int>(i);

    return v * ldexp(one<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>(), static_cast<int>(-i));
  }

  template<const std::int32_t ParamDigitsBaseTen, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType>
  auto fmod(const decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>& v1,
            const decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>& v2) -> decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>
  {
    const decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType> n = ((v1 < 0) ? ceil(v1 / v2) : floor(v1 / v2));

    return v1 - (n * v2);
  }

  template<const std::int32_t ParamDigitsBaseTen, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType>
  auto sqrt(const decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>& x) -> decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>
  {
    return
      decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>
      (
        x
      ).calculate_sqrt();
  }

  template<const std::int32_t ParamDigitsBaseTen, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType>
  auto cbrt(const decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>& x) -> decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>
  {
    return rootn(x, static_cast<std::int32_t>(3));
  }

  template<const std::int32_t ParamDigitsBaseTen, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType>
  auto rootn(const decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>& x, std::int32_t p) -> decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType> // NOLINT(misc-no-recursion)
  {
    decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType> rtn;

    if(p < static_cast<std::int32_t>(0))
    {
      rtn = rootn(one<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>() / x, static_cast<std::int32_t>(-p));
    }
    else if((p == static_cast<std::int32_t>(0)) || ((x < 0) && (p != static_cast<std::int32_t>(3))))
    {
      rtn = std::numeric_limits<decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>>::quiet_NaN();
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
      const auto b_neg = (x < 0);

      using std::fabs;

      rtn = fabs(x).calculate_rootn_inv(3).calculate_inv();

      if(b_neg) { static_cast<void>(rtn.negate()); }
    }
    else
    {
      rtn =
        decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>
        (
          x
        ).calculate_rootn_inv(p).calculate_inv();
    }

    return rtn;
  }

  template<const std::int32_t ParamDigitsBaseTen, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType>
  auto rootn_inv(const decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>& x,
                 std::int32_t p) -> decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>
  {
    return
      decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>
      (
        x
      ).calculate_rootn_inv(p);
  }

  template<const std::int32_t ParamDigitsBaseTen, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType>
  auto log(const decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>& x) -> typename std::enable_if<(ParamDigitsBaseTen > static_cast<std::int32_t>(INT8_C(51))), decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>>::type // NOLINT(misc-no-recursion)
  {
    using floating_point_type = decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>;

    floating_point_type result { };

    if(x < one<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>())
    {
      floating_point_type xx(x);

      static_cast<void>(xx.calculate_inv());

      result = -log(xx);
    }
    else if(x > one<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>())
    {
      const auto precision_of_x = floating_point_type::get_precision(x);

      // Use an AGM method to compute the logarithm of x.
      // Set a0 = 1
      // Set b0 = 4 / (x * 2^m)
      //        = 1 / (x * 2^(m - 2))

      result = one<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>();

      const auto n_times_factor =
        static_cast<float>
        (
          static_cast<float>(static_cast<float>(std::numeric_limits<floating_point_type>::digits10)) * 1.67F
        );

      // Extract lg_xx = Log[mantissa * radix^ib]
      //               = Log[mantissa] + ib * Log[radix],
      // where the logarithm of the mantissa is simply neglected
      // in the approximation.

      using std::ilogb;

      using local_exponent_type = typename floating_point_type::exponent_type;

      auto ilogb_of_x = static_cast<local_exponent_type>(ilogb(x));

      using std::log;

      const auto lg_x_approx =
        static_cast<float>
        (
            static_cast<float>(ilogb_of_x)
          * log(static_cast<float>(std::numeric_limits<floating_point_type>::radix))
        );

      const auto lg_x_over_lg2 = static_cast<float>(lg_x_approx / log(2.0F));

      // Ensure that the resulting power is non-negative.
      // Also enforce that m >= 3.
      const auto m = (std::max)(static_cast<std::int32_t>(n_times_factor - lg_x_over_lg2),
                                static_cast<std::int32_t>(3));

      floating_point_type bk =
        one<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>();

      bk.precision(precision_of_x);

      bk = ldexp(bk, static_cast<std::int32_t>(2 - m));

      bk /= x;

      // TBD: Tolerance should have the log of the argument added to it (usually negligible).
      const auto digits10_iteration_goal_a =
        static_cast<std::uint32_t>
        (
            static_cast<std::uint32_t>(std::numeric_limits<floating_point_type>::digits10 / 2)
          + (std::max)(static_cast<std::uint32_t>(floating_point_type::decwide_t_elem_digits10 + 1),
                       static_cast<std::uint32_t>(UINT8_C(9)))
        );

      const auto digits10_iteration_goal_b =
        static_cast<std::uint32_t>
        (
            static_cast<std::uint32_t>(precision_of_x / 2)
          + (std::max)(static_cast<std::uint32_t>(floating_point_type::decwide_t_elem_digits10 + 1),
                       static_cast<std::uint32_t>(UINT8_C(9)))
        );

      const auto digits10_iteration_goal =
        static_cast<local_exponent_type>
        (
          (std::min)(digits10_iteration_goal_a, digits10_iteration_goal_b)
        );

      using std::lround;

      const auto digits10_scale =
        static_cast<std::uint32_t>
        (
          lround
          (
              static_cast<float>
              (
                  1000.0F
                * log(static_cast<float>(std::numeric_limits<floating_point_type>::radix))
              )
            / log(10.0F)
          )
        );

      for(auto   k = static_cast<std::uint32_t>(UINT8_C(0));
                 k < static_cast<std::uint32_t>(UINT8_C(128));
               ++k)
      {
        // Check for the number of significant digits to be
        // at least half of the requested digits. If at least
        // half of the requested digits have been achieved,
        // then break after the upcoming iteration.

        const auto ilogb_of_ak_minus_bk =
          (std::max)(static_cast<std::int32_t>(0),
                     static_cast<std::int32_t>(-ilogb(result - bk)));

        const auto digits10_of_iteration =
          static_cast<local_exponent_type>
          (
            static_cast<std::uint64_t>(static_cast<std::uint64_t>(ilogb_of_ak_minus_bk) * digits10_scale) / UINT32_C(1000)
          );

        const floating_point_type ak_tmp(result);

        result += bk;

        if(digits10_of_iteration > digits10_iteration_goal)
        {
          break;
        }

        using std::sqrt;

        result /= 2;
        bk *= ak_tmp;
        static_cast<void>(bk.calculate_sqrt());
      }

      // We are now finished with the AGM iteration for log(x).
      // Compute log(x) = {pi / [2 * AGM(1, 4 / 2^m)]} - (m * ln2)
      // Note at this time that (ak = bk) = AGM(...)
      // Retrieve the value of pi, divide by (2 * a) and subtract (m * ln2).

      result.calculate_inv();
      result *= pi<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>();
      result -= (ln_two<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>() * m);
    }
    else
    {
      result = zero<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>();
    }

    return result;
  }

  template<const std::int32_t ParamDigitsBaseTen, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType>
  auto log(const decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>& x) -> typename std::enable_if<(ParamDigitsBaseTen <= static_cast<std::int32_t>(INT8_C(51))), decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>>::type // NOLINT(misc-no-recursion)
  {
    using floating_point_type = decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>;

    floating_point_type result { };

    if(x < one<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>())
    {
      result = -log(floating_point_type(x).calculate_inv());
    }
    else if(x > one<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>())
    {
      // Reduce the argument to x_scaled = 10^n * x.
      // This results in:
      //   log10(x) = n * log(10) + log10(x).

      // Subsequently define y = x_scaled - 1 and use
      // the Taylor series for log(y) evalueated at 1.

      using local_exponent_type = typename floating_point_type::exponent_type;
      using local_limb_type     = typename floating_point_type::limb_type;

      using std::ilogb;

      auto n = ilogb(x);

      // Create a wide decimal scale_factor which is intended to scale
      // the input argument to a value in the approximate range 1 ... 10.

      floating_point_type scale_factor =
        floating_point_type::from_lst
        (
          {
            static_cast<local_limb_type>
            (
              detail::pow10_maker_as_runtime_value(static_cast<std::uint32_t>(n % static_cast<local_exponent_type>(floating_point_type::decwide_t_elem_digits10)))
            )
          },
          static_cast<local_exponent_type>
          (
            (n / static_cast<local_exponent_type>(floating_point_type::decwide_t_elem_digits10)) * static_cast<local_exponent_type>(floating_point_type::decwide_t_elem_digits10)
          )
        );

      auto x_scaled = x / scale_factor;

      if(x_scaled > static_cast<floating_point_type>(1.8F)) // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
      {
        // Scale the argument by an additional factor of ten if
        // it exceeds an empirical limit designed to optimize
        // (i.e., minimize) the number of iterations required
        // in the Taylor series of the logarithm below.

        x_scaled /= static_cast<local_limb_type>(UINT8_C(10));

        ++n;
      }

      const auto digits10_series_goal =
        static_cast<local_exponent_type>
        (
            static_cast<local_exponent_type>(std::numeric_limits<floating_point_type>::digits10)
          + static_cast<local_exponent_type>(5)
        );

      const auto y =
        (
            x_scaled
          - one<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>()
        );

      auto y_pow_n       = y;
      auto sum           = y_pow_n;
      auto negative_term = true;

      for(auto   i = static_cast<std::uint32_t>(UINT32_C(2));
                 i < static_cast<std::uint32_t>(UINT32_C(10000));
               ++i)
      {
        y_pow_n *= y;

        const auto term = y_pow_n / i;

        if(i > static_cast<std::uint32_t>(UINT8_C(4)))
        {
          const auto digits10_of_series =
            (std::max)(static_cast<std::int32_t>(0),
                       static_cast<std::int32_t>(-ilogb(y_pow_n)));

          if(y_pow_n.iszero() || (digits10_of_series > digits10_series_goal))
          {
            break;
          }
        }

        (negative_term ? sum -= term : sum += term);

        negative_term = (!negative_term);
      }

      result =
        (
            calc_ln_ten_low_precision<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>()
          * n
        )
        + sum;
    }
    else
    {
      result = zero<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>();
    }

    return result;
  }

  template<const std::int32_t ParamDigitsBaseTen, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType>
  auto exp(const decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>& x) -> typename std::enable_if<(ParamDigitsBaseTen > static_cast<std::int32_t>(INT32_C(2000))), decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>>::type
  {
    using floating_point_type =
      decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>;

    floating_point_type exp_result;

    if(x.isneg())
    {
      exp_result = exp(floating_point_type(x).negate()).calculate_inv();
    }
    else if(!x.iszero())
    {
      if(x < one<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>())
      {
        if(x < half<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>())
        {
          exp_result =
            exp
            (
                x
              + (ln_two<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>() * 2U)
            )
            / 4U;
        }
        else
        {
          exp_result =
            exp
            (
                x
              + ln_two<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>()
            )
            / 2U;
        }
      }
      else
      {
        const auto precision_of_x = floating_point_type::get_precision(x);

        // Setup the iteration.

        // Use the original value of x for iteration below.
        floating_point_type original_x(x);

        floating_point_type iterate_term;

        using std::exp;

        // Estimate the exponent using built-in <cmath>-functions.
        const auto x_as_built_in_float = static_cast<InternalFloatType>(original_x);
        const auto exp_estimate        = exp(x_as_built_in_float);

        exp_result = exp_estimate;

        for(auto digits  = static_cast<std::int32_t>(std::numeric_limits<InternalFloatType>::digits10 - 1);
                 digits  < precision_of_x;
                 digits *= static_cast<std::int32_t>(INT8_C(2)))
        {
          // Adjust precision of the terms.
          const auto min_elem_digits10_plus_one =
            (std::min)
            (
              static_cast<std::int32_t>(floating_point_type::decwide_t_elem_digits10 + 1),
              static_cast<std::int32_t>(INT8_C(9))
            );

          const auto new_prec_as_digits10 =
            static_cast<std::int32_t>
            (
                static_cast<std::int32_t>(digits * static_cast<std::int8_t>(INT8_C(2)))
              + min_elem_digits10_plus_one
            );

            exp_result.precision(new_prec_as_digits10);
          iterate_term.precision(new_prec_as_digits10);
            original_x.precision(new_prec_as_digits10);

          iterate_term  = log(exp_result);
          iterate_term.negate();
          iterate_term += original_x;

          iterate_term += one<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>();
          exp_result   *= iterate_term;
        }

        exp_result.precision(precision_of_x);
      }
    }
    else
    {
      exp_result = one<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>();
    }

    return exp_result;
  }

  template<const std::int32_t ParamDigitsBaseTen, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType>
  auto exp(const decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>& x) -> typename std::enable_if<(ParamDigitsBaseTen <= static_cast<std::int32_t>(INT32_C(2000))), decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>>::type
  {
    using floating_point_type = decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>;

    const auto b_neg = x.isneg();

    floating_point_type exp_result;

    if(b_neg || (x > 0))
    {
      const floating_point_type xx = ((!b_neg) ? x : -x);

      // The algorithm for exp has been taken from MPFUN.
      // exp(t) = [ (1 + r + r^2/2! + r^3/3! + r^4/4! ...)^p2 ] * 2^n
      // where p2 is a power of 2 such as 2048, r = t_prime / p2, and
      // t_prime = t - n*ln2, with n chosen to minimize the absolute
      // value of t_prime. In the resulting Taylor series, which is
      // implemented as a hypergeometric function, |r| is bounded by
      // ln2 / p2.

      // Get (compute beforehad) ln2 as a constant or constant reference value.
      #if !defined(WIDE_DECIMAL_DISABLE_CACHED_CONSTANTS)
      const floating_point_type& ln2 = ln_two<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>();
      #else
      const floating_point_type  ln2 = ln_two<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>();
      #endif

      const auto nf = static_cast<std::uint32_t>(xx / ln2);

      // Compute the exponential series of the scaled argument.
      // The scaling is 2^11 = 2048.
      const auto p2 = static_cast<std::uint32_t>(UINTMAX_C(1) << 11U);

      // Compute the series representation of Hypergeometric0F0 taken from
      // http://functions.wolfram.com/HypergeometricFunctions/Hypergeometric0F0/06/01/
      // There are no checks on input range or parameter boundaries.

      const auto precision_of_x = floating_point_type::get_precision(x);

      floating_point_type xh((xx - floating_point_type(nf * ln2)) / p2);

      xh.precision(precision_of_x);

      floating_point_type x_pow_n_div_n_fact(xh);

      floating_point_type
        h0f0
        (
            one<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>()
          + x_pow_n_div_n_fact
        );

      h0f0.precision(precision_of_x);

      using local_exponent_type = typename floating_point_type::exponent_type;

      using std::ilogb;

      const auto iteration_goal_ilobg =
        (std::max)(static_cast<local_exponent_type>(0),
                   static_cast<local_exponent_type>(-ilogb(std::numeric_limits<floating_point_type>::epsilon())));

      const auto iteration_goal_prec = static_cast<local_exponent_type>(precision_of_x);

      const auto digits10_iteration_goal =
        static_cast<local_exponent_type>
        (
          (std::min)(iteration_goal_ilobg, iteration_goal_prec)
        );

      // Series expansion of hypergeometric_0f0(; ; x).
      for(auto   n = static_cast<std::uint32_t>(UINT32_C(2));
                 n < static_cast<std::uint32_t>(UINT32_C(100000));
               ++n)
      {
        x_pow_n_div_n_fact *= xh;
        x_pow_n_div_n_fact /= n;

        if(n > static_cast<std::uint32_t>(UINT32_C(4)))
        {
          // Use a tolerance check with iblog (via its digits10-scale).
          // But only do this following the first few iterations.

          const auto iteration_result_so_far =
            (std::max)(static_cast<local_exponent_type>(0),
                       static_cast<local_exponent_type>(-ilogb(x_pow_n_div_n_fact)));

          if(iteration_result_so_far > digits10_iteration_goal)
          {
            break;
          }
        }

        h0f0 += x_pow_n_div_n_fact;
      }

      using std::pow;

      exp_result = pow(h0f0, p2);

      if(nf != static_cast<std::uint32_t>(UINT8_C(0)))
      {
        using std::ldexp;

        exp_result = ldexp(exp_result, static_cast<int>(nf));
      }

      if(b_neg)
      {
        static_cast<void>(exp_result.calculate_inv());
      }
    }
    else
    {
      exp_result = one<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>();
    }

    return exp_result;
  }

  template<const std::int32_t ParamDigitsBaseTen, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType>
  auto sinh(const decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>& x) -> decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>
  {
    using floating_point_type =
      decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>;

    const floating_point_type ep = exp(x);

    return (ep - floating_point_type(ep).calculate_inv()) / 2U;
  }

  template<const std::int32_t ParamDigitsBaseTen, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType>
  auto cosh(const decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>& x) -> decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>
  {
    using floating_point_type =
      decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>;

    const floating_point_type ep = exp(x);

    return (ep + floating_point_type(ep).calculate_inv()) / 2U;
  }

  template<const std::int32_t ParamDigitsBaseTen, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType>
  auto tanh(const decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>& x) -> decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>
  {
    using floating_point_type =
      decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>;

    const floating_point_type ep = exp(x);
    const floating_point_type em(floating_point_type(ep).calculate_inv());

    return (ep - em) / (ep + em);
  }

  template<const std::int32_t ParamDigitsBaseTen, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType>
  auto pow(const decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>& b, std::int64_t p) -> decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType> // NOLINT(misc-no-recursion)
  {
    // Calculate (b ^ p).

    using floating_point_type = decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>;

    floating_point_type result;

    if     (p <  static_cast<std::int64_t>(INT8_C(0))) { result = pow(b, -p).calculate_inv(); }
    else if(p == static_cast<std::int64_t>(INT8_C(0))) { result = floating_point_type(1U); }
    else if(p == static_cast<std::int64_t>(INT8_C(1))) { result = b; }
    else if(p == static_cast<std::int64_t>(INT8_C(2))) { result = b; result *= b; }
    else if(p == static_cast<std::int64_t>(INT8_C(3))) { result = b; result *= b; result *= b; }
    else if(p == static_cast<std::int64_t>(INT8_C(4))) { result = b; result *= b; result *= result; }
    else
    {
      result = floating_point_type(1U);

      floating_point_type y(b);

      auto p_local = static_cast<std::uint64_t>(p);

      // Use the so-called ladder method for the power calculation.
      for(;;)
      {
        const auto do_power_multiply =
          (static_cast<std::uint_fast8_t>(p_local & 1U) != static_cast<std::uint_fast8_t>(0U));

        if(do_power_multiply)
        {
          result *= y;
        }

        p_local >>= 1U;

        if(p_local == static_cast<std::uint64_t>(UINT8_C(0)))
        {
          break;
        }

        y *= y;
      }
    }

    return result;
  }

  #if(__cplusplus >= 201703L)
  } // namespace math::wide_decimal
  #else
  } // namespace wide_decimal
  } // namespace math
  #endif

  WIDE_DECIMAL_NAMESPACE_END

#endif // DECWIDE_T_2004_06_01_H
