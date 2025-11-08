///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2017 - 2025.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

// chapter12_06-001_constexpr_sine.cpp

#include <cmath>
#include <complex>
#include <cstdint>
#include <iomanip>
#include <iostream>
#include <limits>
#include <numbers>
#include <sstream>

template<typename NumericType>
auto is_close_fraction(const NumericType a,
                       const NumericType b,
                       const NumericType tol = NumericType(std::numeric_limits<NumericType>::epsilon() * NumericType(100))) -> bool
{
  using std::fabs;

  NumericType closeness { };

  if(b == NumericType(0))
  {
    closeness = fabs(a - b);
  }
  else
  {
    const NumericType ratio { fabs(NumericType((NumericType(1) * a) / b)) };

    closeness = fabs(NumericType(1 - ratio));
  }

  return (closeness < tol);
}

namespace math { namespace const_functions {

template<typename T>
constexpr T sin(T x)
{
  // Scale the argument.
  const T chi_s
    { T(T(x * 2) / std::numbers::pi_v<T>) };

  // Take the absolute value of chi.
  const bool is_neg { (chi_s < T(0)) };
  const T chi_a { T(is_neg ? -chi_s : chi_s) };

  // Do the argument reduction.
  const std::uint32_t npi2
    { std::uint32_t(chi_a / 2) };

  const std::uint32_t npi =
    std::uint32_t
    (
      (chi_a - (npi2 * 2) > T(1))
              ? npi2 + 1
              : npi2
    );

  const T chi { T(chi_a - T(npi * 2)) };
  const T chi2 { T(chi * chi) };

  // Do the order-19 polynomial expansion.
  const T sum =
    (((((((((- T(4.2468171354841523379493663E-14L)
      * chi2 + T(6.0640855645940930588123490E-12L))
      * chi2 - T(6.6880001786329819459555395E-10L))
      * chi2 + T(5.6921726597221657560994942E-08L))
      * chi2 - T(3.5988432339708525153771884E-06L))
      * chi2 + T(1.6044118478699232812460184E-04L))
      * chi2 - T(4.6817541353186228516958362E-03L))
      * chi2 + T(7.9692626246167038770053004E-02L))
      * chi2 - T(6.4596409750624625337325359E-01L))
      * chi2 + T(1.5707963267948966192276341E+00L))
      * chi;

  // Reflect the result if necessary.
  const bool needs_reflect
    { (((npi % 2) != 0)  == is_neg) };

  return (needs_reflect ? sum : -sum);
}

} } // namespace math::const_functions

constexpr double cexpr_sin_half { math::const_functions::sin(0.5) };

static_assert(std::numeric_limits<double>::digits == 53,
              "Error: this example is intended for double being 8 byte double-precision floating-point");

static_assert((cexpr_sin_half >= 0.479425538604202) && (cexpr_sin_half <= 0.479425538604204),
              "Error: incorrect numerical double sin(0.5) value");

auto main() -> int;

auto main() -> int
{
  double dx { };

  bool result_is_ok { true };

  for(std::size_t index { UINT8_C(0) }; index < std::size_t { UINT8_C(32) }; ++index)
  {
    std::stringstream strm { };

    const double sin_val { math::const_functions::sin(dx) };
    const double ctrl { std::sin(dx) };

    strm << "dx: " << std::setprecision(2) << std::fixed << dx << ", sin_val: " << std::setprecision(std::numeric_limits<double>::digits10) << sin_val << '\n';
    strm << "dx: " << std::setprecision(2) << std::fixed << dx << ", ctrl   : " << std::setprecision(std::numeric_limits<double>::digits10) << ctrl;

    std::cout << strm.str() << std::endl;

    const bool result_sin_is_ok { is_close_fraction(sin_val, ctrl, std::numeric_limits<double>::epsilon() * 48) };

    result_is_ok = (result_sin_is_ok && result_is_ok);

    dx += 0.5;
  }

  {
    std::stringstream strm { };

    strm << "result_is_ok: " << std::boolalpha << result_is_ok << '\n';

    std::cout << strm.str() << std::endl;
  }

  return (result_is_ok ? 0 : -1);
}
