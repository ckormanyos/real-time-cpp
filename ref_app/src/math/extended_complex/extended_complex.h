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

#ifndef EXTENDED_COMPLEX_2016_02_22_H
  #define EXTENDED_COMPLEX_2016_02_22_H

  #if defined(__clang__)
    #if defined __has_feature && __has_feature(thread_sanitizer)
    #define EXTENDED_COMPLEX_REDUCE_TEST_DEPTH
    #endif
  #elif defined(__GNUC__)
    #if defined(__SANITIZE_THREAD__) || defined(EXTENDED_COMPLEX_HAS_COVERAGE)
    #define EXTENDED_COMPLEX_REDUCE_TEST_DEPTH
    #endif
  #elif defined(_MSC_VER)
    #if defined(_DEBUG)
    #define EXTENDED_COMPLEX_REDUCE_TEST_DEPTH
    #endif
  #endif

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
    class complex<T, typename std::enable_if_t<std::is_floating_point<T>::value>>;

    // Non-member operations for extended_complex::complex<T, EnableType>.
    // Similar to ISO/IEC 14882:2011 Sect. 26.4.6.

    // Unary +/- operators.
    template<typename T, typename EnableType = void> EXTENDED_COMPLEX_CONSTEXPR auto operator+(const complex<T, EnableType>&) -> complex<T, EnableType>;
    template<typename T, typename EnableType = void> EXTENDED_COMPLEX_CONSTEXPR auto operator-(const complex<T, EnableType>&) -> complex<T, EnableType>;

    // Global add, sub, mul, div operators.
    template<typename T, typename EnableType = void> EXTENDED_COMPLEX_CONSTEXPR auto operator+(const complex<T, EnableType>&, const complex<T, EnableType>&) -> complex<T, EnableType>;
    template<typename T, typename EnableType = void> EXTENDED_COMPLEX_CONSTEXPR auto operator-(const complex<T, EnableType>&, const complex<T, EnableType>&) -> complex<T, EnableType>;
    template<typename T, typename EnableType = void> EXTENDED_COMPLEX_CONSTEXPR auto operator*(const complex<T, EnableType>&, const complex<T, EnableType>&) -> complex<T, EnableType>;
    template<typename T, typename EnableType = void> EXTENDED_COMPLEX_CONSTEXPR auto operator/(const complex<T, EnableType>&, const complex<T, EnableType>&) -> complex<T, EnableType>;

    template<typename T, typename EnableType = void> EXTENDED_COMPLEX_CONSTEXPR auto operator+(const complex<T, EnableType>&, const T&) -> complex<T, EnableType>;
    template<typename T, typename EnableType = void> EXTENDED_COMPLEX_CONSTEXPR auto operator-(const complex<T, EnableType>&, const T&) -> complex<T, EnableType>;
    template<typename T, typename EnableType = void> EXTENDED_COMPLEX_CONSTEXPR auto operator*(const complex<T, EnableType>&, const T&) -> complex<T, EnableType>;
    template<typename T, typename EnableType = void> EXTENDED_COMPLEX_CONSTEXPR auto operator/(const complex<T, EnableType>&, const T&) -> complex<T, EnableType>;

    template<typename T, typename EnableType = void> EXTENDED_COMPLEX_CONSTEXPR auto operator+(const T&, const complex<T, EnableType>&) -> complex<T, EnableType>;
    template<typename T, typename EnableType = void> EXTENDED_COMPLEX_CONSTEXPR auto operator-(const T&, const complex<T, EnableType>&) -> complex<T, EnableType>;
    template<typename T, typename EnableType = void> EXTENDED_COMPLEX_CONSTEXPR auto operator*(const T&, const complex<T, EnableType>&) -> complex<T, EnableType>;
    template<typename T, typename EnableType = void> EXTENDED_COMPLEX_CONSTEXPR auto operator/(const T&, const complex<T, EnableType>&) -> complex<T, EnableType>;

    // Equality and inequality operators.
    template<typename T, typename EnableType = void> EXTENDED_COMPLEX_CONSTEXPR auto operator==(const complex<T, EnableType>&, const complex<T, EnableType>&) -> bool;
    template<typename T, typename EnableType = void> EXTENDED_COMPLEX_CONSTEXPR auto operator==(const complex<T, EnableType>&, const T&) -> bool;
    template<typename T, typename EnableType = void> EXTENDED_COMPLEX_CONSTEXPR auto operator==(const T&, const complex<T, EnableType>&) -> bool;

    template<typename T, typename EnableType = void> EXTENDED_COMPLEX_CONSTEXPR auto operator!=(const complex<T, EnableType>&, const complex<T, EnableType>&) -> bool;
    template<typename T, typename EnableType = void> EXTENDED_COMPLEX_CONSTEXPR auto operator!=(const complex<T, EnableType>&, const T&) -> bool;
    template<typename T, typename EnableType = void> EXTENDED_COMPLEX_CONSTEXPR auto operator!=(const T&, const complex<T, EnableType>&) -> bool;

    #if !defined(EXTENDED_COMPLEX_DISABLE_IOSTREAM)

    // I/O stream operators.
    template<typename T, typename char_type, typename traits_type, typename EnableType = void>
    auto operator>>(std::basic_istream<char_type, traits_type>&, complex<T, EnableType>&) -> std::basic_istream<char_type, traits_type>&;

    template<typename T, typename char_type, typename traits_type, typename EnableType = void>
    auto operator<<(std::basic_ostream<char_type, traits_type>&, const complex<T, EnableType>&) -> std::basic_ostream<char_type, traits_type>&;

    #endif // !EXTENDED_COMPLEX_DISABLE_IOSTREAM

    // Value operations for extended_complex::complex<T, EnableType>.
    // Similar to ISO/IEC 14882:2011 Sect. 26.4.7.

    template<typename T, typename EnableType = void> EXTENDED_COMPLEX_CONSTEXPR auto real (const complex<T, EnableType>&) -> T;
    template<typename T, typename EnableType = void> EXTENDED_COMPLEX_CONSTEXPR auto imag (const complex<T, EnableType>&) -> T;

    template<typename T, typename EnableType = void> EXTENDED_COMPLEX_CONSTEXPR auto abs  (const complex<T, EnableType>&) -> T;
    template<typename T, typename EnableType = void> EXTENDED_COMPLEX_CONSTEXPR auto arg  (const complex<T, EnableType>&) -> T;
    template<typename T, typename EnableType = void> EXTENDED_COMPLEX_CONSTEXPR auto norm (const complex<T, EnableType>&) -> T;


    template<typename T, typename EnableType = void> EXTENDED_COMPLEX_CONSTEXPR auto conj (const complex<T, EnableType>&) -> complex<T, EnableType>;
    template<typename T, typename EnableType = void> EXTENDED_COMPLEX_CONSTEXPR auto proj (const complex<T, EnableType>&) -> complex<T, EnableType>;
    template<typename T, typename EnableType = void> EXTENDED_COMPLEX_CONSTEXPR auto polar(const T&, const T& = T(static_cast<unsigned>(UINT8_C(0)))) -> complex<T, EnableType>;

    // Elementary transcendental functions for extended_complex::complex<T, EnableType>.
    // Similar to ISO/IEC 14882:2011 Sect. 26.4.8.

    template<typename T, typename EnableType = void> EXTENDED_COMPLEX_CONSTEXPR auto acos (const complex<T, EnableType>&) -> complex<T, EnableType>;
    template<typename T, typename EnableType = void> EXTENDED_COMPLEX_CONSTEXPR auto asin (const complex<T, EnableType>&) -> complex<T, EnableType>;
    template<typename T, typename EnableType = void> EXTENDED_COMPLEX_CONSTEXPR auto atan (const complex<T, EnableType>&) -> complex<T, EnableType>;
    template<typename T, typename EnableType = void> EXTENDED_COMPLEX_CONSTEXPR auto asinh(const complex<T, EnableType>&) -> complex<T, EnableType>;
    template<typename T, typename EnableType = void> EXTENDED_COMPLEX_CONSTEXPR auto acosh(const complex<T, EnableType>&) -> complex<T, EnableType>;
    template<typename T, typename EnableType = void> EXTENDED_COMPLEX_CONSTEXPR auto atanh(const complex<T, EnableType>&) -> complex<T, EnableType>;

    template<typename T, typename EnableType = void> EXTENDED_COMPLEX_CONSTEXPR auto cos  (const complex<T, EnableType>&) -> complex<T, EnableType>;
    template<typename T, typename EnableType = void> EXTENDED_COMPLEX_CONSTEXPR auto cosh (const complex<T, EnableType>&) -> complex<T, EnableType>;
    template<typename T, typename EnableType = void> EXTENDED_COMPLEX_CONSTEXPR auto exp  (const complex<T, EnableType>&) -> complex<T, EnableType>;
    template<typename T, typename EnableType = void> EXTENDED_COMPLEX_CONSTEXPR auto log  (const complex<T, EnableType>&) -> complex<T, EnableType>;
    template<typename T, typename EnableType = void> EXTENDED_COMPLEX_CONSTEXPR auto log10(const complex<T, EnableType>&) -> complex<T, EnableType>;

    template<typename T,
             typename IntegralType,
             typename EnableType = void>             EXTENDED_COMPLEX_CONSTEXPR auto pow  (const complex<T, EnableType>&, IntegralType) -> typename std::enable_if_t<std::is_integral<IntegralType>::value, complex<T, EnableType>>;
    template<typename T, typename EnableType = void> EXTENDED_COMPLEX_CONSTEXPR auto pow  (const complex<T, EnableType>&, const T&) -> complex<T, EnableType>;
    template<typename T, typename EnableType = void> EXTENDED_COMPLEX_CONSTEXPR auto pow  (const complex<T, EnableType>&, const complex<T, EnableType>&) -> complex<T, EnableType>;
    template<typename T, typename EnableType = void> EXTENDED_COMPLEX_CONSTEXPR auto pow  (const T&, const complex<T, EnableType>&) -> complex<T, EnableType>;

    template<typename T, typename EnableType = void> EXTENDED_COMPLEX_CONSTEXPR auto sin  (const complex<T, EnableType>&) -> complex<T, EnableType>;
    template<typename T, typename EnableType = void> EXTENDED_COMPLEX_CONSTEXPR auto sinh (const complex<T, EnableType>&) -> complex<T, EnableType>;
    template<typename T, typename EnableType = void> EXTENDED_COMPLEX_CONSTEXPR auto sqrt (const complex<T, EnableType>&) -> complex<T, EnableType>;
    template<typename T, typename EnableType = void> EXTENDED_COMPLEX_CONSTEXPR auto tan  (const complex<T, EnableType>&) -> complex<T, EnableType>;
    template<typename T, typename EnableType = void> EXTENDED_COMPLEX_CONSTEXPR auto tanh (const complex<T, EnableType>&) -> complex<T, EnableType>;

    // Class template extended_complex::complex<T, EnableType>.
    // See also ISO/IEC 14882:2011 Sect. 26.4.2.

    template<typename T, typename EnableType>
    class complex
    {
    public:
      using value_type = T;

      EXTENDED_COMPLEX_CONSTEXPR complex(const value_type& my_x = value_type(),
                                         const value_type& my_y = value_type()) : my_re(my_x),
                                                                                  my_im(my_y) { }

      EXTENDED_COMPLEX_CONSTEXPR complex(const complex& other) : my_re(other.my_re),
                                                                 my_im(other.my_im) { }

      EXTENDED_COMPLEX_CONSTEXPR complex(complex&& other) noexcept
        : my_re(std::move(static_cast<value_type&&>(other.my_re))),
          my_im(std::move(static_cast<value_type&&>(other.my_im))) { }

      template<typename X>
      EXTENDED_COMPLEX_CONSTEXPR complex(const complex<X>& my_z)
        : my_re(static_cast<value_type>(my_z.my_re)),
          my_im(static_cast<value_type>(my_z.my_im)) { }

      EXTENDED_COMPLEX_CONSTEXPR auto operator=(const complex& other) -> complex&
      {
        if(this != &other)
        {
          my_re = other.my_re;
          my_im = other.my_im;
        }

        return *this;
      }

      EXTENDED_COMPLEX_CONSTEXPR auto operator=(complex&& other) noexcept -> complex&
      {
        my_re = std::move(static_cast<value_type&&>(other.my_re));
        my_im = std::move(static_cast<value_type&&>(other.my_im));

        return *this;
      }

      template<typename X>
      EXTENDED_COMPLEX_CONSTEXPR auto operator=(const complex<X>& other) -> complex&
      {
        if(this != &other)
        {
          my_re = static_cast<value_type>(other.my_re);
          my_im = static_cast<value_type>(other.my_im);
        }

        return *this;
      }

      EXTENDED_COMPLEX_CONSTEXPR auto operator=(const value_type& other_x) -> complex&
      {
        my_re = other_x;
        imag(std::move(static_cast<value_type>(static_cast<unsigned>(UINT8_C(0)))));

        return *this;
      }

      EXTENDED_COMPLEX_CONSTEXPR auto operator=(value_type&& other_x) noexcept -> complex&
      {
        my_re = std::move(other_x);
        imag(std::move(static_cast<value_type>(static_cast<unsigned>(UINT8_C(0)))));

        return *this;
      }

      EXTENDED_COMPLEX_CONSTEXPR auto real() const -> value_type { return my_re; }
      EXTENDED_COMPLEX_CONSTEXPR auto imag() const -> value_type { return my_im; } // LCOV_EXCL_LINE (Bogus missed line from lcov)

      EXTENDED_COMPLEX_CONSTEXPR auto real(const value_type& my_x) -> void { my_re = my_x; }
      EXTENDED_COMPLEX_CONSTEXPR auto imag(const value_type& my_y) -> void { my_im = my_y; }

      EXTENDED_COMPLEX_CONSTEXPR auto real(value_type&& my_x) noexcept -> void { my_re = std::move(my_x); }
      EXTENDED_COMPLEX_CONSTEXPR auto imag(value_type&& my_y) noexcept -> void { my_im = std::move(my_y); }

      EXTENDED_COMPLEX_CONSTEXPR auto operator+=(const value_type& my_x) -> complex&
      {
        my_re += my_x;

        return *this;
      }

      EXTENDED_COMPLEX_CONSTEXPR auto operator-=(const value_type& my_x) -> complex&
      {
        my_re -= my_x;

        return *this;
      }

      EXTENDED_COMPLEX_CONSTEXPR auto operator*=(const value_type& my_x) -> complex&
      {
        my_re *= my_x;
        my_im *= my_x;

        return *this;
      }

      EXTENDED_COMPLEX_CONSTEXPR auto operator/=(const value_type& my_x) -> complex&
      {
        my_re /= my_x;
        my_im /= my_x;

        return *this;
      }

      template<typename X>
      EXTENDED_COMPLEX_CONSTEXPR auto operator+=(const complex<X>& my_z) -> complex&
      {
        my_re += static_cast<value_type>(my_z.my_re);
        my_im += static_cast<value_type>(my_z.my_im);

        return *this;
      }

      template<typename X>
      EXTENDED_COMPLEX_CONSTEXPR auto operator-=(const complex<X>& my_z) -> complex&
      {
        if(this == &my_z)
        {
          real(std::move(static_cast<value_type>(static_cast<unsigned>(UINT8_C(0)))));
          imag(std::move(static_cast<value_type>(static_cast<unsigned>(UINT8_C(0)))));
        }
        else
        {
          my_re -= static_cast<value_type>(my_z.my_re);
          my_im -= static_cast<value_type>(my_z.my_im);
        }

        return *this;
      }

      template<typename X>
      EXTENDED_COMPLEX_CONSTEXPR auto operator*=(const complex<X>& my_z) -> complex&
      {
        const value_type tmp_re { my_re };

        if(this == &my_z)
        {
          real((tmp_re * tmp_re) - (my_im * my_im));
          imag((tmp_re * my_im) * 2U);
        }
        else
        {
          real((tmp_re * my_z.my_re) - (my_im * my_z.my_im));
          imag((tmp_re * my_z.my_im) + (my_im * my_z.my_re));
        }

        return *this;
      }

      template<typename X>
      EXTENDED_COMPLEX_CONSTEXPR auto operator/=(const complex<X>& my_z) -> complex&
      {
        if(this == &my_z)
        {
          real(std::move(static_cast<value_type>(static_cast<unsigned>(UINT8_C(1)))));
          imag(std::move(static_cast<value_type>(static_cast<unsigned>(UINT8_C(0)))));
        }
        else
        {
          if(fabs(my_z.my_re) < fabs(my_z.my_im))
          {
            const value_type my_c_over_d { my_z.my_re / my_z.my_im };

            const value_type my_denominator { (my_z.my_re * my_c_over_d) + my_z.my_im };

            const value_type my_tmp_re { my_re };

           real(((my_tmp_re * my_c_over_d) + my_im)     / my_denominator);
           imag(((my_im     * my_c_over_d) - my_tmp_re) / my_denominator);
          }
          else
          {
            const value_type my_d_over_c { my_z.my_im / my_z.my_re };

            const value_type my_denominator { (my_z.my_im * my_d_over_c) + my_z.my_re };

            const value_type my_tmp_re { my_re };

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

    // Specialization of class template extended_complex::complex<>
    // for built-in floating-point types.
    // See also ISO/IEC 14882:2011 Sect. 26.4.3.

    template<typename T>
    class complex<T, typename std::enable_if_t<std::is_floating_point<T>::value>>
    {
    public:
      using value_type = T;

      static_assert(std::is_floating_point<value_type>::value, "Error: The template parameter must be a built-in floating-point type");

      EXTENDED_COMPLEX_CONSTEXPR complex(value_type my_x = value_type(),
                                         value_type my_y = value_type()) : my_re(my_x),
                                                                           my_im(my_y) { }

      EXTENDED_COMPLEX_CONSTEXPR complex(const complex& other) : my_re(other.my_re),
                                                                 my_im(other.my_im) { }

      EXTENDED_COMPLEX_CONSTEXPR complex(complex&& other) noexcept : my_re(std::move(static_cast<value_type&&>(other.my_re))),
                                                                     my_im(std::move(static_cast<value_type&&>(other.my_im))) { }

      template<typename OtherFloatingPointType,
               typename OtherEnableType = typename std::enable_if_t<std::is_floating_point<OtherFloatingPointType>::value && (sizeof(OtherFloatingPointType) != sizeof(value_type)), void>>
      explicit EXTENDED_COMPLEX_CONSTEXPR complex(const complex<OtherFloatingPointType>& other)
        : my_re(static_cast<value_type>(other.my_re)),
          my_im(static_cast<value_type>(other.my_im)) { }

      EXTENDED_COMPLEX_CONSTEXPR auto operator=(const complex& other) -> complex&
      {
        if(this != &other)
        {
          my_re = other.my_re;
          my_im = other.my_im;
        }

        return *this;
      }

      EXTENDED_COMPLEX_CONSTEXPR auto operator=(complex&& other) noexcept -> complex&
      {
        my_re = std::move(static_cast<value_type&&>(other.my_re));
        my_im = std::move(static_cast<value_type&&>(other.my_im));

        return *this;
      }

      EXTENDED_COMPLEX_CONSTEXPR auto operator=(const value_type& other_x) -> complex&
      {
        my_re = other_x;
        my_im = static_cast<value_type>(0.0L);

        return *this;
      }

      template<typename OtherFloatingPointType,
               typename OtherFloatingPointEnableType = typename std::enable_if_t<std::is_floating_point<OtherFloatingPointType>::value && (sizeof(OtherFloatingPointType) != sizeof(value_type)), void>>
      EXTENDED_COMPLEX_CONSTEXPR auto operator=(const complex<OtherFloatingPointType>& other) -> complex&
      {
        if(this != &other)
        {
          my_re = static_cast<value_type>(other.my_re);
          my_im = static_cast<value_type>(other.my_im);
        }

        return *this;
      }

      EXTENDED_COMPLEX_CONSTEXPR auto real() const -> value_type { return my_re; }
      EXTENDED_COMPLEX_CONSTEXPR auto imag() const -> value_type { return my_im; }

      EXTENDED_COMPLEX_CONSTEXPR auto real(const value_type& my_x) -> void { my_re = my_x; }
      EXTENDED_COMPLEX_CONSTEXPR auto imag(const value_type& my_y) -> void { my_im = my_y; }

      EXTENDED_COMPLEX_CONSTEXPR auto operator+=(const value_type& my_x) -> complex&
      {
        my_re += my_x;

        return *this;
      }

      EXTENDED_COMPLEX_CONSTEXPR auto operator-=(const value_type& my_x) -> complex&
      {
        my_re -= my_x;

        return *this;
      }

      EXTENDED_COMPLEX_CONSTEXPR auto operator*=(const value_type& my_x) -> complex&
      {
        my_re *= my_x;
        my_im *= my_x;

        return *this;
      }

      EXTENDED_COMPLEX_CONSTEXPR auto operator/=(const value_type& my_x) -> complex&
      {
        my_re /= my_x;
        my_im /= my_x;

        return *this;
      }

      template<typename X>
      EXTENDED_COMPLEX_CONSTEXPR auto operator+=(const complex<X>& my_z) -> complex&
      {
        my_re += static_cast<value_type>(my_z.my_re);
        my_im += static_cast<value_type>(my_z.my_im);

        return *this;
      }

      template<typename X>
      EXTENDED_COMPLEX_CONSTEXPR auto operator-=(const complex<X>& my_z) -> complex&
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
      EXTENDED_COMPLEX_CONSTEXPR auto operator*=(const complex<X>& my_z) -> complex&
      {
        const value_type tmp_re { my_re };

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
      EXTENDED_COMPLEX_CONSTEXPR auto operator/=(const complex<X>& my_z) -> complex&
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
            const value_type my_c_over_d { my_z.real() / my_z.imag() };

            const value_type my_denominator { (my_z.real() * my_c_over_d) + my_z.imag() };

            const value_type my_tmp_re { my_re };

            real(((my_tmp_re * my_c_over_d) + my_im)     / my_denominator);
            imag(((my_im     * my_c_over_d) - my_tmp_re) / my_denominator);
          }
          else
          {
            const value_type my_d_over_c { my_z.imag() / my_z.real() };

            const value_type my_denominator { (my_z.imag() * my_d_over_c) + my_z.real() };

            const value_type my_tmp_re { my_re };

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
    template<typename T, typename EnableType> EXTENDED_COMPLEX_CONSTEXPR auto operator+(const complex<T, EnableType>& my_u) -> complex<T, EnableType> { return my_u; }
    template<typename T, typename EnableType> EXTENDED_COMPLEX_CONSTEXPR auto operator-(const complex<T, EnableType>& my_u) -> complex<T, EnableType> { return complex<T, EnableType>(-my_u.real(), -my_u.imag()); }

    // Global add, sub, mul, div operators.
    template<typename T, typename EnableType> EXTENDED_COMPLEX_CONSTEXPR auto operator+(const complex<T, EnableType>& my_u, const complex<T, EnableType>& my_v) -> complex<T, EnableType> { return complex<T, EnableType>(my_u.real() + my_v.real(), my_u.imag() + my_v.imag()); }
    template<typename T, typename EnableType> EXTENDED_COMPLEX_CONSTEXPR auto operator-(const complex<T, EnableType>& my_u, const complex<T, EnableType>& my_v) -> complex<T, EnableType> { return complex<T, EnableType>(my_u.real() - my_v.real(), my_u.imag() - my_v.imag()); }

    template<typename T, typename EnableType> EXTENDED_COMPLEX_CONSTEXPR auto operator*(const complex<T, EnableType>& my_u, const complex<T, EnableType>& my_v) -> complex<T, EnableType>
    {
      return complex<T, EnableType>((my_u.real() * my_v.real()) - (my_u.imag() * my_v.imag()),
                                    (my_u.real() * my_v.imag()) + (my_u.imag() * my_v.real()));
    }

    template<typename T, typename EnableType> EXTENDED_COMPLEX_CONSTEXPR auto operator/(const complex<T, EnableType>& my_u, const complex<T, EnableType>& my_v) -> complex<T, EnableType>
    {
      using std::fabs;

      if(fabs(my_v.real()) < fabs(my_v.imag()))
      {
        const T my_c_over_d { my_v.real() / my_v.imag() };

        const T my_denominator { (my_v.real() * my_c_over_d) + my_v.imag() };

        return
        {
          ((my_u.real() * my_c_over_d) + my_u.imag()) / my_denominator,
          ((my_u.imag() * my_c_over_d) - my_u.real()) / my_denominator
        };
      }
      else
      {
        const T my_d_over_c { my_v.imag() / my_v.real() };

        const T my_denominator { (my_v.imag() * my_d_over_c) + my_v.real() };

        return
        {
          (( my_u.imag() * my_d_over_c) + my_u.real()) / my_denominator,
          ((-my_u.real() * my_d_over_c) + my_u.imag()) / my_denominator
        };
      }
    }

    template<typename T, typename EnableType> EXTENDED_COMPLEX_CONSTEXPR auto operator+(const complex<T, EnableType>& my_u, const T& my_v) -> complex<T, EnableType> { return complex<T, EnableType>(my_u.real() + my_v, my_u.imag()); }
    template<typename T, typename EnableType> EXTENDED_COMPLEX_CONSTEXPR auto operator-(const complex<T, EnableType>& my_u, const T& my_v) -> complex<T, EnableType> { return complex<T, EnableType>(my_u.real() - my_v, my_u.imag()); }
    template<typename T, typename EnableType> EXTENDED_COMPLEX_CONSTEXPR auto operator*(const complex<T, EnableType>& my_u, const T& my_v) -> complex<T, EnableType> { return complex<T, EnableType>(my_u.real() * my_v, my_u.imag() * my_v); }
    template<typename T, typename EnableType> EXTENDED_COMPLEX_CONSTEXPR auto operator/(const complex<T, EnableType>& my_u, const T& my_v) -> complex<T, EnableType> { return complex<T, EnableType>(my_u.real() / my_v, my_u.imag() / my_v); }

    template<typename T, typename EnableType> EXTENDED_COMPLEX_CONSTEXPR auto operator+(const T& my_u, const complex<T, EnableType>& my_v) -> complex<T, EnableType> { return complex<T, EnableType>(my_u + my_v.real(), my_v.imag()); }
    template<typename T, typename EnableType> EXTENDED_COMPLEX_CONSTEXPR auto operator-(const T& my_u, const complex<T, EnableType>& my_v) -> complex<T, EnableType> { return complex<T, EnableType>(my_u - my_v.real(), -my_v.imag()); }
    template<typename T, typename EnableType> EXTENDED_COMPLEX_CONSTEXPR auto operator*(const T& my_u, const complex<T, EnableType>& my_v) -> complex<T, EnableType> { return complex<T, EnableType>(my_u * my_v.real(), my_u * my_v.imag()); }

    template<typename T, typename EnableType> EXTENDED_COMPLEX_CONSTEXPR auto operator/(const T& my_u, const complex<T, EnableType>& my_v) -> complex<T, EnableType>
    {
      using std::fabs;

      if(fabs(my_v.real()) < fabs(my_v.imag()))
      {
        const T my_c_over_d { my_v.real() / my_v.imag() };

        const T my_denominator { (my_v.real() * my_c_over_d) + my_v.imag() };

        return
        {
          ( my_u * my_c_over_d) / my_denominator,
           -my_u                / my_denominator
        };
      }
      else
      {
        const T my_d_over_c { my_v.imag() / my_v.real() };

        const T my_denominator { (my_v.imag() * my_d_over_c) + my_v.real() };

        return
        {
            my_u                / my_denominator,
          (-my_u * my_d_over_c) / my_denominator
        };
      }
    }

    // Equality and inequality operators.
    template<typename T, typename EnableType> EXTENDED_COMPLEX_CONSTEXPR auto operator==(const complex<T, EnableType>& my_u, const complex<T, EnableType>& my_v) -> bool { return ((my_u.real() == my_v.real()) && (my_u.imag() == my_v.imag())); }
    template<typename T, typename EnableType> EXTENDED_COMPLEX_CONSTEXPR auto operator==(const complex<T, EnableType>& my_u, const T&                      my_v) -> bool { return ((my_u.real() == my_v)        && (my_u.imag() == T(0))); }
    template<typename T, typename EnableType> EXTENDED_COMPLEX_CONSTEXPR auto operator==(const T&                      my_u, const complex<T, EnableType>& my_v) -> bool { return ((my_u == my_v.real())        && (my_v.imag() == T(0))); }

    template<typename T, typename EnableType> EXTENDED_COMPLEX_CONSTEXPR auto operator!=(const complex<T, EnableType>& my_u, const complex<T, EnableType>& my_v) -> bool { return ((my_u.real() != my_v.real()) || (my_u.imag() != my_v.imag())); }
    template<typename T, typename EnableType> EXTENDED_COMPLEX_CONSTEXPR auto operator!=(const complex<T, EnableType>& my_u, const T&                      my_v) -> bool { return ((my_u.real() != my_v)        || (my_u.imag() != T(0))); }
    template<typename T, typename EnableType> EXTENDED_COMPLEX_CONSTEXPR auto operator!=(const T&                      my_u, const complex<T, EnableType>& my_v) -> bool { return ((my_u != my_v.real())        || (my_v.imag() != T(0))); }

    #if !defined(EXTENDED_COMPLEX_DISABLE_IOSTREAM)

    // I/O stream operators.
    template<typename T, typename char_type, typename traits_type, typename EnableType>
    auto operator>>(std::basic_istream<char_type, traits_type>& my_istream, complex<T, EnableType>& my_z) -> std::basic_istream<char_type, traits_type>&
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
        // See also: https://godbolt.org/z/M1d48xjnG

        std::regex(  std::string("\\({1}")                             // One open parentheses.
                   + std::string("([\\+\\-]{0,1}[0-9]*\\.*[0-9]*)")    // Possible +-, decimal point and digits 0-9.
                   + std::string("([eE]{0,1}[\\+\\-]{0,1}[0-9]*)")     // Possible exponent field.
                   + std::string("\\){1}")),                           // One close parentheses.

        // A regular expression for an (extended) complex number of the form u.
        // See also: https://godbolt.org/z/3vvrn8jdv

        std::regex(  std::string("([\\+\\-]{0,1}[0-9]*\\.*[0-9]*)")    // Possible +-, decimal point and digits 0-9.
                   + std::string("([eE]{0,1}[\\+\\-]{0,1}[0-9]*)"))    // Possible exponent field.
      }};

      T my_real_input { static_cast<unsigned>(UINT8_C(0)) };
      T my_imag_input { static_cast<unsigned>(UINT8_C(0)) };

      bool my_input_has_error { false };

      std::string my_input_str { };

      my_istream >> my_input_str;

      std::match_results<std::string::const_iterator> my_mr { };

      const auto my_it_regex_match =
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

        const bool my_str1_has_error { (my_str1.length() != static_cast<std::size_t>(UINT8_C(0))) && (my_str1.find_first_of(my_decimal_digits) == std::string::npos) };
        const bool my_str2_has_error { (my_str2.length() != static_cast<std::size_t>(UINT8_C(0))) && (my_str2.find_first_of(my_decimal_digits) == std::string::npos) };
        const bool my_str3_has_error { (my_str3.length() != static_cast<std::size_t>(UINT8_C(0))) && (my_str3.find_first_of(my_decimal_digits) == std::string::npos) };
        const bool my_str4_has_error { (my_str4.length() != static_cast<std::size_t>(UINT8_C(0))) && (my_str4.find_first_of(my_decimal_digits) == std::string::npos) };

        if(my_str1_has_error || my_str2_has_error || my_str3_has_error || my_str4_has_error)
        {
          my_input_has_error = true;
        }
        else
        {
          // Extract the real part of the complex number.
          {
            std::stringstream strm { };

            strm << my_mr[static_cast<std::size_t>(UINT8_C(1))] << my_mr[static_cast<std::size_t>(UINT8_C(2))];
            strm >> my_real_input;
          }

          // Extract the imaginary part of the complex number.
          {
            std::stringstream strm { };

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
          std::stringstream strm { };

          strm << my_mr[static_cast<std::size_t>(UINT8_C(1))] << my_mr[static_cast<std::size_t>(UINT8_C(2))];
          strm >> my_real_input;

          my_imag_input = T(static_cast<unsigned>(UINT8_C(0)));
        }
      }

      if(my_input_has_error)
      {
        // Error case: Restore the characters in the input stream
        // and set the fail bit in the input stream.
        // See also: https://godbolt.org/z/Ye45nEfWf

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
    auto operator<<(std::basic_ostream<char_type, traits_type>& my_ostream, const complex<T, EnableType>& my_z) -> std::basic_ostream<char_type, traits_type>&
    {
      std::basic_ostringstream<char_type, traits_type> my_tmp_ostream { };

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

    template<typename T, typename EnableType> EXTENDED_COMPLEX_CONSTEXPR auto real(const complex<T, EnableType>& my_z) -> T { return my_z.real(); }
    template<typename T, typename EnableType> EXTENDED_COMPLEX_CONSTEXPR auto imag(const complex<T, EnableType>& my_z) -> T { return my_z.imag(); }

    template<typename T, typename EnableType> EXTENDED_COMPLEX_CONSTEXPR auto abs (const complex<T, EnableType>& my_z) -> T { using std::sqrt;  return sqrt(norm(my_z)); }
    template<typename T, typename EnableType> EXTENDED_COMPLEX_CONSTEXPR auto arg (const complex<T, EnableType>& my_z) -> T { using std::atan2; return atan2(my_z.imag(), my_z.real()); }

    template<typename T, typename EnableType> EXTENDED_COMPLEX_CONSTEXPR auto norm(const complex<T, EnableType>& my_z) -> T
    {
      using std::fabs;

      if(fabs(my_z.real()) < fabs(my_z.imag()))
      {
        const T my_a_over_b { my_z.real() / my_z.imag() };

        return (my_z.imag() * my_z.imag()) * (T(static_cast<unsigned>(UINT8_C(1))) + (my_a_over_b * my_a_over_b));
      }
      else
      {
        const T my_b_over_a { my_z.imag() / my_z.real() };

        return (my_z.real() * my_z.real()) * (T(static_cast<unsigned>(UINT8_C(1))) + (my_b_over_a * my_b_over_a));
      }
    }

    template<typename T, typename EnableType> EXTENDED_COMPLEX_CONSTEXPR auto conj(const complex<T, EnableType>& my_z) -> complex<T, EnableType>
    {
      return { -my_z.imag(), my_z.real() };
    }

    template<typename T, typename EnableType> EXTENDED_COMPLEX_CONSTEXPR auto proj(const complex<T, EnableType>& my_z) -> complex<T, EnableType>
    {
      const T denominator_half { (norm(my_z) + T(static_cast<unsigned>(UINT8_C(1)))) / static_cast<unsigned>(UINT8_C(2)) };

      return
      {
        my_z.real() / denominator_half,
        my_z.imag() / denominator_half
      };
    }

    template<typename T, typename EnableType> EXTENDED_COMPLEX_CONSTEXPR auto polar(const T& my_rho, const T& my_theta) -> complex<T, EnableType>
    {
      using std::cos;
      using std::sin;

      return
      {
        my_rho * cos(my_theta),
        my_rho * sin(my_theta)
      };
    }

    // Elementary transcendental functions for extended_complex::complex<T, EnableType>.
    // See also ISO/IEC 14882:2011 Sect. 26.4.8.

    template<typename T, typename EnableType> EXTENDED_COMPLEX_CONSTEXPR auto acos(const complex<T, EnableType>& my_z) -> complex<T, EnableType>
    {
      using std::asin;

      return asin(T(static_cast<unsigned>(UINT8_C(1)))) - asin(my_z);
    }

    template<typename T, typename EnableType> EXTENDED_COMPLEX_CONSTEXPR auto asin(const complex<T, EnableType>& my_z) -> complex<T, EnableType>
    {
      return -conj(log(conj(my_z) + sqrt(T(static_cast<unsigned>(UINT8_C(1))) - (my_z * my_z))));
    }

    template<typename T, typename EnableType> EXTENDED_COMPLEX_CONSTEXPR auto atan(const complex<T, EnableType>& my_z) -> complex<T, EnableType>
    {
      const complex<T, EnableType> z_conj { conj(my_z) };

      const complex<T, EnableType> result { conj(log(T(1) - z_conj) - log(T(static_cast<unsigned>(UINT8_C(1))) + z_conj)) };

      return
      {
        result.real() / static_cast<unsigned>(UINT8_C(2)),
        result.imag() / static_cast<unsigned>(UINT8_C(2))
      };
    }

    template<typename T, typename EnableType> EXTENDED_COMPLEX_CONSTEXPR auto acosh(const complex<T, EnableType>& my_z) -> complex<T, EnableType>
    {
      const complex<T, EnableType> zp { my_z.real() + T(static_cast<unsigned>(UINT8_C(1))), my_z.imag() };
      const complex<T, EnableType> zm { my_z.real() - T(static_cast<unsigned>(UINT8_C(1))), my_z.imag() };

      return log(my_z + (zp * sqrt(zm / zp)));
    }

    template<typename T, typename EnableType> EXTENDED_COMPLEX_CONSTEXPR auto asinh(const complex<T, EnableType>& my_z) -> complex<T, EnableType>
    {
      return log(my_z + sqrt(T(static_cast<unsigned>(UINT8_C(1))) + (my_z * my_z)));
    }

    template<typename T, typename EnableType> EXTENDED_COMPLEX_CONSTEXPR auto atanh(const complex<T, EnableType>& my_z) -> complex<T, EnableType>
    {
      const complex<T, EnableType> result { log(T(static_cast<unsigned>(UINT8_C(1))) + my_z) - log(T(static_cast<unsigned>(UINT8_C(1))) - my_z) };

      return
      {
        result.real() / static_cast<unsigned>(UINT8_C(2)),
        result.imag() / static_cast<unsigned>(UINT8_C(2))
      };
    }

    template<typename T, typename EnableType> EXTENDED_COMPLEX_CONSTEXPR auto cos(const complex<T, EnableType>& my_z) -> complex<T, EnableType>
    {
      using std::cos;
      using std::exp;
      using std::sin;

      const T exp_imag     { exp(my_z.imag()) };
      const T exp_imag_inv { T(static_cast<unsigned>(UINT8_C(1))) / exp_imag };

      const T cosh_imag { (exp_imag + exp_imag_inv) / static_cast<unsigned>(UINT8_C(2)) };
      const T sinh_imag { (exp_imag - exp_imag_inv) / static_cast<unsigned>(UINT8_C(2)) };

      return
      {
          cos(my_z.real()) * cosh_imag,
        -(sin(my_z.real()) * sinh_imag)
      };
    }

    template<typename T, typename EnableType> EXTENDED_COMPLEX_CONSTEXPR auto cosh(const complex<T, EnableType>& my_z) -> complex<T, EnableType>
    {
      using std::cos;
      using std::exp;
      using std::sin;

      const T exp_real     { exp(my_z.real()) };
      const T exp_real_inv { T(static_cast<unsigned>(UINT8_C(1))) / exp_real };

      const T cosh_real { (exp_real + exp_real_inv) / static_cast<unsigned>(UINT8_C(2)) };
      const T sinh_real { (exp_real - exp_real_inv) / static_cast<unsigned>(UINT8_C(2)) };

      return
      {
        cos(my_z.imag()) * cosh_real,
        sin(my_z.imag()) * sinh_real
      };
    }

    template<typename T, typename EnableType> EXTENDED_COMPLEX_CONSTEXPR auto exp(const complex<T, EnableType>& my_z) -> complex<T, EnableType>
    {
      using std::cos;
      using std::exp;
      using std::sin;

      const T exp_term { exp(my_z.real()) };

      return
      {
        cos(my_z.imag()) * exp_term,
        sin(my_z.imag()) * exp_term
      };
    }

    template<typename T, typename EnableType> EXTENDED_COMPLEX_CONSTEXPR auto log(const complex<T, EnableType>& my_z) -> complex<T, EnableType>
    {
      using std::atan2;
      using std::log;

      return
      {
        log(norm(my_z)) / static_cast<unsigned>(UINT8_C(2)),
        atan2(my_z.imag(), my_z.real())
      };
    }

    template<typename T, typename EnableType> EXTENDED_COMPLEX_CONSTEXPR auto log10(const complex<T, EnableType>& my_z) -> complex<T, EnableType>
    {
      using std::log;

      return log(my_z) / log(T(static_cast<unsigned>(UINT8_C(10))));
    }

    template<typename T, typename IntegralType, typename EnableType>
    EXTENDED_COMPLEX_CONSTEXPR auto pow(const complex<T, EnableType>& my_z, IntegralType my_pn) -> typename std::enable_if_t<std::is_integral<IntegralType>::value, complex<T, EnableType>>
    {
      if     (my_pn <  static_cast<int>(INT8_C(0))) { return  T(static_cast<unsigned>(UINT8_C(1))) / pow(my_z, -my_pn); }
      else if(my_pn == static_cast<int>(INT8_C(0))) { return  complex<T, EnableType>(T(static_cast<unsigned>(UINT8_C(1)))); }
      else if(my_pn == static_cast<int>(INT8_C(1))) { return  my_z; }
      else if(my_pn == static_cast<int>(INT8_C(2))) { return  my_z * my_z; }
      else if(my_pn == static_cast<int>(INT8_C(3))) { return (my_z * my_z) * my_z; }
      else if(my_pn == static_cast<int>(INT8_C(4))) { const complex<T, EnableType> my_z2(my_z * my_z); return (my_z2 * my_z2); }
      else
      {
        complex<T, EnableType> my_result { T(static_cast<unsigned>(UINT8_C(1))) };

        complex<T, EnableType> y { my_z };

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

    template<typename T, typename EnableType> EXTENDED_COMPLEX_CONSTEXPR auto pow(const complex<T, EnableType>& my_z, const T& my_a) -> complex<T, EnableType>
    {
      return exp(my_a * log(my_z));
    }

    template<typename T, typename EnableType> EXTENDED_COMPLEX_CONSTEXPR auto pow(const complex<T, EnableType>& my_z, const complex<T, EnableType>& my_a) -> complex<T, EnableType>
    {
      return exp(my_a * log(my_z));
    }

    template<typename T, typename EnableType> EXTENDED_COMPLEX_CONSTEXPR auto pow(const T& my_x, const complex<T, EnableType>& my_a) -> complex<T, EnableType>
    {
      using std::log;

      return exp(my_a * log(my_x));
    }

    template<typename T, typename EnableType> EXTENDED_COMPLEX_CONSTEXPR auto sin(const complex<T, EnableType>& my_z) -> complex<T, EnableType>
    {
      using std::cos;
      using std::exp;
      using std::sin;

      const T exp_imag     { exp(my_z.imag()) };
      const T exp_imag_inv { T(static_cast<unsigned>(UINT8_C(1))) / exp_imag };

      const T cosh_imag { (exp_imag + exp_imag_inv) / static_cast<unsigned>(UINT8_C(2)) };
      const T sinh_imag { (exp_imag - exp_imag_inv) / static_cast<unsigned>(UINT8_C(2)) };

      return
      {
        sin(my_z.real()) * cosh_imag,
        cos(my_z.real()) * sinh_imag
      };
    }

    template<typename T, typename EnableType> EXTENDED_COMPLEX_CONSTEXPR auto sinh(const complex<T, EnableType>& my_z) -> complex<T, EnableType>
    {
      using std::cos;
      using std::exp;
      using std::sin;

      const T exp_real     { exp(my_z.real()) };
      const T exp_real_inv { T(static_cast<unsigned>(UINT8_C(1))) / exp_real };

      const T cosh_real { (exp_real + exp_real_inv) / static_cast<unsigned>(UINT8_C(2)) };
      const T sinh_real { (exp_real - exp_real_inv) / static_cast<unsigned>(UINT8_C(2)) };

      return
      {
        cos(my_z.imag()) * sinh_real,
        sin(my_z.imag()) * cosh_real
      };
    }

    template<typename T, typename EnableType> EXTENDED_COMPLEX_CONSTEXPR auto sqrt(const complex<T, EnableType>& my_z) -> complex<T, EnableType>
    {
      using std::abs;
      using std::sqrt;

      // Use the following:
      // sqrt(z) = (s, zi / 2s)       for zr >= 0
      //           (|zi| / 2s, +-s)   for zr <  0
      // where s = sqrt{ [ |zr| + sqrt(zr^2 + zi^2) ] / 2 },
      // and the +- sign is the same as the sign of zi.

      const bool real_part_is_neg(my_z.real() < T(static_cast<unsigned>(UINT8_C(0))));
      const T    real_part_fabs  ((!real_part_is_neg) ? my_z.real() : -my_z.real());
      const T    s_part          (sqrt((real_part_fabs + abs(my_z)) / static_cast<unsigned>(UINT8_C(2))));

      if(!real_part_is_neg)
      {
        return
        {
          s_part,
          my_z.imag() / (s_part * static_cast<unsigned>(UINT8_C(2)))
        };
      }
      else
      {
        const bool imag_part_is_neg(my_z.imag() < T(static_cast<unsigned>(UINT8_C(0))));
        const T    imag_part_fabs  ((!imag_part_is_neg) ? my_z.imag() : -my_z.imag());

        return
        {
          imag_part_fabs / (s_part * static_cast<unsigned>(UINT8_C(2))),
          ((!imag_part_is_neg) ? s_part : -s_part)
        };
      }
    }

    template<typename T, typename EnableType> EXTENDED_COMPLEX_CONSTEXPR auto tan(const complex<T, EnableType>& my_z) -> complex<T, EnableType>
    {
      using std::cos;
      using std::exp;
      using std::sin;

      const T exp_imag     { exp(my_z.imag()) };
      const T exp_imag_inv { T(static_cast<unsigned>(UINT8_C(1))) / exp_imag };

      const T cosh_imag2 { exp_imag + exp_imag_inv };
      const T sinh_imag2 { exp_imag - exp_imag_inv };

      const T cos_real { cos(my_z.real()) };
      const T sin_real { sin(my_z.real()) };

      return   complex<T, EnableType>(sin_real * cosh_imag2,  cos_real * sinh_imag2)
             / complex<T, EnableType>(cos_real * cosh_imag2, -sin_real * sinh_imag2);
    }

    template<typename T, typename EnableType> EXTENDED_COMPLEX_CONSTEXPR auto tanh(const complex<T, EnableType>& my_z) -> complex<T, EnableType>
    {
      using std::cos;
      using std::exp;
      using std::sin;

      const T exp_real     { exp(my_z.real()) };
      const T exp_real_inv { T(static_cast<unsigned>(UINT8_C(1))) / exp_real };

      const T cosh_real2 { exp_real + exp_real_inv };
      const T sinh_real2 { exp_real - exp_real_inv };

      const T cos_imag { cos(my_z.imag()) };
      const T sin_imag { sin(my_z.imag()) };

      return   complex<T, EnableType>(cos_imag * sinh_real2, sin_imag * cosh_real2)
             / complex<T, EnableType>(cos_imag * cosh_real2, sin_imag * sinh_real2);
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

#endif // EXTENDED_COMPLEX_2016_02_22_H
