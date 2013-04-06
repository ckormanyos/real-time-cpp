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

#endif // _CMATH_IMPL_2010_02_23_H_
