///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 1999 - 2024.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

// Implement templates for an extended complex class and
// its associated functions. These are intended to be used
// with both user-defined types as well as built-in float,
// double and long double.

#ifndef EXTENDED_COMPLEX_2016_02_22
  #define EXTENDED_COMPLEX_2016_02_22

  #if !defined(EXTENDED_COMPLEX_DISABLE_IOSTREAM)
  #include <algorithm>
  #include <array>
  #endif
  #include <cmath>
  #include <cstddef>
  #include <cstdint>
  #if !defined(EXTENDED_COMPLEX_DISABLE_IOSTREAM)
  #include <istream>
  #include <ostream>
  #include <regex>
  #include <sstream>
  #include <string>
  #endif
  #include <type_traits>
  #include <utility>

  #define EXTENDED_COMPLEX_CONSTEXPR constexpr

  namespace extended_complex
  {
    // Forward declarations.

    // Class template extended_complex::complex<T, EnableType>.
    // See also ISO/IEC 14882:2011 Sect. 26.4.2.

    template<typename T, typename EnableType = void>
    class complex;

    // Class template specializations of extended_complex::complex<T, EnableType>.
    // See also ISO/IEC 14882:2011 Sect. 26.4.3.

    template<typename T>
    class complex<T, typename std::enable_if<std::is_floating_point<T>::value>::type>;

    // Non-member operations for extended_complex::complex<T, EnableType>.
    // Similar to ISO/IEC 14882:2011 Sect. 26.4.6.

    // Unary +/- operators.
    template<typename T, typename EnableType = void> complex<T, EnableType> operator+(const complex<T, EnableType>&);
    template<typename T, typename EnableType = void> complex<T, EnableType> operator-(const complex<T, EnableType>&);

    // Global add, sub, mul, div operators.
    template<typename T, typename EnableType = void> complex<T, EnableType> operator+(const complex<T, EnableType>&, const complex<T, EnableType>&);
    template<typename T, typename EnableType = void> complex<T, EnableType> operator-(const complex<T, EnableType>&, const complex<T, EnableType>&);
    template<typename T, typename EnableType = void> complex<T, EnableType> operator*(const complex<T, EnableType>&, const complex<T, EnableType>&);
    template<typename T, typename EnableType = void> complex<T, EnableType> operator/(const complex<T, EnableType>&, const complex<T, EnableType>&);

    template<typename T, typename EnableType = void> complex<T, EnableType> operator+(const complex<T, EnableType>&, const T&);
    template<typename T, typename EnableType = void> complex<T, EnableType> operator-(const complex<T, EnableType>&, const T&);
    template<typename T, typename EnableType = void> complex<T, EnableType> operator*(const complex<T, EnableType>&, const T&);
    template<typename T, typename EnableType = void> complex<T, EnableType> operator/(const complex<T, EnableType>&, const T&);

    template<typename T, typename EnableType = void> complex<T, EnableType> operator+(const T&, const complex<T, EnableType>&);
    template<typename T, typename EnableType = void> complex<T, EnableType> operator-(const T&, const complex<T, EnableType>&);
    template<typename T, typename EnableType = void> complex<T, EnableType> operator*(const T&, const complex<T, EnableType>&);
    template<typename T, typename EnableType = void> complex<T, EnableType> operator/(const T&, const complex<T, EnableType>&);

    // Equality and inequality operators.
    template<typename T, typename EnableType = void> bool operator==(const complex<T, EnableType>&, const complex<T, EnableType>&);
    template<typename T, typename EnableType = void> bool operator==(const complex<T, EnableType>&, const T&);
    template<typename T, typename EnableType = void> bool operator==(const T&,          const complex<T, EnableType>&);

    template<typename T, typename EnableType = void> bool operator!=(const complex<T, EnableType>&, const complex<T, EnableType>&);
    template<typename T, typename EnableType = void> bool operator!=(const complex<T, EnableType>&, const T&);
    template<typename T, typename EnableType = void> bool operator!=(const T&,                      const complex<T, EnableType>&);

    #if !defined(EXTENDED_COMPLEX_DISABLE_IOSTREAM)

    // I/O stream operators.
    template<typename T, typename char_type, typename traits_type, typename EnableType = void>
    std::basic_istream<char_type, traits_type>& operator>>(std::basic_istream<char_type, traits_type>&, complex<T, EnableType>&);

    template<typename T, typename char_type, typename traits_type, typename EnableType = void>
    std::basic_ostream<char_type, traits_type>& operator<<(std::basic_ostream<char_type, traits_type>&, const complex<T, EnableType>&);

    #endif // !EXTENDED_COMPLEX_DISABLE_IOSTREAM

    // Value operations for extended_complex::complex<T, EnableType>.
    // Similar to ISO/IEC 14882:2011 Sect. 26.4.7.

    template<typename T, typename EnableType = void> T real (const complex<T, EnableType>&);
    template<typename T, typename EnableType = void> T imag (const complex<T, EnableType>&);

    template<typename T, typename EnableType = void> T abs  (const complex<T, EnableType>&);
    template<typename T, typename EnableType = void> T arg  (const complex<T, EnableType>&);
    template<typename T, typename EnableType = void> T norm (const complex<T, EnableType>&);

    template<typename T, typename EnableType = void> complex<T, EnableType> conj (const complex<T, EnableType>&);
    template<typename T, typename EnableType = void> complex<T, EnableType> proj (const complex<T, EnableType>&);
    template<typename T, typename EnableType = void> complex<T, EnableType> polar(const T&, const T& = T(static_cast<unsigned>(UINT8_C(0))));

    // Elementary transcendental functions for extended_complex::complex<T, EnableType>.
    // Similar to ISO/IEC 14882:2011 Sect. 26.4.8.

    template<typename T, typename EnableType = void> complex<T, EnableType> acos (const complex<T, EnableType>&);
    template<typename T, typename EnableType = void> complex<T, EnableType> asin (const complex<T, EnableType>&);
    template<typename T, typename EnableType = void> complex<T, EnableType> atan (const complex<T, EnableType>&);
    template<typename T, typename EnableType = void> complex<T, EnableType> asinh(const complex<T, EnableType>&);
    template<typename T, typename EnableType = void> complex<T, EnableType> acosh(const complex<T, EnableType>&);
    template<typename T, typename EnableType = void> complex<T, EnableType> atanh(const complex<T, EnableType>&);

    template<typename T, typename EnableType = void> complex<T, EnableType> cos  (const complex<T, EnableType>&);
    template<typename T, typename EnableType = void> complex<T, EnableType> cosh (const complex<T, EnableType>&);
    template<typename T, typename EnableType = void> complex<T, EnableType> exp  (const complex<T, EnableType>&);
    template<typename T, typename EnableType = void> complex<T, EnableType> log  (const complex<T, EnableType>&);
    template<typename T, typename EnableType = void> complex<T, EnableType> log10(const complex<T, EnableType>&);

    template<typename T, typename IntegralType, typename EnableType = void> typename std::enable_if<std::is_integral<IntegralType>::value, complex<T, EnableType>>::type
                                                                            pow  (const complex<T, EnableType>&, IntegralType);
    template<typename T, typename EnableType = void> complex<T, EnableType> pow  (const complex<T, EnableType>&, const T&);
    template<typename T, typename EnableType = void> complex<T, EnableType> pow  (const complex<T, EnableType>&, const complex<T, EnableType>&);
    template<typename T, typename EnableType = void> complex<T, EnableType> pow  (const T&, const complex<T, EnableType>&);

    template<typename T, typename EnableType = void> complex<T, EnableType> sin  (const complex<T, EnableType>&);
    template<typename T, typename EnableType = void> complex<T, EnableType> sinh (const complex<T, EnableType>&);
    template<typename T, typename EnableType = void> complex<T, EnableType> sqrt (const complex<T, EnableType>&);
    template<typename T, typename EnableType = void> complex<T, EnableType> tan  (const complex<T, EnableType>&);
    template<typename T, typename EnableType = void> complex<T, EnableType> tanh (const complex<T, EnableType>&);

    // Class template extended_complex::complex<T, EnableType>.
    // See also ISO/IEC 14882:2011 Sect. 26.4.2.

    template<typename T, typename EnableType>
    class complex
    {
    public:
      typedef T value_type;

      complex(const value_type& my_x = value_type(),
              const value_type& my_y = value_type()) : my_re(my_x),
                                                       my_im(my_y) { }

      complex(const complex& other) : my_re(other.real()),
                                      my_im(other.imag()) { }

      complex(complex&& other) noexcept : my_re(std::move(static_cast<value_type&&>(other.my_re))),
                                          my_im(std::move(static_cast<value_type&&>(other.my_im))) { }

      template<typename X>
      complex(const complex<X>& my_z) : my_re(static_cast<value_type>(my_z.real())),
                                        my_im(static_cast<value_type>(my_z.imag())) { }

      complex& operator=(const complex& other)
      {
        if(this != &other)
        {
          my_re = other.my_re;
          my_im = other.my_im;
        }

        return *this;
      }

      complex& operator=(complex&& other) noexcept
      {
        my_re = std::move(static_cast<value_type&&>(other.my_re));
        my_im = std::move(static_cast<value_type&&>(other.my_im));

        return *this;
      }

      template<typename X>
      complex& operator=(const complex<X>& other)
      {
        my_re = static_cast<value_type>(other.my_re);
        my_im = static_cast<value_type>(other.my_im);

        return *this;
      }

      complex& operator=(const value_type& other_x)
      {
        my_re = other_x;
        my_im = static_cast<value_type>(static_cast<unsigned>(UINT8_C(0)));

        return *this;
      }

      value_type real() const { return my_re; }
      value_type imag() const { return my_im; }

      void real(const value_type& my_x) { my_re = my_x; }
      void imag(const value_type& my_y) { my_im = my_y; }

      complex& operator+=(const value_type& my_x)
      {
        my_re += my_x;

        return *this;
      }

      complex& operator-=(const value_type& my_x)
      {
        my_re -= my_x;

        return *this;
      }

      complex& operator*=(const value_type& my_x)
      {
        my_re *= my_x;
        my_im *= my_x;

        return *this;
      }

      complex& operator/=(const value_type& my_x)
      {
        my_re /= my_x;
        my_im /= my_x;

        return *this;
      }

      template<typename X>
      complex& operator+=(const complex<X>& my_z)
      {
        my_re += static_cast<value_type>(my_z.my_re);
        my_im += static_cast<value_type>(my_z.my_im);

        return *this;
      }

      template<typename X>
      complex& operator-=(const complex<X>& my_z)
      {
        if(this == &my_z)
        {
          my_re = static_cast<value_type>(static_cast<unsigned>(UINT8_C(0)));
          my_im = static_cast<value_type>(static_cast<unsigned>(UINT8_C(0)));
        }
        else
        {
          my_re -= static_cast<value_type>(my_z.my_re);
          my_im -= static_cast<value_type>(my_z.my_im);
        }

        return *this;
      }

      template<typename X>
      complex& operator*=(const complex<X>& my_z)
      {
        const value_type tmp_re(my_re);

        if(this == &my_z)
        {
          my_re = (tmp_re * tmp_re) - (my_im * my_im);
          my_im = (tmp_re * my_im) * 2U;
        }
        else
        {
          my_re = (tmp_re * my_z.my_re) - (my_im * my_z.my_im);
          my_im = (tmp_re * my_z.my_im) + (my_im * my_z.my_re);
        }

        return *this;
      }

      template<typename X>
      complex& operator/=(const complex<X>& my_z)
      {
        if(this == &my_z)
        {
          my_re = static_cast<value_type>(static_cast<unsigned>(UINT8_C(1)));
          my_im = static_cast<value_type>(static_cast<unsigned>(UINT8_C(0)));
        }
        else
        {
          if(fabs(my_z.real()) < fabs(my_z.imag()))
          {
            const value_type my_c_over_d = my_z.real() / my_z.imag();

            const value_type my_denominator = (my_z.real() * my_c_over_d) + my_z.imag();

            const value_type my_tmp_re(my_re);

            my_re = ((my_tmp_re * my_c_over_d) + my_im)     / my_denominator;
            my_im = ((my_im     * my_c_over_d) - my_tmp_re) / my_denominator;
          }
          else
          {
            const value_type my_d_over_c = my_z.imag() / my_z.real();

            const value_type my_denominator = (my_z.imag() * my_d_over_c) + my_z.real();

            const value_type my_tmp_re(my_re);

            my_re = (( my_im     * my_d_over_c) + my_tmp_re) / my_denominator;
            my_im = ((-my_tmp_re * my_d_over_c) + my_im)     / my_denominator;
          }
        }

        return *this;
      }

    private:
      value_type my_re;
      value_type my_im;
    };

    // Specialization of class template extended_complex::complex<>
    // for built-in floating-point types.
    // See also ISO/IEC 14882:2011 Sect. 26.4.3.

    template<typename T>
    class complex<T, typename std::enable_if<std::is_floating_point<T>::value>::type>
    {
    public:
      using value_type = T;

      EXTENDED_COMPLEX_CONSTEXPR complex(value_type my_x = value_type(),
                                         value_type my_y = value_type()) : my_re(my_x),
                                                                           my_im(my_y) { }

      EXTENDED_COMPLEX_CONSTEXPR complex(const complex& other) : my_re(other.my_re),
                                                                 my_im(other.my_im) { }

      EXTENDED_COMPLEX_CONSTEXPR complex(complex&& other) noexcept : my_re(std::move(static_cast<value_type&&>(other.my_re))),
                                                                     my_im(std::move(static_cast<value_type&&>(other.my_im))) { }

      template<typename OtherFloatingPointType,
               typename OtherFloatingPointEnableType = typename std::enable_if_t<std::is_floating_point<OtherFloatingPointType>::value && (sizeof(OtherFloatingPointType) != sizeof(value_type)), void>>
      explicit EXTENDED_COMPLEX_CONSTEXPR complex(const complex<OtherFloatingPointType>& other)
        : my_re(static_cast<value_type>(other.my_re)),
          my_im(static_cast<value_type>(other.my_im)) { }

      complex& operator=(const complex& other)
      {
        if(this != &other)
        {
          my_re = other.my_re;
          my_im = other.my_im;
        }

        return *this;
      }

      complex& operator=(complex&& other) noexcept
      {
        my_re = std::move(static_cast<value_type&&>(other.my_re));
        my_im = std::move(static_cast<value_type&&>(other.my_im));

        return *this;
      }

      complex& operator=(const value_type& other_x)
      {
        my_re = other_x;
        my_im = static_cast<value_type>(0.0L);

        return *this;
      }

      template<typename OtherFloatingPointType,
               typename OtherFloatingPointEnableType = typename std::enable_if_t<std::is_floating_point<OtherFloatingPointType>::value && (sizeof(OtherFloatingPointType) != sizeof(value_type)), void>>
      complex& operator=(const complex<OtherFloatingPointType>& other)
      {
        my_re = other.my_re;
        my_im = other.my_im;

        return *this;
      }

      EXTENDED_COMPLEX_CONSTEXPR value_type real() const { return my_re; }
      EXTENDED_COMPLEX_CONSTEXPR value_type imag() const { return my_im; }

      void real(const value_type& my_x) { my_re = my_x; }
      void imag(const value_type& my_y) { my_im = my_y; }

      complex& operator+=(const value_type& my_x)
      {
        my_re += my_x;

        return *this;
      }

      complex& operator-=(const value_type& my_x)
      {
        my_re -= my_x;

        return *this;
      }

      complex& operator*=(const value_type& my_x)
      {
        my_re *= my_x;
        my_im *= my_x;

        return *this;
      }

      complex& operator/=(const value_type& my_x)
      {
        my_re /= my_x;
        my_im /= my_x;

        return *this;
      }

      template<typename X>
      complex& operator+=(const complex<X>& my_z)
      {
        my_re += static_cast<value_type>(my_z.my_re);
        my_im += static_cast<value_type>(my_z.my_im);

        return *this;
      }

      template<typename X>
      complex& operator-=(const complex<X>& my_z)
      {
        my_re -= static_cast<value_type>(my_z.my_re);
        my_im -= static_cast<value_type>(my_z.my_im);

        return *this;
      }

      template<typename X>
      complex& operator*=(const complex<X>& my_z)
      {
        const value_type tmp_re(my_re);

        if(this == &my_z)
        {
          my_re = (tmp_re * tmp_re) - (my_im * my_im);
          my_im = (tmp_re * my_im) * static_cast<value_type>(2.0L);
        }
        else
        {
          my_re = (tmp_re * my_z.my_re) - (my_im * my_z.my_im);
          my_im = (tmp_re * my_z.my_im) + (my_im * my_z.my_re);
        }

        return *this;
      }

      template<typename X>
      complex& operator/=(const complex<X>& my_z)
      {
        if(this == &my_z)
        {
          my_re = static_cast<value_type>(1.0L);
          my_im = static_cast<value_type>(0.0L);
        }
        else
        {
          using std::fabs;

          if(fabs(my_z.real()) < fabs(my_z.imag()))
          {
            const value_type my_c_over_d = my_z.real() / my_z.imag();

            const value_type my_denominator = (my_z.real() * my_c_over_d) + my_z.imag();

            const value_type my_tmp_re(my_re);

            real(((my_tmp_re * my_c_over_d) + my_im)     / my_denominator);
            imag(((my_im     * my_c_over_d) - my_tmp_re) / my_denominator);
          }
          else
          {
            const value_type my_d_over_c = my_z.imag() / my_z.real();

            const value_type my_denominator = (my_z.imag() * my_d_over_c) + my_z.real();

            const value_type my_tmp_re(my_re);

            real((( my_im     * my_d_over_c) + my_tmp_re) / my_denominator);
            imag(((-my_tmp_re * my_d_over_c) + my_im)     / my_denominator);
          }
        }

        return *this;
      }

    private:
      value_type my_re;
      value_type my_im;
    };

    // Non-member operations for extended_complex::complex<T, EnableType>.
    // See also ISO/IEC 14882:2011 Sect. 26.4.6.

    // Unary +/- operators.
    template<typename T, typename EnableType> complex<T, EnableType> operator+(const complex<T, EnableType>& my_u) { return my_u; }
    template<typename T, typename EnableType> complex<T, EnableType> operator-(const complex<T, EnableType>& my_u) { return complex<T, EnableType>(-my_u.real(), -my_u.imag()); }

    // Global add, sub, mul, div operators.
    template<typename T, typename EnableType> complex<T, EnableType> operator+(const complex<T, EnableType>& my_u, const complex<T, EnableType>& my_v) { return complex<T, EnableType>(my_u.real() + my_v.real(), my_u.imag() + my_v.imag()); }
    template<typename T, typename EnableType> complex<T, EnableType> operator-(const complex<T, EnableType>& my_u, const complex<T, EnableType>& my_v) { return complex<T, EnableType>(my_u.real() - my_v.real(), my_u.imag() - my_v.imag()); }

    template<typename T, typename EnableType> complex<T, EnableType> operator*(const complex<T, EnableType>& my_u, const complex<T, EnableType>& my_v)
    {
      return complex<T, EnableType>((my_u.real() * my_v.real()) - (my_u.imag() * my_v.imag()),
                                    (my_u.real() * my_v.imag()) + (my_u.imag() * my_v.real()));
    }

    template<typename T, typename EnableType> complex<T, EnableType> operator/(const complex<T, EnableType>& my_u, const complex<T, EnableType>& my_v)
    {
      using std::fabs;

      complex<T, EnableType> my_result;

      if(fabs(my_v.real()) < fabs(my_v.imag()))
      {
        const T my_c_over_d = my_v.real() / my_v.imag();

        const T my_denominator = (my_v.real() * my_c_over_d) + my_v.imag();

        my_result = complex<T, EnableType>(((my_u.real() * my_c_over_d) + my_u.imag()) / my_denominator,
                                           ((my_u.imag() * my_c_over_d) - my_u.real()) / my_denominator);
      }
      else
      {
        const T my_d_over_c = my_v.imag() / my_v.real();

        const T my_denominator = (my_v.imag() * my_d_over_c) + my_v.real();

        my_result = complex<T, EnableType>((( my_u.imag() * my_d_over_c) + my_u.real()) / my_denominator,
                                           ((-my_u.real() * my_d_over_c) + my_u.imag()) / my_denominator);
      }

      return my_result;
    }

    template<typename T, typename EnableType> complex<T, EnableType> operator+(const complex<T, EnableType>& my_u, const T& my_v) { return complex<T, EnableType>(my_u.real() + my_v, my_u.imag()); }
    template<typename T, typename EnableType> complex<T, EnableType> operator-(const complex<T, EnableType>& my_u, const T& my_v) { return complex<T, EnableType>(my_u.real() - my_v, my_u.imag()); }
    template<typename T, typename EnableType> complex<T, EnableType> operator*(const complex<T, EnableType>& my_u, const T& my_v) { return complex<T, EnableType>(my_u.real() * my_v, my_u.imag() * my_v); }
    template<typename T, typename EnableType> complex<T, EnableType> operator/(const complex<T, EnableType>& my_u, const T& my_v) { return complex<T, EnableType>(my_u.real() / my_v, my_u.imag() / my_v); }

    template<typename T, typename EnableType> complex<T, EnableType> operator+(const T& my_u, const complex<T, EnableType>& my_v) { return complex<T, EnableType>(my_u + my_v.real(), my_v.imag()); }
    template<typename T, typename EnableType> complex<T, EnableType> operator-(const T& my_u, const complex<T, EnableType>& my_v) { return complex<T, EnableType>(my_u - my_v.real(), -my_v.imag()); }
    template<typename T, typename EnableType> complex<T, EnableType> operator*(const T& my_u, const complex<T, EnableType>& my_v) { return complex<T, EnableType>(my_u * my_v.real(), my_u * my_v.imag()); }

    template<typename T, typename EnableType> complex<T, EnableType> operator/(const T& my_u, const complex<T, EnableType>& my_v)
    {
      using std::fabs;

      complex<T, EnableType> my_result;

      if(fabs(my_v.real()) < fabs(my_v.imag()))
      {
        const T my_c_over_d = my_v.real() / my_v.imag();

        const T my_denominator = (my_v.real() * my_c_over_d) + my_v.imag();

        my_result = complex<T, EnableType>(( my_u * my_c_over_d) / my_denominator,
                                            -my_u                / my_denominator);
      }
      else
      {
        const T my_d_over_c = my_v.imag() / my_v.real();

        const T my_denominator = (my_v.imag() * my_d_over_c) + my_v.real();

        my_result = complex<T, EnableType>(  my_u                / my_denominator,
                                           (-my_u * my_d_over_c) / my_denominator);
      }

      return my_result;
    }

    // Equality and inequality operators.
    template<typename T, typename EnableType> bool operator==(const complex<T, EnableType>& my_u, const complex<T, EnableType>& my_v) { return ((my_u.real() == my_v.real()) && (my_u.imag() == my_v.imag())); }
    template<typename T, typename EnableType> bool operator==(const complex<T, EnableType>& my_u, const T&                      my_v) { return ((my_u.real() == my_v)        && (my_u.imag() == T(0))); }
    template<typename T, typename EnableType> bool operator==(const T&                      my_u, const complex<T, EnableType>& my_v) { return ((my_u == my_v.real())        && (my_v.imag() == T(0))); }

    template<typename T, typename EnableType> bool operator!=(const complex<T, EnableType>& my_u, const complex<T, EnableType>& my_v) { return ((my_u.real() != my_v.real()) || (my_u.imag() != my_v.imag())); }
    template<typename T, typename EnableType> bool operator!=(const complex<T, EnableType>& my_u, const T&                      my_v) { return ((my_u.real() != my_v)        || (my_u.imag() != T(0))); }
    template<typename T, typename EnableType> bool operator!=(const T&                      my_u, const complex<T, EnableType>& my_v) { return ((my_u != my_v.real())        || (my_v.imag() != T(0))); }

    #if !defined(EXTENDED_COMPLEX_DISABLE_IOSTREAM)

    // I/O stream operators.
    template<typename T, typename char_type, typename traits_type, typename EnableType>
    std::basic_istream<char_type, traits_type>& operator>>(std::basic_istream<char_type, traits_type>& my_istream, complex<T, EnableType>& my_z)
    {
      // Parse an (extended) complex number of any of the forms u, (u) or (u,v).

      const std::array<std::regex, static_cast<std::size_t>(UINT8_C(3))> my_regexes =
      {{
        // A regular expression for an (extended) complex number of the form (u,v).
        std::regex(  std::string("\\({1}")                             // One open parentheses.
                   + std::string("([\\+\\-]{0,1}[0-9]*\\.*[0-9]*)")    // Possible +-, decimal point and digits 0-9.
                   + std::string("([eE]{0,1}[\\+\\-]{0,1}[0-9]*)")     // Possible exponent field.
                   + std::string("\\,{1}")                             // One comma character.
                   + std::string("([\\+\\-]{0,1}[0-9]*\\.*[0-9]*)")    // Possible +-, decimal point and digits 0-9.
                   + std::string("([eE]{0,1}[\\+\\-]{0,1}[0-9]*)")     // Possible exponent field.
                   + std::string("\\){1}")),                           // One close parentheses.

        // A regular expression for an (extended) complex number of the form (u).
        std::regex(  std::string("\\({1}")                             // One open parentheses.
                   + std::string("([\\+\\-]{0,1}[0-9]*\\.*[0-9]*)")    // Possible +-, decimal point and digits 0-9.
                   + std::string("([eE]{0,1}[\\+\\-]{0,1}[0-9]*)")     // Possible exponent field.
                   + std::string("\\){1}")),                           // One close parentheses.

        // A regular expression for an (extended) complex number of the form u.
        std::regex(  std::string("([\\+\\-]{0,1}[0-9]*\\.*[0-9]*)")    // Possible +-, decimal point and digits 0-9.
                   + std::string("([eE]{0,1}[\\+\\-]{0,1}[0-9]*)"))    // Possible exponent field.
      }};

      T my_real_input(static_cast<unsigned>(UINT8_C(0)));
      T my_imag_input(static_cast<unsigned>(UINT8_C(0)));

      bool my_input_has_error = false;

      std::string my_input_str;

      my_istream >> my_input_str;

      std::match_results<std::string::const_iterator> my_mr;

      auto my_it_regex_match =
        std::find_if(my_regexes.cbegin(),
                     my_regexes.cend(),
                     [&my_input_str, &my_mr](const std::regex& my_rx) -> bool
                     {
                       return std::regex_match(my_input_str, my_mr, my_rx);
                     });

      if(my_it_regex_match == my_regexes.cend())
      {
        // The input does not match any of the regular expressions.
        // Set the error flag and take no other action.

        my_input_has_error = true;
      }
      else if(my_it_regex_match == my_regexes.cbegin())
      {
        // The input matches my_regexes[0U], corresponding to the form (u,v).
        // This represents a complex number real and imaginary parts.

        // Rule out erroneous match of invalid mantissa or exponent parts.
        const std::string my_str1(my_mr[static_cast<std::size_t>(UINT8_C(1))]);
        const std::string my_str2(my_mr[static_cast<std::size_t>(UINT8_C(2))]);
        const std::string my_str3(my_mr[static_cast<std::size_t>(UINT8_C(3))]);
        const std::string my_str4(my_mr[static_cast<std::size_t>(UINT8_C(4))]);

        const std::string my_decimal_digits("0123456789");

        const bool my_str1_has_error = ((my_str1.length() != static_cast<std::size_t>(UINT8_C(0))) && (my_str1.find_first_of(my_decimal_digits) == std::string::npos));
        const bool my_str2_has_error = ((my_str2.length() != static_cast<std::size_t>(UINT8_C(0))) && (my_str2.find_first_of(my_decimal_digits) == std::string::npos));
        const bool my_str3_has_error = ((my_str3.length() != static_cast<std::size_t>(UINT8_C(0))) && (my_str3.find_first_of(my_decimal_digits) == std::string::npos));
        const bool my_str4_has_error = ((my_str4.length() != static_cast<std::size_t>(UINT8_C(0))) && (my_str4.find_first_of(my_decimal_digits) == std::string::npos));

        if(my_str1_has_error || my_str2_has_error || my_str3_has_error || my_str4_has_error)
        {
          my_input_has_error = true;
        }
        else
        {
          // Extract the real part of the complex number.
          {
            std::stringstream strm;

            strm << my_mr[static_cast<std::size_t>(UINT8_C(1))] << my_mr[static_cast<std::size_t>(UINT8_C(2))];
            strm >> my_real_input;
          }

          // Extract the imaginary part of the complex number.
          {
            std::stringstream strm;

            strm << my_mr[static_cast<std::size_t>(UINT8_C(3))] << my_mr[static_cast<std::size_t>(UINT8_C(4))];
            strm >> my_imag_input;
          }
        }
      }
      else if(   (my_it_regex_match == (my_regexes.cbegin() + static_cast<std::size_t>(UINT8_C(1))))
              || (my_it_regex_match == (my_regexes.cbegin() + static_cast<std::size_t>(UINT8_C(2)))))
      {
        // The input matches the_regexes[1U] or the_regexes[2U],
        // corresponding to either of the forms (u) or u.
        // This represents a pure real complex number.

        // Rule out erroneous match of invalid mantissa or exponent parts.
        const std::string my_str1(my_mr[static_cast<std::size_t>(UINT8_C(1))]);
        const std::string my_str2(my_mr[static_cast<std::size_t>(UINT8_C(2))]);

        const std::string my_decimal_digits("0123456789");

        if(   ((my_str1.length() != static_cast<std::size_t>(UINT8_C(0))) && (my_str1.find_first_of(my_decimal_digits) == std::string::npos))
           || ((my_str2.length() != static_cast<std::size_t>(UINT8_C(0))) && (my_str2.find_first_of(my_decimal_digits) == std::string::npos)))
        {
          my_input_has_error = true;
        }
        else
        {
          // Extract the real part of the complex number.
          std::stringstream strm;

          strm << my_mr[static_cast<std::size_t>(UINT8_C(1))] << my_mr[static_cast<std::size_t>(UINT8_C(2))];
          strm >> my_real_input;

          my_imag_input = T(static_cast<unsigned>(UINT8_C(0)));
        }
      }

      if(my_input_has_error)
      {
        // Error case: Restore the characters in the input stream
        // and set the fail bit in the input stream.
        std::for_each(my_input_str.cbegin(),
                      my_input_str.cend(),
                      [&my_istream](const char& my_c)
                      {
                        my_istream.putback(my_c);
                      });

        my_istream.setstate(std::ios_base::failbit);
      }
      else
      {
        my_z = complex<T, EnableType>(my_real_input, my_imag_input);
      }

      return my_istream;
    }

    template<typename T, typename char_type, typename traits_type, typename EnableType>
    std::basic_ostream<char_type, traits_type>& operator<<(std::basic_ostream<char_type, traits_type>& my_ostream, const complex<T, EnableType>& my_z)
    {
      std::basic_ostringstream<char_type, traits_type> my_tmp_ostream;

      my_tmp_ostream.flags    (my_ostream.flags());
      my_tmp_ostream.imbue    (my_ostream.getloc());
      my_tmp_ostream.precision(my_ostream.precision());

      my_tmp_ostream << '('
                     << my_z.real()
                     << ','
                     << my_z.imag()
                     << ')';

      return (my_ostream << my_tmp_ostream.str());
    }

    #endif // !EXTENDED_COMPLEX_DISABLE_IOSTREAM

    // Value operations for extended_complex::complex<T, EnableType>.
    // See also ISO/IEC 14882:2011 Sect. 26.4.7.

    template<typename T, typename EnableType> T real(const complex<T, EnableType>& my_z) { return my_z.real(); }
    template<typename T, typename EnableType> T imag(const complex<T, EnableType>& my_z) { return my_z.imag(); }

    template<typename T, typename EnableType> T abs (const complex<T, EnableType>& my_z) { using std::sqrt;  return sqrt(norm(my_z)); }
    template<typename T, typename EnableType> T arg (const complex<T, EnableType>& my_z) { using std::atan2; return atan2(my_z.imag(), my_z.real()); }

    template<typename T, typename EnableType> T norm(const complex<T, EnableType>& my_z)
    {
      using std::fabs;

      T my_result;

      if(fabs(my_z.real()) < fabs(my_z.imag()))
      {
        const T my_a_over_b = my_z.real() / my_z.imag();

        my_result = (my_z.imag() * my_z.imag()) * (T(static_cast<unsigned>(UINT8_C(1))) + (my_a_over_b * my_a_over_b));
      }
      else
      {
        const T my_b_over_a = my_z.imag() / my_z.real();

        my_result = (my_z.real() * my_z.real()) * (T(static_cast<unsigned>(UINT8_C(1))) + (my_b_over_a * my_b_over_a));
      }

      return my_result;
    }

    template<typename T, typename EnableType> complex<T, EnableType> conj(const complex<T, EnableType>& my_z)
    {
      return complex<T, EnableType>(-my_z.imag(), my_z.real());
    }

    template<typename T, typename EnableType> complex<T, EnableType> proj(const complex<T, EnableType>& my_z)
    {
      const T denominator_half((norm(my_z) + T(static_cast<unsigned>(UINT8_C(1)))) / static_cast<unsigned>(UINT8_C(2)));

      return complex<T, EnableType>(my_z.real() / denominator_half,
                        my_z.imag() / denominator_half);
    }

    template<typename T, typename EnableType> complex<T, EnableType> polar(const T& my_rho, const T& my_theta)
    {
      using std::cos;
      using std::sin;

      return complex<T, EnableType>(my_rho * cos(my_theta), my_rho * sin(my_theta));
    }


    // Elementary transcendental functions for extended_complex::complex<T, EnableType>.
    // See also ISO/IEC 14882:2011 Sect. 26.4.8.

    template<typename T, typename EnableType> complex<T, EnableType> acos(const complex<T, EnableType>& my_z)
    {
      using std::asin;

      return T(asin(T(static_cast<unsigned>(UINT8_C(1))))) - asin(my_z);
    }

    template<typename T, typename EnableType> complex<T, EnableType> asin(const complex<T, EnableType>& my_z)
    {
      return -conj(log(conj(my_z) + sqrt(T(static_cast<unsigned>(UINT8_C(1))) - (my_z * my_z))));
    }

    template<typename T, typename EnableType> complex<T, EnableType> atan(const complex<T, EnableType>& my_z)
    {
      const complex<T, EnableType> z_conj = conj(my_z);

      complex<T, EnableType> result = conj(log(T(1) - z_conj) - log(T(static_cast<unsigned>(UINT8_C(1))) + z_conj));

      result.real(result.real() / static_cast<unsigned>(UINT8_C(2)));
      result.imag(result.imag() / static_cast<unsigned>(UINT8_C(2)));

      return result;
    }

    template<typename T, typename EnableType> complex<T, EnableType> acosh(const complex<T, EnableType>& my_z)
    {
      const complex<T, EnableType> zp(my_z.real() + T(static_cast<unsigned>(UINT8_C(1))), my_z.imag());
      const complex<T, EnableType> zm(my_z.real() - T(static_cast<unsigned>(UINT8_C(1))), my_z.imag());

      return log(my_z + (zp * sqrt(zm / zp)));
    }

    template<typename T, typename EnableType> complex<T, EnableType> asinh(const complex<T, EnableType>& my_z)
    {
      return log(my_z + sqrt(T(static_cast<unsigned>(UINT8_C(1))) + (my_z * my_z)));
    }

    template<typename T, typename EnableType> complex<T, EnableType> atanh(const complex<T, EnableType>& my_z)
    {
      complex<T, EnableType> result = (log(T(static_cast<unsigned>(UINT8_C(1))) + my_z) - log(T(static_cast<unsigned>(UINT8_C(1))) - my_z));

      result.real(result.real() / static_cast<unsigned>(UINT8_C(2)));
      result.imag(result.imag() / static_cast<unsigned>(UINT8_C(2)));

      return result;
    }

    template<typename T, typename EnableType> complex<T, EnableType> cos(const complex<T, EnableType>& my_z)
    {
      using std::cos;
      using std::cosh;
      using std::sin;
      using std::sinh;

      return complex<T, EnableType>(   cos(my_z.real()) * cosh(my_z.imag()),
                                    - (sin(my_z.real()) * sinh(my_z.imag())));
    }

    template<typename T, typename EnableType> complex<T, EnableType> cosh(const complex<T, EnableType>& my_z)
    {
      using std::cos;
      using std::cosh;
      using std::sin;
      using std::sinh;

      return complex<T, EnableType>(cos(my_z.imag()) * cosh(my_z.real()),
                                    sin(my_z.imag()) * sinh(my_z.real()));
    }

    template<typename T, typename EnableType> complex<T, EnableType> exp(const complex<T, EnableType>& my_z)
    {
      using std::cos;
      using std::exp;
      using std::sin;

      return complex<T, EnableType>(cos(my_z.imag()), sin(my_z.imag())) * T(exp(my_z.real()));
    }

    template<typename T, typename EnableType> complex<T, EnableType> log(const complex<T, EnableType>& my_z)
    {
      using std::atan2;
      using std::log;

      const T my_real_part(log(norm(my_z)) / static_cast<unsigned>(UINT8_C(2)));
      const T my_imag_part(atan2(my_z.imag(), my_z.real()));

      return complex<T, EnableType>(my_real_part, my_imag_part);
    }

    template<typename T, typename EnableType> complex<T, EnableType> log10(const complex<T, EnableType>& my_z)
    {
      using std::log;

      return log(my_z) / T(log(T(static_cast<unsigned>(UINT8_C(10)))));
    }

    template<typename T, typename IntegralType, typename EnableType> typename std::enable_if<std::is_integral<IntegralType>::value, complex<T, EnableType>>::type
    pow(const complex<T, EnableType>& my_z, IntegralType my_pn)
    {
      if     (my_pn <  static_cast<int>(INT8_C(0))) { return  T(static_cast<unsigned>(UINT8_C(1))) / pow(my_z, -my_pn); }
      else if(my_pn == static_cast<int>(INT8_C(0))) { return  complex<T, EnableType>(T(static_cast<unsigned>(UINT8_C(1)))); }
      else if(my_pn == static_cast<int>(INT8_C(1))) { return  my_z; }
      else if(my_pn == static_cast<int>(INT8_C(2))) { return  my_z * my_z; }
      else if(my_pn == static_cast<int>(INT8_C(3))) { return (my_z * my_z) * my_z; }
      else if(my_pn == static_cast<int>(INT8_C(4))) { const complex<T, EnableType> my_z2(my_z * my_z); return (my_z2 * my_z2); }
      else
      {
        complex<T, EnableType> my_result = T(static_cast<unsigned>(UINT8_C(1)));

        complex<T, EnableType> y(my_z);

        auto p_local = static_cast<std::uint64_t>(my_pn);

        // Use the so-called ladder method for the power calculation.
        for(;;)
        {
          const auto lo_bit = static_cast<std::uint_fast8_t>(p_local & static_cast<unsigned>(UINT8_C(1)));

          const auto do_power_multiply = (lo_bit != static_cast<std::uint_fast8_t>(UINT8_C(0)));

          if(do_power_multiply)
          {
            my_result *= y;
          }

          p_local >>= static_cast<unsigned>(UINT8_C(1));

          if(p_local == static_cast<std::uint64_t>(UINT8_C(0)))
          {
            break;
          }

          y *= y;
        }

        return my_result;
      }
    }

    template<typename T, typename EnableType> complex<T, EnableType> pow(const complex<T, EnableType>& my_z, const T& my_a)
    {
      return exp(my_a * log(my_z));
    }

    template<typename T, typename EnableType> complex<T, EnableType> pow(const complex<T, EnableType>& my_z, const complex<T, EnableType>& my_a)
    {
      return exp(my_a * log(my_z));
    }

    template<typename T, typename EnableType> complex<T, EnableType> pow(const T& my_z, const complex<T, EnableType>& my_a)
    {
      using std::log;

      return exp(my_a * T(log(my_z)));
    }

    template<typename T, typename EnableType> complex<T, EnableType> sin(const complex<T, EnableType>& my_z)
    {
      using std::cos;
      using std::cosh;
      using std::sin;
      using std::sinh;

      return complex<T, EnableType>(sin(my_z.real()) * cosh(my_z.imag()),
                                    cos(my_z.real()) * sinh(my_z.imag()));
    }

    template<typename T, typename EnableType> complex<T, EnableType> sinh(const complex<T, EnableType>& my_z)
    {
      using std::cos;
      using std::cosh;
      using std::sin;
      using std::sinh;

      return complex<T, EnableType>(cos (my_z.imag()) * sinh(my_z.real()),
                                    cosh(my_z.real()) * sin (my_z.imag()));
    }

    template<typename T, typename EnableType> complex<T, EnableType> sqrt(const complex<T, EnableType>& my_z)
    {
      using std::fabs;
      using std::sqrt;

      // Use the following:
      // sqrt(z) = (s, zi / 2s)       for zr >= 0
      //           (|zi| / 2s, +-s)   for zr <  0
      // where s = sqrt{ [ |zr| + sqrt(zr^2 + zi^2) ] / 2 },
      // and the +- sign is the same as the sign of zi.

      const bool real_part_is_neg(my_z.real() < T(static_cast<unsigned>(UINT8_C(0))));
      const T    real_part_fabs  ((real_part_is_neg == false) ? my_z.real() : -my_z.real());
      const T    s_part          (sqrt((real_part_fabs + abs(my_z)) / static_cast<unsigned>(UINT8_C(2))));

      if(real_part_is_neg == false)
      {
        return complex<T, EnableType>(s_part,
                          my_z.imag() / (s_part * static_cast<unsigned>(UINT8_C(2))));
      }
      else
      {
        const bool imag_part_is_neg(my_z.imag() < T(static_cast<unsigned>(UINT8_C(0))));
        const T    imag_part_fabs  ((imag_part_is_neg == false) ? my_z.imag() : -my_z.imag());

        return complex<T, EnableType>( imag_part_fabs / (s_part * static_cast<unsigned>(UINT8_C(2))),
                         ((imag_part_is_neg == false) ? s_part : -s_part));
      }
    }

    template<typename T, typename EnableType> complex<T, EnableType> tan(const complex<T, EnableType>& my_z)
    {
      return sin(my_z) / cos(my_z);
    }

    template<typename T, typename EnableType> complex<T, EnableType> tanh(const complex<T, EnableType>& my_z)
    {
      return sinh(my_z) / cosh(my_z);
    }
  } // namespace extended_complex

  /*
  // 8-bit microcontroller @ 16MHz

  const extended_complex::complex<float> x(1.23F, 3.45F);
  const extended_complex::complex<float> y(0.77F, 0.22F);

  function     run time [micro-sec]    code size [byte]
   x * y               63                    880
  sqrt (x)            190                  1,600
  sin  (x)            590                  1,700
  log  (x)            400                  1,900
  exp  (x)            400                  1,600
  acosh(x)            830                  3,200
  */

#endif // EXTENDED_COMPLEX_2016_02_22
