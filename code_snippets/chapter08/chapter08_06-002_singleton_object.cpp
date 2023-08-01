///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2019 - 2023.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

// chapter08_06-002_singleton_object.cpp

// See also https://godbolt.org/z/oh9PEqqnW

#include <cstdint>
#include <iostream>

struct alpha
{
  std::uint16_t value { };

  explicit constexpr alpha(const std::uint16_t a) : value(a) { }
};

// In file beta.cpp.
// OK, but mind the overhead.
extern auto safe_reference_to_alpha() -> alpha&;

// OK, safe_reference_to_alpha() returns
// an initialized, fully-formed object.
auto beta = std::uint16_t { safe_reference_to_alpha().value };

auto main() -> int;

auto main() -> int
{
  std::cout << "instance_of_alpha.value: "
            << static_cast<std::uint32_t>(safe_reference_to_alpha().value)
            << std::endl;

  std::cout << "beta: "
            << static_cast<std::uint32_t>(beta)
            << std::endl;
}

// In file alpha.cpp.
auto safe_reference_to_alpha() -> alpha&
{
  static auto instance_of_alpha = alpha { static_cast<std::uint16_t>(UINT8_C(3)) };

  return instance_of_alpha;
}
