///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2017 - 2025.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

// chapter03_13-001_basic_stl_numeric.cpp

#include <array>
#include <iostream>
#include <numeric>

const std::array<int, 3U> u
{
  { 1, 2, 3 }
};

const std::array<int, 3U> v
{
  { 4, 5, 6 }
};

const int uv = std::inner_product(u.cbegin(),
                                  u.cend(),
                                  v.cbegin(),
                                  0);
// The result is 32.

auto main() -> int
{
  std::cout << "inner product uv is " << uv << std::endl;
}
