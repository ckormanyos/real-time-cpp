///////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 1999 - 2021.                 //
//  Distributed under the Boost Software License,                //
//  Version 1.0. (See accompanying file LICENSE_1_0.txt          //
//  or copy at http://www.boost.org/LICENSE_1_0.txt)             //
///////////////////////////////////////////////////////////////////

// This work is also based on an earlier work:
// "Algorithm 910: A Portable C++ Multiple-Precision System for Special-Function Calculations",
// in ACM TOMS, {VOL 37, ISSUE 4, (February 2011)} (C) ACM, 2011. http://doi.acm.org/10.1145/1916461.1916469

#ifndef DECWIDE_T_2004_06_01_H_
  #define DECWIDE_T_2004_06_01_H_

  //#define WIDE_DECIMAL_DISABLE_IOSTREAM
  //#define WIDE_DECIMAL_DISABLE_DYNAMIC_MEMORY_ALLOCATION
  //#define WIDE_DECIMAL_DISABLE_CONSTRUCT_FROM_STRING
  //#define WIDE_DECIMAL_DISABLE_CACHED_CONSTANTS

  #include <algorithm>
  #include <cmath>
  #include <cstddef>
  #include <cstdint>
  #include <limits>
  #include <initializer_list>
  #if !defined(WIDE_DECIMAL_DISABLE_IOSTREAM)
  #include <iomanip>
  #include <iostream>
  #include <sstream>
  #endif
  #include <memory>
  #if !defined(WIDE_DECIMAL_DISABLE_CONSTRUCT_FROM_STRING)
  #include <string>
  #endif
  #include <type_traits>

  #include <math/wide_decimal/decwide_t_detail_fft.h>
  #include <math/wide_decimal/decwide_t_detail_helper.h>
  #include <math/wide_decimal/decwide_t_detail_karatsuba.h>

  #include <util/utility/util_baselexical_cast.h>
  #include <util/utility/util_dynamic_array.h>

  #if !defined(WIDE_DECIMAL_DISABLE_CONSTRUCT_FROM_STRING)
  #include <util/utility/util_numeric_cast.h>
  #endif

  namespace math { namespace wide_decimal {

  // Forward declaration of the decwide_t template class.
  template<const std::int32_t MyDigits10,
           typename LimbType = std::uint32_t,
           typename AllocatorType = std::allocator<void>,
           typename InternalFloatType = double>
  class decwide_t;

  namespace detail {

  template <typename MyType,
            const std::uint_fast32_t MySize,
            typename MyAlloc>
  class fixed_dynamic_array final : public util::dynamic_array<MyType, MyAlloc>
  {
  private:
    using base_class_type = util::dynamic_array<MyType, MyAlloc>;

  public:
    fixed_dynamic_array(const typename base_class_type::size_type       s  = MySize,
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

  } // namespace math::wide_decimal::detail

  // Forward declarations of various decwide_t namespace functions.
  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType> constexpr decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType> zero();
  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType> constexpr decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType> one ();
  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType> constexpr decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType> two ();
  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType> constexpr decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType> half();

  #if !defined(WIDE_DECIMAL_DISABLE_CACHED_CONSTANTS)
  template<const std::int32_t MyDigits10,
           typename LimbType = std::uint32_t,
           typename AllocatorType = std::allocator<void>,
           typename InternalFloatType = double>
  const decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>& pi(void(*pfn_callback_to_report_digits10)(const std::uint32_t) = nullptr);
  #else
  template<const std::int32_t MyDigits10,
           typename LimbType = std::uint32_t,
           typename AllocatorType = std::allocator<void>,
           typename InternalFloatType = double>
  decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType> pi(void(*pfn_callback_to_report_digits10)(const std::uint32_t) = nullptr);
  #endif

  #if !defined(WIDE_DECIMAL_DISABLE_CACHED_CONSTANTS)
  template<const std::int32_t MyDigits10,
           typename LimbType = std::uint32_t,
           typename AllocatorType = std::allocator<void>,
           typename InternalFloatType = double>
  const decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>& ln_two();
  #else
  template<const std::int32_t MyDigits10,
           typename LimbType = std::uint32_t,
           typename AllocatorType = std::allocator<void>,
           typename InternalFloatType = double>
  decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType> ln_two();
  #endif

  template<const std::int32_t MyDigits10,
           typename LimbType = std::uint32_t,
           typename AllocatorType = std::allocator<void>,
           typename InternalFloatType = double>
  decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType> calc_pi(void(*pfn_callback_to_report_digits10)(const std::uint32_t) = nullptr);

  template<const std::int32_t MyDigits10,
           typename LimbType = std::uint32_t,
           typename AllocatorType = std::allocator<void>,
           typename InternalFloatType = double>
  decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType> calc_ln_two();

  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType> const decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType> constexpr unsigned_long_long_max();
  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType> const decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType> constexpr signed_long_long_min  ();
  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType> const decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType> constexpr signed_long_long_max  ();
  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType> const decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType> constexpr long_double_min       ();
  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType> const decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType> constexpr long_double_max       ();

  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType> bool (isnan)   (decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType> x);
  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType> bool (isfinite)(decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType> x);
  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType> bool (isinf)   (decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType> x);

  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType> decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType> fabs (decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType> x);
  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType> decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>  abs (decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType> x);
  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType> decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType> floor(decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType> x);
  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType> decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType> ceil (decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType> x);
  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType> std::int32_t                                                      sgn  (decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType> x);
  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType> decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType> ldexp(decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType> v, int e);
  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType> decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType> frexp(decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType> v, int* expon);
  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType> decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType> fmod (decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType> v1, decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType> v2);
  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType> std::int32_t                                                      ilogb(decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType> x);
  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType> decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType> sqrt (decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType> x);
  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType> decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType> cbrt (decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType> x);
  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType> decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType> rootn(decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType> x, std::int32_t p);
  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType> decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType> rootn_inverse
                                                                                                                                                                                        (decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType> x, std::int32_t p);
  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType> decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType> log  (decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType> x);
  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType> decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType> exp  (decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType> x);
  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType> decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType> pow  (decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType> x, const std::int64_t n);
  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType> decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType> pow  (decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType> x,
                                                                                                                                                                                         decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType> a);

  #if !defined(WIDE_DECIMAL_DISABLE_IOSTREAM)
  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType> std::ostream& operator<<(std::ostream& os, const decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>& f);
  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType> std::istream& operator>>(std::istream& is,       decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>& f);
  #endif // !WIDE_DECIMAL_DISABLE_IOSTREAM

  // Global unary operators of decwide_t reference.
  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType> decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType> operator+(const decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>& self);
  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType> decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType> operator-(const decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>& self);

  // Global add/sub/mul/div of const decwide_t& with const decwide_t&.
  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType> decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType> operator+(const decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>& u, const decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>& v);
  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType> decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType> operator-(const decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>& u, const decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>& v);
  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType> decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType> operator*(const decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>& u, const decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>& v);
  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType> decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType> operator/(const decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>& u, const decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>& v);

  // Global add/sub/mul/div of const decwide_t& with all built-in types.
  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType, typename SignedIntegralType>
  typename std::enable_if<   (std::is_integral<SignedIntegralType>::value == true)
                          && (std::is_unsigned<SignedIntegralType>::value == false), decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>>::type operator+(const decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>& u, const SignedIntegralType& n);

  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType, typename UnsignedIntegralType>
  typename std::enable_if<   (std::is_integral<UnsignedIntegralType>::value == true)
                          && (std::is_unsigned<UnsignedIntegralType>::value == true), decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>>::type operator+(const decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>& u, const UnsignedIntegralType& n);

  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType, typename FloatingPointType>
  typename std::enable_if<(std::is_floating_point<FloatingPointType>::value == true), decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>>::type operator+(const decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>& u, const FloatingPointType& f);

  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType, typename SignedIntegralType>
  typename std::enable_if<   (std::is_integral<SignedIntegralType>::value == true)
                          && (std::is_unsigned<SignedIntegralType>::value == false), decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>>::type operator-(const decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>& u, const SignedIntegralType& n);

  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType, typename UnsignedIntegralType>
  typename std::enable_if<   (std::is_integral<UnsignedIntegralType>::value == true)
                          && (std::is_unsigned<UnsignedIntegralType>::value == true), decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>>::type operator-(const decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>& u, const UnsignedIntegralType& n);

  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType, typename FloatingPointType>
  typename std::enable_if<(std::is_floating_point<FloatingPointType>::value == true), decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>>::type operator-(const decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>& u, const FloatingPointType& f);

  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType, typename SignedIntegralType>
  typename std::enable_if<   (std::is_integral<SignedIntegralType>::value == true)
                          && (std::is_unsigned<SignedIntegralType>::value == false), decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>>::type operator*(const decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>& u, const SignedIntegralType& n);

  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType, typename UnsignedIntegralType>
  typename std::enable_if<   (std::is_integral<UnsignedIntegralType>::value == true)
                          && (std::is_unsigned<UnsignedIntegralType>::value == true), decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>>::type operator*(const decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>& u, const UnsignedIntegralType& n);

  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType, typename FloatingPointType>
  typename std::enable_if<(std::is_floating_point<FloatingPointType>::value == true), decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>>::type operator*(const decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>& u, const FloatingPointType& f);

  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType, typename SignedIntegralType>
  typename std::enable_if<   (std::is_integral<SignedIntegralType>::value == true)
                          && (std::is_unsigned<SignedIntegralType>::value == false), decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>>::type operator/(const decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>& u, const SignedIntegralType& n);

  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType, typename UnsignedIntegralType>
  typename std::enable_if<   (std::is_integral<UnsignedIntegralType>::value == true)
                          && (std::is_unsigned<UnsignedIntegralType>::value == true), decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>>::type operator/(const decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>& u, const UnsignedIntegralType& n);

  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType, typename FloatingPointType>
  typename std::enable_if<(std::is_floating_point<FloatingPointType>::value == true), decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>>::type operator/(const decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>& u, const FloatingPointType& f);

  // Global add/sub/mul/div of all built-in types with const decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>&.
  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType, typename SignedIntegralType>
  typename std::enable_if<   (std::is_integral<SignedIntegralType>::value == true)
                          && (std::is_unsigned<SignedIntegralType>::value == false), decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>>::type operator+(const SignedIntegralType& n, const decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>& u);

  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType, typename UnsignedIntegralType>
  typename std::enable_if<   (std::is_integral<UnsignedIntegralType>::value == true)
                          && (std::is_unsigned<UnsignedIntegralType>::value == true), decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>>::type operator+(const UnsignedIntegralType& n, const decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>& u);

  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType, typename FloatingPointType>
  typename std::enable_if<(std::is_floating_point<FloatingPointType>::value == true), decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>>::type operator+(const FloatingPointType& f, const decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>& u);

  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ArithmeticType>
  typename std::enable_if<(std::is_arithmetic<ArithmeticType>::value == true), decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>>::type operator-(const ArithmeticType& n, const decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>& u);

  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType, typename SignedIntegralType>
  typename std::enable_if<   (std::is_integral<SignedIntegralType>::value == true)
                          && (std::is_unsigned<SignedIntegralType>::value == false), decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>>::type operator*(const SignedIntegralType& n, const decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>& u);

  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType, typename UnsignedIntegralType>
  typename std::enable_if<   (std::is_integral<UnsignedIntegralType>::value == true)
                          && (std::is_unsigned<UnsignedIntegralType>::value == true), decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>>::type operator*(const UnsignedIntegralType& n, const decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>& u);

  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType, typename FloatingPointType>
  typename std::enable_if<(std::is_floating_point<FloatingPointType>::value == true), decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>>::type operator*(const FloatingPointType& f, const decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>& u);

  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ArithmeticType>
  typename std::enable_if<(std::is_arithmetic<ArithmeticType>::value == true), decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>>::type operator/(const ArithmeticType& n, const decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>& u);

  // Global self add/sub/mul/div of decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>& with all built-in types.
  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType, typename SignedIntegralType>
  typename std::enable_if<   (std::is_integral<SignedIntegralType>::value == true)
                          && (std::is_unsigned<SignedIntegralType>::value == false), decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>>::type operator+=(decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>& u, const SignedIntegralType& n);

  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType, typename UnsignedIntegralType>
  typename std::enable_if<   (std::is_integral<UnsignedIntegralType>::value == true)
                          && (std::is_unsigned<UnsignedIntegralType>::value == true), decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>>::type operator+=(decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>& u, const UnsignedIntegralType& n);

  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType, typename FloatingPointType>
  typename std::enable_if<(std::is_floating_point<FloatingPointType>::value == true), decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>>::type operator+=(decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>& u, const FloatingPointType& f);

  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType, typename SignedIntegralType>
  typename std::enable_if<   (std::is_integral<SignedIntegralType>::value == true)
                          && (std::is_unsigned<SignedIntegralType>::value == false), decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>>::type operator-=(decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>& u, const SignedIntegralType& n);

  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType, typename UnsignedIntegralType>
  typename std::enable_if<   (std::is_integral<UnsignedIntegralType>::value == true)
                          && (std::is_unsigned<UnsignedIntegralType>::value == true), decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>>::type operator-=(decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>& u, const UnsignedIntegralType& n);

  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType, typename FloatingPointType>
  typename std::enable_if<(std::is_floating_point<FloatingPointType>::value == true), decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>>::type operator-=(decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>& u, const FloatingPointType& f);

  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType, typename SignedIntegralType>
  typename std::enable_if<   (std::is_integral<SignedIntegralType>::value == true)
                          && (std::is_unsigned<SignedIntegralType>::value == false), decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>>::type operator*=(decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>& u, const SignedIntegralType& n);

  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType, typename UnsignedIntegralType>
  typename std::enable_if<   (std::is_integral<UnsignedIntegralType>::value == true)
                          && (std::is_unsigned<UnsignedIntegralType>::value == true), decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>>::type operator*=(decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>& u, const UnsignedIntegralType& n);

  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType, typename FloatingPointType>
  typename std::enable_if<(std::is_floating_point<FloatingPointType>::value == true), decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>>::type operator*=(decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>& u, const FloatingPointType& f);

  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType, typename SignedIntegralType>
  typename std::enable_if<   (std::is_integral<SignedIntegralType>::value == true)
                          && (std::is_unsigned<SignedIntegralType>::value == false), decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>>::type operator/=(decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>& u, const SignedIntegralType& n);

  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType, typename UnsignedIntegralType>
  typename std::enable_if<   (std::is_integral<UnsignedIntegralType>::value == true)
                          && (std::is_unsigned<UnsignedIntegralType>::value == true), decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>>::type operator/=(decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>& u, const UnsignedIntegralType& n);

  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType, typename FloatingPointType>
  typename std::enable_if<(std::is_floating_point<FloatingPointType>::value == true), decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>>::type operator/=(decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>& u, const FloatingPointType& f);

  // Global comparison operators of const decwide_t& with const decwide_t&.
  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType> bool operator< (const decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>& u, const decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>& v);
  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType> bool operator<=(const decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>& u, const decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>& v);
  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType> bool operator==(const decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>& u, const decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>& v);
  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType> bool operator!=(const decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>& u, const decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>& v);
  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType> bool operator>=(const decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>& u, const decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>& v);
  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType> bool operator> (const decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>& u, const decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>& v);

  // Global comparison operators of const decwide_t& with all built-in types.
  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ArithmeticType> typename std::enable_if<std::is_arithmetic<ArithmeticType>::value == true, bool>::type operator< (const decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>& u, const ArithmeticType& v);
  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ArithmeticType> typename std::enable_if<std::is_arithmetic<ArithmeticType>::value == true, bool>::type operator<=(const decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>& u, const ArithmeticType& v);
  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ArithmeticType> typename std::enable_if<std::is_arithmetic<ArithmeticType>::value == true, bool>::type operator==(const decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>& u, const ArithmeticType& v);
  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ArithmeticType> typename std::enable_if<std::is_arithmetic<ArithmeticType>::value == true, bool>::type operator!=(const decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>& u, const ArithmeticType& v);
  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ArithmeticType> typename std::enable_if<std::is_arithmetic<ArithmeticType>::value == true, bool>::type operator>=(const decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>& u, const ArithmeticType& v);
  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ArithmeticType> typename std::enable_if<std::is_arithmetic<ArithmeticType>::value == true, bool>::type operator> (const decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>& u, const ArithmeticType& v);

  // Global comparison operators of all built-in types with const decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>&.
  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ArithmeticType> typename std::enable_if<std::is_arithmetic<ArithmeticType>::value == true, bool>::type operator< (ArithmeticType u, const decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>& v);
  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ArithmeticType> typename std::enable_if<std::is_arithmetic<ArithmeticType>::value == true, bool>::type operator<=(ArithmeticType u, const decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>& v);
  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ArithmeticType> typename std::enable_if<std::is_arithmetic<ArithmeticType>::value == true, bool>::type operator==(ArithmeticType u, const decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>& v);
  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ArithmeticType> typename std::enable_if<std::is_arithmetic<ArithmeticType>::value == true, bool>::type operator!=(ArithmeticType u, const decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>& v);
  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ArithmeticType> typename std::enable_if<std::is_arithmetic<ArithmeticType>::value == true, bool>::type operator>=(ArithmeticType u, const decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>& v);
  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ArithmeticType> typename std::enable_if<std::is_arithmetic<ArithmeticType>::value == true, bool>::type operator> (ArithmeticType u, const decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>& v);

  template<const std::int32_t MyDigits10,
           typename LimbType,
           typename AllocatorType,
           typename InternalFloatType>
  class decwide_t
  {
  public:
    // Define the decwide_t digits characteristics.

    static constexpr std::int32_t decwide_t_elems_for_fft     = 128;

    static constexpr std::int32_t decwide_t_digits10          = detail::decwide_t_helper<MyDigits10, LimbType>::digits10;
    static constexpr std::int32_t decwide_t_digits            = detail::decwide_t_helper<MyDigits10, LimbType>::digits;
    static constexpr std::int32_t decwide_t_max_digits10      = detail::decwide_t_helper<MyDigits10, LimbType>::max_digits10;
    static constexpr std::int32_t decwide_t_radix             = detail::decwide_t_helper<MyDigits10, LimbType>::radix;

    static constexpr std::int32_t decwide_t_elem_digits10     = detail::decwide_t_helper<MyDigits10, LimbType>::elem_digits10;
    static constexpr std::int32_t decwide_t_elem_number       = detail::decwide_t_helper<MyDigits10, LimbType>::elem_number;
    static constexpr std::int32_t decwide_t_elem_mask         = detail::decwide_t_helper<MyDigits10, LimbType>::elem_mask;
    static constexpr std::int32_t decwide_t_elem_mask_half    = detail::decwide_t_helper<MyDigits10, LimbType>::elem_mask_half;

    static constexpr std::int64_t decwide_t_max_exp10         =  static_cast<std::int64_t>((std::numeric_limits<std::int64_t>::max)() / decwide_t_elem_digits10) * decwide_t_elem_digits10;
    static constexpr std::int64_t decwide_t_min_exp10         = -static_cast<std::int64_t>(decwide_t_max_exp10);
    static constexpr std::int64_t decwide_t_max_exp           = decwide_t_max_exp10;
    static constexpr std::int64_t decwide_t_min_exp           = decwide_t_min_exp10;

    // Rebind the decwide_t allocator to the granularity of the LimbType.
    using allocator_type = typename std::allocator_traits<AllocatorType>::template rebind_alloc<LimbType>;

    // Define the array type, which is the internal
    // representation of the data field of a decwide_t.
    using array_type = detail::fixed_dynamic_array<typename allocator_type::value_type,
                                                   static_cast<std::uint_fast32_t>(decwide_t_elem_number),
                                                   allocator_type>;

    // Obtain the limb type, double limb type and signed limb type
    // from meta-templates.
    using limb_type        = typename array_type::value_type;
    using double_limb_type = typename std::conditional<(std::is_same<limb_type, std::uint32_t>::value == true),
                                                        std::uint64_t,
                                                        std::uint32_t>::type;
    using signed_limb_type = typename std::conditional<(std::is_same<limb_type, std::uint32_t>::value == true),
                                                        std::int32_t,
                                                        std::int16_t>::type;

    // Check thw width of the limb type.
    static_assert((   (std::is_same<std::uint16_t, limb_type>::value == true)
                   || (std::is_same<std::uint32_t, limb_type>::value == true)),
                   "Error: limb_type (determined via the template parameter LimbType) must be either uint16_t or uint32_t.");

    typedef enum fpclass_type_enum
    {
      decwide_t_finite,
      decwide_t_inf,
      decwide_t_NaN
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
        native_float_type man = frexp(f, &my_exponent_part);

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
        decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>::my_value_pi    ();
        decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>::my_value_ln_two();
      }

      void do_nothing() { }
    };

    static initializer init;
    #endif

  public:
    // Default constructor.
    constexpr decwide_t() : my_data     (),
                            my_exp      (static_cast<std::int64_t>(0)),
                            my_neg      (false),
                            my_fpclass  (decwide_t_finite),
                            my_prec_elem(decwide_t_elem_number) { }

    // Constructors from built-in unsigned integral types.
    template<typename UnsignedIntegralType,
             typename std::enable_if<(   (std::is_integral<UnsignedIntegralType>::value == true)
                                      && (std::is_unsigned<UnsignedIntegralType>::value == true)
                                      && (std::numeric_limits<UnsignedIntegralType>::digits <= std::numeric_limits<limb_type>::digits))>::type const* = nullptr>
    decwide_t(const UnsignedIntegralType u) : my_data     (),
                                              my_exp      (static_cast<std::int64_t>(0)),
                                              my_neg      (false),
                                              my_fpclass  (decwide_t_finite),
                                              my_prec_elem(decwide_t_elem_number)
    {
      if(u < decwide_t_elem_mask)
      {
        my_data[0U] = u;
      }
      else
      {
        my_data[0U] = u / decwide_t_elem_mask;
        my_data[1U] = u % decwide_t_elem_mask;

        my_exp = decwide_t_elem_digits10;
      }
    }

    // Constructors from built-in unsigned integral types.
    template<typename UnsignedIntegralType,
             typename std::enable_if<(   (std::is_integral<UnsignedIntegralType>::value == true)
                                      && (std::is_unsigned<UnsignedIntegralType>::value == true)
                                      && (std::numeric_limits<limb_type>::digits) < std::numeric_limits<UnsignedIntegralType>::digits)>::type const* = nullptr>
    decwide_t(const UnsignedIntegralType u) : my_data     (),
                                              my_exp      (static_cast<std::int64_t>(0)),
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
                                            my_exp      (static_cast<std::int64_t>(0)),
                                            my_neg      (n < static_cast<signed long long>(0)),
                                            my_fpclass  (decwide_t_finite),
                                            my_prec_elem(decwide_t_elem_number)
    {
      const unsigned long long u =
        ((!my_neg) ? static_cast<unsigned long long>(n)
                   : static_cast<unsigned long long>(-static_cast<signed long long>(n)));

      from_unsigned_long_long(u);
    }

    // Constructors from built-in floating-point types.
    template<typename FloatingPointType,
              typename std::enable_if<std::is_floating_point<FloatingPointType>::value == true>::type const* = nullptr>
    decwide_t(const FloatingPointType f) : my_data     (),
                                           my_exp      (static_cast<std::int64_t>(0)),
                                           my_neg      (false),
                                           my_fpclass  (decwide_t_finite),
                                           my_prec_elem(decwide_t_elem_number)
    {
      from_long_double(static_cast<long double>(f));
    }

    #if !defined(WIDE_DECIMAL_DISABLE_CONSTRUCT_FROM_STRING)
    // Constructors from character representations.
    decwide_t(const char* const s) : my_data     (),
                                     my_exp      (static_cast<std::int64_t>(0)),
                                     my_neg      (false),
                                     my_fpclass  (decwide_t_finite),
                                     my_prec_elem(decwide_t_elem_number)
    {
      if(!rd_string(s))
      {
        std::fill(my_data.begin(), my_data.end(), static_cast<limb_type>(0U));

        my_exp     = static_cast<std::int64_t>(0);
        my_neg     = false;
        my_fpclass = decwide_t_NaN;
      }
    }

    decwide_t(const std::string& str) : my_data     (),
                                        my_exp      (static_cast<std::int64_t>(0)),
                                        my_neg      (false),
                                        my_fpclass  (decwide_t_finite),
                                        my_prec_elem(decwide_t_elem_number)
    {
      if(!rd_string(str.c_str()))
      {
        std::fill(my_data.begin(), my_data.end(), static_cast<limb_type>(0U));

        my_exp     = static_cast<std::int64_t>(0);
        my_neg     = false;
        my_fpclass = decwide_t_NaN;
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
    constexpr decwide_t(decwide_t&& other) : my_data     ((array_type&&) other.my_data),
                                             my_exp      (other.my_exp),
                                             my_neg      (other.my_neg),
                                             my_fpclass  (other.my_fpclass),
                                             my_prec_elem(other.my_prec_elem) { }

    // Constructor from floating-point class.
    explicit constexpr decwide_t(const fpclass_type fpc) : my_data     (),
                                                           my_exp      (static_cast<std::int64_t>(0)),
                                                           my_neg      (false),
                                                           my_fpclass  (fpc),
                                                           my_prec_elem(decwide_t_elem_number) { }

    // Constructor from initializer list of limbs,
    // exponent value (normed to limb granularity) 
    // and optional sign flag.
    explicit constexpr decwide_t(std::initializer_list<limb_type> limb_values,
                                 const std::int64_t e = 0,
                                 const bool is_neg = false)
      : my_data     (limb_values),
        my_exp      (e),
        my_neg      (is_neg),
        my_fpclass  (decwide_t_finite),
        my_prec_elem(decwide_t_elem_number) { }

  private:
    // Constructor from mantissa and exponent.
    explicit decwide_t(const InternalFloatType mantissa,
                       const std::int64_t exponent) : my_data     (),
                                                      my_exp      (static_cast<std::int64_t>(0)),
                                                      my_neg      (false),
                                                      my_fpclass  (decwide_t_finite),
                                                      my_prec_elem(decwide_t_elem_number)
    {
      // Create a decwide_t from mantissa and exponent.

      // This constructor is intended to maintain the
      // full precision of the InternalFloatType.

      using std::fabs;

      const bool mantissa_is_iszero = (fabs(mantissa) < ((std::numeric_limits<InternalFloatType>::min)() * (InternalFloatType(1) + std::numeric_limits<InternalFloatType>::epsilon())));

      if(mantissa_is_iszero)
      {
        operator=((exponent == static_cast<std::int64_t>(0)) ? one<MyDigits10, LimbType, AllocatorType, InternalFloatType>() : zero<MyDigits10, LimbType, AllocatorType, InternalFloatType>());

        return;
      }

      const bool b_neg = (mantissa < InternalFloatType(0));

      InternalFloatType d = ((!b_neg) ? mantissa : -mantissa);
      std::int64_t  e = exponent;

      const InternalFloatType f10(10);

      while(d > f10)                  { d /= f10; ++e; }
      while(d < InternalFloatType(1)) { d *= f10; --e; }

      std::int32_t shift = static_cast<std::int32_t>(e % static_cast<std::int32_t>(decwide_t_elem_digits10));

      while(static_cast<std::int32_t>(shift % decwide_t_elem_digits10) != static_cast<std::int32_t>(0))
      {
        d *= f10;
        --e;
        --shift;
      }

      my_exp = e;
      my_neg = b_neg;

      std::fill(my_data.begin(), my_data.end(), static_cast<limb_type>(0));

      static const std::int32_t digit_ratio = static_cast<std::int32_t>(static_cast<std::int32_t>(std::numeric_limits<InternalFloatType>::digits10) / static_cast<std::int32_t>(decwide_t_elem_digits10));
      static const std::int32_t digit_loops = static_cast<std::int32_t>(digit_ratio + static_cast<std::int32_t>(2));

      for(typename array_type::size_type i = static_cast<typename array_type::size_type>(0); i < static_cast<typename array_type::size_type>(digit_loops); i++)
      {
        limb_type n = static_cast<limb_type>(static_cast<std::uint64_t>(d));

        my_data[i]  = static_cast<limb_type>(n);
        d          -= static_cast<InternalFloatType>(n);
        d          *= static_cast<InternalFloatType>(decwide_t_elem_mask);
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
      my_data      = (array_type&&) other.my_data;
      my_exp       = other.my_exp;
      my_neg       = other.my_neg;
      my_fpclass   = other.my_fpclass;
      my_prec_elem = other.my_prec_elem;

      return *this;
    }

          array_type&  representation()       { return my_data; }
    const array_type&  representation() const { return my_data; }
    const array_type& crepresentation() const { return my_data; }

    // Binary arithmetic operators.
    decwide_t& operator+=(const decwide_t& v)
    {
      // TBD: Eliminate the temporary storage array my_n_data_for_add_sub.

      // TBD: Limit the length of add/sub to only those ranges needed,
      // whereby propagate borrow/carry may be necessary as well.

      if((isnan)())
      {
        return *this;
      }

      if((isinf)())
      {
        if((v.isinf)() && (isneg() != v.isneg()))
        {
          *this = my_value_nan();
        }

        return *this;
      }

      if(iszero())
      {
        return operator=(v);
      }

      // Get the offset for the add/sub operation.
      static const std::int64_t max_delta_exp = static_cast<std::int64_t>((decwide_t_elem_number - 1) * decwide_t_elem_digits10);

      const std::int64_t ofs_exp = static_cast<std::int64_t>(my_exp - v.my_exp);

      // Check if the operation is out of range, requiring special handling.
      if(v.iszero() || (ofs_exp > max_delta_exp))
      {
        // Result is *this unchanged since v is negligible compared to *this.
        return *this;
      }
      else if(ofs_exp < -max_delta_exp)
      {
        // Result is *this = v since *this is negligible compared to v.
        return operator=(v);
      }

      // Do the add/sub operation.

      typename array_type::pointer        p_u    =   my_data.data();
      typename array_type::const_pointer  p_v    = v.my_data.data();
      bool                                b_copy = false;
      const std::int32_t                  ofs    = static_cast<std::int32_t>(static_cast<std::int32_t>(ofs_exp) / decwide_t_elem_digits10);

      #if !defined(WIDE_DECIMAL_DISABLE_DYNAMIC_MEMORY_ALLOCATION)
      detail::fixed_dynamic_array<limb_type,
                                  static_cast<std::uint_fast32_t>(decwide_t_elem_number),
                                  std::allocator<limb_type>>
      my_n_data_for_add_sub;
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
                    my_data.cend()     - static_cast<std::ptrdiff_t>(-ofs),
                    my_n_data_for_add_sub.begin() + static_cast<std::ptrdiff_t>(-ofs));

          std::fill(my_n_data_for_add_sub.begin(),
                    my_n_data_for_add_sub.begin() + static_cast<std::ptrdiff_t>(-ofs),
                    static_cast<limb_type>(0));

          p_u = my_n_data_for_add_sub.data();
          b_copy = true;
        }

        // Addition.
        const limb_type carry = add_loop_uv(p_u, p_v, decwide_t_elem_number);

        if(b_copy)
        {
          std::copy(my_n_data_for_add_sub.cbegin(), my_n_data_for_add_sub.cend(), my_data.begin());
          my_exp  = v.my_exp;
        }

        // There needs to be a carry into the element -1 of the array data
        if(carry != static_cast<limb_type>(0U))
        {
          std::copy_backward(my_data.cbegin(),
                             my_data.cend() - static_cast<std::uint_fast32_t>(1U),
                             my_data.end());

          my_data[0U] = carry;

          my_exp += static_cast<std::int64_t>(decwide_t_elem_digits10);
        }
      }
      else
      {
        // Subtract v from *this, where the data array of either *this or v
        // might have to be treated with a positive, negative or zero offset.
        if(       (ofs >  static_cast<std::int32_t>(0))
           || (   (ofs == static_cast<std::int32_t>(0))
               && (cmp_data(v.my_data) > static_cast<std::int32_t>(0))))
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
          std::copy(v.my_data.cbegin(), v.my_data.cend(), my_n_data_for_add_sub.begin());
          p_u    = my_n_data_for_add_sub.data();
          p_v    = my_data.data();
          b_copy = true;
        }

        // Subtraction.
        const signed_limb_type borrow = sub_loop_uv(p_u, p_v, decwide_t_elem_number);

        static_cast<void>(borrow);

        if(b_copy)
        {
          std::copy(my_n_data_for_add_sub.cbegin(), my_n_data_for_add_sub.cend(), my_data.begin());
          my_exp  = v.my_exp;
          my_neg  = v.my_neg;
        }

        // Is it necessary to justify the data?
        const typename array_type::const_iterator first_nonzero_elem =
          std::find_if(my_data.cbegin(),
                       my_data.cend(),
                       [](const limb_type& d) -> bool
                       {
                         return (d != static_cast<limb_type>(0U));
                       });

        if(first_nonzero_elem != my_data.cbegin())
        {
          if(first_nonzero_elem == my_data.cend())
          {
            // This result of the subtraction is exactly zero.
            // Reset the sign and the exponent.
            my_neg = false;
            my_exp = static_cast<std::int64_t>(0);
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

            my_exp -= static_cast<std::int64_t>(sj * static_cast<std::ptrdiff_t>(decwide_t_elem_digits10));
          }
        }
      }

      // Check for underflow.
      if(iszero()) { return (*this = zero<MyDigits10, LimbType, AllocatorType, InternalFloatType>()); }

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
        *this = zero<MyDigits10, LimbType, AllocatorType, InternalFloatType>();
      }
      else
      {
        // Set the exponent of the result.
        my_exp += v.my_exp;

        const std::int32_t prec_elems_for_multiply = (std::min)(decwide_t_elem_number, (std::min)(my_prec_elem, v.my_prec_elem));

        eval_mul_dispatch_multiplication_method<decwide_t_elem_number>(v, prec_elems_for_multiply);
      }

      // Set the sign of the result.
      my_neg = b_result_is_neg;

      return *this;
    }

    decwide_t& operator/=(const decwide_t& v)
    {
      const bool u_and_v_are_finite_and_identical =
        (    (isfinite)()
         && (my_fpclass == v.my_fpclass)
         && (my_exp     == v.my_exp)
         && (cmp_data(v.my_data) == static_cast<std::int32_t>(0)));

      if(u_and_v_are_finite_and_identical)
      {
        *this = one<MyDigits10, LimbType, AllocatorType, InternalFloatType>();

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
      const bool b_u_is_inf  = (isinf)();
      const bool b_n_is_zero = (n == static_cast<std::int32_t>(0));

      if((isnan)() || (b_u_is_inf && b_n_is_zero))
      {
        return (*this = my_value_nan());
      }

      if(b_u_is_inf)
      {
        *this = ((!b_neg) ?  my_value_inf() : -my_value_inf());

        return *this;
      }

      if(iszero() || b_n_is_zero)
      {
        // Multiplication by zero.
        return (*this = zero<MyDigits10, LimbType, AllocatorType, InternalFloatType>());
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
      const limb_type carry = mul_loop_n(my_data.data(), nn, my_prec_elem);

      // Handle the carry and adjust the exponent.
      if(carry != static_cast<limb_type>(0U))
      {
        my_exp += static_cast<std::int64_t>(decwide_t_elem_digits10);

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

      // Handle special cases like zero, inf and NaN.
      if((isnan)())
      {
        return *this;
      }

      if((isinf)())
      {
        *this = ((!b_neg) ?  my_value_inf() : -my_value_inf());

        return *this;
      }

      if(n == static_cast<unsigned long long>(0U))
      {
        // Divide by 0.
        if(iszero())
        {
          return (*this = my_value_nan());
        }
        else
        {
          *this = ((!isneg()) ?  my_value_inf() : -my_value_inf());

          return *this;
        }
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
        const limb_type prev = div_loop_n(my_data.data(), nn, my_prec_elem);

        // Determine if one leading zero is in the result data.
        if(my_data[0] == static_cast<limb_type>(0U))
        {
          // Adjust the exponent
          my_exp -= static_cast<std::int64_t>(decwide_t_elem_digits10);

          // Shift result of the division one element to the left.
          std::copy(my_data.cbegin() + static_cast<std::ptrdiff_t>(1),
                    my_data.cbegin() + static_cast<std::ptrdiff_t>(my_prec_elem - 1),
                    my_data.begin());

          const typename array_type::size_type ip = static_cast<typename array_type::size_type>(my_prec_elem - 1);

          my_data[ip] = static_cast<limb_type>(static_cast<std::uint64_t>(prev * static_cast<std::uint64_t>(decwide_t_elem_mask)) / nn);
        }
      }

      // Check for underflow.
      if(iszero())
      {
        return (*this = zero<MyDigits10, LimbType, AllocatorType, InternalFloatType>());
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

    int compare(const decwide_t& v) const
    {
      const std::int32_t this_compare_result = cmp(v);

      return static_cast<int>(this_compare_result);
    }

    std::int32_t cmp(const decwide_t& v) const
    {
      // Compare v with *this.
      //         Return +1 for *this > v
      //                 0 for *this = v
      //                -1 for *this < v

      // Handle all non-finite cases.
      if(((isfinite)() == false) || ((v.isfinite)() == false))
      {
        // NaN can never equal NaN. Return an implementation-dependent
        // signed result. Also note that comparison of NaN with NaN
        // using operators greater-than or less-than is undefined.
        if((isnan)() || (v.isnan)())
        {
          return ((isnan)() ? static_cast<std::int32_t>(1) : static_cast<std::int32_t>(-1));
        }

        if((isinf)() && (v.isinf)())
        {
          // Both *this and v are infinite. They are equal if they have the same sign.
          // Otherwise, *this is less than v if and only if *this is negative.
          return ((my_neg == v.my_neg)
                   ? static_cast<std::int32_t>(0)
                   : (my_neg ? static_cast<std::int32_t>(-1) : static_cast<std::int32_t>(1)));
        }

        if((isinf)())
        {
          // *this is infinite, but v is finite.
          // So negative infinite *this is less than any finite v.
          // Whereas positive infinite *this is greater than any finite v.
          return (isneg() ? static_cast<std::int32_t>(-1) : static_cast<std::int32_t>(1));
        }
        else
        {
          // *this is finite, and v is infinite.
          // So any finite *this is greater than negative infinite v.
          // Whereas any finite *this is less than positive infinite v.
          return (v.my_neg ? static_cast<std::int32_t>(1) : static_cast<std::int32_t>(-1));
        }
      }

      // And now handle all *finite* cases.
      if(iszero())
      {
        // The value of *this is zero and v is either zero or non-zero.
        return (v.iszero() ? static_cast<std::int32_t>(0)
                           : (v.my_neg ? static_cast<std::int32_t>(1) : static_cast<std::int32_t>(-1)));
      }
      else if(v.iszero())
      {
        // The value of v is zero and *this is non-zero.
        return (my_neg ? static_cast<std::int32_t>(-1) : static_cast<std::int32_t>(1));
      }
      else
      {
        // Both *this and v are non-zero.

        if(my_neg != v.my_neg)
        {
          // The signs are different.
          return (my_neg ? static_cast<std::int32_t>(-1) : static_cast<std::int32_t>(1));
        }
        else if(my_exp != v.my_exp)
        {
          // The signs are the same and the exponents are different.
          const std::int32_t val_cmp_exp = ((my_exp < v.my_exp) ? static_cast<std::int32_t>(1) : static_cast<std::int32_t>(-1));

          return (my_neg ? val_cmp_exp : static_cast<std::int32_t>(-val_cmp_exp));
        }
        else
        {
          // The signs are the same and the exponents are the same.
          // Compare the data.
          const std::int32_t val_cmp_data = cmp_data(v.my_data);

          return ((!my_neg) ? val_cmp_data : static_cast<std::int32_t>(-val_cmp_data));
        }
      }
    }

    // Specific special values.
    static constexpr decwide_t my_value_inf() { return decwide_t(decwide_t_inf); }
    static constexpr decwide_t my_value_nan() { return decwide_t(decwide_t_NaN); }
    static constexpr decwide_t my_value_max() { return decwide_t( { limb_type(9U) }, decwide_t_max_exp10 ); }
    static constexpr decwide_t my_value_min() { return decwide_t( { limb_type(1U) }, decwide_t_min_exp10 ); }
    static constexpr decwide_t my_value_eps()
    {
      return decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>
      (
        {
          (limb_type) detail::decwide_t_helper<MyDigits10, LimbType>::pow10_maker((std::uint32_t) ((std::int32_t) (INT32_C(1) + (std::int32_t) (((decwide_t_digits10 / decwide_t_elem_digits10) + ((decwide_t_digits10 % decwide_t_elem_digits10) != 0 ? 1 : 0)) * decwide_t_elem_digits10)) - decwide_t_digits10))
        },
        -(std::int64_t) (((decwide_t_digits10 / decwide_t_elem_digits10) + ((decwide_t_digits10 % decwide_t_elem_digits10) != 0 ? 1 : 0)) * decwide_t_elem_digits10)
      );
    }

    #if !defined(WIDE_DECIMAL_DISABLE_CACHED_CONSTANTS)
    static const decwide_t& my_value_pi()
    {
      init.do_nothing();
      static const decwide_t val(calc_pi<MyDigits10, LimbType, AllocatorType, InternalFloatType>());
      return val;
    }

    static const decwide_t& my_value_ln_two()
    {
      init.do_nothing();
      static const decwide_t val(calc_ln_two<MyDigits10, LimbType, AllocatorType, InternalFloatType>());
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

      // Handle special cases like zero, inf and NaN.
      if(iszero())
      {
        *this = ((!b_neg) ? +my_value_inf() : -my_value_inf());

        return *this;
      }

      if((isnan)())
      {
        return *this;
      }

      if((isinf)())
      {
        return (*this = zero<MyDigits10, LimbType, AllocatorType, InternalFloatType>());
      }

      if(isone())
      {
        *this = ((!b_neg) ? one<MyDigits10, LimbType, AllocatorType, InternalFloatType>() : -one<MyDigits10, LimbType, AllocatorType, InternalFloatType>());

        return *this;
      }

      // Use the original value of *this for iteration below.
      decwide_t x(*this);

      // Generate the initial estimate using division.
      // Extract the mantissa and exponent for a "manual"
      // computation of the estimate.
      InternalFloatType dd;
      std::int64_t      ne;

      x.extract_parts(dd, ne);

      const std::int32_t original_prec_elem = my_prec_elem;

      // Do the inverse estimate using InternalFloatType precision estimates of mantissa and exponent.
      operator=(decwide_t(InternalFloatType(1) / dd, -ne));

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
        operator=(*this * (two<MyDigits10, LimbType, AllocatorType, InternalFloatType>() - (*this * x)));
      }

      my_neg = b_neg;

      my_prec_elem = original_prec_elem;

      return *this;
    }

    decwide_t& calculate_sqrt()
    {
      // Compute the square root of *this.

      if(isneg() || ((isfinite)() == false))
      {
        return (*this = my_value_nan());
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
      std::int64_t      ne;

      extract_parts(dd, ne);

      // Force the exponent to be an even multiple of two.
      if((ne % 2) != static_cast<std::int64_t>(0))
      {
        ++ne;
        dd /= InternalFloatType(10);
      }

      using std::sqrt;

      // Setup the iteration.
      // Estimate the square root using simple manipulations.
      const InternalFloatType sqd = sqrt(dd);

      const std::int32_t original_prec_elem = my_prec_elem;

      *this = decwide_t(sqd, static_cast<std::int64_t>(ne / 2));

      // Estimate 1.0 / (2.0 * x0) using simple manipulations.
      decwide_t vi(detail::fft::template_half<InternalFloatType>() / sqd, -static_cast<std::int64_t>(ne / 2));

      // Compute the square root of x. Coupled Newton iteration
      // as described in "Pi Unleashed" is used. During the
      // iterative steps, the precision of the calculation is
      // limited to the minimum required in order to minimize
      // the run-time.
      //
      // Book references:
      // http://www.jjj.de/pibook/pibook.html
      // http://www.amazon.com/exec/obidos/tg/detail/-/3540665722/qid=1035535482/sr=8-7/ref=sr_8_7/104-3357872-6059916?v=glance&n=507846

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
        vi += vi * (-((*this * vi) * static_cast<std::int32_t>(2)) + one<MyDigits10, LimbType, AllocatorType, InternalFloatType>());

        // Next iteration of *this
        *this += (vi * (-((*this) * (*this)) + x));
      }

      my_prec_elem = original_prec_elem;

      return *this;
    }

    decwide_t& negate()
    {
      if(((iszero)() == false) && ((isnan)() == false))
      {
        my_neg = (!my_neg);
      }

      return *this;
    }

    friend inline decwide_t rootn_inverse(decwide_t x, const std::int32_t p)
    {
      decwide_t result;

      if((x.isfinite)() == false)
      {
        result = std::numeric_limits<decwide_t>::quiet_NaN();
      }
      else if(p < static_cast<std::int32_t>(0))
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
        std::int64_t      ne;

        x.extract_parts(dd, ne);

        // Adjust exponent and mantissa such that ne is an even power of p.
        while(ne % static_cast<std::int64_t>(p))
        {
          ++ne;
          dd /= 10.0;
        }

        const std::int32_t original_prec_elem = x.my_prec_elem;

        using std::pow;

        // Estimate the one over the root using simple manipulations.
        const InternalFloatType one_over_rtn_d = pow(dd, InternalFloatType(-1) / static_cast<InternalFloatType>(p));

        // Set the result equal to the initial guess.
        result = decwide_t(one_over_rtn_d, static_cast<std::int64_t>(-ne / p));

        for(std::int32_t digits  = (std::int32_t) (std::numeric_limits<InternalFloatType>::digits10 - 1);
                         digits  < (std::int32_t) (original_prec_elem * decwide_t_elem_digits10);
                         digits *= static_cast<std::int32_t>(2))
        {
          // Adjust precision of the terms.
          const std::int32_t new_prec_as_digits10 =
              (std::int32_t) (digits * 2)
            + (std::max)((std::int32_t) (decwide_t_elem_digits10  + 1), (std::int32_t) 9);

          result.precision(new_prec_as_digits10);

          // Perform the next iteration.
          decwide_t term =
              (((-pow(result, p) * x) + one<MyDigits10, LimbType, AllocatorType, InternalFloatType>()) / p)
            + one<MyDigits10, LimbType, AllocatorType, InternalFloatType>();

          term.precision(new_prec_as_digits10);

          result *= term;
        }

        result.my_prec_elem = original_prec_elem;
      }

      return result;
    }

    // Comparison functions.
    bool (isnan)   () const { return (my_fpclass == decwide_t_NaN); }
    bool (isinf)   () const { return (my_fpclass == decwide_t_inf); }
    bool (isfinite)() const { return (my_fpclass == decwide_t_finite); }

    bool iszero() const
    {
      return ((my_fpclass == decwide_t_finite) && (my_data[0U] == static_cast<limb_type>(0U)));
    }

    bool isone() const
    {
      // Check if the value of *this is identically 1 or very close to 1.

      const bool not_negative_and_is_finite = ((!my_neg) && (isfinite)());

      if(not_negative_and_is_finite)
      {
        if((my_data[0U] == static_cast<limb_type>(1U)) && (my_exp == static_cast<std::int64_t>(0)))
        {
          const typename array_type::const_iterator it_non_zero =
            std::find_if(my_data.cbegin(),
                         my_data.cend(),
                         [](const limb_type& d) -> bool
                         {
                           return (d != static_cast<limb_type>(0U));
                         });

          return (it_non_zero == my_data.cend());
        }
        else if((my_data[0U] == static_cast<limb_type>(decwide_t_elem_mask - 1)) && (my_exp == static_cast<std::int64_t>(-decwide_t_elem_digits10)))
        {
          const typename array_type::const_iterator it_non_nine =
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

      if(my_exp < static_cast<std::int64_t>(0))
      {
        // Here, we have |*this| < 1, so *this can not be int.
        return false;
      }

      const typename array_type::size_type offset_decimal_part =
        static_cast<typename array_type::size_type>(my_exp / decwide_t_elem_digits10) + 1U;

      if(offset_decimal_part >= static_cast<typename array_type::size_type>(decwide_t_elem_number))
      {
        // The number is too large to resolve the integer part.
        // It considered to be a pure integer.
        return true;
      }

      typename array_type::const_iterator it_non_zero =
        std::find_if(my_data.cbegin() + static_cast<std::ptrdiff_t>(offset_decimal_part),
                     my_data.cend(),
                     [](const limb_type& d) -> bool
                     {
                       return (d != static_cast<limb_type>(0U));
                     });

      return (it_non_zero == my_data.cend());
    }

    bool isneg   () const { return my_neg; }
    bool ispos   () const { return (!isneg()); }

    // Operators pre-increment and pre-decrement.
    decwide_t& operator++() { return *this += one<MyDigits10, LimbType, AllocatorType, InternalFloatType>(); }
    decwide_t& operator--() { return *this -= one<MyDigits10, LimbType, AllocatorType, InternalFloatType>(); }

    // Operators post-increment and post-decrement.
    decwide_t operator++(int) { const decwide_t w(*this); static_cast<void>(++(*this)); return w; }
    decwide_t operator--(int) { const decwide_t w(*this); static_cast<void>(--(*this)); return w; }

    // Conversion routines.
    void extract_parts(InternalFloatType& mantissa, std::int64_t& exponent) const
    {
      // Extract the approximate parts mantissa and base-10 exponent from the input decwide_t value x.

      // Extracts the mantissa and exponent.
      exponent = my_exp;

      limb_type p10  = static_cast<limb_type>(1U);
      limb_type test = my_data[0U];

      for(;;)
      {
        test /= static_cast<limb_type>(10U);

        if(test == static_cast<limb_type>(0U))
        {
          break;
        }

        p10 *= static_cast<limb_type>(10U);

        ++exponent;
      }

      mantissa = static_cast<InternalFloatType>(my_data[0]) / static_cast<InternalFloatType>(p10);

      InternalFloatType scale = (InternalFloatType(1) / static_cast<InternalFloatType>(decwide_t_elem_mask)) / static_cast<InternalFloatType>(p10);

      std::int_fast16_t scale_order = -((std::int_fast16_t) decwide_t_elem_digits10);

      for(typename array_type::size_type i = 1U; i < my_data.size(); ++i)
      {
        mantissa += (static_cast<InternalFloatType>(my_data[i]) * scale);

        scale_order = -((std::int_fast16_t) decwide_t_elem_digits10);

        if(scale_order < -std::numeric_limits<InternalFloatType>::max_digits10)
        {
          break;
        }

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

      if((isfinite)() == false)
      {
        return *this;
      }

      if(my_exp < static_cast<std::int64_t>(0))
      {
        // The absolute value of the number is smaller than 1.
        // Thus the integer part is zero.
        return zero<MyDigits10, LimbType, AllocatorType, InternalFloatType>();
      }
      else if(my_exp >= static_cast<std::int64_t>(decwide_t_digits10 - 1))
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
      if((isfinite)() == false)
      {
        ld = ((isnan)() ? std::numeric_limits<long double>::quiet_NaN()
                        : ((my_neg == false) ?  std::numeric_limits<long double>::infinity()
                                             : -std::numeric_limits<long double>::infinity()));
      }
      else
      {
        const decwide_t xx(fabs(*this));

        // Check for zero decwide_t.
        if(iszero() || (xx < long_double_min<MyDigits10, LimbType, AllocatorType, InternalFloatType>()))
        {
          ld = 0.0L;
        }
        else
        if(xx > long_double_max<MyDigits10, LimbType, AllocatorType, InternalFloatType>())
        {
          // Check if decwide_t exceeds the maximum of double.
          ld = ((my_neg == false) ?  std::numeric_limits<long double>::infinity()
                                  : -std::numeric_limits<long double>::infinity());
        }
        else
        {
          ld = (long double) my_data[0U];

          long double scale = 1.0L;

          for(typename array_type::size_type i  = (typename array_type::size_type) decwide_t_elem_digits10;
                                             i  < (typename array_type::size_type) (std::numeric_limits<long double>::digits10 + 3);
                                             i += (typename array_type::size_type) decwide_t_elem_digits10)
          {
            scale /= (long double) decwide_t_elem_mask;

            ld += (long double) my_data[i / decwide_t_elem_digits10] * scale;
          }

          if(my_neg) { ld = -ld; }
        }
      }

      return ld;
    }

    signed long long extract_signed_long_long() const
    {
      // Extracts a signed long long from *this.
      // If (x > maximum of signed long long) or (x < minimum of signed long long),
      // then the maximum or minimum of signed long long is returned accordingly.

      if(my_exp < static_cast<std::int64_t>(0))
      {
        return static_cast<signed long long>(0);
      }

      const bool b_neg = isneg();

      unsigned long long val;

      if((!b_neg) && (*this > signed_long_long_max<MyDigits10, LimbType, AllocatorType, InternalFloatType>()))
      {
        return (std::numeric_limits<signed long long>::max)();
      }
      else if(b_neg &&  (*this < signed_long_long_min<MyDigits10, LimbType, AllocatorType, InternalFloatType>()))
      {
        return (std::numeric_limits<signed long long>::min)();
      }
      else
      {
        // Extract the data into an unsigned long long value.
        const decwide_t xn(fabs(extract_integer_part()));

        val = static_cast<unsigned long long>(xn.my_data[0]);

        const std::int32_t imax = (std::min)(static_cast<std::int32_t>(static_cast<std::int32_t>(xn.my_exp) / decwide_t_elem_digits10), static_cast<std::int32_t>(decwide_t_elem_number - static_cast<std::int32_t>(1)));

        for(typename array_type::size_type i = static_cast<typename array_type::size_type>(1); i <= static_cast<typename array_type::size_type>(imax); ++i)
        {
          val *= static_cast<unsigned long long>(decwide_t_elem_mask);
          val += static_cast<unsigned long long>(xn.my_data[i]);
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

      if(my_exp < static_cast<std::int64_t>(0))
      {
        return static_cast<unsigned long long>(0U);
      }

      const decwide_t xn(extract_integer_part());

      unsigned long long val;

      if(xn > unsigned_long_long_max<MyDigits10, LimbType, AllocatorType, InternalFloatType>())
      {
        return (std::numeric_limits<unsigned long long>::max)();
      }
      else
      {
        // Extract the data into an unsigned long long value.
        val = static_cast<unsigned long long>(xn.my_data[0]);

        const std::int32_t imax =
          (std::min)(static_cast<std::int32_t>(static_cast<std::int32_t>(xn.my_exp) / decwide_t_elem_digits10), static_cast<std::int32_t>(decwide_t_elem_number - static_cast<std::int32_t>(1)));

        for(typename array_type::size_type i = static_cast<typename array_type::size_type>(1); i <= static_cast<typename array_type::size_type>(imax); ++i)
        {
          val *= static_cast<unsigned long long>(decwide_t_elem_mask);
          val += static_cast<unsigned long long>(xn.my_data[i]);
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
    static InternalFloatType my_af_bf_fft_mul_pool[detail::decwide_t_helper<MyDigits10, LimbType>::pow2_maker_of_upper_limit(decwide_t_elem_number) * 8UL];
    static array_type        my_n_data_for_add_sub;
    #endif

    array_type   my_data;
    std::int64_t my_exp;
    bool         my_neg;
    fpclass_type my_fpclass;
    std::int32_t my_prec_elem;

    void from_unsigned_long_long(const unsigned long long u)
    {
      std::fill(my_data.begin(), my_data.end(), static_cast<limb_type>(0U));

      my_exp = static_cast<std::int64_t>(0);

      std::uint_fast32_t i =static_cast<std::uint_fast32_t>(0U);

      unsigned long long uu = u;

      limb_type temp[std::uint_fast32_t(std::numeric_limits<unsigned long long>::digits10 / static_cast<int>(decwide_t_elem_digits10)) + 3U] = { static_cast<limb_type>(0U) };

      while(uu != static_cast<unsigned long long>(0U))
      {
        temp[i] = static_cast<limb_type>(uu % static_cast<unsigned long long>(decwide_t_elem_mask));

        uu = static_cast<unsigned long long>(uu / static_cast<unsigned long long>(decwide_t_elem_mask));

        ++i;
      }

      if(i > static_cast<std::uint_fast32_t>(1U))
      {
        my_exp += static_cast<std::int64_t>((i - 1U) * static_cast<std::uint_fast32_t>(decwide_t_elem_digits10));
      }

      std::reverse(temp, temp + i);

      std::copy(temp, temp + (std::min)(i, static_cast<std::uint_fast32_t>(decwide_t_elem_number)), my_data.begin());
    }

    void from_long_double(const long double l)
    {
      const bool b_neg = (l < static_cast<long double>(0.0L));

      using std::isfinite;
      using std::isnan;

      if((isfinite)(static_cast<double>(l)) == false)
      {
        operator=((isnan)(static_cast<double>(l)) ? my_value_nan() : ((!b_neg) ? my_value_inf() : -my_value_inf()));

        return;
      }

      const long double my_ld = ((!b_neg) ? l : -l);

      if(my_ld < (std::numeric_limits<long double>::min)())
      {
        operator=(zero<MyDigits10, LimbType, AllocatorType, InternalFloatType>());

        return;
      }

      const native_float_parts<long double> ld_parts(my_ld);

      // Create a decwide_t from the fractional part of the
      // mantissa expressed as an unsigned long long.
      from_unsigned_long_long(ld_parts.get_mantissa());

      // Scale the unsigned long long representation to the fractional
      // part of the long double and multiply with the base-2 exponent.
      const int p2 = ld_parts.get_exponent() - (std::numeric_limits<long double>::digits - 1);

      if(p2 != 0)
      {
        operator*=(ldexp(one<MyDigits10, LimbType, AllocatorType, InternalFloatType>(), p2));
      }

      my_neg = b_neg;
    }

    std::int32_t cmp_data(const array_type& vd) const
    {
      // Compare the data of *this with those of v.
      //         Return +1 for *this > v
      //                 0 for *this = v
      //                -1 for *this < v

      using const_iterator_type = typename array_type::const_iterator;

      using mismatch_pair_type = std::pair<const_iterator_type, const_iterator_type>;

      const mismatch_pair_type mismatch_pair =
        std::mismatch(my_data.cbegin(), my_data.cend(), vd.cbegin());

      const bool is_equal = (   (mismatch_pair.first  == my_data.cend())
                             && (mismatch_pair.second == vd.cend()));

      const std::int32_t n_return =
        (is_equal ? static_cast<std::int32_t>(0)
                  : ((*mismatch_pair.first > *mismatch_pair.second) ? static_cast<std::int32_t>(1)
                                                                    : static_cast<std::int32_t>(-1)));

      return n_return;
    }

    static limb_type add_loop_uv(limb_type* const u, const limb_type* const v, const std::int32_t p)
    {
      // Addition algorithm
      limb_type carry = 0U;

      for(std::int32_t j = static_cast<std::int32_t>(p - static_cast<std::int32_t>(1)); j >= static_cast<std::int32_t>(0); j--)
      {
        const limb_type t = static_cast<limb_type>(static_cast<limb_type>(u[j] + v[j]) + carry);
        carry             = ((t > static_cast<limb_type>(decwide_t_elem_mask)) ? 1U : 0U);
        u[j]              = static_cast<limb_type>(t - ((carry != 0U) ? static_cast<limb_type>(decwide_t_elem_mask) : static_cast<limb_type>(0U)));
      }

      return carry;
    }

    static signed_limb_type sub_loop_uv(limb_type* const u, const limb_type* const v, const std::int32_t p)
    {
      // Subtraction algorithm
      signed_limb_type borrow = static_cast<std::int32_t>(0);

      for(std::uint32_t j = static_cast<std::uint32_t>(p - static_cast<std::int32_t>(1)); static_cast<std::int32_t>(j) >= static_cast<std::int32_t>(0); --j)
      {
        signed_limb_type t = static_cast<signed_limb_type>(static_cast<signed_limb_type>(u[j] - v[j]) - borrow);

        // Underflow? Borrow?
        if(t < 0)
        {
          // Yes, underflow and borrow
          t     += static_cast<signed_limb_type>(decwide_t_elem_mask);
          borrow = static_cast<signed_limb_type>(1);
        }
        else
        {
          borrow = static_cast<signed_limb_type>(0);
        }

        u[j] = static_cast<limb_type>(t);
      }

      return borrow;
    }

    static limb_type mul_loop_uv(limb_type* const u, const limb_type* const v, const std::int32_t p)
    {
      double_limb_type carry = static_cast<double_limb_type>(0U);

      for(std::int32_t j = static_cast<std::int32_t>(p - 1); j >= static_cast<std::int32_t>(0); j--)
      {
        double_limb_type sum = carry;

        for(std::int32_t i = j; i >= static_cast<std::int32_t>(0); i--)
        {
          sum += static_cast<double_limb_type>(u[j - i] * static_cast<double_limb_type>(v[i]));
        }

        u[j]  = static_cast<limb_type>(sum % static_cast<limb_type>(decwide_t_elem_mask));
        carry = static_cast<double_limb_type>(sum / static_cast<limb_type>(decwide_t_elem_mask));
      }

      return static_cast<limb_type>(carry);
    }

    static limb_type mul_loop_n(limb_type* const u, limb_type n, const std::int32_t p)
    {
      double_limb_type carry = static_cast<double_limb_type>(0U);

      // Multiplication loop.
      for(std::int32_t j = static_cast<std::int32_t>(p - 1); j >= static_cast<std::int32_t>(0); j--)
      {
        const double_limb_type t = static_cast<double_limb_type>(carry + static_cast<double_limb_type>(u[j] * static_cast<double_limb_type>(n)));
        carry                    = static_cast<double_limb_type>(t / static_cast<limb_type>(decwide_t_elem_mask));
        u[j]                     = static_cast<limb_type>(t - static_cast<double_limb_type>(static_cast<limb_type>(decwide_t_elem_mask) * carry));
      }

      return static_cast<limb_type>(carry);
    }

    static limb_type div_loop_n(limb_type* const u, limb_type n, const std::int32_t p)
    {
      double_limb_type prev = static_cast<double_limb_type>(0U);

      for(std::int32_t j = static_cast<std::int32_t>(0); j < p; j++)
      {
        const double_limb_type t = static_cast<double_limb_type>(u[j] + static_cast<double_limb_type>(prev * static_cast<limb_type>(decwide_t_elem_mask)));
        u[j]                     = static_cast<limb_type>(t / n);
        prev                     = static_cast<double_limb_type>(t - static_cast<double_limb_type>(n * static_cast<double_limb_type>(u[j])));
      }

      return static_cast<limb_type>(prev);
    }

    static void mul_loop_karatsuba_n_by_n_to_2n(      limb_type*          r,
                                                const limb_type*          a,
                                                const limb_type*          b,
                                                const std::uint_fast32_t count)
    {
    }

    static void mul_loop_karatsuba_propagate_carry(limb_type* t, const std::uint_fast32_t n, const bool has_borrow)
    {
    }

    static void mul_loop_karatsuba_propagate_borrow(limb_type* t, const std::uint_fast32_t n, const bool has_borrow)
    {
    }

    static void mul_loop_karatsuba_n_by_n_to_2n(      limb_type*          r,
                                                const limb_type*          a,
                                                const limb_type*          b,
                                                const std::uint_fast32_t n,
                                                      limb_type*          t)
    {
    }

    static void mul_loop_karatsuba(limb_type* const u, const limb_type* const v, const std::int32_t prec_elems_for_multiply)
    {
    }

    static void mul_loop_fft(limb_type* const u, const limb_type* const v, const std::int32_t prec_elems_for_multiply)
    {
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

      std::uint32_t n_fft = 0U;

      {
        std::uint32_t p_fft = (std::uint32_t) ((prec_elems_for_multiply * 2L) * 2L);

        // Use O(log2[N]) binary-halving in an unrolled loop to find the msb.
        if((p_fft & UINT32_C(0xFFFF0000)) != UINT32_C(0)) { p_fft >>= 16U; n_fft |= UINT8_C(16); }
        if((p_fft & UINT32_C(0x0000FF00)) != UINT32_C(0)) { p_fft >>=  8U; n_fft |= UINT8_C( 8); }
        if((p_fft & UINT32_C(0x000000F0)) != UINT32_C(0)) { p_fft >>=  4U; n_fft |= UINT8_C( 4); }
        if((p_fft & UINT32_C(0x0000000C)) != UINT32_C(0)) { p_fft >>=  2U; n_fft |= UINT8_C( 2); }
        if((p_fft & UINT32_C(0x00000002)) != UINT32_C(0)) { p_fft >>=  1U; n_fft |= UINT8_C( 1); }

        // We now obtain the needed FFT size doubled (and doubled again),
        // with the added condition of needing to be a power of 2.
        n_fft = (std::uint32_t) (1UL << n_fft);

        if(n_fft < (std::uint32_t) ((prec_elems_for_multiply * 2L) * 2L))
        {
          n_fft <<= 1U;
        }
      }

      // We now have the needed FFT size doubled (and doubled again).

      #if !defined(WIDE_DECIMAL_DISABLE_DYNAMIC_MEMORY_ALLOCATION)
      InternalFloatType* my_af_bf_fft_mul_pool = new InternalFloatType[n_fft * 2U];
      #endif

      std::fill(my_af_bf_fft_mul_pool, my_af_bf_fft_mul_pool + (n_fft * 2U), InternalFloatType(0));

      InternalFloatType* af = my_af_bf_fft_mul_pool + (0U * n_fft);
      InternalFloatType* bf = my_af_bf_fft_mul_pool + (1U * n_fft);

      for(std::uint32_t i = static_cast<std::uint32_t>(0U); i < static_cast<std::uint32_t>(prec_elems_for_multiply); ++i)
      {
        af[(i * 2U)]      = InternalFloatType(u[i] / decwide_t_elem_mask_half);
        af[(i * 2U) + 1U] = InternalFloatType(u[i] % decwide_t_elem_mask_half);

        bf[(i * 2U)]      = InternalFloatType(v[i] / decwide_t_elem_mask_half);
        bf[(i * 2U) + 1U] = InternalFloatType(v[i] % decwide_t_elem_mask_half);
      }

      // Perform forward FFTs on the data arrays a and b.
      detail::fft::rfft_lanczos_rfft<InternalFloatType, true>(n_fft, af);
      detail::fft::rfft_lanczos_rfft<InternalFloatType, true>(n_fft, bf);

      // Perform the convolution of a and b in the transform space.
      // This does, in fact, execute the actual multiplication of (a * b).
      af[0U] *= bf[0U];
      af[1U] *= bf[1U];

      for(std::uint32_t j = static_cast<std::uint32_t>(2U); j < n_fft; j += 2U)
      {
        const InternalFloatType tmp_aj = af[j];

        af[j + 0U] = (tmp_aj * bf[j + 0U]) - (af[j + 1U] * bf[j + 1U]);
        af[j + 1U] = (tmp_aj * bf[j + 1U]) + (af[j + 1U] * bf[j + 0U]);
      }

      // Perform the reverse FFT on the result of the convolution.
      detail::fft::rfft_lanczos_rfft<InternalFloatType, false>(n_fft, af);

      // Release the carries and re-combine the low and high parts.
      // This sets the integral data elements in the big number
      // to the result of multiplication.
      double_limb_type carry = static_cast<double_limb_type>(0U);

      for(std::uint32_t j = static_cast<std::uint32_t>((prec_elems_for_multiply * 2L) - 2L); static_cast<std::int32_t>(j) >= 0; j -= 2U)
      {
        InternalFloatType      xaj = af[j] / (n_fft / 2U);
        const double_limb_type xlo = static_cast<double_limb_type>(xaj + detail::fft::template_half<InternalFloatType>()) + carry;
        carry                      = static_cast<double_limb_type>(xlo / static_cast<limb_type>(decwide_t_elem_mask_half));
        const limb_type        nlo = static_cast<limb_type>       (xlo - static_cast<double_limb_type>(carry * static_cast<limb_type>(decwide_t_elem_mask_half)));

                               xaj = ((j != 0) ? (af[j - 1U] / (n_fft / 2U)) : InternalFloatType(0));
        const double_limb_type xhi = static_cast<double_limb_type>(xaj + detail::fft::template_half<InternalFloatType>()) + carry;
        carry                      = static_cast<double_limb_type>(xhi / static_cast<limb_type>(decwide_t_elem_mask_half));
        const limb_type        nhi = static_cast<limb_type>       (xhi - static_cast<double_limb_type>(carry * static_cast<limb_type>(decwide_t_elem_mask_half)));

        u[(j / 2U)] = static_cast<limb_type>(static_cast<limb_type>(nhi * static_cast<limb_type>(decwide_t_elem_mask_half)) + nlo);
      }

      #if !defined(WIDE_DECIMAL_DISABLE_DYNAMIC_MEMORY_ALLOCATION)
      // De-allocate the dynamic memory for the FFT result arrays.
      delete [] my_af_bf_fft_mul_pool;
      #endif
    }

    template<const std::int32_t ElemsForFftThreshold>
    void eval_mul_dispatch_multiplication_method(const decwide_t& v,
                                                 const std::int32_t prec_elems_for_multiply,
                                                 const std::int32_t = ElemsForFftThreshold,
                                                 const typename std::enable_if<(decwide_t_elems_for_fft >= ElemsForFftThreshold)>::type* = nullptr)
    {
      // Use school multiplication.
      const limb_type carry = mul_loop_uv(my_data.data(), v.my_data.data(), prec_elems_for_multiply);

      // Handle a potential carry.
      if(carry != static_cast<limb_type>(0U))
      {
        my_exp += static_cast<std::int64_t>(decwide_t_elem_digits10);

        // Shift the result of the multiplication one element to the right.
        std::copy_backward(my_data.cbegin(),
                           my_data.cbegin() + static_cast<std::ptrdiff_t>(my_prec_elem - 1),
                           my_data.begin()  + static_cast<std::ptrdiff_t>(my_prec_elem));

        my_data.front() = static_cast<limb_type>(carry);
      }
    }

    template<const std::int32_t ElemsForFftThreshold>
    void eval_mul_dispatch_multiplication_method(const decwide_t& v,
                                                 const std::int32_t prec_elems_for_multiply,
                                                 const std::int32_t = ElemsForFftThreshold,
                                                 const typename std::enable_if<(ElemsForFftThreshold > decwide_t_elems_for_fft)>::type* = nullptr)
    {
      // Note: Karatsuba multiplication is not used for intermediate digit counts.
      // TBD: Implement Karatsuba multiplication for intermediate digit counts.

      if(prec_elems_for_multiply < decwide_t_elems_for_fft)
      {
        // Use school multiplication.
        const limb_type carry = mul_loop_uv(my_data.data(), v.my_data.data(), prec_elems_for_multiply);

        // Handle a potential carry.
        if(carry != static_cast<limb_type>(0U))
        {
          my_exp += static_cast<std::int64_t>(decwide_t_elem_digits10);

          // Shift the result of the multiplication one element to the right.
          std::copy_backward(my_data.cbegin(),
                             my_data.cbegin() + static_cast<std::ptrdiff_t>(my_prec_elem - 1),
                             my_data.begin()  + static_cast<std::ptrdiff_t>(my_prec_elem));

          my_data.front() = static_cast<limb_type>(carry);
        }
      }
      else
      {
        // Use FFT-based multiplication.
        mul_loop_fft(my_data.data(), v.my_data.data(), static_cast<std::int32_t>(prec_elems_for_multiply));

        if(my_data.front() != static_cast<limb_type>(0U))
        {
          // Adjust the exponent because of the internal scaling of the FFT multiplication.
          my_exp += static_cast<std::int64_t>(decwide_t_elem_digits10);
        }
        else
        {
          // Justify the data if necessary.
          std::copy(my_data.cbegin() +  1,
                    my_data.cbegin() + (std::min)(decwide_t_elem_number, (std::int32_t) (my_prec_elem + 1)),
                    my_data.begin());

          my_data.back() = static_cast<limb_type>(0U);
        }
      }
    }

    #if !defined(WIDE_DECIMAL_DISABLE_CONSTRUCT_FROM_STRING)
    bool rd_string(const char* const s)
    {
      std::string str(s);

      // Get a possible exponent and remove it.
      my_exp = static_cast<std::int64_t>(0);

      std::size_t pos;

      if(   ((pos = str.find('e')) != std::string::npos)
         || ((pos = str.find('E')) != std::string::npos)
        )
      {
        // Remove the exponent part from the string.
        my_exp = Util::numeric_cast<std::int64_t>(static_cast<const char*>(str.c_str() + (pos + 1U)));

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
          operator=(zero<MyDigits10, LimbType, AllocatorType, InternalFloatType>());

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
          operator=(zero<MyDigits10, LimbType, AllocatorType, InternalFloatType>());
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

          my_exp -= static_cast<std::int64_t>(delta_exp + 1U);
        }
      }
      else
      {
        // Input string has no decimal point: Append decimal point.
        str.append(".");
      }

      // Shift the decimal point such that the exponent is an even multiple of decwide_t_elem_digits10.
            std::ptrdiff_t n_shift   = static_cast<std::ptrdiff_t>(0);
      const std::ptrdiff_t n_exp_rem = static_cast<std::ptrdiff_t>(my_exp % static_cast<std::int64_t>(decwide_t_elem_digits10));

      if((my_exp % static_cast<std::int64_t>(decwide_t_elem_digits10)) != static_cast<std::int64_t>(0))
      {
        n_shift = ((my_exp < static_cast<std::int64_t>(0))
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

        str.erase(pos, static_cast<std::ptrdiff_t>(1U));

        my_exp -= static_cast<std::int64_t>(n_shift);
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

        my_exp += static_cast<std::int64_t>(static_cast<std::int64_t>(n) * static_cast<std::int64_t>(decwide_t_elem_digits10));
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
      my_data[static_cast<typename array_type::size_type>(0U)] =
        Util::numeric_cast<limb_type>(str.substr(static_cast<std::ptrdiff_t>(0), pos));

      // ...then get the remaining digits to the right of the decimal point.
      const std::string::difference_type i_end = ((static_cast<std::string::difference_type>(str.length()) - pos_plus_one) / static_cast<std::string::difference_type>(decwide_t_elem_digits10));

      for(std::string::difference_type i = static_cast<std::string::difference_type>(0); i < i_end; ++i)
      {
        const std::string::const_iterator it =   str.cbegin()
                                               + static_cast<std::string::difference_type>(pos_plus_one)
                                               + (i * static_cast<std::string::difference_type>(decwide_t_elem_digits10));

        const typename array_type::size_type i1 = static_cast<typename array_type::size_type>(i + 1);

        const std::string str_i1(it,
                                 it + static_cast<std::string::difference_type>(decwide_t_elem_digits10));

        my_data[i1] = Util::numeric_cast<limb_type>(str_i1);
      }

      // Check for overflow...
      if(my_exp > decwide_t_max_exp10)
      {
        const bool b_result_is_neg = my_neg;

        *this = ((!b_result_is_neg) ?  my_value_inf() : -my_value_inf());
      }

      // ...and check for underflow.
      if(my_exp <= decwide_t_min_exp10)
      {
        if(my_exp == decwide_t_min_exp10)
        {
          // Check for identity with the minimum value.
          decwide_t test = *this;

          test.my_exp = static_cast<std::int64_t>(0);

          if(test.isone())
          {
            *this = zero<MyDigits10, LimbType, AllocatorType, InternalFloatType>();
          }
        }
        else
        {
          *this = zero<MyDigits10, LimbType, AllocatorType, InternalFloatType>();
        }
      }

      return true;
    }
    #endif //!(WIDE_DECIMAL_DISABLE_CONSTRUCT_FROM_STRING)

    #if !defined(WIDE_DECIMAL_DISABLE_IOSTREAM)
    void get_output_string(std::string& str, std::int64_t& the_exp, const std::uint_fast32_t number_of_digits) const
    {
      // Determine the number of elements needed to provide the requested digits from decwide_t.
      const std::uint_fast32_t number_of_elements = (std::min)(static_cast<std::uint_fast32_t>((number_of_digits / static_cast<std::uint_fast32_t>(decwide_t_elem_digits10)) + 2U),
                                                        static_cast<std::uint_fast32_t>(decwide_t_elem_number));

      // Extract the remaining digits from decwide_t after the decimal point.
      char p_str[10U] = { 0 };
      char* p_end = util::baselexical_cast(my_data[0], p_str);

      str = std::string(p_str, p_end);

      // Extract all of the digits from decwide_t, beginning with the first data element.
      for(std::uint_fast32_t i = static_cast<std::uint_fast32_t>(1U); i < number_of_elements; i++)
      {
        std::stringstream ss;

        ss << std::setw(static_cast<std::streamsize>(decwide_t_elem_digits10))
           << std::setfill(static_cast<char>('0'))
           << my_data[i];

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

      // Use special handling for non-finite numbers (inf and nan).
      if((isfinite)() == false)
      {
        special_handle_string_not_finite(str, static_cast<const decwide_t&>(*this), my_showpos, my_uppercase);

        return;
      }

      // Get the base-10 exponent.
      std::int64_t the_exp = (std::int64_t) ilogb(*this);

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
        static const std::int64_t neg_bound_for_scientific_neg_exp = static_cast<std::int64_t>(-4);
               const std::int64_t min_bound_for_scientific_pos_exp = (std::max)(static_cast<std::int64_t>(os_precision), static_cast<std::int64_t>(prec_default));
               const std::int64_t pos_bound_for_scientific_pos_exp = (std::min)(static_cast<std::int64_t>(decwide_t_digits10), min_bound_for_scientific_pos_exp);

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

        if(the_exp >= static_cast<std::int64_t>(0))
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
          const std::int64_t exp_plus_one = static_cast<std::int64_t>(the_exp + 1);
          const std::int64_t exp_plus_one_plus_my_precision = static_cast<std::int64_t>(exp_plus_one + static_cast<std::int64_t>(os_precision));

          the_number_of_digits_i_want_from_decwide_t = (std::min)(static_cast<std::uint_fast32_t>((std::max)(exp_plus_one_plus_my_precision, static_cast<std::int64_t>(0))), max10_plus_one);
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
                                      const std::int64_t the_exp,
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
      const bool          b_exp_is_neg = (the_exp < static_cast<std::int64_t>(0));
      const std::uint64_t u_exp        = static_cast<std::uint64_t>(!b_exp_is_neg ? the_exp : static_cast<std::int64_t>(-the_exp));

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
                                const std::int64_t the_exp,
                                const std::uint_fast32_t os_precision,
                                const bool my_showpoint,
                                const bool trim_trailing_zeros = false)
    {
      const std::size_t input_str_len = str.length();

      if(the_exp < static_cast<std::int64_t>(0))
      {
        // The number is less than one in magnitude. Insert the decimal
        // point using "0." as well as the needed number of leading zeros.
        const std::uint_fast32_t minus_exp_minus_one = static_cast<std::uint_fast32_t>(-the_exp - 1);

        const std::string str_zero_insert((std::min)(minus_exp_minus_one, os_precision), static_cast<char>('0'));

        const std::int64_t n_pad = static_cast<std::int64_t>(static_cast<std::int64_t>(os_precision) - static_cast<std::int64_t>(str.length() + str_zero_insert.length()));

        str.insert(0U, "0." + str_zero_insert);

        // Zero-extend the string to the given precision if necessary.
        if(n_pad > static_cast<std::int64_t>(0))
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
        const std::int64_t n_pad = static_cast<std::int64_t>(os_precision) - static_cast<std::int64_t>(static_cast<std::int64_t>(str.length() - 1U) - (the_exp + 1));

        if(n_pad > static_cast<std::int64_t>(0))
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

    static void special_handle_string_not_finite(std::string& str,
                                                  const decwide_t& f,
                                                  const bool my_showpos,
                                                  const bool my_uppercase)
    {
      // Handle INF and NaN.
      if((f.isinf)())
      {
        if(my_uppercase)
        {
          str = ((!f.isneg()) ? (my_showpos ? std::string("+INF") : std::string("INF")) : std::string("-INF"));
        }
        else
        {
          str = ((!f.isneg()) ? (my_showpos ? std::string("+inf") : std::string("inf")) : std::string("-inf"));
        }
      }
      else
      {
        str = (my_uppercase ? std::string("NAN") : std::string("nan"));
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

    friend inline std::ostream& operator<<(std::ostream& os, const decwide_t& f)
    {
      std::string str;

      f.wr_string(str, os);

      return (os << str);
    }

    friend inline std::istream& operator>>(std::istream& is, decwide_t& f)
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
               : (x.isneg() ? (x - one<MyDigits10, LimbType, AllocatorType, InternalFloatType>()).extract_integer_part()
                            :  x.extract_integer_part()));
    }

    friend inline decwide_t ceil(decwide_t x)
    {
      return ((((x.isfinite)() == false) || x.isint())
               ?  x
               : (x.isneg() ?  x.extract_integer_part()
                            : (x + one<MyDigits10, LimbType, AllocatorType, InternalFloatType>()).extract_integer_part()));
    }

    friend inline std::int32_t ilogb(decwide_t x)
    {
      std::int64_t e10;

      if((x.isfinite)() == false)
      {
        e10 = static_cast<std::int64_t>(0);
      }
      else
      {
        std::int_fast16_t n10 = INT16_C(-1);

        limb_type p10 = (limb_type) 1U;

        const limb_type limit_aligned_with_10 = x.my_data[0U] + (limb_type) (10U - (x.my_data[0U] % 10U));

        while(p10 < limit_aligned_with_10)
        {
          p10 *= 10U;

          ++n10;
        }

        e10 = static_cast<std::int64_t>(x.my_exp + n10);
      }

      return (std::max)(           (std::numeric_limits<std::int32_t>::min)(),
                        (std::min)((std::numeric_limits<std::int32_t>::max)(), (std::int32_t) e10));
    }
  };

  #if !defined(WIDE_DECIMAL_DISABLE_CACHED_CONSTANTS)
  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType>
  typename decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>::initializer decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>::init;
  #endif

  #if !defined(WIDE_DECIMAL_DISABLE_DYNAMIC_MEMORY_ALLOCATION)
  #else
  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType>
  InternalFloatType decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>::my_af_bf_fft_mul_pool[detail::decwide_t_helper<MyDigits10, LimbType>::pow2_maker_of_upper_limit(decwide_t_elem_number) * 8UL];

  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType>
  typename decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>::array_type decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>::my_n_data_for_add_sub;
  #endif

  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType>
  constexpr decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType> zero()
  {
    using floating_point_type = decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>;

    return floating_point_type( { typename floating_point_type::limb_type(0U) } );
  }

  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType>
  constexpr decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType> one()
  {
    using floating_point_type = decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>;

    return floating_point_type( { typename floating_point_type::limb_type(1U) } );
  }

  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType>
  constexpr decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType> two()
  {
    using floating_point_type = decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>;

    return floating_point_type( { typename floating_point_type::limb_type(2U) } );
  }

  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType>
  constexpr decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType> half()
  {
    using floating_point_type = decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>;

    return floating_point_type
           (
             {
               typename floating_point_type::limb_type(floating_point_type::decwide_t_elem_mask / 2)
             },
             -floating_point_type::decwide_t_elem_digits10
           );
  }

  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType> decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType> calc_pi(void(*pfn_callback_to_report_digits10)(const std::uint32_t))
  {
    // Description : Compute pi using the quadratically convergent Gauss AGM,
    //               in particular the Schoenhage variant.
    //               For a description of the algorithm see the book "Pi Unleashed":
    //               If the input b_trace = true, then the calculation progress
    //               will be output to cout.
    //
    //               Book reference:
    //               http://www.jjj.de/pibook/pibook.html
    //               http://www.amazon.com/exec/obidos/tg/detail/-/3540665722/qid=1035535482/sr=8-7/ref=sr_8_7/104-3357872-6059916?v=glance&n=507846
    //
    //               Digits of pi available for test at:
    //               http://www.hepl.phys.nagoya-u.ac.jp/~mitsuru/pi-e.html
    //               http://www.cecm.sfu.ca/projects/ISC/data/pi.html

    if(pfn_callback_to_report_digits10 != nullptr)
    {
      pfn_callback_to_report_digits10((std::uint32_t) 0U);
    }

    using floating_point_type = decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>;

    floating_point_type val_pi;

    floating_point_type a
    (
      {
        (typename floating_point_type::limb_type) 1U
      },
      0
    );

    // Initialize bB to 0.5.
    floating_point_type bB
    (
      {
        (typename floating_point_type::limb_type) (floating_point_type::decwide_t_elem_mask / 2)
      },
      -floating_point_type::decwide_t_elem_digits10
    );

    // Initialize t to 0.375.
    floating_point_type t
    (
      {
        (typename floating_point_type::limb_type) ((floating_point_type::decwide_t_elem_mask * 3LL) / 8L)
      },
      -floating_point_type::decwide_t_elem_digits10
    );

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

  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType> decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType> calc_ln_two()
  {
    using floating_point_type = decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>;

    // Use an AGM method to compute log(2).

    // Set a0 = 1
    // Set b0 = 1 / (2^(m-2))

    floating_point_type ak(1U);

    using std::log;

    const float n_times_factor = ((float) std::numeric_limits<floating_point_type>::digits10) * 1.67F;

    // Ensure that the resulting power is non-negative.
    // Also enforce that m >= 3.
    const std::int32_t m = (std::max)((std::int32_t) n_times_factor, (std::int32_t) 3);

    floating_point_type bk =
      ldexp(one<MyDigits10, LimbType, AllocatorType, InternalFloatType>(), (std::int32_t) (2 - m));

    const std::uint32_t digits10_iteration_goal =
        (std::uint32_t) (std::numeric_limits<floating_point_type>::digits10 / 2)
      + (std::max)((std::uint32_t) (floating_point_type::decwide_t_elem_digits10 + 1), (std::uint32_t) 9U);

    using std::log;

    const std::uint32_t digits10_scale =
      (std::uint32_t) (0.5F + (1000.0F * log((float) std::numeric_limits<floating_point_type>::radix)) / log(10.0F));

    for(std::int32_t k = static_cast<std::int32_t>(0); k < static_cast<std::int32_t>(64); ++k)
    {
      using std::ilogb;
      using std::sqrt;

      // Check for the number of significant digits to be
      // at least half of the requested digits. If at least
      // half of the requested digits have been achieved,
      // then break after the upcoming iteration.

      const std::int32_t ib = (std::max)(std::int32_t(0), -ilogb(ak - bk));

      const std::uint32_t digits10_of_iteration =
        (std::uint32_t) ((std::uint64_t) ((std::uint64_t) ib * digits10_scale) / 1000U);

      const floating_point_type ak_tmp(ak);

      ak += bk;
      ak /= 2;

      if(digits10_of_iteration > digits10_iteration_goal)
      {
        break;
      }

      bk *= ak_tmp;
      bk  = sqrt(bk);
    }

    // We are now finished with the AGM iteration for log(2).
    // Note at this time that (ak = bk) = AGM(...)
    // Retrieve the value of pi and divide by (a * (2 * m)).

    const floating_point_type result =
         pi<MyDigits10, LimbType, AllocatorType, InternalFloatType>() / (ak * (2 * m));

    return result;
  }

  #if !defined(WIDE_DECIMAL_DISABLE_CACHED_CONSTANTS)
  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType> const decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>& pi(void(*pfn_callback_to_report_digits10)(const std::uint32_t))
  {
    (void) pfn_callback_to_report_digits10;

    return decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>::my_value_pi();
  }
  #else
  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType> decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType> pi(void(*pfn_callback_to_report_digits10)(const std::uint32_t))
  {
    return calc_pi<MyDigits10, LimbType, AllocatorType, InternalFloatType>(pfn_callback_to_report_digits10);
  }
  #endif

  #if !defined(WIDE_DECIMAL_DISABLE_CACHED_CONSTANTS)
  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType> const decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>& ln_two()
  {
    return decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>::my_value_ln_two();
  }
  #else
  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType> decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType> ln_two()
  {
    return calc_ln_two<MyDigits10, LimbType, AllocatorType, InternalFloatType>();
  }
  #endif

  // Global unary operators of decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType> reference.
  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType> decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType> operator+(const decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>& self) { return decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>(self); }
  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType> decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType> operator-(const decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>& self) { decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType> tmp(self); tmp.negate(); return tmp; }

  // Global add/sub/mul/div of const decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>& with const decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>&.
  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType> decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType> operator+(const decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>& u, const decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>& v) { return decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>(u) += v; }
  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType> decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType> operator-(const decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>& u, const decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>& v) { return decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>(u) -= v; }
  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType> decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType> operator*(const decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>& u, const decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>& v) { return decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>(u) *= v; }
  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType> decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType> operator/(const decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>& u, const decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>& v) { return decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>(u) /= v; }

  // Global add/sub/mul/div of const decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>& with all built-in types.
  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType, typename SignedIntegralType>
  typename std::enable_if<   (std::is_integral<SignedIntegralType>::value == true)
                          && (std::is_unsigned<SignedIntegralType>::value == false), decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>>::type operator+(const decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>& u, const SignedIntegralType& n)
  {
    return decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>(u).add_signed_long_long(n);
  }

  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType, typename UnsignedIntegralType>
  typename std::enable_if<   (std::is_integral<UnsignedIntegralType>::value == true)
                          && (std::is_unsigned<UnsignedIntegralType>::value == true), decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>>::type operator+(const decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>& u, const UnsignedIntegralType& n)
  {
    return decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>(u).add_unsigned_long_long(n);
  }

  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType, typename FloatingPointType>
  typename std::enable_if<(std::is_floating_point<FloatingPointType>::value == true), decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>>::type operator+(const decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>& u, const FloatingPointType& f)
  {
    return decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>(u) += decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>(f);
  }

  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType, typename SignedIntegralType>
  typename std::enable_if<   (std::is_integral<SignedIntegralType>::value == true)
                          && (std::is_unsigned<SignedIntegralType>::value == false), decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>>::type operator-(const decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>& u, const SignedIntegralType& n)
  {
    return decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>(u).sub_signed_long_long(n);
  }

  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType, typename UnsignedIntegralType>
  typename std::enable_if<   (std::is_integral<UnsignedIntegralType>::value == true)
                          && (std::is_unsigned<UnsignedIntegralType>::value == true), decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>>::type operator-(const decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>& u, const UnsignedIntegralType& n)
  {
    return decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>(u).sub_unsigned_long_long(n);
  }

  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType, typename FloatingPointType>
  typename std::enable_if<(std::is_floating_point<FloatingPointType>::value == true), decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>>::type operator-(const decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>& u, const FloatingPointType& f)
  {
    return decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>(u) -= decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>(f);
  }

  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType, typename SignedIntegralType>
  typename std::enable_if<   (std::is_integral<SignedIntegralType>::value == true)
                          && (std::is_unsigned<SignedIntegralType>::value == false), decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>>::type operator*(const decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>& u, const SignedIntegralType& n)
  {
    return decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>(u).mul_signed_long_long(n);
  }

  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType, typename UnsignedIntegralType>
  typename std::enable_if<   (std::is_integral<UnsignedIntegralType>::value == true)
                          && (std::is_unsigned<UnsignedIntegralType>::value == true), decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>>::type operator*(const decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>& u, const UnsignedIntegralType& n)
  {
    return decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>(u).mul_unsigned_long_long(n);
  }

  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType, typename FloatingPointType>
  typename std::enable_if<(std::is_floating_point<FloatingPointType>::value == true), decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>>::type operator*(const decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>& u, const FloatingPointType& f)
  {
    return decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>(u) *= decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>(f);
  }

  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType, typename SignedIntegralType>
  typename std::enable_if<   (std::is_integral<SignedIntegralType>::value == true)
                          && (std::is_unsigned<SignedIntegralType>::value == false), decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>>::type operator/(const decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>& u, const SignedIntegralType& n)
  {
    return decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>(u).div_signed_long_long(n);
  }

  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType, typename UnsignedIntegralType>
  typename std::enable_if<   (std::is_integral<UnsignedIntegralType>::value == true)
                          && (std::is_unsigned<UnsignedIntegralType>::value == true), decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>>::type operator/(const decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>& u, const UnsignedIntegralType& n)
  {
    return decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>(u).div_unsigned_long_long(n);
  }

  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType, typename FloatingPointType>
  typename std::enable_if<(std::is_floating_point<FloatingPointType>::value == true), decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>>::type operator/(const decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>& u, const FloatingPointType& f)
  {
    return decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>(u) /= decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>(f);
  }

  // Global add/sub/mul/div of all built-in types with const decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>&.
  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType, typename SignedIntegralType>
  typename std::enable_if<   (std::is_integral<SignedIntegralType>::value == true)
                          && (std::is_unsigned<SignedIntegralType>::value == false), decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>>::type operator+(const SignedIntegralType& n, const decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>& u)
  {
    return decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>(u).add_signed_long_long(n);
  }

  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType, typename UnsignedIntegralType>
  typename std::enable_if<   (std::is_integral<UnsignedIntegralType>::value == true)
                          && (std::is_unsigned<UnsignedIntegralType>::value == true), decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>>::type operator+(const UnsignedIntegralType& n, const decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>& u)
  {
    return decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>(u).add_unsigned_long_long(n);
  }

  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType, typename FloatingPointType>
  typename std::enable_if<(std::is_floating_point<FloatingPointType>::value == true), decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>>::type operator+(const FloatingPointType& f, const decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>& u)
  {
    return decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>(f) += u;
  }

  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ArithmeticType>
  typename std::enable_if<(std::is_arithmetic<ArithmeticType>::value == true), decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>>::type operator-(const ArithmeticType& n, const decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>& u)
  {
    return decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>(n) -= u;
  }

  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType, typename SignedIntegralType>
  typename std::enable_if<   (std::is_integral<SignedIntegralType>::value == true)
                          && (std::is_unsigned<SignedIntegralType>::value == false), decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>>::type operator*(const SignedIntegralType& n, const decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>& u)
  {
    return decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>(u).mul_signed_long_long(n);
  }

  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType, typename UnsignedIntegralType>
  typename std::enable_if<   (std::is_integral<UnsignedIntegralType>::value == true)
                          && (std::is_unsigned<UnsignedIntegralType>::value == true), decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>>::type operator*(const UnsignedIntegralType& n, const decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>& u)
  {
    return decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>(u).mul_unsigned_long_long(n);
  }

  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType, typename FloatingPointType>
  typename std::enable_if<(std::is_floating_point<FloatingPointType>::value == true), decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>>::type operator*(const FloatingPointType& f, const decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>& u)
  {
    return decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>(f) *= u;
  }

  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ArithmeticType>
  typename std::enable_if<(std::is_arithmetic<ArithmeticType>::value == true), decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>>::type operator/(const ArithmeticType& n, const decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>& u)
  {
    return decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>(n) /= u;
  }

  // Global self add/sub/mul/div of decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>& with all built-in types.
  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType, typename SignedIntegralType>
  typename std::enable_if<   (std::is_integral<SignedIntegralType>::value == true)
                          && (std::is_unsigned<SignedIntegralType>::value == false), decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>>::type operator+=(decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>& u, const SignedIntegralType& n)
  {
    return u.add_signed_long_long(n);
  }

  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType, typename UnsignedIntegralType>
  typename std::enable_if<   (std::is_integral<UnsignedIntegralType>::value == true)
                          && (std::is_unsigned<UnsignedIntegralType>::value == true), decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>>::type operator+=(decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>& u, const UnsignedIntegralType& n)
  {
    return u.add_unsigned_long_long(n);
  }

  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType, typename FloatingPointType>
  typename std::enable_if<(std::is_floating_point<FloatingPointType>::value == true), decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>>::type operator+=(decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>& u, const FloatingPointType& f)
  {
    return u += decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>(f);
  }

  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType, typename SignedIntegralType>
  typename std::enable_if<   (std::is_integral<SignedIntegralType>::value == true)
                          && (std::is_unsigned<SignedIntegralType>::value == false), decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>>::type operator-=(decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>& u, const SignedIntegralType& n)
  {
    return u.sub_signed_long_long(n);
  }

  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType, typename UnsignedIntegralType>
  typename std::enable_if<   (std::is_integral<UnsignedIntegralType>::value == true)
                          && (std::is_unsigned<UnsignedIntegralType>::value == true), decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>>::type operator-=(decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>& u, const UnsignedIntegralType& n)
  {
    return u.sub_unsigned_long_long(n);
  }

  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType, typename FloatingPointType>
  typename std::enable_if<(std::is_floating_point<FloatingPointType>::value == true), decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>>::type operator-=(decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>& u, const FloatingPointType& f)
  {
    return u -= decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>(f);
  }

  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType, typename SignedIntegralType>
  typename std::enable_if<   (std::is_integral<SignedIntegralType>::value == true)
                          && (std::is_unsigned<SignedIntegralType>::value == false), decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>>::type operator*=(decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>& u, const SignedIntegralType& n)
  {
    return u.mul_signed_long_long(n);
  }

  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType, typename UnsignedIntegralType>
  typename std::enable_if<   (std::is_integral<UnsignedIntegralType>::value == true)
                          && (std::is_unsigned<UnsignedIntegralType>::value == true), decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>>::type operator*=(decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>& u, const UnsignedIntegralType& n)
  {
    return u.mul_unsigned_long_long(n);
  }

  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType, typename FloatingPointType>
  typename std::enable_if<(std::is_floating_point<FloatingPointType>::value == true), decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>>::type operator*=(decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>& u, const FloatingPointType& f)
  {
    return u *= decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>(f);
  }

  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType, typename SignedIntegralType>
  typename std::enable_if<   (std::is_integral<SignedIntegralType>::value == true)
                          && (std::is_unsigned<SignedIntegralType>::value == false), decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>>::type operator/=(decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>& u, const SignedIntegralType& n)
  {
    return u.div_signed_long_long(n);
  }

  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType, typename UnsignedIntegralType>
  typename std::enable_if<   (std::is_integral<UnsignedIntegralType>::value == true)
                          && (std::is_unsigned<UnsignedIntegralType>::value == true), decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>>::type operator/=(decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>& u, const UnsignedIntegralType& n)
  {
    return u.div_unsigned_long_long(n);
  }

  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType, typename FloatingPointType>
  typename std::enable_if<(std::is_floating_point<FloatingPointType>::value == true), decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>>::type operator/=(decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>& u, const FloatingPointType& f)
  {
    return u /= decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>(f);
  }

  // Global comparison operators of const decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>& with const decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>&.
  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType> bool operator< (const decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>& u, const decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>& v) { return (u.cmp(v) <  static_cast<std::int32_t>(0)); }
  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType> bool operator<=(const decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>& u, const decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>& v) { return (u.cmp(v) <= static_cast<std::int32_t>(0)); }
  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType> bool operator==(const decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>& u, const decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>& v) { return (u.cmp(v) == static_cast<std::int32_t>(0)); }
  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType> bool operator!=(const decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>& u, const decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>& v) { return (u.cmp(v) != static_cast<std::int32_t>(0)); }
  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType> bool operator>=(const decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>& u, const decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>& v) { return (u.cmp(v) >= static_cast<std::int32_t>(0)); }
  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType> bool operator> (const decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>& u, const decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>& v) { return (u.cmp(v) >  static_cast<std::int32_t>(0)); }

  // Global comparison operators of const decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>& with all built-in types.
  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ArithmeticType> typename std::enable_if<std::is_arithmetic<ArithmeticType>::value == true, bool>::type operator< (const decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>& u, const ArithmeticType& v) { return (u.cmp(decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>(v)) <  static_cast<std::int32_t>(0)); }
  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ArithmeticType> typename std::enable_if<std::is_arithmetic<ArithmeticType>::value == true, bool>::type operator<=(const decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>& u, const ArithmeticType& v) { return (u.cmp(decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>(v)) <= static_cast<std::int32_t>(0)); }
  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ArithmeticType> typename std::enable_if<std::is_arithmetic<ArithmeticType>::value == true, bool>::type operator==(const decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>& u, const ArithmeticType& v) { return (u.cmp(decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>(v)) == static_cast<std::int32_t>(0)); }
  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ArithmeticType> typename std::enable_if<std::is_arithmetic<ArithmeticType>::value == true, bool>::type operator!=(const decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>& u, const ArithmeticType& v) { return (u.cmp(decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>(v)) != static_cast<std::int32_t>(0)); }
  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ArithmeticType> typename std::enable_if<std::is_arithmetic<ArithmeticType>::value == true, bool>::type operator>=(const decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>& u, const ArithmeticType& v) { return (u.cmp(decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>(v)) >= static_cast<std::int32_t>(0)); }
  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ArithmeticType> typename std::enable_if<std::is_arithmetic<ArithmeticType>::value == true, bool>::type operator> (const decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>& u, const ArithmeticType& v) { return (u.cmp(decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>(v)) >  static_cast<std::int32_t>(0)); }

  // Global comparison operators of all built-in types with const decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>&.
  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ArithmeticType> typename std::enable_if<std::is_arithmetic<ArithmeticType>::value == true, bool>::type operator< (ArithmeticType u, const decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>& v) { return (decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>(u).cmp(v) <  static_cast<std::int32_t>(0)); }
  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ArithmeticType> typename std::enable_if<std::is_arithmetic<ArithmeticType>::value == true, bool>::type operator<=(ArithmeticType u, const decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>& v) { return (decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>(u).cmp(v) <= static_cast<std::int32_t>(0)); }
  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ArithmeticType> typename std::enable_if<std::is_arithmetic<ArithmeticType>::value == true, bool>::type operator==(ArithmeticType u, const decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>& v) { return (decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>(u).cmp(v) == static_cast<std::int32_t>(0)); }
  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ArithmeticType> typename std::enable_if<std::is_arithmetic<ArithmeticType>::value == true, bool>::type operator!=(ArithmeticType u, const decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>& v) { return (decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>(u).cmp(v) != static_cast<std::int32_t>(0)); }
  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ArithmeticType> typename std::enable_if<std::is_arithmetic<ArithmeticType>::value == true, bool>::type operator>=(ArithmeticType u, const decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>& v) { return (decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>(u).cmp(v) >= static_cast<std::int32_t>(0)); }
  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType, typename ArithmeticType> typename std::enable_if<std::is_arithmetic<ArithmeticType>::value == true, bool>::type operator> (ArithmeticType u, const decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>& v) { return (decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>(u).cmp(v) >  static_cast<std::int32_t>(0)); }

  } } // namespace math::wide_decimal

  // Specialization of std::numeric_limits<decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>>.
  namespace std
  {
    template <const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType> class numeric_limits<math::wide_decimal::decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>>
    {
    public:
      static constexpr bool                    is_specialized    = true;
      static constexpr bool                    is_signed         = true;
      static constexpr bool                    is_integer        = false;
      static constexpr bool                    is_exact          = false;
      static constexpr bool                    is_bounded        = true;
      static constexpr bool                    is_modulo         = false;
      static constexpr bool                    is_iec559         = false;
      static constexpr std::int64_t            digits            = math::wide_decimal::decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>::decwide_t_digits;       // Type differs from int.
      static constexpr std::int64_t            digits10          = math::wide_decimal::decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>::decwide_t_digits10;     // Type differs from int.
      static constexpr std::int64_t            max_digits10      = math::wide_decimal::decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>::decwide_t_max_digits10; // Type differs from int.
      static constexpr std::int64_t            min_exponent      = math::wide_decimal::decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>::decwide_t_min_exp;      // Type differs from int.
      static constexpr std::int64_t            min_exponent10    = math::wide_decimal::decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>::decwide_t_min_exp10;    // Type differs from int.
      static constexpr std::int64_t            max_exponent      = math::wide_decimal::decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>::decwide_t_max_exp;      // Type differs from int.
      static constexpr std::int64_t            max_exponent10    = math::wide_decimal::decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>::decwide_t_max_exp10;    // Type differs from int.
      static constexpr int                     radix             = math::wide_decimal::decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>::decwide_t_radix;
      static constexpr std::float_round_style  round_style       = std::round_to_nearest;
      static constexpr bool                    has_infinity      = true;
      static constexpr bool                    has_quiet_NaN     = true;
      static constexpr bool                    has_signaling_NaN = false;
      static constexpr std::float_denorm_style has_denorm        = std::denorm_absent;
      static constexpr bool                    has_denorm_loss   = false;
      static constexpr bool                    traps             = false;
      static constexpr bool                    tinyness_before   = false;

      static constexpr math::wide_decimal::decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType> (min)        () { return math::wide_decimal::decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>::my_value_min(); }
      static constexpr math::wide_decimal::decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType> (max)        () { return math::wide_decimal::decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>::my_value_max(); }
      static constexpr math::wide_decimal::decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType> lowest       () { return math::wide_decimal::zero<MyDigits10, LimbType, AllocatorType, InternalFloatType>(); }
      static constexpr math::wide_decimal::decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType> epsilon      () { return math::wide_decimal::decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>::my_value_eps(); }
      static constexpr math::wide_decimal::decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType> round_error  () { return math::wide_decimal::half<MyDigits10, LimbType, AllocatorType, InternalFloatType>(); }
      static constexpr math::wide_decimal::decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType> infinity     () { return math::wide_decimal::decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>::my_value_inf(); }
      static constexpr math::wide_decimal::decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType> quiet_NaN    () { return math::wide_decimal::decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>::my_value_nan(); }
      static constexpr math::wide_decimal::decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType> signaling_NaN() { return math::wide_decimal::zero<MyDigits10, LimbType, AllocatorType, InternalFloatType>(); }
      static constexpr math::wide_decimal::decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType> denorm_min   () { return math::wide_decimal::zero<MyDigits10, LimbType, AllocatorType, InternalFloatType>(); }
    };
  } // namespace std

  namespace math { namespace wide_decimal {

  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType> const decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType> constexpr unsigned_long_long_max() { return decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>((std::numeric_limits<unsigned long long>::max)()); }
  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType> const decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType> constexpr signed_long_long_min  () { return decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>((std::numeric_limits<signed long long>::min)()); }
  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType> const decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType> constexpr signed_long_long_max  () { return decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>((std::numeric_limits<signed long long>::max)()); }
  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType> const decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType> constexpr long_double_min       () { return decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>((std::numeric_limits<long double>::min)());}
  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType> const decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType> constexpr long_double_max       () { return decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>((std::numeric_limits<long double>::max)());}

  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType> bool (isnan)   (decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType> x) { return (x.isnan)(); }
  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType> bool (isfinite)(decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType> x) { return (x.isfinite)(); }
  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType> bool (isinf)   (decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType> x) { return (x.isinf)(); }

  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType>
  decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType> pow(decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType> x,
                                                                        decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType> a)
  {
    return exp(a * log(x));
  }

  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType> decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType> ldexp(decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType> v, int e)
  {
    decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType> ldexp_result = v;

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
      ldexp_result *= pow(two<MyDigits10, LimbType, AllocatorType, InternalFloatType>(), e);
    }

    return ldexp_result;
  }

  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType> decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType> frexp(decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType> v, int* expon)
  {
    double       d;
    std::int64_t i;

    v.extract_parts(d, i);

    *expon = static_cast<int>(i);

    return v * ldexp(one<MyDigits10, LimbType, AllocatorType, InternalFloatType>(), (int) -i);
  }

  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType> decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType> fmod(decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType> v1, decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType> v2)
  {
    const decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType> n = ((v1 < 0) ? ceil(v1 / v2) : floor(v1 / v2));

    return v1 - (n * v2);
  }

  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType> decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType> sqrt(decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType> x)
  {
    return x.calculate_sqrt();
  }

  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType> decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType> cbrt(decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType> x)
  {
    return rootn(x, static_cast<std::int32_t>(3));
  }

  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType> decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType> rootn(decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType> x, std::int32_t p)
  {
    decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType> rtn;

    if((isfinite)(x) == false)
    {
      rtn = std::numeric_limits<decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>>::quiet_NaN();
    }
    else if(p < static_cast<std::int32_t>(0))
    {
      rtn = rootn(one<MyDigits10, LimbType, AllocatorType, InternalFloatType>() / x, static_cast<std::int32_t>(-p));
    }
    else if((p == static_cast<std::int32_t>(0)) || ((x < 0) && (p != static_cast<std::int32_t>(3))))
    {
      rtn = std::numeric_limits<decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>>::quiet_NaN();
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

  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType> decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType> log(decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType> x)
  {
    using floating_point_type = decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>;

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
    //               = Log[mantissa] + ib * Log[radix]

    InternalFloatType mantissa;
    std::int64_t      ib;

    xx.extract_parts(mantissa, ib);

    using std::log;

    const float lg_xx =   log((float) mantissa)
                        + ((float) ib * log((float) std::numeric_limits<floating_point_type>::radix));

    const float lg_xx_over_lg2 = lg_xx / log(2.0F);

    // Ensure that the resulting power is non-negative.
    // Also enforce that m >= 3.
    const std::int32_t m = (std::max)((std::int32_t) (n_times_factor - lg_xx_over_lg2), (std::int32_t) 3);

    floating_point_type bk =
      ldexp(one<MyDigits10, LimbType, AllocatorType, InternalFloatType>(), (std::int32_t) (2 - m)) / xx;

    // TBD: Tolerance should have the log of the argument added to it (usually negligible).
    const std::uint32_t digits10_iteration_goal =
        (std::uint32_t) (std::numeric_limits<floating_point_type>::digits10 / 2)
      + (std::max)((std::uint32_t) (floating_point_type::decwide_t_elem_digits10 + 1), (std::uint32_t) 9U);

    using std::log;

    const std::uint32_t digits10_scale =
      (std::uint32_t) (0.5F + (1000.0F * log((float) std::numeric_limits<floating_point_type>::radix)) / log(10.0F));

    for(std::int32_t k = static_cast<std::int32_t>(0); k < static_cast<std::int32_t>(64); ++k)
    {
      using std::ilogb;
      using std::sqrt;

      // Check for the number of significant digits to be
      // at least half of the requested digits. If at least
      // half of the requested digits have been achieved,
      // then break after the upcoming iteration.

      const std::int32_t ilogb_of_ak_minus_bk = (std::max)(std::int32_t(0), -ilogb(ak - bk));

      const std::uint32_t digits10_of_iteration =
        (std::uint32_t) ((std::uint64_t) ((std::uint64_t) ilogb_of_ak_minus_bk * digits10_scale) / 1000U);

      const floating_point_type ak_tmp(ak);

      ak += bk;
      ak /= 2;

      if(digits10_of_iteration > digits10_iteration_goal)
      {
        break;
      }

      bk *= ak_tmp;
      bk  = sqrt(bk);
    }

    // We are now finished with the AGM iteration for log(x).
    // Compute log(x) = {pi / [2 * AGM(1, 4 / 2^m)]} - (m * ln2)
    // Note at this time that (ak = bk) = AGM(...)
    // Retrieve the value of pi, divide by (2 * a) and subtract (m * ln2).

    const floating_point_type result =
             pi<MyDigits10, LimbType, AllocatorType, InternalFloatType>() / (ak * 2)
      - (ln_two<MyDigits10, LimbType, AllocatorType, InternalFloatType>() * m);

    return ((b_negate == true) ? -result : result);
  }

  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType> decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType> exp(decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType> x)
  {
    using floating_point_type = decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>;

    floating_point_type exp_result;

    using std::isfinite;
    using math::wide_decimal::isfinite;

    if((isfinite)(x) == false)
    {
      exp_result = x;
    }
    else if(x == 0)
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
      const floating_point_type ln2 = ln_two<MyDigits10, LimbType, AllocatorType, InternalFloatType>();

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

      const floating_point_type exp_series = pow(h0f0, p2) * ldexp(floating_point_type(1U), nf);

      exp_result = ((b_neg == false) ? exp_series : 1 / exp_series);
    }

    return exp_result;
  }

  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType> decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType> pow(decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType> b, const std::int64_t p)
  {
    // Calculate (b ^ p).

    using floating_point_type = decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>;

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

  bool example001_roots_sqrt             ();
  bool example001a_roots_seventh         ();
  bool example001b_roots_almost_integer  ();
  bool example002_pi                     ();
  bool example002a_pi_small_limb         ();
  bool example002b_pi_100k               ();
  bool example002c_pi_quintic            ();
  bool example003_zeta                   ();
  bool example004_bessel_recur           ();
  bool example005_polylog_series         ();
  bool example006_logarithm              ();
  bool example007_catalan_series         ();
  bool example008_bernoulli_tgamma       ();
  bool example009_boost_math_standalone  ();
  bool example010_hypergeometric_2f1     ();
  bool example010a_hypergeometric_1f1    ();
  bool example011_trig_trapezoid_integral();

  } } // namespace math::wide_decimal

#endif // DECWIDE_T_2004_06_01_H_
