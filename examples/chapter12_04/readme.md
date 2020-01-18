# Example Chapter12_04
# Floating-Point Calculations

Example chapter12_04 float performs a variety of floating-point
calculations of selected special functions of pure and applied
mathematics.

# Selected Special Functions

Special functions such as the gamma function, Bessel functions,
Legendre functions, zeta-type functions and many others
are essential in pure and applied mathematics.
Special functions are _special_ in the sense of generally
being considered more specialized than elementary
transecndental functions like trigonometric functions,
logarithmic functions, exponential functions and the like.

Many special functions, although very difficult to calculate
over wide parameter and argument ranges have remarkably
simple small-argument approximations such as Taylor series.
Cylindrical Bessel functions of complex-valued argument
<img src="https://render.githubusercontent.com/render/math?math={z}">
and complex-valued order
<img src="https://render.githubusercontent.com/render/math?math={\nu}">,
for instance, have a
[Bessel function Taylor series representation](http://functions.wolfram.com/Bessel-TypeFunctions/BesselJ/06/01/04/01/01)


# Application Description

The application benchmark task `app::benchmark::task_func()`
calculates three individual floating-point special function
values in small argument range. These include a cylindrical Bessel function,
a generalized hypergeometric geometric function and a generalized
Legendre function.

```
void app::benchmark::task_func()
{
  static std::uint_fast8_t app_benchmark_index;

  app_benchmark_result_is_ok = true;

  // Use a port pin to provide a real-time measurement.
  app_benchmark_port_type::set_pin_high();

  if(app_benchmark_index == 0U)
  {
    // Test the value of a Bessel function.
    // Here is a control value from Wolfram Alpha.
    // N[BesselJ[11/9, EulerGamma], 40]
    // 0.1890533651853886085356717332711858771597

    constexpr std::float32_t v = FLOAT32_C(11.0) / FLOAT32_C(9.0);

    app_benchmark_result_bessel =
      math::functions::cyl_bessel_j(v, math::constants::euler<std::float32_t>());

    app_benchmark_result_is_ok &= is_close_fraction(FLOAT32_C(0.1890533652),
                                                    app_benchmark_result_bessel,
                                                    app_benchmark_tolerance);
  }
  else if(app_benchmark_index == 1U)
  {
    // Test the value of a hypergeometric function.
    // Here is a control value from Wolfram Alpha.
    // N[HypergeometricPFQ[3/{7, 8, 9, 10}, 7/{13, 14, 15, 16, 17}, Log[2]], 40]
    // 1.583596313998374915091256357139915173598

    constexpr std::array<std::float32_t, 4U> ap =
    {{
      FLOAT32_C(3.0) / FLOAT32_C( 7.0),
      FLOAT32_C(3.0) / FLOAT32_C( 8.0),
      FLOAT32_C(3.0) / FLOAT32_C( 9.0),
      FLOAT32_C(3.0) / FLOAT32_C(10.0)
    }};

    constexpr std::array<std::float32_t, 5U> bq =
    {{
      FLOAT32_C(7.0) / FLOAT32_C(13.0),
      FLOAT32_C(7.0) / FLOAT32_C(14.0),
      FLOAT32_C(7.0) / FLOAT32_C(15.0),
      FLOAT32_C(7.0) / FLOAT32_C(16.0),
      FLOAT32_C(7.0) / FLOAT32_C(17.0)
    }};

    app_benchmark_result_hypergeometric =
      math::functions::hypergeometric_pfq(ap.cbegin(),
                                          ap.cend(),
                                          bq.cbegin(),
                                          bq.cend(),
                                          math::constants::ln_two<std::float32_t>());

    app_benchmark_result_is_ok &= is_close_fraction(FLOAT32_C(1.5835963140),
                                                    app_benchmark_result_hypergeometric,
                                                    app_benchmark_tolerance);
  }
  else if(app_benchmark_index == 2U)
  {
    // Test the value of a Legendre function of the first kind.
    // Here is a control value from Wolfram Alpha.
    // N[LegendreP[1/11, 14/19, 2/7], 40]
    // 0.2937838815278435137954432141091105343408
    constexpr std::float32_t v = FLOAT32_C( 1.0) / FLOAT32_C(11.0);
    constexpr std::float32_t u = FLOAT32_C(14.0) / FLOAT32_C(19.0);
    constexpr std::float32_t x = FLOAT32_C( 2.0) / FLOAT32_C( 7.0);

    app_benchmark_result_legendre = math::functions::legendre_p(v, u, x);

    app_benchmark_result_is_ok &= is_close_fraction(FLOAT32_C(0.2937838815),
                                                    app_benchmark_result_legendre,
                                                    app_benchmark_tolerance);
  }

  app_benchmark_port_type::set_pin_low();

  ++app_benchmark_index;

  if(app_benchmark_index == 3U)
  {
    app_benchmark_index = 0U;
  }


  if(app_benchmark_result_is_ok == false)
  {
    // The result of this floating-point benchmark is not OK.

    // Crash the system and toggle a port to provide an indication of failure.
    for(;;) { app_benchmark_port_type::toggle_pin(); mcal::cpu::nop(); }
  }
}
```

As usual, the benchmark port is toggled high prior to the
floating-point calculation and low after the floating-point calculation.
The three individual calculations are not calculated all at once
in a single call of the benchmark task. Rather an index
counting from zero to one to two selects one special function
calculation. The success of the calculation uses a relative
measure of floating-point closeness based on the rqatio of
the expected answer with the control value compared with one.

