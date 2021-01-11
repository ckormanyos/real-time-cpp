# Benchmarks and Performance Classes

## Benchmarks

  - The benchmarks provide code that exercises microcontroller performance.
  - Various efficiency aspects are emphasized such as integral and floating-point calculations, looping, branching, etc.
  - Each benchmark is implemented as a single callable function to be called from a scheduled task in the multitasking scheduler configuration.
  - Every benchmark file can also be compiled separately as a standalone C++11 project.
  - A benchmark digital I/O pin is toggled hi/lo at begin/end of the benchmark run providing for oscilloscope real-time measurement.
  - The benchmarks provide scalable, portable C++11 means for identifying the performance class of the microcontroller.

## Benchmark details

  - ![`APP_BENCHMARK_TYPE_NONE              `](./app_benchmark_none.cpp) is an empty benchmark with merely a Boolean function call returning `true`.
  - ![`APP_BENCHMARK_TYPE_COMPLEX           `](./app_benchmark_complex.cpp) computes a floating-point complex-valued trigonometric sine function using the [`extended_complex::complex`](../../math/extended_complex/extended_complex.h) template class.
  - ![`APP_BENCHMARK_TYPE_CRC               `](./app_benchmark_crc.cpp) calculates a 32-bit byte-oriented CRC result described in Sect. 6.1 of the book.
  - ![`APP_BENCHMARK_TYPE_FAST_MATH         `](./app_benchmark_fast_math.cpp) calculates reduced, time-optimized floating-point elementary transcendental functions.
  - ![`APP_BENCHMARK_TYPE_FILTER            `](./app_benchmark_filter.cpp) calculates an integral FIR filter sampling result.
  - ![`APP_BENCHMARK_TYPE_FIXED_POINT       `](./app_benchmark_fixed_point.cpp) calculates the first derivative of an elementary function using the self-written [`fixed_point`](../../math/fixed_point/fixed_point.h) template class in Chap. 13 of the book.
  - ![`APP_BENCHMARK_TYPE_FLOAT             `](./app_benchmark_float.cpp) implements the floating-point examples detailed in Sect. 12.4 of the book.
  - ![`APP_BENCHMARK_TYPE_WIDE_INTEGER      `](./app_benchmark_wide_integer.cpp) performs 256-bit unsigned big integer calculations using the [`uintwide_t`](../../math/wide_integer/generic_template_uintwide_t.h) class.
  - ![`APP_BENCHMARK_TYPE_PI_SPIGOT         `](./app_benchmark_pi_spigot.cpp) performs a pi calculation using a template-based [_spigot_ algorithm](../../math/constants/pi_spigot_state.h) with calculation steps divided among the slices of the idle task.
  - ![`APP_BENCHMARK_TYPE_PI_SPIGOT_SINGLE  `](./app_benchmark_pi_spigot_single.cpp) does the same pi calculation as above implemented as a single function call.
  - ![`APP_BENCHMARK_TYPE_HASH              `](./app_benchmark_hash.cpp) computes a 160-bit hash checksum of a 3-character message.
  - ![`APP_BENCHMARK_TYPE_WIDE_DECIMAL      `](./app_benchmark_wide_decimal.cpp) computes a 100 decimal digit square root using the [`decwide_t`](../../math/wide_decimal/decwide_t.h) template class.
  - ![`APP_BENCHMARK_TYPE_TRAPEZOID_INTEGRAL`](./app_benchmark_trapezoid_integral.cpp) computes the numerical floating-point result of a Bessel function using a recursive trapezoid integration routine.
  - ![`APP_BENCHMARK_TYPE_PI_AGM            `](./app_benchmark_pi_agm.cpp) computes 105 decimal digits of pi using a Gaus AGM method with the [`decwide_t`](../../math/wide_decimal/decwide_t.h) template class.

## Performance classes

The benchmarks run on each supported target and reveal a wide range of
microcontroller _performance classes_.
Consider, for instance, [`APP_BENCHMARK_TYPE_PI_AGM`](./app_benchmark_pi_agm.cpp)
which compute 105 decimal digits of the mathematical constant pi using
a Gauss AGM method with the [`decwide_t`](../../math/wide_decimal/decwide_t.h) template class.

The [image](./images/app_benchmark_pi_agm.pdf)
shows the real-time measurement of this benchmark
on the 8-bit MICROCHIP(R) AVR controller of the Arduino
and the 32-bit ARM(R) 8 controller
of the BeagleBone Black Edition, Rev. C.
The calculation requires approximately
470ms and 1.5ms respectively on these two microcontrollers
having vastly different performance classes.
