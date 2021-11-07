///////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 1999 - 2021.                 //
//  Distributed under the Boost Software License,                //
//  Version 1.0. (See accompanying file LICENSE_1_0.txt          //
//  or copy at http://www.boost.org/LICENSE_1_0.txt)             //
///////////////////////////////////////////////////////////////////

// This work is also based on an earlier work:
// "Algorithm 910: A Portable C++ Multiple-Precision System for Special-Function Calculations",
// in ACM TOMS, {VOL 37, ISSUE 4, (February 2011)} (C) ACM, 2011. http://doi.acm.org/10.1145/1916461.1916469

// This file implements various details for decwide_t.

#ifndef DECWIDE_T_DETAIL_2020_10_26_H_
  #define DECWIDE_T_DETAIL_2020_10_26_H_

  #include <algorithm>
  #include <array>
  #include <cstdint>
  #include <initializer_list>
  #include <memory>

  #include <util/utility/util_dynamic_array.h>

  namespace math { namespace wide_decimal { namespace detail {

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
    return (SignedIntegralType) detail::negate((unsigned long long) n);
  }

  struct a029750
  {
    static constexpr std::uint32_t a029750_as_constexpr(const std::uint32_t value)
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

    static std::uint32_t a029750_as_runtime_value(const std::uint32_t value)
    {
      using array_type = std::array<std::uint32_t, 65U>;

      // Sloane's A029750 List of numbers of the form 2^k times 1, 3, 5 or 7.
      // CoefficientList[Series[-(x + 1)^2 (x^2 + 1)^2/(2 x^4 - 1), {x, 0, 91}], x]
      constexpr array_type a029750_data =
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

      const typename array_type::const_iterator it =
        std::lower_bound(a029750_data.cbegin(), a029750_data.cend(), value);

      return ((it != a029750_data.cend()) ? *it : a029750_data.back());
    }
  };

  struct a000079
  {
    static constexpr std::uint32_t a000079_as_constexpr(const std::uint32_t value)
    {
      // Sloane's A000079 List of numbers of powers of 2.
      // Table[2^n, {n, 0, 31, 1}]
      return ((value <= UINT32_C(        8)) ? UINT32_C(        8) : ((value <=  UINT32_C(       16)) ?  UINT32_C(       16) : ((value <= UINT32_C(       32)) ? UINT32_C(       32) : ((value <= UINT32_C(        64)) ? UINT32_C(        64) :
             ((value <= UINT32_C(      128)) ? UINT32_C(      128) : ((value <=  UINT32_C(      256)) ?  UINT32_C(      256) : ((value <= UINT32_C(      512)) ? UINT32_C(      512) : ((value <= UINT32_C(      1024)) ? UINT32_C(      1024) :
             ((value <= UINT32_C(     2048)) ? UINT32_C(     2048) : ((value <=  UINT32_C(     4096)) ?  UINT32_C(     4096) : ((value <= UINT32_C(     8192)) ? UINT32_C(     8192) : ((value <= UINT32_C(     16384)) ? UINT32_C(     16384) :
             ((value <= UINT32_C(    32768)) ? UINT32_C(    32768) : ((value <=  UINT32_C(    65536)) ?  UINT32_C(    65536) : ((value <= UINT32_C(   131072)) ? UINT32_C(   131072) : ((value <= UINT32_C(    262144)) ? UINT32_C(    262144) :
             ((value <= UINT32_C(   524288)) ? UINT32_C(   524288) : ((value <=  UINT32_C(  1048576)) ?  UINT32_C(  1048576) : ((value <= UINT32_C(  2097152)) ? UINT32_C(  2097152) : ((value <= UINT32_C(   4194304)) ? UINT32_C(   4194304) :
             ((value <= UINT32_C(  8388608)) ? UINT32_C(  8388608) : ((value <=  UINT32_C( 16777216)) ?  UINT32_C( 16777216) : ((value <= UINT32_C( 33554432)) ? UINT32_C( 33554432) : ((value <= UINT32_C(  67108864)) ? UINT32_C(  67108864) :
             ((value <= UINT32_C(134217728)) ? UINT32_C(134217728) : ((value <=  UINT32_C(268435456)) ?  UINT32_C(268435456) : ((value <= UINT32_C(536870912)) ? UINT32_C(536870912) : ((value <= UINT32_C(1073741824)) ? UINT32_C(1073741824) : UINT32_C(2147483648)))))))))))))))))))))))))))));
    }

    static std::uint32_t a000079_as_runtime_value(const std::uint32_t value)
    {
      using array_type = std::array<std::uint32_t, 29U>;

      // Sloane's A000079 List of numbers of powers of 2.
      // Table[2^n, {n, 0, 31, 1}]
      constexpr array_type a000079_data =
      {{
        UINT32_C(         8), UINT32_C(       16), UINT32_C(       32), UINT32_C(        64),
        UINT32_C(       128), UINT32_C(      256), UINT32_C(      512), UINT32_C(      1024),
        UINT32_C(      2048), UINT32_C(     4096), UINT32_C(     8192), UINT32_C(     16384),
        UINT32_C(     32768), UINT32_C(    65536), UINT32_C(   131072), UINT32_C(    262144),
        UINT32_C(    524288), UINT32_C(  1048576), UINT32_C(  2097152), UINT32_C(   4194304),
        UINT32_C(   8388608), UINT32_C( 16777216), UINT32_C( 33554432), UINT32_C(  67108864),
        UINT32_C( 134217728), UINT32_C(268435456), UINT32_C(536870912), UINT32_C(1073741824),
        UINT32_C(2147483648)
      }};

      const typename array_type::const_iterator it =
        std::lower_bound(a000079_data.cbegin(), a000079_data.cend(), value);

      return ((it != a000079_data.cend()) ? *it : a000079_data.back());
    }
  };

  constexpr std::uint32_t pow10_maker(std::uint32_t n)
  {
    // Make the constant power of 10^n.
    return ((n == UINT32_C(0)) ? UINT32_C(1) : pow10_maker(n - UINT32_C(1)) * UINT32_C(10));
  }

  inline std::uint32_t pow10_maker_as_runtime_value(const std::uint32_t n)
  {
    using local_p10_table_type = std::array<std::uint32_t, 10U>;

    constexpr local_p10_table_type local_p10_table =
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

    return ((n < std::uint32_t(std::tuple_size<local_p10_table_type>::value))
             ? local_p10_table[typename local_p10_table_type::size_type(n)]
             : local_p10_table.back());
  }

  template<typename LimbType>
  struct decwide_t_helper_base
  {
    static constexpr std::int32_t elem_digits10     =
      ((std::is_same<LimbType, std::uint32_t>::value == true)
        ? static_cast<std::int32_t>(8)
        : ((std::is_same<LimbType, std::uint16_t>::value == true) ? static_cast<std::int32_t>(4)
                                                                  : static_cast<std::int32_t>(2)));

    static constexpr std::int32_t elem_mask      = static_cast<std::int32_t>(pow10_maker((std::uint32_t)  elem_digits10));
    static constexpr std::int32_t elem_mask_half = static_cast<std::int32_t>(pow10_maker((std::uint32_t) (elem_digits10 / 2)));

    static std::uint8_t digit_at_pos_in_limb(const LimbType u, const unsigned pos)
    {
      return std::uint8_t(LimbType(u / pow10_maker_as_runtime_value(std::uint32_t(pos))) % LimbType(10U));
    }
  };

  template<typename LimbType> constexpr std::int32_t decwide_t_helper_base<LimbType>::elem_digits10;
  template<typename LimbType> constexpr std::int32_t decwide_t_helper_base<LimbType>::elem_mask;
  template<typename LimbType> constexpr std::int32_t decwide_t_helper_base<LimbType>::elem_mask_half;

  template<const std::int32_t MyDigits10,
           typename LimbType>
  struct decwide_t_helper : decwide_t_helper_base<LimbType>
  {
  private:
    using base_class_type = decwide_t_helper_base<LimbType>;

  public:
    static constexpr std::int32_t digits10          = MyDigits10;
    static constexpr std::int32_t digits            = digits10;
    static constexpr std::int32_t max_digits10      = static_cast<std::int32_t>(digits10 + 4);
    static constexpr std::int32_t radix             = static_cast<std::int32_t>(10);

    static constexpr std::int32_t elem_number_extra = 3;
    static constexpr std::int32_t elem_number       = static_cast<std::int32_t>(((digits10 / base_class_type::elem_digits10) + (((digits10 % base_class_type::elem_digits10) != 0) ? 1 : 0)) + elem_number_extra);
  };

  template<const std::int32_t MyDigits10, typename LimbType> constexpr std::int32_t decwide_t_helper<MyDigits10, LimbType>::digits10;
  template<const std::int32_t MyDigits10, typename LimbType> constexpr std::int32_t decwide_t_helper<MyDigits10, LimbType>::digits;
  template<const std::int32_t MyDigits10, typename LimbType> constexpr std::int32_t decwide_t_helper<MyDigits10, LimbType>::max_digits10;
  template<const std::int32_t MyDigits10, typename LimbType> constexpr std::int32_t decwide_t_helper<MyDigits10, LimbType>::radix;
  template<const std::int32_t MyDigits10, typename LimbType> constexpr std::int32_t decwide_t_helper<MyDigits10, LimbType>::elem_number_extra;
  template<const std::int32_t MyDigits10, typename LimbType> constexpr std::int32_t decwide_t_helper<MyDigits10, LimbType>::elem_number;

  template <typename MyType,
            const std::uint_fast32_t MySize,
            typename MyAlloc>
  class fixed_dynamic_array final : public util::dynamic_array<MyType, MyAlloc>
  {
  private:
    using base_class_type = util::dynamic_array<MyType, MyAlloc>;

  public:
    constexpr fixed_dynamic_array()
      : base_class_type(MySize) { }

    fixed_dynamic_array(const typename base_class_type::size_type       s,
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

    virtual ~fixed_dynamic_array() { }

    static constexpr typename base_class_type::size_type static_size()
    {
      return MySize;
    }
  };

  template<typename MyType,
           const std::uint_fast32_t MySize>
  class fixed_static_array final : public std::array<MyType, std::size_t(MySize)>
  {
  private:
    using base_class_type = std::array<MyType, std::size_t(MySize)>;

  public:
    fixed_static_array() { }

    fixed_static_array(const typename base_class_type::size_type   s,
                       const typename base_class_type::value_type& v = typename base_class_type::value_type())
    {
      std::fill(base_class_type::begin(),
                base_class_type::begin() + (std::min)(MySize, (std::uint_fast32_t) s),
                v);

      std::fill(base_class_type::begin() + (std::min)(MySize, (std::uint_fast32_t) s),
                base_class_type::end(),
                typename base_class_type::value_type());
    }

    fixed_static_array(const fixed_static_array& other_array)
    {
      std::copy(other_array.cbegin(),
                other_array.cbegin() + MySize,
                base_class_type::begin());
    }

    template<const std::uint_fast32_t OtherSize>
    fixed_static_array(const fixed_static_array<std::uint_fast32_t, OtherSize>& other_array)
    {
      std::copy(other_array.cbegin(),
                other_array.cbegin() + (std::min)(OtherSize, MySize),
                base_class_type::begin());

      std::fill(base_class_type::begin() + (std::min)(OtherSize, MySize),
                base_class_type::end(),
                typename base_class_type::value_type());
    }

    explicit fixed_static_array(std::initializer_list<typename base_class_type::value_type> lst)
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

    fixed_static_array& operator=(const fixed_static_array& other_array)
    {
      base_class_type::operator=((const base_class_type&) other_array);

      return *this;
    }

    fixed_static_array& operator=(fixed_static_array&& other_array)
    {
      base_class_type::operator=((base_class_type&&) other_array);

      return *this;
    }

    ~fixed_static_array() { }

    static constexpr typename base_class_type::size_type static_size()
    {
      return MySize;
    }
  };

  typedef enum enum_os_float_field_type
  {
    os_float_field_scientific,
    os_float_field_fixed,
    os_float_field_none
  }
  os_float_field_type;

  template<typename UnsignedIntegerType,
           typename SignedIntegerType>
  struct unsigned_wrap
  {
    using unsigned_type = UnsignedIntegerType;
    using   signed_type =   SignedIntegerType;

    constexpr unsigned_wrap(signed_type n)
      : my_neg  (n < static_cast<signed_type>(0)),
        my_value(static_cast<unsigned_type>((my_neg == false) ? static_cast<unsigned_type>(n)
                                                              : static_cast<unsigned_type>(static_cast<unsigned_type>(~static_cast<unsigned_type>(n)) + 1U))) { }

    unsigned_type get_value_unsigned() const { return my_value; }
      signed_type get_value_signed  () const { return (my_neg == false) ? (signed_type) my_value : -(signed_type) my_value; }

    bool          get_is_neg        () const { return my_neg; }

    bool          my_neg;
    unsigned_type my_value;

    unsigned_wrap& operator+=(const unsigned_wrap& other)
    {
      if(my_neg == other.my_neg)
      {
        // +3 + (+2)
        // -3 + (-2)
        my_value = static_cast<unsigned_type>(my_value + other.my_value);
      }
      else
      {
        if(my_neg == false)
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

            my_neg = (my_value != 0U) ? true : false;
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

    unsigned_wrap& operator-=(const unsigned_wrap& other)
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

  template<typename UnsignedIntegerType, typename SignedIntegerType> inline unsigned_wrap<UnsignedIntegerType, SignedIntegerType> operator+(const unsigned_wrap<UnsignedIntegerType, SignedIntegerType>& a, const unsigned_wrap<UnsignedIntegerType, SignedIntegerType>& b) { return unsigned_wrap<UnsignedIntegerType, SignedIntegerType>(a) += b; }
  template<typename UnsignedIntegerType, typename SignedIntegerType> inline unsigned_wrap<UnsignedIntegerType, SignedIntegerType> operator-(const unsigned_wrap<UnsignedIntegerType, SignedIntegerType>& a, const unsigned_wrap<UnsignedIntegerType, SignedIntegerType>& b) { return unsigned_wrap<UnsignedIntegerType, SignedIntegerType>(a) -= b; }

  } } } // namespace math::wide_decimal::detail

#endif // DECWIDE_T_DETAIL_2020_10_26_H_
