///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2025.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <expected>
#include <iostream>

// chapter03_23-001_expected_div_int.cpp

enum class div_error
{
  div_none,
  div_by_zero
};

auto safe_divide(int a, int b) noexcept -> std::expected<int, div_error>
{
  if (b == 0)
  {
    return std::unexpected(div_error::div_by_zero);
  }
  else
  {
    return a / b;
  }
}

auto do_something() -> void
{
  // Division by zero.
  auto result = safe_divide(10, 0);

  if (result.error() == div_error::div_by_zero)
  {
    std::cout << "Division by zero" << std::endl;
  }
  else
  {
    std::cout << "Division ok, result: " << *result << std::endl;
  }

  result = safe_divide(10, 2);

  if (result.error() == div_error::div_by_zero)
  {
    std::cout << "Division by zero" << std::endl;
  }
  else
  {
    // Division ok, result: 5
    std::cout << "Division ok, result: " << *result << std::endl;
  }
}

auto main() -> int
{
  do_something();
}
