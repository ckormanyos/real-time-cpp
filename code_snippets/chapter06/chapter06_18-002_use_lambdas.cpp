///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2019 - 2025.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

// chapter06_18-002_use_lambdas.cpp

#include <algorithm>
#include <cstddef>
#include <cstdint>
#include <iostream>

using function_type = void(*)();

extern function_type ctors_begin[];
extern function_type ctors_end  [];

namespace
{
  auto call_ctor(const function_type& pf) -> void;

  auto call_ctor(const function_type& pf) -> void { pf(); }
}

auto init_ctors() -> void
{
  std::for_each(ctors_begin,
                ctors_begin + std::size_t { UINT8_C(3) },
                call_ctor);
}

auto main() -> int;

auto main() -> int
{
  init_ctors();
}

auto simulated_constructor1() -> void { std::cout << "simulated_constructor1()" << std::endl; }
auto simulated_constructor2() -> void { std::cout << "simulated_constructor2()" << std::endl; }
auto simulated_constructor3() -> void { std::cout << "simulated_constructor3()" << std::endl; }

function_type ctors_begin[std::size_t { UINT8_C(3) }] =
{
  simulated_constructor1,
  simulated_constructor2,
  simulated_constructor3
};
