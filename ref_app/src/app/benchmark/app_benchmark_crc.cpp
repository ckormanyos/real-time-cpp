#include <array>
#include <cstdint>

#include <app/benchmark/app_benchmark.h>
#include <math/checksums/crc/crc32.h>
#include <mcal_memory/mcal_memory_progmem_array.h>

bool app::benchmark::run_crc()
{
  static const mcal::memory::progmem::array<std::uint8_t, 9U> app_benchmark_crc_data MY_PROGMEM =
  {{
    0x31U, 0x32U, 0x33U, 0x34U, 0x35U, 0x36U, 0x37U, 0x38U, 0x39U
  }};

  const std::uint32_t app_benchmark_crc =
    math::checksums::crc::crc32_mpeg2(app_benchmark_crc_data.cbegin(),
                                      app_benchmark_crc_data.cend());

  const bool result_is_ok = (app_benchmark_crc == UINT32_C(0x0376E6E7));

  return result_is_ok;
}
