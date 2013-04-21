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

    float sin (float  x) { return ::sinf(x); }
    float cos (float  x) { return ::cosf(x); }
    float tan (float  x) { return ::tanf(x); }
    float sinh(float  x) { return ::sinhf(x); }
    float cosh(float  x) { return ::coshf(x); }
    float tanh(float  x) { return ::tanhf(x); }

    double sin (double x) { return ::sin(x); }
    double cos (double x) { return ::cos(x); }
    double tan (double x) { return ::tan(x); }
    double sinh(double x) { return ::sinh(x); }
    double cosh(double x) { return ::cosh(x); }
    double tanh(double x) { return ::tanh(x); }
  }

#endif // _CMATH_IMPL_2010_02_23_H_
