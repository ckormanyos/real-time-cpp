///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2021.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef APP_BENCHMARK_DETAIL_2018_10_02_H_
  #define APP_BENCHMARK_DETAIL_2018_10_02_H_

  #include <cmath>
  #include <limits>

  namespace app { namespace benchmark { namespace detail {

  template<typename NumericType>
  auto is_close_fraction(const NumericType a,
                         const NumericType b,
                         const NumericType tol = NumericType(std::numeric_limits<NumericType>::epsilon() * NumericType(100))) -> bool
  {
    using std::fabs;

    const NumericType ratio     = fabs(NumericType((NumericType(1) * a) / b));

    const NumericType closeness = fabs(NumericType(1 - ratio));

    return (closeness < tol);
  }

  } } } // namespace app::benchmark::detail

#endif // APP_BENCHMARK_DETAIL_2018_10_02_H_
