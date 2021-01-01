#include <math.h>

extern "C"
{
  int atexit (void (*)(void)) noexcept;

  int atexit (void (*)(void))
  {
    return 0;
  }
}

#define __BUILTIN_ISNANF __builtin_isnanf
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

#define __BUILTIN_ISNAN  __builtin_isnan
#define __BUILTIN_FABS   __builtin_fabs
#define __BUILTIN_FMOD   __builtin_fmod
#define __BUILTIN_MODF   __builtin_modf
#define __BUILTIN_FLOOR  __builtin_floor
#define __BUILTIN_CEIL   __builtin_ceil
#define __BUILTIN_FREXP  __builtin_frexp
#define __BUILTIN_LDEXP  __builtin_ldexp
#define __BUILTIN_SQRT   __builtin_sqrt
#define __BUILTIN_SIN    __builtin_sin
#define __BUILTIN_COS    __builtin_cos
#define __BUILTIN_TAN    __builtin_tan
#define __BUILTIN_ASIN   __builtin_asin
#define __BUILTIN_ACOS   __builtin_acos
#define __BUILTIN_ATAN   __builtin_atan
#define __BUILTIN_ATAN2  __builtin_atan2
#define __BUILTIN_EXP    __builtin_exp
#define __BUILTIN_POW    __builtin_pow
#define __BUILTIN_LOG    __builtin_log
#define __BUILTIN_LOG10  __builtin_log10
#define __BUILTIN_SINH   __builtin_sinh
#define __BUILTIN_COSH   __builtin_cosh
#define __BUILTIN_TANH   __builtin_tanh

#define __BUILTIN_ISNANL __builtin_isnanl
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

extern "C"
{
  float         fabsf (float       x)                 { return __BUILTIN_FABSF (x); }
  double        fabs  (double      x)                 { return __BUILTIN_FABS  (x); }
  long double   fabsl (long double x)                 { return __BUILTIN_FABSL (x); }
  float         fmodf (float       x, float       y)  { return __BUILTIN_FMODF (x, y); }
  double        fmod  (double      x, double      y)  { return __BUILTIN_FMOD  (x, y); }
  long double   fmodl (long double x, long double y)  { return __BUILTIN_FMODL (x, y); }
  float         modff (float       x, float*       p) { return __BUILTIN_MODFF (x, p); }
  double        modf  (double      x, double*      p) { return __BUILTIN_MODF  (x, p); }
  long double   modfl (long double x, long double* p) { return __BUILTIN_MODFL (x, p); }
  float         floorf(float       x)                 { return __BUILTIN_FLOORF(x); }
  double        floor (double      x)                 { return __BUILTIN_FLOOR (x); }
  long double   floorl(long double x)                 { return __BUILTIN_FLOORL(x); }
  float         ceilf (float       x)                 { return __BUILTIN_CEILF (x); }
  double        ceil  (double      x)                 { return __BUILTIN_CEIL  (x); }
  long double   ceill (long double x)                 { return __BUILTIN_CEILL (x); }
  float         frexpf(float       x, int* p)         { return __BUILTIN_FREXPF(x, p); }
  double        frexp (double      x, int* p)         { return __BUILTIN_FREXP (x, p); }
  long double   frexpl(long double x, int* p)         { return __BUILTIN_FREXPL(x, p); }
  float         ldexpf(float       x, int p)          { return __BUILTIN_LDEXPF(x, p); }
  double        ldexp (double      x, int p)          { return __BUILTIN_LDEXP (x, p); }
  long double   ldexpl(long double x, int p)          { return __BUILTIN_LDEXPL(x, p); }
  float         sqrtf (float       x)                 { return __BUILTIN_SQRTF (x); }
  double        sqrt  (double      x)                 { return __BUILTIN_SQRT  (x); }
  long double   sqrtl (long double x)                 { return __BUILTIN_SQRTL (x); }
  float         sinf  (float       x)                 { return __BUILTIN_SINF  (x); }
  double        sin   (double      x)                 { return __BUILTIN_SIN   (x); }
  long double   sinl  (long double x)                 { return __BUILTIN_SINL  (x); }
  float         cosf  (float       x)                 { return __BUILTIN_COSF  (x); }
  double        cos   (double      x)                 { return __BUILTIN_COS   (x); }
  long double   cosl  (long double x)                 { return __BUILTIN_COSL  (x); }
  float         tanf  (float       x)                 { return __BUILTIN_TANF  (x); }
  double        tan   (double      x)                 { return __BUILTIN_TAN   (x); }
  long double   tanl  (long double x)                 { return __BUILTIN_TANL  (x); }
  float         asinf (float       x)                 { return __BUILTIN_ASINF (x); }
  double        asin  (double      x)                 { return __BUILTIN_ASIN  (x); }
  long double   asinl (long double x)                 { return __BUILTIN_ASINL (x); }
  float         acosf (float       x)                 { return __BUILTIN_ACOSF (x); }
  double        acos  (double      x)                 { return __BUILTIN_ACOS  (x); }
  long double   acosl (long double x)                 { return __BUILTIN_ACOSL (x); }
  float         atanf (float       x)                 { return __BUILTIN_ATANF (x); }
  double        atan  (double      x)                 { return __BUILTIN_ATAN  (x); }
  long double   atanl (long double x)                 { return __BUILTIN_ATANL (x); }
  float         atan2f(float       y, float       x)  { return __BUILTIN_ATAN2F(y, x); }
  double        atan2 (double      y, double      x)  { return __BUILTIN_ATAN2 (y, x); }
  long double   atan2l(long double y, long double x)  { return __BUILTIN_ATAN2L(y, x); }
  float         expf  (float       x)                 { return __BUILTIN_EXPF  (x); }
  double        exp   (double      x)                 { return __BUILTIN_EXPF  (x); }
  long double   expl  (long double x)                 { return __BUILTIN_EXPL  (x); }
  float         powf  (float       x, float       a)  { return __BUILTIN_POWF  (x, a); }
  double        pow   (double      x, double      a)  { return __BUILTIN_POW   (x, a); }
  long double   powl  (long double x, long double a)  { return __BUILTIN_POWL  (x, a); }
  float         logf  (float       x)                 { return __BUILTIN_LOGF  (x); }
  double        log   (double      x)                 { return __BUILTIN_LOG   (x); }
  long double   logl  (long double x)                 { return __BUILTIN_LOGL  (x); }
  float         log10f(float       x)                 { return __BUILTIN_LOG10F(x); }
  double        log10 (double      x)                 { return __BUILTIN_LOG10 (x); }
  long double   log10l(long double x)                 { return __BUILTIN_LOG10L(x); }
  float         sinhf (float       x)                 { return __BUILTIN_SINHF (x); }
  double        sinh  (double      x)                 { return __BUILTIN_SINH  (x); }
  long double   sinhl (long double x)                 { return __BUILTIN_SINHL (x); }
  float         coshf (float       x)                 { return __BUILTIN_COSHF (x); }
  double        cosh  (double      x)                 { return __BUILTIN_COSH  (x); }
  long double   coshl (long double x)                 { return __BUILTIN_COSHL (x); }
  float         tanhf (float       x)                 { return __BUILTIN_TANHF (x); }
  double        tanh  (double      x)                 { return __BUILTIN_TANH  (x); }
  long double   tanhl (long double x)                 { return __BUILTIN_TANHL (x); }
}
