///////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 1999 - 2022.                 //
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

  template<typename UnsignedIntegralType>
  constexpr auto negate(UnsignedIntegralType u) -> typename std::enable_if<(   std::is_integral<UnsignedIntegralType>::value
                                                                            && std::is_unsigned<UnsignedIntegralType>::value), UnsignedIntegralType>::type
  {
    using local_unsigned_integral_type = UnsignedIntegralType;

    return
      static_cast<local_unsigned_integral_type>
      (
        (static_cast<local_unsigned_integral_type>(~u)) + static_cast<local_unsigned_integral_type>(1U)
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
      return ((value <= UINT32_C(     32)) ? UINT32_C(     32) : ((value <=  UINT32_C(      40)) ?  UINT32_C(      40) : ((value <= UINT32_C(      48)) ? UINT32_C(      48) : ((value <= UINT32_C(      56)) ? UINT32_C(      56) :
             ((value <= UINT32_C(     64)) ? UINT32_C(     64) : ((value <=  UINT32_C(      80)) ?  UINT32_C(      80) : ((value <= UINT32_C(      96)) ? UINT32_C(      96) : ((value <= UINT32_C(     112)) ? UINT32_C(     112) :
             ((value <= UINT32_C(    128)) ? UINT32_C(    128) : ((value <=  UINT32_C(     160)) ?  UINT32_C(     160) : ((value <= UINT32_C(     192)) ? UINT32_C(     192) : ((value <= UINT32_C(     224)) ? UINT32_C(     224) :
             ((value <= UINT32_C(    256)) ? UINT32_C(    256) : ((value <=  UINT32_C(     320)) ?  UINT32_C(     320) : ((value <= UINT32_C(     384)) ? UINT32_C(     384) : ((value <= UINT32_C(     448)) ? UINT32_C(     448) :
             ((value <= UINT32_C(    512)) ? UINT32_C(    512) : ((value <=  UINT32_C(     640)) ?  UINT32_C(     640) : ((value <= UINT32_C(     768)) ? UINT32_C(     768) : ((value <= UINT32_C(     896)) ? UINT32_C(     896) :
             ((value <= UINT32_C(   1024)) ? UINT32_C(   1024) : ((value <=  UINT32_C(    1280)) ?  UINT32_C(    1280) : ((value <= UINT32_C(    1536)) ? UINT32_C(    1536) : ((value <= UINT32_C(    1792)) ? UINT32_C(    1792) :
             ((value <= UINT32_C(   2048)) ? UINT32_C(   2048) : ((value <=  UINT32_C(    2560)) ?  UINT32_C(    2560) : ((value <= UINT32_C(    3072)) ? UINT32_C(    3072) : ((value <= UINT32_C(    3584)) ? UINT32_C(    3584) :
             ((value <= UINT32_C(   4096)) ? UINT32_C(   4096) : ((value <=  UINT32_C(    5120)) ?  UINT32_C(    5120) : ((value <= UINT32_C(    6144)) ? UINT32_C(    6144) : ((value <= UINT32_C(    7168)) ? UINT32_C(    7168) :
             ((value <= UINT32_C(   8192)) ? UINT32_C(   8192) : ((value <=  UINT32_C(   10240)) ?  UINT32_C(   10240) : ((value <= UINT32_C(   12288)) ? UINT32_C(   12288) : ((value <= UINT32_C(   14336)) ? UINT32_C(   14336) :
             ((value <= UINT32_C(  16384)) ? UINT32_C(  16384) : ((value <=  UINT32_C(   20480)) ?  UINT32_C(   20480) : ((value <= UINT32_C(   24576)) ? UINT32_C(   24576) : ((value <= UINT32_C(   28672)) ? UINT32_C(   28672) :
             ((value <= UINT32_C(  32768)) ? UINT32_C(  32768) : ((value <=  UINT32_C(   40960)) ?  UINT32_C(   40960) : ((value <= UINT32_C(   49152)) ? UINT32_C(   49152) : ((value <= UINT32_C(   57344)) ? UINT32_C(   57344) :
             ((value <= UINT32_C(  65536)) ? UINT32_C(  65536) : ((value <=  UINT32_C(   81920)) ?  UINT32_C(   81920) : ((value <= UINT32_C(   98304)) ? UINT32_C(   98304) : ((value <= UINT32_C(  114688)) ? UINT32_C(  114688) :
             ((value <= UINT32_C( 131072)) ? UINT32_C( 131072) : ((value <=  UINT32_C(  163840)) ?  UINT32_C(  163840) : ((value <= UINT32_C(  196608)) ? UINT32_C(  196608) : ((value <= UINT32_C(  229376)) ? UINT32_C(  229376) :
             ((value <= UINT32_C( 262144)) ? UINT32_C( 262144) : ((value <=  UINT32_C(  327680)) ?  UINT32_C(  327680) : ((value <= UINT32_C(  393216)) ? UINT32_C(  393216) : ((value <= UINT32_C(  458752)) ? UINT32_C(  458752) :
             ((value <= UINT32_C( 524288)) ? UINT32_C( 524288) : ((value <=  UINT32_C(  655360)) ?  UINT32_C(  655360) : ((value <= UINT32_C(  786432)) ? UINT32_C(  786432) : ((value <= UINT32_C(  917504)) ? UINT32_C(  917504) :
             ((value <= UINT32_C(1048576)) ? UINT32_C(1048576) : ((value <=  UINT32_C( 1310720)) ?  UINT32_C( 1310720) : ((value <= UINT32_C( 1572864)) ? UINT32_C( 1572864) : ((value <= UINT32_C( 1835008)) ? UINT32_C( 1835008) : UINT32_C(2097152)))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))));
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
        UINT32_C(      32), UINT32_C(      40), UINT32_C(      48), UINT32_C(      56),
        UINT32_C(      64), UINT32_C(      80), UINT32_C(      96), UINT32_C(     112),
        UINT32_C(     128), UINT32_C(     160), UINT32_C(     192), UINT32_C(     224),
        UINT32_C(     256), UINT32_C(     320), UINT32_C(     384), UINT32_C(     448),
        UINT32_C(     512), UINT32_C(     640), UINT32_C(     768), UINT32_C(     896),
        UINT32_C(    1024), UINT32_C(    1280), UINT32_C(    1536), UINT32_C(    1792),
        UINT32_C(    2048), UINT32_C(    2560), UINT32_C(    3072), UINT32_C(    3584),
        UINT32_C(    4096), UINT32_C(    5120), UINT32_C(    6144), UINT32_C(    7168),
        UINT32_C(    8192), UINT32_C(   10240), UINT32_C(   12288), UINT32_C(   14336),
        UINT32_C(   16384), UINT32_C(   20480), UINT32_C(   24576), UINT32_C(   28672),
        UINT32_C(   32768), UINT32_C(   40960), UINT32_C(   49152), UINT32_C(   57344),
        UINT32_C(   65536), UINT32_C(   81920), UINT32_C(   98304), UINT32_C(  114688),
        UINT32_C(  131072), UINT32_C(  163840), UINT32_C(  196608), UINT32_C(  229376),
        UINT32_C(  262144), UINT32_C(  327680), UINT32_C(  393216), UINT32_C(  458752),
        UINT32_C(  524288), UINT32_C(  655360), UINT32_C(  786432), UINT32_C(  917504),
        UINT32_C( 1048576), UINT32_C( 1310720), UINT32_C( 1572864), UINT32_C( 1835008),
        UINT32_C( 2097152)
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
      return ((value <= UINT32_C(        8)) ? UINT32_C(        8) : ((value <=  UINT32_C(       16)) ?  UINT32_C(       16) : ((value <= UINT32_C(       32)) ? UINT32_C(       32) : ((value <= UINT32_C(        64)) ? UINT32_C(        64) :
             ((value <= UINT32_C(      128)) ? UINT32_C(      128) : ((value <=  UINT32_C(      256)) ?  UINT32_C(      256) : ((value <= UINT32_C(      512)) ? UINT32_C(      512) : ((value <= UINT32_C(      1024)) ? UINT32_C(      1024) :
             ((value <= UINT32_C(     2048)) ? UINT32_C(     2048) : ((value <=  UINT32_C(     4096)) ?  UINT32_C(     4096) : ((value <= UINT32_C(     8192)) ? UINT32_C(     8192) : ((value <= UINT32_C(     16384)) ? UINT32_C(     16384) :
             // LCOV_EXCL_START
             ((value <= UINT32_C(    32768)) ? UINT32_C(    32768) : ((value <=  UINT32_C(    65536)) ?  UINT32_C(    65536) : ((value <= UINT32_C(   131072)) ? UINT32_C(   131072) : ((value <= UINT32_C(    262144)) ? UINT32_C(    262144) :
             ((value <= UINT32_C(   524288)) ? UINT32_C(   524288) : ((value <=  UINT32_C(  1048576)) ?  UINT32_C(  1048576) : ((value <= UINT32_C(  2097152)) ? UINT32_C(  2097152) : ((value <= UINT32_C(   4194304)) ? UINT32_C(   4194304) :
             ((value <= UINT32_C(  8388608)) ? UINT32_C(  8388608) : ((value <=  UINT32_C( 16777216)) ?  UINT32_C( 16777216) : ((value <= UINT32_C( 33554432)) ? UINT32_C( 33554432) : ((value <= UINT32_C(  67108864)) ? UINT32_C(  67108864) :
             ((value <= UINT32_C(134217728)) ? UINT32_C(134217728) : ((value <=  UINT32_C(268435456)) ?  UINT32_C(268435456) : ((value <= UINT32_C(536870912)) ? UINT32_C(536870912) : ((value <= UINT32_C(1073741824)) ? UINT32_C(1073741824) : UINT32_C(2147483648)))))))))))))))))))))))))))));
             // LCOV_EXCL_STOP
    }
  };

  // LCOV_EXCL_START
  constexpr auto pow10_maker(std::uint32_t n) noexcept -> std::uint32_t // NOLINT(misc-no-recursion)
  {
    // Make the constant power of 10^n.
    return ((n == UINT32_C(0)) ? UINT32_C(1) : pow10_maker(n - UINT32_C(1)) * UINT32_C(10));
  }
  // LCOV_EXCL_STOP

  static inline auto pow10_maker_as_runtime_value(std::uint32_t n) noexcept -> std::uint32_t
  {
    using local_array_type = std::array<std::uint32_t, 10U>; // NOLINT(,cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)

    constexpr local_array_type local_p10_table =
    {{
      UINT32_C(1),
      UINT32_C(10),
      UINT32_C(100),
      UINT32_C(1000),
      UINT32_C(10000),
      UINT32_C(100000),
      UINT32_C(1000000),
      UINT32_C(10000000),
      UINT32_C(100000000),
      UINT32_C(1000000000)
    }};

    return ((n < static_cast<std::uint32_t>(std::tuple_size<local_array_type>::value))
             ? local_p10_table[typename local_array_type::size_type(n)]
             : local_p10_table.back()); // LCOV_EXCL_LINE
  }

  template<typename LimbType>
  struct decwide_t_helper_base
  {
    static constexpr std::int32_t elem_digits10     =
      (std::is_same<LimbType, std::uint32_t>::value
        ? static_cast<std::int32_t>(8)
        : (std::is_same<LimbType, std::uint16_t>::value ? static_cast<std::int32_t>(4)
                                                        : static_cast<std::int32_t>(2)));

    static constexpr auto elem_mask      = static_cast<std::int32_t>(pow10_maker(static_cast<std::uint32_t>(elem_digits10)));
    static constexpr auto elem_mask_half = static_cast<std::int32_t>(pow10_maker(static_cast<std::uint32_t>(elem_digits10 / 2)));

    static constexpr auto digit_at_pos_in_limb(LimbType u, unsigned pos) noexcept -> std::uint8_t
    {
      return
        static_cast<std::uint8_t>
        (
          static_cast<LimbType>
          (
              static_cast<LimbType>(u / pow10_maker_as_runtime_value(static_cast<std::uint32_t>(pos)))
            % static_cast<LimbType>(10U) // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
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
    static constexpr std::int32_t digits10          = ParamDigitsBaseTen;
    static constexpr std::int32_t digits            = digits10;
    static constexpr std::int32_t max_digits10      = static_cast<std::int32_t>(digits10 + 4);
    static constexpr std::int32_t radix             = static_cast<std::int32_t>(INT32_C(10));

    static constexpr std::int32_t elem_number_extra = static_cast<std::int32_t>(INT32_C(3));
    static constexpr std::int32_t elem_number       = static_cast<std::int32_t>(((digits10 / base_class_type::elem_digits10) + (((digits10 % base_class_type::elem_digits10) != 0) ? 1 : 0)) + elem_number_extra);
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
                                 const typename base_class_type::allocator_type& a = typename base_class_type::allocator_type())
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
                  static_cast<typename base_class_type::value_type>(0U));
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

    constexpr explicit unsigned_wrap(signed_type n)
      : my_neg  (n < static_cast<signed_type>(0)),
        my_value(static_cast<unsigned_type>((!my_neg ) ? static_cast<unsigned_type>(n)
                                                       : static_cast<unsigned_type>(static_cast<unsigned_type>(~static_cast<unsigned_type>(n)) + 1U))) { }

    constexpr unsigned_wrap(const unsigned_wrap& other)
      : my_neg  (other.my_neg),
        my_value(other.my_value) { }

    constexpr unsigned_wrap(unsigned_wrap&& other) noexcept
      : my_neg  (other.my_neg),
        my_value(other.my_value) { }

    ~unsigned_wrap() = default; // LCOV_EXCL_LINE

    auto operator=(const unsigned_wrap& other) -> unsigned_wrap&
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

    WIDE_DECIMAL_NODISCARD auto constexpr get_value_unsigned() const -> unsigned_type { return my_value; }
    WIDE_DECIMAL_NODISCARD auto constexpr get_value_signed  () const ->   signed_type { return ((!my_neg) ? static_cast<signed_type>(my_value) : -static_cast<signed_type>(my_value)); }

    WIDE_DECIMAL_NODISCARD auto constexpr get_is_neg        () const -> bool { return my_neg; }

    bool          my_neg;   // NOLINT(misc-non-private-member-variables-in-classes)
    unsigned_type my_value; // NOLINT(misc-non-private-member-variables-in-classes)

    auto operator+=(const unsigned_wrap& other) -> unsigned_wrap&
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
            my_value = static_cast<unsigned_type>(my_value + static_cast<unsigned_type>(static_cast<unsigned_type>(~static_cast<unsigned_type>(other.my_value)) + 1U));
          }
          else
          {
            // +2 + (-3)
            my_value = static_cast<unsigned_type>(other.my_value + static_cast<unsigned_type>(static_cast<unsigned_type>(~static_cast<unsigned_type>(my_value)) + 1U));

            my_neg = (my_value != 0U);
          }
        }
        else
        {
          if(my_value > other.my_value)
          {
            // -3 + (+2)
            my_value = static_cast<unsigned_type>(my_value + static_cast<unsigned_type>(static_cast<unsigned_type>(~static_cast<unsigned_type>(other.my_value)) + 1U));
          }
          else
          {
            // -2 + (+3)
            my_value = static_cast<unsigned_type>(other.my_value + static_cast<unsigned_type>(static_cast<unsigned_type>(~static_cast<unsigned_type>(my_value)) + 1U));

            my_neg = false;
          }
        }
      }

      return *this;
    }

    auto operator-=(const unsigned_wrap& other) -> unsigned_wrap&
    {
      if(my_value == 0U)
      {
        if(other.my_value != 0U)
        {
          my_value = other.my_value;

          my_neg = (!other.my_neg);
        }
      }
      else
      {
        my_neg = (!my_neg);
        operator+=(other);
        my_neg = (my_value != 0U) ? (!my_neg) : false;
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
