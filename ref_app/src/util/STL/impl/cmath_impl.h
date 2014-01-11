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
  #include <cstdfloat>

  namespace std
  {
    using ::cos;
    using ::fabs;
    using ::fmod;
    using ::modf;
    using ::sin;
    using ::sqrt;
    using ::tan;
    using ::floor;
    using ::ceil;
    using ::frexp;
    using ::ldexp;
    using ::cosh;
    using ::sinh;
    using ::atan;
    using ::atan2;
    using ::log;
    using ::log10;
    using ::pow;
    using ::isnan;
    using ::isinf;
    using ::square;
    using ::copysign;
    using ::fdim;
    using ::fma;
    using ::fmax;
    using ::fmin;
    using ::signbit;
    using ::trunc;
    using ::isfinite;
    using ::hypot;
    using ::round;
    using ::lround;
    using ::lrint;

    inline float abs(const float&  x) { return ::fabs(x); }

    // AVR C-library does not have tgamma or acosh.
    std::float32_t tgamma(std::float32_t x);
    std::float32_t acosh (std::float32_t x);
  }

#endif // _CMATH_IMPL_2010_02_23_H_
