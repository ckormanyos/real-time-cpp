///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2017 - 2025.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <iostream>

// chapter05_06-002_template_enable_if.cpp

// Generic add template function.
template<typename T>
auto add(const T& a, const T& b)
  -> std::enable_if_t
       <   (!std::is_integral_v<T>)
        && (!std::is_floating_point_v<T>), T>
{
  return a + b;
}

// Versions of add for integral types.
template<typename T>
auto add(const T& a, const T& b)
  -> std::enable_if_t<std::is_integral_v<T>, T>
{
  return a + b;
}

// Versions of add for floating-point types.
template<typename T>
auto add(const T&, const T&)
  -> std::enable_if_t<std::is_floating_point_v<T>, T>
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
