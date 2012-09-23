/*
#include "../cmath_impl.h"
#include "../limits_impl.h"

// The acosh function is implemented here for the AVR.
// This provides an example of a special function calculation.
// Note that double is the same as float for AVR.

float acosh(float x)
{
  if(!isfinite(x))
  {
    return x;
  }

  if(x < 1.0)
  {
    return std::numeric_limits<float>::quiet_NaN();
  }
  else if(1 == x)
  {
    return 0.0;
  }
  else
  {
    const float xp(x + 1);
    const float xm(x - 1);
    return log(x + (xp * sqrt(xm / xp)));
  }
}

double acosh(double x)
{
  return static_cast<double>(acosh(static_cast<float>(x)));
}
*/
