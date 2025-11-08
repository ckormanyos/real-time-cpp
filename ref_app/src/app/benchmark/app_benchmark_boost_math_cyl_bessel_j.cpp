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

#if defined(__GNUC__)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wfloat-equal"
#endif

#include <app/benchmark/app_benchmark_detail.h>

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

  // Table[N[BesselJ[123/100, (n  10)/19], 36], {n, 1, 32, 1}]

  using my_float_control_array_type = std::array<my_float_type, 32U>;

  constexpr my_float_control_array_type app_benchmark_control =
  {{
    static_cast<my_float_type>(BOOST_FLOATMAX_C(+0.16749705997695039892041951050855636100)),
    static_cast<my_float_type>(BOOST_FLOATMAX_C(+0.35710740083806272542105607089508589400)),
    static_cast<my_float_type>(BOOST_FLOATMAX_C(+0.49804272683900925535495179621405189800)),
    static_cast<my_float_type>(BOOST_FLOATMAX_C(+0.55269427130008739173359941898456317700)),
    static_cast<my_float_type>(BOOST_FLOATMAX_C(+0.50736882925442381044306016075796287700)),
    static_cast<my_float_type>(BOOST_FLOATMAX_C(+0.37270506120363465536365448047361348800)),
    static_cast<my_float_type>(BOOST_FLOATMAX_C(+0.17991421594532067166829074911167982300)),
    static_cast<my_float_type>(BOOST_FLOATMAX_C(-0.02732268466910398234915055580536922130)),
    static_cast<my_float_type>(BOOST_FLOATMAX_C(-0.20355333869740785258588767330048038400)),
    static_cast<my_float_type>(BOOST_FLOATMAX_C(-0.31231785746207651594878814046777720400)),
    static_cast<my_float_type>(BOOST_FLOATMAX_C(-0.33442266110093192548209516325036567000)),
    static_cast<my_float_type>(BOOST_FLOATMAX_C(-0.27180702818049180454828715801497009200)),
    static_cast<my_float_type>(BOOST_FLOATMAX_C(-0.14619416570067810150835157222391312700)),
    static_cast<my_float_type>(BOOST_FLOATMAX_C(+0.00698957084440496695515622520760417157)),
    static_cast<my_float_type>(BOOST_FLOATMAX_C(+0.14779614527700722889361979468526226600)),
    static_cast<my_float_type>(BOOST_FLOATMAX_C(+0.24168749892306713766242591787726515200)),
    static_cast<my_float_type>(BOOST_FLOATMAX_C(+0.26774720743963560509939373558473043500)),
    static_cast<my_float_type>(BOOST_FLOATMAX_C(+0.22319965160563081437669317948493411000)),
    static_cast<my_float_type>(BOOST_FLOATMAX_C(+0.12324149662259129066397816497048393000)),
    static_cast<my_float_type>(BOOST_FLOATMAX_C(-0.00360882479417362699778956160990062725)),
    static_cast<my_float_type>(BOOST_FLOATMAX_C(-0.12332065041898874167333491049355101300)),
    static_cast<my_float_type>(BOOST_FLOATMAX_C(-0.20524276728094273722865880706491480400)),
    static_cast<my_float_type>(BOOST_FLOATMAX_C(-0.22979160472713542770517941683187081800)),
    static_cast<my_float_type>(BOOST_FLOATMAX_C(-0.19302622216531291569449709862299505600)),
    static_cast<my_float_type>(BOOST_FLOATMAX_C(-0.10705088708803264917682291894326102900)),
    static_cast<my_float_type>(BOOST_FLOATMAX_C(+0.00371733923617317074481324120705288138)),
    static_cast<my_float_type>(BOOST_FLOATMAX_C(+0.10932200791636712906371794202524645900)),
    static_cast<my_float_type>(BOOST_FLOATMAX_C(+0.18224048020083557887438483395729275200)),
    static_cast<my_float_type>(BOOST_FLOATMAX_C(+0.20446172600795092668267903508382583000)),
    static_cast<my_float_type>(BOOST_FLOATMAX_C(+0.17186563897417333196546998482446953200)),
    static_cast<my_float_type>(BOOST_FLOATMAX_C(+0.09485010237289362629039558971667533210)),
    static_cast<my_float_type>(BOOST_FLOATMAX_C(-0.00484616509794550010420980629673446980)),
  }};

  static unsigned app_benchmark_n_index      = 0U;
  static bool     app_benchmark_result_is_ok = true;

  const auto x =
    static_cast<my_float_type>
    (
        static_cast<my_float_type>(static_cast<my_float_type>(xn) * static_cast<my_float_type>(BOOST_FLOATMAX_C(10)))
      / static_cast<my_float_type>(BOOST_FLOATMAX_C(19))
    );

  cyj = boost::math::cyl_bessel_j(v, x);

  const auto& cyj_ctrl = app_benchmark_control.at(app_benchmark_n_index);

  app_benchmark_result_is_ok =
    (
         detail::is_close_fraction(cyj, cyj_ctrl, std::numeric_limits<my_float_type>::epsilon() * 512)
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
ATTRIBUTE(used) auto main() -> int;

auto main() -> int
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

#if defined(__GNUC__)
#pragma GCC diagnostic pop
#endif

#endif // APP_BENCHMARK_TYPE_BOOST_MATH_CYL_BESSEL_J
