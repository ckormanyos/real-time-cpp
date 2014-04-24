
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
  #include <mcal_benchmark.h>

  #define CFG_APP_BENCHMARK_FPU_TYPE_SQRT     1
  #define CFG_APP_BENCHMARK_FPU_TYPE_SIN      2
  #define CFG_APP_BENCHMARK_FPU_TYPE_COS      3
  #define CFG_APP_BENCHMARK_FPU_TYPE_TAN      4
  #define CFG_APP_BENCHMARK_FPU_TYPE_ASIN     5
  #define CFG_APP_BENCHMARK_FPU_TYPE_ACOS     6
  #define CFG_APP_BENCHMARK_FPU_TYPE_ATAN     7
  #define CFG_APP_BENCHMARK_FPU_TYPE_LOG      8
  #define CFG_APP_BENCHMARK_FPU_TYPE_EXP      9
  #define CFG_APP_BENCHMARK_FPU_TYPE_POW     10
  #define CFG_APP_BENCHMARK_FPU_TYPE_SINH    11
  #define CFG_APP_BENCHMARK_FPU_TYPE_COSH    12
  #define CFG_APP_BENCHMARK_FPU_TYPE_TANH    13
  #define CFG_APP_BENCHMARK_FPU_TYPE_GAMMA   14

  #define CFG_APP_BENCHMARK_FPU_TYPE CFG_APP_BENCHMARK_FPU_TYPE_SQRT
//  #define CFG_APP_BENCHMARK_FPU_TYPE CFG_APP_BENCHMARK_FPU_TYPE_SIN
//  #define CFG_APP_BENCHMARK_FPU_TYPE CFG_APP_BENCHMARK_FPU_TYPE_COS
//  #define CFG_APP_BENCHMARK_FPU_TYPE CFG_APP_BENCHMARK_FPU_TYPE_TAN
//  #define CFG_APP_BENCHMARK_FPU_TYPE CFG_APP_BENCHMARK_FPU_TYPE_ASIN
//  #define CFG_APP_BENCHMARK_FPU_TYPE CFG_APP_BENCHMARK_FPU_TYPE_ACOS
//  #define CFG_APP_BENCHMARK_FPU_TYPE CFG_APP_BENCHMARK_FPU_TYPE_ATAN
//  #define CFG_APP_BENCHMARK_FPU_TYPE CFG_APP_BENCHMARK_FPU_TYPE_LOG
//  #define CFG_APP_BENCHMARK_FPU_TYPE CFG_APP_BENCHMARK_FPU_TYPE_EXP
//  #define CFG_APP_BENCHMARK_FPU_TYPE CFG_APP_BENCHMARK_FPU_TYPE_POW
//  #define CFG_APP_BENCHMARK_FPU_TYPE CFG_APP_BENCHMARK_FPU_TYPE_SINH
//  #define CFG_APP_BENCHMARK_FPU_TYPE CFG_APP_BENCHMARK_FPU_TYPE_COSH
//  #define CFG_APP_BENCHMARK_FPU_TYPE CFG_APP_BENCHMARK_FPU_TYPE_TANH
//  #define CFG_APP_BENCHMARK_FPU_TYPE CFG_APP_BENCHMARK_FPU_TYPE_GAMMA

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

  #elif(CFG_APP_BENCHMARK_FPU_TYPE == CFG_APP_BENCHMARK_FPU_TYPE_COS)

    // The expected value is: acos(0.5) = (approx.) 1.047197551.
    value_y = std::acos(value_x);
    const bool the_result_is_ok = is_close_fraction(FLOAT32_C(1.047197551), value_y, tolerance);

  #elif(CFG_APP_BENCHMARK_FPU_TYPE == CFG_APP_BENCHMARK_FPU_TYPE_GAMMA)

    // The expected value is: tgamma(0.5) = sqrt(pi) = (approx.) 1.77245385.
    value_y = std::tgamma(value_x);
    const bool the_result_is_ok = is_close_fraction(FLOAT32_C(1.77245385), value_y, tolerance);

  #endif

  if(the_result_is_ok)
  {
    mcal::benchmark::benchmark_port_type::set_pin_low();
  }

  #endif
}
