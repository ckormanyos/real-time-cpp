///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2017 - 2025.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

// chapter03_17-003_user_defined_literals.cpp

#include <chrono>
#include <iostream>

using namespace std::chrono_literals;

std::chrono::milliseconds time_span { 10ms };

auto main() -> int
{
// time_span is 10.
  std::cout << time_span.count() << std::endl;
}
