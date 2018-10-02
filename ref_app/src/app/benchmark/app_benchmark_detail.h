#ifndef APP_BENCHMARK_DETAIL_2018_10_02_H_
  #define APP_BENCHMARK_DETAIL_2018_10_02_H_

  #include <cmath>
  #include <limits>

  namespace app { namespace benchmark { namespace detail {

  template<typename float_type>
  bool is_close_fraction(const float_type f,
                         const float_type control,
                         const float_type tol = std::numeric_limits<float_type>::epsilon() * float_type(100.0L))
  {
    using std::fabs;

    const float_type ratio = fabs(f / control);

    return (fabs(float_type(1.0L) - ratio) < tol);
  }

  } } } // namespace app::benchmark::detail

#endif // APP_BENCHMARK_DETAIL_2018_10_02_H_
