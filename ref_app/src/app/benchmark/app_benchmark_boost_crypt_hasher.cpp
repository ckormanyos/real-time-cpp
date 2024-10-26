///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2024.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <cstdint>

#include <app/benchmark/app_benchmark.h>

#if (defined(APP_BENCHMARK_TYPE) && (APP_BENCHMARK_TYPE == APP_BENCHMARK_TYPE_BOOST_CRYPT_HASHER))

#if !defined(BOOST_CRYPT_STANDALONE)
#define BOOST_CRYPT_STANDALONE
#endif

#if !defined(BOOST_CRYPT_DISABLE_IOSTREAM)
#define BOOST_CRYPT_DISABLE_IOSTREAM
#endif

#if !defined(BOOST_CRYPT_NO_EXCEPTIONS)
#define BOOST_CRYPT_NO_EXCEPTIONS
#endif

#include <boost/crypt/hash/sha512.hpp>

auto app::benchmark::run_boost_crypt_hasher() -> bool
{
  // "abc"
  const std::array<std::uint8_t, 3U> message =
  {{
    0x61U, 0x62U, 0x63U
  }};

  using local_hasher_type = boost::crypt::sha512_hasher;
  using local_result_type = typename local_hasher_type::return_type;

  constexpr local_result_type control = 
  {{
    0xDDU, 0xAFU, 0x35U, 0xA1U, 0x93U, 0x61U, 0x7AU, 0xBAU,
    0xCCU, 0x41U, 0x73U, 0x49U, 0xAEU, 0x20U, 0x41U, 0x31U,
    0x12U, 0xE6U, 0xFAU, 0x4EU, 0x89U, 0xA9U, 0x7EU, 0xA2U,
    0x0AU, 0x9EU, 0xEEU, 0xE6U, 0x4BU, 0x55U, 0xD3U, 0x9AU,
    0x21U, 0x92U, 0x99U, 0x2AU, 0x27U, 0x4FU, 0xC1U, 0xA8U,
    0x36U, 0xBAU, 0x3CU, 0x23U, 0xA3U, 0xFEU, 0xEBU, 0xBDU,
    0x45U, 0x4DU, 0x44U, 0x23U, 0x64U, 0x3CU, 0xE8U, 0x0EU,
    0x2AU, 0x9AU, 0xC9U, 0x4FU, 0xA5U, 0x4CU, 0xA4U, 0x9FU,
  }};

  local_hasher_type my_hasher { };

  my_hasher.init();

  my_hasher.process_bytes(message.data(), message.size());

  const local_result_type result { my_hasher.get_digest() };

  const bool result_is_ok { result == control };

  return result_is_ok;
}

#if defined(APP_BENCHMARK_STANDALONE_MAIN)
constexpr auto app_benchmark_standalone_foodcafe = static_cast<std::uint32_t>(UINT32_C(0xF00DCAFE));

extern "C"
{
  extern volatile std::uint32_t app_benchmark_standalone_result;

  auto app_benchmark_run_standalone       (void) -> bool;
  auto app_benchmark_get_standalone_result(void) -> bool;

  auto app_benchmark_run_standalone(void) -> bool
  {
    auto result_is_ok = true;

    for(unsigned i = 0U; i < 64U; ++i)
    {
      result_is_ok &= app::benchmark::run_boost_crypt_hasher();
    }

    app_benchmark_standalone_result =
      static_cast<std::uint32_t>
      (
        result_is_ok ? app_benchmark_standalone_foodcafe : static_cast<std::uint32_t>(UINT32_C(0xFFFFFFFF))
      );

    return result_is_ok;
  }

  auto app_benchmark_get_standalone_result(void) -> bool
  {
    volatile auto result_is_ok =
      (app_benchmark_standalone_result == static_cast<std::uint32_t>(UINT32_C(0xF00DCAFE)));

    return result_is_ok;
  }
}

int main()
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

#endif // APP_BENCHMARK_TYPE_CRC
