///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2019 - 2025.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

// chapter06_08-001_comments_sparingly.cpp

void CalculateSpeed();

void CalculateSpeed() { }

auto main() -> int;

auto main() -> int
{
  // This is an example of a potentially redundant comment.

  CalculateSpeed(); // Calculate speed.
}
