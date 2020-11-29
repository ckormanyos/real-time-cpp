///////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 1999 - 2020.                 //
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
  //#define WIDE_DECIMAL_DISABLE_CONVERSION_TO_BUILTINS
  //#define WIDE_DECIMAL_DISABLE_CONSTRUCT_FROM_BUILTIN_FLOAT
  //#define WIDE_DECIMAL_DISABLE_CONSTRUCT_FROM_STRING

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
  #if !defined(WIDE_DECIMAL_DISABLE_CONVERSION_TO_BUILTINS)
  #include <sstream>
  #endif
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

  // TBD: Ensure that the type of MySize (which is std::size_t)
  // can actually handle a full 32-bit width size.
  // This is because size_t might be, for instance,
  // only 16 bits on an 8 bit platform.

  template <typename MyType,
            const std::size_t MySize,
            typename MyAlloc>
  class dynamic_array final : public util::dynamic_array<MyType, MyAlloc>
  {
  private:
    using base_class_type = util::dynamic_array<MyType, MyAlloc>;

  public:
    constexpr dynamic_array()
      : base_class_type(MySize) { }

    constexpr dynamic_array(const typename base_class_type::size_type my_size)
      : base_class_type(my_size) { }

    constexpr dynamic_array(const typename base_class_type::size_type   my_size,
                            const typename base_class_type::value_type& my_value)
      : base_class_type(my_size, my_value) { }

    constexpr dynamic_array(const typename base_class_type::size_type       my_size,
                            const typename base_class_type::value_type&     my_value,
                            const typename base_class_type::allocator_type& my_alloc)
      : base_class_type(my_size, my_value, my_alloc) { }

    dynamic_array(const dynamic_array& other_array)
      : base_class_type(static_cast<const base_class_type&>(other_array)) { }

    dynamic_array(std::initializer_list<typename base_class_type::value_type> lst)
      : base_class_type(MySize)
    {
      base_class_type::fill(typename base_class_type::value_type(0U));

      std::copy(lst.begin(),
                lst.begin() + (std::min)((typename base_class_type::size_type) lst.size(),
                                         (typename base_class_type::size_type) MySize),
                base_class_type::begin());
    }

    dynamic_array(dynamic_array&& other_array)
      : base_class_type(static_cast<base_class_type&&>(other_array)) { }

    dynamic_array& operator=(const dynamic_array& other_array)
    {
      base_class_type::operator=(static_cast<const base_class_type&>(other_array));

      return *this;
    }

    dynamic_array& operator=(dynamic_array&& other_array)
    {
      base_class_type::operator=(static_cast<base_class_type&&>(other_array));

      return *this;
    }

    virtual ~dynamic_array() = default;

    static constexpr typename base_class_type::size_type static_size() { return MySize; }

    typename base_class_type::pointer       data()       { return &(*this->begin()); }
    typename base_class_type::const_pointer data() const { return &(*this->cbegin()); }
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
  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType> decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType> zero();
  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType> decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType> one ();
  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType> decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType> two ();
  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType> decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType> half();
  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType> decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType> pi  (void(*pfn_callback_to_report_digits10)(const std::uint32_t) = nullptr);

  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType> const decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType> unsigned_long_long_max();
  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType> const decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType> signed_long_long_min  ();
  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType> const decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType> signed_long_long_max  ();
  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType> const decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType> double_min            ();
  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType> const decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType> double_max            ();
  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType> const decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType> long_double_min       ();
  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType> const decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType> long_double_max       ();

  #if !defined(WIDE_DECIMAL_DISABLE_CONSTRUCT_FROM_BUILTIN_FLOAT)
  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType> decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType> pow2(const std::int64_t p);
  #endif // !WIDE_DECIMAL_DISABLE_CONSTRUCT_FROM_BUILTIN_FLOAT

  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType> std::int32_t max_iteration();
  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType> std::int64_t tolerance    ();

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
    static constexpr std::int32_t decwide_t_elems_for_fft     = 64;

    // Obtain the decwide_t digits characteristics from a helper meta-template.

    static constexpr std::int32_t decwide_t_digits10          = detail::decwide_t_helper<MyDigits10, LimbType>::digits10;
    static constexpr std::int32_t decwide_t_digits            = detail::decwide_t_helper<MyDigits10, LimbType>::digits;
    static constexpr std::int32_t decwide_t_max_digits10      = detail::decwide_t_helper<MyDigits10, LimbType>::max_digits10;
    static constexpr std::int32_t decwide_t_radix             = detail::decwide_t_helper<MyDigits10, LimbType>::radix;

    static constexpr std::int32_t decwide_t_elem_digits10     = detail::decwide_t_helper<MyDigits10, LimbType>::elem_digits10;
    static constexpr std::int32_t decwide_t_elem_number       = detail::decwide_t_helper<MyDigits10, LimbType>::elem_number;
    static constexpr std::int32_t decwide_t_elem_mask         = detail::decwide_t_helper<MyDigits10, LimbType>::elem_mask;
    static constexpr std::int32_t decwide_t_elem_mask_half    = detail::decwide_t_helper<MyDigits10, LimbType>::elem_mask_half;

    static constexpr std::int64_t decwide_t_max_exp10         =  static_cast<std::int64_t>(INT64_C(0x7FFFFFFFFFFFFFFF) / decwide_t_elem_digits10) * decwide_t_elem_digits10;
    static constexpr std::int64_t decwide_t_min_exp10         = -static_cast<std::int64_t>(decwide_t_max_exp10);
    static constexpr std::int64_t decwide_t_max_exp           = decwide_t_max_exp10;
    static constexpr std::int64_t decwide_t_min_exp           = decwide_t_min_exp10;

    // Rebind the specific allocator to the granularity of LimbType.
    using allocator_type = typename AllocatorType::template rebind<LimbType>::other;

    // Here array_type is the internal representation of the data field of a decwide_t.
    using array_type = detail::dynamic_array<typename allocator_type::value_type,
                                             static_cast<std::size_t>(decwide_t_elem_number),
                                             allocator_type>;

    // Obtain the limb_type and the double_limb_type from templates.
    using limb_type        = typename array_type::value_type;
    using double_limb_type = typename std::conditional<(std::is_same<limb_type, std::uint32_t>::value == true),
                                                        std::uint64_t,
                                                        std::uint32_t>::type;
    using signed_limb_type = typename std::conditional<(std::is_same<limb_type, std::uint32_t>::value == true),
                                                        std::int32_t,
                                                        std::int16_t>::type;

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
    #if !defined(WIDE_DECIMAL_DISABLE_CONSTRUCT_FROM_BUILTIN_FLOAT)
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
    #endif // !WIDE_DECIMAL_DISABLE_CONSTRUCT_FROM_BUILTIN_FLOAT

  public:
    // Default constructor.
    decwide_t() : my_data     (),
                  my_exp      (static_cast<std::int64_t>(0)),
                  my_neg      (false),
                  my_fpclass  (decwide_t_finite),
                  my_prec_elem(decwide_t_elem_number) { }

    // Constructors from built-in unsigned integral types.
    template<typename UnsignedIntegralType,
             typename std::enable_if<(   (std::is_integral<UnsignedIntegralType>::value == true)
                                      && (std::is_unsigned<UnsignedIntegralType>::value == true)
                                      && (std::numeric_limits<UnsignedIntegralType>::digits <= std::numeric_limits<limb_type>::digits))>::type const* = nullptr>
    decwide_t(const UnsignedIntegralType u) : my_data     (decwide_t_elem_number, 0U),
                                              my_exp      (static_cast<std::int64_t>(0)),
                                              my_neg      (false),
                                              my_fpclass  (decwide_t_finite),
                                              my_prec_elem(decwide_t_elem_number)
    {
      my_data[0U] = u;
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

    #if !defined(WIDE_DECIMAL_DISABLE_CONSTRUCT_FROM_BUILTIN_FLOAT)
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
    #endif //!(WIDE_DECIMAL_DISABLE_CONSTRUCT_FROM_BUILTIN_FLOAT)

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
    decwide_t(const decwide_t& f) : my_data     (f.my_data),
                                    my_exp      (f.my_exp),
                                    my_neg      (f.my_neg),
                                    my_fpclass  (f.my_fpclass),
                                    my_prec_elem(f.my_prec_elem) { }

    // Move constructor.
    decwide_t(decwide_t&& f) : my_data     (static_cast<array_type&&>(f.my_data)),
                               my_exp      (f.my_exp),
                               my_neg      (f.my_neg),
                               my_fpclass  (f.my_fpclass),
                               my_prec_elem(f.my_prec_elem) { }

    // Constructor from floating-point class.
    explicit decwide_t(const fpclass_type fpc) : my_data     (),
                                                 my_exp      (static_cast<std::int64_t>(0)),
                                                 my_neg      (false),
                                                 my_fpclass  (fpc),
                                                 my_prec_elem(decwide_t_elem_number) { }

    // Constructor from initializer list of limbs,
    // exponent value (normed to limb granularity) 
    // and optional sign flag.
    decwide_t(std::initializer_list<limb_type> limb_values,
            const std::int64_t e = 0,
            const bool is_neg = false) : my_data     (limb_values),
                                         my_exp      (e),
                                         my_neg      (is_neg),
                                         my_fpclass  (decwide_t_finite),
                                         my_prec_elem(decwide_t_elem_number) { }

  private:
    // Constructor from mantissa and exponent.
    decwide_t(const InternalFloatType mantissa,
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
    decwide_t& operator=(const decwide_t& v)
    {
      if(this != &v)
      {
        my_data      = v.my_data;
        my_exp       = v.my_exp;
        my_neg       = v.my_neg;
        my_fpclass   = v.my_fpclass;
        my_prec_elem = v.my_prec_elem;
      }

      return *this;
    }

    // Move assignment operator.
    decwide_t& operator=(decwide_t&& other)
    {
      my_data      = static_cast<array_type&&>(other.my_data);
      my_exp       = other.my_exp;
      my_neg       = other.my_neg;
      my_fpclass   = other.my_fpclass;
      my_prec_elem = other.my_prec_elem;

      return *this;
    }

          array_type&  representation()       { return my_data; }
    const array_type&  representation() const { return my_data; }
    const array_type& crepresentation() const { return my_data; }

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

    // Fast order-10 range check.
    std::int64_t order() const { return get_order_fast(); }

    static decwide_t my_fabs(const decwide_t& x) { return (x.isneg() ? decwide_t(x).negate() : x); }

    std::int32_t cmp(const decwide_t& v) const
    {
      // Compare v with *this.
      //         Return +1 for *this > v
      //                 0 for *this = v
      //                -1 for *this < v

      // Handle all non-finite cases.
      if((!isfinite()) || (!v.isfinite()))
      {
        // NaN can never equal NaN. Return an implementation-dependent
        // signed result. Also note that comparison of NaN with NaN
        // using operators greater-than or less-than is undefined.
        if(isnan() || v.isnan())
        {
          return (isnan() ? static_cast<std::int32_t>(1) : static_cast<std::int32_t>(-1));
        }

        if(isinf() && v.isinf())
        {
          // Both *this and v are infinite. They are equal if they have the same sign.
          // Otherwise, *this is less than v if and only if *this is negative.
          return ((my_neg == v.my_neg)
                   ? static_cast<std::int32_t>(0)
                   : (my_neg ? static_cast<std::int32_t>(-1) : static_cast<std::int32_t>(1)));
        }

        if(isinf())
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
    static decwide_t my_value_inf() { return decwide_t(decwide_t_inf); }
    static decwide_t my_value_nan() { return decwide_t(decwide_t_NaN); }
    static decwide_t my_value_max() { return decwide_t( { limb_type(9U) }, decwide_t_max_exp10 ); }
    static decwide_t my_value_min() { return decwide_t( { limb_type(1U) }, decwide_t_min_exp10 ); }
    static decwide_t my_value_eps()
    {
      constexpr std::int32_t decwide_t_digits10_aligned =
        -static_cast<std::int32_t>(((decwide_t_digits10 / decwide_t_elem_digits10) + ((decwide_t_digits10 % decwide_t_elem_digits10) != 0 ? 1 : 0)) * decwide_t_elem_digits10);

      return decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>
      (
        {
          limb_type(detail::decwide_t_helper<MyDigits10, LimbType>::pow10_maker(static_cast<std::uint32_t>(static_cast<std::int32_t>(-decwide_t_digits10_aligned + 1) - decwide_t_digits10)))
        },
        static_cast<std::int64_t>(decwide_t_digits10_aligned)
      );
    }

    void precision(const std::int32_t prec_digits)
    {
      if(prec_digits >= decwide_t_digits10)
      {
        my_prec_elem = decwide_t_elem_number;
      }
      else
      {
        const std::int32_t elems =
          static_cast<std::int32_t>(    static_cast<std::int32_t>(prec_digits / decwide_t_elem_digits10)
                                    +                          (((prec_digits % decwide_t_elem_digits10) != 0) ? 1 : 0));

        my_prec_elem = (std::min)(decwide_t_elem_number, (std::max)(elems, static_cast<std::int32_t>(2)));
      }
    }

    // Binary arithmetic operators.
    decwide_t& operator+=(const decwide_t& v)
    {
      // TBD: Eliminate the temporary storage array my_n_data_for_add_sub.

      // TBD: Limit the length of add/sub to only those ranges needed,
      // whereby propagate borrow/carry may be necessary as well.

      if(isnan())
      {
        return *this;
      }

      if(isinf())
      {
        if(v.isinf() && (isneg() != v.isneg()))
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

      typename array_type::iterator       p_u    =   my_data.begin();
      typename array_type::const_iterator p_v    = v.my_data.cbegin();
      bool                                b_copy = false;
      const std::int32_t                  ofs    = static_cast<std::int32_t>(static_cast<std::int32_t>(ofs_exp) / decwide_t_elem_digits10);

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

          p_v = my_n_data_for_add_sub.begin();
        }
        else
        {
          std::copy(my_data.cbegin(),
                    my_data.cend()     - static_cast<std::ptrdiff_t>(-ofs),
                    my_n_data_for_add_sub.begin() + static_cast<std::ptrdiff_t>(-ofs));

          std::fill(my_n_data_for_add_sub.begin(),
                    my_n_data_for_add_sub.begin() + static_cast<std::ptrdiff_t>(-ofs),
                    static_cast<limb_type>(0));

          p_u = my_n_data_for_add_sub.begin();
          b_copy = true;
        }

        // Addition.
        const limb_type carry = add_loop_uv(p_u, p_v, decwide_t_elem_number);

        if(b_copy)
        {
          my_data = my_n_data_for_add_sub;
          my_exp  = v.my_exp;
        }
    
        // There needs to be a carry into the element -1 of the array data
        if(carry != static_cast<limb_type>(0U))
        {
          std::copy_backward(my_data.cbegin(),
                             my_data.cend() - static_cast<std::size_t>(1U),
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

          p_v = my_n_data_for_add_sub.begin();
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
          my_n_data_for_add_sub = v.my_data;
          p_u    = my_n_data_for_add_sub.begin();
          p_v    = my_data.begin();
          b_copy = true;
        }

        // Subtraction.
        const signed_limb_type borrow = sub_loop_uv(p_u, p_v, decwide_t_elem_number);

        static_cast<void>(borrow);

        if(b_copy)
        {
          my_data = my_n_data_for_add_sub;
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
        return (*this = zero<MyDigits10, LimbType, AllocatorType, InternalFloatType>());
      }

      // Check for overflow or underflow.
      const bool u_exp_is_neg = (  my_exp < static_cast<std::int64_t>(0));
      const bool v_exp_is_neg = (v.my_exp < static_cast<std::int64_t>(0));

      if(u_exp_is_neg == v_exp_is_neg)
      {
        // Get the unsigned base-10 exponents of *this and v and...
        const std::int64_t u_exp = ((!u_exp_is_neg) ?   my_exp : static_cast<std::int64_t>(  -my_exp));
        const std::int64_t v_exp = ((!v_exp_is_neg) ? v.my_exp : static_cast<std::int64_t>(-v.my_exp));

        // Check the range of the upcoming multiplication.
        const bool b_result_is_out_of_range = (v_exp >= static_cast<std::int64_t>(decwide_t_max_exp10 - u_exp));

        if(b_result_is_out_of_range)
        {
          if(u_exp_is_neg)
          {
            *this = zero<MyDigits10, LimbType, AllocatorType, InternalFloatType>();
          }
          else
          {
            *this = ((!b_result_is_neg) ?  my_value_inf() : -my_value_inf());
          }

          return *this;
        }
      }

      // Set the exponent of the result.
      my_exp += v.my_exp;

      const std::int32_t prec_elems_for_multiply = (std::min)(my_prec_elem, v.my_prec_elem);

      eval_mul_dispatch_multiplication_method<decwide_t_elem_number>(v, prec_elems_for_multiply);

      // Set the sign of the result.
      my_neg = b_result_is_neg;

      return *this;
    }

    decwide_t& operator/=(const decwide_t& v)
    {
      const bool u_and_v_are_finite_and_identical =
        (    isfinite()
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

        return *this;
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
      const bool b_u_is_inf  = isinf();
      const bool b_n_is_zero = (n == static_cast<std::int32_t>(0));

      if(isnan() || (b_u_is_inf && b_n_is_zero))
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
      if(isnan())
      {
        return *this;
      }

      if(isinf())
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

      if(isnan())
      {
        return *this;
      }

      if(isinf())
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

      for(std::int32_t digits = (std::int32_t) (std::numeric_limits<InternalFloatType>::digits10 - 1); digits < decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>::decwide_t_max_digits10; digits *= static_cast<std::int32_t>(2))
      {
        // Adjust precision of the terms.
        const std::int32_t new_prec_as_digits10 =
                       static_cast<std::int32_t>(digits * 2)
          + (std::max)(static_cast<std::int32_t>(decwide_t_elem_digits10 * 2), static_cast<std::int32_t>(16));

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

      if(isneg() || (!isfinite()))
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

      for(std::int32_t digits = (std::int32_t) (std::numeric_limits<InternalFloatType>::digits10 - 1); digits < decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>::decwide_t_max_digits10; digits *= static_cast<std::int32_t>(2))
      {
        // Adjust precision of the terms.
        const std::int32_t new_prec_as_digits10 =
                       static_cast<std::int32_t>(digits * 2)
          + (std::max)(static_cast<std::int32_t>(decwide_t_elem_digits10 * 2), static_cast<std::int32_t>(16));

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
      if(!iszero())
      {
        my_neg = (!my_neg);
      }

      return *this;
    }

    // Comparison functions.
    bool isnan   () const { return (my_fpclass == decwide_t_NaN); }
    bool isinf   () const { return (my_fpclass == decwide_t_inf); }
    bool isfinite() const { return (my_fpclass == decwide_t_finite); }

    bool iszero() const
    {
      return ((my_fpclass == decwide_t_finite) && (my_data[0U] == static_cast<limb_type>(0U)));
    }

    bool isone() const
    {
      // Check if the value of *this is identically 1 or very close to 1.

      const bool not_negative_and_is_finite = ((!my_neg) && isfinite());

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

      if(isfinite() == false)
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

    #if !defined(WIDE_DECIMAL_DISABLE_CONVERSION_TO_BUILTINS)
    double extract_double() const
    {
      // Returns the double conversion of a decwide_t.

      // Check for non-normal decwide_t.
      if((!isfinite()))
      {
        if(isnan())
        {
          return std::numeric_limits<double>::quiet_NaN();
        }
        else
        {
          return ((!my_neg) ?  std::numeric_limits<double>::infinity()
                            : -std::numeric_limits<double>::infinity());
        }
      }

      const decwide_t xx(my_fabs(*this));

      // Check for zero decwide_t.
      if(iszero() || (xx < math::wide_decimal::double_min<MyDigits10, LimbType, AllocatorType, InternalFloatType>()))
      {
        return 0.0;
      }

      // Check if decwide_t exceeds the maximum of double.
      if(xx > math::wide_decimal::double_max<MyDigits10, LimbType, AllocatorType, InternalFloatType>())
      {
        return ((!my_neg) ?  std::numeric_limits<double>::infinity()
                          : -std::numeric_limits<double>::infinity());
      }

      std::stringstream ss;

      ss << std::setprecision(static_cast<std::streamsize>(std::numeric_limits<double>::digits10 + (2 + 1)))
         << std::scientific
         << *this;

      double d;

      ss >> d;

      return d;
    }

    long double extract_long_double() const
    {
      // Returns the long double conversion of a decwide_t.

      // Check for non-normal decwide_t.
      if((!isfinite()))
      {
        if(isnan())
        {
          return std::numeric_limits<long double>::quiet_NaN();
        }
        else
        {
          return ((!my_neg) ?  std::numeric_limits<long double>::infinity()
                            : -std::numeric_limits<long double>::infinity());
        }
      }

      const decwide_t xx(my_fabs(*this));

      // Check for zero decwide_t.
      if(iszero() || (xx < math::wide_decimal::long_double_min<MyDigits10, LimbType, AllocatorType, InternalFloatType>()))
      {
        return 0.0L;
      }

      // Check if decwide_t exceeds the maximum of double.
      if(xx > math::wide_decimal::long_double_max<MyDigits10, LimbType, AllocatorType, InternalFloatType>())
      {
        return ((!my_neg) ?  std::numeric_limits<long double>::infinity()
                          : -std::numeric_limits<long double>::infinity());
      }

      std::stringstream ss;

      ss << std::setprecision(static_cast<std::streamsize>(std::numeric_limits<long double>::digits10 + (2 + 1)))
         << std::scientific
         << *this;

      long double ld;

      ss >> ld;

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

      if((!b_neg) && (*this > math::wide_decimal::signed_long_long_max<MyDigits10, LimbType, AllocatorType, InternalFloatType>()))
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
        const decwide_t xn(my_fabs(extract_integer_part()));

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

      if(xn > math::wide_decimal::unsigned_long_long_max<MyDigits10, LimbType, AllocatorType, InternalFloatType>())
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

    explicit operator long double() const
    {
      return extract_long_double();
    }

    explicit operator double() const
    {
      return extract_double();
    }

    explicit operator float() const
    {
      return (float) extract_double();
    }

    explicit operator signed long long() const
    {
      return extract_signed_long_long();
    }

    explicit operator unsigned long long() const
    {
      return extract_unsigned_long_long();
    }

    explicit operator signed int() const
    {
      return (int) extract_signed_long_long();
    }

    explicit operator unsigned int() const
    {
      return (unsigned int) extract_unsigned_long_long();
    }

    #endif // !WIDE_DECIMAL_DISABLE_CONVERSION_TO_BUILTINS

  private:
    static InternalFloatType my_af_bf_fft_mul_pool[detail::decwide_t_helper<MyDigits10, LimbType>::pow2_maker_of_upper_limit(decwide_t_elem_number) * 8UL];
    static array_type        my_n_data_for_add_sub;

    array_type   my_data;
    std::int64_t my_exp;
    bool         my_neg;
    fpclass_type my_fpclass;
    std::int32_t my_prec_elem;

    void from_unsigned_long_long(const unsigned long long u)
    {
      std::fill(my_data.begin(), my_data.end(), static_cast<limb_type>(0U));

      my_exp = static_cast<std::int64_t>(0);

      std::size_t i =static_cast<std::size_t>(0U);

      unsigned long long uu = u;

      limb_type temp[std::size_t(std::numeric_limits<unsigned long long>::digits10 / static_cast<int>(decwide_t_elem_digits10)) + 3U] = { static_cast<limb_type>(0U) };

      while(uu != static_cast<unsigned long long>(0U))
      {
        temp[i] = static_cast<limb_type>(uu % static_cast<unsigned long long>(decwide_t_elem_mask));

        uu = static_cast<unsigned long long>(uu / static_cast<unsigned long long>(decwide_t_elem_mask));

        ++i;
      }

      if(i > static_cast<std::size_t>(1U))
      {
        my_exp += static_cast<std::int64_t>((i - 1U) * static_cast<std::size_t>(decwide_t_elem_digits10));
      }

      std::reverse(temp, temp + i);

      std::copy(temp, temp + (std::min)(i, static_cast<std::size_t>(decwide_t_elem_number)), my_data.begin());
    }

    #if !defined(WIDE_DECIMAL_DISABLE_CONSTRUCT_FROM_BUILTIN_FLOAT)
    void from_long_double(const long double l)
    {
      const bool b_neg = (l < static_cast<long double>(0.0L));

      using std::isfinite;
      using std::isnan;

      if(!isfinite(static_cast<double>(l)))
      {
        operator=(isnan(static_cast<double>(l)) ? my_value_nan() : ((!b_neg) ? my_value_inf() : -my_value_inf()));

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
        operator*=(pow2<MyDigits10, LimbType, AllocatorType, InternalFloatType>(static_cast<std::int64_t>(p2)));
      }

      my_neg = b_neg;
    }
    #endif // !WIDE_DECIMAL_DISABLE_CONSTRUCT_FROM_BUILTIN_FLOAT

    std::int32_t cmp_data(const array_type& vd) const
    {
      // Compare the data of *this with those of v.
      //         Return +1 for *this > v
      //                 0 for *this = v
      //                -1 for *this < v

      const std::pair<typename array_type::const_iterator,
                      typename array_type::const_iterator> mismatch_pair =
        std::mismatch(my_data.cbegin(), my_data.cend(), vd.cbegin());

      const bool is_equal = (   (mismatch_pair.first  == my_data.cend())
                             && (mismatch_pair.second == vd.cend()));

      if(is_equal)
      {
        return static_cast<std::int32_t>(0);
      }
      else
      {
        return ((*mismatch_pair.first > *mismatch_pair.second) ? static_cast<std::int32_t>(1) : static_cast<std::int32_t>(-1));
      }
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

    static void mul_loop_karatsuba(limb_type* const u, const limb_type* const v, const std::int32_t p)
    {
    }

    static void mul_loop_fft(limb_type* const u, const limb_type* const v, const std::int32_t p)
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
        std::uint32_t p_fft = (std::uint32_t) ((p * 2L) * 2L);

        // Use O(log2[N]) binary-halving in an unrolled loop to find the msb.
        if((p_fft & UINT32_C(0xFFFF0000)) != UINT32_C(0)) { p_fft >>= 16U; n_fft |= UINT8_C(16); }
        if((p_fft & UINT32_C(0x0000FF00)) != UINT32_C(0)) { p_fft >>=  8U; n_fft |= UINT8_C( 8); }
        if((p_fft & UINT32_C(0x000000F0)) != UINT32_C(0)) { p_fft >>=  4U; n_fft |= UINT8_C( 4); }
        if((p_fft & UINT32_C(0x0000000C)) != UINT32_C(0)) { p_fft >>=  2U; n_fft |= UINT8_C( 2); }
        if((p_fft & UINT32_C(0x00000002)) != UINT32_C(0)) { p_fft >>=  1U; n_fft |= UINT8_C( 1); }

        // We now obtain the needed FFT size doubled (and doubled again),
        // with the added condition of needing to be a power of 2.
        n_fft = (std::uint32_t) (1UL << n_fft);

        if(n_fft < (std::uint32_t) ((p * 2L) * 2L))
        {
          n_fft <<= 1U;
        }
      }

      // We now have the needed FFT size doubled (and doubled again).

      // Use pre-allocated static memory for the FFT result arrays.
      // This was previously given by:
      //   InternalFloatType* af_bf = new InternalFloatType[n_fft * 2U];

      InternalFloatType* af = my_af_bf_fft_mul_pool + (0U * n_fft);
      InternalFloatType* bf = my_af_bf_fft_mul_pool + (1U * n_fft);

      for(std::uint32_t i = static_cast<std::uint32_t>(0U); i < static_cast<std::uint32_t>(p); ++i)
      {
        af[(i * 2U)]      = InternalFloatType(u[i] / decwide_t_elem_mask_half);
        af[(i * 2U) + 1U] = InternalFloatType(u[i] % decwide_t_elem_mask_half);

        bf[(i * 2U)]      = InternalFloatType(v[i] / decwide_t_elem_mask_half);
        bf[(i * 2U) + 1U] = InternalFloatType(v[i] % decwide_t_elem_mask_half);
      }

      std::fill(af + (p * 2), af + n_fft, InternalFloatType(0));
      std::fill(bf + (p * 2), bf + n_fft, InternalFloatType(0));

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

      for(std::uint32_t j = static_cast<std::uint32_t>((p * 2L) - 2L); static_cast<std::int32_t>(j) >= 0; j -= 2U)
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

      // De-allocate the dynamic memory for the FFT result arrays.
      // This was previously given by:
      //   delete [] af_bf;
    }

    template<const std::int32_t ElemsForFftThreshold>
    void eval_mul_dispatch_multiplication_method(const decwide_t& v,
                                                 const std::int32_t p,
                                                 const std::int32_t = ElemsForFftThreshold,
                                                 const typename std::enable_if<(decwide_t_elems_for_fft >= ElemsForFftThreshold)>::type* = nullptr)
    {
      // Use school multiplication.
      const limb_type carry = mul_loop_uv(my_data.data(), v.my_data.data(), p);

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
                                                 const std::int32_t p,
                                                 const std::int32_t = ElemsForFftThreshold,
                                                 const typename std::enable_if<(ElemsForFftThreshold > decwide_t_elems_for_fft)>::type* = nullptr)
    {
      // Note: Karatsuba multiplication is not used for intermediate digit counts.
      // TBD: Implement Karatsuba multiplication for intermediate digit counts.

      if(p < decwide_t_elems_for_fft)
      {
        // Use school multiplication.
        const limb_type carry = mul_loop_uv(my_data.data(), v.my_data.data(), p);

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
        mul_loop_fft(my_data.data(), v.my_data.data(), static_cast<std::int32_t>(p));

        if(my_data.front() != static_cast<limb_type>(0U))
        {
          // Adjust the exponent because of the internal scaling of the FFT multiplication.
          my_exp += static_cast<std::int64_t>(decwide_t_elem_digits10);
        }
        else
        {
          // Justify the data.
          std::copy(my_data.cbegin() +  static_cast<std::ptrdiff_t>(1),
                    my_data.cbegin() + (static_cast<std::ptrdiff_t>(1) + static_cast<std::ptrdiff_t>(my_prec_elem)),
                    my_data.begin());

          my_data.back() = static_cast<limb_type>(0U);
        }
      }
    }

    std::int64_t get_order_exact() const { return get_order_fast(); }

    std::int64_t get_order_fast() const
    {
      if(isfinite() == false)
      {
        return static_cast<std::int64_t>(0);
      }
      else
      {
        std::int_fast16_t n10 = INT16_C(-1);

        limb_type p10 = (limb_type) 1U;

        const limb_type limit_aligned_with_10 = my_data[0U] + (limb_type) (10U - (my_data[0U] % 10U));

        while(p10 < limit_aligned_with_10)
        {
          p10 *= 10U;

          ++n10;
        }

        return static_cast<std::int64_t>(my_exp + n10);
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

        str.erase(pos, static_cast<std::size_t>(1U));
      }

      if((pos = str.find(static_cast<char>('+'))) != std::string::npos)
      {
        str.erase(pos, static_cast<std::size_t>(1U));
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
        if(str.at(static_cast<std::size_t>(0U)) == static_cast<char>('.'))
        {
          const std::string::const_iterator it_non_zero =
            std::find_if(str.cbegin() + 1U,
                         str.cend(),
                         [](const char& c) -> bool
                         {
                           return (c != static_cast<char>('0'));
                         });

          std::size_t delta_exp = static_cast<std::size_t>(0U);

          if(str.at(static_cast<std::size_t>(1U)) == static_cast<char>('0'))
          {
            delta_exp = static_cast<std::size_t>(it_non_zero - (str.cbegin() + 1U));
          }

          // Bring one single digit into the mantissa and adjust exponent accordingly.
          str.erase(str.cbegin(), it_non_zero);

          str.insert(static_cast<std::size_t>(1U), ".");

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

        str.insert(static_cast<std::size_t>(static_cast<std::int32_t>(n_pos - static_cast<std::int32_t>(n * decwide_t_elem_digits10))), ".");

        str.erase(static_cast<std::string::size_type>(pos_plus_one), static_cast<std::size_t>(1U));

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
    void get_output_string(std::string& str, std::int64_t& the_exp, const std::size_t number_of_digits) const
    {
      // Determine the number of elements needed to provide the requested digits from decwide_t.
      const std::size_t number_of_elements = (std::min)(static_cast<std::size_t>((number_of_digits / static_cast<std::size_t>(decwide_t_elem_digits10)) + 2U),
                                                        static_cast<std::size_t>(decwide_t_elem_number));

      // Extract the remaining digits from decwide_t after the decimal point.
      char p_str[10U] = { 0 };
      char* p_end = util::baselexical_cast(my_data[0], p_str);

      str = std::string(p_str, p_end);

      // Extract all of the digits from decwide_t, beginning with the first data element.
      for(std::size_t i = static_cast<std::size_t>(1U); i < number_of_elements; i++)
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
        str = str.substr(static_cast<std::size_t>(0U), number_of_digits);

        if(round >= static_cast<std::uint32_t>(5U))
        {
          std::size_t ix = static_cast<std::size_t>(str.length() - 1U);

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
      if(!isfinite()) { special_handle_string_not_finite(str, static_cast<const decwide_t&>(*this), my_showpos, my_uppercase); return; }

      // Get the base-10 exponent.
      std::int64_t the_exp = get_order_exact();

      // Get the output stream's precision and limit it to max_digits10.
      // Erroneous zero or negative precision (theoretically impossible)
      // will be set to ostream's default precision.
      static const std::stringstream str_default;
      static const std::streamsize   prec_default = str_default.precision();

      const std::size_t os_precision  = ((os.precision() <= static_cast<std::streamsize>(0)) ? static_cast<std::size_t>(prec_default) : static_cast<std::size_t>(os.precision()));

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
      std::size_t the_number_of_digits_i_want_from_decwide_t = static_cast<std::size_t>(0U);

      const std::size_t max10_plus_one = static_cast<std::size_t>(decwide_t_max_digits10 + 1);

      if(use_scientific)
      {
        // The float-field is scientific. The number of digits is given by
        // (1 + the ostream's precision), not to exceed (max_digits10 + 1).
        const std::size_t prec_plus_one  = static_cast<std::size_t>(1U + os_precision);
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
          const std::size_t exp_plus_one = static_cast<std::size_t>(the_exp + 1);
          const std::size_t exp_plus_one_plus_my_precision = static_cast<std::size_t>(exp_plus_one + os_precision);

          the_number_of_digits_i_want_from_decwide_t = (std::min)(exp_plus_one_plus_my_precision, max10_plus_one);
        }
        else
        {
          const std::int64_t exp_plus_one = static_cast<std::int64_t>(the_exp + 1);
          const std::int64_t exp_plus_one_plus_my_precision = static_cast<std::int64_t>(exp_plus_one + static_cast<std::int64_t>(os_precision));

          the_number_of_digits_i_want_from_decwide_t = (std::min)(static_cast<std::size_t>((std::max)(exp_plus_one_plus_my_precision, static_cast<std::int64_t>(0))), max10_plus_one);
        }
      }

      // If the float field is not set, reduce the number of digits requested
      // from decwide_t such that it neither exceeds the ostream's precision
      // nor decwide_t's max_digits10.
      if(my_float_field == detail::os_float_field_none)
      {
        const std::size_t max_digits = (std::min)(os_precision, static_cast<std::size_t>(decwide_t_max_digits10));
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
      if     (isneg())    { str.insert(static_cast<std::size_t>(0U), "-"); }
      else if(my_showpos) { str.insert(static_cast<std::size_t>(0U), "+"); }

      // Handle std::setw(...), std::setfill(...), std::left, std::right, std::internal.
      const std::size_t my_width = ((os.width() >= static_cast<std::streamsize>(0)) ? static_cast<std::size_t>(os.width())
                                                                                    : static_cast<std::size_t>(0U));

      if(my_width > str.length())
      {
        // Get the number of fill characters.
        const std::size_t n_fill = static_cast<std::size_t>(my_width - str.length());

        // Left-justify is the exception, std::right and std::internal justify right.
        const bool my_left = ((my_flags & std::ios::left)  != static_cast<std::ios::fmtflags>(0U));

        // Justify left or right and insert the fill characters.
        str.insert((my_left ? str.cend() : str.cbegin()), n_fill, os.fill());
      }
    }

    static void wr_string_scientific(std::string& str,
                                      const std::int64_t the_exp,
                                      const std::size_t os_precision,
                                      const bool my_showpoint,
                                      const bool my_uppercase,
                                      const bool trim_trailing_zeros = false)
    {
      if(os_precision > static_cast<std::size_t>(str.length() - 1U))
      {
        // Zero-extend the string to the given precision if necessary.
        const std::size_t n_pad = static_cast<std::size_t>(os_precision - (str.length() - 1U));

        str.insert(str.cend(), n_pad, static_cast<char>('0'));
      }

      // Insert the decimal point.
      str.insert(static_cast<std::size_t>(1U), ".");

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
      const std::size_t str_exp_len_pad  = ((str_exp_len_mod3 != static_cast<std::size_t>(0U)) ? static_cast<std::size_t>(3U - (str_exp_len % 3U))
                                                                                                : static_cast<std::size_t>(0U));

      str += std::string(str_exp_len_pad, static_cast<char>('0'));
      str += str_exp;
    }

    static void wr_string_fixed(std::string& str,
                                const std::int64_t the_exp,
                                const std::size_t os_precision,
                                const bool my_showpoint,
                                const bool trim_trailing_zeros = false)
    {
      const std::size_t input_str_len = str.length();

      if(the_exp < static_cast<std::int64_t>(0))
      {
        // The number is less than one in magnitude. Insert the decimal
        // point using "0." as well as the needed number of leading zeros.
        const std::size_t minus_exp_minus_one = static_cast<std::size_t>(-the_exp - 1);
        const std::string str_zero_insert((std::min)(minus_exp_minus_one, os_precision), static_cast<char>('0'));

        const std::int64_t n_pad = static_cast<std::int64_t>(static_cast<std::int64_t>(os_precision) - static_cast<std::int64_t>(str.length() + str_zero_insert.length()));

        str.insert(0U, "0." + str_zero_insert);

        // Zero-extend the string to the given precision if necessary.
        if(n_pad > static_cast<std::int64_t>(0))
        {
          str.insert(str.cend(), static_cast<std::size_t>(n_pad), static_cast<char>('0'));
        }
      }
      else
      {
        // Insert the decimal point.
        const std::size_t my_exp_plus_one = static_cast<std::size_t>(the_exp + 1);

        // The number string is not large enough to hold the integer part of the number.
        // Zero extend the integer part of the string.
        if(input_str_len < my_exp_plus_one)
        {
          str.insert(str.cend(), static_cast<std::size_t>(my_exp_plus_one- str.length()), static_cast<char>('0'));
        }

        str.insert(my_exp_plus_one, ".");

        // Zero-extend the string to the given precision if necessary.
        const std::int64_t n_pad = static_cast<std::int64_t>(os_precision) - static_cast<std::int64_t>(static_cast<std::int64_t>(str.length() - 1U) - (the_exp + 1));

        if(n_pad > static_cast<std::int64_t>(0))
        {
          str.insert(str.cend(), static_cast<std::size_t>(n_pad), static_cast<char>('0'));
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
      if(f.isinf())
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

    static void special_extend_string_to_precision(std::string& str, const std::size_t os_precision)
    {
      // This is the special case of showpoint in combination with
      // a non-fixed, non-scientific representation. The string has
      // to be zero extended such that the total width of its entire
      // non-zero part exactly equals the precision.

      // Check if the number is less than 1.
      if(   (str.at(static_cast<std::size_t>(0U)) == static_cast<char>('0'))
          && (str.at(static_cast<std::size_t>(1U)) == static_cast<char>('.'))
        )
      {
        if(str.length() == static_cast<std::size_t>(2U))
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

          const std::size_t len_non_zero_part = static_cast<std::size_t>(str.cend() - it_non_zero);

          const std::size_t u_pad = static_cast<std::size_t>(os_precision - len_non_zero_part);

          str.insert(str.cend(), u_pad, static_cast<char>('0'));
        }
      }
      else
      {
        // This is a number greater than or equal to 1 that needs zero extension.
        const std::size_t u_pad = static_cast<std::size_t>(os_precision - static_cast<std::size_t>(str.length() - static_cast<std::size_t>(1U)));

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

    friend decwide_t zero<>();
    friend decwide_t one <>();
    friend decwide_t half<>();
    friend decwide_t two <>();
  };

  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType>
  InternalFloatType decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>::my_af_bf_fft_mul_pool[detail::decwide_t_helper<MyDigits10, LimbType>::pow2_maker_of_upper_limit(decwide_t_elem_number) * 8UL];

  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType>
  typename decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>::array_type decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>::my_n_data_for_add_sub;

  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType> decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType> zero() { return decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>( { typename decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>::limb_type(0U) } ); }
  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType> decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType> one () { return decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>( { typename decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>::limb_type(1U) } ); }
  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType> decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType> half() { return decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>( { typename decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>::limb_type(decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>::decwide_t_elem_mask / 2) }, -decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>::decwide_t_elem_digits10 ); }
  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType> decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType> two () { return decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>( { typename decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>::limb_type(2U) } ); }

  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType> decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType> pi(void(*pfn_callback_to_report_digits10)(const std::uint32_t))
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

    decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType> val_pi;

    decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType> a((typename decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>::limb_type) 1U);

    // Initialize bB to 0.5.
    decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType> bB
    (
      {
        (typename decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>::limb_type) (decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>::decwide_t_elem_mask / 2)
      },
      static_cast<std::int64_t>(-decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>::decwide_t_elem_digits10)
    );

    // Initialize t to 0.375.
    decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType> t
    (
      {
        (typename decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>::limb_type) ((((typename decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>::double_limb_type) decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>::decwide_t_elem_mask) * 3) / 8)
      },
      static_cast<std::int64_t>(-decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>::decwide_t_elem_digits10)
    );

    decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType> s(bB);

    // This loop is designed for a maximum of several million
    // decimal digits of pi. The index k should reach no higher
    // than about 25 or 30. After about 20 iterations, the precision
    // is about one million decimal digits.

    for(unsigned k = 0U; k < 48U; ++k)
    {
      a      += sqrt(bB);
      a      /= 2U;
      val_pi  = a;
      val_pi *= a;
      bB      = val_pi;
      bB     -= t;
      bB     *= 2U;

      std::int32_t approximate_digits10_of_iteration_term;

      {
        decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType> iterate_term(bB);

        iterate_term -= val_pi;
        iterate_term *= (unsigned long long) (1ULL << (k + 1U));

        s += iterate_term;

        // Test the number of precise digits from this iteration.
        // If it is there are enough precise digits, then the calculation
        // is finished.
        approximate_digits10_of_iteration_term = -ilogb(iterate_term);

        if(pfn_callback_to_report_digits10 != nullptr)
        {
          pfn_callback_to_report_digits10((std::uint32_t) approximate_digits10_of_iteration_term);
        }
      }

      // Estimate the approximate decimal digits of this iteration term.
      // If we have attained about half of the total desired digits
      // with this iteration term, then the calculation is finished
      // because the change from the next iteration will be
      // insignificantly small.
      const std::int32_t digits10_iteration_goal = static_cast<std::int32_t>((std::numeric_limits<decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>>::digits10 / 2) + 16);

      if(approximate_digits10_of_iteration_term > digits10_iteration_goal)
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
      pfn_callback_to_report_digits10((std::uint32_t) std::numeric_limits<decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>>::digits10);
    }

    return val_pi;
  }

  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType> std::int32_t   max_iteration() { return static_cast<std::int32_t>(10000); }
  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType> std::int64_t   tolerance    () { return static_cast<std::int64_t>(decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>::decwide_t_max_digits10 + (decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>::decwide_t_max_digits10 / 10)); }

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
      static const bool                    is_specialized    = true;
      static const bool                    is_signed         = true;
      static const bool                    is_integer        = false;
      static const bool                    is_exact          = false;
      static const bool                    is_bounded        = true;
      static const bool                    is_modulo         = false;
      static const bool                    is_iec559         = false;
      static const std::int64_t            digits            = math::wide_decimal::decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>::decwide_t_digits;       // Type differs from int.
      static const std::int64_t            digits10          = math::wide_decimal::decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>::decwide_t_digits10;     // Type differs from int.
      static const std::int64_t            max_digits10      = math::wide_decimal::decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>::decwide_t_max_digits10; // Type differs from int.
      static const std::int64_t            min_exponent      = math::wide_decimal::decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>::decwide_t_min_exp;      // Type differs from int.
      static const std::int64_t            min_exponent10    = math::wide_decimal::decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>::decwide_t_min_exp10;    // Type differs from int.
      static const std::int64_t            max_exponent      = math::wide_decimal::decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>::decwide_t_max_exp;      // Type differs from int.
      static const std::int64_t            max_exponent10    = math::wide_decimal::decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>::decwide_t_max_exp10;    // Type differs from int.
      static const int                     radix             = math::wide_decimal::decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>::decwide_t_radix;
      static const std::float_round_style  round_style       = std::round_to_nearest;
      static const bool                    has_infinity      = true;
      static const bool                    has_quiet_NaN     = true;
      static const bool                    has_signaling_NaN = false;
      static const std::float_denorm_style has_denorm        = std::denorm_absent;
      static const bool                    has_denorm_loss   = false;
      static const bool                    traps             = false;
      static const bool                    tinyness_before   = false;

      static math::wide_decimal::decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType> (min)        () { return math::wide_decimal::decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>::my_value_min(); }
      static math::wide_decimal::decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType> (max)        () { return math::wide_decimal::decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>::my_value_max(); }
      static math::wide_decimal::decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType> lowest       () { return math::wide_decimal::zero<MyDigits10, LimbType, AllocatorType, InternalFloatType>(); }
      static math::wide_decimal::decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType> epsilon      () { return math::wide_decimal::decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>::my_value_eps(); }
      static math::wide_decimal::decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType> round_error  () { return math::wide_decimal::half<MyDigits10, LimbType, AllocatorType, InternalFloatType>(); }
      static math::wide_decimal::decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType> infinity     () { return math::wide_decimal::decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>::my_value_inf(); }
      static math::wide_decimal::decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType> quiet_NaN    () { return math::wide_decimal::decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>::my_value_nan(); }
      static math::wide_decimal::decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType> signaling_NaN() { return math::wide_decimal::zero<MyDigits10, LimbType, AllocatorType, InternalFloatType>(); }
      static math::wide_decimal::decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType> denorm_min   () { return math::wide_decimal::zero<MyDigits10, LimbType, AllocatorType, InternalFloatType>(); }
    };
  } // namespace std

  namespace math { namespace wide_decimal {

  namespace detail {

  // *****************************************************************************
  // Function    : template<typename T> T pown_template(const T& d, const std::int64_t p)
  // 
  // Description : Template function for computing an object d of typename T
  //               raised to the power of std::int64_t p, for p positive or negative.
  //               Binary splitting of the power is used. The resulting
  //               computational complexity scales with O[log2(|p|)].
  // 
  // *****************************************************************************
  template<typename T>
  T pown_template(const T& t, const std::int64_t p)
  {
    // Compute the pure power of typename T t^p. Binary splitting of the power is
    // used. The resulting computational complexity is proportional to O[log2(|p|)].

    if     (p <  static_cast<std::int64_t>(0)) { return T(1) / pown_template(t, -p); }
    else if(p == static_cast<std::int64_t>(0)) { return T(1); }
    else if(p == static_cast<std::int64_t>(1)) { return t; }
    else if(p == static_cast<std::int64_t>(2)) { return (t * t); }
    else if(p == static_cast<std::int64_t>(3)) { return (t * t) * t; }
    else if(p == static_cast<std::int64_t>(4)) { const T t2(t * t); return (t2 * t2); }
    else if(p == static_cast<std::int64_t>(5)) { const T t2(t * t); return (t2 * t2) * t; }
    else
    {
      bool has_binary_power = (static_cast<std::int64_t>(p % 2) != static_cast<std::int64_t>(0));

      // The variable tn stores the binary powers of t.
      T result(has_binary_power ? t : T(1U));
      T tn    (t);

      std::int64_t p2 = p;

      while((p2 /= 2) != static_cast<std::int64_t>(0))
      {
        // Square tn for each binary power.
        // TBD: Is it faster (or better) to use the ladder method?
        tn *= tn;

        has_binary_power = (static_cast<std::int64_t>(p2 % 2) != static_cast<std::int64_t>(0));

        if(has_binary_power)
        {
          // Multiply the result with each binary power contained in the exponent.
          result *= tn;
        }
      }

      return result;
    }
  }

  } // namespace math::wide_decimal::detail

  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType> const decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType> int32_min             () { return decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>((std::numeric_limits<std::int32_t>::min)()); }
  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType> const decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType> int32_max             () { return decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>((std::numeric_limits<std::int32_t>::max)()); }
  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType> const decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType> int64_min             () { return decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>((std::numeric_limits<std::int64_t>::min)()); }
  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType> const decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType> int64_max             () { return decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>((std::numeric_limits<std::int64_t>::max)()); }
  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType> const decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType> unsigned_long_long_max() { return decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>((std::numeric_limits<unsigned long long>::max)()); }
  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType> const decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType> signed_long_long_min  () { return decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>((std::numeric_limits<signed long long>::min)()); }
  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType> const decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType> signed_long_long_max  () { return decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>((std::numeric_limits<signed long long>::max)()); }
  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType> const decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType> double_min            () { return decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>((std::numeric_limits<double>::min)()); }
  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType> const decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType> double_max            () { return decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>((std::numeric_limits<double>::max)()); }
  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType> const decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType> long_double_min       () { return decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>((std::numeric_limits<long double>::min)());}
  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType> const decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType> long_double_max       () { return decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>((std::numeric_limits<long double>::max)());}

  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType> decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType> fabs (const decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>& x) { return decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>::my_fabs(x); }

  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType> decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType> floor(const decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>& x);
  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType> decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType> ceil (const decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>& x);
  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType> std::int32_t                  sgn  (const decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>& x);
  #if !defined(WIDE_DECIMAL_DISABLE_CONSTRUCT_FROM_BUILTIN_FLOAT)
  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType> decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType> ldexp(const decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>& v, int e);
  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType> decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType> frexp(const decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>& v, int* expon);
  #endif // !WIDE_DECIMAL_DISABLE_CONSTRUCT_FROM_BUILTIN_FLOAT
  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType> decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType> fmod (const decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>& v1, const decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>& v2);
  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType> std::int32_t                  ilogb(const decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>& x);

  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType> bool isnan   (const decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>& x) { return x.isnan(); }
  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType> bool isfinite(const decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>& x) { return x.isfinite(); }
  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType> bool isinf   (const decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>& x) { return x.isinf(); }
  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType> bool isneg   (const decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>& x) { return x.isneg(); }
  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType> bool ispos   (const decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>& x) { return (!x.isneg()); }
  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType> bool isint   (const decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>& x) { return x.isint(); }
  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType> bool isone   (const decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>& x) { return x.isone(); }
  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType> bool iszero  (const decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>& x) { return x.iszero(); }

  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType> double to_double(const decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>& x);

  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType> std::int64_t to_int64(const decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>& x);
  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType> std::int32_t to_int32(const decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>& x);

  #if !defined(WIDE_DECIMAL_DISABLE_CONSTRUCT_FROM_BUILTIN_FLOAT)
  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType> decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType> pow2(const std::int64_t p)
  {
    // Create a static const table of p^2 for -128 < p < +128.
    // Note: The size of this table must be odd-numbered and
    // symmetric about 0.
    static const std::array<decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>, 255U> p2_data =
    {{
      decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>("5.8774717541114375398436826861112283890933277838604376075437585313920862972736358642578125e-39"),
      decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>("1.1754943508222875079687365372222456778186655567720875215087517062784172594547271728515625e-38"),
      decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>("2.350988701644575015937473074444491355637331113544175043017503412556834518909454345703125e-38"),
      decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>("4.70197740328915003187494614888898271127466222708835008603500682511366903781890869140625e-38"),
      decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>("9.4039548065783000637498922977779654225493244541767001720700136502273380756378173828125e-38"),
      decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>("1.8807909613156600127499784595555930845098648908353400344140027300454676151275634765625e-37"),
      decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>("3.761581922631320025499956919111186169019729781670680068828005460090935230255126953125e-37"),
      decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>("7.52316384526264005099991383822237233803945956334136013765601092018187046051025390625e-37"),
      decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>("1.50463276905252801019998276764447446760789191266827202753120218403637409210205078125e-36"),
      decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>("3.0092655381050560203999655352889489352157838253365440550624043680727481842041015625e-36"),
      decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>("6.018531076210112040799931070577897870431567650673088110124808736145496368408203125e-36"),
      decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>("1.203706215242022408159986214115579574086313530134617622024961747229099273681640625e-35"),
      decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>("2.40741243048404481631997242823115914817262706026923524404992349445819854736328125e-35"),
      decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>("4.8148248609680896326399448564623182963452541205384704880998469889163970947265625e-35"),
      decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>("9.629649721936179265279889712924636592690508241076940976199693977832794189453125e-35"),
      decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>("1.925929944387235853055977942584927318538101648215388195239938795566558837890625e-34"),
      decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>("3.85185988877447170611195588516985463707620329643077639047987759113311767578125e-34"),
      decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>("7.7037197775489434122239117703397092741524065928615527809597551822662353515625e-34"),
      decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>("1.5407439555097886824447823540679418548304813185723105561919510364532470703125e-33"),
      decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>("3.081487911019577364889564708135883709660962637144621112383902072906494140625e-33"),
      decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>("6.16297582203915472977912941627176741932192527428924222476780414581298828125e-33"),
      decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>("1.23259516440783094595582588325435348386438505485784844495356082916259765625e-32"),
      decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>("2.4651903288156618919116517665087069677287701097156968899071216583251953125e-32"),
      decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>("4.930380657631323783823303533017413935457540219431393779814243316650390625e-32"),
      decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>("9.86076131526264756764660706603482787091508043886278755962848663330078125e-32"),
      decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>("1.97215226305252951352932141320696557418301608777255751192569732666015625e-31"),
      decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>("3.9443045261050590270586428264139311483660321755451150238513946533203125e-31"),
      decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>("7.888609052210118054117285652827862296732064351090230047702789306640625e-31"),
      decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>("1.577721810442023610823457130565572459346412870218046009540557861328125e-30"),
      decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>("3.15544362088404722164691426113114491869282574043609201908111572265625e-30"),
      decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>("6.3108872417680944432938285222622898373856514808721840381622314453125e-30"),
      decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>("1.2621774483536188886587657044524579674771302961744368076324462890625e-29"),
      decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>("2.524354896707237777317531408904915934954260592348873615264892578125e-29"),
      decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>("5.04870979341447555463506281780983186990852118469774723052978515625e-29"),
      decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>("1.00974195868289511092701256356196637398170423693954944610595703125e-28"),
      decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>("2.0194839173657902218540251271239327479634084738790988922119140625e-28"),
      decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>("4.038967834731580443708050254247865495926816947758197784423828125e-28"),
      decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>("8.07793566946316088741610050849573099185363389551639556884765625e-28"),
      decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>("1.61558713389263217748322010169914619837072677910327911376953125e-27"),
      decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>("3.2311742677852643549664402033982923967414535582065582275390625e-27"),
      decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>("6.462348535570528709932880406796584793482907116413116455078125e-27"),
      decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>("1.292469707114105741986576081359316958696581423282623291015625e-26"),
      decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>("2.58493941422821148397315216271863391739316284656524658203125e-26"),
      decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>("5.1698788284564229679463043254372678347863256931304931640625e-26"),
      decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>("1.0339757656912845935892608650874535669572651386260986328125e-25"),
      decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>("2.067951531382569187178521730174907133914530277252197265625e-25"),
      decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>("4.13590306276513837435704346034981426782906055450439453125e-25"),
      decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>("8.2718061255302767487140869206996285356581211090087890625e-25"),
      decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>("1.6543612251060553497428173841399257071316242218017578125e-24"),
      decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>("3.308722450212110699485634768279851414263248443603515625e-24"),
      decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>("6.61744490042422139897126953655970282852649688720703125e-24"),
      decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>("1.32348898008484427979425390731194056570529937744140625e-23"),
      decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>("2.6469779601696885595885078146238811314105987548828125e-23"),
      decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>("5.293955920339377119177015629247762262821197509765625e-23"),
      decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>("1.058791184067875423835403125849552452564239501953125e-22"),
      decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>("2.11758236813575084767080625169910490512847900390625e-22"),
      decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>("4.2351647362715016953416125033982098102569580078125e-22"),
      decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>("8.470329472543003390683225006796419620513916015625e-22"),
      decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>("1.694065894508600678136645001359283924102783203125e-21"),
      decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>("3.38813178901720135627329000271856784820556640625e-21"),
      decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>("6.7762635780344027125465800054371356964111328125e-21"),
      decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>("1.3552527156068805425093160010874271392822265625e-20"),
      decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>("2.710505431213761085018632002174854278564453125e-20"),
      decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>("5.42101086242752217003726400434970855712890625e-20"),
      decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>("1.08420217248550443400745280086994171142578125e-19"),
      decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>("2.1684043449710088680149056017398834228515625e-19"),
      decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>("4.336808689942017736029811203479766845703125e-19"),
      decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>("8.67361737988403547205962240695953369140625e-19"),
      decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>("1.73472347597680709441192448139190673828125e-18"),
      decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>("3.4694469519536141888238489627838134765625e-18"),
      decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>("6.938893903907228377647697925567626953125e-18"),
      decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>("1.387778780781445675529539585113525390625e-17"),
      decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>("2.77555756156289135105907917022705078125e-17"),
      decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>("5.5511151231257827021181583404541015625e-17"),
      decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>("1.1102230246251565404236316680908203125e-16"),
      decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>("2.220446049250313080847263336181640625e-16"),
      decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>("4.44089209850062616169452667236328125e-16"),
      decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>("8.8817841970012523233890533447265625e-16"),
      decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>("1.7763568394002504646778106689453125e-15"),
      decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>("3.552713678800500929355621337890625e-15"),
      decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>("7.10542735760100185871124267578125e-15"),
      decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>("1.42108547152020037174224853515625e-14"),
      decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>("2.8421709430404007434844970703125e-14"),
      decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>("5.684341886080801486968994140625e-14"),
      decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>("1.136868377216160297393798828125e-13"),
      decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>("2.27373675443232059478759765625e-13"),
      decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>("4.5474735088646411895751953125e-13"),
      decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>("9.094947017729282379150390625e-13"),
      decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>("1.818989403545856475830078125e-12"),
      decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>("3.63797880709171295166015625e-12"),
      decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>("7.2759576141834259033203125e-12"),
      decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>("1.4551915228366851806640625e-11"),
      decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>("2.910383045673370361328125e-11"),
      decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>("5.82076609134674072265625e-11"),
      decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>("1.16415321826934814453125e-10"),
      decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>("2.3283064365386962890625e-10"),
      decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>("4.656612873077392578125e-10"),
      decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>("9.31322574615478515625e-10"),
      decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>("1.86264514923095703125e-9"),
      decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>("3.7252902984619140625e-9"),
      decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>("7.450580596923828125e-9"),
      decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>("1.490116119384765625e-8"),
      decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>("2.98023223876953125e-8"),
      decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>("5.9604644775390625e-8"),
      decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>("1.1920928955078125e-7"),
      decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>("2.384185791015625e-7"),
      decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>("4.76837158203125e-7"),
      decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>("9.5367431640625e-7"),
      decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>("1.9073486328125e-6"),
      decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>("3.814697265625e-6"),
      decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>("7.62939453125e-6"),
      decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>("0.0000152587890625"),
      decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>("0.000030517578125"),
      decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>("0.00006103515625"),
      decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>("0.0001220703125"),
      decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>("0.000244140625"),
      decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>("0.00048828125"),
      decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>("0.0009765625"),
      decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>("0.001953125"),
      decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>("0.00390625"),
      decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>("0.0078125"),
      decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>("0.015625"),
      decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>("0.03125"),
      decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>("0.0625"),
      decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>("0.0125"),
      decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>("0.25"),
      decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>("0.5"),
      decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>(1U),
      decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>(2U),
      decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>(4U),
      decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>(8U),
      decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>(16),
      decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>(32),
      decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>(64),
      decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>(128),
      decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>(256),
      decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>(512),
      decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>(1024),
      decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>(2048),
      decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>(4096),
      decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>(8192),
      decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>(16384),
      decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>(32768),
      decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>(65536),
      decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>(131072),
      decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>(262144),
      decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>(524288),
      decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>(static_cast<std::uint32_t>(1UL << 20U)),
      decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>(static_cast<std::uint32_t>(1UL << 21U)),
      decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>(static_cast<std::uint32_t>(1UL << 22U)),
      decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>(static_cast<std::uint32_t>(1UL << 23U)),
      decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>(static_cast<std::uint32_t>(1UL << 24U)),
      decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>(static_cast<std::uint32_t>(1UL << 25U)),
      decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>(static_cast<std::uint32_t>(1UL << 26U)),
      decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>(static_cast<std::uint32_t>(1UL << 27U)),
      decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>(static_cast<std::uint32_t>(1UL << 28U)),
      decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>(static_cast<std::uint32_t>(1UL << 29U)),
      decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>(static_cast<std::uint32_t>(1UL << 30U)),
      decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>(static_cast<std::uint32_t>(1UL << 31U)),
      decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>(static_cast<std::uint64_t>(1ULL << 32U)),
      decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>(static_cast<std::uint64_t>(1ULL << 33U)),
      decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>(static_cast<std::uint64_t>(1ULL << 34U)),
      decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>(static_cast<std::uint64_t>(1ULL << 35U)),
      decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>(static_cast<std::uint64_t>(1ULL << 36U)),
      decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>(static_cast<std::uint64_t>(1ULL << 37U)),
      decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>(static_cast<std::uint64_t>(1ULL << 38U)),
      decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>(static_cast<std::uint64_t>(1ULL << 39U)),
      decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>(static_cast<std::uint64_t>(1ULL << 40U)),
      decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>(static_cast<std::uint64_t>(1ULL << 41U)),
      decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>(static_cast<std::uint64_t>(1ULL << 42U)),
      decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>(static_cast<std::uint64_t>(1ULL << 43U)),
      decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>(static_cast<std::uint64_t>(1ULL << 44U)),
      decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>(static_cast<std::uint64_t>(1ULL << 45U)),
      decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>(static_cast<std::uint64_t>(1ULL << 46U)),
      decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>(static_cast<std::uint64_t>(1ULL << 47U)),
      decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>(static_cast<std::uint64_t>(1ULL << 48U)),
      decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>(static_cast<std::uint64_t>(1ULL << 49U)),
      decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>(static_cast<std::uint64_t>(1ULL << 50U)),
      decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>(static_cast<std::uint64_t>(1ULL << 51U)),
      decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>(static_cast<std::uint64_t>(1ULL << 52U)),
      decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>(static_cast<std::uint64_t>(1ULL << 53U)),
      decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>(static_cast<std::uint64_t>(1ULL << 54U)),
      decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>(static_cast<std::uint64_t>(1ULL << 55U)),
      decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>(static_cast<std::uint64_t>(1ULL << 56U)),
      decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>(static_cast<std::uint64_t>(1ULL << 57U)),
      decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>(static_cast<std::uint64_t>(1ULL << 58U)),
      decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>(static_cast<std::uint64_t>(1ULL << 59U)),
      decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>(static_cast<std::uint64_t>(1ULL << 60U)),
      decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>(static_cast<std::uint64_t>(1ULL << 61U)),
      decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>(static_cast<std::uint64_t>(1ULL << 62U)),
      decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>(static_cast<std::uint64_t>(1ULL << 63U)),
      decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>("1.8446744073709551616e19"),
      decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>("3.6893488147419103232e19"),
      decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>("7.3786976294838206464e19"),
      decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>("1.47573952589676412928e20"),
      decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>("2.95147905179352825856e20"),
      decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>("5.90295810358705651712e20"),
      decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>("1.180591620717411303424e21"),
      decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>("2.361183241434822606848e21"),
      decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>("4.722366482869645213696e21"),
      decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>("9.444732965739290427392e21"),
      decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>("1.8889465931478580854784e22"),
      decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>("3.7778931862957161709568e22"),
      decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>("7.5557863725914323419136e22"),
      decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>("1.51115727451828646838272e23"),
      decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>("3.02231454903657293676544e23"),
      decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>("6.04462909807314587353088e23"),
      decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>("1.208925819614629174706176e24"),
      decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>("2.417851639229258349412352e24"),
      decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>("4.835703278458516698824704e24"),
      decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>("9.671406556917033397649408e24"),
      decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>("1.9342813113834066795298816e25"),
      decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>("3.8685626227668133590597632e25"),
      decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>("7.7371252455336267181195264e25"),
      decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>("1.54742504910672534362390528e26"),
      decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>("3.09485009821345068724781056e26"),
      decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>("6.18970019642690137449562112e26"),
      decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>("1.237940039285380274899124224e27"),
      decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>("2.475880078570760549798248448e27"),
      decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>("4.951760157141521099596496896e27"),
      decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>("9.903520314283042199192993792e27"),
      decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>("1.9807040628566084398385987584e28"),
      decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>("3.9614081257132168796771975168e28"),
      decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>("7.9228162514264337593543950336e28"),
      decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>("1.58456325028528675187087900672e29"),
      decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>("3.16912650057057350374175801344e29"),
      decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>("6.33825300114114700748351602688e29"),
      decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>("1.267650600228229401496703205376e30"),
      decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>("2.535301200456458802993406410752e30"),
      decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>("5.070602400912917605986812821504e30"),
      decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>("1.0141204801825835211973625643008e31"),
      decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>("2.0282409603651670423947251286016e31"),
      decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>("4.0564819207303340847894502572032e31"),
      decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>("8.1129638414606681695789005144064e31"),
      decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>("1.62259276829213363391578010288128e32"),
      decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>("3.24518553658426726783156020576256e32"),
      decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>("6.49037107316853453566312041152512e32"),
      decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>("1.298074214633706907132624082305024e33"),
      decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>("2.596148429267413814265248164610048e33"),
      decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>("5.192296858534827628530496329220096e33"),
      decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>("1.0384593717069655257060992658440192e34"),
      decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>("2.0769187434139310514121985316880384e34"),
      decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>("4.1538374868278621028243970633760768e34"),
      decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>("8.3076749736557242056487941267521536e34"),
      decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>("1.66153499473114484112975882535043072e35"),
      decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>("3.32306998946228968225951765070086144e35"),
      decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>("6.64613997892457936451903530140172288e35"),
      decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>("1.329227995784915872903807060280344576e36"),
      decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>("2.658455991569831745807614120560689152e36"),
      decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>("5.316911983139663491615228241121378304e36"),
      decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>("1.0633823966279326983230456482242756608e37"),
      decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>("2.1267647932558653966460912964485513216e37"),
      decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>("4.2535295865117307932921825928971026432e37"),
      decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>("8.5070591730234615865843651857942052864e37"),
      decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>("1.70141183460469231731687303715884105728e38")
    }};

    if((p > static_cast<std::int64_t>(-128)) && (p < static_cast<std::int64_t>(+128)))
    {
      return p2_data[static_cast<std::size_t>(p + ((p2_data.size() - 1U) / 2U))];
    }
    else if(p <= static_cast<std::int64_t>(-128))
    {
      return math::wide_decimal::pow2<MyDigits10, LimbType, AllocatorType, InternalFloatType>(static_cast<std::int64_t>(-p)).calculate_inv();
    }
    else
    {
      return detail::pown_template(two<MyDigits10, LimbType, AllocatorType, InternalFloatType>(), p);
    }
  }
  #endif // !WIDE_DECIMAL_DISABLE_CONSTRUCT_FROM_BUILTIN_FLOAT

  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType> decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType> inv(const decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>& x)
  {
    return decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>(x).calculate_inv();
  }

  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType> decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType> sqrt(const decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>& x)
  {
    return decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>(x).calculate_sqrt();
  }

  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType> decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType> cbrt(const decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>& x)
  {
    return rootn(x, static_cast<std::int32_t>(3));
  }

  namespace ElementaryTrans_Series
  {
    template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType> decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType> rootn_inv(const decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>& x, const std::int32_t p)
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

      using std::pow;

      // Estimate the one over the root using simple manipulations.
      const InternalFloatType one_over_rtn_d = pow(dd, InternalFloatType(-1) / static_cast<InternalFloatType>(p));

      // Set the result equal to the initial guess.
      math::wide_decimal::decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType> result(one_over_rtn_d, static_cast<std::int64_t>(-ne / p));

      for(std::int32_t digits = (std::int32_t) (std::numeric_limits<InternalFloatType>::digits10 - 1); digits < static_cast<std::int32_t>(math::wide_decimal::tolerance<MyDigits10, LimbType, AllocatorType, InternalFloatType>()); digits *= static_cast<std::int32_t>(2))
      {
        // Adjust precision of the terms.
        const std::int32_t new_prec = static_cast<std::int32_t>(digits * 2) + 10;

        result.precision(new_prec);

        // Perform the next iteration.
        math::wide_decimal::decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType> term = (((-math::wide_decimal::detail::pown_template(result, p) * x) + one<MyDigits10, LimbType, AllocatorType, InternalFloatType>()) / p) + one<MyDigits10, LimbType, AllocatorType, InternalFloatType>();

        term.precision(new_prec);

        result *= term;
  
      }

      result.precision(static_cast<std::int32_t>(math::wide_decimal::tolerance<MyDigits10, LimbType, AllocatorType, InternalFloatType>()));

      return result;
    }
  }

  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType> decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType> rootn(const decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>& x, const std::int32_t p)
  {
    if(!isfinite(x))
    {
      return std::numeric_limits<math::wide_decimal::decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>>::quiet_NaN();
    }

    if(p < static_cast<std::int32_t>(0))
    {
      return rootn(one<MyDigits10, LimbType, AllocatorType, InternalFloatType>() / x, static_cast<std::int32_t>(-p));
    }

    if((p == static_cast<std::int32_t>(0)) || isneg(x))
    {
      return std::numeric_limits<decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>>::quiet_NaN();
    }
    else if(p == static_cast<std::int32_t>(1))
    {
      return x;
    }
    else if(p == static_cast<std::int32_t>(2))
    {
      return sqrt(x);
    }

    const decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType> rtn =  ElementaryTrans_Series::rootn_inv(x, p).calculate_inv();

    return rtn;
  }

  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType> decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType> rootn_inverse(const decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>& x, const std::int32_t p)
  {
    if(!isfinite(x))
    {
      return std::numeric_limits<decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>>::quiet_NaN();
    }

    if(p < static_cast<std::int32_t>(0))
    {
      return detail::pown_template(x, static_cast<std::int32_t>(-p));
    }

    if((p == static_cast<std::int32_t>(0)) || isneg(x))
    {
      return std::numeric_limits<decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>>::quiet_NaN();
    }
    else if(p == static_cast<std::int32_t>(1))
    {
      return x;
    }
    else if(p == static_cast<std::int32_t>(2))
    {
      return one<MyDigits10, LimbType, AllocatorType, InternalFloatType>() / math::wide_decimal::sqrt(x);
    }

    const decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType> rtn_inv =  ElementaryTrans_Series::rootn_inv(x, p);

    return rtn_inv;
  }

  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType> decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType> floor(const decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>& x)
  {
    if(!isfinite(x) || isint(x)) { return x; }

    return (isneg(x) ? integer_part(x - one<MyDigits10, LimbType, AllocatorType, InternalFloatType>())
                      : integer_part(x));
  }

  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType> decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType> ceil(const decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>& x)
  {
    if(!isfinite(x) || isint(x)) { return x; }

    return (isneg(x) ? integer_part(x)
                          : integer_part(x + one<MyDigits10, LimbType, AllocatorType, InternalFloatType>()));
  }

  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType> std::int32_t sgn(const decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>& x)
  {
    if(iszero(x))
    {
      return static_cast<std::int32_t>(0);
    }
    else
    {
      return (isneg(x) ? static_cast<std::int32_t>(-1) : static_cast<std::int32_t>(1));
    }
  }

  #if !defined(WIDE_DECIMAL_DISABLE_CONSTRUCT_FROM_BUILTIN_FLOAT)
  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType> decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType> ldexp(const decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>& v, int e)
  {
    return v * pow2<MyDigits10, LimbType, AllocatorType, InternalFloatType>(e);
  }

  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType> decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType> frexp(const decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>& v, int* expon)
  {
    double       d;
    std::int64_t i;

    v.extract_parts(d, i);

    *expon = static_cast<int>(i);

    return v * pow2<MyDigits10, LimbType, AllocatorType, InternalFloatType>(static_cast<std::int64_t>(-i));
  }
  #endif // !WIDE_DECIMAL_DISABLE_CONSTRUCT_FROM_BUILTIN_FLOAT

  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType> std::int32_t ilogb(const decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>& x)
  {
    std::int64_t e10 = x.order();

    const std::int32_t e10_as_int32 =
        (e10 > (std::numeric_limits<std::int32_t>::max)()) ? (std::numeric_limits<std::int32_t>::max)()
      : (e10 < (std::numeric_limits<std::int32_t>::min)()) ? (std::numeric_limits<std::int32_t>::min)()
      : static_cast<std::int32_t>(e10);

    return e10_as_int32;
  }

  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType> decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType> fmod(const decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>& v1, const decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>& v2)
  {
    const decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType> n = (isneg(v1) ? ceil(v1 / v2) : floor(v1 / v2));

    return v1 - (n * v2);
  }

  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType> double to_double(const decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>& x)
  {
    return x.extract_double();
  }

  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType> std::int64_t to_int64(const decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>& x)
  {
    return static_cast<std::int64_t>(x.extract_signed_long_long());
  }

  template<const std::int32_t MyDigits10, typename LimbType, typename AllocatorType, typename InternalFloatType> std::int32_t to_int32(const decwide_t<MyDigits10, LimbType, AllocatorType, InternalFloatType>& x)
  {
    const std::int64_t n32_max = static_cast<std::int64_t>((std::numeric_limits<std::int32_t>::max)());
    const std::int64_t n32_min = static_cast<std::int64_t>((std::numeric_limits<std::int32_t>::min)());

    const std::int64_t n64 = to_int64(x);

    return static_cast<std::int32_t>((std::min)((std::max)(n64, n32_min), n32_max));
  }

  bool example001_sqrt          ();
  bool example002_pi            ();
  bool example002a_pi_small_limb();
  bool example002b_pi_100k      ();
  bool example003_zeta          ();
  bool example004_bessel_recur  ();
  bool example005_polylog_series();

  } } // namespace math::wide_decimal

#endif // DECWIDE_T_2004_06_01_H_
