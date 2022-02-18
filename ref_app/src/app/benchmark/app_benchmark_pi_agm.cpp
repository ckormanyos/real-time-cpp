///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2021.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <cmath>
#include <cstdint>

#include <app/benchmark/app_benchmark.h>

#if(APP_BENCHMARK_TYPE == APP_BENCHMARK_TYPE_PI_AGM)

#define WIDE_DECIMAL_DISABLE_IOSTREAM
#define WIDE_DECIMAL_DISABLE_DYNAMIC_MEMORY_ALLOCATION
#define WIDE_DECIMAL_DISABLE_CONSTRUCT_FROM_STRING
#define WIDE_DECIMAL_DISABLE_CACHED_CONSTANTS
#define WIDE_DECIMAL_NAMESPACE ckormanyos

#include <math/wide_decimal/decwide_t.h>
#include <mcal_memory/mcal_memory_progmem_array.h>
#include <util/memory/util_n_slot_array_allocator.h>

bool app::benchmark::run_pi_agm()
{
  // N[Pi, 106] and truncate the final digit.
  using local_limb_type = std::uint16_t;

  constexpr std::int32_t wide_decimal_digits10 = INT32_C(53);

  #if defined(WIDE_DECIMAL_NAMESPACE)
  constexpr std::int32_t local_elem_number =
    WIDE_DECIMAL_NAMESPACE::math::wide_decimal::detail::decwide_t_helper<wide_decimal_digits10, local_limb_type>::elem_number;
  #else
  constexpr std::int32_t local_elem_number =
    math::wide_decimal::detail::decwide_t_helper<wide_decimal_digits10, local_limb_type>::elem_number;
  #endif

  using local_allocator_type = util::n_slot_array_allocator<void, local_elem_number, 18U>;

  #if defined(WIDE_DECIMAL_NAMESPACE)
  using dec53_t = WIDE_DECIMAL_NAMESPACE::math::wide_decimal::decwide_t<wide_decimal_digits10,
                                                                        local_limb_type,
                                                                        local_allocator_type,
                                                                        float,
                                                                        std::int16_t,
                                                                        float>;
  #else
  using dec53_t = math::wide_decimal::decwide_t<wide_decimal_digits10,
                                                local_limb_type,
                                                local_allocator_type,
                                                float,
                                                std::int16_t,
                                                float>;
  #endif

  static const mcal::memory::progmem::array<typename dec53_t::limb_type, 14U> app_benchmark_pi_agm_control MY_PROGMEM =
  {{
    static_cast<typename dec53_t::limb_type>(UINT16_C(   3)),
    static_cast<typename dec53_t::limb_type>(UINT16_C(1415)),
    static_cast<typename dec53_t::limb_type>(UINT16_C(9265)),
    static_cast<typename dec53_t::limb_type>(UINT16_C(3589)),
    static_cast<typename dec53_t::limb_type>(UINT16_C(7932)),
    static_cast<typename dec53_t::limb_type>(UINT16_C(3846)),
    static_cast<typename dec53_t::limb_type>(UINT16_C(2643)),
    static_cast<typename dec53_t::limb_type>(UINT16_C(3832)),
    static_cast<typename dec53_t::limb_type>(UINT16_C(7950)),
    static_cast<typename dec53_t::limb_type>(UINT16_C(2884)),
    static_cast<typename dec53_t::limb_type>(UINT16_C(1971)),
    static_cast<typename dec53_t::limb_type>(UINT16_C(6939)),
    static_cast<typename dec53_t::limb_type>(UINT16_C(9375)),
    static_cast<typename dec53_t::limb_type>(UINT16_C(1058))
  }};

  #if defined(WIDE_DECIMAL_NAMESPACE)
  const dec53_t my_pi =
    WIDE_DECIMAL_NAMESPACE::math::wide_decimal::pi<wide_decimal_digits10,
                                                   local_limb_type,
                                                   local_allocator_type,
                                                   float,
                                                   std::int16_t,
                                                   float>();
  #else
  const dec53_t my_pi =
    math::wide_decimal::pi<wide_decimal_digits10,
                           local_limb_type,
                           local_allocator_type,
                           float,
                           std::int16_t,
                           float>();
  #endif

  const bool result_is_ok = std::equal(app_benchmark_pi_agm_control.cbegin(),
                                       app_benchmark_pi_agm_control.cend(),
                                       my_pi.crepresentation().cbegin());

  return result_is_ok;
}

#if defined(APP_BENCHMARK_STANDALONE_MAIN)
int main()
{
  // g++ -Wall -O3 -march=native -I./ref_app/src/mcal/host -I./ref_app/src -DAPP_BENCHMARK_TYPE=APP_BENCHMARK_TYPE_PI_AGM -DAPP_BENCHMARK_STANDALONE_MAIN ./ref_app/src/app/benchmark/app_benchmark_pi_agm.cpp -o ./ref_app/bin/app_benchmark_pi_agm.exe

  bool result_is_ok = true;

  for(unsigned i = 0U; i < 64U; ++i)
  {
    result_is_ok &= app::benchmark::run_pi_agm();
  }

  return result_is_ok ? 0 : -1;
}
#endif

#endif // APP_BENCHMARK_TYPE_PI_AGM
