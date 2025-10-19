///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2019- 2025.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

// chapter05_13-003_exp_series.cpp

#include <array>
#include <cmath>
#include <iostream>
#include <sstream>
#include <utility>

template<typename integral_type,
         const integral_type... I,
         typename floating_point_type>
constexpr auto exp_series(
  std::integer_sequence<integral_type, I...>,
  const floating_point_type x)
    -> floating_point_type
{
  static_assert(std::is_floating_point_v<floating_point_type>);

  floating_point_type term(1.0L);
  floating_point_type sum (0.0L);

  for(const integral_type& i : { I... })
  {
    sum += term;

    term *= x;
    term /= static_cast<floating_point_type>(i);
  }

  return sum;
}

// 1.10517...
constexpr float exp_tenth
  {
    exp_series(
      std::integer_sequence
      <unsigned, 1U, 2U, 3U, 4U>(),
      0.1F)
  };

static_assert
(
  (exp_tenth > 1.10516F) && (exp_tenth < 1.10518F)
);

auto main() -> int;

auto main() -> int
{
  std::stringstream strm { };

  using std::exp;

  strm << "exp_tenth (series) : " << std::fixed << exp_tenth << '\n';
  strm << "exp_tenth (<cmath>): " << std::fixed << exp(0.1F) << '\n';

  std::cout << strm.str() << std::endl;
}
