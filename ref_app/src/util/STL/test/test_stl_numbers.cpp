///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2026.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <cmath>
#include <limits>
#include <numbers>
#include <stdfloat>

auto test_stl_sanity_numbers() -> bool;

auto test_stl_sanity_numbers() -> bool
{
  constexpr bool
    result_double_type_is_ok
    {
         (std::numeric_limits<double>::radix == 2)
      && (std::numeric_limits<double>::digits >= 53)
      && (std::numeric_limits<double>::min_exponent <= -1021)
      && (std::numeric_limits<double>::max_exponent >= 1024)
    };

  static_assert(result_double_type_is_ok, "Error: Insufficient width of double type");

  using namespace std::numbers;

  const auto x = std::sqrt(inv_pi) / inv_sqrtpi + std::ceil(std::exp2(log2e)) + sqrt3 * inv_sqrt3 + std::exp(0.0);
  const auto v = (phi * phi - phi) + 1 / std::log2(sqrt2) + log10e * ln10 + std::pow(e, ln2) - std::cos(pi);

  const int the_answer { static_cast<int>(static_cast<std::float32_t>(x * v)) };

  const bool result_the_answer_is_ok { (the_answer == 42) };

  return result_the_answer_is_ok;
}
