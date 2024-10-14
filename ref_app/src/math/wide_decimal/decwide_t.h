///////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 1999 - 2024.                 //
//  Distributed under the Boost Software License,                //
//  Version 1.0. (See accompanying file LICENSE_1_0.txt          //
//  or copy at http://www.boost.org/LICENSE_1_0.txt)             //
///////////////////////////////////////////////////////////////////

// This work is also based on an earlier work:
// "Algorithm 910: A Portable C++ Multiple-Precision System for Special-Function Calculations",
// in ACM TOMS, {VOL 37, ISSUE 4, (February 2011)} (C) ACM, 2011. http://doi.acm.org/10.1145/1916461.1916469

// This file implements the class decwide_t and most of its
// basic functions including constructors, binary arithmetic
// operations, comparison operators, selected elementary
// functions and more.

#ifndef DECWIDE_T_2004_06_01_H // NOLINT(llvm-header-guard)
  #define DECWIDE_T_2004_06_01_H

  //#define WIDE_DECIMAL_DISABLE_IOSTREAM
  //#define WIDE_DECIMAL_DISABLE_DYNAMIC_MEMORY_ALLOCATION
  //#define WIDE_DECIMAL_DISABLE_CONSTRUCT_FROM_STRING
  //#define WIDE_DECIMAL_DISABLE_CACHED_CONSTANTS
  //#define WIDE_DECIMAL_DISABLE_USE_STD_FUNCTION
  //#define WIDE_DECIMAL_NAMESPACE=something_unique // (best if done on the command line)

  #include <cmath>
  #include <cstddef>
  #include <cstdlib>
  #include <cstring>
  #if !defined(WIDE_DECIMAL_DISABLE_USE_STD_FUNCTION)
  #include <functional>
  #endif
  #include <limits>
  #if !defined(WIDE_DECIMAL_DISABLE_IOSTREAM)
  #include <iomanip>
  #include <ios>
  #include <iostream>
  #endif
  #if (!defined(WIDE_DECIMAL_DISABLE_CONSTRUCT_FROM_STRING) && !defined(WIDE_DECIMAL_DISABLE_IOSTREAM))
  #include <string>
  #endif

  #include <math/wide_decimal/decwide_t_detail_ops.h>

  #include <util/utility/util_baselexical_cast.h>

  #if !defined(WIDE_DECIMAL_NAMESPACE_BEGIN)
  #error WIDE_DECIMAL_NAMESPACE_BEGIN is not defined. Ensure that <decwide_t_detail_namespace.h> is properly included.
  #endif

  #if !defined(WIDE_DECIMAL_NAMESPACE_END)
  #error WIDE_DECIMAL_NAMESPACE_END is not defined. Ensure that <decwide_t_detail_namespace.h> is properly included.
  #endif

  #if (defined(__GNUC__) && (defined(__RL78__) || defined(__riscv)))
  namespace std { using ::ilogb; }
  #endif

  #if (defined(__GNUC__) && defined(__riscv))
  namespace std { using ::lround; }
  #endif

  WIDE_DECIMAL_NAMESPACE_BEGIN

  #if(__cplusplus >= 201703L)
  namespace math::wide_decimal {
  #else
  namespace math { namespace wide_decimal { // NOLINT(modernize-concat-nested-namespaces)
  #endif

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
           typename LimbType          = std::uint32_t,
           typename AllocatorType     = std::allocator<void>,
           typename InternalFloatType = double,
           typename ExponentType      = std::int64_t,
           typename FftFloatType      = double>
  #if !defined(WIDE_DECIMAL_DISABLE_USE_STD_FUNCTION)
  auto pi(const std::function<void(const std::uint32_t)>& pfn_callback_to_report_digits10 = nullptr) -> const decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>&;
  #else
  auto pi(void(*pfn_callback_to_report_digits10)(const std::uint32_t) = nullptr) -> const decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>&;
  #endif
  #else
  template<const std::int32_t ParamDigitsBaseTen,
           typename LimbType          = std::uint32_t,
           typename AllocatorType     = std::allocator<void>,
           typename InternalFloatType = double,
           typename ExponentType      = std::int64_t,
           typename FftFloatType      = double>
  #if !defined(WIDE_DECIMAL_DISABLE_USE_STD_FUNCTION)
  auto pi(const std::function<void(const std::uint32_t)>& pfn_callback_to_report_digits10 = nullptr) -> decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>;
  #else
  auto pi(void(*pfn_callback_to_report_digits10)(const std::uint32_t) = nullptr) -> decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>;
  #endif
  #endif

  #if !defined(WIDE_DECIMAL_DISABLE_CACHED_CONSTANTS)
  template<const std::int32_t ParamDigitsBaseTen,
           typename LimbType          = std::uint32_t,
           typename AllocatorType     = std::allocator<void>,
           typename InternalFloatType = double,
           typename ExponentType      = std::int64_t,
           typename FftFloatType      = double>
  auto ln_two() -> const decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>&;
  #else
  template<const std::int32_t ParamDigitsBaseTen,
           typename LimbType          = std::uint32_t,
           typename AllocatorType     = std::allocator<void>,
           typename InternalFloatType = double,
           typename ExponentType      = std::int64_t,
           typename FftFloatType      = double>
  auto ln_two() -> decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>;
  #endif

  template<const std::int32_t ParamDigitsBaseTen,
           typename LimbType          = std::uint32_t,
           typename AllocatorType     = std::allocator<void>,
           typename InternalFloatType = double,
           typename ExponentType      = std::int64_t,
           typename FftFloatType      = double>
  #if !defined(WIDE_DECIMAL_DISABLE_USE_STD_FUNCTION)
  auto calc_pi(const std::function<void(const std::uint32_t)>& pfn_callback_to_report_digits10 = nullptr) -> typename std::enable_if<(ParamDigitsBaseTen > static_cast<std::int32_t>(INT8_C(51))), decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>>::type;
  #else
  auto calc_pi(void(*pfn_callback_to_report_digits10)(const std::uint32_t) = nullptr) -> typename std::enable_if<(ParamDigitsBaseTen > static_cast<std::int32_t>(INT8_C(51))), decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>>::type;
  #endif

  template<const std::int32_t ParamDigitsBaseTen,
           typename LimbType          = std::uint32_t,
           typename AllocatorType     = std::allocator<void>,
           typename InternalFloatType = double,
           typename ExponentType      = std::int64_t,
           typename FftFloatType      = double>
  #if !defined(WIDE_DECIMAL_DISABLE_USE_STD_FUNCTION)
  auto calc_pi(const std::function<void(const std::uint32_t)>& pfn_callback_to_report_digits10 = nullptr) -> typename std::enable_if<((ParamDigitsBaseTen <= static_cast<std::int32_t>(INT8_C(51))) && std::is_same<LimbType, std::uint8_t>::value), decwide_t<ParamDigitsBaseTen, std::uint8_t, AllocatorType, InternalFloatType, ExponentType, FftFloatType>>::type;
  #else
  auto calc_pi(void(*pfn_callback_to_report_digits10)(const std::uint32_t) = nullptr) -> typename std::enable_if<((ParamDigitsBaseTen <= static_cast<std::int32_t>(INT8_C(51))) && std::is_same<LimbType, std::uint8_t>::value), decwide_t<ParamDigitsBaseTen, std::uint8_t, AllocatorType, InternalFloatType, ExponentType, FftFloatType>>::type;
  #endif

  template<const std::int32_t ParamDigitsBaseTen,
           typename LimbType          = std::uint32_t,
           typename AllocatorType     = std::allocator<void>,
           typename InternalFloatType = double,
           typename ExponentType      = std::int64_t,
           typename FftFloatType      = double>
  #if !defined(WIDE_DECIMAL_DISABLE_USE_STD_FUNCTION)
  auto calc_pi(const std::function<void(const std::uint32_t)>& pfn_callback_to_report_digits10 = nullptr) -> typename std::enable_if<((ParamDigitsBaseTen <= static_cast<std::int32_t>(INT8_C(51))) && std::is_same<LimbType, std::uint16_t>::value), decwide_t<ParamDigitsBaseTen, std::uint16_t, AllocatorType, InternalFloatType, ExponentType, FftFloatType>>::type;
  #else
  auto calc_pi(void(*pfn_callback_to_report_digits10)(const std::uint32_t) = nullptr) -> typename std::enable_if<((ParamDigitsBaseTen <= static_cast<std::int32_t>(INT8_C(51))) && std::is_same<LimbType, std::uint16_t>::value), decwide_t<ParamDigitsBaseTen, std::uint16_t, AllocatorType, InternalFloatType, ExponentType, FftFloatType>>::type;
  #endif

  template<const std::int32_t ParamDigitsBaseTen,
           typename LimbType          = std::uint32_t,
           typename AllocatorType     = std::allocator<void>,
           typename InternalFloatType = double,
           typename ExponentType      = std::int64_t,
           typename FftFloatType      = double>
  #if !defined(WIDE_DECIMAL_DISABLE_USE_STD_FUNCTION)
  auto calc_pi(const std::function<void(const std::uint32_t)>& pfn_callback_to_report_digits10 = nullptr) -> typename std::enable_if<((ParamDigitsBaseTen <= static_cast<std::int32_t>(INT8_C(51))) && std::is_same<LimbType, std::uint32_t>::value), decwide_t<ParamDigitsBaseTen, std::uint32_t, AllocatorType, InternalFloatType, ExponentType, FftFloatType>>::type;
  #else
  auto calc_pi(void(*pfn_callback_to_report_digits10)(const std::uint32_t) = nullptr) -> typename std::enable_if<((ParamDigitsBaseTen <= static_cast<std::int32_t>(INT8_C(51))) && std::is_same<LimbType, std::uint32_t>::value), decwide_t<ParamDigitsBaseTen, std::uint16_t, AllocatorType, InternalFloatType, ExponentType, FftFloatType>>::type;
  #endif

  template<const std::int32_t ParamDigitsBaseTen,
           typename LimbType          = std::uint32_t,
           typename AllocatorType     = std::allocator<void>,
           typename InternalFloatType = double,
           typename ExponentType      = std::int64_t,
           typename FftFloatType      = double>
  auto calc_ln_two() -> typename std::enable_if<(ParamDigitsBaseTen > static_cast<std::int32_t>(INT8_C(51))), decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>>::type;

  template<const std::int32_t ParamDigitsBaseTen,
           typename LimbType          = std::uint32_t,
           typename AllocatorType     = std::allocator<void>,
           typename InternalFloatType = double,
           typename ExponentType      = std::int64_t,
           typename FftFloatType      = double>
  auto calc_ln_two() -> typename std::enable_if<((ParamDigitsBaseTen <= static_cast<std::int32_t>(INT8_C(51))) && std::is_same<LimbType, std::uint8_t>::value), decwide_t<ParamDigitsBaseTen, std::uint8_t, AllocatorType, InternalFloatType, ExponentType, FftFloatType>>::type;

  template<const std::int32_t ParamDigitsBaseTen,
           typename LimbType          = std::uint32_t,
           typename AllocatorType     = std::allocator<void>,
           typename InternalFloatType = double,
           typename ExponentType      = std::int64_t,
           typename FftFloatType      = double>
  auto calc_ln_two() -> typename std::enable_if<((ParamDigitsBaseTen <= static_cast<std::int32_t>(INT8_C(51))) && std::is_same<LimbType, std::uint16_t>::value), decwide_t<ParamDigitsBaseTen, std::uint16_t, AllocatorType, InternalFloatType, ExponentType, FftFloatType>>::type;

  template<const std::int32_t ParamDigitsBaseTen,
           typename LimbType          = std::uint32_t,
           typename AllocatorType     = std::allocator<void>,
           typename InternalFloatType = double,
           typename ExponentType      = std::int64_t,
           typename FftFloatType      = double>
  auto calc_ln_two() -> typename std::enable_if<((ParamDigitsBaseTen <= static_cast<std::int32_t>(INT8_C(51))) && std::is_same<LimbType, std::uint32_t>::value), decwide_t<ParamDigitsBaseTen, std::uint32_t, AllocatorType, InternalFloatType, ExponentType, FftFloatType>>::type;

  template<const std::int32_t ParamDigitsBaseTen,
           typename LimbType          = std::uint32_t,
           typename AllocatorType     = std::allocator<void>,
           typename InternalFloatType = double,
           typename ExponentType      = std::int64_t,
           typename FftFloatType      = double>
  auto calc_ln_ten_low_precision() -> typename std::enable_if<((ParamDigitsBaseTen <= static_cast<std::int32_t>(INT8_C(51))) && std::is_same<LimbType, std::uint8_t>::value), decwide_t<ParamDigitsBaseTen, std::uint8_t, AllocatorType, InternalFloatType, ExponentType, FftFloatType>>::type;

  template<const std::int32_t ParamDigitsBaseTen,
           typename LimbType          = std::uint32_t,
           typename AllocatorType     = std::allocator<void>,
           typename InternalFloatType = double,
           typename ExponentType      = std::int64_t,
           typename FftFloatType      = double>
  auto calc_ln_ten_low_precision() -> typename std::enable_if<((ParamDigitsBaseTen <= static_cast<std::int32_t>(INT8_C(51))) && std::is_same<LimbType, std::uint16_t>::value), decwide_t<ParamDigitsBaseTen, std::uint16_t, AllocatorType, InternalFloatType, ExponentType, FftFloatType>>::type;

  template<const std::int32_t ParamDigitsBaseTen,
           typename LimbType          = std::uint32_t,
           typename AllocatorType     = std::allocator<void>,
           typename InternalFloatType = double,
           typename ExponentType      = std::int64_t,
           typename FftFloatType      = double>
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
    using limb_type           = LimbType;
    using exponent_type       = ExponentType;
    using fft_float_type      = FftFloatType;
    using internal_float_type = InternalFloatType;

    // Check the limb type.
    static_assert((   std::is_same<std::uint8_t,  limb_type>::value
                   || std::is_same<std::uint16_t, limb_type>::value
                   || std::is_same<std::uint32_t, limb_type>::value),
                   "Error: limb_type (template parameter LimbType) "
                   "must be one of uint8_t, uint16_t or uint32_t.");

    // Check the exponent type.
    static_assert((   std::is_same<std::int8_t,  exponent_type>::value
                   || std::is_same<std::int16_t, exponent_type>::value
                   || std::is_same<std::int32_t, exponent_type>::value
                   || std::is_same<std::int64_t, exponent_type>::value),
                   "Error: exponent_type (template parameter ExponentType) "
                   "must be one of int8_t, int16_t, int32_t or int64_t.");

    // Define the decwide_t digits characteristics.
    static constexpr std::int32_t  decwide_t_digits10       = detail::decwide_t_helper<ParamDigitsBaseTen, LimbType>::digits10;
    static constexpr std::int32_t  decwide_t_digits         = detail::decwide_t_helper<ParamDigitsBaseTen, LimbType>::digits;
    static constexpr std::int32_t  decwide_t_max_digits10   = detail::decwide_t_helper<ParamDigitsBaseTen, LimbType>::max_digits10;
    static constexpr std::int32_t  decwide_t_radix          = detail::decwide_t_helper<ParamDigitsBaseTen, LimbType>::radix;
    static constexpr std::int32_t  decwide_t_elem_digits10  = detail::decwide_t_helper<ParamDigitsBaseTen, LimbType>::elem_digits10;
    static constexpr std::int32_t  decwide_t_elem_number    = detail::decwide_t_helper<ParamDigitsBaseTen, LimbType>::elem_number;
    static constexpr std::int32_t  decwide_t_elem_mask      = detail::decwide_t_helper<ParamDigitsBaseTen, LimbType>::elem_mask;
    static constexpr std::int32_t  decwide_t_elem_mask_half = detail::decwide_t_helper<ParamDigitsBaseTen, LimbType>::elem_mask_half;
    static constexpr std::int32_t  decwide_t_elem_mask_min1 = static_cast<std::int32_t>(decwide_t_elem_mask - static_cast<std::int32_t>(INT8_C(1)));
    static constexpr std::int32_t  decwide_t_elems_for_kara = static_cast<std::int32_t>(INT32_C( 112) + INT32_C(1));
    static constexpr std::int32_t  decwide_t_elems_for_fft  = static_cast<std::int32_t>(INT32_C(1792) + INT32_C(1));

    static constexpr exponent_type decwide_t_max_exp10      =  static_cast<exponent_type>(UINTMAX_C(1) << static_cast<unsigned>(std::numeric_limits<exponent_type>::digits - (std::is_same<exponent_type, std::int64_t>::value ? 4 : (std::is_same<exponent_type, std::int32_t>::value ? 3 : (std::is_same<exponent_type, std::int16_t>::value ? 2 : 1)))));
    static constexpr exponent_type decwide_t_min_exp10      = -static_cast<exponent_type>(decwide_t_max_exp10);
    static constexpr exponent_type decwide_t_max_exp        = decwide_t_max_exp10;
    static constexpr exponent_type decwide_t_min_exp        = decwide_t_min_exp10;

  private:
    #if (defined(_MSC_VER) && (_MSC_VER < 1920))
    #else
    static constexpr auto is_void_allocator() noexcept -> bool { return std::is_same<AllocatorType, void>::value; }
    #endif

    // Rebind the decwide_t allocator to the granularity of the LimbType.
    using allocator_conditional_type =
      #if (defined(_MSC_VER) && (_MSC_VER < 1920))
      typename std::conditional<std::is_same<AllocatorType, void>::value,
      #else
      typename std::conditional<is_void_allocator(),
      #endif
                                std::allocator<void>,
                                AllocatorType>::type;

  public:
    using allocator_type =
      typename std::allocator_traits<allocator_conditional_type>::template rebind_alloc<limb_type>;

    // Define the internal representation type of the data field
    // of a decwide_t. This can be either a statically or dynamically
    // allocated fixed-size array-like container depending on the
    // nature of the allocator type being used.

    using representation_type =
      #if (defined(_MSC_VER) && (_MSC_VER < 1920))
      typename std::conditional<std::is_same<AllocatorType, void>::value,
      #else
      typename std::conditional<is_void_allocator(),
      #endif
                                detail::fixed_static_array <limb_type, static_cast<std::size_t>(decwide_t_elem_number)>,
                                detail::fixed_dynamic_array<limb_type, static_cast<std::size_t>(decwide_t_elem_number), allocator_type>>::type;

    using double_limb_type =
      typename std::conditional<std::is_same<limb_type, std::uint32_t>::value,
                                std::uint64_t,
                                typename std::conditional<std::is_same<limb_type, std::uint16_t>::value,
                                                          std::uint32_t,
                                                          std::uint16_t>::type>::type;

    using signed_limb_type = typename std::make_signed<limb_type>::type;

    using unsigned_exponent_type = typename std::make_unsigned<exponent_type>::type;

    // TBD: Consider supporting more floating-point classes.
    // In particular, support for NaN is already being
    // partially used through the specialization of limits.
    // When starting, maybe begin with FP-class NaN.
    enum class fpclass_type // NOLINT(performance-enum-size)
    {
      decwide_t_finite
    };

  private:
    #if !defined(WIDE_DECIMAL_DISABLE_CACHED_CONSTANTS)
    // LCOV_EXCL_START
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

      auto operator=(const initializer&) noexcept -> initializer& = delete;
      auto operator=(initializer&&) noexcept -> initializer& = delete;

      ~initializer() noexcept = default;

      auto do_nothing() const noexcept -> void
      {
        // Do nothing on purpose.
      }
    };

    static const initializer my_initializer;
    // LCOV_EXCL_STOP
    #endif

    #if !defined(WIDE_DECIMAL_DISABLE_IOSTREAM)
    static auto wr_string(const decwide_t&         x,
                                std::string&       str, // NOLINT(google-runtime-references)
                                std::ios::fmtflags ostrm_flags,
                                std::streamsize    ostrm_precision,
                                std::streamsize    ostrm_width,
                                char               ostrm_fill = ' ') -> void; // NOLINT(readability-function-cognitive-complexity,google-runtime-references)
    #endif

  public:
    // Default constructor.
    constexpr decwide_t() noexcept
      : my_data     (),
        my_exp      (static_cast<exponent_type>(INT8_C(0))),
        my_neg      (false),
        my_fpclass  (fpclass_type::decwide_t_finite),
        my_prec_elem(decwide_t_elem_number) { }

    // Constructors from built-in unsigned integral types.
    template<typename UnsignedIntegralType,
             typename std::enable_if<(    std::is_integral<UnsignedIntegralType>::value
                                      &&  std::is_unsigned<UnsignedIntegralType>::value
                                      && (std::numeric_limits<UnsignedIntegralType>::digits <= std::numeric_limits<limb_type>::digits))>::type const* = nullptr>
    constexpr decwide_t(const UnsignedIntegralType u) // NOLINT(google-explicit-constructor,hicpp-explicit-conversions)
      : my_data     (decwide_t_elem_number),
        my_exp      (static_cast<exponent_type>(INT8_C(0))),
        my_neg      (false),
        my_fpclass  (fpclass_type::decwide_t_finite),
        my_prec_elem(decwide_t_elem_number)
    {
      const auto u_is_less_than_mask =
        (static_cast<limb_type>(u) < static_cast<limb_type>(decwide_t_elem_mask));

      using local_size_type = typename representation_type::size_type;

      if(u_is_less_than_mask)
      {
        my_data[static_cast<local_size_type>(UINT8_C(0))] = static_cast<limb_type>(u);
      }
      else
      {
        my_data[static_cast<local_size_type>(UINT8_C(0))] = static_cast<limb_type>(u / static_cast<limb_type>(decwide_t_elem_mask));
        my_data[static_cast<local_size_type>(UINT8_C(1))] = static_cast<limb_type>(u % static_cast<limb_type>(decwide_t_elem_mask));

        my_exp = static_cast<exponent_type>(decwide_t_elem_digits10);
      }
    }

    // Constructors from built-in unsigned integral types.
    template<typename UnsignedIntegralType,
             typename std::enable_if<(    std::is_integral<UnsignedIntegralType>::value
                                      &&  std::is_unsigned<UnsignedIntegralType>::value
                                      && (std::numeric_limits<limb_type>::digits < std::numeric_limits<UnsignedIntegralType>::digits))>::type const* = nullptr>
    decwide_t(const UnsignedIntegralType u) : my_data     (), // NOLINT(google-explicit-constructor,hicpp-explicit-conversions)
                                              my_exp      (static_cast<exponent_type>(INT8_C(0))),
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
                                            my_exp      (static_cast<exponent_type>(INT8_C(0))),
                                            my_neg      (n < static_cast<signed long long>(INT8_C(0))), // NOLINT(google-runtime-int)
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
             typename std::enable_if<std::is_floating_point<FloatingPointType>::value>::type const* = nullptr>
    decwide_t(const FloatingPointType f) : my_data     (), // NOLINT(google-explicit-constructor,hicpp-explicit-conversions)
                                           my_exp      (static_cast<exponent_type>(INT8_C(0))),
                                           my_neg      (false),
                                           my_fpclass  (fpclass_type::decwide_t_finite),
                                           my_prec_elem(decwide_t_elem_number)
    {
      from_builtin_float_type(f);
    }

    #if !defined(WIDE_DECIMAL_DISABLE_CONSTRUCT_FROM_STRING)
    // Constructors from character representations.
    explicit decwide_t(const char* s) : my_data     (),
                                        my_exp      (static_cast<exponent_type>(INT8_C(0))),
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
        my_exp      (static_cast<exponent_type>(INT8_C(0))),
        my_neg      (false),
        my_fpclass  (fpclass_type::decwide_t_finite),
        my_prec_elem(decwide_t_elem_number) { }

  private:
    // Constructor from mantissa and exponent.
    explicit decwide_t(const internal_float_type mantissa,
                       const exponent_type       exponent)
      : my_data     (),
        my_exp      (static_cast<exponent_type>(INT8_C(0))),
        my_neg      (false),
        my_fpclass  (fpclass_type::decwide_t_finite),
        my_prec_elem(decwide_t_elem_number)
    {
      // Create a decwide_t from mantissa and exponent.
      // This constructor is, in fact, intended to maintain
      // the full precision of the internal_float_type.

      constexpr auto delta_zero =
        static_cast<internal_float_type>
        (
          (
              (std::numeric_limits<internal_float_type>::min)()
            * static_cast<internal_float_type>
              (
                  static_cast<internal_float_type>(static_cast<unsigned>(UINT8_C(1)))
                + std::numeric_limits<internal_float_type>::epsilon()
              )
          )
        );

      using std::fabs;

      const auto mantissa_is_iszero = (fabs(mantissa) < delta_zero);

      if(mantissa_is_iszero)
      {
        my_data.fill(static_cast<limb_type>(UINT8_C(0))); // LCOV_EXCL_LINE
      }
      else
      {
        const auto b_neg = (mantissa < static_cast<InternalFloatType>(0));

        internal_float_type d = ((!b_neg) ? mantissa : -mantissa);
        exponent_type       e = exponent;

        {
          // Scale the input mantissa to lie between 1 and 10.

          constexpr auto f_ten = static_cast<internal_float_type>(static_cast<std::uint_fast8_t>(UINT8_C(10)));
          constexpr auto f_one = static_cast<internal_float_type>(static_cast<std::uint_fast8_t>(UINT8_C(1)));

          while(d > f_ten) { d /= f_ten; ++e; } // NOLINT(altera-id-dependent-backward-branch)
          while(d < f_one) { d *= f_ten; --e; } // NOLINT(altera-id-dependent-backward-branch)

          auto shift = static_cast<std::int32_t>(e % static_cast<std::int32_t>(decwide_t_elem_digits10));

          while(static_cast<std::int32_t>(shift % decwide_t_elem_digits10) != static_cast<std::int32_t>(INT8_C(0))) // NOLINT(altera-id-dependent-backward-branch)
          {
            d *= f_ten;
            --e;
            --shift;
          }
        }

        my_exp = e;
        my_neg = b_neg;

        constexpr auto digit_elem_whole =
          static_cast<int>
          (
              std::numeric_limits<internal_float_type>::max_digits10
            / static_cast<int>(decwide_t_elem_digits10)
          );

        constexpr auto digit_elem_mod =
          static_cast<int>
          (
              std::numeric_limits<internal_float_type>::max_digits10
            % static_cast<int>(decwide_t_elem_digits10)
          );

        constexpr auto digit_loops = // NOLINT(altera-id-dependent-backward-branch)
          static_cast<int>
          (
              digit_elem_whole
            + static_cast<int>
              (
                (digit_elem_mod != static_cast<int>(INT8_C(0)))
                  ? static_cast<int>(INT8_C(1))
                  : static_cast<int>(INT8_C(0))
              )
          );

        using local_size_type = typename representation_type::size_type;

        local_size_type limb_index;

        // Extract the mantissa's decimal digits.

        for(  limb_index = static_cast<local_size_type>(UINT8_C(0));
              limb_index < static_cast<local_size_type>(digit_loops); // NOLINT(altera-id-dependent-backward-branch)
            ++limb_index)
        {
          const auto n = static_cast<limb_type>(d);

          my_data[limb_index] = n;

          d -= static_cast<internal_float_type>(n);
          d *= static_cast<internal_float_type>(decwide_t_elem_mask);
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

      const local_unsigned_exponent_wrap_type u_exp(  my_exp);
      const local_unsigned_exponent_wrap_type v_exp(v.my_exp);

      const local_unsigned_exponent_wrap_type ofs_exp = (u_exp - v_exp);

      // Check if the operation is out of range, requiring special handling.
      if(   v.iszero()
         || (   (!ofs_exp.get_is_neg())
             && (ofs_exp.get_value_unsigned() >= static_cast<unsigned_exponent_type>(max_delta_exp))))
      {
        // Result is *this unchanged since v is negligible compared to *this.
        return *this;
      }

      if(    ofs_exp.get_is_neg()
         && (ofs_exp.get_value_unsigned() >= static_cast<unsigned_exponent_type>(max_delta_exp)))
      {
        // Result is *this = v since *this is negligible compared to v.
        return operator=(v);
      }

      // Do the add/sub operation.
      const auto ofs =
        static_cast<std::int32_t>
        (
          ((!ofs_exp.get_is_neg()) ? +static_cast<std::int32_t>(ofs_exp.get_value_unsigned() / static_cast<unsigned_exponent_type>(decwide_t_elem_digits10))
                                   : -static_cast<std::int32_t>(ofs_exp.get_value_unsigned() / static_cast<unsigned_exponent_type>(decwide_t_elem_digits10)))
        );

      #if !defined(WIDE_DECIMAL_DISABLE_DYNAMIC_MEMORY_ALLOCATION)
      representation_type my_n_data_for_add_sub;
      #endif

      if(my_neg == v.my_neg)
      {
        auto carry = limb_type { };

        // Add v to *this, where the data array of either *this or v
        // might have to be treated with a positive, negative or zero offset.
        // The result is stored in *this. The data are added one element
        // at a time, each element with carry.
        if(ofs >= static_cast<std::int32_t>(INT8_C(0)))
        {
          std::copy(v.my_data.cbegin(),
                    v.my_data.cend() - static_cast<std::ptrdiff_t>(ofs),
                    my_n_data_for_add_sub.begin() + static_cast<std::ptrdiff_t>(ofs));

          std::fill(my_n_data_for_add_sub.begin(),
                    my_n_data_for_add_sub.begin() + static_cast<std::ptrdiff_t>(ofs),
                    static_cast<limb_type>(UINT8_C(0)));

          using const_limb_pointer_type = typename std::add_const<limb_type*>::type;

          // Addition.
          carry = detail::eval_add_n(my_data.data(),
                                     static_cast<const_limb_pointer_type>(my_data.data()),
                                     static_cast<const_limb_pointer_type>(my_n_data_for_add_sub.data()),
                                     prec_elems_for_add_sub);
        }
        else
        {
          std::copy(my_data.cbegin(),
                    my_data.cend() + static_cast<std::ptrdiff_t>(ofs), // LCOV_EXCL_LINE
                    my_n_data_for_add_sub.begin() - static_cast<std::ptrdiff_t>(ofs));

          // LCOV_EXCL_START
          std::fill(my_n_data_for_add_sub.begin(),
                    my_n_data_for_add_sub.begin() - static_cast<std::ptrdiff_t>(ofs),
                    static_cast<limb_type>(UINT8_C(0)));
          // LCOV_EXCL_STOP

          using const_limb_pointer_type = typename std::add_const<limb_type*>::type;

          // Addition.
          // LCOV_EXCL_START
          carry = detail::eval_add_n(my_n_data_for_add_sub.data(),
                                     const_cast<const_limb_pointer_type>(my_n_data_for_add_sub.data()), // NOLINT(cppcoreguidelines-pro-type-const-cast)
                                     const_cast<const_limb_pointer_type>(v.my_data.data()),             // NOLINT(cppcoreguidelines-pro-type-const-cast)
                                     prec_elems_for_add_sub);
          // LCOV_EXCL_STOP

          #if (defined(__GNUC__) && !defined(__clang__))
          #if(__GNUC__ >= 12)
          #pragma GCC diagnostic push
          #pragma GCC diagnostic ignored "-Warray-bounds"
          #pragma GCC diagnostic push
          #pragma GCC diagnostic ignored "-Wrestrict"
          #endif
          #if(__GNUC__ >= 8)
          #pragma GCC diagnostic push
          #pragma GCC diagnostic ignored "-Wstringop-overflow="
          #endif
          #endif

          std::copy(static_cast<const_limb_pointer_type>(my_n_data_for_add_sub.data()),
                    static_cast<const_limb_pointer_type>(my_n_data_for_add_sub.data()) + static_cast<std::ptrdiff_t>(prec_elems_for_add_sub),
                    my_data.data());

          #if (defined(__GNUC__) && !defined(__clang__))
          #if(__GNUC__ >= 12)
          #pragma GCC diagnostic pop
          #pragma GCC diagnostic pop
          #endif
          #if(__GNUC__ >= 8)
          #pragma GCC diagnostic pop
          #endif
          #endif

          my_exp = v.my_exp;
        }

        if(carry != static_cast<limb_type>(UINT8_C(0)))
        {
          // There needs to be a carry into the element -1 of the array data.
          // But since this can't be done, shift the data to make place for the
          // carry result and adjust the exponent accordingly.

          const auto offset_to_end =
            static_cast<std::ptrdiff_t>
            (
                static_cast<std::ptrdiff_t>(static_cast<std::ptrdiff_t>(my_data.size()) - static_cast<std::ptrdiff_t>(prec_elems_for_add_sub))
              + static_cast<std::ptrdiff_t>(INT8_C(1))
            );

          std::copy_backward(my_data.cbegin(),
                             my_data.cend() - offset_to_end,
                             my_data.end());

          using local_size_type = typename representation_type::size_type;

          my_data[static_cast<local_size_type>(UINT8_C(0))] = carry;

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
        if(       (ofs >  static_cast<std::int32_t>(INT8_C(0)))
           || (   (ofs == static_cast<std::int32_t>(INT8_C(0)))
               && (detail::compare_ranges(  my_data.data(),
                                          v.my_data.data(),
                                          static_cast<std::uint_fast32_t>(prec_elems_for_add_sub)) > static_cast<std::int_fast8_t>(INT8_C(0)))))
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
                    static_cast<limb_type>(UINT8_C(0)));

          using const_limb_pointer_type = typename std::add_const<limb_type*>::type;

          // Subtraction.
          const auto has_borrow =
            detail::eval_subtract_n(my_data.data(),
                                    static_cast<const_limb_pointer_type>(my_data.data()),
                                    static_cast<const_limb_pointer_type>(my_n_data_for_add_sub.data()),
                                    prec_elems_for_add_sub);

          static_cast<void>(has_borrow);
        }
        else
        {
          if(ofs != static_cast<std::int32_t>(INT8_C(0)))
          {
            // In this case, |u| < |v| and ofs is negative.
            // Shift the data of u down to a lower value.
            std::copy_backward(my_data.cbegin(),
                               my_data.cend() - static_cast<std::ptrdiff_t>(-ofs),
                               my_data.end());

            std::fill(my_data.begin(),
                      my_data.begin() + static_cast<std::ptrdiff_t>(-ofs),
                      static_cast<limb_type>(UINT8_C(0)));
          }

          // Copy the data of v into the data array my_n_data_for_add_sub.
          // Set the u-pointer p_u to point to m_n and the
          // operand pointer p_v to point to the shifted
          // data m_data.
          std::copy(v.my_data.cbegin(),
                    v.my_data.cbegin() + static_cast<std::ptrdiff_t>(prec_elems_for_add_sub),
                    my_n_data_for_add_sub.begin());

          using const_limb_pointer_type = typename std::add_const<limb_type*>::type;

          // Subtraction.
          const auto has_borrow =
            detail::eval_subtract_n(my_n_data_for_add_sub.data(),
                                    static_cast<const_limb_pointer_type>(my_n_data_for_add_sub.data()),
                                    static_cast<const_limb_pointer_type>(my_data.data()),
                                    prec_elems_for_add_sub);

          static_cast<void>(has_borrow);

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
            my_exp = static_cast<exponent_type>(INT8_C(0));
          }
          else
          {
            // Justify the data
            const auto sj = std::distance(my_data.cbegin(), first_nonzero_elem);

            std::copy(my_data.cbegin() + sj,
                      my_data.cend(),
                      my_data.begin());

            std::fill(my_data.end() - sj,
                      my_data.end(),
                      static_cast<limb_type>(UINT8_C(0)));

            my_exp =
              static_cast<exponent_type>
              (
                  my_exp
                - static_cast<exponent_type>
                  (
                      static_cast<exponent_type>(sj)
                    * static_cast<exponent_type>(decwide_t_elem_digits10)
                  )
              );
          }
        }

        // Check for underflow.
        if(std::all_of(my_data.cbegin(),
                       my_data.cend(),
                       [](const limb_type& d) // NOLINT(modernize-use-trailing-return-type)
                       {
                         return (d == static_cast<limb_type>(UINT8_C(0)));
                       }))
        {
          static_cast<void>
          (
            operator=(zero<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>())
          );
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
      // Handle multiplication by zero.
      if(iszero() || v.iszero())
      {
        static_cast<void>
        (
          operator=(zero<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>())
        );
      }

      // Evaluate the sign of the result.
      const auto b_result_is_neg = (my_neg != v.my_neg);

      // Artificially set the sign of the result to be positive.
      my_neg = false;

      if(isone_sign_neutral(*this))
      {
        // Simply take the left-hand side since *this is either positive or negative one.
        static_cast<void>(operator=(v));
      }
      else if(isone_sign_neutral(v))
      {
        // Do nothing since this is multiplication of *this by either positive or negative one.
      }
      else
      {
        // Set the exponent of the result.
        using local_unsigned_wrap_type = detail::unsigned_wrap<unsigned_exponent_type, exponent_type>;

        const auto u_exp = local_unsigned_wrap_type {   my_exp };
        const auto v_exp = local_unsigned_wrap_type { v.my_exp };

        const auto result_exp = u_exp + v_exp;

        if((!result_exp.get_is_neg()) && (result_exp.get_value_unsigned() >= decwide_t_max_exp10))
        {
          // Check for (and handle overflow).
          static_cast<void>(operator=(my_value_max()));
        }
        else if((result_exp.get_is_neg()) && (result_exp.get_value_unsigned() >= decwide_t_max_exp10))
        {
          // Check for (and handle underflow).
          static_cast<void>(operator=(my_value_min()));
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

          const auto prec_elems_for_multiply = (std::min)(my_prec_elem, v.my_prec_elem);

          #if (defined(__GNUC__) && !defined(__clang__))
          #if(__GNUC__ >= 12)
          #pragma GCC diagnostic push
          #pragma GCC diagnostic ignored "-Warray-bounds"
          #endif
          #if(__GNUC__ >= 8)
          #pragma GCC diagnostic push
          #pragma GCC diagnostic ignored "-Wstringop-overflow="
          #endif
          #endif

          eval_mul_dispatch_multiplication_method(v, prec_elems_for_multiply);

          #if (defined(__GNUC__) && !defined(__clang__))
          #if(__GNUC__ >= 12)
          #pragma GCC diagnostic pop
          #endif
          #if(__GNUC__ >= 8)
          #pragma GCC diagnostic pop
          #endif
          #endif
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
                                    static_cast<std::uint_fast32_t>(decwide_t_elem_number)) == static_cast<std::int_fast8_t>(INT8_C(0))));

      if(u_and_v_are_identical)
      {
        const auto negate_one = (my_neg != v.my_neg);

        static_cast<void>
        (
          operator=(one<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>())
        );

        if(negate_one)
        {
          negate();
        }
      }
      else
      {
        static_cast<void>(operator*=(decwide_t(v).calculate_inv()));
      }

      return *this;
    }

    // Arithmetic operators with unsigned long long.
    auto add_unsigned_long_long(unsigned long long n) -> decwide_t& // NOLINT(google-runtime-int)
    {
      // Non-optimized addition of unsigned long long.
      return operator+=(decwide_t(n));
    }

    auto sub_unsigned_long_long(unsigned long long n) -> decwide_t& // NOLINT(google-runtime-int)
    {
      // Non-optimized subtraction of unsigned long long.
      return operator-=(decwide_t(n));
    }

    auto mul_unsigned_long_long(unsigned long long n) -> decwide_t& // NOLINT(google-runtime-int)
    {
      // Multiply *this with a constant unsigned long long.

      // Evaluate the sign of the result.
      const auto b_neg = my_neg;

      // Artificially set the sign of the result to be positive.
      my_neg = false;

      // Handle special cases like zero, inf and NaN.
      const auto b_n_is_zero = (n == static_cast<std::int32_t>(INT8_C(0)));

      if(iszero() || b_n_is_zero)
      {
        // Multiplication by zero.
        return operator=(zero<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>());
      }

      // Estimate the exponent of the result.
      using local_unsigned_wrap_type = detail::unsigned_wrap<unsigned_exponent_type, exponent_type>;

      const auto u_exp = local_unsigned_wrap_type { my_exp };
      const auto v_exp = local_unsigned_wrap_type { static_cast<exponent_type>(detail::order_of_builtin_integer(n)) };

      const auto result_exp = u_exp + v_exp;

      if((!result_exp.get_is_neg()) && (result_exp.get_value_unsigned() >= decwide_t_max_exp10))
      {
        // Check for (and handle overflow).
        return operator=((!b_neg) ? my_value_max() : -my_value_max());
      }

      if(n >= static_cast<unsigned long long>(decwide_t_elem_mask)) // NOLINT(google-runtime-int)
      {
        my_neg = b_neg;

        return operator*=(decwide_t(n));
      }

      if(n == static_cast<unsigned long long>(UINT8_C(1))) // NOLINT(google-runtime-int)
      {
        my_neg = b_neg;

        return *this;
      }

      // Set up the multiplication loop.
      const auto nn    = static_cast<limb_type>(n);
      const auto carry = detail::mul_loop_n(my_data.data(), nn, my_prec_elem);

      // Handle the carry and adjust the exponent.
      if(carry != static_cast<limb_type>(UINT8_C(0)))
      {
        my_exp = static_cast<exponent_type>(my_exp + static_cast<exponent_type>(decwide_t_elem_digits10));

        // Shift the result of the multiplication one element to the right.
        std::copy_backward(my_data.cbegin(),
                           my_data.cbegin() + static_cast<std::ptrdiff_t>(static_cast<std::ptrdiff_t>(my_prec_elem) - static_cast<std::ptrdiff_t>(INT8_C(1))),
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
      if(n == static_cast<unsigned long long>(UINT8_C(0))) // NOLINT(google-runtime-int)
      {
        // Divide by 0.
        return operator=(zero<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>());
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

      if(nn > static_cast<limb_type>(UINT8_C(1)))
      {
        // Do the division loop.
        const auto prev = detail::div_loop_n(my_data.data(), nn, my_prec_elem);

        using local_size_type = typename representation_type::size_type;

        // Determine if one leading zero is in the result data.
        if(my_data[static_cast<local_size_type>(UINT8_C(0))] == static_cast<limb_type>(UINT8_C(0)))
        {
          // Adjust the exponent
          my_exp = static_cast<exponent_type>(my_exp - static_cast<exponent_type>(decwide_t_elem_digits10));

          // Shift result of the division one element to the left.
          const auto prec_minus_one =
            static_cast<std::ptrdiff_t>
            (
                static_cast<std::ptrdiff_t>(my_prec_elem)
              - static_cast<std::ptrdiff_t>(INT8_C(1))
            );

          std::copy(my_data.cbegin() + static_cast<std::ptrdiff_t>(INT8_C(1)),
                    my_data.cbegin() + prec_minus_one,
                    my_data.begin());

          const auto index_prev =
            static_cast<local_size_type>
            (
              static_cast<std::ptrdiff_t>(my_prec_elem) - static_cast<std::ptrdiff_t>(INT8_C(1))
            );

          const auto val_prev =
            static_cast<limb_type>
            (
                static_cast<std::uint64_t>
                (
                    static_cast<std::uint64_t>(prev)
                  * static_cast<std::uint32_t>(decwide_t_elem_mask)
                )
              / nn
            );

          my_data[index_prev] = val_prev;
        }
      }

      // Check for underflow.
      if(my_exp < decwide_t_min_exp10)
      {
        return operator=(zero<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>());
      }

      // Set the sign of the result.
      my_neg = b_neg;

      return *this;
    }

    // Arithmetic operators with signed long long.
    auto add_signed_long_long(signed long long n) -> decwide_t& // NOLINT(google-runtime-int)
    {
      if(n < static_cast<signed long long>(INT8_C(0))) // NOLINT(google-runtime-int)
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
      const auto b_neg = (n < static_cast<signed long long>(INT8_C(0))); // NOLINT(google-runtime-int)

      mul_unsigned_long_long
      (
        (!b_neg) ?                static_cast<unsigned long long>(n)  // NOLINT(google-runtime-int)
                 : detail::negate(static_cast<unsigned long long>(n)) // NOLINT(google-runtime-int)
      );

      return ((!b_neg) ? *this : negate());
    }

    auto div_signed_long_long(signed long long n) -> decwide_t& // NOLINT(google-runtime-int)
    {
      const auto b_neg = (n < static_cast<signed long long>(INT8_C(0))); // NOLINT(google-runtime-int)

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

      auto n_result = std::int_fast8_t { };

      // Handle all *finite* cases only.
      if(iszero())
      {
        // The value of *this is zero and v is either zero or non-zero.
        n_result = (v.iszero() ? static_cast<std::int_fast8_t>(INT8_C(0))
                               : (v.my_neg ? static_cast<std::int_fast8_t>(INT8_C(1))
                                           : static_cast<std::int_fast8_t>(INT8_C(-1))));
      }
      else
      {
        if(v.iszero())
        {
          // The value of v is zero and *this is non-zero.
          n_result = (my_neg ? static_cast<std::int_fast8_t>(INT8_C(-1))
                             : static_cast<std::int_fast8_t>(INT8_C(1)));
        }
        else
        {
          // Both *this and v are non-zero.

          if(my_neg != v.my_neg)
          {
            // The signs are different.
            n_result = (my_neg ? static_cast<std::int_fast8_t>(INT8_C(-1))
                               : static_cast<std::int_fast8_t>(INT8_C(1)));
          }
          else
          {
            if(my_exp != v.my_exp)
            {
              // The signs are the same and the exponents are different.
              const auto val_cmp_exp =
                static_cast<std::int_fast8_t>
                (
                  ((my_exp < v.my_exp) ? static_cast<std::int_fast8_t>(INT8_C(1))
                                       : static_cast<std::int_fast8_t>(INT8_C(-1)))
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

              // TBD: Compare the limbs. If the final limb is reached,
              // check the comparison result on the relevant digit-level.
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
          {
            static_cast<limb_type>
            (
              detail::pow10_maker
              (
                static_cast<std::uint32_t>
                (
                  static_cast<std::int32_t>
                  (
                      static_cast<std::int32_t>
                      (
                        static_cast<std::int32_t>(INT8_C(1)) + decwide_t_digits10_for_epsilon()
                      )
                    - decwide_t_digits10
                  )
                )
              )
            )
          },
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

    auto precision(const std::int32_t prec_digits) noexcept -> void
    {
      const auto prec_digits_elem_digits10_div = static_cast<std::int32_t>(prec_digits / decwide_t_elem_digits10);
      const auto prec_digits_elem_digits10_mod = static_cast<std::int32_t>(prec_digits % decwide_t_elem_digits10);

      const auto elems_needed_for_digits =
        static_cast<std::int32_t>
        (
            prec_digits_elem_digits10_div
          + static_cast<std::int32_t>
            (
              (prec_digits_elem_digits10_mod != static_cast<std::int32_t>(INT8_C(0)))
                ? static_cast<std::int32_t>(INT8_C(1))
                : static_cast<std::int32_t>(INT8_C(0))
            )
        );

      {
        const auto elems_least = (std::max)(elems_needed_for_digits, static_cast<std::int32_t>(INT8_C(2)));

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
      // Handle the special case of zero.
      if(iszero())
      {
        return operator=(zero<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>());
      }

      if(isone_sign_neutral(*this))
      {
        return *this;
      }

      const auto b_neg = my_neg;

      my_neg = false;

      // Use the original value of *this for iteration below.
      decwide_t x(*this);

      // Generate the initial estimate using division.
      // Extract the mantissa and exponent for a "manual"
      // computation of the estimate.
      internal_float_type dd { };
      exponent_type       ne { };

      x.extract_parts(dd, ne);

      const auto original_prec_elem = my_prec_elem;

      // Do the inverse estimate using InternalFloatType precision estimates of mantissa and exponent.
      {
        const auto one_over_d =
          static_cast<internal_float_type>
          (
            static_cast<internal_float_type>(1.0F) / dd
          );

        static_cast<void>(operator=(decwide_t(one_over_d, static_cast<exponent_type>(-ne))));
      }

      // Compute the inverse of *this. Quadratically convergent Newton-Raphson iteration
      // is used. During the iterative steps, the precision of the calculation is limited
      // to the minimum required in order to minimize the run-time.

      for(auto digits  = static_cast<std::int32_t>(std::numeric_limits<internal_float_type>::digits10 - 1);
               digits  < static_cast<std::int32_t>(original_prec_elem * decwide_t_elem_digits10); // NOLINT(altera-id-dependent-backward-branch)
               digits *= static_cast<std::int32_t>(INT8_C(2)))
      {
        // Adjust precision of the terms.
        const auto min_elem_digits10_plus_one =
          (std::min)
          (
            static_cast<std::int32_t>(decwide_t_elem_digits10 + static_cast<std::int32_t>(INT8_C(1))),
            static_cast<std::int32_t>(INT8_C(9))
          );

        const auto new_prec_as_digits10 =
          static_cast<std::int32_t>
          (
              static_cast<std::int32_t>(digits * static_cast<std::int32_t>(INT8_C(2)))
            + min_elem_digits10_plus_one
          );

          precision(new_prec_as_digits10);
        x.precision(new_prec_as_digits10);

        // Next iteration of *this.
        static_cast<void>
        (
          operator=(*this * (two<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>() - (*this * x)))
        );
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
        return operator=(zero<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>());
      }

      if(iszero())
      {
        return *this;
      }

      if(isone())
      {
        return *this;
      }

      // Use the original value of *this for iteration below.
      decwide_t x(*this);

      // Generate the initial estimate using division.
      // Extract the mantissa and exponent for a "manual"
      // computation of the estimate.
      auto dd = internal_float_type { };
      auto ne = exponent_type       { };

      extract_parts(dd, ne);

      // Force the exponent to be an even multiple of two.
      const auto exponent_is_odd =
      (
        static_cast<exponent_type>(ne % static_cast<exponent_type>(INT8_C(2))) != static_cast<exponent_type>(INT8_C(0))
      );

      if(exponent_is_odd)
      {
        ++ne;

        dd /= static_cast<internal_float_type>(10.0F); // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
      }

      using std::sqrt;

      // Setup the iteration.
      // Estimate the square root using simple manipulations.
      const internal_float_type sqd = sqrt(dd);

      const auto original_prec_elem = my_prec_elem;

      static_cast<void>(operator=(decwide_t(sqd, static_cast<exponent_type>(ne / 2))));

      // Estimate 1.0 / (2.0 * x0) using simple manipulations.
      const auto inv_half_sqd =
        static_cast<internal_float_type>
        (
          static_cast<internal_float_type>(0.5F) / sqd
        );

      const auto minus_half_ne =
        static_cast<exponent_type>
        (
          static_cast<exponent_type>(-ne) / static_cast<std::int8_t>(INT8_C(2))
        );

      decwide_t vi(inv_half_sqd, minus_half_ne);

      // Compute the square root of *this. Coupled Newton iteration
      // as described in "Pi Unleashed" is used. During the
      // iterative steps, the precision of the calculation is
      // limited to the minimum required in order to minimize
      // the run-time.
      //
      // Book references:
      // http://www.jjj.de/pibook/pibook.html
      // http://www.springer.com/gp/book/9783642567353

      for(auto digits  = static_cast<std::int32_t>(std::numeric_limits<internal_float_type>::digits10 - 1);
               digits  < static_cast<std::int32_t>(original_prec_elem * decwide_t_elem_digits10); // NOLINT(altera-id-dependent-backward-branch)
               digits *= static_cast<std::int32_t>(INT8_C(2)))
      {
        // Adjust precision of the terms.
        const auto min_elem_digits10_plus_one =
          (std::min)
          (
            static_cast<std::int32_t>(decwide_t_elem_digits10 + static_cast<std::int32_t>(INT8_C(1))),
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
        static_cast<void>
        (
          operator+=(vi * (-((*this) * (*this)) + x))
        );
      }

      my_prec_elem = original_prec_elem;

      return *this;
    }

    auto calculate_rootn_inv(std::int32_t p) -> decwide_t&
    {
      // Compute the inverse of the n'th root of *this.
      // In other words compute the value of [1 / (rootn of *this)]
      // with n = p.

      // LCOV_EXCL_START
      if(p < static_cast<std::int32_t>(INT8_C(1)))
      {
        return operator=(zero<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>());
      }

      if(p == static_cast<std::int32_t>(INT8_C(1)))
      {
        return *this;
      }
      // LCOV_EXCL_STOP

      // Use the original value of *this for iteration below.
      decwide_t x(*this);

      // Generate the initial estimate using 1 / rootn.
      // Extract the mantissa and exponent for a "manual"
      // computation of the estimate.
      auto dd = internal_float_type { };
      auto ne = exponent_type       { };

      x.extract_parts(dd, ne);

      // Adjust exponent and mantissa such that ne is an even power of p.
      while(static_cast<exponent_type>(ne % static_cast<exponent_type>(p)) != static_cast<exponent_type>(INT8_C(0)))
      {
        ++ne;

        dd /= static_cast<internal_float_type>(10.0F); // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
      }

      const auto original_prec_elem = x.my_prec_elem;

      using std::pow;

      // Estimate the initial guess of one over the root using simple manipulations.
      const InternalFloatType one_over_rtn_d = pow(dd, static_cast<internal_float_type>(-1) / static_cast<internal_float_type>(p));

      // Set the result equal to the initial guess.
      static_cast<void>
      (
        operator=(decwide_t(one_over_rtn_d, static_cast<exponent_type>(static_cast<exponent_type>(-ne) / p)))
      );

      for(auto digits  = static_cast<std::int32_t>(std::numeric_limits<internal_float_type>::digits10 - 1);
               digits  < static_cast<std::int32_t>(original_prec_elem * decwide_t_elem_digits10); // NOLINT(altera-id-dependent-backward-branch)
               digits *= static_cast<std::int32_t>(INT8_C(2)))
      {
        // Adjust precision of the terms.
        const auto min_elem_digits10_plus_one =
          (std::min)
          (
            static_cast<std::int32_t>(decwide_t_elem_digits10 + static_cast<std::int32_t>(INT8_C(1))),
            static_cast<std::int32_t>(INT8_C(9))
          );

        const auto new_prec_as_digits10 =
          static_cast<std::int32_t>
          (
              static_cast<std::int32_t>(digits * static_cast<std::int32_t>(INT8_C(2)))
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

        static_cast<void>(operator*=(term));
      }

      my_prec_elem = original_prec_elem;

      return *this;
    }

    static auto calculate_frexp(decwide_t& result, const decwide_t& x, exponent_type* e) -> void
    {
      // This implementation of frexp follows closely that of eval_frexp
      // in Boost.Multiprecision's cpp_dec_float template class.
      result = x;

      if(result.iszero())
      {
        *e = static_cast<exponent_type>(INT8_C(0));

        return;
      }

      if(result.isneg())
      {
        result.negate();
      }

      using std::ilogb;

      // N[1000/301, 44]
      auto t =
        static_cast<exponent_type>
        (
            static_cast<long double>(ilogb(result))
          * static_cast<long double>(3.3222591362126245847176079734219269102990033L) // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
        );

      result *= pow(two<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>(), -t);

      // TBD: Handle underflow/overflow if (or when) needed.

      while(result.cmp(one<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>()) >= INT8_C(0))
      {
        result /= static_cast<int>(INT8_C(2));

        ++t;
      }

      while(result.cmp(half<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>()) < INT8_C(0))
      {
        result *= static_cast<int>(INT8_C(2));

        --t;
      }

      *e = t;

      if(x.isneg())
      {
        result.negate();
      }
    }

    auto negate() -> decwide_t&
    {
      if(!iszero())
      {
        my_neg = (!my_neg);
      }

      return *this; // LCOV_EXCL_LINE
    }

    // Comparison functions.
    WIDE_DECIMAL_NODISCARD constexpr auto (isnan)   () const noexcept -> bool { return false; }
    WIDE_DECIMAL_NODISCARD constexpr auto (isinf)   () const noexcept -> bool { return false; }
    WIDE_DECIMAL_NODISCARD constexpr auto (isfinite)() const noexcept -> bool { return (my_fpclass == fpclass_type::decwide_t_finite); }

    WIDE_DECIMAL_NODISCARD constexpr auto iszero() const noexcept -> bool
    {
      using local_size_type = typename representation_type::size_type;

      return (my_data[static_cast<local_size_type>(UINT8_C(0))] == static_cast<limb_type>(UINT8_C(0)));
    }

    WIDE_DECIMAL_NODISCARD auto isone() const -> bool
    {
      // Check if the value of *this is identically 1 or very close to 1.
      return ((!my_neg) && isone_sign_neutral(*this));
    }

    WIDE_DECIMAL_NODISCARD auto isone_minus() const -> bool
    {
      // Check if the value of *this is identically 1 or very close to 1.
      return (my_neg && isone_sign_neutral(*this));
    }

    WIDE_DECIMAL_NODISCARD auto isint() const noexcept -> bool
    {
      auto value_is_int = bool { };

      if(   (my_fpclass != fpclass_type::decwide_t_finite)
         || (my_exp < static_cast<exponent_type>(INT8_C(0))))
      {
        // Here, we have *this non-finite or |*this| < 1,
        // so *this can not be int.
        value_is_int = false;
      }
      else if(iszero() || isone_sign_neutral(*this))
      {
        value_is_int = true;
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
                           return (d != static_cast<limb_type>(UINT8_C(0)));
                         });

          value_is_int = (it_non_zero == my_data.cend());
        }
      }

      return value_is_int;
    }

    WIDE_DECIMAL_NODISCARD constexpr auto isneg() const noexcept -> bool { return my_neg; }
    WIDE_DECIMAL_NODISCARD constexpr auto ispos() const noexcept -> bool { return (!isneg()); }

    // Operators pre-increment and pre-decrement.
    auto operator++() -> decwide_t& { return *this += one<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>(); }
    auto operator--() -> decwide_t& { return *this -= one<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>(); }

    // Operators post-increment and post-decrement.
    auto operator++(int) -> decwide_t { const decwide_t w(*this); static_cast<void>(++(*this)); return w; }
    auto operator--(int) -> decwide_t { const decwide_t w(*this); static_cast<void>(--(*this)); return w; }

    // Conversion routines.
    auto extract_parts(internal_float_type& mantissa, exponent_type& exponent) const -> void
    {
      // Extracts the mantissa as a decimal part less in magnitude
      // than 1 and the base-10 exponent parts of this decwide_t.
      // For instance 45.67e8 will be extracted as 0.4567 * e10.

      mantissa = static_cast<internal_float_type>(0.0F);

      auto p10 = limb_type { };

      const auto expval = detail::order_of_builtin_integer(my_data[static_cast<std::uint_fast32_t>(UINT8_C(0))], &p10);

      exponent = static_cast<exponent_type>(static_cast<exponent_type>(expval) + my_exp);

      auto scale =
        static_cast<internal_float_type>
        (
          static_cast<internal_float_type>(1.0F) / static_cast<internal_float_type>(p10)
        );

      constexpr auto digit_loops_elem_digits10_div =
        static_cast<std::int32_t>
        (
            static_cast<std::int32_t>(std::numeric_limits<internal_float_type>::max_digits10)
          / static_cast<std::int32_t>(decwide_t_elem_digits10)
        );

      constexpr auto digit_loops_elem_digits10_mod =
        static_cast<std::int32_t>
        (
            static_cast<std::int32_t>(std::numeric_limits<internal_float_type>::max_digits10)
          % static_cast<std::int32_t>(decwide_t_elem_digits10)
        );

      constexpr auto digit_loops = // NOLINT(altera-id-dependent-backward-branch)
        static_cast<std::int32_t>
        (
            digit_loops_elem_digits10_div
          + static_cast<std::int32_t>
            (
              (digit_loops_elem_digits10_mod != static_cast<std::int32_t>(INT8_C(0)))
                ? static_cast<std::int32_t>(INT8_C(1))
                : static_cast<std::int32_t>(INT8_C(0))
            )
        );

      using local_size_type = typename representation_type::size_type;

      const auto digit_loops_max =
        static_cast<local_size_type>
        (
          (std::min)(my_data.size(), static_cast<local_size_type>(digit_loops))
        );

      for(auto   limb_index = static_cast<local_size_type>(UINT8_C(0));
                 limb_index < digit_loops_max; // NOLINT(altera-id-dependent-backward-branch)
               ++limb_index)
      {
        mantissa += (static_cast<internal_float_type>(my_data[limb_index]) * scale);

        scale /= static_cast<internal_float_type>(decwide_t_elem_mask);
      }

      if(my_neg)
      {
        mantissa = -mantissa;
      }
    }

    WIDE_DECIMAL_NODISCARD auto extract_integer_part() const -> decwide_t
    {
      // Compute the signed integer part of x.

      if(my_exp < static_cast<exponent_type>(INT8_C(0)))
      {
        // The absolute value of the number is smaller than 1.
        // Thus the integer part is zero.
        return zero<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>();
      }

      const auto is_too_large_to_resolve =
      (
        my_exp >= static_cast<exponent_type>(decwide_t_digits10 - static_cast<std::int32_t>(INT8_C(1)))
      );

      if(is_too_large_to_resolve)
      {
        // The number is too large to resolve the integer part.
        // Thus it is already a pure integer part.
        return *this; // LCOV_EXCL_LINE
      }

      // Make a local copy.
      decwide_t x(*this);

      // Clear out the decimal portion
      const auto first_clear =
        static_cast<std::ptrdiff_t>
        (
            static_cast<std::ptrdiff_t>
            (
              static_cast<std::ptrdiff_t>(x.my_exp) / static_cast<std::ptrdiff_t>(decwide_t_elem_digits10)
            )
          + static_cast<std::ptrdiff_t>(INT8_C(1))
        );

      const auto last_clear  = static_cast<std::ptrdiff_t>(decwide_t_elem_number);

      std::fill(x.my_data.begin() + first_clear,
                x.my_data.begin() + last_clear,
                static_cast<limb_type>(UINT8_C(0)));

      return x;
    }

    WIDE_DECIMAL_NODISCARD auto extract_long_double() const -> long double
    {
      // Returns the long double conversion of a decwide_t.

      // Check for non-normal decwide_t.
      decwide_t xx(*this);

      xx.my_neg = false;

      constexpr auto digs_of_ldbl_to_get = static_cast<std::int32_t>(std::numeric_limits<long double>::max_digits10);

      constexpr auto elems_of_ldbl_to_get_try =
        static_cast<std::int32_t>
        (
            static_cast<std::int32_t>(digs_of_ldbl_to_get / decwide_t_elem_digits10)
          + static_cast<std::int32_t>
            (
              static_cast<std::int32_t>(digs_of_ldbl_to_get % decwide_t_elem_digits10) != static_cast<std::int32_t>(INT8_C(0))
                ? static_cast<std::int32_t>(INT8_C(1))
                : static_cast<std::int32_t>(INT8_C(0))
            )
          + static_cast<int>(INT8_C(1))
        );

      constexpr auto elems_of_ldbl_to_get =
        static_cast<std::int32_t>
        (
          // Caution: Do not use (std::min) here because some language
          // standards (such as C++11) do not have constexpr-<algorithm>.
          (elems_of_ldbl_to_get_try < decwide_t_elem_number) ? elems_of_ldbl_to_get_try : decwide_t_elem_number
        );

      using local_unsigned_exponent_type = typename std::make_unsigned<exponent_type>::type;

      constexpr auto ldbl_max_width_for_exp = static_cast<std::int32_t>(std::numeric_limits<local_unsigned_exponent_type>::digits10);

      constexpr auto ldbl_str_rep_char_cnt =
        static_cast<std::int32_t>
        (
            static_cast<std::int32_t>(INT8_C(1))              // +/- sign
          + static_cast<std::int32_t>
            (
              elems_of_ldbl_to_get * decwide_t_elem_digits10
            )                                                 // number of decimal digits
          + static_cast<std::int32_t>(INT8_C(1))              // decimal point
          + static_cast<std::int32_t>(INT8_C(2))              // E+ or E-
          + ldbl_max_width_for_exp                            // unsigned integral representation of the exponent
        );

      using ldbl_str_array_type = std::array<char, static_cast<std::size_t>(ldbl_str_rep_char_cnt)>;

      auto ldbl_str_rep = ldbl_str_array_type { };

      ldbl_str_rep.fill('\0');

      auto ldbl_str_pos = static_cast<std::size_t>(UINT8_C(0));

      ldbl_str_rep.at(ldbl_str_pos) = ((!my_neg) ? '+' : '-');

      ++ldbl_str_pos;

      auto count_retrieved = std::size_t { };

      get_output_digits(*this,
                        ldbl_str_rep.data() + ldbl_str_pos,
                        elems_of_ldbl_to_get,
                        &count_retrieved,
                        true);

      // Note: Add an additional 1 to the long double string position
      // in order to include both the retrieved decimal digits as well as
      // the decimal point.

      ldbl_str_pos =
        static_cast<std::size_t>
        (
            ldbl_str_pos
          + static_cast<std::size_t>(count_retrieved + static_cast<std::size_t>(UINT8_C(1)))
        );

      // Handle the letter 'E' for the exponent.
      ldbl_str_rep.at(ldbl_str_pos) = 'E';

      ++ldbl_str_pos;

      // Handle the sign of the exponent.
      const auto exp_is_neg = (my_exp < static_cast<exponent_type>(INT8_C(0)));

      ldbl_str_rep.at(ldbl_str_pos) = ((!exp_is_neg) ? '+' : '-');

      ++ldbl_str_pos;

      // Obtain the absolute value of the exponent from decwide_t.
      const auto ul_exp =
        static_cast<local_unsigned_exponent_type>
        (
          (!exp_is_neg) ? static_cast<local_unsigned_exponent_type>(my_exp)
                        : static_cast<local_unsigned_exponent_type>(-my_exp)
        );

      {
        // Extract the integral value of the absolute value of the exponent.
        using exp_array_type =
          std::array<char, static_cast<std::size_t>(ldbl_max_width_for_exp)>;

        auto data_exp_buf = exp_array_type { };

        const char* p_end = util::baselexical_cast(ul_exp, data_exp_buf.data(), data_exp_buf.data() + data_exp_buf.size());

        const auto exp_len = std::distance(static_cast<const char*>(data_exp_buf.data()), p_end);

        std::copy(data_exp_buf.cbegin(),
                  data_exp_buf.cbegin() + static_cast<std::size_t>(exp_len),
                  ldbl_str_rep.begin() + ldbl_str_pos);
      }

      // Use the C-style library function strtold() in order
      // to convert string representation to native long double.

      const auto ldbl_retrieved = std::strtold(ldbl_str_rep.data(), nullptr);

      return ldbl_retrieved;
    }

    WIDE_DECIMAL_NODISCARD auto extract_signed_long_long() const -> signed long long // NOLINT(google-runtime-int)
    {
      // Extracts a signed long long from *this.
      // If either (x > maximum of signed long long)
      // or (x < minimum of signed long long), then
      // the maximum or minimum of signed long long
      // is returned accordingly.

      auto signed_long_long_result = static_cast<signed long long>(INT8_C(0)); // NOLINT(google-runtime-int)

      if(my_exp >= static_cast<exponent_type>(INT8_C(0)))
      {
        const auto b_neg = isneg();

        if((!b_neg) && (*this > signed_long_long_max<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>()))
        {
          signed_long_long_result = (std::numeric_limits<signed long long>::max)(); // NOLINT(google-runtime-int)
        }
        else
        {
          if(b_neg && (*this < signed_long_long_min<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>()))
          {
            signed_long_long_result = (std::numeric_limits<signed long long>::min)(); // NOLINT(google-runtime-int)
          }
          else
          {
            // Extract the data of *this into an unsigned long long value.
            decwide_t xn(*this);

            xn.eval_round_self();

            xn = fabs(xn.extract_integer_part());

            using local_size_type = typename representation_type::size_type;

            auto val = static_cast<unsigned long long>(xn.my_data[static_cast<local_size_type>(UINT8_C(0))]); // NOLINT(google-runtime-int)

            const auto imax =
              (std::min)
              (
                static_cast<std::int32_t>(static_cast<std::int32_t>(xn.my_exp) / decwide_t_elem_digits10),
                static_cast<std::int32_t>(decwide_t_elem_number - static_cast<std::int32_t>(INT8_C(1)))
              );

            using local_size_type = typename representation_type::size_type;

            for(auto  limb_index  = static_cast<local_size_type>(UINT8_C(1));
                      limb_index <= static_cast<local_size_type>(static_cast<std::uint32_t>(imax)); // NOLINT(altera-id-dependent-backward-branch)
                    ++limb_index)
            {
              val *= static_cast<unsigned long long>(decwide_t_elem_mask);    // NOLINT(google-runtime-int)
              val += static_cast<unsigned long long>(xn.my_data[limb_index]); // NOLINT(google-runtime-int)
            }

            signed_long_long_result = ((!b_neg) ? static_cast<signed long long>(val)                   // NOLINT(google-runtime-int)
                                                : static_cast<signed long long>(detail::negate(val))); // NOLINT(google-runtime-int)
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

      auto unsigned_long_long_result = static_cast<unsigned long long>(UINT8_C(0)); // NOLINT(google-runtime-int)

      if(isneg())
      {
        unsigned_long_long_result = static_cast<unsigned long long>(extract_signed_long_long()); // NOLINT(google-runtime-int)
      }
      else
      {
        if(my_exp >= static_cast<exponent_type>(INT8_C(0)))
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
            using local_size_type = typename representation_type::size_type;

            // Extract the data into an unsigned long long value.
            auto val = static_cast<unsigned long long>(xn.my_data[static_cast<local_size_type>(UINT8_C(0))]); // NOLINT(google-runtime-int)

            const auto imax =
              static_cast<std::int32_t>
              (
                (std::min)(static_cast<std::int32_t>(static_cast<std::int32_t>(xn.my_exp) / decwide_t_elem_digits10),
                           static_cast<std::int32_t>(decwide_t_elem_number - static_cast<std::int32_t>(INT8_C(1))))
              );

            using local_size_type = typename representation_type::size_type;

            for(auto   limb_index  = static_cast<local_size_type>(UINT8_C(1));
                       limb_index <= static_cast<local_size_type>(static_cast<std::uint32_t>(imax)); // NOLINT(altera-id-dependent-backward-branch)
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
      return
        static_cast<IntegralType>
        (
          std::is_signed<IntegralType>::value
            ? static_cast<IntegralType>(extract_signed_long_long())
            : static_cast<IntegralType>(extract_unsigned_long_long())
        );
    }

    // Cast operator to built-in Boolean type.
    explicit constexpr operator bool() const { return (!iszero()); }

    static auto from_lst(      std::initializer_list<limb_type> limb_values,
                         const exponent_type                    e      = static_cast<exponent_type>(INT8_C(0)),
                         const bool                             is_neg = false) -> decwide_t
    {
      // Initialization from initializer list of limbs,
      // exponent value (normed to limb granularity)
      // and optional sign flag.
      auto a = decwide_t { };

      if(limb_values.size() < a.my_data.size())
      {
        std::copy(limb_values.begin(),
                  limb_values.end(),
                  a.my_data.begin());

        std::fill(a.my_data.begin() + limb_values.size(),
                  a.my_data.end(),
                  static_cast<limb_type>(UINT8_C(0)));
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

    static constexpr auto decwide_t_digits10_for_epsilon() -> std::int32_t
    {
      return
        static_cast<std::int32_t>
        (
            static_cast<std::int32_t>
            (
                static_cast<std::int32_t>(decwide_t_digits10 / decwide_t_elem_digits10)
              + static_cast<std::int32_t>
                (
                  (static_cast<std::int32_t>(decwide_t_digits10 % decwide_t_elem_digits10) != static_cast<std::int32_t>(INT8_C(0)))
                    ? static_cast<std::int32_t>(INT8_C(1))
                    : static_cast<std::int32_t>(INT8_C(0))
                )
            )
          * decwide_t_elem_digits10
        );
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

    WIDE_DECIMAL_NODISCARD static auto isone_sign_neutral(const decwide_t& x) -> bool
    {
      // Check if the value of *this is identically 1 or very close to 1.

      auto value_is_one = bool { };

      using local_size_type = typename representation_type::size_type;

      if(   (x.my_data[static_cast<local_size_type>(UINT8_C(0))] == static_cast<limb_type>(UINT8_C(1)))
         && (x.my_exp == static_cast<exponent_type>(INT8_C(0))))
      {
        const auto it_non_zero = // NOLINT(llvm-qualified-auto,readability-qualified-auto)
          std::find_if(x.my_data.cbegin() + static_cast<std::ptrdiff_t>(INT8_C(1)),
                       x.my_data.cend(),
                       [](const limb_type& d) // NOLINT(modernize-use-trailing-return-type)
                       {
                         return (d != static_cast<limb_type>(UINT8_C(0)));
                       });

        value_is_one = (it_non_zero == x.my_data.cend());
      }
      else if(   (x.my_data[static_cast<local_size_type>(UINT8_C(0))] == static_cast<limb_type>(decwide_t_elem_mask_min1))
              && (x.my_exp == static_cast<exponent_type>(-decwide_t_elem_digits10)))
      {
        const auto it_non_nine = // NOLINT(llvm-qualified-auto,readability-qualified-auto)
          std::find_if(x.my_data.cbegin() + static_cast<std::ptrdiff_t>(INT8_C(1)),
                       x.my_data.cend(),
                       [](const limb_type& d) // NOLINT(modernize-use-trailing-return-type)
                       {
                         return (d != static_cast<limb_type>(decwide_t_elem_mask_min1));
                       });

        value_is_one = (it_non_nine == x.my_data.cend());
      }

      return value_is_one;
    }

    auto from_unsigned_long_long(unsigned long long u) -> void // NOLINT(google-runtime-int)
    {
      my_exp = static_cast<exponent_type>(INT8_C(0));

      auto i = static_cast<std::uint_fast32_t>(UINT8_C(0));

      auto uu = u;

      constexpr auto local_tmp_array_size =
        static_cast<std::size_t>
        (
            static_cast<std::size_t>
            (
                std::numeric_limits<unsigned long long>::digits10 // NOLINT(google-runtime-int)
              / static_cast<int>(decwide_t_elem_digits10)
            )
          + static_cast<std::size_t>(UINT8_C(3))
        );

      using local_tmp_array_type = std::array<limb_type, local_tmp_array_size>;

      local_tmp_array_type tmp;

      tmp.fill(static_cast<limb_type>(UINT8_C(0)));

      while
      (
           (uu != static_cast<unsigned long long>(UINT8_C(0))) // NOLINT(google-runtime-int,altera-id-dependent-backward-branch)
        && (i  <  static_cast<std::uint_fast32_t>(std::tuple_size<local_tmp_array_type>::value))
      )
      {
        tmp[static_cast<std::size_t>(i)] = // NOLINT(cppcoreguidelines-pro-bounds-constant-array-index)
          static_cast<limb_type>(uu % static_cast<unsigned long long>(decwide_t_elem_mask)); // NOLINT(google-runtime-int)

        uu = static_cast<unsigned long long>(uu / static_cast<unsigned long long>(decwide_t_elem_mask)); // NOLINT(google-runtime-int)

        ++i;
      }

      if(i > static_cast<std::uint_fast32_t>(UINT8_C(1)))
      {
        my_exp =
          static_cast<exponent_type>
          (
              my_exp
            + static_cast<exponent_type>
              (
                  static_cast<exponent_type>(i - static_cast<std::uint_fast32_t>(UINT8_C(1)))
                * static_cast<exponent_type>(decwide_t_elem_digits10)
              )
          );
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
                static_cast<limb_type>(UINT8_C(0)));
    }

    template<typename FloatingPointType>
    auto from_builtin_float_type(FloatingPointType flt) -> void
    {
      const auto b_neg = (flt < static_cast<FloatingPointType>(0.0F));

      const detail::template native_float_parts<FloatingPointType> ld_parts((!b_neg) ? flt : -flt);

      // Create a decwide_t from the fractional part of the
      // mantissa expressed as an unsigned long long.
      from_unsigned_long_long(ld_parts.get_mantissa());

      // Scale the unsigned long long representation to the fractional
      // part of the long double and multiply with the base-2 exponent.
      const auto p2 =
        static_cast<int>
        (
            ld_parts.get_exponent()
          - static_cast<int>(std::numeric_limits<FloatingPointType>::digits - static_cast<int>(INT8_C(1)))
        );

      if     (p2 <  static_cast<int>(INT8_C(-2))) { *this *= pow(half<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>(), -p2); }
      else if(p2 == static_cast<int>(INT8_C(-2))) { *this /= static_cast<limb_type>(UINT8_C(4)); }
      else if(p2 == static_cast<int>(INT8_C(-1))) { *this /= static_cast<limb_type>(UINT8_C(2)); }
      else if(p2 == static_cast<int>(INT8_C( 0))) { ; }
      else if(p2 == static_cast<int>(INT8_C( 1))) { *this *= static_cast<limb_type>(UINT8_C(2)); }
      else if(p2 == static_cast<int>(INT8_C( 2))) { *this *= static_cast<limb_type>(UINT8_C(4)); }
      else                                        { *this *= pow(two<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>(), p2); }

      my_neg = b_neg;
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
              static_cast<typename school_mul_pool_type::size_type>(prec_elems_for_multiply)
            * static_cast<typename school_mul_pool_type::size_type>(UINT8_C(2))
          )
        );
      #endif

      limb_type* result = my_school_mul_pool.data();

      using const_limb_pointer_type = typename std::add_const<limb_type*>::type;

      detail::eval_multiply_n_by_n_to_2n(result,
                                         const_cast<const_limb_pointer_type>(my_data.data()),   // NOLINT(cppcoreguidelines-pro-type-const-cast)
                                         const_cast<const_limb_pointer_type>(v.my_data.data()), // NOLINT(cppcoreguidelines-pro-type-const-cast)
                                         prec_elems_for_multiply);

      // Handle a potential carry.
      if(result[static_cast<std::size_t>(UINT8_C(0))] != static_cast<limb_type>(UINT8_C(0))) // NOLINT(cppcoreguidelines-pro-bounds-pointer-arithmetic)
      {
        my_exp = static_cast<exponent_type>(my_exp + static_cast<exponent_type>(decwide_t_elem_digits10));

        // Shift the result of the multiplication one element to the right.
        std::copy(result,
                  result + static_cast<std::ptrdiff_t>(prec_elems_for_multiply), // NOLINT(cppcoreguidelines-pro-bounds-pointer-arithmetic)
                  my_data.begin());
      }
      else
      {
        const auto kara_limit = (std::min)(decwide_t_elem_number, decwide_t_elems_for_kara);

        const auto copy_limit = static_cast<std::ptrdiff_t>((std::min)(prec_elems_for_multiply, kara_limit));

        std::copy(result +                             static_cast<std::ptrdiff_t>(INT8_C(1)),               // NOLINT(cppcoreguidelines-pro-bounds-pointer-arithmetic)
                  result + static_cast<std::ptrdiff_t>(static_cast<std::ptrdiff_t>(INT8_C(1)) + copy_limit), // NOLINT(cppcoreguidelines-pro-bounds-pointer-arithmetic)
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
                static_cast<typename school_mul_pool_type::size_type>(prec_elems_for_multiply)
              * static_cast<typename school_mul_pool_type::size_type>(UINT8_C(2))
            )
          );
        #endif

        limb_type* result = my_school_mul_pool.data();

        using const_limb_pointer_type = typename std::add_const<limb_type*>::type;

        detail::eval_multiply_n_by_n_to_2n(result,
                                           const_cast<const_limb_pointer_type>(my_data.data()),   // NOLINT(cppcoreguidelines-pro-type-const-cast)
                                           const_cast<const_limb_pointer_type>(v.my_data.data()), // NOLINT(cppcoreguidelines-pro-type-const-cast)
                                           prec_elems_for_multiply);

        // Handle a potential carry.
        if(result[static_cast<std::size_t>(UINT8_C(0))] != static_cast<limb_type>(UINT8_C(0))) // NOLINT(cppcoreguidelines-pro-bounds-pointer-arithmetic)
        {
          my_exp = static_cast<exponent_type>(my_exp + static_cast<exponent_type>(decwide_t_elem_digits10));

          // Shift the result of the multiplication one element to the right.
          std::copy(result,
                    result + static_cast<std::ptrdiff_t>(prec_elems_for_multiply), // NOLINT(cppcoreguidelines-pro-bounds-pointer-arithmetic)
                    my_data.begin());
        }
        else
        {
          const auto kara_limit = (std::min)(decwide_t_elem_number, decwide_t_elems_for_kara);

          const auto copy_limit = static_cast<std::ptrdiff_t>((std::min)(prec_elems_for_multiply, kara_limit));

          std::copy(result +                             static_cast<std::ptrdiff_t>(INT8_C(1)),               // NOLINT(cppcoreguidelines-pro-bounds-pointer-arithmetic)
                    result + static_cast<std::ptrdiff_t>(static_cast<std::ptrdiff_t>(INT8_C(1)) + copy_limit), // NOLINT(cppcoreguidelines-pro-bounds-pointer-arithmetic)
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
                static_cast<typename kara_mul_pool_type::size_type>(kara_elems_for_multiply)
              * static_cast<typename kara_mul_pool_type::size_type>(UINT8_C(8))
            )
          );
        #endif

        limb_type* u_local = my_kara_mul_pool.data() + static_cast<std::size_t>(static_cast<std::size_t>(kara_elems_for_multiply) * static_cast<std::size_t>(UINT8_C(0))); // NOLINT(cppcoreguidelines-pro-bounds-pointer-arithmetic)
        limb_type* v_local = my_kara_mul_pool.data() + static_cast<std::size_t>(static_cast<std::size_t>(kara_elems_for_multiply) * static_cast<std::size_t>(UINT8_C(1))); // NOLINT(cppcoreguidelines-pro-bounds-pointer-arithmetic)
        limb_type* result  = my_kara_mul_pool.data() + static_cast<std::size_t>(static_cast<std::size_t>(kara_elems_for_multiply) * static_cast<std::size_t>(UINT8_C(2))); // NOLINT(cppcoreguidelines-pro-bounds-pointer-arithmetic)
        limb_type* t       = my_kara_mul_pool.data() + static_cast<std::size_t>(static_cast<std::size_t>(kara_elems_for_multiply) * static_cast<std::size_t>(UINT8_C(4))); // NOLINT(cppcoreguidelines-pro-bounds-pointer-arithmetic)

        std::copy(my_data.cbegin(), my_data.cbegin() + prec_elems_for_multiply, u_local);
        std::copy(v.my_data.cbegin(), v.my_data.cbegin() + static_cast<std::ptrdiff_t>(prec_elems_for_multiply), v_local);

        std::fill(u_local + prec_elems_for_multiply, u_local + kara_elems_for_multiply, static_cast<limb_type>(UINT8_C(0))); // NOLINT(cppcoreguidelines-pro-bounds-pointer-arithmetic)
        std::fill(v_local + prec_elems_for_multiply, v_local + kara_elems_for_multiply, static_cast<limb_type>(UINT8_C(0))); // NOLINT(cppcoreguidelines-pro-bounds-pointer-arithmetic)

        detail::eval_multiply_kara_n_by_n_to_2n(result,
                                                u_local,
                                                v_local,
                                                kara_elems_for_multiply,
                                                t);

        // Handle a potential carry.
        if(result[static_cast<std::size_t>(UINT8_C(0))] != static_cast<limb_type>(UINT8_C(0))) // NOLINT(cppcoreguidelines-pro-bounds-pointer-arithmetic)
        {
          my_exp = static_cast<exponent_type>(my_exp + static_cast<exponent_type>(decwide_t_elem_digits10));

          // Shift the result of the multiplication one element to the right.
          std::copy(result,
                    result + static_cast<std::ptrdiff_t>(prec_elems_for_multiply), // NOLINT(cppcoreguidelines-pro-bounds-pointer-arithmetic)
                    my_data.begin());
        }
        else
        {
          const auto fft_limit = (std::min)(decwide_t_elem_number, decwide_t_elems_for_fft);

          const auto copy_limit = static_cast<std::ptrdiff_t>((std::min)(prec_elems_for_multiply, fft_limit));

          std::copy(result +                             static_cast<std::ptrdiff_t>(INT8_C(1)),               // NOLINT(cppcoreguidelines-pro-bounds-pointer-arithmetic)
                    result + static_cast<std::ptrdiff_t>(static_cast<std::ptrdiff_t>(INT8_C(1)) + copy_limit), // NOLINT(cppcoreguidelines-pro-bounds-pointer-arithmetic)
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
                static_cast<typename school_mul_pool_type::size_type>(prec_elems_for_multiply)
              * static_cast<typename school_mul_pool_type::size_type>(UINT8_C(2))
            )
          );

        #endif

        limb_type* result = my_school_mul_pool.data();

        using const_limb_pointer_type = typename std::add_const<limb_type*>::type;

        detail::eval_multiply_n_by_n_to_2n(result,
                                           const_cast<const_limb_pointer_type>(my_data.data()),   // NOLINT(cppcoreguidelines-pro-type-const-cast)
                                           const_cast<const_limb_pointer_type>(v.my_data.data()), // NOLINT(cppcoreguidelines-pro-type-const-cast)
                                           prec_elems_for_multiply);

        // Handle a potential carry.
        if(result[static_cast<std::size_t>(UINT8_C(0))] != static_cast<limb_type>(UINT8_C(0))) // NOLINT(cppcoreguidelines-pro-bounds-pointer-arithmetic)
        {
          my_exp += static_cast<exponent_type>(decwide_t_elem_digits10);

          // Shift the result of the multiplication one element to the right.
          std::copy(result,
                    result + static_cast<std::ptrdiff_t>(prec_elems_for_multiply), // NOLINT(cppcoreguidelines-pro-bounds-pointer-arithmetic)
                    my_data.begin());
        }
        else
        {
          const auto kara_limit = (std::min)(decwide_t_elem_number, decwide_t_elems_for_kara);

          const auto copy_limit = static_cast<std::ptrdiff_t>((std::min)(prec_elems_for_multiply, kara_limit));

          std::copy(result +                             static_cast<std::ptrdiff_t>(INT8_C(1)),               // NOLINT(cppcoreguidelines-pro-bounds-pointer-arithmetic)
                    result + static_cast<std::ptrdiff_t>(static_cast<std::ptrdiff_t>(INT8_C(1)) + copy_limit), // NOLINT(cppcoreguidelines-pro-bounds-pointer-arithmetic)
                    my_data.begin());
        }
      }
      else if(   (prec_elems_for_multiply >= decwide_t_elems_for_kara)
              && (prec_elems_for_multiply <  decwide_t_elems_for_fft))
      {
        // Use Karatsuba multiplication.

        // Use Sloane's A029750: The so-called 7-smooth numbers having the form 2^k times 1, 3, 5 or 7.
        const auto kara_elems_for_multiply =
          detail::a029750::a029750_as_runtime_value(static_cast<std::uint32_t>(prec_elems_for_multiply));

        #if !defined(WIDE_DECIMAL_DISABLE_DYNAMIC_MEMORY_ALLOCATION)
        using kara_mul_pool_type = util::dynamic_array<limb_type>;

        auto my_kara_mul_pool =
          kara_mul_pool_type
          (
            static_cast<typename kara_mul_pool_type::size_type>
            (
                static_cast<typename kara_mul_pool_type::size_type>(kara_elems_for_multiply)
              * static_cast<typename kara_mul_pool_type::size_type>(UINT8_C(8))
            )
          );
        #endif

        limb_type* u_local = my_kara_mul_pool.data() + static_cast<std::size_t>(static_cast<std::size_t>(kara_elems_for_multiply) * static_cast<std::size_t>(UINT8_C(0))); // NOLINT(cppcoreguidelines-pro-bounds-pointer-arithmetic)
        limb_type* v_local = my_kara_mul_pool.data() + static_cast<std::size_t>(static_cast<std::size_t>(kara_elems_for_multiply) * static_cast<std::size_t>(UINT8_C(1))); // NOLINT(cppcoreguidelines-pro-bounds-pointer-arithmetic)
        limb_type* result  = my_kara_mul_pool.data() + static_cast<std::size_t>(static_cast<std::size_t>(kara_elems_for_multiply) * static_cast<std::size_t>(UINT8_C(2))); // NOLINT(cppcoreguidelines-pro-bounds-pointer-arithmetic)
        limb_type* t       = my_kara_mul_pool.data() + static_cast<std::size_t>(static_cast<std::size_t>(kara_elems_for_multiply) * static_cast<std::size_t>(UINT8_C(4))); // NOLINT(cppcoreguidelines-pro-bounds-pointer-arithmetic)

        std::copy(my_data.cbegin(), my_data.cbegin() + prec_elems_for_multiply, u_local);
        std::copy(v.my_data.cbegin(), v.my_data.cbegin() + static_cast<std::ptrdiff_t>(prec_elems_for_multiply), v_local);

        std::fill(u_local + prec_elems_for_multiply, u_local + kara_elems_for_multiply, static_cast<limb_type>(UINT8_C(0))); // NOLINT(cppcoreguidelines-pro-bounds-pointer-arithmetic)
        std::fill(v_local + prec_elems_for_multiply, v_local + kara_elems_for_multiply, static_cast<limb_type>(UINT8_C(0))); // NOLINT(cppcoreguidelines-pro-bounds-pointer-arithmetic)

        detail::eval_multiply_kara_n_by_n_to_2n(result,
                                                u_local,
                                                v_local,
                                                kara_elems_for_multiply,
                                                t);

        // Handle a potential carry.
        if(result[static_cast<std::size_t>(UINT8_C(0))] != static_cast<limb_type>(UINT8_C(0))) // NOLINT(cppcoreguidelines-pro-bounds-pointer-arithmetic)
        {
          my_exp = static_cast<exponent_type>(my_exp + static_cast<exponent_type>(decwide_t_elem_digits10));

          // Shift the result of the multiplication one element to the right.
          std::copy(result,
                    result + static_cast<std::ptrdiff_t>(prec_elems_for_multiply), // NOLINT(cppcoreguidelines-pro-bounds-pointer-arithmetic)
                    my_data.begin());
        }
        else
        {
          const auto fft_limit = (std::min)(decwide_t_elem_number, decwide_t_elems_for_fft);

          const auto copy_limit = static_cast<std::ptrdiff_t>((std::min)(prec_elems_for_multiply, fft_limit));

          std::copy(result +                             static_cast<std::ptrdiff_t>(INT8_C(1)),               // NOLINT(cppcoreguidelines-pro-bounds-pointer-arithmetic)
                    result + static_cast<std::ptrdiff_t>(static_cast<std::ptrdiff_t>(INT8_C(1)) + copy_limit), // NOLINT(cppcoreguidelines-pro-bounds-pointer-arithmetic)
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

        using const_limb_pointer_type = typename std::add_const<limb_type*>::type;

        detail::mul_loop_fft(my_data.data(),
                             const_cast<const_limb_pointer_type>(  my_data.data()), // NOLINT(cppcoreguidelines-pro-type-const-cast)
                             const_cast<const_limb_pointer_type>(v.my_data.data()), // NOLINT(cppcoreguidelines-pro-type-const-cast)
                             my_af_fft_mul_pool.data(),
                             my_bf_fft_mul_pool.data(),
                             static_cast<std::int32_t>(prec_elems_for_multiply),
                             n_fft);

        if(my_data.front() != static_cast<limb_type>(UINT8_C(0)))
        {
          // Adjust the exponent because of the internal scaling of the FFT multiplication.
          my_exp += static_cast<exponent_type>(decwide_t_elem_digits10);
        }
        else
        {
          const auto copy_limit = static_cast<std::ptrdiff_t>((std::min)(prec_elems_for_multiply, decwide_t_elem_number));

          std::copy(my_data.cbegin() +                             static_cast<std::ptrdiff_t>(INT8_C(1)),               // NOLINT(cppcoreguidelines-pro-bounds-pointer-arithmetic)
                    my_data.cbegin() + static_cast<std::ptrdiff_t>(static_cast<std::ptrdiff_t>(INT8_C(1)) + copy_limit), // NOLINT(cppcoreguidelines-pro-bounds-pointer-arithmetic)
                    my_data.begin());

          my_data.back() = static_cast<limb_type>(UINT8_C(0));
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

        auto digits_limb_0 = static_cast<std::int32_t>(INT8_C(0));

        auto tmp_limb_0 = my_data[static_cast<local_size_type>(UINT8_C(0))];

        // Manually count the number of base-10 digits on the zero'th limb.
        while(tmp_limb_0 > static_cast<local_limb_type>(UINT8_C(0))) // NOLINT(altera-id-dependent-backward-branch)
        {
          tmp_limb_0 = static_cast<local_limb_type>(tmp_limb_0 / static_cast<local_limb_type>(UINT8_C(10))); // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)

          ++digits_limb_0;
        }

        const auto digits_limb_1_to_n = static_cast<std::int32_t>(decwide_t_max_digits10 - digits_limb_0);

        const auto digits_limb_1_to_n_elem_digits10_div =
          static_cast<std::int32_t>
          (
            digits_limb_1_to_n / decwide_t_elem_digits10
          );

        const auto digits_limb_1_to_n_elem_digits10_mod =
          static_cast<std::int32_t>
          (
            digits_limb_1_to_n % decwide_t_elem_digits10
          );

        // Find the index of the element that contains the least-significant base-10 digit.
        auto least_digit_idx =
          static_cast<std::int32_t>
          (
              digits_limb_1_to_n_elem_digits10_div
            + static_cast<std::int32_t>
              (
                (digits_limb_1_to_n_elem_digits10_mod != static_cast<std::int32_t>(INT8_C(0)))
                  ? static_cast<std::int32_t>(INT8_C(1))
                  : static_cast<std::int32_t>(INT8_C(0))
              )
          );

        // Set the index of the element that contains the rounding base-10 digit.
        const auto round_digit_idx =
          static_cast<std::int32_t>
          (
            (digits_limb_1_to_n_elem_digits10_mod != static_cast<std::int32_t>(INT8_C(0)))
              ?                           least_digit_idx
              : static_cast<std::int32_t>(least_digit_idx + static_cast<std::int32_t>(INT8_C(1)))
          );

        // Find the base-10 order (position) of the least-significant base-10 digit.
        const auto least_digit_pos =
          static_cast<std::int32_t>
          (
            (digits_limb_1_to_n_elem_digits10_mod != static_cast<std::int32_t>(INT8_C(0)))
              ? static_cast<std::int32_t>
                (
                    static_cast<std::int32_t>
                    (
                        decwide_t_elem_digits10
                      - digits_limb_1_to_n_elem_digits10_mod
                    )
                )
              : static_cast<std::int32_t>(INT8_C(0))
          );

        // Find the base-10 order (position) of the rounding base-10 digit.
        const auto round_digit_pos =
          static_cast<std::int32_t>
          (
            (least_digit_pos != static_cast<std::int32_t>(INT8_C(0)))
              ? static_cast<std::int32_t>(least_digit_pos         - static_cast<std::int32_t>(INT8_C(1)))
              : static_cast<std::int32_t>(decwide_t_elem_digits10 - static_cast<std::int32_t>(INT8_C(1)))
          );

        using digit_helper_struct_type = detail::decwide_t_helper<decwide_t_elem_digits10, limb_type>;

        // Get the value of the rounding base-10 digit.
        const auto round_digit_value =
          digit_helper_struct_type::digit_at_pos_in_limb
          (
             my_data[static_cast<local_size_type>(round_digit_idx)],
             static_cast<unsigned>(round_digit_pos)
          );

        const auto least_digit_p10 =
          detail::pow10_maker_as_runtime_value(static_cast<std::uint32_t>(least_digit_pos));

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
          const auto least_digit_idx_plus_one = static_cast<std::int32_t>(least_digit_idx + static_cast<std::int32_t>(INT8_C(1)));

          const auto do_clear_lower_limbs =
            (least_digit_idx_plus_one < static_cast<std::int32_t>(my_data.size() - static_cast<std::size_t>(UINT8_C(1))));

          if(do_clear_lower_limbs)
          {
            std::fill(my_data.begin() + static_cast<local_size_type>(least_digit_idx_plus_one),
                      my_data.end(),
                      static_cast<local_limb_type>(UINT8_C(0)));
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
              ? static_cast<std::uint_fast8_t>(UINT8_C(1))
              : static_cast<std::uint_fast8_t>(UINT8_C(0)));

          // Propagate the carry into the limbs of higher significance as needed.
          if(carry_out != static_cast<std::uint_fast8_t>(UINT8_C(0)))
          {
            my_data[static_cast<local_size_type>(least_digit_idx)] =
              static_cast<limb_type>
              (
                  my_data[static_cast<local_size_type>(least_digit_idx)]
                - static_cast<limb_type>(decwide_t_elem_mask)
              );

            while(   (--least_digit_idx >= static_cast<std::int32_t>(0)) // NOLINT(altera-id-dependent-backward-branch)
                  && (carry_out != static_cast<std::uint_fast8_t>(UINT8_C(0))))
            {
              const auto tt =
                static_cast<local_limb_type>
                (
                    my_data[static_cast<local_size_type>(least_digit_idx)]
                  + static_cast<local_limb_type>(carry_out)
                );

              carry_out = ((tt >= decwide_t_elem_mask) ? static_cast<std::uint_fast8_t>(UINT8_C(1))
                                                       : static_cast<std::uint_fast8_t>(UINT8_C(0)));

              const auto has_carry = (carry_out != static_cast<std::uint_fast8_t>(UINT8_C(0)));

              my_data[static_cast<local_size_type>(least_digit_idx)] =
                static_cast<local_limb_type>
                (
                    tt
                  - static_cast<local_limb_type>
                    (
                      has_carry ? decwide_t_elem_mask : static_cast<local_limb_type>(UINT8_C(0))
                    )
                );
            }

            if(   (least_digit_idx < static_cast<std::int32_t>(INT8_C(0)))
               && (carry_out != static_cast<std::uint_fast8_t>(UINT8_C(0))))
            {
              // In rare cases, propagation of the carry reaches the zero'th limb
              // of highest significance, and we must shift the data, create a new limb
              // with the carry value of 1 and adjust the exponent accordingly.
              std::copy_backward(my_data.cbegin(),
                                 my_data.cend() - static_cast<std::ptrdiff_t>(INT8_C(1)),
                                 my_data.end());

              my_data[static_cast<local_size_type>(UINT8_C(0))] = carry_out;

              my_exp = static_cast<exponent_type>(my_exp + static_cast<exponent_type>(decwide_t_elem_digits10));
            }
          }
        }
      }
    }

    #if !defined(WIDE_DECIMAL_DISABLE_CONSTRUCT_FROM_STRING)
    static auto pos_of_e_func(const std::string& local_str) -> std::string::size_type
    {
      auto pos_of_e = std::string::npos;

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

    auto rd_string(const char* s) -> bool // NOLINT(readability-function-cognitive-complexity)
    {
      std::string str(s);

      // Get a possible exponent and remove it.
      my_exp = static_cast<exponent_type>(INT8_C(0));

      auto pos = pos_of_e_func(str);

      if(pos != std::string::npos)
      {
        // Remove the exponent part from the string.
        static_assert(std::numeric_limits<signed long long>::digits >= std::numeric_limits<exponent_type>::digits, // NOLINT(google-runtime-int)
                      "Error: Type long long is not wide enough to hold result of type exponent_type");

        auto ptr_end = static_cast<char*>(nullptr); // NOLINT(cppcoreguidelines-pro-type-vararg,hicpp-vararg,cppcoreguidelines-init-variables,llvm-qualified-auto,readability-qualified-auto)

        my_exp =
          static_cast<exponent_type>
          (
            std::strtoll(static_cast<const char*>(str.c_str() + static_cast<std::size_t>(pos + static_cast<std::string::size_type>(UINT8_C(1)))), &ptr_end, 10) // NOLINT(cppcoreguidelines-pro-bounds-pointer-arithmetic,cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
          );

        str = str.substr(static_cast<std::size_t>(UINT8_C(0)), pos);
      }

      // Get a possible +/- sign and remove it.

      if((pos = str.find('-')) != std::string::npos) // NOLINT(bugprone-assignment-in-if-condition)
      {
        my_neg = true;

        str.erase(pos, static_cast<std::uint_fast32_t>(UINT8_C(1)));
      }
      else
      {
        my_neg = false;
      }

      if((pos = str.find('+')) != std::string::npos) // NOLINT(bugprone-assignment-in-if-condition)
      {
        str.erase(pos, static_cast<std::uint_fast32_t>(UINT8_C(1)));
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
          static_cast<void>
          (
            operator=(zero<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>())
          );

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
              - std::distance(str.crbegin(), rit_non_zero)
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
                 (str.size()  == static_cast<std::size_t>(UINT8_C(1)))
              && (str.front() == '.')
            );

          if(input_is_identically_zero)
          {
            static_cast<void>
            (
              operator=(zero<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>())
            );

            return true;
          }
        }

        // Remove leading significant zeros just after the
        // decimal point and adjust the exponent accordingly.

        // Note that the while-loop operates only on strings
        // of the form ".000abcd..." and peels away the trailing
        // zeros following the decimal point.

        if(str.at(static_cast<std::size_t>(UINT8_C(0))) == '.')
        {
          const auto it_non_zero =
            std::find_if(str.cbegin() + static_cast<std::ptrdiff_t>(INT8_C(1)),
                         str.cend(),
                         [](const char& c) // NOLINT(modernize-use-trailing-return-type)
                         {
                           return (c != '0');
                         });

          const auto delta_exp =
            static_cast<std::uint_fast32_t>
            (
              (str.at(static_cast<std::size_t>(UINT8_C(1))) == '0')
                ? static_cast<std::uint_fast32_t>(std::distance((str.cbegin() + static_cast<std::ptrdiff_t>(INT8_C(1))), it_non_zero))
                : static_cast<std::uint_fast32_t>(UINT8_C(0))
            );

          // Bring one single digit into the mantissa and adjust exponent accordingly.
          str.erase
          (
            static_cast<std::string::size_type>(UINT8_C(0U)),
            static_cast<std::string::size_type>(std::distance(str.cbegin(), it_non_zero))
          );

          str.insert(static_cast<std::size_t>(UINT8_C(1)), static_cast<std::size_t>(UINT8_C(1)), '.');

          my_exp =
            static_cast<exponent_type>
            (
                my_exp
              - static_cast<exponent_type>
                (
                  static_cast<exponent_type>(delta_exp) + static_cast<exponent_type>(INT8_C(1))
                )
            );
        }
      }
      else
      {
        // Input string has no decimal point: Append decimal point.
        str.append(static_cast<std::size_t>(UINT8_C(1)), '.');
      }

      // Shift the decimal point such that the exponent
      // is an even multiple of decwide_t_elem_digits10.
      auto n_shift = static_cast<std::ptrdiff_t>(INT8_C(0));

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

        if(n_exp_mod != static_cast<exponent_type>(INT8_C(0)))
        {
          n_shift =
            static_cast<std::ptrdiff_t>
            (
              (my_exp < static_cast<exponent_type>(INT8_C(0)))
                      ? static_cast<std::ptrdiff_t>(n_exp_rem + static_cast<std::ptrdiff_t>(decwide_t_elem_digits10))
                      : static_cast<std::ptrdiff_t>(n_exp_rem)
            );
        }
      }

      // Make sure that there are enough digits for the decimal point shift.
      pos = str.find('.');

      auto pos_plus_one = static_cast<std::ptrdiff_t>(pos + static_cast<std::string::size_type>(UINT8_C(1)));

      if((static_cast<std::ptrdiff_t>(str.length()) - pos_plus_one) < n_shift)
      {
        const auto cnt =
          static_cast<std::ptrdiff_t>
          (
              n_shift
            - static_cast<std::ptrdiff_t>
              (
                static_cast<std::ptrdiff_t>(str.length()) - pos_plus_one
              )
          );

        str.append(static_cast<std::size_t>(cnt), '0');
      }

      // Perform the shift of the decimal point.
      if(n_shift != static_cast<std::ptrdiff_t>(INT8_C(0)))
      {
        str.insert(static_cast<std::size_t>(pos_plus_one + n_shift), static_cast<std::size_t>(UINT8_C(1)), '.');

        str.erase(pos, static_cast<std::ptrdiff_t>(INT8_C(1)));

        my_exp = static_cast<exponent_type>(my_exp - static_cast<exponent_type>(n_shift));
      }

      // Reduce the size of the mantissa to <= decwide_t_elem_digits10.
      pos          = str.find('.');
      pos_plus_one = static_cast<std::ptrdiff_t>(pos + static_cast<std::size_t>(UINT8_C(1)));

      if(pos > static_cast<std::ptrdiff_t>(decwide_t_elem_digits10))
      {
        const auto n_pos         = static_cast<std::int32_t>(pos);
        const auto n_rem_is_zero = static_cast<std::int32_t>((static_cast<std::int32_t>(n_pos % decwide_t_elem_digits10) == static_cast<std::int32_t>(INT8_C(0))) ? static_cast<std::int32_t>(INT8_C(1)) : static_cast<std::int32_t>(0));
        const auto n             = static_cast<std::int32_t> (static_cast<std::int32_t>(n_pos / decwide_t_elem_digits10) - n_rem_is_zero);

        const auto pos_to_insert =
          static_cast<std::size_t>
          (
              static_cast<std::size_t>(n_pos)
            - static_cast<std::size_t>(static_cast<std::size_t>(n) * static_cast<std::size_t>(decwide_t_elem_digits10))
          );

        str.insert(pos_to_insert, static_cast<std::size_t>(UINT8_C(1)), '.');

        str.erase(static_cast<std::string::size_type>(pos_plus_one), static_cast<std::uint_fast32_t>(UINT8_C(1)));

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
      pos_plus_one = static_cast<std::ptrdiff_t>(pos + static_cast<std::size_t>(UINT8_C(1)));

      const auto n_dec = static_cast<std::int32_t> (static_cast<std::int32_t>(str.length() - static_cast<std::size_t>(UINT8_C(1))) - static_cast<std::int32_t>(pos));
      const auto n_rem = static_cast<std::int32_t> (n_dec % decwide_t_elem_digits10);
      const auto n_cnt = static_cast<std::int32_t>((n_rem != static_cast<std::int32_t>(0)) ? static_cast<std::int32_t>(decwide_t_elem_digits10 - n_rem)
                                                                                           : static_cast<std::int32_t>(INT8_C(0)));

      if(n_cnt != static_cast<std::int32_t>(INT8_C(0)))
      {
        str.append(static_cast<std::size_t>(n_cnt), '0');
      }

      // Truncate decimal part if it is too long.
      constexpr auto max_dec =
        static_cast<std::ptrdiff_t>
        (
            static_cast<std::ptrdiff_t>(decwide_t_elem_number - static_cast<std::int32_t>(INT8_C(1)))
          * static_cast<std::ptrdiff_t>(decwide_t_elem_digits10)
        );

      if(static_cast<std::ptrdiff_t>(str.length() - pos) > max_dec)
      {
        str = str.substr(static_cast<std::string::size_type>(UINT8_C(0)),
                         static_cast<std::string::size_type>(pos_plus_one + max_dec));
      }

      // Now the input string has the standard decwide_t
      // input form as described in the comment above.

      // Set all the data elements to 0.
      std::fill(my_data.begin(), my_data.end(), static_cast<limb_type>(UINT8_C(0)));

      // Extract the data.

      using local_size_type = typename representation_type::size_type;

      {
        static_assert(std::numeric_limits<unsigned long>::digits >= std::numeric_limits<limb_type>::digits, // NOLINT(google-runtime-int)
                      "Error: Type unsigned long is not wide enough to hold result of type limb_type");

        auto ptr_end = static_cast<char*>(nullptr); // NOLINT(cppcoreguidelines-pro-type-vararg,hicpp-vararg,llvm-qualified-auto,readability-qualified-auto)

        // First get the digits to the left of the decimal point...

        const auto str_zeroth_limb = str.substr(static_cast<std::ptrdiff_t>(INT8_C(0)), pos);

        my_data[static_cast<local_size_type>(UINT8_C(0))] =
          static_cast<limb_type>
          (
            std::strtoul(str_zeroth_limb.c_str(), &ptr_end, static_cast<int>(INT8_C(10))) // NOLINT(,cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
          );
      }

      // ...then get the remaining digits to the right of the decimal point.
      const auto i_end =
        static_cast<std::string::difference_type>
        (
            static_cast<std::string::difference_type>(static_cast<std::string::difference_type>(str.length()) - pos_plus_one)
          / static_cast<std::string::difference_type>(decwide_t_elem_digits10)
        );

      for(auto i = static_cast<std::string::difference_type>(INT8_C(0)); i < i_end; ++i) // NOLINT(altera-id-dependent-backward-branch)
      {
        const auto idigits =
          static_cast<std::string::difference_type>
          (
              static_cast<std::string::difference_type>(i)
            * static_cast<std::string::difference_type>(decwide_t_elem_digits10)
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
              static_cast<std::string::difference_type>(i)
            + static_cast<std::string::difference_type>(INT8_C(1))
          );

        static_assert(std::numeric_limits<unsigned long>::digits >= std::numeric_limits<limb_type>::digits, // NOLINT(google-runtime-int)
                      "Error: Type unsigned long is not wide enough to hold result of type limb_type");

        auto ptr_end = static_cast<char*>(nullptr); // NOLINT(cppcoreguidelines-pro-type-vararg,hicpp-vararg,llvm-qualified-auto,readability-qualified-auto)

        my_data[i1] =
          static_cast<limb_type>
          (
            std::strtoul(str_next_limb.c_str(), &ptr_end, static_cast<int>(INT8_C(10)))
          );
      }

      return true;
    }
    #endif //!(WIDE_DECIMAL_DISABLE_CONSTRUCT_FROM_STRING)

    static auto get_output_digits(const decwide_t&         x,
                                        char*              it_dst,
                                  const std::uint_fast32_t number_of_elements,
                                        std::size_t*       count_retrieved,
                                  const bool               include_decimal_point = false) -> void
    {
      // Extract the required digits from decwide_t, including
      // digits both before as well as after the decimal point.

      // Include the decimal point in the retrieved characters
      // if requested. Do not, however, count an inserted
      // decimal point as one of the retrieved characters.

      using data_elem_array_type =
        std::array<char, static_cast<std::size_t>(decwide_t_elem_digits10)>;

      data_elem_array_type data_elem_buf { };

      // Obtain the digits in the first limb.
      auto it_rep = x.crepresentation().cbegin(); // NOLINT(llvm-qualified-auto,readability-qualified-auto)

      const char* p_end = util::baselexical_cast(*it_rep, data_elem_buf.data(), data_elem_buf.data() + data_elem_buf.size()); // NOLINT(cppcoreguidelines-pro-type-vararg,hicpp-vararg)

      ++it_rep;

      *count_retrieved =
        static_cast<std::size_t>
        (
          std::distance(static_cast<const char*>(data_elem_buf.data()), p_end)
        );

      it_dst = std::copy(data_elem_buf.cbegin(),
                         data_elem_buf.cbegin() + *count_retrieved,
                         it_dst);

      // Include the decimal point if requested.
      if(include_decimal_point)
      {
        *it_dst++ = '.'; // NOLINT(cppcoreguidelines-pro-bounds-pointer-arithmetic)
      }

      data_elem_array_type data_elem_array { };

      // Extract the digits following the decimal point from decwide_t,
      // beginning with the data element having index 1.
      while(it_rep != (x.crepresentation().cbegin() + static_cast<std::size_t>(number_of_elements))) // NOLINT(altera-id-dependent-backward-branch)
      {
        p_end = util::baselexical_cast(*it_rep, data_elem_buf.data(), data_elem_buf.data() + data_elem_buf.size());

        ++it_rep;

        auto rit = std::copy(static_cast<std::reverse_iterator<const char*>>(p_end),
                             static_cast<std::reverse_iterator<const char*>>(static_cast<const char*>(data_elem_buf.data())),
                             data_elem_array.rbegin());

        std::fill(rit, data_elem_array.rend(), '0');

        it_dst = std::copy(data_elem_array.cbegin(),
                           data_elem_array.cend(),
                           it_dst);

        *count_retrieved =
          static_cast<std::size_t>
          (
              *count_retrieved
            + static_cast<std::size_t>(decwide_t_elem_digits10)
          );
      }
    }

    #if !defined(WIDE_DECIMAL_DISABLE_IOSTREAM)
    static auto get_output_string(const decwide_t&         x,
                                        std::string&       str, // NOLINT(google-runtime-references)
                                        exponent_type&     the_exp,
                                  const std::uint_fast32_t number_of_digits) -> void
    {
      // Determine the number of elements needed to provide the requested digits from decwide_t.
      const std::uint_fast32_t number_of_elements =
        (std::min)(static_cast<std::uint_fast32_t>(static_cast<std::uint_fast32_t>(number_of_digits / static_cast<std::uint_fast32_t>(decwide_t_elem_digits10)) + static_cast<std::uint_fast32_t>(UINT8_C(2))),
                   static_cast<std::uint_fast32_t>(decwide_t_elem_number));

      // Extract the remaining digits from decwide_t after the decimal point.

      util::dynamic_array<char>
        str_tmp_mem
        (
          static_cast<std::size_t>
          (
              static_cast<std::size_t>(number_of_elements)
            * static_cast<std::size_t>(decwide_t_elem_digits10)
          ),
          ' '
        );

      auto count_retrieved = static_cast<std::size_t>(UINT8_C(0));

      get_output_digits(x,
                        str_tmp_mem.data(),
                        number_of_elements,
                        &count_retrieved);

      str.resize(count_retrieved);

      std::copy(str_tmp_mem.cbegin(),
                str_tmp_mem.cbegin() + count_retrieved,
                str.begin());

      // Cut the output to the size of the precision.
      if(str.length() > number_of_digits)
      {
        // Get the digit immediately following the last digit and use this for rounding.
        const auto round =
          static_cast<std::uint32_t>
          (
            static_cast<std::uint32_t>(str.at(number_of_digits)) - static_cast<std::uint32_t>('0')
          );

        // Truncate the string
        str = str.substr(static_cast<std::uint_fast32_t>(UINT8_C(0)), number_of_digits);

        if(round >= static_cast<std::uint32_t>(UINT8_C(5)))
        {
          auto ix = static_cast<std::string::size_type>(str.length() - static_cast<std::size_t>(UINT8_C(1)));

          // Every trailing 9 must be rounded up.
          while(   (ix != static_cast<std::size_t>(UINT8_C(0))) // NOLINT(altera-id-dependent-backward-branch)
                && (static_cast<int>(static_cast<int>(str.at(ix)) - static_cast<int>('0')) == static_cast<int>(INT8_C(9))))
          {
            str.at(ix) = '0';

            --ix;
          }

          if(ix == static_cast<std::size_t>(UINT8_C(0)))
          {
            // There were nothing but trailing nines.
            const auto has_nothing_but_trailing_nines =
              static_cast<int>(static_cast<int>(str.at(ix)) - static_cast<int>(INT8_C(0x30))) == static_cast<int>(INT8_C(9));

            if(has_nothing_but_trailing_nines)
            {
              // Increment up to the next order and adjust exponent.
              ++str[ix] = '1';

              ++the_exp;
            }
            else
            {
              // Round up this digit.
              ++str[ix];
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

    static auto wr_string_scientific(      std::string&       str, // NOLINT(google-runtime-references)
                                     const exponent_type      the_exp,
                                     const std::uint_fast32_t os_precision,
                                     const bool               my_showpoint,
                                     const bool               my_uppercase,
                                     const bool               trim_trailing_zeros = false) -> void
    {
      if(os_precision > static_cast<std::uint_fast32_t>(str.length() - static_cast<std::size_t>(UINT8_C(1))))
      {
        // Zero-extend the string to the given precision if necessary.
        const auto n_pad =
          static_cast<std::uint_fast32_t>
          (
              os_precision
            - static_cast<std::uint_fast32_t>(str.length() - static_cast<std::size_t>(UINT8_C(1)))
          );

        str.insert(str.end(), static_cast<std::size_t>(n_pad), '0');
      }

      // Insert the decimal point.
      str.insert(static_cast<std::size_t>(UINT8_C(1)), static_cast<std::size_t>(UINT8_C(1)), '.');

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

        if(rit_non_zero != str.crbegin())
        {
          const auto ofs =
            static_cast<std::ptrdiff_t>
            (
                static_cast<std::ptrdiff_t>(str.length())
              - std::distance(str.crbegin(), rit_non_zero)
            );

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
        if(str.back() == '.')
        {
          str.pop_back();
        }
      }

      // Append the exponent in uppercase or lower case, including its sign.
      const auto b_exp_is_neg = (the_exp < static_cast<exponent_type>(INT8_C(0)));

      const auto u_exp =
        static_cast<std::uint64_t>
        (
          (!b_exp_is_neg) ? the_exp : static_cast<exponent_type>(-the_exp)
        );

      str.push_back(my_uppercase ? 'E' : 'e');

      str.push_back((!b_exp_is_neg) ? '+' : '-');

      std::array<char, static_cast<std::size_t>(UINT8_C(20))> ptr_str = {{ '\0' }}; // NOLINT(,cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)

      const char* ptr_end = util::baselexical_cast(u_exp, ptr_str.data(), ptr_str.data() + ptr_str.size()); // NOLINT(cppcoreguidelines-pro-type-vararg,hicpp-vararg,llvm-qualified-auto,readability-qualified-auto)

      const auto str_exp_len = static_cast<std::size_t>(std::distance(static_cast<const char*>(ptr_str.data()), ptr_end));

      auto str_exp = std::string(ptr_str.data(), ptr_str.data() + str_exp_len);

      // Format the exponent string to have a width that is an even multiple of three.
      const auto str_exp_len_mod3 = static_cast<std::size_t>(str_exp_len % static_cast<std::size_t>(UINT8_C(3)));

      const auto exp_has_mod3 = (str_exp_len_mod3 != static_cast<std::size_t>(UINT8_C(0)));

      const auto str_exp_len_pad =
        static_cast<std::size_t>
        (
          exp_has_mod3 ? static_cast<std::size_t>(static_cast<std::size_t>(UINT8_C(3)) - str_exp_len_mod3)
                       : static_cast<std::size_t>(UINT8_C(0))
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

      if(the_exp < static_cast<exponent_type>(INT8_C(0)))
      {
        // The number is less than one in magnitude.

        const auto zero_insert_length =
          detail::negate
          (
            static_cast<exponent_type>
            (
                static_cast<exponent_type>(the_exp)
              + static_cast<exponent_type>(INT8_C(1))
            )
          );

        const auto n_pad =
          static_cast<exponent_type>
          (
              static_cast<exponent_type>(os_precision)
            - static_cast<exponent_type>(static_cast<exponent_type>(str.length()) + zero_insert_length)
          );

        // Insert the decimal point using "0." as well as the needed number
        // of leading zeros.

        str.insert(static_cast<std::size_t>(UINT8_C(0)), static_cast<std::size_t>(zero_insert_length), '0');
        str.insert(static_cast<std::size_t>(UINT8_C(0)), static_cast<std::size_t>(UINT8_C(1)),         '.');
        str.insert(static_cast<std::size_t>(UINT8_C(0)), static_cast<std::size_t>(UINT8_C(1)),         '0');

        // Zero-extend the string to the given precision if necessary.
        if(n_pad > static_cast<exponent_type>(INT8_C(0)))
        {
          str.insert(str.end(), static_cast<std::size_t>(n_pad), '0');
        }
      }
      else
      {
        // Insert the decimal point.
        const auto my_exp_plus_one =
          static_cast<std::uint_fast32_t>
          (
            static_cast<exponent_type>
            (
              the_exp + static_cast<exponent_type>(INT8_C(1))
            )
          );

        // The number string is not large enough to hold the integer part of the number.
        // Zero extend the integer part of the string.
        if(input_str_len < static_cast<std::size_t>(my_exp_plus_one))
        {
          str.insert(str.end(), static_cast<std::size_t>(my_exp_plus_one - static_cast<std::uint_fast32_t>(str.length())), '0');
        }

        str.insert(static_cast<std::size_t>(my_exp_plus_one), static_cast<std::size_t>(UINT8_C(1)), '.');

        // Zero-extend the string to the given precision if necessary.
        const auto n_pad =
          static_cast<exponent_type>
          (
              static_cast<exponent_type>(os_precision)
            - static_cast<exponent_type>
              (
                  static_cast<exponent_type>(str.length() - static_cast<std::size_t>(UINT8_C(1)))
                - static_cast<exponent_type>(the_exp + static_cast<exponent_type>(INT8_C(1)))
              )
          );

        if(n_pad > static_cast<exponent_type>(INT8_C(0)))
        {
          // This line is marked as lcov exclude line. Even though
          // there are explicit test cases thought to cover this line,
          // it is mysteriously sometimes not being hit.

          str.insert(str.end(), static_cast<std::size_t>(n_pad), '0'); // LCOV_EXCL_LINE
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

        if(rit_non_zero != str.crbegin())
        {
          const auto ofs =
            static_cast<std::ptrdiff_t>
            (
                static_cast<std::ptrdiff_t>(str.length())
              - std::distance(str.crbegin(), rit_non_zero)
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
      if(   (str.at(static_cast<std::size_t>(UINT8_C(0))) == '0')
         && (str.at(static_cast<std::size_t>(UINT8_C(1))) == '.'))
      {
        if(str.length() == static_cast<std::uint_fast32_t>(UINT8_C(2)))
        {
          // This string represents zero and needs zero extension.
          str.insert(str.end(), static_cast<std::size_t>(os_precision), '0');
        }
        else
        {
          // This is a non-zero decimal less than 1 that needs zero extension.
          const auto it_non_zero =
            std::find_if(str.cbegin() + static_cast<std::ptrdiff_t>(INT8_C(2)),
                         str.cend(),
                         [](const char& c) // NOLINT(modernize-use-trailing-return-type)
                         {
                           return (c != '0');
                         });

          const auto len_non_zero_part =
            static_cast<std::uint_fast32_t>
            (
              static_cast<std::size_t>(std::distance(it_non_zero, str.cend()))
            );

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
                static_cast<std::size_t>
                (
                  str.length() - static_cast<std::size_t>(UINT8_C(1))
                )
              )
          );

        str.insert(str.end(), static_cast<std::size_t>(u_pad), '0');
      }
    }

    template<typename char_type, typename traits_type>
    friend auto operator<<(std::basic_ostream<char_type, traits_type>& os, const decwide_t& f) -> std::basic_ostream<char_type, traits_type>&
    {
      std::string str;

      decwide_t::wr_string(f,
                           str,
                           os.flags(),
                           os.precision(),
                           os.width(),
                           os.fill());

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
      using local_size_type = typename representation_type::size_type;

      const auto exp10_val =
        static_cast<exponent_type>
        (
            static_cast<exponent_type>(detail::order_of_builtin_integer(x.my_data[static_cast<local_size_type>(UINT8_C(0))]))
          - static_cast<exponent_type>(INT8_C(1))
        );

      return static_cast<exponent_type>(x.my_exp + exp10_val);
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

  #if ((defined(__GNUC__) && (__GNUC__ >= 12)) && !defined(__clang__))
  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Warray-bounds"
  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wstringop-overread"
  #endif
  template<const std::int32_t ParamDigitsBaseTen, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType>
  constexpr auto zero() -> decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>
  {
    using other_wide_decimal_type =
      decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>;

    using other_limb_type = typename other_wide_decimal_type::limb_type;

    return other_wide_decimal_type::from_lst( { static_cast<other_limb_type>(UINT8_C(0)) } );
  }
  #if ((defined(__GNUC__) && (__GNUC__ >= 12)) && !defined(__clang__))
  #pragma GCC diagnostic pop
  #pragma GCC diagnostic pop
  #endif

  template<const std::int32_t ParamDigitsBaseTen, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType>
  constexpr auto one() -> decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>
  {
    using other_wide_decimal_type =
      decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>;

    using other_limb_type = typename other_wide_decimal_type::limb_type;

    return other_wide_decimal_type::from_lst( { static_cast<other_limb_type>(UINT8_C(1)) } );
  }

  template<const std::int32_t ParamDigitsBaseTen, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType>
  constexpr auto two() -> decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>
  {
    using other_wide_decimal_type =
      decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>;

    using other_limb_type = typename other_wide_decimal_type::limb_type;

    return other_wide_decimal_type::from_lst( { static_cast<other_limb_type>(UINT8_C(2)) } );
  }

  template<const std::int32_t ParamDigitsBaseTen, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType>
  constexpr auto half() -> decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>
  {
    using other_wide_decimal_type =
      decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>;

    using other_limb_type     = typename other_wide_decimal_type::limb_type;
    using other_exponent_type = typename other_wide_decimal_type::exponent_type;

    return
      other_wide_decimal_type::from_lst
      (
        {
          static_cast<other_limb_type>(other_wide_decimal_type::decwide_t_elem_mask / static_cast<std::int32_t>(INT8_C(2)))
        },
        static_cast<other_exponent_type>(-other_wide_decimal_type::decwide_t_elem_digits10)
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
  template<const std::int32_t ParamDigitsBaseTen, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType> std::array<typename decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>::fft_float_type, static_cast<std::size_t>(detail::a000079::a000079_as_constexpr(static_cast<std::uint32_t>(static_cast<std::uint32_t>(decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>::decwide_t_elem_number)) * 4UL))>       decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>::my_af_fft_mul_pool; // NOLINT(hicpp-uppercase-literal-suffix,readability-uppercase-literal-suffix,cppcoreguidelines-avoid-non-const-global-variables,cert-err58-cpp)
  template<const std::int32_t ParamDigitsBaseTen, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType> std::array<typename decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>::fft_float_type, static_cast<std::size_t>(detail::a000079::a000079_as_constexpr(static_cast<std::uint32_t>(static_cast<std::uint32_t>(decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>::decwide_t_elem_number)) * 4UL))>       decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>::my_bf_fft_mul_pool; // NOLINT(hicpp-uppercase-literal-suffix,readability-uppercase-literal-suffix,cppcoreguidelines-avoid-non-const-global-variables,cert-err58-cpp)
  template<const std::int32_t ParamDigitsBaseTen, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType> typename decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>::representation_type decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>::my_n_data_for_add_sub;                                                                                                                                                                                                                                                                        // NOLINT(hicpp-uppercase-literal-suffix,readability-uppercase-literal-suffix,cppcoreguidelines-avoid-non-const-global-variables,cert-err58-cpp)
  #endif

  #if !defined(WIDE_DECIMAL_DISABLE_IOSTREAM)
  template<const std::int32_t ParamDigitsBaseTen, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType>
  auto decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>::wr_string(const decwide_t&   x,               // NOLINT(readability-function-cognitive-complexity)
                                                                                                                        std::string&       str,             // NOLINT(google-runtime-references)
                                                                                                                        std::ios::fmtflags ostrm_flags,
                                                                                                                        std::streamsize    ostrm_precision, // NOLINT(bugprone-easily-swappable-parameters)
                                                                                                                        std::streamsize    ostrm_width,
                                                                                                                        char               ostrm_fill) -> void
  {
    using local_flags_type = std::ios::fmtflags;

    // Assess the format flags.

    // Obtain the showpos and uppercase flags.
    const bool my_showpos   { static_cast<local_flags_type>(ostrm_flags & std::ios::showpos)   == static_cast<local_flags_type>(std::ios::showpos) };
    const bool my_uppercase { static_cast<local_flags_type>(ostrm_flags & std::ios::uppercase) == static_cast<local_flags_type>(std::ios::uppercase) };

    using std::ilogb;

    // Get the base-10 exponent.
    auto the_exp = static_cast<exponent_type>(ilogb(x));

    // Determine the kind of output format requested (scientific, fixed, none).
    detail::os_float_field_type my_float_field { };

    if     (static_cast<local_flags_type>(ostrm_flags & std::ios::scientific) == static_cast<local_flags_type>(std::ios::scientific)) { my_float_field = detail::os_float_field_type::scientific; }
    else if(static_cast<local_flags_type>(ostrm_flags & std::ios::fixed)      == static_cast<local_flags_type>(std::ios::fixed))      { my_float_field = detail::os_float_field_type::fixed; }
    else                                                                                                                              { my_float_field = detail::os_float_field_type::none; }

    // Get the output stream's precision and limit it to max_digits10.
    // Erroneous negative precision (theoretically impossible) will be
    // set to ostream's default precision. Zero precision will be left
    // at zero.
    const auto prec_default = static_cast<std::streamsize>(INT8_C(6));

    std::uint_fast32_t
      os_precision
      {
        static_cast<std::uint_fast32_t>
        (
          ((ostrm_precision <= static_cast<std::streamsize>(0))
            ? ((my_float_field != detail::os_float_field_type::scientific) ? static_cast<std::uint_fast32_t>(prec_default) : static_cast<std::uint_fast32_t>(UINT8_C(0)))
            : static_cast<std::uint_fast32_t>(ostrm_precision))
        )
      };

    bool use_scientific { false };
    bool use_fixed      { false };

    if     (my_float_field == detail::os_float_field_type::scientific) { use_scientific = true; }
    else if(my_float_field == detail::os_float_field_type::fixed)      { use_fixed      = true; }
    else // os_float_field_none
    {
      // Set up the range for dynamic detection of scientific notation.
      // If the exponent is less than -4 or larger than a precision-dependent
      // positive bound, then scientific notation is used.
      static const auto neg_bound_for_scientific_neg_exp = static_cast<exponent_type>(INT8_C(-4));
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
    auto number_of_digits10_i_want = static_cast<std::uint_fast32_t>(UINT8_C(0));

    const auto max10_plus_one =
      static_cast<std::uint_fast32_t>
      (
          static_cast<std::uint_fast32_t>(decwide_t_max_digits10)
        + static_cast<std::uint_fast32_t>(UINT8_C(1))
      );

    if(use_scientific)
    {
      // The float-field is scientific. The number of digits is given by
      // (1 + the ostream's precision), not to exceed (max_digits10 + 1).
      const auto prec_plus_one  =
        static_cast<std::uint_fast32_t>
        (
          static_cast<std::uint_fast32_t>(UINT8_C(1)) + os_precision
        );

      number_of_digits10_i_want = (std::min)(max10_plus_one, prec_plus_one);
    }

    if(use_fixed)
    {
      // The float-field is scientific. The number of all-digits depends
      // on the form of the number.

      const auto exp_plus_one                   = static_cast<exponent_type>(the_exp      + static_cast<exponent_type>(INT8_C(1)));
      const auto exp_plus_one_plus_my_precision = static_cast<exponent_type>(exp_plus_one + static_cast<exponent_type>(os_precision));

      if(the_exp >= static_cast<exponent_type>(INT8_C(0)))
      {
        // If the number is larger than 1 in absolute value, then the number of
        // digits is given by the width of the integer part plus the ostream's
        // precision, not to exceed (max_digits10 + 1).
        number_of_digits10_i_want =
          static_cast<std::uint_fast32_t>
          (
            (std::min)(exp_plus_one_plus_my_precision, static_cast<exponent_type>(max10_plus_one))
          );
      }
      else
      {
        number_of_digits10_i_want = (std::min)(os_precision, max10_plus_one);
      }
    }

    // If the float field is not set, reduce the number of digits requested
    // from decwide_t such that it neither exceeds the ostream's precision
    // nor decwide_t's max_digits10.
    if(my_float_field == detail::os_float_field_type::none)
    {
      const auto max_dig10 = (std::min)(os_precision, static_cast<std::uint_fast32_t>(decwide_t_max_digits10));

      number_of_digits10_i_want = (std::min)(number_of_digits10_i_want, max_dig10);
    }

    // Extract the rounded output string with the desired number of digits.
    get_output_string(x, str, the_exp, number_of_digits10_i_want);

    // Obtain additional format information.
    const bool
      my_showpoint
      {
        static_cast<local_flags_type>(ostrm_flags & std::ios::showpoint) == static_cast<local_flags_type>(std::ios::showpoint)
      };

    // Write the output string in the desired format.
    if     (my_float_field == detail::os_float_field_type::scientific) { wr_string_scientific(str, the_exp, os_precision, my_showpoint, my_uppercase); }
    else if(my_float_field == detail::os_float_field_type::fixed)      { wr_string_fixed     (str, the_exp, os_precision, my_showpoint); }
    else // os_float_field_none
    {
      (use_scientific ? wr_string_scientific(str, the_exp, os_precision, my_showpoint, my_uppercase, true)
                      : wr_string_fixed     (str, the_exp, os_precision, my_showpoint, true));
    }

    // Append the sign.
    if     (x.isneg())  { str.insert(static_cast<std::size_t>(UINT8_C(0)), static_cast<std::size_t>(UINT8_C(1)), '-'); }
    else if(my_showpos) { str.insert(static_cast<std::size_t>(UINT8_C(0)), static_cast<std::size_t>(UINT8_C(1)), '+'); }

    // Handle std::setw(...), std::setfill(...), std::left, std::right, std::internal.
    const auto my_width =
      static_cast<std::uint_fast32_t>
      (
        (ostrm_width >= static_cast<std::streamsize>(INT8_C(0))) ? static_cast<std::uint_fast32_t>(ostrm_width)
                                                                 : static_cast<std::uint_fast32_t>(UINT8_C(0))
      );

    if(my_width > str.length())
    {
      // Get the number of fill characters.
      const auto n_fill = static_cast<std::uint_fast32_t>(my_width - str.length());

      // Left-justify is the exception, std::right and std::internal justify right.
      const bool
        my_left
        {
          static_cast<local_flags_type>(ostrm_flags & std::ios::left) == static_cast<local_flags_type>(std::ios::left)
        };

      // Justify left or right and insert the fill characters.
      str.insert((my_left ? str.end() : str.begin()), static_cast<std::size_t>(n_fill), ostrm_fill);
    }
  }
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
    // Compute pi using a quadratically convergent Gauss AGM.
    // In particular, the Schoenhage variant is used.

    // For a description of the algorithm see the book "Pi Unleashed":
    // An optional input callback function pointer can be provided
    // for printing digit-related messages at various points.

    // Book reference:
    // http://www.jjj.de/pibook/pibook.html
    // http://www.springer.com/gp/book/9783642567353

    if(pfn_callback_to_report_digits10 != nullptr)
    {
      pfn_callback_to_report_digits10(static_cast<std::uint32_t>(UINT8_C(0))); // LCOV_EXCL_LINE
    }

    using local_wide_decimal_type =
      decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>;

    local_wide_decimal_type val_pi;

    local_wide_decimal_type a(static_cast<unsigned>(UINT8_C(1)));

    // Initialize bB to 0.5.
    local_wide_decimal_type bB(half<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>()); // NOLINT(readability-identifier-naming)

    // Initialize t to 0.375.
    local_wide_decimal_type
      t
      (
        static_cast<local_wide_decimal_type>
        (
          static_cast<unsigned>(UINT8_C(3))
        )
        / static_cast<unsigned>(UINT8_C(8))
      );

    local_wide_decimal_type s(bB);

    // This loop is designed for a maximum of several million
    // decimal digits of pi. The index k should reach no higher
    // than about 25 or 30. After about 20 iterations, the precision
    // is about one million decimal digits.

    const auto digits10_iteration_goal =
      static_cast<std::uint32_t>
      (
          static_cast<std::uint32_t>(std::numeric_limits<local_wide_decimal_type>::digits10 / 2)
        + (std::max)(static_cast<std::uint32_t>(local_wide_decimal_type::decwide_t_elem_digits10  + static_cast<std::int32_t>(INT8_C(1))),
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
                1000.0F * log(static_cast<float>(std::numeric_limits<local_wide_decimal_type>::radix))
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
      a      /= static_cast<unsigned>(UINT8_C(2));
      val_pi  = a;
      val_pi *= a;
      bB      = val_pi;
      bB     -= t;
      bB     *= static_cast<unsigned>(UINT8_C(2));

      local_wide_decimal_type iterate_term(bB);

      iterate_term -= val_pi;
      iterate_term *= static_cast<unsigned long long>(1ULL << (k + static_cast<unsigned>(UINT8_C(1)))); // NOLINT(google-runtime-int)

      s += iterate_term;

      // Test the number of precise digits from this iteration.
      // If it is there are enough precise digits, then the calculation
      // is finished.
      const auto ib =
        static_cast<std::int32_t>
        (
          (std::max)(static_cast<std::int32_t>(INT8_C(0)),
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
        pfn_callback_to_report_digits10(digits10_of_iteration); // LCOV_EXCL_LINE
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
      t /= static_cast<unsigned>(UINT8_C(4));
    }

    val_pi += bB;
    val_pi /= s;

    if(pfn_callback_to_report_digits10 != nullptr)
    {
      pfn_callback_to_report_digits10(static_cast<std::uint32_t>(std::numeric_limits<local_wide_decimal_type>::digits10)); // LCOV_EXCL_LINE
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

    using local_wide_decimal_type =
      decwide_t<ParamDigitsBaseTen, std::uint8_t, AllocatorType, InternalFloatType, ExponentType, FftFloatType>;

    using local_limb_type = typename local_wide_decimal_type::limb_type;

    return
      local_wide_decimal_type::from_lst
      (
        {
          static_cast<local_limb_type>(UINT8_C( 3)),
          static_cast<local_limb_type>(UINT8_C(14)), static_cast<local_limb_type>(UINT8_C(15)), static_cast<local_limb_type>(UINT8_C(92)), static_cast<local_limb_type>(UINT8_C(65)), static_cast<local_limb_type>(UINT8_C(35)), static_cast<local_limb_type>(UINT8_C(89)), static_cast<local_limb_type>(UINT8_C(79)), static_cast<local_limb_type>(UINT8_C(32)),
          static_cast<local_limb_type>(UINT8_C(38)), static_cast<local_limb_type>(UINT8_C(46)), static_cast<local_limb_type>(UINT8_C(26)), static_cast<local_limb_type>(UINT8_C(43)), static_cast<local_limb_type>(UINT8_C(38)), static_cast<local_limb_type>(UINT8_C(32)), static_cast<local_limb_type>(UINT8_C(79)), static_cast<local_limb_type>(UINT8_C(50)),
          static_cast<local_limb_type>(UINT8_C(28)), static_cast<local_limb_type>(UINT8_C(84)), static_cast<local_limb_type>(UINT8_C(19)), static_cast<local_limb_type>(UINT8_C(71)), static_cast<local_limb_type>(UINT8_C(69)), static_cast<local_limb_type>(UINT8_C(39)), static_cast<local_limb_type>(UINT8_C(93)), static_cast<local_limb_type>(UINT8_C(75)),
          static_cast<local_limb_type>(UINT8_C(10)), static_cast<local_limb_type>(UINT8_C(58)), static_cast<local_limb_type>(UINT8_C(20)), static_cast<local_limb_type>(UINT8_C(97)), static_cast<local_limb_type>(UINT8_C(49)), static_cast<local_limb_type>(UINT8_C(44)), static_cast<local_limb_type>(UINT8_C(59)), static_cast<local_limb_type>(UINT8_C(23)),
          static_cast<local_limb_type>(UINT8_C( 7)), static_cast<local_limb_type>(UINT8_C(81)), static_cast<local_limb_type>(UINT8_C(64)), static_cast<local_limb_type>(UINT8_C( 6)), static_cast<local_limb_type>(UINT8_C(28)), static_cast<local_limb_type>(UINT8_C(62)), static_cast<local_limb_type>(UINT8_C( 8)), static_cast<local_limb_type>(UINT8_C(99)),
          static_cast<local_limb_type>(UINT8_C(86)), static_cast<local_limb_type>(UINT8_C(28)), static_cast<local_limb_type>(UINT8_C( 3)), static_cast<local_limb_type>(UINT8_C(48)), static_cast<local_limb_type>(UINT8_C(25)), static_cast<local_limb_type>(UINT8_C(34)), static_cast<local_limb_type>(UINT8_C(21)), static_cast<local_limb_type>(UINT8_C(17))
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

    using local_wide_decimal_type =
      decwide_t<ParamDigitsBaseTen, std::uint16_t, AllocatorType, InternalFloatType, ExponentType, FftFloatType>;

    using local_limb_type = typename local_wide_decimal_type::limb_type;

    return
      local_wide_decimal_type::from_lst
      (
        {
          static_cast<local_limb_type>(UINT16_C(   3)),
          static_cast<local_limb_type>(UINT16_C(1415)), static_cast<local_limb_type>(UINT16_C(9265)), static_cast<local_limb_type>(UINT16_C(3589)), static_cast<local_limb_type>(UINT16_C(7932)),
          static_cast<local_limb_type>(UINT16_C(3846)), static_cast<local_limb_type>(UINT16_C(2643)), static_cast<local_limb_type>(UINT16_C(3832)), static_cast<local_limb_type>(UINT16_C(7950)),
          static_cast<local_limb_type>(UINT16_C(2884)), static_cast<local_limb_type>(UINT16_C(1971)), static_cast<local_limb_type>(UINT16_C(6939)), static_cast<local_limb_type>(UINT16_C(9375)),
          static_cast<local_limb_type>(UINT16_C(1058)), static_cast<local_limb_type>(UINT16_C(2097)), static_cast<local_limb_type>(UINT16_C(4944)), static_cast<local_limb_type>(UINT16_C(5923)),
          static_cast<local_limb_type>(UINT16_C( 781)), static_cast<local_limb_type>(UINT16_C(6406)), static_cast<local_limb_type>(UINT16_C(2862)), static_cast<local_limb_type>(UINT16_C( 899)),
          static_cast<local_limb_type>(UINT16_C(8628)), static_cast<local_limb_type>(UINT16_C( 348)), static_cast<local_limb_type>(UINT16_C(2534)), static_cast<local_limb_type>(UINT16_C(2117))
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

    using local_wide_decimal_type =
      decwide_t<ParamDigitsBaseTen, std::uint32_t, AllocatorType, InternalFloatType, ExponentType, FftFloatType>;

    using local_limb_type = typename local_wide_decimal_type::limb_type;

    return
      local_wide_decimal_type::from_lst
      (
        {
          static_cast<local_limb_type>(UINT32_C(       3)),
          static_cast<local_limb_type>(UINT32_C(14159265)), static_cast<local_limb_type>(UINT32_C(35897932)),
          static_cast<local_limb_type>(UINT32_C(38462643)), static_cast<local_limb_type>(UINT32_C(38327950)),
          static_cast<local_limb_type>(UINT32_C(28841971)), static_cast<local_limb_type>(UINT32_C(69399375)),
          static_cast<local_limb_type>(UINT32_C(10582097)), static_cast<local_limb_type>(UINT32_C(49445923)),
          static_cast<local_limb_type>(UINT32_C( 7816406)), static_cast<local_limb_type>(UINT32_C(28620899)),
          static_cast<local_limb_type>(UINT32_C(86280348)), static_cast<local_limb_type>(UINT32_C(25342117))
        }
      );
  }

  template<const std::int32_t ParamDigitsBaseTen, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType>
  auto calc_ln_two() -> typename std::enable_if<(ParamDigitsBaseTen > static_cast<std::int32_t>(INT8_C(51))), decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>>::type
  {
    using local_wide_decimal_type = decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>;

    // Use an AGM method to compute log(2).

    // Set a0 = 1
    // Set b0 = 1 / (2^(m-2))

    local_wide_decimal_type ak(static_cast<unsigned>(UINT8_C(1)));

    constexpr auto n_times_factor =
      static_cast<float>
      (
        static_cast<float>(std::numeric_limits<local_wide_decimal_type>::digits10) * 1.67F
      );

    // Ensure that the resulting power is non-negative.
    // Also enforce that m >= 3.
    const auto m =
      (std::max)
      (
        static_cast<std::int32_t>(n_times_factor),
        static_cast<std::int32_t>(3)
      );

    local_wide_decimal_type bk =
      ldexp(one<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>(), static_cast<std::int32_t>(2 - m));

    const auto digits10_iteration_goal =
      static_cast<std::uint32_t>
      (
          static_cast<std::uint32_t>(std::numeric_limits<local_wide_decimal_type>::digits10 / 2)
        + (std::max)(static_cast<std::uint32_t>(local_wide_decimal_type::decwide_t_elem_digits10 + static_cast<std::int32_t>(INT8_C(1))),
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
                1000.0F * log(static_cast<float>(std::numeric_limits<local_wide_decimal_type>::radix))
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

      const auto ib = (std::max)(static_cast<std::int32_t>(INT8_C(0)),
                                 static_cast<std::int32_t>(-ilogb(ak - bk)));

      const auto digits10_of_iteration =
        static_cast<std::uint32_t>
        (
            static_cast<std::uint64_t>(static_cast<std::uint64_t>(ib) * digits10_scale)
          / static_cast<std::uint32_t>(UINT16_C(1000))
        );

      const auto ak_tmp = local_wide_decimal_type { ak };

      ak += bk;

      if(digits10_of_iteration > digits10_iteration_goal)
      {
        break;
      }

      using std::sqrt;

      ak /= static_cast<unsigned>(UINT8_C(2));
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

    using local_wide_decimal_type =
      decwide_t<ParamDigitsBaseTen, std::uint8_t, AllocatorType, InternalFloatType, ExponentType, FftFloatType>;

    using local_limb_type = typename local_wide_decimal_type::limb_type;

    return
      local_wide_decimal_type::from_lst
      (
        {
          static_cast<local_limb_type>(UINT8_C(69)), static_cast<local_limb_type>(UINT8_C(31)), static_cast<local_limb_type>(UINT8_C(47)), static_cast<local_limb_type>(UINT8_C(18)),
          static_cast<local_limb_type>(UINT8_C( 5)), static_cast<local_limb_type>(UINT8_C(59)), static_cast<local_limb_type>(UINT8_C(94)), static_cast<local_limb_type>(UINT8_C(53)), static_cast<local_limb_type>(UINT8_C( 9)), static_cast<local_limb_type>(UINT8_C(41)), static_cast<local_limb_type>(UINT8_C(72)), static_cast<local_limb_type>(UINT8_C(32)),
          static_cast<local_limb_type>(UINT8_C(12)), static_cast<local_limb_type>(UINT8_C(14)), static_cast<local_limb_type>(UINT8_C(58)), static_cast<local_limb_type>(UINT8_C(17)), static_cast<local_limb_type>(UINT8_C(65)), static_cast<local_limb_type>(UINT8_C(68)), static_cast<local_limb_type>(UINT8_C( 7)), static_cast<local_limb_type>(UINT8_C(55)),
          static_cast<local_limb_type>(UINT8_C( 0)), static_cast<local_limb_type>(UINT8_C(13)), static_cast<local_limb_type>(UINT8_C(43)), static_cast<local_limb_type>(UINT8_C(60)), static_cast<local_limb_type>(UINT8_C(25)), static_cast<local_limb_type>(UINT8_C(52)), static_cast<local_limb_type>(UINT8_C(54)), static_cast<local_limb_type>(UINT8_C(12)),
          static_cast<local_limb_type>(UINT8_C( 6)), static_cast<local_limb_type>(UINT8_C(80)), static_cast<local_limb_type>(UINT8_C( 0)), static_cast<local_limb_type>(UINT8_C(94)), static_cast<local_limb_type>(UINT8_C(93)), static_cast<local_limb_type>(UINT8_C(39)), static_cast<local_limb_type>(UINT8_C(36)), static_cast<local_limb_type>(UINT8_C(21)),
          static_cast<local_limb_type>(UINT8_C(96)), static_cast<local_limb_type>(UINT8_C(96)), static_cast<local_limb_type>(UINT8_C(94)), static_cast<local_limb_type>(UINT8_C(71)), static_cast<local_limb_type>(UINT8_C(56)), static_cast<local_limb_type>(UINT8_C( 5)), static_cast<local_limb_type>(UINT8_C(86)), static_cast<local_limb_type>(UINT8_C(33)),
          static_cast<local_limb_type>(UINT8_C(26)), static_cast<local_limb_type>(UINT8_C(99)), static_cast<local_limb_type>(UINT8_C(64)), static_cast<local_limb_type>(UINT8_C(18)), static_cast<local_limb_type>(UINT8_C(68)), static_cast<local_limb_type>(UINT8_C(75)), static_cast<local_limb_type>(UINT8_C(42)), static_cast<local_limb_type>(UINT8_C( 0)),
        },
        static_cast<typename local_wide_decimal_type::exponent_type>(INT8_C(-2))
      );
  }

  template<const std::int32_t ParamDigitsBaseTen, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType>
  auto calc_ln_two() -> typename std::enable_if<((ParamDigitsBaseTen <= static_cast<std::int32_t>(INT8_C(51))) && std::is_same<LimbType, std::uint16_t>::value), decwide_t<ParamDigitsBaseTen, std::uint16_t, AllocatorType, InternalFloatType, ExponentType, FftFloatType>>::type
  {
    // N[Log[2], 121]
    // 0.6931471805599453094172321214581765680755001343602552541206800094933936219696947156058633269964186875420014810205706857337

    using local_wide_decimal_type =
      decwide_t<ParamDigitsBaseTen, std::uint16_t, AllocatorType, InternalFloatType, ExponentType, FftFloatType>;

    using local_limb_type = typename local_wide_decimal_type::limb_type;

    return
      local_wide_decimal_type::from_lst
      (
        {
          static_cast<local_limb_type>(UINT16_C(6931)), static_cast<local_limb_type>(UINT16_C(4718)),
          static_cast<local_limb_type>(UINT16_C( 559)), static_cast<local_limb_type>(UINT16_C(9453)), static_cast<local_limb_type>(UINT16_C( 941)), static_cast<local_limb_type>(UINT16_C(7232)),
          static_cast<local_limb_type>(UINT16_C(1214)), static_cast<local_limb_type>(UINT16_C(5817)), static_cast<local_limb_type>(UINT16_C(6568)), static_cast<local_limb_type>(UINT16_C( 755)),
          static_cast<local_limb_type>(UINT16_C(  13)), static_cast<local_limb_type>(UINT16_C(4360)), static_cast<local_limb_type>(UINT16_C(2552)), static_cast<local_limb_type>(UINT16_C(5412)),
          static_cast<local_limb_type>(UINT16_C( 680)), static_cast<local_limb_type>(UINT16_C(  94)), static_cast<local_limb_type>(UINT16_C(9339)), static_cast<local_limb_type>(UINT16_C(3621)),
          static_cast<local_limb_type>(UINT16_C(9696)), static_cast<local_limb_type>(UINT16_C(9471)), static_cast<local_limb_type>(UINT16_C(5605)), static_cast<local_limb_type>(UINT16_C(8633)),
          static_cast<local_limb_type>(UINT16_C(2699)), static_cast<local_limb_type>(UINT16_C(6418)), static_cast<local_limb_type>(UINT16_C(6875)), static_cast<local_limb_type>(UINT16_C(4200)),
        },
        static_cast<typename local_wide_decimal_type::exponent_type>(INT8_C(-4))
      );
  }

  template<const std::int32_t ParamDigitsBaseTen, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType>
  auto calc_ln_two() -> typename std::enable_if<((ParamDigitsBaseTen <= static_cast<std::int32_t>(INT8_C(51))) && std::is_same<LimbType, std::uint32_t>::value), decwide_t<ParamDigitsBaseTen, std::uint32_t, AllocatorType, InternalFloatType, ExponentType, FftFloatType>>::type
  {
    // N[Log[2], 121]
    // 0.6931471805599453094172321214581765680755001343602552541206800094933936219696947156058633269964186875420014810205706857337

    using local_wide_decimal_type =
      decwide_t<ParamDigitsBaseTen, std::uint32_t, AllocatorType, InternalFloatType, ExponentType, FftFloatType>;

    using local_limb_type = typename local_wide_decimal_type::limb_type;

    return
      local_wide_decimal_type::from_lst
      (
        {
          static_cast<local_limb_type>(UINT32_C(69314718)),
          static_cast<local_limb_type>(UINT32_C( 5599453)), static_cast<local_limb_type>(UINT32_C( 9417232)),
          static_cast<local_limb_type>(UINT32_C(12145817)), static_cast<local_limb_type>(UINT32_C(65680755)),
          static_cast<local_limb_type>(UINT32_C(  134360)), static_cast<local_limb_type>(UINT32_C(25525412)),
          static_cast<local_limb_type>(UINT32_C( 6800094)), static_cast<local_limb_type>(UINT32_C(93393621)),
          static_cast<local_limb_type>(UINT32_C(96969471)), static_cast<local_limb_type>(UINT32_C(56058633)),
          static_cast<local_limb_type>(UINT32_C(26996418)), static_cast<local_limb_type>(UINT32_C(68754200)),
        },
        static_cast<typename local_wide_decimal_type::exponent_type>(INT8_C(-8))
      );
  }

  template<const std::int32_t ParamDigitsBaseTen, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType>
  auto calc_ln_ten_low_precision() -> typename std::enable_if<((ParamDigitsBaseTen <= static_cast<std::int32_t>(INT8_C(51))) && std::is_same<LimbType, std::uint8_t>::value), decwide_t<ParamDigitsBaseTen, std::uint8_t, AllocatorType, InternalFloatType, ExponentType, FftFloatType>>::type
  {
    // N[Log[10], 121]
    // 2.302585092994045684017991454684364207601101488628772976033327900967572609677352480235997205089598298341967784042286248633

    using local_wide_decimal_type =
      decwide_t<ParamDigitsBaseTen, std::uint8_t, AllocatorType, InternalFloatType, ExponentType, FftFloatType>;

    using local_limb_type = typename local_wide_decimal_type::limb_type;

    return
      local_wide_decimal_type::from_lst
      (
        {
          static_cast<local_limb_type>(UINT8_C( 2)),
          static_cast<local_limb_type>(UINT8_C(30)), static_cast<local_limb_type>(UINT8_C(25)), static_cast<local_limb_type>(UINT8_C(85)), static_cast<local_limb_type>(UINT8_C( 9)), static_cast<local_limb_type>(UINT8_C(29)), static_cast<local_limb_type>(UINT8_C(94)), static_cast<local_limb_type>(UINT8_C( 4)), static_cast<local_limb_type>(UINT8_C(56)),
          static_cast<local_limb_type>(UINT8_C(84)), static_cast<local_limb_type>(UINT8_C( 1)), static_cast<local_limb_type>(UINT8_C(79)), static_cast<local_limb_type>(UINT8_C(91)), static_cast<local_limb_type>(UINT8_C(45)), static_cast<local_limb_type>(UINT8_C(46)), static_cast<local_limb_type>(UINT8_C(84)), static_cast<local_limb_type>(UINT8_C(36)),
          static_cast<local_limb_type>(UINT8_C(42)), static_cast<local_limb_type>(UINT8_C( 7)), static_cast<local_limb_type>(UINT8_C(60)), static_cast<local_limb_type>(UINT8_C(11)), static_cast<local_limb_type>(UINT8_C( 1)), static_cast<local_limb_type>(UINT8_C(48)), static_cast<local_limb_type>(UINT8_C(86)), static_cast<local_limb_type>(UINT8_C(28)),
          static_cast<local_limb_type>(UINT8_C(77)), static_cast<local_limb_type>(UINT8_C(29)), static_cast<local_limb_type>(UINT8_C(76)), static_cast<local_limb_type>(UINT8_C( 3)), static_cast<local_limb_type>(UINT8_C(33)), static_cast<local_limb_type>(UINT8_C(27)), static_cast<local_limb_type>(UINT8_C(90)), static_cast<local_limb_type>(UINT8_C( 9)),
          static_cast<local_limb_type>(UINT8_C(67)), static_cast<local_limb_type>(UINT8_C(57)), static_cast<local_limb_type>(UINT8_C(26)), static_cast<local_limb_type>(UINT8_C( 9)), static_cast<local_limb_type>(UINT8_C(67)), static_cast<local_limb_type>(UINT8_C(73)), static_cast<local_limb_type>(UINT8_C(52)), static_cast<local_limb_type>(UINT8_C(48)),
          static_cast<local_limb_type>(UINT8_C( 2)), static_cast<local_limb_type>(UINT8_C(35)), static_cast<local_limb_type>(UINT8_C(99)), static_cast<local_limb_type>(UINT8_C(72)), static_cast<local_limb_type>(UINT8_C( 5)), static_cast<local_limb_type>(UINT8_C( 8)), static_cast<local_limb_type>(UINT8_C(95)), static_cast<local_limb_type>(UINT8_C(98)),
        }
      );
  }

  template<const std::int32_t ParamDigitsBaseTen, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType>
  auto calc_ln_ten_low_precision() -> typename std::enable_if<((ParamDigitsBaseTen <= static_cast<std::int32_t>(INT8_C(51))) && std::is_same<LimbType, std::uint16_t>::value), decwide_t<ParamDigitsBaseTen, std::uint16_t, AllocatorType, InternalFloatType, ExponentType, FftFloatType>>::type
  {
    // N[Log[10], 121]
    // 2.302585092994045684017991454684364207601101488628772976033327900967572609677352480235997205089598298341967784042286248633

    using local_wide_decimal_type =
      decwide_t<ParamDigitsBaseTen, std::uint16_t, AllocatorType, InternalFloatType, ExponentType, FftFloatType>;

    using local_limb_type = typename local_wide_decimal_type::limb_type;

    return
      local_wide_decimal_type::from_lst
      (
        {
          static_cast<local_limb_type>(UINT16_C(   2)),
          static_cast<local_limb_type>(UINT16_C(3025)), static_cast<local_limb_type>(UINT16_C(8509)), static_cast<local_limb_type>(UINT16_C(2994)), static_cast<local_limb_type>(UINT16_C( 456)),
          static_cast<local_limb_type>(UINT16_C(8401)), static_cast<local_limb_type>(UINT16_C(7991)), static_cast<local_limb_type>(UINT16_C(4546)), static_cast<local_limb_type>(UINT16_C(8436)),
          static_cast<local_limb_type>(UINT16_C(4207)), static_cast<local_limb_type>(UINT16_C(6011)), static_cast<local_limb_type>(UINT16_C( 148)), static_cast<local_limb_type>(UINT16_C(8628)),
          static_cast<local_limb_type>(UINT16_C(7729)), static_cast<local_limb_type>(UINT16_C(7603)), static_cast<local_limb_type>(UINT16_C(3327)), static_cast<local_limb_type>(UINT16_C(9009)),
          static_cast<local_limb_type>(UINT16_C(6757)), static_cast<local_limb_type>(UINT16_C(2609)), static_cast<local_limb_type>(UINT16_C(6773)), static_cast<local_limb_type>(UINT16_C(5248)),
          static_cast<local_limb_type>(UINT16_C( 235)), static_cast<local_limb_type>(UINT16_C(9972)), static_cast<local_limb_type>(UINT16_C( 508)), static_cast<local_limb_type>(UINT16_C(9598))
        }
      );
  }

  template<const std::int32_t ParamDigitsBaseTen, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType>
  auto calc_ln_ten_low_precision() -> typename std::enable_if<((ParamDigitsBaseTen <= static_cast<std::int32_t>(INT8_C(51))) && std::is_same<LimbType, std::uint32_t>::value), decwide_t<ParamDigitsBaseTen, std::uint32_t, AllocatorType, InternalFloatType, ExponentType, FftFloatType>>::type
  {
    // N[Log[10], 121]
    // 2.302585092994045684017991454684364207601101488628772976033327900967572609677352480235997205089598298341967784042286248633

    using local_wide_decimal_type =
      decwide_t<ParamDigitsBaseTen, std::uint32_t, AllocatorType, InternalFloatType, ExponentType, FftFloatType>;

    using local_limb_type = typename local_wide_decimal_type::limb_type;

    return
      local_wide_decimal_type::from_lst
      (
        {
          static_cast<local_limb_type>(UINT32_C(       2)),
          static_cast<local_limb_type>(UINT32_C(30258509)), static_cast<local_limb_type>(UINT32_C(29940456)),
          static_cast<local_limb_type>(UINT32_C(84017991)), static_cast<local_limb_type>(UINT32_C(45468436)),
          static_cast<local_limb_type>(UINT32_C(42076011)), static_cast<local_limb_type>(UINT32_C( 1488628)),
          static_cast<local_limb_type>(UINT32_C(77297603)), static_cast<local_limb_type>(UINT32_C(33279009)),
          static_cast<local_limb_type>(UINT32_C(67572609)), static_cast<local_limb_type>(UINT32_C(67735248)),
          static_cast<local_limb_type>(UINT32_C( 2359972)), static_cast<local_limb_type>(UINT32_C( 5089598))
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
  // LCOV_EXCL_START
  template<const std::int32_t ParamDigitsBaseTen, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType>
  auto ln_two() -> decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>
  {
    return calc_ln_two<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>();
  }
  // LCOV_EXCL_STOP
  #endif

  // Global unary operators of decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType> reference.
  template<const std::int32_t ParamDigitsBaseTen, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType> auto operator+(const decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>& self) -> decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType> { return self; }
  template<const std::int32_t ParamDigitsBaseTen, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType> auto operator-(const decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>& self) -> decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType> { using local_wide_decimal_type = decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>; return local_wide_decimal_type(self).negate(); }

  // Global add/sub/mul/div of const decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>& with const decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>&.
  template<const std::int32_t ParamDigitsBaseTen, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType>auto operator+(const decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>& u, const decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>& v) -> decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType> { using local_wide_decimal_type = decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>; return local_wide_decimal_type(u) += v; }
  template<const std::int32_t ParamDigitsBaseTen, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType>auto operator-(const decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>& u, const decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>& v) -> decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType> { using local_wide_decimal_type = decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>; return local_wide_decimal_type(u) -= v; }
  template<const std::int32_t ParamDigitsBaseTen, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType>auto operator*(const decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>& u, const decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>& v) -> decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType> { using local_wide_decimal_type = decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>; return local_wide_decimal_type(u) *= v; }
  template<const std::int32_t ParamDigitsBaseTen, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType>auto operator/(const decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>& u, const decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>& v) -> decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType> { using local_wide_decimal_type = decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>; return local_wide_decimal_type(u) /= v; }

  // Global add/sub/mul/div of const decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>& with all built-in types.
  template<const std::int32_t ParamDigitsBaseTen, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType, typename SignedIntegralType>
  auto operator+(const decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>& u,
                 SignedIntegralType n) -> typename std::enable_if<     std::is_integral<SignedIntegralType>::value
                                                                  && (!std::is_unsigned<SignedIntegralType>::value),
                                                                  decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>>::type
  {
    using local_wide_decimal_type = decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>;

    return local_wide_decimal_type(u).add_signed_long_long(n);
  }

  template<const std::int32_t ParamDigitsBaseTen, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType, typename UnsignedIntegralType>
  auto operator+(const decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>& u,
                 UnsignedIntegralType n) -> typename std::enable_if<   std::is_integral<UnsignedIntegralType>::value
                                                                    && std::is_unsigned<UnsignedIntegralType>::value,
                                                                    decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>>::type
  {
    using local_wide_decimal_type = decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>;

    return local_wide_decimal_type(u).add_unsigned_long_long(n);
  }

  template<const std::int32_t ParamDigitsBaseTen, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType, typename FloatingPointType>
  auto operator+(const decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>& u,
                 FloatingPointType f) -> typename std::enable_if<std::is_floating_point<FloatingPointType>::value,
                                                                 decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>>::type
  {
    using local_wide_decimal_type = decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>;

    return local_wide_decimal_type(u) += decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>(f);
  }

  template<const std::int32_t ParamDigitsBaseTen, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType, typename SignedIntegralType>
  auto operator-(const decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>& u,
                 SignedIntegralType n) -> typename std::enable_if<     std::is_integral<SignedIntegralType>::value
                                                                  && (!std::is_unsigned<SignedIntegralType>::value),
                                                                  decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>>::type
  {
    using local_wide_decimal_type = decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>;

    return local_wide_decimal_type(u).sub_signed_long_long(n);
  }

  template<const std::int32_t ParamDigitsBaseTen, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType, typename UnsignedIntegralType>
  auto operator-(const decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>& u,
                 UnsignedIntegralType n) -> typename std::enable_if<   std::is_integral<UnsignedIntegralType>::value
                                                                    && std::is_unsigned<UnsignedIntegralType>::value,
                                                                    decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>>::type
  {
    using local_wide_decimal_type = decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>;

    return local_wide_decimal_type(u).sub_unsigned_long_long(n);
  }

  // LCOV_EXCL_START
  template<const std::int32_t ParamDigitsBaseTen, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType, typename FloatingPointType>
  auto operator-(const decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>& u,
                 FloatingPointType f) -> typename std::enable_if<std::is_floating_point<FloatingPointType>::value,
                                                                 decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>>::type
  {
    using local_wide_decimal_type = decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>;

    return local_wide_decimal_type(u) -= decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>(f);
  }
  // LCOV_EXCL_STOP

  template<const std::int32_t ParamDigitsBaseTen, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType, typename SignedIntegralType>
  auto operator*(const decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>& u,
                 SignedIntegralType n) -> typename std::enable_if<   std::is_integral<SignedIntegralType>::value
                                                                  && (!std::is_unsigned<SignedIntegralType>::value),
                                                                  decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>>::type
  {
    using local_wide_decimal_type = decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>;

    return local_wide_decimal_type(u).mul_signed_long_long(n);
  }

  template<const std::int32_t ParamDigitsBaseTen, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType, typename UnsignedIntegralType>
  auto operator*(const decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>& u,
                 UnsignedIntegralType n) -> typename std::enable_if<   std::is_integral<UnsignedIntegralType>::value
                                                                    && std::is_unsigned<UnsignedIntegralType>::value,
                                                                    decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>>::type
  {
    using local_wide_decimal_type = decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>;

    return local_wide_decimal_type(u).mul_unsigned_long_long(n);
  }

  template<const std::int32_t ParamDigitsBaseTen, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType, typename FloatingPointType>
  auto operator*(const decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>& u,
                 FloatingPointType f) -> typename std::enable_if<std::is_floating_point<FloatingPointType>::value,
                                                                 decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>>::type
  {
    using local_wide_decimal_type = decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>;

    return local_wide_decimal_type(u) *= decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>(f);
  }

  template<const std::int32_t ParamDigitsBaseTen, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType, typename SignedIntegralType>
  auto operator/(const decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>& u,
                 SignedIntegralType n) -> typename std::enable_if<     std::is_integral<SignedIntegralType>::value
                                                                  && (!std::is_unsigned<SignedIntegralType>::value),
                                                                  decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>>::type
  {
    using local_wide_decimal_type = decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>;

    return local_wide_decimal_type(u).div_signed_long_long(n);
  }

  template<const std::int32_t ParamDigitsBaseTen, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType, typename UnsignedIntegralType>
  auto operator/(const decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>& u,
                 UnsignedIntegralType n) -> typename std::enable_if<   std::is_integral<UnsignedIntegralType>::value
                                                                    && std::is_unsigned<UnsignedIntegralType>::value,
                                                                    decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>>::type
  {
    using local_wide_decimal_type = decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>;

    return local_wide_decimal_type(u).div_unsigned_long_long(n);
  }

  template<const std::int32_t ParamDigitsBaseTen, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType, typename FloatingPointType>
  auto operator/(const decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>& u,
                 FloatingPointType f) -> typename std::enable_if<std::is_floating_point<FloatingPointType>::value,
                                                                 decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>>::type
  {
    using local_wide_decimal_type = decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>;

    return local_wide_decimal_type(u) /= decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>(f);
  }

  // Global add/sub/mul/div of all built-in types with const decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>&.
  template<const std::int32_t ParamDigitsBaseTen, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType, typename SignedIntegralType>
  auto operator+(SignedIntegralType n,
                 const decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>& u) -> typename std::enable_if<   std::is_integral<SignedIntegralType>::value
                                                                                                                                                    && (!std::is_unsigned<SignedIntegralType>::value),
                                                                                                                                                    decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>>::type
  {
    using local_wide_decimal_type = decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>;

    return local_wide_decimal_type(u).add_signed_long_long(n);
  }

  template<const std::int32_t ParamDigitsBaseTen, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType, typename UnsignedIntegralType>
  auto operator+(UnsignedIntegralType n,
                 const decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>& u) -> typename std::enable_if<   std::is_integral<UnsignedIntegralType>::value
                                                                                                                                                    && std::is_unsigned<UnsignedIntegralType>::value,
                                                                                                                                                    decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>>::type
  {
    using local_wide_decimal_type = decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>;

    return local_wide_decimal_type(u).add_unsigned_long_long(n);
  }

  template<const std::int32_t ParamDigitsBaseTen, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType, typename FloatingPointType>
  auto operator+(FloatingPointType f,
                 const decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>& u) -> typename std::enable_if<std::is_floating_point<FloatingPointType>::value,
                                                                                                                                                            decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>>::type
  {
    using local_wide_decimal_type = decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>;

    return local_wide_decimal_type(f) += u;
  }

  template<const std::int32_t ParamDigitsBaseTen, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType, typename ArithmeticType>
  auto operator-(ArithmeticType n,
                 const decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>& u) -> typename std::enable_if<std::is_arithmetic<ArithmeticType>::value,
                                                                                                                                                            decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>>::type
  {
    using local_wide_decimal_type = decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>;

    return local_wide_decimal_type(n) -= u;
  }

  template<const std::int32_t ParamDigitsBaseTen, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType, typename SignedIntegralType>
  auto operator*(SignedIntegralType n,
                 const decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>& u) -> typename std::enable_if<     std::is_integral<SignedIntegralType>::value
                                                                                                                                                            && (!std::is_unsigned<SignedIntegralType>::value),
                                                                                                                                                            decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>>::type
  {
    using local_wide_decimal_type = decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>;

    return local_wide_decimal_type(u).mul_signed_long_long(n);
  }

  template<const std::int32_t ParamDigitsBaseTen, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType, typename UnsignedIntegralType>
  auto operator*(UnsignedIntegralType n,
                 const decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>& u) -> typename std::enable_if<   std::is_integral<UnsignedIntegralType>::value
                                                                                                                                                            && std::is_unsigned<UnsignedIntegralType>::value,
                                                                                                                                                            decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>>::type
  {
    using local_wide_decimal_type = decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>;

    return local_wide_decimal_type(u).mul_unsigned_long_long(n);
  }

  template<const std::int32_t ParamDigitsBaseTen, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType, typename FloatingPointType>
  auto operator*(FloatingPointType f,
                 const decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>& u) -> typename std::enable_if<std::is_floating_point<FloatingPointType>::value,
                                                                                                                                                            decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>>::type
  {
    using local_wide_decimal_type = decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>;

    return local_wide_decimal_type(f) *= u;
  }

  template<const std::int32_t ParamDigitsBaseTen, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType, typename ArithmeticType>
  auto operator/(ArithmeticType n,
                 const decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>& u) -> typename std::enable_if<std::is_arithmetic<ArithmeticType>::value,
                                                                                                                                                            decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>>::type
  {
    using local_wide_decimal_type = decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>;

    return local_wide_decimal_type(n) /= u;
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

  // LCOV_EXCL_START
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
    using local_wide_decimal_type = decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>;

    return u += local_wide_decimal_type(f);
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
    using local_wide_decimal_type = decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>;

    return u -= local_wide_decimal_type(f);
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
    using local_wide_decimal_type = decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>;

    return u *= local_wide_decimal_type(f);
  }
  // LCOV_EXCL_STOP

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
    using local_wide_decimal_type = decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>;

    return u /= local_wide_decimal_type(f);
  }

  // Global comparison operators of const decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, typename ExponentType>& with const decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>&.
  template<const std::int32_t ParamDigitsBaseTen, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType> auto operator< (const decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>& u, const decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>& v) -> bool { return (u.cmp(v) <  static_cast<std::int_fast8_t>(INT8_C(0))); }
  template<const std::int32_t ParamDigitsBaseTen, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType> auto operator<=(const decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>& u, const decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>& v) -> bool { return (u.cmp(v) <= static_cast<std::int_fast8_t>(INT8_C(0))); }
  template<const std::int32_t ParamDigitsBaseTen, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType> auto operator==(const decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>& u, const decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>& v) -> bool { return (u.cmp(v) == static_cast<std::int_fast8_t>(INT8_C(0))); }
  template<const std::int32_t ParamDigitsBaseTen, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType> auto operator!=(const decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>& u, const decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>& v) -> bool { return (u.cmp(v) != static_cast<std::int_fast8_t>(INT8_C(0))); }
  template<const std::int32_t ParamDigitsBaseTen, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType> auto operator>=(const decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>& u, const decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>& v) -> bool { return (u.cmp(v) >= static_cast<std::int_fast8_t>(INT8_C(0))); }
  template<const std::int32_t ParamDigitsBaseTen, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType> auto operator> (const decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>& u, const decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>& v) -> bool { return (u.cmp(v) >  static_cast<std::int_fast8_t>(INT8_C(0))); }

  // Global comparison operators of const decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>& with all built-in types.
  template<const std::int32_t ParamDigitsBaseTen, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType, typename ArithmeticType> auto operator< (const decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>& u, const ArithmeticType& v) -> typename std::enable_if<std::is_arithmetic<ArithmeticType>::value, bool>::type { return (u.cmp(decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>(v)) <  static_cast<std::int_fast8_t>(INT8_C(0))); }
  template<const std::int32_t ParamDigitsBaseTen, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType, typename ArithmeticType> auto operator<=(const decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>& u, const ArithmeticType& v) -> typename std::enable_if<std::is_arithmetic<ArithmeticType>::value, bool>::type { return (u.cmp(decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>(v)) <= static_cast<std::int_fast8_t>(INT8_C(0))); }
  template<const std::int32_t ParamDigitsBaseTen, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType, typename ArithmeticType> auto operator==(const decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>& u, const ArithmeticType& v) -> typename std::enable_if<std::is_arithmetic<ArithmeticType>::value, bool>::type { return (u.cmp(decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>(v)) == static_cast<std::int_fast8_t>(INT8_C(0))); }
  template<const std::int32_t ParamDigitsBaseTen, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType, typename ArithmeticType> auto operator!=(const decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>& u, const ArithmeticType& v) -> typename std::enable_if<std::is_arithmetic<ArithmeticType>::value, bool>::type { return (u.cmp(decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>(v)) != static_cast<std::int_fast8_t>(INT8_C(0))); }
  template<const std::int32_t ParamDigitsBaseTen, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType, typename ArithmeticType> auto operator>=(const decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>& u, const ArithmeticType& v) -> typename std::enable_if<std::is_arithmetic<ArithmeticType>::value, bool>::type { return (u.cmp(decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>(v)) >= static_cast<std::int_fast8_t>(INT8_C(0))); }
  template<const std::int32_t ParamDigitsBaseTen, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType, typename ArithmeticType> auto operator> (const decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>& u, const ArithmeticType& v) -> typename std::enable_if<std::is_arithmetic<ArithmeticType>::value, bool>::type { return (u.cmp(decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>(v)) >  static_cast<std::int_fast8_t>(INT8_C(0))); }

  // Global comparison operators of all built-in types with const decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>&.
  template<const std::int32_t ParamDigitsBaseTen, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType, typename ArithmeticType> auto operator< (ArithmeticType u, const decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>& v) -> typename std::enable_if<std::is_arithmetic<ArithmeticType>::value, bool>::type { return (decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>(u).cmp(v) <  static_cast<std::int_fast8_t>(INT8_C(0))); }
  template<const std::int32_t ParamDigitsBaseTen, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType, typename ArithmeticType> auto operator<=(ArithmeticType u, const decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>& v) -> typename std::enable_if<std::is_arithmetic<ArithmeticType>::value, bool>::type { return (decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>(u).cmp(v) <= static_cast<std::int_fast8_t>(INT8_C(0))); }
  template<const std::int32_t ParamDigitsBaseTen, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType, typename ArithmeticType> auto operator==(ArithmeticType u, const decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>& v) -> typename std::enable_if<std::is_arithmetic<ArithmeticType>::value, bool>::type { return (decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>(u).cmp(v) == static_cast<std::int_fast8_t>(INT8_C(0))); }
  template<const std::int32_t ParamDigitsBaseTen, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType, typename ArithmeticType> auto operator!=(ArithmeticType u, const decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>& v) -> typename std::enable_if<std::is_arithmetic<ArithmeticType>::value, bool>::type { return (decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>(u).cmp(v) != static_cast<std::int_fast8_t>(INT8_C(0))); }
  template<const std::int32_t ParamDigitsBaseTen, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType, typename ArithmeticType> auto operator>=(ArithmeticType u, const decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>& v) -> typename std::enable_if<std::is_arithmetic<ArithmeticType>::value, bool>::type { return (decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>(u).cmp(v) >= static_cast<std::int_fast8_t>(INT8_C(0))); }
  template<const std::int32_t ParamDigitsBaseTen, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType, typename ArithmeticType> auto operator> (ArithmeticType u, const decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>& v) -> typename std::enable_if<std::is_arithmetic<ArithmeticType>::value, bool>::type { return (decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>(u).cmp(v) >  static_cast<std::int_fast8_t>(INT8_C(0))); }

  #if(__cplusplus >= 201703L)
  } // namespace math::wide_decimal
  #else
  } // namespace wide_decimal
  } // namespace math
  #endif

  WIDE_DECIMAL_NAMESPACE_END

  // Specialization of std::numeric_limits<decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>>.
  namespace std // NOLINT(cert-dcl58-cpp)
  {
    namespace nonstd
    {
      #if defined(WIDE_DECIMAL_NAMESPACE)
      namespace wide_decimal_namespace = WIDE_DECIMAL_NAMESPACE::math::wide_decimal;
      #else
      namespace wide_decimal_namespace = ::math::wide_decimal;
      #endif
    } // namespace nonstd

    template<const std::int32_t ParamDigitsBaseTen,
             typename LimbType,
             typename AllocatorType,
             typename InternalFloatType,
             typename ExponentType,
             typename FftFloatType>
    class numeric_limits<nonstd::wide_decimal_namespace::decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>>
    {
    private:
      using local_wide_decimal_type =
        nonstd::wide_decimal_namespace::decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>;

    public:
      static constexpr auto is_specialized    = true;
      static constexpr auto is_signed         = true;
      static constexpr auto is_integer        = false;
      static constexpr auto is_exact          = false;
      static constexpr auto is_bounded        = true;
      static constexpr auto is_modulo         = false;
      static constexpr auto is_iec559         = false;
      static constexpr auto digits            = local_wide_decimal_type::decwide_t_digits;       // Type differs from int.
      static constexpr auto digits10          = local_wide_decimal_type::decwide_t_digits10;     // Type differs from int.
      static constexpr auto max_digits10      = local_wide_decimal_type::decwide_t_max_digits10; // Type differs from int.
      static constexpr auto min_exponent      = local_wide_decimal_type::decwide_t_min_exp;      // Type differs from int.
      static constexpr auto min_exponent10    = local_wide_decimal_type::decwide_t_min_exp10;    // Type differs from int.
      static constexpr auto max_exponent      = local_wide_decimal_type::decwide_t_max_exp;      // Type differs from int.
      static constexpr auto max_exponent10    = local_wide_decimal_type::decwide_t_max_exp10;    // Type differs from int.
      static constexpr auto radix             = static_cast<int>(local_wide_decimal_type::decwide_t_radix);
      static constexpr auto round_style       = static_cast<std::float_round_style>(std::round_to_nearest);
      static constexpr auto has_infinity      = false;
      static constexpr auto has_quiet_NaN     = false;
      static constexpr auto has_signaling_NaN = false;
      static constexpr auto has_denorm        = static_cast<std::float_denorm_style>(std::denorm_absent);
      static constexpr auto has_denorm_loss   = false;
      static constexpr auto traps             = false;
      static constexpr auto tinyness_before   = false;

      // LCOV_EXCL_START
      static constexpr auto (min)  () -> local_wide_decimal_type { return local_wide_decimal_type::my_value_min(); }
      static constexpr auto (max)  () -> local_wide_decimal_type { return local_wide_decimal_type::my_value_max(); }
      static constexpr auto lowest () -> local_wide_decimal_type { return local_wide_decimal_type(); }
      static constexpr auto epsilon() -> local_wide_decimal_type
      {
        return local_wide_decimal_type::from_lst
        (
          {
            static_cast<typename local_wide_decimal_type::limb_type>
            (
              nonstd::wide_decimal_namespace::detail::pow10_maker
              (
                static_cast<std::uint32_t>
                (
                  static_cast<std::int32_t>
                  (
                      static_cast<std::int32_t>
                      (
                          static_cast<std::int32_t>(INT8_C(1))
                        + local_wide_decimal_type::decwide_t_digits10_for_epsilon()
                      )
                    - local_wide_decimal_type::decwide_t_digits10
                  )
                )
              )
            )
          },
          static_cast<typename local_wide_decimal_type::exponent_type>(static_cast<std::int32_t>(-local_wide_decimal_type::decwide_t_digits10_for_epsilon()))
        );
      }

      static constexpr auto round_error  () -> local_wide_decimal_type { return nonstd::wide_decimal_namespace::half<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>(); }
      static constexpr auto infinity     () -> local_wide_decimal_type { return nonstd::wide_decimal_namespace::zero<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>(); }
      static constexpr auto quiet_NaN    () -> local_wide_decimal_type { return nonstd::wide_decimal_namespace::zero<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>(); } // NOLINT(readability-identifier-naming)
      static constexpr auto signaling_NaN() -> local_wide_decimal_type { return nonstd::wide_decimal_namespace::zero<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>(); } // NOLINT(readability-identifier-naming)
      static constexpr auto denorm_min   () -> local_wide_decimal_type { return nonstd::wide_decimal_namespace::zero<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>(); }
      // LCOV_EXCL_STOP
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
    return
      (a.iszero()) ? one<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>()
                   : exp(a * log(x));
  }

  template<const std::int32_t ParamDigitsBaseTen, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType>
  auto ldexp(const decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>& v, int e) -> decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>
  {
    if(e == static_cast<int>(INT8_C(0)))
    {
      return v;
    }
    else // NOLINT(llvm-else-after-return,readability-else-after-return)
    {
      using local_wide_decimal_type = decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>;

      local_wide_decimal_type result(v);

      return
        (e <= static_cast<int>(INT8_C(-64)))
          ? result /= pow(two<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>(), -e)
          : (e >= static_cast<int>(INT8_C(64)))
            ? result *= pow(two<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>(), e)
            : (e < static_cast<int>(INT8_C(0))) ? result /= static_cast<std::uint64_t>(1ULL << static_cast<unsigned>(-e))
                                                : result *= static_cast<std::uint64_t>(1ULL << static_cast<unsigned>(e));
    }
  }

  template<const std::int32_t ParamDigitsBaseTen, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType>
  auto frexp(const decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>& v,
             int* expon) -> decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>
  {
    using local_wide_decimal_type = decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>;

    using local_exponent_type = typename local_wide_decimal_type::exponent_type;

    local_wide_decimal_type result;
    local_exponent_type     my_e;

    local_wide_decimal_type::calculate_frexp(result, v, &my_e);

    *expon = static_cast<int>(my_e);

    return result;
  }

  template<const std::int32_t ParamDigitsBaseTen, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType>
  auto fmod(const decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>& v1,
            const decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>& v2) -> decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>
  {
    using local_wide_decimal_type = decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>;

    const local_wide_decimal_type nv = (v1.isneg() ? ceil(v1 / v2) : floor(v1 / v2));

    return v1 - (nv * v2);
  }

  template<const std::int32_t ParamDigitsBaseTen, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType>
  auto sqrt(const decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>& x) -> decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>
  {
    using local_wide_decimal_type = decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>;

    return local_wide_decimal_type(x).calculate_sqrt();
  }

  template<const std::int32_t ParamDigitsBaseTen, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType>
  auto cbrt(const decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>& x) -> decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>
  {
    return rootn(x, static_cast<std::int32_t>(3));
  }

  template<const std::int32_t ParamDigitsBaseTen, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType>
  auto rootn(const decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>& x, std::int32_t p) -> decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType> // NOLINT(misc-no-recursion)
  {
    using local_wide_decimal_type = decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>;

    local_wide_decimal_type rtn;

    if(p < static_cast<std::int32_t>(INT8_C(0)))
    {
      rtn =   one<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>()
            / rootn(x, static_cast<std::int32_t>(-p));
    }
    else if((p == static_cast<std::int32_t>(INT8_C(0))) || ((x < 0) && (p != static_cast<std::int32_t>(INT8_C(3)))))
    {
      rtn = zero<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>();
    }
    else if(p == static_cast<std::int32_t>(INT8_C(1)))
    {
      rtn = x;
    }
    else if(p == static_cast<std::int32_t>(INT8_C(2)))
    {
      rtn = sqrt(x);
    }
    else if(p == static_cast<std::int32_t>(INT8_C(3)))
    {
      const auto b_neg = (x < 0);

      rtn = (fabs(x).calculate_rootn_inv(3)).calculate_inv();

      if(b_neg) { static_cast<void>(rtn.negate()); }
    }
    else
    {
      rtn = (local_wide_decimal_type(x).calculate_rootn_inv(p)).calculate_inv();
    }

    return rtn;
  }

  template<const std::int32_t ParamDigitsBaseTen, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType>
  auto rootn_inv(const decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>& x,
                 std::int32_t p) -> decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>
  {
    using local_wide_decimal_type = decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>;

    return local_wide_decimal_type(x).calculate_rootn_inv(p);
  }

  template<const std::int32_t ParamDigitsBaseTen, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType>
  auto log(const decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>& x) -> typename std::enable_if<(ParamDigitsBaseTen > static_cast<std::int32_t>(INT8_C(51))), decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>>::type // NOLINT(misc-no-recursion)
  {
    using local_wide_decimal_type = decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>;

    local_wide_decimal_type result { };

    if(x < one<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>())
    {
      result = -log(local_wide_decimal_type(x).calculate_inv());
    }
    else if(x > one<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>())
    {
      const auto precision_of_x = local_wide_decimal_type::get_precision(x);

      // Use an AGM method to compute the logarithm of x.
      // Set a0 = 1
      // Set b0 = 4 / (x * 2^m)
      //        = 1 / (x * 2^(m - 2))

      result = one<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>();

      const auto n_times_factor =
        static_cast<float>
        (
          static_cast<float>(static_cast<float>(std::numeric_limits<local_wide_decimal_type>::digits10)) * 1.67F
        );

      // Extract lg_xx = Log[mantissa * radix^ib]
      //               = Log[mantissa] + ib * Log[radix],
      // where the logarithm of the mantissa is simply neglected
      // in the approximation.

      using local_exponent_type = typename local_wide_decimal_type::exponent_type;

      using std::ilogb;
      using std::log;

      const auto lg_x_approx =
        static_cast<float>
        (
            static_cast<float>(static_cast<local_exponent_type>(ilogb(x)))
          * log(static_cast<float>(std::numeric_limits<local_wide_decimal_type>::radix))
        );

      const auto lg_x_over_lg2 = static_cast<float>(lg_x_approx / log(2.0F));

      // Ensure that the resulting power is non-negative.
      // Also enforce that m >= 3.
      const auto m =
        static_cast<std::int32_t>
        (
          (std::max)(static_cast<float>(n_times_factor - lg_x_over_lg2),
                     static_cast<float>(3))
        );

      local_wide_decimal_type bk =
        one<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>();

      bk.precision(precision_of_x);

      bk = ldexp(bk, static_cast<std::int32_t>(2 - m));

      bk /= x;

      // TBD: Tolerance should have the log of the argument added to it (usually negligible).
      const auto digits10_iteration_goal_a =
        static_cast<std::uint32_t>
        (
            static_cast<std::uint32_t>(std::numeric_limits<local_wide_decimal_type>::digits10 / 2)
          + (std::max)(static_cast<std::uint32_t>(local_wide_decimal_type::decwide_t_elem_digits10 + static_cast<std::int32_t>(INT8_C(1))),
                       static_cast<std::uint32_t>(UINT8_C(9)))
        );

      const auto digits10_iteration_goal_b =
        static_cast<std::uint32_t>
        (
            static_cast<std::uint32_t>(precision_of_x / 2)
          + (std::max)(static_cast<std::uint32_t>(local_wide_decimal_type::decwide_t_elem_digits10 + static_cast<std::int32_t>(INT8_C(1))),
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
                * log(static_cast<float>(std::numeric_limits<local_wide_decimal_type>::radix))
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
          (std::max)(static_cast<std::int32_t>(INT8_C(0)),
                     static_cast<std::int32_t>(-ilogb(result - bk)));

        const auto digits10_of_iteration =
          static_cast<local_exponent_type>
          (
            static_cast<std::uint64_t>(static_cast<std::uint64_t>(ilogb_of_ak_minus_bk) * digits10_scale) / UINT32_C(1000)
          );

        const local_wide_decimal_type ak_tmp(result);

        result += bk;

        if(digits10_of_iteration > digits10_iteration_goal)
        {
          break;
        }

        result /= 2;

        bk *= ak_tmp;

        static_cast<void>(bk.calculate_sqrt());
      }

      // We are now finished with the AGM iteration for log(x).
      // Compute log(x) = {pi / [2 * AGM(1, 4 / 2^m)]} - (m * ln2)
      // Note at this time that (ak = bk) = AGM(...)
      // Retrieve the value of pi, divide by (2 * a) and subtract (m * ln2).

      result.calculate_inv() *= pi<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>();

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
    using local_wide_decimal_type = decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>;

    local_wide_decimal_type result { };

    if(x < one<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>())
    {
      result = -log(local_wide_decimal_type(x).calculate_inv());
    }
    else if(x > one<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>())
    {
      // Reduce the argument to x_scaled = 10^n * x.
      // This results in:
      //   log10(x) = n * log(10) + log10(x).

      // Subsequently define y = x_scaled - 1 and use
      // the Taylor series for log(y) evalueated at 1.

      using local_exponent_type = typename local_wide_decimal_type::exponent_type;
      using local_limb_type     = typename local_wide_decimal_type::limb_type;

      auto n = ilogb(x);

      // Create a wide decimal scale_factor which is intended to scale
      // the input argument to a value in the approximate range 1 ... 10.

      local_wide_decimal_type scale_factor =
        local_wide_decimal_type::from_lst
        (
          {
            static_cast<local_limb_type>
            (
              detail::pow10_maker_as_runtime_value(static_cast<std::uint32_t>(n % static_cast<local_exponent_type>(local_wide_decimal_type::decwide_t_elem_digits10)))
            )
          },
          static_cast<local_exponent_type>
          (
            (n / static_cast<local_exponent_type>(local_wide_decimal_type::decwide_t_elem_digits10)) * static_cast<local_exponent_type>(local_wide_decimal_type::decwide_t_elem_digits10)
          )
        );

      auto x_scaled = x / scale_factor;

      if(x_scaled > static_cast<local_wide_decimal_type>(1.8F)) // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
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
            static_cast<local_exponent_type>(std::numeric_limits<local_wide_decimal_type>::digits10)
          + static_cast<local_exponent_type>(INT8_C(5))
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
            (std::max)(static_cast<std::int32_t>(INT8_C(0)),
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
    using local_wide_decimal_type = decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>;

    const auto b_neg = x.isneg();

    local_wide_decimal_type exp_result;

    if(b_neg || (x > 0))
    {
      const local_wide_decimal_type xx = ((!b_neg) ? x : -x);

      // Get (compute beforehad) ln2 as a constant or constant reference value.
      #if !defined(WIDE_DECIMAL_DISABLE_CACHED_CONSTANTS)
      const local_wide_decimal_type& ln2 = ln_two<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>();
      #else
      const local_wide_decimal_type  ln2 = ln_two<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>(); // LCOV_EXCL_LINE
      #endif

      const auto nf = static_cast<std::uint32_t>(xx / ln2);

      local_wide_decimal_type xh(xx - static_cast<local_wide_decimal_type>(nf * ln2));

      const auto precision_of_x = local_wide_decimal_type::get_precision(x);

      // Setup the iteration.

      // Use the original value of x for iteration below.
      local_wide_decimal_type original_x(xh);

      local_wide_decimal_type iterate_term;

      using std::exp;

      // Estimate the exponent using built-in <cmath>-functions.
      const auto x_as_built_in_float = static_cast<InternalFloatType>(original_x);
      const auto exp_estimate        = exp(x_as_built_in_float);

      exp_result = exp_estimate;

      for(auto digits  = static_cast<std::int32_t>(std::numeric_limits<InternalFloatType>::digits10 - 1);
               digits  < precision_of_x; // NOLINT(altera-id-dependent-backward-branch)
               digits *= static_cast<std::int32_t>(INT8_C(2)))
      {
        // Adjust precision of the terms.
        const auto min_elem_digits10_plus_one =
          (std::min)
          (
            static_cast<std::int32_t>(local_wide_decimal_type::decwide_t_elem_digits10 + static_cast<std::int32_t>(INT8_C(1))),
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
  auto exp(const decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>& x) -> typename std::enable_if<(ParamDigitsBaseTen <= static_cast<std::int32_t>(INT32_C(2000))), decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>>::type
  {
    using local_wide_decimal_type = decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>;

    const auto b_neg = x.isneg();

    local_wide_decimal_type exp_result;

    if(b_neg || (x > 0))
    {
      const local_wide_decimal_type xx = ((!b_neg) ? x : -x);

      // The algorithm for exp has been taken from MPFUN.
      // exp(t) = [ (1 + r + r^2/2! + r^3/3! + r^4/4! ...)^p2 ] * 2^n
      // where p2 is a power of 2 such as 2048, r = t_prime / p2, and
      // t_prime = t - n*ln2, with n chosen to minimize the absolute
      // value of t_prime. In the resulting Taylor series, which is
      // implemented as a hypergeometric function, |r| is bounded by
      // ln2 / p2.

      // Get (compute beforehad) ln2 as a constant or constant reference value.
      #if !defined(WIDE_DECIMAL_DISABLE_CACHED_CONSTANTS)
      const local_wide_decimal_type& ln2 = ln_two<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>();
      #else
      const local_wide_decimal_type  ln2 = ln_two<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>(); // LCOV_EXCL_LINE
      #endif

      const auto nf = static_cast<std::uint32_t>(xx / ln2);

      // Compute the exponential series of the scaled argument.
      // The scaling is 2^11 = 2048.
      const auto p2 = static_cast<std::uint32_t>(UINTMAX_C(1) << static_cast<unsigned>(UINT8_C(11)));

      // Compute the series representation of Hypergeometric0F0 taken from
      // http://functions.wolfram.com/HypergeometricFunctions/Hypergeometric0F0/06/01/
      // There are no checks on input range or parameter boundaries.

      const auto precision_of_x = local_wide_decimal_type::get_precision(x);

      local_wide_decimal_type xh((xx - static_cast<local_wide_decimal_type>(nf * ln2)) / p2);

      xh.precision(precision_of_x);

      local_wide_decimal_type x_pow_n_div_n_fact(xh);

      local_wide_decimal_type
        h0f0
        (
            one<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>()
          + x_pow_n_div_n_fact
        );

      h0f0.precision(precision_of_x);

      using local_exponent_type = typename local_wide_decimal_type::exponent_type;

      using std::ilogb;

      const auto iteration_goal_ilobg =
        (std::max)(static_cast<local_exponent_type>(INT8_C(0)),
                   static_cast<local_exponent_type>(-ilogb(std::numeric_limits<local_wide_decimal_type>::epsilon())));

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
            (std::max)(static_cast<local_exponent_type>(INT8_C(0)),
                       static_cast<local_exponent_type>(-ilogb(x_pow_n_div_n_fact)));

          if(iteration_result_so_far > digits10_iteration_goal)
          {
            break;
          }
        }

        h0f0 += x_pow_n_div_n_fact;
      }

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
    const auto ep = exp(x);

    using local_wide_decimal_type = decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>;

    return (ep - local_wide_decimal_type(ep).calculate_inv()) /= static_cast<unsigned>(UINT8_C(2));
  }

  template<const std::int32_t ParamDigitsBaseTen, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType>
  auto cosh(const decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>& x) -> decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>
  {
    const auto ep = exp(x);

    using local_wide_decimal_type = decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>;

    return (ep + local_wide_decimal_type(ep).calculate_inv()) /= static_cast<unsigned>(UINT8_C(2));
  }

  template<const std::int32_t ParamDigitsBaseTen, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType>
  auto tanh(const decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>& x) -> decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>
  {
    const auto ep = exp(x);

    using local_wide_decimal_type = decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>;

    const auto em(local_wide_decimal_type(ep).calculate_inv());

    return (ep - em) /= (ep + em);
  }

  template<const std::int32_t ParamDigitsBaseTen, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ExponentType, typename FftFloatType>
  auto pow(const decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>& b, std::int64_t p) -> decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType> // NOLINT(misc-no-recursion)
  {
    // Calculate (b ^ p).

    using local_wide_decimal_type = decwide_t<ParamDigitsBaseTen, LimbType, AllocatorType, InternalFloatType, ExponentType, FftFloatType>;

    local_wide_decimal_type result;

    if     (p <  static_cast<std::int64_t>(INT8_C(0))) { result = pow(b, -p).calculate_inv(); }
    else if(p == static_cast<std::int64_t>(INT8_C(0))) { result = local_wide_decimal_type(static_cast<unsigned>(UINT8_C(1))); }
    else if(p == static_cast<std::int64_t>(INT8_C(1))) { result = b; }
    else if(p == static_cast<std::int64_t>(INT8_C(2))) { result = b; result *= b; }
    else if(p == static_cast<std::int64_t>(INT8_C(3))) { result = b; result *= b; result *= b; }
    else if(p == static_cast<std::int64_t>(INT8_C(4))) { result = b; result *= b; result *= result; }
    else
    {
      result = local_wide_decimal_type(static_cast<unsigned>(UINT8_C(1)));

      local_wide_decimal_type y(b);

      auto p_local = static_cast<std::uint64_t>(p);

      // Use the so-called ladder method for the power calculation.
      for(;;)
      {
        const auto do_power_multiply =
          (static_cast<std::uint_fast8_t>(p_local & static_cast<unsigned>(UINT8_C(1))) != static_cast<std::uint_fast8_t>(UINT8_C(0)));

        if(do_power_multiply)
        {
          result *= y;
        }

        p_local >>= static_cast<unsigned>(UINT8_C(1));

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
