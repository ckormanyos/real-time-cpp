///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2010 - 2025.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <app/benchmark/app_benchmark.h>

#if (defined(APP_BENCHMARK_TYPE) && (APP_BENCHMARK_TYPE == APP_BENCHMARK_TYPE_FLOAT))

#include <app/benchmark/app_benchmark_detail.h>
#include <math/constants/constants.h>
#include <math/functions/math_functions_bessel.h>
#include <math/functions/math_functions_hypergeometric.h>
#include <math/functions/math_functions_legendre.h>

namespace
{
  constexpr float app_benchmark_tolerance { 1.0E-5F * 20.0F };
}

bool app::benchmark::run_float()
{
  static std::uint_fast8_t app_benchmark_index;

  bool app_benchmark_result_is_ok { true };

  if(app_benchmark_index == std::uint_fast8_t { UINT8_C(0) })
  {
    // Test the value of a Bessel function.
    // Here is a control value from Wolfram Alpha.
    // N[BesselJ[11/9, EulerGamma], 40]
    // 0.1890533651853886085356717332711858771597

    constexpr float v { 11.0F / 9.0F };

    const float app_benchmark_result_bessel =
      math::functions::cyl_bessel_j(v, math::constants::euler<float>());

    app_benchmark_result_is_ok =
    (
         app_benchmark_result_is_ok
      && detail::is_close_fraction(0.1890533652F,
                                   app_benchmark_result_bessel,
                                   app_benchmark_tolerance)
    );
  }
  else if(app_benchmark_index == std::uint_fast8_t { UINT8_C(1) })
  {
    // Test the value of a hypergeometric function.
    // Here is a control value from Wolfram Alpha.
    // N[HypergeometricPFQ[3/{7, 8, 9, 10}, 7/{13, 14, 15, 16, 17}, Log[2]], 40]
    // 1.583596313998374915091256357139915173598

    constexpr std::array<float, std::size_t { UINT8_C(4) }> ap =
    {{
      3.0F /  7.0F,
      3.0F /  8.0F,
      3.0F /  9.0F,
      3.0F / 10.0F
    }};

    constexpr std::array<float, std::size_t { UINT8_C(5) }> bq =
    {{
      7.0F / 13.0F,
      7.0F / 14.0F,
      7.0F / 15.0F,
      7.0F / 16.0F,
      7.0F / 17.0F
    }};

    const float app_benchmark_result_hypergeometric =
      math::functions::hypergeometric_pfq(ap.cbegin(),
                                          ap.cend(),
                                          bq.cbegin(),
                                          bq.cend(),
                                          math::constants::ln_two<float>());

    app_benchmark_result_is_ok =
    (
         app_benchmark_result_is_ok
      && detail::is_close_fraction(1.5835963140F,
                                   app_benchmark_result_hypergeometric,
                                   app_benchmark_tolerance)
    );
  }
  else if(app_benchmark_index == std::uint_fast8_t { UINT8_C(2) })
  {
    // Test the value of a Legendre function of the first kind.
    // Here is a control value from Wolfram Alpha.
    // N[LegendreP[1/11, 14/19, 2/7], 40]
    // 0.2937838815278435137954432141091105343408

    constexpr float v {  1.0F / 11.0F };
    constexpr float u { 14.0F / 19.0F };
    constexpr float x {  2.0F /  7.0F };

    const float app_benchmark_result_legendre = math::functions::legendre_p(v, u, x);

    app_benchmark_result_is_ok =
    (
         app_benchmark_result_is_ok
      && detail::is_close_fraction(0.2937838815F,
                                   app_benchmark_result_legendre,
                                   app_benchmark_tolerance)
    );
  }

  ++app_benchmark_index;

  if(app_benchmark_index == std::uint_fast8_t { UINT8_C(3) })
  {
    app_benchmark_index = std::uint_fast8_t { UINT8_C(0) };
  }

  return app_benchmark_result_is_ok;
}

#if defined(APP_BENCHMARK_STANDALONE_MAIN)
int main()
{
  // g++ -Wall -O3 -march=native -I./ref_app/src/mcal/host -I./ref_app/src -DAPP_BENCHMARK_TYPE=APP_BENCHMARK_TYPE_FLOAT -DAPP_BENCHMARK_STANDALONE_MAIN ./ref_app/src/app/benchmark/app_benchmark_float.cpp -o ./ref_app/bin/app_benchmark_float.exe

  bool result_is_ok = true;

  for(unsigned i = 0U; i < 64U; ++i)
  {
    result_is_ok &= app::benchmark::run_float();
  }

  return result_is_ok ? 0 : -1;
}
#endif

#endif // APP_BENCHMARK_TYPE_FLOAT
