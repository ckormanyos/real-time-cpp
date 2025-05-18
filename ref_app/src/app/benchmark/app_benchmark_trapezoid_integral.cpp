///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2021 - 2025.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <app/benchmark/app_benchmark.h>

#if (defined(APP_BENCHMARK_TYPE) && (APP_BENCHMARK_TYPE == APP_BENCHMARK_TYPE_TRAPEZOID_INTEGRAL))

// See also: https://godbolt.org/z/6cexnsW9Y

#include <cstdint>
#include <limits>

#if defined(_MSC_VER)

#include <util/STL_C++XX_stdfloat/cstdfloat>

#elif (defined(__has_include) && (__has_include(<stdfloat>)))

#include <stdfloat>

#else

#include <util/STL_C++XX_stdfloat/cstdfloat>

#endif

#if (defined(__GNUC__) && defined(__RL78__))

using local_float_type = std::float32_t;
static_assert((std::numeric_limits<local_float_type>::digits >= 24), "Error: Incorrect local_float_type type definition");

#elif (defined(STDFLOAT_FLOAT64_NATIVE_TYPE) || (defined(__STDCPP_FLOAT64_T__) && (__STDCPP_FLOAT64_T__ == 1)))

using local_float_type = std::float64_t;
static_assert((std::numeric_limits<local_float_type>::digits >= 53), "Error: Incorrect local_float_type type definition");

#elif (defined(STDFLOAT_FLOAT32_NATIVE_TYPE) || (defined(__STDCPP_FLOAT32_T__) && (__STDCPP_FLOAT32_T__ == 1)))

using local_float_type = std::float32_t;
static_assert((std::numeric_limits<local_float_type>::digits >= 24), "Error: Incorrect local_float_type type definition");

#else

using local_float_type = double;
static_assert((std::numeric_limits<local_float_type>::digits >= 53), "Error: Incorrect local_float_type type definition");

#endif

namespace app { namespace benchmark {

using my_float_type = ::local_float_type;

} // namespace benchmark
} // namespace app

#include <app/benchmark/app_benchmark_detail.h>
#include <math/calculus/integral.h>
#include <math/constants/constants.h>

namespace local
{
  template<typename FloatingPointType>
  auto cyl_bessel_j(const std::uint_fast8_t n, const FloatingPointType& x) -> FloatingPointType
  {
    using local_float_type = FloatingPointType;

    using std::sqrt;

    const local_float_type tol { sqrt(std::numeric_limits<local_float_type>::epsilon()) };

    const local_float_type
      integration_result
      {
        math::integral
        (
          static_cast<local_float_type>(0),
          math::constants::pi<local_float_type>(),
          tol,
          [&x, &n](const local_float_type& t) noexcept
          {
            using std::cos;
            using std::sin;

            return cos(static_cast<local_float_type>((x * sin(t)) - (t * static_cast<local_float_type>(n))));
          }
        )
      };

    return integration_result / math::constants::pi<local_float_type>();
  }
} // namespace local

auto app::benchmark::run_trapezoid_integral() -> bool
{
  constexpr my_float_type
    app_benchmark_tolerance
    {
      std::numeric_limits<my_float_type>::epsilon() * static_cast<my_float_type>(100.0L)
    };

  // Test the value of a Bessel function.
  // Here is a control value from Wolfram Alpha.
  // N[BesselJ[2, 123/100], 50]
  // 0.16636938378681407351267852431513159437103348245333

  // Compute cyl_bessel_j(2, 1.23)

  const my_float_type j2 { local::cyl_bessel_j(std::uint_fast8_t { UINT8_C(2) }, static_cast<my_float_type>(1.23L)) };

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
auto main() -> int;

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
