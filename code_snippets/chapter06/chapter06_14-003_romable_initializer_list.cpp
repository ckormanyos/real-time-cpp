///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2019 - 2025.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

// chapter06_14-003_romable_initializer_list.cpp

// See also https://godbolt.org/z/qGh6WMYvh

#include <cstddef>
#include <cstdint>
#include <initializer_list>
#include <iomanip>
#include <iostream>
#include <sstream>

namespace
{
  constexpr auto version_string =
    std::initializer_list<char>
    {
      '1', '.', '2', '3', '\0'
    };
}

static_assert(*version_string.begin() == '1',  "Error: Wrong value at begin of initializer_list.");

auto main() -> int;

auto main() -> int
{
  std::stringstream strm { };

  strm << std::hex
       << "version_string[0U]: 0x"
       << std::setw(2)
       << std::setfill('0')
       << static_cast<unsigned>(*version_string.begin())
       << '\n';

  strm << "version_string: "
       << version_string.begin();

  std::cout << strm.str() << std::endl;
}
