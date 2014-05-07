
///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2014.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

//#define CFG_USE_APP_BENCHMARK_FPU

#if defined(CFG_USE_APP_BENCHMARK_FPU)

  #include <cmath>
  #include <cstdfloat>
  #include <cstdint>
  #include <limits>
  #include <mcal_benchmark.h>

  #define CFG_APP_BENCHMARK_FPU_TYPE_SQRT      1
  #define CFG_APP_BENCHMARK_FPU_TYPE_SIN       2
  #define CFG_APP_BENCHMARK_FPU_TYPE_COS       3
  #define CFG_APP_BENCHMARK_FPU_TYPE_TAN       4
  #define CFG_APP_BENCHMARK_FPU_TYPE_ASIN      5
  #define CFG_APP_BENCHMARK_FPU_TYPE_ACOS      6
  #define CFG_APP_BENCHMARK_FPU_TYPE_ATAN      7
  #define CFG_APP_BENCHMARK_FPU_TYPE_EXP       8
  #define CFG_APP_BENCHMARK_FPU_TYPE_POW       9
  #define CFG_APP_BENCHMARK_FPU_TYPE_LOG      10
  #define CFG_APP_BENCHMARK_FPU_TYPE_LOG10    11
  #define CFG_APP_BENCHMARK_FPU_TYPE_SINH     12
  #define CFG_APP_BENCHMARK_FPU_TYPE_COSH     13
  #define CFG_APP_BENCHMARK_FPU_TYPE_TANH     14
  #define CFG_APP_BENCHMARK_FPU_TYPE_GAMMA    15
  #define CFG_APP_BENCHMARK_FPU_TYPE_BESSEL   16
  #define CFG_APP_BENCHMARK_FPU_TYPE_HYPERG   17
  #define CFG_APP_BENCHMARK_FPU_TYPE_LEGENDRE 18

//  #define CFG_APP_BENCHMARK_FPU_TYPE CFG_APP_BENCHMARK_FPU_TYPE_SQRT
//  #define CFG_APP_BENCHMARK_FPU_TYPE CFG_APP_BENCHMARK_FPU_TYPE_SIN
//  #define CFG_APP_BENCHMARK_FPU_TYPE CFG_APP_BENCHMARK_FPU_TYPE_COS
//  #define CFG_APP_BENCHMARK_FPU_TYPE CFG_APP_BENCHMARK_FPU_TYPE_TAN
//  #define CFG_APP_BENCHMARK_FPU_TYPE CFG_APP_BENCHMARK_FPU_TYPE_ASIN
//  #define CFG_APP_BENCHMARK_FPU_TYPE CFG_APP_BENCHMARK_FPU_TYPE_ACOS
//  #define CFG_APP_BENCHMARK_FPU_TYPE CFG_APP_BENCHMARK_FPU_TYPE_ATAN
//  #define CFG_APP_BENCHMARK_FPU_TYPE CFG_APP_BENCHMARK_FPU_TYPE_EXP
//  #define CFG_APP_BENCHMARK_FPU_TYPE CFG_APP_BENCHMARK_FPU_TYPE_POW
//  #define CFG_APP_BENCHMARK_FPU_TYPE CFG_APP_BENCHMARK_FPU_TYPE_LOG
//  #define CFG_APP_BENCHMARK_FPU_TYPE CFG_APP_BENCHMARK_FPU_TYPE_LOG10
//  #define CFG_APP_BENCHMARK_FPU_TYPE CFG_APP_BENCHMARK_FPU_TYPE_SINH
//  #define CFG_APP_BENCHMARK_FPU_TYPE CFG_APP_BENCHMARK_FPU_TYPE_COSH
//  #define CFG_APP_BENCHMARK_FPU_TYPE CFG_APP_BENCHMARK_FPU_TYPE_TANH
//  #define CFG_APP_BENCHMARK_FPU_TYPE CFG_APP_BENCHMARK_FPU_TYPE_GAMMA
//  #define CFG_APP_BENCHMARK_FPU_TYPE CFG_APP_BENCHMARK_FPU_TYPE_BESSEL
//  #define CFG_APP_BENCHMARK_FPU_TYPE CFG_APP_BENCHMARK_FPU_TYPE_HYPERG
//  #define CFG_APP_BENCHMARK_FPU_TYPE CFG_APP_BENCHMARK_FPU_TYPE_LEGENDRE

  #if (CFG_APP_BENCHMARK_FPU_TYPE == CFG_APP_BENCHMARK_FPU_TYPE_GAMMA)
    #if defined(__GNUC__) || (defined(_WIN32) && (_MSC_VER <= 1700))
      namespace std { std::float32_t tgamma(std::float32_t); }
    #endif
  #endif

  #if (CFG_APP_BENCHMARK_FPU_TYPE == CFG_APP_BENCHMARK_FPU_TYPE_BESSEL)
    #include <app/benchmark/app_benchmark_fpu_bessel.h>
    #include <math/constants/constants.h>
  #endif

  #if (CFG_APP_BENCHMARK_FPU_TYPE == CFG_APP_BENCHMARK_FPU_TYPE_HYPERG)
    #include <app/benchmark/app_benchmark_fpu_hypergeometric.h>
    #include <math/constants/constants.h>
  #endif

  #if (CFG_APP_BENCHMARK_FPU_TYPE == CFG_APP_BENCHMARK_FPU_TYPE_LEGENDRE)
    #include <app/benchmark/app_benchmark_fpu_legendre.h>
    #include <math/constants/constants.h>
  #endif

  namespace
  {
    template<typename float_type>
    bool is_close_fraction(float_type left, float_type right, float_type the_tolerance)
    {
      const float_type ratio = left / right;

      using std::fabs;

      const float_type delta = fabs(float_type(1) - ratio);

      return (delta < the_tolerance);
    }

    std::float32_t value_x;
    std::float32_t value_y;
  }

#endif

namespace app
{
  namespace benchmark
  {
    namespace fpu
    {
      void task_init();
      void task_func();
    }
  }
}

void app::benchmark::fpu::task_init()
{
  #if defined(CFG_USE_APP_BENCHMARK_FPU)

  mcal::benchmark::benchmark_port_type::set_direction_output();

  value_x = FLOAT32_C(0.5);

  #endif
}

void app::benchmark::fpu::task_func()
{
  #if defined(CFG_USE_APP_BENCHMARK_FPU)

  const std::float32_t benchmark_tolerance = std::numeric_limits<std::float32_t>::epsilon() * FLOAT32_C(100.0);

  mcal::benchmark::benchmark_port_type::set_pin_high();

  #if(CFG_APP_BENCHMARK_FPU_TYPE == CFG_APP_BENCHMARK_FPU_TYPE_SQRT)

    // The expected value is: sqrt(0.5) = (approx.) 0.707106781.
    value_y = std::sqrt(value_x);

    const bool the_result_is_ok = is_close_fraction(FLOAT32_C(0.707106781),
                                                    value_y,
                                                    benchmark_tolerance);

  #elif(CFG_APP_BENCHMARK_FPU_TYPE == CFG_APP_BENCHMARK_FPU_TYPE_SIN)

    // The expected value is: sin(0.5) = (approx.) 0.479425539.
    value_y = std::sin(value_x);

    const bool the_result_is_ok = is_close_fraction(FLOAT32_C(0.479425539),
                                                    value_y,
                                                    benchmark_tolerance);

  #elif(CFG_APP_BENCHMARK_FPU_TYPE == CFG_APP_BENCHMARK_FPU_TYPE_COS)

    // The expected value is: cos(0.5) = (approx.) 0.877582562.
    value_y = std::cos(value_x);

    const bool the_result_is_ok = is_close_fraction(FLOAT32_C(0.877582562),
                                                    value_y,
                                                    benchmark_tolerance);

  #elif(CFG_APP_BENCHMARK_FPU_TYPE == CFG_APP_BENCHMARK_FPU_TYPE_TAN)

    // The expected value is: tan(0.5) = (approx.) 0.546302490.
    value_y = std::tan(value_x);

    const bool the_result_is_ok = is_close_fraction(FLOAT32_C(0.546302490),
                                                    value_y,
                                                    benchmark_tolerance);

  #elif(CFG_APP_BENCHMARK_FPU_TYPE == CFG_APP_BENCHMARK_FPU_TYPE_ASIN)

    // The expected value is: asin(0.5) = (approx.) 0.523598776.
    value_y = std::asin(value_x);

    const bool the_result_is_ok = is_close_fraction(FLOAT32_C(0.523598776),
                                                    value_y,
                                                    benchmark_tolerance);

  #elif(CFG_APP_BENCHMARK_FPU_TYPE == CFG_APP_BENCHMARK_FPU_TYPE_ACOS)

    // The expected value is: acos(0.5) = (approx.) 1.047197551.
    value_y = std::acos(value_x);

    const bool the_result_is_ok = is_close_fraction(FLOAT32_C(1.047197551),
                                                    value_y,
                                                    benchmark_tolerance);

  #elif(CFG_APP_BENCHMARK_FPU_TYPE == CFG_APP_BENCHMARK_FPU_TYPE_ATAN)

    // The expected value is: atan(0.5) = (approx.) 0.463647609.
    value_y = std::atan(value_x);

    const bool the_result_is_ok = is_close_fraction(FLOAT32_C(0.463647609),
                                                    value_y,
                                                    benchmark_tolerance);

  #elif(CFG_APP_BENCHMARK_FPU_TYPE == CFG_APP_BENCHMARK_FPU_TYPE_EXP)

    // The expected value is: exp(0.5) = (approx.) 1.648721271.
    value_y = std::exp(value_x);

    const bool the_result_is_ok = is_close_fraction(FLOAT32_C(1.648721271),
                                                    value_y,
                                                    benchmark_tolerance);

  #elif(CFG_APP_BENCHMARK_FPU_TYPE == CFG_APP_BENCHMARK_FPU_TYPE_POW)

    // The expected value is: pow(0.5, 1/2) = (approx.) 0.707106781.
    value_y = std::pow(value_x, value_x);

    const bool the_result_is_ok = is_close_fraction(FLOAT32_C(0.707106781),
                                                    value_y,
                                                    benchmark_tolerance);

  #elif(CFG_APP_BENCHMARK_FPU_TYPE == CFG_APP_BENCHMARK_FPU_TYPE_LOG)

    // The expected value is: log(2.0) = (approx.) 0.693147181.
    value_y = std::log(FLOAT32_C(1.0) / value_x);

    const bool the_result_is_ok = is_close_fraction(FLOAT32_C(0.693147181),
                                                    value_y,
                                                    benchmark_tolerance);

  #elif(CFG_APP_BENCHMARK_FPU_TYPE == CFG_APP_BENCHMARK_FPU_TYPE_LOG10)

    // The expected value is: log10(FLOAT32_C(1.0) / value_x) = (approx.) 0.301029996.
    value_y = std::log10(value_x);

    const bool the_result_is_ok = is_close_fraction(FLOAT32_C(0.301029996),
                                                    value_y,
                                                    benchmark_tolerance);

  #elif(CFG_APP_BENCHMARK_FPU_TYPE == CFG_APP_BENCHMARK_FPU_TYPE_SINH)

    // The expected value is: sinh(0.5) = (approx.) 0.521095306.
    value_y = std::sinh(value_x);

    const bool the_result_is_ok = is_close_fraction(FLOAT32_C(0.521095306),
                                                    value_y,
                                                    benchmark_tolerance);

  #elif(CFG_APP_BENCHMARK_FPU_TYPE == CFG_APP_BENCHMARK_FPU_TYPE_COSH)

    // The expected value is: cosh(0.5) = (approx.) 1.127625965.
    value_y = std::cosh(value_x);

    const bool the_result_is_ok = is_close_fraction(FLOAT32_C(1.127625965),
                                                    value_y,
                                                    benchmark_tolerance);

  #elif(CFG_APP_BENCHMARK_FPU_TYPE == CFG_APP_BENCHMARK_FPU_TYPE_TANH)

    // The expected value is: tanh(0.5) = (approx.) 0.462117157.
    value_y = std::tanh(value_x);

    const bool the_result_is_ok = is_close_fraction(FLOAT32_C(0.462117157),
                                                    value_y,
                                                    benchmark_tolerance);

  #elif(CFG_APP_BENCHMARK_FPU_TYPE == CFG_APP_BENCHMARK_FPU_TYPE_GAMMA)

    // The expected value is: tgamma(0.5 + 4) = (approx.) 11.6317284.
    value_y = std::tgamma(value_x + FLOAT32_C(4.0));

    const bool the_result_is_ok = is_close_fraction(FLOAT32_C(11.6317284),
                                                    value_y,
                                                    benchmark_tolerance);

  #elif(CFG_APP_BENCHMARK_FPU_TYPE == CFG_APP_BENCHMARK_FPU_TYPE_BESSEL)

    // Here is a control value from Wolfram's Alpha or Mathematica(R).
    // N[BesselJ[4/3, EulerGamma], 100]
    // 0.1545408731983865945338700820325762509201530141290096479007756642416766799673917382215725937380276286

    // The expected value is: cyl_bessel_j(4/3, euler) = (approx.) 0.154540873,
    // where euler = (approx.) 0.5772156649.
    const std::float32_t v = FLOAT32_C(4.0) / 3;

    using math::constants::euler;

    value_y = app::benchmark::cyl_bessel_j(v,
                                           euler<std::float32_t>());

    const bool the_result_is_ok = is_close_fraction(FLOAT32_C(0.154540873),
                                                    value_y,
                                                    benchmark_tolerance);

    static_cast<void>(value_x);

  #elif(CFG_APP_BENCHMARK_FPU_TYPE == CFG_APP_BENCHMARK_FPU_TYPE_HYPERG)

    // Here is a control value from Wolfram's Alpha or Mathematica(R).
    // N[HypergeometricPFQ[1/{2, 3, 4, 5}, 2/{3, 4, 5, 6, 7}, EulerGamma], 100]
    // 1.437152091623117098817180937046270756251132185487659323159061684966332133966272470711486705986290248

    // The expected value is: hypergeometric_pfq({an}; {bm}; euler) = (approx.) 1.4371520916231,
    // where the coefficients {an} and {bm} are listed above, and euler = (approx.) 0.5772156649.
    const std::array<std::float32_t, 4U> an =
    {{
      FLOAT32_C(1.0) / FLOAT32_C(2.0),
      FLOAT32_C(1.0) / FLOAT32_C(3.0),
      FLOAT32_C(1.0) / FLOAT32_C(4.0),
      FLOAT32_C(1.0) / FLOAT32_C(5.0)
    }};

    const std::array<std::float32_t, 5U> bm =
    {{
      FLOAT32_C(2.0) / FLOAT32_C(3.0),
      FLOAT32_C(2.0) / FLOAT32_C(4.0),
      FLOAT32_C(2.0) / FLOAT32_C(5.0),
      FLOAT32_C(2.0) / FLOAT32_C(6.0),
      FLOAT32_C(2.0) / FLOAT32_C(7.0)
    }};

    using math::constants::euler;

    value_y = app::benchmark::hypergeometric_pfq(an.begin(),
                                                 an.end(),
                                                 bm.begin(),
                                                 bm.end(),
                                                 euler<std::float32_t>());

    const bool the_result_is_ok = is_close_fraction(FLOAT32_C(1.4371520916),
                                                    value_y,
                                                    benchmark_tolerance);

    static_cast<void>(value_x);

  #elif(CFG_APP_BENCHMARK_FPU_TYPE == CFG_APP_BENCHMARK_FPU_TYPE_LEGENDRE)

    // Here is a control value from Wolfram's Alpha or Mathematica(R).
    // N[LegendreP[1/7, 8/3, EulerGamma], 100]
    // 2.404353615156206106157024654523212410197778824303409489709303179021598411526465423796674832263894839

    // The expected value is: legendre_p(1/7, 8/3, euler) = (approx.) 2.4043536151562,
    // where euler = (approx.) 0.5772156649.
    const std::float32_t v = FLOAT32_C(1.0) / 7;
    const std::float32_t u = FLOAT32_C(8.0) / 3;

    using math::constants::euler;

    value_y = app::benchmark::legendre_p(v,
                                         u,
                                         euler<std::float32_t>());

    const bool the_result_is_ok = is_close_fraction(FLOAT32_C(2.4043536151562),
                                                    value_y,
                                                    benchmark_tolerance);

    static_cast<void>(value_x);

  #else

    #error Floating-point benchmark type is undefined (CFG_APP_BENCHMARK_FPU_TYPE)

    const bool the_result_is_ok = true;

  #endif

  if(the_result_is_ok)
  {
    mcal::benchmark::benchmark_port_type::set_pin_low();
  }

  #endif
}
