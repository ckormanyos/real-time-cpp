///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2018 - 2025.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

// chapter05_10-003_const_eval_inner_product.cpp

#include <array>
#include <iostream>
#include <numeric>

// chapter05_10-003_const_eval_inner_product.cpp

constexpr std::array<unsigned, 3U> u
{
  { 1U, 2U, 3U }
};

constexpr std::array<unsigned, 3U> v
{
  { 4U, 5U, 6U }
};

// The result is 32.
constexpr unsigned w
{
  std::inner_product(u.cbegin(),
                     u.cend(),
                     v.cbegin(),
                     0U)
};

static_assert(w == 32U, "Error in inner_produce");

auto main() -> int;

auto main() -> int
{
  std::cout << "Result of inner product is: " << w << std::endl;
}
