///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2019- 2025.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

// chapter05_13-001_integer_sequence.cpp

#include <iostream>
#include <utility>

template<typename integral_type,
         const integral_type... I>
constexpr auto sequence_accumulate(
  std::integer_sequence<integral_type, I...>)
    -> integral_type
{
  integral_type sum { };

  for(const integral_type& i : { I... })
  {
    sum += i;
  }

  return sum;
}

constexpr
std::integer_sequence
  <unsigned, 1U, 3U, 5U, 7U> int_seq;

// 16
constexpr unsigned sum { sequence_accumulate(int_seq) };

static_assert(sum == 16U);

auto main() -> int;

auto main() -> int
{
  std::cout << sum << std::endl;
}
