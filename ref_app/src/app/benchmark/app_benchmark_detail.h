///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2025.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef APP_BENCHMARK_DETAIL_2018_10_02_H
  #define APP_BENCHMARK_DETAIL_2018_10_02_H

  #include <cmath>
  #include <cstdint>
  #include <limits>

  namespace app { namespace benchmark { namespace detail {

  template<typename NumericType>
  constexpr auto default_tol() noexcept -> NumericType
  {
    return NumericType { std::numeric_limits<NumericType>::epsilon() * static_cast<NumericType>(UINT8_C(100)) }; // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
  }

  template<typename NumericType>
  constexpr auto is_close_fraction(const NumericType a, // NOLINT(bugprone-easily-swappable-parameters)
                                   const NumericType b, // NOLINT(bugprone-easily-swappable-parameters)
                                   const NumericType tol = default_tol<NumericType>()) noexcept -> bool
  {
    using std::fabs;
    using std::fpclassify;

    NumericType closeness { };

    if(fpclassify(b) == FP_ZERO)
    {
      closeness = fabs(a - b);
    }
    else
    {
      const NumericType ratio { a / b };

      closeness = NumericType { fabs(NumericType { 1 - ratio }) };
    }

    return (closeness < tol);
  }

  } // namespace detail
  } // namespace benchmark
  } // namespace app

#endif // APP_BENCHMARK_DETAIL_2018_10_02_H
