///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2017 - 2025.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

// chapter03_05-001_basic_classes.cpp

#include <cstdint>
#include <iostream>

// An unsigned xy-coordinate point with some geometry.
class point
{
public:
  std::uint8_t my_x { };
  std::uint8_t my_y { };

  point(const std::uint8_t x = UINT8_C(0),
        const std::uint8_t y = UINT8_C(0)) : my_x(x),
                                             my_y(y)
  { }

  auto squared_euclidean_distance() const -> std::uint16_t
  {
    // Squared Euclidean distance from the origin.
    const std::uint16_t x2(std::uint16_t(my_x) * my_x);
    const std::uint16_t y2(std::uint16_t(my_y) * my_y);

    return x2 + y2;
  }
};

point p1 { };

point p2
{
  UINT8_C(31),
  UINT8_C(47)
};

// The squared Euclidean distance d1 is 0.
std::uint16_t d1 { p1.squared_euclidean_distance() };

// The squared Euclidean distance d2 is 3,170.
std::uint16_t d2 { p2.squared_euclidean_distance() };

auto main() -> int
{
  std::cout << "d1 is " << d1 << std::endl;
  std::cout << "d2 is " << d2 << std::endl;
}
