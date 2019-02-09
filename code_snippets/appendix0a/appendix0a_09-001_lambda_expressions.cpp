///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2019.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

// appendix0a_09-001_lambda_expressions.cpp

#include <cmath>
#include <iostream>

void do_something()
{
  const float x = 3.0F;
  const float y = 4.0F;

  // Capture x and y by reference.
  // The lambda expression has no input parameters.
  // The lambda expression returns the float value
  // of the hypotenuse h.

  // The value of h is 5.
  const float h =
    [&x, &y]() -> float
    {
      return std::sqrt((x * x) + (y * y));
    }();

  std::cout << "h: " << h << std::endl;
}

int main()
{
  do_something();
}
