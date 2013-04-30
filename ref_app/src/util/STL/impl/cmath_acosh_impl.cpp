///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2013.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <cmath>
#include <limits>

// The acosh function is implemented here using logarithmic functions.
// This provides an example of a transcendental function calculation.
// Note that double is the same as float for this compier.

namespace
{
  template<typename float_type>
  inline float_type acosh_template(float_type x)
  {
    using std::log;

    if(x < float_type(1))
    {
      return std::numeric_limits<float_type>::quiet_NaN();
    }
    else if(1 == x)
    {
      return float_type(0);
    }
    else
    {
      const float_type xp(x + 1);
      const float_type xm(x - 1);
      return log(x + (xp * sqrt(xm / xp)));
    }
  }
}

float  acosh(float x)  { return acosh_template(x); }
double acosh(double x) { return acosh_template(x); }
