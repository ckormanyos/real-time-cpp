
//  Copyright (c) 2014 Christopher Kormanyos
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

// This file is a partial reference implementation for the proposed
// "C++ binary fixed-point arithmetic" as specified in N3352.
// See: http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2012/n3352.html

#ifndef _FIXED_POINT_2014_03_03_HPP_
  #define _FIXED_POINT_2014_03_03_HPP_

  #include <algorithm>
  #include <cmath>
  #include <limits>
  #include <sstream>
  #include <cstdint>
  #include <type_traits>

  namespace math { namespace fixed_point {

  namespace round
  {
    typedef enum enum_round_type
    {
      fastest,       // Speed is more important than the choice in value.
      negative,      // Round towards negative infinity. This mode is useful in interval arithmetic.
      truncated,     // Round towards zero. This mode is useful in implementing integral arithmetic.
      positive,      // Round towards positive infinity. This mode is useful in interval arithmetic.
      classic,       // Round towards the nearest value, but exactly-half values are rounded towards maximum magnitude. This mode is the standard school algorithm.
      nearest_even,  // Round towards the nearest value, but exactly-half values are rounded towards even values. This mode has more balance than the classic mode.
      nearest_odd,   // Round towards the nearest value, but exactly-half values are rounded towards odd values. This mode has as much balance as the near_even mode, but preserves more information.
    }
    round_type;
  }

  namespace overflow
  {
    typedef enum enum_overflow_type
    {
      impossible, // Programmer analysis of the program has determined that overflow cannot occur. Uses of this mode should be accompanied by an argument supporting the conclusion.
      undefined,  // Programmers are willing to accept undefined behavior in the event of an overflow.
      modulus,    // The assigned value is the dynamic value mod the range of the variable. This mode makes sense only with unsigned numbers. It is useful for angular measures.
      saturate,   // If the dynamic value exceeds the range of the variable, assign the nearest representable value.
      exception   // If the dynamic value exceeds the range of the variable, throw an exeception of type std::overflow_error.
    }
    overflow_type;
  }
  } } // namespace math::fixed_point

  // Forward declaration of the negatable class.
  namespace math
  {
    namespace fixed_point
    {
      template<const int range,
               const int resolution,
               const math::fixed_point::round::round_type round_mode,
               const math::fixed_point::overflow::overflow_type overflow_mode>
      class negatable;
    }
  }

  // Forward declaration of the specialization of std::numeric_limits<negatable>.
  namespace std
  {
    template<const int range,
             const int resolution,
             const math::fixed_point::round::round_type round_mode,
             const math::fixed_point::overflow::overflow_type overflow_mode>
    class numeric_limits<math::fixed_point::negatable<range, resolution, round_mode, overflow_mode> >;
  }

  namespace math { namespace fixed_point {

  namespace detail
  {
    template<const unsigned bit_count> struct integer_type_helper
    {
      // TBD: Add support for larger integer types using cpp_int from Boost.Multiprecision.
      // TBD: But this also requires modifications of some helper functions and some internals of the negatable class.
      static_assert(bit_count <= 64U, "Error: The integer type helper class does not support the requested digits.");

      typedef std::int64_t  exact_signed_type;
      typedef std::uint64_t exact_unsigned_type;
    };

    template<> struct integer_type_helper< 0U> { typedef std::int8_t  exact_signed_type; typedef std::uint8_t  exact_unsigned_type; };
    template<> struct integer_type_helper< 1U> { typedef std::int8_t  exact_signed_type; typedef std::uint8_t  exact_unsigned_type; };
    template<> struct integer_type_helper< 2U> { typedef std::int8_t  exact_signed_type; typedef std::uint8_t  exact_unsigned_type; };
    template<> struct integer_type_helper< 3U> { typedef std::int8_t  exact_signed_type; typedef std::uint8_t  exact_unsigned_type; };
    template<> struct integer_type_helper< 4U> { typedef std::int8_t  exact_signed_type; typedef std::uint8_t  exact_unsigned_type; };
    template<> struct integer_type_helper< 5U> { typedef std::int8_t  exact_signed_type; typedef std::uint8_t  exact_unsigned_type; };
    template<> struct integer_type_helper< 6U> { typedef std::int8_t  exact_signed_type; typedef std::uint8_t  exact_unsigned_type; };
    template<> struct integer_type_helper< 7U> { typedef std::int8_t  exact_signed_type; typedef std::uint8_t  exact_unsigned_type; };
    template<> struct integer_type_helper< 8U> { typedef std::int8_t  exact_signed_type; typedef std::uint8_t  exact_unsigned_type; };

    template<> struct integer_type_helper< 9U> { typedef std::int16_t exact_signed_type; typedef std::uint16_t exact_unsigned_type; };
    template<> struct integer_type_helper<10U> { typedef std::int16_t exact_signed_type; typedef std::uint16_t exact_unsigned_type; };
    template<> struct integer_type_helper<11U> { typedef std::int16_t exact_signed_type; typedef std::uint16_t exact_unsigned_type; };
    template<> struct integer_type_helper<12U> { typedef std::int16_t exact_signed_type; typedef std::uint16_t exact_unsigned_type; };
    template<> struct integer_type_helper<13U> { typedef std::int16_t exact_signed_type; typedef std::uint16_t exact_unsigned_type; };
    template<> struct integer_type_helper<14U> { typedef std::int16_t exact_signed_type; typedef std::uint16_t exact_unsigned_type; };
    template<> struct integer_type_helper<15U> { typedef std::int16_t exact_signed_type; typedef std::uint16_t exact_unsigned_type; };
    template<> struct integer_type_helper<16U> { typedef std::int16_t exact_signed_type; typedef std::uint16_t exact_unsigned_type; };

    template<> struct integer_type_helper<17U> { typedef std::int32_t exact_signed_type; typedef std::uint32_t exact_unsigned_type; };
    template<> struct integer_type_helper<18U> { typedef std::int32_t exact_signed_type; typedef std::uint32_t exact_unsigned_type; };
    template<> struct integer_type_helper<19U> { typedef std::int32_t exact_signed_type; typedef std::uint32_t exact_unsigned_type; };
    template<> struct integer_type_helper<20U> { typedef std::int32_t exact_signed_type; typedef std::uint32_t exact_unsigned_type; };
    template<> struct integer_type_helper<21U> { typedef std::int32_t exact_signed_type; typedef std::uint32_t exact_unsigned_type; };
    template<> struct integer_type_helper<22U> { typedef std::int32_t exact_signed_type; typedef std::uint32_t exact_unsigned_type; };
    template<> struct integer_type_helper<23U> { typedef std::int32_t exact_signed_type; typedef std::uint32_t exact_unsigned_type; };
    template<> struct integer_type_helper<24U> { typedef std::int32_t exact_signed_type; typedef std::uint32_t exact_unsigned_type; };
    template<> struct integer_type_helper<25U> { typedef std::int32_t exact_signed_type; typedef std::uint32_t exact_unsigned_type; };
    template<> struct integer_type_helper<26U> { typedef std::int32_t exact_signed_type; typedef std::uint32_t exact_unsigned_type; };
    template<> struct integer_type_helper<27U> { typedef std::int32_t exact_signed_type; typedef std::uint32_t exact_unsigned_type; };
    template<> struct integer_type_helper<28U> { typedef std::int32_t exact_signed_type; typedef std::uint32_t exact_unsigned_type; };
    template<> struct integer_type_helper<29U> { typedef std::int32_t exact_signed_type; typedef std::uint32_t exact_unsigned_type; };
    template<> struct integer_type_helper<30U> { typedef std::int32_t exact_signed_type; typedef std::uint32_t exact_unsigned_type; };
    template<> struct integer_type_helper<31U> { typedef std::int32_t exact_signed_type; typedef std::uint32_t exact_unsigned_type; };
    template<> struct integer_type_helper<32U> { typedef std::int32_t exact_signed_type; typedef std::uint32_t exact_unsigned_type; };

    template<> struct integer_type_helper<33U> { typedef std::int64_t exact_signed_type; typedef std::uint64_t exact_unsigned_type; };
    template<> struct integer_type_helper<34U> { typedef std::int64_t exact_signed_type; typedef std::uint64_t exact_unsigned_type; };
    template<> struct integer_type_helper<35U> { typedef std::int64_t exact_signed_type; typedef std::uint64_t exact_unsigned_type; };
    template<> struct integer_type_helper<36U> { typedef std::int64_t exact_signed_type; typedef std::uint64_t exact_unsigned_type; };
    template<> struct integer_type_helper<37U> { typedef std::int64_t exact_signed_type; typedef std::uint64_t exact_unsigned_type; };
    template<> struct integer_type_helper<38U> { typedef std::int64_t exact_signed_type; typedef std::uint64_t exact_unsigned_type; };
    template<> struct integer_type_helper<39U> { typedef std::int64_t exact_signed_type; typedef std::uint64_t exact_unsigned_type; };
    template<> struct integer_type_helper<40U> { typedef std::int64_t exact_signed_type; typedef std::uint64_t exact_unsigned_type; };
    template<> struct integer_type_helper<41U> { typedef std::int64_t exact_signed_type; typedef std::uint64_t exact_unsigned_type; };
    template<> struct integer_type_helper<42U> { typedef std::int64_t exact_signed_type; typedef std::uint64_t exact_unsigned_type; };
    template<> struct integer_type_helper<43U> { typedef std::int64_t exact_signed_type; typedef std::uint64_t exact_unsigned_type; };
    template<> struct integer_type_helper<44U> { typedef std::int64_t exact_signed_type; typedef std::uint64_t exact_unsigned_type; };
    template<> struct integer_type_helper<45U> { typedef std::int64_t exact_signed_type; typedef std::uint64_t exact_unsigned_type; };
    template<> struct integer_type_helper<46U> { typedef std::int64_t exact_signed_type; typedef std::uint64_t exact_unsigned_type; };
    template<> struct integer_type_helper<47U> { typedef std::int64_t exact_signed_type; typedef std::uint64_t exact_unsigned_type; };
    template<> struct integer_type_helper<48U> { typedef std::int64_t exact_signed_type; typedef std::uint64_t exact_unsigned_type; };
    template<> struct integer_type_helper<49U> { typedef std::int64_t exact_signed_type; typedef std::uint64_t exact_unsigned_type; };
    template<> struct integer_type_helper<50U> { typedef std::int64_t exact_signed_type; typedef std::uint64_t exact_unsigned_type; };
    template<> struct integer_type_helper<51U> { typedef std::int64_t exact_signed_type; typedef std::uint64_t exact_unsigned_type; };
    template<> struct integer_type_helper<52U> { typedef std::int64_t exact_signed_type; typedef std::uint64_t exact_unsigned_type; };
    template<> struct integer_type_helper<53U> { typedef std::int64_t exact_signed_type; typedef std::uint64_t exact_unsigned_type; };
    template<> struct integer_type_helper<54U> { typedef std::int64_t exact_signed_type; typedef std::uint64_t exact_unsigned_type; };
    template<> struct integer_type_helper<55U> { typedef std::int64_t exact_signed_type; typedef std::uint64_t exact_unsigned_type; };
    template<> struct integer_type_helper<56U> { typedef std::int64_t exact_signed_type; typedef std::uint64_t exact_unsigned_type; };
    template<> struct integer_type_helper<57U> { typedef std::int64_t exact_signed_type; typedef std::uint64_t exact_unsigned_type; };
    template<> struct integer_type_helper<58U> { typedef std::int64_t exact_signed_type; typedef std::uint64_t exact_unsigned_type; };
    template<> struct integer_type_helper<59U> { typedef std::int64_t exact_signed_type; typedef std::uint64_t exact_unsigned_type; };
    template<> struct integer_type_helper<60U> { typedef std::int64_t exact_signed_type; typedef std::uint64_t exact_unsigned_type; };
    template<> struct integer_type_helper<61U> { typedef std::int64_t exact_signed_type; typedef std::uint64_t exact_unsigned_type; };
    template<> struct integer_type_helper<62U> { typedef std::int64_t exact_signed_type; typedef std::uint64_t exact_unsigned_type; };
    template<> struct integer_type_helper<63U> { typedef std::int64_t exact_signed_type; typedef std::uint64_t exact_unsigned_type; };
    template<> struct integer_type_helper<64U> { typedef std::int64_t exact_signed_type; typedef std::uint64_t exact_unsigned_type; };

    template<typename integral_source_type,
             typename other_destination_type>
    other_destination_type convert_to(const integral_source_type& source)
    {
      return static_cast<other_destination_type>(source);
    }

    template<typename arithmetic_type,
             const int radix_split,
             typename enable_type = void>
    struct radix_split_maker
    {
      static arithmetic_type value()
      {
        static_assert(false, "Error: This template should not be instantiated. Check the underlying types in the negatable class.");

        return arithmetic_type();
      }
    };

    template<typename arithmetic_type,
             const int radix_split>
    struct radix_split_maker<arithmetic_type,
                             radix_split,
                             typename std::enable_if<std::is_integral<arithmetic_type>::value>::type>
    {
      static arithmetic_type value()
      {
        return arithmetic_type(arithmetic_type(1) << radix_split);
      }
    };

    template<typename arithmetic_type,
             const int radix_split>
    struct radix_split_maker<arithmetic_type,
                             radix_split,
                             typename std::enable_if<std::is_floating_point<arithmetic_type>::value>::type>
    {
      static arithmetic_type value()
      {
        using std::ldexp;
        return ldexp(arithmetic_type(1), radix_split);
      }
    };
  } // namespace math::fixed_point::detail

  // We will now begin the implementation of the negatable class.
  template<const int range,
           const int resolution,
           const round::round_type round_mode = round::nearest_odd,
           const overflow::overflow_type overflow_mode = overflow::exception>
  class negatable
  {
  public:
    static_assert( resolution < 0,         "Error: the negatable class resolution must be fractional (negative).");
    static_assert(-resolution < range - 1, "Error: the negatable class resolution exceeds the available range.");

    typedef typename math::fixed_point::detail::integer_type_helper<range>::exact_signed_type value_type;

    negatable() : data() { }

    template<typename signed_integral_type>
    negatable(const signed_integral_type& n,
              const typename std::enable_if<   std::is_same<char,       signed_integral_type>::value
                                            || std::is_same<short,      signed_integral_type>::value
                                            || std::is_same<int,        signed_integral_type>::value
                                            || std::is_same<long,       signed_integral_type>::value
                                            || std::is_same<long long,  signed_integral_type>::value
                                            || std::is_same<value_type, signed_integral_type>::value>::type* = nullptr) : data(n * radix_split_value<value_type>()) { }

    template<typename unsigned_integral_type>
    negatable(const unsigned_integral_type& u,
              const typename std::enable_if<   std::is_same<unsigned char,      unsigned_integral_type>::value
                                            || std::is_same<unsigned short,     unsigned_integral_type>::value
                                            || std::is_same<unsigned int,       unsigned_integral_type>::value
                                            || std::is_same<unsigned long,      unsigned_integral_type>::value
                                            || std::is_same<unsigned long long, unsigned_integral_type>::value>::type* = nullptr) : data(value_type(u) << radix_split) { }

    template<typename floating_point_type>
    negatable(const floating_point_type& f,
              const typename std::enable_if<   std::is_same<float,       floating_point_type>::value
                                            || std::is_same<double,      floating_point_type>::value
                                            || std::is_same<long double, floating_point_type>::value>::type* = nullptr) : data(value_type(f * radix_split_value<floating_point_type>())) { }

    negatable(const negatable& v) : data(v.data) { }

    ~negatable() { }

    negatable& operator=(const negatable& v)
    {
      if(this != (&v)) { data = v.data; }

      return *this;
    }

    negatable& operator=(const char& n)               { data = value_type(n * radix_split_value<value_type>()); return *this; }
    negatable& operator=(const short& n)              { data = value_type(n * radix_split_value<value_type>()); return *this; }
    negatable& operator=(const int& n)                { data = value_type(n * radix_split_value<value_type>()); return *this; }
    negatable& operator=(const long& n)               { data = value_type(n * radix_split_value<value_type>()); return *this; }
    negatable& operator=(const long long& n)          { data = value_type(n * radix_split_value<value_type>()); return *this; }

    negatable& operator=(const unsigned char& u)      { data = value_type(u) << radix_split; return *this; }
    negatable& operator=(const unsigned short& u)     { data = value_type(u) << radix_split; return *this; }
    negatable& operator=(const unsigned int& u)       { data = value_type(u) << radix_split; return *this; }
    negatable& operator=(const unsigned long& u)      { data = value_type(u) << radix_split; return *this; }
    negatable& operator=(const unsigned long long& u) { data = value_type(u) << radix_split; return *this; }

    negatable& operator=(const float& f)              { data = value_type(f * radix_split_value<float>()); return *this; }
    negatable& operator=(const double& f)             { data = value_type(f * radix_split_value<double>()); return *this; }
    negatable& operator=(const long double& f)        { data = value_type(f * radix_split_value<long double>()); return *this; }

    negatable& operator++()   { data += value_type(unsigned_small_type(1) << radix_split); return *this; }
    negatable& operator--()   { data -= value_type(unsigned_small_type(1) << radix_split); return *this; }

    negatable operator++(int) { const negatable tmp(*this); data += value_type(unsigned_small_type(1) << radix_split); return tmp; }
    negatable operator--(int) { const negatable tmp(*this); data -= value_type(unsigned_small_type(1) << radix_split); return tmp; }

    negatable& operator+=(const negatable& v)
    {
      if(is_quiet_nan(*this) || is_quiet_nan(v))
      {
        data = value_quiet_nan().data;
        return *this;
      }

      if(is_infinity(*this))
      {
        return *this;
      }

      if(is_infinity(v))
      {
        data = v.data;
      }
      else
      {
        const bool has_potential_overflow = ((data > 0) && (v.data > 0));

        data += v.data;

        if(has_potential_overflow && ((data > value_max().data) || (data < 0)))
        {
          data = value_infinity().data;
        }
      }

      return *this;
    }

    negatable& operator-=(const negatable& v)
    {
      if(is_quiet_nan(*this) || is_quiet_nan(v))
      {
        data = value_quiet_nan().data;
        return *this;
      }

      if(is_infinity(*this))
      {
        return *this;
      }

      if(is_infinity(v))
      {
        data = -v.data;
      }
      else
      {
        const bool has_potential_overflow = ((data < 0) && (v.data < 0));

        data -= v.data;

        if(has_potential_overflow && ((data < -value_max().data) || (data > 0)))
        {
          data = value_infinity().data;
        }
      }

      return *this;
    }

    negatable& operator*=(const negatable& v)
    {
      const bool u_is_neg      = (  data < 0);
      const bool v_is_neg      = (v.data < 0);
      const bool result_is_neg = (u_is_neg != v_is_neg);

      if(is_quiet_nan(*this) || is_quiet_nan(v))
      {
        data = value_quiet_nan().data;
        return *this;
      }

      if(is_infinity(*this) || is_infinity(v))
      {
        data = value_infinity().data;
      }
      else
      {
        unsigned_large_type result((!u_is_neg) ? data : -data);

        result *= ((!v_is_neg) ? v.data : -v.data);

        result >>= radix_split;

        if(result > unsigned_large_type(value_max().data))
        {
          data = value_infinity().data;
        }
        else
        {
          data = math::fixed_point::detail::convert_to<unsigned_large_type, value_type>(result);
        }
      }

      if(result_is_neg) { data = -data; }

      return *this;
    }

    negatable& operator/=(const negatable& v)
    {
      const bool u_is_neg      = (  data < 0);
      const bool v_is_neg      = (v.data < 0);
      const bool result_is_neg = (u_is_neg != v_is_neg);

      if(is_quiet_nan(*this) || is_quiet_nan(v))
      {
        data = value_quiet_nan().data;
        return *this;
      }

      if(is_infinity(*this))
      {
        data = (result_is_neg ? value_infinity().data : -value_infinity().data);
        return *this;
      }

      if(v.data == 0)
      {
        data = (u_is_neg ? value_infinity().data : -value_infinity().data);
        return *this;
      }

      if(is_infinity(v))
      {
        data = 0;
      }
      else
      {
        unsigned_large_type result((!u_is_neg) ? data : -data);

        result <<= radix_split;

        result /= ((!v_is_neg) ? v.data : -v.data);

        if(result > unsigned_large_type(value_max().data))
        {
          data = value_infinity().data;
        }
        else
        {
          data = math::fixed_point::detail::convert_to<unsigned_large_type, value_type>(result);
        }

        if(result_is_neg) { data = -data; }
      }

      return *this;
    }

    negatable& operator+=(const char& n)               { return (*this) += negatable(n); }
    negatable& operator+=(const short& n)              { return (*this) += negatable(n); }
    negatable& operator+=(const int& n)                { return (*this) += negatable(n); }
    negatable& operator+=(const long& n)               { return (*this) += negatable(n); }
    negatable& operator+=(const long long& n)          { return (*this) += negatable(n); }
    negatable& operator+=(const unsigned char& u)      { return (*this) += negatable(u); }
    negatable& operator+=(const unsigned short& u)     { return (*this) += negatable(u); }
    negatable& operator+=(const unsigned int& u)       { return (*this) += negatable(u); }
    negatable& operator+=(const unsigned long& u)      { return (*this) += negatable(u); }
    negatable& operator+=(const unsigned long long& u) { return (*this) += negatable(u); }
    negatable& operator+=(const float& f)              { return (*this) += negatable(f); }
    negatable& operator+=(const double& f)             { return (*this) += negatable(f); }
    negatable& operator+=(const long double& f)        { return (*this) += negatable(f); }

    negatable& operator-=(const char& n)               { return (*this) -= negatable(n); }
    negatable& operator-=(const short& n)              { return (*this) -= negatable(n); }
    negatable& operator-=(const int& n)                { return (*this) -= negatable(n); }
    negatable& operator-=(const long& n)               { return (*this) -= negatable(n); }
    negatable& operator-=(const long long& n)          { return (*this) -= negatable(n); }
    negatable& operator-=(const unsigned char& u)      { return (*this) -= negatable(u); }
    negatable& operator-=(const unsigned short& u)     { return (*this) -= negatable(u); }
    negatable& operator-=(const unsigned int& u)       { return (*this) -= negatable(u); }
    negatable& operator-=(const unsigned long& u)      { return (*this) -= negatable(u); }
    negatable& operator-=(const unsigned long long& u) { return (*this) -= negatable(u); }
    negatable& operator-=(const float& f)              { return (*this) -= negatable(f); }
    negatable& operator-=(const double& f)             { return (*this) -= negatable(f); }
    negatable& operator-=(const long double& f)        { return (*this) -= negatable(f); }

    negatable& operator*=(const char& n)               { return (*this) *= negatable(n); }
    negatable& operator*=(const short& n)              { return (*this) *= negatable(n); }
    negatable& operator*=(const int& n)                { return (*this) *= negatable(n); }
    negatable& operator*=(const long& n)               { return (*this) *= negatable(n); }
    negatable& operator*=(const long long& n)          { return (*this) *= negatable(n); }
    negatable& operator*=(const unsigned char& u)      { return (*this) *= negatable(u); }
    negatable& operator*=(const unsigned short& u)     { return (*this) *= negatable(u); }
    negatable& operator*=(const unsigned int& u)       { return (*this) *= negatable(u); }
    negatable& operator*=(const unsigned long& u)      { return (*this) *= negatable(u); }
    negatable& operator*=(const unsigned long long& u) { return (*this) *= negatable(u); }
    negatable& operator*=(const float& f)              { return (*this) *= negatable(f); }
    negatable& operator*=(const double& f)             { return (*this) *= negatable(f); }
    negatable& operator*=(const long double& f)        { return (*this) *= negatable(f); }

    negatable& operator/=(const char& n)               { return (*this) /= negatable(n); }
    negatable& operator/=(const short& n)              { return (*this) /= negatable(n); }
    negatable& operator/=(const int& n)                { return (*this) /= negatable(n); }
    negatable& operator/=(const long& n)               { return (*this) /= negatable(n); }
    negatable& operator/=(const long long& n)          { return (*this) /= negatable(n); }
    negatable& operator/=(const unsigned char& u)      { return (*this) /= negatable(u); }
    negatable& operator/=(const unsigned short& u)     { return (*this) /= negatable(u); }
    negatable& operator/=(const unsigned int& u)       { return (*this) /= negatable(u); }
    negatable& operator/=(const unsigned long& u)      { return (*this) /= negatable(u); }
    negatable& operator/=(const unsigned long long& u) { return (*this) /= negatable(u); }
    negatable& operator/=(const float& f)              { return (*this) /= negatable(f); }
    negatable& operator/=(const double& f)             { return (*this) /= negatable(f); }
    negatable& operator/=(const long double& f)        { return (*this) /= negatable(f); }

    operator char()                                    { return static_cast<char>      (data / radix_split_value<value_type>()); }
    operator short()                                   { return static_cast<short>     (data / radix_split_value<value_type>()); }
    operator int()                                     { return static_cast<int>       (data / radix_split_value<value_type>()); }
    operator long()                                    { return static_cast<long>      (data / radix_split_value<value_type>()); }
    operator long long()                               { return static_cast<long long> (data / radix_split_value<value_type>()); }

    operator unsigned char()                           { return static_cast<unsigned char>     (unsigned_small_type(data) >> radix_split); }
    operator unsigned short()                          { return static_cast<unsigned short>    (unsigned_small_type(data) >> radix_split); }
    operator unsigned int()                            { return static_cast<unsigned int>      (unsigned_small_type(data) >> radix_split); }
    operator unsigned long()                           { return static_cast<unsigned long>     (unsigned_small_type(data) >> radix_split); }
    operator unsigned long long()                      { return static_cast<unsigned long long>(unsigned_small_type(data) >> radix_split); }

    operator float()
    {
      const bool is_neg = (data < static_cast<value_type>(0));

      const unsigned_small_type x = static_cast<unsigned_small_type>((!is_neg) ? data : -data);

      const unsigned_small_type integer_part = (x >> radix_split);
      const unsigned_small_type decimal_part = x - (integer_part << radix_split);

      const float f = static_cast<float>(integer_part) + (static_cast<float>(decimal_part) / radix_split_value<float>());

      return ((!is_neg) ? f : -f);
    }

    operator double()
    {
      const bool is_neg = (data < static_cast<value_type>(0));

      const unsigned_small_type x = static_cast<unsigned_small_type>((!is_neg) ? data : -data);

      const unsigned_small_type integer_part = (x >> radix_split);
      const unsigned_small_type decimal_part = x - (integer_part << radix_split);

      const double f = static_cast<double>(integer_part) + (static_cast<double>(decimal_part) / radix_split_value<double>());

      return ((!is_neg) ? f : -f);
    }

    operator long double()
    {
      const bool is_neg = (data < static_cast<value_type>(0));

      const unsigned_small_type x = static_cast<unsigned_small_type>((!is_neg) ? data : -data);

      const unsigned_small_type integer_part = (x >> radix_split);
      const unsigned_small_type decimal_part = x - (integer_part << radix_split);

      const long double f = static_cast<long double>(integer_part) + (static_cast<long double>(decimal_part) / radix_split_value<long double>());

      return ((!is_neg) ? f : -f);
    }

  private:
    value_type data;

    static const int radix_split = -resolution;

    typedef typename detail::integer_type_helper<range * 1>::exact_unsigned_type unsigned_small_type;
    typedef typename detail::integer_type_helper<range * 2>::exact_unsigned_type unsigned_large_type;

    template<typename arithmetic_type>
    static arithmetic_type radix_split_value()
    {
      return fixed_point::detail::radix_split_maker<arithmetic_type, radix_split>::value();
    }

    struct nothing { };

    template<typename signed_integral_type>
    negatable(const nothing&,
              const signed_integral_type& n,
              const typename std::enable_if<   std::is_same<char,       signed_integral_type>::value
                                            || std::is_same<short,      signed_integral_type>::value
                                            || std::is_same<int,        signed_integral_type>::value
                                            || std::is_same<long,       signed_integral_type>::value
                                            || std::is_same<long long,  signed_integral_type>::value
                                            || std::is_same<value_type, signed_integral_type>::value>::type* = nullptr) : data(n) { }

    template<typename unsigned_integral_type>
    negatable(const nothing&,
              const unsigned_integral_type& u,
              const typename std::enable_if<   std::is_same<unsigned char,      unsigned_integral_type>::value
                                            || std::is_same<unsigned short,     unsigned_integral_type>::value
                                            || std::is_same<unsigned int,       unsigned_integral_type>::value
                                            || std::is_same<unsigned long,      unsigned_integral_type>::value
                                            || std::is_same<unsigned long long, unsigned_integral_type>::value>::type* = nullptr) : data(u) { }

    static bool is_quiet_nan(const negatable& x) { return (         x.data  == value_quiet_nan()); }
    static bool is_infinity (const negatable& x) { return (std::abs(x.data) == value_infinity()); }

    static value_type make_unsigned_constant(const value_type& x)
    {
      // TBD: Provide support for smaller ranges and larger resolutions.
      // TBD: This will involve the generation of constant coefficients used for transcendentals.
      // TBD: Of course the magic number *24* will be removed when all is said and done.
      static_assert(range > 24, "Error: the negatable class does not yet support such a small range.");
      static_assert(-resolution <= 24, "Error: the negatable class does not yet support such a large resolution.");

      return x >> (24 - radix_split);
    }

    static negatable value_epsilon()
    {
      value_type r10  = radix_split_value<value_type>();

      if(r10 <= 10)
      {
        return negatable(nothing(), 1);
      }
      else
      {
        // TBD: Consider using template metaprogramming instead of a loop here.
        while(r10 > 10)
        {
          r10 = (r10 + 9) / 10;
        }

        return negatable(nothing(), r10);
      }
    }

    static negatable value_min()       { return negatable(nothing(), 1); }
    static negatable value_max()       { return negatable(nothing(), (std::numeric_limits<value_type>::max)() - 3) ; }
    static negatable value_infinity()  { return negatable(nothing(), value_max().data - 2) ; }
    static negatable value_quiet_nan() { return negatable(nothing(), value_max().data - 1) ; }

    friend class ::std::numeric_limits<negatable>;

    template<typename char_type, class traits_type>
    friend inline std::basic_ostream<char_type, traits_type>& operator<<(std::basic_ostream<char_type, traits_type>& os, const negatable& x)
    {
      std::basic_ostringstream<char_type, traits_type> ostr;
      ostr.flags(os.flags());
      ostr.imbue(os.getloc());
      ostr.precision(os.precision());

      const long double ld = fixed_point::detail::convert_to<value_type, long double>(x.data) / radix_split_value<long double>();

      ostr << ld;

      return (os << ostr.str());
    }

    // Implementations of global unary plus and minus.
    friend inline negatable operator+ (const negatable& left)                                      { return negatable(left); }
    friend inline negatable operator- (const negatable& left)                                      { negatable tmp(left); tmp.data = -tmp.data; return tmp; }

    // Implementations of global add, sub, mul, div of [lhs(negatable)] operator [rhs(negatable)].
    friend inline negatable operator+ (const negatable& u,            const negatable& v)          { return negatable(u) += v; }
    friend inline negatable operator- (const negatable& u,            const negatable& v)          { return negatable(u) -= v; }
    friend inline negatable operator* (const negatable& u,            const negatable& v)          { return negatable(u) *= v; }
    friend inline negatable operator/ (const negatable& u,            const negatable& v)          { return negatable(u) /= v; }

    // Implementations of global add, sub, mul, div of [lhs(negatable)] operator [rhs(arithmetic_type)].
    friend inline negatable operator+ (const negatable& u,            const char& n)               { return negatable(u) += n; }
    friend inline negatable operator+ (const negatable& u,            const short& n)              { return negatable(u) += n; }
    friend inline negatable operator+ (const negatable& u,            const int& n)                { return negatable(u) += n; }
    friend inline negatable operator+ (const negatable& u,            const long& n)               { return negatable(u) += n; }
    friend inline negatable operator+ (const negatable& u,            const long long& n)          { return negatable(u) += n; }
    friend inline negatable operator+ (const negatable& u,            const unsigned char& n)      { return negatable(u) += n; }
    friend inline negatable operator+ (const negatable& u,            const unsigned short& n)     { return negatable(u) += n; }
    friend inline negatable operator+ (const negatable& u,            const unsigned int& n)       { return negatable(u) += n; }
    friend inline negatable operator+ (const negatable& u,            const unsigned long& n)      { return negatable(u) += n; }
    friend inline negatable operator+ (const negatable& u,            const unsigned long long& n) { return negatable(u) += n; }
    friend inline negatable operator+ (const negatable& u,            const float& f)              { return negatable(u) += f; }
    friend inline negatable operator+ (const negatable& u,            const double& f)             { return negatable(u) += f; }
    friend inline negatable operator+ (const negatable& u,            const long double& f)        { return negatable(u) += f; }

    friend inline negatable operator- (const negatable& u,            const char& n)               { return negatable(u) -= n; }
    friend inline negatable operator- (const negatable& u,            const short& n)              { return negatable(u) -= n; }
    friend inline negatable operator- (const negatable& u,            const int& n)                { return negatable(u) -= n; }
    friend inline negatable operator- (const negatable& u,            const long& n)               { return negatable(u) -= n; }
    friend inline negatable operator- (const negatable& u,            const long long& n)          { return negatable(u) -= n; }
    friend inline negatable operator- (const negatable& u,            const unsigned char& n)      { return negatable(u) -= n; }
    friend inline negatable operator- (const negatable& u,            const unsigned short& n)     { return negatable(u) -= n; }
    friend inline negatable operator- (const negatable& u,            const unsigned int& n)       { return negatable(u) -= n; }
    friend inline negatable operator- (const negatable& u,            const unsigned long& n)      { return negatable(u) -= n; }
    friend inline negatable operator- (const negatable& u,            const unsigned long long& n) { return negatable(u) -= n; }
    friend inline negatable operator- (const negatable& u,            const float& f)              { return negatable(u) -= f; }
    friend inline negatable operator- (const negatable& u,            const double& f)             { return negatable(u) -= f; }
    friend inline negatable operator- (const negatable& u,            const long double& f)        { return negatable(u) -= f; }

    friend inline negatable operator* (const negatable& u,            const char& n)               { return negatable(u) *= n; }
    friend inline negatable operator* (const negatable& u,            const short& n)              { return negatable(u) *= n; }
    friend inline negatable operator* (const negatable& u,            const int& n)                { return negatable(u) *= n; }
    friend inline negatable operator* (const negatable& u,            const long& n)               { return negatable(u) *= n; }
    friend inline negatable operator* (const negatable& u,            const long long& n)          { return negatable(u) *= n; }
    friend inline negatable operator* (const negatable& u,            const unsigned char& n)      { return negatable(u) *= n; }
    friend inline negatable operator* (const negatable& u,            const unsigned short& n)     { return negatable(u) *= n; }
    friend inline negatable operator* (const negatable& u,            const unsigned int& n)       { return negatable(u) *= n; }
    friend inline negatable operator* (const negatable& u,            const unsigned long& n)      { return negatable(u) *= n; }
    friend inline negatable operator* (const negatable& u,            const unsigned long long& n) { return negatable(u) *= n; }
    friend inline negatable operator* (const negatable& u,            const float& f)              { return negatable(u) *= f; }
    friend inline negatable operator* (const negatable& u,            const double& f)             { return negatable(u) *= f; }
    friend inline negatable operator* (const negatable& u,            const long double& f)        { return negatable(u) *= f; }

    friend inline negatable operator/ (const negatable& u,            const char& n)               { return negatable(u) /= n; }
    friend inline negatable operator/ (const negatable& u,            const short& n)              { return negatable(u) /= n; }
    friend inline negatable operator/ (const negatable& u,            const int& n)                { return negatable(u) /= n; }
    friend inline negatable operator/ (const negatable& u,            const long& n)               { return negatable(u) /= n; }
    friend inline negatable operator/ (const negatable& u,            const long long& n)          { return negatable(u) /= n; }
    friend inline negatable operator/ (const negatable& u,            const unsigned char& n)      { return negatable(u) /= n; }
    friend inline negatable operator/ (const negatable& u,            const unsigned short& n)     { return negatable(u) /= n; }
    friend inline negatable operator/ (const negatable& u,            const unsigned int& n)       { return negatable(u) /= n; }
    friend inline negatable operator/ (const negatable& u,            const unsigned long& n)      { return negatable(u) /= n; }
    friend inline negatable operator/ (const negatable& u,            const unsigned long long& n) { return negatable(u) /= n; }
    friend inline negatable operator/ (const negatable& u,            const float& f)              { return negatable(u) /= f; }
    friend inline negatable operator/ (const negatable& u,            const double& f)             { return negatable(u) /= f; }
    friend inline negatable operator/ (const negatable& u,            const long double& f)        { return negatable(u) /= f; }

    // Implementations of global add, sub, mul, div of [lhs(arithmetic_type)] operator [rhs(negatable)].
    friend inline negatable operator+ (const char& n,                 const negatable& u)          { return negatable(n) += u; }
    friend inline negatable operator+ (const short& n,                const negatable& u)          { return negatable(n) += u; }
    friend inline negatable operator+ (const int& n,                  const negatable& u)          { return negatable(n) += u; }
    friend inline negatable operator+ (const long& n,                 const negatable& u)          { return negatable(n) += u; }
    friend inline negatable operator+ (const long long& n,            const negatable& u)          { return negatable(n) += u; }
    friend inline negatable operator+ (const unsigned char& n,        const negatable& u)          { return negatable(n) += u; }
    friend inline negatable operator+ (const unsigned short& n,       const negatable& u)          { return negatable(n) += u; }
    friend inline negatable operator+ (const unsigned int& n,         const negatable& u)          { return negatable(n) += u; }
    friend inline negatable operator+ (const unsigned long& n,        const negatable& u)          { return negatable(n) += u; }
    friend inline negatable operator+ (const unsigned long long& n,   const negatable& u)          { return negatable(n) += u; }
    friend inline negatable operator+ (const float& f,                const negatable& u)          { return negatable(f) += u; }
    friend inline negatable operator+ (const double& f,               const negatable& u)          { return negatable(f) += u; }
    friend inline negatable operator+ (const long double& f,          const negatable& u)          { return negatable(f) += u; }

    friend inline negatable operator- (const char& n,                 const negatable& u)          { return negatable(n) -= u; }
    friend inline negatable operator- (const short& n,                const negatable& u)          { return negatable(n) -= u; }
    friend inline negatable operator- (const int& n,                  const negatable& u)          { return negatable(n) -= u; }
    friend inline negatable operator- (const long& n,                 const negatable& u)          { return negatable(n) -= u; }
    friend inline negatable operator- (const long long& n,            const negatable& u)          { return negatable(n) -= u; }
    friend inline negatable operator- (const unsigned char& n,        const negatable& u)          { return negatable(n) -= u; }
    friend inline negatable operator- (const unsigned short& n,       const negatable& u)          { return negatable(n) -= u; }
    friend inline negatable operator- (const unsigned int& n,         const negatable& u)          { return negatable(n) -= u; }
    friend inline negatable operator- (const unsigned long& n,        const negatable& u)          { return negatable(n) -= u; }
    friend inline negatable operator- (const unsigned long long& n,   const negatable& u)          { return negatable(n) -= u; }
    friend inline negatable operator- (const float& f,                const negatable& u)          { return negatable(f) -= u; }
    friend inline negatable operator- (const double& f,               const negatable& u)          { return negatable(f) -= u; }
    friend inline negatable operator- (const long double& f,          const negatable& u)          { return negatable(f) -= u; }

    friend inline negatable operator* (const char& n,                 const negatable& u)          { return negatable(n) *= u; }
    friend inline negatable operator* (const short& n,                const negatable& u)          { return negatable(n) *= u; }
    friend inline negatable operator* (const int& n,                  const negatable& u)          { return negatable(n) *= u; }
    friend inline negatable operator* (const long& n,                 const negatable& u)          { return negatable(n) *= u; }
    friend inline negatable operator* (const long long& n,            const negatable& u)          { return negatable(n) *= u; }
    friend inline negatable operator* (const unsigned char& n,        const negatable& u)          { return negatable(n) *= u; }
    friend inline negatable operator* (const unsigned short& n,       const negatable& u)          { return negatable(n) *= u; }
    friend inline negatable operator* (const unsigned int& n,         const negatable& u)          { return negatable(n) *= u; }
    friend inline negatable operator* (const unsigned long& n,        const negatable& u)          { return negatable(n) *= u; }
    friend inline negatable operator* (const unsigned long long& n,   const negatable& u)          { return negatable(n) *= u; }
    friend inline negatable operator* (const float& f,                const negatable& u)          { return negatable(f) *= u; }
    friend inline negatable operator* (const double& f,               const negatable& u)          { return negatable(f) *= u; }
    friend inline negatable operator* (const long double& f,          const negatable& u)          { return negatable(f) *= u; }

    friend inline negatable operator/ (const char& n,                 const negatable& u)          { return negatable(n) /= u; }
    friend inline negatable operator/ (const short& n,                const negatable& u)          { return negatable(n) /= u; }
    friend inline negatable operator/ (const int& n,                  const negatable& u)          { return negatable(n) /= u; }
    friend inline negatable operator/ (const long& n,                 const negatable& u)          { return negatable(n) /= u; }
    friend inline negatable operator/ (const long long& n,            const negatable& u)          { return negatable(n) /= u; }
    friend inline negatable operator/ (const unsigned char& n,        const negatable& u)          { return negatable(n) /= u; }
    friend inline negatable operator/ (const unsigned short& n,       const negatable& u)          { return negatable(n) /= u; }
    friend inline negatable operator/ (const unsigned int& n,         const negatable& u)          { return negatable(n) /= u; }
    friend inline negatable operator/ (const unsigned long& n,        const negatable& u)          { return negatable(n) /= u; }
    friend inline negatable operator/ (const unsigned long long& n,   const negatable& u)          { return negatable(n) /= u; }
    friend inline negatable operator/ (const float& f,                const negatable& u)          { return negatable(f) /= u; }
    friend inline negatable operator/ (const double& f,               const negatable& u)          { return negatable(f) /= u; }
    friend inline negatable operator/ (const long double& f,          const negatable& u)          { return negatable(f) /= u; }

    // Implementations of global equality.
    friend inline bool      operator==(const negatable& u,            const negatable& v)          { return ((u.data == v.data) && (!(negatable::is_quiet_nan(u) && negatable::is_quiet_nan(v)))); }

    friend inline bool      operator==(const negatable& u,            const char& v)               { return (u.data == negatable(v).data); }
    friend inline bool      operator==(const negatable& u,            const short& v)              { return (u.data == negatable(v).data); }
    friend inline bool      operator==(const negatable& u,            const int& v)                { return (u.data == negatable(v).data); }
    friend inline bool      operator==(const negatable& u,            const long& v)               { return (u.data == negatable(v).data); }
    friend inline bool      operator==(const negatable& u,            const long long& v)          { return (u.data == negatable(v).data); }

    friend inline bool      operator==(const negatable& u,            const unsigned char& v)      { return (u.data == negatable(v).data); }
    friend inline bool      operator==(const negatable& u,            const unsigned short& v)     { return (u.data == negatable(v).data); }
    friend inline bool      operator==(const negatable& u,            const unsigned int& v)       { return (u.data == negatable(v).data); }
    friend inline bool      operator==(const negatable& u,            const unsigned long& v)      { return (u.data == negatable(v).data); }
    friend inline bool      operator==(const negatable& u,            const unsigned long long& v) { return (u.data == negatable(v).data); }

    friend inline bool      operator==(const negatable& u,            const float& v)              { return ((u.data == negatable(v).data) && (!(negatable::is_quiet_nan(u) && (negatable::is_quiet_nan(v))))); }
    friend inline bool      operator==(const negatable& u,            const double& v)             { return ((u.data == negatable(v).data) && (!(negatable::is_quiet_nan(u) && (negatable::is_quiet_nan(v))))); }
    friend inline bool      operator==(const negatable& u,            const long double& v)        { return ((u.data == negatable(v).data) && (!(negatable::is_quiet_nan(u) && (negatable::is_quiet_nan(v))))); }

    friend inline bool      operator==(const char& u,                 const negatable& v)          { return (negatable(u).data == v.data); }
    friend inline bool      operator==(const short& u,                const negatable& v)          { return (negatable(u).data == v.data); }
    friend inline bool      operator==(const int& u,                  const negatable& v)          { return (negatable(u).data == v.data); }
    friend inline bool      operator==(const long& u,                 const negatable& v)          { return (negatable(u).data == v.data); }
    friend inline bool      operator==(const long long& u,            const negatable& v)          { return (negatable(u).data == v.data); }

    friend inline bool      operator==(const unsigned char& u,        const negatable& v)          { return (negatable(u).data == v.data); }
    friend inline bool      operator==(const unsigned short& u,       const negatable& v)          { return (negatable(u).data == v.data); }
    friend inline bool      operator==(const unsigned int& u,         const negatable& v)          { return (negatable(u).data == v.data); }
    friend inline bool      operator==(const unsigned long& u,        const negatable& v)          { return (negatable(u).data == v.data); }
    friend inline bool      operator==(const unsigned long long& u,   const negatable& v)          { return (negatable(u).data == v.data); }

    friend inline bool      operator==(const float& u,                const negatable& v)          { return ((negatable(u).data == v.data) && (!((negatable::is_quiet_nan(u)) && negatable::is_quiet_nan(v)))); }
    friend inline bool      operator==(const double& u,               const negatable& v)          { return ((negatable(u).data == v.data) && (!((negatable::is_quiet_nan(u)) && negatable::is_quiet_nan(v)))); }
    friend inline bool      operator==(const double long& u,          const negatable& v)          { return ((negatable(u).data == v.data) && (!((negatable::is_quiet_nan(u)) && negatable::is_quiet_nan(v)))); }

    // Implementations of global inequality.
    friend inline bool      operator!=(const negatable& u,            const negatable& v)          { return ((u.data != v.data) || (negatable::is_quiet_nan(u) && negatable::is_quiet_nan(v))); }

    friend inline bool      operator!=(const negatable& u,            const char& v)               { return (u.data != negatable(v).data); }
    friend inline bool      operator!=(const negatable& u,            const short& v)              { return (u.data != negatable(v).data); }
    friend inline bool      operator!=(const negatable& u,            const int& v)                { return (u.data != negatable(v).data); }
    friend inline bool      operator!=(const negatable& u,            const long& v)               { return (u.data != negatable(v).data); }
    friend inline bool      operator!=(const negatable& u,            const long long& v)          { return (u.data != negatable(v).data); }

    friend inline bool      operator!=(const negatable& u,            const unsigned char& v)      { return (u.data != negatable(v).data); }
    friend inline bool      operator!=(const negatable& u,            const unsigned short& v)     { return (u.data != negatable(v).data); }
    friend inline bool      operator!=(const negatable& u,            const unsigned int& v)       { return (u.data != negatable(v).data); }
    friend inline bool      operator!=(const negatable& u,            const unsigned long& v)      { return (u.data != negatable(v).data); }
    friend inline bool      operator!=(const negatable& u,            const unsigned long long& v) { return (u.data != negatable(v).data); }

    friend inline bool      operator!=(const negatable& u,            const float& v)              { return ((u.data != negatable(v).data) || (negatable::is_quiet_nan(u) && (negatable::is_quiet_nan(v)))); }
    friend inline bool      operator!=(const negatable& u,            const double& v)             { return ((u.data != negatable(v).data) || (negatable::is_quiet_nan(u) && (negatable::is_quiet_nan(v)))); }
    friend inline bool      operator!=(const negatable& u,            const long double& v)        { return ((u.data != negatable(v).data) || (negatable::is_quiet_nan(u) && (negatable::is_quiet_nan(v)))); }

    friend inline bool      operator!=(const char& u,                 const negatable& v)          { return (negatable(u).data != v.data); }
    friend inline bool      operator!=(const short& u,                const negatable& v)          { return (negatable(u).data != v.data); }
    friend inline bool      operator!=(const int& u,                  const negatable& v)          { return (negatable(u).data != v.data); }
    friend inline bool      operator!=(const long& u,                 const negatable& v)          { return (negatable(u).data != v.data); }
    friend inline bool      operator!=(const long long& u,            const negatable& v)          { return (negatable(u).data != v.data); }

    friend inline bool      operator!=(const unsigned char& u,        const negatable& v)          { return (negatable(u).data != v.data); }
    friend inline bool      operator!=(const unsigned short& u,       const negatable& v)          { return (negatable(u).data != v.data); }
    friend inline bool      operator!=(const unsigned int& u,         const negatable& v)          { return (negatable(u).data != v.data); }
    friend inline bool      operator!=(const unsigned long& u,        const negatable& v)          { return (negatable(u).data != v.data); }
    friend inline bool      operator!=(const unsigned long long& u,   const negatable& v)          { return (negatable(u).data != v.data); }

    friend inline bool      operator!=(const float& u,                const negatable& v)          { return ((negatable(u).data != v.data) || ((negatable::is_quiet_nan(u)) && negatable::is_quiet_nan(v))); }
    friend inline bool      operator!=(const double& u,               const negatable& v)          { return ((negatable(u).data != v.data) || ((negatable::is_quiet_nan(u)) && negatable::is_quiet_nan(v))); }
    friend inline bool      operator!=(const double long& u,          const negatable& v)          { return ((negatable(u).data != v.data) || ((negatable::is_quiet_nan(u)) && negatable::is_quiet_nan(v))); }

    // Implementations of global operators >, <, >=, <=.
    friend inline bool      operator> (const negatable& u,            const negatable& v)          { return ((u.data > v.data) && (!(negatable::is_quiet_nan(u) && negatable::is_quiet_nan(v)))); }

    friend inline bool      operator> (const negatable& u,            const char& v)               { return (u.data > negatable(v).data); }
    friend inline bool      operator> (const negatable& u,            const short& v)              { return (u.data > negatable(v).data); }
    friend inline bool      operator> (const negatable& u,            const int& v)                { return (u.data > negatable(v).data); }
    friend inline bool      operator> (const negatable& u,            const long& v)               { return (u.data > negatable(v).data); }
    friend inline bool      operator> (const negatable& u,            const long long& v)          { return (u.data > negatable(v).data); }

    friend inline bool      operator> (const negatable& u,            const unsigned char& v)      { return (u.data > negatable(v).data); }
    friend inline bool      operator> (const negatable& u,            const unsigned short& v)     { return (u.data > negatable(v).data); }
    friend inline bool      operator> (const negatable& u,            const unsigned int& v)       { return (u.data > negatable(v).data); }
    friend inline bool      operator> (const negatable& u,            const unsigned long& v)      { return (u.data > negatable(v).data); }
    friend inline bool      operator> (const negatable& u,            const unsigned long long& v) { return (u.data > negatable(v).data); }

    friend inline bool      operator> (const negatable& u,            const float& v)              { return ((u.data > negatable(v).data) && (!(negatable::is_quiet_nan(u) && (negatable::is_quiet_nan(v))))); }
    friend inline bool      operator> (const negatable& u,            const double& v)             { return ((u.data > negatable(v).data) && (!(negatable::is_quiet_nan(u) && (negatable::is_quiet_nan(v))))); }
    friend inline bool      operator> (const negatable& u,            const long double& v)        { return ((u.data > negatable(v).data) && (!(negatable::is_quiet_nan(u) && (negatable::is_quiet_nan(v))))); }

    friend inline bool      operator> (const char& u,                 const negatable& v)          { return (negatable(u).data > v.data); }
    friend inline bool      operator> (const short& u,                const negatable& v)          { return (negatable(u).data > v.data); }
    friend inline bool      operator> (const int& u,                  const negatable& v)          { return (negatable(u).data > v.data); }
    friend inline bool      operator> (const long& u,                 const negatable& v)          { return (negatable(u).data > v.data); }
    friend inline bool      operator> (const long long& u,            const negatable& v)          { return (negatable(u).data > v.data); }

    friend inline bool      operator> (const unsigned char& u,        const negatable& v)          { return (negatable(u).data > v.data); }
    friend inline bool      operator> (const unsigned short& u,       const negatable& v)          { return (negatable(u).data > v.data); }
    friend inline bool      operator> (const unsigned int& u,         const negatable& v)          { return (negatable(u).data > v.data); }
    friend inline bool      operator> (const unsigned long& u,        const negatable& v)          { return (negatable(u).data > v.data); }
    friend inline bool      operator> (const unsigned long long& u,   const negatable& v)          { return (negatable(u).data > v.data); }

    friend inline bool      operator> (const float& u,                const negatable& v)          { return ((negatable(u).data > v.data) && (!((negatable::is_quiet_nan(u)) && negatable::is_quiet_nan(v)))); }
    friend inline bool      operator> (const double& u,               const negatable& v)          { return ((negatable(u).data > v.data) && (!((negatable::is_quiet_nan(u)) && negatable::is_quiet_nan(v)))); }
    friend inline bool      operator> (const double long& u,          const negatable& v)          { return ((negatable(u).data > v.data) && (!((negatable::is_quiet_nan(u)) && negatable::is_quiet_nan(v)))); }

    friend inline bool      operator< (const negatable& u,            const negatable& v)          { return ((u.data < v.data) || (negatable::is_quiet_nan(u) && negatable::is_quiet_nan(v))); }

    friend inline bool      operator< (const negatable& u,            const char& v)               { return (u.data < negatable(v).data); }
    friend inline bool      operator< (const negatable& u,            const short& v)              { return (u.data < negatable(v).data); }
    friend inline bool      operator< (const negatable& u,            const int& v)                { return (u.data < negatable(v).data); }
    friend inline bool      operator< (const negatable& u,            const long& v)               { return (u.data < negatable(v).data); }
    friend inline bool      operator< (const negatable& u,            const long long& v)          { return (u.data < negatable(v).data); }

    friend inline bool      operator< (const negatable& u,            const unsigned char& v)      { return (u.data < negatable(v).data); }
    friend inline bool      operator< (const negatable& u,            const unsigned short& v)     { return (u.data < negatable(v).data); }
    friend inline bool      operator< (const negatable& u,            const unsigned int& v)       { return (u.data < negatable(v).data); }
    friend inline bool      operator< (const negatable& u,            const unsigned long& v)      { return (u.data < negatable(v).data); }
    friend inline bool      operator< (const negatable& u,            const unsigned long long& v) { return (u.data < negatable(v).data); }

    friend inline bool      operator< (const negatable& u,            const float& v)              { return ((u.data < negatable(v).data) || (negatable::is_quiet_nan(u) && (negatable::is_quiet_nan(v)))); }
    friend inline bool      operator< (const negatable& u,            const double& v)             { return ((u.data < negatable(v).data) || (negatable::is_quiet_nan(u) && (negatable::is_quiet_nan(v)))); }
    friend inline bool      operator< (const negatable& u,            const long double& v)        { return ((u.data < negatable(v).data) || (negatable::is_quiet_nan(u) && (negatable::is_quiet_nan(v)))); }

    friend inline bool      operator< (const char& u,                 const negatable& v)          { return (negatable(u).data < v.data); }
    friend inline bool      operator< (const short& u,                const negatable& v)          { return (negatable(u).data < v.data); }
    friend inline bool      operator< (const int& u,                  const negatable& v)          { return (negatable(u).data < v.data); }
    friend inline bool      operator< (const long& u,                 const negatable& v)          { return (negatable(u).data < v.data); }
    friend inline bool      operator< (const long long& u,            const negatable& v)          { return (negatable(u).data < v.data); }

    friend inline bool      operator< (const unsigned char& u,        const negatable& v)          { return (negatable(u).data < v.data); }
    friend inline bool      operator< (const unsigned short& u,       const negatable& v)          { return (negatable(u).data < v.data); }
    friend inline bool      operator< (const unsigned int& u,         const negatable& v)          { return (negatable(u).data < v.data); }
    friend inline bool      operator< (const unsigned long& u,        const negatable& v)          { return (negatable(u).data < v.data); }
    friend inline bool      operator< (const unsigned  long long& u,  const negatable& v)          { return (negatable(u).data < v.data); }

    friend inline bool      operator< (const float& u,                const negatable& v)          { return ((negatable(u).data < v.data) || ((negatable::is_quiet_nan(u)) && negatable::is_quiet_nan(v))); }
    friend inline bool      operator< (const double& u,               const negatable& v)          { return ((negatable(u).data < v.data) || ((negatable::is_quiet_nan(u)) && negatable::is_quiet_nan(v))); }
    friend inline bool      operator< (const double long& u,          const negatable& v)          { return ((negatable(u).data < v.data) || ((negatable::is_quiet_nan(u)) && negatable::is_quiet_nan(v))); }

    friend inline bool      operator>=(const negatable& u,            const negatable& v)          { return ((u.data >= v.data) && (!(negatable::is_quiet_nan(u) && negatable::is_quiet_nan(v)))); }

    friend inline bool      operator>=(const negatable& u,            const char& v)               { return (u.data >= negatable(v).data); }
    friend inline bool      operator>=(const negatable& u,            const short& v)              { return (u.data >= negatable(v).data); }
    friend inline bool      operator>=(const negatable& u,            const int& v)                { return (u.data >= negatable(v).data); }
    friend inline bool      operator>=(const negatable& u,            const long& v)               { return (u.data >= negatable(v).data); }
    friend inline bool      operator>=(const negatable& u,            const long long& v)          { return (u.data >= negatable(v).data); }

    friend inline bool      operator>=(const negatable& u,            const unsigned char& v)      { return (u.data >= negatable(v).data); }
    friend inline bool      operator>=(const negatable& u,            const unsigned short& v)     { return (u.data >= negatable(v).data); }
    friend inline bool      operator>=(const negatable& u,            const unsigned int& v)       { return (u.data >= negatable(v).data); }
    friend inline bool      operator>=(const negatable& u,            const unsigned long& v)      { return (u.data >= negatable(v).data); }
    friend inline bool      operator>=(const negatable& u,            const unsigned long long& v) { return (u.data >= negatable(v).data); }

    friend inline bool      operator>=(const negatable& u,            const float& v)              { return ((u.data >= negatable(v).data) && (!(negatable::is_quiet_nan(u) && (negatable::is_quiet_nan(v))))); }
    friend inline bool      operator>=(const negatable& u,            const double& v)             { return ((u.data >= negatable(v).data) && (!(negatable::is_quiet_nan(u) && (negatable::is_quiet_nan(v))))); }
    friend inline bool      operator>=(const negatable& u,            const long double& v)        { return ((u.data >= negatable(v).data) && (!(negatable::is_quiet_nan(u) && (negatable::is_quiet_nan(v))))); }

    friend inline bool      operator>=(const char& u,                 const negatable& v)          { return (negatable(u).data >= v.data); }
    friend inline bool      operator>=(const short& u,                const negatable& v)          { return (negatable(u).data >= v.data); }
    friend inline bool      operator>=(const int& u,                  const negatable& v)          { return (negatable(u).data >= v.data); }
    friend inline bool      operator>=(const long& u,                 const negatable& v)          { return (negatable(u).data >= v.data); }
    friend inline bool      operator>=(const long long& u,            const negatable& v)          { return (negatable(u).data >= v.data); }

    friend inline bool      operator>=(const unsigned char& u,        const negatable& v)          { return (negatable(u).data >= v.data); }
    friend inline bool      operator>=(const unsigned short& u,       const negatable& v)          { return (negatable(u).data >= v.data); }
    friend inline bool      operator>=(const unsigned int& u,         const negatable& v)          { return (negatable(u).data >= v.data); }
    friend inline bool      operator>=(const unsigned long& u,        const negatable& v)          { return (negatable(u).data >= v.data); }
    friend inline bool      operator>=(const unsigned long long& u,   const negatable& v)          { return (negatable(u).data >= v.data); }

    friend inline bool      operator>=(const float& u,                const negatable& v)          { return ((negatable(u).data >= v.data) && (!((negatable::is_quiet_nan(u)) && negatable::is_quiet_nan(v)))); }
    friend inline bool      operator>=(const double& u,               const negatable& v)          { return ((negatable(u).data >= v.data) && (!((negatable::is_quiet_nan(u)) && negatable::is_quiet_nan(v)))); }
    friend inline bool      operator>=(const double long& u,          const negatable& v)          { return ((negatable(u).data >= v.data) && (!((negatable::is_quiet_nan(u)) && negatable::is_quiet_nan(v)))); }

    friend inline bool      operator<=(const negatable& u,            const negatable& v)          { return ((u.data <= v.data) || (negatable::is_quiet_nan(u) && negatable::is_quiet_nan(v))); }

    friend inline bool      operator<=(const negatable& u,            const char& v)               { return (u.data <= negatable(v).data); }
    friend inline bool      operator<=(const negatable& u,            const short& v)              { return (u.data <= negatable(v).data); }
    friend inline bool      operator<=(const negatable& u,            const int& v)                { return (u.data <= negatable(v).data); }
    friend inline bool      operator<=(const negatable& u,            const long& v)               { return (u.data <= negatable(v).data); }
    friend inline bool      operator<=(const negatable& u,            const long long& v)          { return (u.data <= negatable(v).data); }

    friend inline bool      operator<=(const negatable& u,            const unsigned char& v)      { return (u.data <= negatable(v).data); }
    friend inline bool      operator<=(const negatable& u,            const unsigned short& v)     { return (u.data <= negatable(v).data); }
    friend inline bool      operator<=(const negatable& u,            const unsigned int& v)       { return (u.data <= negatable(v).data); }
    friend inline bool      operator<=(const negatable& u,            const unsigned long& v)      { return (u.data <= negatable(v).data); }
    friend inline bool      operator<=(const negatable& u,            const unsigned long long& v) { return (u.data <= negatable(v).data); }

    friend inline bool      operator<=(const negatable& u,            const float& v)              { return ((u.data <= negatable(v).data) || (negatable::is_quiet_nan(u) && (negatable::is_quiet_nan(v)))); }
    friend inline bool      operator<=(const negatable& u,            const double& v)             { return ((u.data <= negatable(v).data) || (negatable::is_quiet_nan(u) && (negatable::is_quiet_nan(v)))); }
    friend inline bool      operator<=(const negatable& u,            const long double& v)        { return ((u.data <= negatable(v).data) || (negatable::is_quiet_nan(u) && (negatable::is_quiet_nan(v)))); }

    friend inline bool      operator<=(const char& u,                 const negatable& v)          { return (negatable(u).data <= v.data); }
    friend inline bool      operator<=(const short& u,                const negatable& v)          { return (negatable(u).data <= v.data); }
    friend inline bool      operator<=(const int& u,                  const negatable& v)          { return (negatable(u).data <= v.data); }
    friend inline bool      operator<=(const long& u,                 const negatable& v)          { return (negatable(u).data <= v.data); }
    friend inline bool      operator<=(const long long& u,            const negatable& v)          { return (negatable(u).data <= v.data); }

    friend inline bool      operator<=(const unsigned char& u,        const negatable& v)          { return (negatable(u).data <= v.data); }
    friend inline bool      operator<=(const unsigned short& u,       const negatable& v)          { return (negatable(u).data <= v.data); }
    friend inline bool      operator<=(const unsigned int& u,         const negatable& v)          { return (negatable(u).data <= v.data); }
    friend inline bool      operator<=(const unsigned long& u,        const negatable& v)          { return (negatable(u).data <= v.data); }
    friend inline bool      operator<=(const unsigned long long& u,   const negatable& v)          { return (negatable(u).data <= v.data); }

    friend inline bool      operator<=(const float& u,                const negatable& v)          { return ((negatable(u).data <= v.data) || ((negatable::is_quiet_nan(u)) && negatable::is_quiet_nan(v))); }
    friend inline bool      operator<=(const double& u,               const negatable& v)          { return ((negatable(u).data <= v.data) || ((negatable::is_quiet_nan(u)) && negatable::is_quiet_nan(v))); }
    friend inline bool      operator<=(const double long& u,          const negatable& v)          { return ((negatable(u).data <= v.data) || ((negatable::is_quiet_nan(u)) && negatable::is_quiet_nan(v))); }

    friend inline negatable fabs(const negatable& x)
    {
      return ((x.data < value_type(0)) ? -x : x);
    }

    friend inline negatable floor(const negatable& x)
    {
      // TBD: implement floor().
      return negatable(0);
    }

    friend inline negatable ceil(const negatable& x)
    {
      // TBD: implement ceil().
      return negatable(0);
    }

    friend inline negatable sqrt(const negatable& x)
    {
      if(negatable::is_quiet_nan(x))
      {
        return negatable::value_quiet_nan();
      }
      else if(x > 0)
      {
        // TBD: Use a more efficient square root algorithm (if one can be found).
        return exp(log(x) / 2);
      }
      else if(x < 0)
      {
        return negatable::value_quiet_nan();
      }
      else
      {
        return negatable(0);
      }
    }

    friend inline negatable exp(const negatable& x)
    {
      if(negatable::is_quiet_nan(x))
      {
        return negatable::value_quiet_nan();
      }
      else if(x > 0)
      {
        const value_type n = static_cast<value_type>(x / negatable(nothing(), make_unsigned_constant(11629079)));

        const negatable alpha = x - (n * negatable(nothing(), make_unsigned_constant(11629079)));

        // Obtained from Wolfram's Alpha or Mathematica(R) with the following command.
        // The coefficientws have subsequently been *rationalized* for the <32,-24> split.
        // Fit[N[Table[{x, Exp[x] - 1}, {x, -Log[2], Log[2], 1/180}], 50], {x, x^2, x^3, x^4, x^5, x^6}, x]
        negatable sum  =   1
                         + alpha * (negatable(nothing(), make_unsigned_constant(16777246))
                         + alpha * (negatable(nothing(), make_unsigned_constant( 8388613))
                         + alpha * (negatable(nothing(), make_unsigned_constant( 2795628))
                         + alpha * (negatable(nothing(), make_unsigned_constant(  698971))
                         + alpha * (negatable(nothing(), make_unsigned_constant(  142422))
                         + alpha * (negatable(nothing(), make_unsigned_constant(   23635))))))));

        return negatable(nothing(), sum.data << n);
      }
      else if(x < 0)
      {
        return 1 / exp(-x);
      }
      else
      {
        return negatable(1);
      }
    }

    friend inline negatable log(const negatable& x)
    {
      if(negatable::is_quiet_nan(x))
      {
        return negatable::value_quiet_nan();
      }
      else if(x > 0)
      {
        if(x > 1)
        {
          negatable xx  = x;

          const value_type n = static_cast<value_type>(xx / 2);

          // TBD: Is argument scaling here correct, or would it be better to use a constant offset?
          xx.data >>= n;

          --xx;

          // TBD: Should this approximation be improved?
          negatable sum        = xx * (negatable(nothing(), + make_unsigned_constant(16768752))
                               + xx * (negatable(nothing(), - make_unsigned_constant( 8252862))
                               + xx * (negatable(nothing(), + make_unsigned_constant( 4856580))
                               + xx * (negatable(nothing(), - make_unsigned_constant( 2282754))
                               + xx * (negatable(nothing(), + make_unsigned_constant(  539529)))))));

          return sum + (n * negatable(nothing(), make_unsigned_constant(11629079)));
        }
        else if(x < 1)
        {
          return -log(1 / x);
        }
        else
        {
          return negatable(0);
        }
      }
      else
      {
        return negatable::value_quiet_nan();
      }
    }

    friend inline negatable sin(const negatable& x)
    {
      if(negatable::is_quiet_nan(x))
      {
        return negatable::value_quiet_nan();
      }
      else
      {
        return cos(x - negatable(nothing(), make_unsigned_constant(26353589)));
      }
    }

    friend inline negatable cos(const negatable& x)
    {
      if(negatable::is_quiet_nan(x))
      {
        return negatable::value_quiet_nan();
      }
      else
      {
        negatable xx = x;

        if(x < 0) { xx = -xx; }

        value_type n = static_cast<value_type>(x * negatable(nothing(), make_unsigned_constant(10680707)));

        xx = xx - (n * negatable(nothing(), make_unsigned_constant(26353589)));

        bool x_sym = true;
        bool y_sym = true;

        if((n % 2) == 0) { y_sym = false; }
        if((n % 3) == 0) { x_sym = y_sym = false; }
        if((n % 4) == 0) { x_sym = y_sym = false; }

        if(y_sym) { xx = negatable(nothing(), make_unsigned_constant(26353589)) - xx; }

        const negatable x2  = xx * xx;

        const negatable sum =         1
                              + x2 * (negatable(nothing(), - make_unsigned_constant(8388607))
                              + x2 * (negatable(nothing(), + make_unsigned_constant( 699050))
                              + x2 * (negatable(nothing(), - make_unsigned_constant(  23300))
                              + x2 * (negatable(nothing(), + make_unsigned_constant(    415))
                              + x2 * (negatable(nothing(), - make_unsigned_constant(      4)))))));

        return ((x_sym) ? -sum : sum);
      }
    }

    friend inline negatable tan(const negatable& x)
    {
      if(negatable::is_quiet_nan(x))
      {
        return negatable::value_quiet_nan();
      }
      else
      {
        return sin(x) / cos(x);
      }
    }

    friend inline negatable asin(const negatable& x)
    {
      if(negatable::is_quiet_nan(x))
      {
        return negatable::value_quiet_nan();
      }
      else if(x > 0)
      {
        if(x > 1)
        {
          return negatable::value_quiet_nan();
        }
        else
        {
          const negatable sum =          negatable(nothing(), + make_unsigned_constant(26353588))
                                  + x * (negatable(nothing(), - make_unsigned_constant( 3600370))
                                  + x * (negatable(nothing(), + make_unsigned_constant( 1492819))
                                  + x * (negatable(nothing(), - make_unsigned_constant(  841785))
                                  + x * (negatable(nothing(), + make_unsigned_constant(  518279))
                                  + x * (negatable(nothing(), - make_unsigned_constant(  286691))
                                  + x * (negatable(nothing(), + make_unsigned_constant(  111905))
                                  + x * (negatable(nothing(), - make_unsigned_constant(   21181)))))))));

          return negatable(nothing(), + make_unsigned_constant(26353589)) - (sqrt(1 - x) * sum);
        }
      }
      else
      {
        return -asin(-x);
      }
    }

    friend inline negatable acos(const negatable& x)
    {
      if(negatable::is_quiet_nan(x))
      {
        return negatable::value_quiet_nan();
      }
      else
      {
        return negatable(nothing(), make_unsigned_constant(26353589)) - asin(x);
      }
    }

    friend inline negatable atan(const negatable& x)
    {
      if(negatable::is_quiet_nan(x))
      {
        return negatable::value_quiet_nan();
      }
      else if(x < 0)
      {
        return -atan(-x);
      }
      else if(x > 0)
      {
        if(x > 1)
        {
          return negatable(nothing(), + make_unsigned_constant(26353589)) - atan(1 / x);
        }
        else
        {
          const negatable x2 = x * x;

          return     x * (negatable(nothing(), + make_unsigned_constant(16774967))
                  + x2 * (negatable(nothing(), - make_unsigned_constant( 5541506))
                  + x2 * (negatable(nothing(), + make_unsigned_constant( 3022264))
                  + x2 * (negatable(nothing(), - make_unsigned_constant( 1428294))
                  + x2 * (negatable(nothing(), + make_unsigned_constant(  349554)))))));
        }
      }
      else
      {
        return negatable(0);
      }
    }

    friend inline negatable sinh(const negatable& x)
    {
      if(negatable::is_quiet_nan(x))
      {
        return negatable::value_quiet_nan();
      }
      else
      {
        // TBD: Use a small argument approximation for small arguments.
        const negatable ep = exp(x);
        const negatable em = 1 / ep;

        return (ep - em) / 2;
      }
    }

    friend inline negatable cosh(const negatable& x)
    {
      if(negatable::is_quiet_nan(x))
      {
        return negatable::value_quiet_nan();
      }
      else
      {
        const negatable ep = exp(x);
        const negatable em = 1 / ep;

        return (ep + em) / 2;
      }
    }

    friend inline negatable tanh(const negatable& x)
    {
      if(negatable::is_quiet_nan(x))
      {
        return negatable::value_quiet_nan();
      }
      else
      {
        const negatable ep = exp(+x);
        const negatable em = 1 / ep;

        return (ep - em) / (ep + em);
      }
    }

    friend inline negatable asinh(const negatable& x)
    {
      if(negatable::is_quiet_nan(x))
      {
        return negatable::value_quiet_nan();
      }
      else
      {
        return log(x + exp(log((x * x) + 1) / 2));
      }
    }

    friend inline negatable acosh(const negatable& x)
    {
      if(negatable::is_quiet_nan(x))
      {
        return negatable::value_quiet_nan();
      }
      else
      {
        return log(x + exp(log((x * x) - 1) / 2));
      }
    }

    friend inline negatable atanh(const negatable& x)
    {
      if(negatable::is_quiet_nan(x))
      {
        return negatable::value_quiet_nan();
      }
      else
      {
        return log((1 + x) / (1 - x)) / 2;
      }
    }
  };

  } } // namespace math::fixed_point

  // Provide a specialization of std::numeric_limits<negatable>.
  namespace std
  {
    template<const int range,
             const int resolution,
             const math::fixed_point::round::round_type round_mode,
             const math::fixed_point::overflow::overflow_type overflow_mode>
    class numeric_limits<math::fixed_point::negatable<range, resolution, round_mode, overflow_mode> >
    {
    private:
      typedef math::fixed_point::negatable<range, resolution, round_mode, overflow_mode> negatable_type;

    public:
      static const bool                    is_specialized    = true;
      static const int                     digits            = std::numeric_limits<typename negatable_type::value_type>::digits;
      static const int                     digits10          = std::numeric_limits<typename negatable_type::value_type>::digits;
      static const int                     max_digits10      = std::numeric_limits<typename negatable_type::value_type>::max_digits10;
      static const bool                    is_signed         = true;
      static const bool                    is_integer        = false;
      static const bool                    is_exact          = true;
      static const int                     radix             = 2;
      static const int                     min_exponent      = -negatable_type::radix_split;
      static const int                     min_exponent10    = static_cast<int>((static_cast<long>(min_exponent) * 301L) / 1000L);
      static const int                     max_exponent      = std::numeric_limits<typename negatable_type::value_type>::digits - negatable_type::radix_split;
      static const int                     max_exponent10    = static_cast<int>((static_cast<long>(max_exponent) * 301L) / 1000L);
      static const bool                    has_infinity      = true;
      static const bool                    has_quiet_NaN     = true;
      static const bool                    has_signaling_NaN = false;
      static const std::float_denorm_style has_denorm        = std::denorm_absent;
      static const bool                    has_denorm_loss   = false;
      static const bool                    is_iec559         = false;
      static const bool                    is_bounded        = true;
      static const bool                    is_modulo         = false;
      static const bool                    traps             = false;
      static const bool                    tinyness_before   = false;
      static const std::float_round_style  round_style       = std::round_toward_zero;

      static negatable_type (min)() throw()                  { return negatable_type::value_min(); }
      static negatable_type (max)() throw()                  { return negatable_type::value_max(); }
      static negatable_type lowest() throw()                 { return -(max)(); }
      static negatable_type epsilon() throw()                { return negatable_type::value_epsilon(); }
      static negatable_type round_error() throw()            { return negatable_type(1) / 2; }
      static negatable_type infinity() throw()               { return negatable_type::value_infinity(); }
      static negatable_type quiet_NaN() throw()              { return negatable_type::value_quiet_nan(); }
    };
  } // namespace std

#endif // _FIXED_POINT_2014_03_03_HPP_
