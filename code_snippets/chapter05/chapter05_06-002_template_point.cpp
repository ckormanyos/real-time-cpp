///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2017 - 2023.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

// chapter05_06-002_template_point.cpp

#include <cstdint>
#include <iostream>

template<typename x_type,
         typename y_type>
class point
{
public:
  x_type my_x { };
  y_type my_y { };

  explicit constexpr point(const x_type& x = x_type { },
                           const y_type& y = y_type { })
    : my_x(x),
      my_y(y) { }
};

// A partial specialization of the point
// class with x-axis having type std::uint8_t.

template<typename y_type>
class point<std::uint8_t, y_type>
{
public:
  std::uint8_t my_x { };
  y_type       my_y { };

  explicit constexpr point(const std::uint8_t& x = std::uint8_t { },
                           const y_type&       y = y_type { })
    : my_x(x),
      my_y(y)
  {
    std::cout << "In the constructor of the template specialization." << std::endl;
  }
};

// An (x8, y16) point.
point<std::uint8_t, std::uint16_t> pt08_16
{
  static_cast<std::uint8_t>(UINT8_C(34)),
  static_cast<std::uint16_t>(UINT16_C(5678))
};

int main()
{
  std::cout << "pt08_16: "
            << "(" << unsigned(pt08_16.my_x) << "," << unsigned(pt08_16.my_y) << ")"
            << std::endl;
}
