///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2021 - 2022.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <app/benchmark/app_benchmark.h>

#if(APP_BENCHMARK_TYPE == APP_BENCHMARK_TYPE_TRAPEZOID_INTEGRAL)

#include <cstdint>

#include <util/STL_C++XX_stdfloat/cstdfloat>

#include <app/benchmark/app_benchmark_detail.h>
#include <math/calculus/integral.h>
#include <math/constants/constants.h>

namespace
{
  template<typename FloatingPointType>
  FloatingPointType cyl_bessel_j(const std::uint_fast8_t n,
                                 const FloatingPointType& x)
  {
    using local_float_type = FloatingPointType;

    constexpr local_float_type epsilon = std::numeric_limits<local_float_type>::epsilon();

    using std::cos;
    using std::sin;
    using std::sqrt;

    const local_float_type tol = sqrt(epsilon);

    const local_float_type integration_result = math::integral(static_cast<local_float_type>(0),
                                                         math::constants::pi<local_float_type>(),
                                                         tol,
                                                         [&x, &n](const local_float_type& t) noexcept -> local_float_type
                                                         {
                                                           return cos(x * sin(t) - (t * static_cast<local_float_type>(n)));
                                                         });

    const local_float_type jn = integration_result / math::constants::pi<local_float_type>();

    return jn;
  }
}

auto app::benchmark::run_trapezoid_integral() -> bool
{
  using my_float_type = std::floatmax_t;

  static_assert((std::numeric_limits<my_float_type>::digits >= 24),
                "Error: Incorrect my_float_type type definition");

  constexpr my_float_type app_benchmark_tolerance =
    static_cast<my_float_type>
    (
        std::numeric_limits<my_float_type>::epsilon()
      * static_cast<my_float_type>(FLOATMAX_C(100.0))
    );

  // Compute y = cyl_bessel_j(2, 1.23) = 0.16636938378681407351267852431513159437103348245333
  // N[BesselJ[2, 123/100], 50]
  const my_float_type j2 =
    cyl_bessel_j
    (
      UINT8_C(2),
      static_cast<my_float_type>(FLOATMAX_C(1.23))
    );

  const bool app_benchmark_result_is_ok =
    detail::is_close_fraction
    (
      static_cast<my_float_type>(FLOATMAX_C(0.1663693837868140735126785243)),
      j2,
      app_benchmark_tolerance
    );

  return app_benchmark_result_is_ok;
}

#if defined(APP_BENCHMARK_STANDALONE_MAIN)
int main()
{
  // g++ -Wall -O3 -march=native -I./ref_app/src/mcal/host -I./ref_app/src -DAPP_BENCHMARK_TYPE=APP_BENCHMARK_TYPE_TRAPEZOID_INTEGRAL -DAPP_BENCHMARK_STANDALONE_MAIN ./ref_app/src/app/benchmark/app_benchmark_trapezoid_integral.cpp -o ./ref_app/bin/app_benchmark_trapezoid_integral.exe

  bool result_is_ok = true;

  for(unsigned i = 0U; i < 64U; ++i)
  {
    result_is_ok &= app::benchmark::run_trapezoid_integral();
  }

  return result_is_ok ? 0 : -1;
}
#endif

#endif // APP_BENCHMARK_TYPE_TRAPEZOID_INTEGRAL
