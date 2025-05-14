///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2021.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <algorithm>

#include <app/benchmark/app_benchmark.h>
#include <app/benchmark/app_benchmark_detail.h>

#if (defined(APP_BENCHMARK_TYPE) && (APP_BENCHMARK_TYPE == APP_BENCHMARK_TYPE_CNL_SCALED_INTEGER))

#include <cnl/scaled_integer.h>

namespace
{
  template<typename NumericType>
  auto quadratic(const NumericType a,
                 const NumericType b,
                 const NumericType c,
                 const NumericType x) -> NumericType
  {
    return NumericType((NumericType(a * x) + b) * x) + c;
  }

  template<typename NumericType>
  auto is_close_fraction(const NumericType a,
                         const NumericType b,
                         const NumericType tol = NumericType(std::numeric_limits<NumericType>::epsilon() * 100)) -> bool
  {
    using std::abs;

    const NumericType ratio     = abs(NumericType((NumericType(1) * a) / b));

    const NumericType closeness = abs(NumericType(1 - ratio));

    return (closeness < tol);
  }

  using fixed_point_bin_type = cnl::scaled_integer<std::int32_t, cnl::power<-10>>;
  using fixed_point_dec_type = cnl::scaled_integer<std::int32_t, cnl::power<-3, 10>>;
}

extern fixed_point_bin_type a_bin;
extern fixed_point_bin_type b_bin;
extern fixed_point_bin_type c_bin;
extern fixed_point_bin_type x_bin;
extern fixed_point_bin_type r_bin;

extern fixed_point_dec_type a_dec;
extern fixed_point_dec_type b_dec;
extern fixed_point_dec_type c_dec;
extern fixed_point_dec_type x_dec;
extern fixed_point_dec_type r_dec;

auto app::benchmark::run_cnl_scaled_integer() -> bool
{
  static std::uint_fast8_t app_benchmark_cnl_scaled_integer_type_toggler;

  bool result_is_ok;

  if((app_benchmark_cnl_scaled_integer_type_toggler % 2U) == 0U)
  {
    const fixed_point_bin_type f = quadratic(a_bin, b_bin, c_bin, x_bin);

    result_is_ok = is_close_fraction(f, r_bin, fixed_point_bin_type(fixed_point_bin_type(1) / 100));
  }
  else
  {
    const fixed_point_dec_type f = quadratic(a_dec, b_dec, c_dec, x_dec);

    result_is_ok = is_close_fraction(f, r_dec, fixed_point_dec_type(fixed_point_dec_type(1) / 100));
  }

  ++app_benchmark_cnl_scaled_integer_type_toggler;

  return result_is_ok;
}

// Consider the result of the quadratic:
//  = ((12/10) (1/2)^2) + (34/10) (1/2) + (56/10)
//  = (12 + (34*2) + (56*4)) / 40
//  = 304 / 40
//  = 38/5
//  = 7.6

fixed_point_bin_type a_bin(fixed_point_bin_type(12) / 10);
fixed_point_bin_type b_bin(fixed_point_bin_type(34) / 10);
fixed_point_bin_type c_bin(fixed_point_bin_type(56) / 10);
fixed_point_bin_type x_bin(fixed_point_bin_type( 1) /  2);
fixed_point_bin_type r_bin(fixed_point_bin_type(76) / 10);

fixed_point_dec_type a_dec(fixed_point_dec_type(12) / 10);
fixed_point_dec_type b_dec(fixed_point_dec_type(34) / 10);
fixed_point_dec_type c_dec(fixed_point_dec_type(56) / 10);
fixed_point_dec_type x_dec(fixed_point_dec_type( 1) /  2);
fixed_point_dec_type r_dec(fixed_point_dec_type(76) / 10);

#if defined(APP_BENCHMARK_STANDALONE_MAIN)
constexpr auto app_benchmark_standalone_foodcafe = static_cast<std::uint32_t>(UINT32_C(0xF00DCAFE));

extern "C"
{
  extern volatile std::uint32_t app_benchmark_standalone_result;

  auto app_benchmark_run_standalone       () -> bool;
  auto app_benchmark_get_standalone_result() -> bool;

  auto app_benchmark_run_standalone() -> bool
  {
    auto result_is_ok = true;

    for(unsigned i = 0U; i < 64U; ++i)
    {
      result_is_ok &= app::benchmark::run_cnl_scaled_integer();
    }

    app_benchmark_standalone_result =
      static_cast<std::uint32_t>
      (
        result_is_ok ? app_benchmark_standalone_foodcafe : static_cast<std::uint32_t>(UINT32_C(0xFFFFFFFF))
      );

    return result_is_ok;
  }

  auto app_benchmark_get_standalone_result() -> bool
  {
    volatile auto result_is_ok =
      (app_benchmark_standalone_result == static_cast<std::uint32_t>(UINT32_C(0xF00DCAFE)));

    return result_is_ok;
  }
}

auto main() -> int
{
  auto result_is_ok = true;

  result_is_ok = (::app_benchmark_run_standalone       () && result_is_ok);
  result_is_ok = (::app_benchmark_get_standalone_result() && result_is_ok);

  return (result_is_ok ? 0 : -1);
}

extern "C"
{
  volatile std::uint32_t app_benchmark_standalone_result;
}
#endif // APP_BENCHMARK_STANDALONE_MAIN

#endif // APP_BENCHMARK_TYPE_CNL_SCALED_INTEGER
