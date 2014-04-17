///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2013.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef _CMATH_IMPL_2010_02_23_H_
  #define _CMATH_IMPL_2010_02_23_H_

  // Here, we do not provide a full std implementation of <cmath>.
  // We simply include math.h and provide a few exemplary patches.

  #include <math.h>
  #include <cstdfloat>

  namespace std
  {
    inline std::float32_t abs(const std::float32_t  x) { return ::fabs(x); }
    using ::fabs;
    using ::fmod;
    using ::modf;
    using ::floor;
    using ::ceil;
    using ::frexp;
    using ::ldexp;
    using ::isnan;
    using ::isinf;
    using ::isfinite;
    using ::sqrt;
    using ::sin;
    using ::cos;
    using ::tan;
    using ::asin;
    using ::acos;
    using ::atan;
    using ::atan2;
    using ::exp;
    using ::pow;
    using ::log;
    using ::log10;
    using ::sinh;
    using ::cosh;
    using ::tanh;

    // AVR C-library does not have certain functions. So we will
    // patch some of them in an exemplary fashion for float32_t.
    std::float32_t asinh (std::float32_t x);
    std::float32_t acosh (std::float32_t x);
    std::float32_t atanh (std::float32_t x);
    std::float32_t lgamma(std::float32_t x);
    std::float32_t tgamma(std::float32_t x);
  }

#endif // _CMATH_IMPL_2010_02_23_H_
