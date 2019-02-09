///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2019.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

// appendix0a_03-001_function_overloading.cpp

#include <iostream>

// The area of a rectangle.
float area(const float& length,
           const float& width)
{
  return length * width;
}

// The area of a circle.
float area(const float& radius)
{
  constexpr float pi = 3.14159265358979323846F;

  return (pi * radius) * radius;
}

int main()
{
  std::cout << "area rectangle: " << area(1.2F, 3.4F)  << std::endl;
  std::cout << "area circle   : " << area(1.234F)      << std::endl;
}
