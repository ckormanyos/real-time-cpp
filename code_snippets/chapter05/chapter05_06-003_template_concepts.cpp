///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2017 - 2025.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <concepts>
#include <iostream>
#include <string>

// chapter05_06-003_template_concepts.cpp

// Generic add template function.
template<typename T>
auto add(const T& a, const T& b) -> T
{
  return a + b;
}

template<typename T>
requires std::integral<T>
auto add(const T& a, const T& b) -> T
{
  return a + b;
}

template<typename T>
requires std::floating_point<T>
auto add(const T&, const T&) -> T
{
  // A clear error for floating-point types.
  static_assert(false, "Error not allowed");

  return T { 0.0F };
}

auto do_something() -> void;

auto do_something() -> void
{
  // 3
  const unsigned c { add(1U, 2U) };

  std::cout << c << std::endl;

  // abcxyz
  const std::string str
    { add(std::string("abc"), std::string("xyz")) };

  std::cout << str << std::endl;

  // Error for instantiation with float is not allowed.
  //const float flt { add(1.0F, 2.0F) };
}

auto main() -> int;

auto main() -> int
{
  do_something();
}
