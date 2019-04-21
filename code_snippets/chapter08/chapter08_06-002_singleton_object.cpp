///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2019.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

// chapter08_06-002_singleton_object.cpp

#include <cstdint>
#include <iostream>

struct alpha
{
  std::uint16_t value;

  alpha(const std::uint16_t a) : value(a) { }
};


// In file beta.cpp.
// OK, but mind the overhead.
extern alpha& safe_reference_to_alpha();

// OK, safe_reference_to_alpha() returns
// an initialized, fully-formed object.
std::uint16_t beta
{
  safe_reference_to_alpha().value
};

int main()
{
  std::cout << "instance_of_alpha.value: "
            << static_cast<std::uint32_t>(safe_reference_to_alpha().value)
            << std::endl;

  std::cout << "beta: "
            << static_cast<std::uint32_t>(beta)
            << std::endl;
}

// In file alpha.cpp.
alpha& safe_reference_to_alpha()
{
  static alpha instance_of_alpha { 3U };

  return instance_of_alpha;
}
