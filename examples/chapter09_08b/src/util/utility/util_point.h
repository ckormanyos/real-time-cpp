///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2025.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef UTIL_POINT_2008_11_22_H
  #define UTIL_POINT_2008_11_22_H

  namespace util
  {
    template<typename x_type,
             typename y_type = x_type>
    struct point
    {
      x_type x { };
      y_type y { };

      explicit constexpr point(const x_type& x0 = x_type(),
                               const y_type& y0 = y_type()) : x { x0 },
                                                              y { y0 } { }

      constexpr point(const point& other) : x { other.x },
                                            y { other.y } { }

      constexpr point(point&& other) : x { other.x },
                                       y { other.y } { }

      ~point() = default;

      constexpr auto operator=(const point& other) -> point&
      {
        if(this != &other)
        {
          x = other.x;
          y = other.y;
        }

        return *this;
      }

      constexpr auto operator=(point&& other) -> point&
      {
        x = other.x;
        y = other.y;

        return *this;
      }

      constexpr auto operator<(const point& other) const -> bool
      {
        return (x < other.x);
      }
    };

    template<typename x_type, typename y_type>
    constexpr auto operator==(const point<x_type, y_type>& left, const point<x_type, y_type>& right) -> bool
    {
      return (   (left.x  == right.x)
              && (left.y == right.y));
    }

    template<typename x_type, typename y_type>
    constexpr auto operator!=(const point<x_type, y_type>& left, const point<x_type, y_type>& right) -> bool
    {
      return (   (left.x  != right.x)
              || (left.y != right.y));
    }

    template<typename x_type, typename y_type>
    constexpr auto operator<(const point<x_type, y_type>& left, const point<x_type, y_type>& right) -> bool
    {
      return ((left.x < right.x)
               ? true
               : ((right.x < left.x)
                   ? false
                   : ((left.y < right.y) ? true : false)));
    }

    template<typename x_type, typename y_type>
    constexpr auto operator<=(const point<x_type, y_type>& left, const point<x_type, y_type>& right) -> bool
    {
      return (!(right < left));
    }

    template<typename x_type, typename y_type>
    constexpr auto operator>(const point<x_type, y_type>& left, const point<x_type, y_type>& right) -> bool
    {
      return (right < left);
    }

    template<typename x_type, typename y_type>
    constexpr auto operator>=(const point<x_type, y_type>& left, const point<x_type, y_type>& right) -> bool
    {
      return (!(left < right));
    }
  } // namespace util

#endif // UTIL_POINT_2008_11_22_H
