///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2013.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef UTIL_LINEAR_INTERPOLATE_2008_11_22_H_
  #define UTIL_LINEAR_INTERPOLATE_2008_11_22_H_

  #include <util/utility/util_point.h>

  namespace util
  {
    template<typename point_iterator,
             typename x_type,
             typename y_type = x_type>
    y_type linear_interpolate(point_iterator pts_begin,
                              point_iterator pts_end,
                              const x_type& x,
                              const y_type& offset)
    {
      if(pts_begin == pts_end)
      {
        // There are no data points to interpolate.
        return y_type();
      }
      else if(   (x <= pts_begin->x)
              || ((pts_begin + 1U) == pts_end))
      {
        // We are beneath the lower x-range or there
        // is only one data point to interpolate.
        return pts_begin->y;
      }
      else if(x >= (pts_end - 1U)->x)
      {
        // We are above the upper x-range.
        return (pts_end - 1U)->y;
      }
      else
      {
        // Find the interpolation pair with binary search.
        point_iterator it = std::lower_bound(pts_begin,
                                             pts_end,
                                             point<x_type>(x));

        // Do the linear interpolation.
        const x_type xn       = (it - 1U)->x;
        const x_type delta_xn = it->x - xn;
        const x_type delta_x  = x - xn;
        const y_type yn       = (it - 1U)->y;
        const y_type delta_yn = it->y - yn;

        const y_type delta_y = (delta_x * delta_yn) / delta_xn;

        return (yn + delta_y) + offset;
      }
    }
  }

#endif // UTIL_LINEAR_INTERPOLATE_2008_11_22_H_
