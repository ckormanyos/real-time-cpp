///////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2010 - 2019.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
///////////////////////////////////////////////////////////////////

#ifndef FAST_MATH_2018_12_01_H_
  #define FAST_MATH_2018_12_01_H_

  #include <cmath>
  #include <cstdint>

  #if defined(__GNUC__)
  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wstrict-aliasing"
  #endif

  typedef float fast_math_float32_t;

  static inline fast_math_float32_t fast_math_frexp (const fast_math_float32_t x, int_fast8_t* pn);
  static inline fast_math_float32_t fast_math_sqrt_q(const fast_math_float32_t x);
  static inline fast_math_float32_t fast_math_sqrt  (const fast_math_float32_t x);
  static inline fast_math_float32_t fast_math_log   (const fast_math_float32_t x);
  static inline fast_math_float32_t fast_math_exp   (const fast_math_float32_t x);

  static inline fast_math_float32_t fast_math_frexp(const fast_math_float32_t x, int_fast8_t* pn)
  {
    // Implement a highly optimized frexp function that
    // extracts the components of a 4-byte value stored
    // in IEEE754 single-precision float format.

    // Note that the cast in the following line breaks strict alignment rules.
    #if defined(__GNUC__)
    #pragma GCC diagnostic push
    #pragma GCC diagnostic ignored "-Wstrict-aliasing"
    #endif
    const uint32_t i = *(const uint32_t*) (&x);
    #if defined(__GNUC__)
    #pragma GCC diagnostic pop
    #endif

    const uint32_t raw_mantissa = (uint32_t) (i & (uint32_t) (((uint32_t) (1UL) << 23) - 1UL));
    const uint32_t raw_exponent = (uint32_t) ((uint32_t) (i >> 23) & (uint32_t) 0xFFUL);

    *pn = (int_fast8_t) ((int_fast16_t) raw_exponent - 127);

    const fast_math_float32_t m =
      1.0F + ((fast_math_float32_t) raw_mantissa / (fast_math_float32_t) 8388608.0F);

    {
      const bool is_negative = ((uint_fast8_t) (i >> 31) != 0U) ? true : false;

      return (is_negative ? -m : m);
    }
  }

  static inline fast_math_float32_t fast_math_sqrt_q(const fast_math_float32_t x)
  {
    #if defined(FAST_MATH_IMPLEMENT_SPECIALIZED_SQRT)

    // Compute the quotient (inverse) of sqrt(x),
    // in other words 1 / sqrt(x).

    // Use a variation of Quake3's "legendary" fast inverse sqrt.
    // See also: https://www.beyond3d.com/content/articles/8

    // Make the initial guess of the inverse square root.
    // The constant differs slightly from the original value.

    // Note that the cast in the following line breaks strict alignment rules.
    const uint32_t i =
      (uint32_t) 0X5F375A86ULL - (uint32_t) ((*(const uint32_t*) ((const void*) &x)) >> 1);

    // Note that the cast in the following line breaks strict alignment rules.
    fast_math_float32_t y = *(const fast_math_float32_t*) ((const void*) &i);

    // Perform the first Newton iteration.
    y = y * ((fast_math_float32_t) 1.5F - ((x * (fast_math_float32_t) 0.5F) * (y * y)));

    if(x > 512)
    {
      // Perform a second Newton iteration.
      // This is only used for "large" arguments.
      y = y * ((fast_math_float32_t) 1.5F - ((x * (fast_math_float32_t) 0.5F) * (y * y)));
    }

    return y;

    #else

    return (fast_math_float32_t) 1.0F / ::sqrtf(x);

    #endif // FAST_MATH_IMPLEMENT_SPECIALIZED_SQRT_Q
  }

  static inline fast_math_float32_t fast_math_sqrt(const fast_math_float32_t x)
  {
    #if defined(FAST_MATH_IMPLEMENT_SPECIALIZED_SQRT)
    return fast_math_sqrt_q(x) * x;
    #else
    return ::sqrtf(x);
    #endif
  }

  static inline fast_math_float32_t fast_math_log(const fast_math_float32_t x)
  {
    // Use argument reduction combined with
    // a simple approximation near a (=alpha) = 1.

    if(x < (fast_math_float32_t) 1.0F)
    {
      return -fast_math_log((fast_math_float32_t) 1.0F / x);
    }
    else
    {
      // Perform argument reduction.

      // log(x) = log(a * (2^n)) = [n log(2)] + log(a),
      //   where a (=alpha) can be extracted from frexp.

      int_fast8_t n;

      const fast_math_float32_t alpha = fast_math_frexp(x, &n);

      fast_math_float32_t log_alpha;

      if(x < (fast_math_float32_t) 1.01F)
      {
        // log(a) =~  (a - 1) - (a - 1)^2 / 2
        const fast_math_float32_t delta_one = x - (fast_math_float32_t) 1.0F;

        log_alpha = delta_one * ((fast_math_float32_t) 1.0F - (fast_math_float32_t) 0.5F * delta_one);
      }
      else
      {
        //             3(a^2 - 1)
        // log(a) =~  ------------, near a = 1
        //            1 + a(a + 4)

        log_alpha = 
            ((fast_math_float32_t) 3.0F * ((alpha * alpha) - (fast_math_float32_t) 1.0F))
          / ((fast_math_float32_t) 1.0F + (alpha * (alpha + (fast_math_float32_t) 4.0F)));
      }

      return fast_math_float32_t(n * (fast_math_float32_t) 0.6931471806F) + log_alpha;
    }
  }

  static inline fast_math_float32_t fast_math_exp(const fast_math_float32_t x)
  {
    // Use argument reduction combined with a
    // Pade approximation near a (=alpha) = 0.

    // Perform argument reduction.
    const int_fast8_t n = int_fast8_t(x * (fast_math_float32_t) 1.442695041F);

    const fast_math_float32_t alpha = x - ((fast_math_float32_t) 0.6931471806F * n);

    #if 0
    // Use a polynomial approximation.
    // exp(x) - 1 = approx.   0.99792060811054451 x
    //                      + 0.49948832659208106 x^2
    //                      + 0.17621882066892929 x^3
    //                      + 0.04348249331418186 x^4
    // in the range -1 < x <= +1. These coefficients
    // have been specifically derived for this work.

    const fast_math_float32_t series_of_alpha =
              (fast_math_float32_t) 1.0F
      + ((((  (fast_math_float32_t) 0.04348249331418186F  * alpha
            + (fast_math_float32_t) 0.17621882066892929F) * alpha
            + (fast_math_float32_t) 0.49948832659208106F) * alpha
            + (fast_math_float32_t) 0.99792060811054451F) * alpha);
    #endif

    // PadeApproximant[Exp[a], {a, 0, {2, 2}}]
    // FullSimplify[%]
    //
    //                   12a
    // e^a =~ 1.0 + -------------, near a = 0
    //              12 + a(a - 6)
    const fast_math_float32_t series_of_alpha =
            (fast_math_float32_t)  1.0F
      + (  ((fast_math_float32_t) 12.0F * alpha)
         / ((fast_math_float32_t) 12.0F + (alpha * (alpha - (fast_math_float32_t) 6.0F))));

    #if 0
    // PadeApproximant[Exp[a], {a, 0, {1, 1}}]]
    // FullSimplify[%]
    //          4
    // e^a =~ ----- - 1
    //        2 - a
    const fast_math_float32_t series_of_alpha =
      (   (fast_math_float32_t) 4.0F
       / ((fast_math_float32_t) 2.0F - alpha)) - (fast_math_float32_t) 1.0F;
    #endif

    return ((n >= 0) ? series_of_alpha * (fast_math_float32_t) (uint32_t(1UL) <<   n)
                     : series_of_alpha / (fast_math_float32_t) (uint32_t(1UL) << (-n)));
  }

  #if defined(__GNUC__)
  #pragma GCC diagnostic pop
  #endif

  #if defined(__cplusplus)
  namespace fast_math
  {
  #endif

  using float32_t = fast_math_float32_t;

  inline float32_t frexp (const float32_t x, int_fast8_t* pn) { return fast_math_frexp (x, pn); }
  inline float32_t sqrt_q(const float32_t x)                  { return fast_math_sqrt_q(x); }
  inline float32_t sqrt  (const float32_t x)                  { return fast_math_sqrt  (x); }
  inline float32_t log   (const float32_t x)                  { return fast_math_log   (x); }
  inline float32_t exp   (const float32_t x)                  { return fast_math_exp   (x); }

  #if defined(__cplusplus)
  } // namespace fast_math
  #endif

#endif // FAST_MATH_2018_12_01_H_
