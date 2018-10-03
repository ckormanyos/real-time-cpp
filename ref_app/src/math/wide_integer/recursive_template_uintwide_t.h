#ifndef RECURSIVE_TEMPLATE_UINTWIDE_T_2018_09_22_H_
  #define RECURSIVE_TEMPLATE_UINTWIDE_T_2018_09_22_H_

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

  #if !defined(WIDE_INTEGER_DISABLE_IOSTREAM)
    #include <iostream>
  #endif

  namespace wide_integer { namespace recursive_template {
  // Forward declaration.
  template<typename ST,
           typename LT>
  class uintwide_t;
  } }

  namespace std
  {
    // Forward declaration: Support for numeric_limits<>.
    template<typename ST,
             typename LT>
    class numeric_limits<wide_integer::recursive_template::uintwide_t<ST, LT>>;
  }

  namespace wide_integer { namespace recursive_template { namespace detail {

  // From an unsigned integral input parameter of type LT, extract
  // the low part of it. The type of the extracted low part is ST,
  // which has half the width of LT.
  template<typename ST, typename LT>
  ST make_lo(const LT& u)
  {
    // Compile-time checks.
    static_assert(    (std::numeric_limits<ST>::is_integer == true)
                  &&  (std::numeric_limits<LT>::is_integer == true)
                  &&  (std::numeric_limits<ST>::is_signed  == false)
                  &&  (std::numeric_limits<LT>::is_signed  == false)
                  && ((std::numeric_limits<ST>::digits * 2) == std::numeric_limits<LT>::digits),
                  "Error: Please check the characteristics of ushort_type and ularge_type");

    return static_cast<ST>(u);
  }

  // From an unsigned integral input parameter of type LT, extract
  // the high part of it. The type of the extracted high part is ST,
  // which has half the width of LT.
  template<typename ST, typename LT>
  ST make_hi(const LT& u)
  {
    // Compile-time checks.
    static_assert(    (std::numeric_limits<ST>::is_integer == true)
                  &&  (std::numeric_limits<LT>::is_integer == true)
                  &&  (std::numeric_limits<ST>::is_signed  == false)
                  &&  (std::numeric_limits<LT>::is_signed  == false)
                  && ((std::numeric_limits<ST>::digits * 2) == std::numeric_limits<LT>::digits),
                  "Error: Please check the characteristics of ushort_type and ularge_type");

    return static_cast<ST>(u >> std::numeric_limits<ST>::digits);
  }

  // Create a composite unsigned integral value having type LT.
  // Two constituents are used having type ST, whereby the
  // width of ST is half the width of LT.
  template<typename ST, typename LT>
  LT make_large(const ST& lo, const ST& hi)
  {
    // Compile-time checks.
    static_assert(    (std::numeric_limits<ST>::is_integer == true)
                  &&  (std::numeric_limits<LT>::is_integer == true)
                  &&  (std::numeric_limits<ST>::is_signed  == false)
                  &&  (std::numeric_limits<LT>::is_signed  == false)
                  && ((std::numeric_limits<ST>::digits * 2) == std::numeric_limits<LT>::digits),
                  "Error: Please check the characteristics of ushort_type and ularge_type");

    return LT(LT(static_cast<LT>(hi) << std::numeric_limits<ST>::digits) | LT(lo));
  }

  } } } // namespace wide_integer::recursive_template::detail

  namespace wide_integer { namespace recursive_template {

  template<typename ST, typename LT>
  class uintwide_t
  {
  public:
    // Class-local type definitions.
    using ushort_type = ST;
    using ularge_type = LT;

    using representation_type = std::array<ushort_type, 4U>;

    // Compile-time checks.
    static_assert(    (std::numeric_limits<ushort_type>::is_integer == true)
                  &&  (std::numeric_limits<ularge_type>::is_integer == true)
                  &&  (std::numeric_limits<ushort_type>::is_signed  == false)
                  &&  (std::numeric_limits<ularge_type>::is_signed  == false)
                  && ((std::numeric_limits<ushort_type>::digits * 2) == std::numeric_limits<ularge_type>::digits),
                  "Error: Please check the characteristics of ushort_type and ularge_type");

    // Default destructor.
    ~uintwide_t() = default;

    // Default constructor.
    uintwide_t() = default;

    // Constructor from another uintwide_t that is less wide
    // than *this or has exactly the same width as *this.
    template<typename OtherST,
             typename OtherLT>
    uintwide_t(const uintwide_t<OtherST, OtherLT>& u,
               typename std::enable_if<std::numeric_limits<typename uintwide_t<OtherST, OtherLT>::ushort_type>::digits <= std::numeric_limits<ushort_type>::digits>::type* = nullptr)
    {
      create_from_uintwide_t_having_smaller_width(u);
    }

    // Constructor from another uintwide_t that is wider
    // than *this, and does not have exactly the same width
    // as *this.
    template<typename OtherST,
             typename OtherLT>
    uintwide_t(const uintwide_t<OtherST, OtherLT>& u,
               typename std::enable_if<std::numeric_limits<ushort_type>::digits < std::numeric_limits<typename uintwide_t<OtherST, OtherLT>::ushort_type>::digits>::type* = nullptr)
    {
      create_from_uintwide_t_having_greater_width(u);
    }

    // Constructors from built-in unsigned integral types that
    // are less wide than ushort_type or exactly as wide as ushort_type.
    template<typename UnsignedIntegralType>
    uintwide_t(const UnsignedIntegralType v,
              typename std::enable_if<   (std::is_fundamental<UnsignedIntegralType>::value == true)
                                      && (std::is_integral   <UnsignedIntegralType>::value == true)
                                      && (std::is_unsigned   <UnsignedIntegralType>::value == true)
                                      && (   std::numeric_limits<UnsignedIntegralType>::digits
                                          <= std::numeric_limits<ushort_type         >::digits)>::type* = nullptr)
    {
      values[0U] = ushort_type(v);
      values[1U] = values[2U] = values[3U] = ushort_type(0U);
    }

    // Constructors from built-in unsigned integral types that
    // are wider than ushort_type, and do not have exactly the
    // same width as ushort_type.
    template<typename UnsignedIntegralType>
    uintwide_t(const UnsignedIntegralType v,
               typename std::enable_if<   (std::is_fundamental<UnsignedIntegralType>::value == true)
                                       && (std::is_integral   <UnsignedIntegralType>::value == true)
                                       && (std::is_unsigned   <UnsignedIntegralType>::value == true)
                                       && (  std::numeric_limits<ushort_type         >::digits
                                           < std::numeric_limits<UnsignedIntegralType>::digits)>::type* = nullptr)
    {
      std::uint_fast32_t right_shift_amount_v = 0U;
      std::uint_fast8_t  index_u              = 0U;

      for( ; (index_u < 4U) && (right_shift_amount_v < std::uint_fast32_t(std::numeric_limits<UnsignedIntegralType>::digits)); ++index_u)
      {
        values[index_u] = ushort_type(v >> (int) right_shift_amount_v);

        right_shift_amount_v += std::uint_fast32_t(std::numeric_limits<ushort_type>::digits);
      }

      std::fill(values.begin() + index_u, values.end(), ushort_type(0U));
    }

    // Constructor from the internal data representation.
    uintwide_t(const representation_type& rep)
    {
      std::copy(rep.cbegin(), rep.cend(), values.begin());
    }

    // Constructor from an initialization list.
    template<const std::size_t N>
    uintwide_t(const ushort_type(&init)[N])
    {
      static_assert(N <= std::size_t(4U), "Error: The initialization list has too many elements.");

      std::copy(init, init + (std::min)(N, std::size_t(4U)), values.begin());
    }

    // Copy constructor.
    uintwide_t(const uintwide_t& other)
    {
      std::copy(other.values.cbegin(), other.values.cend(), values.begin());
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

    // Implement cast operators that cast to types having less width.
    operator ushort_type() const { return values[0U]; }
    operator ularge_type() const { return detail::make_large<ushort_type, ularge_type>(values[0U], values[1U]); }

    // Provide a user interface to the internal data representation.
          representation_type&  representation()       { return values; }
    const representation_type&  representation() const { return values; }
    const representation_type& crepresentation() const { return values; }

    uintwide_t& operator+=(const uintwide_t& other)
    {
      // Unary addition function.
      ularge_type result_as_ularge_array[4U];

      result_as_ularge_array[0U] =  ularge_type(values[0U]) + ularge_type(other.values[0U]);
      result_as_ularge_array[1U] = (ularge_type(values[1U]) + ularge_type(other.values[1U])) + ularge_type(detail::make_hi<ushort_type, ularge_type>(result_as_ularge_array[0U]));
      result_as_ularge_array[2U] = (ularge_type(values[2U]) + ularge_type(other.values[2U])) + ularge_type(detail::make_hi<ushort_type, ularge_type>(result_as_ularge_array[1U]));
      result_as_ularge_array[3U] = (ularge_type(values[3U]) + ularge_type(other.values[3U])) + ularge_type(detail::make_hi<ushort_type, ularge_type>(result_as_ularge_array[2U]));

      values[0U] = ushort_type(result_as_ularge_array[0U]);
      values[1U] = ushort_type(result_as_ularge_array[1U]);
      values[2U] = ushort_type(result_as_ularge_array[2U]);
      values[3U] = ushort_type(result_as_ularge_array[3U]);

      return *this;
    }

    uintwide_t& operator-=(const uintwide_t& other)
    {
      // Unary subtraction function.
      ularge_type result_as_ularge_array[4U];

      bool has_borrow;

      result_as_ularge_array[0U] = ularge_type(values[0U]) - ularge_type(other.values[0U]);

      result_as_ularge_array[1U] = ularge_type(values[1U]) - ularge_type(other.values[1U]);
      has_borrow = (detail::make_hi<ushort_type, ularge_type>(result_as_ularge_array[0U]) != ushort_type(0U));
      if(has_borrow) { --result_as_ularge_array[1U]; }

      result_as_ularge_array[2U] = ularge_type(values[2U]) - ularge_type(other.values[2U]);
      has_borrow = (detail::make_hi<ushort_type, ularge_type>(result_as_ularge_array[1U]) != ushort_type(0U));
      if(has_borrow) { --result_as_ularge_array[2U]; }

      result_as_ularge_array[3U] = ularge_type(values[3U]) - ularge_type(other.values[3U]);
      has_borrow = (detail::make_hi<ushort_type, ularge_type>(result_as_ularge_array[2U]) != ushort_type(0U));
      if(has_borrow) { --result_as_ularge_array[3U]; }

      values[0U] = ushort_type(result_as_ularge_array[0U]);
      values[1U] = ushort_type(result_as_ularge_array[1U]);
      values[2U] = ushort_type(result_as_ularge_array[2U]);
      values[3U] = ushort_type(result_as_ularge_array[3U]);

      return *this;
    }

    uintwide_t& operator*=(const uintwide_t& other)
    {
      // Unary multiplication function.

      // Consider the polynomial multiplication of:
      //   (A + Bx + Cx^2 + Dx^3) * (a + bx + cx^2 + dx^3).
      //
      // The result is:    Aa
      //                + (Ab + Ba) x
      //                + (Bb + Ac + Ca) x^2
      //                + (Bc + Cb + Ad + Da) x^3
      //
      // Also handle the degenerate half-quadratic case of:
      //   (A + Bx) * (a + bx).
      // The result is:    Aa
      //                + (Ab + Ba) x
      //                + (Bb)      x^2

      // Identify and handle multiplication with zero.

      const ushort_type local_short_zero(0U);

      const bool lo_part_left_is_zero  = ((      values[0U] == local_short_zero) && (      values[1U] == local_short_zero));
      const bool hi_part_left_is_zero  = ((      values[2U] == local_short_zero) && (      values[3U] == local_short_zero));
      const bool lo_part_right_is_zero = ((other.values[0U] == local_short_zero) && (other.values[1U] == local_short_zero));
      const bool hi_part_right_is_zero = ((other.values[2U] == local_short_zero) && (other.values[3U] == local_short_zero));

      const bool left_is_zero  = (lo_part_left_is_zero  && hi_part_left_is_zero);
      const bool right_is_zero = (lo_part_right_is_zero && hi_part_right_is_zero);

      if(left_is_zero || right_is_zero)
      {
        // Handle multiplication with zero.
        operator=(std::uint16_t(0U));
      }
      else
      {
        const ularge_type Aa = ularge_type(values[0U]) * ularge_type(other.values[0U]);
        const ularge_type Ab = ularge_type(values[1U]) * ularge_type(other.values[0U]);
        const ularge_type Ba = ularge_type(values[0U]) * ularge_type(other.values[1U]);
        const ularge_type Bb = ularge_type(values[1U]) * ularge_type(other.values[1U]);

        const ularge_type result_value_tmp1 =   (ularge_type(detail::make_lo<ushort_type, ularge_type>(Ab)) + ularge_type(detail::make_lo<ushort_type, ularge_type>(Ba)))
                                              +  ularge_type(detail::make_hi<ushort_type, ularge_type>(Aa));

        ularge_type result_value_tmp2;

        if(hi_part_left_is_zero && hi_part_right_is_zero)
        {
          // Handle the degenerate half-quadratic case.
          result_value_tmp2 =   (ularge_type(detail::make_lo<ushort_type, ularge_type>(Bb)) + ularge_type(detail::make_hi<ushort_type, ularge_type>(Ab)))
                              + (ularge_type(detail::make_hi<ushort_type, ularge_type>(Ba)) + ularge_type(detail::make_hi<ushort_type, ularge_type>(result_value_tmp1)));

          values[3U] = detail::make_lo<ushort_type, ularge_type>(ularge_type(ularge_type(detail::make_hi<ushort_type, ularge_type>(Bb)) + ularge_type(detail::make_hi<ushort_type, ularge_type>(result_value_tmp2))));
        }
        else
        {
          // Handle the full quadratic case.
          const ularge_type Ac = ularge_type(values[2U]) * ularge_type(other.values[0U]);
          const ularge_type Ca = ularge_type(values[0U]) * ularge_type(other.values[2U]);
          const ularge_type Bc = ularge_type(values[2U]) * ularge_type(other.values[1U]);
          const ularge_type Cb = ularge_type(values[1U]) * ularge_type(other.values[2U]);
          const ularge_type Ad = ularge_type(values[3U]) * ularge_type(other.values[0U]);
          const ularge_type Da = ularge_type(values[0U]) * ularge_type(other.values[3U]);

          result_value_tmp2 =   (ularge_type(detail::make_lo<ushort_type, ularge_type>(Bb)) + ularge_type(detail::make_lo<ushort_type, ularge_type>(Ac)))
                              + (ularge_type(detail::make_lo<ushort_type, ularge_type>(Ca)) + ularge_type(detail::make_hi<ushort_type, ularge_type>(Ab)))
                              + (ularge_type(detail::make_hi<ushort_type, ularge_type>(Ba)) + ularge_type(detail::make_hi<ushort_type, ularge_type>(result_value_tmp1)));

          values[3U] = ushort_type(  (ularge_type(detail::make_lo<ushort_type, ularge_type>(Bc)) + ularge_type(detail::make_lo<ushort_type, ularge_type>(Cb)))
                                   + (ularge_type(detail::make_lo<ushort_type, ularge_type>(Ad)) + ularge_type(detail::make_lo<ushort_type, ularge_type>(Da)))
                                   + (ularge_type(detail::make_hi<ushort_type, ularge_type>(Bb)) + ularge_type(detail::make_hi<ushort_type, ularge_type>(Ac)))
                                   + (ularge_type(detail::make_hi<ushort_type, ularge_type>(Ca)) + ularge_type(detail::make_hi<ushort_type, ularge_type>(result_value_tmp2))));
        }

        values[0U] = detail::make_lo<ushort_type, ularge_type>(Aa);
        values[1U] = detail::make_lo<ushort_type, ularge_type>(result_value_tmp1);
        values[2U] = detail::make_lo<ushort_type, ularge_type>(result_value_tmp2);
      }

      return *this;
    }

    uintwide_t& operator/=(const uintwide_t& other)
    {
      // Unary division function.
      division_knuth_simplified(other);

      return *this;
    }

    uintwide_t& operator%=(const uintwide_t& other)
    {
      // Unary modulus function.
      uintwide_t quotient(*this);

      quotient.division_knuth_simplified(other);

      operator-=(quotient *= other);

      return *this;
    }

    const uintwide_t& operator++()
    {
      // Operator pre-increment.
      if(   (++values[0U] == ushort_type(0U))
         && (++values[1U] == ushort_type(0U))
         && (++values[2U] == ushort_type(0U)))
      {
        ++values[3U];
      }

      return *this;
    }

    const uintwide_t& operator--()
    {
      // Operator pre-decrement.
      if(   (values[0U]-- == ushort_type(0U))
         && (values[1U]-- == ushort_type(0U))
         && (values[2U]-- == ushort_type(0U)))
      {
        --values[3U];
      }

      return *this;
    }

    // Operators post-increment and post decrement.
    uintwide_t operator++(int) { uintwide_t w(*this); ++(*this); return w; }
    uintwide_t operator--(int) { uintwide_t w(*this); --(*this); return w; }

    uintwide_t& operator|=(const uintwide_t& other)
    {
      // Bitwise OR.
      values[0U] = ushort_type(values[0U] | other.values[0U]);
      values[1U] = ushort_type(values[1U] | other.values[1U]);
      values[2U] = ushort_type(values[2U] | other.values[2U]);
      values[3U] = ushort_type(values[3U] | other.values[3U]);

      return *this;
    }

    uintwide_t& operator^=(const uintwide_t& other)
    {
      // Bitwise XOR.
      values[0U] = ushort_type(values[0U] ^ other.values[0U]);
      values[1U] = ushort_type(values[1U] ^ other.values[1U]);
      values[2U] = ushort_type(values[2U] ^ other.values[2U]);
      values[3U] = ushort_type(values[3U] ^ other.values[3U]);

      return *this;
    }

    uintwide_t& operator&=(const uintwide_t& other)
    {
      // Bitwise AND.
      values[0U] = ushort_type(values[0U] & other.values[0U]);
      values[1U] = ushort_type(values[1U] & other.values[1U]);
      values[2U] = ushort_type(values[2U] & other.values[2U]);
      values[3U] = ushort_type(values[3U] & other.values[3U]);

      return *this;
    }

    uintwide_t& operator~()
    {
      // Bitwise NOT.
      values[0U] = ushort_type(~values[0U]);
      values[1U] = ushort_type(~values[1U]);
      values[2U] = ushort_type(~values[2U]);
      values[3U] = ushort_type(~values[3U]);

      return *this;
    }

    uintwide_t& operator<<=(const int n)
    {
      // Left-shift operator. Use composite ularge_type parts.
      if(n < int(0))
      {
        operator>>=(-n);
      }
      else if(n == int(0))
      {
      }
      else if(n >= int(std::numeric_limits<ularge_type>::digits * 2))
      {
        // If the amount of left-shift exceeds the total bit-count
        // of the uintwide_t type, then the result is zero.
        operator=(std::uint16_t(0U));
      }
      else
      {
        ularge_type lo_part = detail::make_large<ushort_type, ularge_type>(values[0U], values[1U]);
        ularge_type hi_part;

        if(n >= int(std::numeric_limits<ularge_type>::digits))
        {
          hi_part = ularge_type(lo_part << (int(n - int(std::numeric_limits<ularge_type>::digits))));

          values[0U] = 0U;
          values[1U] = 0U;
        }
        else
        {
          hi_part = detail::make_large<ushort_type, ularge_type>(values[2U], values[3U]);

          hi_part   =   ularge_type(hi_part << n)
                      |            (lo_part >> (int(int(std::numeric_limits<ularge_type>::digits - n))));

          lo_part <<= n;

          values[0U] = detail::make_lo<ushort_type, ularge_type>(lo_part);
          values[1U] = detail::make_hi<ushort_type, ularge_type>(lo_part);
        }

        values[2U] = detail::make_lo<ushort_type, ularge_type>(hi_part);
        values[3U] = detail::make_hi<ushort_type, ularge_type>(hi_part);
      }

      return *this;
    }

    uintwide_t& operator>>=(const int n)
    {
      // Right-shift operator. Use composite ularge_type parts.
      ularge_type lo_part;
      ularge_type hi_part = detail::make_large<ushort_type, ularge_type>(values[2U], values[3U]);

      if(n < int(0))
      {
        operator<<=(-n);
      }
      else if(n == (int) 0U)
      {
      }
      else if(n >= int(std::numeric_limits<ularge_type>::digits * 2))
      {
        // If the amount of right-shift exceeds the total bit-count
        // of the uintwide_t type, then the result is zero.
        operator=(std::uint16_t(0U));
      }
      else
      {
        if(n >= int(std::numeric_limits<ularge_type>::digits))
        {
          lo_part = ularge_type(hi_part >> (int(n - int(std::numeric_limits<ularge_type>::digits))));

          values[2U] = 0U;
          values[3U] = 0U;
        }
        else
        {
          lo_part = detail::make_large<ushort_type, ularge_type>(values[0U], values[1U]);

          lo_part   =   ularge_type(lo_part >> n)
                      |            (hi_part << (int(int(std::numeric_limits<ularge_type>::digits) - n)));

          hi_part >>= n;

          values[2U] = detail::make_lo<ushort_type, ularge_type>(hi_part);
          values[3U] = detail::make_hi<ushort_type, ularge_type>(hi_part);
        }

        values[0U] = detail::make_lo<ushort_type, ularge_type>(lo_part);
        values[1U] = detail::make_hi<ushort_type, ularge_type>(lo_part);
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

    // Create helper variables and functions for supporting std::numeric_limits<>.
    static const int limits_helper_digits   = std::numeric_limits<ushort_type>::digits * 4;
    static const int limits_helper_digits10 = static_cast<int>((std::uintmax_t(limits_helper_digits) * UINTMAX_C(301)) / 1000U);

    static uintwide_t limits_helper_max()
    {
      return uintwide_t(
                         {
                           (std::numeric_limits<ushort_type>::max)(),
                           (std::numeric_limits<ushort_type>::max)(),
                           (std::numeric_limits<ushort_type>::max)(),
                           (std::numeric_limits<ushort_type>::max)()
                         }
                       );
    }

    static uintwide_t limits_helper_min()
    {
      return uintwide_t(std::uint8_t(0U));
    }

  private:
    representation_type values;

    template<typename OtherST, typename OtherLT>
    void create_from_uintwide_t_having_smaller_width(const uintwide_t<OtherST, OtherLT>& v)
    {
      // Here, v is less wide than *this or exactly as wide as *this.
      // We will associate *this with the variable u in this subroutine.

      // Initialize the values of *this.
      values[0U] = values[1U] = values[2U] = values[3U] = 0U;

      const std::uint_fast8_t upper_index_u =
        std::uint_fast8_t(  (std::uint_fast32_t(4U) * std::uint_fast32_t(std::numeric_limits<OtherST>::digits))
                          /  std::uint_fast32_t(std::numeric_limits<ST>::digits));

      // Convert the values in the representation of u
      // to the values in *this.
      for(std::uint_fast8_t index_u = 0U; index_u < (std::max)(std::uint_fast8_t(1U), upper_index_u); ++index_u)
      {
        const std::uint_fast32_t upper_index_v =
          std::uint_fast32_t(  std::uint_fast32_t(std::numeric_limits<ST>::digits)
                             / std::uint_fast32_t(std::numeric_limits<OtherST>::digits));

        for(std::uint_fast8_t index_v = 0U; index_v < std::uint_fast8_t((std::min)(std::uint_fast32_t(4U), upper_index_v)); ++index_v)
        {
          const std::uint_fast32_t index_val_offset =
            std::uint_fast32_t(  (std::uint_fast32_t(index_u) * std::uint_fast32_t(std::numeric_limits<ST>::digits))
                               /  std::uint_fast32_t(std::numeric_limits<OtherST>::digits));

          const ushort_type val =
            ushort_type(v.crepresentation()[index_v + index_val_offset])
              << (int) (index_v * std::uint_fast32_t(std::numeric_limits<OtherST>::digits));

          values[index_u] |= val;
        }
      }
    }

    template<typename OtherST, typename OtherLT>
    void create_from_uintwide_t_having_greater_width(const uintwide_t<OtherST, OtherLT>& v)
    {
      // Here, v is wider than *this (yet not exactly as wide as *this).
      // We will associate *this with the variable u in this subroutine.

      // Initialize the values of *this.
      values[0U] = values[1U] = values[2U] = values[3U] = 0U;

      std::uint_fast8_t  index_v              = 0U;
      std::uint_fast32_t right_shift_amount_v = 0U;

      // Convert the values in the representation of u
      // to the values in *this.
      for(std::uint_fast8_t index_u = 0U; index_u < std::uint_fast8_t(4U); ++index_u)
      {
        const ushort_type val = ushort_type(v.crepresentation()[index_v] >> ((int) right_shift_amount_v));

        values[index_u] = ushort_type(val);

        right_shift_amount_v += std::uint_fast32_t(std::numeric_limits<ushort_type>::digits);

        if(right_shift_amount_v >= std::uint_fast32_t(std::numeric_limits<OtherST>::digits))
        {
          right_shift_amount_v = 0U;

          ++index_v;
        }
      }
    }

    bool string_out(char*             strResult,
                    std::uint_fast8_t baseRep,
                    bool              showBase,
                    bool              showPos,
                    bool              isUpperCase) const
    {
      // TBD: Implement extraction of string representation.

      static_cast<void>(strResult);
      static_cast<void>(baseRep);
      static_cast<void>(showBase);
      static_cast<void>(showPos);
      static_cast<void>(isUpperCase);

      return false;
    }

    void division_knuth_simplified(const uintwide_t& other)
    {
      // Use a simplified version of Knuth's long division algorithm
      // with reduction to four limbs. The loop-ordering of indexes
      // in Knuth's original algorithm has been reversed due
      // to the little-endian data format used here.

      // See also:
      // D.E. Knuth, "The Art of Computer Programming, Volume 2:
      // Seminumerical Algorithms", Addison-Wesley (1998),
      // Section 4.3.1 Algorithm D and Exercise 16.

      using local_uint_index_type = std::uint_fast8_t;

      local_uint_index_type u_offset = local_uint_index_type(0U);
      local_uint_index_type v_offset = local_uint_index_type(0U);

      // Compute the offsets for u and v.
      for(local_uint_index_type i = 0U; (i < 4U) && (      values[(4U - 1U) - i] == ushort_type(0U)); ++i) { ++u_offset; }
      for(local_uint_index_type i = 0U; (i < 4U) && (other.values[(4U - 1U) - i] == ushort_type(0U)); ++i) { ++v_offset; }

      if(v_offset == local_uint_index_type(4U))
      {
        // The denominator is zero. Set the maximum value and return.
        // This also catches (0 / 0) and sets the maximum value for it.
        operator=(limits_helper_max());

        return;
      }

      if(u_offset == local_uint_index_type(4U))
      {
        // The numerator is zero. Do nothing and return.
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
          operator=(std::uint8_t(0U));

          return;
        }

        if(left_is_equal_to_right)
        {
          // If the denominator is equal to the numerator,
          // then the result of the division is one.
          operator=(std::uint8_t(1U));

          return;
        }
      }

      if(v_offset == local_uint_index_type(4U - 1U))
      {
        // The denominator has one single limb.
        // Use a one-dimensional division algorithm.

              ularge_type long_numerator    =       values[4U - 1U];
        const ushort_type short_denominator = other.values[0U];

        values[3U] /= short_denominator;

        long_numerator = ularge_type(values[2U]) + ((long_numerator - (ularge_type(short_denominator) * ularge_type(values[3U]))) << std::numeric_limits<ushort_type>::digits);
        values[2U]     = detail::make_lo<ushort_type, ularge_type>(long_numerator / ularge_type(short_denominator));

        long_numerator = ularge_type(values[1U]) + ((long_numerator - (ularge_type(short_denominator) * ularge_type(values[2U]))) << std::numeric_limits<ushort_type>::digits);
        values[1U]     = detail::make_lo<ushort_type, ularge_type>(long_numerator / ularge_type(short_denominator));

        long_numerator = ularge_type(values[0U]) + ((long_numerator - (ularge_type(short_denominator) * ularge_type(values[1U]))) << std::numeric_limits<ushort_type>::digits);
        values[0U]     = detail::make_lo<ushort_type, ularge_type>(long_numerator / ularge_type(short_denominator));

        return;
      }

      // We will now use a simplified version
      // of the Knuth long division algorithm.
      {
        // Compute the normalization factor d.
        const ushort_type d =
          detail::make_lo<ushort_type, ularge_type>(  ((ularge_type(std::uint8_t(1U))) << std::numeric_limits<ushort_type>::digits)
                                                    /  (ularge_type(other.values[(4U - 1U) - v_offset]) + ularge_type(std::uint8_t(1U))));

        // Step D1(b), normalize u -> u * d = uu.
        // Note the added digit in uu and also that
        // the data of uu have not been initialized yet.

        std::array<ushort_type, 4U + 1U> uu;

        if(d == ushort_type(1U))
        {
          // The normalization is one.
          uu[0U] = values[0U];
          uu[1U] = values[1U];
          uu[2U] = values[2U];
          uu[3U] = values[3U];
          uu[4U] = 0U;
        }
        else
        {
          // Multiply u by d.
          ushort_type carry = 0U;

          local_uint_index_type i;

          for(i = local_uint_index_type(0U); i < local_uint_index_type(4U - u_offset); ++i)
          {
            const ularge_type t = (ularge_type(values[i]) * ularge_type(d)) + ularge_type(carry);

            uu[i] = detail::make_lo<ushort_type, ularge_type>(t);
            carry = detail::make_hi<ushort_type, ularge_type>(t);
          }

          uu[i] = carry;
        }

        std::array<ushort_type, 4U> vv;

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

          for(local_uint_index_type i = local_uint_index_type(0U); i < local_uint_index_type(4U - v_offset); ++i)
          {
            const ularge_type t = (ularge_type(other.values[i]) * ularge_type(d)) + ularge_type(carry);

            vv[i] = detail::make_lo<ushort_type, ularge_type>(t);
            carry = detail::make_hi<ushort_type, ularge_type>(t);
          }
        }

        // Step D2: Initialize j.
        // Step D7: Loop on j from m to 0.

        const local_uint_index_type n =  4U  - v_offset;
        const local_uint_index_type m = (4U  - u_offset) - n;

        for(local_uint_index_type j = local_uint_index_type(0U); j <= m; ++j)
        {
          // Step D3 [Calculate q_hat].
          //   if u[j] == v[j0]
          //     set q_hat = b - 1
          //   else
          //     set q_hat = (u[j] * b + u[j + 1]) / v[1]

          const local_uint_index_type uj  = (((4U + 1U) - 1U) - u_offset) - j;
          const local_uint_index_type vj0 =   (4U       - 1U) - v_offset;
          const ularge_type       u_j_j1  = (ularge_type(uu[uj]) << std::numeric_limits<ushort_type>::digits) + ularge_type(uu[uj - 1U]);

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

            if(   (ularge_type(vv[vj0 - 1U]) * ularge_type(q_hat))
               <= ((t << std::numeric_limits<ushort_type>::digits) + ularge_type(uu[uj - 2U])))
            {
              break;
            }

            --q_hat;
          }

          // Step D4: Multiply and subtract.
          // Replace u[j, ... j + n] by u[j, ... j + n] - q_hat * v[1, ... n].

          // Set nv = q_hat * (v[1, ... n]).
          {
            std::array<ushort_type, 4U + 1U> nv;

            ushort_type carry = 0U;

            local_uint_index_type i;

            for(i = local_uint_index_type(0U); i < n; ++i)
            {
              t     = (ularge_type(vv[i]) * ularge_type(q_hat)) + ularge_type(carry);
              nv[i] = detail::make_lo<ushort_type, ularge_type>(t);
              carry = detail::make_hi<ushort_type, ularge_type>(t);
            }

            nv[i] = carry;

            // Subtract nv[0, ... n] from u[j, ... j + n].
            local_uint_index_type borrow = 0U;
            local_uint_index_type ul     = uj - n;

            for(i = local_uint_index_type(0U); i <= n; ++i)
            {
              t        = (ularge_type(uu[ul]) - ularge_type(nv[i])) - ularge_type(std::uint8_t(borrow));
              uu[ul]   =   detail::make_lo<ushort_type, ularge_type>(t);
              borrow   = ((detail::make_hi<ushort_type, ularge_type>(t) != ushort_type(0U)) ? 1U : 0U);

              ++ul;
            }

            // Get the result data.
            values[local_uint_index_type(m - j)] = detail::make_lo<ushort_type, ularge_type>(q_hat);

            // Step D5: Test the remainder.
            // Set the result value: Set result.m_data[m - j] = q_hat
            // Condition: If u[j] < 0, in other words if the borrow
            // is non-zero, then step D6 needs to be carried out.

            if(borrow != 0U)
            {
              // Step D6: Add back.
              // Add v[1, ... n] back to u[j, ... j + n],
              // and decrease the result by 1.

              carry = 0U;
              ul    = uj - n;

              for(i = local_uint_index_type(0U); i <= n; ++i)
              {
                t        = (ularge_type(uu[ul]) + ularge_type(vv[i])) + ularge_type(carry);

                uu[ul++] = detail::make_lo<ushort_type, ularge_type>(t);
                carry    = detail::make_hi<ushort_type, ularge_type>(t);
              }

              uu[local_uint_index_type(m - j)] += carry;

              --values[local_uint_index_type(m - j)];
            }
          }
        }

        for(local_uint_index_type i = local_uint_index_type(m + 1U); i < local_uint_index_type(4U); ++i)
        {
          // Clear the data elements that have not
          // been computed in the division algorithm.
          values[i] = 0U;
        }
      }
    }

    std::int_fast8_t compare(const uintwide_t& other) const
    {
      std::int_fast8_t return_value;
      std::int_fast8_t element_index;

      for(element_index = std::int_fast8_t(3); element_index >= std::int_fast8_t(0); --element_index)
      {
        if(values[std::uint_fast8_t(element_index)] != other.values[std::uint_fast8_t(element_index)])
        {
          break;
        }
      }

      if(element_index == std::int_fast8_t(-1))
      {
        return_value = std::int_fast8_t(0);
      }
      else
      {
        const bool left_is_greater_than_right =
          ((values[std::uint_fast8_t(element_index)] > other.values[std::uint_fast8_t(element_index)]) ? true : false);

        return_value = (left_is_greater_than_right ? std::int_fast8_t(1) : std::int_fast8_t(-1));
      }

      return return_value;
    }
  };

  // Define some convenient unsigned wide integer types.
  using uint64_t   = uintwide_t<                             std::uint16_t,                                std::uint32_t>;
  using uint128_t  = uintwide_t<                             std::uint32_t,                                std::uint64_t>;
  using uint256_t  = uintwide_t<                             std::uint64_t,   wide_integer::recursive_template::uint128_t>;
  using uint512_t  = uintwide_t<wide_integer::recursive_template::uint128_t,  wide_integer::recursive_template::uint256_t>;
  using uint1024_t = uintwide_t<wide_integer::recursive_template::uint256_t,  wide_integer::recursive_template::uint512_t>;
  using uint2048_t = uintwide_t<wide_integer::recursive_template::uint512_t,  wide_integer::recursive_template::uint1024_t>;
  using uint4096_t = uintwide_t<wide_integer::recursive_template::uint1024_t, wide_integer::recursive_template::uint2048_t>;
  using uint8192_t = uintwide_t<wide_integer::recursive_template::uint2048_t, wide_integer::recursive_template::uint4096_t>;

  // Prepare a base class for numeric_limits<> support.
  template<typename WideUnsignedIntegerType>
  class numeric_limits_base : public std::numeric_limits<unsigned int>
  {
  private:
    using uintwide_type = WideUnsignedIntegerType;

  public:
    static const int digits   = uintwide_type::limits_helper_digits;
    static const int digits10 = uintwide_type::limits_helper_digits10;

    static uintwide_type (max)() { return uintwide_type::limits_helper_max(); }
    static uintwide_type (min)() { return uintwide_type::limits_helper_min(); }
  };

  } } // namespace wide_integer::recursive_template

  namespace std {

  // Support for numeric_limits<>.
  template<> class numeric_limits<wide_integer::recursive_template::uint128_t>  : public wide_integer::recursive_template::numeric_limits_base<wide_integer::recursive_template::uint128_t>  { };
  template<> class numeric_limits<wide_integer::recursive_template::uint256_t>  : public wide_integer::recursive_template::numeric_limits_base<wide_integer::recursive_template::uint256_t>  { };
  template<> class numeric_limits<wide_integer::recursive_template::uint512_t>  : public wide_integer::recursive_template::numeric_limits_base<wide_integer::recursive_template::uint512_t>  { };
  template<> class numeric_limits<wide_integer::recursive_template::uint1024_t> : public wide_integer::recursive_template::numeric_limits_base<wide_integer::recursive_template::uint1024_t> { };
  template<> class numeric_limits<wide_integer::recursive_template::uint2048_t> : public wide_integer::recursive_template::numeric_limits_base<wide_integer::recursive_template::uint2048_t> { };
  template<> class numeric_limits<wide_integer::recursive_template::uint4096_t> : public wide_integer::recursive_template::numeric_limits_base<wide_integer::recursive_template::uint4096_t> { };
  template<> class numeric_limits<wide_integer::recursive_template::uint8192_t> : public wide_integer::recursive_template::numeric_limits_base<wide_integer::recursive_template::uint8192_t> { };

  } // namespace std

  namespace wide_integer { namespace recursive_template {

  template<typename ST, typename LT> uintwide_t<ST, LT> operator+ (const uintwide_t<ST, LT>& left, const uintwide_t<ST, LT>& right) { return uintwide_t<ST, LT>(left).operator+=(right); }
  template<typename ST, typename LT> uintwide_t<ST, LT> operator- (const uintwide_t<ST, LT>& left, const uintwide_t<ST, LT>& right) { return uintwide_t<ST, LT>(left).operator-=(right); }
  template<typename ST, typename LT> uintwide_t<ST, LT> operator* (const uintwide_t<ST, LT>& left, const uintwide_t<ST, LT>& right) { return uintwide_t<ST, LT>(left).operator*=(right); }
  template<typename ST, typename LT> uintwide_t<ST, LT> operator/ (const uintwide_t<ST, LT>& left, const uintwide_t<ST, LT>& right) { return uintwide_t<ST, LT>(left).operator/=(right); }
  template<typename ST, typename LT> uintwide_t<ST, LT> operator% (const uintwide_t<ST, LT>& left, const uintwide_t<ST, LT>& right) { return uintwide_t<ST, LT>(left).operator%=(right); }

  template<typename ST, typename LT> uintwide_t<ST, LT> operator| (const uintwide_t<ST, LT>& left, const uintwide_t<ST, LT>& right) { return uintwide_t<ST, LT>(left).operator|=(right); }
  template<typename ST, typename LT> uintwide_t<ST, LT> operator^ (const uintwide_t<ST, LT>& left, const uintwide_t<ST, LT>& right) { return uintwide_t<ST, LT>(left).operator^=(right); }
  template<typename ST, typename LT> uintwide_t<ST, LT> operator& (const uintwide_t<ST, LT>& left, const uintwide_t<ST, LT>& right) { return uintwide_t<ST, LT>(left).operator&=(right); }

  template<typename ST, typename LT> uintwide_t<ST, LT> operator<<(const uintwide_t<ST, LT>& left, const int n)                     { return uintwide_t<ST, LT>(left).operator<<=(n); }
  template<typename ST, typename LT> uintwide_t<ST, LT> operator>>(const uintwide_t<ST, LT>& left, const int n)                     { return uintwide_t<ST, LT>(left).operator>>=(n); }

  } } // namespace wide_integer::recursive_template

#endif // RECURSIVE_TEMPLATE_UINTWIDE_T_2018_09_22_H_
