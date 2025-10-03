///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2017 - 2025.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

// chapter03_17-001_user_defined_literals.cpp

#include <iostream>

inline constexpr auto
operator"" _inch(long double inches) -> float
{
  return static_cast<float>(inches * 0.0254L);
}

inline constexpr auto
operator"" _foot(long double feet) -> float
{
  return static_cast<float>(feet * 0.294L);
}

inline constexpr auto
operator"" _yard(long double yards) -> float
{
  return static_cast<float>(yards * 0.9144L);
}

constexpr float
one_foot          { 12.0_inch }; // 0.3048m

constexpr float
basketball_player { 7.0_foot };  // 2.058m

constexpr float
football_field    { 100.0_yard }; // 91.44m

auto main() -> int
{
  std::cout << "one_foot          is " << one_foot          << "m" << std::endl;
  std::cout << "basketball_player is " << basketball_player << "m" << std::endl;
  std::cout << "football_field    is " << football_field    << "m" << std::endl;
}
