#include <cstdint>
#include <limits>

#define EXTERN_C extern "C"

#if defined(_MSC_VER)

#define STD_CLIB_LOCAL_WEAK_USED_NOINLINE

#define SINF  sinf_vc
#define COSF  cosf_vc
#define EXPF  expf_vc
#define SINHF sinhf_vc
#define COSHF coshf_vc

#else

#define STD_CLIB_LOCAL_WEAK_USED_NOINLINE __attribute__((weak,used,noinline))

#define SINF  sinf
#define COSF  cosf
#define EXPF  expf
#define SINHF sinhf
#define COSHF coshf

#endif

EXTERN_C float SINF (float) STD_CLIB_LOCAL_WEAK_USED_NOINLINE;
EXTERN_C float COSF (float) STD_CLIB_LOCAL_WEAK_USED_NOINLINE;
EXTERN_C float EXPF (float) STD_CLIB_LOCAL_WEAK_USED_NOINLINE;
EXTERN_C float SINHF(float) STD_CLIB_LOCAL_WEAK_USED_NOINLINE;
EXTERN_C float COSHF(float) STD_CLIB_LOCAL_WEAK_USED_NOINLINE;

EXTERN_C int   __ltsf2    (float, float) STD_CLIB_LOCAL_WEAK_USED_NOINLINE;
EXTERN_C int   __gtsf2    (float, float) STD_CLIB_LOCAL_WEAK_USED_NOINLINE;
EXTERN_C float __addsf3   (float, float) STD_CLIB_LOCAL_WEAK_USED_NOINLINE;
EXTERN_C float __subsf3   (float, float) STD_CLIB_LOCAL_WEAK_USED_NOINLINE;
EXTERN_C float __mulsf3   (float, float) STD_CLIB_LOCAL_WEAK_USED_NOINLINE;
EXTERN_C float __divsf3   (float, float) STD_CLIB_LOCAL_WEAK_USED_NOINLINE;
EXTERN_C float __floatsisf(int)          STD_CLIB_LOCAL_WEAK_USED_NOINLINE;
EXTERN_C int   __fixsfsi  (float)        STD_CLIB_LOCAL_WEAK_USED_NOINLINE;

namespace local
{
  int   cmpf  (const float a, const float b);
  int   to_int(const float a);
  float fabsf (float x);
  float floorf(float x);
  float expm1f(float x);
  float pown  (float b, int p);

  struct ieee754_float32
  {
  public:
    // See also:
    // https://babbage.cs.qc.cuny.edu/IEEE-754.old/Decimal.html

    // See also:
    // https://www.exploringbinary.com/floating-point-converter
    // Select single, doubloe or both. Check, for instance,
    // "Raw binary" and "Raw hexadecimal" and stat converting
    // decimal float numbers

    //   Bit 31    |        Bits 30 - 23          |  Bits 22 - 0
    //   Sign Bit  |        Exponent Field        |  Significand
    //   0/1: +/-  |  0Bxxxxxxx - 127 = exponent  |     binary

    ieee754_float32(const float a)
      : my_neg     (get_raw_neg______from_float(a)),
        my_mantissa(get_raw_mantissa_from_float(a)),
        my_expon   (get_raw_expon____from_float(a)) { }

    std::uint32_t mantissa() const
    {
      return my_mantissa;
    }

    std::int8_t expon() const
    {
      return my_expon;
    }

    bool iszero() const
    {
      return ((my_expon == 0) && (my_mantissa == UINT32_C(0x00800000)));
    }

    bool isneg() const
    {
      return my_neg;
    }

  private:
    const bool          my_neg;
    const std::uint32_t my_mantissa;
    const std::int8_t   my_expon;

    static std::uint32_t get_raw_uint32_from_float(const float a)
    {
      #if defined(__GNUC__)
      #pragma GCC diagnostic push
      #pragma GCC diagnostic ignored "-Wstrict-aliasing"
      #endif
      const std::uint32_t raw32 = *reinterpret_cast<const std::uint32_t*>(&a);
      #if defined(__GNUC__)
      #pragma GCC diagnostic pop
      #endif

      return raw32;
    }

    static bool get_raw_neg______from_float(const float a)
    {
      const std::uint32_t raw32 = get_raw_uint32_from_float(a);

      return (static_cast<std::uint32_t>(raw32 & UINT32_C(0x80000000)) != UINT32_C(0));
    }

    static std::uint32_t get_raw_mantissa_from_float(const float a)
    {
      const std::uint32_t raw32 = get_raw_uint32_from_float(a);

      const std::uint32_t raw_mantissa =
        static_cast<std::uint32_t>(static_cast<std::uint32_t>(raw32 & UINT32_C(0x00FFFFFF)) | UINT32_C(0x00800000));

      return raw_mantissa;
    }

    static std::int8_t get_raw_expon____from_float(const float a)
    {
      std::uint32_t raw32 = get_raw_uint32_from_float(a);

      const bool expon_is_neg = (static_cast<std::uint32_t>(raw32 & UINT32_C(0x40000000)) != UINT32_C(0));

      if(expon_is_neg)
      {
        raw32 |= UINT32_C(0x80000000);
      }

      const std::int8_t sraw8 = static_cast<std::int8_t>(static_cast<std::int32_t>(INT32_C(127) - static_cast<std::int32_t>(static_cast<std::int8_t>(raw32 >> 23U))));

      return sraw8;
    }

  };

  int cmpf(const float a, const float b)
  {
    const ieee754_float32 fa(a);
    const ieee754_float32 fb(b);

    const bool b_is_zero = fb.iszero();

    // Now handle all *finite* cases.
    if(fa.iszero())
    {
      // The value of *this is zero and v is either zero or non-zero.
      return (b_is_zero ? 0 : (fb.isneg() ? 1 : -1));
    }
    else if(b_is_zero)
    {
      // The value of v is zero and *this is non-zero.
      return (fa.isneg() ? -1 : 1);
    }
    else
    {
      // Both *this and v are non-zero.

      if(fa.isneg() != fb.isneg())
      {
        // The signs are different.
        return (fa.isneg() ? -1 : 1);
      }
      else if(fa.expon() != fb.expon())
      {
        // The signs are the same and the exponents are different.
        const int val_exp_compare = ((fa.expon() < fb.expon()) ? -1 : 1);

        return (fa.isneg() ? val_exp_compare : -val_exp_compare);
      }
      else
      {
        // The signs are the same and the exponents are the same.
        // We need to manually compare the mantissa.

        int val_cmp_data;

        if(fa.mantissa() < fb.mantissa())
        {
          val_cmp_data = -1;
        }
        else if(fb.mantissa() < fa.mantissa())
        {
          val_cmp_data = 1;
        }
        else
        {
          val_cmp_data = 0;
        }

        return ((fa.isneg() == false) ? val_cmp_data : -val_cmp_data);
      }
    }
  }

  int to_int(const float a)
  {
    const ieee754_float32 fa(a);

    std::uint32_t un_result;

    if(fa.iszero())
    {
      un_result = UINT32_C(0);
    }
    else
    {
      const unsigned right_shitf_amount = static_cast<unsigned>((23 - 1) + static_cast<int>(fa.expon()));

      un_result = fa.mantissa() >> right_shitf_amount;

      if((un_result & UINT32_C(1)) != 0U)
      {
        un_result |= UINT32_C(2);
      }

      un_result >>= 1U;
    }

    return ((fa.isneg() == false) ?  static_cast<int>(un_result)
                                  : -static_cast<int>(un_result));
  }

  float fabsf(float x)
  {
    return ((x < 0.0F) ? -x : x);
  }

  float floorf(float x)
  {
    float result = x;

    if(result < 0.0F)
    {
      result -= 1.0F;
    }

    const int nr = local::to_int(result);

    return static_cast<float>(nr);
  }

  float expm1f(float x)
  {
    // Taken from:
    // Coefficient Table 1802 page 179 (description on page 104),
    // J.F. Hart, "Computer Approximations", Krieger Press (1978)

    const float x2 = (x * x);

    const float px2 = ((       0.3333206802628149222225154E-1F
                        * x2 + 0.1400022777377555304975874306E2F)
                        * x2 + 0.5040127554054843027460596926E3F);

    const float qx2 = ((       1.0F
                        * x2 + 0.1120025814484651564577585494E3F)
                        * x2 + 0.1008025510810968605492139581E4F);

    const float numerator   =  (2.0F * x) * px2;

    const float denominator = qx2 - (x * px2);

    const float result = numerator / denominator;

    return result;
  }

  float pown(float b, int p)
  {
    // Calculate (b ^ p).
    float result;

    if     (p  < 0) { return 1.0F / pown(b, -p); }
    else if(p == 0) { result = 1.0F; }
    else if(p == 1) { result = b; }
    else if(p == 2) { result = b; result *= b; }
    else
    {
      result = 1.0F;

      float y(b);

      for(unsigned int pu = static_cast<unsigned int>(p) ; pu != 0U; pu >>= 1U)
      {
        if((pu & 1U) != 0U)
        {
          result *= y;
        }

        y *= y;
      }
    }

    return result;
  }
}

EXTERN_C int __ltsf2(float a, float b)
{
  const int cmp_result = local::cmpf(a, b);

  return ((cmp_result >= 0) ? 1 : -1);
}

EXTERN_C int __gtsf2(float a, float b)
{
  const int cmp_result = local::cmpf(a, b);

  return ((cmp_result <= 0) ? 1 : -1);
}

EXTERN_C float __addsf3(float a, float b) { const float r = a + b; return r; }
EXTERN_C float __subsf3(float a, float b) { const float r = a - b; return r; }
EXTERN_C float __mulsf3(float a, float b) { const float r = a * b; return r; }
EXTERN_C float __divsf3(float a, float b) { const float r = a / b; return r; }

EXTERN_C float __floatsisf(int i)
{
  return static_cast<float>(i);
}

EXTERN_C int __fixsfsi(float a)
{
  return local::to_int(a);
}

EXTERN_C float SINF(float x)
{
  // Handle reflection for negative arguments.
  if(x < 0.0F)
  {
    return -SINF(-x);
  }

  constexpr float pi      = 3.1415926535897932384626433832795028841971693993751F;
  constexpr float pi_half = 1.5707963267948966192313216916397514420985846996876F;

  int n = 0;

  // Reduce the argument to the range 0 <= x <= +pi/2.
  if(x > pi)
  {
    n = local::to_int(x / pi);

    x -= (static_cast<float>(n) * pi);
  }

  float result;

  if(x > pi_half)
  {
    result = SINF(pi - x);
  }
  else
  {
    if(!(x < pi_half))
    {
      result = 1.0F;
    }
    else
    {
      // Use a polynomial approximation.
      // sin(x) = approx. + 0.9999999815561047 x
      //                  - 0.1666665066192447 x^3
      //                  + 0.0083329484215251 x^5
      //                  - 0.0001980373563403 x^7
      //                  + 0.0000025959374407 x^9,
      // in the range -pi/2 <= x <= +pi/2. These coefficients
      // have been specifically derived for this work.

      const float x2 = (x * x);

      // Perform the polynomial approximation using a coefficient
      // expansion via the method of Horner.
      result = ((((        0.0000025959374407F
                    * x2 - 0.0001980373563403F)
                    * x2 + 0.0083329484215251F)
                    * x2 - 0.1666665066192447F)
                    * x2 + 0.9999999815561047F)
                    * x;
    }
  }

  return (((n % 2) == 0) ? result : -result);
}

EXTERN_C float COSF(float x)
{
  constexpr float pi_half = 1.5707963267948966192313216916397514420985846996876F;

  return SINF(pi_half - x);
}

EXTERN_C float EXPF(float x)
{
  // Patch the expf() function for a subset of broken GCC builds
  // like GCC 4.9 mips-sde-elf that has been built locally
  // with only big endian libraries, but without little endian.

  // Use an order-9 polynomial approximation of the exponential function
  // in the range of (-ln2 < x < ln2). Scale the argument to this range
  // and subsequently multiply the result by 2^n accordingly.

  // Derive the polynomial coefficients with Mathematica(R) by generating
  // a table of high-precision values of exp(x) in the range (-ln2 < x < ln2)
  // and subsequently applying the built-in *Fit* function.

   // Scale the argument x to the range (-ln2 < x < ln2).
   constexpr float one_over_ln2 = 1.44269504088896340735992468100189213742664595415299F;

   const float x_over_ln2 = x * one_over_ln2;

   int n;

   if(local::fabsf(x) > 0.693147180559945309417232121458176568075500134360255F)
   {
      // The absolute value of the argument exceeds ln2.
      n = local::to_int(local::floorf(x_over_ln2));
   }
   else if(local::fabsf(x) < 0.693147180559945309417232121458176568075500134360255F)
   {
      // The absolute value of the argument is less than ln2.
      n = 0;
   }
   else
   {
      // The absolute value of the argument is exactly equal to ln2,
      // in the sense of floating-point equality.
      return 2.0F;
   }

  // Check if the argument is very near an integer.
  const float floor_of_x = local::floorf(x);

  if(local::fabsf(x - floor_of_x) < std::numeric_limits<float>::epsilon())
  {
    // Return e^n for arguments very near an integer.
    return local::pown(2.71828182845904523536028747135266249775724709369996F, local::to_int(floor_of_x));
  }

  // Compute the scaled argument alpha.
  const float alpha = x - (static_cast<float>(n) * 0.693147180559945309417232121458176568075500134360255F);

  // Compute the polynomial approximation of expm1(alpha) and add to it
  // in order to obtain the scaled result.
  const float scaled_result = local::expm1f(alpha) + 1.0F;

  // Rescale the result and return it.
  return scaled_result * local::pown(2.0F, n);
}

EXTERN_C float SINHF(float x)
{
  const float epx = expf(x);
  const float emx = 1.0F / epx;

  return (epx - emx) / 2.0F;
}

EXTERN_C float COSHF(float x)
{
  const float epx = expf(x);
  const float emx = 1.0F / epx;

  return (epx + emx) / 2.0F;
}
