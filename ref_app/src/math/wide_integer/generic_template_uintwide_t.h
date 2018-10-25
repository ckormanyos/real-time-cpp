#ifndef GENERIC_TEMPLATE_UINTWIDE_T_2018_10_02_H_
  #define GENERIC_TEMPLATE_UINTWIDE_T_2018_10_02_H_

  ///////////////////////////////////////////////////////////////////
  //  Copyright Christopher Kormanyos 1999 - 2018.                 //
  //  Distributed under the Boost Software License,                //
  //  Version 1.0. (See accompanying file LICENSE_1_0.txt          //
  //  or copy at http://www.boost.org/LICENSE_1_0.txt)             //
  ///////////////////////////////////////////////////////////////////

  #include <algorithm>
  #include <array>
  #include <cstddef>
  #include <cstdint>
  #include <limits>
  #include <type_traits>

  #if defined(WIDE_INTEGER_DISABLE_IOSTREAM)
  #else
  #include <iomanip>
  #include <istream>
  #include <ostream>
  #include <sstream>
  #endif

  namespace wide_integer { namespace generic_template {
  // Forward declaration.
  template<const std::size_t Digits2,
           typename ST = std::uint32_t,
           typename LT = std::uint64_t>
  class uintwide_t;

  // Forward declarations of non-member binary add, sub, mul, div, mod of (uintwide_t op IntegralType).
  template<typename IntegralType, const std::size_t Digits2, typename ST, typename LT>
  typename std::enable_if<(   (std::is_fundamental<IntegralType>::value == true)
                           && (std::is_integral   <IntegralType>::value == true)), uintwide_t<Digits2, ST, LT>>::type
  operator+(const uintwide_t<Digits2, ST, LT>& u, const IntegralType& v);

  template<typename IntegralType, const std::size_t Digits2, typename ST, typename LT>
  typename std::enable_if<(   (std::is_fundamental<IntegralType>::value == true)
                           && (std::is_integral   <IntegralType>::value == true)), uintwide_t<Digits2, ST, LT>>::type
  operator-(const uintwide_t<Digits2, ST, LT>& u, const IntegralType& v);

  template<typename IntegralType, const std::size_t Digits2, typename ST, typename LT>
  typename std::enable_if<(   (std::is_fundamental<IntegralType>::value == true)
                           && (std::is_integral   <IntegralType>::value == true)), uintwide_t<Digits2, ST, LT>>::type
  operator*(const uintwide_t<Digits2, ST, LT>& u, const IntegralType& v);

  template<typename IntegralType, const std::size_t Digits2, typename ST, typename LT>
  typename std::enable_if<(   (std::is_fundamental<IntegralType>::value == true)
                           && (std::is_integral   <IntegralType>::value == true)), uintwide_t<Digits2, ST, LT>>::type
  operator/(const uintwide_t<Digits2, ST, LT>& u, const IntegralType& v);

  template<typename IntegralType, const std::size_t Digits2, typename ST, typename LT>
  typename std::enable_if<(   (std::is_fundamental<IntegralType>::value == true)
                           && (std::is_integral   <IntegralType>::value == true)), uintwide_t<Digits2, ST, LT>>::type
  operator%(const uintwide_t<Digits2, ST, LT>& u, const IntegralType& v);

  // Forward declarations of non-member binary add, sub, mul, div, mod of (IntegralType op uintwide_t).
  template<typename IntegralType, const std::size_t Digits2, typename ST, typename LT>
  typename std::enable_if<(   (std::is_fundamental<IntegralType>::value == true)
                           && (std::is_integral   <IntegralType>::value == true)), uintwide_t<Digits2, ST, LT>>::type
  operator+(const IntegralType& u, const uintwide_t<Digits2, ST, LT>& v);

  template<typename IntegralType, const std::size_t Digits2, typename ST, typename LT>
  typename std::enable_if<(   (std::is_fundamental<IntegralType>::value == true)
                           && (std::is_integral   <IntegralType>::value == true)), uintwide_t<Digits2, ST, LT>>::type
  operator-(const IntegralType& u, const uintwide_t<Digits2, ST, LT>& v);

  template<typename IntegralType, const std::size_t Digits2, typename ST, typename LT>
  typename std::enable_if<(   (std::is_fundamental<IntegralType>::value == true)
                           && (std::is_integral   <IntegralType>::value == true)), uintwide_t<Digits2, ST, LT>>::type
  operator*(const IntegralType& u, const uintwide_t<Digits2, ST, LT>& v);

  template<typename IntegralType, const std::size_t Digits2, typename ST, typename LT>
  typename std::enable_if<(   (std::is_fundamental<IntegralType>::value == true)
                           && (std::is_integral   <IntegralType>::value == true)), uintwide_t<Digits2, ST, LT>>::type
  operator/(const IntegralType& u, const uintwide_t<Digits2, ST, LT>& v);

  template<typename IntegralType, const std::size_t Digits2, typename ST, typename LT>
  typename std::enable_if<(   (std::is_fundamental<IntegralType>::value == true)
                           && (std::is_integral   <IntegralType>::value == true)), uintwide_t<Digits2, ST, LT>>::type
  operator%(const IntegralType& u, const uintwide_t<Digits2, ST, LT>& v);

  // Forward declarations of non-member binary logic operations of (uintwide_t op IntegralType).
  template<typename IntegralType, const std::size_t Digits2, typename ST, typename LT>
  typename std::enable_if<(   (std::is_fundamental<IntegralType>::value == true)
                           && (std::is_integral   <IntegralType>::value == true)), uintwide_t<Digits2, ST, LT>>::type
  operator|(const uintwide_t<Digits2, ST, LT>& u, const IntegralType& v);

  template<typename IntegralType, const std::size_t Digits2, typename ST, typename LT>
  typename std::enable_if<(   (std::is_fundamental<IntegralType>::value == true)
                           && (std::is_integral   <IntegralType>::value == true)), uintwide_t<Digits2, ST, LT>>::type
  operator^(const uintwide_t<Digits2, ST, LT>& u, const IntegralType& v);

  template<typename IntegralType, const std::size_t Digits2, typename ST, typename LT>
  typename std::enable_if<(   (std::is_fundamental<IntegralType>::value == true)
                           && (std::is_integral   <IntegralType>::value == true)), uintwide_t<Digits2, ST, LT>>::type
  operator&(const uintwide_t<Digits2, ST, LT>& u, const IntegralType& v);

  // Forward declarations of non-member binary binary logic operations of (IntegralType op uintwide_t).
  template<typename IntegralType, const std::size_t Digits2, typename ST, typename LT>
  typename std::enable_if<(   (std::is_fundamental<IntegralType>::value == true)
                           && (std::is_integral   <IntegralType>::value == true)), uintwide_t<Digits2, ST, LT>>::type
  operator|(const IntegralType& u, const uintwide_t<Digits2, ST, LT>& v);

  template<typename IntegralType, const std::size_t Digits2, typename ST, typename LT>
  typename std::enable_if<(   (std::is_fundamental<IntegralType>::value == true)
                           && (std::is_integral   <IntegralType>::value == true)), uintwide_t<Digits2, ST, LT>>::type
  operator^(const IntegralType& u, const uintwide_t<Digits2, ST, LT>& v);

  template<typename IntegralType, const std::size_t Digits2, typename ST, typename LT>
  typename std::enable_if<(   (std::is_fundamental<IntegralType>::value == true)
                           && (std::is_integral   <IntegralType>::value == true)), uintwide_t<Digits2, ST, LT>>::type
  operator&(const IntegralType& u, const uintwide_t<Digits2, ST, LT>& v);

  // Forward declarations of non-member shift functions of (uintwide_t shift IntegralType).
  template<typename IntegralType, const std::size_t Digits2, typename ST, typename LT>
  typename std::enable_if<(   (std::is_fundamental<IntegralType>::value == true)
                           && (std::is_integral   <IntegralType>::value == true)), uintwide_t<Digits2, ST, LT>>::type
  operator<<(const uintwide_t<Digits2, ST, LT>& u, const IntegralType n);

  template<typename IntegralType, const std::size_t Digits2, typename ST, typename LT>
  typename std::enable_if<(   (std::is_fundamental<IntegralType>::value == true)
                           && (std::is_integral   <IntegralType>::value == true)), uintwide_t<Digits2, ST, LT>>::type
  operator>>(const uintwide_t<Digits2, ST, LT>& u, const IntegralType n);

  // Forward declarations of non-member comparison functions of (uintwide_t cmp IntegralType).
  template<typename IntegralType, const std::size_t Digits2, typename ST, typename LT>
  typename std::enable_if<(   (std::is_fundamental<IntegralType>::value == true)
                           && (std::is_integral   <IntegralType>::value == true)), bool>::type
  operator==(const uintwide_t<Digits2, ST, LT>& u, const IntegralType& v);

  template<typename IntegralType, const std::size_t Digits2, typename ST, typename LT>
  typename std::enable_if<(   (std::is_fundamental<IntegralType>::value == true)
                           && (std::is_integral   <IntegralType>::value == true)), bool>::type
  operator!=(const uintwide_t<Digits2, ST, LT>& u, const IntegralType& v);

  template<typename IntegralType, const std::size_t Digits2, typename ST, typename LT>
  typename std::enable_if<(   (std::is_fundamental<IntegralType>::value == true)
                           && (std::is_integral   <IntegralType>::value == true)), bool>::type
  operator> (const uintwide_t<Digits2, ST, LT>& u, const IntegralType& v);

  template<typename IntegralType, const std::size_t Digits2, typename ST, typename LT>
  typename std::enable_if<(   (std::is_fundamental<IntegralType>::value == true)
                           && (std::is_integral   <IntegralType>::value == true)), bool>::type
  operator< (const uintwide_t<Digits2, ST, LT>& u, const IntegralType& v);

  template<typename IntegralType, const std::size_t Digits2, typename ST, typename LT>
  typename std::enable_if<(   (std::is_fundamental<IntegralType>::value == true)
                           && (std::is_integral   <IntegralType>::value == true)), bool>::type
  operator>=(const uintwide_t<Digits2, ST, LT>& u, const IntegralType& v);

  template<typename IntegralType, const std::size_t Digits2, typename ST, typename LT>
  typename std::enable_if<(   (std::is_fundamental<IntegralType>::value == true)
                           && (std::is_integral   <IntegralType>::value == true)), bool>::type
  operator<=(const uintwide_t<Digits2, ST, LT>& u, const IntegralType& v);

  // Forward declarations of non-member comparison functions of (IntegralType cmp uintwide_t).
  template<typename IntegralType, const std::size_t Digits2, typename ST, typename LT>
  typename std::enable_if<(   (std::is_fundamental<IntegralType>::value == true)
                           && (std::is_integral   <IntegralType>::value == true)), bool>::type
  operator==(const IntegralType& u, const uintwide_t<Digits2, ST, LT>& v);

  template<typename IntegralType, const std::size_t Digits2, typename ST, typename LT>
  typename std::enable_if<(   (std::is_fundamental<IntegralType>::value == true)
                           && (std::is_integral   <IntegralType>::value == true)), bool>::type
  operator!=(const IntegralType& u, const uintwide_t<Digits2, ST, LT>& v);

  template<typename IntegralType, const std::size_t Digits2, typename ST, typename LT>
  typename std::enable_if<(   (std::is_fundamental<IntegralType>::value == true)
                           && (std::is_integral   <IntegralType>::value == true)), bool>::type
  operator> (const IntegralType& u, const uintwide_t<Digits2, ST, LT>& v);

  template<typename IntegralType, const std::size_t Digits2, typename ST, typename LT>
  typename std::enable_if<(   (std::is_fundamental<IntegralType>::value == true)
                           && (std::is_integral   <IntegralType>::value == true)), bool>::type
  operator< (const IntegralType& u, const uintwide_t<Digits2, ST, LT>& v);

  template<typename IntegralType, const std::size_t Digits2, typename ST, typename LT>
  typename std::enable_if<(   (std::is_fundamental<IntegralType>::value == true)
                           && (std::is_integral   <IntegralType>::value == true)), bool>::type
  operator>=(const IntegralType& u, const uintwide_t<Digits2, ST, LT>& v);

  template<typename IntegralType, const std::size_t Digits2, typename ST, typename LT>
  typename std::enable_if<(   (std::is_fundamental<IntegralType>::value == true)
                           && (std::is_integral   <IntegralType>::value == true)), bool>::type
  operator<=(const IntegralType& u, const uintwide_t<Digits2, ST, LT>& v);

  #if defined(WIDE_INTEGER_DISABLE_IOSTREAM)
  #else

  // Forward declarations of I/O streaming functions.
  template<typename char_type,
           typename traits_type,
           const std::size_t Digits2,
           typename ST,
           typename LT>
  std::basic_ostream<char_type, traits_type>& operator<<(std::basic_ostream<char_type, traits_type>& out, const uintwide_t<Digits2, ST, LT>& x);

  template<typename char_type,
           typename traits_type,
           const std::size_t Digits2,
           typename ST,
           typename LT>
  std::basic_istream<char_type, traits_type>& operator>>(std::basic_istream<char_type, traits_type>& in, uintwide_t<Digits2, ST, LT>& x);

  #endif

  } } // namespace wide_integer::generic_template

  namespace std
  {
    // Forward declaration: Support for numeric_limits<>.
    template<const std::size_t Digits2,
             typename ST,
             typename LT>
    class numeric_limits<wide_integer::generic_template::uintwide_t<Digits2, ST, LT>>;
  }

  namespace wide_integer { namespace generic_template { namespace detail {

  // A local implementation of string copy.
  inline char* strcpy_unsafe(char* dst, const char* src)
  {
    while((*dst++ = *src++) != char('\0')) { ; }

    return dst;
  }

  // A local implementation of string length.
  inline std::size_t strlen_unsafe(const char* p_str)
  {
    const char* p_str_copy;

    for(p_str_copy = p_str; (*p_str_copy != char('\0')); ++p_str_copy) { ; }

    return std::size_t(p_str_copy - p_str);
  }

  // From an unsigned integral input parameter of type LT,
  // extract the low part of it. The type of the extracted
  // low part is ST, which has half the width of LT.
  template<typename ST, typename LT>
  ST make_lo(const LT& u)
  {
    using local_ushort_type = ST;
    using local_ularge_type = LT;

    // Compile-time checks.
    static_assert((    (std::numeric_limits<local_ushort_type>::is_integer == true)
                   &&  (std::numeric_limits<local_ularge_type>::is_integer == true)
                   &&  (std::numeric_limits<local_ushort_type>::is_signed  == false)
                   &&  (std::numeric_limits<local_ularge_type>::is_signed  == false)
                   && ((std::numeric_limits<local_ushort_type>::digits * 2) == std::numeric_limits<local_ularge_type>::digits)),
                   "Error: Please check the characteristics of ushort_type and ularge_type");

    return static_cast<local_ushort_type>(u);
  }

  // From an unsigned integral input parameter of type LT,
  // extract the high part of it. The type of the extracted
  // high part is ST, which has half the width of LT.
  template<typename ST, typename LT>
  ST make_hi(const LT& u)
  {
    using local_ushort_type = ST;
    using local_ularge_type = LT;

    // Compile-time checks.
    static_assert((    (std::numeric_limits<local_ushort_type>::is_integer == true)
                   &&  (std::numeric_limits<local_ularge_type>::is_integer == true)
                   &&  (std::numeric_limits<local_ushort_type>::is_signed  == false)
                   &&  (std::numeric_limits<local_ularge_type>::is_signed  == false)
                   && ((std::numeric_limits<local_ushort_type>::digits * 2) == std::numeric_limits<local_ularge_type>::digits)),
                   "Error: Please check the characteristics of ushort_type and ularge_type");

    return static_cast<local_ushort_type>(u >> std::numeric_limits<local_ushort_type>::digits);
  }

  // Create a composite unsigned integral value having type LT.
  // Two constituents are used having type ST, whereby the
  // width of ST is half the width of LT.
  template<typename ST, typename LT>
  LT make_large(const ST& lo, const ST& hi)
  {
    using local_ushort_type = ST;
    using local_ularge_type = LT;

    // Compile-time checks.
    static_assert((    (std::numeric_limits<local_ushort_type>::is_integer == true)
                   &&  (std::numeric_limits<local_ularge_type>::is_integer == true)
                   &&  (std::numeric_limits<local_ushort_type>::is_signed  == false)
                   &&  (std::numeric_limits<local_ularge_type>::is_signed  == false)
                   && ((std::numeric_limits<local_ushort_type>::digits * 2) == std::numeric_limits<local_ularge_type>::digits)),
                   "Error: Please check the characteristics of ushort_type and ularge_type");

    return local_ularge_type(local_ularge_type(static_cast<local_ularge_type>(hi) << std::numeric_limits<ST>::digits) | lo);
  }

  template<const std::size_t Digits2>
  struct verify_power_of_two
  {
    static const bool conditional_value =
      ((Digits2 != 0U) && ((Digits2 & (Digits2 - 1U)) == 0U));
  };

  template<typename SignedIntegralType>   struct uint_type_helper                { using exact_unsigned_type = std::uintmax_t; };
  template<>                              struct uint_type_helper<std::int8_t>   { using exact_unsigned_type = std::uint8_t; };
  template<>                              struct uint_type_helper<std::int16_t>  { using exact_unsigned_type = std::uint16_t; };
  template<>                              struct uint_type_helper<std::int32_t>  { using exact_unsigned_type = std::uint32_t; };
  template<>                              struct uint_type_helper<std::int64_t>  { using exact_unsigned_type = std::uint64_t; };

  template<typename UnsignedIntegralType> struct sint_type_helper                { using exact_signed_type   = std::intmax_t; };
  template<>                              struct sint_type_helper<std::uint8_t>  { using exact_signed_type   = std::int8_t; };
  template<>                              struct sint_type_helper<std::uint16_t> { using exact_signed_type   = std::int16_t; };
  template<>                              struct sint_type_helper<std::uint32_t> { using exact_signed_type   = std::int32_t; };
  template<>                              struct sint_type_helper<std::uint64_t> { using exact_signed_type   = std::int64_t; };

  } } } // namespace wide_integer::generic_template::detail

  namespace wide_integer { namespace generic_template {

  template<const std::size_t Digits2,
           typename ST,
           typename LT>
  class uintwide_t
  {
  public:
    // Verify that the Digits2 template parameter is a power of 2.
    static_assert(detail::verify_power_of_two<Digits2>::conditional_value == true,
                  "Error: The Digits2 template parameter must be a power of 2");

    // Class-local type definitions.
    using ushort_type = ST;
    using ularge_type = LT;

    // More compile-time checks.
    static_assert((    (std::numeric_limits<ushort_type>::is_integer == true)
                   &&  (std::numeric_limits<ularge_type>::is_integer == true)
                   &&  (std::numeric_limits<ushort_type>::is_signed  == false)
                   &&  (std::numeric_limits<ularge_type>::is_signed  == false)
                   && ((std::numeric_limits<ushort_type>::digits * 2) == std::numeric_limits<ularge_type>::digits)),
                   "Error: Please check the characteristics of ushort_type and ularge_type");

    // Helper constants for the digit characteristics.
    static const std::size_t my_digits   = Digits2;
    static const std::size_t my_digits10 = static_cast<int>((std::uintmax_t(my_digits) * UINTMAX_C(301)) / 1000U);

    // The number of limbs.
    static const std::size_t number_of_limbs =
      std::size_t(my_digits / std::size_t(std::numeric_limits<ushort_type>::digits));

    // The type of the internal data representation.
    using representation_type = std::array<ushort_type, number_of_limbs>;

    // Types that have half or double the width of *this.
    using half_width_type   = uintwide_t<my_digits / 2U, ST, LT>;
    using double_width_type = uintwide_t<my_digits * 2U, ST, LT>;

    // Define the maximum buffer sizes for extracting
    // octal, decimal and hexadecimal string representations.
    static const std::size_t wr_string_max_buffer_size_oct = (16U + (my_digits / 3U)) + std::size_t(((my_digits % 3U) != 0U) ? 1U : 0U) + 1U;
    static const std::size_t wr_string_max_buffer_size_hex = (32U + (my_digits / 4U)) + 1U;
    static const std::size_t wr_string_max_buffer_size_dec = (20U + std::size_t((std::uintmax_t(my_digits) * UINTMAX_C(301)) / UINTMAX_C(1000))) + 1U;

    // Default destructor.
    ~uintwide_t() = default;

    // Default constructor.
    uintwide_t() = default;

    // Constructors from built-in unsigned integral types that
    // are less wide than ushort_type or exactly as wide as ushort_type.
    template<typename UnsignedIntegralType>
    uintwide_t(const UnsignedIntegralType v,
               typename std::enable_if<(   (std::is_fundamental<UnsignedIntegralType>::value == true)
                                        && (std::is_integral   <UnsignedIntegralType>::value == true)
                                        && (std::is_unsigned   <UnsignedIntegralType>::value == true)
                                        && (   std::numeric_limits<UnsignedIntegralType>::digits
                                            <= std::numeric_limits<ushort_type         >::digits))>::type* = nullptr)
    {
      values[0U] = ushort_type(v);

      std::fill(values.begin() + 1U, values.end(), ushort_type(0U));
    }

    // Constructors from built-in unsigned integral types that
    // are wider than ushort_type, and do not have exactly the
    // same width as ushort_type.
    template<typename UnsignedIntegralType>
    uintwide_t(const UnsignedIntegralType v,
               typename std::enable_if<(   (std::is_fundamental<UnsignedIntegralType>::value == true)
                                        && (std::is_integral   <UnsignedIntegralType>::value == true)
                                        && (std::is_unsigned   <UnsignedIntegralType>::value == true)
                                        && (  std::numeric_limits<ushort_type         >::digits
                                            < std::numeric_limits<UnsignedIntegralType>::digits))>::type* = nullptr)
    {
      std::uint_fast32_t right_shift_amount_v = 0U;
      std::uint_fast8_t  index_u              = 0U;

      for( ; (index_u < values.size()) && (right_shift_amount_v < std::uint_fast32_t(std::numeric_limits<UnsignedIntegralType>::digits)); ++index_u)
      {
        values[index_u] = ushort_type(v >> (int) right_shift_amount_v);

        right_shift_amount_v += std::uint_fast32_t(std::numeric_limits<ushort_type>::digits);
      }

      std::fill(values.begin() + index_u, values.end(), ushort_type(0U));
    }

    // Constructors from built-in signed integral types.
    template<typename SignedIntegralType>
    uintwide_t(const SignedIntegralType v,
               typename std::enable_if<(   (std::is_fundamental<SignedIntegralType>::value == true)
                                        && (std::is_integral   <SignedIntegralType>::value == true)
                                        && (std::is_signed     <SignedIntegralType>::value == true))>::type* = nullptr)
    {
      const bool is_neg = (v < SignedIntegralType(0));

      using local_unsigned_type =
        typename detail::uint_type_helper<SignedIntegralType>::exact_unsigned_type;

      const local_unsigned_type u =
        ((is_neg == false) ? local_unsigned_type(v) : local_unsigned_type(-v));

      operator=(uintwide_t(u));

      if(is_neg) { negate(); }
    }

    // Constructor from the internal data representation.
    uintwide_t(const representation_type& rep)
    {
      std::copy(rep.cbegin(), rep.cend(), values.begin());
    }

    // Constructor from an initialization list (C-style array).
    template<const std::size_t N>
    uintwide_t(const ushort_type(&init)[N])
    {
      static_assert(N <= number_of_limbs,
                    "Error: The initialization list has too many elements.");

      std::copy(init, init + (std::min)(N, number_of_limbs), values.begin());
    }

    // Copy constructor.
    uintwide_t(const uintwide_t& other)
    {
      std::copy(other.values.cbegin(), other.values.cend(), values.begin());
    }

    // Constructor from the double-width type.
    // This constructor is explicit because it
    // is a narrowing conversion.
    template<typename UnknownUnsignedWideIntegralType = double_width_type>
    explicit uintwide_t(const UnknownUnsignedWideIntegralType& v,
                        typename std::enable_if<(   (std::is_same<UnknownUnsignedWideIntegralType, double_width_type>::value == true)
                                                 && (my_digits >= 128U))>::type* = nullptr)
    {
      std::copy(v.crepresentation().cbegin(),
                v.crepresentation().cbegin() + (v.crepresentation().size() / 2U),
                values.begin());
    }

    // Constructor from constant character string.
    uintwide_t(const char* str_input)
    {
      if(rd_string(str_input) == false)
      {
        std::fill(values.begin(), values.end(), (std::numeric_limits<ushort_type>::max)());
      }
    }

    // Move constructor.
    uintwide_t(uintwide_t&& other) : values(static_cast<representation_type&&>(other.values)) { }

    // Assignment operator.
    uintwide_t& operator=(const uintwide_t& other)
    {
      if(this != &other)
      {
        std::copy(other.values.cbegin(), other.values.cend(), values.begin());
      }

      return *this;
    }

    // Trivial move assignment operator.
    uintwide_t& operator=(uintwide_t&& other)
    {
      std::copy(other.values.cbegin(), other.values.cend(), values.begin());

      return *this;
    }

    // Implement a cast operator that casts to ushort_type
    // or any built-in unsigned integral type that is less wide
    // than ushort_type.
    template<typename UnknownUnsignedBuiltInIntegralType,
             typename = typename std::enable_if<(   (std::is_fundamental<UnknownUnsignedBuiltInIntegralType>::value == true)
                                                 && (std::is_integral   <UnknownUnsignedBuiltInIntegralType>::value == true)
                                                 && (std::is_unsigned   <UnknownUnsignedBuiltInIntegralType>::value == true)
                                                 && (std::numeric_limits<UnknownUnsignedBuiltInIntegralType>::digits <= std::numeric_limits<ushort_type>::digits))>::type>
    operator UnknownUnsignedBuiltInIntegralType() const
    {
      return UnknownUnsignedBuiltInIntegralType(values[0U]);
    }

    // Implement a cast operator that casts to ularge_type.
    template<typename UnknownUnsignedBuiltInIntegralType,
             typename = typename std::enable_if<(   std::numeric_limits<UnknownUnsignedBuiltInIntegralType>::digits >  std::numeric_limits<ushort_type>::digits
                                                 && std::numeric_limits<UnknownUnsignedBuiltInIntegralType>::digits <= std::numeric_limits<ularge_type>::digits)>::type>
    operator ularge_type() const
    {
      return detail::make_large<ushort_type, ularge_type>(values[0U], values[1U]);
    }

    // Implement cast operators that cast to built-in
    // signed integral types having less width than *this.
    operator typename detail::sint_type_helper<ushort_type>::exact_signed_type() const { return typename detail::sint_type_helper<ushort_type>::exact_signed_type(values[0U]); }
    operator typename detail::sint_type_helper<ularge_type>::exact_signed_type() const { return typename detail::sint_type_helper<ularge_type>::exact_signed_type(detail::make_large<ushort_type, ularge_type>(values[0U], values[1U])); }

    // Implement the cast operator that casts to the double-width type.
    template<typename UnknownUnsignedWideIntegralType = double_width_type,
             typename = typename std::enable_if<(   (std::is_same<UnknownUnsignedWideIntegralType, double_width_type>::value == true)
                                                 && (my_digits >= 128U))>::type>
    operator double_width_type() const
    {
      double_width_type my_double_width_instance;

      std::copy(values.cbegin(),
                values.cend(),
                my_double_width_instance.representation().begin());

      std::fill(my_double_width_instance.representation().begin() + number_of_limbs,
                my_double_width_instance.representation().end(),
                ushort_type(0U));

      return my_double_width_instance;
    }

    // Implement the Boolean cast operator that tests for zero/non-zero.
    // This cast operator returns true if the value of *this is non-zero.
    operator bool() const
    {
      return (is_zero() == false);
    }

    // Purposely delete the cast operator that casts to the half-width type.
    // This cast is deleted because it is a narrowing conversion.
    // There is an explicit constructor above for this conversion.
    template<typename UnknownUnsignedWideIntegralType = half_width_type,
             typename = typename std::enable_if<std::is_same<UnknownUnsignedWideIntegralType, half_width_type>::value == true>::type>
    operator half_width_type() const = delete;

    // Provide a user interface to the internal data representation.
          representation_type&  representation()       { return values; }
    const representation_type&  representation() const { return values; }
    const representation_type& crepresentation() const { return values; }

    // Unary operators: not, plus and minus.
    bool        operator!() const { return is_zero(); }
    uintwide_t& operator+() const { return *this; }
    uintwide_t  operator-() const { const uintwide_t tmp(*this); tmp.negate(); return tmp; }

    uintwide_t& operator+=(const uintwide_t& other)
    {
      // Unary addition function.
      std::array<ularge_type, number_of_limbs> result_as_ularge_array;

      ushort_type carry(0U);

      for(std::size_t i = 0U; i < number_of_limbs; ++i)
      {
        result_as_ularge_array[i] = ularge_type(ularge_type(values[i]) + other.values[i]) + carry;

        carry = detail::make_hi<ushort_type, ularge_type>(result_as_ularge_array[i]);

        values[i] = ushort_type(result_as_ularge_array[i]);
      }

      return *this;
    }

    uintwide_t& operator-=(const uintwide_t& other)
    {
      // Unary subtraction function.
      std::array<ularge_type, number_of_limbs> result_as_ularge_array;

      bool has_borrow = false;

      for(std::size_t i = 0U; i < number_of_limbs; ++i)
      {
        result_as_ularge_array[i] = ularge_type(values[i]) - other.values[i];

        if(has_borrow) { --result_as_ularge_array[i]; }

        has_borrow = (detail::make_hi<ushort_type, ularge_type>(result_as_ularge_array[i]) != ushort_type(0U));

        values[i] = ushort_type(result_as_ularge_array[i]);
      }

      return *this;
    }

    uintwide_t& operator*=(const uintwide_t& other)
    {
      // Unary multiplication function.
      std::array<ushort_type, number_of_limbs> w = {{ 0U }};

      multiplication_loop_schoolbook(values.data(),
                                     other.values.data(),
                                     w.data(),
                                     w.size());

      std::copy(w.cbegin(), w.cend(), values.begin());

      return *this;
    }

    uintwide_t& operator/=(const uintwide_t& other)
    {
      // Unary division function.
      quotient_and_remainder_knuth(other);

      return *this;
    }

    uintwide_t& operator%=(const uintwide_t& other)
    {
      // Unary modulus function.
      uintwide_t remainder;

      quotient_and_remainder_knuth(other, &remainder);

      std::copy(remainder.values.cbegin(),
                remainder.values.cend(),
                values.begin());

      return *this;
    }

    // Operators pre-increment and pre-decrement.
    uintwide_t& operator++() { preincrement(); return *this; }
    uintwide_t& operator--() { predecrement(); return *this; }

    // Operators post-increment and post-decrement.
    uintwide_t operator++(int) { uintwide_t w(*this); preincrement(); return w; }
    uintwide_t operator--(int) { uintwide_t w(*this); predecrement(); return w; }

    uintwide_t& operator~()
    {
      bitwise_not();

      return *this;
    }

    uintwide_t& operator|=(const uintwide_t& other)
    {
      // Bitwise OR.
      for(std::size_t i = 0U; i < number_of_limbs; ++i)
      {
        values[i] |= other.values[i];
      }

      return *this;
    }

    uintwide_t& operator^=(const uintwide_t& other)
    {
      // Bitwise XOR.
      for(std::size_t i = 0U; i < number_of_limbs; ++i)
      {
        values[i] ^= other.values[i];
      }

      return *this;
    }

    uintwide_t& operator&=(const uintwide_t& other)
    {
      // Bitwise AND.
      for(std::size_t i = 0U; i < number_of_limbs; ++i)
      {
        values[i] &= other.values[i];
      }

      return *this;
    }

    template<typename IntegralType>
    typename std::enable_if<(   (std::is_fundamental<IntegralType>::value == true)
                             && (std::is_integral   <IntegralType>::value == true)), uintwide_t>::type&
    operator<<=(const IntegralType n)
    {
      // Left-shift operator.
      if     (n <  0) { operator>>=(n); }
      else if(n == 0) { ; }
      else
      {
        if(std::size_t(n) >= my_digits)
        {
          operator=(std::uint8_t(0U));
        }
        else
        {
          const std::size_t offset            = std::size_t(n) / std::size_t(std::numeric_limits<ushort_type>::digits);
          const std::size_t left_shift_amount = std::size_t(n) % std::size_t(std::numeric_limits<ushort_type>::digits);

          std::copy_backward(values.data(),
                             values.data() + (number_of_limbs - offset),
                             values.data() +  number_of_limbs);

          std::fill(values.begin(), values.begin() + offset, ushort_type(0U));

          ushort_type part_from_previous_value = ushort_type(0U);

          using local_integral_type = IntegralType;

          if(left_shift_amount != local_integral_type(0U))
          {
            for(std::size_t i = offset; i < number_of_limbs; ++i)
            {
              const ushort_type t = values[i];

              values[i] = (t << local_integral_type(left_shift_amount)) | part_from_previous_value;

              part_from_previous_value = ushort_type(t >> local_integral_type(std::size_t(std::numeric_limits<ushort_type>::digits - left_shift_amount)));
            }
          }
        }
      }

      return *this;
    }

    template<typename IntegralType>
    typename std::enable_if<(   (std::is_fundamental<IntegralType>::value == true)
                             && (std::is_integral   <IntegralType>::value == true)), uintwide_t>::type&
    operator>>=(const IntegralType n)
    {
      // Right-shift operator.
      if     (n <  0) { operator<<=(n); }
      else if(n == 0) { ; }
      else
      {
        if(std::size_t(n) >= my_digits)
        {
          operator=(std::uint8_t(0U));
        }
        else
        {
          const std::size_t offset             = std::size_t(n) / std::size_t(std::numeric_limits<ushort_type>::digits);
          const std::size_t right_shift_amount = std::size_t(n) % std::size_t(std::numeric_limits<ushort_type>::digits);

          std::copy(values.begin() + offset,
                    values.begin() + number_of_limbs,
                    values.begin());

          std::fill(values.rbegin(), values.rbegin() + std::ptrdiff_t(offset), ushort_type(0U));

          ushort_type part_from_previous_value = ushort_type(0U);

          using local_integral_type = IntegralType;

          if(right_shift_amount != local_integral_type(0U))
          {
            for(std::size_t i = ((number_of_limbs - 1U) - offset); std::ptrdiff_t(i) >= 0; --i)
            {
              const ushort_type t = values[i];

              values[i] = (t >> local_integral_type(right_shift_amount)) | part_from_previous_value;

              part_from_previous_value = ushort_type(t << local_integral_type(std::size_t(std::numeric_limits<ushort_type>::digits - right_shift_amount)));
            }
          }
        }
      }

      return *this;
    }

    // Implement comparison operators.
    bool operator==(const uintwide_t& other) const { return (compare(other) == std::int_fast8_t( 0)); }
    bool operator< (const uintwide_t& other) const { return (compare(other) == std::int_fast8_t(-1)); }
    bool operator> (const uintwide_t& other) const { return (compare(other) == std::int_fast8_t( 1)); }
    bool operator!=(const uintwide_t& other) const { return (compare(other) != std::int_fast8_t( 0)); }
    bool operator<=(const uintwide_t& other) const { return (compare(other) <= std::int_fast8_t( 0)); }
    bool operator>=(const uintwide_t& other) const { return (compare(other) >= std::int_fast8_t( 0)); }

    // Helper functions for supporting std::numeric_limits<>.
    static uintwide_t limits_helper_max()
    {
      uintwide_t val;

      std::fill(val.values.begin(),
                val.values.end(),
                (std::numeric_limits<ushort_type>::max)());

      return val;
    }

    static uintwide_t limits_helper_min()
    {
      return uintwide_t(std::uint8_t(0U));
    }

    bool wr_string(      char*             str_result,
                   const std::uint_fast8_t base_rep     = 0x10U,
                   const bool              show_base    = true,
                   const bool              show_pos     = false,
                   const bool              is_uppercase = true,
                         std::size_t       field_width  = 0U,
                   const char              fill_char    = char('0')) const
    {
            uintwide_t t   (*this);
      const uintwide_t zero(std::uint8_t(0U));

      bool wr_string_is_ok = true;

      if(base_rep == 8U)
      {
        const ushort_type mask(std::uint8_t(0x7U));

        char str_temp[wr_string_max_buffer_size_oct];

        std::size_t pos = (sizeof(str_temp) - 1U);

        if(t == zero)
        {
          --pos;

          str_temp[pos] = char('0');
        }
        else
        {
          while(t != zero)
          {
            char c = char(t.values[0U] & mask);

            if(c <= 8) { c += char(0x30); }

            --pos;

            str_temp[pos] = c;

            t >>= 3;
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
          field_width = (std::min)(field_width, std::size_t(sizeof(str_temp) - 1U));

          while(std::ptrdiff_t(pos) > std::ptrdiff_t((sizeof(str_temp) - 1U) - field_width))
          {
            --pos;

            str_temp[pos] = fill_char;
          }
        }

        str_temp[std::size_t(sizeof(str_temp) - 1U)] = char('\0');

        detail::strcpy_unsafe(str_result, str_temp + pos);
      }
      else if(base_rep == 10U)
      {
        char str_temp[wr_string_max_buffer_size_dec];

        std::size_t pos = (sizeof(str_temp) - 1U);

        if(t == zero)
        {
          --pos;

          str_temp[pos] = char('0');
        }
        else
        {
          const uintwide_t ten(std::uint8_t(10U));

          while(t != zero)
          {
            const uintwide_t t_temp(t);

            t /= ten;

            char c = char(ushort_type((t_temp - (t * ten)).values[0U]));

            if(c <= char(9)) { c += char(0x30); }

            --pos;

            str_temp[pos] = c;
          }
        }

        if(show_pos)
        {
          --pos;

          str_temp[pos] = char('+');
        }

        if(field_width != 0U)
        {
          field_width = (std::min)(field_width, std::size_t(sizeof(str_temp) - 1U));

          while(std::ptrdiff_t(pos) > std::ptrdiff_t((sizeof(str_temp) - 1U) - field_width))
          {
            --pos;

            str_temp[pos] = fill_char;
          }
        }

        str_temp[std::size_t(sizeof(str_temp) - 1U)] = char('\0');

        detail::strcpy_unsafe(str_result, str_temp + pos);
      }
      else if(base_rep == 16U)
      {
        const ushort_type mask(std::uint8_t(0xFU));

        char str_temp[wr_string_max_buffer_size_hex];

        std::size_t pos = (sizeof(str_temp) - 1U);

        if(t == zero)
        {
          --pos;

          str_temp[pos] = char('0');
        }
        else
        {
          while(t != zero)
          {
            char c(t.values[0U] & mask);

            if      (c <= char(  9))                      { c += char(0x30); }
            else if((c >= char(0xA)) && (c <= char(0xF))) { c += (is_uppercase ? char(55) : char(87)); }

            --pos;

            str_temp[pos] = c;

            t >>= 4;
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
          field_width = (std::min)(field_width, std::size_t(sizeof(str_temp) - 1U));

          while(std::ptrdiff_t(pos) > std::ptrdiff_t((sizeof(str_temp) - 1U) - field_width))
          {
            --pos;

            str_temp[pos] = fill_char;
          }
        }

        str_temp[std::size_t(sizeof(str_temp) - 1U)] = char('\0');

        detail::strcpy_unsafe(str_result, str_temp + pos);
      }
      else
      {
        wr_string_is_ok = false;
      }

      return wr_string_is_ok;
    }

  private:
    representation_type values;

    bool rd_string(const char* str_input)
    {
      std::fill(values.begin(), values.end(), ushort_type(0U));

      const std::size_t str_length = detail::strlen_unsafe(str_input);

      std::uint_fast8_t base = 10U;

      std::size_t pos = 0U;

      // Skip over a potential plus sign.
      if((str_length > 0U) && (str_input[0U] == char('+')))
      {
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
            if  ((c >= char('0')) && (c <= char('8'))) { c -= std::uint8_t(0x30U); }
            else                                       { char_is_valid = false; }

            if(char_is_valid)
            {
              operator<<=(3);

              values[0U] |= std::uint8_t(c);
            }
          }
          else if(base == 10U)
          {
            if   ((c >= std::uint8_t('0')) && (c <= std::uint8_t('9'))) { c -= std::uint8_t(0x30U); }
            else                                                        { char_is_valid = false; }

            if(char_is_valid)
            {
              operator*=(10U);

              values[0U] += c;
            }
          }
          else if(base == 16U)
          {
            if     ((c >= std::uint8_t('a')) && (c <= std::uint8_t('f'))) { c -= std::uint8_t(  87U); }
            else if((c >= std::uint8_t('A')) && (c <= std::uint8_t('F'))) { c -= std::uint8_t(  55U); }
            else if((c >= std::uint8_t('0')) && (c <= std::uint8_t('9'))) { c -= std::uint8_t(0x30U); }
            else                                                          { char_is_valid = false; }

            if(char_is_valid)
            {
              operator<<=(4);

              values[0U] |= c;
            }
          }
        }
      }

      return char_is_valid;
    }

    static void multiplication_loop_schoolbook(      ushort_type* pu,
                                               const ushort_type* pv,
                                                     ushort_type* pw,
                                               const std::size_t  count)
    {
      for(std::size_t j = 0U; j < count; ++j)
      {
        if(pv[j] != ushort_type(0U))
        {
          ushort_type carry = ushort_type(0U);

          for(std::size_t i = 0U, iplusj = i + j; iplusj < count; ++i, ++iplusj)
          {
            const ularge_type t =
              ularge_type(ularge_type(ularge_type(pu[i]) * pv[j]) + pw[iplusj]) + carry;

            pw[iplusj] = detail::make_lo<ushort_type, ularge_type>(t);
            carry      = detail::make_hi<ushort_type, ularge_type>(t);
          }
        }
      }
    }

    void quotient_and_remainder_knuth(const uintwide_t& other, uintwide_t* remainder = nullptr)
    {
      // TBD: Consider cleaning up the unclear flow-control
      // caused by numerous return statements in this subroutine.

      // Use Knuth's long division algorithm.
      // The loop-ordering of indexes in Knuth's original
      // algorithm has been reversed due to the little-endian
      // data format used here.

      // See also:
      // D.E. Knuth, "The Art of Computer Programming, Volume 2:
      // Seminumerical Algorithms", Addison-Wesley (1998),
      // Section 4.3.1 Algorithm D and Exercise 16.

      using local_uint_index_type = std::size_t;

      local_uint_index_type u_offset = local_uint_index_type(0U);
      local_uint_index_type v_offset = local_uint_index_type(0U);

      // Compute the offsets for u and v.
      for(local_uint_index_type i = 0U; (i < number_of_limbs) && (      values[(number_of_limbs - 1U) - i] == ushort_type(0U)); ++i) { ++u_offset; }
      for(local_uint_index_type i = 0U; (i < number_of_limbs) && (other.values[(number_of_limbs - 1U) - i] == ushort_type(0U)); ++i) { ++v_offset; }

      if(v_offset == local_uint_index_type(number_of_limbs))
      {
        // The denominator is zero. Set the maximum value and return.
        // This also catches (0 / 0) and sets the maximum value for it.
        operator=(limits_helper_max());

        if(remainder != nullptr)
        {
          *remainder = uintwide_t(std::uint8_t(0U));
        }

        return;
      }

      if(u_offset == local_uint_index_type(number_of_limbs))
      {
        // The numerator is zero. Do nothing and return.

        if(remainder != nullptr)
        {
          *remainder = uintwide_t(std::uint8_t(0U));
        }

        return;
      }

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
          }

          operator=(std::uint8_t(0U));

          return;
        }

        if(left_is_equal_to_right)
        {
          // If the denominator is equal to the numerator,
          // then the result of the division is one.
          operator=(std::uint8_t(1U));

          if(remainder != nullptr)
          {
            *remainder = uintwide_t(std::uint8_t(0U));
          }

          return;
        }
      }

      if(v_offset == local_uint_index_type(number_of_limbs - 1U))
      {
        // The denominator has one single limb.
        // Use a one-dimensional division algorithm.

              ularge_type long_numerator    = ularge_type(0U);
        const ushort_type short_denominator = other.values[0U];

        ushort_type hi_part = ushort_type(0U);

        for(local_uint_index_type i = local_uint_index_type((number_of_limbs - 1U) - u_offset); std::ptrdiff_t(i) >= 0; --i)
        {
          long_numerator = ularge_type(values[i]) + ((long_numerator - ularge_type(ularge_type(short_denominator) * hi_part)) << std::numeric_limits<ushort_type>::digits);

          values[i] = detail::make_lo<ushort_type, ularge_type>(ularge_type(long_numerator / short_denominator));

          hi_part = values[i];
        }

        if(remainder != nullptr)
        {
          long_numerator = ularge_type(values[0U]) + ((long_numerator - ularge_type(ularge_type(short_denominator) * hi_part)) << std::numeric_limits<ushort_type>::digits);

          *remainder = ushort_type(long_numerator >> std::numeric_limits<ushort_type>::digits);

          if(u_offset != 0U)
          {
            std::fill(values.begin() + std::size_t((number_of_limbs - 1U) - u_offset),
                      values.end(),
                      ushort_type(0U));
          }
        }

        return;
      }

      // We will now use the Knuth long division algorithm.
      {
        // Compute the normalization factor d.
        const ushort_type d =
          detail::make_lo<ushort_type, ularge_type>(  ((ularge_type(std::uint8_t(1U))) << std::numeric_limits<ushort_type>::digits)
                                                    /   ularge_type(ularge_type(other.values[(number_of_limbs - 1U) - v_offset]) + ushort_type(1U)));

        // Step D1(b), normalize u -> u * d = uu.
        // Note the added digit in uu and also that
        // the data of uu have not been initialized yet.

        std::array<ushort_type, number_of_limbs + 1U> uu;

        if(d == ushort_type(1U))
        {
          // The normalization is one.
          std::copy(values.cbegin(), values.cend(), uu.begin());

          uu.back() = ushort_type(0U);
        }
        else
        {
          // Multiply u by d.
          ushort_type carry = 0U;

          local_uint_index_type i;

          for(i = local_uint_index_type(0U); i < local_uint_index_type(number_of_limbs - u_offset); ++i)
          {
            const ularge_type t = ularge_type(ularge_type(values[i]) * d) + carry;

            uu[i] = detail::make_lo<ushort_type, ularge_type>(t);
            carry = detail::make_hi<ushort_type, ularge_type>(t);
          }

          uu[i] = carry;
        }

        std::array<ushort_type, number_of_limbs> vv;

        // Step D1(c): normalize v -> v * d = vv.
        if(d == ushort_type(1U))
        {
          // The normalization is one.
          vv = other.values;
        }
        else
        {
          // Multiply v by d.
          ushort_type carry = 0U;

          for(local_uint_index_type i = local_uint_index_type(0U); i < local_uint_index_type(number_of_limbs - v_offset); ++i)
          {
            const ularge_type t = ularge_type(ularge_type(other.values[i]) * d) + carry;

            vv[i] = detail::make_lo<ushort_type, ularge_type>(t);
            carry = detail::make_hi<ushort_type, ularge_type>(t);
          }
        }

        // Step D2: Initialize j.
        // Step D7: Loop on j from m to 0.

        const local_uint_index_type n = local_uint_index_type(number_of_limbs - v_offset);
        const local_uint_index_type m = local_uint_index_type(number_of_limbs - u_offset) - n;

        for(local_uint_index_type j = local_uint_index_type(0U); j <= m; ++j)
        {
          // Step D3 [Calculate q_hat].
          //   if u[j] == v[j0]
          //     set q_hat = b - 1
          //   else
          //     set q_hat = (u[j] * b + u[j + 1]) / v[1]

          const local_uint_index_type uj     = (((number_of_limbs + 1U) - 1U) - u_offset) - j;
          const local_uint_index_type vj0    =   (number_of_limbs       - 1U) - v_offset;
          const ularge_type           u_j_j1 = (ularge_type(uu[uj]) << std::numeric_limits<ushort_type>::digits) + uu[uj - 1U];

          ularge_type q_hat = ((uu[uj] == vv[vj0])
                                ? ularge_type((std::numeric_limits<ushort_type>::max)())
                                : u_j_j1 / ularge_type(vv[vj0]));

          // Decrease q_hat if necessary.
          // This means that q_hat must be decreased if the
          // expression [(u[uj] * b + u[uj - 1] - q_hat * v[vj0 - 1]) * b]
          // exceeds the range of uintwide_t.

          ularge_type t;

          for(;;)
          {
            t = u_j_j1 - ularge_type(q_hat * ularge_type(vv[vj0]));

            if(detail::make_hi<ushort_type, ularge_type>(t) != ushort_type(0U))
            {
              break;
            }

            if(   ularge_type(ularge_type(vv[vj0 - 1U]) * q_hat)
               <= ularge_type((t << std::numeric_limits<ushort_type>::digits) + uu[uj - 2U]))
            {
              break;
            }

            --q_hat;
          }

          // Step D4: Multiply and subtract.
          // Replace u[j, ... j + n] by u[j, ... j + n] - q_hat * v[1, ... n].

          // Set nv = q_hat * (v[1, ... n]).
          {
            std::array<ushort_type, number_of_limbs + 1U> nv;

            ushort_type carry = 0U;

            local_uint_index_type i;

            for(i = local_uint_index_type(0U); i < n; ++i)
            {
              t     = ularge_type(ularge_type(vv[i]) * q_hat) + carry;
              nv[i] = detail::make_lo<ushort_type, ularge_type>(t);
              carry = detail::make_hi<ushort_type, ularge_type>(t);
            }

            nv[i] = carry;

            {
              // Subtract nv[0, ... n] from u[j, ... j + n].
              std::uint_fast8_t     borrow = 0U;
              local_uint_index_type ul     = uj - n;

              for(i = local_uint_index_type(0U); i <= n; ++i, ++ul)
              {
                t      = ularge_type(ularge_type(uu[ul]) - nv[i]) - ushort_type(borrow);
                uu[ul] =   detail::make_lo<ushort_type, ularge_type>(t);
                borrow = ((detail::make_hi<ushort_type, ularge_type>(t) != ushort_type(0U)) ? 1U : 0U);
              }

              // Get the result data.
              values[local_uint_index_type(m - j)] = detail::make_lo<ushort_type, ularge_type>(q_hat);

              // Step D5: Test the remainder.
              // Set the result value: Set result.m_data[m - j] = q_hat.
              // Use the condition (u[j] < 0), in other words if the borrow
              // is non-zero, then step D6 needs to be carried out.

              if(borrow != std::uint_fast8_t(0U))
              {
                // Step D6: Add back.
                // Add v[1, ... n] back to u[j, ... j + n],
                // and decrease the result by 1.

                carry = 0U;
                ul    = uj - n;

                for(i = local_uint_index_type(0U); i <= n; ++i, ++ul)
                {
                  t      = ularge_type(ularge_type(uu[ul]) + vv[i]) + carry;
                  uu[ul] = detail::make_lo<ushort_type, ularge_type>(t);
                  carry  = detail::make_hi<ushort_type, ularge_type>(t);
                }

                // A potential test case for uint512_t is:
                //   QuotientRemainder[698937339790347543053797400564366118744312537138445607919548628175822115805812983955794321304304417541511379093392776018867245622409026835324102460829431,100041341335406267530943777943625254875702684549707174207105689918734693139781]
                --values[local_uint_index_type(m - j)];
              }
            }
          }
        }

        // Clear the data elements that have not
        // been computed in the division algorithm.
        std::fill(values.begin() + (m + 1U), values.end(), ushort_type(0U));

        if(remainder != nullptr)
        {
          if(d == 1)
          {
            std::copy(uu.cbegin(),
                      uu.cbegin() + (number_of_limbs - v_offset),
                      remainder->values.begin());
          }
          else
          {
            ushort_type previous_u = ushort_type(0U);

            for(local_uint_index_type rl = n - 1U, ul = local_uint_index_type(number_of_limbs - (v_offset + 1U)); std::ptrdiff_t(rl) >= 0; --rl, --ul)
            {
              const ularge_type t = ularge_type(uu[ul] + ularge_type(ularge_type(previous_u) << std::numeric_limits<ushort_type>::digits));

              remainder->values[rl] = detail::make_lo<ushort_type, ularge_type>(t / d);
              previous_u            = ushort_type(t - ularge_type(ularge_type(d) * remainder->values[rl]));
            }
          }

          std::fill(remainder->values.begin() + n,
                    remainder->values.end(),
                    ushort_type(0U));
        }
      }
    }

    std::int_fast8_t compare(const uintwide_t& other) const
    {
      std::int_fast8_t return_value;
      std::ptrdiff_t   element_index;

      for(element_index = std::ptrdiff_t(number_of_limbs - 1U); element_index >= std::ptrdiff_t(0); --element_index)
      {
        if(values[std::size_t(element_index)] != other.values[std::size_t(element_index)])
        {
          break;
        }
      }

      if(element_index == std::ptrdiff_t(-1))
      {
        return_value = std::int_fast8_t(0);
      }
      else
      {
        const bool left_is_greater_than_right =
          (values[std::size_t(element_index)] > other.values[std::size_t(element_index)]);

        return_value = (left_is_greater_than_right ? std::int_fast8_t(1) : std::int_fast8_t(-1));
      }

      return return_value;
    }

    void bitwise_not()
    {
      for(std::size_t i = 0U; i < number_of_limbs; ++i)
      {
        values[i] = ushort_type(~values[i]);
      }
    }

    void preincrement()
    {
      // Implement pre-increment.
      std::size_t i = 0U;

      for( ; (i < (values.size() - 1U)) && (++values[i] == ushort_type(0U)); ++i) { ; }

      if(i == (values.size() - 1U)) { ++values[i]; }
    }

    void predecrement()
    {
      // Implement pre-decrement.
      std::size_t i = 0U;

      for( ; (i < (values.size() - 1U)) && (values[i]-- == ushort_type(0U)); ++i) { ; }

      if(i == (values.size() - 1U)) { --values[i]; }
    }

    void negate()
    {
      bitwise_not();

      preincrement();
    }

    bool is_zero() const
    {
      return std::all_of(values.cbegin(),
                         values.cend(),
                         [](const ushort_type& u) -> bool { return u == ushort_type(0U); });
    }
  };

  // Define some convenient unsigned wide integer types.
  using uint64_t   = uintwide_t<  64U, std::uint16_t, std::uint32_t>;
  using uint128_t  = uintwide_t< 128U>;
  using uint256_t  = uintwide_t< 256U>;
  using uint512_t  = uintwide_t< 512U>;
  using uint1024_t = uintwide_t<1024U>;
  using uint2048_t = uintwide_t<2048U>;
  using uint4096_t = uintwide_t<4096U>;
  using uint8192_t = uintwide_t<8192U>;

  // Prepare a base class for numeric_limits<> support.
  template<typename WideUnsignedIntegerType>
  class numeric_limits_base : public std::numeric_limits<unsigned int>
  {
  private:
    using uintwide_type = WideUnsignedIntegerType;

  public:
    static const int digits   = static_cast<int>(uintwide_type::my_digits);
    static const int digits10 = static_cast<int>(uintwide_type::my_digits10);

    static uintwide_type (max)() { return uintwide_type::limits_helper_max(); }
    static uintwide_type (min)() { return uintwide_type::limits_helper_min(); }
  };

  } } // namespace wide_integer::generic_template

  namespace std
  {
    // Specialization of std::numeric_limits<>.
    template<const std::size_t Digits2,
             typename ST,
             typename LT>
    class numeric_limits<wide_integer::generic_template::uintwide_t<Digits2, ST, LT>>
      : public wide_integer::generic_template::numeric_limits_base<wide_integer::generic_template::uintwide_t<Digits2, ST, LT>> { };
  }

  namespace wide_integer { namespace generic_template {

  template<const std::size_t Digits2, typename ST, typename LT> uintwide_t<Digits2, ST, LT> operator+ (const uintwide_t<Digits2, ST, LT>& left, const uintwide_t<Digits2, ST, LT>& right) { return uintwide_t<Digits2, ST, LT>(left).operator+=(right); }
  template<const std::size_t Digits2, typename ST, typename LT> uintwide_t<Digits2, ST, LT> operator- (const uintwide_t<Digits2, ST, LT>& left, const uintwide_t<Digits2, ST, LT>& right) { return uintwide_t<Digits2, ST, LT>(left).operator-=(right); }
  template<const std::size_t Digits2, typename ST, typename LT> uintwide_t<Digits2, ST, LT> operator* (const uintwide_t<Digits2, ST, LT>& left, const uintwide_t<Digits2, ST, LT>& right) { return uintwide_t<Digits2, ST, LT>(left).operator*=(right); }
  template<const std::size_t Digits2, typename ST, typename LT> uintwide_t<Digits2, ST, LT> operator/ (const uintwide_t<Digits2, ST, LT>& left, const uintwide_t<Digits2, ST, LT>& right) { return uintwide_t<Digits2, ST, LT>(left).operator/=(right); }
  template<const std::size_t Digits2, typename ST, typename LT> uintwide_t<Digits2, ST, LT> operator% (const uintwide_t<Digits2, ST, LT>& left, const uintwide_t<Digits2, ST, LT>& right) { return uintwide_t<Digits2, ST, LT>(left).operator%=(right); }

  template<const std::size_t Digits2, typename ST, typename LT> uintwide_t<Digits2, ST, LT> operator| (const uintwide_t<Digits2, ST, LT>& left, const uintwide_t<Digits2, ST, LT>& right) { return uintwide_t<Digits2, ST, LT>(left).operator|=(right); }
  template<const std::size_t Digits2, typename ST, typename LT> uintwide_t<Digits2, ST, LT> operator^ (const uintwide_t<Digits2, ST, LT>& left, const uintwide_t<Digits2, ST, LT>& right) { return uintwide_t<Digits2, ST, LT>(left).operator^=(right); }
  template<const std::size_t Digits2, typename ST, typename LT> uintwide_t<Digits2, ST, LT> operator& (const uintwide_t<Digits2, ST, LT>& left, const uintwide_t<Digits2, ST, LT>& right) { return uintwide_t<Digits2, ST, LT>(left).operator&=(right); }

  // Non-member binary add, sub, mul, div, mod of (uintwide_t op IntegralType).
  template<typename IntegralType, const std::size_t Digits2, typename ST, typename LT>
  typename std::enable_if<(   (std::is_fundamental<IntegralType>::value == true)
                           && (std::is_integral   <IntegralType>::value == true)), uintwide_t<Digits2, ST, LT>>::type
  operator+(const uintwide_t<Digits2, ST, LT>& u, const IntegralType& v) { return uintwide_t<Digits2, ST, LT>(u).operator+=(uintwide_t<Digits2, ST, LT>(v)); }

  template<typename IntegralType, const std::size_t Digits2, typename ST, typename LT>
  typename std::enable_if<(   (std::is_fundamental<IntegralType>::value == true)
                           && (std::is_integral   <IntegralType>::value == true)), uintwide_t<Digits2, ST, LT>>::type
  operator-(const uintwide_t<Digits2, ST, LT>& u, const IntegralType& v) { return uintwide_t<Digits2, ST, LT>(u).operator-=(uintwide_t<Digits2, ST, LT>(v)); }

  template<typename IntegralType, const std::size_t Digits2, typename ST, typename LT>
  typename std::enable_if<(   (std::is_fundamental<IntegralType>::value == true)
                           && (std::is_integral   <IntegralType>::value == true)), uintwide_t<Digits2, ST, LT>>::type
  operator*(const uintwide_t<Digits2, ST, LT>& u, const IntegralType& v) { return uintwide_t<Digits2, ST, LT>(u).operator*=(uintwide_t<Digits2, ST, LT>(v)); }

  template<typename IntegralType, const std::size_t Digits2, typename ST, typename LT>
  typename std::enable_if<(   (std::is_fundamental<IntegralType>::value == true)
                           && (std::is_integral   <IntegralType>::value == true)), uintwide_t<Digits2, ST, LT>>::type
  operator/(const uintwide_t<Digits2, ST, LT>& u, const IntegralType& v) { return uintwide_t<Digits2, ST, LT>(u).operator/=(uintwide_t<Digits2, ST, LT>(v)); }

  template<typename IntegralType, const std::size_t Digits2, typename ST, typename LT>
  typename std::enable_if<(   (std::is_fundamental<IntegralType>::value == true)
                           && (std::is_integral   <IntegralType>::value == true)), uintwide_t<Digits2, ST, LT>>::type
  operator%(const uintwide_t<Digits2, ST, LT>& u, const IntegralType& v) { return uintwide_t<Digits2, ST, LT>(u).operator%=(uintwide_t<Digits2, ST, LT>(v)); }

  // Non-member binary add, sub, mul, div, mod of (IntegralType op uintwide_t).
  template<typename IntegralType, const std::size_t Digits2, typename ST, typename LT>
  typename std::enable_if<(   (std::is_fundamental<IntegralType>::value == true)
                           && (std::is_integral   <IntegralType>::value == true)), uintwide_t<Digits2, ST, LT>>::type
  operator+(const IntegralType& u, const uintwide_t<Digits2, ST, LT>& v) { return uintwide_t<Digits2, ST, LT>(u).operator+=(v); }

  template<typename IntegralType, const std::size_t Digits2, typename ST, typename LT>
  typename std::enable_if<(   (std::is_fundamental<IntegralType>::value == true)
                           && (std::is_integral   <IntegralType>::value == true)), uintwide_t<Digits2, ST, LT>>::type
  operator-(const IntegralType& u, const uintwide_t<Digits2, ST, LT>& v) { return uintwide_t<Digits2, ST, LT>(u).operator-=(v); }

  template<typename IntegralType, const std::size_t Digits2, typename ST, typename LT>
  typename std::enable_if<(   (std::is_fundamental<IntegralType>::value == true)
                           && (std::is_integral   <IntegralType>::value == true)), uintwide_t<Digits2, ST, LT>>::type
  operator*(const IntegralType& u, const uintwide_t<Digits2, ST, LT>& v) { return uintwide_t<Digits2, ST, LT>(u).operator*=(v); }

  template<typename IntegralType, const std::size_t Digits2, typename ST, typename LT>
  typename std::enable_if<(   (std::is_fundamental<IntegralType>::value == true)
                           && (std::is_integral   <IntegralType>::value == true)), uintwide_t<Digits2, ST, LT>>::type
  operator/(const IntegralType& u, const uintwide_t<Digits2, ST, LT>& v) { return uintwide_t<Digits2, ST, LT>(u).operator/=(v); }

  template<typename IntegralType, const std::size_t Digits2, typename ST, typename LT>
  typename std::enable_if<(   (std::is_fundamental<IntegralType>::value == true)
                           && (std::is_integral   <IntegralType>::value == true)), uintwide_t<Digits2, ST, LT>>::type
  operator%(const IntegralType& u, const uintwide_t<Digits2, ST, LT>& v) { return uintwide_t<Digits2, ST, LT>(u).operator%=(v); }

  // Non-member binary logic operations of (uintwide_t op IntegralType).
  template<typename IntegralType, const std::size_t Digits2, typename ST, typename LT>
  typename std::enable_if<(   (std::is_fundamental<IntegralType>::value == true)
                           && (std::is_integral   <IntegralType>::value == true)), uintwide_t<Digits2, ST, LT>>::type
  operator|(const uintwide_t<Digits2, ST, LT>& u, const IntegralType& v) { return uintwide_t<Digits2, ST, LT>(u).operator|=(uintwide_t<Digits2, ST, LT>(v)); }

  template<typename IntegralType, const std::size_t Digits2, typename ST, typename LT>
  typename std::enable_if<(   (std::is_fundamental<IntegralType>::value == true)
                           && (std::is_integral   <IntegralType>::value == true)), uintwide_t<Digits2, ST, LT>>::type
  operator^(const uintwide_t<Digits2, ST, LT>& u, const IntegralType& v) { return uintwide_t<Digits2, ST, LT>(u).operator^=(uintwide_t<Digits2, ST, LT>(v)); }

  template<typename IntegralType, const std::size_t Digits2, typename ST, typename LT>
  typename std::enable_if<(   (std::is_fundamental<IntegralType>::value == true)
                           && (std::is_integral   <IntegralType>::value == true)), uintwide_t<Digits2, ST, LT>>::type
  operator&(const uintwide_t<Digits2, ST, LT>& u, const IntegralType& v) { return uintwide_t<Digits2, ST, LT>(u).operator&=(uintwide_t<Digits2, ST, LT>(v)); }

  // Non-member binary binary logic operations of (IntegralType op uintwide_t).
  template<typename IntegralType, const std::size_t Digits2, typename ST, typename LT>
  typename std::enable_if<(   (std::is_fundamental<IntegralType>::value == true)
                           && (std::is_integral   <IntegralType>::value == true)), uintwide_t<Digits2, ST, LT>>::type
  operator|(const IntegralType& u, const uintwide_t<Digits2, ST, LT>& v) { return uintwide_t<Digits2, ST, LT>(u).operator|=(v); }

  template<typename IntegralType, const std::size_t Digits2, typename ST, typename LT>
  typename std::enable_if<(   (std::is_fundamental<IntegralType>::value == true)
                           && (std::is_integral   <IntegralType>::value == true)), uintwide_t<Digits2, ST, LT>>::type
  operator^(const IntegralType& u, const uintwide_t<Digits2, ST, LT>& v) { return uintwide_t<Digits2, ST, LT>(u).operator^=(v); }

  template<typename IntegralType, const std::size_t Digits2, typename ST, typename LT>
  typename std::enable_if<(   (std::is_fundamental<IntegralType>::value == true)
                           && (std::is_integral   <IntegralType>::value == true)), uintwide_t<Digits2, ST, LT>>::type
  operator&(const IntegralType& u, const uintwide_t<Digits2, ST, LT>& v) { return uintwide_t<Digits2, ST, LT>(u).operator&=(v); }

  // Non-member shift functions of (uintwide_t shift IntegralType).
  template<typename IntegralType, const std::size_t Digits2, typename ST, typename LT>
  typename std::enable_if<(   (std::is_fundamental<IntegralType>::value == true)
                           && (std::is_integral   <IntegralType>::value == true)), uintwide_t<Digits2, ST, LT>>::type
  operator<<(const uintwide_t<Digits2, ST, LT>& u, const IntegralType n) { return uintwide_t<Digits2, ST, LT>(u).operator<<=(n); }

  template<typename IntegralType, const std::size_t Digits2, typename ST, typename LT>
  typename std::enable_if<(   (std::is_fundamental<IntegralType>::value == true)
                           && (std::is_integral   <IntegralType>::value == true)), uintwide_t<Digits2, ST, LT>>::type
  operator>>(const uintwide_t<Digits2, ST, LT>& u, const IntegralType n) { return uintwide_t<Digits2, ST, LT>(u).operator>>=(n); }

  // Non-member comparison functions of (uintwide_t cmp IntegralType).
  template<typename IntegralType, const std::size_t Digits2, typename ST, typename LT>
  typename std::enable_if<(   (std::is_fundamental<IntegralType>::value == true)
                           && (std::is_integral   <IntegralType>::value == true)), bool>::type
  operator==(const uintwide_t<Digits2, ST, LT>& u, const IntegralType& v) { return u.operator==(uintwide_t<Digits2, ST, LT>(v)); }

  template<typename IntegralType, const std::size_t Digits2, typename ST, typename LT>
  typename std::enable_if<(   (std::is_fundamental<IntegralType>::value == true)
                           && (std::is_integral   <IntegralType>::value == true)), bool>::type
  operator!=(const uintwide_t<Digits2, ST, LT>& u, const IntegralType& v) { return u.operator!=(uintwide_t<Digits2, ST, LT>(v)); }

  template<typename IntegralType, const std::size_t Digits2, typename ST, typename LT>
  typename std::enable_if<(   (std::is_fundamental<IntegralType>::value == true)
                           && (std::is_integral   <IntegralType>::value == true)), bool>::type
  operator> (const uintwide_t<Digits2, ST, LT>& u, const IntegralType& v) { return u.operator> (uintwide_t<Digits2, ST, LT>(v)); }

  template<typename IntegralType, const std::size_t Digits2, typename ST, typename LT>
  typename std::enable_if<(   (std::is_fundamental<IntegralType>::value == true)
                           && (std::is_integral   <IntegralType>::value == true)), bool>::type
  operator< (const uintwide_t<Digits2, ST, LT>& u, const IntegralType& v) { return u.operator< (uintwide_t<Digits2, ST, LT>(v)); }

  template<typename IntegralType, const std::size_t Digits2, typename ST, typename LT>
  typename std::enable_if<(   (std::is_fundamental<IntegralType>::value == true)
                           && (std::is_integral   <IntegralType>::value == true)), bool>::type
  operator>=(const uintwide_t<Digits2, ST, LT>& u, const IntegralType& v) { return u.operator>=(uintwide_t<Digits2, ST, LT>(v)); }

  template<typename IntegralType, const std::size_t Digits2, typename ST, typename LT>
  typename std::enable_if<(   (std::is_fundamental<IntegralType>::value == true)
                           && (std::is_integral   <IntegralType>::value == true)), bool>::type
  operator<=(const uintwide_t<Digits2, ST, LT>& u, const IntegralType& v) { return u.operator<=(uintwide_t<Digits2, ST, LT>(v)); }

  // Non-member comparison functions of (IntegralType cmp uintwide_t).
  template<typename IntegralType, const std::size_t Digits2, typename ST, typename LT>
  typename std::enable_if<(   (std::is_fundamental<IntegralType>::value == true)
                           && (std::is_integral   <IntegralType>::value == true)), bool>::type
  operator==(const IntegralType& u, const uintwide_t<Digits2, ST, LT>& v) { return uintwide_t<Digits2, ST, LT>(u).operator==(v); }

  template<typename IntegralType, const std::size_t Digits2, typename ST, typename LT>
  typename std::enable_if<(   (std::is_fundamental<IntegralType>::value == true)
                           && (std::is_integral   <IntegralType>::value == true)), bool>::type
  operator!=(const IntegralType& u, const uintwide_t<Digits2, ST, LT>& v) { return uintwide_t<Digits2, ST, LT>(u).operator!=(v); }

  template<typename IntegralType, const std::size_t Digits2, typename ST, typename LT>
  typename std::enable_if<(   (std::is_fundamental<IntegralType>::value == true)
                           && (std::is_integral   <IntegralType>::value == true)), bool>::type
  operator> (const IntegralType& u, const uintwide_t<Digits2, ST, LT>& v) { return uintwide_t<Digits2, ST, LT>(u).operator> (v); }

  template<typename IntegralType, const std::size_t Digits2, typename ST, typename LT>
  typename std::enable_if<(   (std::is_fundamental<IntegralType>::value == true)
                           && (std::is_integral   <IntegralType>::value == true)), bool>::type
  operator< (const IntegralType& u, const uintwide_t<Digits2, ST, LT>& v) { return uintwide_t<Digits2, ST, LT>(u).operator< (v); }

  template<typename IntegralType, const std::size_t Digits2, typename ST, typename LT>
  typename std::enable_if<(   (std::is_fundamental<IntegralType>::value == true)
                           && (std::is_integral   <IntegralType>::value == true)), bool>::type
  operator>=(const IntegralType& u, const uintwide_t<Digits2, ST, LT>& v) { return uintwide_t<Digits2, ST, LT>(u).operator>=(v); }

  template<typename IntegralType, const std::size_t Digits2, typename ST, typename LT>
  typename std::enable_if<(   (std::is_fundamental<IntegralType>::value == true)
                           && (std::is_integral   <IntegralType>::value == true)), bool>::type
  operator<=(const IntegralType& u, const uintwide_t<Digits2, ST, LT>& v) { return uintwide_t<Digits2, ST, LT>(u).operator<=(v); }

  #if defined(WIDE_INTEGER_DISABLE_IOSTREAM)
  #else

  // I/O streaming functions.
  template<typename char_type,
           typename traits_type,
           const std::size_t Digits2,
           typename ST,
           typename LT>
  std::basic_ostream<char_type, traits_type>&
  operator<<(std::basic_ostream<char_type, traits_type>& out,
             const uintwide_t<Digits2, ST, LT>& x)
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

    const std::size_t field_width = std::size_t(out.width());
    const char        fill_char   = out.fill();

    using local_wide_integer_type = uintwide_t<Digits2, ST, LT>;

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
           const std::size_t Digits2,
           typename ST,
           typename LT>
  std::basic_istream<char_type, traits_type>&
  operator>>(std::basic_istream<char_type, traits_type>& in,
             uintwide_t<Digits2, ST, LT>& x)
  {
    std::string str_in;

    in >> str_in;

    using local_wide_integer_type = uintwide_t<Digits2, ST, LT>;

    x = local_wide_integer_type(str_in.c_str());

    return in;
  }

  #endif

  } } // namespace wide_integer::generic_template

#endif // GENERIC_TEMPLATE_UINTWIDE_T_2018_10_02_H_
