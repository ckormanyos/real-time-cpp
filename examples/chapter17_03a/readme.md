# Example Chapter17_03a
# Traditional C-Language in Modern C++, Using Time Slices

Example chapter17_03a is almost identical with
example chapter17_03. It performs the same CRC calculations
and uses essentially the same code technical methods
for accessing traditional C-language code within a
modern C++ project. Example chapter17_03a, however,
distributes the CRC calculations over multitasking using
time slices to process one single byte at a time, per task schedule call.

# Application Description

The application task `app::crc::task_func()` implements a state machine
that performs initialization, data processing and finalization
of the CRC calculations and switches through the CRC calculation
schedule having widths of 8, 16, 32 and 64 bits.

The code of `app::crc::task_func()` from example17_03a
is shown below.

```cpp
void app::crc::task_func()
{
  // Calculate and verify the 8-bit, 16-bit,
  // 32-bit and 64-bit CRC.

  typedef enum app_crc_calculation_state
  {
    app_crc_calculation_state_initialize,
    app_crc_calculation_state_process_bytes,
    app_crc_calculation_state_finalize
  }
  app_crc_calculation_state_type;

  static app_crc_calculation_state_type app_crc_calculation_state =
    app_crc_calculation_state_initialize;

  static std::uint_fast8_t app_crc_process_data_byte_count;

  static std::uint_fast8_t app_crc_object_index;

  // On 8-bit target, take runtime statistics for the
  // state machine (averaged over all 8,16,32,64-bit CRCs,
  // all bytes and all states).
  //   * average 10.3us
  //   * low      3.4us
  //   * high    22  us.

  // Average load for CRC calculation only is:
  //   * 10.3us / 1ms = approx. 1%.
  //   * 36ms (total) needed to cycle through all 4 CRCs.

  // Disable all interrupts before each calculation
  // in order to provide for a clean time measurement.
  mcal::irq::disable_all();

  // Use a port pin to provide a real-time measurement.
  app_crc_measurement_port_type::set_pin_high();

  // Distribute the CRC calculations
  // over multitasking time slices.
  // Process one single byte at a time,

  switch(app_crc_calculation_state)
  {
    case app_crc_calculation_state_initialize:

      // Initialize the CRC object.
      app_crc_checksums[app_crc_object_index]->initialize();

      app_crc_calculation_state = app_crc_calculation_state_process_bytes;

      break;

      case app_crc_calculation_state_process_bytes:

      {
        // Process the next byte.
        const std::uint8_t next_byte =
          *(app_crc_test_values.data() + app_crc_process_data_byte_count);

        app_crc_checksums[app_crc_object_index]->process_bytes(&next_byte, 1U);
      }

      ++app_crc_process_data_byte_count;

      if(app_crc_process_data_byte_count >= app_crc_test_values.size())
      {
        // If all bytes for this CRC have been processed,
        // then reset the byte count to 0 and move to the
        // finalize state for this CRC calculation.
        app_crc_process_data_byte_count = 0U;

        // We are now ready to move to CRC state finalize
        // for this CRC object.
        app_crc_calculation_state = app_crc_calculation_state_finalize;
      }

      break;

    default:
    case app_crc_calculation_state_finalize:

      // Finalize this CRC object.
      app_crc_checksums[app_crc_object_index]->finalize();

      // Increment to othe next CRC object in the list.
      ++app_crc_object_index;

      if(app_crc_object_index >= app_crc_checksums.size())
      {
        // If we have reached the end of the CRC object list,
        // Then reset to the beginning of the list.
        app_crc_object_index = 0U;

        // Verify all CRC results.
        app_crc_results_are_ok =
          (    (app_crc_checksums[0U]->get_result<std::uint8_t> () == UINT8_C (0xDF))
            && (app_crc_checksums[1U]->get_result<std::uint16_t>() == UINT16_C(0x29B1))
            && (app_crc_checksums[2U]->get_result<std::uint32_t>() == UINT32_C(0x1697D06A))
            && (app_crc_checksums[3U]->get_result<std::uint64_t>() == UINT64_C(0x995DC9BBDF1939FA)));
      }

      // Return to CRC state initialization.
      app_crc_calculation_state = app_crc_calculation_state_initialize;

      break;
  }

  app_crc_measurement_port_type::set_pin_low();

  // Remember to enable all interrupts after the calculation.
  mcal::irq::enable_all();

  if(app_crc_results_are_ok == false)
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
```
