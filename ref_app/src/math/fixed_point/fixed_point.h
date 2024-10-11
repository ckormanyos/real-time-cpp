///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2018.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef FIXED_POINT_2011_02_22_H_
  #define FIXED_POINT_2011_02_22_H_

  #define FIXED_POINT_DISABLE_IOSTREAM

  #include <cstddef>
  #include <cstdint>
  #include <limits>

  #if !defined(FIXED_POINT_DISABLE_IOSTREAM)
    #include <istream>
    #include <ostream>
  #endif

  #include <util/utility/util_nothing.h>
  #include <util/utility/util_utype_helper.h>

  // Utility structure to help with the epsilon limits for fixed_point.
  // These special numbers represent the smallest value for a decimal part
  // that differs from 1 for the corresponding decimal-part width.
  template<const std::size_t> struct epsilon_helper      { static const std::size_t epsilon_value = std::size_t(0U); };
  template<>                  struct epsilon_helper<4U>  { static const std::size_t epsilon_value = std::size_t(1U); };
  template<>                  struct epsilon_helper<8U>  { static const std::size_t epsilon_value = std::size_t(3U); };
  template<>                  struct epsilon_helper<16U> { static const std::size_t epsilon_value = std::size_t(7U); };
  template<>                  struct epsilon_helper<32U> { static const std::size_t epsilon_value = std::size_t(44U); };

  // Forward declaration of the fixed_point template class.
  template<typename integer_type>
  class fixed_point;

  // The scalable fixed_point template class.
  template<typename integer_type>
  class fixed_point
  {
  public:
    typedef integer_type signed_value_type;
    typedef typename util::utype_helper<std::numeric_limits<signed_value_type>::digits + 1>::exact_type unsigned_value_type;

  private:
    typedef typename util::utype_helper<std::numeric_limits<unsigned_value_type>::digits / 2>::exact_type unsigned_short_type;

    static const std::size_t         decimal_split       = std::numeric_limits<unsigned_value_type>::digits / 2;
    static const signed_value_type   decimal_split_value = unsigned_value_type(1ULL) << decimal_split;
    static const unsigned_short_type decimal_split_mask  = unsigned_value_type(decimal_split_value) - 1U;

    // Ensure that the underlying integer type of the fixed_point class is signed.
    static_assert(std::numeric_limits<signed_value_type>::is_signed,
                  "the fixed point signed_value_type must be signed");

    // Another template kind of this class itself is a friend.
    // This is needed for the copy ctor and operator=().
    template<typename other_signed_type>
    friend class fixed_point;

    // Forward-declare my_numeric_limits and make it a friend of fixed_point.
    friend class my_numeric_limits;

  public:
    // Constructors.
    fixed_point() : data() { }
    fixed_point(const          char  n) : data(signed_value_type(n) << decimal_split)  { }
    fixed_point(const   signed char  n) : data(signed_value_type(n) << decimal_split)  { }
    fixed_point(const unsigned char  n) : data(signed_value_type(n) << decimal_split)  { }
    fixed_point(const   signed short n) : data(signed_value_type(n) << decimal_split)  { }
    fixed_point(const unsigned short n) : data(signed_value_type(n) << decimal_split)  { }
    fixed_point(const   signed int   n) : data(signed_value_type(n) << decimal_split)  { }
    fixed_point(const unsigned int   n) : data(signed_value_type(n) << decimal_split)  { }
    fixed_point(const   signed long  n) : data(signed_value_type(n) << decimal_split)  { }
    fixed_point(const unsigned long  n) : data(signed_value_type(n) << decimal_split)  { }
    fixed_point(const float&  f)        : data(signed_value_type(f * decimal_split_value)) { }
    fixed_point(const double& d)        : data(signed_value_type(d * decimal_split_value)) { }
    fixed_point(const long double& l)   : data(signed_value_type(l * decimal_split_value)) { }
    fixed_point(const fixed_point& fp)  : data(fp.data) { }

    template<typename other_signed_type>
    fixed_point(const fixed_point<other_signed_type>& other)
    {
      const std::size_t other_decimal_split = fixed_point<other_signed_type>::decimal_split;

      // TBD: Needs compiler support for conditional compilation.
      if(other_decimal_split > decimal_split)
      {
        data = signed_value_type(other.data >> (other_decimal_split - decimal_split));
      }
      else
      {
        data = signed_value_type(other.data) << (decimal_split - other_decimal_split);
      }
    }

    // Assignment operators.
    fixed_point& operator=(const          char  n) { data = signed_value_type(n) << decimal_split; return *this; }
    fixed_point& operator=(const   signed char  n) { data = signed_value_type(n) << decimal_split; return *this; }
    fixed_point& operator=(const unsigned char  n) { data = signed_value_type(n) << decimal_split; return *this; }
    fixed_point& operator=(const   signed short n) { data = signed_value_type(n) << decimal_split; return *this; }
    fixed_point& operator=(const unsigned short n) { data = signed_value_type(n) << decimal_split; return *this; }
    fixed_point& operator=(const   signed int   n) { data = signed_value_type(n) << decimal_split; return *this; }
    fixed_point& operator=(const unsigned int   n) { data = signed_value_type(n) << decimal_split; return *this; }
    fixed_point& operator=(const   signed long  n) { data = signed_value_type(n) << decimal_split; return *this; }
    fixed_point& operator=(const unsigned long  n) { data = signed_value_type(n) << decimal_split; return *this; }
    fixed_point& operator=(const float&         f) { data = signed_value_type(f * decimal_split_value); return *this; }
    fixed_point& operator=(const double&        d) { data = signed_value_type(d * decimal_split_value); return *this; }

    fixed_point& operator=(const fixed_point& fp)
    {
      if(this != &fp)
      {
        data = fp.data;
      }
      return *this;
    }

    template<typename other_signed_type>
    fixed_point& operator=(const fixed_point<other_signed_type>& other)
    {
      // TBD: Needs compiler support for conditional compilation.
      const std::size_t other_decimal_split = fixed_point<other_signed_type>::decimal_split;
      const bool other_has_more_digits = (fixed_point<other_signed_type>::decimal_split > decimal_split);

      data = (other_has_more_digits ? signed_value_type(other.data >> (other_decimal_split - decimal_split))
                                    : signed_value_type(other.data << (decimal_split - other_decimal_split)));

      return *this;
    }

    // Self-operations and compound assign operations.
    void negate() { data = -data; }

    fixed_point& operator++() { data += decimal_split_value; return *this; }
    fixed_point& operator--() { data -= decimal_split_value; return *this; }

    fixed_point& operator+=(const fixed_point& v) { data += v.data; return *this; }
    fixed_point& operator-=(const fixed_point& v) { data -= v.data; return *this; }

    fixed_point& operator*=(const fixed_point& v)
    {
      const bool self_is_neg  = (  data < static_cast<signed_value_type>(0));
      const bool other_is_neg = (v.data < static_cast<signed_value_type>(0));

      const unsigned_value_type u_self  = unsigned_value_type((!self_is_neg)  ?   data :   -data);
      const unsigned_value_type v_other = unsigned_value_type((!other_is_neg) ? v.data : -v.data);

      // TBD: Needs compiler support for conditional compilation.
      if(std::numeric_limits<unsigned_value_type>::digits <= 16)
      {
        typedef typename util::utype_helper<std::numeric_limits<unsigned_value_type>::digits * 2>::exact_type unsigned_long_long_type;

        const unsigned_long_long_type result = (static_cast<unsigned_long_long_type>(u_self) * v_other) >> decimal_split;

        data = static_cast<signed_value_type>(result);
      }
      else
      {
        const unsigned_short_type self_upper = static_cast<unsigned_short_type>(u_self >> decimal_split);
        const unsigned_short_type self_lower = static_cast<unsigned_short_type>(u_self) & decimal_split_mask;

        const unsigned_short_type other_upper = static_cast<unsigned_short_type>(v_other >> decimal_split);
        const unsigned_short_type other_lower = static_cast<unsigned_short_type>(v_other) & decimal_split_mask;

        const unsigned_value_type lower_self_upper_other = static_cast<unsigned_value_type>(self_lower) * other_upper;
        const unsigned_short_type lower_self_lower_other = static_cast<unsigned_short_type>(static_cast<unsigned_value_type>(static_cast<unsigned_value_type>(self_lower) * other_lower) >> decimal_split);

        data =
          signed_value_type(  static_cast<unsigned_value_type>(static_cast<unsigned_value_type>(self_upper * v_other))
                            + static_cast<unsigned_value_type>(lower_self_upper_other + lower_self_lower_other));
      }

      if(self_is_neg != other_is_neg)
      {
        negate();
      }

      return *this;
    }

    fixed_point& operator/=(const fixed_point& v)
    {
      // TBD: Investigate other division algorithms.

      if(v.data == static_cast<signed_value_type>(0))
      {
        return (*this = value_max());
      }

      const bool a_is_neg = (  data < static_cast<signed_value_type>(0));
      const bool b_is_neg = (v.data < static_cast<signed_value_type>(0));

      unsigned_value_type a = unsigned_value_type((!a_is_neg) ?   data :   -data);
      unsigned_value_type b = unsigned_value_type((!b_is_neg) ? v.data : -v.data);

      const bool a_is_larger = (a > b);

      unsigned_value_type temp  = b;
      std::uint_least8_t  shift = decimal_split;

      if(a_is_larger)
      {
        const unsigned_value_type half_a = a >> 1U;

        while(temp < half_a)
        {
          temp <<= 1u;
          ++shift;
        }
      }

      unsigned_value_type d = static_cast<unsigned_value_type>(1U) << shift;

      data = static_cast<signed_value_type>(0U);

      if(a_is_larger)
      {
        a    -= temp;
        data += static_cast<signed_value_type>(d);
      }

      while(   (a     != static_cast<unsigned_value_type>(0U))
            && (temp  != static_cast<unsigned_value_type>(0U))
            && (shift != static_cast<std::uint_least8_t>(0U))
           )
      {
        std::uint_least8_t right_shift = static_cast<std::uint_least8_t>(0U);

        while((right_shift < shift) && (temp > a))
        {
          temp >>= 1u;
          ++right_shift;
        }

        d    >>= right_shift;
        shift -= right_shift;
        a     -= temp;
        data  += static_cast<signed_value_type>(d);
      }

      if(a_is_neg != b_is_neg)
      {
        data = -data;
      }

      return *this;
    }

    fixed_point& calculate_sqrt()
    {
      // TBD: Investigate other square root algorithms.

      if(data < static_cast<signed_value_type>(0))
      {
        data = signed_value_type(0);
        return *this;
      }

      const signed_value_type  ten_local = static_cast<signed_value_type>(0xAULL << decimal_split);
      const std::uint_least8_t max_shift = static_cast<std::uint_least8_t>(std::numeric_limits<unsigned_value_type>::digits - 2);

      const bool is_shifted_to_larger_value = (data < ten_local);

      unsigned_value_type a_squared = unsigned_value_type(1U) << max_shift;
      std::uint_least8_t  b_shift   = static_cast<std::uint_least8_t>((max_shift + decimal_split) / 2U);
      unsigned_value_type a         = unsigned_value_type(1U) << b_shift;

      const unsigned_value_type x = ((!is_shifted_to_larger_value) ? static_cast<unsigned_value_type>(data) : static_cast<unsigned_value_type>(data) << 6U);

      while((b_shift != static_cast<std::uint_least8_t>(0U)) && (a_squared > x))
      {
        a         >>= 1U;
        a_squared >>= 2U;
        --b_shift;
      }

      unsigned_value_type remainder = x - a_squared;

      --b_shift;

      while((remainder != static_cast<unsigned_value_type>(0U)) && (b_shift != static_cast<std::uint_least8_t>(0U)))
      {
        unsigned_value_type     b_squared     = unsigned_value_type(1U) << ((2U * b_shift) - decimal_split);
        const std::int_least8_t two_a_b_shift = static_cast<std::int_least8_t>(b_shift + 1U) - static_cast<std::int_least8_t>(decimal_split);
        unsigned_value_type     two_a_b       = ((two_a_b_shift > static_cast<std::int_least8_t>(0)) ? (a << two_a_b_shift) : (a >> (-two_a_b_shift)));

        while((b_shift != static_cast<std::uint_least8_t>(0U)) && (remainder < (b_squared + two_a_b)))
        {
          b_squared >>= 2U;
          two_a_b   >>= 1U;
          --b_shift;
        }

        const unsigned_value_type delta = b_squared + two_a_b;

        if((2u * remainder) > delta)
        {
          a += unsigned_value_type(unsigned_value_type(1U) << b_shift);
          remainder -= delta;

          if(b_shift != static_cast<std::uint_least8_t>(0U))
          {
            --b_shift;
          }
        }
      }

      data = ((!is_shifted_to_larger_value) ? static_cast<signed_value_type>(a) : static_cast<signed_value_type>(a >> 3U));

      return *this;
    }

    fixed_point& operator+=(const signed_value_type& n) { data += signed_value_type(n << decimal_split); return *this; }
    fixed_point& operator-=(const signed_value_type& n) { data -= signed_value_type(n << decimal_split); return *this; }
    fixed_point& operator*=(const signed_value_type& n) { data *= n; return *this; }
    fixed_point& operator/=(const signed_value_type& n) { data /= n; return *this; }

    // Special values.
    static fixed_point value_max         () { return fixed_point(internal(), signed_value_type((unsigned_value_type(-1LL) - 1U) / 2U)); }
    static fixed_point value_min         () { return fixed_point(internal(), signed_value_type(2L)); }
    static fixed_point value_half        () { return fixed_point(internal(), signed_value_type(1ULL << (decimal_split - 1U))); }
    static fixed_point value_eps         () { return fixed_point(internal(), signed_value_type(epsilon_helper<decimal_split>::epsilon_value)); }
    static fixed_point value_pi          () { return fixed_point(internal(), signed_value_type(0x3243f6A88ULL >> (32U - decimal_split))); }
    static fixed_point value_pi_half     () { return fixed_point(internal(), signed_value_type(0x1921FB544ULL >> (32U - decimal_split))); }
    static fixed_point value_two_over_pi () { return fixed_point(internal(), signed_value_type(0x0A2F98370ULL >> (32U - decimal_split))); }
    static fixed_point value_ln2         () { return fixed_point(internal(), signed_value_type(0x0B17217F7ULL >> (32U - decimal_split))); }
    static fixed_point value_one_over_ln2() { return fixed_point(internal(), signed_value_type(0x171547652ULL >> (32U - decimal_split))); }

    // Conversion operations.
    float             to_float      () const { return static_cast<float>      (data) / decimal_split_value; }
    double            to_double     () const { return static_cast<double>     (data) / decimal_split_value; }
    long double       to_long_double() const { return static_cast<long double>(data) / decimal_split_value; }
    signed_value_type to_int        () const { return static_cast<signed_value_type>(data >> decimal_split); }
    std::int8_t       to_int8       () const { return static_cast<std::int8_t>(to_int()); }
    std::int16_t      to_int16      () const { return static_cast<std::int16_t>(to_int()); }
    std::int32_t      to_int32      () const { return static_cast<std::int32_t>(to_int()); }

  private:
    signed_value_type data; // Internal data representation.

    // Internal structure for special constructor.
    typedef util::nothing internal;

    // Special private constructor from data representation.
    fixed_point(const internal&, const signed_value_type& n) : data(n) { }

    // Comparison functions.
    std::int_least8_t cmp(const          char  n) const { return ((data > (signed_value_type(n) << decimal_split)) ? 1 : ((data < (signed_value_type(n) << decimal_split)) ? -1 : 0)); }
    std::int_least8_t cmp(const   signed char  n) const { return ((data > (signed_value_type(n) << decimal_split)) ? 1 : ((data < (signed_value_type(n) << decimal_split)) ? -1 : 0)); }
    std::int_least8_t cmp(const unsigned char  n) const { return ((data > (signed_value_type(n) << decimal_split)) ? 1 : ((data < (signed_value_type(n) << decimal_split)) ? -1 : 0)); }
    std::int_least8_t cmp(const   signed short n) const { return ((data > (signed_value_type(n) << decimal_split)) ? 1 : ((data < (signed_value_type(n) << decimal_split)) ? -1 : 0)); }
    std::int_least8_t cmp(const unsigned short n) const { return ((data > (signed_value_type(n) << decimal_split)) ? 1 : ((data < (signed_value_type(n) << decimal_split)) ? -1 : 0)); }
    std::int_least8_t cmp(const   signed int   n) const { return ((data > (signed_value_type(n) << decimal_split)) ? 1 : ((data < (signed_value_type(n) << decimal_split)) ? -1 : 0)); }
    std::int_least8_t cmp(const unsigned int   n) const { return ((data > (signed_value_type(n) << decimal_split)) ? 1 : ((data < (signed_value_type(n) << decimal_split)) ? -1 : 0)); }
    std::int_least8_t cmp(const   signed long  n) const { return ((data > (signed_value_type(n) << decimal_split)) ? 1 : ((data < (signed_value_type(n) << decimal_split)) ? -1 : 0)); }
    std::int_least8_t cmp(const unsigned long  n) const { return ((data > (signed_value_type(n) << decimal_split)) ? 1 : ((data < (signed_value_type(n) << decimal_split)) ? -1 : 0)); }

    std::int_least8_t cmp(const float& f) const
    {
      const fixed_point other_fp(f);
      return ((data > other_fp.data) ? 1 : ((data < other_fp.data) ? -1 : 0));
    }

    std::int_least8_t cmp(const double& d) const
    {
      const fixed_point other_fp(d);
      return ((data > other_fp.data) ? 1 : ((data < other_fp.data) ? -1 : 0));
    }

    std::int_least8_t cmp(const fixed_point& other) const
    {
      return ((data > other.data) ? 1 : ((data < other.data) ? -1 : 0));
    }

    template<typename other_signed_type>
    std::int_least8_t cmp(const fixed_point<other_signed_type>& other) const
    {
      const fixed_point other_in_my_format(other);
      return ((data > other_in_my_format.data) ? 1 : ((data < other_in_my_format.data) ? -1 : 0));
    }

    // Global operators post-increment and post-decrement.
    friend inline fixed_point operator++(fixed_point& u, int) { const fixed_point v(u); ++u; return v; }
    friend inline fixed_point operator--(fixed_point& u, int) { const fixed_point v(u); --u; return v; }

    // Global unary operators of fixed_point reference.
    friend inline fixed_point operator+(const fixed_point& self) { return fixed_point(self); }
    friend inline fixed_point operator-(const fixed_point& self) { fixed_point tmp(self); tmp.data = -tmp.data; return tmp; }

    // Global add/sub/mul/div of const fixed_point reference with another.
    friend inline fixed_point operator+(const fixed_point& a, const fixed_point& b) { return fixed_point(internal(), a.data + b.data); }
    friend inline fixed_point operator-(const fixed_point& a, const fixed_point& b) { return fixed_point(internal(), a.data - b.data); }
    friend inline fixed_point operator*(const fixed_point& a, const fixed_point& b) { return fixed_point(a) *= b; }
    friend inline fixed_point operator/(const fixed_point& a, const fixed_point& b) { return fixed_point(a) /= b; }

    friend inline fixed_point operator+(const fixed_point& a, const char n) { return fixed_point(internal(), a.data + (signed_value_type(n) << decimal_split)); }
    friend inline fixed_point operator-(const fixed_point& a, const char n) { return fixed_point(internal(), a.data - (signed_value_type(n) << decimal_split)); }
    friend inline fixed_point operator*(const fixed_point& a, const char n) { return fixed_point(internal(), a.data * n); }
    friend inline fixed_point operator/(const fixed_point& a, const char n) { return fixed_point(internal(), a.data / n); }

    friend inline fixed_point operator+(const fixed_point& a, const signed char n) { return fixed_point(internal(), a.data + (signed_value_type(n) << decimal_split)); }
    friend inline fixed_point operator-(const fixed_point& a, const signed char n) { return fixed_point(internal(), a.data - (signed_value_type(n) << decimal_split)); }
    friend inline fixed_point operator*(const fixed_point& a, const signed char n) { return fixed_point(internal(), a.data * n); }
    friend inline fixed_point operator/(const fixed_point& a, const signed char n) { return fixed_point(internal(), a.data / n); }

    friend inline fixed_point operator+(const fixed_point& a, const unsigned char n) { return fixed_point(internal(), a.data + (signed_value_type(n) << decimal_split)); }
    friend inline fixed_point operator-(const fixed_point& a, const unsigned char n) { return fixed_point(internal(), a.data - (signed_value_type(n) << decimal_split)); }
    friend inline fixed_point operator*(const fixed_point& a, const unsigned char n) { return fixed_point(internal(), a.data * n); }
    friend inline fixed_point operator/(const fixed_point& a, const unsigned char n) { return fixed_point(internal(), a.data / n); }

    friend inline fixed_point operator+(const fixed_point& a, const signed short n) { return fixed_point(internal(), a.data + (signed_value_type(n) << decimal_split)); }
    friend inline fixed_point operator-(const fixed_point& a, const signed short n) { return fixed_point(internal(), a.data - (signed_value_type(n) << decimal_split)); }
    friend inline fixed_point operator*(const fixed_point& a, const signed short n) { return fixed_point(internal(), a.data * n); }
    friend inline fixed_point operator/(const fixed_point& a, const signed short n) { return fixed_point(internal(), a.data / n); }

    friend inline fixed_point operator+(const fixed_point& a, const unsigned short n) { return fixed_point(internal(), a.data + (signed_value_type(n) << decimal_split)); }
    friend inline fixed_point operator-(const fixed_point& a, const unsigned short n) { return fixed_point(internal(), a.data - (signed_value_type(n) << decimal_split)); }
    friend inline fixed_point operator*(const fixed_point& a, const unsigned short n) { return fixed_point(internal(), a.data * n); }
    friend inline fixed_point operator/(const fixed_point& a, const unsigned short n) { return fixed_point(internal(), a.data / n); }

    friend inline fixed_point operator+(const fixed_point& a, const signed int n) { return fixed_point(internal(), a.data + (signed_value_type(n) << decimal_split)); }
    friend inline fixed_point operator-(const fixed_point& a, const signed int n) { return fixed_point(internal(), a.data - (signed_value_type(n) << decimal_split)); }
    friend inline fixed_point operator*(const fixed_point& a, const signed int n) { return fixed_point(internal(), a.data * n); }
    friend inline fixed_point operator/(const fixed_point& a, const signed int n) { return fixed_point(internal(), a.data / n); }

    friend inline fixed_point operator+(const fixed_point& a, const unsigned int n) { return fixed_point(internal(), a.data + signed_value_type(n << decimal_split)); }
    friend inline fixed_point operator-(const fixed_point& a, const unsigned int n) { return fixed_point(internal(), a.data - signed_value_type(n << decimal_split)); }
    friend inline fixed_point operator*(const fixed_point& a, const unsigned int n) { return fixed_point(internal(), a.data * signed_value_type(n)); }
    friend inline fixed_point operator/(const fixed_point& a, const unsigned int n) { return fixed_point(internal(), a.data / signed_value_type(n)); }

    friend inline fixed_point operator+(const fixed_point& a, const signed long n) { return fixed_point(internal(), a.data + (signed_value_type(n) << decimal_split)); }
    friend inline fixed_point operator-(const fixed_point& a, const signed long n) { return fixed_point(internal(), a.data - (signed_value_type(n) << decimal_split)); }
    friend inline fixed_point operator*(const fixed_point& a, const signed long n) { return fixed_point(internal(), a.data * n); }
    friend inline fixed_point operator/(const fixed_point& a, const signed long n) { return fixed_point(internal(), a.data / n); }

    friend inline fixed_point operator+(const fixed_point& a, const unsigned long n) { return fixed_point(internal(), a.data + signed_value_type(n << decimal_split)); }
    friend inline fixed_point operator-(const fixed_point& a, const unsigned long n) { return fixed_point(internal(), a.data - signed_value_type(n << decimal_split)); }
    friend inline fixed_point operator*(const fixed_point& a, const unsigned long n) { return fixed_point(internal(), a.data * signed_value_type(n)); }
    friend inline fixed_point operator/(const fixed_point& a, const unsigned long n) { return fixed_point(internal(), a.data / signed_value_type(n)); }

    friend inline fixed_point operator+(const fixed_point& a, const float& f) { return fixed_point(a) += fixed_point(f); }
    friend inline fixed_point operator-(const fixed_point& a, const float& f) { return fixed_point(a) -= fixed_point(f); }
    friend inline fixed_point operator*(const fixed_point& a, const float& f) { return fixed_point(a) *= fixed_point(f); }
    friend inline fixed_point operator/(const fixed_point& a, const float& f) { return fixed_point(a) /= fixed_point(f); }

    friend inline fixed_point operator+(const fixed_point& a, const double& d) { return fixed_point(a) += fixed_point(d); }
    friend inline fixed_point operator-(const fixed_point& a, const double& d) { return fixed_point(a) -= fixed_point(d); }
    friend inline fixed_point operator*(const fixed_point& a, const double& d) { return fixed_point(a) *= fixed_point(d); }
    friend inline fixed_point operator/(const fixed_point& a, const double& d) { return fixed_point(a) /= fixed_point(d); }

    // Global add/sub/mul/div of another with const fixed_point reference.
    friend inline fixed_point operator+(const char& n, const fixed_point& a) { return fixed_point(internal(), (signed_value_type(n) << decimal_split) + a.data); }
    friend inline fixed_point operator-(const char& n, const fixed_point& a) { return fixed_point(internal(), (signed_value_type(n) << decimal_split) - a.data); }
    friend inline fixed_point operator*(const char& n, const fixed_point& a) { return fixed_point(internal(), n * a.data); }
    friend inline fixed_point operator/(const char& n, const fixed_point& a) { return fixed_point(n) /= a; }

    friend inline fixed_point operator+(const signed char& n, const fixed_point& a) { return fixed_point(internal(), (signed_value_type(n) << decimal_split) + a.data); }
    friend inline fixed_point operator-(const signed char& n, const fixed_point& a) { return fixed_point(internal(), (signed_value_type(n) << decimal_split) - a.data); }
    friend inline fixed_point operator*(const signed char& n, const fixed_point& a) { return fixed_point(internal(), n * a.data); }
    friend inline fixed_point operator/(const signed char& n, const fixed_point& a) { return fixed_point(n) /= a; }

    friend inline fixed_point operator+(const unsigned char& n, const fixed_point& a) { return fixed_point(internal(), (signed_value_type(n) << decimal_split) + a.data); }
    friend inline fixed_point operator-(const unsigned char& n, const fixed_point& a) { return fixed_point(internal(), (signed_value_type(n) << decimal_split) - a.data); }
    friend inline fixed_point operator*(const unsigned char& n, const fixed_point& a) { return fixed_point(internal(), n * a.data); }
    friend inline fixed_point operator/(const unsigned char& n, const fixed_point& a) { return fixed_point(n) /= a; }

    friend inline fixed_point operator+(const signed short& n, const fixed_point& a) { return fixed_point(internal(), (signed_value_type(n) << decimal_split) + a.data); }
    friend inline fixed_point operator-(const signed short& n, const fixed_point& a) { return fixed_point(internal(), (signed_value_type(n) << decimal_split) - a.data); }
    friend inline fixed_point operator*(const signed short& n, const fixed_point& a) { return fixed_point(internal(), n * a.data); }
    friend inline fixed_point operator/(const signed short& n, const fixed_point& a) { return fixed_point(n) /= a; }

    friend inline fixed_point operator+(const unsigned short& n, const fixed_point& a) { return fixed_point(internal(), (signed_value_type(n) << decimal_split) + a.data); }
    friend inline fixed_point operator-(const unsigned short& n, const fixed_point& a) { return fixed_point(internal(), (signed_value_type(n) << decimal_split) - a.data); }
    friend inline fixed_point operator*(const unsigned short& n, const fixed_point& a) { return fixed_point(internal(), n * a.data); }
    friend inline fixed_point operator/(const unsigned short& n, const fixed_point& a) { return fixed_point(n) /= a; }

    friend inline fixed_point operator+(const signed int& n, const fixed_point& a) { return fixed_point(internal(), (signed_value_type(n) << decimal_split) + a.data); }
    friend inline fixed_point operator-(const signed int& n, const fixed_point& a) { return fixed_point(internal(), (signed_value_type(n) << decimal_split) - a.data); }
    friend inline fixed_point operator*(const signed int& n, const fixed_point& a) { return fixed_point(internal(), n * a.data); }
    friend inline fixed_point operator/(const signed int& n, const fixed_point& a) { return fixed_point(n) /= a; }

    friend inline fixed_point operator+(const unsigned int& n, const fixed_point& a) { return fixed_point(internal(), (signed_value_type(n) << decimal_split) + a.data); }
    friend inline fixed_point operator-(const unsigned int& n, const fixed_point& a) { return fixed_point(internal(), (signed_value_type(n) << decimal_split) - a.data); }
    friend inline fixed_point operator*(const unsigned int& n, const fixed_point& a) { return fixed_point(internal(), n * a.data); }
    friend inline fixed_point operator/(const unsigned int& n, const fixed_point& a) { return fixed_point(n) /= a; }

    friend inline fixed_point operator+(const signed long& n, const fixed_point& a) { return fixed_point(internal(), (signed_value_type(n) << decimal_split) + a.data); }
    friend inline fixed_point operator-(const signed long& n, const fixed_point& a) { return fixed_point(internal(), (signed_value_type(n) << decimal_split) - a.data); }
    friend inline fixed_point operator*(const signed long& n, const fixed_point& a) { return fixed_point(internal(), n * a.data); }
    friend inline fixed_point operator/(const signed long& n, const fixed_point& a) { return fixed_point(n) /= a; }

    friend inline fixed_point operator+(const unsigned long& n, const fixed_point& a) { return fixed_point(internal(), (signed_value_type(n) << decimal_split) + a.data); }
    friend inline fixed_point operator-(const unsigned long& n, const fixed_point& a) { return fixed_point(internal(), (signed_value_type(n) << decimal_split) - a.data); }
    friend inline fixed_point operator*(const unsigned long& n, const fixed_point& a) { return fixed_point(internal(), n * a.data); }
    friend inline fixed_point operator/(const unsigned long& n, const fixed_point& a) { return fixed_point(n) /= a; }

    friend inline fixed_point operator+(const float& f, const fixed_point& a) { return fixed_point(signed_value_type(signed_value_type(f * decimal_split_value) + a.data)); }
    friend inline fixed_point operator-(const float& f, const fixed_point& a) { return fixed_point(signed_value_type(signed_value_type(f * decimal_split_value) - a.data)); }
    friend inline fixed_point operator*(const float& f, const fixed_point& a) { return fixed_point(f) *= a; }
    friend inline fixed_point operator/(const float& f, const fixed_point& a) { return fixed_point(f) /= a; }

    friend inline fixed_point operator+(const double& d, const fixed_point& a) { return fixed_point(signed_value_type(signed_value_type(d * decimal_split_value) + a.data)); }
    friend inline fixed_point operator-(const double& d, const fixed_point& a) { return fixed_point(signed_value_type(signed_value_type(d * decimal_split_value) + a.data)); }
    friend inline fixed_point operator*(const double& d, const fixed_point& a) { return fixed_point(d) *= a; }
    friend inline fixed_point operator/(const double& d, const fixed_point& a) { return fixed_point(d) /= a; }

    // Global comparison operators of fixed_point with another.
    friend inline bool operator< (const fixed_point& a, const fixed_point& b) { return (a.cmp(b) <  std::int_least8_t(0)); }
    friend inline bool operator<=(const fixed_point& a, const fixed_point& b) { return (a.cmp(b) <= std::int_least8_t(0)); }
    friend inline bool operator==(const fixed_point& a, const fixed_point& b) { return (a.cmp(b) == std::int_least8_t(0)); }
    friend inline bool operator!=(const fixed_point& a, const fixed_point& b) { return (a.cmp(b) != std::int_least8_t(0)); }
    friend inline bool operator>=(const fixed_point& a, const fixed_point& b) { return (a.cmp(b) >= std::int_least8_t(0)); }
    friend inline bool operator> (const fixed_point& a, const fixed_point& b) { return (a.cmp(b) >  std::int_least8_t(0)); }

    template<typename other_type> friend inline bool operator< (const fixed_point& a, const other_type n) { return (a.cmp(n) <  std::int_least8_t(0)); }
    template<typename other_type> friend inline bool operator<=(const fixed_point& a, const other_type n) { return (a.cmp(n) <= std::int_least8_t(0)); }
    template<typename other_type> friend inline bool operator==(const fixed_point& a, const other_type n) { return (a.cmp(n) == std::int_least8_t(0)); }
    template<typename other_type> friend inline bool operator!=(const fixed_point& a, const other_type n) { return (a.cmp(n) != std::int_least8_t(0)); }
    template<typename other_type> friend inline bool operator>=(const fixed_point& a, const other_type n) { return (a.cmp(n) >= std::int_least8_t(0)); }
    template<typename other_type> friend inline bool operator> (const fixed_point& a, const other_type n) { return (a.cmp(n) >  std::int_least8_t(0)); }

    template<typename other_signed_type> friend inline bool operator< (const fixed_point& a, const fixed_point<other_signed_type>& b) { return (a.cmp(b) <  std::int_least8_t(0)); }
    template<typename other_signed_type> friend inline bool operator<=(const fixed_point& a, const fixed_point<other_signed_type>& b) { return (a.cmp(b) <= std::int_least8_t(0)); }
    template<typename other_signed_type> friend inline bool operator==(const fixed_point& a, const fixed_point<other_signed_type>& b) { return (a.cmp(b) == std::int_least8_t(0)); }
    template<typename other_signed_type> friend inline bool operator!=(const fixed_point& a, const fixed_point<other_signed_type>& b) { return (a.cmp(b) != std::int_least8_t(0)); }
    template<typename other_signed_type> friend inline bool operator>=(const fixed_point& a, const fixed_point<other_signed_type>& b) { return (a.cmp(b) >= std::int_least8_t(0)); }
    template<typename other_signed_type> friend inline bool operator> (const fixed_point& a, const fixed_point<other_signed_type>& b) { return (a.cmp(b) >  std::int_least8_t(0)); }

    // Global comparison operators of another with fixed_point.
    template<typename other_type> friend inline bool operator< (const other_type n, const fixed_point& a) { return (std::int_least8_t(-a.cmp(n)) <  std::int_least8_t(0)); }
    template<typename other_type> friend inline bool operator<=(const other_type n, const fixed_point& a) { return (std::int_least8_t(-a.cmp(n)) <= std::int_least8_t(0)); }
    template<typename other_type> friend inline bool operator==(const other_type n, const fixed_point& a) { return (std::int_least8_t(-a.cmp(n)) == std::int_least8_t(0)); }
    template<typename other_type> friend inline bool operator!=(const other_type n, const fixed_point& a) { return (std::int_least8_t(-a.cmp(n)) != std::int_least8_t(0)); }
    template<typename other_type> friend inline bool operator>=(const other_type n, const fixed_point& a) { return (std::int_least8_t(-a.cmp(n)) >= std::int_least8_t(0)); }
    template<typename other_type> friend inline bool operator> (const other_type n, const fixed_point& a) { return (std::int_least8_t(-a.cmp(n)) >  std::int_least8_t(0)); }

    template<typename other_signed_type> friend inline bool operator< (const fixed_point<other_signed_type>& b, const fixed_point& a) { return (std::int_least8_t(-a.cmp(b)) <  std::int_least8_t(0)); }
    template<typename other_signed_type> friend inline bool operator<=(const fixed_point<other_signed_type>& b, const fixed_point& a) { return (std::int_least8_t(-a.cmp(b)) <= std::int_least8_t(0)); }
    template<typename other_signed_type> friend inline bool operator==(const fixed_point<other_signed_type>& b, const fixed_point& a) { return (std::int_least8_t(-a.cmp(b)) == std::int_least8_t(0)); }
    template<typename other_signed_type> friend inline bool operator!=(const fixed_point<other_signed_type>& b, const fixed_point& a) { return (std::int_least8_t(-a.cmp(b)) != std::int_least8_t(0)); }
    template<typename other_signed_type> friend inline bool operator>=(const fixed_point<other_signed_type>& b, const fixed_point& a) { return (std::int_least8_t(-a.cmp(b)) >= std::int_least8_t(0)); }
    template<typename other_signed_type> friend inline bool operator> (const fixed_point<other_signed_type>& b, const fixed_point& a) { return (std::int_least8_t(-a.cmp(b)) >  std::int_least8_t(0)); }

    // Include a few global sample fixed_point functions.
    friend inline fixed_point fabs(const fixed_point& x)
    {
      return fixed_point(internal(), (x.data < signed_value_type(0) ? -x.data : x.data));
    }

    friend inline fixed_point floor(const fixed_point& x)
    {
      fixed_point res(x);

      const signed_value_type remainder = x.data % decimal_split_value;

      if(remainder != static_cast<signed_value_type>(0))
      {
        res.data -= remainder;

        if(x.data < static_cast<signed_value_type>(0))
        {
          --res;
        }
      }

      return res;
    }

    friend inline fixed_point sin(const fixed_point& x)
    {
      // This function makes heavy use of fixed_point's internals
      // and is, therefore, a friend of the fixed_point class.

      // Scale x to chi (+-pi/2 to +-1).
      fixed_point chi(x * value_two_over_pi());

      // Take the absolute value of chi for argument reduction.
      const bool is_neg = (chi < 0);

      if(is_neg)
      {
        chi.negate();
      }

      // Do the argument reduction.
      std::uint_fast8_t npi = 0U;

      // Remove multiples of pi (1 in the units of chi).
      if(chi.data > decimal_split_value)
      {
        const std::uint_fast8_t npi1 = static_cast<std::uint_fast8_t>((chi.data >> 1) >> decimal_split);
        npi = ((chi - (npi1 * 2U) > 1) ? npi1 + 1 : npi1);
        chi -= fixed_point(npi * 2);
      }

      const fixed_point chi2(chi * chi);

      // Do the order-5 polynomial expansion.
      const fixed_point sum =
        ((         fixed_point(internal(), unsigned_value_type(0x012808B37ULL >> (32U - decimal_split)))
          * chi2 - fixed_point(internal(), unsigned_value_type(0x0A47F11EEULL >> (32U - decimal_split))))
          * chi2 + fixed_point(internal(), unsigned_value_type(0x19206922FULL >> (32U - decimal_split))))
          * chi;

      // Reflect the result if necessary.
      const bool needs_reflect = ((npi % 2) != 0);

      return ((is_neg == needs_reflect) ? sum : -sum);
    }

    friend inline fixed_point cos(const fixed_point& x)
    {
      return -sin(x - value_pi_half());
    }

    friend inline fixed_point tan(const fixed_point& x)
    {
      const fixed_point s(sin(x));
      const fixed_point c(cos(x));

      if(s.data >= decimal_split_value || c.data == 0)
      {
        return fixed_point(0);
      }
      else
      {
        return fixed_point( internal(),
                           (s.data << decimal_split) / c.data);
      }
    }

    friend inline fixed_point asin(const fixed_point& x)
    {
      if(x.data < signed_value_type(0))
      {
        return -asin(-x);
      }
      else
      {
        if(x.data > decimal_split_value)
        {
          return fixed_point(0);
        }
        else if(x.data == decimal_split_value)
        {
          return value_pi_half();
        }

        // Do the order-3 polynomial expansion.
        // See Abramowitz & Stegun 4.4.45, page 81.
        fixed_point sum =
          (((    - fixed_point(internal(), // Approx. 0.0187293
                               unsigned_value_type(0x004CB7182ULL >> (32U - decimal_split)))
             * x + fixed_point(internal(), // Approx. 0.0742610
                               unsigned_value_type(0x01302C4D6ULL >> (32U - decimal_split))))
             * x - fixed_point(internal(), // Approx. 0.2121144
                               unsigned_value_type(0x0364D211BULL >> (32U - decimal_split))))
             * x + fixed_point(internal(), // Approx. 1.5707288
                               unsigned_value_type(0x1921B485AULL >> (32U - decimal_split))));

        return value_pi_half() - (sqrt(1 - x) * sum);
      }
    }

    friend inline fixed_point acos(const fixed_point& x)
    {
      if(x.data < signed_value_type(0))
      {
        return value_pi() - acos(-x);
      }
      else
      {
        if(x.data > decimal_split_value)
        {
          return fixed_point(0);
        }
        else if(x.data == signed_value_type(0))
        {
          return value_pi_half();
        }

        return value_pi_half() - asin(x);
      }
    }

    friend inline fixed_point atan(const fixed_point& x)
    {
      if(x.data < signed_value_type(0))
      {
        return -atan(-x);
      }
      else
      {
        if(x.data == signed_value_type(decimal_split_value))
        {
          fixed_point result(value_pi_half());
          result.data >>= 1;
          return result;
        }
        else if(x.data > signed_value_type(decimal_split_value))
        {
          return value_pi_half() - atan(1 / x);
        }

        const fixed_point x2(x * x);

        // Do the order-6 polynomial expansion.
        const fixed_point sum =
          ((     - fixed_point(internal(), unsigned_value_type(0x0C6A271FULL >> (32U - decimal_split)))
            * x2 + fixed_point(internal(), unsigned_value_type(0x2968EA48ULL >> (32U - decimal_split))))
            * x2 - fixed_point(internal(), unsigned_value_type(0x5408643BULL >> (32U - decimal_split))))
            * x2;

        return x * (1 + sum);
      }
    }

    friend inline fixed_point atan2(const fixed_point& y, const fixed_point& x)
    {
      // Handle the negative arguments and zero arguments.
      const bool x_is_neg = (x.data < 0);

      if(y.data == 0)
      {
        return ((!x_is_neg) ? fixed_point(0U) : value_pi());
      }

      const bool y_is_neg = (y.data < 0);

      if(x.data == 0)
      {
        return ((!y_is_neg) ? value_pi_half() : -value_pi_half());
      }

      // Compute atan(y / x), thereby ignoring the sign of the arguments.
      const fixed_point atan_term(atan(y / x));

      // Determine the proper quadrant based on signs of x and y.
      return ((y_is_neg == x_is_neg) ? ((!x_is_neg) ? atan_term : (atan_term - value_pi()))
                                     : ((!x_is_neg) ? atan_term : (atan_term + value_pi())));
    }

    friend inline fixed_point exp(const fixed_point& x)
    {
      const fixed_point x_over_ln2 = x * value_one_over_ln2();
      const std::int_fast8_t n     = x_over_ln2.to_int8();
      const fixed_point alpha      = x - (value_ln2() * n);

      // Do the order-4 polynomial expansion.
      fixed_point sum =
        (((          fixed_point(internal(), unsigned_value_type(0x0B238740ULL >> (32U - decimal_split)))
           * alpha + fixed_point(internal(), unsigned_value_type(0x2D26bC00ULL >> (32U - decimal_split))))
           * alpha + fixed_point(internal(), unsigned_value_type(0x7FDD6C80ULL >> (32U - decimal_split))))
           * alpha + fixed_point(internal(), unsigned_value_type(0xFF735F00ULL >> (32U - decimal_split))))
           * alpha;

      sum.data += decimal_split_value;

      // Scale the result by 2^n if necessary.
      if(n > 0)
      {
        sum.data <<= n;
      }
      else if(n < 0)
      {
        sum.data >>= (-n);
      }

      return sum;
    }

    friend inline fixed_point log(const fixed_point& x)
    {
      // Check for negative arguments.
      if(x.data < signed_value_type(0))
      {
        return fixed_point(0);
      }

      unsigned_value_type x2_data(x.data);

      if(x2_data == unsigned_value_type(decimal_split_value))
      {
        // The argument is identically equal to one.
        return fixed_point(0);
      }
      else if(x2_data < unsigned_value_type(decimal_split_value))
      {
        // Invert and negate for (0 < x < 1).
        return -log(1 / x);
      }

      std::uint_fast8_t n2 = 0U;

      // Remove even powers of two from the argument.
      while(x2_data > unsigned_value_type(decimal_split_value * 2))
      {
        ++n2;
        x2_data >>= 1;
      }

      const fixed_point my_x2 = fixed_point(internal(), x2_data - decimal_split_value);

      // Do the order-4 polynomial expansion.
      const fixed_point sum =
        (((        - fixed_point(internal(), unsigned_value_type(0x0154E1943ULL >> (32U - decimal_split)))
           * my_x2 + fixed_point(internal(), unsigned_value_type(0x0526502D0ULL >> (32U - decimal_split))))
           * my_x2 - fixed_point(internal(), unsigned_value_type(0x0AD5C5271ULL >> (32U - decimal_split))))
           * my_x2 + fixed_point(internal(), unsigned_value_type(0x1703C3967ULL >> (32U - decimal_split))))
           * my_x2;

      // Re-scale the result and return (be sure to account for 2^n).
      return (sum + n2) * value_ln2();
    }

    friend inline fixed_point sinh(const fixed_point& x)
    {
      // Compute exp(x) and exp(-x)
      const fixed_point ep = exp(x);
      const fixed_point em = 1 / ep;

      // Subtract exp(-x) from exp(x) and divide by two.
      fixed_point result(ep - em);
      result.data >>= 1;

      return result;
    }

    friend inline fixed_point cosh(const fixed_point& x)
    {
      // Compute exp(x) and exp(-x)
      const fixed_point ep = exp(x);
      const fixed_point em = 1 / ep;

      // Subtract exp(x) and exp(-x) and divide by two.
      fixed_point result(ep + em);
      result.data >>= 1;

      return result;
    }

    friend inline fixed_point pow(const fixed_point& x, const int n)
    {
      return exp(fixed_point(n) * log(x));
    }

    friend inline fixed_point pow(const fixed_point& x, const fixed_point& a)
    {
      return exp(a * log(x));
    }

    friend inline fixed_point tanh(const fixed_point& x)
    {
      // Compute exp(x) and exp(-x)
      const fixed_point ep = exp(x);
      const fixed_point em = 1 / ep;

      // Do the division and return the result.
      return (ep - em) / (ep + em);
    }

  public:
    // Implement my_numeric_limits for the fixed_point class.
    class my_numeric_limits
    {
    public:
      static const bool is_specialized    = true;
      static const int digits             = fixed_point::decimal_split;
      static const int digits10           = static_cast<int>((my_numeric_limits::digits * 643LL) / 2136LL);
      static const int max_digits10       = my_numeric_limits::digits10 + 1;
      static const bool is_signed         = true;
      static const bool is_integer        = false;
      static const bool is_exact          = false;
      static const int radix              = 2;
      static const int min_exponent       = -(static_cast<int>(fixed_point::decimal_split) - 1);
      static const int min_exponent10     = static_cast<int>((my_numeric_limits::min_exponent * 643LL) / 2136LL);
      static const int max_exponent       = (static_cast<int>(fixed_point::decimal_split) - 2);
      static const int max_exponent10     = static_cast<int>((my_numeric_limits::max_exponent * 643LL) / 2136LL);
      static const bool has_infinity      = false;
      static const bool has_quiet_NaN     = false;
      static const bool has_signaling_NaN = false;
      static const std::float_denorm_style has_denorm =
                                            std::denorm_absent;
      static const bool has_denorm_loss   = false;
      static const bool is_iec559         = false;
      static const bool is_bounded        = true;
      static const bool is_modulo         = false;
      static const bool traps             = false;
      static const bool tinyness_before   = false;
      static const std::float_round_style round_style = std::round_toward_zero;

      static fixed_point (min)      () throw() { return fixed_point::value_min(); }
      static fixed_point (max)      () throw() { return fixed_point::value_max(); }
      static fixed_point lowest     () throw() { return fixed_point::value_min(); }
      static fixed_point epsilon    () throw() { return fixed_point::value_eps(); }
      static fixed_point round_error() throw() { return fixed_point::value_half(); }
      static fixed_point infinity   () throw() { return fixed_point(internal(), signed_value_type(0)); }
      static fixed_point quiet_NaN  () throw() { return fixed_point(internal(), signed_value_type(0)); }
    };

    #if !defined(FIXED_POINT_DISABLE_IOSTREAM)

    template<typename char_type, typename traits_type>
    friend std::basic_ostream<char_type, traits_type>& operator<<(std::basic_ostream<char_type, traits_type>& out,
                                                                  const fixed_point& x)
    {
      typedef long double local_float_type;

      std::basic_ostringstream<char_type, traits_type> ostr;

      // Copy all ostream settings from out to local ostr.
      ostr.flags(out.flags());
      ostr.imbue(out.getloc());
      ostr.precision(out.precision());

      static_cast<void>(ostr << x.to_long_double());

      return (out << ostr.str());
    }

    template<typename char_type, typename traits_type>
    friend std::basic_istream<char_type, traits_type>& operator>>(std::basic_istream<char_type, traits_type>& in,
                                                                  fixed_point& x)
    {
      typedef long double local_float_type;

      local_float_type v;

      // Receive a floating-point number from the input stream.
      static_cast<void>(in >> v);

      // Subsequently make a fixed-point object from it.
      x = fixed_point(v);

      return in;
    }

    #endif // !FIXED_POINT_DISABLE_IOSTREAM
  };

  // Define the four scalable fixed_point types.
  typedef fixed_point<std::int8_t>  fixed_point_3pt4;
  typedef fixed_point<std::int16_t> fixed_point_7pt8;
  typedef fixed_point<std::int32_t> fixed_point_15pt16;
  typedef fixed_point<std::int64_t> fixed_point_31pt32;

  namespace std
  {
    // Make numeric_limits specializations for the fixed_point types.
    template<> class numeric_limits<fixed_point_3pt4> : public fixed_point_3pt4::my_numeric_limits { };
    template<> class numeric_limits<fixed_point_7pt8> : public fixed_point_7pt8::my_numeric_limits { };
    template<> class numeric_limits<fixed_point_15pt16> : public fixed_point_15pt16::my_numeric_limits { };
    template<> class numeric_limits<fixed_point_31pt32> : public fixed_point_31pt32::my_numeric_limits { };
  }

  // Include a few more global sample fixed_point functions.
  template<typename fixed_point_type>
  inline fixed_point_type sqrt(const fixed_point_type& x) { return fixed_point_type(x).calculate_sqrt(); }

  template<typename fixed_point_type>
  inline fixed_point_type const_pi() { return fixed_point_type::value_pi(); }

  template<typename fixed_point_type>
  inline fixed_point_type const_half() { return fixed_point_type::value_half(); }

  template<typename fixed_point_type>
  inline fixed_point_type hypot(const fixed_point_type& x,
                                const fixed_point_type& y)
  {
    return sqrt<fixed_point_type>((x * x) + (y * y));
  }

#endif // FIXED_POINT_2011_02_22_H_
