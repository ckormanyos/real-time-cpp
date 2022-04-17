///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2020 - 2022.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <cmath>
#include <cstdint>

#include <app/benchmark/app_benchmark.h>

#if(APP_BENCHMARK_TYPE == APP_BENCHMARK_TYPE_WIDE_DECIMAL)

#define WIDE_DECIMAL_DISABLE_IOSTREAM
#define WIDE_DECIMAL_DISABLE_DYNAMIC_MEMORY_ALLOCATION
#define WIDE_DECIMAL_DISABLE_CONSTRUCT_FROM_STRING
#define WIDE_DECIMAL_DISABLE_CACHED_CONSTANTS
#define WIDE_DECIMAL_DISABLE_USE_STD_FUNCTION
#define WIDE_DECIMAL_NAMESPACE ckormanyos

#include <math/wide_decimal/decwide_t.h>
#include <util/memory/util_n_slot_array_allocator.h>

auto app::benchmark::run_wide_decimal() -> bool
{
  using local_limb_type = std::uint16_t;

  constexpr std::int32_t wide_decimal_digits10 = INT32_C(101);

  #if defined(WIDE_DECIMAL_NAMESPACE)
  constexpr std::int32_t local_elem_number =
    WIDE_DECIMAL_NAMESPACE::math::wide_decimal::detail::decwide_t_helper<wide_decimal_digits10, local_limb_type>::elem_number;
  #else
  constexpr std::int32_t local_elem_number =
    math::wide_decimal::detail::decwide_t_helper<wide_decimal_digits10, local_limb_type>::elem_number;
  #endif

  using local_allocator_type = util::n_slot_array_allocator<void, local_elem_number, 14U>;

  #if defined(WIDE_DECIMAL_NAMESPACE)
  using dec101_t = WIDE_DECIMAL_NAMESPACE::math::wide_decimal::decwide_t<wide_decimal_digits10, local_limb_type, local_allocator_type, float>;
  #else
  using dec101_t = math::wide_decimal::decwide_t<wide_decimal_digits10, local_limb_type, local_allocator_type, float>;
  #endif

  const dec101_t s = sqrt(dec101_t(123456U) / 100);

  // N[Sqrt[123456/100], 111]
  // 35.1363060095963986639333846404180557597515182871693145281659761647177108954528909286350312191322209780537650946

  dec101_t control;

  typename dec101_t::representation_type rep
  (
    { 35U, 1363U, 600U, 9596U, 3986U, 6393U, 3384U, 6404U, 1805U, 5759U, 7515U, 1828U, 7169U, 3145U, 2816U, 5976U, 1647U, 1771U, 895U, 4528U, 9092U, 8635U, 312U, 1913U, 2220U, 9780U }
  );

  std::copy(rep.cbegin(), rep.cend(), control.representation().begin());

  using std::fabs;

  const dec101_t closeness = fabs(1 - (s / control));

  const bool result_is_ok = closeness < (std::numeric_limits<dec101_t>::epsilon() * 10);

  return result_is_ok;
}

#if defined(APP_BENCHMARK_STANDALONE_MAIN)
int main()
{
  // g++ -Wall -O3 -march=native -I./ref_app/src/mcal/host -I./ref_app/src -DAPP_BENCHMARK_TYPE=APP_BENCHMARK_TYPE_WIDE_DECIMAL -DAPP_BENCHMARK_STANDALONE_MAIN ./ref_app/src/app/benchmark/app_benchmark_wide_decimal.cpp -o ./ref_app/bin/app_benchmark_wide_decimal.exe

  bool result_is_ok = true;

  for(unsigned i = 0U; i < 64U; ++i)
  {
    result_is_ok &= app::benchmark::run_wide_decimal();
  }

  return result_is_ok ? 0 : -1;
}
#endif

#endif // APP_BENCHMARK_TYPE_WIDE_DECIMAL
