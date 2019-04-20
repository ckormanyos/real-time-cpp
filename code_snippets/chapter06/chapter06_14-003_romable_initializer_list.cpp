///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2019.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

// chapter06_14-003_romable_initializer_list.cpp

#include <initializer_list>
#include <iomanip>
#include <iostream>

namespace
{
  constexpr std::initializer_list<char>
  version_string
  {
    { '1', '.', '2', '3', '\0' }
  };
}

static_assert(
  *version_string.begin() == char('1'));

int main()
{

  std::cout << std::hex
            << "version_string[0U]: 0x"
            << std::setw(2)
            << std::setfill(static_cast<char>('0'))
            << static_cast<unsigned>(*version_string.begin())
            << std::endl;

  std::cout << "version_string: "
            << version_string.begin()
            << std::endl;
}
