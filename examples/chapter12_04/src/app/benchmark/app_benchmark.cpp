///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2017 - 2020.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <cmath>
#include <cstdfloat>
#include <limits>

#include <math/constants/constants.h>
#include <math/functions/math_functions_bessel.h>
#include <math/functions/math_functions_hypergeometric.h>
#include <math/functions/math_functions_legendre.h>
#include <mcal_benchmark.h>
#include <mcal_cpu.h>
#include <mcal_irq.h>
#include <util/utility/util_time.h>

namespace app
{
  namespace benchmark
  {
    void task_init();
    void task_func();
  }
}

namespace
{
  using app_benchmark_port_type = mcal::benchmark::benchmark_port_type;

  typedef util::timer<std::uint32_t> app_benchmark_timer_type;

  app_benchmark_timer_type  app_benchmark_timer;

  std::float32_t app_benchmark_result_bessel;
  std::float32_t app_benchmark_result_hypergeometric;
  std::float32_t app_benchmark_result_legendre;

  bool app_benchmark_result_is_ok;

  const std::float32_t app_benchmark_tolerance =
    std::numeric_limits<std::float32_t>::epsilon() * FLOAT32_C(20.0);

  template<typename float_type>
  bool is_close_fraction(const float_type& left,
                         const float_type& right,
                         const float_type& tolerance)
  {
    const float_type ratio = left / right;

    using std::fabs;

    const float_type delta = fabs(static_cast<float_type>(FLOATMAX_C(1.0)) - fabs(ratio));

    return (delta < tolerance);
  }
}

void app::benchmark::task_init()
{
  // Set the CRC port measurement pin to output
  app_benchmark_port_type::set_direction_output();
}

void app::benchmark::task_func()
{
  static std::uint_fast8_t app_benchmark_index;

  app_benchmark_result_is_ok = true;

  // Use a port pin to provide a real-time measurement.
  app_benchmark_port_type::set_pin_high();

  if(app_benchmark_index == 0U)
  {
    // Test the value of a Bessel function.
    // Here is a control value from Wolfram Alpha.
    // N[BesselJ[11/9, EulerGamma], 40]
    // 0.1890533651853886085356717332711858771597

    constexpr std::float32_t v = FLOAT32_C(11.0) / FLOAT32_C(9.0);

    app_benchmark_result_bessel =
      math::functions::cyl_bessel_j(v, math::constants::euler<std::float32_t>());

    app_benchmark_result_is_ok &= is_close_fraction(FLOAT32_C(0.1890533652),
                                                    app_benchmark_result_bessel,
                                                    app_benchmark_tolerance);
  }
  else if(app_benchmark_index == 1U)
  {
    // Test the value of a hypergeometric function.
    // Here is a control value from Wolfram Alpha.
    // N[HypergeometricPFQ[3/{7, 8, 9, 10}, 7/{13, 14, 15, 16, 17}, Log[2]], 40]
    // 1.583596313998374915091256357139915173598

    constexpr std::array<std::float32_t, 4U> ap =
    {{
      FLOAT32_C(3.0) / FLOAT32_C( 7.0),
      FLOAT32_C(3.0) / FLOAT32_C( 8.0),
      FLOAT32_C(3.0) / FLOAT32_C( 9.0),
      FLOAT32_C(3.0) / FLOAT32_C(10.0)
    }};

    constexpr std::array<std::float32_t, 5U> bq =
    {{
      FLOAT32_C(7.0) / FLOAT32_C(13.0),
      FLOAT32_C(7.0) / FLOAT32_C(14.0),
      FLOAT32_C(7.0) / FLOAT32_C(15.0),
      FLOAT32_C(7.0) / FLOAT32_C(16.0),
      FLOAT32_C(7.0) / FLOAT32_C(17.0)
    }};

    app_benchmark_result_hypergeometric =
      math::functions::hypergeometric_pfq(ap.cbegin(),
                                          ap.cend(),
                                          bq.cbegin(),
                                          bq.cend(),
                                          math::constants::ln_two<std::float32_t>());

    app_benchmark_result_is_ok &= is_close_fraction(FLOAT32_C(1.5835963140),
                                                    app_benchmark_result_hypergeometric,
                                                    app_benchmark_tolerance);
  }
  else if(app_benchmark_index == 2U)
  {
    // Test the value of a Legendre function of the first kind.
    // Here is a control value from Wolfram Alpha.
    // N[LegendreP[1/11, 14/19, 2/7], 40]
    // 0.2937838815278435137954432141091105343408
    constexpr std::float32_t v = FLOAT32_C( 1.0) / FLOAT32_C(11.0);
    constexpr std::float32_t u = FLOAT32_C(14.0) / FLOAT32_C(19.0);
    constexpr std::float32_t x = FLOAT32_C( 2.0) / FLOAT32_C( 7.0);

    app_benchmark_result_legendre = math::functions::legendre_p(v, u, x);

    app_benchmark_result_is_ok &= is_close_fraction(FLOAT32_C(0.2937838815),
                                                    app_benchmark_result_legendre,
                                                    app_benchmark_tolerance);
  }

  app_benchmark_port_type::set_pin_low();

  ++app_benchmark_index;

  if(app_benchmark_index == 3U)
  {
    app_benchmark_index = 0U;
  }


  if(app_benchmark_result_is_ok == false)
  {
    // The result of this floating-point benchmark is not OK.

    // Crash the system and toggle a port to provide an indication of failure.
    for(;;) { app_benchmark_port_type::toggle_pin(); mcal::cpu::nop(); }
  }
}
