///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2013 - 2023.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <app/benchmark/app_benchmark.h>

#if (defined(APP_BENCHMARK_TYPE) && (APP_BENCHMARK_TYPE == APP_BENCHMARK_TYPE_HASH_SHA256))

#include <math/checksums/hash/hash_sha256.h>
#include <mcal_memory/mcal_memory_progmem_array.h>

namespace
{
  using app_benchmark_hash_type = math::checksums::hash::hash_sha256<std::uint_fast16_t>;

  app_benchmark_hash_type app_benchmark_hash_object;

  using app_benchmark_hash_count_type  = typename app_benchmark_hash_type::count_type;
  using app_benchmark_hash_result_type = typename app_benchmark_hash_type::result_type;

  const mcal::memory::progmem::array<std::uint8_t, std::tuple_size<app_benchmark_hash_result_type>::value>
  app_benchmark_hash_ctrl MY_PROGMEM =
  {
    0xBAU, 0x78U, 0x16U, 0xBFU, 0x8FU, 0x01U, 0xCFU, 0xEAU,
    0x41U, 0x41U, 0x40U, 0xDEU, 0x5DU, 0xAEU, 0x22U, 0x23U,
    0xB0U, 0x03U, 0x61U, 0xA3U, 0x96U, 0x17U, 0x7AU, 0x9CU,
    0xB4U, 0x10U, 0xFFU, 0x61U, 0xF2U, 0x00U, 0x15U, 0xADU
  };
}

auto app::benchmark::run_hash_sha256() -> bool
{
  static constexpr std::array<std::uint8_t, static_cast<std::size_t>(UINT8_C(3))> app_benchmark_hash_data =
  {
    static_cast<std::uint8_t>('a'),
    static_cast<std::uint8_t>('b'),
    static_cast<std::uint8_t>('c')
  };

  app_benchmark_hash_object.hash(app_benchmark_hash_data.data(),
                                 static_cast<app_benchmark_hash_count_type>(app_benchmark_hash_data.size()));

  auto local_hash_result = app_benchmark_hash_result_type { };

  app_benchmark_hash_object.get_result(local_hash_result.data());

  const auto result_is_ok = std::equal(app_benchmark_hash_ctrl.cbegin(),
                                       app_benchmark_hash_ctrl.cend(),
                                       local_hash_result.cbegin());

  return result_is_ok;
}

#if defined(APP_BENCHMARK_STANDALONE_MAIN)
auto main() -> int;

auto main() -> int
{
  // g++ -Wall -O3 -march=native -I./ref_app/src/mcal/host -I./ref_app/src -DAPP_BENCHMARK_TYPE=APP_BENCHMARK_TYPE_HASH_SHA256 -DAPP_BENCHMARK_STANDALONE_MAIN ./ref_app/src/app/benchmark/app_benchmark_hash.cpp -o ./ref_app/bin/app_benchmark_hash.exe

  auto result_is_ok = true;

  for(auto i = static_cast<unsigned>(UINT8_C(0)); i < static_cast<unsigned>(UINT8_C(64)); ++i)
  {
    result_is_ok = (app::benchmark::run_hash_sha256() && result_is_ok);
  }

  return (result_is_ok ? 0 : -1);
}
#endif

#endif // APP_BENCHMARK_TYPE_HASH_SHA256
