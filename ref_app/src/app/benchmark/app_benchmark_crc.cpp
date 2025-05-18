///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2019.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <cstdint>

#include <app/benchmark/app_benchmark.h>

#if (defined(APP_BENCHMARK_TYPE) && (APP_BENCHMARK_TYPE == APP_BENCHMARK_TYPE_CRC))

#include <math/checksums/crc/crc32.h>
#include <mcal_memory/mcal_memory_progmem_array.h>

auto app::benchmark::run_crc() -> bool
{
  static const mcal::memory::progmem::array<std::uint8_t, 9U> app_benchmark_crc_data MY_PROGMEM =
  {{
    0x31U, 0x32U, 0x33U, 0x34U, 0x35U, 0x36U, 0x37U, 0x38U, 0x39U
  }};

  const auto app_benchmark_crc =
    math::checksums::crc::crc32_mpeg2(app_benchmark_crc_data.cbegin(),
                                      app_benchmark_crc_data.cend());

  const auto result_is_ok = (app_benchmark_crc == static_cast<std::uint32_t>(UINT32_C(0x0376E6E7)));

  return result_is_ok;
}

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
      result_is_ok &= app::benchmark::run_crc();
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

ATTRIBUTE(used) auto main() -> int;

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

#endif // APP_BENCHMARK_TYPE_CRC
