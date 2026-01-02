///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2013 - 2026.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <app/benchmark/app_benchmark.h>

#if (defined(APP_BENCHMARK_TYPE) && (APP_BENCHMARK_TYPE == APP_BENCHMARK_TYPE_HASH))

#include <math/checksums/hash/hash_sha1.h>

#include <array>

namespace
{
  using app_benchmark_hash_type = math::checksums::hash::hash_sha1;

  app_benchmark_hash_type app_benchmark_hash_object;

  using app_benchmark_hash_count_type  = typename app_benchmark_hash_type::count_type;
  using app_benchmark_hash_result_type = typename app_benchmark_hash_type::result_type;

  constexpr std::array<std::uint8_t, std::tuple_size<app_benchmark_hash_result_type>::value>
  app_benchmark_hash_ctrl =
  {
    0xA9U, 0x99U, 0x3EU, 0x36U, 0x47U, 0x06U, 0x81U, 0x6AU,
    0xBAU, 0x3EU, 0x25U, 0x71U, 0x78U, 0x50U, 0xC2U, 0x6CU,
    0x9CU, 0xD0U, 0xD8U, 0x9DU
  };
}

auto app::benchmark::run_hash() -> bool
{
  using app_benchmark_msg_array_type = std::array<std::uint8_t, static_cast<std::size_t>(UINT8_C(3))>;

  constexpr app_benchmark_msg_array_type app_benchmark_hash_msg =
  {
    static_cast<std::uint8_t>('a'),
    static_cast<std::uint8_t>('b'),
    static_cast<std::uint8_t>('c')
  };

  app_benchmark_hash_object.hash(app_benchmark_hash_msg.data(),
                                 static_cast<app_benchmark_hash_count_type>(std::tuple_size<app_benchmark_msg_array_type>::value));

  app_benchmark_hash_result_type local_hash_result { };

  app_benchmark_hash_object.get_result(local_hash_result.data());

  const auto result_is_ok = std::equal(app_benchmark_hash_ctrl.cbegin(),
                                       app_benchmark_hash_ctrl.cend(),
                                       local_hash_result.cbegin());

  return result_is_ok;
}

#if defined(APP_BENCHMARK_STANDALONE_MAIN)
ATTRIBUTE(used) auto main() -> int;

auto main() -> int
{
  // g++ -Wall -O3 -march=native -I./ref_app/src/mcal/host -I./ref_app/src -DAPP_BENCHMARK_TYPE=APP_BENCHMARK_TYPE_HASH -DAPP_BENCHMARK_STANDALONE_MAIN ./ref_app/src/app/benchmark/app_benchmark_hash.cpp -o ./ref_app/bin/app_benchmark_hash.exe

  auto result_is_ok = true;

  for(auto i = static_cast<unsigned>(UINT8_C(0)); i < static_cast<unsigned>(UINT8_C(64)); ++i)
  {
    result_is_ok = (app::benchmark::run_hash() && result_is_ok);
  }

  return (result_is_ok ? 0 : -1);
}
#endif

#endif // APP_BENCHMARK_TYPE_HASH
