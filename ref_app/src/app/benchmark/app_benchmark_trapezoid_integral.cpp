///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2021 - 2024.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <app/benchmark/app_benchmark.h>

#if (defined(APP_BENCHMARK_TYPE) && (APP_BENCHMARK_TYPE == APP_BENCHMARK_TYPE_TRAPEZOID_INTEGRAL))

// See also: https://godbolt.org/z/8ahv5Ghx5

#include <cstdint>

#if (defined(__has_include) && (__has_include(<stdfloat>)))
  #include <stdfloat>
  namespace app { namespace benchmark {
  #if (defined(__STDCPP_FLOAT64_T__) && (__STDCPP_FLOAT64_T__ == 1))
  using my_float_type = std::float64_t;
  #else
  using my_float_type = float;
  #endif
  } } // namespace app::benchmark
#else
  #include <util/STL_C++XX_stdfloat/cstdfloat>
  namespace app { namespace benchmark {
  using my_float_type = std::floatmax_t;
  } } // namespace app::benchmark
#endif

#include <app/benchmark/app_benchmark_detail.h>
#include <math/calculus/integral.h>
#include <math/constants/constants.h>

namespace
{
  template<typename FloatingPointType>
  auto cyl_bessel_j(const std::uint_fast8_t n, const FloatingPointType& x) -> FloatingPointType
  {
    using local_float_type = FloatingPointType;

    constexpr auto epsilon = std::numeric_limits<local_float_type>::epsilon();

    using std::sqrt;

    const auto tol = sqrt(epsilon);

    const auto integration_result =
      math::integral(static_cast<local_float_type>(0),
                     math::constants::pi<local_float_type>(),
                     tol,
                     [&x, &n](const local_float_type& t) noexcept
                     {
                       using std::cos;
                       using std::sin;

                       return
                         static_cast<local_float_type>
                         (
                           cos(x * sin(t) - (t * static_cast<local_float_type>(n)))
                         );
                     });

    return integration_result / math::constants::pi<local_float_type>();
  }
}

auto app::benchmark::run_trapezoid_integral() -> bool
{
  static_assert((std::numeric_limits<my_float_type>::digits >= 24),
                "Error: Incorrect my_float_type type definition");

  constexpr auto app_benchmark_tolerance =
    static_cast<my_float_type>
    (
        std::numeric_limits<my_float_type>::epsilon()
      * static_cast<my_float_type>(100.0L)
    );

  // Compute y = cyl_bessel_j(2, 1.23) = 0.16636938378681407351267852431513159437103348245333
  // N[BesselJ[2, 123/100], 50]
  const auto j2 = cyl_bessel_j(static_cast<std::uint_fast8_t>(UINT8_C(2)), static_cast<my_float_type>(1.23L));

  const bool app_benchmark_result_is_ok =
    detail::is_close_fraction
    (
      static_cast<my_float_type>(0.1663693837868140735126785243L),
      j2,
      app_benchmark_tolerance
    );

  return app_benchmark_result_is_ok;
}

#if defined(APP_BENCHMARK_STANDALONE_MAIN)
auto main() -> int
{
  bool result_is_ok { true };

  for(auto i = static_cast<unsigned>(UINT8_C(0)); i < static_cast<unsigned>(UINT8_C(64)); ++i)
  {
    result_is_ok = (app::benchmark::run_trapezoid_integral() && result_is_ok);
  }

  return (result_is_ok ? 0 : -1);
}
#endif

#endif // APP_BENCHMARK_TYPE_TRAPEZOID_INTEGRAL
