///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2014.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef _COMPLEX_IMPL_2012_02_20_H_
  #define _COMPLEX_IMPL_2012_02_20_H_

  #if defined(__GNUC__)
  #pragma GCC system_header
  #endif

  #include "cmath_impl.h"

  // Implement std::complex for compilers that do not support it.

  namespace std
  {
    // Forward template class definitions.
    template<typename T> class complex;
    template<> class complex<float>;
    template<> class complex<double>;
    template<> class complex<long double>;

    // Forward template function definitions.
    template<typename T> complex<T> sqrt (const complex<T>& my_xt);
    template<typename T> complex<T> sin  (const complex<T>& my_xt);
    template<typename T> complex<T> cos  (const complex<T>& my_xt);
    template<typename T> complex<T> tan  (const complex<T>& my_xt);
    template<typename T> complex<T> asin (const complex<T>& my_xt);
    template<typename T> complex<T> acos (const complex<T>& my_xt);
    template<typename T> complex<T> atan (const complex<T>& my_xt);
    template<typename T> complex<T> exp  (const complex<T>& my_xt);
    template<typename T> complex<T> log  (const complex<T>& my_xt);
    template<typename T> complex<T> log10(const complex<T>& my_xt);
    template<typename T> complex<T> pow  (const complex<T>& my_xt, int my_pn);
    template<typename T> complex<T> pow  (const complex<T>& my_xt, const T& my_at);
    template<typename T> complex<T> pow  (const complex<T>& my_xt, const complex<T>& my_at);
    template<typename T> complex<T> pow  (const T& my_xt, const complex<T>& my_at);
    template<typename T> complex<T> sinh (const complex<T>& my_xt);
    template<typename T> complex<T> cosh (const complex<T>& my_xt);
    template<typename T> complex<T> tanh (const complex<T>& my_xt);
    template<typename T> complex<T> asinh(const complex<T>& my_xt);
    template<typename T> complex<T> acosh(const complex<T>& my_xt);
    template<typename T> complex<T> atanh(const complex<T>& my_xt);

    template<typename T>
    class complex
    {
    public:
      typedef T value_type;

      complex(const value_type& re_ = value_type(),
              const value_type& im_ = value_type()) : my_re(re_), my_im(im_) { }

      complex(const complex& my_vt) : my_re(my_vt.real), my_im(my_vt.imag) { }

      template<typename X>
      complex(const complex<X>& my_xt) : my_re(my_xt.real), my_im(my_xt.imag) { }

      value_type real() const { return my_re; }
      value_type imag() const { return my_im; }
      void real(value_type my_vt) { my_re = my_vt; }
      void imag(value_type my_vt) { my_im = my_vt; }

      complex<value_type>& operator=(value_type my_vt) { my_re = my_vt; my_im = value_type(0); return *this; }
      complex<value_type>& operator=(const complex<value_type>& my_vt) { my_re = my_vt.my_re; my_im = my_vt.my_im; return *this; }

      complex<value_type>& operator+=(value_type my_vt)
      {
        my_re += my_vt;
        return *this;
      }

      complex<value_type>& operator-=(value_type my_vt)
      {
        my_re -= my_vt;
        return *this;
      }

      complex<value_type>& operator*=(value_type my_vt)
      {
        my_re *= my_vt;
        my_im *= my_vt;
        return *this;
      }

      complex<value_type>& operator/=(value_type my_vt)
      {
        my_re /= my_vt;
        my_im /= my_vt;
        return *this;
      }

      template<typename X> complex<value_type>& operator=(const complex<X>& my_xt)
      {
        my_re = value_type(my_xt.my_re);
        my_im = value_type(my_xt.my_im);
        return *this;
      }

      template<typename X> complex<value_type>& operator+=(const complex<X>& my_xt)
      {
        my_re += value_type(my_xt.my_re);
        my_im += value_type(my_xt.my_im);
        return *this;
      }

      template<typename X> complex<value_type>& operator-=(const complex<X>& my_xt)
      {
        my_re -= value_type(my_xt.my_re);
        my_im -= value_type(my_xt.my_im);
        return *this;
      }

      template<typename X> complex<value_type>& operator*=(const complex<X>& my_xt)
      {
        const value_type re_x(my_xt.my_re);
        const value_type im_x(my_xt.my_im);
        const value_type tmp_re((my_re * re_x) - (my_im * im_x));
        const value_type tmp_im((my_re * im_x) + (my_im * re_x));
        my_re = tmp_re;
        my_im = tmp_im;
        return *this;
      }

      template<typename X> complex<value_type>& operator/=(const complex<X>& my_xt)
      {
        const value_type re_x(my_xt.my_re);
        const value_type im_x(my_xt.my_im);
        const value_type one_over_denom = value_type(1) / ::sqrt((re_x * re_x) + (im_x * im_x));
        const value_type tmp_re = ((my_re * re_x) + (my_im * im_x)) * one_over_denom;
        const value_type tmp_im = ((my_im * re_x) - (my_re * im_x)) * one_over_denom;
        my_re = tmp_re;
        my_im = tmp_im;
        return *this;
      }

    private:
      value_type my_re;
      value_type my_im;
    };

    template<>
    class complex<float>
    {
    public:
      typedef float value_type;

      complex(float re_ = 0.0F, float im_ = 0.0F) : my_re(re_), my_im(im_) { }

      explicit complex(const complex<double>& my_d);
      explicit complex(const complex<long double>& my_ld);

      value_type real() const { return my_re; }
      value_type imag() const { return my_im; }
      void real(value_type my_vt) { my_re = my_vt; }
      void imag(value_type my_vt) { my_im = my_vt; }

      complex<value_type>& operator=(value_type my_vt) { my_re = my_vt; my_im = value_type(0); return *this; }
      complex<value_type>& operator=(const complex<value_type>& my_vt) { my_re = my_vt.my_re; my_im = my_vt.my_im; return *this; }

      complex<value_type>& operator+=(value_type my_vt)
      {
        my_re += my_vt;
        return *this;
      }

      complex<value_type>& operator-=(value_type my_vt)
      {
        my_re -= my_vt;
        return *this;
      }

      complex<value_type>& operator*=(value_type my_vt)
      {
        my_re *= my_vt;
        my_im *= my_vt;
        return *this;
      }

      complex<value_type>& operator/=(value_type my_vt)
      {
        my_re /= my_vt;
        my_im /= my_vt;
        return *this;
      }

      template<typename X> complex<value_type>& operator=(const complex<X>& my_xt)
      {
        my_re = value_type(my_xt.my_re);
        my_im = value_type(my_xt.my_im);
        return *this;
      }

      template<typename X> complex<value_type>& operator+=(const complex<X>& my_xt)
      {
        my_re += value_type(my_xt.my_re);
        my_im += value_type(my_xt.my_im);
        return *this;
      }

      template<typename X> complex<value_type>& operator-=(const complex<X>& my_xt)
      {
        my_re -= value_type(my_xt.my_re);
        my_im -= value_type(my_xt.my_im);
        return *this;
      }

      template<typename X> complex<value_type>& operator*=(const complex<X>& my_xt)
      {
        const value_type re_x(my_xt.my_re);
        const value_type im_x(my_xt.my_im);
        const value_type tmp_re((my_re * re_x) - (my_im * im_x));
        const value_type tmp_im((my_re * im_x) + (my_im * re_x));
        my_re = tmp_re;
        my_im = tmp_im;
        return *this;
      }

      template<typename X> complex<value_type>& operator/=(const complex<X>& my_xt)
      {
        const value_type re_x(my_xt.my_re);
        const value_type im_x(my_xt.my_im);
        const value_type one_over_denom = value_type(1) / ::sqrt((re_x * re_x) + (im_x * im_x));
        const value_type tmp_re = ((my_re * re_x) + (my_im * im_x)) * one_over_denom;
        const value_type tmp_im = ((my_im * re_x) - (my_re * im_x)) * one_over_denom;
        my_re = tmp_re;
        my_im = tmp_im;
        return *this;
      }

    private:
      value_type my_re;
      value_type my_im;
    };

    template<>
    class complex<double>
    {
    public:
      typedef double value_type;

      complex(double re_ = 0.0, double im_ = 0.0) : my_re(re_), my_im(im_) { }

      explicit complex(const complex<float>& my_d) : my_re(value_type( my_d.real())), my_im(value_type( my_d.imag())) { }
      explicit complex(const complex<long double>& my_ld);

      value_type real() const { return my_re; }
      value_type imag() const { return my_im; }
      void real(value_type my_vt) { my_re = my_vt; }
      void imag(value_type my_vt) { my_im = my_vt; }

      complex<value_type>& operator=(value_type my_vt) { my_re = my_vt; my_im = value_type(0); return *this; }
      complex<value_type>& operator=(const complex<value_type>& my_vt) { my_re = my_vt.my_re; my_im = my_vt.my_im; return *this; }

      complex<value_type>& operator+=(value_type my_vt)
      {
        my_re += my_vt;
        return *this;
      }

      complex<value_type>& operator-=(value_type my_vt)
      {
        my_re -= my_vt;
        return *this;
      }

      complex<value_type>& operator*=(value_type my_vt)
      {
        my_re *= my_vt;
        my_im *= my_vt;
        return *this;
      }

      complex<value_type>& operator/=(value_type my_vt)
      {
        my_re /= my_vt;
        my_im /= my_vt;
        return *this;
      }

      template<typename X> complex<value_type>& operator=(const complex<X>& my_xt)
      {
        my_re = value_type(my_xt.my_re);
        my_im = value_type(my_xt.my_im);
        return *this;
      }

      template<typename X> complex<value_type>& operator+=(const complex<X>& my_xt)
      {
        my_re += value_type(my_xt.my_re);
        my_im += value_type(my_xt.my_im);
        return *this;
      }

      template<typename X> complex<value_type>& operator-=(const complex<X>& my_xt)
      {
        my_re -= value_type(my_xt.my_re);
        my_im -= value_type(my_xt.my_im);
        return *this;
      }

      template<typename X> complex<value_type>& operator*=(const complex<X>& my_xt)
      {
        const value_type re_x(my_xt.my_re);
        const value_type im_x(my_xt.my_im);
        const value_type tmp_re((my_re * re_x) - (my_im * im_x));
        const value_type tmp_im((my_re * im_x) + (my_im * re_x));
        my_re = tmp_re;
        my_im = tmp_im;
        return *this;
      }

      template<typename X> complex<value_type>& operator/=(const complex<X>& my_xt)
      {
        const value_type re_x(my_xt.my_re);
        const value_type im_x(my_xt.my_im);
        const value_type one_over_denom = value_type(1) / ::sqrt((re_x * re_x) + (im_x * im_x));
        const value_type tmp_re = ((my_re * re_x) + (my_im * im_x)) * one_over_denom;
        const value_type tmp_im = ((my_im * re_x) - (my_re * im_x)) * one_over_denom;
        my_re = tmp_re;
        my_im = tmp_im;
        return *this;
      }

    private:
      value_type my_re;
      value_type my_im;
    };

    template<>
    class complex<long double>
    {
    public:
      typedef long double value_type;

      complex(value_type re_ = 0.0L, value_type im_ = 0.0L) : my_re(re_), my_im(im_) { }

      explicit complex(const complex<float>&  f) : my_re(value_type(f.real())), my_im(value_type(f.imag())) { }
      explicit complex(const complex<double>& my_d) : my_re(value_type(my_d.real())), my_im(value_type(my_d.imag())) { }

      value_type real() const { return my_re; }
      value_type imag() const { return my_im; }
      void real(value_type my_vt) { my_re = my_vt; }
      void imag(value_type my_vt) { my_im = my_vt; }

      complex<value_type>& operator=(value_type my_vt) { my_re = my_vt; my_im = value_type(0); return *this; }
      complex<value_type>& operator=(const complex<value_type>& my_vt) { my_re = my_vt.my_re; my_im = my_vt.my_im; return *this; }

      complex<value_type>& operator+=(value_type my_vt)
      {
        my_re += my_vt;
        return *this;
      }

      complex<value_type>& operator-=(value_type my_vt)
      {
        my_re -= my_vt;
        return *this;
      }

      complex<value_type>& operator*=(value_type my_vt)
      {
        my_re *= my_vt;
        my_im *= my_vt;
        return *this;
      }

      complex<value_type>& operator/=(value_type my_vt)
      {
        my_re /= my_vt;
        my_im /= my_vt;
        return *this;
      }

      template<typename X> complex<value_type>& operator=(const complex<X>& my_xt)
      {
        my_re = value_type(my_xt.my_re);
        my_im = value_type(my_xt.my_im);
        return *this;
      }

      template<typename X> complex<value_type>& operator+=(const complex<X>& my_xt)
      {
        my_re += value_type(my_xt.my_re);
        my_im += value_type(my_xt.my_im);
        return *this;
      }

      template<typename X> complex<value_type>& operator-=(const complex<X>& my_xt)
      {
        my_re -= value_type(my_xt.my_re);
        my_im -= value_type(my_xt.my_im);
        return *this;
      }

      template<typename X> complex<value_type>& operator*=(const complex<X>& my_xt)
      {
        const value_type re_x(my_xt.my_re);
        const value_type im_x(my_xt.my_im);
        const value_type tmp_re((my_re * re_x) - (my_im * im_x));
        const value_type tmp_im((my_re * im_x) + (my_im * re_x));
        my_re = tmp_re;
        my_im = tmp_im;
        return *this;
      }

      template<typename X> complex<value_type>& operator/=(const complex<X>& my_xt)
      {
        const value_type re_x(my_xt.my_re);
        const value_type im_x(my_xt.my_im);
        const value_type one_over_denom = value_type(1) / ::sqrt((re_x * re_x) + (im_x * im_x));
        const value_type tmp_re = ((my_re * re_x) + (my_im * im_x)) * one_over_denom;
        const value_type tmp_im = ((my_im * re_x) - (my_re * im_x)) * one_over_denom;
        my_re = tmp_re;
        my_im = tmp_im;
        return *this;
      }

    private:
      value_type my_re;
      value_type my_im;
    };

    // These constructors are here because they need to come
    // after the template specializations have been defined.

    inline complex<float>::complex (const complex<double>& my_d) :       my_re(float ( my_d.real())), my_im(float ( my_d.imag())) { }
    inline complex<float>::complex (const complex<long double>& my_ld) : my_re(float (my_ld.real())), my_im(float (my_ld.imag())) { }
    inline complex<double>::complex(const complex<long double>& my_ld) : my_re(double(my_ld.real())), my_im(double(my_ld.imag())) { }

    // 26.4.7, values
    template<typename T> T real(const complex<T>& my_xt) { return my_xt.real(); }
    template<typename T> T imag(const complex<T>& my_xt) { return my_xt.imag(); }
    template<typename T> T abs (const complex<T>& my_xt) { return std::sqrt((real(my_xt) * real(my_xt)) + (imag(my_xt) * imag(my_xt))); }
    template<typename T> T arg (const complex<T>& my_xt);
    template<typename T> T norm(const complex<T>& my_xt) { return (real(my_xt) * real(my_xt)) + (imag(my_xt) * imag(my_xt)); }
    template<typename T> complex<T> conj (const complex<T>& my_xt);
    template<typename T> complex<T> proj (const complex<T>& my_xt);
    template<typename T> complex<T> polar(const T& my_xt, const T& = T(0.0F));

    // Global add, sub, mul, div.
    template<typename T> complex<T> operator+(const complex<T>& my_ut, const complex<T>& my_vt) { return complex<T>(my_ut.real() + my_vt.real(), my_ut.imag() + my_vt.imag()); }
    template<typename T> complex<T> operator-(const complex<T>& my_ut, const complex<T>& my_vt) { return complex<T>(my_ut.real() - my_vt.real(), my_ut.imag() - my_vt.imag()); }

    template<typename T> complex<T> operator*(const complex<T>& my_ut, const complex<T>& my_vt)
    {
      const typename complex<T>::value_type ur = my_ut.real();
      const typename complex<T>::value_type ui = my_ut.imag();
      const typename complex<T>::value_type vr = my_vt.real();
      const typename complex<T>::value_type vi = my_vt.imag();
      return complex<T>((ur * vr) - (ui * vi), (ur * vi) + (ui * vr));
    }

    template<typename T> complex<T> operator/(const complex<T>& my_ut, const complex<T>& my_vt)
    {
      const T one_over_denom = T(1.0F) / std::norm(my_vt);
      const T tmp_re = ((my_ut.real() * my_vt.real()) + (my_ut.imag() * my_vt.imag())) * one_over_denom;
      const T tmp_im = ((my_ut.imag() * my_vt.real()) - (my_ut.real() * my_vt.imag())) * one_over_denom;
      return complex<T>(tmp_re, tmp_im);
    }

    template<typename T> complex<T> operator+(const complex<T>& my_ut, const T& my_vt)  { return complex<T>(my_ut.real() + my_vt, my_ut.imag()); }
    template<typename T> complex<T> operator-(const complex<T>& my_ut, const T& my_vt)  { return complex<T>(my_ut.real() - my_vt, my_ut.imag()); }
    template<typename T> complex<T> operator*(const complex<T>& my_ut, const T& my_vt)  { return complex<T>(my_ut.real() * my_vt, my_ut.imag() * my_vt); }
    template<typename T> complex<T> operator/(const complex<T>& my_ut, const T& my_vt)  { return complex<T>(my_ut.real() / my_vt, my_ut.imag() / my_vt); }

    template<typename T> complex<T> operator+(const T& my_ut, const complex<T>& my_vt) { return complex<T>(my_ut + my_vt.real(), my_vt.imag()); }
    template<typename T> complex<T> operator-(const T& my_ut, const complex<T>& my_vt) { return complex<T>(my_ut - my_vt.real(), -my_vt.imag()); }
    template<typename T> complex<T> operator*(const T& my_ut, const complex<T>& my_vt) { return complex<T>(my_ut * my_vt.real(), my_ut * my_vt.imag()); }
    template<typename T> complex<T> operator/(const T& my_ut, const complex<T>& my_vt) { const T v_norm = norm(my_vt); return complex<T>((my_ut * my_vt.real()) / v_norm, (-my_ut * my_vt.imag()) / v_norm); }

    // Unary +/-
    template<typename T> complex<T> operator+(const complex<T>& my_ut) { return my_ut; }
    template<typename T> complex<T> operator-(const complex<T>& my_ut) { return complex<T>(-my_ut.real(), -my_ut.imag()); }

    // Equality and inequality
    template<typename T> bool operator==(const complex<T>& my_ut, const complex<T>& my_vt) { return ((my_ut.real() == my_vt.real()) && (my_ut.imag() == my_vt.imag())); }
    template<typename T> bool operator!=(const complex<T>& my_ut, const complex<T>& my_vt) { return ((my_ut.real() != my_vt.real()) || (my_ut.imag() != my_vt.imag())); }

    template<typename T> bool operator==(const complex<T>& my_ut, const T& my_vt) { return ((my_ut.real() == my_vt) && (my_ut.imag() == T(0))); }
    template<typename T> bool operator!=(const complex<T>& my_ut, const T& my_vt) { return ((my_ut.real() != my_vt) || (my_ut.imag() != T(0))); }

    template<typename T> bool operator==(const T& my_ut, const complex<T>& my_vt) { return ((my_ut == my_vt.real()) && (my_vt.imag() == T(0))); }
    template<typename T> bool operator!=(const T& my_ut, const complex<T>& my_vt) { return ((my_ut != my_vt.real()) || (my_vt.imag() != T(0))); }

    namespace detail
    {
      template<typename T> complex<T> multiply_by_i(const complex<T>& my_xt)
      {
        const T tmp_r = my_xt.real();
        return complex<T>(-my_xt.imag(), tmp_r);
      }
    }

    // 26.4.8, transcendentals
    template<typename T> complex<T> sqrt(const complex<T>& my_xt)
    {
      // sqrt(*this) = (s, I / 2s)     for R >= 0
      //               (|I| / 2s, +-s) for R <  0
      // where s = sqrt{ [ |R| + sqrt(R^2 + I^2) ] / 2 },
      // and the +- sign is the same as the sign of I.
      const T zr = my_xt.real();
      const T s = std::sqrt((std::fabs(zr) + std::abs(my_xt)) / T(2.0F));
      const T zi = my_xt.imag();
      if(zr >= T(0.0F))
      {
        return complex<T>(s, (zi / s) / T(2.0F));
      }
      else
      {
        const bool imag_is_pos = (zi >= T(0.0F));
        return complex<T>((std::fabs(zi) / s) / T(2.0F), (imag_is_pos ? s : -s));
      }
    }

    template<typename T> complex<T> sin(const complex<T>& my_xt)
    {
      const T sin_x  = std::sin (my_xt.real());
      const T cos_x  = std::cos (my_xt.real());
      const T sinh_y = std::sinh(my_xt.imag());
      const T cosh_y = std::cosh(my_xt.imag());
      return complex<T>(sin_x * cosh_y, cos_x * sinh_y);
    }

    template<typename T> complex<T> cos(const complex<T>& my_xt)
    {
      const T sin_x =  std::sin (my_xt.real());
      const T cos_x =  std::cos (my_xt.real());
      const T sinh_y = std::sinh(my_xt.imag());
      const T cosh_y = std::cosh(my_xt.imag());
      return complex<T>(cos_x * cosh_y, -(sin_x * sinh_y));
    }

    template<typename T> complex<T> tan(const complex<T>& my_xt)
    {
      return std::sin(my_xt) / std::cos(my_xt);
    }

    template<typename T> complex<T> asin(const complex<T>& my_xt)
    {
      return -detail::multiply_by_i(std::log(detail::multiply_by_i(my_xt) + std::sqrt(T(1.0F) - (my_xt * my_xt))));
    }

    template<typename T> complex<T> acos(const complex<T>& my_xt)
    {
      return T(1.570796326794896619231321691639751442099L) - std::asin(my_xt);
    }

    template<typename T> complex<T> atan(const complex<T>& my_xt)
    {
      const complex<T> izz = detail::multiply_by_i(my_xt);
      return detail::multiply_by_i(std::log(T(1) - izz) - std::log(T(1) + izz)) / T(2.0F);
    }

    template<typename T> complex<T> exp(const complex<T>& my_xt)
    {
      const T zi  = my_xt.imag();
      const T szi = std::sin(zi);
      const T czi = std::cos(zi);
      return complex<T>(czi, szi) * std::exp(my_xt.real());
    }

    template<typename T> complex<T> log(const complex<T>& my_xt)
    {
      return complex<T>(std::log(std::norm(my_xt)) / T(2.0F), std::atan2(my_xt.imag(), my_xt.real()));
    }

    template<typename T> complex<T> log10(const complex<T>& my_xt)
    {
      return std::log(my_xt) / T(2.302585092994045684017991454684364207601L);
    }

    template<typename T> complex<T> pow(const complex<T>& my_xt, int my_pn)
    {
      if     (my_pn <  0) { return  T(1.0F) / pow(my_xt, -my_pn); }
      else if(my_pn == 0) { return  T(1.0F); }
      else if(my_pn == 1) { return  my_xt; }
      else if(my_pn == 2) { return  my_xt * my_xt; }
      else if(my_pn == 3) { return (my_xt * my_xt) * my_xt; }
      else if(my_pn == 4) { const complex<T> x2 = my_xt * my_xt; return (x2 * x2); }
      else
      {
        // The variable xn stores the binary powers of my_xt.
        complex<T> result(((my_pn % 2) != 0) ? my_xt : complex<T>(T(1.0F)));
        complex<T> xn    (my_xt);

        int p2 = my_pn;

        while((p2 /= 2) != 0)
        {
          // Square xn for each binary power.
          xn *= xn;

          const bool has_binary_power = ((p2 % 2) != 0);

          if(has_binary_power)
          {
            // Multiply the result with each binary power contained in the exponent.
            result *= xn;
          }
        }

        return result;
      }
    }

    template<typename T> complex<T> pow(const complex<T>& my_xt, const T& my_at)
    {
      std::exp(my_at * std::log(my_xt));
    }

    template<typename T> complex<T> pow(const complex<T>& my_xt, const complex<T>& my_at)
    {
      std::exp(my_at * std::log(my_xt));
    }

    template<typename T> complex<T> pow(const T& my_xt, const complex<T>& my_at)
    {
      std::exp(my_at * std::log(my_xt));
    }

    template<typename T> complex<T> sinh(const complex<T>& my_xt)
    {
      const T sin_y =  std::sin (my_xt.imag());
      const T cos_y =  std::cos (my_xt.imag());
      const T sinh_x = std::sinh(my_xt.real());
      const T cosh_x = std::cosh(my_xt.real());
      return complex<T>(cos_y * sinh_x, cosh_x * sin_y);
    }

    template<typename T> complex<T> cosh(const complex<T>& my_xt)
    {
      const T sin_y =  std::sin (my_xt.imag());
      const T cos_y =  std::cos (my_xt.imag());
      const T sinh_x = std::sinh(my_xt.real());
      const T cosh_x = std::cosh(my_xt.real());
      return complex<T>(cos_y * cosh_x, sin_y * sinh_x);
    }

    template<typename T> complex<T> tanh(const complex<T>& my_xt)
    {
      return std::sinh(my_xt) / std::cosh(my_xt);
    }

    template<typename T> complex<T> asinh(const complex<T>& my_xt)
    {
      return std::log(my_xt + std::sqrt((my_xt * my_xt) + T(1.0F)));
    }

    template<typename T> complex<T> acosh(const complex<T>& my_xt)
    {
      const complex<T> zp(my_xt.real() + T(1.0F), my_xt.imag());
      const complex<T> zm(my_xt.real() - T(1.0F), my_xt.imag());
      return std::log(my_xt + (zp * std::sqrt(zm / zp)));
    }

    template<typename T> complex<T> atanh(const complex<T>& my_xt)
    {
      return (std::log(T(1.0F) + my_xt) - std::log(T(1.0F) - my_xt)) / T(2.0F);
    }
  }

#endif // _COMPLEX_IMPL_2012_02_20_H_

/*
#include <complex>

const std::complex<double> x(1.2, 3.4);
const std::complex<double> y = std::asinh(x);
*/
