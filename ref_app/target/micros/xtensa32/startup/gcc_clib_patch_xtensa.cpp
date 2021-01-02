///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2020 - 2021.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <cmath>

extern "C"
{
  int atexit (void (*)(void)) noexcept;

  int atexit (void (*)(void))
  {
    return 0;
  }
}

extern "C"
{
  float         fabsf (float       x)                 { return __builtin_fabsf (x); }
  long double   fabsl (long double x)                 { return __builtin_fabsl (x); }
  float         fmodf (float       x, float       y)  { return __builtin_fmodf (x, y); }
  long double   fmodl (long double x, long double y)  { return __builtin_fmodl (x, y); }
  float         modff (float       x, float*       p) { return __builtin_modff (x, p); }
  long double   modfl (long double x, long double* p) { return __builtin_modfl (x, p); }
  float         floorf(float       x)                 { return __builtin_floorf(x); }
  long double   floorl(long double x)                 { return __builtin_floorl(x); }
  float         ceilf (float       x)                 { return __builtin_ceilf (x); }
  long double   ceill (long double x)                 { return __builtin_ceill (x); }
  float         frexpf(float       x, int* p)         { return __builtin_frexpf(x, p); }
  long double   frexpl(long double x, int* p)         { return __builtin_frexpl(x, p); }
  float         ldexpf(float       x, int p)          { return __builtin_ldexpf(x, p); }
  long double   ldexpl(long double x, int p)          { return __builtin_ldexpl(x, p); }
  float         sqrtf (float       x)                 { return __builtin_sqrtf (x); }
  long double   sqrtl (long double x)                 { return __builtin_sqrtl (x); }
  float         sinf  (float       x)                 { return __builtin_sinf  (x); }
  long double   sinl  (long double x)                 { return __builtin_sinl  (x); }
  float         cosf  (float       x)                 { return __builtin_cosf  (x); }
  long double   cosl  (long double x)                 { return __builtin_cosl  (x); }
  float         tanf  (float       x)                 { return __builtin_tanf  (x); }
  long double   tanl  (long double x)                 { return __builtin_tanl  (x); }
  float         asinf (float       x)                 { return __builtin_asinf (x); }
  long double   asinl (long double x)                 { return __builtin_asinl (x); }
  float         acosf (float       x)                 { return __builtin_acosf (x); }
  long double   acosl (long double x)                 { return __builtin_acosl (x); }
  float         atanf (float       x)                 { return __builtin_atanf (x); }
  long double   atanl (long double x)                 { return __builtin_atanl (x); }
  float         atan2f(float       y, float       x)  { return __builtin_atan2f(y, x); }
  long double   atan2l(long double y, long double x)  { return __builtin_atan2l(y, x); }
  float         expf  (float       x)                 { return __builtin_expf  (x); }
  long double   expl  (long double x)                 { return __builtin_expl  (x); }
  float         powf  (float       x, float       a)  { return __builtin_powf  (x, a); }
  long double   powl  (long double x, long double a)  { return __builtin_powl  (x, a); }
  float         logf  (float       x)                 { return __builtin_logf  (x); }
  long double   logl  (long double x)                 { return __builtin_logl  (x); }
  float         log10f(float       x)                 { return __builtin_log10f(x); }
  long double   log10l(long double x)                 { return __builtin_log10l(x); }
  float         sinhf (float       x)                 { return __builtin_sinhf (x); }
  long double   sinhl (long double x)                 { return __builtin_sinhl (x); }
  float         coshf (float       x)                 { return __builtin_coshf (x); }
  long double   coshl (long double x)                 { return __builtin_coshl (x); }
  float         tanhf (float       x)                 { return __builtin_tanhf (x); }
  long double   tanhl (long double x)                 { return __builtin_tanhl (x); }
}
