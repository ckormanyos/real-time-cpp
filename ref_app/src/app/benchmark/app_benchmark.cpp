
///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2016.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <array>
#include <cstdint>
#include <limits>

#include <mcal_benchmark.h>
#include <mcal_cpu.h>
#include <mcal_irq.h>

#define APP_BENCHMARK_TYPE_NONE                0
#define APP_BENCHMARK_TYPE_CRC32               1
#define APP_BENCHMARK_TYPE_FILTER              2
#define APP_BENCHMARK_TYPE_FIXED_POINT         3
#define APP_BENCHMARK_TYPE_STD_COMPLEX         4

#define APP_BENCHMARK_TYPE   APP_BENCHMARK_TYPE_NONE
//#define APP_BENCHMARK_TYPE   APP_BENCHMARK_TYPE_CRC32
//#define APP_BENCHMARK_TYPE   APP_BENCHMARK_TYPE_FILTER
//#define APP_BENCHMARK_TYPE   APP_BENCHMARK_TYPE_FIXED_POINT
//#define APP_BENCHMARK_TYPE   APP_BENCHMARK_TYPE_STD_COMPLEX

#if(APP_BENCHMARK_TYPE != APP_BENCHMARK_TYPE_NONE)

  namespace
  {
    typedef mcal::benchmark::benchmark_port_type port_type;
  }

#endif

#if(APP_BENCHMARK_TYPE == APP_BENCHMARK_TYPE_CRC32)

  #include <math/checksums/crc/crc32.h>

  std::uint32_t app_benchmark_crc;

#elif(APP_BENCHMARK_TYPE == APP_BENCHMARK_TYPE_FILTER)

  #include <math/filters/fir_order_n.h>

  typedef fir_order_n<17U, 64U, std::int16_t, std::int32_t> filter_type;

  extern filter_type  f;
  extern std::int16_t sample;

#elif(APP_BENCHMARK_TYPE == APP_BENCHMARK_TYPE_FIXED_POINT)

  #define BOOST_FIXED_POINT_DISABLE_IOSTREAM
  #define BOOST_FIXED_POINT_DISABLE_MULTIPRECISION

  #include <boost/fixed_point/fixed_point.hpp>
  typedef boost::fixed_point::negatable<7, -24> numeric_type;

  //#include <cmath>
  //typedef float numeric_type;

  namespace local
  {
    template<typename RealValueType,
             typename RealFunctionType>
    RealValueType first_derivative(const RealValueType& x,
                                   const RealValueType& dx,
                                   RealFunctionType real_function)
    {
      const RealValueType dx2(dx  + dx);
      const RealValueType dx3(dx2 + dx);

      const RealValueType m1((  real_function(x + dx)
                              - real_function(x - dx))  / 2U);
      const RealValueType m2((  real_function(x + dx2)
                              - real_function(x - dx2)) / 4U);
      const RealValueType m3((  real_function(x + dx3)
                              - real_function(x - dx3)) / 6U);

      const RealValueType fifteen_m1(m1 * 15U);
      const RealValueType six_m2    (m2 *  6U);
      const RealValueType ten_dx    (dx * 10U);

      return ((fifteen_m1 - six_m2) + m3) / ten_dx;
    }
  } // namespace local

  extern numeric_type a;
  extern numeric_type b;
  extern numeric_type c;
  extern numeric_type d;

#elif(APP_BENCHMARK_TYPE == APP_BENCHMARK_TYPE_STD_COMPLEX)

  #include <complex>
  #include <limits>

  typedef std::complex<float> complex_type;

  extern complex_type x;
  extern complex_type y;

  template<typename float_type>
  bool is_close_fraction(const float_type f,
                         const float_type control,
                         const float_type tol = std::numeric_limits<float_type>::epsilon() * float_type(100.0L))
  {
    const float ratio = std::fabs(f / control);

    return (std::abs(1.0F - ratio) < tol);
  }

#endif // APP_BENCHMARK_TYPE

namespace app
{
  namespace benchmark
  {
    void task_init();
    void task_func();
  }
}

void app::benchmark::task_init()
{
  #if(APP_BENCHMARK_TYPE != APP_BENCHMARK_TYPE_NONE)

    port_type::set_direction_output();

  #endif
}

void app::benchmark::task_func()
{
  #if(APP_BENCHMARK_TYPE == APP_BENCHMARK_TYPE_CRC32)

    const std::array<std::uint8_t, 9U> data =
    {{
      0x31U, 0x32U, 0x33U, 0x34U, 0x35U, 0x36U, 0x37U, 0x38U, 0x39U
    }};

    mcal::irq::disable_all();
    port_type::set_pin_high();

    app_benchmark_crc = math::checksums::crc32_mpeg2(data.cbegin(),
                                                     data.cend());

    port_type::set_pin_low();
    mcal::irq::enable_all();

    if(app_benchmark_crc == UINT32_C(0x0376E6E7))
    {
      // The benchmark is OK.
      // Perform one nop and leave.

      mcal::cpu::nop();
    }
    else
    {
      // The benchmark result is not OK!
      // Remain in a blocking loop and crash the system.

      for(;;) { mcal::cpu::nop(); }
    }

  #elif (APP_BENCHMARK_TYPE == APP_BENCHMARK_TYPE_FILTER)

    mcal::irq::disable_all();
    port_type::set_pin_high();

    f.new_sample<-2, -2, -2, -1, 3, 9, 15, 20, 24,
                 24, 20, 15, 9, 3, -1, -2, -2, -2>(sample);

    port_type::set_pin_low();
    mcal::irq::enable_all();

  #elif(APP_BENCHMARK_TYPE == APP_BENCHMARK_TYPE_FIXED_POINT)

    mcal::irq::disable_all();
    port_type::set_pin_high();

    d = local::first_derivative(numeric_type(1) / 2,  // x
                                numeric_type(1) / 4,  // Step size dx.
                                [](const numeric_type& x) -> numeric_type
                                {
                                  return (((a * x) + b) * x) + c;
                                });

    port_type::set_pin_low();
    mcal::irq::enable_all();

  #elif(APP_BENCHMARK_TYPE == APP_BENCHMARK_TYPE_STD_COMPLEX)

    mcal::irq::disable_all();
    port_type::set_pin_high();

    // 14.859343457123410999 + 5.259004469728472689 i
    y = std::sin(x);

    port_type::set_pin_low();
    mcal::irq::enable_all();

    const bool result_is_ok = (   is_close_fraction(y.real(), 14.859343457123410999F)
                               && is_close_fraction(y.imag(),  5.259004469728472689F));

    if(result_is_ok)
    {
      // The benchmark is OK.
      // Perform one nop and leave.

      mcal::cpu::nop();
    }
    else
    {
      // The benchmark result is not OK!
      // Remain in a blocking loop and crash the system.

      for(;;) { mcal::cpu::nop(); }
    }

  #endif // APP_BENCHMARK_TYPE
}

#if(APP_BENCHMARK_TYPE == APP_BENCHMARK_TYPE_FILTER)

  filter_type f;
  std::int16_t sample = INT16_C(100);

#endif

#if(APP_BENCHMARK_TYPE == APP_BENCHMARK_TYPE_FIXED_POINT)

  numeric_type a = numeric_type(12) / 10;
  numeric_type b = numeric_type(34) / 10;
  numeric_type c = numeric_type(56) / 10;
  numeric_type d;

#endif

#if(APP_BENCHMARK_TYPE == APP_BENCHMARK_TYPE_STD_COMPLEX)

complex_type x(1.23F, 3.45F);
complex_type y;

#endif
