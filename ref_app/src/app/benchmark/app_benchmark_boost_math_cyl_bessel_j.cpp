///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2021 - 2025.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//


#include <app/benchmark/app_benchmark.h>

#if (defined(APP_BENCHMARK_TYPE) && (APP_BENCHMARK_TYPE == APP_BENCHMARK_TYPE_BOOST_MATH_CYL_BESSEL_J))

#include <array>
#include <cstdint>

#if (defined(__clang__) && defined(__riscv))

#include <math.h>

extern "C"
{
  long double floorl(long double x)                { return static_cast<long double>(::floor(static_cast<double>(x))); }
  long double ceill (long double x)                { return static_cast<long double>(::ceil (static_cast<double>(x))); }
  long double fmodl (long double x, long double y) { return static_cast<long double>(::fmod (static_cast<double>(x), static_cast<double>(y))); }
  long double atan2l(long double y, long double x) { return static_cast<long double>(::atan2(static_cast<double>(y), static_cast<double>(x))); }
  long double cosl  (long double x)                { return static_cast<long double>(::cos  (static_cast<double>(x))); }
  long double sinl  (long double x)                { return static_cast<long double>(::sin  (static_cast<double>(x))); }
  long double expl  (long double x)                { return static_cast<long double>(::exp  (static_cast<double>(x))); }
  long double logl  (long double x)                { return static_cast<long double>(::log  (static_cast<double>(x))); }
  long double powl  (long double x, long double a) { return static_cast<long double>(::pow  (static_cast<double>(x), static_cast<double>(a))); }
  long double coshl (long double x)                { return static_cast<long double>(::cosh (static_cast<double>(x))); }
  long double sinhl (long double x)                { return static_cast<long double>(::sinh (static_cast<double>(x))); }
}

#endif

#include <app/benchmark/app_benchmark_detail.h>

//#define APP_BENCHMARK_TYPE_BOOST_MATH_CBRT_TGAMMA_EXCLUDES_TGAMMA

#if !defined(BOOST_MATH_STANDALONE)
#define BOOST_MATH_STANDALONE
#endif

#if !defined(BOOST_MATH_NO_RTTI)
#define BOOST_MATH_NO_RTTI
#endif

#if !defined(BOOST_MATH_DISABLE_THREADS)
#define BOOST_MATH_DISABLE_THREADS
#endif

#if !defined(BOOST_MATH_NO_EXCEPTIONS)
#define BOOST_MATH_NO_EXCEPTIONS
#endif

#if !defined(BOOST_MATH_DISABLE_STD_FPCLASSIFY)
#define BOOST_MATH_DISABLE_STD_FPCLASSIFY
#endif

#if !defined(BOOST_MATH_MAX_SERIES_ITERATION_POLICY)
#define BOOST_MATH_MAX_SERIES_ITERATION_POLICY 1000U
#endif

#define BOOST_MATH_PROMOTE_FLOAT_POLICY false

#include <boost/cstdfloat.hpp>
#include <boost/math/special_functions/bessel.hpp>

using my_float_type = ::boost::float64_t;

extern my_float_type cyj;
extern unsigned      xn;
extern my_float_type v;

auto app::benchmark::run_boost_math_cbrt_cyl_bessel_j() -> bool
{
  static_assert(std::numeric_limits<my_float_type>::digits >= 53,
                "Error: Incorrect float64_t type definition");

  // Table[N[BesselJ[123/100, n/10], 36], {n, 1, 10, 1}]

  using my_float_control_array_type = std::array<my_float_type, 10U>;

  constexpr my_float_control_array_type app_benchmark_control =
  {{
    static_cast<my_float_type>(BOOST_FLOATMAX_C(0.022384094800424078635130529844793803)),
    static_cast<my_float_type>(BOOST_FLOATMAX_C(0.052329252391407531307435184345226877)),
    static_cast<my_float_type>(BOOST_FLOATMAX_C(0.085683437351809687785091267647371436)),
    static_cast<my_float_type>(BOOST_FLOATMAX_C(0.121101214488587461397609703216026929)),
    static_cast<my_float_type>(BOOST_FLOATMAX_C(0.157737296526501682321434739413437594)),
    static_cast<my_float_type>(BOOST_FLOATMAX_C(0.194945869633552745026958864087027370)),
    static_cast<my_float_type>(BOOST_FLOATMAX_C(0.232184726291181620217067657303383795)),
    static_cast<my_float_type>(BOOST_FLOATMAX_C(0.268975614426188781953361485754411729)),
    static_cast<my_float_type>(BOOST_FLOATMAX_C(0.304885613485023234627936201325996814)),
    static_cast<my_float_type>(BOOST_FLOATMAX_C(0.339517879133361150735582864456735830)),
  }};

  static unsigned app_benchmark_n_index      = 0U;
  static bool     app_benchmark_result_is_ok = true;

  const auto x =
    static_cast<my_float_type>
    (
      static_cast<my_float_type>(xn) / static_cast<my_float_type>(BOOST_FLOATMAX_C(10))
    );

  cyj = boost::math::cyl_bessel_j(v, x);

  const auto& cyj_ctrl = app_benchmark_control.at(app_benchmark_n_index);

  app_benchmark_result_is_ok =
    (
         detail::is_close_fraction(cyj, cyj_ctrl)
      && app_benchmark_result_is_ok
    );

  ++xn;

  ++app_benchmark_n_index;

  if(app_benchmark_n_index == static_cast<unsigned>(std::tuple_size<my_float_control_array_type>::value))
  {
    app_benchmark_n_index = 0U;
    xn                    = 1U;
  }

  return app_benchmark_result_is_ok;
}

#if defined(APP_BENCHMARK_STANDALONE_MAIN)
int main()
{
  // g++ -Wall -O3 -march=native -I./ref_app/src/mcal/host -I./ref_app/src -DAPP_BENCHMARK_TYPE=APP_BENCHMARK_TYPE_BOOST_MATH_CYL_BESSEL_J -DAPP_BENCHMARK_STANDALONE_MAIN ./ref_app/src/app/benchmark/app_benchmark_boost_math_cyl_bessel_j.cpp -o ./ref_app/bin/app_benchmark_boost_math_cyl_bessel_j.exe

  bool result_is_ok = true;

  for(unsigned i = 0U; i < 64U; ++i)
  {
    result_is_ok &= app::benchmark::run_boost_math_cbrt_cyl_bessel_j();
  }

  return result_is_ok ? 0 : -1;
}

#endif

my_float_type cyj;
unsigned      xn = static_cast<unsigned>(UINT8_C(1));
my_float_type v  = static_cast<my_float_type>(BOOST_FLOATMAX_C(1.23));

#endif // APP_BENCHMARK_TYPE_BOOST_MATH_CYL_BESSEL_J
