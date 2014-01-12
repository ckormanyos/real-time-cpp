///////////////////////////////////////////////////////////////////////////////
// Copyright Christopher Kormanyos 2014.
// Copyright John Maddock 2014.
// Copyright Paul Bristow 2014.
// Distributed under the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)
//

// <stdfloat.h> implements floating-point typedefs having
// specified widths, as described in N1703 (proposed for JTC1/SC22/WG14 - C).
// See: http://www.open-std.org/jtc1/sc22/wg14/www/docs/n1703.pdf

#ifndef _STDFLOAT_2014_01_09_H_
  #define _STDFLOAT_2014_01_09_H_

  #include <float.h>

  // This is the beginning of the preamble.

  // In this preamble, the preprocessor is used to query certain
  // preprocessor definitions from <float.h>. Based on the results
  // of these queries, an attempt is made to automatically detect
  // the presence of built-in floating-point types having specified
  // widths. These are *thought* to be conformant with IEEE-754,
  // whereby an unequivocal test based on numeric_limits follows below.

  // First, we will pre-load some preprocessor definitions with
  // dummy values.
  #define STDFLOAT_MAXIMUM_AVAILABLE_WIDTH  0

  #define STDFLOAT_HAS_FLOAT32_NATIVE_TYPE  0
  #define STDFLOAT_HAS_FLOAT64_NATIVE_TYPE  0
  #define STDFLOAT_HAS_FLOAT80_NATIVE_TYPE  0
  #define STDFLOAT_HAS_FLOAT128_NATIVE_TYPE 0

  #define STDFLOAT_FLOAT32_NATIVE_TYPE  float
  #define STDFLOAT_FLOAT64_NATIVE_TYPE  float
  #define STDFLOAT_FLOAT80_NATIVE_TYPE  float
  #define STDFLOAT_FLOAT128_NATIVE_TYPE float

  #define FLOAT32_C(x)  (x ## F)
  #define FLOAT64_C(x)  (x ## F)
  #define FLOAT80_C(x)  (x ## F)
  #define FLOAT128_C(x) (x ## F)

  #if (!defined(FLT_RADIX) || ((defined(FLT_RADIX) && (FLT_RADIX != 2))))
    #error The compiler does not support radix-2 floating-point types for <stdfloat.h>.
  #endif

  // Check if built-in float is equivalent to float32_t, float64_t, float80_t, or float128_t.
  #if(defined(FLT_MANT_DIG) && defined(FLT_MAX_EXP))
    #if  ((FLT_MANT_DIG == 24) && (FLT_MAX_EXP == 128) && (STDFLOAT_HAS_FLOAT32_NATIVE_TYPE == 0))
      #undef  STDFLOAT_FLOAT32_NATIVE_TYPE
      #define STDFLOAT_FLOAT32_NATIVE_TYPE float
      #undef  STDFLOAT_MAXIMUM_AVAILABLE_WIDTH
      #define STDFLOAT_MAXIMUM_AVAILABLE_WIDTH 32
      #undef  STDFLOAT_HAS_FLOAT32_NATIVE_TYPE
      #define STDFLOAT_HAS_FLOAT32_NATIVE_TYPE  1
      #undef  FLOAT32_C
      #define FLOAT32_C(x)  (x ## F)
    #elif((FLT_MANT_DIG == 53) && (FLT_MAX_EXP == 1024) && (STDFLOAT_HAS_FLOAT64_NATIVE_TYPE == 0))
      #undef  STDFLOAT_FLOAT64_NATIVE_TYPE
      #define STDFLOAT_FLOAT64_NATIVE_TYPE float
      #undef  STDFLOAT_MAXIMUM_AVAILABLE_WIDTH
      #define STDFLOAT_MAXIMUM_AVAILABLE_WIDTH 64
      #undef  STDFLOAT_HAS_FLOAT64_NATIVE_TYPE
      #define STDFLOAT_HAS_FLOAT64_NATIVE_TYPE  1
      #undef  FLOAT64_C
      #define FLOAT64_C(x)  (x ## F)
    #elif((FLT_MANT_DIG == 63) && (FLT_MAX_EXP == 16384) && (STDFLOAT_HAS_FLOAT80_NATIVE_TYPE == 0))
      #undef  STDFLOAT_FLOAT80_NATIVE_TYPE
      #define STDFLOAT_FLOAT80_NATIVE_TYPE float
      #undef  STDFLOAT_MAXIMUM_AVAILABLE_WIDTH
      #define STDFLOAT_MAXIMUM_AVAILABLE_WIDTH 80
      #undef  STDFLOAT_HAS_FLOAT80_NATIVE_TYPE
      #define STDFLOAT_HAS_FLOAT80_NATIVE_TYPE  1
      #undef  FLOAT80_C
      #define FLOAT80_C(x)  (x ## F)
    #elif((FLT_MANT_DIG == 113) && (FLT_MAX_EXP == 16384) && (STDFLOAT_HAS_FLOAT128_NATIVE_TYPE == 0))
      #undef  STDFLOAT_FLOAT128_NATIVE_TYPE
      #define STDFLOAT_FLOAT128_NATIVE_TYPE float
      #undef  STDFLOAT_MAXIMUM_AVAILABLE_WIDTH
      #define STDFLOAT_MAXIMUM_AVAILABLE_WIDTH 128
      #undef  STDFLOAT_HAS_FLOAT128_NATIVE_TYPE
      #define STDFLOAT_HAS_FLOAT128_NATIVE_TYPE  1
      #undef  FLOAT128_C
      #define FLOAT128_C(x)  (x ## F)
    #endif
  #endif

  // Check if built-in double is equivalent to float32_t, float64_t, float80_t, or float128_t.
  #if(defined(DBL_MANT_DIG) && defined(DBL_MAX_EXP))
    #if  ((DBL_MANT_DIG == 24) && (DBL_MAX_EXP == 128) && (STDFLOAT_HAS_FLOAT32_NATIVE_TYPE == 0))
      #undef  STDFLOAT_FLOAT32_NATIVE_TYPE
      #define STDFLOAT_FLOAT32_NATIVE_TYPE double
      #undef  STDFLOAT_MAXIMUM_AVAILABLE_WIDTH
      #define STDFLOAT_MAXIMUM_AVAILABLE_WIDTH 32
      #undef  STDFLOAT_HAS_FLOAT32_NATIVE_TYPE
      #define STDFLOAT_HAS_FLOAT32_NATIVE_TYPE  1
      #undef  FLOAT32_C
      #define FLOAT32_C(x)  (x)
    #elif((DBL_MANT_DIG == 53) && (DBL_MAX_EXP == 1024) && (STDFLOAT_HAS_FLOAT64_NATIVE_TYPE == 0))
      #undef  STDFLOAT_FLOAT64_NATIVE_TYPE
      #define STDFLOAT_FLOAT64_NATIVE_TYPE double
      #undef  STDFLOAT_MAXIMUM_AVAILABLE_WIDTH
      #define STDFLOAT_MAXIMUM_AVAILABLE_WIDTH 64
      #undef  STDFLOAT_HAS_FLOAT64_NATIVE_TYPE
      #define STDFLOAT_HAS_FLOAT64_NATIVE_TYPE  1
      #undef  FLOAT64_C
      #define FLOAT64_C(x)  (x)
    #elif((DBL_MANT_DIG == 63) && (DBL_MAX_EXP == 16384) && (STDFLOAT_HAS_FLOAT80_NATIVE_TYPE == 0))
      #undef  STDFLOAT_FLOAT80_NATIVE_TYPE
      #define STDFLOAT_FLOAT80_NATIVE_TYPE double
      #undef  STDFLOAT_MAXIMUM_AVAILABLE_WIDTH
      #define STDFLOAT_MAXIMUM_AVAILABLE_WIDTH 80
      #undef  STDFLOAT_HAS_FLOAT80_NATIVE_TYPE
      #define STDFLOAT_HAS_FLOAT80_NATIVE_TYPE  1
      #undef  FLOAT80_C
      #define FLOAT80_C(x)  (x)
    #elif((DBL_MANT_DIG == 113) && (DBL_MAX_EXP == 16384) && (STDFLOAT_HAS_FLOAT128_NATIVE_TYPE == 0))
      #undef  STDFLOAT_FLOAT128_NATIVE_TYPE
      #define STDFLOAT_FLOAT128_NATIVE_TYPE double
      #undef  STDFLOAT_MAXIMUM_AVAILABLE_WIDTH
      #define STDFLOAT_MAXIMUM_AVAILABLE_WIDTH 128
      #undef  STDFLOAT_HAS_FLOAT128_NATIVE_TYPE
      #define STDFLOAT_HAS_FLOAT128_NATIVE_TYPE  1
      #undef  FLOAT128_C
      #define FLOAT128_C(x)  (x)
    #endif
  #endif

  // Check if built-in long double is equivalent to float32_t, float64_t, float80_t, or float128_t.
  #if(defined(LDBL_MANT_DIG) && defined(LDBL_MAX_EXP))
    #if  ((LDBL_MANT_DIG == 24) && (LDBL_MAX_EXP == 128) && (STDFLOAT_HAS_FLOAT32_NATIVE_TYPE == 0))
      #undef  STDFLOAT_FLOAT32_NATIVE_TYPE
      #define STDFLOAT_FLOAT32_NATIVE_TYPE long double
      #undef  STDFLOAT_MAXIMUM_AVAILABLE_WIDTH
      #define STDFLOAT_MAXIMUM_AVAILABLE_WIDTH 32
      #undef  STDFLOAT_HAS_FLOAT32_NATIVE_TYPE
      #define STDFLOAT_HAS_FLOAT32_NATIVE_TYPE  1
      #undef  FLOAT32_C
      #define FLOAT32_C(x)  (x ## L)
    #elif((LDBL_MANT_DIG == 53) && (LDBL_MAX_EXP == 1024) && (STDFLOAT_HAS_FLOAT64_NATIVE_TYPE == 0))
      #undef  STDFLOAT_FLOAT64_NATIVE_TYPE
      #define STDFLOAT_FLOAT64_NATIVE_TYPE long double
      #undef  STDFLOAT_MAXIMUM_AVAILABLE_WIDTH
      #define STDFLOAT_MAXIMUM_AVAILABLE_WIDTH 64
      #undef  STDFLOAT_HAS_FLOAT64_NATIVE_TYPE
      #define STDFLOAT_HAS_FLOAT64_NATIVE_TYPE  1
      #undef  FLOAT64_C
      #define FLOAT64_C(x)  (x ## L)
    #elif((LDBL_MANT_DIG == 63) && (LDBL_MAX_EXP == 16384) && (STDFLOAT_HAS_FLOAT80_NATIVE_TYPE == 0))
      #undef  STDFLOAT_FLOAT80_NATIVE_TYPE
      #define STDFLOAT_FLOAT80_NATIVE_TYPE long double
      #undef  STDFLOAT_MAXIMUM_AVAILABLE_WIDTH
      #define STDFLOAT_MAXIMUM_AVAILABLE_WIDTH 80
      #undef  STDFLOAT_HAS_FLOAT80_NATIVE_TYPE
      #define STDFLOAT_HAS_FLOAT80_NATIVE_TYPE  1
      #undef  FLOAT80_C
      #define FLOAT80_C(x)  (x ## L)
    #elif((LDBL_MANT_DIG == 113) && (LDBL_MAX_EXP == 16384) && (STDFLOAT_HAS_FLOAT128_NATIVE_TYPE == 0))
      #undef  STDFLOAT_FLOAT128_NATIVE_TYPE
      #define STDFLOAT_FLOAT128_NATIVE_TYPE long double
      #undef  STDFLOAT_MAXIMUM_AVAILABLE_WIDTH
      #define STDFLOAT_MAXIMUM_AVAILABLE_WIDTH 128
      #undef  STDFLOAT_HAS_FLOAT128_NATIVE_TYPE
      #define STDFLOAT_HAS_FLOAT128_NATIVE_TYPE  1
      #undef  FLOAT128_C
      #define FLOAT128_C(x)  (x ## L)
    #endif
  #endif

  #if (   (STDFLOAT_HAS_FLOAT32_NATIVE_TYPE  == 0) \
       && (STDFLOAT_HAS_FLOAT64_NATIVE_TYPE  == 0) \
       && (STDFLOAT_HAS_FLOAT80_NATIVE_TYPE  == 0) \
       && (STDFLOAT_HAS_FLOAT128_NATIVE_TYPE == 0))

    #undef STDFLOAT_MAXIMUM_AVAILABLE_WIDTH

    #undef STDFLOAT_HAS_FLOAT32_NATIVE_TYPE
    #undef STDFLOAT_HAS_FLOAT64_NATIVE_TYPE
    #undef STDFLOAT_HAS_FLOAT80_NATIVE_TYPE
    #undef STDFLOAT_HAS_FLOAT128_NATIVE_TYPE
    #undef STDFLOAT_FLOAT32_NATIVE_TYPE
    #undef STDFLOAT_FLOAT64_NATIVE_TYPE
    #undef STDFLOAT_FLOAT80_NATIVE_TYPE
    #undef STDFLOAT_FLOAT128_NATIVE_TYPE
    #undef FLOAT32_C
    #undef FLOAT64_C
    #undef FLOAT80_C
    #undef FLOAT128_C

    #error The compiler does not support any of the required floating-point types for <stdfloat.h>.
  #endif

  // This is the end of the preamble and the beginning of the type definitions.

  // Here, we define the floating-point typedefs having specified widths
  // based on the preprocessor analysis from the preamble above.

  // These type definitions are defined in the global namespace.

  // For simplicity, the least and fast types are type defined identically
  // as the corresponding fixed-width type. This behavior can, however,
  // be modified in order to be optimized for a given compiler implementation.

  #if(STDFLOAT_HAS_FLOAT32_NATIVE_TYPE == 1)
    typedef STDFLOAT_FLOAT32_NATIVE_TYPE  float32_t;
    typedef float32_t float_fast32_t;
    typedef float32_t float_least32_t;
  #endif

  #if(STDFLOAT_HAS_FLOAT64_NATIVE_TYPE == 1)
    typedef STDFLOAT_FLOAT64_NATIVE_TYPE  float64_t;
    typedef float64_t float_fast64_t;
    typedef float64_t float_least64_t;
  #endif

  #if(STDFLOAT_HAS_FLOAT80_NATIVE_TYPE == 1)
    typedef STDFLOAT_FLOAT80_NATIVE_TYPE  float80_t;
    typedef float80_t float_fast80_t;
    typedef float80_t float_least80_t;
  #endif

  #if(STDFLOAT_HAS_FLOAT128_NATIVE_TYPE == 1)
    typedef STDFLOAT_FLOAT128_NATIVE_TYPE float128_t;
    typedef float128_t float_fast128_t;
    typedef float128_t float_least128_t;
  #endif

  // The following section contains the first group of macros that
  // are used for initializing floating-point literal values.
  // The types of the three forms (fixed-width, least-width, and fast-width)
  // in bit-counts of 32, 64, 80, 128 are handled.

  #if(STDFLOAT_HAS_FLOAT32_NATIVE_TYPE == 1)
    #define FLOAT_32_MIN       FLOAT32_C(1.175494351e-38)
    #define FLOAT_FAST32_MIN   FLOAT_32_MIN
    #define FLOAT_LEAST32_MIN  FLOAT_32_MIN
    #define FLOAT_32_MAX       FLOAT32_C(3.402823466e+38)
    #define FLOAT_FAST32_MAX   FLOAT_32_MAX
    #define FLOAT_LEAST32_MAX  FLOAT_32_MAX
  #endif

  #if(STDFLOAT_HAS_FLOAT64_NATIVE_TYPE == 1)
    #define FLOAT_64_MIN       FLOAT64_C(2.2250738585072014e-308)
    #define FLOAT_FAST64_MIN   FLOAT_64_MIN
    #define FLOAT_LEAST64_MIN  FLOAT_64_MIN
    #define FLOAT_64_MAX       FLOAT64_C(1.7976931348623158e+308)
    #define FLOAT_FAST64_MAX   FLOAT_64_MAX
    #define FLOAT_LEAST64_MAX  FLOAT_64_MAX
  #endif

  #if(STDFLOAT_HAS_FLOAT80_NATIVE_TYPE == 1)
    #define FLOAT_80_MIN       FLOAT80_C(3.3621031431120935062627E-4932)
    #define FLOAT_FAST80_MIN   FLOAT_80_MIN
    #define FLOAT_LEAST80_MIN  FLOAT_80_MIN
    #define FLOAT_80_MAX       FLOAT80_C(1.1897314953572317650213E+4932)
    #define FLOAT_FAST80_MAX   FLOAT_80_MAX
    #define FLOAT_LEAST80_MAX  FLOAT_80_MAX
  #endif

  #if(STDFLOAT_HAS_FLOAT128_NATIVE_TYPE == 1)
    #define FLOAT_128_MIN       FLOAT128_C(3.362103143112093506262677817321752603E-4932)
    #define FLOAT_FAST128_MIN   FLOAT_128_MIN
    #define FLOAT_LEAST128_MIN  FLOAT_128_MIN
    #define FLOAT_128_MAX       FLOAT128_C(1.189731495357231765085759326628007016E+4932)
    #define FLOAT_FAST128_MAX   FLOAT_128_MAX
    #define FLOAT_LEAST128_MAX  FLOAT_128_MAX
  #endif

  // The following section contains the second group of macros that
  // are used for initializing floating-point literal values.
  // The types of the max-form are handled.

  // In addition, all unused pre-processor definitions previously
  // initialized with dummy values are herewith un-defined.

  #if  (STDFLOAT_MAXIMUM_AVAILABLE_WIDTH == 32)
    typedef float32_t     floatmax_t;
    #define FLOATMAX_C(x) FLOAT32_C(x)
    #define FLOATMAX_MIN  FLOAT_32_MIN
    #define FLOATMAX_MAX  FLOAT_32_MAX

    #undef BOOST_CSTDFLOAT_HAS_FLOAT64_NATIVE_TYPE
    #undef BOOST_CSTDFLOAT_HAS_FLOAT80_NATIVE_TYPE
    #undef BOOST_CSTDFLOAT_HAS_FLOAT128_NATIVE_TYPE
    #undef BOOST_CSTDFLOAT_FLOAT64_NATIVE_TYPE
    #undef BOOST_CSTDFLOAT_FLOAT80_NATIVE_TYPE
    #undef BOOST_CSTDFLOAT_FLOAT128_NATIVE_TYPE
    #undef BOOST_FLOAT64_C
    #undef BOOST_FLOAT80_C
    #undef BOOST_FLOAT128_C
  #elif(STDFLOAT_MAXIMUM_AVAILABLE_WIDTH == 64)
    typedef float64_t     floatmax_t;
    #define FLOATMAX_C(x) FLOAT64_C(x)
    #define FLOATMAX_MIN  FLOAT_64_MIN
    #define FLOATMAX_MAX  FLOAT_64_MAX

    #undef BOOST_CSTDFLOAT_HAS_FLOAT80_NATIVE_TYPE
    #undef BOOST_CSTDFLOAT_HAS_FLOAT128_NATIVE_TYPE
    #undef BOOST_CSTDFLOAT_FLOAT80_NATIVE_TYPE
    #undef BOOST_CSTDFLOAT_FLOAT128_NATIVE_TYPE
    #undef BOOST_FLOAT80_C
    #undef BOOST_FLOAT128_C
  #elif(STDFLOAT_MAXIMUM_AVAILABLE_WIDTH == 80)
    typedef float80_t     floatmax_t;
    #define FLOATMAX_C(x) FLOAT80_C(x)
    #define FLOATMAX_MIN  FLOAT_80_MIN
    #define FLOATMAX_MAX  FLOAT_80_MAX

    #undef BOOST_CSTDFLOAT_HAS_FLOAT128_NATIVE_TYPE
    #undef BOOST_CSTDFLOAT_FLOAT128_NATIVE_TYPE
    #undef BOOST_FLOAT128_C
  #elif(STDFLOAT_MAXIMUM_AVAILABLE_WIDTH == 128)
    typedef float128_t    floatmax_t;
    #define FLOATMAX_C(x) FLOAT128_C(x)
    #define FLOATMAX_MIN  FLOAT_128_MIN
    #define FLOATMAX_MAX  FLOAT_128_MAX
  #else
    #error The maximum available floating-point width for <stdfloat.h> is undefined.
  #endif

#endif // _STDFLOAT_2014_01_09_H_
