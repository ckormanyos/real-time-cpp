
///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2014.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

//#define CFG_USE_APP_BENCHMARK_FPU

#if defined(CFG_USE_APP_BENCHMARK_FPU)

  #include <cmath>
  #include <cstdint>
  #include <cstdfloat>
  #include <limits>
  #include <math/constants/constants.h>
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
  #define CFG_APP_BENCHMARK_FPU_TYPE_LEGENDRE 17
  #define CFG_APP_BENCHMARK_FPU_TYPE_HYPERG   18

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
//  #define CFG_APP_BENCHMARK_FPU_TYPE CFG_APP_BENCHMARK_FPU_TYPE_LEGENDRE
//  #define CFG_APP_BENCHMARK_FPU_TYPE CFG_APP_BENCHMARK_FPU_TYPE_HYPERG

  #if (CFG_APP_BENCHMARK_FPU_TYPE == CFG_APP_BENCHMARK_FPU_TYPE_BESSEL)
    #include <app/benchmark/app_benchmark_fpu_bessel.h>
  #endif

  #if (CFG_APP_BENCHMARK_FPU_TYPE == CFG_APP_BENCHMARK_FPU_TYPE_LEGENDRE)
    #include <app/benchmark/app_benchmark_fpu_legendre.h>
  #endif

  #if (CFG_APP_BENCHMARK_FPU_TYPE == CFG_APP_BENCHMARK_FPU_TYPE_HYPERG)
    #include <app/benchmark/app_benchmark_fpu_hypergeometric.h>
  #endif

  namespace
  {
    bool is_close_fraction(std::float32_t a, std::float32_t b, std::float32_t tol)
    {
      const std::float32_t ratio = a / b;

      using std::fabs;

      const std::float32_t delta = fabs(FLOAT32_C(1.0) - ratio);

      return (delta < tol);
    }

    std::float32_t value_x;
    std::float32_t value_y;

    const std::float32_t tolerance = std::numeric_limits<std::float32_t>::epsilon() * FLOAT32_C(100.0);
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

  value_x = 0.5F;

  #endif
}

void app::benchmark::fpu::task_func()
{
  #if defined(CFG_USE_APP_BENCHMARK_FPU)

  mcal::benchmark::benchmark_port_type::set_pin_high();

  #if(CFG_APP_BENCHMARK_FPU_TYPE == CFG_APP_BENCHMARK_FPU_TYPE_SQRT)

    // The expected value is: sqrt(0.5) = (approx.) 0.707106781.
    value_y = std::sqrt(value_x);
    const bool the_result_is_ok = is_close_fraction(FLOAT32_C(0.707106781), value_y, tolerance);

  #elif(CFG_APP_BENCHMARK_FPU_TYPE == CFG_APP_BENCHMARK_FPU_TYPE_SIN)

    // The expected value is: sin(0.5) = (approx.) 0.479425539.
    value_y = std::sin(value_x);
    const bool the_result_is_ok = is_close_fraction(FLOAT32_C(0.479425539), value_y, tolerance);

  #elif(CFG_APP_BENCHMARK_FPU_TYPE == CFG_APP_BENCHMARK_FPU_TYPE_COS)

    // The expected value is: cos(0.5) = (approx.) 0.877582562.
    value_y = std::cos(value_x);
    const bool the_result_is_ok = is_close_fraction(FLOAT32_C(0.877582562), value_y, tolerance);

  #elif(CFG_APP_BENCHMARK_FPU_TYPE == CFG_APP_BENCHMARK_FPU_TYPE_TAN)

    // The expected value is: tan(0.5) = (approx.) 0.546302490.
    value_y = std::tan(value_x);
    const bool the_result_is_ok = is_close_fraction(FLOAT32_C(0.546302490), value_y, tolerance);

  #elif(CFG_APP_BENCHMARK_FPU_TYPE == CFG_APP_BENCHMARK_FPU_TYPE_ASIN)

    // The expected value is: asin(0.5) = (approx.) 0.523598776.
    value_y = std::asin(value_x);
    const bool the_result_is_ok = is_close_fraction(FLOAT32_C(0.523598776), value_y, tolerance);

  #elif(CFG_APP_BENCHMARK_FPU_TYPE == CFG_APP_BENCHMARK_FPU_TYPE_ACOS)

    // The expected value is: acos(0.5) = (approx.) 1.047197551.
    value_y = std::acos(value_x);
    const bool the_result_is_ok = is_close_fraction(FLOAT32_C(1.047197551), value_y, tolerance);

  #elif(CFG_APP_BENCHMARK_FPU_TYPE == CFG_APP_BENCHMARK_FPU_TYPE_ATAN)

    // The expected value is: atan(0.5) = (approx.) 0.463647609.
    value_y = std::atan(value_x);
    const bool the_result_is_ok = is_close_fraction(FLOAT32_C(0.463647609), value_y, tolerance);

  #elif(CFG_APP_BENCHMARK_FPU_TYPE == CFG_APP_BENCHMARK_FPU_TYPE_EXP)

    // The expected value is: exp(0.5) = (approx.) 1.648721271.
    value_y = std::exp(value_x);
    const bool the_result_is_ok = is_close_fraction(FLOAT32_C(1.648721271), value_y, tolerance);

  #elif(CFG_APP_BENCHMARK_FPU_TYPE == CFG_APP_BENCHMARK_FPU_TYPE_POW)

    // The expected value is: pow(0.5, 1/2) = (approx.) 0.707106781.
    value_y = std::pow(value_x, value_x);
    const bool the_result_is_ok = is_close_fraction(FLOAT32_C(0.707106781), value_y, tolerance);

  #elif(CFG_APP_BENCHMARK_FPU_TYPE == CFG_APP_BENCHMARK_FPU_TYPE_LOG)

    // The expected value is: log(2.0) = (approx.) 0.693147181.
    value_y = std::log(FLOAT32_C(1.0) / value_x);
    const bool the_result_is_ok = is_close_fraction(FLOAT32_C(0.693147181), value_y, tolerance);

  #elif(CFG_APP_BENCHMARK_FPU_TYPE == CFG_APP_BENCHMARK_FPU_TYPE_LOG10)

    // The expected value is: log10(FLOAT32_C(1.0) / value_x) = (approx.) 0.301029996.
    value_y = std::log10(value_x);
    const bool the_result_is_ok = is_close_fraction(FLOAT32_C(0.301029996), value_y, tolerance);

  #elif(CFG_APP_BENCHMARK_FPU_TYPE == CFG_APP_BENCHMARK_FPU_TYPE_SINH)

    // The expected value is: sinh(0.5) = (approx.) 0.521095306.
    value_y = std::sinh(value_x);
    const bool the_result_is_ok = is_close_fraction(FLOAT32_C(0.521095306), value_y, tolerance);

  #elif(CFG_APP_BENCHMARK_FPU_TYPE == CFG_APP_BENCHMARK_FPU_TYPE_COSH)

    // The expected value is: cosh(0.5) = (approx.) 1.127625965.
    value_y = std::cosh(value_x);
    const bool the_result_is_ok = is_close_fraction(FLOAT32_C(1.127625965), value_y, tolerance);

  #elif(CFG_APP_BENCHMARK_FPU_TYPE == CFG_APP_BENCHMARK_FPU_TYPE_TANH)

    // The expected value is: tanh(0.5) = (approx.) 0.462117157.
    value_y = std::tanh(value_x);
    const bool the_result_is_ok = is_close_fraction(FLOAT32_C(0.462117157), value_y, tolerance);

  #elif(CFG_APP_BENCHMARK_FPU_TYPE == CFG_APP_BENCHMARK_FPU_TYPE_GAMMA)

    // The expected value is: tgamma(0.5 + 4) = (approx.) 11.6317284.
    value_y = std::tgamma(value_x + FLOAT32_C(4.0));
    const bool the_result_is_ok = is_close_fraction(FLOAT32_C(11.6317284), value_y, tolerance);

  #elif(CFG_APP_BENCHMARK_FPU_TYPE == CFG_APP_BENCHMARK_FPU_TYPE_BESSEL)

    // Here is a control value from Wolfram's Alpha or Mathematica(R).
    // N[BesselJ[4/3, EulerGamma], 100]
    // 0.1545408731983865945338700820325762509201530141290096479007756642416766799673917382215725937380276286

    // The expected value is: cyl_bessel_j(4/3, euler) = (approx.) 0.154540873,
    // where euler = (approx.) 0.57721566.
    value_y = app::benchmark::cyl_bessel_j(FLOAT32_C(4.0) / FLOAT32_C(3.0), math::constants::euler<float>());
    const bool the_result_is_ok = is_close_fraction(FLOAT32_C(0.154540873), value_y, tolerance);
    static_cast<void>(value_x);

  #elif(CFG_APP_BENCHMARK_FPU_TYPE == CFG_APP_BENCHMARK_FPU_TYPE_LEGENDRE)

    const std::float32_t v = FLOAT32_C(1.0) / 3;
    const std::float32_t u = FLOAT32_C(1.0) / 7;

    // Here is a control value from Wolfram's Alpha or Mathematica(R).
    // N[LegendreP[1/3, 1/7, EulerGamma], 100]
    // 0.8734061203459608685331902841293191064844651089604800371508223554141952931137089620534011111088934175

    // The expected value is: legendre_p(1/7, 1/3, euler) = (approx.) 0.8734061203,
    // where euler = (approx.) 0.57721566.
    value_y = app::benchmark::legendre_p(v, u, math::constants::euler<float>());
    const bool the_result_is_ok = is_close_fraction(FLOAT32_C(0.8734061203), value_y, tolerance);
    static_cast<void>(value_x);

  #elif(CFG_APP_BENCHMARK_FPU_TYPE == CFG_APP_BENCHMARK_FPU_TYPE_HYPERG)

    const std::array<std::float32_t, 4U> an = {{ FLOAT32_C(1.0) / 2, FLOAT32_C(1.0) / 3, FLOAT32_C(1.0) / 4, FLOAT32_C(1.0) / 5, }};
    const std::array<std::float32_t, 5U> bm = {{ FLOAT32_C(2.0) / 3, FLOAT32_C(2.0) / 4, FLOAT32_C(2.0) / 5, FLOAT32_C(2.0) / 6, FLOAT32_C(2.0) / 7 }};

    // Here is a control value from Wolfram's Alpha or Mathematica(R).
    // N[HypergeometricPFQ[{1/2, 1/3, 1/4, 1/5}, {2/3, 2/4, 2/5, 2/6, 2/7}; EulerGamma], 100]
    // 1.437152091623117098817180937046270756251132185487659323159061684966332133966272470711486705986290248

    // The expected value is: hypergeometric_pfq({an}; {bm}; euler) = (approx.) 1.43715209,
    // where the coefficients {an} and {bm} are listed above, and euler = (approx.) 0.57721566.
    value_y = app::benchmark::hypergeometric_pfq(an.begin(),
                                                 an.end(),
                                                 bm.begin(),
                                                 bm.end(),
                                                 math::constants::euler<float>());

    const bool the_result_is_ok = is_close_fraction(FLOAT32_C(1.43715209), value_y, tolerance);
    static_cast<void>(value_x);

  #else

    const bool the_result_is_ok = true;

  #endif

  if(the_result_is_ok)
  {
    mcal::benchmark::benchmark_port_type::set_pin_low();
  }

  #endif
}
