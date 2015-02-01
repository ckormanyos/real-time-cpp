///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2013.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef _CMATH_IMPL_2010_02_23_H_
  #define _CMATH_IMPL_2010_02_23_H_

  // Implement most of <cmath> for compilers that do not yet support it.

  #include <math.h>
  #include <cstdfloat>

  namespace std
  {
    #if defined(__GNUC__)

      #if defined(__AVR__)
        #define __BUILTIN_FABSF  __builtin_fabs
        #define __BUILTIN_FMODF  __builtin_fmod
        #define __BUILTIN_MODFF  __builtin_modff
        #define __BUILTIN_FLOORF __builtin_floor
        #define __BUILTIN_CEILF  __builtin_ceil
        #define __BUILTIN_FREXPF __builtin_frexp
        #define __BUILTIN_LDEXPF __builtin_ldexp
        #define __BUILTIN_SQRTF  __builtin_sqrt
        #define __BUILTIN_SINF   __builtin_sin
        #define __BUILTIN_COSF   __builtin_cos
        #define __BUILTIN_TANF   __builtin_tan
        #define __BUILTIN_ASINF  __builtin_asin
        #define __BUILTIN_ACOSF  __builtin_acos
        #define __BUILTIN_ATANF  __builtin_atan
        #define __BUILTIN_ATAN2F __builtin_atan2
        #define __BUILTIN_EXPF   __builtin_exp
        #define __BUILTIN_POWF   __builtin_pow
        #define __BUILTIN_LOGF   __builtin_log
        #define __BUILTIN_LOG10F __builtin_log10
        #define __BUILTIN_SINHF  __builtin_sinh
        #define __BUILTIN_COSHF  __builtin_cosh
        #define __BUILTIN_TANHF  __builtin_tanh
      #else
        #define __BUILTIN_FABSF  __builtin_fabsf
        #define __BUILTIN_FMODF  __builtin_fmodf
        #define __BUILTIN_MODFF  __builtin_modff
        #define __BUILTIN_FLOORF __builtin_floorf
        #define __BUILTIN_CEILF  __builtin_ceilf
        #define __BUILTIN_FREXPF __builtin_frexpf
        #define __BUILTIN_LDEXPF __builtin_ldexpf
        #define __BUILTIN_SQRTF  __builtin_sqrtf
        #define __BUILTIN_SINF   __builtin_sinf
        #define __BUILTIN_COSF   __builtin_cosf
        #define __BUILTIN_TANF   __builtin_tanf
        #define __BUILTIN_ASINF  __builtin_asinf
        #define __BUILTIN_ACOSF  __builtin_acosf
        #define __BUILTIN_ATANF  __builtin_atanf
        #define __BUILTIN_ATAN2F __builtin_atan2f
        #define __BUILTIN_EXPF   __builtin_expf
        #define __BUILTIN_POWF   __builtin_powf
        #define __BUILTIN_LOGF   __builtin_logf
        #define __BUILTIN_LOG10F __builtin_log10f
        #define __BUILTIN_SINHF  __builtin_sinhf
        #define __BUILTIN_COSHF  __builtin_coshf
        #define __BUILTIN_TANHF  __builtin_tanhf
      #endif // __AVR__ or not __AVR__ stuff

      #define __BUILTIN_FABSL  __builtin_fabsl
      #define __BUILTIN_FMODL  __builtin_fmodl
      #define __BUILTIN_MODFL  __builtin_modfl
      #define __BUILTIN_FLOORL __builtin_floorl
      #define __BUILTIN_CEILL  __builtin_ceill
      #define __BUILTIN_FREXPL __builtin_frexpl
      #define __BUILTIN_LDEXPL __builtin_ldexpl
      #define __BUILTIN_SQRTL  __builtin_sqrtl
      #define __BUILTIN_SINL   __builtin_sinl
      #define __BUILTIN_COSL   __builtin_cosl
      #define __BUILTIN_TANL   __builtin_tanl
      #define __BUILTIN_ASINL  __builtin_asinl
      #define __BUILTIN_ACOSL  __builtin_acosl
      #define __BUILTIN_ATANL  __builtin_atanl
      #define __BUILTIN_ATAN2L __builtin_atan2l
      #define __BUILTIN_EXPL   __builtin_expl
      #define __BUILTIN_POWL   __builtin_powl
      #define __BUILTIN_LOGL   __builtin_logl
      #define __BUILTIN_LOG10L __builtin_log10l
      #define __BUILTIN_SINHL  __builtin_sinhl
      #define __BUILTIN_COSHL  __builtin_coshl
      #define __BUILTIN_TANHL  __builtin_tanhl

      inline float         abs  (float       x)                 { return __BUILTIN_FABSF (x); }
      inline double        abs  (double      x)                 { return __builtin_fabs  (x); }
      inline long double   abs  (long double x)                 { return __BUILTIN_FABSL (x); }

      inline float         fabs (float       x)                 { return __BUILTIN_FABSF (x); }
      using              ::fabs;                                // Using global fabs function.
      inline long double   fabs (long double x)                 { return __BUILTIN_FABSL (x); }

      inline float         fmod (float       x, float y)        { return __BUILTIN_FMODF (x, y); }
      using              ::fmod;                                // Using global fmod function.
      inline long double   fmod (long double x, long double y)  { return __BUILTIN_FMODL (x, y); }

      inline float         modf (float x,       float*       p) { return __BUILTIN_MODFF (x, p); }
      using              ::modf;                                // Using global modf function.
      inline long double   modf (long double x, long double* p) { return __BUILTIN_MODFL (x, p); }

      inline float         floor(float       x)                 { return __BUILTIN_FLOORF(x); }
      using              ::floor;                               // Using global floor function.
      inline long double   floor(long double x)                 { return __BUILTIN_FLOORL(x); }

      inline float         ceil (float       x)                 { return __BUILTIN_CEILF (x); }
      using              ::ceil;                                // Using global ceil function.
      inline long double   ceil (long double x)                 { return __BUILTIN_CEILL (x); }

      inline float         frexp(float x,       int* p)         { return __BUILTIN_FREXPF(x, p); }
      using              ::frexp;                               // Using global fresp function.
      inline long double   frexp(long double x, int* p)         { return __BUILTIN_FREXPL(x, p); }

      inline float         ldexp(float x,       int p)          { return __BUILTIN_LDEXPF(x, p); }
      using              ::ldexp;                               // Using global ldexp function.
      inline long double   ldexp(long double x, int p)          { return __BUILTIN_LDEXPL(x, p); }

      inline float         sqrt (float       x)                 { return __BUILTIN_SQRTF (x); }
      using              ::sqrt;                                // Using global function.
      inline long double   sqrt (long double x)                 { return __BUILTIN_SQRTL (x); }

      inline float         sin  (float       x)                 { return __BUILTIN_SINF  (x); }
      using              ::sin;                                 // Using global function.
      inline long double   sin  (long double x)                 { return __BUILTIN_SINL  (x); }

      inline float         cos  (float       x)                 { return __BUILTIN_COSF  (x); }
      using              ::cos;                                 // Using global sqrt function.
      inline long double   cos  (long double x)                 { return __BUILTIN_COSL  (x); }

      inline float         tan  (float       x)                 { return __BUILTIN_TANF  (x); }
      using              ::tan;                                 // Using global tan function.
      inline long double   tan  (long double x)                 { return __BUILTIN_TANL  (x); }

      inline float         asin (float       x)                 { return __BUILTIN_ASINF (x); }
      using              ::asin;                                // Using global asin function.
      inline long double   asin (long double x)                 { return __BUILTIN_ASINL (x); }

      inline float         acos (float       x)                 { return __BUILTIN_ACOSF (x); }
      using              ::acos;                                // Using global acos function.
      inline long double   acos (long double x)                 { return __BUILTIN_ACOSL (x); }

      inline float         atan (float       x)                 { return __BUILTIN_ATANF (x); }
      using              ::atan;                                // Using global atan function.
      inline long double   atan (long double x)                 { return __BUILTIN_ATANL (x); }

      inline float         atan2(float       y, float       x)  { return __BUILTIN_ATAN2F(y, x); }
      using              ::atan2;                               // Using global atan2 function.
      inline long double   atan2(long double y, long double x)  { return __BUILTIN_ATAN2L(y, x); }

      inline float         exp  (float       x)                 { return __BUILTIN_EXPF  (x); }
      using              ::exp;                                 // Using global exp function.
      inline long double   exp  (long double x)                 { return __BUILTIN_EXPL  (x); }

      inline float         pow  (float       x, float a)        { return __BUILTIN_POWF  (x, a); }
      using              ::pow;                                 // Using global pow function.
      inline long double   pow  (long double x, long double a)  { return __BUILTIN_POWL  (x, a); }

      inline float         log  (float       x)                 { return __BUILTIN_LOGF  (x); }
      using              ::log;                                 // Using global log function.
      inline long double   log  (long double x)                 { return __BUILTIN_LOGL  (x); }

      inline float         log10(float       x)                 { return __BUILTIN_LOG10F(x); }
      using              ::log10;                               // Using global log10 function.
      inline long double   log10(long double x)                 { return __BUILTIN_LOG10L(x); }

      inline float         sinh (float       x)                 { return __BUILTIN_SINHF (x); }
      using              ::sinh;                                // Using global sinh function.
      inline long double   sinh (long double x)                 { return __BUILTIN_SINHL (x); }

      inline float         cosh (float       x)                 { return __BUILTIN_COSHF (x); }
      using              ::cosh;                                // Using global cosh function.
      inline long double   cosh (long double x)                 { return __BUILTIN_COSHL (x); }

      inline float         tanh (float       x)                 { return __BUILTIN_TANHF (x); }
      using              ::tanh;                                // Using global tanh function.
      inline long double   tanh (long double x)                 { return __BUILTIN_TANHL (x); }

    #else

      inline float       abs(float x)       { return ::fabsf(x); }
      inline double      abs(double x)      { return ::fabs (x); }
      inline long double abs(long double x) { return ::fabsl(x); }

      using ::fabs;
      using ::fmod;
      using ::modf;
      using ::floor;
      using ::ceil;
      using ::frexp;
      using ::ldexp;
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

    #endif // __GNUC__ or not __GNUC__ stuff

    // Provide certain functions that are often missing from <math.h>.
    // Here, we patch some of these in an exemplary fashion for the
    // proposed std::float32_t.
    std::float32_t asinh (std::float32_t x);
    std::float32_t acosh (std::float32_t x);
    std::float32_t atanh (std::float32_t x);
    std::float32_t tgamma(std::float32_t x);
  }

#endif // _CMATH_IMPL_2010_02_23_H_
