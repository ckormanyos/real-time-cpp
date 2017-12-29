///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2017 - 2018.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <algorithm>
#include <any>
#include <array>
#include <cstdint>

#include <math/checksums/crc/crc_autosar.h>
#include <mcal_benchmark.h>
#include <mcal_cpu.h>
#include <mcal_irq.h>
#include <util/utility/util_time.h>

namespace app
{
  namespace crc
  {
    void task_init();
    void task_func();
  }
}

namespace
{
  std::array<std::uint8_t, 9U> app_crc_test_values;

  math::checksums::crc::crc08_autosar app_crc_autosar_crc08;
  math::checksums::crc::crc16_autosar app_crc_autosar_crc16;
  math::checksums::crc::crc32_autosar app_crc_autosar_crc32;
  math::checksums::crc::crc64_autosar app_crc_autosar_crc64;

  using app_crc_measurement_port_type = mcal::benchmark::benchmark_port_type;

  using app_crc_timer_type = util::timer<std::uint_fast16_t>;
}

void app::crc::task_init()
{
  // Initialize the test values to 0x31, ..., 0x39.
  std::uint_fast8_t i = UINT8_C(1);

  std::generate_n(app_crc_test_values.begin(),
                  app_crc_test_values.size(),
                  [&i]() -> std::uint_fast8_t
                  {
                    const std::uint_fast8_t value = UINT8_C(0x30) + i;

                    ++i;

                    return std::uint8_t(value);
                  });

  // Set the CRC port measurement pin to output
  app_crc_measurement_port_type::set_direction_output();
}

void app::crc::task_func()
{
  // Create an array of 4 crc_base class pointers.
  std::array<math::checksums::crc::crc_base*, 4U> checksums =
  {{
    &app_crc_autosar_crc08,
    &app_crc_autosar_crc16,
    &app_crc_autosar_crc32,
    &app_crc_autosar_crc64
  }};

  // Create an array of std::any containing
  // the 8, 16, 32, 64 bit CRC control values.
  const std::array<std::any, 4U> control_values =
  {{
    std::uint8_t (UINT8_C (0xDF)),
    std::uint16_t(UINT16_C(0x29B1)),
    std::uint32_t(UINT32_C(0x1697D06A)),
    std::uint64_t(UINT64_C(0x995DC9BBDF1939FA))
  }};

  // Calculate and verify the 8-bit, 16-bit,
  // 32-bit and 64-bit CRC.

  std::for_each(checksums.begin(),
                checksums.end(),
                [](math::checksums::crc::crc_base* my_crc)
                {
                  // Disable all interrupts before each calculation
                  // in order to provide for a clean time measurement.
                  mcal::irq::disable_all();

                  // Use a port pin to provide a real-time measurement.
                  app_crc_measurement_port_type::set_pin_high();

                  my_crc->initialize();

                  my_crc->process_bytes(app_crc_test_values.data(),
                                        app_crc_test_values.size());

                  my_crc->finalize();

                  app_crc_measurement_port_type::set_pin_low();

                  // Remember to enable all interrupts after the calculation.
                  mcal::irq::enable_all();

                  // Insert a 10us delay after each calculation
                  // in order to separate the individual time measurements
                  // for observation with an oscilloscope.
                  app_crc_timer_type::blocking_delay(app_crc_timer_type::microseconds(10U));
                });

  // Verify all CRC results.
  const volatile bool results_are_ok =
    (   (checksums[0U]->get_result<std::uint8_t> () == std::any_cast<std::uint8_t> (control_values[0U]))
     && (checksums[1U]->get_result<std::uint16_t>() == std::any_cast<std::uint16_t>(control_values[1U]))
     && (checksums[2U]->get_result<std::uint32_t>() == std::any_cast<std::uint32_t>(control_values[2U]))
     && (checksums[3U]->get_result<std::uint64_t>() == std::any_cast<std::uint64_t>(control_values[3U])));

  if(results_are_ok == false)
  {
    // The CRC results are not OK.

    for(;;)
    {
      // Crash the system and toggle a port
      // to provide an indication of failure.

      app_crc_measurement_port_type::toggle_pin();

      mcal::cpu::nop();
    }
  }
}
