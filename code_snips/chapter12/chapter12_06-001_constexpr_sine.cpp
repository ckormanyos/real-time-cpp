///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2017 - 2018.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

// chapter12_06-001_constexpr_sine.cpp

#include <cstdint>
#include <iomanip>
#include <iostream>
#include <limits>

template<typename T>
constexpr T pi =
  T(3.1415926535'8979323846'2643383279'5028841972L);

// Scale the argument.
#define CHI_S T(T(x * 2) / pi<T>)

// Take the absolute value of CHI.
#define IS_NEG bool(CHI_S < T(0))
#define CHI_A  T(IS_NEG ? -CHI_S : CHI_S)

// Do the argument reduction.
#define NPI2 std::uint32_t(CHI_A / 2)
#define NPI  std::uint32_t(               \
              (CHI_A - (NPI2 * 2) > T(1)) \
                ? NPI2 + 1                \
                : NPI2)

#define CHI  T(CHI_A - T(NPI * 2))
#define CHI2 T(CHI * CHI)

// Do the order-19 polynomial expansion.
#define SUM                                       \
  (((((((((- T(4.2468171354841523379493663E-14L)  \
    * CHI2 + T(6.0640855645940930588123490E-12L)) \
    * CHI2 - T(6.6880001786329819459555395E-10L)) \
    * CHI2 + T(5.6921726597221657560994942E-08L)) \
    * CHI2 - T(3.5988432339708525153771884E-06L)) \
    * CHI2 + T(1.6044118478699232812460184E-04L)) \
    * CHI2 - T(4.6817541353186228516958362E-03L)) \
    * CHI2 + T(7.9692626246167038770053004E-02L)) \
    * CHI2 - T(6.4596409750624625337325359E-01L)) \
    * CHI2 + T(1.5707963267948966192276341E+00L)) \
    * CHI

// Reflect the result if necessary.
#define NEEDS_REFLECT bool((NPI % 2) != 0)

namespace math { namespace const_functions {

template<typename T>
constexpr T sin(T x)
{
  return ((NEEDS_REFLECT == IS_NEG) ? SUM : -SUM);
}

} } // namespace math::const_functions

constexpr double y = math::const_functions::sin(0.5);

int main()
{
  // 0.47942553860420301
  std::cout << std::setprecision(std::numeric_limits<double>::max_digits10)
            << y
            << std::endl;
}
