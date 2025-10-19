///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2017 - 2025.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

// chapter05_05-001_template_point.cpp

#include <cstdint>
#include <iostream>

template<typename x_type = std::uint16_t,
         typename y_type = x_type>
class point
{
public:
  x_type my_x;
  y_type my_y;

  explicit constexpr point(const x_type& x = x_type(),
                           const y_type& y = y_type())
    : my_x { x },
      my_y { y } { }
};

// An (x16, y16) point.
point<> pt16_16
{
  UINT16_C(1234),
  UINT16_C(5678)
};

// An (x8, y8) point.
point<std::uint8_t>
pt08_08
{
  UINT8_C(12),
  UINT8_C(34)
};

// An (x8, y16) point.
point<std::uint8_t,
      std::uint16_t>
pt08_16
{
  UINT8_C(34),
  UINT16_C(5678)
};

auto main() -> int;

auto main() -> int
{
  std::cout << "pt16_16: "
            << "(" << unsigned(pt16_16.my_x) << "," << unsigned(pt16_16.my_y) << ")"
            << std::endl;

  std::cout << "pt08_08: "
            << "(" << unsigned(pt08_08.my_x) << "," << unsigned(pt08_08.my_y) << ")"
            << std::endl;

  std::cout << "pt08_16: "
            << "(" << unsigned(pt08_16.my_x) << "," << unsigned(pt08_16.my_y) << ")"
            << std::endl;
}
