///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2013.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef _COMPLEX_IMPL_2012_02_20_H_
  #define _COMPLEX_IMPL_2012_02_20_H_

  #if defined(__GNUC__)
  #pragma GCC system_header
  #endif

  #include <math.h>

  // Implement std::complex for compilers that do not support it.

  namespace std
  {
    // Forward template class definitions.
    template<typename T> class complex;
    template<> class complex<float>;
    template<> class complex<double>;
    template<> class complex<long double>;

    // Forward template function definitions.
    template<typename T> complex<T> sqrt(const complex<T>& x);
    template<typename T> complex<T> sin(const complex<T>& x);
    template<typename T> complex<T> cos(const complex<T>& x);
    template<typename T> complex<T> tan(const complex<T>& x);
    template<typename T> complex<T> asin(const complex<T>& x);
    template<typename T> complex<T> acos(const complex<T>& x);
    template<typename T> complex<T> atan(const complex<T>& x);
    template<typename T> complex<T> exp(const complex<T>& x);
    template<typename T> complex<T> log(const complex<T>& x);
    template<typename T> complex<T> log10(const complex<T>& x);
    template<typename T> complex<T> pow(const complex<T>& x, const T& a);
    template<typename T> complex<T> pow(const complex<T>& x, const complex<T>& a);
    template<typename T> complex<T> pow(const T& x, const complex<T>& a);
    template<typename T> complex<T> sinh(const complex<T>& x);
    template<typename T> complex<T> cosh(const complex<T>& x);
    template<typename T> complex<T> tanh(const complex<T>& x);
    template<typename T> complex<T> asinh(const complex<T>& x);
    template<typename T> complex<T> acosh(const complex<T>& x);
    template<typename T> complex<T> atanh(const complex<T>& x);

    template<typename T>
    class complex
    {
    public:
      typedef T value_type;

      complex(const value_type& Re = value_type(),
              const value_type& Im = value_type()) : re(Re), im(Im) { }

      complex(const complex& v) : re(v.real), im(v.imag) { }

      template<typename X>
      complex(const complex<X>& x) : re(x.real), im(x.imag) { }

      value_type real() const { return re; }
      value_type imag() const { return im; }
      void real(value_type v) { re = v; }
      void imag(value_type v) { im = v; }

      complex<value_type>& operator=(value_type v) { re = v; im = value_type(0); return *this; }
      complex<value_type>& operator=(const complex<value_type>& v) { re = v.re; im = v.im; return *this; }

      complex<value_type>& operator+=(value_type v)
      {
        re += v;
        return *this;
      }

      complex<value_type>& operator-=(value_type v)
      {
        re -= v;
        return *this;
      }

      complex<value_type>& operator*=(value_type v)
      {
        re *= v;
        im *= v;
        return *this;
      }

      complex<value_type>& operator/=(value_type v)
      {
        re /= v;
        im /= v;
        return *this;
      }

      template<typename X> complex<value_type>& operator=(const complex<X>& x)
      {
        re = value_type(x.re);
        im = value_type(x.im);
        return *this;
      }

      template<typename X> complex<value_type>& operator+=(const complex<X>& x)
      {
        re += value_type(x.re);
        im += value_type(x.im);
        return *this;
      }

      template<typename X> complex<value_type>& operator-=(const complex<X>& x)
      {
        re -= value_type(x.re);
        im -= value_type(x.im);
        return *this;
      }

      template<typename X> complex<value_type>& operator*=(const complex<X>& x)
      {
        const value_type re_x(x.re);
        const value_type im_x(x.im);
        const value_type tmp_re((re * re_x) - (im * im_x));
        const value_type tmp_im((re * im_x) + (im * re_x));
        re = tmp_re;
        im = tmp_im;
        return *this;
      }

      template<typename X> complex<value_type>& operator/=(const complex<X>& x)
      {
        const value_type re_x(x.re);
        const value_type im_x(x.im);
        const value_type one_over_denom = value_type(1) / ::sqrt((re_x * re_x) + (im_x * im_x));
        const value_type tmp_re = ((re * re_x) + (im * im_x)) * one_over_denom;
        const value_type tmp_im = ((im * re_x) - (re * im_x)) * one_over_denom;
        re = tmp_re;
        im = tmp_im;
        return *this;
      }

    private:
      value_type re;
      value_type im;
    };

    template<>
    class complex<float>
    {
    public:
      typedef float value_type;

      complex(float Re = 0.0f, float Im = 0.0f) : re(Re), im(Im) { }

      explicit complex(const complex<double>& d);
      explicit complex(const complex<long double>& ld);

      value_type real() const { return re; }
      value_type imag() const { return im; }
      void real(value_type v) { re = v; }
      void imag(value_type v) { im = v; }

      complex<value_type>& operator=(value_type v) { re = v; im = value_type(0); return *this; }
      complex<value_type>& operator=(const complex<value_type>& v) { re = v.re; im = v.im; return *this; }

      complex<value_type>& operator+=(value_type v)
      {
        re += v;
        return *this;
      }

      complex<value_type>& operator-=(value_type v)
      {
        re -= v;
        return *this;
      }

      complex<value_type>& operator*=(value_type v)
      {
        re *= v;
        im *= v;
        return *this;
      }

      complex<value_type>& operator/=(value_type v)
      {
        re /= v;
        im /= v;
        return *this;
      }

      template<typename X> complex<value_type>& operator=(const complex<X>& x)
      {
        re = value_type(x.re);
        im = value_type(x.im);
        return *this;
      }

      template<typename X> complex<value_type>& operator+=(const complex<X>& x)
      {
        re += value_type(x.re);
        im += value_type(x.im);
        return *this;
      }

      template<typename X> complex<value_type>& operator-=(const complex<X>& x)
      {
        re -= value_type(x.re);
        im -= value_type(x.im);
        return *this;
      }

      template<typename X> complex<value_type>& operator*=(const complex<X>& x)
      {
        const value_type re_x(x.re);
        const value_type im_x(x.im);
        const value_type tmp_re((re * re_x) - (im * im_x));
        const value_type tmp_im((re * im_x) + (im * re_x));
        re = tmp_re;
        im = tmp_im;
        return *this;
      }

      template<typename X> complex<value_type>& operator/=(const complex<X>& x)
      {
        const value_type re_x(x.re);
        const value_type im_x(x.im);
        const value_type one_over_denom = value_type(1) / ::sqrt((re_x * re_x) + (im_x * im_x));
        const value_type tmp_re = ((re * re_x) + (im * im_x)) * one_over_denom;
        const value_type tmp_im = ((im * re_x) - (re * im_x)) * one_over_denom;
        re = tmp_re;
        im = tmp_im;
        return *this;
      }

    private:
      value_type re;
      value_type im;
    };

    template<>
    class complex<double>
    {
    public:
      typedef double value_type;

      complex(double Re = 0.0, double Im = 0.0) : re(Re), im(Im) { }

      explicit complex(const complex<float>& d) : re(value_type( d.real())), im(value_type( d.imag())) { }
      explicit complex(const complex<long double>& ld);

      value_type real() const { return re; }
      value_type imag() const { return im; }
      void real(value_type v) { re = v; }
      void imag(value_type v) { im = v; }

      complex<value_type>& operator=(value_type v) { re = v; im = value_type(0); return *this; }
      complex<value_type>& operator=(const complex<value_type>& v) { re = v.re; im = v.im; return *this; }

      complex<value_type>& operator+=(value_type v)
      {
        re += v;
        return *this;
      }

      complex<value_type>& operator-=(value_type v)
      {
        re -= v;
        return *this;
      }

      complex<value_type>& operator*=(value_type v)
      {
        re *= v;
        im *= v;
        return *this;
      }

      complex<value_type>& operator/=(value_type v)
      {
        re /= v;
        im /= v;
        return *this;
      }

      template<typename X> complex<value_type>& operator=(const complex<X>& x)
      {
        re = value_type(x.re);
        im = value_type(x.im);
        return *this;
      }

      template<typename X> complex<value_type>& operator+=(const complex<X>& x)
      {
        re += value_type(x.re);
        im += value_type(x.im);
        return *this;
      }

      template<typename X> complex<value_type>& operator-=(const complex<X>& x)
      {
        re -= value_type(x.re);
        im -= value_type(x.im);
        return *this;
      }

      template<typename X> complex<value_type>& operator*=(const complex<X>& x)
      {
        const value_type re_x(x.re);
        const value_type im_x(x.im);
        const value_type tmp_re((re * re_x) - (im * im_x));
        const value_type tmp_im((re * im_x) + (im * re_x));
        re = tmp_re;
        im = tmp_im;
        return *this;
      }

      template<typename X> complex<value_type>& operator/=(const complex<X>& x)
      {
        const value_type re_x(x.re);
        const value_type im_x(x.im);
        const value_type one_over_denom = value_type(1) / ::sqrt((re_x * re_x) + (im_x * im_x));
        const value_type tmp_re = ((re * re_x) + (im * im_x)) * one_over_denom;
        const value_type tmp_im = ((im * re_x) - (re * im_x)) * one_over_denom;
        re = tmp_re;
        im = tmp_im;
        return *this;
      }

    private:
      value_type re;
      value_type im;
    };

    template<>
    class complex<long double>
    {
    public:
      typedef long double value_type;

      complex(value_type Re = value_type(0), value_type Im = value_type(0)) : re(Re), im(Im) { }

      explicit complex(const complex<float>&  f) : re(value_type(f.real())), im(value_type(f.imag())) { }
      explicit complex(const complex<double>& d) : re(value_type(d.real())), im(value_type(d.imag())) { }

      value_type real() const { return re; }
      value_type imag() const { return im; }
      void real(value_type v) { re = v; }
      void imag(value_type v) { im = v; }

      complex<value_type>& operator=(value_type v) { re = v; im = value_type(0); return *this; }
      complex<value_type>& operator=(const complex<value_type>& v) { re = v.re; im = v.im; return *this; }

      complex<value_type>& operator+=(value_type v)
      {
        re += v;
        return *this;
      }

      complex<value_type>& operator-=(value_type v)
      {
        re -= v;
        return *this;
      }

      complex<value_type>& operator*=(value_type v)
      {
        re *= v;
        im *= v;
        return *this;
      }

      complex<value_type>& operator/=(value_type v)
      {
        re /= v;
        im /= v;
        return *this;
      }

      template<typename X> complex<value_type>& operator=(const complex<X>& x)
      {
        re = value_type(x.re);
        im = value_type(x.im);
        return *this;
      }

      template<typename X> complex<value_type>& operator+=(const complex<X>& x)
      {
        re += value_type(x.re);
        im += value_type(x.im);
        return *this;
      }

      template<typename X> complex<value_type>& operator-=(const complex<X>& x)
      {
        re -= value_type(x.re);
        im -= value_type(x.im);
        return *this;
      }

      template<typename X> complex<value_type>& operator*=(const complex<X>& x)
      {
        const value_type re_x(x.re);
        const value_type im_x(x.im);
        const value_type tmp_re((re * re_x) - (im * im_x));
        const value_type tmp_im((re * im_x) + (im * re_x));
        re = tmp_re;
        im = tmp_im;
        return *this;
      }

      template<typename X> complex<value_type>& operator/=(const complex<X>& x)
      {
        const value_type re_x(x.re);
        const value_type im_x(x.im);
        const value_type one_over_denom = value_type(1) / ::sqrt((re_x * re_x) + (im_x * im_x));
        const value_type tmp_re = ((re * re_x) + (im * im_x)) * one_over_denom;
        const value_type tmp_im = ((im * re_x) - (re * im_x)) * one_over_denom;
        re = tmp_re;
        im = tmp_im;
        return *this;
      }

    private:
      value_type re;
      value_type im;
    };

    // These constructors are here because they need to come
    // after the template specializations have been defined.

    inline complex<float>::complex (const complex<double>& d) :       re(float ( d.real())), im(float ( d.imag())) { }
    inline complex<float>::complex (const complex<long double>& ld) : re(float (ld.real())), im(float (ld.imag())) { }
    inline complex<double>::complex(const complex<long double>& ld) : re(double(ld.real())), im(double(ld.imag())) { }

    // 26.4.7, values
    template<typename T> T real(const complex<T>& x) { return x.real(); }
    template<typename T> T imag(const complex<T>& x) { return x.imag(); }
    template<typename T> T abs (const complex<T>& x) { return ::sqrt((real(x) * real(x)) + (imag(x) * imag(x))); }
    template<typename T> T arg (const complex<T>& x);
    template<typename T> T norm(const complex<T>& x) { return (real(x) * real(x)) + (imag(x) * imag(x)); }
    template<typename T> complex<T> conj (const complex<T>& x);
    template<typename T> complex<T> proj (const complex<T>& x);
    template<typename T> complex<T> polar(const T& x, const T& = 0);

    // Global add, sub, mul, div.
    template<typename T> complex<T> operator+(const complex<T>& u, const complex<T>& v) { return complex<T>(u.real() + v.real(), u.imag() + v.imag()); }
    template<typename T> complex<T> operator-(const complex<T>& u, const complex<T>& v) { return complex<T>(u.real() - v.real(), u.imag() - v.imag()); }
    template<typename T> complex<T> operator*(const complex<T>& u, const complex<T>& v)
    {
      const typename complex<T>::value_type ur = u.real();
      const typename complex<T>::value_type ui = u.imag();
      const typename complex<T>::value_type vr = v.real();
      const typename complex<T>::value_type vi = v.imag();
      return complex<T>((ur * vr) - (ui * vi), (ur * vi) + (ui * vr));
    }
    template<typename T> complex<T> operator/(const complex<T>& u, const complex<T>& v)
    {
      const T one_over_denom = T(1) / std::norm(v);
      const T tmp_re = ((u.real() * v.real()) + (u.imag() * v.imag())) * one_over_denom;
      const T tmp_im = ((u.imag() * v.real()) - (u.real() * v.imag())) * one_over_denom;
      return complex<T>(tmp_re, tmp_im);
    }

    template<typename T> complex<T> operator+(const complex<T>& u, const T& v)  { return complex<T>(u.real() + v, u.imag()); }
    template<typename T> complex<T> operator-(const complex<T>& u, const T& v)  { return complex<T>(u.real() - v, u.imag()); }
    template<typename T> complex<T> operator*(const complex<T>& u, const T& v)  { return complex<T>(u.real() * v, u.imag() * v); }
    template<typename T> complex<T> operator/(const complex<T>& u, const T& v)  { return complex<T>(u.real() / v, u.imag() / v); }

    template<typename T> complex<T> operator+(const T& u, const complex<T>& v) { return complex<T>(u + v.real(), v.imag()); }
    template<typename T> complex<T> operator-(const T& u, const complex<T>& v) { return complex<T>(u - v.real(), -v.imag()); }
    template<typename T> complex<T> operator*(const T& u, const complex<T>& v) { return complex<T>(u * v.real(), u * v.imag()); }
    template<typename T> complex<T> operator/(const T& u, const complex<T>& v) { const T v_norm = norm(v); return complex<T>((u * v.real()) / v_norm, (-u * v.imag()) / v_norm); }

    // Unary +/-
    template<typename T> complex<T> operator+(const complex<T>& u) { return u; }
    template<typename T> complex<T> operator-(const complex<T>& u) { return complex<T>(-u.real(), -u.imag()); }

    // Equality and inequality
    template<typename T> bool operator==(const complex<T>& u, const complex<T>& v) { return ((u.real() == v.real()) && (u.imag() == v.imag())); }
    template<typename T> bool operator!=(const complex<T>& u, const complex<T>& v) { return ((u.real() != v.real()) || (u.imag() != v.imag())); }

    template<typename T> bool operator==(const complex<T>& u, const T& v) { return ((u.real() == v) && (u.imag() == T(0))); }
    template<typename T> bool operator!=(const complex<T>& u, const T& v) { return ((u.real() != v) || (u.imag() != T(0))); }

    template<typename T> bool operator==(const T& u, const complex<T>& v) { return ((u == v.real()) && (v.imag() == T(0))); }
    template<typename T> bool operator!=(const T& u, const complex<T>& v) { return ((u != v.real()) || (v.imag() != T(0))); }

    template<typename T> complex<T> iz_helper__x(const complex<T>& x)
    {
      const T tmp_r = x.real();
      return complex<T>(-x.imag(), tmp_r);
    }

    // 26.4.8, transcendentals
    template<typename T> complex<T> sqrt(const complex<T>& x)
    {
      // sqrt(*this) = (s, I / 2s)     for R >= 0
      //               (|I| / 2s, +-s) for R <  0
      // where s = sqrt{ [ |R| + sqrt(R^2 + I^2) ] / 2 },
      // and the +- sign is the same as the sign of I.
      const T zr = x.real();
      const T s = ::sqrt((::fabs(zr) + std::abs(x)) / 2);
      const T zi = x.imag();
      if(zr >= T(0))
      {
        return complex<T>(s, (zi / s) / 2);
      }
      else
      {
        const bool imag_is_pos = (zi >= T(0));
        return complex<T>((::fabs(zi) / s) / 2, (imag_is_pos ? s : -s));
      }
    }
    template<typename T> complex<T> sin(const complex<T>& x)
    {
      const T sin_x = ::sin(x.real());
      const T cos_x = ::cos(x.real());
      const T sinh_y = ::sinh(x.imag());
      const T cosh_y = ::cosh(x.imag());
      return complex<T>(sin_x * cosh_y, cos_x * sinh_y);
    }
    template<typename T> complex<T> cos(const complex<T>& x)
    {
      const T sin_x = ::sin(x.real());
      const T cos_x = ::cos(x.real());
      const T sinh_y = ::sinh(x.imag());
      const T cosh_y = ::cosh(x.imag());
      return complex<T>(cos_x * cosh_y, -(sin_x * sinh_y));
    }
    template<typename T> complex<T> tan(const complex<T>& x)
    {
      return std::sin(x) / std::cos(x);
    }
    template<typename T> complex<T> asin(const complex<T>& x)
    {
      return -iz_helper__x(std::log(iz_helper__x(x) + std::sqrt(1 - (x * x))));
    }
    template<typename T> complex<T> acos(const complex<T>& x)
    {
      return T(1.570796326794896619231321691639751442099) - std::asin(x);
    }
    template<typename T> complex<T> atan(const complex<T>& x)
    {
      const complex<T> izz = iz_helper__x(x);
      return iz_helper__x(std::log(T(1) - izz) - std::log(T(1) + izz)) / T(2);
    }
    template<typename T> complex<T> exp(const complex<T>& x)
    {
      const T zi = x.imag();
      const T szi = ::sin(zi);
      const T czi = ::cos(zi);
      return complex<T>(czi, szi) * ::exp(x.real());
    }
    template<typename T> complex<T> log(const complex<T>& x)
    {
      return complex<T>(::log(std::norm(x)) / 2, ::atan2(x.imag(), x.real()));
    }
    template<typename T> complex<T> log10(const complex<T>& x)
    {
      return std::log(x) / T(2.302585092994045684017991454684364207601);
    }
    template<typename T> complex<T> pow(const complex<T>& x, const T& a)
    {
      std::exp(a * std::log(x));
    }
    template<typename T> complex<T> pow(const complex<T>& x, const complex<T>& a)
    {
      std::exp(a * std::log(x));
    }
    template<typename T> complex<T> pow(const T& x, const complex<T>& a)
    {
      std::exp(a * ::log(x));
    }
    template<typename T> complex<T> sinh(const complex<T>& x)
    {
      const T sin_y = ::sin(x.imag());
      const T cos_y = ::cos(x.imag());
      const T sinh_x = ::sinh(x.real());
      const T cosh_x = ::cosh(x.real());
      return complex<T>(cos_y * sinh_x, cosh_x * sin_y);
    }
    template<typename T> complex<T> cosh(const complex<T>& x)
    {
      const T sin_y = ::sin(x.imag());
      const T cos_y = ::cos(x.imag());
      const T sinh_x = ::sinh(x.real());
      const T cosh_x = ::cosh(x.real());
      return complex<T>(cos_y * cosh_x, sin_y * sinh_x);
    }
    template<typename T> complex<T> tanh(const complex<T>& x)
    {
      return std::sinh(x) / std::cosh(x);
    }
    template<typename T> complex<T> asinh(const complex<T>& x)
    {
      return std::log(x + std::sqrt((x * x) + T(1)));
    }
    template<typename T> complex<T> acosh(const complex<T>& x)
    {
      const complex<T> zp(x.real() + 1, x.imag());
      const complex<T> zm(x.real() - 1, x.imag());
      return std::log(x + (zp * std::sqrt(zm / zp)));
    }
    template<typename T> complex<T> atanh(const complex<T>& x)
    {
      return (std::log(T(1) + x) - std::log(T(1) - x)) / T(2);
    }
  }

#endif // _COMPLEX_IMPL_2012_02_20_H_
