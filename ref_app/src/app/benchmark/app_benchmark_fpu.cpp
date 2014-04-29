
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

  #define CFG_APP_BENCHMARK_FPU_TYPE_FLOOR    1
  #define CFG_APP_BENCHMARK_FPU_TYPE_CEIL     2
  #define CFG_APP_BENCHMARK_FPU_TYPE_SQRT     3
  #define CFG_APP_BENCHMARK_FPU_TYPE_SIN      4
  #define CFG_APP_BENCHMARK_FPU_TYPE_COS      5
  #define CFG_APP_BENCHMARK_FPU_TYPE_TAN      6
  #define CFG_APP_BENCHMARK_FPU_TYPE_ASIN     7
  #define CFG_APP_BENCHMARK_FPU_TYPE_ACOS     8
  #define CFG_APP_BENCHMARK_FPU_TYPE_ATAN     9
  #define CFG_APP_BENCHMARK_FPU_TYPE_EXP     10
  #define CFG_APP_BENCHMARK_FPU_TYPE_POW     11
  #define CFG_APP_BENCHMARK_FPU_TYPE_LOG     12
  #define CFG_APP_BENCHMARK_FPU_TYPE_LOG10   13
  #define CFG_APP_BENCHMARK_FPU_TYPE_SINH    14
  #define CFG_APP_BENCHMARK_FPU_TYPE_COSH    15
  #define CFG_APP_BENCHMARK_FPU_TYPE_TANH    16
  #define CFG_APP_BENCHMARK_FPU_TYPE_GAMMA   17
  #define CFG_APP_BENCHMARK_FPU_TYPE_HYPERG  18

//  #define CFG_APP_BENCHMARK_FPU_TYPE CFG_APP_BENCHMARK_FPU_TYPE_FLOOR
//  #define CFG_APP_BENCHMARK_FPU_TYPE CFG_APP_BENCHMARK_FPU_TYPE_CEIL
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
//  #define CFG_APP_BENCHMARK_FPU_TYPE CFG_APP_BENCHMARK_FPU_TYPE_HYPERG

  #if (CFG_APP_BENCHMARK_FPU_TYPE == CFG_APP_BENCHMARK_FPU_TYPE_HYPERG)
    #include <app/benchmark/app_benchmark_fpu_hypergeometric.h>
  #endif

  namespace
  {
    bool is_close_fraction(const std::float32_t& a, const std::float32_t& b, const std::float32_t& tol)
    {
      const std::float32_t ratio = a / b;

      const std::float32_t delta = std::fabs(FLOAT32_C(1.0) - ratio);

      return (delta < tol);
    }

    std::float32_t value_x;
    std::float32_t value_y;

    const std::float32_t tolerance = std::numeric_limits<std::float32_t>::epsilon() * FLOAT32_C(1000.0);
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

  #if(CFG_APP_BENCHMARK_FPU_TYPE == CFG_APP_BENCHMARK_FPU_TYPE_FLOOR)

    // The expected value is: floor(pi) = (approx.) 3.0.
    value_y = std::floor(math::constants::pi<std::float32_t>());
    const bool the_result_is_ok = is_close_fraction(FLOAT32_C(3.0), value_y, tolerance);
    static_cast<void>(value_x);

  #elif(CFG_APP_BENCHMARK_FPU_TYPE == CFG_APP_BENCHMARK_FPU_TYPE_CEIL)

    // The expected value is: ceil(root_two) = (approx.) 2.0.
    value_y = std::ceil(math::constants::root_two<std::float32_t>());
    const bool the_result_is_ok = is_close_fraction(FLOAT32_C(2.0), value_y, tolerance);
    static_cast<void>(value_x);

  #elif(CFG_APP_BENCHMARK_FPU_TYPE == CFG_APP_BENCHMARK_FPU_TYPE_SQRT)

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

  #elif(CFG_APP_BENCHMARK_FPU_TYPE == CFG_APP_BENCHMARK_FPU_TYPE_GAMMA)

    // The expected value is: tgamma(0.5) = sqrt(pi) = (approx.) 1.77245385.
    value_y = std::tgamma(value_x);
    const bool the_result_is_ok = is_close_fraction(FLOAT32_C(1.77245385), value_y, tolerance);

  #elif(CFG_APP_BENCHMARK_FPU_TYPE == CFG_APP_BENCHMARK_FPU_TYPE_HYPERG)

    const std::array<float, 4U> an = {{ 1.0F / 2, 1.0F / 3, 1.0F / 4, 1.0F / 5, }};
    const std::array<float, 5U> bm = {{ 2.0F / 3, 2.0F / 4, 2.0F / 5, 2.0F / 6, 2.0F / 7 }};

    // Here is a control value from Wolfram's Alpha or Mathematica(R).
    // N[HypergeometricPFQ[{1/2, 1/3, 1/4, 1/5}, {2/3, 2/4, 2/5, 2/6, 2/7}, EulerGamma], 100]
    // 1.437152091623117098817180937046270756251132185487659323159061684966332133966272470711486705986290248

    // The expected value is: hypergeometric_pfq({an};{bm}, euler) = (approx.) 1.43715209,
    // where the coefficients {an} and {bm} are listed above, and euler = (approx.) 0.57721566.
    value_y = hypergeometric_pfq(an.begin(),
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
