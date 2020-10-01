///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2013 - 2020.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <cstdint>

#include <app/benchmark/app_benchmark.h>

#if(APP_BENCHMARK_TYPE == APP_BENCHMARK_TYPE_HASH)

#include <math/checksums/hash/hash_sha1.h>
#include <mcal_memory/mcal_memory_progmem_array.h>

bool app::benchmark::run_hash()
{
  using hash_type = math::checksums::hash::hash_sha1<std::uint8_t>;

  static const std::array<std::uint8_t, 3U> app_benchmark_hash_data =
  {{
    (std::uint8_t) ((char) 'a'),
    (std::uint8_t) ((char) 'b'),
    (std::uint8_t) ((char) 'c')
  }};

  static const mcal::memory::progmem::array<std::uint8_t,
                                            std::tuple_size<typename hash_type::result_type>::value>
  app_benchmark_hash_result MY_PROGMEM =
  {{
    0xA9U, 0x99U, 0x3EU, 0x36U, 0x47U, 0x06U, 0x81U, 0x6AU,
    0xBAU, 0x3EU, 0x25U, 0x71U, 0x78U, 0x50U, 0xC2U, 0x6CU,
    0x9CU, 0xD0U, 0xD8U, 0x9DU
  }};

  hash_type h;

  h.hash(app_benchmark_hash_data.data(),
         (typename hash_type::count_type) app_benchmark_hash_data.size());

  typename hash_type::result_type r;

  h.get_result(r.data());

  const bool result_is_ok = std::equal(app_benchmark_hash_result.cbegin(),
                                       app_benchmark_hash_result.cend(),
                                       r.cbegin());

  return result_is_ok;
}

#endif // APP_BENCHMARK_TYPE_CRC
