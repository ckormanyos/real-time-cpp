///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2018.
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
#define APP_BENCHMARK_TYPE_STD_WIDE_INTEGER    5

#define APP_BENCHMARK_TYPE   APP_BENCHMARK_TYPE_NONE
//#define APP_BENCHMARK_TYPE   APP_BENCHMARK_TYPE_CRC32
//#define APP_BENCHMARK_TYPE   APP_BENCHMARK_TYPE_FILTER
//#define APP_BENCHMARK_TYPE   APP_BENCHMARK_TYPE_FIXED_POINT
//#define APP_BENCHMARK_TYPE   APP_BENCHMARK_TYPE_STD_COMPLEX
//#define APP_BENCHMARK_TYPE   APP_BENCHMARK_TYPE_STD_WIDE_INTEGER

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

  #include <math/fixed_point/fixed_point.h>
  typedef fixed_point<std::int32_t> numeric_type;

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

#elif(APP_BENCHMARK_TYPE == APP_BENCHMARK_TYPE_STD_WIDE_INTEGER)

  #include <math/wide_integer/non_template_uint256_t.h>

  using wide_integer_type = wide_integer::non_template::uint256_t;

  namespace control
  {
    // Create two pseudo-random 256-bit unsigned integers.
    //   Table[IntegerString[RandomInteger[{1, (2^256) - 1}], 16], 2]
    //   {
    //     F4DF741DE58BCB2F37F18372026EF9CBCFC456CB80AF54D53BDEED78410065DE,
    //     166D63E0202B3D90ECCEAA046341AB504658F55B974A7FD63733ECF89DD0DF75
    //   }
    //
    // Create two random 256-bit unsigned integers.
    //   a = 0xF4DF741DE58BCB2F'37F18372026EF9CB'CFC456CB80AF54D5'3BDEED78410065DE
    //   b = 0x166D63E0202B3D90'ECCEAA046341AB50'4658F55B974A7FD6'3733ECF89DD0DF75
    //
    // Multiply c = a * b.
    //   a * b = 0xE491A360C57EB430'6C61F9A04F7F7D99'BE3676AAD2D71C55'92D5AE70F84AF076
    //
    // Divide d = a / b.
    //   a / b = 0xA

    const wide_integer_type a
    (
      {
        UINT64_C(0x3BDEED78410065DE),
        UINT64_C(0xCFC456CB80AF54D5),
        UINT64_C(0x37F18372026EF9CB),
        UINT64_C(0xF4DF741DE58BCB2F)
      }
    );

    const wide_integer_type b
    (
      {
        UINT64_C(0x3733ECF89DD0DF75),
        UINT64_C(0x4658F55B974A7FD6),
        UINT64_C(0xECCEAA046341AB50),
        UINT64_C(0x166D63E0202B3D90)
      }
    );

    const wide_integer_type a_mul_b
    (
      {
        UINT64_C(0x92D5AE70F84AF076),
        UINT64_C(0xBE3676AAD2D71C55),
        UINT64_C(0x6C61F9A04F7F7D99),
        UINT64_C(0xE491A360C57EB430)
      }
    );

    wide_integer_type a_div_b(std::uint16_t(0xAU));
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

  #elif(APP_BENCHMARK_TYPE == APP_BENCHMARK_TYPE_STD_WIDE_INTEGER)

    mcal::irq::disable_all();
    port_type::set_pin_high();

    const wide_integer_type c = (control::a * control::b);
    const wide_integer_type d = (control::a / control::b);

    const bool result_is_ok =
      ((c == control::a_mul_b) && (d == control::a_div_b));

    port_type::set_pin_low();
    mcal::irq::enable_all();

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
