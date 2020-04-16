///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2017 - 2018.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <array>

#include <mcal_benchmark.h>
#include <mcal_cpu.h>
#include <mcal_irq.h>
#include <mcal_memory/mcal_memory_progmem_array.h>
#include <math/checksums/crc/crc32.h>

namespace app
{
  namespace benchmark
  {
    void task_init();
    void task_func();
  }
}

namespace
{
  using app_crc_measurement_port_type = mcal::benchmark::benchmark_port_type;
}

void app::benchmark::task_init()
{
  // Set the CRC port measurement pin to output
  app_crc_measurement_port_type::set_direction_output();
}

void app::benchmark::task_func()
{
  static const mcal::memory::progmem::array<std::uint8_t, 9U> app_benchmark_crc_data MY_PROGMEM =
  {{
    0x31U, 0x32U, 0x33U, 0x34U, 0x35U, 0x36U, 0x37U, 0x38U, 0x39U
  }};

  // Disable all interrupts before each calculation
  // in order to provide for a clean time measurement.
  mcal::irq::disable_all();

  // Use a port pin to provide a real-time measurement.
  app_crc_measurement_port_type::set_pin_high();

  // Perform the CRC32-MPEG2 calculation.
  const std::uint32_t app_benchmark_crc_result =
    math::checksums::crc::crc32_mpeg2(app_benchmark_crc_data.cbegin(),
                                      app_benchmark_crc_data.cend());

  app_crc_measurement_port_type::set_pin_low();

  // Remember to enable all interrupts after the calculation.
  mcal::irq::enable_all();

  // Verify the CRC result.
  const bool results_are_ok = (app_benchmark_crc_result == UINT32_C(0x0376E6E7));

  if(results_are_ok == false)
  {
    // The CRC result is not OK.

    for(;;)
    {
      // Crash the system and toggle a port
      // to provide an indication of failure.

      app_crc_measurement_port_type::toggle_pin();

      mcal::cpu::nop();
    }
  }
}
