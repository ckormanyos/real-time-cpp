# Example Chapter17_03
# Traditional C Language Code in a Modern C++ Project

Example chapter17_03 depicts some methods that potentially allow
the successful use of traditional C-language code within a
modern C++ project.

Example chapter17_03 assumes that there is a useful
library of well-tested, efficient and trusted C-language code
available in the local project domain and it is desired to make
use of this code within a modern C++ project.

# CRC Functions in Traditional C

In order to emulate this situation, we have built up a
little library of CRC functions that are specified in the
[AUTOSAR](www.autosar.org) architecture. This architecture
is ubiquitously used in embedded systems projects in the
automotive industry. The CRC library features well-known
CRC variants with results having widths of 8, 16, 32 and 64 bits.

A C-language interface to an 8-bit CRC is shown below.

```
// The interface to Crc08 can be used in both C as well as C++.

/* Name            : CRC-8/AUTOSAR */
/* Width in bits   : 8             */
/* Polynomial      : 0x2F          */
/* Initial value   : 0xFF          */
/* Final XOR       : 0xFF          */
/* Test: '1'...'9' : 0xDF          */
/* See also AUTOSAR Version 4.3.   */

#if defined(__cplusplus)
extern "C"
{
#endif

typedef struct Crc08_Context_Type
{
  uint8_t Crc08_Value;
}
Crc08_Context_Type;

void Crc08_Initialize  (Crc08_Context_Type* Crc_Context);

void Crc08_ProcessBytes(const uint8_t*      DataIn,
                        const size_t        DataLength,
                        Crc08_Context_Type* Crc_Context);

void Crc08_Finalize    (Crc08_Context_Type* Crc_Context);

#if defined(__cplusplus)
}
#endif
```

# Application Description

On top of the existing C-language CRC library we have built a skinny
object-oriented C++ wrapper class architecture that
allows the CRC objects to be used effectively in a
modern C++ envorinment. The application benchmark task,
for instance, tests all four CRC functions and compares
the results with their expected values. As mentioned in
![Example chapter06_01](../chapter06_01), the standard
CRC test involves the result of performing the CRC on the
bytes of the ACII digits
<img src="https://render.githubusercontent.com/render/math?math=1{\ldots}9">.

The application task `app::crc::task_func()` is shown below.

```
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
```
