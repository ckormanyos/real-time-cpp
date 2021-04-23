# Benchmarks and Performance Classes

## Benchmarks

  - The benchmarks provide code that exercises microcontroller performance.
  - Various efficiency aspects are emphasized such as integral and floating-point calculations, looping, branching, etc.
  - Each benchmark is implemented as a single callable function to be called from a scheduled task in the multitasking scheduler configuration.
  - Every benchmark file can also be compiled separately as a standalone C++11 project.
  - A benchmark digital I/O pin is toggled hi/lo at begin/end of the benchmark run providing for oscilloscope real-time measurement.
  - The benchmarks provide scalable, portable C++11 means for identifying the performance class of the microcontroller.

## Benchmark details

  - ![app_benchmark_none.cpp](./app_benchmark_none.cpp) via `#define APP_BENCHMARK_TYPE_NONE` is an empty benchmark with merely a Boolean function call returning `true`.
  - ![app_benchmark_complex.cpp](./app_benchmark_complex.cpp) via `#define APP_BENCHMARK_TYPE_COMPLEX` computes a floating-point complex-valued trigonometric sine function using the [`extended_complex::complex`](../../math/extended_complex/extended_complex.h) template class.
  - ![app_benchmark_crc.cpp](./app_benchmark_crc.cpp) via `#define APP_BENCHMARK_TYPE_CRC` calculates a 32-bit byte-oriented CRC result described in Sect. 6.1 of the book.
  - ![app_benchmark_fast_math.cpp](./app_benchmark_fast_math.cpp) via `#define APP_BENCHMARK_TYPE_FAST_MATH` calculates reduced, time-optimized floating-point elementary transcendental functions.
  - ![app_benchmark_filter.cpp](./app_benchmark_filter.cpp) via `#define APP_BENCHMARK_TYPE_FILTER` calculates an integral FIR filter sampling result.
  - ![app_benchmark_fixed_point.cpp](./app_benchmark_fixed_point.cpp) via `#define APP_BENCHMARK_TYPE_FIXED_POINT` calculates the first derivative of an elementary function using the self-written [`fixed_point`](../../math/fixed_point/fixed_point.h) template class in Chap. 13 of the book.
  - ![app_benchmark_float.cpp](./app_benchmark_float.cpp) via `#define APP_BENCHMARK_TYPE_FLOAT` implements the floating-point examples detailed in Sect. 12.4 of the book.
  - ![app_benchmark_wide_integer.cpp](./app_benchmark_wide_integer.cpp) via `#define APP_BENCHMARK_TYPE_WIDE_INTEGER` performs 256-bit unsigned big integer calculations using the [`uintwide_t`](../../math/wide_integer/generic_template_uintwide_t.h) class.
  - ![app_benchmark_pi_spigot.cpp](./app_benchmark_pi_spigot.cpp) via `#define APP_BENCHMARK_TYPE_PI_SPIGOT` performs a pi calculation using a template-based [_spigot_ algorithm](../../math/constants/pi_spigot_state.h) with calculation steps divided among the slices of the idle task.
  - ![app_benchmark_pi_spigot_single.cpp](./app_benchmark_pi_spigot_single.cpp) via `#define APP_BENCHMARK_TYPE_PI_SPIGOT_SINGLE` does the same pi calculation as above implemented as a single function call.
  - ![app_benchmark_hash.cpp](./app_benchmark_hash.cpp) via `#define APP_BENCHMARK_TYPE_HASH` computes a 160-bit hash checksum of a 3-character message.
  - ![app_benchmark_wide_decimal.cpp](./app_benchmark_wide_decimal.cpp) via `#define APP_BENCHMARK_TYPE_WIDE_DECIMAL` computes a 100 decimal digit square root using the [`decwide_t`](../../math/wide_decimal/decwide_t.h) template class.
  - ![app_benchmark_trapezoid_integral.cpp](./app_benchmark_trapezoid_integral.cpp) via `#define APP_BENCHMARK_TYPE_TRAPEZOID_INTEGRAL` computes the numerical floating-point result of a Bessel function using a recursive trapezoid integration routine.
  - ![app_benchmark_pi_agm.cpp](./app_benchmark_pi_agm.cpp) via `#define APP_BENCHMARK_TYPE_PI_AGM` computes 53 decimal digits of pi using a Gaus AGM method with the [`decwide_t`](../../math/wide_decimal/decwide_t.h) template class having a so-called _limb type_ of `std::uint16_t`.
  - ![app_benchmark_soft_double_h2f1.cpp](./app_benchmark_soft_double_h2f1.cpp) via `#define APP_BENCHMARK_TYPE_SOFT_DOUBLE_H2F1` calculates an <img src="https://render.githubusercontent.com/render/math?math=\approx\,15"> decimal digit hypergeometric function value using a classic iterative rational approximation scheme. This calculation is also included as an example in the [soft_double](https://github.com/ckormanyos/soft_double) project.
  - ![app_benchmark_boost_math_cbrt.cpp](./app_benchmark_pi_agm.cpp) via `#define APP_BENCHMARK_TYPE_BOOST_MATH_CBRT` uses [Boost.Math](https://www.boost.org/doc/libs/1_76_0/libs/math/doc/html/index.html) to compute the cube root of various Gamma functions values (at the moment only available on PC or workstation hosts).
  - ![app_benchmark_cnl_scaled_integer.cpp](./app_benchmark_cnl_scaled_integer.cpp) via `#define APP_BENCHMARK_TYPE_CNL_SCALED_INTEGER` brings a small subset of the [CNL Library](https://github.com/johnmcfarlane/cnl) _onto the metal_ by exercising an elementary quadratic calculations with the fixed-point representations of [`cnl::scaled_integer`](https://github.com/johnmcfarlane/cnl/tree/main/include/cnl/_impl/scaled_integer).

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
