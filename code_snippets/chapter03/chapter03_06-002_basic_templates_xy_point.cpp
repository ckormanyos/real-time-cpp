///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2017 - 2025.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

// chapter03_06-002_basic_templates_xy_point.cpp

#include <cstdint>
#include <iostream>
#include <type_traits>

// Template version of the xy-coordinate class.

template<typename short_type,
         typename long_type>
class point
{
public:
  static_assert(
       std::is_integral<short_type>::value
    && std::is_integral<long_type>::value,
       "the short and long types must be integral");

  short_type my_x { };
  short_type my_y { };

  point(const short_type& x = short_type(),
        const short_type& y = short_type()) : my_x(x),
                                              my_y(y)
  { }

  long_type squared_euclidean_distance() const
  {
    // Squared Euclidean distance from the origin.
    const long_type x2(long_type(my_x) * my_x);
    const long_type y2(long_type(my_y) * my_y);

    return x2 + y2;
  }
};

point<std::int16_t, std::int32_t> p
{
  INT16_C(-2129),
  INT16_C(+5471)
};

const std::int32_t d { p.squared_euclidean_distance() };
// d is 34,464,482

auto main() -> int
{
  std::cout << "d is " << d << std::endl;
}
