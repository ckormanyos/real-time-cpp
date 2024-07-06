///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2023 - 2024.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <cstdint>
#include <limits>
#include <type_traits>

#include <app/benchmark/app_benchmark.h>

#if (defined(APP_BENCHMARK_TYPE) && (APP_BENCHMARK_TYPE == APP_BENCHMARK_TYPE_NON_STD_DECIMAL))

#if (defined(__arm__) || defined(__AVR__))
#if !defined(BOOST_DECIMAL_DISABLE_CLIB)
#define BOOST_DECIMAL_DISABLE_CLIB
#endif
#endif

#include <boost/decimal.hpp>

#include <app/benchmark/app_benchmark_detail.h>

using builtin_float_type = double;
using decimal_float_type = boost::decimal::decimal64;

//using arithmetic_float_type = builtin_float_type;
using arithmetic_float_type = decimal_float_type;

static_assert(std::numeric_limits<builtin_float_type>::digits == 53,
              "Error: Incorrect builtin_float_type definition");


#if 0
GCC11, arm-none-eabi, float-abi=soft, -O2

Calculation exp() via Pade approximation approx. 15 decimal digits.
Code-size includes about 2kb for startup, clock-init, skinny MCAL and cooperative time-scheduler.


target-specific flags
---------------------
-O2
-mcpu=cortex-m4
-mtune=cortex-m4
-mthumb
-mfloat-abi=soft
-finline-functions
-finline-limit=128
-mno-unaligned-access
-mno-long-calls


| Type                           |  runtime [us] |  relative  |    code-size [kb] |
|--------------------------------|---------------|------------|-------------------|
| double (built-in, no FPU)      |  22           |   1.0      |       5.6         |
| ::math::softfloat::float64_t   |  27           |   1.2      |       8.5         |
| boost::decimal::decimal64      |  490          |    22      |       20          |
#endif

namespace local
{

namespace numbers {

template <typename T> constexpr T                  ln2_v = static_cast<T>(static_cast<T>(UINT64_C(6931471805599453094)) / UINT64_C(10000000000000000000));
template <>           constexpr builtin_float_type ln2_v<builtin_float_type> = static_cast<builtin_float_type>(0.6931471805599453094L);
template <>           constexpr decimal_float_type ln2_v<decimal_float_type> = ::boost::decimal::numbers::ln2_v<decimal_float_type>;

template <typename T> constexpr T                  half_v = static_cast<T>(static_cast<T>(5) / 10);
template <>           constexpr builtin_float_type half_v<builtin_float_type> = static_cast<builtin_float_type>(0.5L);
template <>           constexpr decimal_float_type half_v<decimal_float_type> = decimal_float_type { 5, -1 };

} // namespace numbers

namespace detail {

template<typename T, typename UnsignedIntegralType>
auto pow_n_impl(T b, UnsignedIntegralType p) noexcept -> std::enable_if_t<(std::is_integral<UnsignedIntegralType>::value && std::is_unsigned<UnsignedIntegralType>::value), T> // NOLINT(misc-no-recursion)
{
  using local_unsigned_integral_type = UnsignedIntegralType;

  T result { 1 };

  if (p < static_cast<local_unsigned_integral_type>(UINT8_C(5)))
  {
    switch (p)
    {
      case static_cast<local_unsigned_integral_type>(UINT8_C(4)):
        result = b; result *= result; result *= result; break;
      case static_cast<local_unsigned_integral_type>(UINT8_C(3)):
        result = b; result *= result; result *= b; break;
      case static_cast<local_unsigned_integral_type>(UINT8_C(2)):
        result = b; result *= result; break;
      case static_cast<local_unsigned_integral_type>(UINT8_C(1)):
        result = b; break;
      case static_cast<local_unsigned_integral_type>(UINT8_C(0)):
      default:
        break;
    }
  }
  else
  {
    // Calculate (b ^ p) using the ladder method for powers.

    T y(b);

    auto p_local = static_cast<local_unsigned_integral_type>(p);

    for(;;)
    {
      const auto value_lo_bit = static_cast<std::uint_fast8_t>(p_local & static_cast<unsigned>(UINT8_C(1)));

      const auto do_power_multiply = (value_lo_bit != static_cast<std::uint_fast8_t>(UINT8_C(0)));

      if(do_power_multiply)
      {
        result *= y;
      }

      p_local >>= static_cast<unsigned>(UINT8_C(1));

      if(p_local == static_cast<local_unsigned_integral_type>(UINT8_C(0)))
      {
        break;
      }

      y *= y;
    }
  }

  return result;
}

template<typename T>
auto pow_2_impl(int e2) noexcept -> T
{
  T result { 1 };

  if(e2 > 0)
  {
    if(e2 < static_cast<int>(INT8_C(64)))
    {
      result = static_cast<T>(static_cast<std::uint64_t>(UINT64_C(1) << e2));
    }
    else
    {
      constexpr T two { 2 };

      result = detail::pow_n_impl(two, static_cast<unsigned>(e2));
    }
  }
  else if(e2 < 0)
  {
    const auto e2_neg = static_cast<unsigned>(static_cast<unsigned>(~e2) + 1U);

    if(e2 > static_cast<int>(INT8_C(-64)))
    {
      result /= static_cast<std::uint64_t>(static_cast<std::uint64_t>(UINT64_C(1) << e2_neg));
    }
    else
    {
      using local::numbers::half_v;

      constexpr T half = half_v<T>;

      result = detail::pow_n_impl(half, e2_neg);
    }
  }
  else
  {
    // result = one;
  }

  return result;
}

} // namespace detail

template<typename T>
auto exp(T x) noexcept -> T
{
  T result { 1 };

  if (x < 0)
  {
    result /= local::exp(-x);
  }
  else if (x > 0)
  {
    // Scale the argument to 0 < x < log(2).

    int nf2 { };

    using local::numbers::ln2_v;

    if (x > ln2_v<T>)
    {
      nf2 = int(x / ln2_v<T>);

      x -= (ln2_v<T> * nf2);
    }

    // PadeApproximant[Exp[x] - 1, {x, 0, {6, 6}}]
    // FullSimplify[%]
    //   (84 x (7920 + 240 x^2 + x^4))
    // / (665280 + x (-332640 + x (75600 + x (-10080 + x (840 + (-42 + x) x)))))

    const auto x2 = x * x;

    // Use the small-argument Pade approximation having coefficients shown above.
    const T top = T { UINT8_C(84) } * x * ( T { UINT16_C(7920) } + ( T { UINT8_C(240) } + x2) * x2);
    const T bot = T { UINT32_C(665280) } + x * (T { INT32_C(-332640) } + x * (T { UINT32_C(75600) } + x * (T { INT16_C(-10080) } + x * (T { UINT16_C(840) } + (T { INT8_C(-42) } + x) * x))));

    result += (top / bot);

    if (nf2 > 0)
    {
      (nf2 < 64) ? result *= static_cast<T>(static_cast<std::uint64_t>(UINT64_C(1) << static_cast<unsigned>(nf2)))
                 : result *= detail::pow_2_impl<T>(nf2);
    }
  }
  else
  {
    // result = one;
  }

  return result;
}

} // namespace local

extern arithmetic_float_type xarg;
extern arithmetic_float_type ctrl;

auto app::benchmark::run_non_std_decimal() -> bool
{
  auto app_benchmark_result_is_ok = true;

  // N[Exp[1234/1000], 42]
  // 3.43494186080075996825034289575947873494206

  const auto exp_result = local::exp(xarg);

  constexpr auto my_tol =
    static_cast<arithmetic_float_type>
    (
      std::numeric_limits<arithmetic_float_type>::epsilon() * 64
    );

  const auto result_exp_is_ok = detail::is_close_fraction(exp_result, ctrl, my_tol);

  app_benchmark_result_is_ok = (result_exp_is_ok && app_benchmark_result_is_ok);

  return app_benchmark_result_is_ok;
}

arithmetic_float_type xarg = static_cast<arithmetic_float_type>(1234) / 1000;
arithmetic_float_type ctrl = static_cast<arithmetic_float_type>(UINT64_C(343494186080075997)) / UINT64_C(100000000000000000);

#if defined(APP_BENCHMARK_STANDALONE_MAIN)
int main()
{
  // g++ -Wall -O3 -march=native -I./ref_app/src/mcal/host -I./ref_app/src -DAPP_BENCHMARK_TYPE=APP_BENCHMARK_TYPE_NON_STD_DECIMAL -DAPP_BENCHMARK_STANDALONE_MAIN ./ref_app/src/app/benchmark/app_benchmark_float.cpp -o ./ref_app/bin/app_benchmark_float.exe

  bool result_is_ok = true;

  for(unsigned i = 0U; i < 64U; ++i)
  {
    result_is_ok &= app::benchmark::run_non_std_decimal();
  }

  return result_is_ok ? 0 : -1;
}
#endif

#endif // APP_BENCHMARK_TYPE_NON_STD_DECIMAL
