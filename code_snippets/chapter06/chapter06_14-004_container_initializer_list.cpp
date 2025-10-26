///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2019 - 2025.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

// chapter06_14-004_container_initializer_list.cpp

#include <initializer_list>
#include <iostream>
#include <vector>

const std::vector<char> v{ { '1', '.', '2', '3', '\0' } };

auto main() -> int;

auto main() -> int
{
  std::cout << "v.data(): "
            <<  v.data()
            << std::endl;
}
