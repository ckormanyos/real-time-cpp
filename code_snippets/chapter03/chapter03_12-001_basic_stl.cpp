///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2017 - 2025.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

// chapter03_12-001_basic_stl.cpp

#include <algorithm>
#include <array>
#include <cstdint>
#include <iostream>
#include <iterator>

namespace
{
  // Four counters.
  std::array<std::uint8_t, 4U> counters;
}

auto do_something() -> void
{
  // (Re-)Initialize the counters with std::fill().
  std::fill(counters.begin(),
            counters.end(),
            static_cast<std::uint8_t>(0U));

  // Do something with the counters.
  std::for_each(counters.begin(),
                counters.end(),
                [](std::uint8_t& c)
                {
                  ++c;
                });
}

auto main() -> int
{
  do_something();

  std::cout << "counters are ";
  std::copy(counters.cbegin(), counters.cend(), std::ostream_iterator<unsigned int>(std::cout, ","));
  std::cout << std::endl;
}
