///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2018 - 2023.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

// chapter12_06-002_constexpr_exp.cpp
// See also short link to GodBolt: https://godbolt.org/z/e76xvGasf

#include <cstdint>
#include <limits>
#include <type_traits>

namespace ccmath {

namespace detail
{

  template <typename FloatingPoint>
  constexpr auto abs(FloatingPoint x,
                     typename std::enable_if<std::is_floating_point<FloatingPoint>::value>::type* = nullptr) -> FloatingPoint
  {
    using local_float_type = FloatingPoint;

    return
      (
        (x >= static_cast<local_float_type>(0.0F))
          ? x
          : ((x < static_cast<local_float_type>(0.0F)) ? -x : static_cast<local_float_type>(0.0F))
      );
  }

  // test whether values are within machine epsilon, used for algorithm
  // termination
  template <typename T>
  constexpr auto feq(T x, T y) -> bool
  {
    return abs(x - y) <= std::numeric_limits<T>::epsilon();
  }

  //----------------------------------------------------------------------------
  // exp by Taylor series expansion
  template <typename T>
  constexpr auto exp(T x, T sum, T n, int i, T t) -> T
  {
    return
      (
        feq(sum, sum + t/n)
          ? sum
          : exp(x, sum + t/n, n * i, i + 1, t * x)
      );
  }
} // namespace detail

template <typename FloatingPoint>
constexpr FloatingPoint exp(FloatingPoint x,
                            typename std::enable_if<std::is_floating_point<FloatingPoint>::value>::type* = nullptr)
{
  using local_float_type = FloatingPoint;

  return
    (
      x < 0
        ? static_cast<local_float_type>(1.0F) / detail::exp(-x, static_cast<local_float_type>(1.0F), static_cast<local_float_type>(1.0F), 2, -x)
        : detail::exp(x, static_cast<local_float_type>(1.0F), static_cast<local_float_type>(1.0F), 2, x)
    );
}

template <typename Integral>
constexpr double exp(Integral x,
                     typename std::enable_if<std::is_integral<Integral>::value>::type* = nullptr)
{
  return detail::exp<double>(x, static_cast<double>(1.0F), static_cast<double>(1.0F), 2, x);
}

} // namespace ccmath

int main()
{
  {
    // 95.58348
    // Check with N[Exp[456/100], 7]

    constexpr auto xf = static_cast<float>(static_cast<float>(456) / 100.0F);
    constexpr auto ef = ccmath::exp(xf);

    static_assert(ef > 95.5834F && ef < 95.5835F, "Error: constexpr exp() appears to be incorrect");
  }

  {
    // 0.01046206
    // Check with N[Exp[-456/100], 7]

    constexpr auto xf = static_cast<float>(static_cast<float>(-456) / 100.0F);
    constexpr auto ef = ccmath::exp(xf);

    static_assert(ef > 0.0104620F && ef < 0.0104621F, "Error: constexpr exp() appears to be incorrect");
  }

  {
    // 1.086904
    // Check with N[Exp[1/12], 7]

    constexpr auto xf = static_cast<float>(static_cast<float>(1) / 12.0F);
    constexpr auto ef = ccmath::exp(xf);

    static_assert(ef > 1.08690F && ef < 1.086905, "Error: constexpr exp() appears to be incorrect");
  }

  {
    // 219695.988672138
    // Check with N[Exp[123 / 10], 15]

    constexpr auto xd = static_cast<double>(static_cast<double>(123) / 10.0);
    constexpr auto ed = ccmath::exp(xd);

    static_assert(ed > 219695.98867213 && ed < 219695.98867214, "Error: constexpr exp() appears to be incorrect");
  }
}
