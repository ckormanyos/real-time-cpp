///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2025.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

// chapter05_14-001_stirlings_approx_complex.cpp

#include <cmath>
#include <complex>
#include <iomanip>
#include <iostream>
#include <limits>
#include <numbers>
#include <sstream>

template<typename T>
struct make_scalar
{
  using type = T;
};

template<typename T>
struct make_scalar<std::complex<T>>
{
  using type = typename std::complex<T>::value_type;
};

template<typename T>
using make_scalar_t = typename make_scalar<T>::type;

template<typename T>
constexpr auto tgamma_order_2(T x) -> T
{
  using namespace std::numbers;

  using std::pow;
  using std::sqrt;

  using real_type = make_scalar_t<T>;

  const T sqx { sqrt2_v<real_type> * sqrt(pi_v<real_type> / x) };

  constexpr T one { 1 };

  return T { pow(x / e_v<real_type>, x) } * sqx * (one + one / (T { 12 } * x));
}

auto main() -> int
{
  std::stringstream strm { };

  constexpr std::streamsize prec { std::numeric_limits<float>::digits10 + 1 };

  // Ensure that compilation works for real.
  const auto tg { tgamma_order_2(20.0F) };
  static_cast<void>(tg);

  // Perform a test at a complex-valued point.
  const auto tg_cpx { tgamma_order_2(std::complex(21.25F, 11.75F)) };
  constexpr std::complex ctrl(1.750357666990216354e+16F, -2.1750138237828702757e+17F);

  strm << std::setprecision(prec) << "tg_cpx: " << tg_cpx << "\nctrl:   " << ctrl;

  std::cout << strm.str() << std::endl;
}
