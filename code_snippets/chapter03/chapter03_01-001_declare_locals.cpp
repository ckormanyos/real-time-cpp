///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2017 - 2025.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

// chapter_03_01-001_declare_locals.cpp

#include <iostream>

void initialize() { std::cout << "initialization" << std::endl; }

auto use_i(const int i) -> void { std::cout << "i = " << i << std::endl; }
auto use_j(const int j) -> void { std::cout << "j = " << j << std::endl; }
auto use_k(const int k) -> void { std::cout << "k = " << k << std::endl; }

auto do_something() -> void
{
  // Initialize someting.
  initialize();

  // Declare i when using it in use_i().
  const int i { 3 };
  use_i(i);

  // Declare j when using it in use_j().
  const int j { 7 };
  use_j(j);

  // Declare k in the scope of the for-loop.
  for(int k = 0; k < 10; ++k)
  {
    use_k(k);
  }
}

auto main() -> int
{
  do_something();
}
