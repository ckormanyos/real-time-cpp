///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2021 - 2022.
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
#define WIDE_DECIMAL_DISABLE_USE_STD_FUNCTION
#define WIDE_DECIMAL_NAMESPACE ckormanyos

#include <math/wide_decimal/decwide_t.h>
#include <mcal_memory/mcal_memory_progmem_array.h>
#include <util/memory/util_n_slot_array_allocator.h>

// Define APP_BENCHMARK_TYPE_PI_AGM_USES_101_DIGITS in order
// to go up to 101 decimal digits in the pi AGM calculation.
// If this is done, however, the AVR target needs a bit more RAM,
// which can be subtracted from the ample stack in the LD file.

// When using 101 decmial digits on the AVR, also consider
// switching the optimization level to -O2 in order to speed
// up the calculation a bit.

// Benchmarks (with -O2) on AVR show about 200ms needed
// for 53 decimal digits, whereas about 480ms are needed
// for the 101 decimal digit calculation.

//#define APP_BENCHMARK_TYPE_PI_AGM_USES_101_DIGITS

auto app::benchmark::run_pi_agm() -> bool
{
  using local_limb_type = std::uint16_t;

  #if defined(APP_BENCHMARK_TYPE_PI_AGM_USES_101_DIGITS)
  constexpr auto wide_decimal_digits10 = static_cast<std::int32_t>(INT8_C(101));
  #else
  constexpr auto wide_decimal_digits10 = static_cast<std::int32_t>(INT8_C(53));
  #endif

  #if defined(WIDE_DECIMAL_NAMESPACE)
  constexpr auto local_elem_number =
    WIDE_DECIMAL_NAMESPACE::math::wide_decimal::detail::decwide_t_helper<wide_decimal_digits10, local_limb_type>::elem_number;
  #else
  constexpr auto local_elem_number =
    math::wide_decimal::detail::decwide_t_helper<wide_decimal_digits10, local_limb_type>::elem_number;
  #endif

  using local_allocator_type = util::n_slot_array_allocator<void, local_elem_number, 18U>;

  #if defined(WIDE_DECIMAL_NAMESPACE)
  using local_wide_decimal_type = WIDE_DECIMAL_NAMESPACE::math::wide_decimal::decwide_t<wide_decimal_digits10,
                                                                                        local_limb_type,
                                                                                        local_allocator_type,
                                                                                        float,
                                                                                        std::int16_t,
                                                                                        float>;
  #else
  using local_wide_decimal_type = math::wide_decimal::decwide_t<wide_decimal_digits10,
                                                local_limb_type,
                                                local_allocator_type,
                                                float,
                                                std::int16_t,
                                                float>;
  #endif

  // Use the Wolfram Alpha expression:
  //   N[Pi, 106] and truncate the final digit.

  #if defined(APP_BENCHMARK_TYPE_PI_AGM_USES_101_DIGITS)
  static const mcal::memory::progmem::array<typename local_wide_decimal_type::limb_type, 26U> app_benchmark_pi_agm_control MY_PROGMEM =
  #else
  static const mcal::memory::progmem::array<typename local_wide_decimal_type::limb_type, 14U> app_benchmark_pi_agm_control MY_PROGMEM =
  #endif
  {{
    static_cast<local_limb_type>(UINT16_C(   3)),
    static_cast<local_limb_type>(UINT16_C(1415)),
    static_cast<local_limb_type>(UINT16_C(9265)),
    static_cast<local_limb_type>(UINT16_C(3589)),
    static_cast<local_limb_type>(UINT16_C(7932)),
    static_cast<local_limb_type>(UINT16_C(3846)),
    static_cast<local_limb_type>(UINT16_C(2643)),
    static_cast<local_limb_type>(UINT16_C(3832)),
    static_cast<local_limb_type>(UINT16_C(7950)),
    static_cast<local_limb_type>(UINT16_C(2884)),
    static_cast<local_limb_type>(UINT16_C(1971)),
    static_cast<local_limb_type>(UINT16_C(6939)),
    static_cast<local_limb_type>(UINT16_C(9375)),
    static_cast<local_limb_type>(UINT16_C(1058)),
    #if defined(APP_BENCHMARK_TYPE_PI_AGM_USES_101_DIGITS)
    static_cast<local_limb_type>(UINT16_C(2097)),
    static_cast<local_limb_type>(UINT16_C(4944)),
    static_cast<local_limb_type>(UINT16_C(5923)),
    static_cast<local_limb_type>(UINT16_C( 781)),
    static_cast<local_limb_type>(UINT16_C(6406)),
    static_cast<local_limb_type>(UINT16_C(2862)),
    static_cast<local_limb_type>(UINT16_C( 899)),
    static_cast<local_limb_type>(UINT16_C(8628)),
    static_cast<local_limb_type>(UINT16_C( 348)),
    static_cast<local_limb_type>(UINT16_C(2534)),
    static_cast<local_limb_type>(UINT16_C(2117)),
    static_cast<local_limb_type>(UINT16_C( 679))
    #endif
  }};

  #if defined(WIDE_DECIMAL_NAMESPACE)
  const local_wide_decimal_type my_pi =
    WIDE_DECIMAL_NAMESPACE::math::wide_decimal::pi<wide_decimal_digits10,
                                                   local_limb_type,
                                                   local_allocator_type,
                                                   float,
                                                   std::int16_t,
                                                   float>();
  #else
  const local_wide_decimal_type my_pi =
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
