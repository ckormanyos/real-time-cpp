///////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 1999 - 2023.                 //
//  Distributed under the Boost Software License,                //
//  Version 1.0. (See accompanying file LICENSE_1_0.txt          //
//  or copy at http://www.boost.org/LICENSE_1_0.txt)             //
///////////////////////////////////////////////////////////////////

// This work is also based on an earlier work:
// "Algorithm 910: A Portable C++ Multiple-Precision System for Special-Function Calculations",
// in ACM TOMS, {VOL 37, ISSUE 4, (February 2011)} (C) ACM, 2011. http://doi.acm.org/10.1145/1916461.1916469

// This file implements various details for decwide_t.

#ifndef DECWIDE_T_DETAIL_2020_10_26_H // NOLINT(llvm-header-guard)
  #define DECWIDE_T_DETAIL_2020_10_26_H

  #include <algorithm>
  #include <array>
  #include <cstdint>
  #include <initializer_list>
  #include <memory>

  #include <util/utility/util_dynamic_array.h>

  #include <math/wide_decimal/decwide_t_detail_namespace.h>

  #if defined(_MSC_VER)
    #if (_MSC_VER >= 1900) && defined(_HAS_CXX20) && (_HAS_CXX20 != 0)
      #define WIDE_DECIMAL_NODISCARD [[nodiscard]]           // NOLINT(cppcoreguidelines-macro-usage)
    #else
      #define WIDE_DECIMAL_NODISCARD
    #endif
  #else
    #if (defined(__cplusplus) && (__cplusplus >= 201402L))
      #if defined(__AVR__) && (!defined(__GNUC__) || (defined(__GNUC__) && (__GNUC__ > 6)))
      #define WIDE_DECIMAL_NODISCARD [[nodiscard]]           // NOLINT(cppcoreguidelines-macro-usage)
      #elif (defined(__cpp_lib_constexpr_algorithms) && (__cpp_lib_constexpr_algorithms>=201806))
        #if defined(__clang__)
          #if (__clang_major__ > 9)
          #define WIDE_DECIMAL_NODISCARD [[nodiscard]]           // NOLINT(cppcoreguidelines-macro-usage)
          #else
          #define WIDE_DECIMAL_NODISCARD
          #endif
        #else
        #define WIDE_DECIMAL_NODISCARD [[nodiscard]]           // NOLINT(cppcoreguidelines-macro-usage)
        #endif
      #elif (defined(__clang__) && (__clang_major__ >= 10)) && (defined(__cplusplus) && (__cplusplus > 201703L))
        #if defined(__x86_64__)
        #define WIDE_DECIMAL_NODISCARD [[nodiscard]]           // NOLINT(cppcoreguidelines-macro-usage)
        #else
        #define WIDE_DECIMAL_NODISCARD
        #endif
      #else
      #define WIDE_DECIMAL_NODISCARD
      #endif
    #else
      #define WIDE_DECIMAL_NODISCARD
    #endif
  #endif

  WIDE_DECIMAL_NAMESPACE_BEGIN

  #if(__cplusplus >= 201703L)
  namespace math::wide_decimal::detail {
  #else
  namespace math { namespace wide_decimal { namespace detail { // NOLINT(modernize-concat-nested-namespaces)
  #endif

  template<const std::size_t BitCount,
           typename EnableType = void>
  struct uint_type_helper
  {
  private:
    static constexpr auto bit_count   () -> std::size_t { return BitCount; }
    static constexpr auto bit_count_lo() -> std::size_t { return static_cast<std::size_t>(std::numeric_limits<unsigned char>::digits); }
    static constexpr auto bit_count_hi() -> std::size_t { return static_cast<std::size_t>(std::numeric_limits<std::uintmax_t>::digits); }

    static_assert
    (
      (   (bit_count()    >= bit_count_lo())
       && (BitCount       <= bit_count_hi())
       && (bit_count_hi() >= static_cast<std::size_t>(UINT8_C(64)))
      ),
      "Error: uint_type_helper is not intended to be used for this BitCount"
    );

  public:
    using exact_unsigned_type = std::uintmax_t;
    using exact_signed_type   = std::intmax_t;
    using fast_unsigned_type  = std::uintmax_t;
    using fast_signed_type    = std::intmax_t;
  };

  template<const std::size_t BitCount> struct uint_type_helper<BitCount, typename std::enable_if<                                                       (BitCount <= static_cast<std::size_t>(UINT8_C(  8)))>::type> { using exact_unsigned_type = std::uint8_t;  using exact_signed_type = std::int8_t;  using fast_unsigned_type = std::uint_fast8_t;  using fast_signed_type = std::int_fast8_t;  };
  template<const std::size_t BitCount> struct uint_type_helper<BitCount, typename std::enable_if<(BitCount >= static_cast<std::size_t>(UINT8_C( 9))) && (BitCount <= static_cast<std::size_t>(UINT8_C( 16)))>::type> { using exact_unsigned_type = std::uint16_t; using exact_signed_type = std::int16_t; using fast_unsigned_type = std::uint_fast16_t; using fast_signed_type = std::int_fast16_t; };
  template<const std::size_t BitCount> struct uint_type_helper<BitCount, typename std::enable_if<(BitCount >= static_cast<std::size_t>(UINT8_C(17))) && (BitCount <= static_cast<std::size_t>(UINT8_C( 32)))>::type> { using exact_unsigned_type = std::uint32_t; using exact_signed_type = std::int32_t; using fast_unsigned_type = std::uint_fast32_t; using fast_signed_type = std::int_fast32_t; };
  template<const std::size_t BitCount> struct uint_type_helper<BitCount, typename std::enable_if<(BitCount >= static_cast<std::size_t>(UINT8_C(33))) && (BitCount <= static_cast<std::size_t>(UINT8_C( 64)))>::type> { using exact_unsigned_type = std::uint64_t; using exact_signed_type = std::int64_t; using fast_unsigned_type = std::uint_fast64_t; using fast_signed_type = std::int_fast64_t; };

  template<typename UnsignedIntegralType>
  constexpr auto negate(UnsignedIntegralType u) -> typename std::enable_if<(   std::is_integral<UnsignedIntegralType>::value
                                                                            && std::is_unsigned<UnsignedIntegralType>::value), UnsignedIntegralType>::type
  {
    using local_unsigned_integral_type = UnsignedIntegralType;

    return
      static_cast<local_unsigned_integral_type>
      (
        (static_cast<local_unsigned_integral_type>(~u)) + static_cast<local_unsigned_integral_type>(UINT8_C(1))
      );
  }

  template<typename SignedIntegralType>
  constexpr auto negate(SignedIntegralType n) -> typename std::enable_if<(   std::is_integral<SignedIntegralType>::value
                                                                          && std::is_signed  <SignedIntegralType>::value), SignedIntegralType>::type
  {
    using local_signed_integral_type = SignedIntegralType;

    return
      static_cast<local_signed_integral_type>
      (
        detail::negate(static_cast<unsigned long long>(n)) // NOLINT(google-runtime-int)
      );
  }

  struct a029750
  {
    #if !defined(WIDE_DECIMAL_DISABLE_DYNAMIC_MEMORY_ALLOCATION)
    #else
    // LCOV_EXCL_START
    static constexpr auto a029750_as_constexpr(std::uint32_t value) noexcept -> std::uint32_t // NOLINT(readability-function-cognitive-complexity)
    {
      // Sloane's A029750 List of numbers of the form 2^k times 1, 3, 5 or 7.
      // CoefficientList[Series[-(x + 1)^2 (x^2 + 1)^2/(2 x^4 - 1), {x, 0, 91}], x]
      return ((value <= static_cast<std::uint32_t>(UINT32_C(     32))) ? static_cast<std::uint32_t>(UINT32_C(     32)) : ((value <=  static_cast<std::uint32_t>(UINT32_C(      40))) ?  static_cast<std::uint32_t>(UINT32_C(      40)) : ((value <= static_cast<std::uint32_t>(UINT32_C(      48))) ? static_cast<std::uint32_t>(UINT32_C(      48)) : ((value <= static_cast<std::uint32_t>(UINT32_C(      56))) ? static_cast<std::uint32_t>(UINT32_C(      56)) :
             ((value <= static_cast<std::uint32_t>(UINT32_C(     64))) ? static_cast<std::uint32_t>(UINT32_C(     64)) : ((value <=  static_cast<std::uint32_t>(UINT32_C(      80))) ?  static_cast<std::uint32_t>(UINT32_C(      80)) : ((value <= static_cast<std::uint32_t>(UINT32_C(      96))) ? static_cast<std::uint32_t>(UINT32_C(      96)) : ((value <= static_cast<std::uint32_t>(UINT32_C(     112))) ? static_cast<std::uint32_t>(UINT32_C(     112)) :
             ((value <= static_cast<std::uint32_t>(UINT32_C(    128))) ? static_cast<std::uint32_t>(UINT32_C(    128)) : ((value <=  static_cast<std::uint32_t>(UINT32_C(     160))) ?  static_cast<std::uint32_t>(UINT32_C(     160)) : ((value <= static_cast<std::uint32_t>(UINT32_C(     192))) ? static_cast<std::uint32_t>(UINT32_C(     192)) : ((value <= static_cast<std::uint32_t>(UINT32_C(     224))) ? static_cast<std::uint32_t>(UINT32_C(     224)) :
             ((value <= static_cast<std::uint32_t>(UINT32_C(    256))) ? static_cast<std::uint32_t>(UINT32_C(    256)) : ((value <=  static_cast<std::uint32_t>(UINT32_C(     320))) ?  static_cast<std::uint32_t>(UINT32_C(     320)) : ((value <= static_cast<std::uint32_t>(UINT32_C(     384))) ? static_cast<std::uint32_t>(UINT32_C(     384)) : ((value <= static_cast<std::uint32_t>(UINT32_C(     448))) ? static_cast<std::uint32_t>(UINT32_C(     448)) :
             ((value <= static_cast<std::uint32_t>(UINT32_C(    512))) ? static_cast<std::uint32_t>(UINT32_C(    512)) : ((value <=  static_cast<std::uint32_t>(UINT32_C(     640))) ?  static_cast<std::uint32_t>(UINT32_C(     640)) : ((value <= static_cast<std::uint32_t>(UINT32_C(     768))) ? static_cast<std::uint32_t>(UINT32_C(     768)) : ((value <= static_cast<std::uint32_t>(UINT32_C(     896))) ? static_cast<std::uint32_t>(UINT32_C(     896)) :
             ((value <= static_cast<std::uint32_t>(UINT32_C(   1024))) ? static_cast<std::uint32_t>(UINT32_C(   1024)) : ((value <=  static_cast<std::uint32_t>(UINT32_C(    1280))) ?  static_cast<std::uint32_t>(UINT32_C(    1280)) : ((value <= static_cast<std::uint32_t>(UINT32_C(    1536))) ? static_cast<std::uint32_t>(UINT32_C(    1536)) : ((value <= static_cast<std::uint32_t>(UINT32_C(    1792))) ? static_cast<std::uint32_t>(UINT32_C(    1792)) :
             ((value <= static_cast<std::uint32_t>(UINT32_C(   2048))) ? static_cast<std::uint32_t>(UINT32_C(   2048)) : ((value <=  static_cast<std::uint32_t>(UINT32_C(    2560))) ?  static_cast<std::uint32_t>(UINT32_C(    2560)) : ((value <= static_cast<std::uint32_t>(UINT32_C(    3072))) ? static_cast<std::uint32_t>(UINT32_C(    3072)) : ((value <= static_cast<std::uint32_t>(UINT32_C(    3584))) ? static_cast<std::uint32_t>(UINT32_C(    3584)) :
             ((value <= static_cast<std::uint32_t>(UINT32_C(   4096))) ? static_cast<std::uint32_t>(UINT32_C(   4096)) : ((value <=  static_cast<std::uint32_t>(UINT32_C(    5120))) ?  static_cast<std::uint32_t>(UINT32_C(    5120)) : ((value <= static_cast<std::uint32_t>(UINT32_C(    6144))) ? static_cast<std::uint32_t>(UINT32_C(    6144)) : ((value <= static_cast<std::uint32_t>(UINT32_C(    7168))) ? static_cast<std::uint32_t>(UINT32_C(    7168)) :
             ((value <= static_cast<std::uint32_t>(UINT32_C(   8192))) ? static_cast<std::uint32_t>(UINT32_C(   8192)) : ((value <=  static_cast<std::uint32_t>(UINT32_C(   10240))) ?  static_cast<std::uint32_t>(UINT32_C(   10240)) : ((value <= static_cast<std::uint32_t>(UINT32_C(   12288))) ? static_cast<std::uint32_t>(UINT32_C(   12288)) : ((value <= static_cast<std::uint32_t>(UINT32_C(   14336))) ? static_cast<std::uint32_t>(UINT32_C(   14336)) :
             ((value <= static_cast<std::uint32_t>(UINT32_C(  16384))) ? static_cast<std::uint32_t>(UINT32_C(  16384)) : ((value <=  static_cast<std::uint32_t>(UINT32_C(   20480))) ?  static_cast<std::uint32_t>(UINT32_C(   20480)) : ((value <= static_cast<std::uint32_t>(UINT32_C(   24576))) ? static_cast<std::uint32_t>(UINT32_C(   24576)) : ((value <= static_cast<std::uint32_t>(UINT32_C(   28672))) ? static_cast<std::uint32_t>(UINT32_C(   28672)) :
             ((value <= static_cast<std::uint32_t>(UINT32_C(  32768))) ? static_cast<std::uint32_t>(UINT32_C(  32768)) : ((value <=  static_cast<std::uint32_t>(UINT32_C(   40960))) ?  static_cast<std::uint32_t>(UINT32_C(   40960)) : ((value <= static_cast<std::uint32_t>(UINT32_C(   49152))) ? static_cast<std::uint32_t>(UINT32_C(   49152)) : ((value <= static_cast<std::uint32_t>(UINT32_C(   57344))) ? static_cast<std::uint32_t>(UINT32_C(   57344)) :
             ((value <= static_cast<std::uint32_t>(UINT32_C(  65536))) ? static_cast<std::uint32_t>(UINT32_C(  65536)) : ((value <=  static_cast<std::uint32_t>(UINT32_C(   81920))) ?  static_cast<std::uint32_t>(UINT32_C(   81920)) : ((value <= static_cast<std::uint32_t>(UINT32_C(   98304))) ? static_cast<std::uint32_t>(UINT32_C(   98304)) : ((value <= static_cast<std::uint32_t>(UINT32_C(  114688))) ? static_cast<std::uint32_t>(UINT32_C(  114688)) :
             ((value <= static_cast<std::uint32_t>(UINT32_C( 131072))) ? static_cast<std::uint32_t>(UINT32_C( 131072)) : ((value <=  static_cast<std::uint32_t>(UINT32_C(  163840))) ?  static_cast<std::uint32_t>(UINT32_C(  163840)) : ((value <= static_cast<std::uint32_t>(UINT32_C(  196608))) ? static_cast<std::uint32_t>(UINT32_C(  196608)) : ((value <= static_cast<std::uint32_t>(UINT32_C(  229376))) ? static_cast<std::uint32_t>(UINT32_C(  229376)) :
             ((value <= static_cast<std::uint32_t>(UINT32_C( 262144))) ? static_cast<std::uint32_t>(UINT32_C( 262144)) : ((value <=  static_cast<std::uint32_t>(UINT32_C(  327680))) ?  static_cast<std::uint32_t>(UINT32_C(  327680)) : ((value <= static_cast<std::uint32_t>(UINT32_C(  393216))) ? static_cast<std::uint32_t>(UINT32_C(  393216)) : ((value <= static_cast<std::uint32_t>(UINT32_C(  458752))) ? static_cast<std::uint32_t>(UINT32_C(  458752)) :
             ((value <= static_cast<std::uint32_t>(UINT32_C( 524288))) ? static_cast<std::uint32_t>(UINT32_C( 524288)) : ((value <=  static_cast<std::uint32_t>(UINT32_C(  655360))) ?  static_cast<std::uint32_t>(UINT32_C(  655360)) : ((value <= static_cast<std::uint32_t>(UINT32_C(  786432))) ? static_cast<std::uint32_t>(UINT32_C(  786432)) : ((value <= static_cast<std::uint32_t>(UINT32_C(  917504))) ? static_cast<std::uint32_t>(UINT32_C(  917504)) :
             ((value <= static_cast<std::uint32_t>(UINT32_C(1048576))) ? static_cast<std::uint32_t>(UINT32_C(1048576)) : ((value <=  static_cast<std::uint32_t>(UINT32_C( 1310720))) ?  static_cast<std::uint32_t>(UINT32_C( 1310720)) : ((value <= static_cast<std::uint32_t>(UINT32_C( 1572864))) ? static_cast<std::uint32_t>(UINT32_C( 1572864)) : ((value <= static_cast<std::uint32_t>(UINT32_C( 1835008))) ? static_cast<std::uint32_t>(UINT32_C( 1835008)) : static_cast<std::uint32_t>(UINT32_C(2097152))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))));
    }
    // LCOV_EXCL_STOP
    #endif

    static auto a029750_as_runtime_value(std::uint32_t value) noexcept -> std::uint32_t
    {
      using local_array_type = std::array<std::uint32_t, 65U>; // NOLINT(,cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)

      // Sloane's A029750 List of numbers of the form 2^k times 1, 3, 5 or 7.
      // CoefficientList[Series[-(x + 1)^2 (x^2 + 1)^2/(2 x^4 - 1), {x, 0, 91}], x]
      constexpr local_array_type a029750_data =
      {{
        static_cast<std::uint32_t>(UINT32_C(      32)), static_cast<std::uint32_t>(UINT32_C(      40)), static_cast<std::uint32_t>(UINT32_C(      48)), static_cast<std::uint32_t>(UINT32_C(      56)),
        static_cast<std::uint32_t>(UINT32_C(      64)), static_cast<std::uint32_t>(UINT32_C(      80)), static_cast<std::uint32_t>(UINT32_C(      96)), static_cast<std::uint32_t>(UINT32_C(     112)),
        static_cast<std::uint32_t>(UINT32_C(     128)), static_cast<std::uint32_t>(UINT32_C(     160)), static_cast<std::uint32_t>(UINT32_C(     192)), static_cast<std::uint32_t>(UINT32_C(     224)),
        static_cast<std::uint32_t>(UINT32_C(     256)), static_cast<std::uint32_t>(UINT32_C(     320)), static_cast<std::uint32_t>(UINT32_C(     384)), static_cast<std::uint32_t>(UINT32_C(     448)),
        static_cast<std::uint32_t>(UINT32_C(     512)), static_cast<std::uint32_t>(UINT32_C(     640)), static_cast<std::uint32_t>(UINT32_C(     768)), static_cast<std::uint32_t>(UINT32_C(     896)),
        static_cast<std::uint32_t>(UINT32_C(    1024)), static_cast<std::uint32_t>(UINT32_C(    1280)), static_cast<std::uint32_t>(UINT32_C(    1536)), static_cast<std::uint32_t>(UINT32_C(    1792)),
        static_cast<std::uint32_t>(UINT32_C(    2048)), static_cast<std::uint32_t>(UINT32_C(    2560)), static_cast<std::uint32_t>(UINT32_C(    3072)), static_cast<std::uint32_t>(UINT32_C(    3584)),
        static_cast<std::uint32_t>(UINT32_C(    4096)), static_cast<std::uint32_t>(UINT32_C(    5120)), static_cast<std::uint32_t>(UINT32_C(    6144)), static_cast<std::uint32_t>(UINT32_C(    7168)),
        static_cast<std::uint32_t>(UINT32_C(    8192)), static_cast<std::uint32_t>(UINT32_C(   10240)), static_cast<std::uint32_t>(UINT32_C(   12288)), static_cast<std::uint32_t>(UINT32_C(   14336)),
        static_cast<std::uint32_t>(UINT32_C(   16384)), static_cast<std::uint32_t>(UINT32_C(   20480)), static_cast<std::uint32_t>(UINT32_C(   24576)), static_cast<std::uint32_t>(UINT32_C(   28672)),
        static_cast<std::uint32_t>(UINT32_C(   32768)), static_cast<std::uint32_t>(UINT32_C(   40960)), static_cast<std::uint32_t>(UINT32_C(   49152)), static_cast<std::uint32_t>(UINT32_C(   57344)),
        static_cast<std::uint32_t>(UINT32_C(   65536)), static_cast<std::uint32_t>(UINT32_C(   81920)), static_cast<std::uint32_t>(UINT32_C(   98304)), static_cast<std::uint32_t>(UINT32_C(  114688)),
        static_cast<std::uint32_t>(UINT32_C(  131072)), static_cast<std::uint32_t>(UINT32_C(  163840)), static_cast<std::uint32_t>(UINT32_C(  196608)), static_cast<std::uint32_t>(UINT32_C(  229376)),
        static_cast<std::uint32_t>(UINT32_C(  262144)), static_cast<std::uint32_t>(UINT32_C(  327680)), static_cast<std::uint32_t>(UINT32_C(  393216)), static_cast<std::uint32_t>(UINT32_C(  458752)),
        static_cast<std::uint32_t>(UINT32_C(  524288)), static_cast<std::uint32_t>(UINT32_C(  655360)), static_cast<std::uint32_t>(UINT32_C(  786432)), static_cast<std::uint32_t>(UINT32_C(  917504)),
        static_cast<std::uint32_t>(UINT32_C( 1048576)), static_cast<std::uint32_t>(UINT32_C( 1310720)), static_cast<std::uint32_t>(UINT32_C( 1572864)), static_cast<std::uint32_t>(UINT32_C( 1835008)),
        static_cast<std::uint32_t>(UINT32_C( 2097152))
      }};

      const auto it = std::lower_bound(a029750_data.cbegin(), a029750_data.cend(), value); // NOLINT(llvm-qualified-auto,readability-qualified-auto)

      return ((it != a029750_data.cend()) ? *it : a029750_data.back());
    }
  };

  struct a000079
  {
    static constexpr auto a000079_as_constexpr(const std::uint32_t value) noexcept -> std::uint32_t // NOLINT(readability-function-cognitive-complexity)
    {
      // Sloane's A000079 List of numbers of powers of 2.
      // Table[2^n, {n, 0, 31, 1}]
      return ((value <= static_cast<std::uint32_t>(UINT32_C(        8))) ? static_cast<std::uint32_t>(UINT32_C(        8)) : ((value <=  static_cast<std::uint32_t>(UINT32_C(       16))) ?  static_cast<std::uint32_t>(UINT32_C(       16)) : ((value <= static_cast<std::uint32_t>(UINT32_C(       32))) ? static_cast<std::uint32_t>(UINT32_C(       32)) : ((value <= static_cast<std::uint32_t>(UINT32_C(        64))) ? static_cast<std::uint32_t>(UINT32_C(        64)) :
             ((value <= static_cast<std::uint32_t>(UINT32_C(      128))) ? static_cast<std::uint32_t>(UINT32_C(      128)) : ((value <=  static_cast<std::uint32_t>(UINT32_C(      256))) ?  static_cast<std::uint32_t>(UINT32_C(      256)) : ((value <= static_cast<std::uint32_t>(UINT32_C(      512))) ? static_cast<std::uint32_t>(UINT32_C(      512)) : ((value <= static_cast<std::uint32_t>(UINT32_C(      1024))) ? static_cast<std::uint32_t>(UINT32_C(      1024)) :
             ((value <= static_cast<std::uint32_t>(UINT32_C(     2048))) ? static_cast<std::uint32_t>(UINT32_C(     2048)) : ((value <=  static_cast<std::uint32_t>(UINT32_C(     4096))) ?  static_cast<std::uint32_t>(UINT32_C(     4096)) : ((value <= static_cast<std::uint32_t>(UINT32_C(     8192))) ? static_cast<std::uint32_t>(UINT32_C(     8192)) : ((value <= static_cast<std::uint32_t>(UINT32_C(     16384))) ? static_cast<std::uint32_t>(UINT32_C(     16384)) :
             // LCOV_EXCL_START
             ((value <= static_cast<std::uint32_t>(UINT32_C(    32768))) ? static_cast<std::uint32_t>(UINT32_C(    32768)) : ((value <=  static_cast<std::uint32_t>(UINT32_C(    65536))) ?  static_cast<std::uint32_t>(UINT32_C(    65536)) : ((value <= static_cast<std::uint32_t>(UINT32_C(   131072))) ? static_cast<std::uint32_t>(UINT32_C(   131072)) : ((value <= static_cast<std::uint32_t>(UINT32_C(    262144))) ? static_cast<std::uint32_t>(UINT32_C(    262144)) :
             ((value <= static_cast<std::uint32_t>(UINT32_C(   524288))) ? static_cast<std::uint32_t>(UINT32_C(   524288)) : ((value <=  static_cast<std::uint32_t>(UINT32_C(  1048576))) ?  static_cast<std::uint32_t>(UINT32_C(  1048576)) : ((value <= static_cast<std::uint32_t>(UINT32_C(  2097152))) ? static_cast<std::uint32_t>(UINT32_C(  2097152)) : ((value <= static_cast<std::uint32_t>(UINT32_C(   4194304))) ? static_cast<std::uint32_t>(UINT32_C(   4194304)) :
             ((value <= static_cast<std::uint32_t>(UINT32_C(  8388608))) ? static_cast<std::uint32_t>(UINT32_C(  8388608)) : ((value <=  static_cast<std::uint32_t>(UINT32_C( 16777216))) ?  static_cast<std::uint32_t>(UINT32_C( 16777216)) : ((value <= static_cast<std::uint32_t>(UINT32_C( 33554432))) ? static_cast<std::uint32_t>(UINT32_C( 33554432)) : ((value <= static_cast<std::uint32_t>(UINT32_C(  67108864))) ? static_cast<std::uint32_t>(UINT32_C(  67108864)) :
             ((value <= static_cast<std::uint32_t>(UINT32_C(134217728))) ? static_cast<std::uint32_t>(UINT32_C(134217728)) : ((value <=  static_cast<std::uint32_t>(UINT32_C(268435456))) ?  static_cast<std::uint32_t>(UINT32_C(268435456)) : ((value <= static_cast<std::uint32_t>(UINT32_C(536870912))) ? static_cast<std::uint32_t>(UINT32_C(536870912)) : ((value <= static_cast<std::uint32_t>(UINT32_C(1073741824))) ? static_cast<std::uint32_t>(UINT32_C(1073741824)) : static_cast<std::uint32_t>(UINT32_C(2147483648))))))))))))))))))))))))))))));
             // LCOV_EXCL_STOP
    }
  };

  // LCOV_EXCL_START
  constexpr auto pow10_maker(std::uint32_t n) noexcept -> std::uint32_t // NOLINT(misc-no-recursion)
  {
    // Make the constant power of 10^n.
    return
      static_cast<std::uint32_t>
      (
        (n == static_cast<std::uint32_t>(UINT8_C(0)))
          ? static_cast<std::uint32_t>(UINT8_C(1))
          : static_cast<std::uint32_t>
            (
                pow10_maker(static_cast<std::uint32_t>(n - static_cast<std::uint32_t>(UINT8_C(1))))
              * static_cast<std::uint32_t>(UINT8_C(10))
            )
      );
  }
  // LCOV_EXCL_STOP

  inline auto pow10_maker_as_runtime_value(std::uint32_t n) noexcept -> std::uint32_t
  {
    using local_array_type = std::array<std::uint32_t, static_cast<std::size_t>(UINT8_C(10))>; // NOLINT(,cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)

    constexpr local_array_type local_p10_table =
    {{
      static_cast<std::uint32_t>(UINT32_C(1)),
      static_cast<std::uint32_t>(UINT32_C(10)),
      static_cast<std::uint32_t>(UINT32_C(100)),
      static_cast<std::uint32_t>(UINT32_C(1000)),
      static_cast<std::uint32_t>(UINT32_C(10000)),
      static_cast<std::uint32_t>(UINT32_C(100000)),
      static_cast<std::uint32_t>(UINT32_C(1000000)),
      static_cast<std::uint32_t>(UINT32_C(10000000)),
      static_cast<std::uint32_t>(UINT32_C(100000000)),
      static_cast<std::uint32_t>(UINT32_C(1000000000))
    }};

    {
      using local_size_type = typename local_array_type::size_type;

      return ((n < static_cast<std::uint32_t>(std::tuple_size<local_array_type>::value))
               ? local_p10_table[static_cast<local_size_type>(n)]
               : local_p10_table.back()); // LCOV_EXCL_LINE
    }
  }

  template<typename IntegralType,
           typename ExponentType = int>
  inline auto order_of_builtin_integer(const IntegralType n, ExponentType* p10_ptr = nullptr) -> unsigned
  {
    // This subroutine returns the order of an input integral type.
    // The order is counted as 1 for 0...9, 2 for 10...99, 3 for 100...999, etc.
    // This may differ from the order expected, for example, from the ilogb()
    // function. So this must be taken into account at the calling point
    // of this subroutine if needed.

    static_assert(std::is_integral<IntegralType>::value, "Error: This template is intended for IntegralType to be of actual integral type");
    static_assert(std::is_integral<ExponentType>::value, "Error: This template is intended for ExponentType to be of actual integral type");

    using local_unsigned_integral_type = typename uint_type_helper<std::numeric_limits<IntegralType>::digits + (std::is_signed<IntegralType>::value ? 1 : 0)>::exact_unsigned_type;
    using local_unsigned_exponent_type = typename uint_type_helper<std::numeric_limits<ExponentType>::digits + (std::is_signed<ExponentType>::value ? 1 : 0)>::exact_unsigned_type;

    auto expval = static_cast<unsigned>(UINT8_C(0));
    auto p10    = static_cast<local_unsigned_exponent_type>(UINT8_C(1));

    auto un = static_cast<local_unsigned_integral_type>(n);

    for(;;)
    {
      un = static_cast<local_unsigned_integral_type>(un / static_cast<local_unsigned_integral_type>(UINT8_C(10U)));

      p10 = static_cast<local_unsigned_exponent_type>(p10 * static_cast<local_unsigned_exponent_type>(UINT8_C(10)));

      ++expval;

      if(un == static_cast<local_unsigned_exponent_type>(UINT8_C(0)))
      {
        break;
      }
    }

    if(p10_ptr != nullptr)
    {
      *p10_ptr = static_cast<ExponentType>(p10);
    }

    return expval;
  }

  template<typename LimbType>
  struct decwide_t_helper_base
  {
  private:
    using local_limb_type = LimbType;

  public:
    static constexpr std::int32_t elem_digits10 =
      (std::is_same<local_limb_type, std::uint32_t>::value
        ? static_cast<std::int32_t>(INT8_C(8))
        : (std::is_same<local_limb_type, std::uint16_t>::value ? static_cast<std::int32_t>(INT8_C(4))
                                                               : static_cast<std::int32_t>(INT8_C(2))));

    static constexpr auto elem_mask      = static_cast<std::int32_t>(pow10_maker(static_cast<std::uint32_t>(elem_digits10)));
    static constexpr auto elem_mask_half = static_cast<std::int32_t>(pow10_maker(static_cast<std::uint32_t>(elem_digits10 / 2)));

    static constexpr auto digit_at_pos_in_limb(local_limb_type u, unsigned pos) noexcept -> std::uint8_t
    {
      return
        static_cast<std::uint8_t>
        (
          static_cast<local_limb_type>
          (
              static_cast<local_limb_type>(u / pow10_maker_as_runtime_value(static_cast<std::uint32_t>(pos)))
            % static_cast<local_limb_type>(UINT8_C(10)) // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
          )
        );
    }
  };

  template<typename LimbType> constexpr std::int32_t decwide_t_helper_base<LimbType>::elem_digits10;  // NOLINT(readability-redundant-declaration)
  template<typename LimbType> constexpr std::int32_t decwide_t_helper_base<LimbType>::elem_mask;      // NOLINT(readability-redundant-declaration)
  template<typename LimbType> constexpr std::int32_t decwide_t_helper_base<LimbType>::elem_mask_half; // NOLINT(readability-redundant-declaration)

  template<const std::int32_t ParamDigitsBaseTen,
           typename LimbType>
  struct decwide_t_helper : decwide_t_helper_base<LimbType>
  {
  private:
    using base_class_type = decwide_t_helper_base<LimbType>;

  public:
    static constexpr auto digits10          = ParamDigitsBaseTen;
    static constexpr auto digits            = digits10;
    static constexpr auto max_digits10      = static_cast<std::int32_t>(digits10 + static_cast<std::int32_t>(INT32_C(4)));
    static constexpr auto radix             = static_cast<std::int32_t>(INT32_C(10));

    static constexpr auto elem_number_extra = static_cast<std::int32_t>(INT32_C(3));
    static constexpr auto elem_number       = static_cast<std::int32_t>(((digits10 / base_class_type::elem_digits10) + (((digits10 % base_class_type::elem_digits10) != 0) ? 1 : 0)) + elem_number_extra);
  };

  template<const std::int32_t ParamDigitsBaseTen, typename LimbType> constexpr std::int32_t decwide_t_helper<ParamDigitsBaseTen, LimbType>::digits10;          // NOLINT(readability-redundant-declaration,hicpp-uppercase-literal-suffix,readability-uppercase-literal-suffix)
  template<const std::int32_t ParamDigitsBaseTen, typename LimbType> constexpr std::int32_t decwide_t_helper<ParamDigitsBaseTen, LimbType>::digits;            // NOLINT(readability-redundant-declaration,hicpp-uppercase-literal-suffix,readability-uppercase-literal-suffix)
  template<const std::int32_t ParamDigitsBaseTen, typename LimbType> constexpr std::int32_t decwide_t_helper<ParamDigitsBaseTen, LimbType>::max_digits10;      // NOLINT(readability-redundant-declaration,hicpp-uppercase-literal-suffix,readability-uppercase-literal-suffix)
  template<const std::int32_t ParamDigitsBaseTen, typename LimbType> constexpr std::int32_t decwide_t_helper<ParamDigitsBaseTen, LimbType>::radix;             // NOLINT(readability-redundant-declaration,hicpp-uppercase-literal-suffix,readability-uppercase-literal-suffix)
  template<const std::int32_t ParamDigitsBaseTen, typename LimbType> constexpr std::int32_t decwide_t_helper<ParamDigitsBaseTen, LimbType>::elem_number_extra; // NOLINT(readability-redundant-declaration,hicpp-uppercase-literal-suffix,readability-uppercase-literal-suffix)
  template<const std::int32_t ParamDigitsBaseTen, typename LimbType> constexpr std::int32_t decwide_t_helper<ParamDigitsBaseTen, LimbType>::elem_number;       // NOLINT(readability-redundant-declaration,hicpp-uppercase-literal-suffix,readability-uppercase-literal-suffix)

  template<typename MyType,
           const std::size_t MySize,
           typename MyAlloc>
  class fixed_dynamic_array final : public util::dynamic_array<MyType, MyAlloc, std::size_t, ptrdiff_t>
  {
  private:
    using base_class_type = util::dynamic_array<MyType, MyAlloc, std::size_t, ptrdiff_t>;

  public:
    static constexpr auto static_size() -> typename base_class_type::size_type { return MySize; }

    explicit fixed_dynamic_array(const typename base_class_type::size_type       s = MySize, // NOLINT(hicpp-uppercase-literal-suffix,readability-uppercase-literal-suffix)
                                 const typename base_class_type::value_type&     v = typename base_class_type::value_type(),
                                 const typename base_class_type::allocator_type& a = typename base_class_type::allocator_type()) noexcept
      : base_class_type(MySize, typename base_class_type::value_type(), a)
    {
      std::fill(base_class_type::begin(),
                base_class_type::begin() + (std::min)(MySize, static_cast<typename base_class_type::size_type>(s)),
                v);
    }

    constexpr fixed_dynamic_array(const fixed_dynamic_array& other)
      : base_class_type(static_cast<const base_class_type&>(other)) { }

    fixed_dynamic_array(std::initializer_list<typename base_class_type::value_type> lst)
      : base_class_type(MySize)
    {
      std::copy(lst.begin(),
                lst.begin() + (std::min)(static_cast<typename base_class_type::size_type>(lst.size()), MySize),
                base_class_type::begin());
    }

    constexpr fixed_dynamic_array(fixed_dynamic_array&& other) noexcept
      : base_class_type(static_cast<base_class_type&&>(other)) { }

    auto operator=(const fixed_dynamic_array& other) -> fixed_dynamic_array& // NOLINT(cert-oop54-cpp)
    {
      if(this != &other)
      {
        base_class_type::operator=(static_cast<const base_class_type&>(other));
      }

      return *this;
    }

    auto operator=(fixed_dynamic_array&& other) noexcept -> fixed_dynamic_array&
    {
      base_class_type::operator=(static_cast<base_class_type&&>(other));

      return *this;
    }

    ~fixed_dynamic_array() override = default;
  };

  template<typename MyType,
           const std::size_t MySize>
  class fixed_static_array final : public std::array<MyType, static_cast<std::size_t>(MySize)>
  {
  private:
    using base_class_type = std::array<MyType, static_cast<std::size_t>(MySize)>;

  public:
    using size_type  = std::size_t;
    using value_type = typename base_class_type::value_type;

    static constexpr auto static_size() -> size_type { return MySize; }

    constexpr fixed_static_array() = default; // LCOV_EXCL_LINE

    explicit fixed_static_array(const size_type   s,
                                                       const value_type& v = value_type())
    {
      if(s < static_size())
      {
        std::fill(base_class_type::begin(),     base_class_type::begin() + s, v);
        std::fill(base_class_type::begin() + s, base_class_type::end(),       value_type());
      }
      else
      {
        base_class_type::fill(v);
      }
    }

    fixed_static_array(const fixed_static_array&) = default;
    fixed_static_array(fixed_static_array&&) noexcept = default;

    fixed_static_array(std::initializer_list<typename base_class_type::value_type> lst)
    {
      const auto size_to_copy =
        (std::min)(static_cast<size_type>(lst.size()),
                   static_cast<size_type>(MySize));

      if(size_to_copy < static_cast<size_type>(base_class_type::size()))
      {
        std::copy(lst.begin(),
                  lst.begin() + size_to_copy,
                  base_class_type::begin());

        std::fill(base_class_type::begin() + size_to_copy,
                  base_class_type::end(),
                  static_cast<typename base_class_type::value_type>(UINT8_C(0)));
      }
      else
      {
        std::copy(lst.begin(),
                  lst.begin() + size_to_copy,
                  base_class_type::begin());
      }
    }

    ~fixed_static_array() = default; // LCOV_EXCL_LINE

    auto operator=(const fixed_static_array& other_array) -> fixed_static_array& = default;
    auto operator=(fixed_static_array&& other_array) noexcept -> fixed_static_array& = default;

    auto operator[](const size_type i)       -> typename base_class_type::reference       { return base_class_type::operator[](static_cast<typename base_class_type::size_type>(i)); }
    auto operator[](const size_type i) const -> typename base_class_type::const_reference { return base_class_type::operator[](static_cast<typename base_class_type::size_type>(i)); }
  };

  enum class os_float_field_type
  {
    scientific,
    fixed,
    none
  };

  template<typename UnsignedIntegerType,
           typename SignedIntegerType>
  struct unsigned_wrap
  {
    using unsigned_type = UnsignedIntegerType;
    using   signed_type =   SignedIntegerType;

    constexpr explicit unsigned_wrap(signed_type n) noexcept
      : my_neg  (n < static_cast<signed_type>(INT8_C(0))),
        my_value(static_cast<unsigned_type>((!my_neg ) ? static_cast<unsigned_type>(n)
                                                       : static_cast<unsigned_type>(static_cast<unsigned_type>(~static_cast<unsigned_type>(n)) + static_cast<unsigned_type>(UINT8_C(1))))) { }

    constexpr unsigned_wrap(const unsigned_wrap& other) noexcept
      : my_neg  (other.my_neg),
        my_value(other.my_value) { }

    constexpr unsigned_wrap(unsigned_wrap&& other) noexcept
      : my_neg  (other.my_neg),
        my_value(other.my_value) { }

    ~unsigned_wrap() noexcept = default; // LCOV_EXCL_LINE

    auto operator=(const unsigned_wrap& other) noexcept -> unsigned_wrap&
    {
      if(this != &other)
      {
        my_neg   = other.my_neg;
        my_value = other.my_value;
      }

      return *this;
    }

    auto operator=(unsigned_wrap&& other) noexcept -> unsigned_wrap&
    {
      my_neg   = other.my_neg;
      my_value = other.my_value;

      return *this;
    }

    WIDE_DECIMAL_NODISCARD auto constexpr get_value_unsigned() const noexcept -> unsigned_type { return my_value; }
    WIDE_DECIMAL_NODISCARD auto constexpr get_value_signed  () const noexcept ->   signed_type { return static_cast<signed_type>((!my_neg) ? static_cast<signed_type>(my_value) : -static_cast<signed_type>(my_value)); }
    WIDE_DECIMAL_NODISCARD auto constexpr get_is_neg        () const noexcept -> bool          { return my_neg; }

    bool          my_neg;   // NOLINT(misc-non-private-member-variables-in-classes)
    unsigned_type my_value; // NOLINT(misc-non-private-member-variables-in-classes)

    auto operator+=(const unsigned_wrap& other) noexcept -> unsigned_wrap&
    {
      if(my_neg == other.my_neg)
      {
        // +3 + (+2)
        // -3 + (-2)
        my_value = static_cast<unsigned_type>(my_value + other.my_value);
      }
      else
      {
        if(!my_neg)
        {
          if(my_value > other.my_value)
          {
            // +3 + (-2)
            my_value = static_cast<unsigned_type>(my_value + static_cast<unsigned_type>(static_cast<unsigned_type>(~static_cast<unsigned_type>(other.my_value)) + static_cast<unsigned_type>(UINT8_C(1))));
          }
          else
          {
            // +2 + (-3)
            my_value = static_cast<unsigned_type>(other.my_value + static_cast<unsigned_type>(static_cast<unsigned_type>(~static_cast<unsigned_type>(my_value)) + static_cast<unsigned_type>(UINT8_C(1))));

            my_neg = (my_value != static_cast<unsigned_type>(UINT8_C(0)));
          }
        }
        else
        {
          if(my_value > other.my_value)
          {
            // -3 + (+2)
            my_value = static_cast<unsigned_type>(my_value + static_cast<unsigned_type>(static_cast<unsigned_type>(~static_cast<unsigned_type>(other.my_value)) + static_cast<unsigned_type>(UINT8_C(1))));
          }
          else
          {
            // -2 + (+3)
            my_value = static_cast<unsigned_type>(other.my_value + static_cast<unsigned_type>(static_cast<unsigned_type>(~static_cast<unsigned_type>(my_value)) + static_cast<unsigned_type>(UINT8_C(1))));

            my_neg = false;
          }
        }
      }

      return *this;
    }

    auto operator-=(const unsigned_wrap& other) noexcept -> unsigned_wrap&
    {
      if(my_value == static_cast<unsigned_type>(UINT8_C(0)))
      {
        if(other.my_value != static_cast<unsigned_type>(UINT8_C(0)))
        {
          my_value = other.my_value;

          my_neg = (!other.my_neg);
        }
      }
      else
      {
        my_neg = (!my_neg);
        operator+=(other);
        my_neg = ((my_value != static_cast<unsigned_type>(UINT8_C(0))) ? (!my_neg) : false);
      }

      return *this;
    }
  };

  template<typename UnsignedIntegerType, typename SignedIntegerType> inline auto operator+(const unsigned_wrap<UnsignedIntegerType, SignedIntegerType>& a, const unsigned_wrap<UnsignedIntegerType, SignedIntegerType>& b) -> unsigned_wrap<UnsignedIntegerType, SignedIntegerType> { return unsigned_wrap<UnsignedIntegerType, SignedIntegerType>(a) += b; }
  template<typename UnsignedIntegerType, typename SignedIntegerType> inline auto operator-(const unsigned_wrap<UnsignedIntegerType, SignedIntegerType>& a, const unsigned_wrap<UnsignedIntegerType, SignedIntegerType>& b) -> unsigned_wrap<UnsignedIntegerType, SignedIntegerType> { return unsigned_wrap<UnsignedIntegerType, SignedIntegerType>(a) -= b; }

  #if(__cplusplus >= 201703L)
  } // namespace math::wide_decimal::detail
  #else
  } // namespace detail
  } // namespace wide_decimal
  } // namespace math
  #endif

  WIDE_DECIMAL_NAMESPACE_END

#endif // DECWIDE_T_DETAIL_2020_10_26_H
