# Benchmarks and Performance Classes

# Benchmarks

  - The benchmarks provide code that exercises microcontroller performance.
  - Various efficiency aspects are emphasized such as integral and floating-point calculations, looping, branching, etc.
  - Each benchmark is implemented as a single callable function to be called from a scheduled task in the multitasking scheduler configuration.
  - Every benchmark file can also be compiled separately as a standalone C++11 project.
  - A benchmark digital I/O pin is toggled hi/lo at begin/end of the benchmark run providing for oscilloscope real-time measurement.
  - The benchmarks provide scalability, portability means for identifying the performance class of the microcontroller.

# Benchmark details

  - ![`#define APP_BENCHMARK_TYPE_NONE                  0`](./app_benchmark.cpp) is an empty benchmark with no functionality other than pin toggle.
  - ![`#define APP_BENCHMARK_TYPE_COMPLEX               1`](./app_benchmark_complex.cpp) computes a floating-point complex-valued trigonometric sine function using the [`extended_complex::complex`](../../math/extended_complex/extended_complex.h) template class.
  - ![`#define APP_BENCHMARK_TYPE_CRC                   2`](./app_benchmark_crc.cpp) calculates a 32-bit byte-oriented CRC result described in Sect. 6.1 of the book.
  - ![`#define APP_BENCHMARK_TYPE_FAST_MATH             3`](./app_benchmark_fast_math.cpp) calculates reduced, time-optimized floating-point elementary transcendental functions.
  - ![`#define APP_BENCHMARK_TYPE_FILTER                4`](./app_benchmark_filter.cpp) calculates an integral FIR filter sampling result.
  - ![`#define APP_BENCHMARK_TYPE_FIXED_POINT           5`](./app_benchmark_fixed_point.cpp) calculates the first derivative of an elementary function using the self-written [`fixed_point`](../../math/fixed_point/fixed_point.h) template class in Chap. 13 of the book.
  - ![`#define APP_BENCHMARK_TYPE_FLOAT                 6`](./app_benchmark_float.cpp) implements the floating-point examples detailed in Sect. 12.4 of the book.
  - ![`#define APP_BENCHMARK_TYPE_WIDE_INTEGER          7`](./app_benchmark_wide_integer.cpp) performs 256-bit unsigned big integer calculations using the [`uintwide_t`](../../math/wide_integer/generic_template_uintwide_t.h) class.
  - ![`#define APP_BENCHMARK_TYPE_PI_SPIGOT             8`](./app_benchmark_pi_spigot.cpp) performs a pi calculation using a template-based [_spigot_ algorithm](../../math/constants/pi_spigot_state.h) with calculation steps divided among the slices of the idle task.
  - ![`#define APP_BENCHMARK_TYPE_PI_SPIGOT_SINGLE      9`](./app_benchmark_pi_spigot_single.cpp) does the same pi calculation as above implemented as a single function call.
  - ![`#define APP_BENCHMARK_TYPE_HASH                 10`](./app_benchmark_hash.cpp) computes a 160-bit hash checksum of a 3-character message.
  - ![`#define APP_BENCHMARK_TYPE_WIDE_DECIMAL         11`](./app_benchmark_wide_decimal.cpp) computes a 100 decimal digit square root using the [`decwide_t`](../../math/wide_decimal/decwide_t.h) template class.
  - ![`#define APP_BENCHMARK_TYPE_TRAPEZOID_INTEGRAL   12`](./app_benchmark_trapezoid_integral.cpp) computes the numerical floating-point result of a Bessel function using a recursive trapezoid integration routine.
  - ![`#define APP_BENCHMARK_TYPE_PI_AGM               13`](./app_benchmark_pi_agm.cpp) computes 105 decimal digits of pi using a Gaus AGM method with the [`decwide_t`](../../math/wide_decimal/decwide_t.h) template class.
