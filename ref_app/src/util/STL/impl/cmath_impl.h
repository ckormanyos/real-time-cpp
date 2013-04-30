///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2013.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef _CMATH_IMPL_2010_02_23_H_
  #define _CMATH_IMPL_2010_02_23_H_

  // No real std implementation yet.
  // Just include math.h.
  #include <math.h>

  inline bool isfinite (float x)  { return (::isfinite(static_cast<double>(x)) != 0); }

  // AVR C-library does not have tgamma.
  float tgamma(float x);
  double tgamma(double x);

  float acosh(float x);
  double acosh(double x);

  namespace std
  {
    template<typename T> inline T abs(T t) { return ((t < T(0)) ? -t : t); }

    inline float sin (float  x) { return ::sinf(x); }
    inline float cos (float  x) { return ::cosf(x); }
    inline float tan (float  x) { return ::tanf(x); }
    inline float asin(float  x) { return ::asinf(x); }
    inline float acos(float  x) { return ::acosf(x); }
    inline float atan(float  x) { return ::atanf(x); }
    inline float sinh(float  x) { return ::sinhf(x); }
    inline float cosh(float  x) { return ::coshf(x); }
    inline float tanh(float  x) { return ::tanhf(x); }
    inline float exp (float  x) { return ::expf(x); }
    inline float log (float  x) { return ::logf(x); }

    inline double sin (double x) { return ::sin(x); }
    inline double cos (double x) { return ::cos(x); }
    inline double tan (double x) { return ::tan(x); }
    inline double asin(double x) { return ::asin(x); }
    inline double acos(double x) { return ::acos(x); }
    inline double atan(double x) { return ::atan(x); }
    inline double sinh(double x) { return ::sinh(x); }
    inline double cosh(double x) { return ::cosh(x); }
    inline double tanh(double x) { return ::tanh(x); }
    inline double exp (double x) { return ::exp(x); }
    inline double log (double x) { return ::log(x); }
  }

#endif // _CMATH_IMPL_2010_02_23_H_
