///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2024.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef APP_BENCHMARK_DETAIL_2018_10_02_H
  #define APP_BENCHMARK_DETAIL_2018_10_02_H

  #include <cmath>
  #include <limits>

  namespace app { namespace benchmark { namespace detail {

  template<typename NumericType>
  auto is_close_fraction(const NumericType a, // NOLINT(bugprone-easily-swappable-parameters)
                         const NumericType b, // NOLINT(bugprone-easily-swappable-parameters)
                         const NumericType tol = NumericType(std::numeric_limits<NumericType>::epsilon() * NumericType(100))) -> bool
  {
    using std::fabs;

    const NumericType ratio     = fabs(NumericType((NumericType(1) * a) / b));

    const NumericType closeness = fabs(NumericType(1 - ratio));

    return (closeness < tol);
  }

  } // namespace detail
  } // namespace benchmark
  } // namespace app

#endif // APP_BENCHMARK_DETAIL_2018_10_02_H
