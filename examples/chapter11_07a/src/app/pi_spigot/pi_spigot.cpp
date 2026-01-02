///////////////////////////////////////////////////////////////////
//                                                               //
//  Copyright Iliass Mahjoub 2022.                               //
//  Copyright Christopher Kormanyos 2019 - 2026.                 //
//  Distributed under the Boost Software License,                //
//  Version 1.0. (See accompanying file LICENSE_1_0.txt          //
//  or copy at http://www.boost.org/LICENSE_1_0.txt)             //
//                                                               //
///////////////////////////////////////////////////////////////////

// This program can be used to compute many thousands
// of decimal digits of digits of pi. It uses a so-called
// "spigot" algorithm having quadratic complexity.

#include <pi_calc_cfg.h>

#include <math/checksums/hash/hash_sha1.h>
#include <math/pi_spigot/pi_spigot.h>
#include <mcal_benchmark.h>
#include <mcal_memory/mcal_memory_sram_array.h>
#include <util/utility/util_baselexical_cast.h>

namespace local
{
  #if defined(PI_CRUNCH_METAL_PI_SPIGOT_DIGITS)
    #if (PI_CRUNCH_METAL_PI_SPIGOT_DIGITS == PI_CRUNCH_METAL_PI_SPIGOT_USE_100_DIGITS)
    constexpr auto result_digit = static_cast<std::uint32_t>(UINT32_C(101));
    #elif (PI_CRUNCH_METAL_PI_SPIGOT_DIGITS == PI_CRUNCH_METAL_PI_SPIGOT_USE_1K_DIGITS)
    constexpr auto result_digit = static_cast<std::uint32_t>(UINT32_C(1001));
    #elif (PI_CRUNCH_METAL_PI_SPIGOT_DIGITS == PI_CRUNCH_METAL_PI_SPIGOT_USE_10K_DIGITS)
    constexpr auto result_digit = static_cast<std::uint32_t>(UINT32_C(10001));
    #elif (PI_CRUNCH_METAL_PI_SPIGOT_DIGITS == PI_CRUNCH_METAL_PI_SPIGOT_USE_100K_DIGITS)
    constexpr auto result_digit = static_cast<std::uint32_t>(UINT32_C(100001));
    #endif
  #else
    #error Error: Please define PI_CRUNCH_METAL_PI_SPIGOT_DIGITS
  #endif

  constexpr auto loop_digit = static_cast<std::uint32_t>(UINT8_C(9));

  using pi_spigot_type = math::constants::pi_spigot<result_digit, loop_digit>;

  auto pi_spigot_instance() -> pi_spigot_type&;

  auto pi_spigot_instance() -> pi_spigot_type&
  {
    static pi_spigot_type instance { };

    return instance;
  }

  auto pi_output_digits10 = std::uint32_t { UINT8_C(0) };

  using benchmark_port_type = ::mcal::benchmark::benchmark_port_type;

  constexpr auto pi_spigot_input_start_address = mcal_sram_uintptr_t { UINT8_C(0) };

  using pi_spigot_input_container_type = mcal::memory::sram::array<std::uint32_t,
                                                                   pi_spigot_type::get_input_static_size(),
                                                                   pi_spigot_input_start_address>;

  auto pi_spigot_input() -> pi_spigot_input_container_type&;

  auto pi_spigot_input() -> pi_spigot_input_container_type&
  {
    static pi_spigot_input_container_type container_instance { };

    return container_instance;
  }

  using hash_type = math::checksums::hash::hash_sha1;
  using hash_result_type = typename hash_type::result_type;

  auto pi_spigot_hash() -> hash_type&;

  auto pi_spigot_hash() -> hash_type&
  {
    static hash_type hash_instance { };

    return hash_instance;
  }
} // namespace local

extern auto pi_lcd_progress(const std::uint32_t pi_output_digits10) -> void;

auto pi_count_of_calculations() -> std::uint32_t;
auto pi_main() -> int;

auto pi_count_of_calculations() -> std::uint32_t
{
  return local::pi_spigot_type::get_count_of_calculations();
}

auto pi_main() -> int
{
  local::benchmark_port_type::toggle_pin();

  auto& local_pi_spigot_instance { local::pi_spigot_instance() };

  auto& local_container_instance { local::pi_spigot_input() };

  auto& local_hash { local::pi_spigot_hash() };

  local_pi_spigot_instance.calculate(local_container_instance.data(), pi_lcd_progress, &local_hash);

  // Check the hash result of the pi calculation.
  constexpr local::hash_result_type hash_control
    #if (PI_CRUNCH_METAL_PI_SPIGOT_DIGITS == PI_CRUNCH_METAL_PI_SPIGOT_USE_100_DIGITS)
    {
      0x93U, 0xF1U, 0xB4U, 0xEAU, 0xABU, 0xCBU, 0xC9U, 0xB9U,
      0x0CU, 0x93U, 0x93U, 0x24U, 0xF7U, 0x85U, 0x13U, 0x2EU,
      0xDFU, 0x3BU, 0xF2U, 0x01U
    };
    #elif (PI_CRUNCH_METAL_PI_SPIGOT_DIGITS == PI_CRUNCH_METAL_PI_SPIGOT_USE_1K_DIGITS)
    {
      0xA0U, 0x92U, 0x47U, 0x1FU, 0xD5U, 0xFEU, 0x41U, 0x51U,
      0x20U, 0xE7U, 0xDDU, 0x18U, 0x5BU, 0x93U, 0x0DU, 0x05U,
      0x3AU, 0x86U, 0xF1U, 0x7EU
    };
    #elif (PI_CRUNCH_METAL_PI_SPIGOT_DIGITS == PI_CRUNCH_METAL_PI_SPIGOT_USE_10K_DIGITS)
    {
      // 10001: 4BDF69A5FF25B9BED6BA9802BD2A68306FAB71EC
      0x4BU, 0xDFU, 0x69U, 0xA5U, 0xFFU, 0x25U, 0xB9U, 0xBEU,
      0xD6U, 0xBAU, 0x98U, 0x02U, 0xBDU, 0x2AU, 0x68U, 0x30U,
      0x6FU, 0xABU, 0x71U, 0xECU
    };
    #elif (PI_CRUNCH_METAL_PI_SPIGOT_DIGITS == PI_CRUNCH_METAL_PI_SPIGOT_USE_100K_DIGITS)
    {
      // 100001: D9D56240EB6B626A8FE179E3054D332F1767071D
      0xD9U, 0xD5U, 0x62U, 0x40U, 0xEBU, 0x6BU, 0x62U, 0x6AU,
      0x8FU, 0xE1U, 0x79U, 0xE3U, 0x05U, 0x4DU, 0x33U, 0x2FU,
      0x17U, 0x67U, 0x07U, 0x1DU
    };
    #endif

  local::hash_result_type hash_result { };

  local_hash.get_result(hash_result.data());

  const bool result_is_ok { std::equal(hash_result.cbegin(), hash_result.cend(), hash_control.cbegin()) };

  const int result_of_pi_main { (result_is_ok ? static_cast<int>(INT8_C(0)) : static_cast<int>(INT8_C(-1))) };

  return result_of_pi_main;
}
