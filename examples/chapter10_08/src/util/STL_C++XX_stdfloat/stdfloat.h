///////////////////////////////////////////////////////////////////////////////
// Copyright Christopher Kormanyos 2014.
// Copyright John Maddock 2014.
// Copyright Paul Bristow 2014.
// Distributed under the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)
//

// <stdfloat.h> implements floating-point typedefs having specified widths,
// as described in N1703 (proposed for C via JTC1/SC22/WG14).
// See: http://www.open-std.org/jtc1/sc22/wg14/www/docs/n1703.pdf

#ifndef STDFLOAT_2014_01_09_H_
  #define STDFLOAT_2014_01_09_H_

  #include <float.h>

  // This is the beginning of the preamble.

  // In this preamble, the preprocessor is used to query certain
  // preprocessor definitions from <float.h>. Based on the results
  // of these queries, an attempt is made to automatically detect
  // the presence of built-in floating-point types having specified
  // widths. These are *thought* to be conformant with IEEE-754,
  // whereby an unequivocal test based on numeric_limits is
  // provided in the C++ header <cstdfloat>.

  // In addition, macros that are used for initializing floating-point
  // literal values and some basic min/max values are defined.

  // First, we will pre-load certain preprocessor definitions
  // with a dummy value.

  #define STDFLOAT_MAXIMUM_AVAILABLE_WIDTH  0

  #define STDFLOAT_HAS_FLOAT16_NATIVE_TYPE  0
  #define STDFLOAT_HAS_FLOAT32_NATIVE_TYPE  0
  #define STDFLOAT_HAS_FLOAT64_NATIVE_TYPE  0
  #define STDFLOAT_HAS_FLOAT80_NATIVE_TYPE  0
  #define STDFLOAT_HAS_FLOAT128_NATIVE_TYPE 0

  // Ensure that the compiler has a radix-2 floating-point representation.
  #if (!defined(FLT_RADIX) || ((defined(FLT_RADIX) && (FLT_RADIX != 2))))
    #error The compiler does not support any of the radix-2 floating-point types required for <stdfloat.h>.
  #endif

  // Check if built-in float is equivalent to float16_t, float32_t, float64_t, float80_t, or float128_t.
  #if(defined(FLT_MANT_DIG) && defined(FLT_MAX_EXP))
    #if  ((FLT_MANT_DIG == 11) && (FLT_MAX_EXP == 16) && (STDFLOAT_HAS_FLOAT16_NATIVE_TYPE == 0))
      #define STDFLOAT_FLOAT16_NATIVE_TYPE float
      #undef  STDFLOAT_MAXIMUM_AVAILABLE_WIDTH
      #define STDFLOAT_MAXIMUM_AVAILABLE_WIDTH 16
      #undef  STDFLOAT_HAS_FLOAT16_NATIVE_TYPE
      #define STDFLOAT_HAS_FLOAT16_NATIVE_TYPE  1
      #define FLOAT16_C(x)  (x ## F)
      #define FLOAT_16_MIN  FLT_MIN
      #define FLOAT_16_MAX  FLT_MAX
    #elif((FLT_MANT_DIG == 24) && (FLT_MAX_EXP == 128) && (STDFLOAT_HAS_FLOAT32_NATIVE_TYPE == 0))
      #define STDFLOAT_FLOAT32_NATIVE_TYPE float
      #undef  STDFLOAT_MAXIMUM_AVAILABLE_WIDTH
      #define STDFLOAT_MAXIMUM_AVAILABLE_WIDTH 32
      #undef  STDFLOAT_HAS_FLOAT32_NATIVE_TYPE
      #define STDFLOAT_HAS_FLOAT32_NATIVE_TYPE  1
      #define FLOAT32_C(x)  (x ## F)
      #define FLOAT_32_MIN  FLT_MIN
      #define FLOAT_32_MAX  FLT_MAX
    #elif((FLT_MANT_DIG == 53) && (FLT_MAX_EXP == 1024) && (STDFLOAT_HAS_FLOAT64_NATIVE_TYPE == 0))
      #define STDFLOAT_FLOAT64_NATIVE_TYPE float
      #undef  STDFLOAT_MAXIMUM_AVAILABLE_WIDTH
      #define STDFLOAT_MAXIMUM_AVAILABLE_WIDTH 64
      #undef  STDFLOAT_HAS_FLOAT64_NATIVE_TYPE
      #define STDFLOAT_HAS_FLOAT64_NATIVE_TYPE  1
      #define FLOAT64_C(x)  (x ##F)
      #define FLOAT_64_MIN  FLT_MIN
      #define FLOAT_64_MAX  FLT_MAX
    #elif((FLT_MANT_DIG == 64) && (FLT_MAX_EXP == 16384) && (STDFLOAT_HAS_FLOAT80_NATIVE_TYPE == 0))
      #define STDFLOAT_FLOAT80_NATIVE_TYPE float
      #undef  STDFLOAT_MAXIMUM_AVAILABLE_WIDTH
      #define STDFLOAT_MAXIMUM_AVAILABLE_WIDTH 80
      #undef  STDFLOAT_HAS_FLOAT80_NATIVE_TYPE
      #define STDFLOAT_HAS_FLOAT80_NATIVE_TYPE  1
      #define FLOAT80_C(x)  (x ## F)
      #define FLOAT_80_MIN  FLT_MIN
      #define FLOAT_80_MAX  FLT_MAX
    #elif((FLT_MANT_DIG == 113) && (FLT_MAX_EXP == 16384) && (STDFLOAT_HAS_FLOAT128_NATIVE_TYPE == 0))
      #define STDFLOAT_FLOAT128_NATIVE_TYPE float
      #undef  STDFLOAT_MAXIMUM_AVAILABLE_WIDTH
      #define STDFLOAT_MAXIMUM_AVAILABLE_WIDTH 128
      #undef  STDFLOAT_HAS_FLOAT128_NATIVE_TYPE
      #define STDFLOAT_HAS_FLOAT128_NATIVE_TYPE  1
      #define FLOAT128_C(x)  (x ## F)
      #define FLOAT_128_MIN  FLT_MIN
      #define FLOAT_128_MAX  FLT_MAX
    #endif
  #endif

  // Check if built-in double is equivalent to float16_t, float32_t, float64_t, float80_t, or float128_t.
  #if(defined(DBL_MANT_DIG) && defined(DBL_MAX_EXP))
    #if  ((DBL_MANT_DIG == 11) && (DBL_MAX_EXP == 16) && (STDFLOAT_HAS_FLOAT16_NATIVE_TYPE == 0))
      #define STDFLOAT_FLOAT16_NATIVE_TYPE double
      #undef  STDFLOAT_MAXIMUM_AVAILABLE_WIDTH
      #define STDFLOAT_MAXIMUM_AVAILABLE_WIDTH 16
      #undef  STDFLOAT_HAS_FLOAT16_NATIVE_TYPE
      #define STDFLOAT_HAS_FLOAT16_NATIVE_TYPE  1
      #define FLOAT16_C(x)  (x)
      #define FLOAT_16_MIN  DBL_MIN
      #define FLOAT_16_MAX  DBL_MAX
    #elif((DBL_MANT_DIG == 24) && (DBL_MAX_EXP == 128) && (STDFLOAT_HAS_FLOAT32_NATIVE_TYPE == 0))
      #define STDFLOAT_FLOAT32_NATIVE_TYPE double
      #undef  STDFLOAT_MAXIMUM_AVAILABLE_WIDTH
      #define STDFLOAT_MAXIMUM_AVAILABLE_WIDTH 32
      #undef  STDFLOAT_HAS_FLOAT32_NATIVE_TYPE
      #define STDFLOAT_HAS_FLOAT32_NATIVE_TYPE  1
      #define FLOAT32_C(x)  (x)
      #define FLOAT_32_MIN  DBL_MIN
      #define FLOAT_32_MAX  DBL_MAX
    #elif((DBL_MANT_DIG == 53) && (DBL_MAX_EXP == 1024) && (STDFLOAT_HAS_FLOAT64_NATIVE_TYPE == 0))
      #define STDFLOAT_FLOAT64_NATIVE_TYPE double
      #undef  STDFLOAT_MAXIMUM_AVAILABLE_WIDTH
      #define STDFLOAT_MAXIMUM_AVAILABLE_WIDTH 64
      #undef  STDFLOAT_HAS_FLOAT64_NATIVE_TYPE
      #define STDFLOAT_HAS_FLOAT64_NATIVE_TYPE  1
      #define FLOAT64_C(x)  (x)
      #define FLOAT_64_MIN  DBL_MIN
      #define FLOAT_64_MAX  DBL_MAX
    #elif((DBL_MANT_DIG == 64) && (DBL_MAX_EXP == 16384) && (STDFLOAT_HAS_FLOAT80_NATIVE_TYPE == 0))
      #define STDFLOAT_FLOAT80_NATIVE_TYPE double
      #undef  STDFLOAT_MAXIMUM_AVAILABLE_WIDTH
      #define STDFLOAT_MAXIMUM_AVAILABLE_WIDTH 80
      #undef  STDFLOAT_HAS_FLOAT80_NATIVE_TYPE
      #define STDFLOAT_HAS_FLOAT80_NATIVE_TYPE  1
      #define FLOAT80_C(x)  (x)
      #define FLOAT_80_MIN  DBL_MIN
      #define FLOAT_80_MAX  DBL_MAX
    #elif((DBL_MANT_DIG == 113) && (DBL_MAX_EXP == 16384) && (STDFLOAT_HAS_FLOAT128_NATIVE_TYPE == 0))
      #define STDFLOAT_FLOAT128_NATIVE_TYPE double
      #undef  STDFLOAT_MAXIMUM_AVAILABLE_WIDTH
      #define STDFLOAT_MAXIMUM_AVAILABLE_WIDTH 128
      #undef  STDFLOAT_HAS_FLOAT128_NATIVE_TYPE
      #define STDFLOAT_HAS_FLOAT128_NATIVE_TYPE  1
      #define FLOAT128_C(x)  (x)
      #define FLOAT_128_MIN  DBL_MIN
      #define FLOAT_128_MAX  DBL_MAX
    #endif
  #endif

  // Check if built-in long double is equivalent to float16_t, float32_t, float64_t, float80_t, or float128_t.
  #if(defined(LDBL_MANT_DIG) && defined(LDBL_MAX_EXP))
    #if  ((LDBL_MANT_DIG == 11) && (LDBL_MAX_EXP == 16) && (STDFLOAT_HAS_FLOAT16_NATIVE_TYPE == 0))
      #define STDFLOAT_FLOAT16_NATIVE_TYPE long double
      #undef  STDFLOAT_MAXIMUM_AVAILABLE_WIDTH
      #define STDFLOAT_MAXIMUM_AVAILABLE_WIDTH 16
      #undef  STDFLOAT_HAS_FLOAT16_NATIVE_TYPE
      #define STDFLOAT_HAS_FLOAT16_NATIVE_TYPE  1
      #define FLOAT16_C(x)  (x ## L)
      #define FLOAT_16_MIN  LDBL_MIN
      #define FLOAT_16_MAX  LDBL_MAX
    #elif((LDBL_MANT_DIG == 24) && (LDBL_MAX_EXP == 128) && (STDFLOAT_HAS_FLOAT32_NATIVE_TYPE == 0))
      #define STDFLOAT_FLOAT32_NATIVE_TYPE long double
      #undef  STDFLOAT_MAXIMUM_AVAILABLE_WIDTH
      #define STDFLOAT_MAXIMUM_AVAILABLE_WIDTH 32
      #undef  STDFLOAT_HAS_FLOAT32_NATIVE_TYPE
      #define STDFLOAT_HAS_FLOAT32_NATIVE_TYPE  1
      #define FLOAT32_C(x)  (x ## L)
      #define FLOAT_32_MIN  LDBL_MIN
      #define FLOAT_32_MAX  LDBL_MAX
    #elif((LDBL_MANT_DIG == 53) && (LDBL_MAX_EXP == 1024) && (STDFLOAT_HAS_FLOAT64_NATIVE_TYPE == 0))
      #define STDFLOAT_FLOAT64_NATIVE_TYPE long double
      #undef  STDFLOAT_MAXIMUM_AVAILABLE_WIDTH
      #define STDFLOAT_MAXIMUM_AVAILABLE_WIDTH 64
      #undef  STDFLOAT_HAS_FLOAT64_NATIVE_TYPE
      #define STDFLOAT_HAS_FLOAT64_NATIVE_TYPE  1
      #define FLOAT64_C(x)  (x ## L)
      #define FLOAT_64_MIN  LDBL_MIN
      #define FLOAT_64_MAX  LDBL_MAX
    #elif((LDBL_MANT_DIG == 64) && (LDBL_MAX_EXP == 16384) && (STDFLOAT_HAS_FLOAT80_NATIVE_TYPE == 0))
      #define STDFLOAT_FLOAT80_NATIVE_TYPE long double
      #undef  STDFLOAT_MAXIMUM_AVAILABLE_WIDTH
      #define STDFLOAT_MAXIMUM_AVAILABLE_WIDTH 80
      #undef  STDFLOAT_HAS_FLOAT80_NATIVE_TYPE
      #define STDFLOAT_HAS_FLOAT80_NATIVE_TYPE  1
      #define FLOAT80_C(x)  (x ## L)
      #define FLOAT_80_MIN  LDBL_MIN
      #define FLOAT_80_MAX  LDBL_MAX
    #elif((LDBL_MANT_DIG == 113) && (LDBL_MAX_EXP == 16384) && (STDFLOAT_HAS_FLOAT128_NATIVE_TYPE == 0))
      #define STDFLOAT_FLOAT128_NATIVE_TYPE long double
      #undef  STDFLOAT_MAXIMUM_AVAILABLE_WIDTH
      #define STDFLOAT_MAXIMUM_AVAILABLE_WIDTH 128
      #undef  STDFLOAT_HAS_FLOAT128_NATIVE_TYPE
      #define STDFLOAT_HAS_FLOAT128_NATIVE_TYPE  1
      #define FLOAT128_C(x)  (x ## L)
      #define FLOAT_128_MIN  LDBL_MIN
      #define FLOAT_128_MAX  LDBL_MAX
    #endif
  #endif

  // This is the end of the preamble. Now we use the results
  // of the queries that have been obtained in the preamble.

  // Ensure that the compiler has any suitable floating-point type whatsoever.
  #if (   (STDFLOAT_HAS_FLOAT16_NATIVE_TYPE  == 0) \
       && (STDFLOAT_HAS_FLOAT32_NATIVE_TYPE  == 0) \
       && (STDFLOAT_HAS_FLOAT64_NATIVE_TYPE  == 0) \
       && (STDFLOAT_HAS_FLOAT80_NATIVE_TYPE  == 0) \
       && (STDFLOAT_HAS_FLOAT128_NATIVE_TYPE == 0))
    #error The compiler does not support any of the floating-point types required for <stdfloat.h>.
  #endif

  // Here, we define the floating-point typedefs having specified widths
  // based on the preprocessor analysis from the preamble above.

  // These type definitions are defined in the global namespace.

  // For simplicity, the least and fast types are type defined identically
  // as the corresponding fixed-width type. This behavior can, however,
  // be modified in order to be optimized for a given compiler implementation.

  // This section also contains the various min/max macros
  // for the least and fast types.

  #if(STDFLOAT_HAS_FLOAT16_NATIVE_TYPE == 1)
    typedef STDFLOAT_FLOAT16_NATIVE_TYPE  float16_t;
    typedef float16_t float_fast16_t;
    typedef float16_t float_least16_t;

    #define FLOAT_FAST16_MIN   FLOAT_16_MIN
    #define FLOAT_LEAST16_MIN  FLOAT_16_MIN
    #define FLOAT_FAST16_MAX   FLOAT_16_MAX
    #define FLOAT_LEAST16_MAX  FLOAT_16_MAX
  #endif

  #if(STDFLOAT_HAS_FLOAT32_NATIVE_TYPE == 1)
    typedef STDFLOAT_FLOAT32_NATIVE_TYPE  float32_t;
    typedef float32_t float_fast32_t;
    typedef float32_t float_least32_t;

    #define FLOAT_FAST32_MIN   FLOAT_32_MIN
    #define FLOAT_LEAST32_MIN  FLOAT_32_MIN
    #define FLOAT_FAST32_MAX   FLOAT_32_MAX
    #define FLOAT_LEAST32_MAX  FLOAT_32_MAX
  #endif

  #if(STDFLOAT_HAS_FLOAT64_NATIVE_TYPE == 1)
    typedef STDFLOAT_FLOAT64_NATIVE_TYPE  float64_t;
    typedef float64_t float_fast64_t;
    typedef float64_t float_least64_t;

    #define FLOAT_FAST64_MIN   FLOAT_64_MIN
    #define FLOAT_LEAST64_MIN  FLOAT_64_MIN
    #define FLOAT_FAST64_MAX   FLOAT_64_MAX
    #define FLOAT_LEAST64_MAX  FLOAT_64_MAX
  #endif

  #if(STDFLOAT_HAS_FLOAT80_NATIVE_TYPE == 1)
    typedef STDFLOAT_FLOAT80_NATIVE_TYPE  float80_t;
    typedef float80_t float_fast80_t;
    typedef float80_t float_least80_t;

    #define FLOAT_FAST80_MIN   FLOAT_80_MIN
    #define FLOAT_LEAST80_MIN  FLOAT_80_MIN
    #define FLOAT_FAST80_MAX   FLOAT_80_MAX
    #define FLOAT_LEAST80_MAX  FLOAT_80_MAX
  #endif

  #if(STDFLOAT_HAS_FLOAT128_NATIVE_TYPE == 1)
    typedef STDFLOAT_FLOAT128_NATIVE_TYPE float128_t;
    typedef float128_t float_fast128_t;
    typedef float128_t float_least128_t;

    #define FLOAT_FAST128_MIN   FLOAT_128_MIN
    #define FLOAT_LEAST128_MIN  FLOAT_128_MIN
    #define FLOAT_FAST128_MAX   FLOAT_128_MAX
    #define FLOAT_LEAST128_MAX  FLOAT_128_MAX
  #endif

  // The following section contains macros that are used for
  // initializing floating-point literal values and various
  // min and max macros for the floatmax types.

  #if  (STDFLOAT_MAXIMUM_AVAILABLE_WIDTH == 16)
    typedef float16_t     floatmax_t;
    #define FLOATMAX_C(x) FLOAT16_C(x)
    #define FLOATMAX_MIN  FLOAT_16_MIN
    #define FLOATMAX_MAX  FLOAT_16_MAX
  #elif(STDFLOAT_MAXIMUM_AVAILABLE_WIDTH == 32)
    typedef float32_t     floatmax_t;
    #define FLOATMAX_C(x) FLOAT32_C(x)
    #define FLOATMAX_MIN  FLOAT_32_MIN
    #define FLOATMAX_MAX  FLOAT_32_MAX
  #elif(STDFLOAT_MAXIMUM_AVAILABLE_WIDTH == 64)
    typedef float64_t     floatmax_t;
    #define FLOATMAX_C(x) FLOAT64_C(x)
    #define FLOATMAX_MIN  FLOAT_64_MIN
    #define FLOATMAX_MAX  FLOAT_64_MAX
  #elif(STDFLOAT_MAXIMUM_AVAILABLE_WIDTH == 80)
    typedef float80_t     floatmax_t;
    #define FLOATMAX_C(x) FLOAT80_C(x)
    #define FLOATMAX_MIN  FLOAT_80_MIN
    #define FLOATMAX_MAX  FLOAT_80_MAX
  #elif(STDFLOAT_MAXIMUM_AVAILABLE_WIDTH == 128)
    typedef float128_t    floatmax_t;
    #define FLOATMAX_C(x) FLOAT128_C(x)
    #define FLOATMAX_MIN  FLOAT_128_MIN
    #define FLOATMAX_MAX  FLOAT_128_MAX
  #else
    #error The maximum available floating-point width for <stdfloat.h> is undefined.
  #endif

  #undef STDFLOAT_MAXIMUM_AVAILABLE_WIDTH

#endif // STDFLOAT_2014_01_09_H_
