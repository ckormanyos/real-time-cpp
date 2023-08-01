///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2019 - 2023.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

// appendix0a_08-004_stl_algorithms.cpp

// See also https://godbolt.org/z/Gar4Yjh8n

#include <algorithm>
#include <cstddef>
#include <cstdint>
#include <iostream>
#include <vector>

auto do_something() -> void
{
  // Set v to (1,2,3).
  auto v = std::vector<int>(static_cast<std::size_t>(UINT8_C(3)));

  v[static_cast<std::size_t>(UINT8_C(0))] = static_cast<int>(INT8_C(1));
  v[static_cast<std::size_t>(UINT8_C(1))] = static_cast<int>(INT8_C(2));
  v[static_cast<std::size_t>(UINT8_C(2))] = static_cast<int>(INT8_C(3));

  std::cout << "v: ";
  for(int element : v) { std::cout << element << ","; }
  std::cout << std::endl;

  // Add 5 to each element in v, giving (6,7,8).
  std::for_each(v.begin(),
                v.end(),
                [](int& elem)
                {
                  elem += static_cast<int>(INT8_C(5));
                });

  std::cout << "v: ";
  for(int element : v) { std::cout << element << ","; }
  std::cout << std::endl;
}

auto main() -> int;

auto main() -> int
{
  do_something();
}
