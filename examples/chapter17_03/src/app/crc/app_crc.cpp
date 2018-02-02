///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2017 - 2018.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <algorithm>
#include <array>
#include <cstdint>

#include <math/checksums/crc/cpp_crc.h>
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

  math::checksums::crc::cpp_crc08 app_cpp_crc08;
  math::checksums::crc::cpp_crc16 app_cpp_crc16;
  math::checksums::crc::cpp_crc32 app_cpp_crc32;
  math::checksums::crc::cpp_crc64 app_cpp_crc64;

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
  const std::array<math::checksums::crc::cpp_crc_base*, 4U> checksums =
  {{
    &app_cpp_crc08,
    &app_cpp_crc16,
    &app_cpp_crc32,
    &app_cpp_crc64
  }};

  // Calculate and verify the 8-bit, 16-bit,
  // 32-bit and 64-bit CRC.

  std::for_each(checksums.begin(),
                checksums.end(),
                [](math::checksums::crc::cpp_crc_base* my_crc)
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
    (   (checksums[0U]->get_result<std::uint8_t> () == UINT8_C (0xDF))
     && (checksums[1U]->get_result<std::uint16_t>() == UINT16_C(0x29B1))
     && (checksums[2U]->get_result<std::uint32_t>() == UINT32_C(0x1697D06A))
     && (checksums[3U]->get_result<std::uint64_t>() == UINT64_C(0x995DC9BBDF1939FA)));

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
